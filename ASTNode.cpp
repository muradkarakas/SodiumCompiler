#include "pch.h"

#include "ASTNode.hpp"


Sodium::ASTNode::ASTNode(
	ASTNodeType	nodeType,
	Token * token,
	string scope)
{
	this->_nodeType = nodeType;
	this->_token = token;
	this->_scope = scope;
}