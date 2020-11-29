#include "Verifier/ProverifTranslator.hpp"
using std::cout, std::endl;
namespace isadt {
    void getMessage(const list<Action*>& actions, unordered_map<Attribute*, vector<Term*>>& map) {
        for (auto action : actions) {
                cout << "action" << action << endl;
            if (action -> isAssignmentAction()) {
                if (action -> getLhs() -> getTermType() == AT) {
                    auto at = (AttributeTerm*)action -> getLhs();
                    cout << "at" << at << endl;
                    auto attr = at -> getAttribute();
                    auto type = attr -> getType();
                    cout << type << endl;
                    if (type -> getAttributes().size() == 0) {
                        continue;
                    }
                    cout << 111 << endl;
                    auto& vec = map[attr];
                    if (map.count(attr) == 0) {
                        vec.resize(type -> getAttributes().size());
                    }
                    cout << 222 << endl;
                    auto childTerm = at -> getChildren().front();
                    cout << childTerm << endl;
                    auto child = ((AttributeTerm*)childTerm) -> getAttribute();
                    cout << child -> getIdentifier() << endl;
                    cout << type -> getID(child -> getIdentifier()) << endl;
                    vec[type -> getID(child -> getIdentifier())] = action -> getRhs();
                    cout << 333 << endl;
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
            unordered_map<Attribute*, vector<Term*> > map;
            getMessage(actions, map);
            for (auto&[attr, vec] : map) {
                cout << attr -> getIdentifier() << " ";
                for (auto term : vec) {
                    cout << term -> to_string() << "";
                }
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

