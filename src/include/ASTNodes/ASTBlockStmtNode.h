//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTBLOCKSTMTNODE_H
#define MINILANG_COMPILER_ASTBLOCKSTMTNODE_H


#include "ASTStatement_Node.h"

class ASTBlockStmtNode : public ASTStatement_Node {
public:
    std::vector<ASTStatement_Node *> statements;

    ASTBlockStmtNode(std::vector<ASTStatement_Node *>);

    ~ASTBlockStmtNode();

    virtual void accept(Visitor &v) override;
};


#endif //MINILANG_COMPILER_ASTBLOCKSTMTNODE_H
