#include "Verifier/mkProcess.hpp"

namespace isadt {
    string mkEdgeModel(Edge *pEdge);
    string mkAttributeTermAction(Edge* edge, Action* action);
    string mkMethodTermAction(Edge* edge, Action* action);
    string getArgStr(Term* arg);
    string mkCommMethodAction(Edge* edge, Action* action);

    std::string mkProcess(Process* process, Model* model) {
        string result = "";
        result += "let "+process->getName()+"(";
        bool isFirst = true;
        for (auto ik : model->getInitialKnowledges()) {
            if (ik->getProc() == process)
            {
                if (!isFirst) {
                    result += " ,";
                }
                Attribute* attribute = ik->getAttribute();
                result += attribute->getIdentifier()+": "+attribute->getType()->getName();
                isFirst = false;
            }
        }
        result += ")=\n";
        for (auto originalAttribute : process->getOriginalAttributes()) {
            if (originalAttribute->getType()->getName() == "int")
                originalAttribute->getType()->setName("ByteVec");
            result += "\tnew " + originalAttribute->getIdentifier() + ": " + originalAttribute->getType()->getName() + ";\n";
        }
        //return result+"0.\n";
        // Add start vertex
        StateMachine* sm = process->getStateMachine();
        Vertex* startVertex = sm->getStartVertex();
        std::unordered_map<Edge*, bool> usedEdge;
        for (auto edge : sm->getEdges()) {
            usedEdge[edge] = false;
        }
        std::list<Vertex*> vertexList;
        vertexList.push_back(startVertex);
        while (!vertexList.empty()) {
            Vertex* curVertex = *vertexList.begin();
            result += "\tevent " + process->getName() + "_" + curVertex->getName() + "();\n";
            vertexList.pop_front();
            for (auto next : curVertex->getNexts()) {
                if (!usedEdge[next])
                {
                    vertexList.push_back(next->getToVertex());
                    usedEdge[next] = true;
                    result += mkEdgeModel(next);
                }
            }
        }
        return result+"\t0.\n\n";
    }

    string mkEdgeModel(Edge *edge) {
        std::string result = "";
        for (auto action : edge->getActions())
        {
            auto lhs = action->getLhs();
            auto rhs = action->getRhs();
            if (lhs == NULL) continue;
            auto lhsTermType = lhs->getTermType();
            if (lhsTermType == MT) {
                result += mkCommMethodAction(edge, action);
                continue;
            }
            if (rhs == NULL) continue;
            auto termType = rhs->getTermType();
            switch(termType) {
                case AT: result += mkAttributeTermAction(edge, action); break;
                case MT: result += mkMethodTermAction(edge, action); break;
                case CT:
                case LT:
                case EXP:
                default: break;
            }
            //result += "let " + lhs->getAttribute()->getIdentifier() + "=";
            //result += " in\n";
        }
        return result;
    }

    std::string mkAttributeTermAction(Edge* edge, Action* action) {
        string result = "";
        auto lhs = action->getLhs();
        auto rhs = action->getRhs();
        result += "\tlet " + ((AttributeTerm*)lhs)->getAttribute()->getIdentifier() + "=";
        result += ((AttributeTerm*)rhs)->getAttribute()->getIdentifier();
        result += " in\n";
        return result;
    }

    string mkMethodTermAction(Edge* edge, Action* action) {
        string result = "";
        auto lhs = action->getLhs();
        auto rhs = action->getRhs();
        result += "\tlet " + ((AttributeTerm*)lhs)->getAttribute()->getIdentifier() + "=";
        result += ((MethodTerm*)rhs)->getMethod()->getName()+"(";
        bool isFirst = true;
        for (auto arg : ((MethodTerm*)rhs)->getArgs()) {
            if (isFirst)
            {
                result +=  getArgStr(arg);
                isFirst = false;
            }
            else {
                result += ", " + getArgStr(arg);
            }
        }
        result += ") in\n";
        return result;
    }

    string mkCommMethodAction(Edge* edge, Action* action) {
        string result = "";
        auto lhs = action->getLhs();
        auto commMethod = ((MethodTerm*)lhs)->getMethod();
        bool isSendMethod = ((CommMethod*)commMethod)->getInOut();
        if (isSendMethod) {
            result += "\tout(c, ";
            auto arg = ((MethodTerm*)lhs)->getArgs().front();
            auto attr = ((AttributeTerm*)arg)->getAttribute();
            result += attr->getIdentifier();
            result += ");\n";
        }
        else {
            result += "\tin(c, ";
            auto arg = ((MethodTerm*)lhs)->getArgs().front();
            auto attr = ((AttributeTerm*)arg)->getAttribute();
            result += attr->getIdentifier() + ":" + attr->getType()->getName();
            result += ");\n";
        }
        return result;
    }

    string getArgStr(Term* arg) {
        string result = "";
        if (arg->getTermType() == AT) {
            result += ((AttributeTerm*)arg)->getAttribute()->getIdentifier();
        }
        else {
            result += ((MethodTerm*)arg)->getMethod()->getName()+"(";
            bool isFirst = true;
            for (auto methodArg : ((MethodTerm*)arg)->getArgs())
                if (isFirst)
                {
                    result +=  getArgStr(methodArg);
                    isFirst = false;
                }
                else {
                    result += ", " + getArgStr(methodArg);
                }
            result += ")";
        }
        return result;
    }

    std::string mkStateMachine() {
        string result = "";

        return result;
    }

    std::string mkDefaultProcess(Model* model) {
        std::string result = "let processA(pkB: pkey, skA: skey) =\n"
                             "\tin(c, pkX: pkey);\n"
                             "\tevent beginBparam(pkX); \n"
                             "\tnew Na: bitstring; \n"
                             "\tout(c, aenc((Na, pk(skA)), pkX));\n"
                             "\tin(c, m: bitstring); \n"
                             "\tlet (=Na, NX: bitstring) = adec(m, skA) in\n"
                             "\tout(c, aenc(NX, pkX));\n"
                             "\tif pkX = pkB  then\n"
                             "\tevent endAparam(pk(skA));\n"
                             "\tlet NaA = Na in\n"
                             "\tlet NbA = NX.\n"
                             "\n";

        result += "let processB(pkA: pkey, skB: skey) =\n"
                  "\tin(c, m: bitstring);\n"
                  "\tlet (NY: bitstring, pkY: pkey) = adec(m, skB) in\n"
                  "\tevent beginAparam(pkY);\n"
                  "\tnew Nb: bitstring;\n"
                  "\tout(c, aenc((NY, Nb), pkY));\n"
                  "\tin(c, m3: bitstring);\n"
                  "\tif Nb = adec(m3, skB) then\n"
                  "\tif pkY = pkA then\n"
                  "\tevent endBparam(pk(skB));\n"
                  "\tlet nonceA = NY in\n"
                  "\tlet nonceB = Nb.\n\n";
        return result;
    }
}