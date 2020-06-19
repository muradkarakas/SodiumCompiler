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
        //  if identifier is a name of variable or function parameter, this property will hold the type of variable/parameter.
        //  if it is not, it will be set to TYPELESS_IDENTIFIER
        ASTNodePrimitiveDataType    primitiveDataType;

        string ToString();
        ASTNode_Identifier(Token* _token, string scope);
    };

}

