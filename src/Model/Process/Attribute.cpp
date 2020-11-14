#include "Model/Process/Attribute.hpp"
namespace isadt {
    UserType* Attribute::getType() const {
        return type_;
    }

    void Attribute::setType(UserType* type) {
        type_ = type;
    }

    const string& Attribute::getIdentifier() const {
        return identifier_;
    }

    int Attribute::getArray() const {
        return array_;
    }

    void Attribute::setIdentifier(const string& identifier) {
        identifier_ = identifier;
    }
}
