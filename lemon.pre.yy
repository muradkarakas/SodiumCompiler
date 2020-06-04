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

#include <assert.h>
#include "pre.parser.imp.h"

}

%name preParse

%extra_argument { SodiumCompiler *session }

%type function_body_line    { char * }
%type function_body_lines   { char * }

%token_type { Token }

%default_type { Token }

%token_destructor {
    if ($$.tokenStr != NULL) {
        printf("%s", $$.tokenStr);
        mkFree(session->heapHandle, $$.tokenStr);
        $$.tokenStr = NULL;
    }
}


%syntax_error {

}

start ::= expressions.

expressions ::= expressions expression.
expressions ::= expression.


expression  ::= comment.
expression  ::= globals.
expression  ::= PRE_END_OF_FILE.

comment     ::= PRE_COMMENT_START   PRE_COMMENT_END.

/**  GLOBALS VARIABLES */
globals      ::= PRE_VARIABLE_TYPE_VARCHAR   identifier(AAA) PRE_SEMICOLON.
{
   
    // preTokenDestructor(session, AAA);
}
globals      ::= PRE_VARIABLE_TYPE_BOOL   identifier(AAA) PRE_SEMICOLON.
{
    
    // preTokenDestructor(session, AAA);
}
globals      ::= PRE_VARIABLE_TYPE_NUMBER    identifier(AAA) PRE_SEMICOLON.
{
    
    // preTokenDestructor(session, AAA);
}
globals      ::= PRE_VARIABLE_TYPE_DATE      identifier(AAA) PRE_SEMICOLON.
{
    
    // preTokenDestructor(session, AAA);
}
globals      ::= PRE_VARIABLE_TYPE_REDIS	identifier(AAA) PRE_SEMICOLON.
{
	
	// preTokenDestructor(session, AAA);
}


/**  GLOBALS FUNCTIONS */
globals      ::= PRE_VARIABLE_TYPE_VARCHAR funcdechead.
{
    
}
globals      ::= PRE_VARIABLE_TYPE_NUMBER  funcdechead.
{
    
}
globals      ::= PRE_VARIABLE_TYPE_DATE    funcdechead.
{
    
}
globals      ::= PRE_VARIABLE_TYPE_VOID    funcdechead.
{
    
}
globals      ::= PRE_VARIABLE_TYPE_BOOL    funcdechead.
{
    
}

funcdechead ::= funcdecid parameterlist htsqlfunctionbody.
{
	
}
funcdecid   ::= identifier(BBB).
{
    
    // preTokenDestructor(session, BBB);
}



htsqlfunctionbody   ::= PRE_FUNCTION_BEGIN(AAA) function_body_lines(BBB) PRE_FUNCTION_END(CCC).
{
    printf("\n%s\n%s\n%s", AAA.tokenStr, BBB, CCC.tokenStr); 
    // preTokenDestructor(session, AAA);
    mkFree(session->heapHandle, BBB);
    // preTokenDestructor(session, CCC);
}
htsqlfunctionbody   ::= PRE_FUNCTION_BEGIN(AAA) PRE_FUNCTION_END(CCC).
{
        
    // preTokenDestructor(session, AAA);
    // preTokenDestructor(session, CCC);
}


function_body_lines(RET) ::= function_body_lines(AAA) function_body_line(BBB).
{
    char *p1  = AAA;
    char *p2  = BBB;
    char *ret = mkStrcat(session->heapHandle, __FILE__, __LINE__, p1, p2, NULL);
    RET = ret;
    mkFree(session->heapHandle, p1);
    mkFree(session->heapHandle, p2);
}
function_body_lines ::= function_body_line.

function_body_line(RET)  ::= PRE_FUNCTION_BODY_LINE(BBB).
{
    RET = BBB.tokenStr;
}






/**  Parameter list
*/
parameterlist   ::= openparenthesis parameters closeparenthesis.

parameters      ::= parameters comma parameter.
parameters      ::= parameter.


parameter       ::= PRE_VARIABLE_TYPE_VARCHAR identifier(AAA).
{
    
	// preTokenDestructor(session, AAA);
}
parameter       ::= PRE_VARIABLE_TYPE_NUMBER  identifier(AAA).
{
    
	// preTokenDestructor(session, AAA);
}
parameter       ::= PRE_VARIABLE_TYPE_DATE    identifier(AAA).
{
    
	// preTokenDestructor(session, AAA);
}
parameter       ::= .




/**  identifier
*/
identifier(RET) ::= PRE_IDENTIFIER(A).
{
	Token a = A;
	RET = a;
}


/**  parenthesis
*/
openparenthesis     ::= PRE_OPEN_PARAN.
closeparenthesis    ::= PRE_CLOSE_PARAN.

comma               ::= PRE_COMMA.
