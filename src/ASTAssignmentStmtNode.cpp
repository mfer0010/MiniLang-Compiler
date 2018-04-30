//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTAssignmentStmtNode.h"

ASTAssignmentStmtNode::ASTAssignmentStmtNode(std::string identifier, ASTExpression_Node * expression) {
    this->identifier = identifier;
    this->expression = expression;
}

ASTAssignmentStmtNode::~ASTAssignmentStmtNode() {
    delete expression;
}