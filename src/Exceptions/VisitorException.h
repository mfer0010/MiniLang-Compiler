//
// Created by marc on 01/05/2018.
//

#ifndef MINILANG_COMPILER_VISITOREXCEPTION_H
#define MINILANG_COMPILER_VISITOREXCEPTION_H

#include "MiniLangExceptions.h"

class VisitorException : public MiniLangExceptions {
public:
    VisitorException(std::string);

    virtual std::string printMessage();
};

#endif //MINILANG_COMPILER_VISITOREXCEPTION_H
