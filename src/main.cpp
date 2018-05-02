#include <iostream>

#include "include/Lexer.h"
#include "include/Parser.h"
#include "include/Exceptions/LexerException.h"

using namespace std;

int main() {
    std::vector<ASTStatement_Node *> statements;
    Lexer r = Lexer();
    r.scanner("../sampleProgram.ml");

    Parser parser = Parser(&r);
    cout << "Parser Loaded" << endl;

    ASTNode node = ASTNode();
    try {
        node.statements = parser.parse();
    } catch (MiniLangExceptions &e) {
        cout << e.printMessage() << endl;
        return 0;
    }
    return 0;
}