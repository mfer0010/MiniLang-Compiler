//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTSUBEXPRESSIONEXPRNODE_H
#define MINILANG_COMPILER_ASTSUBEXPRESSIONEXPRNODE_H


#include "ASTExpression_Node.h"

class ASTSubExpressionExprNode : public ASTExpression_Node {
public:
    ASTExpression_Node *expression;

    ASTSubExpressionExprNode(ASTExpression_Node *);

    ~ASTSubExpressionExprNode();

    virtual void accept(Visitor &v) override;
};


#endif //MINILANG_COMPILER_ASTSUBEXPRESSIONEXPRNODE_H
