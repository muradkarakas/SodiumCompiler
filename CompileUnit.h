#pragma once

#include "Token.h"


using namespace std;

namespace Sodium {

	extern class SodiumCompiler;
	
	class CompilerUnit {

		string			filePath;
		Token* frmxCurrentToken;
		Token* frmxRootToken;
		SodiumCompiler* compiler;

	public:
		CompilerUnit(SodiumCompiler* compiler);

		~CompilerUnit();

		BOOL	ParseFrmx(char* filePath);
		string	GetFrmxFileContent();

		void PrintParsedFileContent();

		friend class SodiumCompiler;
	};

}
