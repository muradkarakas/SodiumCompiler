#include "pch.h"

#include "ASTNode_Statement.hpp"


Sodium::ASTNode_Statement::ASTNode_Statement(ASTNodeType nodeType, Token* _token, string scope)
	: ASTNode(nodeType, _token, scope)
{

}

string
Sodium::ASTNode_Statement::ToString()
{
	return string("Not implemented yet");
}