
# CMake 最低版本号要求
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
# 项目工程名
PROJECT (isadt)
MESSAGE(STATUS "root This is SOURCE dir " ${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/Parser/XmlParser/
  ${PROJECT_SOURCE_DIR}/src/Parser/LParser/generated/
  ${PROJECT_SOURCE_DIR}/src/Parser/LParser/third_party/antlr4-cpp-runtime/src
  /usr/local/include
  /usr/include
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
SET (CMAKE_CXX_STANDARD 17)

# 添加子目录
ADD_SUBDIRECTORY(src)
