%include
{
  /**
  * This file is part of Sodium Language project
  *
  * Copyright © 2020 Murad Karakaş <muradkarakas@gmail.com>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License v3.0
  * as published by the Free Software Foundation; either
  * version 3 of the License, or (at your option) any later version.
  *
  *	https://choosealicense.com/licenses/gpl-3.0/
  */

#include "pch.h"

#include <stdint.h>
#include <assert.h>

#include "pre.parser.imp.hpp"

#include "ASTNode.hpp"
#include "ASTNode_Data_Type.hpp"
#include "ASTNode_Identifier.hpp"
#include "ASTNode_Statement_Function_Declaration.hpp"
#include "ASTNode_Statement_Variable_Declaration.hpp"

#include "ASTNode_Identifier.hpp"

    using namespace Sodium;
}

%name preParse

%extra_argument { SodiumCompiler * compiler }

%type   function_body_line      { const char * }
%type   function_body_lines     { const char * }
%type   parameterlist           { vector<ASTNode_Identifier> * }

%token_type { Token * }

%token_destructor {
    Token *token = $$;
    preTokenDestructor(token);
}


%syntax_error {
    printf("\nsyntax error");
}

start ::= expressions.

expressions ::= expressions expression.
expressions ::= expression.


expression  ::= comment.
expression  ::= globals.
expression  ::= enters.
expression  ::= PRE_END_OF_FILE.

comment     ::= PRE_COMMENT_START   PRE_COMMENT_END.

/**  GLOBALS VARIABLES */
globals      ::= PRE_VARIABLE_TYPE_VARCHAR  identifier(A)   PRE_SEMICOLON.
{
    ASTNode_Statement_Variable_Declaration* stmVarDeclaration =
        new ASTNode_Statement_Variable_Declaration(A, ASTNodePrimitiveDataType_String, ASTNODE_SCOPE_GLOBAL);

    A->ASTNodeInstance = stmVarDeclaration;

    //  adding variable declaration to the AST
    compiler->InsertASTNode(stmVarDeclaration);

    preTokenDestructor(A);
}

globals      ::= PRE_VARIABLE_TYPE_BOOL     identifier(A)   PRE_SEMICOLON.
{
    ASTNode_Statement_Variable_Declaration* stmVarDeclaration =
        new ASTNode_Statement_Variable_Declaration(A, ASTNodePrimitiveDataType_Bool, ASTNODE_SCOPE_GLOBAL);

    A->ASTNodeInstance = stmVarDeclaration;

    //  adding variable declaration to the AST
    compiler->InsertASTNode(stmVarDeclaration);

    preTokenDestructor(A);
}

globals      ::= PRE_VARIABLE_TYPE_NUMBER   identifier(A)   PRE_SEMICOLON.
{
    ASTNode_Statement_Variable_Declaration* stmVarDeclaration =
        new ASTNode_Statement_Variable_Declaration(A, ASTNodePrimitiveDataType_Number, ASTNODE_SCOPE_GLOBAL);

    A->ASTNodeInstance = stmVarDeclaration;

    //  adding variable declaration to the AST
    compiler->InsertASTNode(stmVarDeclaration);

    preTokenDestructor(A);
}

globals      ::= PRE_VARIABLE_TYPE_DATE     identifier(A)   PRE_SEMICOLON.
{
    ASTNode_Statement_Variable_Declaration* stmVarDeclaration =
        new ASTNode_Statement_Variable_Declaration(A, ASTNodePrimitiveDataType_DateTime, ASTNODE_SCOPE_GLOBAL);

    A->ASTNodeInstance = stmVarDeclaration;

    //  adding variable declaration to the AST
    compiler->InsertASTNode(stmVarDeclaration);

    preTokenDestructor(A);
}

globals      ::= PRE_VARIABLE_TYPE_REDIS	identifier(A)   PRE_SEMICOLON.
{
    ASTNode_Statement_Variable_Declaration* stmVarDeclaration = 
        new ASTNode_Statement_Variable_Declaration(A, ASTNodePrimitiveDataType_Redis, ASTNODE_SCOPE_GLOBAL);

    A->ASTNodeInstance = stmVarDeclaration;

    //  adding variable declaration to the AST
    compiler->InsertASTNode(stmVarDeclaration);

    preTokenDestructor(A);
}


/**  GLOBALS FUNCTIONS */
globals      ::= PRE_VARIABLE_TYPE_VARCHAR funcdechead(A).
{
    ASTNode_Statement_Function_Declaration* funcDecl = (ASTNode_Statement_Function_Declaration*)A->ASTNodeInstance;
    ASTNode_Data_Type* returnDataType = new ASTNode_Data_Type(A, ASTNODE_SCOPE_GLOBAL, ASTNodePrimitiveDataType_String);
    funcDecl->SetFunctionReturnType(returnDataType);
    preTokenDestructor(A);
}

globals      ::= PRE_VARIABLE_TYPE_NUMBER  funcdechead(A).
{
    ASTNode_Statement_Function_Declaration* funcDecl = (ASTNode_Statement_Function_Declaration*)A->ASTNodeInstance;
    ASTNode_Data_Type* returnDataType = new ASTNode_Data_Type(A, ASTNODE_SCOPE_GLOBAL, ASTNodePrimitiveDataType_Number);
    funcDecl->SetFunctionReturnType(returnDataType);
    preTokenDestructor(A);
}

