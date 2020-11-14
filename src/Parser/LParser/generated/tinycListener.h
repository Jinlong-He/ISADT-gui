
// Generated from tinyc.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "tinycParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by tinycParser.
 */
class  tinycListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterPrimaryExpression(tinycParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(tinycParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterPostfixExpression(tinycParser::PostfixExpressionContext *ctx) = 0;
  virtual void exitPostfixExpression(tinycParser::PostfixExpressionContext *ctx) = 0;

  virtual void enterArgumentExpressionList(tinycParser::ArgumentExpressionListContext *ctx) = 0;
  virtual void exitArgumentExpressionList(tinycParser::ArgumentExpressionListContext *ctx) = 0;

  virtual void enterCastExpression(tinycParser::CastExpressionContext *ctx) = 0;
  virtual void exitCastExpression(tinycParser::CastExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(tinycParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(tinycParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(tinycParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(tinycParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(tinycParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(tinycParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(tinycParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(tinycParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(tinycParser::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(tinycParser::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(tinycParser::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(tinycParser::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(tinycParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(tinycParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterDeclaration(tinycParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(tinycParser::DeclarationContext *ctx) = 0;

  virtual void enterInitDeclaratorList(tinycParser::InitDeclaratorListContext *ctx) = 0;
  virtual void exitInitDeclaratorList(tinycParser::InitDeclaratorListContext *ctx) = 0;

  virtual void enterInitDeclarator(tinycParser::InitDeclaratorContext *ctx) = 0;
  virtual void exitInitDeclarator(tinycParser::InitDeclaratorContext *ctx) = 0;

  virtual void enterDeclarator(tinycParser::DeclaratorContext *ctx) = 0;
  virtual void exitDeclarator(tinycParser::DeclaratorContext *ctx) = 0;

  virtual void enterInitializer(tinycParser::InitializerContext *ctx) = 0;
  virtual void exitInitializer(tinycParser::InitializerContext *ctx) = 0;

  virtual void enterInitializerList(tinycParser::InitializerListContext *ctx) = 0;
  virtual void exitInitializerList(tinycParser::InitializerListContext *ctx) = 0;

  virtual void enterStatement(tinycParser::StatementContext *ctx) = 0;
  virtual void exitStatement(tinycParser::StatementContext *ctx) = 0;


};

