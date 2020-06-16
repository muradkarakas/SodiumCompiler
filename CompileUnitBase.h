#pragma once

#include "Token.h"


using namespace std;

namespace Sodium {

	extern class SodiumCompiler;

	enum CompileUnitType {
		COMPILE_UNIT_TYPE_BASE,
		COMPILE_UNIT_TYPE_FRMX,
		COMPILE_UNIT_TYPE_PRE,
		COMPILE_UNIT_TYPE_POST
	};

	class CompileUnitBase {

	protected:
		/// <summary>
		///		Derived classes must set this in their constructor to approprity value one of the values defined CompileUnitType enum. 
		///		Base class function gets the derived class type and acts accordingly in base class functions.
		/// </summary>
		CompileUnitType	compileUnitType;
		int				lineNumberOuter;

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
