#pragma once

#include "pch.h"

#include "Token.h"

using namespace std;

namespace Sodium {

	enum ASTCompareOperatorType {
		ASTCompareOperatorType_Equal,
		ASTCompareOperatorType_NotEqual,
		ASTCompareOperatorType_LessThan,
		ASTCompareOperatorType_GreaterThan,
		ASTCompareOperatorType_LessThanOrEqual,
		ASTCompareOperatorType_GreaterThanOrEqual,
	};
	
	enum ASTNodeType {
		ASTNodeType_Function,
		ASTNodeType_Statement,
		ASTNodeType_Statement_Condition,
		ASTNodeType_Statement_If,
		ASTNodeType_Statement_While,
		ASTNodeType_Statement_Assigment,
	};

	class ASTNode
	{

	public:
		ASTNode(ASTNodeType	nodeType, Token * _token, string scope);

		ASTNodeType		_nodeType;
		string			_scope;
		Token			* _token;


	};

	

}

