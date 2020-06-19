#include "pch.h"

#include "ASTNode_Statement_If.hpp"


Sodium::ASTNode_Statement_If::ASTNode_Statement_If(Token* _token, string scope)
	: ASTNode_Statement(ASTNodeType_Statement_If, _token, scope)
{

}

string
Sodium::ASTNode_Statement_If::ToString()
{
	return string("Not implemented yet");
}