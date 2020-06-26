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

#include "ASTNode.hpp"
#include "ASTNode_Code_Block.hpp"
#include "ASTNode_Data_Type.hpp"
#include "ASTNode_Statement_Variable_Declaration.hpp"
#include "ASTNode_Statement_Function_Declaration.hpp"

HANDLE gHeapHandle = NULL;

using namespace llvm;

void
Sodium::SodiumCompiler::IterateOverCodeBlock(
    Module* M,
    LLVMContext& Context,
    ASTNode_Code_Block* codeBlock)
{
    for (auto pos = codeBlock->statements.begin(); pos != codeBlock->statements.end(); ++pos) {

        switch ((*pos)->_nodeType) {
            case ASTNodeType_Statement_Declaration_Variable: {
                ASTNode_Statement_Variable_Declaration* varDeclaration = (ASTNode_Statement_Variable_Declaration*)(*pos);
                printf("\n%s", varDeclaration->ToString().c_str());
                CreateIRGlobalVariable(
                    M,
                    Context,
                    varDeclaration);
                break;
            }
            case ASTNodeType_Statement_Declaration_Function: {
                ASTNode_Statement_Function_Declaration* funcDeclaration = (ASTNode_Statement_Function_Declaration*)(*pos);
                printf("\n%s", funcDeclaration->ToString().c_str());
                string funcName = this->sqlxParser->fileName + "_";
                funcName.append(funcDeclaration->_token->tokenStr, funcDeclaration->_token->tokenStrLength);
                CreateIRGloabalFunction(
                    M, 
                    Context,
                    funcDeclaration->GetFunctionPrimitiveReturnType(),
                    funcName,
                    funcDeclaration->parameters);
                break;
            }
        }
    }
}

void
Sodium::SodiumCompiler::CreateIRGlobalVariable(
    Module* M,
    LLVMContext& Context,
    ASTNode_Statement_Variable_Declaration* varDeclaration)
{
    string varName = "";
    varName.append(varDeclaration->_token->tokenStr, varDeclaration->_token->tokenStrLength);

    switch (varDeclaration->dataType) {
        case ASTNodePrimitiveDataType_Typeless: { 
            Type* varType = Type::getVoidTy(Context);
            break; 
        }
        case ASTNodePrimitiveDataType_Void: { 
            Type* varType = Type::getVoidTy(Context);
            break; 
        }
        case ASTNodePrimitiveDataType_Number: { 
            Type* varType = Type::getDoubleTy(Context);
            M->getOrInsertGlobal(varName, varType);
            GlobalVariable* gVar = M->getNamedGlobal(varName);
            gVar->setVisibility(GlobalValue::VisibilityTypes::DefaultVisibility);
            gVar->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
            gVar->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLExportStorageClass);
            gVar->setInitializer(ConstantFP::get(varType, "20.20"));
            break; 
        }
        case ASTNodePrimitiveDataType_DateTime: { 
            Type* varType = Type::getDoubleTy(Context);
            break; 
        }
        case ASTNodePrimitiveDataType_String: { 
            PointerType *varType = Type::getInt8PtrTy(Context);

            GlobalVariable* strGlobalVariable = new GlobalVariable(
                *M,
                varType,
                FALSE,
                GlobalValue::LinkageTypes::ExternalLinkage,
                0,
                varName);

            strGlobalVariable->setVisibility(GlobalValue::VisibilityTypes::DefaultVisibility);
            strGlobalVariable->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
            strGlobalVariable->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLExportStorageClass);
            strGlobalVariable->setAlignment(MaybeAlign(1));

            ConstantPointerNull* const_ptr_2_null = ConstantPointerNull::get(varType);
            // Global Variable Definitions
            strGlobalVariable->setInitializer(const_ptr_2_null);

            break; 
        }
        case ASTNodePrimitiveDataType_Bool: { 
            Type* varType = Type::getInt8Ty(Context); 
            break; 
        }
        case ASTNodePrimitiveDataType_Redis: { 
            Type* varType = Type::getVoidTy(Context);
            printf("\nRedis not supported"); 
            break; 
        }
    }
    
    /**/
}


