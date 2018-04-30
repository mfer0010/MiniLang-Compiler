//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTREALLITERALEXPRNODE_H
#define MINILANG_COMPILER_ASTREALLITERALEXPRNODE_H


#include "ASTLiteralExprNode.h"

class ASTRealLiteralExprNode : public ASTLiteralExprNode {
public:
    double literalValue;

    ASTRealLiteralExprNode(double);

    ~ASTRealLiteralExprNode();
};


#endif //MINILANG_COMPILER_ASTREALLITERALEXPRNODE_H
