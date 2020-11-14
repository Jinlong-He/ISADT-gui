//
//  AttributeTerm.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_AttributeTerm_hpp
#define Model_AttributeTerm_hpp
#include "Term.hpp"
#include "../../Process/Attribute.hpp"

namespace isadt {
    /// \breif the attribute term in the action
    class AttributeTerm : public Term {
    public:
        AttributeTerm()
            : Term(),
              attribute_(nullptr) {}

        AttributeTerm(Attribute* attribute)
            : attribute_(attribute) {}

        string to_string() const;
        UserType* getType() const;
        bool isBeagleAvailable() const;
        bool isAtomic() const;
        TermType getTermType() const;
        Attribute* getAttribute() const;
    private:
        Attribute* attribute_;       //< attribute of the term
    };
}

#endif /* Model_AttributeTerm_hpp */
