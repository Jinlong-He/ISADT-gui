#include "Verifier/ProverifTranslator.hpp"
using std::cout, std::endl;
namespace isadt {
    void getMessage(const list<Action*>& actions, unordered_map<string, vector<string>>& attrMap,
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
                    if (action -> getRhs() -> getChildren().size() == 0) {
                        string name = ((AttributeTerm*)action -> getRhs()) -> getAttribute() -> getIdentifier();
                        attrMap.at(attr -> getIdentifier())[type -> getID(child -> getIdentifier())] = name;
                    } else {
                        string name = ((AttributeTerm*)action -> getRhs()) -> getType() -> getName() + "_" +
                            ((AttributeTerm*)((Expression*)action -> getRhs() -> getChildren().front()) -> getTerm1()) -> getAttribute() -> getIdentifier();
                        
                        attrMap.at(attr -> getIdentifier())[type -> getID(child -> getIdentifier())] = name;
                    }
                }
            }
        }
        for (auto&[attr, vec] : attrMap) {
            auto& str = strMap[attr];
            str = "(";
            for (auto name : vec) {
                str += name + ",";
            }
            str[str.length() - 1] = ')';
        }
    }

    void ProverifTranslator::translateProcess(Process* process) {
        string res = "let process" + process -> getName() + "(";
        unordered_set<string> attrSet;
        auto sm = process -> getStateMachines().front();
        auto vertex = sm -> getStartVertex();
        list<Action*> actions;
        while (vertex != sm -> getEndVertex()) {
            auto edge = vertex -> getNexts().front();
            if (!edge -> isGuardNull()) {
                actions.push_back(new Action(edge -> getGuard() -> getExpression()));
            }
            actions.insert(actions.end(), edge -> getActions().begin(), edge -> getActions().end());
            vertex = edge -> getToVertex();
        }
        list<Action*> messageActions;
        unordered_map<string, vector<string> > attrMap;
        unordered_map<string, string> strMap;
        unordered_map<string, vector<string> > verMap;
        unordered_map<string, string> signMap;
        for (auto action : actions) {
            if (action -> isAssignmentAction()) {
                if (!action -> getRhs() && action -> getLhs() -> getTermType() == MT) {
                    getMessage(messageActions, attrMap, strMap);
                    messageActions.clear();
                    auto methodTerm = ((MethodTerm*)action -> getLhs());
                    auto method = methodTerm -> getMethod();
                    if (method -> isCommMethod()) {
                        auto mess = methodTerm -> getArgs().front();
                        if (mess -> getTermType() != AT) continue;
                        string messStr = ((AttributeTerm*)mess) -> getAttribute() -> getIdentifier();
                        if (!((CommMethod*)method) -> getInOut()) {
                            string name = method -> getName() + "_m";
                            string res1 = "in(c," + name + ": bitstring);";
                            string res2 = "let " + messStr + " = " + name + " in";
                            cout << res1 << endl << res2 << endl;
                        } else {
                            string res = "out(c,";
                            if (signMap.count(messStr) > 0) {
                                res += signMap.at(messStr) + ");";
                            } else {
                                res += messStr + ");";
                            }
                            cout << res << endl;
                        }
                    } else {
                        if (method -> getName() == "Sign") {
                            //string res = "new "
                            string res = "sign(";
                            string firstStr = "";
                            size_t i = 0;
                            for (auto attrTerm : methodTerm -> getArgs()) {
                                if (attrTerm -> getTermType() != AT) continue;
                                const auto& attrStr = ((AttributeTerm*)attrTerm) -> getAttribute() -> getIdentifier();
                                if (i == 0) firstStr = attrStr;
                                if (strMap.count(attrStr) > 0) {
                                    res += strMap[attrStr] + ",";
                                } else {
                                    res += attrStr + ",";
                                }
                                i++;
                            }
                            res[res.length() - 1] = ')';
                            signMap[firstStr] = res;
                        } else if (method -> getName() == "Verify") {
                            string res1 = "let (";
                            string res2 = " = checksign(";
                            size_t i = 0;
                            Attribute* attr = nullptr;
                            for (auto attrTerm : methodTerm -> getArgs()) {
                                if (attrTerm -> getTermType() != AT) continue;
                                const auto& attrStr = ((AttributeTerm*)attrTerm) -> getAttribute() -> getIdentifier();
                                if (i == 0)  attr = ((AttributeTerm*)attrTerm) -> getAttribute();
                                res2 += attrStr + ",";
                                i++;
                            }
                            auto type = attr -> getType();
                            auto& vec = verMap[attr -> getIdentifier()];
                            for (auto attr : type -> getAttributes()) {
                                string name = type -> getName() + "_" + attr -> getIdentifier();
                                vec.push_back(name);
                                res1 += name + ",";
                            }
                            res1[res1.length() - 1] = ')';
                            res2[res2.length() - 1] = ')';
                            string res = res1 + res2 + " in";
                            cout << res << endl;
                        }
                    }
                } else {
                    auto rhsTerm = action -> getRhs();
                    if (rhsTerm != nullptr && rhsTerm -> getTermType() == AT) {
                        if (rhsTerm -> getChildren().size() == 0) {
                            string attrStr = ((AttributeTerm*) rhsTerm) -> getAttribute() -> getIdentifier();
                            string typeStr = ((AttributeTerm*) rhsTerm) -> getAttribute() -> getType() -> getName();
                            if (attrSet.count(attrStr) == 0) {
                                attrSet.insert(attrStr);
                                string res = "new " + attrStr + ":" + typeStr + ";";
                                cout << res << endl;
                            }
                        } else {
                        }
                    }
                    messageActions.push_back(action);
                }
            }
        }
    }

    void ProverifTranslator::translate() {
        for (auto p : model_ -> getProcesses()) {
            translateProcess(p);
        }
    }
}

