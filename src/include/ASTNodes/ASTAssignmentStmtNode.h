//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTASSIGNMENTSTMTNODE_H
#define MINILANG_COMPILER_ASTASSIGNMENTSTMTNODE_H


#include "ASTStatement_Node.h"
#include "ASTExpression_Node.h"

class ASTAssignmentStmtNode : public ASTStatement_Node {
public:
    std::string identifier;
    ASTExpression_Node *expression;

    ASTAssignmentStmtNode(std::string, ASTExpression_Node *);

    ~ASTAssignmentStmtNode();
};


#endif //MINILANG_COMPILER_ASTASSIGNMENTSTMTNODE_H
