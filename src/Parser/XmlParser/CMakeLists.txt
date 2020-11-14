MESSAGE(STATUS "XmlParser This is SOURCE dir " ${PROJECT_SOURCE_DIR})
ADD_LIBRARY(XmlParser tinyxml2.cpp XmlParser.cpp)
