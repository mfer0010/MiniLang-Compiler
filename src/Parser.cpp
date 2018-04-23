//
// Created by marc on 23/04/2018.
//

#include "include/Parser.h"

Parser::Parser(Lexer * lexer) {
    this->lexer = lexer;
}

//ASTExpression_Node* Parser::parseExpression() {
//
//}

ASTNumberExprNode* Parser::parseUnaryExpression() {
    switch(currentToken.token_name) {
        case TOK_Number:
            return new ASTNumberExprNode(currentToken.numerical_value, currentToken.string_value);
        default:
            return nullptr;
    }
}

//ASTBinaryExprNode* Parser::parseBinaryExpression() {
//
//}