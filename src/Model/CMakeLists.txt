MESSAGE(STATUS "Model This is SOURCE dir " ${PROJECT_SOURCE_DIR})
SET(proc_dir
    Process/Attribute.cpp
    Process/CommMethod.cpp
    Process/Method.cpp
    Process/MethodBase.cpp
    Process/Process.cpp)
SET(sm_dir
    StateMachine/Action/Action.cpp
    StateMachine/Guard/Guard.cpp
    StateMachine/Term/AttributeTerm.cpp
    StateMachine/Term/ConstTerm.cpp
    StateMachine/Term/ListTerm.cpp
    StateMachine/Term/MethodTerm.cpp
    StateMachine/Edge.cpp
    StateMachine/Expression.cpp
    StateMachine/StateMachine.cpp)
SET(struct_dir
    Struct/Struct.cpp
    Struct/Class.cpp)
SET(type_dir
    Type/UserType.cpp)

ADD_LIBRARY(Model Model.cpp ${proc_dir} ${sm_dir} ${struct_dir} ${type_dir})
    
