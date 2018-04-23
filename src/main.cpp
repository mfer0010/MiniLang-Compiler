#include <iostream>

#include "include/Lexer.h"
#include "include/Token.h"

using namespace std;

int main() {
    Lexer r = Lexer();
    r.scanner("../sampleProgram.ml");
    //cout << "Lexer Loaded" << endl;
    Token t = r.nextToken();
    Token t2 = r.nextToken();
    //Token t3 = r.nextToken();
    cout << t.token_name << endl;
    cout << t2.token_name << endl;
    //cout << t3.token_name << endl;
    return 0;
}