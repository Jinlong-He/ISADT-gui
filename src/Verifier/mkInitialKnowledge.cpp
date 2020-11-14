#include "Verifier/mkInitialKnowledge.hpp"

namespace isadt {
    std::string mkInitialKnowledge(Model* model) {
        //string result = "new ska: sk; let pka = pk(ska) in out(c, pka);\n\tnew skb: sk; let pkb = pk(skb) in out(c, pkb);\n";
        string result = "";
        for (auto ik : model->getInitialKnowledges()) {
            if (ik->getPkKnowledge() == NULL)
            {
                Attribute* attr = ik->getAttribute();
                result += "\tnew " + attr->getIdentifier() + " :pk;\n";
            }
            else {
                Attribute* attr = ik->getAttribute();
                Attribute* attr1 = ik->getPkKnowledge()->getAttribute();
                result += "\tnew " + attr1->getIdentifier() + " :sk; ";
                result += "let " + attr->getIdentifier() + "= pk1(" + attr1->getIdentifier() + ") in out(c, " + attr->getIdentifier() + ");\n";
            }
        }
        return result;
    }

    std::string mkInitialProcess(Model* model) {
        string result = "\t(";
        bool isFirst = true;
        for (auto process : model->getProcesses()) {
            if (isFirst) {
                isFirst = false;
            }
            else {
                result += "|";
            }
            result += "(!"+process->getName()+"(";
            bool isFirstArg = true;
            for (auto ik : model->getInitialKnowledges()) {
                if (ik->getProc() == process)
                {
                    if (!isFirstArg) {
                        result += " ,";
                    }
                    Attribute* attribute = ik->getAttribute();
                    result += attribute->getIdentifier();
                    isFirstArg = false;
                }
            }
            result += "))";
        }
        result += ")\n";
        return result;
    }
}