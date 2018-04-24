//
// Created by marc on 24/04/2018.
//

#ifndef MINILANG_COMPILER_MINILANGEXCEPTIONS_H
#define MINILANG_COMPILER_MINILANGEXCEPTIONS_H

#include <string>

class MiniLangExceptions {
public:
    std::string error = "Error in Code! Compiler Failed to Compile!";

    virtual std::string printMessage() = 0;
};

#endif //MINILANG_COMPILER_MINILANGEXCEPTIONS_H
