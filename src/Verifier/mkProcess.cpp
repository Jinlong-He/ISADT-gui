#include "Verifier/mkProcess.hpp"

namespace isadt {
    std::string mkProcess(Process* process,Model* model) {
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
        //for ()
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