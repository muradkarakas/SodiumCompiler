#pragma once

#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Data_Type.hpp"

#include "Token.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Identifier : public ASTNode
    {

    public:

        string ToString();
        ASTNode_Identifier(Token* _token, string scope);
    };

}

