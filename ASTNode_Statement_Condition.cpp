#include "pch.h"

#include "ASTNode_Statement_Condition.hpp"


Sodium::ASTNode_Statement_Condition::ASTNode_Statement_Condition(Token* _token, string scope)
	: ASTNode_Statement(ASTNodeType_Statement_Condition, _token, scope)
{

}

string
Sodium::ASTNode_Statement_Condition::ToString()
{
	return string("Not implemented yet");
}