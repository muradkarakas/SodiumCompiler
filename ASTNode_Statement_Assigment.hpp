#pragma once

#include "pch.h"

#include "ASTNode_Statement.hpp"

using namespace std;

namespace Sodium {

    class ASTNode_Statement_Assigment : public ASTNode_Statement
    {
        ASTNode* left;
        ASTNode* right;

    public:

        string ToString();
        ASTNode_Statement_Assigment(Token* _token, string scope);
    };

}