Function*
Sodium::SodiumCompiler::CreateIRGloabalFunction(
    Module* M,
    LLVMContext& Context,
    ASTNodePrimitiveDataType returnType,
    string functionName,
    vector<ASTNode_Identifier> parameters)
{
    //  Preparing paramater list as ArrayRef<Type*>
    //  Loop in parameter list
    Type* typeArray[25];
    int index = 0;
    for (auto pos = parameters.begin(); pos != parameters.end(); ++pos, index++) {
        switch (pos->primitiveDataType) {
            case ASTNodePrimitiveDataType_Typeless: { typeArray[index] = Type::getVoidTy(Context); break; }
            case ASTNodePrimitiveDataType_Void: { typeArray[index] = Type::getVoidTy(Context); break; }
            case ASTNodePrimitiveDataType_Number: { typeArray[index] = Type::getDoubleTy(Context); break; }
            case ASTNodePrimitiveDataType_DateTime: { typeArray[index] = Type::getDoubleTy(Context); break; }
            case ASTNodePrimitiveDataType_String: { typeArray[index] = Type::getInt8PtrTy(Context); break; }
            case ASTNodePrimitiveDataType_Bool: { typeArray[index] = Type::getInt8Ty(Context); break; }
            case ASTNodePrimitiveDataType_Redis: { typeArray[index] = Type::getVoidTy(Context); printf("\nRedis not supported"); break; }
        }    
    }
    ArrayRef<Type*> llvmParameters = makeArrayRef<Type*>(typeArray, index);
    
    //  Function return type
    Type* retType = NULL;
    switch (returnType) {
        case ASTNodePrimitiveDataType_Typeless: { retType = Type::getVoidTy(Context); break; }
        case ASTNodePrimitiveDataType_Void: { retType = Type::getVoidTy(Context); break; }
        case ASTNodePrimitiveDataType_Number: { retType = Type::getDoubleTy(Context); break; }
        case ASTNodePrimitiveDataType_DateTime: { retType = Type::getInt64Ty(Context); break; }
        case ASTNodePrimitiveDataType_String: { retType = Type::getInt8PtrTy(Context); break; }
        case ASTNodePrimitiveDataType_Bool: { retType = Type::getInt1Ty(Context); break; }
        case ASTNodePrimitiveDataType_Redis: { retType = Type::getVoidTy(Context); printf("\nRedis not supported"); break; }
    }

    // Create the page function and insert it into module M. No return value
    FunctionType* FibFTy = FunctionType::get(retType, llvmParameters, false);
    Function* FibF = Function::Create(FibFTy, Function::ExternalLinkage, functionName, M);


    // visibility settings
    FibF->setVisibility(llvm::GlobalValue::VisibilityTypes::DefaultVisibility);
    FibF->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
    FibF->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLExportStorageClass);
    
    // Add a basic block to the function.
    BasicBlock* BB = BasicBlock::Create(Context, "EntryBlock", FibF);

    // Create the return instruction and add it to the basic block
    llvm::IRBuilder<> builder(Context);
    builder.SetInsertPoint(BB);

    string funcRetValGlobalStringName = functionName + "_retval";
    Value *tempRetValForString = builder.CreateGlobalStringPtr("muradkarakas@gmail.com", funcRetValGlobalStringName);
    Value * tempRetValForNumber = ConstantFP::get(Type::getDoubleTy(Context), 20.20);
    Value *tempRetValForBool = builder.getTrue();

    switch (returnType) {
        case ASTNodePrimitiveDataType_Typeless: { ReturnInst::Create(Context, (llvm::Value*) nullptr, BB); break; }
        case ASTNodePrimitiveDataType_Void: { ReturnInst::Create(Context, (llvm::Value*) nullptr, BB); break; }
        case ASTNodePrimitiveDataType_Number: { ReturnInst::Create(Context, tempRetValForNumber, BB); break; }
        case ASTNodePrimitiveDataType_DateTime: { ReturnInst::Create(Context, (llvm::Value*) nullptr, BB); break; }
        case ASTNodePrimitiveDataType_String: { ReturnInst::Create(Context, tempRetValForString, BB); break; }
        case ASTNodePrimitiveDataType_Bool: { ReturnInst::Create(Context, tempRetValForBool, BB); break; }
        case ASTNodePrimitiveDataType_Redis: { ReturnInst::Create(Context, (llvm::Value*) nullptr, BB); break; }
    }

    return FibF;
}


