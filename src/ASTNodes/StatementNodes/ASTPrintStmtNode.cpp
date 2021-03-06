//
// Created by marc on 25/04/2018.
//

#include "ASTPrintStmtNode.h"

ASTPrintStmtNode::ASTPrintStmtNode(ASTExpression_Node *expression) {
    this->expression = expression;
}

ASTPrintStmtNode::~ASTPrintStmtNode(){
    delete expression;
}

void ASTPrintStmtNode::accept(Visitor *v) {
    v->visit(this);
}