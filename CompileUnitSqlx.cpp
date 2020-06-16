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

Sodium::CompileUnitSqlx::CompileUnitSqlx(SodiumCompiler* compiler) : CompileUnitBase(compiler)
{
    this->compiler = compiler;
    this->compileUnitType = COMPILE_UNIT_TYPE_PRE;
}

Sodium::CompileUnitSqlx::~CompileUnitSqlx() {

}

BOOL
Sodium::CompileUnitSqlx::Parse()
{
    bool retVal;
    yyscan_t scanner;
    string filePath = fileFullPath.append(".sqlx");
    FILE* mkSourceFile = fopen(filePath.c_str(), "r");

    if (mkSourceFile == NULL) {
        /** File does not exists */
        printf("\nFile not found: %s", fileFullPath.c_str());
        return false;
    }
    else {

        prelex_init_extra(this->compiler, &scanner);
        preset_in(mkSourceFile, scanner);

        void* pParser = preParseAlloc(malloc);

        Sodium::Token* curToken = NULL;

        do {
            int tokenCode = prelex(scanner);
            int tokenLength = preget_leng(scanner);
            const char* tokenStr = preget_text(scanner);
            curToken = this->CreateToken(
                tokenCode,
                tokenLength,
                this->lineNumberOuter,
                tokenStr);
            preParse(pParser, curToken->tokenCode, curToken, this->compiler);
        } while (curToken->tokenCode != PRE_END_OF_FILE);

        preParse(pParser, 0, 0, this->compiler);

        preParseFree(pParser, free);
        prelex_destroy(scanner);
        fclose(mkSourceFile);

        retVal = true;
    }

    return retVal;
}
