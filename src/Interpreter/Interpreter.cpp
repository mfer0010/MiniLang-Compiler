//
// Created by marc on 11/05/2018.
//

#include <iostream>
#include "Interpreter.h"
#include "../Exceptions/InterpreterException.h"
#include "../ASTNodes/StatementNodes/ASTAssignmentStmtNode.h"
#include "../ASTNodes/ExpressionNodes/ASTBinaryExprNode.h"
#include "../ASTNodes/StatementNodes/ASTBlockStmtNode.h"
#include "../ASTNodes/ExpressionNodes/ASTBooleanLiteralExprNode.h"
#include "../ASTNodes/ExpressionNodes/ASTFunctionCallExprNode.h"
#include "../ASTNodes/ExpressionNodes/ASTIdentifierExprNode.h"
#include "../ASTNodes/StatementNodes/ASTIfStmtNode.h"
#include "../ASTNodes/ExpressionNodes/ASTIntegerLiteralExprNode.h"
#include "../ASTNodes/StatementNodes/ASTPrintStmtNode.h"
#include "../ASTNodes/ExpressionNodes/ASTRealLiteralExprNode.h"
#include "../ASTNodes/StatementNodes/ASTReturnStmtNode.h"
#include "../ASTNodes/ExpressionNodes/ASTStringLiteralExprNode.h"
#include "../ASTNodes/ExpressionNodes/ASTSubExpressionExprNode.h"
#include "../ASTNodes/ExpressionNodes/ASTUnaryExprNode.h"
#include "../ASTNodes/StatementNodes/ASTVariableDeclStmtNode.h"
#include "../ASTNodes/StatementNodes/ASTWhileStmtNode.h"

Interpreter::Interpreter() {
}

Interpreter::~Interpreter() {
    if (lastEvaluation != nullptr) {
        lastEvaluation = nullptr;
    }
}

void Interpreter::visit(ASTNode *node) {
    //push global scope:
    InterpreterScope * globalScope = new InterpreterScope();
    pushScope(globalScope);
    for (auto const &statement: node->statements) {
        statement->accept(this);
    }
}

void Interpreter::visit(ASTAssignmentStmtNode *node) {
    //type of expression cannot change from when it was declared,
    //thus look for the identifier's type
    Evaluation * variableEvaluation = getVariableEvaluationFromAnyScope(node->identifier);

    //visit Expression Node
    node->expression->accept(this);

    if(lastEvaluation->type == "INT") {
        if (variableEvaluation->type == "REAL") {
            variableEvaluation->setRealValue(lastEvaluation->getIntValue());
        } else {
            variableEvaluation->setIntValue(lastEvaluation->getIntValue());
        }
    } else if (lastEvaluation->type == "STRING") {
        variableEvaluation->setStringValue(lastEvaluation->getStringVaue());
    } else if (lastEvaluation->type == "REAL") {
        variableEvaluation->setRealValue(lastEvaluation->getRealValue());
    } else if (lastEvaluation->type == "BOOL") {
        variableEvaluation->setBoolValue(lastEvaluation->getBoolValue());
    } else {
        throw InterpreterException("Error in Compiler Code: Type in expression passed badly");
    }
}

Evaluation* Interpreter::getVariableEvaluationFromAnyScope(std::string identifier) {
    std::stack<InterpreterScope *> tempStack = this->scopes;
    InterpreterScope * currentScope;
    Evaluation * tempEval;

    while (!tempStack.empty()) {
        currentScope = tempStack.top();
        tempEval = currentScope->returnVariable(identifier);
        if (tempEval != nullptr) {
            return tempEval;
        }
        tempStack.pop();
    }
    //this should never run since semantic analysis would not allow it:
    throw InterpreterException("Identifier not found.");
}

void Interpreter::visit(ASTBinaryExprNode *node) {
    //visit LHS
    node->LHS->accept(this);
    Evaluation *LHS = lastEvaluation;
    lastEvaluation = nullptr;

    //visit RHS
    node->RHS->accept(this);
    Evaluation *RHS = lastEvaluation;
    lastEvaluation = nullptr;

    evaluateOperation(LHS, RHS, node->_operator);

    //delete from memory:
    delete LHS;
    delete RHS;
}

