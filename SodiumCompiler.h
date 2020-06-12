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

		CompilerUnit* frmxFile;

		SymbolTable* rootSymbol;

	public:
		HANDLE			heapHandle;
		int				lineNumberOuter;

		SodiumCompiler();
		~SodiumCompiler();

		//	returns FALSE if file does not exists or not accessble
		BOOL	ParseFRMXFile(char* filePath);
		BOOL	ParseSQLXFile(char* filePath);

		BOOL	ExecuteLLVMIR();
		BOOL	DumpIR2Screen();
		BOOL	DumpLLVMIR2File();

		llvm::Function* CreatePageFunction(llvm::Module* M, llvm::LLVMContext& Context);

		void	PrintParsedFRMXFile();
	};

}





