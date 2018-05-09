//
// Created by marc on 03/05/2018.
//

#include "Scope.h"
#include "../ASTNodes/StatementNodes/ASTVariableDeclStmtNode.h"
#include "../ASTNodes/StatementNodes/ASTFuncDeclStmtNode.h"
#include "../Exceptions/VisitorException.h"

bool Scope::inScope(std::string identifier) {
    return identifiers.find(identifier) != identifiers.end();
}

void Scope::addToScope(ASTVariableDeclStmtNode *variable) {
    VariableDetails * details = new VariableDetails(variable->type);

    identifiers.insert(std::pair<std::string, VariableDetails *>(variable->identifier, details));
}

void Scope::addToScope(ASTFormalParamStmtNode *formalParam) {
    VariableDetails * details = new VariableDetails(formalParam->type);

    identifiers.insert(std::pair<std::string, VariableDetails *>(formalParam->identifier, details));
}

void Scope::addToScope(ASTFuncDeclStmtNode *function) {
    VariableDetails * details = new VariableDetails(function->type, function->formalParams);

    identifiers.insert(std::pair<std::string, VariableDetails *>(function->identifier,details));
}

void Scope::addToScope(std::string identifier) {
    identifiers.insert(std::pair<std::string, VariableDetails *>(identifier, nullptr));
}

void Scope::removeFromScope(std::string identifier) {
    std::map<std::string, VariableDetails *>::iterator iter = identifiers.find(identifier);

    if (iter != identifiers.end()) {
        identifiers.erase(iter);
    } else {
        throw VisitorException("Semantic Analysis Error:\n\tIdentifier to be deleted not found");
    }
}

std::string Scope::returnType(std::string identifier) {
    std::map<std::string, VariableDetails *>::iterator iter = identifiers.find(identifier);

    if (iter != identifiers.end()) {
        return iter->second->type;
    } else {
        throw VisitorException("Semantic Analysis Error:\n\tIdentifier not found");
    }
}

std::vector<ASTFormalParamStmtNode *>* Scope::returnParams(std::string identifier) {
    std::map<std::string, VariableDetails *>::iterator iter = identifiers.find(identifier);

    if (iter != identifiers.end()) {
        return iter->second->parameters;
    } else {
        //throw VisitorException("Semantic Analysis Error:\n\tIdentifier not found");
        return nullptr;
    }
}

Scope::~Scope() {
    for (auto &identifier : identifiers) {
        delete identifier.second;
    }
}