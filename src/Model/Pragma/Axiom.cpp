#include "Model/Pragma/Axiom.hpp"
namespace isadt {
    void Axiom::addProcMethod(Process* proc, MethodBase* method) {
        procMethods_.push_back(new ProcMethodPair(proc, method));
    }

    void Axiom::setAxiomStr(const string& axiomStr) {
        axiomStr_ = axiomStr;
    }
}
