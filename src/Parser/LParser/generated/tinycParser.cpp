
// Generated from tinyc.g4 by ANTLR 4.7.1


#include "tinycListener.h"

#include "tinycParser.h"


using namespace antlrcpp;
using namespace antlr4;

tinycParser::tinycParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

tinycParser::~tinycParser() {
  delete _interpreter;
}

std::string tinycParser::getGrammarFileName() const {
  return "tinyc.g4";
}

const std::vector<std::string>& tinycParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& tinycParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- PrimaryExpressionContext ------------------------------------------------------------------

tinycParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* tinycParser::PrimaryExpressionContext::Identifier() {
  return getToken(tinycParser::Identifier, 0);
}

tree::TerminalNode* tinycParser::PrimaryExpressionContext::DecimalConstant() {
  return getToken(tinycParser::DecimalConstant, 0);
}

tinycParser::AssignmentExpressionContext* tinycParser::PrimaryExpressionContext::assignmentExpression() {
  return getRuleContext<tinycParser::AssignmentExpressionContext>(0);
}


size_t tinycParser::PrimaryExpressionContext::getRuleIndex() const {
  return tinycParser::RulePrimaryExpression;
}

void tinycParser::PrimaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpression(this);
}

void tinycParser::PrimaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpression(this);
}

tinycParser::PrimaryExpressionContext* tinycParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 0, tinycParser::RulePrimaryExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(42);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case tinycParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(36);
        match(tinycParser::Identifier);
        break;
      }

      case tinycParser::DecimalConstant: {
        enterOuterAlt(_localctx, 2);
        setState(37);
        match(tinycParser::DecimalConstant);
        break;
      }

      case tinycParser::T__0: {
        enterOuterAlt(_localctx, 3);
        setState(38);
        match(tinycParser::T__0);
        setState(39);
        assignmentExpression();
        setState(40);
        match(tinycParser::T__1);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixExpressionContext ------------------------------------------------------------------

tinycParser::PostfixExpressionContext::PostfixExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::PrimaryExpressionContext* tinycParser::PostfixExpressionContext::primaryExpression() {
  return getRuleContext<tinycParser::PrimaryExpressionContext>(0);
}

tinycParser::ArgumentExpressionListContext* tinycParser::PostfixExpressionContext::argumentExpressionList() {
  return getRuleContext<tinycParser::ArgumentExpressionListContext>(0);
}

tinycParser::PostfixExpressionContext* tinycParser::PostfixExpressionContext::postfixExpression() {
  return getRuleContext<tinycParser::PostfixExpressionContext>(0);
}

tinycParser::AssignmentExpressionContext* tinycParser::PostfixExpressionContext::assignmentExpression() {
  return getRuleContext<tinycParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* tinycParser::PostfixExpressionContext::Identifier() {
  return getToken(tinycParser::Identifier, 0);
}


size_t tinycParser::PostfixExpressionContext::getRuleIndex() const {
  return tinycParser::RulePostfixExpression;
}

void tinycParser::PostfixExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostfixExpression(this);
}

void tinycParser::PostfixExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostfixExpression(this);
}


tinycParser::PostfixExpressionContext* tinycParser::postfixExpression() {
   return postfixExpression(0);
}

tinycParser::PostfixExpressionContext* tinycParser::postfixExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::PostfixExpressionContext *_localctx = _tracker.createInstance<PostfixExpressionContext>(_ctx, parentState);
  tinycParser::PostfixExpressionContext *previousContext = _localctx;
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, tinycParser::RulePostfixExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(53);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(45);
      primaryExpression();
      break;
    }

    case 2: {
      setState(46);
      primaryExpression();
      setState(47);
      match(tinycParser::T__0);
      setState(49);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << tinycParser::T__0)
        | (1ULL << tinycParser::T__6)
        | (1ULL << tinycParser::Identifier)
        | (1ULL << tinycParser::DecimalConstant))) != 0)) {
        setState(48);
        argumentExpressionList(0);
      }
      setState(51);
      match(tinycParser::T__1);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(73);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(71);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<PostfixExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RulePostfixExpression);
          setState(55);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(56);
          match(tinycParser::T__2);
          setState(57);
          assignmentExpression();
          setState(58);
          match(tinycParser::T__3);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<PostfixExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RulePostfixExpression);
          setState(60);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(61);
          match(tinycParser::T__4);
          setState(62);
          match(tinycParser::Identifier);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<PostfixExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RulePostfixExpression);
          setState(63);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(64);
          match(tinycParser::T__4);
          setState(65);
          match(tinycParser::Identifier);
          setState(66);
          match(tinycParser::T__0);
          setState(68);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << tinycParser::T__0)
            | (1ULL << tinycParser::T__6)
            | (1ULL << tinycParser::Identifier)
            | (1ULL << tinycParser::DecimalConstant))) != 0)) {
            setState(67);
            argumentExpressionList(0);
          }
          setState(70);
          match(tinycParser::T__1);
          break;
        }

        } 
      }
      setState(75);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ArgumentExpressionListContext ------------------------------------------------------------------

tinycParser::ArgumentExpressionListContext::ArgumentExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::AssignmentExpressionContext* tinycParser::ArgumentExpressionListContext::assignmentExpression() {
  return getRuleContext<tinycParser::AssignmentExpressionContext>(0);
}

tinycParser::ArgumentExpressionListContext* tinycParser::ArgumentExpressionListContext::argumentExpressionList() {
  return getRuleContext<tinycParser::ArgumentExpressionListContext>(0);
}


