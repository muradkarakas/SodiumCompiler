%{
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

    #include "lemon.pre.h"
    #include "SodiumCompiler.hpp"
%}

%top{
    #include "pch.h"
    #include <stdint.h>
}

%option extra-type="Sodium::SodiumCompiler *"
%option reentrant
%option noyywrap noinput nounput
%option never-interactive
%option nounistd

%x SC_FUNCTION_PARAMETERS
%x SC_FUNCTION_BODY
%x SC_COMMENT

PRE_ENTER		"\n"
SPACE           [ \t]*
NUMBER          [0-9]*
IDENTIFIER      [a-zA-Z_][a-zA-Z0-9_]*(\.?[a-zA-Z0-9_])*
DECLARE_BODY    [ \t.]*

BEGIN(INITIAL);
%%

{SPACE}char{SPACE}              {
                                    return PRE_VARIABLE_TYPE_VARCHAR;
                                }
{SPACE}int{SPACE}               {
                                    return PRE_VARIABLE_TYPE_NUMBER;
                                }
{SPACE}redis{SPACE}				{
									return PRE_VARIABLE_TYPE_REDIS;
								}
{SPACE}date{SPACE}              {
                                    return PRE_VARIABLE_TYPE_DATE;
                                }
{SPACE}void{SPACE}              {
                                    return PRE_VARIABLE_TYPE_VOID;
                                }
{SPACE}bool{SPACE}              {
                                    return PRE_VARIABLE_TYPE_BOOL;
                                }
{SPACE}";"{SPACE}               {
                                    return PRE_SEMICOLON;
                                }
{SPACE}"/**"{SPACE}             {
                                    BEGIN(SC_COMMENT);
                                    return PRE_COMMENT_START;
                                }
{SPACE}"/*"{SPACE}              {
                                    BEGIN(SC_COMMENT);
                                    return PRE_COMMENT_START;
                                }
{PRE_ENTER}						{
									Sodium::SodiumCompiler *session = yyextra;
									session->IncreseLineNumberOuter();
                                    return PRE_ENTER;
								}
[ \t]*							{
									
                                }
{SPACE}"\("{SPACE}              {
                                    BEGIN(SC_FUNCTION_PARAMETERS);
                                    return PRE_OPEN_PARAN;
                                }
{IDENTIFIER}	                {
                                    return PRE_IDENTIFIER;
                                }
<<EOF>>                         {
                                    return PRE_END_OF_FILE;
                                }

<SC_COMMENT>{
{PRE_ENTER}						{
									Sodium::SodiumCompiler *session = yyextra;
									session->IncreseLineNumberOuter();
                                    //return PRE_ENTER;
								}
"*/"                            {
                                    BEGIN(INITIAL);
                                    return PRE_COMMENT_END;
                                }
.                               {

                                }
}


<SC_FUNCTION_PARAMETERS>{
{SPACE}"char"{SPACE}        {
                                return PRE_VARIABLE_TYPE_VARCHAR;
                            }
{SPACE}"int"{SPACE}         {
                                return PRE_VARIABLE_TYPE_NUMBER;
                            }
{SPACE}"date"{SPACE}        {
                                return PRE_VARIABLE_TYPE_DATE;
                            }
{SPACE}","{SPACE}           {
                                return PRE_COMMA;
                            }
{IDENTIFIER}	            {
                                return PRE_IDENTIFIER;
                            }
{SPACE}"\)"{SPACE}          {
                                BEGIN(SC_FUNCTION_BODY);
                                return PRE_CLOSE_PARAN;
                            }
}


<SC_FUNCTION_BODY>{
{SPACE}"\{"{SPACE}          {
                                return PRE_FUNCTION_BEGIN;
                            }
[ \t]*						{
                                return PRE_FUNCTION_BODY_LINE;
                            }
{SPACE}"} else {"{SPACE}    {
                                return PRE_FUNCTION_BODY_LINE;
                            }
"};"                        {
                                return PRE_FUNCTION_BODY_LINE;
                            }
"}"{SPACE}";"               {
                                return PRE_FUNCTION_BODY_LINE;
                            }
{SPACE}"}"{SPACE}			{
                                BEGIN(INITIAL);
                                return PRE_FUNCTION_END;
                            }
{PRE_ENTER}					{
								Sodium::SodiumCompiler *session = yyextra;
								session->IncreseLineNumberOuter();
								return PRE_FUNCTION_BODY_LINE;
							}
.*                          {
                                return PRE_FUNCTION_BODY_LINE;
                            }
}

.                           {
                                printf("Unrecognized character: %s\n", yytext);
                            }

%%


