#include "Verifier/mkProcesses.hpp"

namespace isadt {
    std::string mkProcesses(Model* model) {
        string result;
        auto processes = model->getProcesses();
        for (auto process : processes) {
            result += mkProcess(process, model);
        }
        //result += mkDefaultProcess(model);
        return result;
    }
}