size_t tinycParser::ArgumentExpressionListContext::getRuleIndex() const {
  return tinycParser::RuleArgumentExpressionList;
}

void tinycParser::ArgumentExpressionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentExpressionList(this);
}

void tinycParser::ArgumentExpressionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentExpressionList(this);
}


tinycParser::ArgumentExpressionListContext* tinycParser::argumentExpressionList() {
   return argumentExpressionList(0);
}

tinycParser::ArgumentExpressionListContext* tinycParser::argumentExpressionList(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::ArgumentExpressionListContext *_localctx = _tracker.createInstance<ArgumentExpressionListContext>(_ctx, parentState);
  tinycParser::ArgumentExpressionListContext *previousContext = _localctx;
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, tinycParser::RuleArgumentExpressionList, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(77);
    assignmentExpression();
    _ctx->stop = _input->LT(-1);
    setState(84);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ArgumentExpressionListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleArgumentExpressionList);
        setState(79);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(80);
        match(tinycParser::T__5);
        setState(81);
        assignmentExpression(); 
      }
      setState(86);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- CastExpressionContext ------------------------------------------------------------------

tinycParser::CastExpressionContext::CastExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::PostfixExpressionContext* tinycParser::CastExpressionContext::postfixExpression() {
  return getRuleContext<tinycParser::PostfixExpressionContext>(0);
}

tinycParser::CastExpressionContext* tinycParser::CastExpressionContext::castExpression() {
  return getRuleContext<tinycParser::CastExpressionContext>(0);
}


size_t tinycParser::CastExpressionContext::getRuleIndex() const {
  return tinycParser::RuleCastExpression;
}

void tinycParser::CastExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCastExpression(this);
}

void tinycParser::CastExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCastExpression(this);
}

tinycParser::CastExpressionContext* tinycParser::castExpression() {
  CastExpressionContext *_localctx = _tracker.createInstance<CastExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, tinycParser::RuleCastExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(90);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case tinycParser::T__0:
      case tinycParser::Identifier:
      case tinycParser::DecimalConstant: {
        enterOuterAlt(_localctx, 1);
        setState(87);
        postfixExpression(0);
        break;
      }

      case tinycParser::T__6: {
        enterOuterAlt(_localctx, 2);
        setState(88);
        match(tinycParser::T__6);
        setState(89);
        castExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

tinycParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::CastExpressionContext* tinycParser::MultiplicativeExpressionContext::castExpression() {
  return getRuleContext<tinycParser::CastExpressionContext>(0);
}

tinycParser::MultiplicativeExpressionContext* tinycParser::MultiplicativeExpressionContext::multiplicativeExpression() {
  return getRuleContext<tinycParser::MultiplicativeExpressionContext>(0);
}


size_t tinycParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return tinycParser::RuleMultiplicativeExpression;
}

void tinycParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void tinycParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}


tinycParser::MultiplicativeExpressionContext* tinycParser::multiplicativeExpression() {
   return multiplicativeExpression(0);
}

tinycParser::MultiplicativeExpressionContext* tinycParser::multiplicativeExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, parentState);
  tinycParser::MultiplicativeExpressionContext *previousContext = _localctx;
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, tinycParser::RuleMultiplicativeExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(93);
    castExpression();
    _ctx->stop = _input->LT(-1);
    setState(103);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(101);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<MultiplicativeExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMultiplicativeExpression);
          setState(95);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(96);
          match(tinycParser::T__7);
          setState(97);
          castExpression();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<MultiplicativeExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMultiplicativeExpression);
          setState(98);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(99);
          match(tinycParser::T__8);
          setState(100);
          castExpression();
          break;
        }

        } 
      }
      setState(105);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

tinycParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::MultiplicativeExpressionContext* tinycParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContext<tinycParser::MultiplicativeExpressionContext>(0);
}

tinycParser::AdditiveExpressionContext* tinycParser::AdditiveExpressionContext::additiveExpression() {
  return getRuleContext<tinycParser::AdditiveExpressionContext>(0);
}


size_t tinycParser::AdditiveExpressionContext::getRuleIndex() const {
  return tinycParser::RuleAdditiveExpression;
}

void tinycParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void tinycParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}


tinycParser::AdditiveExpressionContext* tinycParser::additiveExpression() {
   return additiveExpression(0);
}

tinycParser::AdditiveExpressionContext* tinycParser::additiveExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, parentState);
  tinycParser::AdditiveExpressionContext *previousContext = _localctx;
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, tinycParser::RuleAdditiveExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(107);
    multiplicativeExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(117);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(115);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<AdditiveExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdditiveExpression);
          setState(109);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(110);
          match(tinycParser::T__9);
          setState(111);
          multiplicativeExpression(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<AdditiveExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdditiveExpression);
          setState(112);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(113);
          match(tinycParser::T__10);
          setState(114);
          multiplicativeExpression(0);
          break;
        }

        } 
      }
      setState(119);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

tinycParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::AdditiveExpressionContext* tinycParser::RelationalExpressionContext::additiveExpression() {
  return getRuleContext<tinycParser::AdditiveExpressionContext>(0);
}

tinycParser::RelationalExpressionContext* tinycParser::RelationalExpressionContext::relationalExpression() {
  return getRuleContext<tinycParser::RelationalExpressionContext>(0);
}


size_t tinycParser::RelationalExpressionContext::getRuleIndex() const {
  return tinycParser::RuleRelationalExpression;
}

void tinycParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void tinycParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}


tinycParser::RelationalExpressionContext* tinycParser::relationalExpression() {
   return relationalExpression(0);
}

tinycParser::RelationalExpressionContext* tinycParser::relationalExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, parentState);
  tinycParser::RelationalExpressionContext *previousContext = _localctx;
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, tinycParser::RuleRelationalExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(121);
    additiveExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(137);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(135);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<RelationalExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRelationalExpression);
          setState(123);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(124);
          match(tinycParser::T__11);
          setState(125);
          additiveExpression(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<RelationalExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRelationalExpression);
          setState(126);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(127);
          match(tinycParser::T__12);
          setState(128);
          additiveExpression(0);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<RelationalExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRelationalExpression);
          setState(129);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(130);
          match(tinycParser::T__13);
          setState(131);
          additiveExpression(0);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<RelationalExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRelationalExpression);
          setState(132);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(133);
          match(tinycParser::T__14);
          setState(134);
          additiveExpression(0);
          break;
        }

        } 
      }
      setState(139);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

tinycParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::RelationalExpressionContext* tinycParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContext<tinycParser::RelationalExpressionContext>(0);
}

tinycParser::EqualityExpressionContext* tinycParser::EqualityExpressionContext::equalityExpression() {
  return getRuleContext<tinycParser::EqualityExpressionContext>(0);
}


size_t tinycParser::EqualityExpressionContext::getRuleIndex() const {
  return tinycParser::RuleEqualityExpression;
}

void tinycParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}

void tinycParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}


tinycParser::EqualityExpressionContext* tinycParser::equalityExpression() {
   return equalityExpression(0);
}

tinycParser::EqualityExpressionContext* tinycParser::equalityExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, parentState);
  tinycParser::EqualityExpressionContext *previousContext = _localctx;
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, tinycParser::RuleEqualityExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(141);
    relationalExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(151);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(149);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<EqualityExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEqualityExpression);
          setState(143);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(144);
          match(tinycParser::T__15);
          setState(145);
          relationalExpression(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<EqualityExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEqualityExpression);
          setState(146);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(147);
          match(tinycParser::T__16);
          setState(148);
          relationalExpression(0);
          break;
        }

        } 
      }
      setState(153);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

tinycParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::EqualityExpressionContext* tinycParser::LogicalAndExpressionContext::equalityExpression() {
  return getRuleContext<tinycParser::EqualityExpressionContext>(0);
}

tinycParser::LogicalAndExpressionContext* tinycParser::LogicalAndExpressionContext::logicalAndExpression() {
  return getRuleContext<tinycParser::LogicalAndExpressionContext>(0);
}


size_t tinycParser::LogicalAndExpressionContext::getRuleIndex() const {
  return tinycParser::RuleLogicalAndExpression;
}

void tinycParser::LogicalAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAndExpression(this);
}

void tinycParser::LogicalAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAndExpression(this);
}


tinycParser::LogicalAndExpressionContext* tinycParser::logicalAndExpression() {
   return logicalAndExpression(0);
}

tinycParser::LogicalAndExpressionContext* tinycParser::logicalAndExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, parentState);
  tinycParser::LogicalAndExpressionContext *previousContext = _localctx;
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, tinycParser::RuleLogicalAndExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(155);
    equalityExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(162);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalAndExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalAndExpression);
        setState(157);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(158);
        match(tinycParser::T__17);
        setState(159);
        equalityExpression(0); 
      }
      setState(164);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

tinycParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::LogicalAndExpressionContext* tinycParser::LogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContext<tinycParser::LogicalAndExpressionContext>(0);
}

tinycParser::LogicalOrExpressionContext* tinycParser::LogicalOrExpressionContext::logicalOrExpression() {
  return getRuleContext<tinycParser::LogicalOrExpressionContext>(0);
}


size_t tinycParser::LogicalOrExpressionContext::getRuleIndex() const {
  return tinycParser::RuleLogicalOrExpression;
}

void tinycParser::LogicalOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOrExpression(this);
}

void tinycParser::LogicalOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOrExpression(this);
}


tinycParser::LogicalOrExpressionContext* tinycParser::logicalOrExpression() {
   return logicalOrExpression(0);
}

tinycParser::LogicalOrExpressionContext* tinycParser::logicalOrExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, parentState);
  tinycParser::LogicalOrExpressionContext *previousContext = _localctx;
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, tinycParser::RuleLogicalOrExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(166);
    logicalAndExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(173);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalOrExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalOrExpression);
        setState(168);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(169);
        match(tinycParser::T__18);
        setState(170);
        logicalAndExpression(0); 
      }
      setState(175);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AssignmentExpressionContext ------------------------------------------------------------------

tinycParser::AssignmentExpressionContext::AssignmentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::CastExpressionContext* tinycParser::AssignmentExpressionContext::castExpression() {
  return getRuleContext<tinycParser::CastExpressionContext>(0);
}

tinycParser::AssignmentExpressionContext* tinycParser::AssignmentExpressionContext::assignmentExpression() {
  return getRuleContext<tinycParser::AssignmentExpressionContext>(0);
}

tinycParser::LogicalOrExpressionContext* tinycParser::AssignmentExpressionContext::logicalOrExpression() {
  return getRuleContext<tinycParser::LogicalOrExpressionContext>(0);
}


