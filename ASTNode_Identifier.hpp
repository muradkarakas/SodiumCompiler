#pragma once

#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Data_Type.hpp"

#include "Token.h"

using namespace std;

namespace Sodium {

    class ASTNode_Identifier : public ASTNode
    {
        ASTNode_Data_Type* dataType;

    public:

        ASTNode_Identifier(Token* _token, string scope);
    };

}

