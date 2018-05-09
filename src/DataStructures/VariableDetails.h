//
// Created by marc on 03/05/2018.
//

#ifndef MINILANG_COMPILER_VARIABLEDETAILS_H
#define MINILANG_COMPILER_VARIABLEDETAILS_H

#include <vector>
#include "Token.h"
#include "../ASTNodes/StatementNodes/ASTFormalParamStmtNode.h"

class VariableDetails {
public:
    std::string type;

    std::vector<ASTFormalParamStmtNode *> *parameters = nullptr;

    VariableDetails(std::string type);

    VariableDetails(std::string type, std::vector<ASTFormalParamStmtNode *> parameters);

    ~VariableDetails();
};

#endif //MINILANG_COMPILER_VARIABLEDETAILS_H
