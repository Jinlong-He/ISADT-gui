#include "Model/Process/MethodBase.hpp"
namespace isadt {
    UserType* MethodBase::getReturnType() const{
        return returnType_;
    }

    void MethodBase::setReturnType(UserType* returnType){
        returnType_ = returnType;
    }
}
