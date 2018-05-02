//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTRealLiteralExprNode.h"

ASTRealLiteralExprNode::ASTRealLiteralExprNode(double value) {
    this->literalValue = value;
}

ASTRealLiteralExprNode::~ASTRealLiteralExprNode() {}

void ASTRealLiteralExprNode::accept(Visitor &v) {
    v.visit(this);
}