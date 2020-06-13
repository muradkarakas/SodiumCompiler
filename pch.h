#pragma once

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
#include "IRBuilder.h"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <stdio.h>
#include <iostream>


#ifdef __cplusplus
extern "C" {
#endif

	#include "..\SodiumShared\SodiumShared.h"

#ifdef __cplusplus
}
#endif

#include "CompileUnit.h"

#include "pre.parser.imp.h"
#include "html.parser.imp.h"
#include "lemon.html.h"
#include "lemon.pre.h"

#include "SymbolTable.h"
#include "Node.h"

#include "SodiumCompiler.h"