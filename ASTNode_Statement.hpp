#pragma once

#include "pch.h"

#include "ASTNode.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Statement : public ASTNode
    {
    public:
        ASTNode_Statement(ASTNodeType nodeType, Token* _token, string scope);

    };
}

