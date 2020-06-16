/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/
#line 2 "lemon.html.yy"
 
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

#include <stdint.h>
#include "html.parser.imp.h"
#include "lemon.html.h" //  must be removed for the first time compile since this file will not be exists

#include <assert.h>

#line 51 "lemon.html.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    htmlParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is htmlParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    htmlParseARG_SDECL     A static variable declaration for the %extra_argument
**    htmlParseARG_PDECL     A parameter declaration for the %extra_argument
**    htmlParseARG_STORE     Code to store %extra_argument into yypParser
**    htmlParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_MIN_REDUCE      Maximum value for reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 248
#define YYACTIONTYPE unsigned short int
#define htmlParseTOKENTYPE  Sodium::Token * 
typedef union {
  int yyinit;
  htmlParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define htmlParseARG_SDECL  Sodium::SodiumCompiler * compiler ;
#define htmlParseARG_PDECL , Sodium::SodiumCompiler * compiler 
#define htmlParseARG_FETCH  Sodium::SodiumCompiler * compiler  = yypParser->compiler 
#define htmlParseARG_STORE yypParser->compiler  = compiler 
#define YYNSTATE             187
#define YYNRULE              291
#define YY_MAX_SHIFT         186
#define YY_MIN_SHIFTREDUCE   467
#define YY_MAX_SHIFTREDUCE   757
#define YY_MIN_REDUCE        758
#define YY_MAX_REDUCE        1048
#define YY_ERROR_ACTION      1049
#define YY_ACCEPT_ACTION     1050
#define YY_NO_ACTION         1051
/************* End control #defines *******************************************/

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if:
**    (1)  The yy_shift_ofst[S]+X value is out of range, or
**    (2)  yy_lookahead[yy_shift_ofst[S]+X] is not equal to X, or
**    (3)  yy_shift_ofst[S] equal YY_SHIFT_USE_DFLT.
** (Implementation note: YY_SHIFT_USE_DFLT is chosen so that
** YY_SHIFT_USE_DFLT+X will be out of range for all possible lookaheads X.
** Hence only tests (1) and (2) need to be evaluated.)
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (880)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   756,    3,    3,    3,    3,    3,    3,    3,    3,    3,
 /*    10 */    93,   71,  140,   81,   71,  181,   24,   24, 1050,   44,
 /*    20 */    44,   61,  511,  185,  182,   44,   44,  568,  135,   24,
 /*    30 */    34,   34,  750,  750,  176,  174,  172,  170,  168,  166,
 /*    40 */   164,  162,  160,  158,  156,  154,  152,  150,  148,  146,
 /*    50 */   144,  142,   39,    4,    4,  606,  606,   72,  756,   76,
 /*    60 */    72,   72,    4,    4,    4,    4,    4,    4,    4,    4,
 /*    70 */   475,  475,  138,  475,  475,  475,  475,  475,  475,   82,
 /*    80 */   499,   62,  180,  756,  740,   34,  757,   14,   88,   34,
 /*    90 */    59,  523,   59,   25,   25,  566,   13,  566,   21,   43,
 /*   100 */   740,   50,  678,   79,  678,   74,   25,  756,   78,  519,
 /*   110 */    73,   88,   20,    5,   49,   24,   58,  683,   19,  140,
 /*   120 */    36,  606,  606,  606,  606,   22,  676,  740,   54,  530,
 /*   130 */    31,  740,   53,   30,  696,   52,   45,  696,  728,   99,
 /*   140 */   728,  176,  174,  172,  170,  168,  166,  164,  162,  160,
 /*   150 */   158,  156,  154,  152,  150,  148,  146,  144,  142,   24,
 /*   160 */   750,  750,  721,  756,    2,  510,   51,   21,  747,  757,
 /*   170 */    50,  616,   79,  635,   74,  505,  750,   78,  505,   73,
 /*   180 */   756,   20,  756,   49,  484,  484,  722,   19,  467,   36,
 /*   190 */   742,  742,   25,  757,  484,  484,  484,  484,  484,  484,
 /*   200 */   484,  103,  101,  742,   72,  684,  135,  729,  684,  729,
 /*   210 */    82,  756,   62,   72,   45,  177,   72,   72,   14,  545,
 /*   220 */   545,   59,  734,   59,   29,   29,   92,   13,  660,  668,
 /*   230 */    43,  675,  756,  682,  756,  689,   25,  618,  756,  701,
 /*   240 */   636,  535,  636,  756,    5,  138,  732,   58,  604,  757,
 /*   250 */   133,  131,  129,  127,  125,  123,  121,  119,  117,  115,
 /*   260 */   113,  111,  109,  107,  105,  756,  757,  712,  757,  545,
 /*   270 */    10,   10,  637,  648,  600,  661,  754,  133,  131,  129,
 /*   280 */   127,  125,  123,  121,  119,  117,  115,  113,  111,  109,
 /*   290 */   107,  105,  500,  494,  495,  613,   29,  757,  756,   42,
 /*   300 */    42,    8,    8,   90,  750,   29,   16,  496,  697,   55,
 /*   310 */   740,  697,  726,    8,    8,    9,    9,  723,  757,  467,
 /*   320 */   757,  713,  740,  726,  757,  468,   90,    9,    9,  757,
 /*   330 */   756,  599,   87,  742,  138,   10,   10,   10,   10,   10,
 /*   340 */    22,   15,   15,   54,  756,   31,   42,   53,   30,   42,
 /*   350 */    52,  757,    8,    8,    8,   41,  638,  638,  650,  650,
 /*   360 */    72,    5,  671,  756,   58,  671,    9,    9,    9,   41,
 /*   370 */   650,  650,   39,  650,  650,    5,  756,  707,   58,  708,
 /*   380 */   742,  742,  524,  524,  757,  650,  650,  737,   26,   26,
 /*   390 */   715,  715,    8,  742,    8,  524,  657,  706,   46,  524,
 /*   400 */    89,   26,   75,   95,   96,  644,    9,  702,    9,  650,
 /*   410 */   650,  650,   41,  705,  695,  747,  757,  518,    5,   91,
 /*   420 */    98,   58,  518,  524,  650,  650,  650,   41,  740,  604,
 /*   430 */   617,  694,  622,    5,  627,   32,   58,  100,   32,   32,
 /*   440 */   633,  687,  638,  638,  638,    7,   17,   17,   57,  757,
 /*   450 */     6,  650,   56,  658,  102,  756,   12,   12,   17,   17,
 /*   460 */   693,   35,  757,  645,   35,   35,  650,  709,   15,  563,
 /*   470 */    15,   15,   23,    2,  104,   51,   46,    1,  664,    1,
 /*   480 */   562,  664,  561,  569,  570,  571,  663,   26,  106,  663,
 /*   490 */   533,   17,  742,  742,  533,   17,  108,   18,   18,  629,
 /*   500 */   629,   40,  560,  750,  750,  742,    5,  603,  110,   58,
 /*   510 */    18,  629,  629,  756,   18,   89,  710,   75,  649,  715,
 /*   520 */   715,   23,    2,  742,   51,  559,    1,  756,    1,  629,
 /*   530 */   629,   26,  517,   18,  112,  691,  756,  517,   18,   12,
 /*   540 */   747,  757,   12,   12,   12,    7,  539,  539,   57,  114,
 /*   550 */     6,  558,   56,  756,  138,  137,  508,  557,  539,  539,
 /*   560 */   521,   27,   27,  536,  569,  570,  571,  617,  720,  622,
 /*   570 */     2,  627,   51,   28,   28,  756,  679,  698,  624,  116,
 /*   580 */   629,   16,   32,  756,   55,  556,  538,  619,  603,  648,
 /*   590 */   534,  661,  629,   16,  534,  539,   55,  699,  472,  757,
 /*   600 */   614,  662,  750,  750,  685,  603,    5,  685,   35,   58,
 /*   610 */   629,   16,  118,  757,   55,  576,  576,  760,  756,  494,
 /*   620 */   495,  747,  757,  756,  756,  760,  555,  603,   11,  756,
 /*   630 */   756,   47,  179,   27,  727,  742,  120,   37,  747,  757,
 /*   640 */    77,  138,   27,   16,   77,   28,   55,  750,   72,  138,
 /*   650 */   178,   72,   72,  756,   28,   16,  690,  741,   55,  680,
 /*   660 */   747,  757,   72,  711,  186,   72,   72,  615,  747,  757,
 /*   670 */   554,  672,  567,   91,  576,   48,   93,   48,   97,   94,
 /*   680 */   138,  634,  628,  636,  138,  669,  623,  470,   61,  636,
 /*   690 */   180,  138,  470,  470,  138,  686,  737,  703,   97,   94,
 /*   700 */   138,  659,  665,  747,  757,   63,  724,  138,   33,  757,
 /*   710 */   757,   33,   33,  625,  740,  757,  620,  184,  183,   83,
 /*   720 */   138,  138,  646,  138,   60,  122,   60,  185,  182,  601,
 /*   730 */   138,  553,  714,   84,  138,  124,  552,  138,   80,  757,
 /*   740 */   501,  181,  666,  725,   65,  626,  750,  126,   66,  573,
 /*   750 */   574,  575,  621,   86,  673,   67,  647,  551,   68,  602,
 /*   760 */   740,  128,  550,  130,   69,  549,  132,  736,  739,  134,
 /*   770 */   598,   70,  136,  597,  740,  139,  596,  141,  143,  595,
 /*   780 */   145,  594,  593,   63,  592,   85,   85,   64,  147,   64,
 /*   790 */   149,  737,  151,  591,  153,   72,  590,  155,  589,   85,
 /*   800 */    85,  588,  157,  159,  587,  161,  586,  585,  163,   72,
 /*   810 */   584,  165,  167,  583,  169,  582,  581,  171,  760,   85,
 /*   820 */    85,  173,   65,  580,  175,   38,   66,  532,  503,  504,
 /*   830 */   515,  760,  516,   67,  514,  513,   68,  760,  760,  760,
 /*   840 */   760,  760,   69,  760,  760,  760,  760,  760,  760,   70,
 /*   850 */   760,  760,  760,  760,  760,   33,  760,  760,  760,  760,
 /*   860 */   760,  760,  737,  737,  760,  737,  760,  760,  760,  760,
 /*   870 */   760,  760,  737,  760,  760,  760,  737,  760,  760,  737,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     7,  102,  103,  104,  105,  106,  107,  108,  109,  110,
 /*    10 */     7,  123,   19,  124,  126,  127,  102,  103,   95,   96,
 /*    20 */    97,   98,  133,  134,  135,  102,  103,   34,   19,  115,
 /*    30 */   102,  103,  102,  103,   41,   42,   43,   44,   45,   46,
 /*    40 */    47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*    50 */    57,   58,   16,  102,  103,  102,  103,   99,    7,  101,
 /*    60 */   102,  103,  111,  112,  113,  114,  115,  116,  117,  118,
 /*    70 */   102,  103,  102,  105,  106,  107,  108,  109,  110,  128,
 /*    80 */     4,  130,    7,    7,   91,  157,   93,  136,  102,  161,
 /*    90 */   139,   15,  141,  102,  103,  158,  145,  160,  199,  148,
 /*   100 */    91,  202,  210,  204,  212,  206,  115,    7,  209,  124,
 /*   110 */   211,  125,  213,  162,  215,  201,  165,   78,  219,   19,
 /*   120 */   221,  168,  169,  170,  171,  172,   76,   91,  175,  144,
 /*   130 */   177,   91,  179,  180,  220,  182,  166,  223,  239,   19,
 /*   140 */   241,   41,   42,   43,   44,   45,   46,   47,   48,   49,
 /*   150 */    50,   51,   52,   53,   54,   55,   56,   57,   58,  245,
 /*   160 */   102,  103,  232,    7,  234,   11,  236,  199,   92,   93,
 /*   170 */   202,  124,  204,  124,  206,  129,  246,  209,  132,  211,
 /*   180 */     7,  213,    7,  215,  102,  103,  235,  219,  237,  221,
 /*   190 */   102,  103,  201,   93,  112,  113,  114,  115,  116,  117,
 /*   200 */   118,   81,   82,  115,  246,  214,   19,  239,  217,  241,
 /*   210 */   128,    7,  130,   99,  244,  101,  102,  103,  136,  102,
 /*   220 */   103,  139,  243,  141,  102,  103,    7,  145,  124,   73,
 /*   230 */   148,   75,    7,   77,    7,   79,  245,   62,    7,   83,
 /*   240 */    67,  124,   67,    7,  162,  102,   90,  165,   60,   93,
 /*   250 */    19,   20,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   260 */    29,   30,   31,   32,   33,    7,   93,  124,   93,  152,
 /*   270 */   102,  103,   68,   69,  163,   71,  102,   19,   20,   21,
 /*   280 */    22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
 /*   290 */    32,   33,    5,    2,    3,  173,  174,   93,    7,  102,
 /*   300 */   103,  102,  103,  102,  246,  183,  184,  121,  220,  187,
 /*   310 */    91,  223,   87,  114,  115,  102,  103,  235,   93,  237,
 /*   320 */    93,   85,   91,   87,   93,   89,  125,  114,  115,   93,
 /*   330 */     7,  163,  164,  245,  102,  167,  168,  169,  170,  171,
 /*   340 */   172,  102,  103,  175,    7,  177,  149,  179,  180,  152,
 /*   350 */   182,   93,  153,  154,  155,  156,  102,  103,  102,  103,
 /*   360 */   246,  162,  205,    7,  165,  208,  153,  154,  155,  156,
 /*   370 */   114,  115,   16,  102,  103,  162,    7,    6,  165,    9,
 /*   380 */   102,  103,  102,  103,   93,  114,  115,  244,  102,  103,
 /*   390 */   102,  103,  193,  115,  195,  115,  197,    9,  166,  119,
 /*   400 */   120,  115,  122,   81,   82,  192,  193,   84,  195,  153,
 /*   410 */   154,  155,  156,    6,    6,   92,   93,  137,  162,  102,
 /*   420 */     9,  165,  142,  143,  153,  154,  155,  156,   91,   60,
 /*   430 */    61,    6,   63,  162,   65,   99,  165,    9,  102,  103,
 /*   440 */   186,  124,  188,  189,  190,  191,  102,  103,  194,   93,
 /*   450 */   196,  195,  198,  197,    9,    7,  102,  103,  114,  115,
 /*   460 */     6,   99,   93,  192,  102,  103,  195,  228,  229,    6,
 /*   470 */   231,  232,  233,  234,    9,  236,  244,  238,  200,  240,
 /*   480 */     6,  203,    6,   35,   36,   37,  200,  201,    9,  203,
 /*   490 */   146,  147,  102,  103,  150,  151,    9,  102,  103,  102,
 /*   500 */   103,  100,    6,  102,  103,  115,  162,   59,    9,  165,
 /*   510 */   115,  102,  103,    7,  119,  120,  228,  122,   70,  231,
 /*   520 */   232,  233,  234,  245,  236,    6,  238,    7,  240,  102,
 /*   530 */   103,  245,  137,  138,    9,  218,    7,  142,  143,  185,
 /*   540 */    92,   93,  188,  189,  190,  191,  102,  103,  194,    9,
 /*   550 */   196,    6,  198,    7,  102,   19,   10,    6,  114,  115,
 /*   560 */    14,  102,  103,   17,   35,   36,   37,   61,  232,   63,
 /*   570 */   234,   65,  236,  102,  103,    7,  124,  124,  181,    9,
 /*   580 */   183,  184,  246,    7,  187,    6,   18,  178,   59,   69,
 /*   590 */   146,   71,  183,  184,  150,  151,  187,  124,    1,   93,
 /*   600 */   173,   72,  102,  103,  214,   59,  162,  217,  246,  165,
 /*   610 */   183,  184,    9,   93,  187,  102,  103,    0,    7,    2,
 /*   620 */     3,   92,   93,    7,    7,  247,    6,   59,  227,    7,
 /*   630 */     7,  230,    8,  174,   88,  245,    9,  124,   92,   93,
 /*   640 */   140,  102,  183,  184,  144,  174,  187,  246,   99,  102,
 /*   650 */   101,  102,  103,    7,  183,  184,   80,   34,  187,  207,
 /*   660 */    92,   93,   99,  124,  101,  102,  103,  124,   92,   93,
 /*   670 */     6,  124,  159,  102,  161,  222,    7,  224,  225,  226,
 /*   680 */   102,  124,   66,   67,  102,   74,   64,   97,   98,   67,
 /*   690 */     7,  102,  102,  103,  102,  124,  244,  224,  225,  226,
 /*   700 */   102,  124,  124,   92,   93,  166,  124,  102,   99,   93,
 /*   710 */    93,  102,  103,  124,   91,   93,  124,   12,   13,  176,
 /*   720 */   102,  102,  124,  102,  131,    9,  133,  134,  135,  124,
 /*   730 */   102,    6,   86,  176,  102,    9,    6,  102,  124,   93,
 /*   740 */   126,  127,  124,  124,  166,  124,  246,    9,  166,   38,
 /*   750 */    39,   40,  124,  176,  207,  166,  124,    6,  166,  124,
 /*   760 */    91,    9,    6,    9,  166,    6,    9,    6,    6,    9,
 /*   770 */     6,  166,    9,    6,   91,    9,    6,    9,    9,    6,
 /*   780 */     9,    6,    6,  244,    6,  242,  243,  216,    9,  218,
 /*   790 */     9,  244,    9,    6,    9,  246,    6,    9,    6,  242,
 /*   800 */   243,    6,    9,    9,    6,    9,    6,    6,    9,  246,
 /*   810 */     6,    9,    9,    6,    9,    6,    6,    9,  247,  242,
 /*   820 */   243,    9,  244,    6,    9,    9,  244,    6,    6,    9,
 /*   830 */     6,  247,    9,  244,    9,    6,  244,  247,  247,  247,
 /*   840 */   247,  247,  244,  247,  247,  247,  247,  247,  247,  244,
 /*   850 */   247,  247,  247,  247,  247,  246,  247,  247,  247,  247,
 /*   860 */   247,  247,  244,  244,  247,  244,  247,  247,  247,  247,
 /*   870 */   247,  247,  244,  247,  247,  247,  244,  247,  247,  244,
};
#define YY_SHIFT_USE_DFLT (880)
#define YY_SHIFT_COUNT    (186)
#define YY_SHIFT_MIN      (-7)
#define YY_SHIFT_MAX      (829)
static const short yy_shift_ofst[] = {
 /*     0 */   291,  156,  546,  156,  546,  369,  529,  448,  529,  448,
 /*    10 */   506,  236,  204,  568,   76,  236,  520,  568,   76,  323,
 /*    20 */   576,  611,  175,  225,  323,  576,  611,  616,  622,  175,
 /*    30 */   173,  173,  225,  646,   -7,  356,  219,  227,  227,  227,
 /*    40 */   227,  100,  231,  258,  617,  623,  623,  337,  219,  337,
 /*    50 */   337,  337,  337,  337,    9,    9,    9,  337,  337,  227,
 /*    60 */   669,  227,    3,  337,  337,  337,  337,  337,  337,  337,
 /*    70 */   337,  683,  227,   51,   51,   75,  711,   36,   39,   50,
 /*    80 */    51,   51,  154,   40,   40,  187,   40,  188,   51,  287,
 /*    90 */    51,  120,  322,  705,  371,  370,  388,  407,  408,  411,
 /*   100 */   425,  428,  454,  445,  463,  465,  474,  479,  476,  487,
 /*   110 */   496,  499,  519,  525,  545,  540,  551,  570,  579,  603,
 /*   120 */   620,  627,  664,  716,  725,  726,  730,  738,  751,  752,
 /*   130 */   756,  754,  759,  757,  761,  760,  762,  763,  536,  764,
 /*   140 */   766,  767,  768,  770,  769,  773,  771,  775,  779,  776,
 /*   150 */   781,  778,  783,  787,  785,  790,  788,  792,  793,  795,
 /*   160 */   794,  798,  796,  800,  799,  801,  802,  804,  803,  807,
 /*   170 */   805,  809,  808,  810,  812,  817,  815,  821,  816,  820,
 /*   180 */   624,  822,  824,  823,  825,  829,  597,
};
#define YY_REDUCE_USE_DFLT (-113)
#define YY_REDUCE_COUNT (90)
#define YY_REDUCE_MIN   (-112)
#define YY_REDUCE_MAX   (635)
static const short yy_reduce_ofst[] = {
 /*     0 */   -77, -101,  -49,  -32,   82,  168,  199,  213,  256,  271,
 /*    10 */   -47,  239,  254,  344,  395,  288,  354,  444,  280,  -86,
 /*    20 */    -9,  286,  122,  336,   88,  390,  278,  397,  409,  427,
 /*    30 */   459,  471,  -70,  401,  513,  500,  453,  -42,  114,  549,
 /*    40 */   563,  -72,  117,  197,  590,  452,  547,  539,  473,  571,
 /*    50 */   578,  582,  589,  592,  543,  557,  577,  598,  605,  362,
 /*    60 */  -111,  609,  593,  143,  317,  618,  619,  621,  628,  632,
 /*    70 */   635,  614,   58,  -30,  232, -112,  -63,  -15, -108,  157,
 /*    80 */   -14,  201,   46,   47,   49,  -21,  104,  111,  174,  186,
 /*    90 */   174,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*    10 */   896, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*    20 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*    30 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1040, 1040, 1040,
 /*    40 */  1040, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*    50 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*    60 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*    70 */  1049, 1049, 1039, 1049, 1049, 1049, 1049, 1049,  968,  961,
 /*    80 */   788,  797, 1049, 1049, 1049, 1024, 1049, 1049,  789, 1049,
 /*    90 */   798, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*   100 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*   110 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*   120 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*   130 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*   140 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*   150 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*   160 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*   170 */  1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 /*   180 */  1049, 1049, 1049, 1049, 1049, 1049, 1049,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  htmlParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void htmlParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "END_OF_FILE",   "TAG_DOCTYPE_HTSQL_DTD",  "TAG_DOCTYPE_HTML",
  "TAG_TREE_OPEN",  "TAG_TREE_BLOCK_CLOSE",  "PROPERTYDATA",  "SPACE",       
  "PROP_TREE_NAME",  "ASSIGMENT",     "TAG_DATALIST_OPEN",  "TAG_DATALIST_BLOCK_CLOSE",
  "PROP_DATALIST_DATALIST_NAME",  "PROP_DATALIST_CONNECTION_NAME",  "TAG_CONTROLBLOCK_OPEN",  "TAG_CONTROLBLOCK_CLOSE",
  "PROP_CONTROLBLOCK_BLOCK_NAME",  "TAG_DATABLOCK_OPEN",  "TAG_DATABLOCK_BLOCK_CLOSE",  "PROPERTYID",  
  "PROP_BLOCK_JOIN_CONDITION",  "PROP_BLOCK_CONNECTION_NAME",  "PROP_BLOCK_AUTO_GENERATED_COLUMNS",  "PROP_BLOCK_RECORD_COUNT",
  "PROP_BLOCK_DATA_SOURCE_NAME",  "PROP_BLOCK_DATA_SCHEMA_NAME",  "PROP_BLOCK_BLOCK_NAME",  "PROP_BLOCK_KEY_COLUMN_NAME",
  "PROP_BLOCK_MASTER_BLOCK_NAME",  "PROP_BLOCK_INSERT_ALLOWED",  "PROP_BLOCK_DELETE_ALLOWED",  "PROP_BLOCK_UPDATE_ALLOWED",
  "PROP_BLOCK_WHERE_CLAUSE",  "PROP_BLOCK_OREDERBY_CLAUSE",  "TAG_SHORT_CLOSE",  "TAG_INPUT_OPEN",
  "TAG_SELECT_OPEN",  "TAG_TEXTAREA_OPEN",  "TAG_INPUT_BLOCK_CLOSE",  "TAG_SELECT_BLOCK_CLOSE",
  "TAG_TEXTAREA_BLOCK_CLOSE",  "PROP_INPUT_CHECKED_VALUE",  "PROP_INPUT_UNCHECKED_VALUE",  "PROP_INPUT_NAME",
  "PROP_INPUT_SEQUENCE_NAME",  "PROP_INPUT_SEQUENCE_SCHEMA_NAME",  "PROP_INPUT_MASTER_ITEM_NAME",  "PROP_INPUT_TYPE",
  "PROP_INPUT_VALUE",  "PROP_INPUT_DEFAULT_VALUE",  "PROP_INPUT_COLUMN_NAME",  "PROP_INPUT_FORMAT_MASK",
  "PROP_INPUT_DATA_TYPE",  "PROP_INPUT_MAX_LENGTH",  "PROP_INPUT_INSERT_ALLOWED",  "PROP_INPUT_UPDATE_ALLOWED",
  "PROP_INPUT_DATALIST_NAME",  "PROP_INPUT_LOOKUP_ITEM_NAME",  "PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME",  "TAG_TABLE_OPEN",
  "TAG_TABLE_BLOCK_CLOSE",  "TAG_THEAD_OPEN",  "TAG_THEAD_BLOCK_CLOSE",  "TAG_TFOOT_OPEN",
  "TAG_TFOOT_BLOCK_CLOSE",  "TAG_TBODY_OPEN",  "TAG_TBODY_BLOCK_CLOSE",  "TAG_TR_OPEN", 
  "TAG_TR_BLOCK_CLOSE",  "TAG_TD_OPEN",   "TAG_TD_BLOCK_CLOSE",  "TAG_TH_OPEN", 
  "TAG_TH_BLOCK_CLOSE",  "TAG_TITLE_OPEN",  "TAG_TITLE_BLOCK_CLOSE",  "TAG_LINK_OPEN",
  "TAG_LINK_BLOCK_CLOSE",  "TAG_META_OPEN",  "TAG_META_BLOCK_CLOSE",  "TAG_STYLE_OPEN",
  "TAG_STYLE_BLOCK_CLOSE",  "PROPERTYID_SCRIPT_SRC",  "PROPERTYID_SCRIPT_TYPE",  "TAG_SCRIPT_OPEN",
  "TAG_SCRIPT_BLOCK_CLOSE",  "TAG_HTML_BLOCK_CLOSE",  "TAG_HTML_OPEN",  "TAG_BODY_OPEN",
  "TAG_BODY_BLOCK_CLOSE",  "TAG_HEAD_OPEN",  "TAG_HEAD_BLOCK_CLOSE",  "TAG_CLOSE",   
  "HTMLTEXT",      "HTML_ENTER",    "error",         "start",       
  "expressions",   "expression",    "tagdoctype",    "spaces_enters",
  "taghtml",       "opt__spaces_enters",  "space",         "enter",       
  "tagheadcontents",  "tagheadcontent",  "tagtitle",      "tagscript",   
  "tagstyle",      "taglink",       "tagmeta",       "tagbodycontents",
  "tagbodycontent",  "htsqls",        "tagtable",      "htmltext",    
  "tagdatablock",  "tagcontrolblock",  "tagdatalist",   "tagtree",     
  "tagtreefullopen",  "tagtreeblockclosefull",  "tagtreeopen",   "tagtreeproperties",
  "tagclosechar",  "spaces",        "tagtreeproperty",  "tagtreepropertyid",
  "tagdatalistfullopen",  "tagdatalistblockclosefull",  "tagdatalistopen",  "datalistproperties",
  "tagdatalistblockclose",  "datalistproperty",  "tagdatalistpropertyid",  "tagdatalistpropertyconnectionname",
  "tagcontrolblockfullopen",  "tagcontrolblockclosefull",  "tagcontrolblockcontents",  "tagcontrolblockopen",
  "tagcontrolblockproperties",  "tagcontrolblockopen_",  "tagcontrolblockblockclose",  "tagcontrolblockcontent",
  "tagcontrolblockproperty",  "tagdatablockfullopen",  "tagdatablockblockclosefull",  "tagdatablockcontents",
  "tagdatablockopen",  "tagdatablockproperties",  "tagdatablockblockclose",  "tagdatablockcontent",
  "tagdatablockproperty",  "taginput",      "taginput_with_block",  "taginput_without_block",
  "taginputopen",  "taginputproperties",  "taginputblockclosefull",  "taginputshortclose",
  "taginputblockclose",  "taginputproperty",  "tagtablefullopen",  "tagtableblockclosefull",
  "tablecontent",  "tagtableopen",  "tagproperties",  "tablecontentparts",
  "tablecontentpart",  "tagthead",      "tagtbody",      "tagtfoot",    
  "tagtheadfullopen",  "tagtheadblockclosefull",  "tagtablerows",  "tagtheadopen",
  "tagpropertieswithreturnvaluesall",  "tagtfootfullopen",  "tagtfootblockclosefull",  "tagtfootopen",
  "tagtbodyfullopen",  "tagtbodyblockclosefull",  "tagtbodyopen",  "tagtablerow", 
  "tagtablerowfullopen",  "tagtablecols",  "tagtablerowblockclosefull",  "tagtablerowopen",
  "tagtablecol",   "tagtablecoltd",  "tagtablecolth",  "tagtablecoltdfullopen",
  "tagtablecoltdblockclosefull",  "tagtablecolcontents",  "tagtablecoltdopen",  "tagtablecolcontent",
  "tagtablecolthfullopen",  "tagtablecolthblockclosefull",  "tagtablecolthopen",  "tagtitlefullopen",
  "tagtitleblockclosefull",  "htmlandspaces",  "tagtitleopen",  "tagtitleblockclose",
  "taglinkfullopen",  "taglinkblockclosefull",  "taglinkopen",   "tagshortclose",
  "taglinkblockclose",  "tagmetafullopen",  "tagmetablockclosefull",  "tagmetaopen", 
  "tagmetablockclose",  "tagstylefullopen",  "tagstyleblockclosefull",  "tagstyleopen",
  "tagstyleproperties",  "tagstyleblockclose",  "tagstyleproperty",  "tagscriptfullopen",
  "tagscriptblockclosefull",  "tagscriptopen",  "tagscriptproperties",  "tagscriptblockclose",
  "tagscriptproperty",  "tagscriptpropertyscripttype",  "tagscriptpropertysrc",  "taghtmlfullopen",
  "taghtmlblockclosefull",  "taghtmlcontents",  "taghtmlopen",   "taghtmlcontent",
  "tagbody",       "taghead",       "tagbodyfullopen",  "tagbodyblockclosefull",
  "tagbodyopen",   "tagbodyblockclose",  "tagheadfullopen",  "tagheadblockclosefull",
  "tagheadopen",   "tagheadblockclose",  "tagpropertieswithreturnvalues",  "tagpropertywithreturnvalue",
  "tagproperty",   "htmlandspace",  "spaces_enter",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "tagbodyblockclosefull ::= tagbodyblockclose",
 /*   1 */ "tagheadopen ::= TAG_HEAD_OPEN",
 /*   2 */ "start ::= expressions",
 /*   3 */ "expressions ::= expressions expression",
 /*   4 */ "expressions ::= expression",
 /*   5 */ "expression ::= tagdoctype spaces_enters taghtml opt__spaces_enters END_OF_FILE",
 /*   6 */ "expression ::= space",
 /*   7 */ "expression ::= enter",
 /*   8 */ "tagheadcontents ::= tagheadcontents tagheadcontent",
 /*   9 */ "tagheadcontents ::= tagheadcontent",
 /*  10 */ "tagheadcontent ::= space",
 /*  11 */ "tagheadcontent ::= enter",
 /*  12 */ "tagheadcontent ::= tagtitle",
 /*  13 */ "tagheadcontent ::= tagscript",
 /*  14 */ "tagheadcontent ::= tagstyle",
 /*  15 */ "tagheadcontent ::= taglink",
 /*  16 */ "tagheadcontent ::= tagmeta",
 /*  17 */ "tagbodycontents ::= tagbodycontents tagbodycontent",
 /*  18 */ "tagbodycontents ::= tagbodycontent",
 /*  19 */ "tagbodycontent ::= htsqls",
 /*  20 */ "tagbodycontent ::= tagtable",
 /*  21 */ "tagbodycontent ::= space",
 /*  22 */ "tagbodycontent ::= enter",
 /*  23 */ "tagbodycontent ::= htmltext",
 /*  24 */ "htsqls ::= tagdatablock",
 /*  25 */ "htsqls ::= tagcontrolblock",
 /*  26 */ "htsqls ::= tagdatalist",
 /*  27 */ "tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD",
 /*  28 */ "tagdoctype ::= TAG_DOCTYPE_HTML",
 /*  29 */ "tagtree ::= tagtreefullopen tagtreeblockclosefull",
 /*  30 */ "tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar",
 /*  31 */ "tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces",
 /*  32 */ "tagtreeopen ::= TAG_TREE_OPEN",
 /*  33 */ "tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE",
 /*  34 */ "tagtreeproperties ::= tagtreeproperties tagtreeproperty",
 /*  35 */ "tagtreeproperties ::= tagtreeproperty",
 /*  36 */ "tagtreeproperty ::= tagtreepropertyid PROPERTYDATA",
 /*  37 */ "tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT",
 /*  38 */ "tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull",
 /*  39 */ "tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar",
 /*  40 */ "tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces",
 /*  41 */ "tagdatalistopen ::= TAG_DATALIST_OPEN",
 /*  42 */ "tagdatalistblockclosefull ::= tagdatalistblockclose",
 /*  43 */ "tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE",
 /*  44 */ "datalistproperties ::= datalistproperties datalistproperty",
 /*  45 */ "datalistproperties ::= datalistproperty",
 /*  46 */ "datalistproperty ::= tagdatalistpropertyid PROPERTYDATA",
 /*  47 */ "tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT",
 /*  48 */ "datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA",
 /*  49 */ "tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT",
 /*  50 */ "tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull",
 /*  51 */ "tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull",
 /*  52 */ "tagcontrolblockfullopen ::= tagcontrolblockopen spaces_enters tagcontrolblockproperties tagclosechar",
 /*  53 */ "tagcontrolblockopen ::= tagcontrolblockopen_",
 /*  54 */ "tagcontrolblockopen_ ::= TAG_CONTROLBLOCK_OPEN",
 /*  55 */ "tagcontrolblockclosefull ::= tagcontrolblockblockclose",
 /*  56 */ "tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE",
 /*  57 */ "tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent",
 /*  58 */ "tagcontrolblockcontents ::= tagcontrolblockcontent",
 /*  59 */ "tagcontrolblockcontent ::= tagtree",
 /*  60 */ "tagcontrolblockcontent ::= space",
 /*  61 */ "tagcontrolblockcontent ::= enter",
 /*  62 */ "tagcontrolblockcontent ::= htmltext",
 /*  63 */ "tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty",
 /*  64 */ "tagcontrolblockproperties ::= tagcontrolblockproperty",
 /*  65 */ "tagcontrolblockproperty ::= PROP_CONTROLBLOCK_BLOCK_NAME opt__spaces_enters ASSIGMENT opt__spaces_enters PROPERTYDATA",
 /*  66 */ "tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull",
 /*  67 */ "tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull",
 /*  68 */ "tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar",
 /*  69 */ "tagdatablockopen ::= TAG_DATABLOCK_OPEN",
 /*  70 */ "tagdatablockblockclosefull ::= tagdatablockblockclose",
 /*  71 */ "tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE",
 /*  72 */ "tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent",
 /*  73 */ "tagdatablockcontents ::= tagdatablockcontent",
 /*  74 */ "tagdatablockcontent ::= tagtable",
 /*  75 */ "tagdatablockcontent ::= space",
 /*  76 */ "tagdatablockcontent ::= enter",
 /*  77 */ "tagdatablockcontent ::= htmltext",
 /*  78 */ "tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty",
 /*  79 */ "tagdatablockproperties ::= tagdatablockproperty",
 /*  80 */ "tagdatablockproperty ::= space",
 /*  81 */ "tagdatablockproperty ::= enter",
 /*  82 */ "tagdatablockproperty ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /*  83 */ "tagdatablockproperty ::= PROP_BLOCK_JOIN_CONDITION ASSIGMENT PROPERTYDATA",
 /*  84 */ "tagdatablockproperty ::= PROP_BLOCK_CONNECTION_NAME ASSIGMENT PROPERTYDATA",
 /*  85 */ "tagdatablockproperty ::= PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT PROPERTYDATA",
 /*  86 */ "tagdatablockproperty ::= PROP_BLOCK_RECORD_COUNT ASSIGMENT PROPERTYDATA",
 /*  87 */ "tagdatablockproperty ::= PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT PROPERTYDATA",
 /*  88 */ "tagdatablockproperty ::= PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT PROPERTYDATA",
 /*  89 */ "tagdatablockproperty ::= PROP_BLOCK_BLOCK_NAME ASSIGMENT PROPERTYDATA",
 /*  90 */ "tagdatablockproperty ::= PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT PROPERTYDATA",
 /*  91 */ "tagdatablockproperty ::= PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT PROPERTYDATA",
 /*  92 */ "tagdatablockproperty ::= PROP_BLOCK_INSERT_ALLOWED ASSIGMENT PROPERTYDATA",
 /*  93 */ "tagdatablockproperty ::= PROP_BLOCK_DELETE_ALLOWED ASSIGMENT PROPERTYDATA",
 /*  94 */ "tagdatablockproperty ::= PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT PROPERTYDATA",
 /*  95 */ "tagdatablockproperty ::= PROP_BLOCK_WHERE_CLAUSE ASSIGMENT PROPERTYDATA",
 /*  96 */ "tagdatablockproperty ::= PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT PROPERTYDATA",
 /*  97 */ "taginput ::= taginput_with_block",
 /*  98 */ "taginput ::= taginput_without_block",
 /*  99 */ "taginput_with_block ::= taginputopen taginputproperties tagclosechar opt__spaces_enters taginputblockclosefull",
 /* 100 */ "taginput_without_block ::= taginputopen taginputproperties taginputshortclose",
 /* 101 */ "taginputshortclose ::= TAG_SHORT_CLOSE",
 /* 102 */ "taginputopen ::= TAG_INPUT_OPEN",
 /* 103 */ "taginputopen ::= TAG_SELECT_OPEN",
 /* 104 */ "taginputopen ::= TAG_TEXTAREA_OPEN",
 /* 105 */ "taginputblockclosefull ::= taginputblockclose",
 /* 106 */ "taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE",
 /* 107 */ "taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE",
 /* 108 */ "taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE",
 /* 109 */ "taginputproperties ::= taginputproperties taginputproperty",
 /* 110 */ "taginputproperties ::= taginputproperty",
 /* 111 */ "taginputproperty ::= space",
 /* 112 */ "taginputproperty ::= enter",
 /* 113 */ "taginputproperty ::= PROP_INPUT_CHECKED_VALUE ASSIGMENT PROPERTYDATA",
 /* 114 */ "taginputproperty ::= PROP_INPUT_UNCHECKED_VALUE ASSIGMENT PROPERTYDATA",
 /* 115 */ "taginputproperty ::= PROP_INPUT_NAME ASSIGMENT PROPERTYDATA",
 /* 116 */ "taginputproperty ::= PROP_INPUT_SEQUENCE_NAME ASSIGMENT PROPERTYDATA",
 /* 117 */ "taginputproperty ::= PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT PROPERTYDATA",
 /* 118 */ "taginputproperty ::= PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT PROPERTYDATA",
 /* 119 */ "taginputproperty ::= PROP_INPUT_TYPE ASSIGMENT PROPERTYDATA",
 /* 120 */ "taginputproperty ::= PROP_INPUT_VALUE ASSIGMENT PROPERTYDATA",
 /* 121 */ "taginputproperty ::= PROP_INPUT_DEFAULT_VALUE ASSIGMENT PROPERTYDATA",
 /* 122 */ "taginputproperty ::= PROP_INPUT_COLUMN_NAME ASSIGMENT PROPERTYDATA",
 /* 123 */ "taginputproperty ::= PROP_INPUT_FORMAT_MASK ASSIGMENT PROPERTYDATA",
 /* 124 */ "taginputproperty ::= PROP_INPUT_DATA_TYPE ASSIGMENT PROPERTYDATA",
 /* 125 */ "taginputproperty ::= PROP_INPUT_MAX_LENGTH ASSIGMENT PROPERTYDATA",
 /* 126 */ "taginputproperty ::= PROP_INPUT_INSERT_ALLOWED ASSIGMENT PROPERTYDATA",
 /* 127 */ "taginputproperty ::= PROP_INPUT_UPDATE_ALLOWED ASSIGMENT PROPERTYDATA",
 /* 128 */ "taginputproperty ::= PROP_INPUT_DATALIST_NAME ASSIGMENT PROPERTYDATA",
 /* 129 */ "taginputproperty ::= PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT PROPERTYDATA",
 /* 130 */ "taginputproperty ::= PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT PROPERTYDATA",
 /* 131 */ "taginputproperty ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 132 */ "tagtable ::= tagtablefullopen tagtableblockclosefull",
 /* 133 */ "tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull",
 /* 134 */ "tagtablefullopen ::= tagtableopen tagclosechar",
 /* 135 */ "tagtablefullopen ::= tagtableopen tagproperties tagclosechar",
 /* 136 */ "tagtableopen ::= TAG_TABLE_OPEN",
 /* 137 */ "tagtableblockclosefull ::= TAG_TABLE_BLOCK_CLOSE",
 /* 138 */ "tablecontent ::= tablecontentparts",
 /* 139 */ "tablecontentparts ::= tablecontentparts tablecontentpart",
 /* 140 */ "tablecontentparts ::= tablecontentpart",
 /* 141 */ "tablecontentpart ::= space",
 /* 142 */ "tablecontentpart ::= enter",
 /* 143 */ "tablecontentpart ::= tagthead",
 /* 144 */ "tablecontentpart ::= tagtbody",
 /* 145 */ "tablecontentpart ::= tagtfoot",
 /* 146 */ "tagthead ::= tagtheadfullopen tagtheadblockclosefull",
 /* 147 */ "tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull",
 /* 148 */ "tagtheadfullopen ::= tagtheadopen tagclosechar",
 /* 149 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 150 */ "tagtheadopen ::= TAG_THEAD_OPEN",
 /* 151 */ "tagtheadblockclosefull ::= TAG_THEAD_BLOCK_CLOSE",
 /* 152 */ "tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull",
 /* 153 */ "tagtfootfullopen ::= tagtfootopen tagclosechar",
 /* 154 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar",
 /* 155 */ "tagtfootopen ::= TAG_TFOOT_OPEN",
 /* 156 */ "tagtfootblockclosefull ::= TAG_TFOOT_BLOCK_CLOSE",
 /* 157 */ "tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull",
 /* 158 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar",
 /* 159 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar",
 /* 160 */ "tagtbodyopen ::= TAG_TBODY_OPEN",
 /* 161 */ "tagtbodyblockclosefull ::= TAG_TBODY_BLOCK_CLOSE",
 /* 162 */ "tagtablerows ::= tagtablerows tagtablerow",
 /* 163 */ "tagtablerows ::= tagtablerow",
 /* 164 */ "tagtablerow ::= space",
 /* 165 */ "tagtablerow ::= enter",
 /* 166 */ "tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull",
 /* 167 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar",
 /* 168 */ "tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 169 */ "tagtablerowopen ::= TAG_TR_OPEN",
 /* 170 */ "tagtablerowblockclosefull ::= TAG_TR_BLOCK_CLOSE",
 /* 171 */ "tagtablecols ::= tagtablecols tagtablecol",
 /* 172 */ "tagtablecols ::= tagtablecol",
 /* 173 */ "tagtablecol ::= space",
 /* 174 */ "tagtablecol ::= enter",
 /* 175 */ "tagtablecol ::= tagtablecoltd",
 /* 176 */ "tagtablecol ::= tagtablecolth",
 /* 177 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull",
 /* 178 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull",
 /* 179 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar",
 /* 180 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar",
 /* 181 */ "tagtablecoltdopen ::= TAG_TD_OPEN",
 /* 182 */ "tagtablecoltdblockclosefull ::= TAG_TD_BLOCK_CLOSE",
 /* 183 */ "tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent",
 /* 184 */ "tagtablecolcontents ::= tagtablecolcontent",
 /* 185 */ "tagtablecolcontent ::= taginput",
 /* 186 */ "tagtablecolcontent ::= htmltext",
 /* 187 */ "tagtablecolcontent ::= tagtable",
 /* 188 */ "tagtablecolcontent ::= space",
 /* 189 */ "tagtablecolcontent ::= enter",
 /* 190 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull",
 /* 191 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull",
 /* 192 */ "tagtablecolthfullopen ::= tagtablecolthopen tagclosechar",
 /* 193 */ "tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 194 */ "tagtablecolthopen ::= TAG_TH_OPEN",
 /* 195 */ "tagtablecolthblockclosefull ::= TAG_TH_BLOCK_CLOSE",
 /* 196 */ "tagtitle ::= tagtitlefullopen tagtitleblockclosefull",
 /* 197 */ "tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull",
 /* 198 */ "tagtitlefullopen ::= tagtitleopen tagclosechar",
 /* 199 */ "tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar",
 /* 200 */ "tagtitleblockclosefull ::= tagtitleblockclose",
 /* 201 */ "tagtitleopen ::= TAG_TITLE_OPEN",
 /* 202 */ "tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE",
 /* 203 */ "taglink ::= taglinkfullopen",
 /* 204 */ "taglink ::= taglinkfullopen taglinkblockclosefull",
 /* 205 */ "taglinkfullopen ::= taglinkopen tagproperties tagclosechar",
 /* 206 */ "taglinkfullopen ::= taglinkopen tagproperties tagshortclose",
 /* 207 */ "taglinkblockclosefull ::= taglinkblockclose",
 /* 208 */ "taglinkopen ::= TAG_LINK_OPEN",
 /* 209 */ "taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE",
 /* 210 */ "tagmeta ::= tagmetafullopen",
 /* 211 */ "tagmeta ::= tagmetafullopen tagmetablockclosefull",
 /* 212 */ "tagmetafullopen ::= tagmetaopen tagproperties tagclosechar",
 /* 213 */ "tagmetafullopen ::= tagmetaopen tagproperties tagshortclose",
 /* 214 */ "tagmetablockclosefull ::= tagmetablockclose",
 /* 215 */ "tagmetaopen ::= TAG_META_OPEN",
 /* 216 */ "tagmetablockclose ::= TAG_META_BLOCK_CLOSE",
 /* 217 */ "tagstyle ::= tagstylefullopen tagstyleblockclosefull",
 /* 218 */ "tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull",
 /* 219 */ "tagstylefullopen ::= tagstyleopen tagclosechar",
 /* 220 */ "tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar",
 /* 221 */ "tagstyleblockclosefull ::= tagstyleblockclose",
 /* 222 */ "tagstyleopen ::= TAG_STYLE_OPEN",
 /* 223 */ "tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE",
 /* 224 */ "tagstyleproperties ::= tagstyleproperties tagstyleproperty",
 /* 225 */ "tagstyleproperties ::= tagstyleproperty",
 /* 226 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA",
 /* 227 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA",
 /* 228 */ "tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 229 */ "tagscript ::= tagscriptfullopen tagscriptblockclosefull",
 /* 230 */ "tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull",
 /* 231 */ "tagscriptfullopen ::= tagscriptopen tagclosechar",
 /* 232 */ "tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar",
 /* 233 */ "tagscriptblockclosefull ::= tagscriptblockclose",
 /* 234 */ "tagscriptopen ::= TAG_SCRIPT_OPEN",
 /* 235 */ "tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE",
 /* 236 */ "tagscriptproperties ::= tagscriptproperties tagscriptproperty",
 /* 237 */ "tagscriptproperties ::= tagscriptproperty",
 /* 238 */ "tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA",
 /* 239 */ "tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT",
 /* 240 */ "tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA",
 /* 241 */ "tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT",
 /* 242 */ "taghtml ::= taghtmlfullopen taghtmlblockclosefull",
 /* 243 */ "taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull",
 /* 244 */ "taghtmlfullopen ::= taghtmlopen tagclosechar",
 /* 245 */ "taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar",
 /* 246 */ "taghtmlblockclosefull ::= TAG_HTML_BLOCK_CLOSE",
 /* 247 */ "taghtmlopen ::= TAG_HTML_OPEN",
 /* 248 */ "taghtmlcontents ::= taghtmlcontents taghtmlcontent",
 /* 249 */ "taghtmlcontents ::= taghtmlcontent",
 /* 250 */ "taghtmlcontent ::= space",
 /* 251 */ "taghtmlcontent ::= enter",
 /* 252 */ "taghtmlcontent ::= tagbody",
 /* 253 */ "taghtmlcontent ::= taghead tagbody",
 /* 254 */ "taghtmlcontent ::= taghead spaces_enters tagbody",
 /* 255 */ "tagbody ::= tagbodyfullopen tagbodyblockclosefull",
 /* 256 */ "tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull",
 /* 257 */ "tagbodyfullopen ::= tagbodyopen tagclosechar",
 /* 258 */ "tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar",
 /* 259 */ "tagbodyopen ::= TAG_BODY_OPEN",
 /* 260 */ "tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE",
 /* 261 */ "taghead ::= tagheadfullopen tagheadblockclosefull",
 /* 262 */ "taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull",
 /* 263 */ "tagheadfullopen ::= tagheadopen",
 /* 264 */ "tagheadblockclosefull ::= tagheadblockclose",
 /* 265 */ "tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE",
 /* 266 */ "tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues",
 /* 267 */ "tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue",
 /* 268 */ "tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue",
 /* 269 */ "tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 270 */ "tagproperties ::= tagproperties tagproperty",
 /* 271 */ "tagproperties ::= tagproperty",
 /* 272 */ "tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 273 */ "tagclosechar ::= TAG_CLOSE",
 /* 274 */ "tagshortclose ::= TAG_SHORT_CLOSE",
 /* 275 */ "htmlandspaces ::= htmlandspaces htmlandspace",
 /* 276 */ "htmlandspaces ::= htmlandspace",
 /* 277 */ "htmlandspace ::= htmltext",
 /* 278 */ "htmlandspace ::= space",
 /* 279 */ "htmlandspace ::= enter",
 /* 280 */ "htmltext ::= HTMLTEXT",
 /* 281 */ "opt__spaces_enters ::= spaces_enters",
 /* 282 */ "opt__spaces_enters ::=",
 /* 283 */ "spaces_enters ::= spaces_enters spaces_enter",
 /* 284 */ "spaces_enters ::= spaces_enter",
 /* 285 */ "spaces_enter ::= space",
 /* 286 */ "spaces_enter ::= enter",
 /* 287 */ "spaces ::= spaces space",
 /* 288 */ "spaces ::= space",
 /* 289 */ "space ::= SPACE",
 /* 290 */ "enter ::= HTML_ENTER",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to htmlParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to htmlParse and htmlParseFree.
*/
void *htmlParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( pParser ){
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yytos = NULL;
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    if( yyGrowStack(pParser) ){
      pParser->yystack = &pParser->yystk0;
      pParser->yystksz = 1;
    }
#endif
#ifndef YYNOERRORRECOVERY
    pParser->yyerrcnt = -1;
#endif
    pParser->yytos = pParser->yystack;
    pParser->yystack[0].stateno = 0;
    pParser->yystack[0].major = 0;
  }
  return pParser;
}

