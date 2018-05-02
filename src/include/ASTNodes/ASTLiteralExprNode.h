//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTLITERALEXPRNODE_H
#define MINILANG_COMPILER_ASTLITERALEXPRNODE_H


#include "ASTExpression_Node.h"

class ASTLiteralExprNode : public ASTExpression_Node {
    //pure virtual class that will be inherited by all types of literal nodes
public:
    virtual ~ASTLiteralExprNode() {};

    virtual void accept(Visitor &v) = 0;
};


#endif //MINILANG_COMPILER_ASTLITERALEXPRNODE_H
