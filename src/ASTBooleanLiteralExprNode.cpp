//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTBooleanLiteralExprNode.h"

ASTBooleanLiteralExprNode::ASTBooleanLiteralExprNode(bool value) {
    this->literalValue = value;
}

ASTBooleanLiteralExprNode::~ASTBooleanLiteralExprNode() {}

void ASTBooleanLiteralExprNode::accept(Visitor &v) {
    v.visit(this);
}