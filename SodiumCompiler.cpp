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
    yyscan_t scanner;

    FILE* mkSourceFile = fopen(filePath, "r");

    if (mkSourceFile == NULL) {
        /** File does not exists */
        printf("\nFile not found: %s", filePath);
        return false;
    }
    else {
        strcpy(this->frmxFile->filePath, filePath);
        
        htmllex_init_extra(this, &scanner);
        htmlset_in(mkSourceFile, scanner);

        void* pParser = htmlParseAlloc(malloc);
        
        Token* curToken = NULL;

        do {
            curToken = (Token *) mkMalloc(this->heapHandle, sizeof(Token), __FILE__, __LINE__);
            curToken->tokenCode = htmllex(scanner);
            curToken->tokenStrLength = htmlget_leng(scanner);
            curToken->line = this->lineNumberOuter;
            curToken->tokenStr = mkStrdup(this->heapHandle, htmlget_text(scanner), __FILE__, __LINE__);
            if (this->frmxFile->frmxRootToken == NULL) {
                this->frmxFile->frmxRootToken = curToken;
                curToken->tokenId = this->frmxFile->frmxRootToken->tokenId + 1;
            }
            else {
                curToken->tokenId = this->frmxFile->frmxCurrentToken->tokenId + 1;
                this->frmxFile->frmxCurrentToken->next = curToken;
            }            
            this->frmxFile->frmxCurrentToken = curToken;
            htmlParse(pParser, curToken->tokenCode, curToken, this);
        } while (curToken->tokenCode != END_OF_FILE);

        htmlParse(pParser, 0, 0, this);

        htmlParseFree(pParser, free);
        htmllex_destroy(scanner);
        fclose(mkSourceFile);

        return true;
    }
}

void
SodiumCompiler::PrintParsedFRMXFile() {
    printf("\n%s, (Token count: %d)", this->frmxFile->filePath, this->frmxFile->frmxCurrentToken->tokenId);
    printf("\n--------------------------------------------------------------------------------\n");
    Token* token = this->frmxFile->frmxRootToken;
    while (token) {
        if (token->tokenId == 1 && token->tokenCode != ENTER) {
            printf("\n%4d:", token->line);
        }
        if (token) {
            if (token->tokenCode == ENTER) {
                printf("\n%4d:", token->line);
            }
            else {
                printf("%.*s", token->tokenStrLength, token->tokenStr);
            }
        }
        token = token->next;
    }
    printf("\n---------------------------------------------------\n");
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
    this->frmxFile = new CompilerUnit();
    this->lineNumberOuter = 1;
    this->rootSymbol = NULL;
    this->heapHandle = HeapCreate(HEAP_ZERO_MEMORY, 2048, 0);
}

SodiumCompiler::~SodiumCompiler()
{
    if (this->heapHandle != NULL) {
        HeapDestroy(this->heapHandle);
        this->heapHandle = NULL;
    }
    if (this->frmxFile)
        delete this->frmxFile;
}

void
SodiumCompiler::DumpDllFile()
{

}


