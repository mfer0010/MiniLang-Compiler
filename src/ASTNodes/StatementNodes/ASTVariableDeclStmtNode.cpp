//
// Created by marc on 25/04/2018.
//

#include "ASTVariableDeclStmtNode.h"


ASTVariableDeclStmtNode::ASTVariableDeclStmtNode(std::string identifier, std::string type, ASTExpression_Node * expression) {
    this->identifier = identifier;
    this->type = type;
    this->expression = expression;
}

ASTVariableDeclStmtNode::~ASTVariableDeclStmtNode(){
    delete expression;
}

void ASTVariableDeclStmtNode::accept(Visitor *v) {
    v->visit(this);
}