//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTFUNCDECLSTMTNODE_H
#define MINILANG_COMPILER_ASTFUNCDECLSTMTNODE_H


#include "ASTStatement_Node.h"
#include "ASTFormalParamStmtNode.h"

class ASTFuncDeclStmtNode : public ASTStatement_Node{
public:
    std::string identifier;
    std::vector<ASTFormalParamStmtNode *> formalParams;
    std::string type;
    ASTStatement_Node *block;

    ASTFuncDeclStmtNode(std::string, std::vector<ASTFormalParamStmtNode *>, std::string, ASTStatement_Node *);

    ~ASTFuncDeclStmtNode();
};


#endif //MINILANG_COMPILER_ASTFUNCDECLSTMTNODE_H