globals      ::= PRE_VARIABLE_TYPE_DATE    funcdechead(A).
{
    ASTNode_Statement_Function_Declaration* funcDecl = (ASTNode_Statement_Function_Declaration*)A->ASTNodeInstance;
    ASTNode_Data_Type* returnDataType = new ASTNode_Data_Type(A, ASTNODE_SCOPE_GLOBAL, ASTNodePrimitiveDataType_DateTime);
    funcDecl->SetFunctionReturnType(returnDataType);
    preTokenDestructor(A);
}

globals      ::= PRE_VARIABLE_TYPE_VOID funcdechead(A).
{
    ASTNode_Statement_Function_Declaration* funcDecl = (ASTNode_Statement_Function_Declaration*) A->ASTNodeInstance;    
    ASTNode_Data_Type* returnDataType = new ASTNode_Data_Type(A, ASTNODE_SCOPE_GLOBAL, ASTNodePrimitiveDataType_Void);    
    funcDecl->SetFunctionReturnType(returnDataType);
    preTokenDestructor(A);
}

globals      ::= PRE_VARIABLE_TYPE_BOOL    funcdechead(A).
{
    ASTNode_Statement_Function_Declaration* funcDecl = (ASTNode_Statement_Function_Declaration*)A->ASTNodeInstance;
    ASTNode_Data_Type* returnDataType = new ASTNode_Data_Type(A, ASTNODE_SCOPE_GLOBAL, ASTNodePrimitiveDataType_Bool);
    funcDecl->SetFunctionReturnType(returnDataType);
    preTokenDestructor(A);
}



funcdechead(RET) ::= funcdecid(A) parameterlist(B) htsqlfunctionbody.
{
    ASTNode_Statement_Function_Declaration* functionDeclaration =
        new ASTNode_Statement_Function_Declaration(A, ASTNODE_SCOPE_GLOBAL, (ASTNode_Identifier*) A->ASTNodeInstance, *B);

    //  adding variable declaration to the AST
    compiler->InsertASTNode(functionDeclaration);
    RET = functionDeclaration->_token;

    preTokenDestructor(A);
}


funcdecid   ::= identifier.



htsqlfunctionbody   ::= PRE_FUNCTION_BEGIN function_body_lines PRE_FUNCTION_END.

htsqlfunctionbody   ::= PRE_FUNCTION_BEGIN PRE_FUNCTION_END.



function_body_lines ::= function_body_lines function_body_line.

function_body_lines ::= function_body_line.

function_body_line  ::= PRE_FUNCTION_BODY_LINE.






/**  Parameter list
*/
parameterlist(RET)   ::= openparenthesis parameters closeparenthesis.
{
    vector<ASTNode_Identifier> * paramList = new vector<ASTNode_Identifier>(compiler->tempVectorForASTNodeIdentifier);
    RET = paramList;
    compiler->tempVectorForASTNodeIdentifier.clear();
}

parameters      ::= parameters comma parameter(A).
{
    Token* parameter = A;
    //  check function has parameter
    if (parameter) {
        compiler->tempVectorForASTNodeIdentifier.push_back(*((ASTNode_Identifier*)parameter->ASTNodeInstance));
    }
}

parameters      ::= parameter(A).
{
    Token* parameter = A;
    //  check function has parameter
    if (parameter) {
        compiler->tempVectorForASTNodeIdentifier.push_back(*((ASTNode_Identifier*)parameter->ASTNodeInstance));
    }
}


parameter(RET)  ::= PRE_VARIABLE_TYPE_VARCHAR identifier(A).
{
    ASTNode_Identifier* identifier = new ASTNode_Identifier(A, ASTNODE_SCOPE_FUNCTION_PARAMETER, ASTNodePrimitiveDataType_String);
    preTokenDestructor(A);
    RET = A;
}

parameter(RET)  ::= PRE_VARIABLE_TYPE_NUMBER  identifier(A).
{
    ASTNode_Identifier* identifier = new ASTNode_Identifier(A, ASTNODE_SCOPE_FUNCTION_PARAMETER, ASTNodePrimitiveDataType_Number);
    preTokenDestructor(A);
    RET = A;
}

parameter(RET)  ::= PRE_VARIABLE_TYPE_DATE    identifier(A).
{
    ASTNode_Identifier* identifier = new ASTNode_Identifier(A, ASTNODE_SCOPE_FUNCTION_PARAMETER, ASTNodePrimitiveDataType_DateTime);
    preTokenDestructor(A);
    RET = A;
}

parameter(RET)   ::= .
{
    //  function has no parameter
    RET = NULL;
    compiler->tempVectorForASTNodeIdentifier.clear();
}

/**  enter
*/
enters ::= enters enter.
enters ::= enter.

enter ::= PRE_ENTER.

/**  identifier
*/
identifier(RET) ::= PRE_IDENTIFIER(A).
{
    ASTNode_Identifier * identifier = new ASTNode_Identifier(A, ASTNODE_SCOPE_GLOBAL);
    preTokenDestructor(A);
    RET = A;
}


/**  parenthesis
*/
openparenthesis     ::= PRE_OPEN_PARAN.
closeparenthesis    ::= PRE_CLOSE_PARAN.

comma               ::= PRE_COMMA.
