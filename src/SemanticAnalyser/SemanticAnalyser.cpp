//
// Created by marc on 09/05/2018.
//

#include "SemanticAnalyser.h"
#include "../Exceptions/VisitorException.h"

SemanticAnalyser::SemanticAnalyser() {}

SemanticAnalyser::~SemanticAnalyser() {}

void SemanticAnalyser::pushScope(Scope *scope) {
    scopes.push(scope);
}

Scope* SemanticAnalyser::popScope() {
    if (scopes.empty()) {
        throw VisitorException("Semantic Pass: Stack is Empty, No Scopes are currently open.");
    }
    Scope *toReturn = scopes.top();
    scopes.pop();
    return toReturn;
}

Scope* SemanticAnalyser::topScope() {
    if (scopes.empty()) {
        throw VisitorException("Semantic Pass: Stack is Empty, No Scopes are currently open.");
    }
    return scopes.top();
}

std::string SemanticAnalyser::returnIdentifierType(std::string identifier) {
    std::stack<Scope *> copyOfScopes = scopes;
    Scope *currentScope;
    std::string temp;
    std::string exceptionMessage;
    bool exception;

    while (!copyOfScopes.empty()) {
        exception = false;
        currentScope = copyOfScopes.top();
        try {
            temp = currentScope->returnType(identifier);
        } catch (VisitorException &v) {
            exception = true;
        }
        if (!exception) {
            return temp;
        }
        copyOfScopes.pop();
    }
    throw VisitorException("Semantic Pass: Identifier Not Found");
}

std::vector<ASTFormalParamStmtNode *>* SemanticAnalyser::returnFunctionParameters(std::string identifier) {
    std::stack<Scope *> copyOfScopes = scopes;
    Scope *currentScope;
    std::vector<ASTFormalParamStmtNode *> *params;

    while (!copyOfScopes.empty()) {
        currentScope = copyOfScopes.top();
        params = currentScope->returnParams(identifier);

        if (params != nullptr) {
            return params;
        }
        copyOfScopes.pop();
    }
    return nullptr;
}

bool SemanticAnalyser::checkTypes(std::string _operator, std::string lhs, std::string rhs) {
    //Check for Binary Operators
    if (_operator == "-" || _operator == "*" || _operator == "/") {
        // -, * and / accept numeric types only (i.e. int and real)
        if (lhs == "STRING" || lhs == "BOOL" || rhs == "STRING" || rhs == "BOOL") {
            return false; //incorrect type
        }
        //if both sides of the operators are integers, then set the type to INT,
        //else one of them must be real, thus set the type to real.
        lastType = (lhs == "INT" && rhs == "INT") ? "INT" : "REAL";
        return true; //correct type
    } else if (_operator == "AND" || _operator == "OR") {
        //types should only be boolean
        if (lhs == "BOOL" && rhs == "BOOL") {
            lastType = "BOOL";
            return true; //correct type
        }
        return false; //incorrect type
    } else if (_operator == "+") {
        //Cannot be Boolean but can be string (Concatenation)
        if (lhs == "BOOL" || rhs == "BOOL") {
            return false; //incorrect type
        } else if (lhs == "STRING" && rhs == "STRING") {
            return true; //correct type
        } else if (lhs == "STRING" || rhs == "STRING") {
            //they must both be Strings for Concatenation
            return false; //incorrect type
        } else {
            //either int or real, same as for the previous operators
            lastType = (lhs == "INT" && rhs == "INT") ? "INT" : "REAL";
            return true; //correct type
        }
    }

    //Check for Relational Operators
    lastType = "BOOL";
    if (_operator == "<" || _operator == ">" || _operator == "<=" || _operator == ">=") {
        if (lhs == "STRING" || lhs == "BOOL" || rhs == "STRING" || rhs == "BOOL") {
            return false; //incorrect type
        }
        return true; //correct type
    } else if (_operator == "==" || _operator == "!=") {
        //both types must be identical
        if (lhs == rhs) {
            if (lhs == "STRING" || lhs == "BOOL" || lhs == "REAL" || lhs == "INT")
                return true; //correct type
        }
        return false; //incorrect type
    }

    return false; //should never reach here
}