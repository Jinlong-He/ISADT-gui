#ifndef CodeGenerator_Plugin_hpp
#define CodeGenerator_Plugin_hpp

#include <iostream>
#include <vector>

namespace isadt{
    class Plugin {
        private: 
            std::string pluginName;
            std::string plugunLanguage;
            std::string pluginAlgorithmId;
        public: 
            std::string getPluginName();
            std::string getPluginLanguage();
            std::string getPluginAlgorithmId();
            Plugin();
            ~Plugin();
    };
}

#endif
