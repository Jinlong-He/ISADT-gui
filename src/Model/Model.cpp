#include "Model/Model.hpp"
#include <iostream>
namespace isadt{
    UserType* Model::mkUserType(const string& name, 
                                UserType* base) {
        UserType* type = new UserType(name, base);
        userTypes_.push_back(type);
        userTypeMap_[name] = type;
        return type;
    }

    UserType* Model::getUserTypeByName(const string& name) {
        if (userTypeMap_.count(name) == 0) return mkUserType(name);
        return userTypeMap_[name];
    }

    void Model::addUserType(UserType* type) {
        userTypeMap_[type -> getName()] = type;
    }

    Channel* Model::mkChannel(Process* p1, CommMethod* cm1,
                              Process* p2, CommMethod* cm2, bool privacy) {
        auto channel = new Channel(p1, cm1, p2, cm2, privacy);
        channels_.push_back(channel);
        return channel;
    }

    //UserType* Model::getUserTypeById(const string& id) {
    //    return getUserTypeById(stoi(id));
    //}

    //UserType* Model::getUserTypeById(int id) {
    //    if (id == -1 || userTypes_.size() < id) return nullptr;
    //    return userTypes_[id - 1];
    //}

    Process* Model::mkProcess(const string& name) {
        Process* proc = new Process(name, this);
        procs_.push_back(proc);
        procMap_[name] = proc;
        return proc;
    }

    Process* Model::mkSystemProcess() {
        systemProc_ = new Process("_sys_", this);
        return systemProc_;
    }

    Process* Model::getProcByName(const string& name) {
        if (procMap_.count(name) == 0) return mkProcess(name);
        return procMap_[name];
    }

    ConfidentialProperty*
    Model::mkConfidentialProperty(Process* process, Attribute* attribute){
        ConfidentialProperty* prop = new ConfidentialProperty(process, attribute);
        props_.push_back(prop);
        return prop;
    }

    IntegratyProperty* 
    Model::mkIntegratyProperty(Process* process1, const string& vertex1, Attribute* attribute1,
                               Process* process2, const string& vertex2, Attribute* attribute2){
        IntegratyProperty* prop = new IntegratyProperty(process1, vertex1, attribute1,
                                                        process2, vertex2, attribute2);
        props_.push_back(prop);
        return prop;
    }

    AvailabilityProperty* 
    Model::mkAvailabilityProperty(Process* process, const string& vertex) {
        AvailabilityProperty* prop = new AvailabilityProperty(process, vertex);
        props_.push_back(prop);
        return prop;
    }

    InitialKnowledge* 
    Model::mkInitialKnowledge(Process* process, Attribute* attribute){
        InitialKnowledge* k = new InitialKnowledge(process, attribute);
        initialKnowledges_.push_back(k);
        return k;
    }

    InitialKnowledge* 
    Model::mkInitialKnowledge(Process* process1, Attribute* attribute1,
                              Process* process2, Attribute* attribute2) {
        InitialKnowledge* k = new InitialKnowledge(process1, attribute1,
                                                   process2, attribute2);
        initialKnowledges_.push_back(k);
        return k;
    }
    
    const vector<Process*>& Model::getProcesses() const{
        return procs_;
    }

    const list<UserType*>& Model::getUserTypes() const {
        return userTypes_;
    }

    bool Model::hasUserType(const string& name) {
        return userTypeMap_.count(name);
    }


    bool Model::isChannelPair(Process* proc1, Edge* edge1, Process* proc2, Edge* edge2) {
        if (edge1 -> getActions().size() > 1) return false;
        if (edge2 -> getActions().size() > 1) return false;
        auto action1 = edge1 -> getActions().front();
        auto action2 = edge2 -> getActions().front();
        if (!action1 -> isAssignmentAction() || !action2 -> isAssignmentAction()) return false;
        if (action1 -> getRhs() || action2 -> getRhs()) return false;
        if (action1 -> getLhs() -> getTermType() != MT || action2 -> getLhs() -> getTermType() != MT) return false;
        auto methodTerm1 = (MethodTerm*) action1 -> getLhs();
        auto methodTerm2 = (MethodTerm*) action2 -> getLhs();
        for (auto channel : channels_) {
            if (channel -> equal(proc1, methodTerm1 -> getMethod(),
                                 proc2, methodTerm2 -> getMethod())) return true;
        }
        return false;
    }

    struct hash_pair {
        template <class T1, class T2> 
        size_t operator()(const std::pair<T1, T2>& p) const {
            return ((size_t)p.first ^ (size_t)p.second);
        }
    };

