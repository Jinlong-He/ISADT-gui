#include <iostream>
#include <list>
#include "../include/Model/Model.hpp"
#include "../include/Parser/XmlParser/XmlParser.hpp"
#include "../include/Parser/LParser/LParser.hpp"
#include "../include/CodeGenerator/CCodeGenerator.hpp"
#include "../include/Manage.hpp"
using namespace std;
using namespace isadt;

unordered_set<string> Manage::eqOps_({"==", "!=", ">", ">=", "<", "<="});
unordered_set<string> Manage::arOps_({"+", "-", "*", "/"});
UserType* Manage::intType_(new UserType("int"));
UserType* Manage::boolType_(new UserType("bool"));
UserType* Manage::numberType_(new UserType("number"));
UserType* Manage::byteType_(new UserType("byte"));
UserType* Manage::byteVecType_(new UserType("ByteVec"));
UserType* Manage::timerType_(new UserType("Timer"));
unordered_map<string, UserType*> Manage::typeMap_({{"int", Manage::intType_},
                                                   {"bool", Manage::boolType_},
                                                   {"number", Manage::numberType_},
                                                   {"byte", Manage::byteType_},
                                                   {"ByteVet", Manage::byteVecType_},
                                                   {"Timer", Manage::timerType_}});

int main(int argc, char *argv[]) {
    try {
        Model model;
        Manage::timerType_ -> mkAttribute(Manage::numberType_, "time");
        Manage::timerType_ -> mkMethod("reset", Manage::numberType_, "", "");
        XmlParser::parse(argv[1], &model);
        for (auto proc : model.getProcesses()) {
            if (proc -> getStateMachines().size() > 1)
                proc -> getStateMachine() -> print();
        }
    } catch (string e) {
        cout << e << endl;
        exit(1);
    }
}
