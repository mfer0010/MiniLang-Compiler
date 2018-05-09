//
// Created by marc on 01/05/2018.
//

#include "include/XMLVisitor.h"
#include "include/Exceptions/VisitorException.h"
#include "include/ASTNode.h"
#include "include/ASTAssignmentStmtNode.h"
#include "include/ASTBinaryExprNode.h"
#include "include/ASTBlockStmtNode.h"
#include "include/ASTBooleanLiteralExprNode.h"
#include "include/Token.h"
#include "include/ASTFormalParamStmtNode.h"
#include "include/ASTFuncDeclStmtNode.h"
#include "include/ASTFunctionCallExprNode.h"
#include "include/ASTIdentifierExprNode.h"
#include "include/ASTIfStmtNode.h"
#include "include/ASTIntegerLiteralExprNode.h"
#include "include/ASTPrintStmtNode.h"
#include "include/ASTRealLiteralExprNode.h"
#include "include/ASTReturnStmtNode.h"
#include "include/ASTStringLiteralExprNode.h"
#include "include/ASTSubExpressionExprNode.h"
#include "include/ASTUnaryExprNode.h"
#include "include/ASTVariableDeclStmtNode.h"
#include "include/ASTWhileStmtNode.h"

XMLVisitor::XMLVisitor() {}

XMLVisitor::~XMLVisitor() {}

std::string XMLVisitor::getIndentation() {
    std::string indentation = "";
    for (int i = 0; i < indentationNo; i++) {
        indentation.append("\t");
    }
    return indentation;
}

std::string XMLVisitor::printOperator(std::string _operator) {
    if (_operator.compare("<") == 0) {
        return "&lt;";
    } else if (_operator.compare(">") == 0) {
        return "&gt;";
    } else if (_operator.compare("<=") == 0) {
        return "&lt;=";
    } else if (_operator.compare(">=") == 0) {
        return "&gt;=";
    } else {
        return _operator;
    }
}

void XMLVisitor::printExpression(ASTExpression_Node * node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Expression>" << std::endl;

    indentationNo++;
    node->accept(this);
    indentationNo--;

    XMLFileOutput << indent << "</Expression>" << std::endl;
}

void XMLVisitor::visit(ASTAssignmentStmtNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Assignment>" << std::endl;

    indentationNo ++;
    indent = getIndentation();
    XMLFileOutput << indent << "<Identifier>" << node->identifier << "</Identifier>" << std::endl;
    printExpression(node->expression);
    indentationNo --;

    indent = getIndentation();
    XMLFileOutput << indent << "</Assignment>" << std::endl;
}

void XMLVisitor::visit(ASTBinaryExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<BinaryExprNode op=\"" << printOperator(node->_operator) << "\">" << std::endl;

    indentationNo ++;
    node->LHS->accept(this);
    node->RHS->accept(this);
    indentationNo --;

    XMLFileOutput << indent << "</BinaryExprNode>" << std::endl;
}

void XMLVisitor::visit(ASTBlockStmtNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Block>" << std::endl;

    indentationNo++;
    for (auto const &statement : node->statements) {
        statement->accept(this);
    }
    indentationNo--;

    XMLFileOutput << indent << "</Block>" << std::endl;
}

void XMLVisitor::visit(ASTBooleanLiteralExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Boolean>" << node->literalValue << "</Boolean>" << std::endl;
}

void XMLVisitor::visit(ASTFormalParamStmtNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<FormalParam type=\"" << node->type << "\">" << std::endl;

    indentationNo++;
    indent = getIndentation();
    XMLFileOutput << indent << "<Identifier>" << node->identifier << "</Identifier>" << std::endl;
    indentationNo--;

    indent = getIndentation();
    XMLFileOutput << indent << "</FormalParam>" << std::endl;
}

void XMLVisitor::visit(ASTFuncDeclStmtNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<FuncDecl type=\"" << node->type << "\">" << std::endl;

    indentationNo++;
    indent = getIndentation();
    XMLFileOutput << indent << "<Identifier>" << node->identifier << "</Identifier>" << std::endl;

    XMLFileOutput << indent << "<FormalParams>" << std::endl;
    indentationNo++;
    for (auto const &formalParameter : node->formalParams) {
        formalParameter->accept(this);
    }
    indentationNo--;
    XMLFileOutput << indent << "</FormalParams>" << std::endl;

    node->block->accept(this);
    indentationNo--;

    indent = getIndentation();
    XMLFileOutput << indent << "</FuncDecl>" << std::endl;
}

