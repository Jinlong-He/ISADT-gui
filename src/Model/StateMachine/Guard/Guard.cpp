#include "Model/StateMachine/Guard/Guard.hpp"

namespace isadt {
    Expression* Guard::getExpression(){
        return expression_;
    }

    void Guard::setExpression(Expression* expression){
        expression_ = expression;
    }

    string Guard::to_string() const{
        return expression_ -> to_string();
    }
}
