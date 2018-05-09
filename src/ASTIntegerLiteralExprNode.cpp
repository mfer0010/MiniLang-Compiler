//
// Created by marc on 25/04/2018.
//

#include "include/ASTIntegerLiteralExprNode.h"

ASTIntegerLiteralExprNode::ASTIntegerLiteralExprNode(int value) {
    this->literalValue = value;
}

ASTIntegerLiteralExprNode::~ASTIntegerLiteralExprNode() {}

void ASTIntegerLiteralExprNode::accept(Visitor *v) {
    v->visit(this);
}