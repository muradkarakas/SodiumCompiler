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

#ifdef __cplusplus
extern "C" {
#endif
    #include "..\SodiumShared\SodiumShared.h"
#ifdef __cplusplus
}
#endif


HANDLE gHeapHandle = NULL;

BOOL
SodiumCompiler::ParseFRMXFile(
    char* filePath
)
{
    return this->frmxFile->ParseFRMXFile(filePath);
}

void
SodiumCompiler::PrintParsedFRMXFile() {
    if (this->frmxFile) {
        this->frmxFile->PrintParsedFileContent();
    }
}

BOOL
SodiumCompiler::ParseSQLXFile(
    char* filePath
)
{
    bool retVal;
    
    FILE* mkSourceFile = fopen(filePath, "r");

    if (mkSourceFile == NULL) {
        /** File does not exists */
        printf("\nFile not found: %s", filePath);
        retVal = false;
    }
    else {
        /*
        yyscan_t scanner;

        prelex_init_extra(this, &scanner);
        preset_in(mkSourceFile, scanner);

        void* pParser = preParseAlloc(malloc);

        Token token;

        do {
            token.tokenCode = prelex(scanner);
            token.tokenStrLength = preget_leng(scanner);
            token.tokenStr = preget_text(scanner);
            preParse(pParser, token.tokenCode, token, this);
        } while (token.tokenCode != PRE_END_OF_FILE);

        token.tokenCode = ENTER;
        token.tokenStrLength = 1;
        token.tokenStr = "\n";
        preParse(pParser, token.tokenCode, token, this);

        preParse(pParser, 0, NULL, this);

        preParseFree(pParser, free);
        prelex_destroy(scanner);
        fclose(mkSourceFile);
        */
        retVal = true;
    }

    return retVal;
}


SodiumCompiler::SodiumCompiler()
{
    this->frmxFile = new CompilerUnit(this);
    this->lineNumberOuter = 1;
    this->rootSymbol = NULL;
    this->heapHandle = HeapCreate(HEAP_ZERO_MEMORY, 2048, 0);
}

SodiumCompiler::~SodiumCompiler()
{
    if (this->frmxFile)
        delete this->frmxFile;

    if (this->heapHandle != NULL) {
        HeapDestroy(this->heapHandle);
        this->heapHandle = NULL;
    }
}

void
SodiumCompiler::DumpDllFile()
{

}


