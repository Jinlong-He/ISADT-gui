#include <stack>
#include <unordered_set>
#include "Parser/LParser/LParser.hpp"
using namespace std;
namespace isadt {
    class Reader {
    public:
        void init(Model* model, Process* proc, Edge* edge) {
            model_ = model;
            proc_ = proc;
            edge_ = edge;
        }

        Term* readPrimaryExpression(tinycParser::PrimaryExpressionContext* ctx) {
            if (ctx -> Identifier()) {
                string id = ctx -> Identifier() -> getText();
                if (!(proc_ -> hasAttribute(id))) {
                    throw "error: use of undeclared identifier " + id;
                }
                return edge_ -> mkAttributeTerm(proc_ -> getAttributeByName(id));
            }
            if (ctx -> DecimalConstant()) {
                return edge_ -> mkConstTerm(model_ -> getUserTypeByName("int"), ctx -> DecimalConstant() -> getText());
            }
            if (ctx -> assignmentExpression()) {
                return edge_ -> mkExpression("()", readAssignmentExpression(ctx -> assignmentExpression()));
            }
            return nullptr;
        }

        Term* readPostfixExpression(tinycParser::PostfixExpressionContext* ctx) {
            if (ctx -> primaryExpression() && ctx -> primaryExpression() -> Identifier()) {
                string id = ctx -> primaryExpression() -> Identifier() -> getText();
                if (ctx -> getText().find("(") != string::npos) {
                    // method
                    if (!(proc_ -> hasMethod(id)) && !(proc_ -> hasCommMethod(id))) {
                        throw "error: use of undeclared method " + id;
                    }
                    MethodBase* method_ = proc_ -> getMethodByName(id);
                    if (!method_) method_ = proc_ -> getCommMethodByName(id);
                    auto term = edge_ -> mkMethodTerm(method_);
                    auto list = ctx -> argumentExpressionList();
                    while (list) {
                        term -> pushfrontArg(readAssignmentExpression(list -> assignmentExpression()));
                        list = list -> argumentExpressionList();
                    }
                    return term;
                }
                if (!(proc_ -> hasAttribute(id))) {
                    throw "error: use of undeclared identifier " + id;
                }
                return edge_ -> mkAttributeTerm(proc_ -> getAttributeByName(id));
            }
            if (ctx -> primaryExpression()) {
                return readPrimaryExpression(ctx -> primaryExpression());
            }
            if (ctx -> Identifier()) {
                auto term = readPostfixExpression(ctx -> postfixExpression());
                auto type = term -> getRealType();
                auto attrStr = ctx -> Identifier() -> getText();
                if (ctx -> getText().find("(") != string::npos) {
                    if (!(type -> hasMethod(attrStr))) {
                        throw "error: no member method named " + attrStr + " in " + term -> to_string();
                    }
                    MethodBase* method_ = type -> getMethodByName(attrStr);
                    auto child_term = edge_ -> mkMethodTerm(method_);
                    auto child = edge_ -> mkExpression(".", child_term);
                    term -> addChild(child);
                    auto list = ctx -> argumentExpressionList();
                    while (list) {
                        child_term -> pushfrontArg(readAssignmentExpression(list -> assignmentExpression()));
                        list = list -> argumentExpressionList();
                    }
                } else {
                    if (!(type -> hasAttribute(attrStr))) {
                        throw "error: no member named " + attrStr + " in " + term -> to_string();
                    }
                    auto attr = type -> getAttributeByName(attrStr);
                    auto child = edge_ -> mkExpression(".", edge_ -> mkAttributeTerm(attr));
                    term -> addChild(child);
                }
                return term;
            }
            if (ctx -> assignmentExpression()) {
                auto term = readPostfixExpression(ctx -> postfixExpression());
                auto array = edge_ -> mkExpression("[]", readAssignmentExpression(ctx -> assignmentExpression()));
                term -> addChild(array);
                return term;
            }
            return nullptr;
        }

        Term* readCastExpression(tinycParser::CastExpressionContext* ctx) {
            if (ctx -> postfixExpression()) {
                return readPostfixExpression(ctx -> postfixExpression());
            }
            return edge_ -> mkExpression("!", readCastExpression(ctx -> castExpression()));
        }

        Term* readMultiplicativeExpression(tinycParser::MultiplicativeExpressionContext* ctx) {
            auto term = readCastExpression(ctx -> castExpression());
            if (!(ctx -> multiplicativeExpression())) return term;
            if (ctx -> getText().find("*") != string::npos) {
                return edge_ -> mkExpression("*", readMultiplicativeExpression(ctx -> multiplicativeExpression()), term);
            }
            if (ctx -> getText().find("/") != string::npos) {
                return edge_ -> mkExpression("/", readMultiplicativeExpression(ctx -> multiplicativeExpression()), term);
            }
            return nullptr;
        }

        Term* readAdditiveExpression(tinycParser::AdditiveExpressionContext* ctx) {
            auto term = readMultiplicativeExpression(ctx -> multiplicativeExpression());
            if (!(ctx -> additiveExpression())) return term;
            if (ctx -> getText().find("+") != string::npos) {
                return edge_ -> mkExpression("+", readAdditiveExpression(ctx -> additiveExpression()), term);
            }
            if (ctx -> getText().find("-") != string::npos) {
                return edge_ -> mkExpression("-", readAdditiveExpression(ctx -> additiveExpression()), term);
            }
            return nullptr;
        }