BOOL
Sodium::SodiumCompiler::DumpIR()
{
    if (this->parsingPhase < PARSING_PHASE_SQLX_PRE_DONE)
        return FALSE;

    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    LLVMContext Context;

    // Create some module to put our function into it.
    std::unique_ptr<Module> Owner(new Module("Sodium", Context));
    Module* M = Owner.get();

    // We are about to create a spesific function for a frmx file to return its context:
    /*Function* FibF = */ CreateHtmlFunction(M, Context);
    /*Function* FibF =  CreatePageLoadFunction(M, Context);*/

    IterateOverCodeBlock(M, Context, this->astNodeCodeBlock);

    // writing LLCM IR file to disk
    string irFileName = this->frmxParser->fileName;
    irFileName.append(".ll");
    StringRef irfileNameRef(irFileName);
    std::error_code error;
    raw_fd_ostream file(irfileNameRef, error);
    file << *M;
    file.close();

    return TRUE;
}

void
Sodium::SodiumCompiler::InsertASTNode(
    ASTNode_Statement* statement)
{
    this->astNodeCodeBlock->InsertStatement(statement);
}


Sodium::Token *
Sodium::SodiumCompiler::CreateToken(
    int tokenCode, 
    int tokenStrLength, 
    const char * tokenStr)
{
    if (this->parsingPhase = PARSING_PHASE_FRMX)
        return this->frmxParser->CreateToken(tokenCode, tokenStrLength, this->frmxParser->lineNumberOuter, tokenStr);
    else if (this->parsingPhase = PARSING_PHASE_SQLX_PRE)
        return this->sqlxParser->CreateToken(tokenCode, tokenStrLength, this->sqlxParser->lineNumberOuter, tokenStr);
    
    return NULL;
}

void
Sodium::SodiumCompiler::SetCodeBlock(ASTNode_Code_Block* codeBlock) {
    this->astNodeCodeBlock = codeBlock;
}


void
Sodium::SodiumCompiler::IncreseLineNumberOuter() {
    if (this->parsingPhase == PARSING_PHASE_FRMX) {
        frmxParser->lineNumberOuter++;
    } else if (this->parsingPhase = PARSING_PHASE_SQLX_PRE) {
        sqlxParser->lineNumberOuter++;
    }
}

Function* 
Sodium::SodiumCompiler::CreateHtmlFunction(
    Module* M, 
    LLVMContext& Context) 
{
    //  
    //  calculating function name
    //  converting "c:\....\core.frmx" to "core_html".
    //
    string pageFunctionName = this->frmxParser->fileName + "_html";

    // Create the page function and insert it into module M. This function is said
    // to return a char * and takes no parameter.
    FunctionType* FibFTy = FunctionType::get(Type::getInt8PtrTy(Context), {  }, false);
    Function* FibF = Function::Create(FibFTy, Function::ExternalLinkage, pageFunctionName, M);

    // visibility settings
    FibF->setVisibility(llvm::GlobalValue::VisibilityTypes::DefaultVisibility);
    FibF->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
    FibF->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLExportStorageClass);

    // Add a basic block to the function.
    BasicBlock* BB = BasicBlock::Create(Context, "EntryBlock", FibF);

    //  getting html file content as string
    string html = this->frmxParser->GetFileContent();

    // creating global variable holding page html content
    llvm::IRBuilder<> builder(Context);
    builder.SetInsertPoint(BB);
    llvm::Value* htmlContent = builder.CreateGlobalStringPtr(html, "g_" + pageFunctionName);

    // Create the return instruction and add it to the basic block
    ReturnInst::Create(Context, htmlContent, BB);

    return FibF;
}

