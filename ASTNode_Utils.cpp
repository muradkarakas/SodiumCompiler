#include "pch.h"


#include "ASTNode_Utils.hpp"


string 
Sodium::ASTNode_Utils::ConvertVectorOfASTNode_Identifier(vector<Sodium::ASTNode_Identifier> list) {
	string retval = "";
	for (auto identifier = list.begin(); identifier != list.end(); ++identifier) {
		if (retval.size() > 0)
			retval.append(", ");

		retval.append(identifier->ToString());
	}
	return retval;
}


