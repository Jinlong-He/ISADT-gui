MESSAGE(STATUS "LParser This is SOURCE dir " ${PROJECT_SOURCE_DIR})
SET(src_dir
    generated/tinycLexer.cpp
    generated/tinycParser.cpp
    generated/tinycVisitor.cpp
    generated/tinycBaseVisitor.cpp
 )
FILE(GLOB antlr4-cpp-src
    third_party/antlr4-cpp-runtime/src/*.cpp
    third_party/antlr4-cpp-runtime/src/atn/*.cpp
    third_party/antlr4-cpp-runtime/src/dfa/*.cpp
    third_party/antlr4-cpp-runtime/src/misc/*.cpp
    third_party/antlr4-cpp-runtime/src/support/*.cpp
    third_party/antlr4-cpp-runtime/src/tree/*.cpp
    third_party/antlr4-cpp-runtime/src/tree/pattern/*.cpp
    third_party/antlr4-cpp-runtime/src/tree/xpath/*.cpp
)
ADD_LIBRARY (LParser LParser.cpp ${src_dir} ${antlr4-cpp-src})
TARGET_LINK_LIBRARIES (LParser Model)
