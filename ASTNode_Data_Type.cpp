#include "pch.h"

#include "ASTNode.hpp"

#include "ASTNode_Data_Type.hpp"


Sodium::ASTNode_Data_Type::ASTNode_Data_Type(Token* _token, string scope)
	: ASTNode(ASTNodeType_Data_Type, _token, scope)
{

}
