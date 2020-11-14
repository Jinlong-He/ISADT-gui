#ifndef CodeGenerator_CodeGenerator_hpp
#define CodeGenerator_CodeGenerator_hpp
#include "./Model/Model.hpp"
namespace isadt
{
    class CodeGenerator
    {
        protected:
            Model* model;
        public:
            Model* getModel() const;
            virtual void generateCode(std::string path);
    };
}


#endif