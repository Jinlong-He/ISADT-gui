//
//  StateMachine.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_StateMachine_hpp
#define Model_StateMachine_hpp
#include <list>
#include <unordered_map>
#include "Vertex.hpp"
#include "Edge.hpp"
using std::string;
namespace isadt {
    class Process;

    /// \brief StateMachine class
	class StateMachine {
	public:
		StateMachine()
            : startVertex_(nullptr),
              parent_(nullptr),
              proc_(nullptr) {}

		StateMachine(Vertex* parent,
                     Process* proc)
            : startVertex_(nullptr),
              parent_(parent),
              proc_(proc) {}

		StateMachine(Process* proc)
            : startVertex_(nullptr),
              parent_(nullptr),
              proc_(proc) {}

		~StateMachine() {
            for (auto vertex : vertices_) {
                if (vertex) {
                    delete vertex;
                    vertex = nullptr;
                }
            }
            for (auto edge : edges_) {
                if (edge) {
                    delete edge;
                    edge = nullptr;
                }
            }
        }

		Vertex* mkVertex(const string& name);
		Vertex* mkStartVertex(const string& name);
		Vertex* mkEndVertex(const string& name);
		Vertex* mkMidVertex(Vertex* start, Vertex* end);
		Vertex* cpVertex(Vertex* vertex, unordered_map<Vertex* ,Vertex*>& vertex2Map);

		Vertex* getStartVertex();
		Vertex* getEndVertex();
		Vertex* getParent();
        Process* getProcess();

		const std::list<Vertex*>& getVertices() const;
		Vertex* getVertexByName(const string& name);
		Vertex* getVertexByName1(const string& name);

		const std::list<Edge*>& getEdges() const;
		Edge* mkEdge(Vertex* source, Vertex* target);
		Edge* cpEdge(Edge* edge, unordered_map<Vertex* ,Vertex*>& vertex2Map);
		Edge* cpEdge(Edge* edge, Edge* newEdge);

        void print() const;
	private:
    	list<Vertex*> vertices_;    //< the set of the states of this fsm.
    	list<Edge*> edges_;         //< the set of the transitions of this fsm.
        unordered_map<string, Vertex*> vertexMap;
    	Vertex* startVertex_;            //< record the start state of this fsm.
		Vertex* endVertex_;
        Vertex* parent_;
    	Process* proc_;               //< the StateMachine belongs to the process.
	};
}
#endif /* Model_StateMachine_hpp */
