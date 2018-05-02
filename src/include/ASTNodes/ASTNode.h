//
// Created by marc on 23/04/2018.
//

#ifndef MINILANG_COMPILER_ASTNODE_H
#define MINILANG_COMPILER_ASTNODE_H

#include <vector>
#include <algorithm>

class ASTStatement_Node;

class ASTNode {
public:
    std::vector<ASTStatement_Node *> statements;

    ASTNode();

    virtual ~ASTNode();

    void addStatements(std::vector<ASTStatement_Node *> statements);

    void clearStatements();

private:
    void deleteStatement(ASTStatement_Node *);
};

#endif //MINILANG_COMPILER_ASTNODE_H
