//
//  Manage.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Manage_hpp
#define Manage_hpp 
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Model/Type/UserType.hpp"
using std::string, std::unordered_set, std::unordered_map;
namespace isadt {
    class Manage {
    public:
        Manage() {}
        
        ~Manage() {
            if (intType_) {
                delete intType_;
                intType_ = nullptr;
            }
            if (boolType_) {
                delete boolType_;
                boolType_ = nullptr;
            }
            if (byteType_) {
                delete byteType_;
                byteType_ = nullptr;
            }
            if (byteVecType_) {
                delete byteVecType_;
                byteVecType_ = nullptr;
            }
            if (timerType_) {
                delete timerType_;
                timerType_ = nullptr;
            }
        }

        static UserType* getType(const string& typeStr) {
            if (typeMap_.count(typeStr) == 0) return nullptr;
            return typeMap_.at(typeStr);
        }

        static UserType* getIntType() {
            return intType_;
        }

        static UserType* getBoolType() {
            return boolType_;
        }

        static UserType* getNumberType() {
            return numberType_;
        }

        static UserType* getByteType() {
            return byteType_;
        }

        static UserType* getByteVecType() {
            return byteVecType_;
        }

        static UserType* getTimerType() {
            return timerType_;
        }

        static bool isEqOp(const string& op) {
            return eqOps_.count(op);
        }

        static bool isArOp(const string& op) {
            return arOps_.count(op);
        }

        static unordered_set<string> eqOps_;
        static unordered_set<string> arOps_;
        static UserType* intType_;
        static UserType* boolType_;
        static UserType* numberType_;
        static UserType* byteType_;
        static UserType* byteVecType_;
        static UserType* timerType_;
        static unordered_map<string, UserType*> typeMap_;
    };
}
#endif /* Manage_hpp */