void Interpreter::evaluateOperation(Evaluation *LHS, Evaluation *RHS, std::string _operator) {
    if (LHS->type != RHS->type) {
        //this will happen with int and real
        if (LHS->type == "INT" && RHS->type == "REAL") {
            LHS->setRealValue(LHS->getIntValue());
        } else if (LHS->type == "REAL" && RHS->type == "INT") {
            RHS->setRealValue(RHS->getIntValue());
        } else {
            throw InterpreterException("Compiler Code Error, semantic analysis shouldn't have allowed "
                                       + LHS->type + " and " + RHS->type + " to be evaluated by operator " + _operator);
        }
    }

    if (LHS->type == "STRING") {
        handleOperator(LHS->getStringVaue(), RHS->getStringVaue(), _operator);
    } else if (LHS->type == "REAL") {
        handleOperator(LHS->getRealValue(), RHS->getRealValue(), _operator);
    } else if (LHS->type == "BOOL") {
        handleOperator(LHS->getBoolValue(), RHS->getBoolValue(), _operator);
    } else if (LHS->type == "INT") {
        handleOperator(LHS->getIntValue(), RHS->getIntValue(), _operator);
    } else {
        throw InterpreterException("Error in Compiler Code: Type in expression passed badly");
    }
}

void Interpreter::handleOperator(bool LHS, bool RHS, std::string _operator) {
    if (_operator == "AND") {
        lastEvaluation = new Evaluation(LHS && RHS);
    } else if (_operator == "OR") {
        lastEvaluation = new Evaluation(LHS || RHS);
    } else if (_operator == "==") {
        lastEvaluation = new Evaluation(LHS==RHS);
    } else if (_operator == "!=") {
        lastEvaluation = new Evaluation(LHS != RHS);
    } else {
        throw InterpreterException("Error in Compiler Code, operator not supported for bool");
    }
}

void Interpreter::handleOperator(double LHS, double RHS, std::string _operator) {
    if (_operator == "+") {
        lastEvaluation = new Evaluation(LHS + RHS);
    } else if (_operator == "-") {
        lastEvaluation = new Evaluation(LHS - RHS);
    } else if (_operator == "*") {
        lastEvaluation = new Evaluation(LHS * RHS);
    } else if (_operator == "/") {
        if (RHS == 0) {
            throw InterpreterException("Division by 0 error.");
        }
        lastEvaluation = new Evaluation(LHS / RHS);
    } else if (_operator == "<") {
        lastEvaluation = new Evaluation(LHS < RHS);
    } else if (_operator == ">") {
        lastEvaluation = new Evaluation(LHS > RHS);
    } else if (_operator == "<=") {
        lastEvaluation = new Evaluation(LHS <= RHS);
    } else if (_operator == ">=") {
        lastEvaluation = new Evaluation(LHS >= RHS);
    } else if (_operator == "==") {
        lastEvaluation = new Evaluation(LHS == RHS);
    } else if (_operator == "!=") {
        lastEvaluation = new Evaluation(LHS != RHS);
    } else {
        throw InterpreterException("Error in Compiler Code, operator not supported for real");
    }
}

void Interpreter::handleOperator(int LHS, int RHS, std::string _operator) {
    if (_operator == "+") {
        lastEvaluation = new Evaluation(LHS + RHS);
    } else if (_operator == "-") {
        lastEvaluation = new Evaluation(LHS - RHS);
    } else if (_operator == "*") {
        lastEvaluation = new Evaluation(LHS * RHS);
    } else if (_operator == "/") {
        if (RHS == 0) {
            throw InterpreterException("Division by 0 error.");
        }
        lastEvaluation = new Evaluation(LHS / RHS);
    } else if (_operator == "<") {
        lastEvaluation = new Evaluation(LHS < RHS);
    } else if (_operator == ">") {
        lastEvaluation = new Evaluation(LHS > RHS);
    } else if (_operator == "<=") {
        lastEvaluation = new Evaluation(LHS <= RHS);
    } else if (_operator == ">=") {
        lastEvaluation = new Evaluation(LHS >= RHS);
    } else if (_operator == "==") {
        lastEvaluation = new Evaluation(LHS == RHS);
    } else if (_operator == "!=") {
        lastEvaluation = new Evaluation(LHS != RHS);
    } else {
        throw InterpreterException("Error in Compiler Code, operator not supported for real");
    }
}

