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

Sodium::CompileUnitBase::CompileUnitBase(SodiumCompiler* compiler) {
    this->compiler = compiler;
    this->RootToken = NULL;
    this->CurrentToken = NULL;
    this->astRootNode = NULL;
    this->lineNumberOuter = 1;
    this->compileUnitType = COMPILE_UNIT_TYPE_BASE;
}

Sodium::CompileUnitBase::~CompileUnitBase() {
    Token* token = this->RootToken;
    while (token) {
        if (token->tokenStr) {
            mkFree(this->compiler->heapHandle, (void*)token->tokenStr);
            token->tokenStr = NULL;
        }
        Token* tmp = token;
        token = token->next;
        mkFree(this->compiler->heapHandle, tmp);
    }
}

string
Sodium::CompileUnitBase::GetFileContent() {
    string html = "";
    Token* token = this->RootToken;
    while (token) {
        if (token->tokenStr) {
            html.append(token->tokenStr);
        }
        token = token->next;
    }
    return html;
}



BOOL
Sodium::CompileUnitBase::SetSourceFile(
    char* filePath
)
{
    string _functionName = filePath;
    this->fileFullPath = filePath;
    std::size_t lastIndexOf = this->fileFullPath.find_last_of("\\");
    //  check filePath contains path or not
    if (string::npos != lastIndexOf) {
        _functionName = this->fileFullPath.substr(this->fileFullPath.find_last_of('\\') + sizeof(char), this->fileFullPath.length() - 5);
        this->filePath = this->fileFullPath.substr(0, lastIndexOf);
    }
    else {
        this->filePath = "";
    }
    this->fileName = _functionName.substr(0, _functionName.find_last_of('.'));
    
    return TRUE;
}



void
Sodium::CompileUnitBase::PrintParsedFileContent() 
{
    printf("\n%s, (Token count: %d)", this->fileFullPath.c_str(), this->CurrentToken->tokenId);
    printf("\n--------------------------------------------------------------------------------\n");
    Token* token = this->RootToken;
    while (token) {
        if (token->tokenId == 1 && token->tokenCode != HTML_ENTER && token->tokenCode != PRE_ENTER) {
            printf("\n%4d:", token->line);
        }
        if (token) {
            if (    
                    (this->compileUnitType == COMPILE_UNIT_TYPE_FRMX && token->tokenCode == HTML_ENTER)
                    ||  
                    (this->compileUnitType == COMPILE_UNIT_TYPE_PRE && token->tokenCode == PRE_ENTER)
                ) 
            {
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

Token*
Sodium::CompileUnitBase::CreateToken(
    int tokenCode,
    int tokenStrLength,
    int line,
    const char* tokenStr)
{
    Token* token = (Token*)mkMalloc(this->compiler->heapHandle, sizeof(Token), __FILE__, __LINE__);
    token->tokenCode = tokenCode;
    token->tokenStrLength = tokenStrLength;
    token->line = line;
    token->tokenStr = mkStrdup(this->compiler->heapHandle, tokenStr, __FILE__, __LINE__);
    if (this->RootToken == NULL) {
        this->RootToken = token;
        token->tokenId = this->RootToken->tokenId + 1;
    }
    else {
        token->tokenId = this->CurrentToken->tokenId + 1;
        this->CurrentToken->next = token;
    }
    this->CurrentToken = token;
    return token;
}