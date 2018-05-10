//
// Created by marc on 27/03/2018.
//
#ifndef MINILANG_COMPILER_TOKEN_H
#define MINILANG_COMPILER_TOKEN_H

#include <iostream>

enum TOKEN {
    TOK_EOF = 0,                // '\0'
    TOK_Type = 1,               // real,int,bool or string keywords
    TOK_Bool = 2,               // 'true'|'false'
    TOK_Number = 3,             // Integer number or real number
    TOK_StringLiteral = 4,      // '"' {<Printable>} '"'
    TOK_Identifier = 5,         // ('_'|<Letter>){('_'|<Letter>|<Digit>)}
    TOK_MultiplicativeOp = 6,   // '*'|'/'|'and'
    TOK_AdditiveOp = 7,         // '+'|'-'|'or'
    TOK_RelationalOp = 8,       // '<'|'>'|'=='|'!='|'<='|'>='
    TOK_Not = 9,                // 'not'
    TOK_Set = 10,               // 'set'
    TOK_Var = 11,               // 'var'
    TOK_Print = 12,             // 'print'
    TOK_Return = 13,            // 'return'
    TOK_If = 14,                // 'if'
    TOK_Else = 15,              // 'else'
    TOK_While = 16,             // 'while'
    TOK_Def = 17,               // 'def'
    TOK_LeftBrace = 18,         // '{'
    TOK_RightBrace = 19,        // '}'
    TOK_LeftBracket = 20,       // '('
    TOK_RightBracket = 21,      // ')'
    TOK_Comma = 22,             // ','
    TOK_Colon = 23,             // ':'
    TOK_SemiColon = 24,         // ';'
    TOK_Equals = 25,            // '='
    TOK_Skip = 26,               // Used to discard comments
    TOK_Error = 27
};

const std::string TOKEN_NAME[] = {
        "TOK_EOF",
        "TOK_Type",
        "TOK_Bool",
        "TOK_Number",
        "TOK_StringLiteral",
        "TOK_Identifier",
        "TOK_MultiplicativeOp",
        "TOK_AdditiveOp",
        "TOK_RelationalOp",
        "TOK_Not",
        "TOK_Set",
        "TOK_Var",
        "TOK_Print",
        "TOK_Return",
        "TOK_If",
        "TOK_Else",
        "OK_While",
        "TOK_Def",
        "TOK_LeftBrace",
        "TOK_RightBrace",
        "TOK_LeftBracket",
        "TOK_RightBracket",
        "TOK_Comma",
        "TOK_Colon",
        "TOK_SemiColon",
        "TOK_Equals",
        "TOK_Skip",
        "TOK_Error"
};

class Token {
public:
    TOKEN token_name; //The type of token

    double numerical_value = 0; //stores any numeric value the Token is referring to
    std::string string_value = ""; //stores any text value the Token might refer to

    //constructors:
    Token(); //empty constructor initializes with TOK_Skip
    Token(TOKEN);
    //Token(TOKEN, double);
    Token(TOKEN, std::string);
    Token(TOKEN, double, std::string);

    //destructor:
    ~Token();
};
#endif //MINILANG_COMPILER_TOKEN_H
