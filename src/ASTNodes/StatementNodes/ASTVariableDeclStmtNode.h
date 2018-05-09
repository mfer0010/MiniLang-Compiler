//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_VARIABLEDECLSTMTNODE_H
#define MINILANG_COMPILER_VARIABLEDECLSTMTNODE_H


#include "ASTStatement_Node.h"
#include "../ExpressionNodes/ASTExpression_Node.h"

class ASTVariableDeclStmtNode : public ASTStatement_Node {
public:
    std::string identifier;
    std::string type;
    ASTExpression_Node * expression;

    ASTVariableDeclStmtNode(std::string, std::string, ASTExpression_Node *);

    ~ASTVariableDeclStmtNode();

    virtual void accept(Visitor *v) override;
};


#endif //MINILANG_COMPILER_VARIABLEDECLSTMTNODE_H
