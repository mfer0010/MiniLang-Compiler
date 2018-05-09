//
// Created by marc on 09/05/2018.
//

#ifndef MINILANG_COMPILER_SEMANTICANALYSEREXCEPTION_H
#define MINILANG_COMPILER_SEMANTICANALYSEREXCEPTION_H


#include "MiniLangExceptions.h"

class SemanticAnalyserException : public MiniLangExceptions {
public:
    SemanticAnalyserException(std::string);

    virtual std::string printMessage();
};


#endif //MINILANG_COMPILER_SEMANTICANALYSEREXCEPTION_H
