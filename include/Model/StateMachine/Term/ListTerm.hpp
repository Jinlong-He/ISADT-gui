//
//  ListTerm.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_ListTerm_hpp
#define Model_ListTerm_hpp
#include "Term.hpp"

namespace isadt {
    /// \breif the attribute term in the action
    class ListTerm : public Term {
    public:
        ListTerm()
            : Term(){}

        void pushfrontTerm(Term* term);
        void pushbackTerm(Term* term);
        const list<Term*>& getTermList() const;

        string to_string() const;
        UserType* getType() const;
        bool isBeagleAvailable() const;
        bool isAtomic() const;
        TermType getTermType() const;
    private:
        list<Term*> list_;
    };
}

#endif /* Model_ListTerm_hpp */
