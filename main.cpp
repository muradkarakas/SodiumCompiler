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

    compiler.ParseSQLXFile(argv[1]);

    compiler.DumpDllFile();

    return 0;
    /*
    int n = argc > 1 ? atol(argv[1]) : 24;

    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    LLVMContext Context;

    // Create some module to put our function into it.
    std::unique_ptr<Module> Owner(new Module("test", Context));
    Module* M = Owner.get();

    // We are about to create the "fib" function:
    Function* FibF = CreateFibFunction(M, Context);

    // Now we going to create JIT
    std::string errStr;
    ExecutionEngine* EE =
        EngineBuilder(std::move(Owner))
        .setErrorStr(&errStr)
        .create();

    if (!EE) {
        errs() << argv[0] << ": Failed to construct ExecutionEngine: " << errStr
            << "\n";
        return 1;
    }

    errs() << "verifying... ";
    if (verifyModule(*M)) {
        errs() << argv[0] << ": Error constructing function!\n";
        return 1;
    }

    errs() << "OK\n";
    errs() << "We just constructed this LLVM module:\n\n---------\n" << *M;
    errs() << "---------\nstarting fibonacci(" << n << ") with JIT...\n";

    // Call the Fibonacci function with argument n:
    std::vector<GenericValue> Args(1);
    Args[0].IntVal = APInt(32, n);
    GenericValue GV = EE->runFunction(FibF, Args);

    // import result of execution
    outs() << "Result: " << GV.IntVal << "\n";

    return 0;
    */
}

