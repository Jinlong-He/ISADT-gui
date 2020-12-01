#include "Verifier/ProverifTranslator.hpp"
#include <iostream>
#include <fstream>
using std::cout, std::endl;
namespace isadt {
    void getMessage(const list<Action*>& actions, unordered_map<string, vector<string>>& attrMap,
            unordered_map<string, string>& strMap, std::ostream& os) {
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
                    //os << action -> getRhs() -> getChildren().size() << endl;
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

    void ProverifTranslator::translateProcess(Process* process, std::ostream& os, unordered_map<Process*, vector<Attribute*>>& confPropMap) {
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
                    getMessage(messageActions, attrMap, strMap, os);
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
                            os << res1 << endl << res2 << endl;
                        } else {
                            string res = "out(c,";
                            if (signMap.count(messStr) > 0) {
                                res += signMap.at(messStr) + ");";
                            } else {
                                res += messStr + ");";
                            }
                            os << res << endl;
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
                                res1 += name + ":int ,";
                            }
                            res1[res1.length() - 1] = ')';
                            res2[res2.length() - 1] = ')';
                            string res = res1 + res2 + " in";
                            os << res << endl;
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
                                os << res << endl;
                            }
                        } else {
                        }
                    }
                    messageActions.push_back(action);
                }
            }
        }
        if (confPropMap.count(process) > 0) {
            for (auto attr : confPropMap.at(process)) {
                os << "let " + process -> getName() + attr -> getIdentifier()
                    + "=" + attr -> getIdentifier() + "." << endl;
            }
        } else {
            os << "new end:bitstring;" << endl;
            os << "out(c, end)." << endl;
        }
    }

    void ProverifTranslator::translate() {
        std::ofstream os;
        os.open("proverif.pv");
        os << "free c : channel." << endl;
        os << "type spkey." << endl;
        os << "type sskey." << endl;
        os << "type int." << endl;
        os << "fun spk(sskey): spkey." << endl;
        os << "fun sign(bitstring, sskey): bitstring." << endl;
        os << "reduc forall x: bitstring, y: sskey; getmess(sign(x,y)) = x." << endl;
        os << "reduc forall x: bitstring, y: sskey; checksign(sign(x,y), spk(y)) = x." << endl;
        unordered_map<Process*, vector<Attribute*>> confPropMap;
        for (auto p : model_ -> getProps()) {
            if (p -> getPropertyType() == CONFIDENTIAL) {
                auto pp = ((ConfidentialProperty*) p);
                os << "query secret " + pp -> getProc() -> getName() + pp -> getAttribute() -> getIdentifier() + "." << endl;
                confPropMap[pp -> getProc()].push_back(pp -> getAttribute());
            }
        }
        for (auto p : model_ -> getProps()) {
            if (p -> getPropertyType() == INTEGRATY) {
                auto pp = (IntegratyProperty*) p;
                os << "event " + 
                    pp -> getProc1() -> getName() + pp -> getVertex1() 
                    + "(" + pp -> getAttr1() -> getType() -> getName() + ")." << endl;
                os << "event " + 
                    pp -> getProc2() -> getName() + pp -> getVertex2() 
                    + "(" + pp -> getAttr2() -> getType() -> getName() + ")." << endl;
                os << "query " + pp -> getAttr1() -> getIdentifier() + ":" +
                    pp -> getAttr1() -> getType() -> getName() + "; inj-event(" +
                    pp -> getProc2() -> getName() + pp -> getVertex2() +
                    "(" + pp -> getAttr1() -> getIdentifier() + ")) ==> inj-event(" +
                    pp -> getProc1() -> getName() + pp -> getVertex1() +
                    "(" + pp -> getAttr1() -> getIdentifier() + "))." << endl;
            }
        }
        unordered_map<Process*, vector<Attribute*> > knowledgeMap;
        unordered_map<string, string> pairMap;
        string endStr = "process\n";
        string startProcStr = "(";
        for (auto n : model_ -> getInitialKnowledges()) {
            if (!n -> isKeyPair()) {
                knowledgeMap[n -> getProc()].push_back(n -> getAttribute());
            } else {
                string pkStr = n -> getAttribute() -> getType() -> getName();
                if (pkStr == "spkey") pkStr = "spk";
                if (pkStr == "pkey") pkStr = "pk";
                pairMap[n -> getAttribute() -> getIdentifier()] =
                        n -> getPkKnowledge() -> getAttribute() -> getIdentifier(); 
                string res = "new " + n -> getPkKnowledge() -> getAttribute() -> getIdentifier() + ": "
                    + n -> getPkKnowledge() -> getAttribute() -> getType() -> getName() + ";";
                res += "let " +n -> getAttribute() -> getIdentifier()
                    + "=" + pkStr + "(" + n -> getPkKnowledge() -> getAttribute() -> getIdentifier() + ") in out(c, " 
                    + n -> getPkKnowledge() -> getAttribute() -> getIdentifier() + ");\n";

                endStr += res;
            }
        }
        for (auto p : model_ -> getProcesses()) {
            string res = "let process" + p -> getName() + "( ";
            startProcStr += "(!process" + p -> getName() + "(";
            for (auto attr : knowledgeMap[p]) {
                res += attr -> getIdentifier() + " : " + attr -> getType() -> getName() + ",";
                startProcStr += attr -> getIdentifier() + ",";
            }
            res[res.length() - 1] = ')';
            startProcStr[startProcStr.length() - 1] = ')';
            res += "=";
            startProcStr += ")|";
            os << res << endl;
            translateProcess(p, os, confPropMap);
        }
        startProcStr[startProcStr.length() - 1] = ')';
        os << endStr << endl;
        os << startProcStr << endl;
    }
}

