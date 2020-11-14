#ifndef ISADT_MKINITIALKNOWLEDGE_HPP
#define ISADT_MKINITIALKNOWLEDGE_HPP
#include <iostream>
#include <./Model/Model.hpp>
namespace isadt {
    std::string mkInitialKnowledge(Model* model);
    std::string mkInitialProcess(Model* model);
}

#endif //ISADT_MKINITIALKNOWLEDGE_HPP
