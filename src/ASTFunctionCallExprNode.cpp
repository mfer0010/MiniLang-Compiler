//
// Created by marc on 25/04/2018.
//

#include "include/ASTFunctionCallExprNode.h"

ASTFunctionCallExprNode::ASTFunctionCallExprNode(std::string identifier) {
    this->identifier = identifier;
}

ASTFunctionCallExprNode::ASTFunctionCallExprNode(std::string identifier, std::vector<ASTExpression_Node *> actualParams) {
    this->identifier = identifier;
    this->actualParams = actualParams;
}

ASTFunctionCallExprNode::~ASTFunctionCallExprNode() {
    for (auto const &actualParam : actualParams) {
        delete actualParam;
    }
}

void ASTFunctionCallExprNode::accept(Visitor *v) {
    v->visit(this);
}