//
// Created by marc on 23/04/2018.
//

#include "include/ASTNodes/ASTNumberExprNode.h"

ASTNumberExprNode::ASTNumberExprNode(float value, std::string type) {
    this->value = value;
    this->type = type;
}

ASTNumberExprNode::~ASTNumberExprNode() {}