//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTRETURNSTMTNODE_H
#define MINILANG_COMPILER_ASTRETURNSTMTNODE_H


#include "ASTStatement_Node.h"
#include "ASTExpression_Node.h"

class ASTReturnStmtNode : public ASTStatement_Node{
public:
    ASTExpression_Node *expression;

    ASTReturnStmtNode(ASTExpression_Node *);

    ~ASTReturnStmtNode();

    virtual void accept(Visitor *v) override;
};


#endif //MINILANG_COMPILER_ASTRETURNSTMTNODE_H
