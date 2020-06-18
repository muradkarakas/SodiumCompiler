#pragma once

#include "pch.h"

#include "ASTNode_Statement.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Statement_Variable_Declaration : public ASTNode_Statement
    {
    public:
        ASTNode_Statement_Variable_Declaration(Token* _token, string scope);
    };

}


