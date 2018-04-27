//
// Created by marc on 23/04/2018.
//

#include "include/Parser.h"
#include "include/Exceptions/ParserException.h"
#include "include/ASTNodes/ASTBooleanLiteralExprNode.h"
#include "include/ASTNodes/ASTIntegerLiteralExprNode.h"
#include "include/ASTNodes/ASTRealLiteralExprNode.h"
#include "include/ASTNodes/ASTStringLiteralExprNode.h"
#include "include/ASTNodes/ASTIdentifierExprNode.h"
#include "include/ASTNodes/ASTUnaryExprNode.h"
#include "include/ASTNodes/ASTSubExpressionExprNode.h"


Parser::Parser(Lexer * lexer) {
    this->lexer = lexer;
}

std::vector<ASTStatement_Node *> Parser::parse() {
    std::vector<ASTStatement_Node *> statementNodes;
    while (lexer->oneTokenLookahead().token_name != TOK_EOF) {
        statementNodes.push_back(parseStatement());
    }
    return statementNodes;
}

ASTStatement_Node * Parser::parseStatement() {
    currentToken = lexer->oneTokenLookahead();
    switch (currentToken.token_name) {
        case TOK_Var:
            currentToken = lexer->nextToken();
            return parseVariableDecl();
        case  TOK_Set:
            currentToken = lexer->nextToken();
            return parseAssignment();
        case TOK_Print:
            currentToken = lexer->nextToken();
            return parsePrintStatement();
        case TOK_If:
            currentToken = lexer->nextToken();
            return parseIfStatement();
        case TOK_While:
            currentToken = lexer->nextToken();
            return parseWhileStatement();
        case TOK_Return:
            currentToken = lexer->nextToken();
            return parseReturnStatement();
        case TOK_Def:
            currentToken = lexer->nextToken();
            return parseFunctionDeclStatement();
        case TOK_LeftBrace:
            return parseBlock();
        default:
            throw ParserException("Expected Statement Token",lexer->getErrorLine());
    }
}

ASTVariableDeclStmtNode * Parser::parseVariableDecl() {
    currentToken = lexer->nextToken(); //<Identifier>
    if (currentToken.token_name != TOK_Identifier) {
        throw ParserException("Expected Identifier Token",lexer->getErrorLine());
    }
    std::string identifier = currentToken.string_value;

    currentToken = lexer->nextToken();// ':'
    if (currentToken.token_name != TOK_Colon) {
        throw ParserException("Expected Colon Token",lexer->getErrorLine());
    }

    currentToken = lexer->nextToken(); //<Type>
    if (currentToken.token_name != TOK_Type) {
        throw ParserException("Expected Type Token",lexer->getErrorLine());
    }
    std::string type = currentToken.string_value;

    currentToken = lexer->nextToken(); //'='
    if (currentToken.token_name != TOK_Equals) {
        throw ParserException("Expected Equals Token",lexer->getErrorLine());
    }

    //<Expression> (nextToken will be called in parseExpression Function)
    ASTExpression_Node *expression = parseExpression();

    currentToken = lexer->nextToken();//';'
    if (currentToken.token_name != TOK_SemiColon) {
        throw ParserException("Expected SemiColon Token",lexer->getErrorLine());
    }

    return new ASTVariableDeclStmtNode(identifier,type,expression);
}

ASTAssignmentStmtNode * Parser::parseAssignment() {
    currentToken = lexer->nextToken(); //<Identifier>
    if(currentToken.token_name != TOK_Identifier) {
        throw ParserException("Expected Identifier Token",lexer->getErrorLine());
    }
    std::string identifier = currentToken.string_value;

    currentToken = lexer->nextToken();//'='
    if (currentToken.token_name != TOK_Equals) {
        throw ParserException("Expected Equals Token",lexer->getErrorLine());
    }

    //<Expression>
    ASTExpression_Node *expression = parseExpression();

    currentToken = lexer->nextToken();//';'
    if (currentToken.token_name != TOK_SemiColon) {
        throw ParserException("Expected Semicolon Token",lexer->getErrorLine());
    }

    return new ASTAssignmentStmtNode(identifier,expression);
}

