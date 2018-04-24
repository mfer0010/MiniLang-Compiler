//
// Created by marc on 27/03/2018.
//

#include "include/Lexer.h"
#include "include/LexerException.h"

Lexer::Lexer() {}

Lexer::~Lexer() {
}

void Lexer::scanner(std::string path) {
    std::ifstream src;
    std::string line;
    src.open(path);

    program = "";

    //std::cout << src.is_open() << std::endl;
    //check that the file was opened, if not throw error
    if (!src) {
        throw std::runtime_error("Error Opening File");
    }

    //save program to string:
    while (std::getline(src,line)) {
        //std::cout << line << std::endl;
        program += line + "\n";
    }

    //testing:
    std::cout << "Program: " << program <<std::endl;
    //close file
    try {
        src.close();
    } catch (std::exception &e) {
        std::cerr << "Error Closing File";
    }
}

Token Lexer::nextToken() {
    //check that the file was opened, if not throw error
    if (program == "EMPTY") {
        throw std::runtime_error("Error Opening File");
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
        ch = getNextChar(lexeme.length());
        //if condition added in order for detection of */ to work
        if (ch == '*' && program[programPointer] == '/') {
            lexeme = lexeme + "*/";
        } else {
            lexeme = lexeme + ch;
        }
        //if state is a final state, clear stack
        if (isFinalState(state)) {
            while(!stack.empty()) {
                stack.pop();
            }
        }
        stack.push(state);
        state = Lexer::transitionTable[state][toClassifier(ch)];

        //if the character is EOF then stop scanning as we have reached the end of the document
        if (ch == EOF || ch == '\0') {
            break;
        }
    }

    //Rollback Loop
    while (!isFinalState(state) && state == SE) {
        state = stack.top();
        stack.pop();
        //if we have a */ we need to remove both these characters
        if (lexeme.length() > 1) {
            if (lexeme.back() == '/' && lexeme.at(lexeme.length() - 2) == '*') {
                lexeme.pop_back();
                programPointer--;
            }
        }
        lexeme.pop_back();
        programPointer--;
    }

    //std::cout << state << std::endl;
    //Report Result
    if (isFinalState(state)) {
        return toToken(lexeme, state);
    } else {
        throw LexerException("Lexer Error, char at " + std::to_string(programPointer), getErrorLine());
//        error = "Lexer Error at line: " + std::to_string(getErrorLine()) + "\nChar at " + std::to_string(programPointer);
//        std::cout << error << std::endl;
//        std::cout << "\""<<lexeme<< "\"" << std::endl;
//        return (Token(TOK_Error));
        //throw std::runtime_error(error);
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
        case S11:
        case S12:
        case S14:
            return true;
    }
    return false;
}

int Lexer::toClassifier(char ch) {
    switch (ch) {
        case EOF:
        case '\0':
            return END_OF_File;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return DIGIT;
        case '.':
            return DECIMAL_POINT;
        case '"':
            return INVERTED_COMMA;
        case '_':
            return UNDERSCORE;
        case '>':
        case '<':
            return GREATER_LESSTHAN;
        case '!':
            return EXCLEMATION;
        case '=':
            return EQUALS;
        case '/':
            return SLASH;
        case '\n':
            return NEW_LINE;
        case '*':
            //1 character lookahead for line comments:
            if (program[programPointer] == '/') {
                programPointer++;
                return END_COMMENT;
            }
            return STAR;
        case '+':
        case '-':
        case '{':
        case '}':
        case '(':
        case ')':
        case ',':
        case ':':
        case ';':
            return OPERATORS;
        default:
            if (isalpha(ch)) {
                return LETTER;
            } else if (ch >= 32 && ch <= 126) {
                return PRINTABLE;
            } else {
                return OTHER;
            }
    }
}

