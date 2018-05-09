//
// Created by marc on 25/04/2018.
//

#include "include/ASTWhileStmtNode.h"

ASTWhileStmtNode::ASTWhileStmtNode(ASTExpression_Node *expression, ASTStatement_Node *block) {
    this->expression = expression;
    this->block = block;
}

ASTWhileStmtNode::~ASTWhileStmtNode() {
    delete expression;
    delete block;
}

void ASTWhileStmtNode::accept(Visitor *v) {
    v->visit(this);
}