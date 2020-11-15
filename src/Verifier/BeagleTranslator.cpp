#include<iostream>
#include<fstream>
#include<string>
#include "Verifier/BeagleTranslator.hpp"
namespace isadt {
    void BeagleTranslator::beagleTranslate(Model *model) {
        std::string dstFile = "beagle_Model.pv";
        std::ofstream out;
        out.open(dstFile, std::ios::trunc);

        out.close();
    }
}