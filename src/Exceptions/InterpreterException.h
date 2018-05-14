//
// Created by marc on 11/05/2018.
//

#ifndef MINILANG_COMPILER_INTERPRETEREXCEPTION_H
#define MINILANG_COMPILER_INTERPRETEREXCEPTION_H


#include "MiniLangExceptions.h"

class InterpreterException : public MiniLangExceptions {
public:
    InterpreterException(std::string);

    virtual std::string printMessage();
};


#endif //MINILANG_COMPILER_INTERPRETEREXCEPTION_H
