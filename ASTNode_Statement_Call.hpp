#pragma once

#include "pch.h"

#include "ASTNode_Statement.hpp"
#include "ASTNode_Function_Declaration.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Statement_Call : public ASTNode_Statement
    {
        ASTNode_Function_Declaration * functionToCall;

    public:
        ASTNode_Statement_Call(Token* _token, string scope);
    };

}





