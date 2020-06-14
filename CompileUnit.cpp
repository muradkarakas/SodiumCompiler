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
Sodium::CompilerUnit::SetSourceFile(
    char* filePath
)
{
    string _functionName = filePath;
    this->fileFullPath = filePath;
    std::size_t lastIndexOf  = this->fileFullPath.find_last_of("\\");
    //  check filePath contains path or not
    if (string::npos != lastIndexOf) {
        _functionName = this->fileFullPath.substr(this->fileFullPath.find_last_of('\\') + sizeof(char), this->fileFullPath.length() - 5);
        this->filePath = this->fileFullPath.substr(0, lastIndexOf);
    }
    else {
        this->filePath = "";
    }    
    this->fileName = _functionName.substr(0, _functionName.find_last_of('.'));
    this->fileFullIR = this->filePath + ((this->filePath.empty()) ? "" : "\\") + this->fileName + ".ll";
    return TRUE;
}

Token *
Sodium::CompilerUnit::CreateToken(
    int tokenCode, 
    int tokenStrLength,
    int line,
    const char * tokenStr) 
{
    Token * token = (Token*)mkMalloc(this->compiler->heapHandle, sizeof(Token), __FILE__, __LINE__);
    token->tokenCode = tokenCode;
    token->tokenStrLength = tokenStrLength;
    token->line = line;
    token->tokenStr = mkStrdup(this->compiler->heapHandle, tokenStr, __FILE__, __LINE__);
    if (this->frmxRootToken == NULL) {
        this->frmxRootToken = token;
        token->tokenId = this->frmxRootToken->tokenId + 1;
    }
    else {
        token->tokenId = this->frmxCurrentToken->tokenId + 1;
        this->frmxCurrentToken->next = token;
    }
    this->frmxCurrentToken = token;
    return token;
}

BOOL
Sodium::CompilerUnit::ParseFrmx()
{
    yyscan_t scanner;
    string frmxFilePath = this->fileFullPath.append(".frmx");
    FILE* mkSourceFile = fopen(frmxFilePath.c_str(), "r");

    if (mkSourceFile == NULL) {
        /** File does not exists */
        printf("\nFile not found: %s", this->fileFullPath.c_str());
        return false;
    }
    else {       
        htmllex_init_extra(this->compiler, &scanner);
        htmlset_in(mkSourceFile, scanner);

        void* pParser = htmlParseAlloc(malloc);

        Sodium::Token * curToken = NULL;

        do {
            int tokenCode = htmllex(scanner);
            int tokenLength = htmlget_leng(scanner);
            const char* tokenStr = htmlget_text(scanner);
            curToken = this->CreateToken(
                tokenCode,
                tokenLength, 
                this->compiler->lineNumberOuter,
                tokenStr);
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