ASTPrintStmtNode * Parser::parsePrintStatement() {
    //<Expression>
    ASTExpression_Node *expression = parseExpression();

    currentToken = lexer->nextToken();//';'
    if (currentToken.token_name != TOK_SemiColon) {
        throw ParserException("Expected SemiColon Token",lexer->getErrorLine());
    }

    return new ASTPrintStmtNode(expression);
}

ASTIfStmtNode * Parser::parseIfStatement() {
    currentToken = lexer->nextToken();//'('
    if (currentToken.token_name != TOK_LeftBracket) {
        throw ParserException("Expected LeftBracket Token",lexer->getErrorLine());
    }

    //<Expression>
    ASTExpression_Node *expression = parseExpression();

    currentToken = lexer->nextToken(); //')'
    if (currentToken.token_name != TOK_RightBracket) {
        throw ParserException("Expected RightBracket Token",lexer->getErrorLine());
    }

    //<Block>
    ASTBlockStmtNode *block1 = parseBlock();

    if (lexer->oneTokenLookahead().token_name == TOK_Else) {
        currentToken = lexer->nextToken(); //'else'

        //<Block>
        ASTBlockStmtNode *block2 = parseBlock();

        return new ASTIfStmtNode(expression,block1,block2);
    }

    return new ASTIfStmtNode(expression, block1);
}

ASTWhileStmtNode * Parser::parseWhileStatement() {
    currentToken = lexer->nextToken();//'('
    if (currentToken.token_name != TOK_LeftBracket) {
        throw ParserException("Expected LeftBracket Token",lexer->getErrorLine());
    }

    //<Expression>
    ASTExpression_Node *expression = parseExpression();

    currentToken = lexer->nextToken(); //')'
    if (currentToken.token_name != TOK_RightBracket) {
        throw ParserException("Expected RightBracket Token",lexer->getErrorLine());
    }

    //<Block>
    ASTBlockStmtNode *block = parseBlock();

    return new ASTWhileStmtNode(expression,block);
}

ASTReturnStmtNode * Parser::parseReturnStatement() {
    //<Expression>
    ASTExpression_Node *expression = parseExpression();

    currentToken = lexer->nextToken();//';'
    if (currentToken.token_name != TOK_SemiColon) {
        throw ParserException("Expected Semicolon Token",lexer->getErrorLine());
    }

    return new ASTReturnStmtNode(expression);
}

ASTFuncDeclStmtNode * Parser::parseFunctionDeclStatement() {
    currentToken = lexer->nextToken();//<Identifier>
    if (currentToken.token_name != TOK_Identifier) {
        throw ParserException("Expected Identifier Token",lexer->getErrorLine());
    }
    std::string identifier = currentToken.string_value;

    currentToken = lexer->nextToken();//'('
    if (currentToken.token_name != TOK_LeftBracket) {
        throw ParserException("Expected LeftBracket Token",lexer->getErrorLine());
    }

    std::vector<ASTFormalParamStmtNode *> formalParams;
    if (lexer->oneTokenLookahead().token_name != TOK_RightBracket) {
        //<FormalParams>
        parseFormalParams(formalParams);
    }

    currentToken = lexer->nextToken();//')'
    if (currentToken.token_name != TOK_RightBracket) {
        throw ParserException("Expected RightBracket Token",lexer->getErrorLine());
    }

    currentToken = lexer->nextToken();//':'
    if (currentToken.token_name != TOK_Colon) {
        throw ParserException("Expected Colon Token",lexer->getErrorLine());
    }

    currentToken = lexer->nextToken();//<Type>
    if (currentToken.token_name != TOK_Type) {
        throw ParserException("Expected Type Token",lexer->getErrorLine());
    }
    std::string type = currentToken.string_value;

    //<Block>
    ASTBlockStmtNode *block = parseBlock();

    return new ASTFuncDeclStmtNode(identifier,formalParams,type, block);
}

