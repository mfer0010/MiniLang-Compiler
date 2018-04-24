//
// Created by marc on 23/04/2018.
//

#include "include/Parser.h"
#include "include/MiniLangExceptions.h"
#include "include/ParserException.h"


Parser::Parser(Lexer * lexer) {
    this->lexer = lexer;
}

void Parser::parse() {
    ASTBinaryExprNode *Node;
    try {
        Node = parseBinaryExpression();
    } catch(MiniLangExceptions &e) {
        std::cout << e.printMessage() << std::endl;
        throw -1;
    }
    std::cout << Node->LHS << Node->_opertor << Node->RHS;
}

//ASTExpression_Node* Parser::parseExpression() {
//
//}

ASTNumberExprNode* Parser::parseUnaryExpression() {
    switch(currentToken.token_name) {
        case TOK_Number:
            return new ASTNumberExprNode(currentToken.numerical_value, currentToken.string_value);
        default:
            throw ParserException("Expected Unary Expression",lexer->getErrorLine());
    }
}

ASTBinaryExprNode* Parser::parseBinaryExpression() {
    currentToken = lexer->nextToken();

    ASTNumberExprNode *LHS;
    ASTNumberExprNode *RHS;
    std::string _operator;

    TOKEN opToken = lexer->oneTokenLookahead().token_name;
    if (opToken == TOK_MultiplicativeOp || opToken == TOK_AdditiveOp) {
        LHS = parseUnaryExpression();

        currentToken = lexer->nextToken();
        _operator = currentToken.string_value;

        currentToken = lexer->nextToken();
        RHS = parseUnaryExpression();

        return new ASTBinaryExprNode(_operator, LHS, RHS);
    }
    throw ParserException("Expected Binary Expression", lexer->getErrorLine());
}