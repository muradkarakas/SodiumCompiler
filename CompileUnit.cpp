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

using namespace Sodium;

Sodium::CompilerUnit::CompilerUnit(SodiumCompiler * compiler) {
    this->compiler = compiler;
    this->frmxRootToken = NULL;
    this->frmxCurrentToken = NULL;
}

string
Sodium::CompilerUnit::GetFrmxFileContent() {
    string html = "";
    Token* token = this->frmxRootToken;
    while (token) {
        if (token->tokenStr) {
            html.append(token->tokenStr);
        }
        token = token->next;
    }
    return html;
}

Sodium::CompilerUnit::~CompilerUnit() {
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
Sodium::CompilerUnit::ParseFrmx(
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
        this->filePath = filePath;

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
Sodium::CompilerUnit::PrintParsedFileContent() {
    printf("\n%s, (Token count: %d)", this->filePath.c_str(), this->frmxCurrentToken->tokenId);
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