    struct hash_vec {
        template <class T1> 
        size_t operator()(const std::vector<T1>& v) const {
            size_t seed = 0; 
            for (const auto& t : v) {
                seed ^= (size_t)(t) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            }
            return seed;
        }
    };

    void compositeEdge(Edge* newEdge, const vector<Edge*>& edges) {
        Expression* exp = nullptr;
        for (auto edge : edges) {
            if (exp == nullptr) {
                exp = (Expression*) (newEdge -> cpTerm(edge -> getGuard() -> getExpression()));
            }
            if (edge -> getGuard()) {
                newEdge -> cpTerm(edge -> getGuard() -> getExpression());
            }
        }
    }

    void Model::mkCommProductEdge(Vertex* source, Vertex* target, const vector<Edge*>& edges) {
        vector<MethodBase*> methods;
        size_t ii = 0, jj = 0, count = 0;
        bool flag = false;
        for (size_t i = 0; i < edges.size(); i++) {
            auto edge = edges[i];
            const auto& actions = edge -> getActions();
            auto action = actions.front();
            if (actions.size() == 1 && action -> isAssignmentAction() &&
               !(action -> getRhs()) && action -> getLhs() -> getTermType() == MT) {
                auto method = ((MethodTerm*) action -> getLhs()) -> getMethod();
                if (method -> isCommMethod()) {
                    count++;
                    for (auto channel : channels_) {
                        for (size_t j = 0; j < methods.size(); j++) {
                            if (channel -> equal(procs_[i], method,
                                                 procs_[j], methods[j])) {
                                flag = true;
                                ii = i;
                                jj = j;
                            }
                        }
                    }
                    methods.push_back(method);
                } else {
                    methods.push_back(nullptr);
                }
            } else {
                methods.push_back(nullptr);
            }
        }
        auto sm = systemProc_ -> getStateMachines().front();
        if (count == 0) {
            auto e = sm -> mkEdge(source, target);
        }
        if (flag && count == 2 && methods[ii] && methods[jj]) {
            auto e = sm -> mkEdge(source, target);
        }
    }

    void Model::mkCommProductEdge(const vector<Vertex*>& source_vertices, 
                                  const vector<Vertex*>& target_vertices,
                                  Vertex* s, Vertex* t) {
        vector<Edge*> edges;
        vector<vector<Edge*> > edgesVec({vector<Edge*>()}), newEdgesVec;
        for (size_t i = 0; i < source_vertices.size(); i++) {
            auto source = source_vertices[i];
            auto target = target_vertices[i];
            newEdgesVec.clear();
            for (const auto& edges: edgesVec) {
                for (auto edge : source -> getNexts()) {
                    if (edge -> getToVertex() == target) {
                        vector<Edge*> newEdges = edges;
                        newEdges.push_back(edge);
                        newEdgesVec.push_back(newEdges);
                    }
                }
            }
            if (newEdgesVec.size() == 0) return;
            edgesVec.clear();
            edgesVec = newEdgesVec;
        }
        for (const auto& edges : edgesVec) {
            mkCommProductEdge(s, t, edges);
        }
    }

    StateMachine* Model::mkCommProductStateMahine() {
        vector<StateMachine*> sms;
        for (auto proc : procs_) {
            sms.push_back(proc -> getStateMachine());
        }
        auto res = systemProc_ -> mkStateMachine();
        unordered_map<std::vector<Vertex*>, Vertex*, hash_vec> vertexMap;
        vector<vector<Vertex*> > verticesVec({vector<Vertex*>()}), newVerticesVec;
        for (auto sm : sms) {
            newVerticesVec.clear();
            for (auto vertex : sm -> getVertices()) {
                sm -> mkEdge(vertex, vertex);
                for (const auto& vertices : verticesVec) {
                    std::vector<Vertex*> v = vertices;
                    v.push_back(vertex);
                    newVerticesVec.push_back(v);
                }
            }
            verticesVec.clear();
            verticesVec = newVerticesVec;
        }
        for (const auto& vertices : verticesVec) {
            string name = "_sys_";
            for (auto vertex : vertices) {
                name += vertex -> getName() + "_";
            }
            vertexMap[vertices] = res -> mkVertex(name);
        }
        for (const auto& source_vertices : verticesVec) {
            auto source = vertexMap.at(source_vertices);
            for (const auto& target_vertices : verticesVec) {
                auto target = vertexMap.at(target_vertices);
                mkCommProductEdge(source_vertices, target_vertices, source, target);
            }
        }
        return res;
    }
}
