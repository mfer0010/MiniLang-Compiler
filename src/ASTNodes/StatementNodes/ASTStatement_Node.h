//
// Created by marc on 23/04/2018.
//

#ifndef MINILANG_COMPILER_ASTSTATEMENT_NODE_H
#define MINILANG_COMPILER_ASTSTATEMENT_NODE_H

#include "../ASTNode.h"
#include "../../Visitors/Visitor.h"

class ASTStatement_Node /*: public ASTNode*/ {
public:
    virtual ~ASTStatement_Node() {};

    virtual void accept(Visitor *v) = 0;
};

#endif //MINILANG_COMPILER_ASTSTATEMENT_NODE_H
