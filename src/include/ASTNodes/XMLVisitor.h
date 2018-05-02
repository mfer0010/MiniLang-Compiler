//
// Created by marc on 01/05/2018.
//

#ifndef MINILANG_COMPILER_XMLVISITOR_H
#define MINILANG_COMPILER_XMLVISITOR_H

#include <fstream>
#include <iostream>
#include "Visitor.h"


class XMLVisitor : public Visitor {
private:
    int indentationNo = 0;
    std::ofstream XMLFileOutput;

    std::string getIndentation();

    /*std::string printOperator(std::string _operator);

    void printExpression(ASTExpression_Node * node);*/

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
    XMLVisitor();

    virtual ~XMLVisitor();
};

#endif //MINILANG_COMPILER_XMLVISITOR_H