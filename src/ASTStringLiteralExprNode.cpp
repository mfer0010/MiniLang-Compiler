//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTStringLiteralExprNode.h"

ASTStringLiteralExprNode::ASTStringLiteralExprNode(std::string value) {
    this->literalValue = value;
}

ASTStringLiteralExprNode::~ASTStringLiteralExprNode() {}

void ASTStringLiteralExprNode::accept(Visitor *v) {
    v->visit(this);
}