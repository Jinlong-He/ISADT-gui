//
//  Process.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Process_hpp
#define Model_Process_hpp
#include <unordered_set>
#include <iostream>
#include "../Struct/Class.hpp"
#include "CommMethod.hpp"
#include "../StateMachine/StateMachine.hpp"
#include "../../Manage.hpp"
using std::unordered_set;

namespace isadt {
    class Model;
    /// \brief the process of model.
    class Process : public Class {
    public:
        Process()
            : stateMachine_(nullptr),
              model_(nullptr) {}

        Process(const string& name, Model* model = nullptr) 
            : Class(name),
              stateMachine_(nullptr),
              model_(model) {}

        ~Process() {
            for (auto commMethod : commMethods_) {
                delete commMethod;
                commMethod = nullptr;
            }

            for (auto stateMachine : stateMachines_) {
                if (stateMachine) {
                    delete stateMachine;
                    stateMachine = nullptr;
                }
            }
        }

        Model* getModel() const;
        void setModel(Model* model);
        
        StateMachine* mkStateMachine(Vertex* parent = nullptr);

        const list<CommMethod*>& getCommMethods() const;
        StateMachine* getStateMachine() const;
        const list<StateMachine*> getStateMachines() const;

        void setOriginalAttributes();
        const list<Attribute*> getOriginalAttributes() const;

        Attribute* mkNewAttribute(UserType* type, const string& name);
        
        CommMethod* mkCommMethod(const string& name, UserType* returnType,
                                 bool inout, const string& commId);
        CommMethod* mkCommMethod(const string& name);
        CommMethod* getCommMethodByName(const string& name);
        bool hasCommMethod(const string& name);

        void addVertex(Vertex* vertex);
        Vertex* getVertexByName(const string& name);

        Term* cpBeagleTerm(Term* term, Edge* edge1, Edge* edge2);
        StateMachine* mkBeagleStateMachine(StateMachine* sm);
        StateMachine* mkCompositeStateMachine();
        unordered_map<string, Vertex*> getVertexMap() {return this->vertexMap;};
    private:
        list<Attribute*> original_attributes_;
        list<CommMethod*> commMethods_;      ///< the communication methods for this process.
        list<StateMachine*> stateMachines_;  ///< the finite state machines for this process.
        //TODO map (state,sm) to sm
        unordered_map<string, StateMachine*> stateMachineMap;
        unordered_map<string, CommMethod*> commMethodMap;
        unordered_map<string, Vertex*> vertexMap;
        StateMachine* stateMachine_;
        Model* model_;                       ///< the model this process from.
    };
}

#endif /* Model_Process_hpp */
