//
// Created by marc on 23/04/2018.
//

#ifndef MINILANG_COMPILER_PARSER_H
#define MINILANG_COMPILER_PARSER_H

#include "Lexer.h"
#include "ASTNodes/ASTExpression_Node.h"
#include "ASTNodes/ASTNumberExprNode.h"
#include "ASTNodes/ASTBinaryExprNode.h"


class Parser {

public:
    Parser(Lexer *);

    //std::vector<ASTStatement_Node *> parse();
    void parse();
private:
    Lexer * lexer;

    Token currentToken = Token(TOK_Skip);


    /* Uses ParseUnaryExpression and Parse Binary Expression to
     * parse any expression and take care of operator precedence */
    ASTExpression_Node * parseExpression();

    ASTNumberExprNode * parseUnaryExpression();

    ASTBinaryExprNode * parseBinaryExpression();
};


#endif //MINILANG_COMPILER_PARSER_H
