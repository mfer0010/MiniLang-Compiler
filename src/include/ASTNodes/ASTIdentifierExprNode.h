//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTIDENTIFIEREXPRNODE_H
#define MINILANG_COMPILER_ASTIDENTIFIEREXPRNODE_H


#include "ASTExpression_Node.h"

class ASTIdentifierExprNode : public ASTExpression_Node {
public:
    std::string identifier;

    ASTIdentifierExprNode(std::string);

    ~ASTIdentifierExprNode();
};


#endif //MINILANG_COMPILER_ASTIDENTIFIEREXPRNODE_H