void Interpreter::handleOperator(std::string LHS, std::string RHS, std::string _operator) {
    if (_operator == "+") {
        lastEvaluation = new Evaluation(LHS + RHS);
    } else if (_operator == "==") {
        lastEvaluation = new Evaluation(LHS == RHS);
    } else if (_operator == "!=") {
        lastEvaluation = new Evaluation(LHS != RHS);
    } else {
        throw InterpreterException("Error in Compiler Code, operator not supported for real");
    }
}

void Interpreter::visit(ASTBlockStmtNode *node) {
    //create a new scope
    InterpreterScope *newScope = new InterpreterScope();
    ASTFuncDeclStmtNode * functionDeclNode;
    bool functionBlock = nextBlockIsAFunction;

    //push scope
    pushScope(newScope);

    //check if this block is part of a function definition
    if (nextBlockIsAFunction) {
        nextBlockIsAFunction = false;
        functionDeclNode = returnFunctionDeclarationNode(functionCalled.identifier);
        //Add the function arguments to the scope of the function:
        for (unsigned long i = 0; i < functionCalled.parameters.size(); i++) {
            functionCalled.parameters.at(i)->accept(this);
            functionDeclNode->formalParams.at(i)->accept(this);
        }
    }

    //visit all the statements in the block:
    for (auto const &statement : node->statements) {
        statement->accept(this);

        //stop at return
        if (returnFound) {
            break;
        }
        //stop the return if the block is a function block
        if (functionBlock && returnFound) {
            returnFound = false;
        }
    }

    //pop scope
    popScope();
    delete newScope;
}

ASTFuncDeclStmtNode* Interpreter::returnFunctionDeclarationNode(std::string identifier) {
    std::stack<InterpreterScope *> tempStack = scopes;
    InterpreterScope * currentScope;
    ASTFuncDeclStmtNode * tempNode;

    while (!tempStack.empty()) {
        currentScope = tempStack.top();
        tempNode = currentScope->returnFunction(identifier);
        if (tempNode != nullptr) {
            return tempNode;
        }
        tempStack.pop();
    }
    //this should never run since semantic analysis would not allow it:
    throw InterpreterException("Identifier not found.");
}

void Interpreter::visit(ASTBooleanLiteralExprNode *node) {
    if (lastEvaluation != nullptr) {
        lastEvaluation = nullptr;
    }
    lastEvaluation = new Evaluation(node->literalValue);
}

void Interpreter::visit(ASTFormalParamStmtNode *node) {
    InterpreterScope *currentScope = topScope();
    //add lastEvaluation to the Scope (the actual Parameter)
    currentScope->addToScope(node->identifier,lastEvaluation);
    lastEvaluation = nullptr;
}

void Interpreter::visit(ASTFuncDeclStmtNode *node) {
    InterpreterScope * currentScope = topScope();
    //save function information to the scope, to be used once called
    currentScope->addToScope(node->identifier,node);
}

void Interpreter::visit(ASTFunctionCallExprNode *node) {
    ASTFuncDeclStmtNode * funcDecl;

    //set the global variables accordingly
    nextBlockIsAFunction = true;
    returnFound = false;
    //save information in functionCalled
    functionCalled.identifier = node->identifier;
    functionCalled.parameters = node->actualParams;

    funcDecl = returnFunctionDeclarationNode(node->identifier);

    //visit the block
    funcDecl->block->accept(this);
}

void Interpreter::visit(ASTIdentifierExprNode *node) {
    if (lastEvaluation != nullptr) {
        lastEvaluation = nullptr;
    }
    Evaluation * evaluation = getVariableEvaluationFromAnyScope(node->identifier);
    if (evaluation->type == "STRING") {
        lastEvaluation = new Evaluation(evaluation->getStringVaue());
    } else if (evaluation->type == "INT") {
        lastEvaluation = new Evaluation(evaluation->getIntValue());
    } else if (evaluation->type == "REAL") {
        lastEvaluation = new Evaluation(evaluation->getRealValue());
    } else if (evaluation->type == "BOOL") {
        lastEvaluation = new Evaluation(evaluation->getBoolValue());
    }
}

