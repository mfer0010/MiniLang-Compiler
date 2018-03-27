//
// Created by marc on 27/03/2018.
//
#ifndef MINILANG_COMPILER_LEXER_H
#define MINILANG_COMPILER_LEXER_H

#include <string>
#include <fstream>
#include <iostream>

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

};

#endif //MINILANG_COMPILER_LEXER_H