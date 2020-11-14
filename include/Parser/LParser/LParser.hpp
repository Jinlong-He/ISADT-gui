//
//  Model.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Parser_C_hpp 
#define Parser_C_hpp
#include <string>
#include <vector>
#include "../../Model/Model.hpp"
#include "antlr4-runtime.h"
#include "tinycLexer.h"
#include "tinycParser.h"
#include "tinycBaseVisitor.h"
#include "tinycBaseListener.h"
#pragma execution_character_set("utf-8")
using namespace antlrcpp;
using namespace antlr4;
using std::string;
using std::vector;
namespace isadt {
    class LParser {
    public:
        static void parseGuard(const char* text, Model* model, Process* proc, Edge* edge);
        static void parseAction(const char* text, Model* model, Process* proc, Edge* edge);
        static tinycParser::StatementContext* parse(const char* text, Model* model, Process* proc, Edge* edge);
    };
}
#endif /* Parser_C_hpp */

