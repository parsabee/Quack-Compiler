cmake_minimum_required(VERSION 3.15)
project(Qucak_Compiler)

set(CMAKE_CXX_STANDARD 14)

find_package(BISON 3.4.2)
find_package(FLEX 2.6.4)

BISON_TARGET(MyParser src/qk.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(MyScanner src/qk.lpp  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(./src/)

file(GLOB qkc_SRC "src/*.hpp" "src/*.cpp")

add_executable(
        qkc
        ${qkc_SRC}
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)