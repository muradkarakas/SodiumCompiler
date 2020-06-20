#pragma once

#include "pch.h"

#include "ASTNode_Identifier.hpp"

using namespace std;

namespace Sodium {

	//
	//	CLASSES
	//	
	class ASTNode_Utils
	{

	public:

		static string Sodium::ASTNode_Utils::ConvertVectorOfASTNode_Identifier(vector<Sodium::ASTNode_Identifier> list);
	};

}

