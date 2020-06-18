#include "pch.h"

#include "ASTNode_Statement_While.hpp"


Sodium::ASTNode_Statement_While::ASTNode_Statement_While(Token* _token, string scope)
	: ASTNode_Statement(ASTNodeType_Statement_While, _token, scope)
{

}