Function* 
Sodium::SodiumCompiler::CreatePageLoadFunction(
    Module* M, 
    LLVMContext& Context) 
{
    //  
    //  calculating function name
    //  converting "c:\....\core.frmx" to "core_html".
    //
    string pageFunctionName = this->frmxParser->fileName + "_page_load";

    // Create the page function and insert it into module M. No return value
    FunctionType* FibFTy = FunctionType::get(Type::getVoidTy(Context), {  }, false);
    Function* FibF = Function::Create(FibFTy, Function::ExternalLinkage, pageFunctionName, M);

    // visibility settings
    FibF->setVisibility(GlobalValue::VisibilityTypes::DefaultVisibility);
    FibF->setLinkage(GlobalValue::LinkageTypes::ExternalLinkage);
    FibF->setDLLStorageClass(GlobalValue::DLLStorageClassTypes::DLLExportStorageClass);

    // Add a basic block to the function.
    BasicBlock* BB = BasicBlock::Create(Context, "EntryBlock", FibF);

    // Create the return instruction and add it to the basic block
    ReturnInst::Create(Context, (llvm::Value*) nullptr, BB);

    return FibF;
}



BOOL
Sodium::SodiumCompiler::ParsePage(
    char* filePath
)
{
    //  Init Abstract Parse Tree
    this->SetCodeBlock(new ASTNode_Code_Block(NULL, "Global"));

    // FRMX PARSING
    this->parsingPhase = PARSING_PHASE_FRMX;
    this->frmxParser = new CompileUnitFrmx(this);
    
    if (this->frmxParser->SetSourceFile(filePath) && this->frmxParser->Parse()) {
        //  FRMX PARSING DONE
        this->parsingPhase = PARSING_PHASE_FRMX_DONE;
        
        //this->frmxParser->PrintParsedFileContent();

        // SQL PRE PARSING
        this->parsingPhase = PARSING_PHASE_SQLX_PRE;
        this->sqlxParser = new CompileUnitSqlx(this);
        
        if (this->sqlxParser->SetSourceFile(filePath) && this->sqlxParser->Parse()) {
            // SQL PRE PARSING DONE
            this->parsingPhase = PARSING_PHASE_SQLX_PRE_DONE;
            
            //this->sqlxParser->PrintParsedFileContent();
            
            return TRUE;
        }
    }

    return FALSE;
}


Sodium::SodiumCompiler::SodiumCompiler()
{
    this->parsingPhase = PARSING_PHASE_NOTSET;
    this->frmxParser = NULL;
    this->sqlxParser = NULL;
    this->heapHandle = HeapCreate(HEAP_ZERO_MEMORY, 2048, 0);
}

Sodium::SodiumCompiler::~SodiumCompiler()
{

    //  TODO: Free all function parameter list defined as "vector<ASTNode_Identifier>	tempVectorForASTNodeIdentifier;" in SodiumCompiler.cpp 
    if (this->frmxParser) {
        delete this->frmxParser;
        this->frmxParser = NULL;
    }
    
    if (this->sqlxParser) {
        delete this->sqlxParser;
        this->sqlxParser = NULL;
    }

    if (this->astNodeCodeBlock) {
        delete this->astNodeCodeBlock;
        this->astNodeCodeBlock = NULL;
    }

    if (this->heapHandle != NULL) {
        HeapDestroy(this->heapHandle);
        this->heapHandle = NULL;
    }
}


