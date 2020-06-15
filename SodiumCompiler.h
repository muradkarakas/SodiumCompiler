/**
 * This file is part of Sodium Language project
 *
 * Copyright © 2020 Murad Karakaþ <muradkarakas@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v3.0
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 *	https://choosealicense.com/licenses/gpl-3.0/
 */

#pragma once

#include "SymbolTable.h"

typedef void* HANDLE;

extern HANDLE gHeapHandle;

using namespace std;

namespace Sodium {

	class SodiumCompiler {

		CompileUnitFrmx		* frmxParser;
		CompileUnitSqlx		* sqlxParser;

		SymbolTable		* rootSymbol;

	public:
		HANDLE			heapHandle;
		int				lineNumberOuter;

		SodiumCompiler();
		~SodiumCompiler();

		//	returns FALSE if file does not exists or not accessble
		BOOL	ParsePage(char* filePath);
		BOOL	DumpFrmx();
		Token	* CreateFrmxToken(int tokenCode, int tokenStrLength, int line, const char* tokenStr);

		BOOL	ParseSQLXFile(char* filePath);

		llvm::Function* CreateHtmlFunction(llvm::Module* M, llvm::LLVMContext& Context);
		llvm::Function* CreatePageLoadFunction(llvm::Module* M, llvm::LLVMContext& Context);

		void	PrintParsedFRMXFile();
	};

}





