//
//  Edge.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Edge_hpp
#define Model_Edge_hpp
#include <list>
#include <iostream>
#include "Vertex.hpp"
#include "Guard/Guard.hpp"
#include "Action/Action.hpp"
#include "Term/ListTerm.hpp"
using std::list;

namespace isadt {
    class Process;
	/// \brief transition in the StateMachine 
	class Edge {
    public:
    	/// \brief Edge constructor 
        Edge() 
            : from_(nullptr),
              to_(nullptr),
              guard_(nullptr) {}

    	Edge(Vertex* from, Vertex* to)
            : from_(from),
              to_(to),
              guard_(nullptr) {
                  from -> addNext(this);
              }

    	Edge(Vertex* from, Vertex* to, 
             Guard* guard, 
             const std::initializer_list<Action*>& actions)
            : from_(from),
              to_(to),
              guard_(guard),
              actions_(actions) {
                  from -> addNext(this);
              }

    	Edge(Vertex* from, Vertex* to, 
             const string& guardStr, 
             const std::initializer_list<string>& actionStrs);

        ~Edge() {
            if (guard_) {
                delete guard_;
                guard_ = nullptr;
            }
            for (auto action : actions_) {
                if (action) {
                    delete action;
                    action = nullptr;
                }
            }
            for (auto exp : exps_) {
                if (exp) {
                    delete exp;
                    exp = nullptr;
                }
            }
            for (auto term : terms_) {
                if (term) {
                    delete term;
                    term = nullptr;
                }
            }
        }

    	Vertex* getFromVertex();
    	void SetFromVertex(Vertex* from);

    	Vertex* getToVertex();
    	void SetToVertex(Vertex* to);

    	Guard* getGuard();

    	Guard* mkGuard(Expression* exp);

    	const list<Action*>& getActions() const;
        void setActions(const list<Action*>& actions);

    	Action* mkDeclarationAction(Attribute* attr, const string& value = "");
    	Action* mkAssignmentAction(Term* lhs, Term* rhs = nullptr);

        AttributeTerm* mkAttributeTerm(Attribute* attr);
        MethodTerm* mkMethodTerm(MethodBase* method);
        ConstTerm* mkConstTerm(UserType* type, const string& value);
        ListTerm* mkListTerm();

        Expression* mkExpression(const string& op, Term* exp1, Term* exp2 = nullptr);
        Term* cpChildren(Term* term, Term* newTerm);
        Term* cpTerm(Term* term);
        void cpActions(Edge* edge);

        string to_string() const;

    	bool hasNonDeterministicGuard();
    	bool isEmpty();
    	bool hasActions();
    	void removeAllActions();
    	void removeFirstAction();
	private:
    	Vertex* from_;               //< from Vertex
    	Vertex* to_;                 //< to Vertex
    	Guard* guard_;               //< transtion guard
        string guardStr_;
    	list<Action*> actions_;      //< actions on the transition
        list<string> actionStrs_;
        list<Expression*> exps_;
        list<Term*> terms_;
	};
}


#endif /* Model_Edge_hpp */
