//
// Created by marc on 23/04/2018.
//
#include "ASTBinaryExprNode.h"

ASTBinaryExprNode::ASTBinaryExprNode(std::string _operator, ASTExpression_Node *LHS, ASTExpression_Node *RHS) {
    this->_operator = _operator;
    this->LHS = LHS;
    this->RHS = RHS;
}

ASTBinaryExprNode::~ASTBinaryExprNode() {
    delete LHS;
    delete RHS;
}

void ASTBinaryExprNode::accept(Visitor *v) {
    v->visit(this);
}