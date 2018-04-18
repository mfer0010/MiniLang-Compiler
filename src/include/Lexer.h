//
// Created by marc on 27/03/2018.
//
#ifndef MINILANG_COMPILER_LEXER_H
#define MINILANG_COMPILER_LEXER_H

#include <string>
#include <fstream>
#include <iostream>
#include <stack>

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

class Lexer {

public:
    static std::ifstream src;

    Lexer(); //constructor
    ~Lexer(); //destructor

    /*
     * Function to read program input from file using an input file stream.
     */
    void scanner(std::string);

    void nextToken();

private:
    static STATE transitionTable[8][8] = {
            //{EOF,[0-9],.,",",<printable>,_,<letter>}
            {S1,S2,SE,S5,SE,SE,S7,S7},//S0
            {SE,SE,SE,SE,SE,SE,SE,SE},//S1
            {SE,S2,S3,SE,SE,SE,SE,SE},//S2
            {SE,S4,SE,SE,SE,SE,SE,SE},//S3
            {SE,S4,SE,SE,SE,SE,SE,SE},//S4
            {SE,SE,SE,SE,S6,S5,SE,SE},//S5
            {SE,SE,SE,SE,SE,SE,SE,SE},//S6
            {SE,S7,SE,SE,SE,SE,S7,S7},//S7
    };

    bool isFinalState(STATE);
};

#endif //MINILANG_COMPILER_LEXER_H