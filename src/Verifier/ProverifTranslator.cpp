#include "Verifier/ProverifTranslator.hpp"
using std::cout, std::endl;
namespace isadt {
    void getMessage(const list<Action*>& actions, unordered_map<Attribute*, vector<Term*>>& map) {
        for (auto action : actions) {
            if (action -> isAssignmentAction()) {
                if (action -> getLhs() -> getTermType() == AT) {
                    auto at = (AttributeTerm*)action -> getLhs();
                    auto attr = at -> getAttribute();
                    auto type = at -> getType();
                    if (type -> getAttributes().size() == 0) {
                        continue;
                    }
                    if (map.count(attr) == 0) {
                        map[attr].resize(type -> getAttributes().size());
                    }
                    auto childTerm = at -> getChildren().front();
                    auto child = ((AttributeTerm*)((Expression*)childTerm) -> getTerm1()) -> getAttribute();
                    map.at(attr)[type -> getID(child -> getIdentifier())] = action -> getRhs();
                }
            }
        }
    }


    void ProverifTranslator::translateProcess(Process* process) {
        auto sm = process -> getStateMachines().front();
        auto vertex = sm -> getStartVertex();
        while (vertex != sm -> getEndVertex()) {
            auto edge = vertex -> getNexts().front();
            list<Action*> messageActions;
            const auto& actions = edge -> getActions();
            for (auto action : actions) {
                if (action -> isAssignmentAction()) {
                    if (!action -> getRhs()) break;
                    messageActions.push_back(action);
                }
            }
            unordered_map<Attribute*, vector<Term*> > map;
            unordered_map<Attribute*, string> strMap;
            getMessage(messageActions, map);
            for (auto&[attr, vec] : map) {
                auto& str = strMap[attr];
                str = "(";
                for (auto term : vec) {
                    if (term) {
                        str += term -> to_string() + ",";
                    }
                }
                str[str.length() - 1] = ')';
            }

            //for (auto action : actions) {
            //    if (action -> isAssignmentAction()) {
            //        if (action -> getRhs() -> getTermType() == MT) {
            //            auto mt = (MethodTerm*)action -> getRhs();
            //            if (mt -> getMethod() -> getName() == "") {
            //                //signature
            //                const auto& args = mt -> getArgs();
            //                auto iter = args.begin();
            //                auto message = ((AttributeTerm*)(*(iter++))) -> getAttribute();
            //                auto key = ((AttributeTerm*)(*(iter))) -> getAttribute();
            //            }
            //        }
            //    }
            //}
            vertex = edge -> getToVertex();
        }
    }
    void ProverifTranslator::translate() {
        for (auto p : model_ -> getProcesses()) {
            translateProcess(p);
        }
    }
}

