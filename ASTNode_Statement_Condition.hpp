#pragma once

#pragma once

#include "pch.h"

#include "ASTNode_Statement.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Statement_Condition : public ASTNode_Statement
    {
        ASTNode* left;
        ASTCompareOperatorType op;
        ASTNode* rigth;

        ASTNode_Statement* ifBlock;
        ASTNode_Statement* elseBlock;

    public:

        string ToString();
        ASTNode_Statement_Condition(Token* _token, string scope);
    };

}





