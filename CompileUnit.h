#pragma once

#include "Token.h"

extern class SodiumCompiler;

using namespace std;

class CompilerUnit {

	char			filePath[MAX_PATH];
	Token			* frmxCurrentToken;
	Token			* frmxRootToken;
	SodiumCompiler	* compiler;

public:
	CompilerUnit(SodiumCompiler * compiler);

	~CompilerUnit();

	BOOL ParseFRMXFile(char * filePath);
	void PrintParsedFileContent();

	friend class SodiumCompiler;
};


