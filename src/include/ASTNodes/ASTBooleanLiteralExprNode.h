//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTBOOLEANLITERALEXPRNODE_H
#define MINILANG_COMPILER_ASTBOOLEANLITERALEXPRNODE_H


#include "ASTLiteralExprNode.h"

class ASTBooleanLiteralExprNode : public ASTLiteralExprNode{
public:
    bool literalValue;

    ASTBooleanLiteralExprNode(bool);

    ~ASTBooleanLiteralExprNode();

    virtual void accept(Visitor *v) override;
};


#endif //MINILANG_COMPILER_ASTBOOLEANLITERALEXPRNODE_H