void Interpreter::visit(ASTIfStmtNode *node) {
    //visit expression node
    node->expression->accept(this);

    //if true visit the block
    if (lastEvaluation->getBoolValue()) {
        node->ifBlock->accept(this);
    }
    //visit else block if not null
    if (node->elseBlock != nullptr) {
        node->elseBlock->accept(this);
    }
}

void Interpreter::visit(ASTIntegerLiteralExprNode *node) {
    if (lastEvaluation != nullptr) {
        delete  lastEvaluation;
    }
    lastEvaluation = new Evaluation(node->literalValue);
}

void Interpreter::visit(ASTNumberExprNode *node) {
    if (lastEvaluation != nullptr) {
        lastEvaluation = nullptr;
    }
    lastEvaluation = new Evaluation(node->value);
}

void Interpreter::visit(ASTPrintStmtNode *node) {
    //visit expression
    node->expression->accept(this);

    if (lastEvaluation->type == "String") {
        std::cout << lastEvaluation->getStringVaue() << std::endl;
    } else if (lastEvaluation->type == "REAL") {
        std::cout<< lastEvaluation->getRealValue() << std::endl;
    } else if (lastEvaluation->type == "INT") {
        std::cout << lastEvaluation->getIntValue() << std::endl;
    } else if (lastEvaluation->type == "BOOL") {
        std::cout << (lastEvaluation->getBoolValue() ? "true" : "false") << std::endl;
    }
}

void Interpreter::visit(ASTRealLiteralExprNode *node) {
    if (lastEvaluation != nullptr) {
        lastEvaluation = nullptr;
    }
    lastEvaluation = new Evaluation(node->literalValue);
}

void Interpreter::visit(ASTReturnStmtNode *node) {
    node->expression->accept(this); //interpret expression
    returnFound = true; //set return flag to true to stop visiting function block
}

void Interpreter::visit(ASTStringLiteralExprNode *node) {
    if (lastEvaluation != nullptr) {
        lastEvaluation = nullptr;
    }
    lastEvaluation = new Evaluation(node->literalValue);
}

void Interpreter::visit(ASTSubExpressionExprNode *node) {
    node->expression->accept(this);
}

void Interpreter::visit(ASTUnaryExprNode *node) {
    node->expression->accept(this);

    Evaluation * evaluation = new Evaluation();
    if(node->prefix == "NOT") {
        evaluation->setBoolValue(!lastEvaluation->getBoolValue());
    } else if (node->prefix == "-") {
        if (lastEvaluation->type == "INT") {
            evaluation->setIntValue(-(lastEvaluation->getIntValue()));
        } else if (lastEvaluation->type == "REAL") {
            evaluation->setRealValue(-(lastEvaluation->getRealValue()));
        } else {
            throw InterpreterException("Error in Compiler Code: Type in expression passed badly");
        }
    } else {
        throw InterpreterException("Error in Compiler Code: Type in expression passed badly");
    }

    if (lastEvaluation != nullptr) {
        lastEvaluation = nullptr; // should always run
    }
    lastEvaluation = evaluation;
}

void Interpreter::visit(ASTVariableDeclStmtNode *node) {
    node->expression->accept(this);

    InterpreterScope *currentScope = topScope();

    if (node->type == "REAL" && lastEvaluation->type == "INT") {
        lastEvaluation->setRealValue(lastEvaluation->getIntValue());
    }

    currentScope->addToScope(node->identifier, lastEvaluation);
    lastEvaluation = nullptr;
}

void Interpreter::visit(ASTWhileStmtNode *node) {
    node->expression->accept(this);

    while (lastEvaluation->getBoolValue()) {
        node->block->accept(this);
        node->expression->accept(this);
    }
}

void Interpreter::pushScope(InterpreterScope *scope) {
    scopes.push(scope);
}

InterpreterScope* Interpreter::popScope() {
    InterpreterScope *toReturn = scopes.top();
    scopes.pop();
    return toReturn;
}

InterpreterScope* Interpreter::topScope() {
    return scopes.top();
}