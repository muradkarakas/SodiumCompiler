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
#include "ASTNode_Statement_Variable_Declaration.hpp"
#include "ASTNode_Statement_Function_Declaration.hpp"

HANDLE gHeapHandle = NULL;

using namespace llvm;

void
Sodium::SodiumCompiler::IterateOverCodeBlock(
    ASTNode_Code_Block* codeBlock)
{
    for (auto pos = codeBlock->statements.begin(); pos != codeBlock->statements.end(); ++pos) {

        switch ( (*pos)->_nodeType ) {
            case ASTNodeType_Statement_Declaration_Variable: {
                ASTNode_Statement_Variable_Declaration* node = (ASTNode_Statement_Variable_Declaration*)(*pos);
                printf("\n%s", node->ToString().c_str());
                break;
            }
            case ASTNodeType_Statement_Declaration_Function: {
                ASTNode_Statement_Function_Declaration* node = (ASTNode_Statement_Function_Declaration*)(*pos);
                printf("\n%s", node->ToString().c_str());
                break;
            }
        }
    }
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
    /*Function* FibF = */ CreatePageLoadFunction(M, Context);

    IterateOverCodeBlock(this->astNodeCodeBlock);

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
    FibF->setVisibility(llvm::GlobalValue::VisibilityTypes::DefaultVisibility);
    FibF->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
    FibF->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLExportStorageClass);

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
            
            this->sqlxParser->PrintParsedFileContent();
            
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


