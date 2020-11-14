#include "Model/StateMachine/Term/MethodTerm.hpp"
namespace isadt {
    void MethodTerm::pushfrontArg(Term* term) {
        args_.push_front(term);
    }

    void MethodTerm::pushbackArg(Term* term) {
        args_.push_back(term);
    }

    MethodBase* MethodTerm::getMethod() {
        return method_;
    }

    const list<Term*>& MethodTerm::getArgs() const {
        return args_;
    }

    string MethodTerm::to_string() const {
        string res = method_ -> getName() + "(";
        for (auto arg : args_) {
            res += arg -> to_string() + ",";
        }
        if (res[res.length() - 1] == '(') {
            res += ")";
        } else {
            res[res.length() - 1] = ')';
        }
        return res + Term::to_string();
    }

    UserType* MethodTerm::getType() const {
        return method_  -> getReturnType();
    }

    bool MethodTerm::isBeagleAvailable() const {
        return false;
    }

    bool MethodTerm::isAtomic() const {
        return false;
    }

    TermType MethodTerm::getTermType() const {
        return MT;
    }
}
