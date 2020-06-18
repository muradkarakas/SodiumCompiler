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
	
	enum ASTNodePrimitiveDataType {
		Number,
		DateTime,
		String
	};
	
	enum ASTNodeType {
		ASTNodeType_Identifier,
		ASTNodeType_Literal,
		ASTNodeType_Data_Type,
		ASTNodeType_Function,
		ASTNodeType_Block_Statement,
		ASTNodeType_Statement,
		ASTNodeType_Statement_Condition,
		ASTNodeType_Statement_If,
		ASTNodeType_Statement_While,
		ASTNodeType_Statement_Assigment,
		ASTNodeType_Statement_Declaration,
		ASTNodeType_Statement_Call,
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

