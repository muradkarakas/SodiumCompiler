#pragma once

#include "pch.h"

#include "ASTNode.hpp"
#include "ASTNode_Statement.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Statement_Variable_Declaration : public ASTNode_Statement
    {
    public:
        ASTNodePrimitiveDataType dataType;
        ASTNode_Statement_Variable_Declaration(Token* _token, ASTNodePrimitiveDataType dataType, string scope);
        string ToString();
    };

}


