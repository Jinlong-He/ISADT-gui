#include "Verifier/ProverifTranslator.hpp"
using std::cout, std::endl;
namespace isadt {
    void getMessage(const list<Action*>& actions, unordered_map<Attribute*, vector<Attribute>>& map) {
        for (auto action : actions) {
            if (action -> isAssignmentAction()) {
                if (action -> getRhs() -> getTermType() == AT) {
                    auto at = (AttributeTerm*)action -> getLhs();
                    auto attr = at -> getAttribute();
                    auto type = attr -> getType();
                    if (type -> getAttributes().size() == 0) {
                        continue;
                    }
                    auto& vec = map[attr];
                    if (map.count(attr) == 0) {
                        vec.resize(type -> getAttributes().size());
                    }
                    auto child = attr -> getChildren().front();
                    vec[type -> getID()];
                }
            }
        }
    }

    void ProverifTranslator::translateProcess(Process* process) {
        auto sm = process -> getStateMachines().front();
        auto vertex = sm -> getStartVertex();
        while (vertex != sm -> getEndVertex()) {
            auto edge = vertex -> getNexts().front();
            const auto& actions = edge -> getActions();
            for (auto action : actions) {
                if (action -> isAssignmentAction()) {
                    if (action -> getRhs() -> getTermType() == MT) {
                        auto mt = (MethodTerm*)action -> getRhs();
                        if (mt -> getMethod() -> getName() == "") {
                            //signature
                            const auto& args = mt -> getArgs();
                            auto iter = args.begin();
                            auto message = ((AttributeTerm*)(*(iter++))) -> getAttribute();
                            auto key = ((AttributeTerm*)(*(iter))) -> getAttribute();
                        }
                    }
                    if (action -> getLhs() -> getTermType() == AT) {
                    }
                }
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

