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

Sodium::CompileUnitFrmx::CompileUnitFrmx(SodiumCompiler * compiler) : CompileUnitBase(compiler)
{
    this->compiler = compiler;
    this->compileUnitType = COMPILE_UNIT_TYPE_FRMX;
}

Sodium::CompileUnitFrmx::~CompileUnitFrmx() {
    
}


BOOL
Sodium::CompileUnitFrmx::Parse()
{
    yyscan_t scanner;
    string filePath = fileFullPath.append(".frmx");
    FILE* mkSourceFile = fopen(filePath.c_str(), "r");

    if (mkSourceFile == NULL) {
        /** File does not exists */
        printf("\nFile not found: %s", fileFullPath.c_str());
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
                this->lineNumberOuter,
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
