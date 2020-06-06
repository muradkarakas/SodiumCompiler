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
#include "html.parser.imp.h"
#include "lemon.html.h"
#include "lemon.pre.h"

HANDLE gHeapHandle = NULL;

BOOL
SodiumCompiler::ParseFRMXFile(
    char* filePath
)
{
    yyscan_t scanner;

    FILE* mkSourceFile = fopen(filePath, "r");

    if (mkSourceFile == NULL) {
        /** File does not exists */
        printf("\nFile not found: %s", filePath);
        return false;
    }
    else {
        //htmllex_init(&scanner);
        htmllex_init_extra(this, &scanner);
        htmlset_in(mkSourceFile, scanner);

        void* pParser = htmlParseAlloc(malloc);
        Token token;

        while (token.tokenCode = htmllex(scanner) != END_OF_FILE) {
            token.tokenStrLength = htmlget_leng(scanner);
            token.tokenStr = htmlget_text(scanner);
            htmlParse(pParser, token.tokenCode, token, this);
        }

        token.tokenCode = SPACE;
        token.tokenStr = " ";
        token.tokenStrLength = 1;
        htmlParse(pParser, SPACE, token, this);

        token.tokenCode = 0;
        token.tokenStr = "";
        token.tokenStrLength = 0;
        htmlParse(pParser, 0, token, this);

        htmlParseFree(pParser, free);
        htmllex_destroy(scanner);
        fclose(mkSourceFile);

        return true;
    }
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
            token.tokenStr = preget_text(scanner);
            preParse(pParser, token.tokenCode, token, this);
        } while (token.tokenCode != PRE_END_OF_FILE);

        preParseFree(pParser, free);
        prelex_destroy(scanner);
        fclose(mkSourceFile);

        retVal = true;
    }

    return retVal;
}


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
