//
// Created by marc on 24/04/2018.
//

#ifndef MINILANG_COMPILER_LEXEREXCEPTION_H
#define MINILANG_COMPILER_LEXEREXCEPTION_H

#include "MiniLangExceptions.h"

class ParserException : public MiniLangExceptions {
public:
    int lineNo = 0;

    ParserException();

    ParserException(std::string, int);

    virtual std::string printMessage();
};


#endif //MINILANG_COMPILER_LEXEREXCEPTION_H
