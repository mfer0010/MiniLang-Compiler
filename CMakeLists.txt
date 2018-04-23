cmake_minimum_required(VERSION 3.6)
project(MiniLang_Compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/include/Lexer.h src/Lexer.cpp src/include/Token.h src/Token.cpp src/Parser.cpp src/include/Parser.h src/include/ASTNodes/ASTNode.h src/include/ASTNodes/ASTStatement_Node.h src/include/ASTNodes/ASTExpression_Node.h src/ASTNode.cpp src/include/ASTNodes/ASTBinaryExprNode.h src/ASTBinaryExprNode.cpp src/ASTNumberExprNode.cpp src/include/ASTNodes/ASTNumberExprNode.h)
add_executable(MiniLang_Compiler ${SOURCE_FILES})