//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTINTEGERLITERALEXPRNODE_H
#define MINILANG_COMPILER_ASTINTEGERLITERALEXPRNODE_H


#include "ASTLiteralExprNode.h"

class ASTIntegerLiteralExprNode : public ASTLiteralExprNode {
public:
    int literalValue;

    ASTIntegerLiteralExprNode(int);

    ~ASTIntegerLiteralExprNode();

    virtual void accept(Visitor &v) override;
};


#endif //MINILANG_COMPILER_ASTINTEGERLITERALEXPRNODE_H
