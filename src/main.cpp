#include <iostream>

#include "include/Lexer.h"
#include "include/Parser.h"

using namespace std;

int main() {
    Lexer r = Lexer();
    r.scanner("../sampleProgram.ml");
    //cout << "Lexer Loaded" << endl;
    Token t0 = r.nextToken();
    Token t = r.nextToken();
    Token t2 = r.nextToken();
    Token t3 = r.nextToken();
    Token t4 = r.nextToken();
    Token t5 = r.nextToken();
    Token t6 = r.nextToken();
    Token t7 = r.nextToken();
    Token t8 = r.nextToken();

    cout << TOKEN_NAME[t0.token_name] << endl;
    cout << TOKEN_NAME[t.token_name] << endl;
    cout << TOKEN_NAME[t2.token_name] << " " << t2.string_value << endl;
    cout << TOKEN_NAME[t3.token_name] << endl;
    cout << TOKEN_NAME[t4.token_name] << " " << t4.string_value << endl;
    cout << TOKEN_NAME[t5.token_name] << endl;
    cout << TOKEN_NAME[t6.token_name]<< " " << t6.numerical_value << endl;
    cout << TOKEN_NAME[t8.token_name] << endl;
    Parser parser = Parser(&r);
    cout << "Parser Loaded" << endl;
    return 0;
}