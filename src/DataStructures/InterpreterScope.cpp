//
// Created by marc on 11/05/2018.
//

#include "InterpreterScope.h"


InterpreterScope::InterpreterScope() {}

InterpreterScope::~InterpreterScope() {
    //delete expressions
    for (auto &variable : variables) {
        delete variable.second;
    }
}

void InterpreterScope::addToScope(std::string identifier, ASTFuncDeclStmtNode *function) {
    functions.insert(std::pair<std::string, ASTFuncDeclStmtNode *>(identifier,function));
}

void InterpreterScope::addToScope(std::string identifier, Evaluation *evaluation) {
    variables.insert(std::pair<std::string, Evaluation *>(identifier,evaluation));
}

ASTFuncDeclStmtNode* InterpreterScope::returnFunction(std::string identifier) {
    std::map<std::string,ASTFuncDeclStmtNode *>::iterator iter = functions.find(identifier);

    //if not found, return nullptr
    if (iter == functions.end()) {
        return nullptr;
    }
    return iter->second;
}

Evaluation* InterpreterScope::returnVariable(std::string identifier) {
    std::map<std::string, Evaluation *>::iterator iter = variables.find(identifier);

    //if not found return nullpts
    if(iter == variables.end()) {
        return nullptr;
    }
    return iter->second;
}

std::map<std::string, Evaluation *> InterpreterScope::getVariables() {
    return variables;
}

std::map<std::string, ASTFuncDeclStmtNode *> InterpreterScope::getFunctions() {
    return functions;
}

