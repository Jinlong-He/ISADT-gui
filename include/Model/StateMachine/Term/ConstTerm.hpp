//
//  Term.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//
//TODO
#ifndef Model_ConstTerm_hpp
#define Model_ConstTerm_hpp
#include "Term.hpp"
#include "../../Process/Attribute.hpp"

namespace isadt {
  /// \breif the attribute term in the action
    class ConstTerm : public Term {
    public:
        ConstTerm()
            : type_(nullptr),
              typeStr_(""),
              valueStr_("") {}

        ConstTerm(UserType* type, const string& valueStr)
            : type_(type),
              typeStr_(type -> getName()),
              valueStr_(valueStr) {}

        const string& getTypeStr() const;
        const string& getValueStr() const;
        bool getBoolValue() const;
        int getIntValue() const;

        string to_string() const;
        UserType* getType() const;
        bool isBeagleAvailable() const;
        bool isAtomic() const;
        TermType getTermType() const;
    private:
        UserType* type_;
        string typeStr_;
        string valueStr_;
    };
}

#endif /* Model_AttributeTerm_hpp */
