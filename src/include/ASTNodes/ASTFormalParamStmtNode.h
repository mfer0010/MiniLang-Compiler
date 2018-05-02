//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTFORMALPARAMSTMTNODE_H
#define MINILANG_COMPILER_ASTFORMALPARAMSTMTNODE_H


#include "ASTStatement_Node.h"

class ASTFormalParamStmtNode : public ASTStatement_Node {
public:
    std::string identifier;
    std::string type;

    ASTFormalParamStmtNode(std::string, std::string);

    ~ASTFormalParamStmtNode();

    virtual void accept(Visitor &v) override;
};


#endif //MINILANG_COMPILER_ASTFORMALPARAMSTMTNODE_H
