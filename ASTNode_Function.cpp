#include "pch.h"

#include "ASTNode_Function.hpp"


Sodium::ASTNode_Function::ASTNode_Function(Token * _token, string scope)
	: ASTNode(ASTNodeType_Function, _token, scope)
{

}