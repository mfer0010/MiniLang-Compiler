//
// Created by marc on 09/05/2018.
//

#include "SemanticAnalyserException.h"


SemanticAnalyserException::SemanticAnalyserException(std::string _message){
    this->error = _message;
}

std::string SemanticAnalyserException::printMessage() {
    return "Semantic Analyser Exception:\n\t" + error;
}