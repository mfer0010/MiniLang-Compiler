//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTWHILESTMTNODE_H
#define MINILANG_COMPILER_ASTWHILESTMTNODE_H


#include "ASTStatement_Node.h"
#include "ASTExpression_Node.h"

class ASTWhileStmtNode : public ASTStatement_Node{
public:
    ASTExpression_Node *expression;
    ASTStatement_Node *block;

    ASTWhileStmtNode(ASTExpression_Node *, ASTStatement_Node *);

    ~ASTWhileStmtNode();
};


#endif //MINILANG_COMPILER_ASTWHILESTMTNODE_H
