#pragma once

#include "pch.h"

#include "ASTNode.hpp"
#include "ASTNode_Statement.hpp"

using namespace std;

namespace Sodium {

	class ASTNode_Function : public ASTNode
	{
		vector<ASTNode_Statement>	statement;

	public:
		ASTNode_Function(Token* _token, string scope);
	};

}


