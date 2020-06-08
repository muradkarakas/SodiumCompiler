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

#include "pch.h"

#include <stdio.h>

#include "CompileUnit.h"

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

CompilerUnit::CompilerUnit(SodiumCompiler * compiler) {
    this->compiler = compiler;
    this->frmxRootToken = NULL;
    this->frmxCurrentToken = NULL;
}

CompilerUnit::~CompilerUnit() {
    Token* token = this->frmxRootToken;
    while (token) {
        if (token->tokenStr) {
            mkFree(this->compiler->heapHandle, (void*) token->tokenStr);
            token->tokenStr = NULL;
        }
        Token* tmp = token;
        token = token->next;
        mkFree(this->compiler->heapHandle, tmp);
    }
}

BOOL
CompilerUnit::ParseFRMXFile(
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
        strcpy(this->filePath, filePath);

        htmllex_init_extra(this->compiler, &scanner);
        htmlset_in(mkSourceFile, scanner);

        void* pParser = htmlParseAlloc(malloc);

        Token* curToken = NULL;

        do {
            curToken = (Token*)mkMalloc(this->compiler->heapHandle, sizeof(Token), __FILE__, __LINE__);
            curToken->tokenCode = htmllex(scanner);
            curToken->tokenStrLength = htmlget_leng(scanner);
            curToken->line = this->compiler->lineNumberOuter;
            curToken->tokenStr = mkStrdup(this->compiler->heapHandle, htmlget_text(scanner), __FILE__, __LINE__);
            if (this->frmxRootToken == NULL) {
                this->frmxRootToken = curToken;
                curToken->tokenId = this->frmxRootToken->tokenId + 1;
            }
            else {
                curToken->tokenId = this->frmxCurrentToken->tokenId + 1;
                this->frmxCurrentToken->next = curToken;
            }
            this->frmxCurrentToken = curToken;
            htmlParse(pParser, curToken->tokenCode, curToken, this->compiler);
        } while (curToken->tokenCode != END_OF_FILE);

        htmlParse(pParser, 0, 0, this->compiler);

        htmlParseFree(pParser, free);
        htmllex_destroy(scanner);
        fclose(mkSourceFile);

        return true;
    }
}

void
CompilerUnit::PrintParsedFileContent() {
    printf("\n%s, (Token count: %d)", this->filePath, this->frmxCurrentToken->tokenId);
    printf("\n--------------------------------------------------------------------------------\n");
    Token* token = this->frmxRootToken;
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