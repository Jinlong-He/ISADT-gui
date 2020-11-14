MESSAGE(STATUS "StateMachine This is SOURCE dir " ${PROJECT_SOURCE_DIR})

ADD_SUBDIRECTORY(Action)
ADD_SUBDIRECTORY(Guard)
ADD_SUBDIRECTORY(Term)
ADD_LIBRARY(StateMachine StateMachine.cpp Expression.cpp Edge.cpp)
TARGET_LINK_LIBRARIES(StateMachine Action Guard Term)