ASTBlockStmtNode * Parser::parseBlock() {
    currentToken = lexer->nextToken();//'{'
    if (currentToken.token_name != TOK_LeftBrace) {
        throw ParserException("Expected LeftBrace Token",lexer->getErrorLine());
    }

    std::vector<ASTStatement_Node *> statements;
    while(lexer->oneTokenLookahead().token_name != TOK_RightBrace) {
        statements.push_back(parseStatement());
    }

    currentToken = lexer->nextToken();//'}' has to be this, else error would have been thrown

    return new ASTBlockStmtNode(statements);
}

ASTExpression_Node * Parser::parseExpression(){
    //<SimpleExpression>
    ASTExpression_Node *simpleExpression = parseSimpleExpression();

    if (lexer->oneTokenLookahead().token_name == TOK_RelationalOp) {
        currentToken = lexer->nextToken();//<RelationalOp>
        std::string _operator = currentToken.string_value;
        //Here we shall parse expression and not simple expression since we can have one or
        //more relational operators, i.e. change ebnf to:
        //<Expression> = <SimpleExpression>|<SimpleExpression><RelationalOperator><Expression>
        ASTExpression_Node * expression = parseExpression();
        return new ASTBinaryExprNode(_operator, simpleExpression, expression);
    }
    return simpleExpression;
}

ASTExpression_Node * Parser::parseSimpleExpression() {
    //<Term>
    ASTExpression_Node * term = parseTerm();

    if (lexer->oneTokenLookahead().token_name == TOK_AdditiveOp) {
        currentToken = lexer->nextToken();//<AdditiveOp>
        std::string additiveOp = currentToken.string_value;
        //Same recursive definition as parseExpression()
        ASTExpression_Node *simpleExpression = parseSimpleExpression();
        return new ASTBinaryExprNode(additiveOp,term, simpleExpression);
    }
    return term;
}

ASTExpression_Node * Parser::parseTerm() {
    //<Factor>
    ASTExpression_Node * factor = parseFactor();

    if (lexer->oneTokenLookahead().token_name == TOK_MultiplicativeOp) {
        currentToken = lexer->nextToken();//<MultiplicativeOp>
        std::string multiplicativeOp = currentToken.string_value;
        //Usual recursive definition
        ASTExpression_Node *term = parseTerm();
        return new ASTBinaryExprNode(multiplicativeOp,factor,term);
    }
    return factor;
}

ASTExpression_Node * Parser::parseFactor() {
    /*consume token:
     *needs to be either: TOK_Bool, TOK_Number, TOK_String to return a literal;
     *TOK_Identifier to return an identifier or function call
     *TOK_LeftBracket to return a SubExpression
     *TOK_Not or TOK_AdditiveOp - to return a Unary
     */
    currentToken = lexer->nextToken();

    //if token is a '(' then it must be a sub expression
    if(currentToken.token_name == TOK_LeftBracket) {
        //<Expression>
        ASTExpression_Node * expressionNode = parseExpression();

        currentToken = lexer->nextToken();//')'
        if (currentToken.token_name != TOK_RightBracket) {
            throw ParserException("Expected Right Bracket", lexer->getErrorLine());
        }
        return new ASTSubExpressionExprNode(expressionNode);
    }

    //if token is a '-' or 'not' then it must be a unary
    if(currentToken.token_name == TOK_Not ||
       (currentToken.token_name == TOK_AdditiveOp && currentToken.string_value == "-")) {
        //<Expression>
        ASTExpression_Node * expressionNode = parseExpression();
        return new ASTUnaryExprNode(currentToken.string_value ,expressionNode);
    } else if (currentToken.token_name == TOK_AdditiveOp && currentToken.string_value != "-") {
        throw ParserException("Expected Unary Operator", lexer->getErrorLine());
    }

    //Check if token is a literal
    ASTLiteralExprNode * literal = parseLiteral();

    //if token wasn't a literal then it must be a FunctionCall or an identifier
    if (literal == nullptr) {
        if (currentToken.token_name == TOK_Identifier) {
            //could be a function call or an identifier
            ASTFunctionCallExprNode *funcCall = parseFunctionCall();
            if (funcCall != nullptr) {
                return funcCall;
            }
            return new ASTIdentifierExprNode(currentToken.string_value);
        }
        throw ParserException("Expected Factor", lexer->getErrorLine());
    } else {
        return literal;
    }
}

