
// Generated from tinyc.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "tinycListener.h"


/**
 * This class provides an empty implementation of tinycListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  tinycBaseListener : public tinycListener {
public:

  virtual void enterPrimaryExpression(tinycParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(tinycParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterPostfixExpression(tinycParser::PostfixExpressionContext * /*ctx*/) override { }
  virtual void exitPostfixExpression(tinycParser::PostfixExpressionContext * /*ctx*/) override { }

  virtual void enterArgumentExpressionList(tinycParser::ArgumentExpressionListContext * /*ctx*/) override { }
  virtual void exitArgumentExpressionList(tinycParser::ArgumentExpressionListContext * /*ctx*/) override { }

  virtual void enterCastExpression(tinycParser::CastExpressionContext * /*ctx*/) override { }
  virtual void exitCastExpression(tinycParser::CastExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(tinycParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(tinycParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(tinycParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(tinycParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(tinycParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(tinycParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(tinycParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(tinycParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpression(tinycParser::LogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpression(tinycParser::LogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpression(tinycParser::LogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpression(tinycParser::LogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(tinycParser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(tinycParser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterDeclaration(tinycParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(tinycParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterInitDeclaratorList(tinycParser::InitDeclaratorListContext * /*ctx*/) override { }
  virtual void exitInitDeclaratorList(tinycParser::InitDeclaratorListContext * /*ctx*/) override { }

  virtual void enterInitDeclarator(tinycParser::InitDeclaratorContext * /*ctx*/) override { }
  virtual void exitInitDeclarator(tinycParser::InitDeclaratorContext * /*ctx*/) override { }

  virtual void enterDeclarator(tinycParser::DeclaratorContext * /*ctx*/) override { }
  virtual void exitDeclarator(tinycParser::DeclaratorContext * /*ctx*/) override { }

  virtual void enterInitializer(tinycParser::InitializerContext * /*ctx*/) override { }
  virtual void exitInitializer(tinycParser::InitializerContext * /*ctx*/) override { }

  virtual void enterInitializerList(tinycParser::InitializerListContext * /*ctx*/) override { }
  virtual void exitInitializerList(tinycParser::InitializerListContext * /*ctx*/) override { }

  virtual void enterStatement(tinycParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(tinycParser::StatementContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

