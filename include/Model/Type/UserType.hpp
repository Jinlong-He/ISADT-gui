//
//  UserType.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_UserType_hpp
#define Model_UserType_hpp 
#include <iostream>
#include "../Struct/Class.hpp"

namespace isadt {
    /// \brief the user defined data type of process.
    class UserType : public Class {
    public:
        UserType()
            : Class(),
              sigLen_(0) {}

        UserType(const string& name, 
                 UserType* base = nullptr)
            : Class(name),
              base_(base),
              sigLen_(0) {}

        ~UserType() {}

        UserType* getBase();
        void setBase(UserType* base);
        void setMsgType(const string& msgType) {
            msgType_ = msgType;
        }

        const string& getMsgType() const {
            return msgType_;
        }

        void setSigLen(int sigLen) {
            sigLen_ = sigLen;
        }

        void setSigLen(const string& sigLen) {
            sigLen_ = std::stoi(sigLen);
        }

        int getSigLen() const {
            return sigLen_;
        }
    private:
        UserType* base_;                  //< the base type of this type.
        string msgType_;
        int sigLen_;
    };
}

#endif /* Model_UserType_hpp */
