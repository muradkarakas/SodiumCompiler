#pragma once

#pragma once

#include "pch.h"

#include "ASTNode_Statement.hpp"
#include "ASTNode_Statement_Condition.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Statement_While : public ASTNode_Statement
    {
        ASTNode_Statement_Condition* condition;

        ASTNode_Statement* block;

    public:

        string ToString();
        ASTNode_Statement_While(Token* _token, string scope);
    };

}





