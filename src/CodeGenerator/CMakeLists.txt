MESSAGE(STATUS "CodeGenerator This is SOURCE dir " ${PROJECT_SOURCE_DIR})


ADD_LIBRARY(CodeGenerator CCodeGenerator.cpp CPPCodeGenerator.cpp JavaCodeGenerator.cpp CodeGenerator.cpp ImpleCodeGenerator.cpp Plugin.cpp)