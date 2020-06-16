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
#define YY_EXTRA_TYPE Sodium::SodiumCompiler *
#endif

#ifdef __cplusplus
extern "C" {
#endif

	int				prelex(yyscan_t yyscanner);
	int				prelex_init_extra(YY_EXTRA_TYPE user_defined, yyscan_t* scanner);
	int             preget_leng(yyscan_t yyscanner);
	int				prelex_init(yyscan_t* scanner);
	char			* preget_text(yyscan_t yyscanner);
	int             prelex_destroy(yyscan_t yyscanner);

	void preParse(
		void* yyp,           // The parser 
		int yymajor,         // The major token code number 
		Sodium::Token* yyminor,       // The value for the token 
		Sodium::SodiumCompiler*     //	Optional %extra_argument parameter 
	);

	void* preParseAlloc(void* (*allocProc)(size_t));
	void					preset_in(FILE* _in_str, yyscan_t yyscanner);
	void					preParseFree(void* p, void (*freeProc)(void*));

#ifdef __cplusplus
}
#endif
