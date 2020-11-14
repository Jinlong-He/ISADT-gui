#include "Model/StateMachine/Term/ConstTerm.hpp"
#include "Manage.hpp"
namespace isadt {

    const string& ConstTerm::getTypeStr() const {
        return typeStr_;
    }

    const string& ConstTerm::getValueStr() const {
        return valueStr_;
    }

    bool ConstTerm::getBoolValue() const {
        if (valueStr_ == "False" || valueStr_ == "0") return 0;
        return 1;
    }

    int ConstTerm::getIntValue() const {
        if (valueStr_ == "False") return 0;
        if (valueStr_ == "True") return 1;
        return stoi(valueStr_);
    }

    string ConstTerm::to_string() const {
        return valueStr_;
    }

    UserType* ConstTerm::getType() const {
        return Manage::getType(typeStr_);
    }

    bool ConstTerm::isBeagleAvailable() const {
        return true;
    }

    bool ConstTerm::isAtomic() const {
        return true;
    }

    TermType ConstTerm::getTermType() const {
        return CT;
    }
}
