//
// Created by marc on 25/04/2018.
//

#include "ASTSubExpressionExprNode.h"

ASTSubExpressionExprNode::ASTSubExpressionExprNode(ASTExpression_Node *expression) {
    this->expression = expression;
}

ASTSubExpressionExprNode::~ASTSubExpressionExprNode() {
    delete expression;
}

void ASTSubExpressionExprNode::accept(Visitor *v) {
    v->visit(this);
}