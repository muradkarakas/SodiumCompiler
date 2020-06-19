#pragma once

#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Statement.hpp"

using namespace std;

namespace Sodium {

	class ASTNode_Code_Block : public ASTNode
	{
	public:
		vector<ASTNode_Statement*> statements;

		ASTNode_Code_Block(Token* _token, string scope);
		
		string ToString();
		void InsertStatement(ASTNode_Statement * statement);
	};

}

