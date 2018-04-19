//
// Created by marc on 27/03/2018.
//

#include "include/Lexer.h"
#include "include/Exceptions/FileNotFound.h"

Lexer::Lexer() {}

Lexer::~Lexer() {
}

void Lexer::scanner(std::string path) {
    std::ifstream src;
    std::string line;
    src.open(path);

    program = "";

    //check that the file was opened, if not throw error
    if (src) {
        throw(FileNotFound::FileNotFound());
    }

    //save program to string:
    while (getline(src,line)) {
        program += line + "\n";
    }

    //close file
    try {
        src.close();
    } catch (std::exception &e) {
        std::cerr << "Error Closing File";
    }
}

Token Lexer::nextToken() {
    //check that the file was opened, if not throw error
    if (program == '\0') {
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
        ch = getNextChar(lexeme.length());
        lexeme = lexeme + ch;
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
    while (!isFinalState(state) && state != SE) {
        state = stack.top();
        stack.pop();
        lexeme.pop_back();
        programPointer--;
    }

    //Report Result
    if (isFinalState(state)) {
        return toToken(lexeme, state);
    } else {
        error = "Lexer Error"; //" at line: " + determineErrorLine(program, charIndex)
        //throw LexerFailedException(error);
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