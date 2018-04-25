//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTSubExpressionExprNode.h"

ASTSubExpressionExprNode::ASTSubExpressionExprNode(ASTExpression_Node *expression) {
    this->expression = expression;
}

ASTSubExpressionExprNode::~ASTSubExpressionExprNode() {
    delete expression;
}