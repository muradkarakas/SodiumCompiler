#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Statement_Variable_Declaration.hpp"


Sodium::ASTNode_Statement_Variable_Declaration::ASTNode_Statement_Variable_Declaration(Token* _token, ASTNodePrimitiveDataType dataType, string scope)
	: ASTNode_Statement(ASTNodeType_Statement_Declaration_Variable, _token, scope)
{
	this->dataType = dataType;
}

string
Sodium::ASTNode_Statement_Variable_Declaration::ToString()
{
	string retval = "";
	char buff[1000];
	const char* typeName = ASTNode_Data_TypeName(this->dataType);

	sprintf(buff, "%s %.*s",
		//this->_scope.c_str(),
		typeName,
		this->_token->tokenStrLength,
		this->_token->tokenStr);

	retval = buff;

	return retval;
}

