//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTReturnStmtNode.h"

ASTReturnStmtNode::ASTReturnStmtNode(ASTExpression_Node *expression) {
    this->expression = expression;
}

ASTReturnStmtNode::~ASTReturnStmtNode(){
    delete expression;
}