/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  htmlParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
      /* TERMINAL Destructor */
    case 1: /* END_OF_FILE */
    case 2: /* TAG_DOCTYPE_HTSQL_DTD */
    case 3: /* TAG_DOCTYPE_HTML */
    case 4: /* TAG_TREE_OPEN */
    case 5: /* TAG_TREE_BLOCK_CLOSE */
    case 6: /* PROPERTYDATA */
    case 7: /* SPACE */
    case 8: /* PROP_TREE_NAME */
    case 9: /* ASSIGMENT */
    case 10: /* TAG_DATALIST_OPEN */
    case 11: /* TAG_DATALIST_BLOCK_CLOSE */
    case 12: /* PROP_DATALIST_DATALIST_NAME */
    case 13: /* PROP_DATALIST_CONNECTION_NAME */
    case 14: /* TAG_CONTROLBLOCK_OPEN */
    case 15: /* TAG_CONTROLBLOCK_CLOSE */
    case 16: /* PROP_CONTROLBLOCK_BLOCK_NAME */
    case 17: /* TAG_DATABLOCK_OPEN */
    case 18: /* TAG_DATABLOCK_BLOCK_CLOSE */
    case 19: /* PROPERTYID */
    case 20: /* PROP_BLOCK_JOIN_CONDITION */
    case 21: /* PROP_BLOCK_CONNECTION_NAME */
    case 22: /* PROP_BLOCK_AUTO_GENERATED_COLUMNS */
    case 23: /* PROP_BLOCK_RECORD_COUNT */
    case 24: /* PROP_BLOCK_DATA_SOURCE_NAME */
    case 25: /* PROP_BLOCK_DATA_SCHEMA_NAME */
    case 26: /* PROP_BLOCK_BLOCK_NAME */
    case 27: /* PROP_BLOCK_KEY_COLUMN_NAME */
    case 28: /* PROP_BLOCK_MASTER_BLOCK_NAME */
    case 29: /* PROP_BLOCK_INSERT_ALLOWED */
    case 30: /* PROP_BLOCK_DELETE_ALLOWED */
    case 31: /* PROP_BLOCK_UPDATE_ALLOWED */
    case 32: /* PROP_BLOCK_WHERE_CLAUSE */
    case 33: /* PROP_BLOCK_OREDERBY_CLAUSE */
    case 34: /* TAG_SHORT_CLOSE */
    case 35: /* TAG_INPUT_OPEN */
    case 36: /* TAG_SELECT_OPEN */
    case 37: /* TAG_TEXTAREA_OPEN */
    case 38: /* TAG_INPUT_BLOCK_CLOSE */
    case 39: /* TAG_SELECT_BLOCK_CLOSE */
    case 40: /* TAG_TEXTAREA_BLOCK_CLOSE */
    case 41: /* PROP_INPUT_CHECKED_VALUE */
    case 42: /* PROP_INPUT_UNCHECKED_VALUE */
    case 43: /* PROP_INPUT_NAME */
    case 44: /* PROP_INPUT_SEQUENCE_NAME */
    case 45: /* PROP_INPUT_SEQUENCE_SCHEMA_NAME */
    case 46: /* PROP_INPUT_MASTER_ITEM_NAME */
    case 47: /* PROP_INPUT_TYPE */
    case 48: /* PROP_INPUT_VALUE */
    case 49: /* PROP_INPUT_DEFAULT_VALUE */
    case 50: /* PROP_INPUT_COLUMN_NAME */
    case 51: /* PROP_INPUT_FORMAT_MASK */
    case 52: /* PROP_INPUT_DATA_TYPE */
    case 53: /* PROP_INPUT_MAX_LENGTH */
    case 54: /* PROP_INPUT_INSERT_ALLOWED */
    case 55: /* PROP_INPUT_UPDATE_ALLOWED */
    case 56: /* PROP_INPUT_DATALIST_NAME */
    case 57: /* PROP_INPUT_LOOKUP_ITEM_NAME */
    case 58: /* PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME */
    case 59: /* TAG_TABLE_OPEN */
    case 60: /* TAG_TABLE_BLOCK_CLOSE */
    case 61: /* TAG_THEAD_OPEN */
    case 62: /* TAG_THEAD_BLOCK_CLOSE */
    case 63: /* TAG_TFOOT_OPEN */
    case 64: /* TAG_TFOOT_BLOCK_CLOSE */
    case 65: /* TAG_TBODY_OPEN */
    case 66: /* TAG_TBODY_BLOCK_CLOSE */
    case 67: /* TAG_TR_OPEN */
    case 68: /* TAG_TR_BLOCK_CLOSE */
    case 69: /* TAG_TD_OPEN */
    case 70: /* TAG_TD_BLOCK_CLOSE */
    case 71: /* TAG_TH_OPEN */
    case 72: /* TAG_TH_BLOCK_CLOSE */
    case 73: /* TAG_TITLE_OPEN */
    case 74: /* TAG_TITLE_BLOCK_CLOSE */
    case 75: /* TAG_LINK_OPEN */
    case 76: /* TAG_LINK_BLOCK_CLOSE */
    case 77: /* TAG_META_OPEN */
    case 78: /* TAG_META_BLOCK_CLOSE */
    case 79: /* TAG_STYLE_OPEN */
    case 80: /* TAG_STYLE_BLOCK_CLOSE */
    case 81: /* PROPERTYID_SCRIPT_SRC */
    case 82: /* PROPERTYID_SCRIPT_TYPE */
    case 83: /* TAG_SCRIPT_OPEN */
    case 84: /* TAG_SCRIPT_BLOCK_CLOSE */
    case 85: /* TAG_HTML_BLOCK_CLOSE */
    case 86: /* TAG_HTML_OPEN */
    case 87: /* TAG_BODY_OPEN */
    case 88: /* TAG_BODY_BLOCK_CLOSE */
    case 89: /* TAG_HEAD_OPEN */
    case 90: /* TAG_HEAD_BLOCK_CLOSE */
    case 91: /* TAG_CLOSE */
    case 92: /* HTMLTEXT */
    case 93: /* HTML_ENTER */
{
#line 37 "lemon.html.yy"

    /*Sodium::Token *token = (yypminor->yy0);
    if (token) {
        if (token->tokenId == 1 && token->tokenCode != HTML_ENTER) {
            printf("\n%4d:", token->line);
        }
        if (token) {
            if (token->tokenCode == HTML_ENTER) {
                printf("\n%4d:", token->line);
            }
            else {
                printf("%.*s", token->tokenStrLength, token->tokenStr);
            }
        }
    }*/

#line 1133 "lemon.html.c"
}
      break;
      /* Default NON-TERMINAL Destructor */
    case 94: /* error */
    case 95: /* start */
    case 96: /* expressions */
    case 97: /* expression */
    case 98: /* tagdoctype */
    case 99: /* spaces_enters */
    case 100: /* taghtml */
    case 101: /* opt__spaces_enters */
    case 102: /* space */
    case 103: /* enter */
    case 104: /* tagheadcontents */
    case 105: /* tagheadcontent */
    case 106: /* tagtitle */
    case 107: /* tagscript */
    case 108: /* tagstyle */
    case 109: /* taglink */
    case 110: /* tagmeta */
    case 111: /* tagbodycontents */
    case 112: /* tagbodycontent */
    case 113: /* htsqls */
    case 114: /* tagtable */
    case 115: /* htmltext */
    case 116: /* tagdatablock */
    case 117: /* tagcontrolblock */
    case 118: /* tagdatalist */
    case 119: /* tagtree */
    case 120: /* tagtreefullopen */
    case 121: /* tagtreeblockclosefull */
    case 122: /* tagtreeopen */
    case 123: /* tagtreeproperties */
    case 124: /* tagclosechar */
    case 125: /* spaces */
    case 126: /* tagtreeproperty */
    case 127: /* tagtreepropertyid */
    case 128: /* tagdatalistfullopen */
    case 129: /* tagdatalistblockclosefull */
    case 130: /* tagdatalistopen */
    case 131: /* datalistproperties */
    case 132: /* tagdatalistblockclose */
    case 133: /* datalistproperty */
    case 134: /* tagdatalistpropertyid */
    case 135: /* tagdatalistpropertyconnectionname */
    case 136: /* tagcontrolblockfullopen */
    case 137: /* tagcontrolblockclosefull */
    case 138: /* tagcontrolblockcontents */
    case 139: /* tagcontrolblockopen */
    case 140: /* tagcontrolblockproperties */
    case 141: /* tagcontrolblockopen_ */
    case 142: /* tagcontrolblockblockclose */
    case 143: /* tagcontrolblockcontent */
    case 144: /* tagcontrolblockproperty */
    case 145: /* tagdatablockfullopen */
    case 146: /* tagdatablockblockclosefull */
    case 147: /* tagdatablockcontents */
    case 148: /* tagdatablockopen */
    case 149: /* tagdatablockproperties */
    case 150: /* tagdatablockblockclose */
    case 151: /* tagdatablockcontent */
    case 152: /* tagdatablockproperty */
    case 153: /* taginput */
    case 154: /* taginput_with_block */
    case 155: /* taginput_without_block */
    case 156: /* taginputopen */
    case 157: /* taginputproperties */
    case 158: /* taginputblockclosefull */
    case 159: /* taginputshortclose */
    case 160: /* taginputblockclose */
    case 161: /* taginputproperty */
    case 162: /* tagtablefullopen */
    case 163: /* tagtableblockclosefull */
    case 164: /* tablecontent */
    case 165: /* tagtableopen */
    case 166: /* tagproperties */
    case 167: /* tablecontentparts */
    case 168: /* tablecontentpart */
    case 169: /* tagthead */
    case 170: /* tagtbody */
    case 171: /* tagtfoot */
    case 172: /* tagtheadfullopen */
    case 173: /* tagtheadblockclosefull */
    case 174: /* tagtablerows */
    case 175: /* tagtheadopen */
    case 176: /* tagpropertieswithreturnvaluesall */
    case 177: /* tagtfootfullopen */
    case 178: /* tagtfootblockclosefull */
    case 179: /* tagtfootopen */
    case 180: /* tagtbodyfullopen */
    case 181: /* tagtbodyblockclosefull */
    case 182: /* tagtbodyopen */
    case 183: /* tagtablerow */
    case 184: /* tagtablerowfullopen */
    case 185: /* tagtablecols */
    case 186: /* tagtablerowblockclosefull */
    case 187: /* tagtablerowopen */
    case 188: /* tagtablecol */
    case 189: /* tagtablecoltd */
    case 190: /* tagtablecolth */
    case 191: /* tagtablecoltdfullopen */
    case 192: /* tagtablecoltdblockclosefull */
    case 193: /* tagtablecolcontents */
    case 194: /* tagtablecoltdopen */
    case 195: /* tagtablecolcontent */
    case 196: /* tagtablecolthfullopen */
    case 197: /* tagtablecolthblockclosefull */
    case 198: /* tagtablecolthopen */
    case 199: /* tagtitlefullopen */
    case 200: /* tagtitleblockclosefull */
    case 201: /* htmlandspaces */
    case 202: /* tagtitleopen */
    case 203: /* tagtitleblockclose */
    case 204: /* taglinkfullopen */
    case 205: /* taglinkblockclosefull */
    case 206: /* taglinkopen */
    case 207: /* tagshortclose */
    case 208: /* taglinkblockclose */
    case 209: /* tagmetafullopen */
    case 210: /* tagmetablockclosefull */
    case 211: /* tagmetaopen */
    case 212: /* tagmetablockclose */
    case 213: /* tagstylefullopen */
    case 214: /* tagstyleblockclosefull */
    case 215: /* tagstyleopen */
    case 216: /* tagstyleproperties */
    case 217: /* tagstyleblockclose */
    case 218: /* tagstyleproperty */
    case 219: /* tagscriptfullopen */
    case 220: /* tagscriptblockclosefull */
    case 221: /* tagscriptopen */
    case 222: /* tagscriptproperties */
    case 223: /* tagscriptblockclose */
    case 224: /* tagscriptproperty */
    case 225: /* tagscriptpropertyscripttype */
    case 226: /* tagscriptpropertysrc */
    case 227: /* taghtmlfullopen */
    case 228: /* taghtmlblockclosefull */
    case 229: /* taghtmlcontents */
    case 230: /* taghtmlopen */
    case 231: /* taghtmlcontent */
    case 232: /* tagbody */
    case 233: /* taghead */
    case 234: /* tagbodyfullopen */
    case 235: /* tagbodyblockclosefull */
    case 236: /* tagbodyopen */
    case 237: /* tagbodyblockclose */
    case 238: /* tagheadfullopen */
    case 239: /* tagheadblockclosefull */
    case 240: /* tagheadopen */
    case 241: /* tagheadblockclose */
    case 242: /* tagpropertieswithreturnvalues */
    case 243: /* tagpropertywithreturnvalue */
    case 244: /* tagproperty */
    case 245: /* htmlandspace */
    case 246: /* spaces_enter */
{
#line 54 "lemon.html.yy"



#line 1295 "lemon.html.c"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void htmlParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
#ifndef YYPARSEFREENEVERNULL
  if( pParser==0 ) return;
#endif
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int htmlParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static unsigned int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yytos->stateno;
 
  if( stateno>=YY_MIN_REDUCE ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
  do{
    i = yy_shift_ofst[stateno];
    assert( iLookAhead!=YYNOCODE );
    i += iLookAhead;
    if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   htmlParseARG_FETCH;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   htmlParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%sShift '%s', go to state %d\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%sShift '%s'\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major]);
    }
  }
}
#else
# define yyTraceShift(X,Y)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  htmlParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH] ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState);
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 235, 1 },
  { 240, 1 },
  { 95, 1 },
  { 96, 2 },
  { 96, 1 },
  { 97, 5 },
  { 97, 1 },
  { 97, 1 },
  { 104, 2 },
  { 104, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 111, 2 },
  { 111, 1 },
  { 112, 1 },
  { 112, 1 },
  { 112, 1 },
  { 112, 1 },
  { 112, 1 },
  { 113, 1 },
  { 113, 1 },
  { 113, 1 },
  { 98, 1 },
  { 98, 1 },
  { 119, 2 },
  { 120, 3 },
  { 120, 4 },
  { 122, 1 },
  { 121, 1 },
  { 123, 2 },
  { 123, 1 },
  { 126, 2 },
  { 127, 3 },
  { 118, 2 },
  { 128, 3 },
  { 128, 4 },
  { 130, 1 },
  { 129, 1 },
  { 132, 1 },
  { 131, 2 },
  { 131, 1 },
  { 133, 2 },
  { 134, 3 },
  { 133, 2 },
  { 135, 3 },
  { 117, 2 },
  { 117, 3 },
  { 136, 4 },
  { 139, 1 },
  { 141, 1 },
  { 137, 1 },
  { 142, 1 },
  { 138, 2 },
  { 138, 1 },
  { 143, 1 },
  { 143, 1 },
  { 143, 1 },
  { 143, 1 },
  { 140, 2 },
  { 140, 1 },
  { 144, 5 },
  { 116, 2 },
  { 116, 3 },
  { 145, 3 },
  { 148, 1 },
  { 146, 1 },
  { 150, 1 },
  { 147, 2 },
  { 147, 1 },
  { 151, 1 },
  { 151, 1 },
  { 151, 1 },
  { 151, 1 },
  { 149, 2 },
  { 149, 1 },
  { 152, 1 },
  { 152, 1 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 152, 3 },
  { 153, 1 },
  { 153, 1 },
  { 154, 5 },
  { 155, 3 },
  { 159, 1 },
  { 156, 1 },
  { 156, 1 },
  { 156, 1 },
  { 158, 1 },
  { 160, 1 },
  { 160, 1 },
  { 160, 1 },
  { 157, 2 },
  { 157, 1 },
  { 161, 1 },
  { 161, 1 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 161, 3 },
  { 114, 2 },
  { 114, 3 },
  { 162, 2 },
  { 162, 3 },
  { 165, 1 },
  { 163, 1 },
  { 164, 1 },
  { 167, 2 },
  { 167, 1 },
  { 168, 1 },
  { 168, 1 },
  { 168, 1 },
  { 168, 1 },
  { 168, 1 },
  { 169, 2 },
  { 169, 3 },
  { 172, 2 },
  { 172, 3 },
  { 175, 1 },
  { 173, 1 },
  { 171, 3 },
  { 177, 2 },
  { 177, 3 },
  { 179, 1 },
  { 178, 1 },
  { 170, 3 },
  { 180, 2 },
  { 180, 3 },
  { 182, 1 },
  { 181, 1 },
  { 174, 2 },
  { 174, 1 },
  { 183, 1 },
  { 183, 1 },
  { 183, 3 },
  { 184, 2 },
  { 184, 3 },
  { 187, 1 },
  { 186, 1 },
  { 185, 2 },
  { 185, 1 },
  { 188, 1 },
  { 188, 1 },
  { 188, 1 },
  { 188, 1 },
  { 189, 2 },
  { 189, 3 },
  { 191, 2 },
  { 191, 3 },
  { 194, 1 },
  { 192, 1 },
  { 193, 2 },
  { 193, 1 },
  { 195, 1 },
  { 195, 1 },
  { 195, 1 },
  { 195, 1 },
  { 195, 1 },
  { 190, 2 },
  { 190, 3 },
  { 196, 2 },
  { 196, 3 },
  { 198, 1 },
  { 197, 1 },
  { 106, 2 },
  { 106, 3 },
  { 199, 2 },
  { 199, 3 },
  { 200, 1 },
  { 202, 1 },
  { 203, 1 },
  { 109, 1 },
  { 109, 2 },
  { 204, 3 },
  { 204, 3 },
  { 205, 1 },
  { 206, 1 },
  { 208, 1 },
  { 110, 1 },
  { 110, 2 },
  { 209, 3 },
  { 209, 3 },
  { 210, 1 },
  { 211, 1 },
  { 212, 1 },
  { 108, 2 },
  { 108, 3 },
  { 213, 2 },
  { 213, 3 },
  { 214, 1 },
  { 215, 1 },
  { 217, 1 },
  { 216, 2 },
  { 216, 1 },
  { 218, 4 },
  { 218, 4 },
  { 218, 4 },
  { 107, 2 },
  { 107, 3 },
  { 219, 2 },
  { 219, 3 },
  { 220, 1 },
  { 221, 1 },
  { 223, 1 },
  { 222, 2 },
  { 222, 1 },
  { 224, 2 },
  { 225, 3 },
  { 224, 2 },
  { 226, 3 },
  { 100, 2 },
  { 100, 3 },
  { 227, 2 },
  { 227, 3 },
  { 228, 1 },
  { 230, 1 },
  { 229, 2 },
  { 229, 1 },
  { 231, 1 },
  { 231, 1 },
  { 231, 1 },
  { 231, 2 },
  { 231, 3 },
  { 232, 2 },
  { 232, 3 },
  { 234, 2 },
  { 234, 3 },
  { 236, 1 },
  { 237, 1 },
  { 233, 2 },
  { 233, 3 },
  { 238, 1 },
  { 239, 1 },
  { 241, 1 },
  { 176, 1 },
  { 242, 2 },
  { 242, 1 },
  { 243, 3 },
  { 166, 2 },
  { 166, 1 },
  { 244, 4 },
  { 124, 1 },
  { 207, 1 },
  { 201, 2 },
  { 201, 1 },
  { 245, 1 },
  { 245, 1 },
  { 245, 1 },
  { 115, 1 },
  { 101, 1 },
  { 101, 0 },
  { 99, 2 },
  { 99, 1 },
  { 246, 1 },
  { 246, 1 },
  { 125, 2 },
  { 125, 1 },
  { 102, 1 },
  { 103, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno        /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  htmlParseARG_FETCH;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    fprintf(yyTraceFILE, "%sReduce [%s], go to state %d.\n", yyTracePrompt,
      yyRuleName[yyruleno], yymsp[-yysize].stateno);
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH-1] ){
      yyStackOverflow(yypParser);
      return;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        return;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
      case 0: /* tagbodyblockclosefull ::= tagbodyblockclose */
{  yy_destructor(yypParser,237,&yymsp[0].minor);
#line 583 "lemon.html.yy"
{
    char* headContent = "<script type=\"text/javascript\"> window.onload = initResponse(); </script>\n";

    compiler->CreateToken(
        HTMLTEXT,
        strlen(headContent),
        headContent);
}
#line 1902 "lemon.html.c"
}
        break;
      case 1: /* tagheadopen ::= TAG_HEAD_OPEN */
{  yy_destructor(yypParser,89,&yymsp[0].minor);
#line 610 "lemon.html.yy"
{
    char * headContent = "\n"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">                                                           \n"
        "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>                                                           \n"
        "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">                                                                          \n"
        "<script type=\"text/javascript\" src=\"/Sodium-Site/resources/js/jquery-3.1.1.min.js\"></script>                                   \n"
        "<script type=\"text/javascript\" src=\"/Sodium-Site/resources/pnotify/dist/iife/PNotify.js\"></script>                             \n"
        "<script type=\"text/javascript\" src=\"/Sodium-Site/resources/pnotify/dist/iife/PNotifyConfirm.js\"></script>                      \n"
        "<script type=\"text/javascript\" src=\"/Sodium-Site/resources/js/next-level-init.js?_=1\"></script>                                \n"
        "<script type=\"text/javascript\" src=\"/Sodium-Site/resources/js/next-level-response.js?_=1\"></script>                            \n"
        "<script type=\"text/javascript\" src=\"/Sodium-Site/resources/js/next-level-request.js\"></script>                                 \n"
        "<script type=\"text/javascript\" src=\"/Sodium-Site/resources/js/next-level-selection.js\"></script>                               \n"
        "<script type=\"text/javascript\" src=\"/Sodium-Site/resources/js/next-level-jstree.js\"></script>                                  \n"
        "<script type=\"text/javascript\" src=\"/Sodium-Site/resources/jsTree/jstree.min.js\"></script>                                     \n"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"/Sodium-Site/resources/pnotify/dist/PNotifyBrightTheme.css\"/>                   \n"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"/Sodium-Site/resources/jsTree/themes/default/style.min.css\"/>                   \n"
        "<link id=\"bootstrap-css\" rel=\"stylesheet\" href=\"/Sodium-Site/resources/css/bootstrap.min.css\" crossorigin=\"anonymous\" />   \n"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"/Sodium-Site/resources/css/next-level-default.css\"/>                            \n";

    compiler->CreateToken(
        HTMLTEXT,
        strlen(headContent),
        headContent);
}
#line 1932 "lemon.html.c"
}
        break;
      case 2: /* start ::= expressions */
{  yy_destructor(yypParser,96,&yymsp[0].minor);
#line 58 "lemon.html.yy"
{
}
#line 1940 "lemon.html.c"
}
        break;
      case 3: /* expressions ::= expressions expression */
{  yy_destructor(yypParser,96,&yymsp[-1].minor);
#line 60 "lemon.html.yy"
{
}
#line 1948 "lemon.html.c"
  yy_destructor(yypParser,97,&yymsp[0].minor);
}
        break;
      case 4: /* expressions ::= expression */
{  yy_destructor(yypParser,97,&yymsp[0].minor);
#line 61 "lemon.html.yy"
{
}
#line 1957 "lemon.html.c"
}
        break;
      case 5: /* expression ::= tagdoctype spaces_enters taghtml opt__spaces_enters END_OF_FILE */
{  yy_destructor(yypParser,98,&yymsp[-4].minor);
#line 63 "lemon.html.yy"
{
}
#line 1965 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-3].minor);
  yy_destructor(yypParser,100,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,1,&yymsp[0].minor);
}
        break;
      case 6: /* expression ::= space */
      case 10: /* tagheadcontent ::= space */ yytestcase(yyruleno==10);
      case 21: /* tagbodycontent ::= space */ yytestcase(yyruleno==21);
      case 60: /* tagcontrolblockcontent ::= space */ yytestcase(yyruleno==60);
      case 75: /* tagdatablockcontent ::= space */ yytestcase(yyruleno==75);
      case 80: /* tagdatablockproperty ::= space */ yytestcase(yyruleno==80);
      case 111: /* taginputproperty ::= space */ yytestcase(yyruleno==111);
      case 141: /* tablecontentpart ::= space */ yytestcase(yyruleno==141);
      case 164: /* tagtablerow ::= space */ yytestcase(yyruleno==164);
      case 173: /* tagtablecol ::= space */ yytestcase(yyruleno==173);
      case 188: /* tagtablecolcontent ::= space */ yytestcase(yyruleno==188);
      case 250: /* taghtmlcontent ::= space */ yytestcase(yyruleno==250);
      case 278: /* htmlandspace ::= space */ yytestcase(yyruleno==278);
      case 285: /* spaces_enter ::= space */ yytestcase(yyruleno==285);
      case 288: /* spaces ::= space */ yytestcase(yyruleno==288);
{  yy_destructor(yypParser,102,&yymsp[0].minor);
#line 65 "lemon.html.yy"
{
}
#line 1991 "lemon.html.c"
}
        break;
      case 7: /* expression ::= enter */
      case 11: /* tagheadcontent ::= enter */ yytestcase(yyruleno==11);
      case 22: /* tagbodycontent ::= enter */ yytestcase(yyruleno==22);
      case 61: /* tagcontrolblockcontent ::= enter */ yytestcase(yyruleno==61);
      case 76: /* tagdatablockcontent ::= enter */ yytestcase(yyruleno==76);
      case 81: /* tagdatablockproperty ::= enter */ yytestcase(yyruleno==81);
      case 112: /* taginputproperty ::= enter */ yytestcase(yyruleno==112);
      case 142: /* tablecontentpart ::= enter */ yytestcase(yyruleno==142);
      case 165: /* tagtablerow ::= enter */ yytestcase(yyruleno==165);
      case 174: /* tagtablecol ::= enter */ yytestcase(yyruleno==174);
      case 189: /* tagtablecolcontent ::= enter */ yytestcase(yyruleno==189);
      case 251: /* taghtmlcontent ::= enter */ yytestcase(yyruleno==251);
      case 279: /* htmlandspace ::= enter */ yytestcase(yyruleno==279);
      case 286: /* spaces_enter ::= enter */ yytestcase(yyruleno==286);
{  yy_destructor(yypParser,103,&yymsp[0].minor);
#line 67 "lemon.html.yy"
{
}
#line 2012 "lemon.html.c"
}
        break;
      case 8: /* tagheadcontents ::= tagheadcontents tagheadcontent */
{  yy_destructor(yypParser,104,&yymsp[-1].minor);
#line 70 "lemon.html.yy"
{
}
#line 2020 "lemon.html.c"
  yy_destructor(yypParser,105,&yymsp[0].minor);
}
        break;
      case 9: /* tagheadcontents ::= tagheadcontent */
{  yy_destructor(yypParser,105,&yymsp[0].minor);
#line 71 "lemon.html.yy"
{
}
#line 2029 "lemon.html.c"
}
        break;
      case 12: /* tagheadcontent ::= tagtitle */
{  yy_destructor(yypParser,106,&yymsp[0].minor);
#line 75 "lemon.html.yy"
{
}
#line 2037 "lemon.html.c"
}
        break;
      case 13: /* tagheadcontent ::= tagscript */
{  yy_destructor(yypParser,107,&yymsp[0].minor);
#line 76 "lemon.html.yy"
{
}
#line 2045 "lemon.html.c"
}
        break;
      case 14: /* tagheadcontent ::= tagstyle */
{  yy_destructor(yypParser,108,&yymsp[0].minor);
#line 77 "lemon.html.yy"
{
}
#line 2053 "lemon.html.c"
}
        break;
      case 15: /* tagheadcontent ::= taglink */
{  yy_destructor(yypParser,109,&yymsp[0].minor);
#line 78 "lemon.html.yy"
{
}
#line 2061 "lemon.html.c"
}
        break;
      case 16: /* tagheadcontent ::= tagmeta */
{  yy_destructor(yypParser,110,&yymsp[0].minor);
#line 79 "lemon.html.yy"
{
}
#line 2069 "lemon.html.c"
}
        break;
      case 17: /* tagbodycontents ::= tagbodycontents tagbodycontent */
{  yy_destructor(yypParser,111,&yymsp[-1].minor);
#line 81 "lemon.html.yy"
{
}
#line 2077 "lemon.html.c"
  yy_destructor(yypParser,112,&yymsp[0].minor);
}
        break;
      case 18: /* tagbodycontents ::= tagbodycontent */
{  yy_destructor(yypParser,112,&yymsp[0].minor);
#line 82 "lemon.html.yy"
{
}
#line 2086 "lemon.html.c"
}
        break;
      case 19: /* tagbodycontent ::= htsqls */
{  yy_destructor(yypParser,113,&yymsp[0].minor);
#line 84 "lemon.html.yy"
{
}
#line 2094 "lemon.html.c"
}
        break;
      case 20: /* tagbodycontent ::= tagtable */
      case 74: /* tagdatablockcontent ::= tagtable */ yytestcase(yyruleno==74);
      case 187: /* tagtablecolcontent ::= tagtable */ yytestcase(yyruleno==187);
{  yy_destructor(yypParser,114,&yymsp[0].minor);
#line 85 "lemon.html.yy"
{
}
#line 2104 "lemon.html.c"
}
        break;
      case 23: /* tagbodycontent ::= htmltext */
      case 62: /* tagcontrolblockcontent ::= htmltext */ yytestcase(yyruleno==62);
      case 77: /* tagdatablockcontent ::= htmltext */ yytestcase(yyruleno==77);
      case 186: /* tagtablecolcontent ::= htmltext */ yytestcase(yyruleno==186);
      case 277: /* htmlandspace ::= htmltext */ yytestcase(yyruleno==277);
{  yy_destructor(yypParser,115,&yymsp[0].minor);
#line 88 "lemon.html.yy"
{
}
#line 2116 "lemon.html.c"
}
        break;
      case 24: /* htsqls ::= tagdatablock */
{  yy_destructor(yypParser,116,&yymsp[0].minor);
#line 90 "lemon.html.yy"
{
}
#line 2124 "lemon.html.c"
}
        break;
      case 25: /* htsqls ::= tagcontrolblock */
{  yy_destructor(yypParser,117,&yymsp[0].minor);
#line 91 "lemon.html.yy"
{
}
#line 2132 "lemon.html.c"
}
        break;
      case 26: /* htsqls ::= tagdatalist */
{  yy_destructor(yypParser,118,&yymsp[0].minor);
#line 92 "lemon.html.yy"
{
}
#line 2140 "lemon.html.c"
}
        break;
      case 27: /* tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD */
{  yy_destructor(yypParser,2,&yymsp[0].minor);
#line 94 "lemon.html.yy"
{
}
#line 2148 "lemon.html.c"
}
        break;
      case 28: /* tagdoctype ::= TAG_DOCTYPE_HTML */
{  yy_destructor(yypParser,3,&yymsp[0].minor);
#line 96 "lemon.html.yy"
{
}
#line 2156 "lemon.html.c"
}
        break;
      case 29: /* tagtree ::= tagtreefullopen tagtreeblockclosefull */
{  yy_destructor(yypParser,120,&yymsp[-1].minor);
#line 103 "lemon.html.yy"
{
}
#line 2164 "lemon.html.c"
  yy_destructor(yypParser,121,&yymsp[0].minor);
}
        break;
      case 30: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar */
{  yy_destructor(yypParser,122,&yymsp[-2].minor);
#line 104 "lemon.html.yy"
{
}
#line 2173 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 31: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces */
{  yy_destructor(yypParser,122,&yymsp[-3].minor);
#line 105 "lemon.html.yy"
{
}
#line 2183 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 32: /* tagtreeopen ::= TAG_TREE_OPEN */
{  yy_destructor(yypParser,4,&yymsp[0].minor);
#line 107 "lemon.html.yy"
{
}
#line 2194 "lemon.html.c"
}
        break;
      case 33: /* tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE */
{  yy_destructor(yypParser,5,&yymsp[0].minor);
#line 109 "lemon.html.yy"
{
}
#line 2202 "lemon.html.c"
}
        break;
      case 34: /* tagtreeproperties ::= tagtreeproperties tagtreeproperty */
{  yy_destructor(yypParser,123,&yymsp[-1].minor);
#line 111 "lemon.html.yy"
{
}
#line 2210 "lemon.html.c"
  yy_destructor(yypParser,126,&yymsp[0].minor);
}
        break;
      case 35: /* tagtreeproperties ::= tagtreeproperty */
{  yy_destructor(yypParser,126,&yymsp[0].minor);
#line 112 "lemon.html.yy"
{
}
#line 2219 "lemon.html.c"
}
        break;
      case 36: /* tagtreeproperty ::= tagtreepropertyid PROPERTYDATA */
{  yy_destructor(yypParser,127,&yymsp[-1].minor);
#line 114 "lemon.html.yy"
{
}
#line 2227 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 37: /* tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 116 "lemon.html.yy"
{
}
#line 2236 "lemon.html.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 38: /* tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull */
{  yy_destructor(yypParser,128,&yymsp[-1].minor);
#line 122 "lemon.html.yy"
{
}
#line 2246 "lemon.html.c"
  yy_destructor(yypParser,129,&yymsp[0].minor);
}
        break;
      case 39: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar */
{  yy_destructor(yypParser,130,&yymsp[-2].minor);
#line 123 "lemon.html.yy"
{
}
#line 2255 "lemon.html.c"
  yy_destructor(yypParser,131,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 40: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces */
{  yy_destructor(yypParser,130,&yymsp[-3].minor);
#line 124 "lemon.html.yy"
{
}
#line 2265 "lemon.html.c"
  yy_destructor(yypParser,131,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 41: /* tagdatalistopen ::= TAG_DATALIST_OPEN */
{  yy_destructor(yypParser,10,&yymsp[0].minor);
#line 126 "lemon.html.yy"
{
}
#line 2276 "lemon.html.c"
}
        break;
      case 42: /* tagdatalistblockclosefull ::= tagdatalistblockclose */
{  yy_destructor(yypParser,132,&yymsp[0].minor);
#line 128 "lemon.html.yy"
{
}
#line 2284 "lemon.html.c"
}
        break;
      case 43: /* tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE */
{  yy_destructor(yypParser,11,&yymsp[0].minor);
#line 130 "lemon.html.yy"
{
}
#line 2292 "lemon.html.c"
}
        break;
      case 44: /* datalistproperties ::= datalistproperties datalistproperty */
{  yy_destructor(yypParser,131,&yymsp[-1].minor);
#line 132 "lemon.html.yy"
{
}
#line 2300 "lemon.html.c"
  yy_destructor(yypParser,133,&yymsp[0].minor);
}
        break;
      case 45: /* datalistproperties ::= datalistproperty */
{  yy_destructor(yypParser,133,&yymsp[0].minor);
#line 133 "lemon.html.yy"
{
}
#line 2309 "lemon.html.c"
}
        break;
      case 46: /* datalistproperty ::= tagdatalistpropertyid PROPERTYDATA */
{  yy_destructor(yypParser,134,&yymsp[-1].minor);
#line 135 "lemon.html.yy"
{
}
#line 2317 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 47: /* tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 137 "lemon.html.yy"
{
}
#line 2326 "lemon.html.c"
  yy_destructor(yypParser,12,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 48: /* datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA */
{  yy_destructor(yypParser,135,&yymsp[-1].minor);
#line 139 "lemon.html.yy"
{
}
#line 2336 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 49: /* tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 141 "lemon.html.yy"
{
}
#line 2345 "lemon.html.c"
  yy_destructor(yypParser,13,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 50: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull */
{  yy_destructor(yypParser,136,&yymsp[-1].minor);
#line 148 "lemon.html.yy"
{
}
#line 2355 "lemon.html.c"
  yy_destructor(yypParser,137,&yymsp[0].minor);
}
        break;
      case 51: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull */
{  yy_destructor(yypParser,136,&yymsp[-2].minor);
#line 149 "lemon.html.yy"
{
}
#line 2364 "lemon.html.c"
  yy_destructor(yypParser,138,&yymsp[-1].minor);
  yy_destructor(yypParser,137,&yymsp[0].minor);
}
        break;
      case 52: /* tagcontrolblockfullopen ::= tagcontrolblockopen spaces_enters tagcontrolblockproperties tagclosechar */
{  yy_destructor(yypParser,139,&yymsp[-3].minor);
#line 151 "lemon.html.yy"
{
}
#line 2374 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-2].minor);
  yy_destructor(yypParser,140,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 53: /* tagcontrolblockopen ::= tagcontrolblockopen_ */
{  yy_destructor(yypParser,141,&yymsp[0].minor);
#line 153 "lemon.html.yy"
{
}
#line 2385 "lemon.html.c"
}
        break;
      case 54: /* tagcontrolblockopen_ ::= TAG_CONTROLBLOCK_OPEN */
{  yy_destructor(yypParser,14,&yymsp[0].minor);
#line 154 "lemon.html.yy"
{
}
#line 2393 "lemon.html.c"
}
        break;
      case 55: /* tagcontrolblockclosefull ::= tagcontrolblockblockclose */
{  yy_destructor(yypParser,142,&yymsp[0].minor);
#line 156 "lemon.html.yy"
{
}
#line 2401 "lemon.html.c"
}
        break;
      case 56: /* tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 157 "lemon.html.yy"
{
}
#line 2409 "lemon.html.c"
}
        break;
      case 57: /* tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent */
{  yy_destructor(yypParser,138,&yymsp[-1].minor);
#line 159 "lemon.html.yy"
{
}
#line 2417 "lemon.html.c"
  yy_destructor(yypParser,143,&yymsp[0].minor);
}
        break;
      case 58: /* tagcontrolblockcontents ::= tagcontrolblockcontent */
{  yy_destructor(yypParser,143,&yymsp[0].minor);
#line 160 "lemon.html.yy"
{
}
#line 2426 "lemon.html.c"
}
        break;
      case 59: /* tagcontrolblockcontent ::= tagtree */
{  yy_destructor(yypParser,119,&yymsp[0].minor);
#line 162 "lemon.html.yy"
{
}
#line 2434 "lemon.html.c"
}
        break;
      case 63: /* tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty */
{  yy_destructor(yypParser,140,&yymsp[-1].minor);
#line 167 "lemon.html.yy"
{
}
#line 2442 "lemon.html.c"
  yy_destructor(yypParser,144,&yymsp[0].minor);
}
        break;
      case 64: /* tagcontrolblockproperties ::= tagcontrolblockproperty */
{  yy_destructor(yypParser,144,&yymsp[0].minor);
#line 168 "lemon.html.yy"
{
}
#line 2451 "lemon.html.c"
}
        break;
      case 65: /* tagcontrolblockproperty ::= PROP_CONTROLBLOCK_BLOCK_NAME opt__spaces_enters ASSIGMENT opt__spaces_enters PROPERTYDATA */
{  yy_destructor(yypParser,16,&yymsp[-4].minor);
#line 170 "lemon.html.yy"
{
}
#line 2459 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[-3].minor);
  yy_destructor(yypParser,9,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 66: /* tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull */
{  yy_destructor(yypParser,145,&yymsp[-1].minor);
#line 179 "lemon.html.yy"
{
}
#line 2471 "lemon.html.c"
  yy_destructor(yypParser,146,&yymsp[0].minor);
}
        break;
      case 67: /* tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull */
{  yy_destructor(yypParser,145,&yymsp[-2].minor);
#line 180 "lemon.html.yy"
{
}
#line 2480 "lemon.html.c"
  yy_destructor(yypParser,147,&yymsp[-1].minor);
  yy_destructor(yypParser,146,&yymsp[0].minor);
}
        break;
      case 68: /* tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar */
{  yy_destructor(yypParser,148,&yymsp[-2].minor);
#line 181 "lemon.html.yy"
{
}
#line 2490 "lemon.html.c"
  yy_destructor(yypParser,149,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 69: /* tagdatablockopen ::= TAG_DATABLOCK_OPEN */
{  yy_destructor(yypParser,17,&yymsp[0].minor);
#line 183 "lemon.html.yy"
{
}
#line 2500 "lemon.html.c"
}
        break;
      case 70: /* tagdatablockblockclosefull ::= tagdatablockblockclose */
{  yy_destructor(yypParser,150,&yymsp[0].minor);
#line 185 "lemon.html.yy"
{
}
#line 2508 "lemon.html.c"
}
        break;
      case 71: /* tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE */
{  yy_destructor(yypParser,18,&yymsp[0].minor);
#line 187 "lemon.html.yy"
{
}
#line 2516 "lemon.html.c"
}
        break;
      case 72: /* tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent */
{  yy_destructor(yypParser,147,&yymsp[-1].minor);
#line 190 "lemon.html.yy"
{
}
#line 2524 "lemon.html.c"
  yy_destructor(yypParser,151,&yymsp[0].minor);
}
        break;
      case 73: /* tagdatablockcontents ::= tagdatablockcontent */
{  yy_destructor(yypParser,151,&yymsp[0].minor);
#line 191 "lemon.html.yy"
{
}
#line 2533 "lemon.html.c"
}
        break;
      case 78: /* tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty */
{  yy_destructor(yypParser,149,&yymsp[-1].minor);
#line 198 "lemon.html.yy"
{
}
#line 2541 "lemon.html.c"
  yy_destructor(yypParser,152,&yymsp[0].minor);
}
        break;
      case 79: /* tagdatablockproperties ::= tagdatablockproperty */
{  yy_destructor(yypParser,152,&yymsp[0].minor);
#line 200 "lemon.html.yy"
{
}
#line 2550 "lemon.html.c"
}
        break;
      case 82: /* tagdatablockproperty ::= PROPERTYID ASSIGMENT PROPERTYDATA */
      case 131: /* taginputproperty ::= PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==131);
      case 269: /* tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==269);
{  yy_destructor(yypParser,19,&yymsp[-2].minor);
#line 205 "lemon.html.yy"
{
}
#line 2560 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 83: /* tagdatablockproperty ::= PROP_BLOCK_JOIN_CONDITION ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,20,&yymsp[-2].minor);
#line 207 "lemon.html.yy"
{
}
#line 2570 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 84: /* tagdatablockproperty ::= PROP_BLOCK_CONNECTION_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,21,&yymsp[-2].minor);
#line 209 "lemon.html.yy"
{
}
#line 2580 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 85: /* tagdatablockproperty ::= PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,22,&yymsp[-2].minor);
#line 211 "lemon.html.yy"
{
}
#line 2590 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 86: /* tagdatablockproperty ::= PROP_BLOCK_RECORD_COUNT ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,23,&yymsp[-2].minor);
#line 213 "lemon.html.yy"
{
}
#line 2600 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 87: /* tagdatablockproperty ::= PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,24,&yymsp[-2].minor);
#line 215 "lemon.html.yy"
{
}
#line 2610 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 88: /* tagdatablockproperty ::= PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,25,&yymsp[-2].minor);
#line 217 "lemon.html.yy"
{
}
#line 2620 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 89: /* tagdatablockproperty ::= PROP_BLOCK_BLOCK_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,26,&yymsp[-2].minor);
#line 219 "lemon.html.yy"
{
}
#line 2630 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 90: /* tagdatablockproperty ::= PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,27,&yymsp[-2].minor);
#line 221 "lemon.html.yy"
{
}
#line 2640 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 91: /* tagdatablockproperty ::= PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,28,&yymsp[-2].minor);
#line 223 "lemon.html.yy"
{
}
#line 2650 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 92: /* tagdatablockproperty ::= PROP_BLOCK_INSERT_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,29,&yymsp[-2].minor);
#line 225 "lemon.html.yy"
{
}
#line 2660 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 93: /* tagdatablockproperty ::= PROP_BLOCK_DELETE_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,30,&yymsp[-2].minor);
#line 227 "lemon.html.yy"
{
}
#line 2670 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 94: /* tagdatablockproperty ::= PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,31,&yymsp[-2].minor);
#line 229 "lemon.html.yy"
{
}
#line 2680 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 95: /* tagdatablockproperty ::= PROP_BLOCK_WHERE_CLAUSE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,32,&yymsp[-2].minor);
#line 231 "lemon.html.yy"
{
}
#line 2690 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 96: /* tagdatablockproperty ::= PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,33,&yymsp[-2].minor);
#line 233 "lemon.html.yy"
{
}
#line 2700 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 97: /* taginput ::= taginput_with_block */
{  yy_destructor(yypParser,154,&yymsp[0].minor);
#line 241 "lemon.html.yy"
{
}
#line 2710 "lemon.html.c"
}
        break;
      case 98: /* taginput ::= taginput_without_block */
{  yy_destructor(yypParser,155,&yymsp[0].minor);
#line 242 "lemon.html.yy"
{
}
#line 2718 "lemon.html.c"
}
        break;
      case 99: /* taginput_with_block ::= taginputopen taginputproperties tagclosechar opt__spaces_enters taginputblockclosefull */
{  yy_destructor(yypParser,156,&yymsp[-4].minor);
#line 244 "lemon.html.yy"
{
}
#line 2726 "lemon.html.c"
  yy_destructor(yypParser,157,&yymsp[-3].minor);
  yy_destructor(yypParser,124,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,158,&yymsp[0].minor);
}
        break;
      case 100: /* taginput_without_block ::= taginputopen taginputproperties taginputshortclose */
{  yy_destructor(yypParser,156,&yymsp[-2].minor);
#line 246 "lemon.html.yy"
{
}
#line 2738 "lemon.html.c"
  yy_destructor(yypParser,157,&yymsp[-1].minor);
  yy_destructor(yypParser,159,&yymsp[0].minor);
}
        break;
      case 101: /* taginputshortclose ::= TAG_SHORT_CLOSE */
      case 274: /* tagshortclose ::= TAG_SHORT_CLOSE */ yytestcase(yyruleno==274);
{  yy_destructor(yypParser,34,&yymsp[0].minor);
#line 249 "lemon.html.yy"
{
}
#line 2749 "lemon.html.c"
}
        break;
      case 102: /* taginputopen ::= TAG_INPUT_OPEN */
{  yy_destructor(yypParser,35,&yymsp[0].minor);
#line 252 "lemon.html.yy"
{
}
#line 2757 "lemon.html.c"
}
        break;
      case 103: /* taginputopen ::= TAG_SELECT_OPEN */
{  yy_destructor(yypParser,36,&yymsp[0].minor);
#line 254 "lemon.html.yy"
{
}
#line 2765 "lemon.html.c"
}
        break;
      case 104: /* taginputopen ::= TAG_TEXTAREA_OPEN */
{  yy_destructor(yypParser,37,&yymsp[0].minor);
#line 256 "lemon.html.yy"
{
}
#line 2773 "lemon.html.c"
}
        break;
      case 105: /* taginputblockclosefull ::= taginputblockclose */
{  yy_destructor(yypParser,160,&yymsp[0].minor);
#line 258 "lemon.html.yy"
{
}
#line 2781 "lemon.html.c"
}
        break;
      case 106: /* taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE */
{  yy_destructor(yypParser,38,&yymsp[0].minor);
#line 260 "lemon.html.yy"
{
}
#line 2789 "lemon.html.c"
}
        break;
      case 107: /* taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE */
{  yy_destructor(yypParser,39,&yymsp[0].minor);
#line 262 "lemon.html.yy"
{
}
#line 2797 "lemon.html.c"
}
        break;
      case 108: /* taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE */
{  yy_destructor(yypParser,40,&yymsp[0].minor);
#line 264 "lemon.html.yy"
{
}
#line 2805 "lemon.html.c"
}
        break;
      case 109: /* taginputproperties ::= taginputproperties taginputproperty */
{  yy_destructor(yypParser,157,&yymsp[-1].minor);
#line 267 "lemon.html.yy"
{
}
#line 2813 "lemon.html.c"
  yy_destructor(yypParser,161,&yymsp[0].minor);
}
        break;
      case 110: /* taginputproperties ::= taginputproperty */
{  yy_destructor(yypParser,161,&yymsp[0].minor);
#line 269 "lemon.html.yy"
{
}
#line 2822 "lemon.html.c"
}
        break;
      case 113: /* taginputproperty ::= PROP_INPUT_CHECKED_VALUE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,41,&yymsp[-2].minor);
#line 276 "lemon.html.yy"
{
}
#line 2830 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 114: /* taginputproperty ::= PROP_INPUT_UNCHECKED_VALUE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,42,&yymsp[-2].minor);
#line 278 "lemon.html.yy"
{
}
#line 2840 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 115: /* taginputproperty ::= PROP_INPUT_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,43,&yymsp[-2].minor);
#line 280 "lemon.html.yy"
{
}
#line 2850 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 116: /* taginputproperty ::= PROP_INPUT_SEQUENCE_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,44,&yymsp[-2].minor);
#line 282 "lemon.html.yy"
{
}
#line 2860 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 117: /* taginputproperty ::= PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,45,&yymsp[-2].minor);
#line 284 "lemon.html.yy"
{
}
#line 2870 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 118: /* taginputproperty ::= PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,46,&yymsp[-2].minor);
#line 286 "lemon.html.yy"
{
}
#line 2880 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 119: /* taginputproperty ::= PROP_INPUT_TYPE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,47,&yymsp[-2].minor);
#line 288 "lemon.html.yy"
{
}
#line 2890 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 120: /* taginputproperty ::= PROP_INPUT_VALUE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,48,&yymsp[-2].minor);
#line 290 "lemon.html.yy"
{
}
#line 2900 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 121: /* taginputproperty ::= PROP_INPUT_DEFAULT_VALUE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,49,&yymsp[-2].minor);
#line 292 "lemon.html.yy"
{
}
#line 2910 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 122: /* taginputproperty ::= PROP_INPUT_COLUMN_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,50,&yymsp[-2].minor);
#line 294 "lemon.html.yy"
{
}
#line 2920 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 123: /* taginputproperty ::= PROP_INPUT_FORMAT_MASK ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,51,&yymsp[-2].minor);
#line 296 "lemon.html.yy"
{
}
#line 2930 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 124: /* taginputproperty ::= PROP_INPUT_DATA_TYPE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,52,&yymsp[-2].minor);
#line 298 "lemon.html.yy"
{
}
#line 2940 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 125: /* taginputproperty ::= PROP_INPUT_MAX_LENGTH ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,53,&yymsp[-2].minor);
#line 300 "lemon.html.yy"
{
}
#line 2950 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 126: /* taginputproperty ::= PROP_INPUT_INSERT_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,54,&yymsp[-2].minor);
#line 302 "lemon.html.yy"
{
}
#line 2960 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 127: /* taginputproperty ::= PROP_INPUT_UPDATE_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,55,&yymsp[-2].minor);
#line 304 "lemon.html.yy"
{
}
#line 2970 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 128: /* taginputproperty ::= PROP_INPUT_DATALIST_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,56,&yymsp[-2].minor);
#line 306 "lemon.html.yy"
{
}
#line 2980 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 129: /* taginputproperty ::= PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,57,&yymsp[-2].minor);
#line 308 "lemon.html.yy"
{
}
#line 2990 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 130: /* taginputproperty ::= PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,58,&yymsp[-2].minor);
#line 310 "lemon.html.yy"
{
}
#line 3000 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 132: /* tagtable ::= tagtablefullopen tagtableblockclosefull */
{  yy_destructor(yypParser,162,&yymsp[-1].minor);
#line 319 "lemon.html.yy"
{
}
#line 3010 "lemon.html.c"
  yy_destructor(yypParser,163,&yymsp[0].minor);
}
        break;
      case 133: /* tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull */
{  yy_destructor(yypParser,162,&yymsp[-2].minor);
#line 320 "lemon.html.yy"
{
}
#line 3019 "lemon.html.c"
  yy_destructor(yypParser,164,&yymsp[-1].minor);
  yy_destructor(yypParser,163,&yymsp[0].minor);
}
        break;
      case 134: /* tagtablefullopen ::= tagtableopen tagclosechar */
{  yy_destructor(yypParser,165,&yymsp[-1].minor);
#line 322 "lemon.html.yy"
{
}
#line 3029 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 135: /* tagtablefullopen ::= tagtableopen tagproperties tagclosechar */
{  yy_destructor(yypParser,165,&yymsp[-2].minor);
#line 323 "lemon.html.yy"
{
}
#line 3038 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 136: /* tagtableopen ::= TAG_TABLE_OPEN */
{  yy_destructor(yypParser,59,&yymsp[0].minor);
#line 325 "lemon.html.yy"
{
}
#line 3048 "lemon.html.c"
}
        break;
      case 137: /* tagtableblockclosefull ::= TAG_TABLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,60,&yymsp[0].minor);
#line 327 "lemon.html.yy"
{
}
#line 3056 "lemon.html.c"
}
        break;
      case 138: /* tablecontent ::= tablecontentparts */
{  yy_destructor(yypParser,167,&yymsp[0].minor);
#line 331 "lemon.html.yy"
{
}
#line 3064 "lemon.html.c"
}
        break;
      case 139: /* tablecontentparts ::= tablecontentparts tablecontentpart */
{  yy_destructor(yypParser,167,&yymsp[-1].minor);
#line 333 "lemon.html.yy"
{
}
#line 3072 "lemon.html.c"
  yy_destructor(yypParser,168,&yymsp[0].minor);
}
        break;
      case 140: /* tablecontentparts ::= tablecontentpart */
{  yy_destructor(yypParser,168,&yymsp[0].minor);
#line 334 "lemon.html.yy"
{
}
#line 3081 "lemon.html.c"
}
        break;
      case 143: /* tablecontentpart ::= tagthead */
{  yy_destructor(yypParser,169,&yymsp[0].minor);
#line 338 "lemon.html.yy"
{
}
#line 3089 "lemon.html.c"
}
        break;
      case 144: /* tablecontentpart ::= tagtbody */
{  yy_destructor(yypParser,170,&yymsp[0].minor);
#line 339 "lemon.html.yy"
{
}
#line 3097 "lemon.html.c"
}
        break;
      case 145: /* tablecontentpart ::= tagtfoot */
{  yy_destructor(yypParser,171,&yymsp[0].minor);
#line 340 "lemon.html.yy"
{
}
#line 3105 "lemon.html.c"
}
        break;
      case 146: /* tagthead ::= tagtheadfullopen tagtheadblockclosefull */
{  yy_destructor(yypParser,172,&yymsp[-1].minor);
#line 348 "lemon.html.yy"
{
}
#line 3113 "lemon.html.c"
  yy_destructor(yypParser,173,&yymsp[0].minor);
}
        break;
      case 147: /* tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull */
{  yy_destructor(yypParser,172,&yymsp[-2].minor);
#line 349 "lemon.html.yy"
{
}
#line 3122 "lemon.html.c"
  yy_destructor(yypParser,174,&yymsp[-1].minor);
  yy_destructor(yypParser,173,&yymsp[0].minor);
}
        break;
      case 148: /* tagtheadfullopen ::= tagtheadopen tagclosechar */
{  yy_destructor(yypParser,175,&yymsp[-1].minor);
#line 350 "lemon.html.yy"
{
}
#line 3132 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 149: /* tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,175,&yymsp[-2].minor);
#line 351 "lemon.html.yy"
{
}
#line 3141 "lemon.html.c"
  yy_destructor(yypParser,176,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 150: /* tagtheadopen ::= TAG_THEAD_OPEN */
{  yy_destructor(yypParser,61,&yymsp[0].minor);
#line 353 "lemon.html.yy"
{
}
#line 3151 "lemon.html.c"
}
        break;
      case 151: /* tagtheadblockclosefull ::= TAG_THEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,62,&yymsp[0].minor);
#line 355 "lemon.html.yy"
{
}
#line 3159 "lemon.html.c"
}
        break;
      case 152: /* tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull */
{  yy_destructor(yypParser,177,&yymsp[-2].minor);
#line 363 "lemon.html.yy"
{
}
#line 3167 "lemon.html.c"
  yy_destructor(yypParser,174,&yymsp[-1].minor);
  yy_destructor(yypParser,178,&yymsp[0].minor);
}
        break;
      case 153: /* tagtfootfullopen ::= tagtfootopen tagclosechar */
{  yy_destructor(yypParser,179,&yymsp[-1].minor);
#line 364 "lemon.html.yy"
{
}
#line 3177 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 154: /* tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar */
{  yy_destructor(yypParser,179,&yymsp[-2].minor);
#line 365 "lemon.html.yy"
{
}
#line 3186 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 155: /* tagtfootopen ::= TAG_TFOOT_OPEN */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 367 "lemon.html.yy"
{
}
#line 3196 "lemon.html.c"
}
        break;
      case 156: /* tagtfootblockclosefull ::= TAG_TFOOT_BLOCK_CLOSE */
{  yy_destructor(yypParser,64,&yymsp[0].minor);
#line 369 "lemon.html.yy"
{
}
#line 3204 "lemon.html.c"
}
        break;
      case 157: /* tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull */
{  yy_destructor(yypParser,180,&yymsp[-2].minor);
#line 377 "lemon.html.yy"
{
}
#line 3212 "lemon.html.c"
  yy_destructor(yypParser,174,&yymsp[-1].minor);
  yy_destructor(yypParser,181,&yymsp[0].minor);
}
        break;
      case 158: /* tagtbodyfullopen ::= tagtbodyopen tagclosechar */
{  yy_destructor(yypParser,182,&yymsp[-1].minor);
#line 378 "lemon.html.yy"
{
}
#line 3222 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 159: /* tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,182,&yymsp[-2].minor);
#line 379 "lemon.html.yy"
{
}
#line 3231 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 160: /* tagtbodyopen ::= TAG_TBODY_OPEN */
{  yy_destructor(yypParser,65,&yymsp[0].minor);
#line 381 "lemon.html.yy"
{
}
#line 3241 "lemon.html.c"
}
        break;
      case 161: /* tagtbodyblockclosefull ::= TAG_TBODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,66,&yymsp[0].minor);
#line 383 "lemon.html.yy"
{
}
#line 3249 "lemon.html.c"
}
        break;
      case 162: /* tagtablerows ::= tagtablerows tagtablerow */
{  yy_destructor(yypParser,174,&yymsp[-1].minor);
#line 391 "lemon.html.yy"
{
}
#line 3257 "lemon.html.c"
  yy_destructor(yypParser,183,&yymsp[0].minor);
}
        break;
      case 163: /* tagtablerows ::= tagtablerow */
{  yy_destructor(yypParser,183,&yymsp[0].minor);
#line 392 "lemon.html.yy"
{
}
#line 3266 "lemon.html.c"
}
        break;
      case 166: /* tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull */
{  yy_destructor(yypParser,184,&yymsp[-2].minor);
#line 397 "lemon.html.yy"
{
}
#line 3274 "lemon.html.c"
  yy_destructor(yypParser,185,&yymsp[-1].minor);
  yy_destructor(yypParser,186,&yymsp[0].minor);
}
        break;
      case 167: /* tagtablerowfullopen ::= tagtablerowopen tagclosechar */
{  yy_destructor(yypParser,187,&yymsp[-1].minor);
#line 398 "lemon.html.yy"
{
}
#line 3284 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 168: /* tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,187,&yymsp[-2].minor);
#line 399 "lemon.html.yy"
{
}
#line 3293 "lemon.html.c"
  yy_destructor(yypParser,176,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 169: /* tagtablerowopen ::= TAG_TR_OPEN */
{  yy_destructor(yypParser,67,&yymsp[0].minor);
#line 401 "lemon.html.yy"
{
}
#line 3303 "lemon.html.c"
}
        break;
      case 170: /* tagtablerowblockclosefull ::= TAG_TR_BLOCK_CLOSE */
{  yy_destructor(yypParser,68,&yymsp[0].minor);
#line 403 "lemon.html.yy"
{
}
#line 3311 "lemon.html.c"
}
        break;
      case 171: /* tagtablecols ::= tagtablecols tagtablecol */
{  yy_destructor(yypParser,185,&yymsp[-1].minor);
#line 407 "lemon.html.yy"
{
}
#line 3319 "lemon.html.c"
  yy_destructor(yypParser,188,&yymsp[0].minor);
}
        break;
      case 172: /* tagtablecols ::= tagtablecol */
{  yy_destructor(yypParser,188,&yymsp[0].minor);
#line 408 "lemon.html.yy"
{
}
#line 3328 "lemon.html.c"
}
        break;
      case 175: /* tagtablecol ::= tagtablecoltd */
{  yy_destructor(yypParser,189,&yymsp[0].minor);
#line 412 "lemon.html.yy"
{
}
#line 3336 "lemon.html.c"
}
        break;
      case 176: /* tagtablecol ::= tagtablecolth */
{  yy_destructor(yypParser,190,&yymsp[0].minor);
#line 413 "lemon.html.yy"
{
}
#line 3344 "lemon.html.c"
}
        break;
      case 177: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,191,&yymsp[-1].minor);
#line 419 "lemon.html.yy"
{
}
#line 3352 "lemon.html.c"
  yy_destructor(yypParser,192,&yymsp[0].minor);
}
        break;
      case 178: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,191,&yymsp[-2].minor);
#line 420 "lemon.html.yy"
{
}
#line 3361 "lemon.html.c"
  yy_destructor(yypParser,193,&yymsp[-1].minor);
  yy_destructor(yypParser,192,&yymsp[0].minor);
}
        break;
      case 179: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar */
{  yy_destructor(yypParser,194,&yymsp[-1].minor);
#line 421 "lemon.html.yy"
{
}
#line 3371 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 180: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar */
{  yy_destructor(yypParser,194,&yymsp[-2].minor);
#line 423 "lemon.html.yy"
{
}
#line 3380 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 181: /* tagtablecoltdopen ::= TAG_TD_OPEN */
{  yy_destructor(yypParser,69,&yymsp[0].minor);
#line 425 "lemon.html.yy"
{
}
#line 3390 "lemon.html.c"
}
        break;
      case 182: /* tagtablecoltdblockclosefull ::= TAG_TD_BLOCK_CLOSE */
{  yy_destructor(yypParser,70,&yymsp[0].minor);
#line 427 "lemon.html.yy"
{
}
#line 3398 "lemon.html.c"
}
        break;
      case 183: /* tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent */
{  yy_destructor(yypParser,193,&yymsp[-1].minor);
#line 431 "lemon.html.yy"
{
}
#line 3406 "lemon.html.c"
  yy_destructor(yypParser,195,&yymsp[0].minor);
}
        break;
      case 184: /* tagtablecolcontents ::= tagtablecolcontent */
{  yy_destructor(yypParser,195,&yymsp[0].minor);
#line 432 "lemon.html.yy"
{
}
#line 3415 "lemon.html.c"
}
        break;
      case 185: /* tagtablecolcontent ::= taginput */
{  yy_destructor(yypParser,153,&yymsp[0].minor);
#line 434 "lemon.html.yy"
{
}
#line 3423 "lemon.html.c"
}
        break;
      case 190: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull */
{  yy_destructor(yypParser,196,&yymsp[-1].minor);
#line 444 "lemon.html.yy"
{
}
#line 3431 "lemon.html.c"
  yy_destructor(yypParser,197,&yymsp[0].minor);
}
        break;
      case 191: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull */
{  yy_destructor(yypParser,196,&yymsp[-2].minor);
#line 445 "lemon.html.yy"
{
}
#line 3440 "lemon.html.c"
  yy_destructor(yypParser,193,&yymsp[-1].minor);
  yy_destructor(yypParser,197,&yymsp[0].minor);
}
        break;
      case 192: /* tagtablecolthfullopen ::= tagtablecolthopen tagclosechar */
{  yy_destructor(yypParser,198,&yymsp[-1].minor);
#line 446 "lemon.html.yy"
{
}
#line 3450 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 193: /* tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,198,&yymsp[-2].minor);
#line 448 "lemon.html.yy"
{
}
#line 3459 "lemon.html.c"
  yy_destructor(yypParser,176,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 194: /* tagtablecolthopen ::= TAG_TH_OPEN */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 450 "lemon.html.yy"
{
}
#line 3469 "lemon.html.c"
}
        break;
      case 195: /* tagtablecolthblockclosefull ::= TAG_TH_BLOCK_CLOSE */
{  yy_destructor(yypParser,72,&yymsp[0].minor);
#line 452 "lemon.html.yy"
{
}
#line 3477 "lemon.html.c"
}
        break;
      case 196: /* tagtitle ::= tagtitlefullopen tagtitleblockclosefull */
{  yy_destructor(yypParser,199,&yymsp[-1].minor);
#line 460 "lemon.html.yy"
{
}
#line 3485 "lemon.html.c"
  yy_destructor(yypParser,200,&yymsp[0].minor);
}
        break;
      case 197: /* tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull */
{  yy_destructor(yypParser,199,&yymsp[-2].minor);
#line 461 "lemon.html.yy"
{
}
#line 3494 "lemon.html.c"
  yy_destructor(yypParser,201,&yymsp[-1].minor);
  yy_destructor(yypParser,200,&yymsp[0].minor);
}
        break;
      case 198: /* tagtitlefullopen ::= tagtitleopen tagclosechar */
{  yy_destructor(yypParser,202,&yymsp[-1].minor);
#line 462 "lemon.html.yy"
{
}
#line 3504 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 199: /* tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar */
{  yy_destructor(yypParser,202,&yymsp[-2].minor);
#line 463 "lemon.html.yy"
{
}
#line 3513 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 200: /* tagtitleblockclosefull ::= tagtitleblockclose */
{  yy_destructor(yypParser,203,&yymsp[0].minor);
#line 464 "lemon.html.yy"
{
}
#line 3523 "lemon.html.c"
}
        break;
      case 201: /* tagtitleopen ::= TAG_TITLE_OPEN */
{  yy_destructor(yypParser,73,&yymsp[0].minor);
#line 465 "lemon.html.yy"
{
}
#line 3531 "lemon.html.c"
}
        break;
      case 202: /* tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,74,&yymsp[0].minor);
#line 466 "lemon.html.yy"
{
}
#line 3539 "lemon.html.c"
}
        break;
      case 203: /* taglink ::= taglinkfullopen */
{  yy_destructor(yypParser,204,&yymsp[0].minor);
#line 472 "lemon.html.yy"
{
}
#line 3547 "lemon.html.c"
}
        break;
      case 204: /* taglink ::= taglinkfullopen taglinkblockclosefull */
{  yy_destructor(yypParser,204,&yymsp[-1].minor);
#line 473 "lemon.html.yy"
{
}
#line 3555 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[0].minor);
}
        break;
      case 205: /* taglinkfullopen ::= taglinkopen tagproperties tagclosechar */
{  yy_destructor(yypParser,206,&yymsp[-2].minor);
#line 474 "lemon.html.yy"
{
}
#line 3564 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 206: /* taglinkfullopen ::= taglinkopen tagproperties tagshortclose */
{  yy_destructor(yypParser,206,&yymsp[-2].minor);
#line 475 "lemon.html.yy"
{
}
#line 3574 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,207,&yymsp[0].minor);
}
        break;
      case 207: /* taglinkblockclosefull ::= taglinkblockclose */
{  yy_destructor(yypParser,208,&yymsp[0].minor);
#line 477 "lemon.html.yy"
{
}
#line 3584 "lemon.html.c"
}
        break;
      case 208: /* taglinkopen ::= TAG_LINK_OPEN */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 479 "lemon.html.yy"
{
}
#line 3592 "lemon.html.c"
}
        break;
      case 209: /* taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE */
{  yy_destructor(yypParser,76,&yymsp[0].minor);
#line 480 "lemon.html.yy"
{
}
#line 3600 "lemon.html.c"
}
        break;
      case 210: /* tagmeta ::= tagmetafullopen */
{  yy_destructor(yypParser,209,&yymsp[0].minor);
#line 487 "lemon.html.yy"
{
}
#line 3608 "lemon.html.c"
}
        break;
      case 211: /* tagmeta ::= tagmetafullopen tagmetablockclosefull */
{  yy_destructor(yypParser,209,&yymsp[-1].minor);
#line 488 "lemon.html.yy"
{
}
#line 3616 "lemon.html.c"
  yy_destructor(yypParser,210,&yymsp[0].minor);
}
        break;
      case 212: /* tagmetafullopen ::= tagmetaopen tagproperties tagclosechar */
{  yy_destructor(yypParser,211,&yymsp[-2].minor);
#line 489 "lemon.html.yy"
{
}
#line 3625 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 213: /* tagmetafullopen ::= tagmetaopen tagproperties tagshortclose */
{  yy_destructor(yypParser,211,&yymsp[-2].minor);
#line 490 "lemon.html.yy"
{
}
#line 3635 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,207,&yymsp[0].minor);
}
        break;
      case 214: /* tagmetablockclosefull ::= tagmetablockclose */
{  yy_destructor(yypParser,212,&yymsp[0].minor);
#line 492 "lemon.html.yy"
{
}
#line 3645 "lemon.html.c"
}
        break;
      case 215: /* tagmetaopen ::= TAG_META_OPEN */
{  yy_destructor(yypParser,77,&yymsp[0].minor);
#line 494 "lemon.html.yy"
{
}
#line 3653 "lemon.html.c"
}
        break;
      case 216: /* tagmetablockclose ::= TAG_META_BLOCK_CLOSE */
{  yy_destructor(yypParser,78,&yymsp[0].minor);
#line 495 "lemon.html.yy"
{
}
#line 3661 "lemon.html.c"
}
        break;
      case 217: /* tagstyle ::= tagstylefullopen tagstyleblockclosefull */
{  yy_destructor(yypParser,213,&yymsp[-1].minor);
#line 502 "lemon.html.yy"
{
}
#line 3669 "lemon.html.c"
  yy_destructor(yypParser,214,&yymsp[0].minor);
}
        break;
      case 218: /* tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull */
{  yy_destructor(yypParser,213,&yymsp[-2].minor);
#line 503 "lemon.html.yy"
{
}
#line 3678 "lemon.html.c"
  yy_destructor(yypParser,201,&yymsp[-1].minor);
  yy_destructor(yypParser,214,&yymsp[0].minor);
}
        break;
      case 219: /* tagstylefullopen ::= tagstyleopen tagclosechar */
{  yy_destructor(yypParser,215,&yymsp[-1].minor);
#line 504 "lemon.html.yy"
{
}
#line 3688 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 220: /* tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar */
{  yy_destructor(yypParser,215,&yymsp[-2].minor);
#line 505 "lemon.html.yy"
{
}
#line 3697 "lemon.html.c"
  yy_destructor(yypParser,216,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 221: /* tagstyleblockclosefull ::= tagstyleblockclose */
{  yy_destructor(yypParser,217,&yymsp[0].minor);
#line 507 "lemon.html.yy"
{
}
#line 3707 "lemon.html.c"
}
        break;
      case 222: /* tagstyleopen ::= TAG_STYLE_OPEN */
{  yy_destructor(yypParser,79,&yymsp[0].minor);
#line 509 "lemon.html.yy"
{
}
#line 3715 "lemon.html.c"
}
        break;
      case 223: /* tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,80,&yymsp[0].minor);
#line 510 "lemon.html.yy"
{
}
#line 3723 "lemon.html.c"
}
        break;
      case 224: /* tagstyleproperties ::= tagstyleproperties tagstyleproperty */
{  yy_destructor(yypParser,216,&yymsp[-1].minor);
#line 513 "lemon.html.yy"
{
}
#line 3731 "lemon.html.c"
  yy_destructor(yypParser,218,&yymsp[0].minor);
}
        break;
      case 225: /* tagstyleproperties ::= tagstyleproperty */
{  yy_destructor(yypParser,218,&yymsp[0].minor);
#line 514 "lemon.html.yy"
{
}
#line 3740 "lemon.html.c"
}
        break;
      case 226: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 516 "lemon.html.yy"
{
}
#line 3748 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 227: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 517 "lemon.html.yy"
{
}
#line 3759 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 228: /* tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */
      case 272: /* tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==272);
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 518 "lemon.html.yy"
{
}
#line 3771 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 229: /* tagscript ::= tagscriptfullopen tagscriptblockclosefull */
{  yy_destructor(yypParser,219,&yymsp[-1].minor);
#line 525 "lemon.html.yy"
{
}
#line 3782 "lemon.html.c"
  yy_destructor(yypParser,220,&yymsp[0].minor);
}
        break;
      case 230: /* tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull */
{  yy_destructor(yypParser,219,&yymsp[-2].minor);
#line 526 "lemon.html.yy"
{
}
#line 3791 "lemon.html.c"
  yy_destructor(yypParser,201,&yymsp[-1].minor);
  yy_destructor(yypParser,220,&yymsp[0].minor);
}
        break;
      case 231: /* tagscriptfullopen ::= tagscriptopen tagclosechar */
{  yy_destructor(yypParser,221,&yymsp[-1].minor);
#line 527 "lemon.html.yy"
{
}
#line 3801 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 232: /* tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar */
{  yy_destructor(yypParser,221,&yymsp[-2].minor);
#line 528 "lemon.html.yy"
{
}
#line 3810 "lemon.html.c"
  yy_destructor(yypParser,222,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 233: /* tagscriptblockclosefull ::= tagscriptblockclose */
{  yy_destructor(yypParser,223,&yymsp[0].minor);
#line 530 "lemon.html.yy"
{
}
#line 3820 "lemon.html.c"
}
        break;
      case 234: /* tagscriptopen ::= TAG_SCRIPT_OPEN */
{  yy_destructor(yypParser,83,&yymsp[0].minor);
#line 532 "lemon.html.yy"
{
}
#line 3828 "lemon.html.c"
}
        break;
      case 235: /* tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE */
{  yy_destructor(yypParser,84,&yymsp[0].minor);
#line 533 "lemon.html.yy"
{
}
#line 3836 "lemon.html.c"
}
        break;
      case 236: /* tagscriptproperties ::= tagscriptproperties tagscriptproperty */
{  yy_destructor(yypParser,222,&yymsp[-1].minor);
#line 537 "lemon.html.yy"
{
}
#line 3844 "lemon.html.c"
  yy_destructor(yypParser,224,&yymsp[0].minor);
}
        break;
      case 237: /* tagscriptproperties ::= tagscriptproperty */
{  yy_destructor(yypParser,224,&yymsp[0].minor);
#line 538 "lemon.html.yy"
{
}
#line 3853 "lemon.html.c"
}
        break;
      case 238: /* tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA */
{  yy_destructor(yypParser,225,&yymsp[-1].minor);
#line 540 "lemon.html.yy"
{
}
#line 3861 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 239: /* tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 542 "lemon.html.yy"
{
}
#line 3870 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 240: /* tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA */
{  yy_destructor(yypParser,226,&yymsp[-1].minor);
#line 544 "lemon.html.yy"
{
}
#line 3880 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 241: /* tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 546 "lemon.html.yy"
{
}
#line 3889 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 242: /* taghtml ::= taghtmlfullopen taghtmlblockclosefull */
{  yy_destructor(yypParser,227,&yymsp[-1].minor);
#line 552 "lemon.html.yy"
{
}
#line 3899 "lemon.html.c"
  yy_destructor(yypParser,228,&yymsp[0].minor);
}
        break;
      case 243: /* taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull */
{  yy_destructor(yypParser,227,&yymsp[-2].minor);
#line 553 "lemon.html.yy"
{
}
#line 3908 "lemon.html.c"
  yy_destructor(yypParser,229,&yymsp[-1].minor);
  yy_destructor(yypParser,228,&yymsp[0].minor);
}
        break;
      case 244: /* taghtmlfullopen ::= taghtmlopen tagclosechar */
{  yy_destructor(yypParser,230,&yymsp[-1].minor);
#line 554 "lemon.html.yy"
{
}
#line 3918 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 245: /* taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar */
{  yy_destructor(yypParser,230,&yymsp[-2].minor);
#line 555 "lemon.html.yy"
{
}
#line 3927 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 246: /* taghtmlblockclosefull ::= TAG_HTML_BLOCK_CLOSE */
{  yy_destructor(yypParser,85,&yymsp[0].minor);
#line 557 "lemon.html.yy"
{
}
#line 3937 "lemon.html.c"
}
        break;
      case 247: /* taghtmlopen ::= TAG_HTML_OPEN */
{  yy_destructor(yypParser,86,&yymsp[0].minor);
#line 559 "lemon.html.yy"
{
}
#line 3945 "lemon.html.c"
}
        break;
      case 248: /* taghtmlcontents ::= taghtmlcontents taghtmlcontent */
{  yy_destructor(yypParser,229,&yymsp[-1].minor);
#line 561 "lemon.html.yy"
{
}
#line 3953 "lemon.html.c"
  yy_destructor(yypParser,231,&yymsp[0].minor);
}
        break;
      case 249: /* taghtmlcontents ::= taghtmlcontent */
{  yy_destructor(yypParser,231,&yymsp[0].minor);
#line 562 "lemon.html.yy"
{
}
#line 3962 "lemon.html.c"
}
        break;
      case 252: /* taghtmlcontent ::= tagbody */
{  yy_destructor(yypParser,232,&yymsp[0].minor);
#line 566 "lemon.html.yy"
{
}
#line 3970 "lemon.html.c"
}
        break;
      case 253: /* taghtmlcontent ::= taghead tagbody */
{  yy_destructor(yypParser,233,&yymsp[-1].minor);
#line 567 "lemon.html.yy"
{
}
#line 3978 "lemon.html.c"
  yy_destructor(yypParser,232,&yymsp[0].minor);
}
        break;
      case 254: /* taghtmlcontent ::= taghead spaces_enters tagbody */
{  yy_destructor(yypParser,233,&yymsp[-2].minor);
#line 568 "lemon.html.yy"
{
}
#line 3987 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-1].minor);
  yy_destructor(yypParser,232,&yymsp[0].minor);
}
        break;
      case 255: /* tagbody ::= tagbodyfullopen tagbodyblockclosefull */
{  yy_destructor(yypParser,234,&yymsp[-1].minor);
#line 575 "lemon.html.yy"
{
}
#line 3997 "lemon.html.c"
  yy_destructor(yypParser,235,&yymsp[0].minor);
}
        break;
      case 256: /* tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull */
{  yy_destructor(yypParser,234,&yymsp[-2].minor);
#line 576 "lemon.html.yy"
{
}
#line 4006 "lemon.html.c"
  yy_destructor(yypParser,111,&yymsp[-1].minor);
  yy_destructor(yypParser,235,&yymsp[0].minor);
}
        break;
      case 257: /* tagbodyfullopen ::= tagbodyopen tagclosechar */
{  yy_destructor(yypParser,236,&yymsp[-1].minor);
#line 578 "lemon.html.yy"
{
}
#line 4016 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 258: /* tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,236,&yymsp[-2].minor);
#line 580 "lemon.html.yy"
{
}
#line 4025 "lemon.html.c"
  yy_destructor(yypParser,166,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 259: /* tagbodyopen ::= TAG_BODY_OPEN */
{  yy_destructor(yypParser,87,&yymsp[0].minor);
#line 592 "lemon.html.yy"
{
}
#line 4035 "lemon.html.c"
}
        break;
      case 260: /* tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,88,&yymsp[0].minor);
#line 594 "lemon.html.yy"
{
}
#line 4043 "lemon.html.c"
}
        break;
      case 261: /* taghead ::= tagheadfullopen tagheadblockclosefull */
{  yy_destructor(yypParser,238,&yymsp[-1].minor);
#line 602 "lemon.html.yy"
{
}
#line 4051 "lemon.html.c"
  yy_destructor(yypParser,239,&yymsp[0].minor);
}
        break;
      case 262: /* taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull */
{  yy_destructor(yypParser,238,&yymsp[-2].minor);
#line 603 "lemon.html.yy"
{
}
#line 4060 "lemon.html.c"
  yy_destructor(yypParser,104,&yymsp[-1].minor);
  yy_destructor(yypParser,239,&yymsp[0].minor);
}
        break;
      case 263: /* tagheadfullopen ::= tagheadopen */
{  yy_destructor(yypParser,240,&yymsp[0].minor);
#line 605 "lemon.html.yy"
{
}
#line 4070 "lemon.html.c"
}
        break;
      case 264: /* tagheadblockclosefull ::= tagheadblockclose */
{  yy_destructor(yypParser,241,&yymsp[0].minor);
#line 607 "lemon.html.yy"
{
}
#line 4078 "lemon.html.c"
}
        break;
      case 265: /* tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,90,&yymsp[0].minor);
#line 635 "lemon.html.yy"
{
}
#line 4086 "lemon.html.c"
}
        break;
      case 266: /* tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues */
{  yy_destructor(yypParser,242,&yymsp[0].minor);
#line 643 "lemon.html.yy"
{
}
#line 4094 "lemon.html.c"
}
        break;
      case 267: /* tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue */
{  yy_destructor(yypParser,242,&yymsp[-1].minor);
#line 645 "lemon.html.yy"
{
}
#line 4102 "lemon.html.c"
  yy_destructor(yypParser,243,&yymsp[0].minor);
}
        break;
      case 268: /* tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue */
{  yy_destructor(yypParser,243,&yymsp[0].minor);
#line 647 "lemon.html.yy"
{
}
#line 4111 "lemon.html.c"
}
        break;
      case 270: /* tagproperties ::= tagproperties tagproperty */
{  yy_destructor(yypParser,166,&yymsp[-1].minor);
#line 656 "lemon.html.yy"
{
}
#line 4119 "lemon.html.c"
  yy_destructor(yypParser,244,&yymsp[0].minor);
}
        break;
      case 271: /* tagproperties ::= tagproperty */
{  yy_destructor(yypParser,244,&yymsp[0].minor);
#line 657 "lemon.html.yy"
{
}
#line 4128 "lemon.html.c"
}
        break;
      case 273: /* tagclosechar ::= TAG_CLOSE */
{  yy_destructor(yypParser,91,&yymsp[0].minor);
#line 663 "lemon.html.yy"
{
}
#line 4136 "lemon.html.c"
}
        break;
      case 275: /* htmlandspaces ::= htmlandspaces htmlandspace */
{  yy_destructor(yypParser,201,&yymsp[-1].minor);
#line 672 "lemon.html.yy"
{
}
#line 4144 "lemon.html.c"
  yy_destructor(yypParser,245,&yymsp[0].minor);
}
        break;
      case 276: /* htmlandspaces ::= htmlandspace */
{  yy_destructor(yypParser,245,&yymsp[0].minor);
#line 673 "lemon.html.yy"
{
}
#line 4153 "lemon.html.c"
}
        break;
      case 280: /* htmltext ::= HTMLTEXT */
{  yy_destructor(yypParser,92,&yymsp[0].minor);
#line 679 "lemon.html.yy"
{
}
#line 4161 "lemon.html.c"
}
        break;
      case 281: /* opt__spaces_enters ::= spaces_enters */
{  yy_destructor(yypParser,99,&yymsp[0].minor);
#line 686 "lemon.html.yy"
{
}
#line 4169 "lemon.html.c"
}
        break;
      case 283: /* spaces_enters ::= spaces_enters spaces_enter */
{  yy_destructor(yypParser,99,&yymsp[-1].minor);
#line 689 "lemon.html.yy"
{
}
#line 4177 "lemon.html.c"
  yy_destructor(yypParser,246,&yymsp[0].minor);
}
        break;
      case 284: /* spaces_enters ::= spaces_enter */
{  yy_destructor(yypParser,246,&yymsp[0].minor);
#line 690 "lemon.html.yy"
{
}
#line 4186 "lemon.html.c"
}
        break;
      case 287: /* spaces ::= spaces space */
{  yy_destructor(yypParser,125,&yymsp[-1].minor);
#line 696 "lemon.html.yy"
{
}
#line 4194 "lemon.html.c"
  yy_destructor(yypParser,102,&yymsp[0].minor);
}
        break;
      case 289: /* space ::= SPACE */
{  yy_destructor(yypParser,7,&yymsp[0].minor);
#line 701 "lemon.html.yy"
{
}
#line 4203 "lemon.html.c"
}
        break;
      case 290: /* enter ::= HTML_ENTER */
{  yy_destructor(yypParser,93,&yymsp[0].minor);
#line 703 "lemon.html.yy"
{
}
#line 4211 "lemon.html.c"
}
        break;
      default:
      /* (282) opt__spaces_enters ::= */ yytestcase(yyruleno==282);
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact <= YY_MAX_SHIFTREDUCE ){
    if( yyact>YY_MAX_SHIFT ){
      yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
    }
    yymsp -= yysize-1;
    yypParser->yytos = yymsp;
    yymsp->stateno = (YYACTIONTYPE)yyact;
    yymsp->major = (YYCODETYPE)yygoto;
    yyTraceShift(yypParser, yyact);
  }else{
    assert( yyact == YY_ACCEPT_ACTION );
    yypParser->yytos -= yysize;
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  htmlParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  htmlParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  htmlParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  htmlParseARG_FETCH;
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 32 "lemon.html.yy"

    printf("--SYNTAX ERROR--");
    exit(100);
#line 4276 "lemon.html.c"
/************ End %syntax_error code ******************************************/
  htmlParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  htmlParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
/*********** End %parse_accept code *******************************************/
  htmlParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "htmlParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void htmlParse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  htmlParseTOKENTYPE yyminor       /* The value for the token */
  htmlParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  unsigned int yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  yypParser = (yyParser*)yyp;
  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif
  htmlParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput '%s'\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      yymajor = YYNOCODE;
    }else if( yyact <= YY_MAX_REDUCE ){
      yy_reduce(yypParser,yyact-YY_MIN_REDUCE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}
