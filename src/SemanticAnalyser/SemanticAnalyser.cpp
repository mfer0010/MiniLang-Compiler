//
// Created by marc on 09/05/2018.
//

#include "SemanticAnalyser.h"
#include "../Exceptions/VisitorException.h"
#include "../ASTNodes/StatementNodes/ASTAssignmentStmtNode.h"
#include "../Exceptions/SemanticAnalyserException.h"
#include "../ASTNodes/ExpressionNodes/ASTBinaryExprNode.h"
#include "../ASTNodes/StatementNodes/ASTBlockStmtNode.h"
#include "../ASTNodes/StatementNodes/ASTFuncDeclStmtNode.h"
#include "../ASTNodes/ExpressionNodes/ASTFunctionCallExprNode.h"
#include "../ASTNodes/ExpressionNodes/ASTIdentifierExprNode.h"
#include "../ASTNodes/StatementNodes/ASTIfStmtNode.h"
#include "../ASTNodes/StatementNodes/ASTPrintStmtNode.h"
#include "../ASTNodes/StatementNodes/ASTReturnStmtNode.h"
#include "../ASTNodes/ExpressionNodes/ASTSubExpressionExprNode.h"
#include "../ASTNodes/ExpressionNodes/ASTUnaryExprNode.h"
#include "../ASTNodes/StatementNodes/ASTVariableDeclStmtNode.h"
#include "../ASTNodes/StatementNodes/ASTWhileStmtNode.h"

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

void SemanticAnalyser::visit(ASTNode *node) {
    for (auto const &statement : node->statements) {
        statement->accept(this);
    }
}

void SemanticAnalyser::visit(ASTAssignmentStmtNode *node) {
    std::string type = returnIdentifierType(node->identifier); //throws exception if identifier is not found

    //get the Type of the expression Node
    node->expression->accept(this);

    //check types
    if (lastType != type) {
        if (!(lastType == "INT" && type == "REAL")) {
            throw SemanticAnalyserException("Incompatible types, expected '" + type + "'");
        }
    }
}

void SemanticAnalyser::visit(ASTBinaryExprNode *node) {
    //accept LHS of expression
    node->LHS->accept(this);
    std::string LHSType = lastType;
    //accept RHS of expression
    node->RHS->accept(this);
    std::string RHSType = lastType;

    //check operator types
    if (!checkTypes(node->_operator,LHSType,RHSType)) {
        //if there is an error
        throw SemanticAnalyserException("Incompatible Types on operator '" +
                                                node->_operator + "' (" + LHSType + node->_operator + RHSType +")");
    }
}

void SemanticAnalyser::visit(ASTBlockStmtNode *node) {
    Scope *newScope = new Scope();
    //push scope on stack
    pushScope(newScope);

    for (auto &function : functionsReturn) {
        if (!function->isFunctionDecl) {
            function->isFunctionDecl = true;
            for (auto const &param : function->funcDecl->formalParams) {
                param->accept(this);
            }
            break;
        }
    }

    //Check all the statements in the block
    for (auto const &statement : node->statements) {
        statement->accept(this);
    }

    //pop the scope from stack
    popScope();
    delete newScope; //free memory
}

void SemanticAnalyser::visit(ASTBooleanLiteralExprNode *node) {
    lastType = "BOOL";
}

void SemanticAnalyser::visit(ASTFormalParamStmtNode *node) {
    Scope * currentScope = topScope();
    //if identifier already exists, throw error, else add it to the scope
    if (currentScope->inScope(node->identifier)) {
        throw SemanticAnalyserException("Duplicate Declaration of variable or function with identifier '"
                                        + node->identifier + "'");
    }
    currentScope->addToScope(node);
}

void SemanticAnalyser::visit(ASTFuncDeclStmtNode *node) {
    CheckFunctionDeclReturn * checkFunctionDeclReturn;
    //get the current scope
    Scope * currentScope = topScope();
    //check if function is already declared in scope
    if (currentScope->inScope(node->identifier)) {
        throw SemanticAnalyserException("Duplicate Declaration of function with identifier '"
                                        + node->identifier + "'");
    }

    //add function information to functionsReturn vector
    checkFunctionDeclReturn = new CheckFunctionDeclReturn();
    checkFunctionDeclReturn->currentBlockIndex = 0;
    checkFunctionDeclReturn->funcDecl = node;
    checkFunctionDeclReturn->isFunctionDecl = false;
    checkFunctionDeclReturn->isGlobal = false;
    checkFunctionDeclReturn->noOfIfsEncountered = 0;
    checkFunctionDeclReturn->noOfreturnsEncountered = 0;
    functionsReturn.push_back(checkFunctionDeclReturn);

    //add function to scope
    currentScope->addToScope(node);

    //visit block
    try {
        node->block->accept(this);
    } catch (SemanticAnalyserException &exception) {
        currentScope->removeFromScope(node->identifier);
        throw SemanticAnalyserException(exception.error);
    }

    //check for return TOKEN
    checkFunctionDeclReturn = functionsReturn.back();
    functionsReturn.pop_back();
    if (!checkFunctionDeclReturn->isGlobal) {
        if (checkFunctionDeclReturn->noOfIfsEncountered * 2 != checkFunctionDeclReturn->noOfreturnsEncountered) {
            //returns could exist in if statements
            currentScope->removeFromScope(node->identifier);
            throw SemanticAnalyserException("Return expected at end of non-void function.");
        } else if (checkFunctionDeclReturn->noOfIfsEncountered ==0) {
            currentScope->removeFromScope(node->identifier);
            throw SemanticAnalyserException("Return expected at end of non-void function.");
        }
    }

    delete checkFunctionDeclReturn; //free memory
}

