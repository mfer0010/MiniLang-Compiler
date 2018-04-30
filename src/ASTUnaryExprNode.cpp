//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTUnaryExprNode.h"

ASTUnaryExprNode::ASTUnaryExprNode(std::string prefix, ASTExpression_Node * expression) {
    this->prefix = prefix;
    this->expression = expression;
}

ASTUnaryExprNode::~ASTUnaryExprNode() {
    delete expression;
}