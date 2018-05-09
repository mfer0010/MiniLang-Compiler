//
// Created by marc on 24/04/2018.
//

#ifndef MINILANG_COMPILER_PARSEREXCEPTIONS_H
#define MINILANG_COMPILER_PARSEREXCEPTIONS_H

#include "MiniLangExceptions.h"

class LexerException : public MiniLangExceptions {
public:
    int lineNo;

    LexerException(std::string, int);

    LexerException(int);

    virtual std::string printMessage();
};

#endif //MINILANG_COMPILER_PARSEREXCEPTIONS_H
