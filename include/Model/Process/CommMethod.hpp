//
//  CommMethod.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_CommMethod_hpp
#define Model_CommMethod_hpp 
#include "MethodBase.hpp"

namespace isadt {
    /// \brief the signal of process.
    class CommMethod : public MethodBase{
    public:
        CommMethod()
            : MethodBase() {}

        CommMethod(const string& name)
            : MethodBase(name) {}

        CommMethod(const string& name,
                   UserType* returnType)
            : MethodBase(name, returnType) {}

        CommMethod(const string& name, 
                   UserType* returnType,
                   bool inout, 
                   const string& commId = "")
            : MethodBase(name, returnType),
              inout_(inout),
              commId_(commId) {}

        bool isCommMethod() const {
            return true;
        }

        ~CommMethod() {}

        bool getInOut() const ;
        void setInOut(bool inout);

        const string& getCommId() const;
        void setCommId(const string& commId);

    private:
        bool inout_;                 //< the in_out value.
        string commId_;              //< the communication identifier.
    };
}

#endif /* Model_CommMethod_hpp */
