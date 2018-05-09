//
// Created by marc on 23/04/2018.
//

#include "include/ASTNumberExprNode.h"

ASTNumberExprNode::ASTNumberExprNode(double value, std::string type) {
    this->value = value;
    this->type = type;
}

ASTNumberExprNode::~ASTNumberExprNode() {}

void ASTNumberExprNode::accept(Visitor *v) {
    v->visit(this);
}