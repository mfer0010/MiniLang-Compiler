//
// Created by marc on 23/04/2018.
//

#ifndef MINILANG_COMPILER_PARSER_H
#define MINILANG_COMPILER_PARSER_H

#include "Lexer.h"
#include "ASTExpression_Node.h"
#include "ASTNumberExprNode.h"
#include "ASTBinaryExprNode.h"
#include "ASTStatement_Node.h"
#include "ASTVariableDeclStmtNode.h"
#include "ASTAssignmentStmtNode.h"
#include "ASTPrintStmtNode.h"
#include "ASTIfStmtNode.h"
#include "ASTWhileStmtNode.h"
#include "ASTReturnStmtNode.h"
#include "ASTFuncDeclStmtNode.h"
#include "ASTBlockStmtNode.h"
#include "ASTLiteralExprNode.h"
#include "ASTFunctionCallExprNode.h"


class Parser {

public:
    Parser(Lexer *);

    std::vector<ASTStatement_Node *> parse();
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
    void parseFormalParams(std::vector<ASTFormalParamStmtNode *> &);

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

    //<FunctionCall> ::= <Identifier> '(' [<ActualParams>] ')'
    ASTFunctionCallExprNode *parseFunctionCall();

    //<ActualParams> ::= <Expression> {',' <Expression>}
    void parseActualParams(std::vector<ASTExpression_Node *> &);

    /*<Literal> ::= <BooleanLiteral>
     *          | <IntegerLiteral>
     *          | <RealLiteral>
     *          | <StringLiteral>
    */
    ASTLiteralExprNode *parseLiteral();

//    ASTNumberExprNode *parseUnaryExpression();
//
//    ASTBinaryExprNode *parseBinaryExpression();
};


#endif //MINILANG_COMPILER_PARSER_H
