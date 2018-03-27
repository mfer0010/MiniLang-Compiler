//
// Created by marc on 27/03/2018.
//
#include <string>
#ifndef MINILANG_COMPILER_LEXER_H
#define MINILANG_COMPILER_LEXER_H

class Lexer {

public:
    Lexer(); //constructor
    ~Lexer(); //destructor
    /*
     * Function to read program input from file using an input file stream.
     * The function returns a string of lexemes.
     */
    std::string scanner(std::string path);

    void nextToken();

};

#endif //MINILANG_COMPILER_LEXER_H