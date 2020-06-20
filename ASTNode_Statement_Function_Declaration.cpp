#include "pch.h"

#include "ASTNode.hpp"
#include "ASTNode_Statement_Function_Declaration.hpp"


Sodium::ASTNode_Statement_Function_Declaration::ASTNode_Statement_Function_Declaration(
	Token * _token, 
	string scope, 
	ASTNode_Identifier * nameIdentifier,
	vector<ASTNode_Identifier> parameters)
	: ASTNode_Statement(ASTNodeType_Statement_Declaration_Function, _token, scope)
{
	this->nameIdentifier = nameIdentifier;
	this->returnType = NULL;
	this->codeblock = NULL;
	this->returnType = NULL;
	this->parameters = parameters;
}


string
Sodium::ASTNode_Statement_Function_Declaration::ToString()
{
	string retval = "";
	char buff[1000];
	//const char* typeName = ASTNode_Data_TypeName(this->returnType->primitiveDataType);

	sprintf(buff, "\nFunction:\n   In scope: '%s'\n    %s %s",
		this->_scope.c_str(),
		((this->returnType) ? this->returnType->ToString().c_str() : ""),
		((this->nameIdentifier) ? this->nameIdentifier->ToString().c_str() : ""));

	retval = buff;

	return retval;
}