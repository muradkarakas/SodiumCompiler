#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Literal.hpp"

Sodium::ASTNode_Literal::ASTNode_Literal(Token* _token, string scope)
	: ASTNode(ASTNodeType_Literal, _token, scope)
{

}
