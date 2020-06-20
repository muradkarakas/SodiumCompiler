#pragma once

#include "pch.h"

#include "ASTNode.hpp"

#include "Token.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Data_Type : public ASTNode
    {
    public:
        ASTNodePrimitiveDataType    primitiveDataType;

        string          ToString();
        static string   ToString(ASTNodePrimitiveDataType primitiveDataType);

        ASTNode_Data_Type(Token* _token, string scope, ASTNodePrimitiveDataType primitiveDataType);
    };

}
