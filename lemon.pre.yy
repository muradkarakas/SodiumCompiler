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

%type function_body_line    { const char * }
%type function_body_lines   { const char * }

%token_type { Token * }


%token_destructor {
    /*Token *token = $$;
    if (token) {
        if (token->tokenId == 1 && token->tokenCode != ENTER) {
            printf("\n%4d:", token->line);
        }
        if (token) {
            if (token->tokenCode == ENTER) {
                printf("\n%4d:", token->line);
            }
            else {
                printf("%.*s", token->tokenStrLength, token->tokenStr);
            }
        }
    }*/
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
globals      ::= PRE_VARIABLE_TYPE_VARCHAR  identifier PRE_SEMICOLON.

globals      ::= PRE_VARIABLE_TYPE_BOOL     identifier PRE_SEMICOLON.

globals      ::= PRE_VARIABLE_TYPE_NUMBER   identifier PRE_SEMICOLON.

globals      ::= PRE_VARIABLE_TYPE_DATE     identifier PRE_SEMICOLON.

globals      ::= PRE_VARIABLE_TYPE_REDIS	identifier(A) PRE_SEMICOLON.
{
    ASTNode_Statement_Variable_Declaration* stmVarDeclaration = 
        new ASTNode_Statement_Variable_Declaration(A, ASTNodePrimitiveDataType_Redis, "global");

    A->ASTNodeInstance = stmVarDeclaration;

    //  adding variable declaration to the AST
    compiler->InsertASTNode(stmVarDeclaration);
}


/**  GLOBALS FUNCTIONS */
globals      ::= PRE_VARIABLE_TYPE_VARCHAR funcdechead.

globals      ::= PRE_VARIABLE_TYPE_NUMBER  funcdechead.

globals      ::= PRE_VARIABLE_TYPE_DATE    funcdechead.

globals      ::= PRE_VARIABLE_TYPE_VOID    funcdechead(A).
{
    ASTNode_Statement_Function_Declaration* funcDecl = (ASTNode_Statement_Function_Declaration*)A->ASTNodeInstance;
    
    ASTNode_Data_Type* returnDataType =
        new ASTNode_Data_Type(A, "global", ASTNodePrimitiveDataType_Void);
    
    funcDecl->returnType = returnDataType;
}

globals      ::= PRE_VARIABLE_TYPE_BOOL    funcdechead.


funcdechead(RET) ::= funcdecid(A) parameterlist htsqlfunctionbody.
{
    ASTNode_Statement_Function_Declaration* functionDeclaration =
        new ASTNode_Statement_Function_Declaration(A, "global", (ASTNode_Identifier*) A->ASTNodeInstance);

    //  adding variable declaration to the AST
    compiler->InsertASTNode(functionDeclaration);
    RET = functionDeclaration->_token;
}


funcdecid   ::= identifier.



htsqlfunctionbody   ::= PRE_FUNCTION_BEGIN function_body_lines PRE_FUNCTION_END.

htsqlfunctionbody   ::= PRE_FUNCTION_BEGIN PRE_FUNCTION_END.



function_body_lines ::= function_body_lines function_body_line.

function_body_lines ::= function_body_line.

function_body_line  ::= PRE_FUNCTION_BODY_LINE.






/**  Parameter list
*/
parameterlist   ::= openparenthesis parameters closeparenthesis.

parameters      ::= parameters comma parameter.
parameters      ::= parameter.


parameter       ::= PRE_VARIABLE_TYPE_VARCHAR identifier.

parameter       ::= PRE_VARIABLE_TYPE_NUMBER  identifier.

parameter       ::= PRE_VARIABLE_TYPE_DATE    identifier.

parameter       ::= .


/**  enter
*/
enters ::= enters enter.
enters ::= enter.

enter ::= PRE_ENTER.

/**  identifier
*/
identifier(RET) ::= PRE_IDENTIFIER(A).
{
    ASTNode_Identifier * identifier = new ASTNode_Identifier(A, "global");
    //A->ASTNodeInstance = identifier;
    RET = A;
}


/**  parenthesis
*/
openparenthesis     ::= PRE_OPEN_PARAN.
closeparenthesis    ::= PRE_CLOSE_PARAN.

comma               ::= PRE_COMMA.
