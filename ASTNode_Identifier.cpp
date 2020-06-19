#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Identifier.hpp"


Sodium::ASTNode_Identifier::ASTNode_Identifier(Token* _token, string scope)
	: ASTNode(ASTNodeType_Identifier, _token, scope)
{
}

string
Sodium::ASTNode_Identifier::ToString()
{
	char buf[200];
	sprintf(buf, "%.*s", this->_token->tokenStrLength, this->_token->tokenStr);
	return string(buf);
}