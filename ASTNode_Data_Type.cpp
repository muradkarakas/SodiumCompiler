#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Data_Type.hpp"


Sodium::ASTNode_Data_Type::ASTNode_Data_Type(Token* _token, string scope, ASTNodePrimitiveDataType primitiveDataType)
	: ASTNode(ASTNodeType_Data_Type, _token, scope)
{
	this->primitiveDataType = primitiveDataType;
}

string
Sodium::ASTNode_Data_Type::ToString()
{
	char *buf;
	switch (primitiveDataType) {
		case ASTNodePrimitiveDataType_Typeless: { buf = "No data type"; break; }
		case ASTNodePrimitiveDataType_Void: { buf = "void"; break; }
		case ASTNodePrimitiveDataType_Number: { buf = "number"; break; }
		case ASTNodePrimitiveDataType_String: { buf = "string"; break; }
		case ASTNodePrimitiveDataType_DateTime: { buf = "datetime"; break; }
		case ASTNodePrimitiveDataType_Redis: { buf = "redis"; break; }
		default:  buf = "Unknown";
	}
	return string(buf);
}