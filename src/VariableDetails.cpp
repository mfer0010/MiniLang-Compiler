//
// Created by marc on 03/05/2018.
//
#include "include/VariableDetails.h"

VariableDetails::VariableDetails(std::string type) {
    this->type = type;
}

VariableDetails::VariableDetails(std::string type, std::vector<ASTFormalParamStmtNode *> parameters) {
    this->type = type;
    this->parameters = new std::vector<ASTFormalParamStmtNode *> (parameters);
}

VariableDetails::~VariableDetails() {
    delete parameters;
}