#ifndef ISADT_BEAGLETRANSLATOR_HPP
#define ISADT_BEAGLETRANSLATOR_HPP

#include <iostream>
#include <./Model/Model.hpp>
#include "../Model/Process/Process.hpp"

namespace isadt {
    class BeagleTranslator {
    public:
        void beagleTranslate(Model* model);

    private:
        string mkProcesses(Model* model);
        string mkProcess(Model* model, Process* process);
        string mkProperties(Model* model);
    };
}


#endif //ISADT_BEAGLETRANSLATOR_HPP
