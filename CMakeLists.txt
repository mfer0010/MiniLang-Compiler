cmake_minimum_required(VERSION 3.6)
project(MiniLang_Compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/include/Lexer.h src/class/Lexer.cpp)
add_executable(MiniLang_Compiler ${SOURCE_FILES})