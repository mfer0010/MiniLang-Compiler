//
// Created by marc on 25/04/2018.
//

#include "ASTReturnStmtNode.h"

ASTReturnStmtNode::ASTReturnStmtNode(ASTExpression_Node *expression) {
    this->expression = expression;
}

ASTReturnStmtNode::~ASTReturnStmtNode(){
    delete expression;
}

void ASTReturnStmtNode::accept(Visitor *v) {
    v->visit(this);
}