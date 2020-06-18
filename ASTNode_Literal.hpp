#pragma once

#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Data_Type.hpp"

#include "Token.h"

using namespace std;

namespace Sodium {

    class ASTNode_Literal : public ASTNode
    {
        ASTNode_Data_Type* dataType;

    public:

        ASTNode_Literal(Token* _token, string scope);
    };

}