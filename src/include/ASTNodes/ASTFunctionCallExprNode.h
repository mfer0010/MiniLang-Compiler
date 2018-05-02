//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTFUNCTIONCALLEXPRNODE_H
#define MINILANG_COMPILER_ASTFUNCTIONCALLEXPRNODE_H


#include "ASTExpression_Node.h"

class ASTFunctionCallExprNode : public ASTExpression_Node{
public:
    std::string identifier;
    std::vector<ASTExpression_Node *> actualParams;

    ASTFunctionCallExprNode(std::string);
    ASTFunctionCallExprNode(std::string, std::vector<ASTExpression_Node *>);

    ~ASTFunctionCallExprNode();

    virtual void accept(Visitor &v) override;
};


#endif //MINILANG_COMPILER_ASTFUNCTIONCALLEXPRNODE_H
