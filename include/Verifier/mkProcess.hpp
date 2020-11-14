#ifndef ISADT_MKPROCESS_HPP
#define ISADT_MKPROCESS_HPP

#include <iostream>
#include <./Model/Model.hpp>
#include <./Model/Process/Process.hpp>
namespace isadt {
    std::string mkProcess(Process* process, Model* model);
    std::string mkDefaultProcess(Model* model);
}


#endif //ISADT_MKPROCESS_HPP
