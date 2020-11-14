#include "Model/StateMachine/Action/Action.hpp"

namespace isadt{
    Term* Action::getLhs() const {
        return lhs_;
    }

    Term* Action::getRhs() const {
        return rhs_;
    }

    Attribute* Action::getAttribute() const {
        return attribute_;
    }

    const string& Action::getValue() const {
        return value_;
    }

    bool Action::isAssignmentAction() const {
        return lhs_;
    }

    bool Action::isDeclarationAction() const {
        return attribute_;
    }

    string Action::to_string() const{
        if (lhs_) {
            if (rhs_)
                return lhs_ -> to_string() + " = " + rhs_ -> to_string();
            return lhs_ -> to_string();
        }
        string res = attribute_ -> getType() -> getName() + " " + attribute_ -> getIdentifier();
        for (int i = 0; i < attribute_ -> getArray(); i++) {
            res += "[]";
        }
        return res;
    }
}
