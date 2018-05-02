//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTFormalParamStmtNode.h"

ASTFormalParamStmtNode::ASTFormalParamStmtNode(std::string identifier, std::string type) {
    this->identifier = identifier;
    this->type = type;
}

ASTFormalParamStmtNode::~ASTFormalParamStmtNode() {}

void ASTFormalParamStmtNode::accept(Visitor &v) {
    v.visit(this);
}