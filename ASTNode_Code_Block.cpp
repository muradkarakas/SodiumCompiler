#include "pch.h"

#include "ASTNode_Code_Block.hpp"

Sodium::ASTNode_Code_Block::ASTNode_Code_Block(Token* _token, string scope)
	: ASTNode(ASTNodeType_Block_Statement, _token, scope)
{

}

void
Sodium::ASTNode_Code_Block::InsertStatement(ASTNode_Statement * statement)
{
	this->statements.push_back(statement);
}

string 
Sodium::ASTNode_Code_Block::ToString()
{
	return string("Not implemented yet");
}
