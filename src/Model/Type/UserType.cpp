#include "Model/Type/UserType.hpp"
namespace isadt {
    UserType* UserType::getBase() {
        return base_;
    }

    void UserType::setBase(UserType* base) {
        base_ = base;
    }
}
