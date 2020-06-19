#pragma once

#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Data_Type.hpp"

#include "Token.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Literal : public ASTNode
    {
        ASTNode_Data_Type* dataType;

    public:

        string ToString();
        ASTNode_Literal(Token* _token, string scope);
    };

}