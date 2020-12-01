#include <iostream>
#include <list>
#include "../include/Model/Model.hpp"
#include "../include/Parser/XmlParser/XmlParser.hpp"
#include "../include/Parser/LParser/LParser.hpp"
#include "../include/CodeGenerator/CCodeGenerator.hpp"
#include "../include/CodeGenerator/CPPCodeGenerator.hpp"
#include "../include/CodeGenerator/JavaCodeGenerator.hpp"
#include "../include/Verifier/ProverifTranslator.hpp"
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
        XmlParser::parse(argv[2].c_str(), &model);
        cout << "#true#";
    }
}
