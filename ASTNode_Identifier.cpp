#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Identifier.hpp"


Sodium::ASTNode_Identifier::ASTNode_Identifier(Token* _token, string scope)
	: ASTNode(ASTNodeType_Identifier, _token, scope)
{

}
