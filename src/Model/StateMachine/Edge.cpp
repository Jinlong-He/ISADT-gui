#include "Model/StateMachine/Edge.hpp"
namespace isadt {
    Vertex* Edge::getFromVertex() {
        return from_;
    }

    void Edge::SetFromVertex(Vertex* from) {
        from_ = from;
    }

    Vertex* Edge::getToVertex() {
        return to_;
    }
    void Edge::SetToVertex(Vertex* to) {
        to_ = to;
    }

    Guard* Edge::mkGuard(Expression* exp) {
        guard_ = new Guard(exp);
        return guard_;
    }
    
    Guard* Edge::getGuard() {
        return guard_;
    }

    Action* Edge::mkAssignmentAction(Term* lhs, Term* rhs) {
        Action* action = new Action(lhs, rhs);
        actions_.push_back(action);
        return action;
    }

    Action* Edge::mkDeclarationAction(Attribute* attr, const string& value) {
        Action* action = new Action(attr, value);
        actions_.push_back(action);
        return action;
    }

    //MethodAction* Edge::mkMethodAction(MethodTerm* methodTerm) {
    //    MethodAction* action = new MethodAction(methodTerm);
    //    actions_.push_back(action);
    //    return action;
    //}

    AttributeTerm* Edge::mkAttributeTerm(Attribute* attr) {
        AttributeTerm* term = new AttributeTerm(attr);
        terms_.push_back(term);
        return term;
    }

    MethodTerm* Edge::mkMethodTerm(MethodBase* method) {
        MethodTerm* term = new MethodTerm(method);
        terms_.push_back(term);
        return term;
    }

    ConstTerm* Edge::mkConstTerm(UserType* type, const string& value) {
        ConstTerm* term = new ConstTerm(type, value);
        terms_.push_back(term);
        return term;
    }

    ListTerm* Edge::mkListTerm() {
        ListTerm* term = new ListTerm();
        terms_.push_back(term);
        return term;
    }

    Expression* Edge::mkExpression(const string& op, Term* term1, Term* term2) {
        Expression* exp = new Expression(op, term1, term2);
        exps_.push_back(exp);
        return exp;
    }

    const list<Action*>& Edge::getActions() const {
        return actions_;
    }

    void Edge::setActions(const list<Action*>& actions) {
        actions_ = actions;
    }

    string Edge::to_string() const {
        string res = "Guard: ";
        if (guard_) res += guard_ -> getExpression() -> to_string() + "\n";
        res += "Actions: \n";
        for (auto action : actions_) {
            res += action -> to_string() + "\n";
        }
        return res;
    }

    Term* Edge::cpChildren(Term* term, Term* newTerm) {
        for (auto child : term -> getChildren()) {
            newTerm -> addChild(cpTerm(child));
        }
        return newTerm;
    }

    Term* Edge::cpTerm(Term* term) {
        if (term == nullptr) return nullptr;
        auto termType = term -> getTermType();
        switch (termType) {
            case EXP: {
                auto term1 = cpTerm(((Expression*) term) -> getTerm1());
                auto term2 = cpTerm(((Expression*) term) -> getTerm2());
                return cpChildren(term, mkExpression(((Expression*) term) -> getOp(), term1, term2));
            } case AT: {
                return cpChildren(term, mkAttributeTerm(((AttributeTerm*) term) -> getAttribute()));
            } case CT: {
                auto type = ((ConstTerm*) term) -> getType();
                auto value = ((ConstTerm*) term) -> getValueStr();
                return mkConstTerm(type, value);
            } case MT: {
                auto mt = mkMethodTerm(((MethodTerm*) term) -> getMethod());
                for (auto arg : ((MethodTerm*) term) -> getArgs()) {
                    mt -> pushbackArg(cpTerm(arg));
                }
                return cpChildren(term, mt);
            } case LT: {
                auto lt = mkListTerm();
                for (auto arg : ((ListTerm*) term) -> getTermList()) {
                    lt -> pushbackTerm(cpTerm(arg));
                }
                return cpChildren(term, lt);
            } default : {
                return nullptr;
            }
        }
    }

    void Edge::cpActions(Edge* edge) {
        for (auto action : edge -> getActions()) {
            if (action -> isAssignmentAction()) {
                mkAssignmentAction(cpTerm(action -> getLhs()),
                                   cpTerm(action -> getRhs()));
            } else {
                mkDeclarationAction(action -> getAttribute(), action -> getValue());
            }
        }
    }
}
