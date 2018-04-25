//
// Created by marc on 23/04/2018.
//
#include "include/ASTNodes/ASTBinaryExprNode.h"

ASTBinaryExprNode::ASTBinaryExprNode(std::string _operator, ASTNumberExprNode *LHS, ASTNumberExprNode *RHS) {
    this->_opertor = _operator;
    this->LHS = LHS;
    this->RHS = RHS;
}

ASTBinaryExprNode::~ASTBinaryExprNode() {
    delete LHS;
    delete RHS;
}