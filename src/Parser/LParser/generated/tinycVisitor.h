
// Generated from tinyc.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "tinycParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by tinycParser.
 */
class  tinycVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by tinycParser.
   */
    virtual antlrcpp::Any visitPrimaryExpression(tinycParser::PrimaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPostfixExpression(tinycParser::PostfixExpressionContext *context) = 0;

    virtual antlrcpp::Any visitArgumentExpressionList(tinycParser::ArgumentExpressionListContext *context) = 0;

    virtual antlrcpp::Any visitCastExpression(tinycParser::CastExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMultiplicativeExpression(tinycParser::MultiplicativeExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAdditiveExpression(tinycParser::AdditiveExpressionContext *context) = 0;

    virtual antlrcpp::Any visitRelationalExpression(tinycParser::RelationalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitEqualityExpression(tinycParser::EqualityExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLogicalAndExpression(tinycParser::LogicalAndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLogicalOrExpression(tinycParser::LogicalOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAssignmentExpression(tinycParser::AssignmentExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration(tinycParser::DeclarationContext *context) = 0;

    virtual antlrcpp::Any visitInitDeclaratorList(tinycParser::InitDeclaratorListContext *context) = 0;

    virtual antlrcpp::Any visitInitDeclarator(tinycParser::InitDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitDeclarator(tinycParser::DeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitInitializer(tinycParser::InitializerContext *context) = 0;

    virtual antlrcpp::Any visitInitializerList(tinycParser::InitializerListContext *context) = 0;

    virtual antlrcpp::Any visitStatement(tinycParser::StatementContext *context) = 0;


};

