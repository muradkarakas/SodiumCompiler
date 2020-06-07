#pragma once

#include "Token.h"


using namespace std;

class CompilerUnit {

	char	filePath[MAX_PATH];
	Token	* frmxCurrentToken;
	Token	* frmxRootToken;

public:
	CompilerUnit();

	friend class SodiumCompiler;
};


