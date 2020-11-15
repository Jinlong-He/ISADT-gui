MESSAGE(STATUS "src This is SOURCE dir " ${PROJECT_SOURCE_DIR})

ADD_SUBDIRECTORY(Model)
ADD_SUBDIRECTORY(Parser)
ADD_SUBDIRECTORY(CodeGenerator)

ADD_EXECUTABLE(isadt main.cpp Verifier/ProverifTranslator.cpp ../include/Verifier/ProverifTranslator.hpp Verifier/mkInitialKnowledge.cpp ../include/Verifier/mkInitialKnowledge.hpp ../include/Verifier/mkProcesses.hpp Verifier/mkProcesses.cpp ../include/Verifier/mkProcess.hpp Verifier/mkProcess.cpp ../include/Verifier/BeagleTranslator.hpp Verifier/BeagleTranslator.cpp)
#ADD_EXECUTABLE(isadt main_verify.cpp)
TARGET_LINK_LIBRARIES(isadt Model CodeGenerator Parser)
