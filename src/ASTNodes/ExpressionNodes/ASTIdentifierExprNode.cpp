//
// Created by marc on 25/04/2018.
//

#include "ASTIdentifierExprNode.h"

ASTIdentifierExprNode::ASTIdentifierExprNode(std::string identifier) {
    this->identifier = identifier;
}

ASTIdentifierExprNode::~ASTIdentifierExprNode() {}

void ASTIdentifierExprNode::accept(Visitor *v) {
    v->visit(this);
}