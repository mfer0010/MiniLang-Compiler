//
// Created by marc on 01/05/2018.
//

#include "include/Exceptions/VisitorException.h"

VisitorException::VisitorException(std::string _message) {
    this->error = _message;
}

std::string VisitorException::printMessage() {
    return "Visitor Exception:\n\t" + error;
}