#pragma once

#include "pch.h"

#include "ASTNode_Statement.hpp"
#include "ASTNode_Statement_Function_Declaration.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Statement_Call : public ASTNode_Statement
    {
        ASTNode_Statement_Function_Declaration* functionToCall;

    public:

        string ToString();
        ASTNode_Statement_Call(Token* _token, string scope);
    };

}





