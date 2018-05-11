//
// Created by marc on 11/05/2018.
//

#include "InterpreterException.h"

InterpreterException::InterpreterException(std::string _message) {
    this->error = _message;
}

std::string InterpreterException::printMessage() {
    return "Interpreter Exceptions:\n\t" + error;
}