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

#include "SodiumCompiler.h"


#ifdef __cplusplus
extern "C" {
#endif
    #include "..\SodiumShared\SodiumShared.h"
#ifdef __cplusplus
}
#endif


HANDLE gHeapHandle = NULL;



using namespace llvm;

static Function* CreateFibFunction(Module* M, LLVMContext& Context) {
    
    // Create the fib function and insert it into module M. This function is said
    // to return an int and take an int parameter.
    FunctionType* FibFTy = FunctionType::get(Type::getInt32Ty(Context),
        { Type::getInt32Ty(Context) }, false);
    Function* FibF =
        Function::Create(FibFTy, Function::ExternalLinkage, "fib", M);

    // Add a basic block to the function.
    BasicBlock* BB = BasicBlock::Create(Context, "EntryBlock", FibF);

    // Get pointers to the constants.
    Value* One = ConstantInt::get(Type::getInt32Ty(Context), 1);
    Value* Two = ConstantInt::get(Type::getInt32Ty(Context), 2);

    // Get pointer to the integer argument of the add1 function...
    Argument* ArgX = &*FibF->arg_begin(); // Get the arg.
    ArgX->setName("AnArg");            // Give it a nice symbolic name for fun.

    // Create the true_block.
    BasicBlock* RetBB = BasicBlock::Create(Context, "return", FibF);
    // Create an exit block.
    BasicBlock* RecurseBB = BasicBlock::Create(Context, "recurse", FibF);

    // Create the "if (arg <= 2) goto exitbb"
    Value* CondInst = new ICmpInst(*BB, ICmpInst::ICMP_SLE, ArgX, Two, "cond");
    BranchInst::Create(RetBB, RecurseBB, CondInst, BB);

    // Create: ret int 1
    ReturnInst::Create(Context, One, RetBB);

    // create fib(x-1)
    Value* Sub = BinaryOperator::CreateSub(ArgX, One, "arg", RecurseBB);
    CallInst* CallFibX1 = CallInst::Create(FibF, Sub, "fibx1", RecurseBB);
    CallFibX1->setTailCall();

    // create fib(x-2)
    Sub = BinaryOperator::CreateSub(ArgX, Two, "arg", RecurseBB);
    CallInst* CallFibX2 = CallInst::Create(FibF, Sub, "fibx2", RecurseBB);
    CallFibX2->setTailCall();

    // fib(x-1)+fib(x-2)
    Value* Sum = BinaryOperator::CreateAdd(CallFibX1, CallFibX2,
        "addresult", RecurseBB);

    // Create the return instruction and add it to the basic block
    ReturnInst::Create(Context, Sum, RecurseBB);

    return FibF;
}


BOOL
SodiumCompiler::DumpDllFile()
{
    int n = 10;
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
        errs() << this->frmxFile->filePath << ": Failed to construct ExecutionEngine: " << errStr
            << "\n";
        return FALSE;
    }

    errs() << "verifying... ";
    if (verifyModule(*M)) {
        errs() << this->frmxFile->filePath << ": Error constructing function!\n";
        return FALSE;
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

    return TRUE;
}



BOOL
SodiumCompiler::ParseFRMXFile(
    char* filePath
)
{
    return this->frmxFile->ParseFRMXFile(filePath);
}

void
SodiumCompiler::PrintParsedFRMXFile() {
    if (this->frmxFile) {
        this->frmxFile->PrintParsedFileContent();
    }
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
    this->frmxFile = new CompilerUnit(this);
    this->lineNumberOuter = 1;
    this->rootSymbol = NULL;
    this->heapHandle = HeapCreate(HEAP_ZERO_MEMORY, 2048, 0);
}

SodiumCompiler::~SodiumCompiler()
{
    if (this->frmxFile)
        delete this->frmxFile;

    if (this->heapHandle != NULL) {
        HeapDestroy(this->heapHandle);
        this->heapHandle = NULL;
    }
}

