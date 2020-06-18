#include "pch.h"

#include "ASTNode_Statement_Variable_Declaration.hpp"


Sodium::ASTNode_Statement_Variable_Declaration::ASTNode_Statement_Variable_Declaration(Token* _token, string scope)
	: ASTNode_Statement(ASTNodeType_Statement_Declaration, _token, scope)
{

}
