//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTIfStmtNode.h"

ASTIfStmtNode::ASTIfStmtNode(ASTExpression_Node * expression, ASTStatement_Node * block) {
    this->expression = expression;
    this->ifBlock = block;
}

ASTIfStmtNode::ASTIfStmtNode(ASTExpression_Node *expression, ASTStatement_Node *ifBlock, ASTStatement_Node *elseBlock) {
    this->expression = expression;
    this->ifBlock = ifBlock;
    this->elseBlock = elseBlock;
}

ASTIfStmtNode::~ASTIfStmtNode() {
    delete expression;
    delete ifBlock;
    delete elseBlock;
}

void ASTIfStmtNode::accept(Visitor *v) {
    v->visit(this);
}