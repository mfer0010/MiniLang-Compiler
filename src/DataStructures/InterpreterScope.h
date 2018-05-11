//
// Created by marc on 11/05/2018.
//

#ifndef MINILANG_COMPILER_INTERPRETERSCOPE_H
#define MINILANG_COMPILER_INTERPRETERSCOPE_H

#include<map>
#include "Evaluation.h"
#include "../ASTNodes/StatementNodes/ASTFuncDeclStmtNode.h"

class InterpreterScope {
private:
    /*
     * Two maps in this scope:
     * -> 1 for functions
     * -> 1 for other variables
     * These will be used to store the values corresponding to each identifier
     */
    std::map<std::string, Evaluation *> variables;
    std::map<std::string, ASTFuncDeclStmtNode *> functions;

public:
    //constructor & Destructor
    InterpreterScope();
    ~InterpreterScope();

    //add to scope
    void addToScope(std::string identifier, Evaluation * evaluation);
    void addToScope(std::string identifier, ASTFuncDeclStmtNode * function);

    //return value from scope
    Evaluation * returnVariable(std::string identifier);
    ASTFuncDeclStmtNode * returnFunction(std::string identifier);
};


#endif //MINILANG_COMPILER_INTERPRETERSCOPE_H
