#include "Verifier/ProverifTranslator.hpp"
using std::cout, std::endl;
namespace isadt {
    void getMessage(const list<Action*>& actions, unordered_map<string, vector<Term*>>& attrMap,
            unordered_map<string, string>& strMap) {
        for (auto action : actions) {
            if (action -> isAssignmentAction()) {
                if (action -> getLhs() -> getTermType() == AT) {
                    auto at = (AttributeTerm*)action -> getLhs();
                    auto attr = at -> getAttribute();
                    auto type = at -> getType();
                    if (type -> getAttributes().size() == 0) {
                        continue;
                    }
                    if (attrMap.count(attr -> getIdentifier()) == 0) {
                        attrMap[attr -> getIdentifier()].resize(type -> getAttributes().size());
                    }
                    auto childTerm = at -> getChildren().front();
                    auto child = ((AttributeTerm*)((Expression*)childTerm) -> getTerm1()) -> getAttribute();
                    attrMap.at(attr -> getIdentifier())[type -> getID(child -> getIdentifier())] = action -> getRhs();
                }
            }
        }
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
    }

    void ProverifTranslator::translateProcess(Process* process) {
        auto sm = process -> getStateMachines().front();
        auto vertex = sm -> getStartVertex();
        while (vertex != sm -> getEndVertex()) {
            auto edge = vertex -> getNexts().front();
            list<Action*> messageActions;
            const auto& actions = edge -> getActions();
            unordered_map<string, vector<Term*> > attrMap;
            unordered_map<string, string> strMap;
            for (auto action : actions) {
                if (action -> isAssignmentAction()) {
                    if (!action -> getRhs() && action -> getLhs() -> getTermType() == MT) {
                        getMessage(messageActions, attrMap, strMap);
                        messageActions.clear();
                        auto methodTerm = ((MethodTerm*)action -> getLhs());
                        auto method = methodTerm -> getMethod();
                        if (method -> isCommMethod()) {
                            string inoutStr = ((CommMethod*)method) -> getInOut() ? "in" : "out";
                            auto mess = methodTerm -> getArgs().front();
                            if (mess -> getTermType() != AT) continue;
                            string messStr = ((AttributeTerm*)mess) -> getAttribute() -> getIdentifier();
                            string res = inoutStr + "(c, " + messStr + ": bitstring);";
                            cout << res << endl;
                        } else {
                            if (method -> getName() == "Sign") {
                                //string res = "new "
                                string res = "sign(";
                                for (auto attrTerm : methodTerm -> getArgs()) {
                                    if (attrTerm -> getTermType() != AT) continue;
                                    const auto& attrStr = ((AttributeTerm*)attrTerm) -> getAttribute() -> getIdentifier();
                                    if (strMap.count(attrStr) > 0) {
                                        res += strMap[attrStr] + ",";
                                    } else {
                                        res += attrStr + ",";
                                    }
                                }
                                res[res.length() - 1] = ')';
                                cout << res << endl;
                            } else if (method -> getName() == "Verify") {
                            }
                        }
                    } else {
                        messageActions.push_back(action);
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

