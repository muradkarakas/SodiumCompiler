#pragma once

#include "Token.h"


using namespace std;

namespace Sodium {

	extern class SodiumCompiler;

	class CompileUnitBase {

		

	protected:

		string			fileFullIR;

		//	file path parts 
		string			fileFullPath;
		string			fileName;
		string			filePath;

		Token			* CurrentToken;
		Token			* RootToken;
		SodiumCompiler	* compiler;

		Token			* CreateToken(int tokenCode, int tokenStrLength, int line, const char* tokenStr);

	public:
		CompileUnitBase(SodiumCompiler * compiler);

		~CompileUnitBase();

		BOOL	SetSourceFile(char* filePath);

		string			GetFileContent();
		void			PrintParsedFileContent();

		virtual BOOL	Parse() = 0;
		
		friend class SodiumCompiler;
	};

}
