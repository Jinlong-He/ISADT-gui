//
//  UserType.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_UserType_hpp
#define Model_UserType_hpp 
#include "../Struct/Class.hpp"

namespace isadt {
    /// \brief the user defined data type of process.
    class UserType : public Class {
    public:
        UserType()
            : Class() {}

        UserType(const string& name, 
                 UserType* base = nullptr)
            : Class(name),
              base_(base) {}

        ~UserType() {}

        UserType* getBase();
        void setBase(UserType* base);
    private:
        UserType* base_;                  //< the base type of this type.
    };
}

#endif /* Model_UserType_hpp */
