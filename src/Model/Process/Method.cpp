#include "Model/Process/Method.hpp"
namespace isadt {
    const string& Method::getAlgorithmId() const{
        return algorithmId_;
    }
    void Method::setAlgorithmId(const string& algorithmId){
        algorithmId_ = algorithmId;
    }

    const string& Method::getUserCode() const{
        return userCode_;
    }
    void Method::setUserCode(const string& userCode){
        userCode_ = userCode;
    }
}
