//
//  InitialKnowledge.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_InitialKnowledge_hpp
#define Model_InitialKnowledge_hpp 
#include "../Process/Attribute.hpp"

namespace isadt {
    class Process;
    class InitialKnowledge {
    public:
        InitialKnowledge()
            : proc_(nullptr),
              attribute_(nullptr),
              pkKnowledge_(nullptr) {}
        InitialKnowledge(Process* proc, Attribute* attribute)
            : proc_(proc),
              attribute_(attribute),
              pkKnowledge_(nullptr) {}
        InitialKnowledge(Process* proc1, Attribute* attribute1,
                         Process* proc2, Attribute* attribute2)
            : proc_(proc1),
              attribute_(attribute1),
              pkKnowledge_(new InitialKnowledge(proc2, attribute2)) {}
        ~InitialKnowledge() {
            if (pkKnowledge_) {
                delete pkKnowledge_;
                pkKnowledge_ = nullptr;
            }
        }
        Process* getProc() {return this->proc_;}
        Attribute* getAttribute() {return this->attribute_;}
        InitialKnowledge* getPkKnowledge() {return this->pkKnowledge_;}
        bool isKeyPair();
    private:
        Process* proc_;
        Attribute* attribute_;
        InitialKnowledge* pkKnowledge_;
    };
}

#endif /* Model_InitialKnowledge_hpp */