ASTLiteralExprNode * Parser::parseLiteral(){
    bool value;
    switch(currentToken.token_name) {
        case TOK_Bool:
            value = currentToken.string_value == "TRUE";
            return new ASTBooleanLiteralExprNode(value);
        case TOK_Number:
            if (currentToken.string_value == "INT") {
                return new ASTIntegerLiteralExprNode((int) currentToken.numerical_value);
            } else {
                return new ASTRealLiteralExprNode(currentToken.numerical_value);
            }
        case TOK_StringLiteral:
            return new ASTStringLiteralExprNode(currentToken.string_value);
    }
    return nullptr;
}

void Parser::parseFormalParams(std::vector <ASTFormalParamStmtNode *> &formalParams) {
    //<FormalParam>
    if (formalParams.size()==0) {
        formalParams.push_back(parseFormalParam());
    } else {
        currentToken = lexer->nextToken();//','
        if (currentToken.token_name != TOK_Comma) {
            throw ParserException("Expected Comma", lexer->getErrorLine());
        }
        //<FormalParam>
        formalParams.push_back(parseFormalParam());
    }
    if (lexer->oneTokenLookahead().token_name == TOK_RightBracket) {
        return;
    }
    parseFormalParams(formalParams);
}

ASTFormalParamStmtNode * Parser::parseFormalParam() {
    currentToken = lexer->nextToken(); //<Identifier>
    if (currentToken.token_name != TOK_Identifier) {
        throw ParserException("Expected Identifier Token", lexer->getErrorLine());
    }
    std::string identifier = currentToken.string_value;

    currentToken = lexer->nextToken();//':'
    if (currentToken.token_name != TOK_Colon) {
        throw ParserException("Expected Colon Token", lexer->getErrorLine());
    }

    currentToken = lexer->nextToken();//<Type>
    if (currentToken.token_name != TOK_Type) {
        throw  ParserException("Expected Type Token", lexer->getErrorLine());
    }
    std::string type = currentToken.string_value;

    return new ASTFormalParamStmtNode(identifier, type);
}

ASTFunctionCallExprNode * Parser::parseFunctionCall() {
    //current token is TOK_Identifier
    std::string identifier = currentToken.string_value;
    std::vector<ASTExpression_Node *> actualParams;
    ASTFunctionCallExprNode *functionCall = nullptr;

    if (lexer->oneTokenLookahead().token_name == TOK_LeftBracket) {
        currentToken = lexer->nextToken();//'('
        //<ActualParams>
        parseActualParams(actualParams);

        currentToken = lexer->nextToken();//')'
        if (currentToken.token_name != TOK_RightBracket) {
            throw ParserException("Expected Right Bracket",lexer->getErrorLine());
        }

        if (actualParams.empty()) {
            functionCall = new ASTFunctionCallExprNode(identifier);
        } else {
            functionCall = new ASTFunctionCallExprNode(identifier, actualParams);
        }
    }
    return functionCall;
}


void Parser::parseActualParams(std::vector<ASTExpression_Node *> &args) {
    //<Expression>
    while (lexer->oneTokenLookahead().token_name != TOK_RightBracket) {
        args.push_back(parseExpression());

        currentToken = lexer->nextToken();//','|')'
        if (currentToken.token_name != TOK_Comma &&
                currentToken.token_name != TOK_RightBracket) {
            throw ParserException("Expected Comma or Right Bracket",lexer->getErrorLine());
        }
        //currentToken = lexer->nextToken();
    }
}
