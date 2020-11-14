#include "Model/StateMachine/Expression.hpp"
#include "Manage.hpp"
namespace isadt{
    Term* Expression::getTerm1() {
        return term1_;
    }

    Term* Expression::getTerm2() {
        return term2_;
    }

    string Expression::getOp() {
        return op_;
    }

    bool Expression::isSingledExpression() {
        return isSingle_;
    }

    string Expression::to_string() const {
        if (isSingle_) {
            if (op_ == "!" || op_ == ".")
                return op_ + term1_ -> to_string();
            if (op_ == "()")
                return "(" + term1_ -> to_string() + ")";
            if (op_ == "[]")
                return "[" + term1_ -> to_string() + "]";
        } else {
            return term1_ -> to_string() + op_ + term2_ -> to_string();
        }
        return "";
    }

    UserType* Expression::getType() const {
        if (Manage::isEqOp(op_)) return Manage::getBoolType();
        return term1_ -> getType();
    }

    bool Expression::isBeagleAvailable() const {
        if (isSingle_) return term1_ -> isBeagleAvailable();
        return term1_ -> isBeagleAvailable() && term2_ -> isBeagleAvailable();
    }

    bool Expression::isAtomic() const {
        if (isSingle_) {
            return term1_ -> isAtomic();
        } else {
            if (Manage::isArOp(op_)) return false;
            return term1_ -> isAtomic() && term2_ -> isAtomic();
        }
    }

    TermType Expression::getTermType() const {
        return EXP;
    }
}
