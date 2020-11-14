//
//  Term.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_MethodTerm_hpp
#define Model_MethodTerm_hpp
#include "Term.hpp"
#include "AttributeTerm.hpp"
#include "ConstTerm.hpp"
#include "../../Process/MethodBase.hpp"

namespace isadt {
    /// \breif the method term in the action
    /// \breif the method term can be a method with a series of args.
    class MethodTerm : public Term {
    public:
        MethodTerm()
            : Term(),
              method_(nullptr) {}

        MethodTerm(MethodBase* method)
            : Term(),
              method_(method) {}

        ~MethodTerm() {
        }

        MethodTerm(const string& toParse); // create a method term from string.

        void pushfrontArg(Term* term);
        void pushbackArg(Term* term);

        MethodBase* getMethod();
        const list<Term*>& getArgs() const;

        bool isAMethodCall() {return true;};
        bool isAVariableSetting() {return false;};
        bool isLeftHand() {return false;} // method term can be only appear in the rightHand of the action.
        bool containMethodCall() {return true;}
        string to_string() const;
        UserType* getType() const;
        bool isBeagleAvailable() const;
        bool isAtomic() const;
        TermType getTermType() const;
    private:
        MethodBase* method_;    //< the method in the method term
        list<Term*> args_;  //< the args in the method term
    };
}


#endif /* Model_MethodTerm_hpp */