        Term* readRelationalExpression(tinycParser::RelationalExpressionContext* ctx) {
            auto term = readAdditiveExpression(ctx -> additiveExpression());
            if (!(ctx -> relationalExpression())) return term;
            if (ctx -> getText().find("<=") != string::npos) {
                return edge_ -> mkExpression("<=", readRelationalExpression(ctx -> relationalExpression()), term);
            }
            if (ctx -> getText().find("<") != string::npos) {
                return edge_ -> mkExpression("<", readRelationalExpression(ctx -> relationalExpression()), term);
            }
            if (ctx -> getText().find(">=") != string::npos) {
                return edge_ -> mkExpression(">=", readRelationalExpression(ctx -> relationalExpression()), term);
            }
            if (ctx -> getText().find(">") != string::npos) {
                return edge_ -> mkExpression(">", readRelationalExpression(ctx -> relationalExpression()), term);
            }
            return nullptr;
        }

        Term* readEqualityExpression(tinycParser::EqualityExpressionContext* ctx) {
            auto term = readRelationalExpression(ctx -> relationalExpression());
            if (!(ctx -> equalityExpression())) return term;
            if (ctx -> getText().find("==") != string::npos) {
                return edge_ -> mkExpression("==", readEqualityExpression(ctx -> equalityExpression()), term);
            }
            if (ctx -> getText().find("!=") != string::npos) {
                return edge_ -> mkExpression("!=", readEqualityExpression(ctx -> equalityExpression()), term);
            }
            return nullptr;
        }

        Term* readLogicalAndExpression(tinycParser::LogicalAndExpressionContext* ctx) {
            auto term = readEqualityExpression(ctx -> equalityExpression());
            if (ctx -> logicalAndExpression()) {
                return edge_ -> mkExpression("&&", readLogicalAndExpression(ctx -> logicalAndExpression()), term);
            } 
            return term;
        }

        Term* readLogicalOrExpression(tinycParser::LogicalOrExpressionContext* ctx) {
            auto term = readLogicalAndExpression(ctx -> logicalAndExpression());
            if (ctx -> logicalOrExpression()) {
                return edge_ -> mkExpression("||", readLogicalOrExpression(ctx -> logicalOrExpression()), term);
            }
            return term;
        }

        Term* readAssignmentExpression(tinycParser::AssignmentExpressionContext* ctx) {
            if (ctx -> castExpression()) {
                return edge_ -> mkExpression("=", readCastExpression(ctx -> castExpression()), 
                                             readAssignmentExpression(ctx -> assignmentExpression()));
            } else if (ctx -> logicalOrExpression()) {
                return readLogicalOrExpression(ctx -> logicalOrExpression());
            }
            return nullptr;
        }

        Term* readInitializer(tinycParser::InitializerContext* ctx) {
            if (ctx -> logicalOrExpression()) {
                return readLogicalOrExpression(ctx -> logicalOrExpression());
            }
            auto term = edge_ -> mkListTerm();
            auto list = ctx -> initializerList();
            while (list) {
                term -> pushfrontTerm(readInitializer(list -> initializer()));
                list = list -> initializerList();
            }
            return term;
        }

        Attribute* readDeclarator(tinycParser::DeclaratorContext* ctx, UserType* type) {
            auto dec = ctx;
            int array = 0;
            while (dec -> declarator()) {
                array++;
                dec = dec -> declarator();
            }
            string id = dec -> Identifier() -> getText();
            if (proc_ -> hasAttribute(id)) {
                throw "error: redefinition of " + id;
            }
            return proc_ -> mkAttribute(type, id, array);
        }

        void readInitDeclarator(tinycParser::InitDeclaratorContext* ctx, UserType* type) {
            auto attr = readDeclarator(ctx -> declarator(), type);
            auto da = edge_ -> mkDeclarationAction(attr);
            auto term = edge_ -> mkAttributeTerm(attr);
            if (ctx -> initializer()) {
                da -> setNext();
                edge_ -> mkAssignmentAction(term, readInitializer(ctx -> initializer()));
            }
        }

        void readDeclaration(tinycParser::DeclarationContext* ctx) {
            auto list = ctx -> initDeclaratorList();
            string typeStr = ctx -> Identifier() -> getText();
            if (!(model_ -> hasUserType(typeStr))) {
                throw "error: use of undeclared type " + typeStr;
            }
            UserType* type = model_ -> getUserTypeByName(typeStr);
            while (list) {
                readInitDeclarator(list -> initDeclarator(), type);
                list = list -> initDeclaratorList();
            }
        }

        private:
        Model* model_;
        Process* proc_;
        Edge* edge_;
    };

    void LParser::parseGuard(const char* text, Model* model, Process* proc, Edge* edge) {
        ANTLRInputStream input(text);
        tinycLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        tinycParser parser(&tokens);
        auto tree = parser.statement();
        Reader reader;
        reader.init(model, proc, edge);
        if (tree -> assignmentExpression()) {
            auto exp = tree -> assignmentExpression();
            if (exp -> castExpression()) {
                throw "error: cannot use '=' in Guard";
            } else {
                edge -> mkGuard((Expression*)reader.readAssignmentExpression(exp));
            }
        } else {
            throw "error: is not a Guard";
        }
    }

    void LParser::parseAction(const char* text, Model* model, Process* proc, Edge* edge) {
        ANTLRInputStream input(text);
        tinycLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        tinycParser parser(&tokens);
        auto tree = parser.statement();
        Reader reader;
        reader.init(model, proc, edge);
        if (tree -> assignmentExpression()) {
            auto exp = tree -> assignmentExpression();
            if (exp -> castExpression()) {
                edge -> mkAssignmentAction(reader.readCastExpression(exp -> castExpression()),
                                           reader.readAssignmentExpression(exp -> assignmentExpression()));
            } else {
                edge -> mkAssignmentAction(reader.readAssignmentExpression(exp));
            }
        } else if (tree -> declaration()) {
            reader.readDeclaration(tree -> declaration());
        }
    }
}
