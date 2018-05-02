//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTIFSTMTNODE_H
#define MINILANG_COMPILER_ASTIFSTMTNODE_H


#include "ASTStatement_Node.h"
#include "ASTExpression_Node.h"

class ASTIfStmtNode : public ASTStatement_Node {
public:
    ASTExpression_Node *expression;
    ASTStatement_Node *ifBlock;
    ASTStatement_Node *elseBlock = nullptr; //optional

    ASTIfStmtNode(ASTExpression_Node *,ASTStatement_Node *);
    ASTIfStmtNode(ASTExpression_Node *, ASTStatement_Node *, ASTStatement_Node *);

    ~ASTIfStmtNode();

    virtual void accept(Visitor *v) override;
};


#endif //MINILANG_COMPILER_ASTIFSTMTNODE_H
