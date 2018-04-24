//
// Created by marc on 24/04/2018.
//

#include "include/LexerException.h"

LexerException::LexerException(std::string _message, int line_no) {
    this->error = _message;
    this->lineNo = line_no;
}

LexerException::LexerException(int line_no) {
    this -> lineNo = line_no;
}

std::string LexerException::printMessage() {
    std::string message;
    message.append(error);
    message.append("\nLine:");
    message.append(std::to_string(lineNo));
    return message;
}