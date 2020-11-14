//
//  Action.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Action_hpp
#define Model_Action_hpp
#include <list>
#include "../Term/MethodTerm.hpp"

using std::list;
namespace isadt {
	/// \breif the Action on the transition
	class Action {
	public:
		Action()
            : lhs_(nullptr),
              rhs_(nullptr),
              attribute_(nullptr),
              value_(""),
              hasNext_(false) {}

        Action(Term* lhs, Term* rhs = nullptr)
            : lhs_(lhs),
              rhs_(rhs),
              attribute_(nullptr),
              value_(""),
              hasNext_(false) {}

        Action(Attribute* attr, const string& value = "")
            : lhs_(nullptr),
              rhs_(nullptr),
              attribute_(attr),
              value_(value),
              hasNext_(false) {}

        ~Action() {
        }

        void setNext(bool b = 1) {
            hasNext_ = b;
        }

        bool hasNext() const {
            return hasNext_;
        }

        Term* getLhs() const;
        Term* getRhs() const;
        Attribute* getAttribute() const;
        const string& getValue() const;

        bool isAssignmentAction() const;
        bool isDeclarationAction() const;

        string to_string() const;
	private:
		Term* lhs_;              //< leftHand of the assignment
		Term* rhs_;              //< rightHand can be an attribute or a method call.
        Attribute* attribute_;
        string value_;
        bool hasNext_;
	};
}
#endif /* Model_Action_hpp */
