#include "Model/Process/CommMethod.hpp"
namespace isadt {
    bool CommMethod::getInOut() const{
        return inout_;
    }
    void CommMethod::setInOut(bool inout) {
        inout_ = inout;
    }

    const string& CommMethod::getCommId() const {
        return commId_;
    }
    void CommMethod::setCommId(const string& commId) {
        commId_ = commId;
    }
}
