#pragma once

#include "pch.h"

#include "Token.hpp"

using namespace std;

namespace Sodium {

	typedef struct Token;

	//
	//	ENUMS
	//
	enum ASTCompareOperatorType {
		ASTCompareOperatorType_Equal,
		ASTCompareOperatorType_NotEqual,
		ASTCompareOperatorType_LessThan,
		ASTCompareOperatorType_GreaterThan,
		ASTCompareOperatorType_LessThanOrEqual,
		ASTCompareOperatorType_GreaterThanOrEqual,
	};
	
	#define ASTNODE_SCOPE_GLOBAL			"GLOBAL"
	#define ASTNODE_SCOPE_FUNCTION_PARAMETER "FUNCTION_PARAMETER"
	
	enum ASTNodePrimitiveDataType {
		ASTNodePrimitiveDataType_Typeless,
		ASTNodePrimitiveDataType_Void,
		ASTNodePrimitiveDataType_Number,
		ASTNodePrimitiveDataType_DateTime,
		ASTNodePrimitiveDataType_String,
		ASTNodePrimitiveDataType_Redis
	};
	

	enum ASTNodeType {
		ASTNodeType_Identifier,
		ASTNodeType_Literal,
		ASTNodeType_Data_Type,
		ASTNodeType_Block_Statement,
		ASTNodeType_Statement,
		ASTNodeType_Statement_Condition,
		ASTNodeType_Statement_If,
		ASTNodeType_Statement_While,
		ASTNodeType_Statement_Assigment,
		ASTNodeType_Statement_Declaration_Function,
		ASTNodeType_Statement_Declaration_Variable,
		ASTNodeType_Statement_Call,
	};
	
	//
	//	FUNCTIONS
	//
	const char* ASTNode_Data_TypeName(ASTNodePrimitiveDataType primitiveDataType);

	//
	//	CLASSES
	//	
	class ASTNode
	{

	public:
		ASTNode(ASTNodeType	nodeType, Token * _token, string scope);

		ASTNodeType		_nodeType;
		string			_scope;
		Token			* _token;

		virtual string ToString() = 0;
	};

}

