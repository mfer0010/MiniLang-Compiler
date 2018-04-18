cmake_minimum_required(VERSION 3.6)
project(MiniLang_Compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/include/Lexer.h src/Lexer.cpp src/include/Token.h src/Token.cpp src/include/Exceptions/FileNotFound.h src/FileNotFound.cpp)
add_executable(MiniLang_Compiler ${SOURCE_FILES})