//
// Created by marc on 27/03/2018.
//

#include "include/Lexer.h"
#include "include/Exceptions/FileNotFound.h"

Lexer::Lexer() {}

Lexer::~Lexer() {
    try {
        Lexer::src.close();
    } catch (std::exception &e) {
        std::cerr << "Error Closing File";
    }
}

void Lexer::scanner(std::string path) {
    Lexer::src.open(path);

    //check that the file was opened, if not throw error
    if (!Lexer::src) {
        throw(FileNotFound::FileNotFound());
    }
}

void Lexer::nextToken() {
    //If file isn't open, return error
    //check that the file was opened, if not throw error
    if (!Lexer::src) {
        throw(FileNotFound::FileNotFound());
    }

    //Initialisation
    STATE state = S0;
    std::string lexeme;
    std::stack <STATE> stack;
    stack.push(SE);
    char ch;

    //Scanning Loop
    while (state!=SE) {
        //get next character
        Lexer::src.get(ch);
        lexeme = lexeme + ch;
        //if state is a final state, clear stack
        if (isFinalState(state)) {
            while(!stack.empty()) {
                stack.pop();
            }
        }
        stack.push(state);
        //cat = Charcat(char);
        //state = TX[state,cat]
    }
}

bool Lexer::isFinalState(STATE s) {
    switch(s) {
        case S1:
        case S2:
        case S4:
        case S6:
        case S7:
        case S8:
        case S9:
            return true;
    }
    return false;
}