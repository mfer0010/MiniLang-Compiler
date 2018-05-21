//
// Created by marc on 11/05/2018.
//

#ifndef MINILANG_COMPILER_INTERPRETER_H
#define MINILANG_COMPILER_INTERPRETER_H

#include <string>
#include <vector>
#include <stack>
#include "../Visitors/Visitor.h"
#include "../DataStructures/Evaluation.h"
#include "../DataStructures/InterpreterScope.h"

class Interpreter : public Visitor {
private:
    //stack containing all scopes of the program
    std::stack<InterpreterScope *> scopes;

    //Struct to store the values of a function call
    typedef struct FunctionCalls {
        std::vector <ASTExpression_Node *> parameters;
        std::string identifier;
    } FunctionCalls;

    //Last Evaluation in an expression
    Evaluation * lastEvaluation = nullptr;

    //This is set to true when defining a function so that when the block
    //of the function is visited, it can be handled accordingly.
    bool nextBlockIsAFunction = false;

    //true if return is called in a scope, used to stop visiting a block
    bool returnFound = false;

    //Stores information on current function that has been called or defined
    FunctionCalls functionCalled;

    //Same use as push scope of Semantic Analyser
    void pushScope(InterpreterScope *scope);

    //Same use as pop scope of Semantic Analyser
    InterpreterScope * popScope();

    //Same use as top scope of Semantic Analyser
    InterpreterScope * topScope();

    //Returns the Evaluation of a variable from any scope
    Evaluation * getVariableEvaluationFromAnyScope(std::string identifier);

    //Returns the Function Decleration Node of a function
    ASTFuncDeclStmtNode * returnFunctionDeclarationNode(std::string identifier);

    //Evaluates the operation depending on the operator passed
    void evaluateOperation(Evaluation * LHS, Evaluation * RHS, std::string _operator);

    //does the actual evaluation, only called by evaluateOperation
    void handleOperator(std::string LHS, std::string RHS, std::string _operator);
    void handleOperator(int LHS, int RHS, std::string _operator);
    void handleOperator(double LHS, double RHS, std::string _operator);
    void handleOperator(bool LHS, bool RHS, std::string _operator);

    //Visitor Functions:
    virtual void visit(ASTAssignmentStmtNode *node) override;

    virtual void visit(ASTBinaryExprNode *node) override;

    virtual void visit(ASTBlockStmtNode *node) override;

    virtual void visit(ASTBooleanLiteralExprNode *node) override;

    virtual void visit(ASTFormalParamStmtNode *node) override;

    virtual void visit(ASTFuncDeclStmtNode *node) override;

    virtual void visit(ASTFunctionCallExprNode *node) override;

    virtual void visit(ASTIdentifierExprNode *node) override;

    virtual void visit(ASTIfStmtNode *node) override;

    virtual void visit(ASTIntegerLiteralExprNode *node) override;

    virtual void visit(ASTNode *node) override;

    virtual void visit(ASTNumberExprNode *node) override;

    virtual void visit(ASTPrintStmtNode *node) override;

    virtual void visit(ASTRealLiteralExprNode *node) override;

    virtual void visit(ASTReturnStmtNode *node) override;

    virtual void visit(ASTStringLiteralExprNode *node) override;

    virtual void visit(ASTSubExpressionExprNode *node) override;

    virtual void visit(ASTUnaryExprNode *node) override;

    virtual void visit(ASTVariableDeclStmtNode *node) override;

    virtual void visit(ASTWhileStmtNode *node) override;

public:
    Interpreter();

    //used for #st in repl
    void printSymbolTable();

    virtual ~Interpreter();
};


#endif //MINILANG_COMPILER_INTERPRETER_H
