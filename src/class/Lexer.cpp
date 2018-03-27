//
// Created by marc on 27/03/2018.
//

#include "../include/Lexer.h"
#include "../include/Exceptions/FileNotFound.h"

Lexer::Lexer() {}

Lexer::~Lexer() {
    try {
        Lexer::src.close();
    } catch (std::exception &e) {
        std::cerr << "Error Closing File";
    }
}

void scanner(std::string path) {
    Lexer::src.open(path);

    //check that the file was opened, if not throw error
    if (!Lexer::src) {
        throw(FileNotFound::FileNotFound());
    }
}