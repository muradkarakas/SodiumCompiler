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

#include "SodiumCompiler.h"

typedef void* yyscan_t;

#ifndef YY_EXTRA_TYPE
#define YY_EXTRA_TYPE SodiumCompiler *
#endif


int				htmllex(yyscan_t yyscanner);
int				htmllex_init_extra(YY_EXTRA_TYPE user_defined, yyscan_t* scanner);
int             htmlget_leng(yyscan_t yyscanner);
int				htmllex_init(yyscan_t* scanner);
char		  * htmlget_text(yyscan_t yyscanner);
int             htmllex_destroy(yyscan_t yyscanner);

void htmlParse(
	void* yyp,           // The parser 
	int yymajor,         // The major token code number 
	Token * yyminor,       // The value for the token 
	Sodium::SodiumCompiler*     //	Optional %extra_argument parameter 
);

void		  * htmlParseAlloc(void* (*allocProc)(size_t));
void			htmlset_in(FILE* _in_str, yyscan_t yyscanner);
void			htmlParseFree(void* p, void (*freeProc)(void*));


