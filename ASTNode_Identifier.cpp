#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Identifier.hpp"


Sodium::ASTNode_Identifier::ASTNode_Identifier(Token* _token, string scope)
	: ASTNode(ASTNodeType_Identifier, _token, scope)
{
	this->primitiveDataType = ASTNodePrimitiveDataType_Typeless;
}

Sodium::ASTNode_Identifier::ASTNode_Identifier(Token* _token, string scope, ASTNodePrimitiveDataType primitiveDataType)
	: ASTNode(ASTNodeType_Identifier, _token, scope)
{
	this->primitiveDataType = primitiveDataType;
}

string
Sodium::ASTNode_Identifier::ToString()
{
	char buf[200];
	
	sprintf(
		buf, 
		"%s %.*s", 
		ASTNode_Data_Type::ToString(this->primitiveDataType).c_str(), 
		this->_token->tokenStrLength, 
		this->_token->tokenStr);
	
	return string(buf);
}