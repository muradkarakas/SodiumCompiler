#include "pch.h"

#include "ASTNode_Statement_Assigment.hpp"


Sodium::ASTNode_Statement_Assigment::ASTNode_Statement_Assigment(Token* _token, string scope)
	: ASTNode_Statement(ASTNodeType_Statement_Assigment, _token, scope)
{

}

string
Sodium::ASTNode_Statement_Assigment::ToString()
{
	return string("Not implemented yet");
}