//
// Created by marc on 27/03/2018.
//
#ifndef MINILANG_COMPILER_LEXER_H
#define MINILANG_COMPILER_LEXER_H

#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include "Token.h"

enum STATE {
    S0 = 0,
    S1 = 1,
    S2 = 2,
    S3 = 3,
    S4 = 4,
    S5 = 5,
    S6 = 6,
    S7 = 7,
    S8 = 8,
    S9 = 9,
    S10 = 10,
    S11 = 11,
    S12 = 12,
    S13 = 13,
    S14 = 14,
    S15 = 15,
    SE = 16 //Error state
};

enum CLASSIFIER {
    END_OF_File = 0,
    DIGIT = 1,
    DECIMAL_POINT = 2,
    INVERTED_COMMA = 3,
    PRINTABLE = 4,
    UNDERSCORE = 5,
    LETTER = 6,
    GREATER_LESSTHAN = 7,
    EXCLEMATION = 8,
    EQUALS = 9,
    SLASH = 10,
    NEW_LINE = 11,
    STAR = 12,
    END_COMMENT = 13,
    OPERATORS = 14,
    OTHER = 15 //Some symbol not recognised by the language
};

class Lexer {

public:
    //static std::ifstream src;

    std::string error = "";

    Lexer(); //constructor
    ~Lexer(); //destructor

    /*
     * Function to read program input from file using an input file stream.
     */
    void scanner(std::string);

    Token nextToken();

    Token oneTokenLookahead();

    int getErrorLine();

private:
    std::string program = "EMPTY";
    unsigned int programPointer = 0;

    STATE transitionTable[17][16] = {
            {S1,S2,SE,S5,SE,S7,S7,S8,S10,S8,S12,S14,S11,S11,S11,SE},
            {SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE},
            {SE,S2,S3,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE},
            {SE,S4,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE},
            {SE,S4,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE},
            {SE,S5,S5,S6,S5,S5,S5,S5,S5,S5,S5,S5,S5,S5,S5,SE},
            {SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE},
            {SE,S7,SE,SE,SE,S7,S7,SE,SE,SE,SE,SE,SE,SE,SE,SE},
            {SE,SE,SE,SE,SE,SE,SE,SE,SE,S9,SE,SE,SE,SE,SE,SE},
            {SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE},
            {SE,SE,SE,SE,SE,SE,SE,SE,SE,S9,SE,SE,SE,SE,SE,SE},
            {SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE},
            {SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,S13,SE,S15,S15,SE,SE},
            {SE,S13,S13,S13,S13,S13,S13,S13,S13,S13,S13,S14,S13,S13,S13,S13},
            {SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE},
            {SE,S15,S15,S15,S15,S15,S15,S15,S15,S15,S15,S15,S15,S14,S15,S15},
            {SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE,SE}
    };

    bool isFinalState(STATE);

    int toClassifier(char);

    Token toToken(std::string,STATE);

    //Checks if word is a keyword and return that keyword token,
    // if not return identifier token
    Token determineIDToken(std::string);

    //Returns either a > , < or = token
    Token determineOperatorToken(std::string);

    //Returns the correct token for one of the following:
    //* + - { } ( ) , : ;
    Token determineOthersToken(std::string);

    char getNextChar(size_t);

};

#endif //MINILANG_COMPILER_LEXER_H