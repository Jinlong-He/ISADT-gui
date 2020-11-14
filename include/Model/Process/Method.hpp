//
//  Method.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Method_hpp
#define Model_Method_hpp 
#include "MethodBase.hpp"
using std::list;

namespace isadt {
    /// \brief the method of process.
    class Method : public MethodBase{
    public:
        Method()
            : MethodBase() {}

        Method(const string& name)
            : MethodBase(name) {}

        Method(const string& name,
               UserType* returnType)
            : MethodBase(name, returnType) {}

        Method(const string& name, 
               UserType* returnType,
               const string& algorithmId,
               const string& userCode = "")
            : MethodBase(name, returnType),
              algorithmId_(algorithmId),
              userCode_(userCode) {}

        bool isCommMethod() const {
            return false;
        }

        ~Method() {}

        const string& getAlgorithmId() const;
        void setAlgorithmId(const string& algorithmId);

        const string& getUserCode() const;
        void setUserCode(const string& userCode);
    private:
        string algorithmId_;             //< the algorithm identifier. encryption and decryption: not null ==> .
        string userCode_;                //< the user insertion code.
    };
}

#endif /* Model_Method_hpp */
