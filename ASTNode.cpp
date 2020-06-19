#include "pch.h"

#include "ASTNode.hpp"


Sodium::ASTNode::ASTNode(
	ASTNodeType	nodeType,
	Token * token,
	string scope)
{
	this->_nodeType = nodeType;
	this->_token = token;
	this->_scope = scope;

	if (token)
		token->ASTNodeInstance = this;
}

const char*
Sodium::ASTNode_Data_TypeName(ASTNodePrimitiveDataType primitiveDataType) {
	switch (primitiveDataType) {
		case ASTNodePrimitiveDataType_Void: return "void";
		case ASTNodePrimitiveDataType_Number: return "number";
		case ASTNodePrimitiveDataType_String: return "string";
		case ASTNodePrimitiveDataType_DateTime: return "datetime";
		case ASTNodePrimitiveDataType_Redis: return "redis";
	}
	return "Unknow";
}