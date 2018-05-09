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
    std::string _operator;
    ASTExpression_Node *LHS = nullptr;
    ASTExpression_Node *RHS = nullptr;

    ASTBinaryExprNode(std::string, ASTExpression_Node*, ASTExpression_Node*);

    virtual ~ASTBinaryExprNode();

    virtual void accept(Visitor *v) override;
};

#endif //MINILANG_COMPILER_ASTBINARYEXPRNODE_H
