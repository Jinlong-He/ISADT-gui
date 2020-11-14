#include "Model/StateMachine/Term/ListTerm.hpp"
namespace isadt {
    void ListTerm::pushfrontTerm(Term* term) {
        list_.push_front(term);
    }

    void ListTerm::pushbackTerm(Term* term) {
        list_.push_back(term);
    }

    const list<Term*>& ListTerm::getTermList() const {
        return list_;
    }

    string ListTerm::to_string() const {
        string res = "{";
        for (auto term: list_) {
            res += term -> to_string() + ",";
        }
        res[res.length() - 1] = '}';
        return res;
    }

    UserType* ListTerm::getType() const {
        return nullptr;
    }

    bool ListTerm::isBeagleAvailable() const {
        return false;
    }

    bool ListTerm::isAtomic() const {
        return false;
    }

    TermType ListTerm::getTermType() const {
        return LT;
    }
}
