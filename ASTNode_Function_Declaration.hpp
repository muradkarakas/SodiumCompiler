#pragma once

#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Identifier.hpp"

#include "ASTNode_Code_Block.hpp"

using namespace std;

namespace Sodium {

	class ASTNode_Function_Declaration : public ASTNode
	{
		vector<ASTNode_Identifier>	parameters;
		ASTNode_Code_Block			* codeblock;
		ASTNode_Identifier			* returnType;

	public:
		ASTNode_Function_Declaration(Token* _token, string scope);
	};

}


