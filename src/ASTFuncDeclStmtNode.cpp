//
// Created by marc on 25/04/2018.
//

#include "include/ASTNodes/ASTFuncDeclStmtNode.h"

ASTFuncDeclStmtNode::ASTFuncDeclStmtNode(std::string identifier, std::vector<ASTFormalParamStmtNode *> formalParams,
                                         std::string type, ASTStatement_Node *block) {
    this->identifier = identifier;
    this->formalParams = formalParams;
    this->type = type;
    this->block = block;
}

ASTFuncDeclStmtNode::~ASTFuncDeclStmtNode() {
    delete block;
    for (auto &param : formalParams) {
        delete param;
    }
}