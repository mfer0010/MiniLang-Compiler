//
// Created by marc on 01/05/2018.
//

#ifndef MINILANG_COMPILER_VISITOR_H_H
#define MINILANG_COMPILER_VISITOR_H_H

#include "ASTAssignmentStmtNode.h"
#include "ASTBinaryExprNode.h"
#include "ASTBlockStmtNode.h"
#include "ASTBooleanLiteralExprNode.h"
#include "ASTFormalParamStmtNode.h"
#include "ASTFuncDeclStmtNode.h"
#include "ASTFunctionCallExprNode.h"
#include "ASTIdentifierExprNode.h"
#include "ASTIfStmtNode.h"
#include "ASTIntegerLiteralExprNode.h"
#include "ASTPrintStmtNode.h"
#include "ASTRealLiteralExprNode.h"
#include "ASTReturnStmtNode.h"
#include "ASTStringLiteralExprNode.h"
#include "ASTSubExpressionExprNode.h"
#include "ASTUnaryExprNode.h"
#include "ASTVariableDeclStmtNode.h"
#include "ASTWhileStmtNode.h"

class Visitor {
public:
    virtual void visit(ASTAssignmentStmtNode *node) = 0;
    virtual void visit(ASTBinaryExprNode *node) = 0;
    virtual void visit(ASTBlockStmtNode *node) = 0;
    virtual void visit(ASTBooleanLiteralExprNode *node) = 0;
    virtual void visit(ASTFormalParamStmtNode *node) = 0;
    virtual void visit(ASTFuncDeclStmtNode *node) = 0;
    virtual void visit(ASTFunctionCallExprNode *node) = 0;
    virtual void visit(ASTIdentifierExprNode *node) = 0;
    virtual void visit(ASTIfStmtNode *node) = 0;
    virtual void visit(ASTIntegerLiteralExprNode *node) = 0;
    virtual void visit(ASTNode *node) = 0;
    virtual void visit(ASTNumberExprNode *node) = 0;
    virtual void visit(ASTPrintStmtNode *node) = 0;
    virtual void visit(ASTRealLiteralExprNode *node) = 0;
    virtual void visit(ASTReturnStmtNode *node) = 0;
    virtual void visit(ASTStringLiteralExprNode *node) = 0;
    virtual void visit(ASTSubExpressionExprNode *node) = 0;
    virtual void visit(ASTUnaryExprNode *node) = 0;
    virtual void visit(ASTVariableDeclStmtNode *node) = 0;
    virtual void visit(ASTWhileStmtNode *node) = 0;
};

#endif //MINILANG_COMPILER_VISITOR_H_H