void XMLVisitor::visit(ASTFunctionCallExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<FunctionCall>" << std::endl;

    indentationNo++;
    indent = getIndentation();
    XMLFileOutput << indent << "<Identifier>" << node->identifier << "</Identifier>" << std::endl;
    XMLFileOutput << indent << "<ActualParams>" << std::endl;

    indentationNo++;
    for (auto const &param : node->actualParams) {
        param->accept(this);
    }
    indentationNo--;

    XMLFileOutput << indent << "</ActualParams>" << std::endl;

    indentationNo--;
    indent = getIndentation();
    XMLFileOutput << indent << "</FunctionCall>" << std::endl;
}

void XMLVisitor::visit(ASTIdentifierExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Identifier>" << node->identifier << "</Identifier>" << std::endl;
}

void XMLVisitor::visit(ASTIfStmtNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<IfStmt>" << std::endl;
    printExpression(node->expression);

    indentationNo++;
    node->ifBlock->accept(this);
    if (node->elseBlock != nullptr) {
        node->elseBlock->accept(this);
    }
    indentationNo--;
    XMLFileOutput << indent << "</IfStmt>" << std::endl;
}

void XMLVisitor::visit(ASTIntegerLiteralExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Integer>" << node->literalValue << "</Integer>" << std::endl;
}

void XMLVisitor::visit(ASTNode *node) {
    indentationNo = 0;
    try {
        XMLFileOutput.open("../AST.xml", std::ofstream::out | std::ofstream::trunc);
    } catch (std::exception &e) {
        throw VisitorException("Error Opening File:\n" + *e.what());
    }

    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Program>" << std::endl;

    indentationNo++;
    for (auto const &statement : node->statements) {
        statement->accept(this);
    }
    indentationNo--;

    XMLFileOutput << indent << "</Program>" << std::endl;
    XMLFileOutput.close();
}

void XMLVisitor::visit(ASTNumberExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Number type=\"" << node->type << "\">" << node->value << "</Number>" << std::endl;
}

void XMLVisitor::visit(ASTPrintStmtNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<PrintStmt>" << std::endl;

    indentationNo++;
    printExpression(node->expression);
    indentationNo--;

    XMLFileOutput << indent << "</PrintStmt>" << std::endl;
}

void XMLVisitor::visit(ASTRealLiteralExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Real>" << node->literalValue << "</Real>" << std::endl;
}

void XMLVisitor::visit(ASTReturnStmtNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<ReturnStmt>" << std::endl;

    indentationNo ++;
    printExpression(node->expression);
    indentationNo --;

    XMLFileOutput << indent << "</ReturnStmt>" << std::endl;
}

void XMLVisitor::visit(ASTStringLiteralExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<String>" << node->literalValue << "</String>" << std::endl;
}

void XMLVisitor::visit(ASTSubExpressionExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<SubExpression>" << std::endl;

    indentationNo ++;
    node->expression->accept(this);
    indentationNo --;

    XMLFileOutput << indent << "</SubExpression>" << std::endl;
}

void XMLVisitor::visit(ASTUnaryExprNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<Unary op=\"" << node->prefix << "\">" << std::endl;

    indentationNo++;
    node->expression->accept(this);
    indentationNo--;

    XMLFileOutput << indent << "</Unary>" << std::endl;
}

void XMLVisitor::visit(ASTVariableDeclStmtNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<VariableDecl type=\"" << node->type << "\">" << std::endl;

    indentationNo++;
    indent = getIndentation();
    XMLFileOutput << indent << "<Identifier>" << node->identifier << "</Identifier>" << std::endl;
    printExpression(node->expression);
    indentationNo--;

    indent = getIndentation();
    XMLFileOutput << indent << "</VariableDecl>" << std::endl;
}

void XMLVisitor::visit(ASTWhileStmtNode *node) {
    std::string indent = getIndentation();
    XMLFileOutput << indent << "<WhileStmt>" << std::endl;
    printExpression(node->expression);

    indentationNo ++;
    node->block->accept(this);
    indentationNo --;
    XMLFileOutput << indent << "</WhileStmt>" << std::endl;
}