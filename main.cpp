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

int 
main(
    int argc, 
    char** argv
)
{
    if (argc != 2) {
        printf("\nExample Usage: SodiumCompiler.exe C:\\Sodium\\Sodium-Setup\\Sodium-Site\\apps\\core.sqlx\n");
        return 1;
    }

    SodiumCompiler compiler;

    if (compiler.ParseFrmx(argv[1])) {
        compiler.DumpFrmx();
    }

    return 0;
}

