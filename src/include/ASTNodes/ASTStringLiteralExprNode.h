//
// Created by marc on 25/04/2018.
//

#ifndef MINILANG_COMPILER_ASTSTRINGLITERALEXPRNODE_H
#define MINILANG_COMPILER_ASTSTRINGLITERALEXPRNODE_H


#include "ASTLiteralExprNode.h"

class ASTStringLiteralExprNode : public ASTLiteralExprNode {
public:
    std::string literalValue;

    ASTStringLiteralExprNode(std::string);

    ~ASTStringLiteralExprNode();

    virtual void accept(Visitor &v) override;
};


#endif //MINILANG_COMPILER_ASTSTRINGLITERALEXPRNODE_H
