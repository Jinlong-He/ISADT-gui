//
//  Expression.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Expression_hpp
#define Model_Expression_hpp
#include <string>
#include <unordered_set>
#include "Term/Term.hpp"
using std::string;

class Edge;
namespace isadt {
    /// \brief Expression in the Guard condition.
    class Expression : public Term {
    public:
        Expression()
            : term1_(nullptr),
              term2_(nullptr) {}

        Expression(const string& op, Term* term1, Term* term2 = nullptr)
            : op_(op),
              term1_(term1),
              term2_(term2),
              isSingle_(term2 == nullptr) {}

        virtual ~Expression() {}

        Term* getTerm1();
        Term* getTerm2();
        string getOp();
        bool isSingledExpression();
        string to_string() const;
        UserType* getType() const;
        bool isBeagleAvailable() const;
        bool isAtomic() const;
        TermType getTermType() const;
    private:
        string op_;
        Term* term1_;
        Term* term2_;
        bool isSingle_;
        string xml_;
        std::unordered_set<string> eqOps_;
    };
}

#endif /* Model_Expression_hpp */
