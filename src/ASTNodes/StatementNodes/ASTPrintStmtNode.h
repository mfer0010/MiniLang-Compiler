//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTPRINTSTMTNODE_H
#define MINILANG_COMPILER_ASTPRINTSTMTNODE_H


#include "ASTStatement_Node.h"
#include "../ExpressionNodes/ASTExpression_Node.h"

class ASTPrintStmtNode : public ASTStatement_Node{
public:
    ASTExpression_Node *expression;

    ASTPrintStmtNode(ASTExpression_Node *);

    ~ASTPrintStmtNode();

    virtual void accept(Visitor *v) override;
};


#endif //MINILANG_COMPILER_ASTPRINTSTMTNODE_H
