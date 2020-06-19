#pragma once

#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Identifier.hpp"

#include "ASTNode_Statement.hpp"

#include "ASTNode_Code_Block.hpp"

using namespace std;

namespace Sodium {

	class ASTNode_Statement_Function_Declaration : public ASTNode_Statement
	{

	public:
		ASTNode_Identifier			* nameIdentifier;
		vector<ASTNode_Identifier>	parameters;
		ASTNode_Code_Block			* codeblock;
		ASTNode_Data_Type			* returnType;

		string ToString();
		ASTNode_Statement_Function_Declaration(Token* _token, string scope, ASTNode_Identifier* nameIdentifier);
	};

}


