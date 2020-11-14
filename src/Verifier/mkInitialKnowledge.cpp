#include "Verifier/mkInitialKnowledge.hpp"

namespace isadt {
    std::string mkInitialKnowledge(Model* model) {
        string result = "new skA: skey; let pkA = pk(skA) in out(c, pkA);\n\tnew skB: skey; let pkB = pk(skB) in out(c, pkB);\n";
        return result;
    }

    std::string mkInitialProcess(Model* model) {
        string result = "( (!processA(pkB, skA)) | (!processB(pkA, skB)) )";
        return result;
    }
}