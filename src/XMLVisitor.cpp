//
// Created by marc on 01/05/2018.
//
/*
#include "include/ASTNodes/XMLVisitor.h"
#include "include/Exceptions/VisitorException.h"

XMLVisitor::XMLVisitor() {}

XMLVisitor::~XMLVisitor() {}

void XMLVisitor::visit(ASTNode *node) {
    //This is always the first node in the tree
    indentationNo = 0;

    try {
        XMLFileOutput.open("AST.xml");
    } catch (std::exception &e) {
        throw VisitorException("Error Opening File:\n" + *e.what());
    }

    std::string word = getIndentation();
    XMLFileOutput << word << "<Program>" << std::endl;

    indentationNo++;
    for (auto const &children : node->statements) {
        //children.accept(this);
    }
    indentationNo --;
    XMLFileOutput << word << "</Program>" << std::endl;
    XMLFileOutput.close();
}*/