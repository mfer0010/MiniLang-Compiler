//
// Created by marc on 03/05/2018.
//

#ifndef MINILANG_COMPILER_SCOPE_H
#define MINILANG_COMPILER_SCOPE_H


#include <map>
#include "VariableDetails.h"

class Scope {
private:
    //this will contain all the identifiers in the scope
    //to ensure there will be no duplicates
    std::map<std::string, VariableDetails *> identifiers;

public:
    void addToScope(std::string identifier);

    void addToScope(ASTFuncDeclStmtNode *function);

    void addToScope(ASTFormalParamStmtNode *formalParam);

    void addToScope(ASTVariableDeclStmtNode *variable);

    void removeFromScope(std::string identifier);

    bool inScope(std::string identifier);

    std::string returnType(std::string identifier);

    std::vector<ASTFormalParamStmtNode *> * returnParams(std::string identifier);

    ~Scope();
};


#endif //MINILANG_COMPILER_SCOPE_H
