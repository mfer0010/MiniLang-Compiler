//
// Created by marc on 24/04/2018.
//

#include "include/ParserException.h"

ParserException::ParserException() {}

ParserException::ParserException(std::string _message) {
    this->error = _message;
}

std::string ParserException::printMessage() {
    return error;
}