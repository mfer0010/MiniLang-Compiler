//
// Created by marc on 23/04/2018.
//
#include "include/ASTNodes/ASTNode.h"

ASTNode::ASTNode() {};

void ASTNode::addStatements(std::vector<ASTNode *> statements) {
    this->statements.insert(this->statements.end(),statements.begin(),statements.end());
}

void ASTNode::clearStatements() {
    this->statements.clear();
}

ASTNode::~ASTNode() {
    for (auto &statement : statements) {
        delete statement;
    }
}

void ASTNode::deleteStatement(ASTNode * statement) {
    delete statement;
}