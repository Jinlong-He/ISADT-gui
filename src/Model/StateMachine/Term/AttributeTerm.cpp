#include "Model/StateMachine/Term/AttributeTerm.hpp"
namespace isadt {
    Attribute* AttributeTerm::getAttribute() const {
        return attribute_;
    }
    string AttributeTerm::to_string() const {
        return attribute_ -> getIdentifier() + Term::to_string();
    }

    UserType* AttributeTerm::getType() const {
        return attribute_ -> getType();
    }

    bool AttributeTerm::isBeagleAvailable() const {
        const auto& typeStr = attribute_ -> getType() -> getName();
        if (typeStr == "int" || typeStr == "bool") 
            return Term::isBeagleAvailable();
        return false;
    }

    bool AttributeTerm::isAtomic() const {
        return true;
    }

    TermType AttributeTerm::getTermType() const {
        return AT;
    }
}
