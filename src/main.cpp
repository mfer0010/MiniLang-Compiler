#include <iostream>

#include "include/Lexer.h"
#include "include/Parser.h"
#include "include/Exceptions/LexerException.h"
#include "include/XMLVisitor.h"

using namespace std;

int main() {
    std::vector<ASTStatement_Node *> statements;
    Lexer r = Lexer();
    r.scanner("../sampleProgram.ml");

    Parser parser = Parser(&r);
    cout << "Parser Loaded" << endl;

    ASTNode node = ASTNode();
    XMLVisitor * xml = new XMLVisitor();
    try {
        node.statements = parser.parse();
        node.accept(xml);
    } catch (MiniLangExceptions &e) {
        cout << e.printMessage() << endl;
        return 0;
    }
    return 0;
}