#include "Verifier/ProverifTranslator.hpp"
using std::cout, std::endl;
namespace isadt {
    void ProverifTranslator::translateProcess(Process* process) {
        auto sm = process -> getStateMachines().front();
        auto vertex = sm -> getStartVertex();
        while (vertex != sm -> getEndVertex()) {
            auto edge = vertex -> getNexts().front();
            auto& actions = edge -> getActions();
            for (auto action : actions) {
                
            }
            vertex = edge -> getToVertex();
        }
    }
    void ProverifTranslator::translate() {
        for (auto p : model_ -> getProcesses()) {
            translateProcess(p);
        }
    }
}

