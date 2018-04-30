//
// Created by marc on 23/04/2018.
//

#ifndef MINILANG_COMPILER_ASTNODE_H
#define MINILANG_COMPILER_ASTNODE_H

#include <vector>
#include <algorithm>

class ASTNode {
public:
    std::vector<ASTNode *> statements;

    ASTNode();

    virtual ~ASTNode();

    void addStatements(std::vector<ASTNode *> statements);

    void clearStatements();

private:
    void deleteStatement(ASTNode *);
};

#endif //MINILANG_COMPILER_ASTNODE_H