Token Lexer::toToken(std::string lexeme, STATE state) {
    switch (state) {
        case S1:
            return Token(TOK_EOF);
        case S2:
            return Token(TOK_Number, std::stod(lexeme), "INTEGER");
        case S4:
            return Token(TOK_Number,std::stod(lexeme), "REAL");
        case S6:
            //remove inverted commas in printable string:
            return Token(TOK_StringLiteral,lexeme.substr(1,lexeme.size()-2));
        case S7:
            return determineIDToken(lexeme);
        case S8:
            return determineOperatorToken(lexeme);
        case S9:
            return Token(TOK_RelationalOp,lexeme);
        case S11:
            return determineOthersToken(lexeme);
        case S12:
            return Token(TOK_MultiplicativeOp, lexeme);
        case S14:
            return Token(TOK_Skip);
    }
    return Token(TOK_Error, "Error: Non Final State"); //This line should never happen
}

Token Lexer::determineIDToken(std::string lexeme) {
    std::string keyWords [] = {"real","int","bool","string","true","false","and","or","not","set","var","print",
                               "return","if","else","while","def"};
    Token tokens [] = {Token(TOK_Type,"REAL"),Token(TOK_Type,"INT"),Token(TOK_Type,"BOOL"),Token(TOK_Type,"STRING"),
                       Token(TOK_Bool,"TRUE"), Token(TOK_Bool,"FALSE"), Token(TOK_MultiplicativeOp,"AND"),
                       Token(TOK_AdditiveOp,"OR"), Token(TOK_Not), Token(TOK_Set), Token(TOK_Var), Token(TOK_Print),
                       Token(TOK_Return), Token(TOK_If), Token(TOK_Else), Token(TOK_While), Token(TOK_Def)};

    //Check if lexeme is a keyword:
    for (int i = 0; i < sizeof(keyWords)/sizeof(keyWords[0]);i++) {
        if (lexeme.length() == keyWords[i].length() && keyWords[i].find(lexeme) != std::string::npos) {
            return tokens[i];
        }
    }

    //return Identifier token
    return Token(TOK_Identifier, lexeme);
}

Token Lexer::determineOperatorToken(std::string lexeme) {
    if (lexeme == "<" || lexeme == ">") {
        return Token(TOK_RelationalOp,lexeme);
    } else if (lexeme == "=") {
        return Token(TOK_Equals);
    }
    return Token(TOK_Error, "Error: Non Final State");
}

Token Lexer::determineOthersToken(std::string lexeme) {
    if (lexeme == "*") {
        return Token(TOK_MultiplicativeOp,lexeme);
    } else if (lexeme == "+" || lexeme == "-") {
        return Token(TOK_AdditiveOp,lexeme);
    } else if (lexeme == "{") {
        return Token(TOK_LeftBrace);
    } else if (lexeme == "}") {
        return Token(TOK_RightBrace);
    } else if (lexeme == "(") {
        return Token(TOK_LeftBracket);
    } else if (lexeme == ")") {
        return Token(TOK_RightBracket);
    } else if (lexeme == ",") {
        return Token(TOK_Comma);
    } else if (lexeme == ":") {
        return Token(TOK_Colon);
    } else if (lexeme == ";") {
        return Token(TOK_SemiColon);
    }
    return Token(TOK_Error, "Error: Non Final State");
}

char Lexer::getNextChar(size_t lexemeLength) {
    while (true) {
        if ((size_t) programPointer == program.length()) {
            return EOF;
        } else if (lexemeLength == 0) {
            //skip white spaces
            if (program[programPointer] == ' ' || program[programPointer] == '\n' || program[programPointer] == '\t') {
                programPointer++;
            } else {
                return program[programPointer++];
            }
        } else {
            return program[programPointer++];
        }
    }
}

int Lexer::getErrorLine() {
    int counter = 1;
    for (int i = 0; i <= programPointer; i++) {
        if (program[i]=='\n') {
            counter ++;
        }
    }
    return(counter);
}