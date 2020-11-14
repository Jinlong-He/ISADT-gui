#ifndef CodeGenerator_ImpleCodeGenerator_hpp
#define CodeGenerator_ImpleCodeGenerator_hpp
#include "CodeGenerator.hpp"
namespace isadt 
{
    class ImpleCodeGenerator : public CodeGenerator
    {
        private:

        public:
            ImpleCodeGenerator(/*args*/);
            ~ImpleCodeGenerator();
            virtual std::string generateDecrptAlgorithm() = 0;
            virtual std::string generateEncrptAlgorithm() = 0;
    };
}

#endif