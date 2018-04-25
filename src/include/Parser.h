//
// Created by marc on 23/04/2018.
//

#ifndef MINILANG_COMPILER_PARSER_H
#define MINILANG_COMPILER_PARSER_H

#include "Lexer.h"
#include "ASTNodes/ASTExpression_Node.h"
#include "ASTNodes/ASTNumberExprNode.h"
#include "ASTNodes/ASTBinaryExprNode.h"
#include "ASTNodes/ASTStatement_Node.h"
#include "ASTNodes/ASTVariableDeclStmtNode.h"
#include "ASTNodes/ASTAssignmentStmtNode.h"
#include "ASTNodes/ASTPrintStmtNode.h"
#include "ASTNodes/ASTIfStmtNode.h"
#include "ASTNodes/ASTWhileStmtNode.h"
#include "ASTNodes/ASTReturnStmtNode.h"
#include "ASTNodes/ASTFuncDeclStmtNode.h"
#include "ASTNodes/ASTBlockStmtNode.h"


class Parser {

public:
    Parser(Lexer *);

    //std::vector<ASTStatement_Node *> parse();
    void parse();
private:
    Lexer * lexer;

    Token currentToken = Token(TOK_Skip);

    /*
     * Function to Parse a statement.
     * According to EBNF:
     * <Statement> ::= <VariableDecl>;
     *              | <Assignment>;
     *              | <PrintStatement>;
     *              | <IfStatement>
     *              | <WhileStatement>
     *              | <ReturnStatement>;
     *              | <FunctionDecl>
     *              | <Block>
     */
    ASTStatement_Node *parseStatement();

    //<VariableDecl> ::= 'var' <Identifier> '=' <Expression>
    ASTVariableDeclStmtNode *parseVariableDecl();

    //<Assignment> ::= 'set' <Identifier> '=' <Expression>
    ASTAssignmentStmtNode *parseAssignment();

    //<PrintStatement> ::= 'print' ,Expression
    ASTPrintStmtNode *parsePrintStatement();

    //<IfStatement> ::= 'if' '(' <Expression> ')' <Block> ['else' <Block>]
    ASTIfStmtNode *parseIfStatement();

    //<WhileStatement> ::= 'while' '(' <Expression> ')' <Block>
    ASTWhileStmtNode *parseWhileStatement();

    //<ReturnStatement> ::= 'return' <Expression>
    ASTReturnStmtNode *parseReturnStatement();

    //<FunctionDecl> ::= 'def' <Identifier> '('[<FormalParams>]')' ':' <Type> <Block>
    ASTFuncDeclStmtNode *parseFunctionDeclStatement();

    //<Block> ::= '{' {<Statement>} '}'
    ASTBlockStmtNode *parseBlock();

    //<Expression> ::= <SimpleExpression> {<RelationalOp> <SimpleExpression>}
    ASTExpression_Node *parseExpression();

    //<FormalParams> ::= <FormalParam> {',' <FormalParam>}
    std::vector<ASTFormalParamStmtNode *> parseFormalParams();

    //<FormalParam> ::= <Identifier> ':' <Type>
    ASTFormalParamStmtNode *parseFormalParam();

    //<SimpleExpression> ::= <Term> {<AdditiveOp> <Term>}
    ASTExpression_Node *parseSimpleExpression();

    //<Term> ::= <Factor> {<MultiplicativeOp> <Factor>}
    ASTExpression_Node *parseTerm();

    /* <Factor> ::= <Literal>
     *          | <Identifier>
     *          | <FunctionCall>
     *          | <SubExpression>
     *          | <Unary>
     */
    ASTExpression_Node *parseFactor();

//    ASTNumberExprNode *parseUnaryExpression();
//
//    ASTBinaryExprNode *parseBinaryExpression();
};


#endif //MINILANG_COMPILER_PARSER_H