size_t tinycParser::AssignmentExpressionContext::getRuleIndex() const {
  return tinycParser::RuleAssignmentExpression;
}

void tinycParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}

void tinycParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}

tinycParser::AssignmentExpressionContext* tinycParser::assignmentExpression() {
  AssignmentExpressionContext *_localctx = _tracker.createInstance<AssignmentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 20, tinycParser::RuleAssignmentExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(181);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(176);
      castExpression();
      setState(177);
      match(tinycParser::T__19);
      setState(178);
      assignmentExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(180);
      logicalOrExpression(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

tinycParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* tinycParser::DeclarationContext::Identifier() {
  return getToken(tinycParser::Identifier, 0);
}

tinycParser::InitDeclaratorListContext* tinycParser::DeclarationContext::initDeclaratorList() {
  return getRuleContext<tinycParser::InitDeclaratorListContext>(0);
}


size_t tinycParser::DeclarationContext::getRuleIndex() const {
  return tinycParser::RuleDeclaration;
}

void tinycParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void tinycParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}

tinycParser::DeclarationContext* tinycParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 22, tinycParser::RuleDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    match(tinycParser::Identifier);
    setState(184);
    initDeclaratorList(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitDeclaratorListContext ------------------------------------------------------------------

tinycParser::InitDeclaratorListContext::InitDeclaratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::InitDeclaratorContext* tinycParser::InitDeclaratorListContext::initDeclarator() {
  return getRuleContext<tinycParser::InitDeclaratorContext>(0);
}

tinycParser::InitDeclaratorListContext* tinycParser::InitDeclaratorListContext::initDeclaratorList() {
  return getRuleContext<tinycParser::InitDeclaratorListContext>(0);
}


size_t tinycParser::InitDeclaratorListContext::getRuleIndex() const {
  return tinycParser::RuleInitDeclaratorList;
}

void tinycParser::InitDeclaratorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitDeclaratorList(this);
}

void tinycParser::InitDeclaratorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitDeclaratorList(this);
}


tinycParser::InitDeclaratorListContext* tinycParser::initDeclaratorList() {
   return initDeclaratorList(0);
}

tinycParser::InitDeclaratorListContext* tinycParser::initDeclaratorList(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::InitDeclaratorListContext *_localctx = _tracker.createInstance<InitDeclaratorListContext>(_ctx, parentState);
  tinycParser::InitDeclaratorListContext *previousContext = _localctx;
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, tinycParser::RuleInitDeclaratorList, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(187);
    initDeclarator();
    _ctx->stop = _input->LT(-1);
    setState(194);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<InitDeclaratorListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleInitDeclaratorList);
        setState(189);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(190);
        match(tinycParser::T__5);
        setState(191);
        initDeclarator(); 
      }
      setState(196);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- InitDeclaratorContext ------------------------------------------------------------------

tinycParser::InitDeclaratorContext::InitDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::DeclaratorContext* tinycParser::InitDeclaratorContext::declarator() {
  return getRuleContext<tinycParser::DeclaratorContext>(0);
}

tinycParser::InitializerContext* tinycParser::InitDeclaratorContext::initializer() {
  return getRuleContext<tinycParser::InitializerContext>(0);
}


size_t tinycParser::InitDeclaratorContext::getRuleIndex() const {
  return tinycParser::RuleInitDeclarator;
}

void tinycParser::InitDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitDeclarator(this);
}

void tinycParser::InitDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitDeclarator(this);
}

tinycParser::InitDeclaratorContext* tinycParser::initDeclarator() {
  InitDeclaratorContext *_localctx = _tracker.createInstance<InitDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 26, tinycParser::RuleInitDeclarator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(202);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(197);
      declarator(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(198);
      declarator(0);
      setState(199);
      match(tinycParser::T__19);
      setState(200);
      initializer();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclaratorContext ------------------------------------------------------------------

tinycParser::DeclaratorContext::DeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* tinycParser::DeclaratorContext::Identifier() {
  return getToken(tinycParser::Identifier, 0);
}

tinycParser::DeclaratorContext* tinycParser::DeclaratorContext::declarator() {
  return getRuleContext<tinycParser::DeclaratorContext>(0);
}


size_t tinycParser::DeclaratorContext::getRuleIndex() const {
  return tinycParser::RuleDeclarator;
}

void tinycParser::DeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarator(this);
}

void tinycParser::DeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarator(this);
}


tinycParser::DeclaratorContext* tinycParser::declarator() {
   return declarator(0);
}

tinycParser::DeclaratorContext* tinycParser::declarator(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::DeclaratorContext *_localctx = _tracker.createInstance<DeclaratorContext>(_ctx, parentState);
  tinycParser::DeclaratorContext *previousContext = _localctx;
  size_t startState = 28;
  enterRecursionRule(_localctx, 28, tinycParser::RuleDeclarator, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(205);
    match(tinycParser::Identifier);
    _ctx->stop = _input->LT(-1);
    setState(212);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<DeclaratorContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleDeclarator);
        setState(207);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(208);
        match(tinycParser::T__2);
        setState(209);
        match(tinycParser::T__3); 
      }
      setState(214);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- InitializerContext ------------------------------------------------------------------

tinycParser::InitializerContext::InitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::LogicalOrExpressionContext* tinycParser::InitializerContext::logicalOrExpression() {
  return getRuleContext<tinycParser::LogicalOrExpressionContext>(0);
}

tinycParser::InitializerListContext* tinycParser::InitializerContext::initializerList() {
  return getRuleContext<tinycParser::InitializerListContext>(0);
}


