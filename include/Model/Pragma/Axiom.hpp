#ifndef Model_Axiom_hpp
#define Model_Axiom_hpp 
#include "../Process/MethodBase.hpp"

namespace isadt {
    class Process;
    class Axiom {
    public:
        Axiom() {}
        ~Axiom() {
            for (auto procMethod : procMethods_) {
                delete procMethod;
                procMethod = nullptr;
            }
        }
        void addProcMethod(Process* proc, MethodBase* method);
        void setAxiomStr(const string& axiomStr);
    private:
        struct ProcMethodPair {
        public:
            ProcMethodPair()
                : proc_(nullptr),
                  method_(nullptr) {}
            ProcMethodPair(Process* proc, MethodBase* method)
                : proc_(proc),
                  method_(method) {}
        private:
            Process* proc_;
            MethodBase* method_;
        };

        list<ProcMethodPair*> procMethods_;
        string axiomStr_;
    };
}

#endif /* Axiom_hpp */
