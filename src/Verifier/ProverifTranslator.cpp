#include "Verifier/ProverifTranslator.hpp"
using std::cout, std::endl;
namespace isadt {
    void getMessage(const list<Action*>& actions, unordered_map<string, vector<Term*>>& map) {
        for (auto action : actions) {
            if (action -> isAssignmentAction()) {
                if (action -> getLhs() -> getTermType() == AT) {
                    auto at = (AttributeTerm*)action -> getLhs();
                    auto attr = at -> getAttribute();
                    auto type = at -> getType();
                    if (type -> getAttributes().size() == 0) {
                        continue;
                    }
                    if (map.count(attr -> getIdentifier()) == 0) {
                        map[attr -> getIdentifier()].resize(type -> getAttributes().size());
                    }
                    auto childTerm = at -> getChildren().front();
                    auto child = ((AttributeTerm*)((Expression*)childTerm) -> getTerm1()) -> getAttribute();
                    map.at(attr -> getIdentifier())[type -> getID(child -> getIdentifier())] = action -> getRhs();
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
                    if (!action -> getRhs() && action -> getLhs() -> getTermType() == MT) {
                        auto methodTerm = ((MethodTerm*)action -> getLhs());
                        auto method = methodTerm -> getMethod();
                        if (method -> isCommMethod()) {
                        } else {
                            if (method -> getName() == "Sign") {
                                for (auto attrTerm : methodTerm -> getArgs()) {
                                    if (attrTerm -> getTermType() == AT) {
                                        const auto& attrStr = ((AttributeTerm*)attrTerm) -> getAttribute() -> getIdentifier();
                                    }
                                }
                            } else if (method -> getName() == "Verify") {
                            }
                        }
                    }
                    messageActions.push_back(action);
                }
            }
            unordered_map<string, vector<Term*> > attrMap;
            unordered_map<string, string> strMap;
            getMessage(messageActions, attrMap);
            for (auto&[attr, vec] : attrMap) {
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

