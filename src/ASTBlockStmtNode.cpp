//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTBlockStmtNode.h"

ASTBlockStmtNode::ASTBlockStmtNode(std::vector<ASTStatement_Node *> statements) {
    this->statements = statements;
}

ASTBlockStmtNode::~ASTBlockStmtNode() {
    for (auto &statement: statements) {
        delete statement;
    }
}