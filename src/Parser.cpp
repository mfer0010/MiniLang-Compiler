//
// Created by marc on 23/04/2018.
//

#include "include/Parser.h"
#include "include/Exceptions/MiniLangExceptions.h"
#include "include/Exceptions/ParserException.h"


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
    //std::cout << Node->LHS->value << Node->_opertor << Node->RHS->value;
}

//ASTExpression_Node* Parser::parseExpression() {
//    TOKEN acceptedTokens [] = {TOK_Number, TOK_MultiplicativeOp, TOK_RelationalOp,TOK_AdditiveOp,TOK_Identifier};
//    TOKEN *found = acceptedTokens;
//
//    ASTExpression_Node *toReturn;
//
//    //loop until the next token is not in acceptedTokens:
//    while (found != std::end(acceptedTokens)) {
//        currentToken = lexer->nextToken();
//        switch (currentToken.token_name) {
//            case TOK_Number:
//                try {
////                    ASTBinaryExprNode * = parseBinaryExpression();
////                    toReturn.
//                } catch (ParserException &e) {
//                    throw e;
//                }
//            case TOK_MultiplicativeOp:
//            case TOK_AdditiveOp:
//            case TOK_RelationalOp:
//            case TOK_Identifier:
//        }
//
//        found = std::find(acceptedTokens, std::end(acceptedTokens),lexer->oneTokenLookahead().token_name);
//    }
//}

ASTExpression_Node *Parser::parseExpression() {

    //First we parse the binary expression
    ASTBinaryExprNode *binaryExpression = parseBinaryExpression();

    //then we see if there's more to parse
    TOKEN lookahead = lexer->oneTokenLookahead().token_name;
    bool loop = lookahead == TOK_MultiplicativeOp || lookahead == TOK_AdditiveOp;
    while(loop) {
        //if multiplicative op, do that first
        if (lookahead == TOK_MultiplicativeOp) {

        } else {
            //else do it after
        }

        lookahead = lexer->oneTokenLookahead().token_name;
        loop = lookahead == TOK_MultiplicativeOp || lookahead == TOK_AdditiveOp;
    }
}

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