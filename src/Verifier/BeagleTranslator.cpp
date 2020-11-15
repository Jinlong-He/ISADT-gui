#include<fstream>
#include<string>
#include "Verifier/BeagleTranslator.hpp"
namespace isadt {
    string BeagleTranslator::mkProcess(Model *model, Process *process) {
        string result = "";
        result += "\tmodule " + process->getName() + "\n";

        for (auto attribute : process->getOriginalAttributes()) {
            result += "\t\tint[0:256] " + attribute->getIdentifier() + ";\n";
        }
        result += "\t\tlabel channel;\n";
        result += "\t\tlocation _init, _final";
        for (auto location : process->getVertexMap()) {
            result += ", " + location.first;
        }
        result += ";\n";
        result += "\n";

        result += "\t\tinit _init do {\n";
        for (auto ik : model->getInitialKnowledges()) {
            if (ik->getProc() == process)
            {
                result += "\t\t\t" + ik->getAttribute()->getIdentifier() + "= 0;\n";
            }
        }
        result += "\t\t};\n";

        for (auto edge : process->getStateMachine()->getEdges()) {
            result += "\t\tfrom " + edge->getFromVertex()->getName() + " to " + edge->getToVertex()->getName() + " do {\n";
            for (auto action : edge->getActions()) {
                auto lhs = action->getLhs();
                if (lhs == NULL) continue;
                auto rhs = action->getRhs();
                if (rhs == NULL) continue;
                if (lhs->getTermType() == AT) {
                    auto attrLhs = (AttributeTerm*)lhs;
                    if (rhs->getTermType() == AT) {
                        result += "\t\t\t" + attrLhs->getAttribute()->getIdentifier() + " = " + ((AttributeTerm*)rhs)->getAttribute()->getIdentifier() + ";\n";
                    }
                    else if (rhs->getTermType() == MT) {
                        result += "\t\t\t" + attrLhs->getAttribute()->getIdentifier() + " = " +
                                attrLhs->getAttribute()->getIdentifier() + " + 10;\n";
                    }
                }
            }
            result += "\t\t};\n";
        }

        result += "\tend\n";
        result += "\n";
        return result;
    }

    string BeagleTranslator::mkProcesses(Model *model) {
        string result = "";

        auto processes = model->getProcesses();
        for (auto process : processes) {
            result += this->mkProcess(model, process);
        }
        return result;
    }

    string BeagleTranslator::mkProperties(Model *model) {
        string result = "";
        for (auto property : model->getProps()) {
            if (property->getPropertyType() == CTL) {
                result += "\t\tINVARSPEC (" + ((CTLProperty*)property)->getCtlStr() + ")\n";
            }
            if (property->getPropertyType() == INVARIANT) {
                result += "\t\tINVARSPEC (" + ((InvariantProperty*)property)->getInvariantStr() + ")\n";
            }
        }
        Process* firstProc = model->getProcesses().front();
        result += "\t\tINVARSPEC (!(" + firstProc->getName() + ".location == _final))\n";
        return result;
    }

    void BeagleTranslator::beagleTranslate(Model *model) {
        std::string dstFile = "beagleModel.elt";
        std::ofstream out;
        out.open(dstFile, std::ios::trunc);

        out << "system\n";

        out << this->mkProcesses(model);
        out << this->mkProperties(model);

        out << "end\n";
        out.close();
    }
}