#pragma once

#include <Windows.h>

#include "ASTNode.hpp"

using namespace std;

namespace Sodium {

	typedef struct Token {
		int				tokenId;
		int				tokenCode;
		int				line;
		const char		* tokenStr;
		DWORD			tokenStrLength;

		ASTNode			* ASTNodeInstance;
		
		struct Token	* next;
	} Token;

}


