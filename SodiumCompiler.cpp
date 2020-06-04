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

#include "SodiumCompiler.h"
#include "pre.parser.imp.h"
#include "lemon.pre.h"

HANDLE gHeapHandle = NULL;


SodiumCompiler::SodiumCompiler() 
{
    this->lineNumberOuter = 0;
    this->rootSymbol = NULL;
    this->heapHandle = HeapCreate(HEAP_ZERO_MEMORY, 2048, 0);
}

SodiumCompiler::~SodiumCompiler()
{
    if (this->heapHandle != NULL) {
        HeapDestroy(this->heapHandle);
        this->heapHandle = NULL;
    }
}

void
SodiumCompiler::DumpDllFile()
{

}

BOOL
SodiumCompiler::ParseSQLXFile(
    char* filePath
)
{
    bool retVal;
    yyscan_t scanner;

    FILE* mkSourceFile = fopen(filePath, "r");

    if (mkSourceFile == NULL) {
        /** File does not exists */
        printf("\nFile not found: %s", filePath);
        retVal = false;
    }
    else {

        prelex_init_extra(this, &scanner);
        preset_in(mkSourceFile, scanner);

        void* pParser = preParseAlloc(malloc);

        Token token;

        do {
            token.tokenCode = prelex(scanner);
            token.tokenStrLength = preget_leng(scanner);
            token.tokenStr = (char*)mkMalloc(this->heapHandle, token.tokenStrLength + 1, __FILE__, __LINE__);
            strncpy_s(token.tokenStr, token.tokenStrLength + 1, preget_text(scanner), token.tokenStrLength + 1);
            preParse(pParser, token.tokenCode, token, this);

        } while (token.tokenCode != PRE_END_OF_FILE);

        preParseFree(pParser, free);
        prelex_destroy(scanner);
        fclose(mkSourceFile);

        retVal = true;
    }

    return retVal;
}

