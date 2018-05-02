//
// Created by marc on 23/04/2018.
//

#ifndef MINILANG_COMPILER_ASTNUMBEREXPRNODE_H
#define MINILANG_COMPILER_ASTNUMBEREXPRNODE_H

#include <string>
#include "ASTExpression_Node.h"

class ASTNumberExprNode : public ASTExpression_Node {
public:
    double value;
    std::string type;

    ASTNumberExprNode(double, std::string);

    virtual ~ASTNumberExprNode();

    virtual void accept(Visitor &v) override;
};


#endif //MINILANG_COMPILER_ASTNUMBEREXPRNODE_H
