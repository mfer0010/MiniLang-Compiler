//
// Created by marc on 27/03/2018.
//

#include "../include/Token.h"

Token::Token() {
    token_name = TOK_Skip;
}

Token::Token(TOKEN token, double value) {
    token_name = token;
    numerical_value = value;
}

Token::Token(TOKEN token, std::string value) {
    token_name = token;
    string_value = value;
}

Token::Token(TOKEN token, double num_val, std::string string_val) {
    token_name = token;
    numerical_value = num_val;
    string_value = string_val;
}

Token::~Token() {}
