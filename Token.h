#pragma once

#include <Windows.h>

using namespace std;

typedef struct Token {
	int				tokenId;
	int				tokenCode;
	int				line;
	const char		* tokenStr;
	DWORD			tokenStrLength;
	struct Token	* next;
} Token;


