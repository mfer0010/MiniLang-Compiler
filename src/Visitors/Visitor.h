//
// Created by marc on 01/05/2018.
//

#ifndef MINILANG_COMPILER_VISITOR_H_H
#define MINILANG_COMPILER_VISITOR_H_H


class ASTNode;
class ASTAssignmentStmtNode;
class ASTBinaryExprNode;
class ASTBlockStmtNode;
class ASTBooleanLiteralExprNode;
class ASTFormalParamStmtNode;
class ASTFuncDeclStmtNode;
class ASTFunctionCallExprNode;
class ASTIdentifierExprNode;
class ASTIfStmtNode;
class ASTIntegerLiteralExprNode;
class ASTNumberExprNode;
class ASTPrintStmtNode;
class ASTRealLiteralExprNode;
class ASTReturnStmtNode;
class ASTStringLiteralExprNode;
class ASTSubExpressionExprNode;
class ASTUnaryExprNode;
class ASTVariableDeclStmtNode;
class ASTWhileStmtNode;
class ASTExpression_Node;


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
