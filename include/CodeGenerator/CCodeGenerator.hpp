#ifndef CodeGenerator_CCodeGenerator_hpp
#define CodeGenerator_CCodeGenerator_hpp

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <list>
#include "ImpleCodeGenerator.hpp"
#include "./CodeGenerator/Plugin.hpp"
#include "./Model/Process/Process.hpp"
#include "./Model/Type/UserType.hpp"
namespace isadt 
{
    class CCodeGenerator : public ImpleCodeGenerator 
    {
    private:
        std::list<Plugin*> plugins;
    public: 
        void addPlugin(Plugin* plugin);
        Plugin* getFirstPlugin();
        Plugin* getPlugin(std::string algorithmId, std::string pluginLanguage);   
        void rmPlugin(std::string pluginName);
        std::list<Plugin*> getPlugins();
        // methods for generating header file 
        void generateHeaderFile(std::string path, Process* proc);
        std::string generateCommonIncludes();
        std::string generateCommunicationIncludes();
        std::string generateCryptoIncludes();
        std::string generateDependIncludes(Process* currentProc);
        std::string appendAttrDef(std::string inStr, Attribute* attr);
        std::string appendMethodDeclaration(std::string inStr, Method* method);
        std::string appendCommMethodDeclaration(std::string inStr, CommMethod* method);
        std::string generateHeaderIfDef(Process* proc);
        std::string generateClassPre(Process* proc);
        // methods for generating src file
        void generateSrcFile(std::string path, Process* proc);
        std::string generateStateDef(Process* proc);
        std::string generateSrcIncludes(Process* proc);
        std::string generateTempStorage(Process* proc);
        std::string generateSrcMethods(Process* proc);
        std::string generateMain(Process* proc);
        std::string generateInstObject(Process* proc);
        std::string generateGuardVarsDef(Process* proc);
        std::string generateSMLoop(Process* proc);
        std::string generateStateBehavior(StateMachine* sm);
        /*------------UserType------------*/
        void generateUserTypes(std::string path, Model* model);
        std::string generateSerializeBinding(Model* model);
        std::string generateTimer();
        /*------------Compile-------------*/
        void generateCompileFile(std::string path, Model* model);
        /*---------Gen---------*/
        void generateCodeProc(std::string path, Process* proc);
        void generateAll(std::string path, Model* model);
        void generateRefine(std::string path, Model* model);
        
        std::string generateDecrptAlgorithm()
        {
            
        }
        std::string generateEncrptAlgorithm()
        {
            
        }
        //constructors
        CCodeGenerator(/*args*/);
        ~CCodeGenerator();
    };
}


#endif