void SemanticAnalyser::visit(ASTFunctionCallExprNode *node) {
    std::vector<ASTFormalParamStmtNode *> *params = returnFunctionParameters(node->identifier);

    if (params == nullptr) {
        throw SemanticAnalyserException("Error resolving function '" + node->identifier +"'");
    }

    //check number of parameters
    if (params->size() != node->actualParams.size()) {
        throw SemanticAnalyserException("Incorrect number of parameters passes. Expected " + node->actualParams.size());
    }

    //check type for each parameter
    for (size_t i=0; i < node->actualParams.size(); i++) {
        node->actualParams[i]->accept(this);

        if (lastType != (*params)[i]->type) {
            if (!(lastType == "INT" && (*params)[i]->type == "REAL")) {
                throw SemanticAnalyserException("Parameter types do not match, expected '"
                                                + (*params)[i]->type +"' Received: '" + lastType + "'");
            }
        }
    }

    lastType = returnIdentifierType(node->identifier);
}

void SemanticAnalyser::visit(ASTIdentifierExprNode *node) {
    lastType = returnIdentifierType(node->identifier); //throws exception is identifier is not found
}

void SemanticAnalyser::visit(ASTIfStmtNode *node) {
    CheckFunctionDeclReturn * checkFunctionDeclReturn;

    //if functionsReturn is not empty update last entry accordingly
    if (functionsReturn.size() != 0) {
        checkFunctionDeclReturn = functionsReturn.back();
        checkFunctionDeclReturn->noOfIfsEncountered++;
        checkFunctionDeclReturn->currentBlockIndex++;
    }

    //check expression node, it must be a Bool
    node->expression->accept(this);
    if (lastType != "BOOL") {
        throw SemanticAnalyserException("Expression in if node must be of type BOOL");
    }

    //check if block
    node->ifBlock->accept(this);

    //check else block if it exists
    if (node->elseBlock != nullptr) {
        node->elseBlock->accept(this);
    }

    //update functionsReturn accordingly
    if (functionsReturn.size() != 0) {
        checkFunctionDeclReturn = functionsReturn.back();
        checkFunctionDeclReturn->currentBlockIndex--;
    }
}

void SemanticAnalyser::visit(ASTIntegerLiteralExprNode *node) {
    lastType = "INT";
}

void SemanticAnalyser::visit(ASTNumberExprNode *node) {
    lastType = node->type;
}

void SemanticAnalyser::visit(ASTPrintStmtNode *node) {
    node->expression->accept(this);
}

void SemanticAnalyser::visit(ASTRealLiteralExprNode *node) {
    lastType = "REAL";
}

void SemanticAnalyser::visit(ASTReturnStmtNode *node) {
    CheckFunctionDeclReturn * checkFunctionDeclReturn;

    //check expression
    node->expression->accept(this);

    //check if return is in a function scope
    if (functionsReturn.size() == 0) {
        throw SemanticAnalyserException("Return called outside function scope");
    }

    checkFunctionDeclReturn = functionsReturn.back();

    //check that expression returned is of correct type from function
    if (checkFunctionDeclReturn->funcDecl->type != lastType) {
        throw SemanticAnalyserException("Expected to return " + checkFunctionDeclReturn->funcDecl->type
                                        + " but actually returning " + lastType);
    }
    //update function scope to return whole function
    if (checkFunctionDeclReturn->currentBlockIndex == 0) {
        checkFunctionDeclReturn->isGlobal = true;
    } else {
        checkFunctionDeclReturn->noOfreturnsEncountered++;
    }
}

void SemanticAnalyser::visit(ASTStringLiteralExprNode *node) {
    lastType = "STRING";
}

void SemanticAnalyser::visit(ASTSubExpressionExprNode *node) {
    //check sub expression:
    node->expression->accept(this);
}

void SemanticAnalyser::visit(ASTUnaryExprNode *node) {
    //Check expression type
    node->expression->accept(this);

    //Unary expression cannot accept Strings
    if (lastType == "STRING") {
        throw SemanticAnalyserException("Unary operator does not accept String Literals");
    } else if (lastType == "BOOL") {
        //- can not be applied to boolean, not can
        if (node->prefix != "NOT") {
            throw SemanticAnalyserException("Operator " + node->prefix + " does not support BOOL Type");
        }
    } else if (lastType == "INT" || lastType == "REAL") {
        //not cannout be applied to int or real
        if (node->prefix != "-") {
            throw SemanticAnalyserException("Operator " + node->prefix + " does not support " + lastType + " Type");
        }
    } else {
        throw SemanticAnalyserException("Type " + lastType + " not supported for "
                                        + node->prefix + " unary operator");
    }
}

void SemanticAnalyser::visit(ASTVariableDeclStmtNode *node) {
    //get the scope
    Scope * currentScope = topScope();

    //check if identifier exists
    if (currentScope->inScope(node->identifier)) {
        throw SemanticAnalyserException("Variable " + node->identifier + " already exists in scope");
    }

    //check expression type
    node->expression->accept(this);

    //if type is real then int can be accepted
    if (node->type == "REAL" && lastType == "INT") {
        currentScope->addToScope(node);
        return;
    } else if (node->type != lastType) {
        throw SemanticAnalyserException("Incompatible types, expected: " + node->type);
    }
    //add identifier
    currentScope->addToScope(node);
}

void SemanticAnalyser::visit(ASTWhileStmtNode *node) {
    //accept expression
    node->expression->accept(this);

    if (lastType != "BOOL") {
        throw SemanticAnalyserException("Non-BOOL statement found in while condition");
    }
    //check block
    node->block->accept(this);
}