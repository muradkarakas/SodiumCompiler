#include "pch.h"

#include "ASTNode_Function_Declaration.hpp"


Sodium::ASTNode_Function_Declaration::ASTNode_Function_Declaration(Token * _token, string scope)
	: ASTNode(ASTNodeType_Function, _token, scope)
{

}