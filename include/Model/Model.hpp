//
//  Model.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Model_hpp
#define Model_Model_hpp 
#include <vector>
#include <iostream>
#include "Type/UserType.hpp"
#include "Process/Process.hpp"
#include "Pragma/Property.hpp"
#include "Pragma/InitialKnowledge.hpp"
#include "SequenceDiagram/SequenceDiagram.hpp"
#include "Pragma/Axiom.hpp"
#include "Channel/Channel.hpp"
using std::vector;
namespace isadt {
    /// \brief the model in isadt.
    class Model {
    public:
        Model() {
            mkSystemProcess();
        }

        ~Model() {
            delete systemProc_;
            systemProc_ = nullptr;

            for (auto proc : procs_) {
                if (proc) {
                    delete proc;
                    proc = nullptr;
                }
            }
            for (auto ik : initialKnowledges_) {
                delete ik;
                ik = nullptr;
            }
            for (auto ut : userTypes_) {
                delete ut;
                ut = nullptr;
            }
            for (auto axiom : axioms_) {
                delete axiom;
                axiom = nullptr;
            }
            for (auto channel : channels_) {
                delete channel;
                channel = nullptr;
            }
        }

        UserType* mkUserType(const string& name, 
                             UserType* base = nullptr);

        UserType* mkUserType(const string& name, 
                             const std::initializer_list<Attribute*>& parameters, 
                             UserType* base = nullptr);

        Channel* mkChannel(Process* p1, CommMethod* cm1,
                           Process* p2, CommMethod* cm2, bool privacy);

        void addUserType(UserType* type);

        Process* mkProcess(const string& procName);
        Process* mkSystemProcess();

        SafetyProperty*
        mkSafetyProperty(const string& str) {
            SafetyProperty* prop = new SafetyProperty(str);
            props_.push_back(prop);
            return prop;
        }

        ConfidentialProperty*
        mkConfidentialProperty(Process* process, Attribute* attribute);

        IntegratyProperty* 
        mkIntegratyProperty(Process* process1, const string& vertex1, Attribute* attribute1,
                            Process* process2, const string& vertex2, Attribute* attribute2);

        AvailabilityProperty* 
        mkAvailabilityProperty(Process* process, const string& vertex);

        InitialKnowledge* 
        mkInitialKnowledge(Process* process, Attribute* attribute);

        InitialKnowledge* 
        mkInitialKnowledge(Process* process1, Attribute* attribute1,
                          Process* process2, Attribute* attribute2);
        
        const vector<Process*>& getProcesses() const;
        const list<UserType*>& getUserTypes() const;

        UserType* getUserTypeByName(const string& name);
        Process* getProcByName(const string& name);
        bool hasUserType(const string& name);
        bool isChannelPair(Process* proc1, Edge* edge1, Process* proc2, Edge* edge2);
        StateMachine* mkCommProductStateMahine();
        void mkCommProductEdge(const vector<Vertex*>& source_vertices, 
                               const vector<Vertex*>& target_vertices,
                               Vertex* s, Vertex* t);
        void mkCommProductEdge(Vertex* source, Vertex* target, const vector<Edge*>& edge);
        list<Property*> getProps() { return this->props_;};
        list<InitialKnowledge*> getInitialKnowledges() {return this->initialKnowledges_;}
    private:
        vector<Process*> procs_;
        list<Property*> props_;
        list<InitialKnowledge*> initialKnowledges_;
        list<UserType*> userTypes_;
        list<Axiom*> axioms_;
        list<Channel*> channels_;
        std::unordered_map<string, UserType*> userTypeMap_;
        std::unordered_map<string, Process*> procMap_;
        Process* systemProc_;
        //list<SequenceDiagram*> sd_;
        // ProcMethodPair * 2, bool privacy

    };
}

#endif /* Model_Model_hpp */
