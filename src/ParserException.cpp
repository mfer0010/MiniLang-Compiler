//
// Created by marc on 24/04/2018.
//

#include "include/ParserException.h"

ParserException::ParserException() {}

ParserException::ParserException(std::string _message, int lineNo) {
    this->error = _message;
    this->lineNo = lineNo;
}

std::string ParserException::printMessage() {
    return "Parser Error:\n\t"+error+"\n\tLine: "+std::to_string(lineNo);
}