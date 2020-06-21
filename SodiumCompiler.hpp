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

#pragma once

#include "pch.h"

#include "Token.hpp"

#include "ASTNode_Identifier.hpp"
#include "ASTNode_Code_Block.hpp"
#include "ASTNode_Data_Type.hpp"

#include "CompileUnitBase.hpp"
#include "CompileUnitFrmx.hpp"
#include "CompileUnitSqlx.hpp"

typedef void* HANDLE;

extern HANDLE gHeapHandle;

using namespace std;
using namespace llvm;

namespace Sodium {

	enum ParsingPhase {
		PARSING_PHASE_NOTSET,
		PARSING_PHASE_FRMX,
		PARSING_PHASE_FRMX_DONE,
		PARSING_PHASE_SQLX_PRE,
		PARSING_PHASE_SQLX_PRE_DONE,
		PARSING_PHASE_SQLX_POST,
		PARSING_PHASE_SQLX_POST_DONE,
	};

	class SodiumCompiler {

		CompileUnitFrmx		* frmxParser;
		CompileUnitSqlx		* sqlxParser;

		/// <summary>
		/// Parsing phase can be get from this variable. 
		///	Initialy it is set to PARSING_PHASE_NOTSET enum value.
		///	Variable is set before to "XXXX" enum value and then after to "XXXX_DONE" enum value if parsing is successfully for this phase. 
		/// </summary>
		ParsingPhase		parsingPhase;

	protected:
		
		ASTNode_Code_Block	* astNodeCodeBlock;

		void	SetCodeBlock(ASTNode_Code_Block* codeBlock);

	public:
		HANDLE						heapHandle;
		vector<ASTNode_Identifier>	tempVectorForASTNodeIdentifier;


		SodiumCompiler();
		~SodiumCompiler();

		//	returns FALSE if file does not exists or not accessble
		BOOL	ParsePage(char* filePath);
		BOOL	DumpIR();
		void	IncreseLineNumberOuter();

		void	InsertASTNode(ASTNode_Statement* statement);
		void	IterateOverCodeBlock(Module* M, LLVMContext& Context, ASTNode_Code_Block* codeBlock);

		Token	* CreateToken(int tokenCode, int tokenStrLength, const char* tokenStr);

		Function* CreateHtmlFunction(Module* M, LLVMContext& Context);
		Function* CreatePageLoadFunction(Module* M, LLVMContext& Context);

		Function* CreateIRFunction(Module* M, LLVMContext& Context, 
			ASTNodePrimitiveDataType returnType, string functionName, vector<ASTNode_Identifier> parameters);

		friend class CompileUnitBase;
		friend class CompileUnitBaseSqlx;
	};

}





