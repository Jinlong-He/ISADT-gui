//
//  Method.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_MethodBase_hpp
#define Model_MethodBase_hpp 
#include "../Struct/Struct.hpp"
namespace isadt {
    class UserType;
    /// \brief the method of process.
    class MethodBase : public Struct {
    public:
        MethodBase()
            : Struct(),
              returnType_(nullptr) {}

        MethodBase(const string& name)
            : Struct(name),
              returnType_(nullptr) {}

        MethodBase(const string& name, 
                   UserType* returnType)
            : Struct(name),
              returnType_(returnType) {}

        virtual bool isCommMethod() const = 0;

        ~MethodBase() {}

        UserType* getReturnType() const;
        void setReturnType(UserType* returnType);
    private:
        UserType* returnType_;
    };
}

#endif /* Model_Method_hpp */
