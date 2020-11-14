//
//  Term.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Term_hpp
#define Model_Term_hpp

#include <string>
#include "../../Type/UserType.hpp"
using std::string;

namespace isadt {
    enum TermType {EXP,AT,CT,LT,MT};
	/// \breif the term in the action has two inheritance class AttributeTerm and MethodTerm.
	class Term {
	public:
        Term() {}

        virtual ~Term() {}

		bool isValidName(string _name);
		bool containAMethodCall(); //< check if the term has a MethodTerm subclass.

        void addChild(Term* term) {
            children_.push_back(term);
        }

        const list<Term*>& getChildren() const {
            return children_;
        }

        UserType* getRealType() const {
            for (auto it = children_.rbegin(); it != children_.rend(); it++) {
                if ((*it) -> to_string().find(".") != string::npos) {
                    return (*it) -> getType();
                }
            }
            //for (auto child : children_) {
            //    if (child -> to_string().find(".") != string::npos)
            //        return child -> getType();
            //}
            return getType();
        }

        virtual 
        string to_string() const {
            string res = "";
            for (auto term : children_) {
                res += term -> to_string();
            }
            return res;
        }

        virtual 
        UserType* getType() const {
            return nullptr;
        }

        virtual
        bool isBeagleAvailable() const {
            if (children_.size() > 0) return false;
            return true;
        }

        virtual
        bool isAtomic() const {
            return false;
        }

        virtual TermType getTermType() const = 0;

	private:
        list<Term*> children_;
	};
}

#endif /* Model_Term_hpp */
