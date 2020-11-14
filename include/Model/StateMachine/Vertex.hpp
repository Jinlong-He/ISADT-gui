//
//  Vertex.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Vertex_hpp
#define Model_Vertex_hpp
#include <string>
#include <list>
using std::string;
using std::list;

namespace isadt {
	class Edge;
    class StateMachine;
	/// \brief State in FSM.
	class Vertex {
	private:
		string name_;           //< the name of this state. 
		list<Edge*> nexts_;     //< the next states of this state.
        StateMachine* refine_;
	public:
		Vertex();

		Vertex(string name) : name_(name) {}

		Vertex(string name, const list<Edge*>& nexts) 
            : name_(name), 
              nexts_(nexts) {}

		void setName(string name) {
			name_ = name;
		}

		const string& getName() {
			return name_;
		}

        StateMachine* getRefine() {
            return refine_;
        }

        void addNext(Edge* edge) {
            nexts_.push_back(edge);
        }

        const list<Edge*> getNexts() const {
            return nexts_;
        }
	};
}

#endif /* Model_Vertex_hpp */
