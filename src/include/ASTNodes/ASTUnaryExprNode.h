//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTUNARYEXPRNODE_H
#define MINILANG_COMPILER_ASTUNARYEXPRNODE_H


#include "ASTExpression_Node.h"

class ASTUnaryExprNode : public ASTExpression_Node {
public:
    std::string prefix;
    ASTExpression_Node *expression;

    ASTUnaryExprNode(std::string, ASTExpression_Node *);

    ~ASTUnaryExprNode();

    virtual void accept(Visitor *v) override;
};


#endif //MINILANG_COMPILER_ASTUNARYEXPRNODE_H
