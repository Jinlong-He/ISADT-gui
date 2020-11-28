#ifndef ISADT_PROVERIFTRANSLATOR_HPP
#define ISADT_PROVERIFTRANSLATOR_HPP
#include "../Model/Model.hpp"
namespace isadt {
    class ProverifTranslator {
    public:
        ProverifTranslator()
            : model_(nullptr) {}

        ProverifTranslator(Model* model)
            : model_(model) {}

        void translate();
        void translateProcess(Process* proc);
    private:
        Model* model_;
    };
}

#endif //ISADT_PROVERIFTRANSLATOR_HPP
