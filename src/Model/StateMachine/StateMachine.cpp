#include "Model/StateMachine/StateMachine.hpp"
#include <iostream>
using std::cout, std::endl;
namespace isadt{
	Vertex* StateMachine::mkStartVertex(const string& name) {
		startVertex_ = mkVertex(name);
        return startVertex_;
	}

	Vertex* StateMachine::mkEndVertex(const string& name){
		endVertex_ = mkVertex(name);
        return endVertex_;
	}

    Vertex* StateMachine::mkMidVertex(Vertex* start, Vertex* end) {
        string name = start -> getName() + "_" + end -> getName();
        while (vertexMap.count(name) > 0) {
            name += "_";
        }
        return mkVertex(name);
    }

	Vertex* StateMachine::getStartVertex() {
		return startVertex_;
	}

	Vertex* StateMachine::getEndVertex() {
		return endVertex_;
	}

	Vertex* StateMachine::getParent() {
		return parent_;
	}

    Process* StateMachine::getProcess() {
        return proc_;
    }

	Vertex* StateMachine::getVertexByName(const string& name) {
        if (vertexMap.count(name) == 0) return nullptr;
        return vertexMap[name];
	}
    
	Vertex* StateMachine::getVertexByName1(const string& name) {
        if (vertexMap.count(name) == 0) return mkVertex(name);
        return vertexMap[name];
	}

	const std::list<Vertex*>& StateMachine::getVertices() const {
		return vertices_;
	}

	const std::list<Edge*>& StateMachine::getEdges() const {
		return edges_;
	}
	
	Vertex* StateMachine::mkVertex(const string& name) {
        if (vertexMap.count(name) > 0) {
            throw "error: state name " + name + " has existed.";
        }
		Vertex* vertex = new Vertex(name);
        vertices_.push_back(vertex);
        vertexMap[name] = vertex;
        return vertex;
	}

	Edge* StateMachine::mkEdge(Vertex* source, Vertex* target) {
        Edge* edge = new Edge(source, target);
		edges_.push_front(edge);
        return edge;
	}

    Vertex* StateMachine::cpVertex(Vertex* vertex, unordered_map<Vertex*, Vertex*>& vertex2Map) {
        if (vertex2Map.count(vertex) == 0) {
            auto newState = mkVertex(vertex -> getName());
            vertex2Map[vertex] = newState;
            return newState;
        } else {
            return vertex2Map.at(vertex);
        }
    }

    Edge* StateMachine::cpEdge(Edge* edge, unordered_map<Vertex*, Vertex*>& vertex2Map) {
        auto source = cpVertex(edge -> getFromVertex(), vertex2Map);
        auto target = cpVertex(edge -> getToVertex(), vertex2Map);
        auto newEdge = mkEdge(source, target);
        return cpEdge(edge, newEdge);
    }

    Edge* StateMachine::cpEdge(Edge* edge, Edge* newEdge) {
        if (edge -> getGuard()) {
            newEdge -> mkGuard((Expression*) newEdge -> cpTerm(edge -> getGuard() -> getExpression()));
        }
        for (auto action : edge -> getActions()) {
            if (action -> isAssignmentAction()) {
                newEdge -> mkAssignmentAction(newEdge -> cpTerm(action -> getLhs()),
                                              newEdge -> cpTerm(action -> getRhs()));
            } else {
                newEdge -> mkDeclarationAction(action -> getAttribute(), action -> getValue());
            }
        }
        return newEdge;
    }

    void StateMachine::print() const {
        for (auto edge : edges_) {
            cout << edge -> getFromVertex() -> getName() << "--->"
                 << edge -> getToVertex() -> getName() << endl;
            if (edge -> getGuard()) {
                cout << "Guard: " << edge -> getGuard() -> to_string() << endl;
            }

            cout << "Actions: " << endl;

            for (auto action : edge -> getActions()) {
                cout << action -> to_string() << endl;
            }
        }
    }

}
