#include "pch.h"

#include "ASTNode_Statement.hpp"

#include "ASTNode_Statement_Call.hpp"


Sodium::ASTNode_Statement_Call::ASTNode_Statement_Call(Token* _token, string scope)
	: ASTNode_Statement(ASTNodeType_Statement_Call, _token, scope)
{

}
