//
// Created by marc on 23/04/2018.
//
#include "ASTNode.h"

ASTNode::ASTNode() {};

void ASTNode::addStatements(std::vector<ASTStatement_Node *> statements) {
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

void ASTNode::deleteStatement(ASTStatement_Node * statement) {
    delete statement;
}

void ASTNode::accept(Visitor *v) {
    v->visit(this);
}