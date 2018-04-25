//
// Created by marc on 23/04/2018.
//

#ifndef MINILANG_COMPILER_ASTBINARYEXPRNODE_H
#define MINILANG_COMPILER_ASTBINARYEXPRNODE_H

#include "ASTExpression_Node.h"
#include "ASTNumberExprNode.h"
#include <string>

class ASTBinaryExprNode : public ASTExpression_Node {
public:
    std::string _opertor;
    ASTNumberExprNode *LHS = nullptr;
    ASTNumberExprNode *RHS = nullptr;

    ASTBinaryExprNode(std::string, ASTNumberExprNode*, ASTNumberExprNode*);

    virtual ~ASTBinaryExprNode();
};

#endif //MINILANG_COMPILER_ASTBINARYEXPRNODE_H
