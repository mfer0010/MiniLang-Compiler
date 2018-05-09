//
// Created by marc on 09/05/2018.
//

#ifndef MINILANG_COMPILER_SEMANTICANALYSER_H
#define MINILANG_COMPILER_SEMANTICANALYSER_H


#include <stack>
#include "../Visitors/Visitor.h"
#include "../DataStructures/Scope.h"

class SemanticAnalyser : public Visitor {
private:
    //Scopes of the program
    std::stack<Scope *> scopes;

    //Push new scope into scopes stack
    void pushScope(Scope *scope);

    //Pop a scope from the scopes stack
    Scope * popScope();

    //Return the top of the scopes stack
    Scope * topScope();

    //Struct used when returning functions
    typedef struct CheckFunctionDeclReturn {
        bool isGlobal;
        bool isFunctionDecl;
        int currentBlockIndex;
        int noOfIfsEncountered;
        int noOfreturnsEncountered;
        ASTFuncDeclStmtNode * funcDecl;
    } CheckFunctionDeclReturn;

    //Stores functions declared inside a function
    std::vector<CheckFunctionDeclReturn *> functionsReturn;

    //last type of expression
    std::string lastType;

    //returns the type of a given identifier
    std::string returnIdentifierType(std::string identifier);

    //returns the parameters of a function
    std::vector<ASTFormalParamStmtNode *> * returnFunctionParameters(std::string identifier);

    //Checks the types for binary operators
    bool checkTypes(std::string _operator, std::string lhs, std::string rhs);

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
    SemanticAnalyser();

    virtual ~SemanticAnalyser();
};


#endif //MINILANG_COMPILER_SEMANTICANALYSER_H