size_t tinycParser::InitializerContext::getRuleIndex() const {
  return tinycParser::RuleInitializer;
}

void tinycParser::InitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializer(this);
}

void tinycParser::InitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializer(this);
}

tinycParser::InitializerContext* tinycParser::initializer() {
  InitializerContext *_localctx = _tracker.createInstance<InitializerContext>(_ctx, getState());
  enterRule(_localctx, 30, tinycParser::RuleInitializer);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(220);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case tinycParser::T__0:
      case tinycParser::T__6:
      case tinycParser::Identifier:
      case tinycParser::DecimalConstant: {
        enterOuterAlt(_localctx, 1);
        setState(215);
        logicalOrExpression(0);
        break;
      }

      case tinycParser::T__20: {
        enterOuterAlt(_localctx, 2);
        setState(216);
        match(tinycParser::T__20);
        setState(217);
        initializerList(0);
        setState(218);
        match(tinycParser::T__21);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerListContext ------------------------------------------------------------------

tinycParser::InitializerListContext::InitializerListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::InitializerContext* tinycParser::InitializerListContext::initializer() {
  return getRuleContext<tinycParser::InitializerContext>(0);
}

tinycParser::InitializerListContext* tinycParser::InitializerListContext::initializerList() {
  return getRuleContext<tinycParser::InitializerListContext>(0);
}


size_t tinycParser::InitializerListContext::getRuleIndex() const {
  return tinycParser::RuleInitializerList;
}

void tinycParser::InitializerListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializerList(this);
}

void tinycParser::InitializerListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializerList(this);
}


tinycParser::InitializerListContext* tinycParser::initializerList() {
   return initializerList(0);
}

tinycParser::InitializerListContext* tinycParser::initializerList(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tinycParser::InitializerListContext *_localctx = _tracker.createInstance<InitializerListContext>(_ctx, parentState);
  tinycParser::InitializerListContext *previousContext = _localctx;
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, tinycParser::RuleInitializerList, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(223);
    initializer();
    _ctx->stop = _input->LT(-1);
    setState(230);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<InitializerListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleInitializerList);
        setState(225);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(226);
        match(tinycParser::T__5);
        setState(227);
        initializer(); 
      }
      setState(232);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

tinycParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tinycParser::AssignmentExpressionContext* tinycParser::StatementContext::assignmentExpression() {
  return getRuleContext<tinycParser::AssignmentExpressionContext>(0);
}

tinycParser::DeclarationContext* tinycParser::StatementContext::declaration() {
  return getRuleContext<tinycParser::DeclarationContext>(0);
}


size_t tinycParser::StatementContext::getRuleIndex() const {
  return tinycParser::RuleStatement;
}

void tinycParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void tinycParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<tinycListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

