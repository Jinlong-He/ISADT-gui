message(STATUS "Parser This is SOURCE dir " ${PROJECT_SOURCE_DIR})
SET(tinyc_dir
    LParser/generated/tinycLexer.cpp
    LParser/generated/tinycParser.cpp
    LParser/generated/tinycVisitor.cpp
    LParser/generated/tinycBaseVisitor.cpp
 )
SET(xml_dir
    XmlParser/tinyxml2.cpp
    XmlParser/XmlParser.cpp
 )
FILE(GLOB antlr4-cpp-src
    LParser/third_party/antlr4-cpp-runtime/src/*.cpp
    LParser/third_party/antlr4-cpp-runtime/src/atn/*.cpp
    LParser/third_party/antlr4-cpp-runtime/src/dfa/*.cpp
    LParser/third_party/antlr4-cpp-runtime/src/misc/*.cpp
    LParser/third_party/antlr4-cpp-runtime/src/support/*.cpp
    LParser/third_party/antlr4-cpp-runtime/src/tree/*.cpp
    LParser/third_party/antlr4-cpp-runtime/src/tree/pattern/*.cpp
    LParser/third_party/antlr4-cpp-runtime/src/tree/xpath/*.cpp
)
ADD_LIBRARY (Parser LParser/LParser.cpp ${tinyc_dir} ${antlr4-cpp-src} ${xml_dir})
TARGET_LINK_LIBRARIES(Parser Model)
