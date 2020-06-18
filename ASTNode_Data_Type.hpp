#pragma once

#include "pch.h"

#include "ASTNode.hpp"

#include "Token.h"

using namespace std;

namespace Sodium {

    class ASTNode_Data_Type : public ASTNode
    {
        ASTNodePrimitiveDataType    primitiveDataType;
    public:

        ASTNode_Data_Type(Token* _token, string scope);
    };

}
