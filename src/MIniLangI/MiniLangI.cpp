//
// Created by marc on 18/05/2018.
//

#include <iostream>
#include "MiniLangI.h"
#include "../Exceptions/MiniLangExceptions.h"

MiniLangI::MiniLangI() {
    input = "";

    std::cout<<"MiniLangI, by Marc Ferriggi"<<std::endl;
    std::cout<<"Enter #cmd to see the list of available commands, #quit to quit"<<std::endl;

    loop();
}

void MiniLangI::loop() {
    bool quit = false;
    std::string filename;
    std::string tempInput;
    std::ifstream src;
    std::string line;

    std::vector<ASTStatement_Node *> newStatements;
    ASTNode * nodeOfNewStatements;

    while (!quit) {
        std::cout<<"MiniLangI> ";
        std::getline(std::cin, input);

        try {
            if (input[0] == '#') {
                //special commands
                if (input == "#cmd") {
                    //list all commands
                    std::cout
                            << "Commands:\n#load\tCompile a file\n#st\t\tDisplays the Symbol Table\n#ast\tDisplays the XML output of the latest command"
                            << "\n#quit\tQuit" << std::endl;
                } else if (input == "#load") {
                    //compile the loaded file
                    std::cout << "Enter the name of the file with the file extension: ";
                    std::cin >> filename;
                    l.scanner(fd + filename);
                    try {
                        node.statements = p.parse();
                        node.accept(xml);
                        node.accept(sa);
                        node.accept(interpreter);
                    } catch (MiniLangExceptions &e) {
                        std::cout << e.printMessage() << std::endl;
                    }
                } else if (input == "#st") {
                    interpreter->printSymbolTable();
                } else if (input == "#ast") {
                    src.open("../AST.xml");
                    if (!src) {
                        std::cout<<"Error: AST file not created"<<std::endl;
                    } else {
                        while (std::getline(src, line)) {
                            std::cout << line << std::endl;
                        }

                        try {
                            src.close();
                        } catch (std::exception &e) {
                            std::cerr << "Error Closing File";
                        }
                    }
                } else if (input == "#quit") {
                    quit = true;
                } else {
                    std::cout << "Command not recognised" << std::endl;
                }
            } else {
                input += "\n\0"; //add EOF to the end of the string
                l.readLine(input);
                try {
                    newStatements = p.parse();
                } catch (MiniLangExceptions &e) {
                    tempInput = input;
                    input = "var ans : real = 0;\nset ans = " + tempInput + ";\n\0";
                    l.readLine(input);
                    newStatements = p.parse();
                }
                nodeOfNewStatements = new ASTNode;
                nodeOfNewStatements->addStatements(newStatements);
                node.addStatements(newStatements);
                node.accept(xml);
                nodeOfNewStatements->accept(sa);
                nodeOfNewStatements->accept(interpreter);
            }
        } catch (MiniLangExceptions &e) {
            std::cout << e.printMessage() << std::endl;
        }
    }
}