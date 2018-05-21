//
// Created by marc on 18/05/2018.
//

#ifndef MINILANG_COMPILER_MINILANGI_H
#define MINILANG_COMPILER_MINILANGI_H


#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"
#include "../Visitors/XMLVisitor.h"
#include "../SemanticAnalyser/SemanticAnalyser.h"
#include "../Interpreter/Interpreter.h"

class MiniLangI {
private:
    Lexer l = Lexer();
    Parser p = Parser(&l);
    ASTNode node = ASTNode();
    XMLVisitor * xml = new XMLVisitor();
    SemanticAnalyser * sa = new SemanticAnalyser();
    Interpreter * interpreter = new Interpreter();
    std::string input;
    std::string fd = "../"; //file directory

    void loop();
public:
    //The constructor will also initiate the main loop
    MiniLangI();
};


#endif //MINILANG_COMPILER_MINILANGI_H
