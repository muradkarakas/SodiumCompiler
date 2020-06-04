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


#include <iostream>

#include "llvm/ADT/APInt.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>


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
