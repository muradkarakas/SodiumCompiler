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



#ifdef __cplusplus
extern "C" {
#endif

	#include "..\SodiumShared\SodiumShared.h"

#ifdef __cplusplus
}
#endif

typedef struct Token {
	int			tokenCode;
	char		* tokenStr;
	DWORD		tokenStrLength;
} Token;

class SodiumCompiler {

	SymbolTable	  * rootSymbol;

public:
	HANDLE			heapHandle;
	int				lineNumberOuter;

	SodiumCompiler();
	~SodiumCompiler();

	//	returns FALSE if file does not exists or not accessble
	BOOL	ParseSQLXFile(char * filePath);
	void	DumpDllFile();
};


extern HANDLE gHeapHandle;
