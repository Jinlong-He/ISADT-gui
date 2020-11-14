//
//  Attribute.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Attribute_hpp
#define Model_Attribute_hpp 
#include <string>
using std::string;
namespace isadt {
    class UserType;
    /// \brief the attribute of process.
    class Attribute {
    public:
        Attribute()
            : type_(nullptr),
              identifier_(""),
              array_(0) {}

        Attribute(UserType* type, const string& identifier, int array = 0)
            : type_(type),
              identifier_(identifier),
              array_(array) {}

        ~Attribute() {}

        UserType* getType() const;
        void setType(UserType* type);
        const string& getIdentifier() const;
        int getArray() const;
        void setIdentifier(const string& identifier);
    private:
        UserType* type_;
        string identifier_;
        int array_;
    };
}

#endif /* Model_Attribute_hpp */
