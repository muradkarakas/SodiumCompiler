#pragma once

#include "Token.h"


using namespace std;

namespace Sodium {

	extern class SodiumCompiler;
	
	class CompilerUnit {

		//	file path parts 
		string			fileFullPath;
		string			fileName;
		string			filePath;
		string			fileFullIR;

		Token			* frmxCurrentToken;
		Token			* frmxRootToken;
		SodiumCompiler	* compiler;

	public:
		CompilerUnit(SodiumCompiler* compiler);

		~CompilerUnit();

		BOOL	ParseFrmx();
		BOOL	SetSourceFile(char* filePath);
		string	GetFrmxFileContent();

		void PrintParsedFileContent();

		friend class SodiumCompiler;
	};

}
