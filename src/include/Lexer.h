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
    SE = -1 //Error state
};

enum CLASSIFIER {
    END_OF_File = 0,
    DIGIT = 1,
    DECIMAL_POINT = 2,
    INVERTED_COMMA = 3,
    PRINTABLE = 4,
    UNDERSCORE = 5,
    LETTER = 6,
    OTHER = 7
};

class Lexer {

public:
    //static std::ifstream src;

    std::string error;

    Lexer(); //constructor
    ~Lexer(); //destructor

    /*
     * Function to read program input from file using an input file stream.
     */
    void scanner(std::string);

    Token nextToken();

private:
    std::string program = '\0';
    unsigned int programPointer = 0;

    static STATE transitionTable[8][8] = {
            //{EOF,[0-9],.,",<printable>,_,<letter>,OTHER}
            {S1,S2,SE,S5,SE,S7,S7,SE},//S0
            {SE,SE,SE,SE,SE,SE,SE,SE},//S1
            {SE,S2,S3,SE,SE,SE,SE,SE},//S2
            {SE,S4,SE,SE,SE,SE,SE,SE},//S3
            {SE,S4,SE,SE,SE,SE,SE,SE},//S4
            {SE,SE,SE,S6,S5,SE,SE,SE},//S5
            {SE,SE,SE,SE,SE,SE,SE,SE},//S6
            {SE,S7,SE,SE,SE,S7,S7,SE},//S7
    };

    bool isFinalState(STATE);

    int toClassifier(char);

    Token toToken(std::string,STATE);

    //Checks if word is a keyword and return that keyword token,
    // if not return identifier token
    Token determineIDToken(std::string);

    char getNextChar(size_t);
};

#endif //MINILANG_COMPILER_LEXER_H