tinycParser::StatementContext* tinycParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 34, tinycParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(235);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(233);
      assignmentExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(234);
      declaration();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool tinycParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return postfixExpressionSempred(dynamic_cast<PostfixExpressionContext *>(context), predicateIndex);
    case 2: return argumentExpressionListSempred(dynamic_cast<ArgumentExpressionListContext *>(context), predicateIndex);
    case 4: return multiplicativeExpressionSempred(dynamic_cast<MultiplicativeExpressionContext *>(context), predicateIndex);
    case 5: return additiveExpressionSempred(dynamic_cast<AdditiveExpressionContext *>(context), predicateIndex);
    case 6: return relationalExpressionSempred(dynamic_cast<RelationalExpressionContext *>(context), predicateIndex);
    case 7: return equalityExpressionSempred(dynamic_cast<EqualityExpressionContext *>(context), predicateIndex);
    case 8: return logicalAndExpressionSempred(dynamic_cast<LogicalAndExpressionContext *>(context), predicateIndex);
    case 9: return logicalOrExpressionSempred(dynamic_cast<LogicalOrExpressionContext *>(context), predicateIndex);
    case 12: return initDeclaratorListSempred(dynamic_cast<InitDeclaratorListContext *>(context), predicateIndex);
    case 14: return declaratorSempred(dynamic_cast<DeclaratorContext *>(context), predicateIndex);
    case 16: return initializerListSempred(dynamic_cast<InitializerListContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool tinycParser::postfixExpressionSempred(PostfixExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::argumentExpressionListSempred(ArgumentExpressionListContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::multiplicativeExpressionSempred(MultiplicativeExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::additiveExpressionSempred(AdditiveExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 6: return precpred(_ctx, 2);
    case 7: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::relationalExpressionSempred(RelationalExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 8: return precpred(_ctx, 4);
    case 9: return precpred(_ctx, 3);
    case 10: return precpred(_ctx, 2);
    case 11: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::equalityExpressionSempred(EqualityExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 12: return precpred(_ctx, 2);
    case 13: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::logicalAndExpressionSempred(LogicalAndExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 14: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::logicalOrExpressionSempred(LogicalOrExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 15: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::initDeclaratorListSempred(InitDeclaratorListContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 16: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::declaratorSempred(DeclaratorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 17: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool tinycParser::initializerListSempred(InitializerListContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 18: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> tinycParser::_decisionToDFA;
atn::PredictionContextCache tinycParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN tinycParser::_atn;
std::vector<uint16_t> tinycParser::_serializedATN;

std::vector<std::string> tinycParser::_ruleNames = {
  "primaryExpression", "postfixExpression", "argumentExpressionList", "castExpression", 
  "multiplicativeExpression", "additiveExpression", "relationalExpression", 
  "equalityExpression", "logicalAndExpression", "logicalOrExpression", "assignmentExpression", 
  "declaration", "initDeclaratorList", "initDeclarator", "declarator", "initializer", 
  "initializerList", "statement"
};

std::vector<std::string> tinycParser::_literalNames = {
  "", "'('", "')'", "'['", "']'", "'.'", "','", "'!'", "'*'", "'/'", "'+'", 
  "'-'", "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", "'&&'", "'||'", "'='", 
  "'{'", "'}'"
};

std::vector<std::string> tinycParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "Identifier", "DecimalConstant", "Whitespace"
};

dfa::Vocabulary tinycParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> tinycParser::_tokenNames;

tinycParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x1b, 0xf0, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x2d, 0xa, 0x2, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x34, 0xa, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x5, 0x3, 0x38, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x47, 0xa, 0x3, 0x3, 0x3, 0x7, 0x3, 0x4a, 
    0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x4d, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x55, 0xa, 0x4, 0xc, 0x4, 
    0xe, 0x4, 0x58, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x5d, 
    0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x68, 0xa, 0x6, 0xc, 0x6, 0xe, 
    0x6, 0x6b, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x76, 0xa, 0x7, 0xc, 
    0x7, 0xe, 0x7, 0x79, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x8a, 0xa, 0x8, 0xc, 
    0x8, 0xe, 0x8, 0x8d, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x98, 0xa, 
    0x9, 0xc, 0x9, 0xe, 0x9, 0x9b, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0xa3, 0xa, 0xa, 0xc, 0xa, 0xe, 
    0xa, 0xa6, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x7, 0xb, 0xae, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0xb1, 0xb, 0xb, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0xb8, 0xa, 
    0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0xc3, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 
    0xc6, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 
    0xf, 0xcd, 0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x7, 0x10, 0xd5, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0xd8, 
    0xb, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 
    0x11, 0xdf, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x7, 0x12, 0xe7, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0xea, 
    0xb, 0x12, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xee, 0xa, 0x13, 0x3, 0x13, 
    0x2, 0xd, 0x4, 0x6, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x1a, 0x1e, 0x22, 
    0x14, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
    0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x2, 0x2, 0x2, 0xfa, 0x2, 0x2c, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x37, 0x3, 0x2, 0x2, 0x2, 0x6, 0x4e, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x5c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x5e, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x6c, 0x3, 0x2, 0x2, 0x2, 0xe, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x8e, 0x3, 0x2, 0x2, 0x2, 0x12, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x14, 0xa7, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0xb7, 0x3, 0x2, 0x2, 0x2, 0x18, 0xb9, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0xbc, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xcc, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0xce, 0x3, 0x2, 0x2, 0x2, 0x20, 0xde, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0xe0, 0x3, 0x2, 0x2, 0x2, 0x24, 0xed, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0x2d, 0x7, 0x19, 0x2, 0x2, 0x27, 0x2d, 0x7, 0x1a, 0x2, 0x2, 0x28, 
    0x29, 0x7, 0x3, 0x2, 0x2, 0x29, 0x2a, 0x5, 0x16, 0xc, 0x2, 0x2a, 0x2b, 
    0x7, 0x4, 0x2, 0x2, 0x2b, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x26, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x28, 0x3, 0x2, 
    0x2, 0x2, 0x2d, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x8, 0x3, 0x1, 
    0x2, 0x2f, 0x38, 0x5, 0x2, 0x2, 0x2, 0x30, 0x31, 0x5, 0x2, 0x2, 0x2, 
    0x31, 0x33, 0x7, 0x3, 0x2, 0x2, 0x32, 0x34, 0x5, 0x6, 0x4, 0x2, 0x33, 
    0x32, 0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 
    0x3, 0x2, 0x2, 0x2, 0x35, 0x36, 0x7, 0x4, 0x2, 0x2, 0x36, 0x38, 0x3, 
    0x2, 0x2, 0x2, 0x37, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x37, 0x30, 0x3, 0x2, 
    0x2, 0x2, 0x38, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0xc, 0x5, 0x2, 
    0x2, 0x3a, 0x3b, 0x7, 0x5, 0x2, 0x2, 0x3b, 0x3c, 0x5, 0x16, 0xc, 0x2, 
    0x3c, 0x3d, 0x7, 0x6, 0x2, 0x2, 0x3d, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0x3f, 0xc, 0x4, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x7, 0x2, 0x2, 0x40, 0x4a, 
    0x7, 0x19, 0x2, 0x2, 0x41, 0x42, 0xc, 0x3, 0x2, 0x2, 0x42, 0x43, 0x7, 
    0x7, 0x2, 0x2, 0x43, 0x44, 0x7, 0x19, 0x2, 0x2, 0x44, 0x46, 0x7, 0x3, 
    0x2, 0x2, 0x45, 0x47, 0x5, 0x6, 0x4, 0x2, 0x46, 0x45, 0x3, 0x2, 0x2, 
    0x2, 0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 0x2, 
    0x48, 0x4a, 0x7, 0x4, 0x2, 0x2, 0x49, 0x39, 0x3, 0x2, 0x2, 0x2, 0x49, 
    0x3e, 0x3, 0x2, 0x2, 0x2, 0x49, 0x41, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4d, 
    0x3, 0x2, 0x2, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x3, 
    0x2, 0x2, 0x2, 0x4c, 0x5, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4b, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x4f, 0x8, 0x4, 0x1, 0x2, 0x4f, 0x50, 0x5, 0x16, 0xc, 
    0x2, 0x50, 0x56, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0xc, 0x3, 0x2, 0x2, 
    0x52, 0x53, 0x7, 0x8, 0x2, 0x2, 0x53, 0x55, 0x5, 0x16, 0xc, 0x2, 0x54, 
    0x51, 0x3, 0x2, 0x2, 0x2, 0x55, 0x58, 0x3, 0x2, 0x2, 0x2, 0x56, 0x54, 
    0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x3, 0x2, 0x2, 0x2, 0x57, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x58, 0x56, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5d, 0x5, 0x4, 
    0x3, 0x2, 0x5a, 0x5b, 0x7, 0x9, 0x2, 0x2, 0x5b, 0x5d, 0x5, 0x8, 0x5, 
    0x2, 0x5c, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5a, 0x3, 0x2, 0x2, 0x2, 
    0x5d, 0x9, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x8, 0x6, 0x1, 0x2, 0x5f, 
    0x60, 0x5, 0x8, 0x5, 0x2, 0x60, 0x69, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 
    0xc, 0x4, 0x2, 0x2, 0x62, 0x63, 0x7, 0xa, 0x2, 0x2, 0x63, 0x68, 0x5, 
    0x8, 0x5, 0x2, 0x64, 0x65, 0xc, 0x3, 0x2, 0x2, 0x65, 0x66, 0x7, 0xb, 
    0x2, 0x2, 0x66, 0x68, 0x5, 0x8, 0x5, 0x2, 0x67, 0x61, 0x3, 0x2, 0x2, 
    0x2, 0x67, 0x64, 0x3, 0x2, 0x2, 0x2, 0x68, 0x6b, 0x3, 0x2, 0x2, 0x2, 
    0x69, 0x67, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 
    0xb, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 
    0x8, 0x7, 0x1, 0x2, 0x6d, 0x6e, 0x5, 0xa, 0x6, 0x2, 0x6e, 0x77, 0x3, 
    0x2, 0x2, 0x2, 0x6f, 0x70, 0xc, 0x4, 0x2, 0x2, 0x70, 0x71, 0x7, 0xc, 
    0x2, 0x2, 0x71, 0x76, 0x5, 0xa, 0x6, 0x2, 0x72, 0x73, 0xc, 0x3, 0x2, 
    0x2, 0x73, 0x74, 0x7, 0xd, 0x2, 0x2, 0x74, 0x76, 0x5, 0xa, 0x6, 0x2, 
    0x75, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x75, 0x72, 0x3, 0x2, 0x2, 0x2, 0x76, 
    0x79, 0x3, 0x2, 0x2, 0x2, 0x77, 0x75, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 
    0x3, 0x2, 0x2, 0x2, 0x78, 0xd, 0x3, 0x2, 0x2, 0x2, 0x79, 0x77, 0x3, 
    0x2, 0x2, 0x2, 0x7a, 0x7b, 0x8, 0x8, 0x1, 0x2, 0x7b, 0x7c, 0x5, 0xc, 
    0x7, 0x2, 0x7c, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0xc, 0x6, 0x2, 
    0x2, 0x7e, 0x7f, 0x7, 0xe, 0x2, 0x2, 0x7f, 0x8a, 0x5, 0xc, 0x7, 0x2, 
    0x80, 0x81, 0xc, 0x5, 0x2, 0x2, 0x81, 0x82, 0x7, 0xf, 0x2, 0x2, 0x82, 
    0x8a, 0x5, 0xc, 0x7, 0x2, 0x83, 0x84, 0xc, 0x4, 0x2, 0x2, 0x84, 0x85, 
    0x7, 0x10, 0x2, 0x2, 0x85, 0x8a, 0x5, 0xc, 0x7, 0x2, 0x86, 0x87, 0xc, 
    0x3, 0x2, 0x2, 0x87, 0x88, 0x7, 0x11, 0x2, 0x2, 0x88, 0x8a, 0x5, 0xc, 
    0x7, 0x2, 0x89, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x89, 0x80, 0x3, 0x2, 0x2, 
    0x2, 0x89, 0x83, 0x3, 0x2, 0x2, 0x2, 0x89, 0x86, 0x3, 0x2, 0x2, 0x2, 
    0x8a, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x89, 0x3, 0x2, 0x2, 0x2, 0x8b, 
    0x8c, 0x3, 0x2, 0x2, 0x2, 0x8c, 0xf, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8b, 
    0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x8, 0x9, 0x1, 0x2, 0x8f, 0x90, 0x5, 
    0xe, 0x8, 0x2, 0x90, 0x99, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0xc, 0x4, 
    0x2, 0x2, 0x92, 0x93, 0x7, 0x12, 0x2, 0x2, 0x93, 0x98, 0x5, 0xe, 0x8, 
    0x2, 0x94, 0x95, 0xc, 0x3, 0x2, 0x2, 0x95, 0x96, 0x7, 0x13, 0x2, 0x2, 
    0x96, 0x98, 0x5, 0xe, 0x8, 0x2, 0x97, 0x91, 0x3, 0x2, 0x2, 0x2, 0x97, 
    0x94, 0x3, 0x2, 0x2, 0x2, 0x98, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x99, 0x97, 
    0x3, 0x2, 0x2, 0x2, 0x99, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x11, 0x3, 
    0x2, 0x2, 0x2, 0x9b, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x8, 0xa, 
    0x1, 0x2, 0x9d, 0x9e, 0x5, 0x10, 0x9, 0x2, 0x9e, 0xa4, 0x3, 0x2, 0x2, 
    0x2, 0x9f, 0xa0, 0xc, 0x3, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0x14, 0x2, 0x2, 
    0xa1, 0xa3, 0x5, 0x10, 0x9, 0x2, 0xa2, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xa3, 
    0xa6, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa5, 
    0x3, 0x2, 0x2, 0x2, 0xa5, 0x13, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa4, 0x3, 
    0x2, 0x2, 0x2, 0xa7, 0xa8, 0x8, 0xb, 0x1, 0x2, 0xa8, 0xa9, 0x5, 0x12, 
    0xa, 0x2, 0xa9, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0xc, 0x3, 0x2, 
    0x2, 0xab, 0xac, 0x7, 0x15, 0x2, 0x2, 0xac, 0xae, 0x5, 0x12, 0xa, 0x2, 
    0xad, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xae, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xaf, 
    0xad, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x15, 
    0x3, 0x2, 0x2, 0x2, 0xb1, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb3, 0x5, 
    0x8, 0x5, 0x2, 0xb3, 0xb4, 0x7, 0x16, 0x2, 0x2, 0xb4, 0xb5, 0x5, 0x16, 
    0xc, 0x2, 0xb5, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb8, 0x5, 0x14, 0xb, 
    0x2, 0xb7, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb6, 0x3, 0x2, 0x2, 0x2, 
    0xb8, 0x17, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xba, 0x7, 0x19, 0x2, 0x2, 0xba, 
    0xbb, 0x5, 0x1a, 0xe, 0x2, 0xbb, 0x19, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 
    0x8, 0xe, 0x1, 0x2, 0xbd, 0xbe, 0x5, 0x1c, 0xf, 0x2, 0xbe, 0xc4, 0x3, 
    0x2, 0x2, 0x2, 0xbf, 0xc0, 0xc, 0x3, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0x8, 
    0x2, 0x2, 0xc1, 0xc3, 0x5, 0x1c, 0xf, 0x2, 0xc2, 0xbf, 0x3, 0x2, 0x2, 
    0x2, 0xc3, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc2, 0x3, 0x2, 0x2, 0x2, 
    0xc4, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc5, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xc6, 
    0xc4, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xcd, 0x5, 0x1e, 0x10, 0x2, 0xc8, 0xc9, 
    0x5, 0x1e, 0x10, 0x2, 0xc9, 0xca, 0x7, 0x16, 0x2, 0x2, 0xca, 0xcb, 0x5, 
    0x20, 0x11, 0x2, 0xcb, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xc7, 0x3, 0x2, 
    0x2, 0x2, 0xcc, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xcd, 0x1d, 0x3, 0x2, 0x2, 
    0x2, 0xce, 0xcf, 0x8, 0x10, 0x1, 0x2, 0xcf, 0xd0, 0x7, 0x19, 0x2, 0x2, 
    0xd0, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0xc, 0x3, 0x2, 0x2, 0xd2, 
    0xd3, 0x7, 0x5, 0x2, 0x2, 0xd3, 0xd5, 0x7, 0x6, 0x2, 0x2, 0xd4, 0xd1, 
    0x3, 0x2, 0x2, 0x2, 0xd5, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd4, 0x3, 
    0x2, 0x2, 0x2, 0xd6, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd7, 0x1f, 0x3, 0x2, 
    0x2, 0x2, 0xd8, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xdf, 0x5, 0x14, 0xb, 
    0x2, 0xda, 0xdb, 0x7, 0x17, 0x2, 0x2, 0xdb, 0xdc, 0x5, 0x22, 0x12, 0x2, 
    0xdc, 0xdd, 0x7, 0x18, 0x2, 0x2, 0xdd, 0xdf, 0x3, 0x2, 0x2, 0x2, 0xde, 
    0xd9, 0x3, 0x2, 0x2, 0x2, 0xde, 0xda, 0x3, 0x2, 0x2, 0x2, 0xdf, 0x21, 
    0x3, 0x2, 0x2, 0x2, 0xe0, 0xe1, 0x8, 0x12, 0x1, 0x2, 0xe1, 0xe2, 0x5, 
    0x20, 0x11, 0x2, 0xe2, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe4, 0xc, 0x3, 
    0x2, 0x2, 0xe4, 0xe5, 0x7, 0x8, 0x2, 0x2, 0xe5, 0xe7, 0x5, 0x20, 0x11, 
    0x2, 0xe6, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xea, 0x3, 0x2, 0x2, 0x2, 
    0xe8, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe9, 0x3, 0x2, 0x2, 0x2, 0xe9, 
    0x23, 0x3, 0x2, 0x2, 0x2, 0xea, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xee, 
    0x5, 0x16, 0xc, 0x2, 0xec, 0xee, 0x5, 0x18, 0xd, 0x2, 0xed, 0xeb, 0x3, 
    0x2, 0x2, 0x2, 0xed, 0xec, 0x3, 0x2, 0x2, 0x2, 0xee, 0x25, 0x3, 0x2, 
    0x2, 0x2, 0x1b, 0x2c, 0x33, 0x37, 0x46, 0x49, 0x4b, 0x56, 0x5c, 0x67, 
    0x69, 0x75, 0x77, 0x89, 0x8b, 0x97, 0x99, 0xa4, 0xaf, 0xb7, 0xc4, 0xcc, 
    0xd6, 0xde, 0xe8, 0xed, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

tinycParser::Initializer tinycParser::_init;
