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
#define YYNOCODE 247
#define YYACTIONTYPE unsigned short int
#define htmlParseTOKENTYPE  Token * 
typedef union {
  int yyinit;
  htmlParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define htmlParseARG_SDECL  SodiumCompiler *session ;
#define htmlParseARG_PDECL , SodiumCompiler *session 
#define htmlParseARG_FETCH  SodiumCompiler *session  = yypParser->session 
#define htmlParseARG_STORE yypParser->session  = session 
#define YYNSTATE             187
#define YYNRULE              290
#define YY_MAX_SHIFT         186
#define YY_MIN_SHIFTREDUCE   466
#define YY_MAX_SHIFTREDUCE   755
#define YY_MIN_REDUCE        756
#define YY_MAX_REDUCE        1045
#define YY_ERROR_ACTION      1046
#define YY_ACCEPT_ACTION     1047
#define YY_NO_ACTION         1048
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
#define YY_ACTTAB_COUNT (909)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   754,    2,    2,    2,    2,    2,    2,    2,    2,    2,
 /*    10 */   467,   61,  140,   93,   71,  467,  467,   71,  181,  754,
 /*    20 */   754,  135,  602,  602,   95,   96,   72,  564,   76,   72,
 /*    30 */    72,   91,  140,  754,  176,  174,  172,  170,  168,  166,
 /*    40 */   164,  162,  160,  158,  156,  154,  152,  150,  148,  146,
 /*    50 */   144,  142,  611,  683,  176,  174,  172,  170,  168,  166,
 /*    60 */   164,  162,  160,  158,  156,  154,  152,  150,  148,  146,
 /*    70 */   144,  142,  472,  472,  180,  472,  472,  472,  472,  472,
 /*    80 */   472,  754,  679,  562,  738,  562,  755,  602,  602,  602,
 /*    90 */   602,   22,   91,  738,   54,  672,   31,   21,   53,   30,
 /*   100 */    50,   52,   79,   83,   74,  755,  755,   78,  739,   73,
 /*   110 */   754,   20,  738,   49,  682,  754,   92,   19,   80,   36,
 /*   120 */   498,  181,  133,  131,  129,  127,  125,  123,  121,  119,
 /*   130 */   117,  115,  113,  111,  109,  107,  105,  725,  754,  725,
 /*   140 */  1047,   44,   44,   61,  491,  492,  687,   44,   44,  754,
 /*   150 */   133,  131,  129,  127,  125,  123,  121,  119,  117,  115,
 /*   160 */   113,  111,  109,  107,  105,  738,   26,   26,   21,   85,
 /*   170 */    85,   50,   72,   79,  754,   74,  184,  183,   78,   26,
 /*   180 */    73,  664,   20,  671,   49,  678,  507,  685,   19,  754,
 /*   190 */    36,  697,  754,  612,  738,  505,  755,   39,  730,  517,
 /*   200 */   738,  755,  532,    4,    4,   64,  631,   64,  726,  754,
 /*   210 */   726,  135,    4,    4,    4,    4,    4,    4,    4,    4,
 /*   220 */   534,  754,   29,   29,  755,  541,  541,  600,  613,   82,
 /*   230 */   618,   62,  623,  732,  656,  755,  754,   14,    8,    8,
 /*   240 */    59,  596,  481,  481,  599,   13,  667,  531,   43,  667,
 /*   250 */     8,    8,  481,  481,  481,  481,  481,  481,  481,  754,
 /*   260 */   755,  599,    5,  659,   26,   58,  659,  709,   82,  723,
 /*   270 */    62,  729,  738,  724,  541,  755,   14,  745,  755,   59,
 /*   280 */   600,   10,   10,  644,   13,  657,  754,   43,    8,    8,
 /*   290 */     8,   41,  609,   29,  745,  755,  752,    5,   34,   34,
 /*   300 */    58,    5,   29,   16,   58,  497,   55,  755,   26,  754,
 /*   310 */   493,    9,    9,  698,  565,  566,  567,   15,   15,  634,
 /*   320 */   634,  745,  755,    9,    9,  516,  138,  703,    8,   93,
 /*   330 */     8,  674,  653,  674,  704,  718,  702,  718,  599,   98,
 /*   340 */   754,  595,   87,  738,  526,   10,   10,   10,   10,   10,
 /*   350 */    22,  658,   34,   54,  701,   31,   34,   53,   30,  100,
 /*   360 */    52,    9,    9,    9,   41,  646,  646,  179,  624,  632,
 /*   370 */     5,  745,  755,   58,  719,  694,  719,  646,  646,  646,
 /*   380 */   646,  691,  711,  711,  690,   24,   24,  748,  748,   45,
 /*   390 */    32,  646,  646,   32,   32,  755,  754,  102,   24,  689,
 /*   400 */   640,    9,  629,    9,  634,  634,  634,    7,  559,  104,
 /*   410 */    57,  558,    6,  738,   56,  646,  646,  646,   41,  710,
 /*   420 */   740,  740,   17,   17,    5,   77,  755,   58,   77,  646,
 /*   430 */   646,  646,   41,  740,   17,   17,  502,  106,    5,  502,
 /*   440 */   557,   58,  705,   15,  108,   15,   15,   23,    3,  556,
 /*   450 */    51,  614,    1,  110,    1,  138,  632,  646,  555,  654,
 /*   460 */    18,   18,  112,   12,   12,  529,   17,   45,  641,  529,
 /*   470 */    17,  646,   48,   18,   48,   97,   94,   18,   89,  554,
 /*   480 */    75,    5,  755,   24,   58,  535,  535,  114,   25,   25,
 /*   490 */   116,  754,  553,  740,  740,  514,   18,  535,  535,  514,
 /*   500 */    18,   25,  692,  520,  520,  692,  740,  706,  625,  625,
 /*   510 */   711,  711,   23,    3,  552,   51,  520,    1,   46,    1,
 /*   520 */   520,   89,  716,   75,    3,  118,   51,   24,  530,  551,
 /*   530 */   748,  754,  530,  535,  625,  625,   32,  693,  515,  754,
 /*   540 */   693,  137,  515,  520,    5,   12,  754,   58,   12,   12,
 /*   550 */    12,    7,  633,  644,   57,  657,    6,  138,   56,  565,
 /*   560 */   566,  567,  740,  740,  740,  120,  625,  625,   27,   27,
 /*   570 */   550,  748,  748,   28,   28,  180,  740,  755,  610,  675,
 /*   580 */   122,  695,   40,  599,  748,  748,   25,  496,  625,   16,
 /*   590 */   754,  138,   55,  613,  645,  618,   46,  623,  519,  680,
 /*   600 */   572,  572,  680,  754,  681,  754,   72,  681,  177,   72,
 /*   610 */    72,  549,  620,  668,  625,   16,  745,  755,   55,  686,
 /*   620 */   138,  124,   37,  138,   72,  755,  178,   72,   72,  548,
 /*   630 */    25,  745,  755,  138,   72,  740,  186,   72,   72,   27,
 /*   640 */   126,  615,  707,  469,   28,  661,  625,   16,   27,   16,
 /*   650 */    55,  547,   55,   28,   16,  720,  563,   55,  572,  738,
 /*   660 */   660,  676,  619,  660,  756,  632,  491,  492,  630,  754,
 /*   670 */   665,  754,   42,   42,  655,  745,  755,  138,  128,  138,
 /*   680 */   699,   97,   94,   63,  138,  754,   65,  138,  745,  755,
 /*   690 */    35,  755,  546,   35,   35,  669,   66,  130,  735,  621,
 /*   700 */   717,  616,    3,  545,   51,  740,  642,  132,   11,  597,
 /*   710 */    88,   47,   33,   81,  748,   33,   33,  734,   42,   84,
 /*   720 */    99,   42,  508,  185,  182,   86,   60,  748,   60,  185,
 /*   730 */   182,  138,  735,   88,  138,  754,  138,  138,  138,   90,
 /*   740 */    67,  138,   68,  134,   39,  632,  737,   69,  136,  723,
 /*   750 */    70,  138,   72,  708,  594,  755,  662,  755,  721,  622,
 /*   760 */   617,   63,   90,  643,   65,  748,  748,  569,  570,  571,
 /*   770 */    72,  755,  139,  598,   66,  593,  141,  592,  591,  143,
 /*   780 */    72,  758,  103,  101,  145,   85,   85,  590,  147,  589,
 /*   790 */   758,   85,   85,  149,  588,  151,  587,  758,  153,  586,
 /*   800 */   585,  155,  584,  758,  157,  583,  159,  582,  758,  161,
 /*   810 */   758,  163,  581,  580,  165,  758,  579,  167,   67,  758,
 /*   820 */    68,  755,  169,  578,  171,   69,  758,  577,   70,  576,
 /*   830 */   758,  173,  528,  175,   38,  500,   35,  501,  512,  513,
 /*   840 */   510,  758,  511,  758,  758,  758,  758,  758,  758,  758,
 /*   850 */   758,  758,  758,  758,  758,  758,  758,  758,   33,  758,
 /*   860 */   758,  758,  758,  758,  758,  758,  758,  758,  758,  758,
 /*   870 */   758,  758,  735,  758,  758,  735,  758,  735,  735,  735,
 /*   880 */   758,  758,  735,  758,  758,  758,  758,  758,  758,  758,
 /*   890 */   758,  758,  735,  758,  758,  758,  758,  758,  758,  758,
 /*   900 */   758,  758,  758,  758,  758,  758,  758,  758,  748,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     7,  102,  103,  104,  105,  106,  107,  108,  109,  110,
 /*    10 */    97,   98,   19,    7,  123,  102,  103,  126,  127,    7,
 /*    20 */     7,   19,  102,  103,   81,   82,   99,   34,  101,  102,
 /*    30 */   103,  102,   19,    7,   41,   42,   43,   44,   45,   46,
 /*    40 */    47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*    50 */    57,   58,  124,  124,   41,   42,   43,   44,   45,   46,
 /*    60 */    47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*    70 */    57,   58,  102,  103,    7,  105,  106,  107,  108,  109,
 /*    80 */   110,    7,   78,  157,   91,  159,   93,  167,  168,  169,
 /*    90 */   170,  171,  102,   91,  174,   76,  176,  198,  178,  179,
 /*   100 */   201,  181,  203,  175,  205,   93,   93,  208,   34,  210,
 /*   110 */     7,  212,   91,  214,  124,    7,    7,  218,  124,  220,
 /*   120 */   126,  127,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   130 */    27,   28,   29,   30,   31,   32,   33,  238,    7,  240,
 /*   140 */    95,   96,   97,   98,    2,    3,  217,  102,  103,    7,
 /*   150 */    19,   20,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   160 */    29,   30,   31,   32,   33,   91,  102,  103,  198,  241,
 /*   170 */   242,  201,  245,  203,    7,  205,   12,   13,  208,  115,
 /*   180 */   210,   73,  212,   75,  214,   77,   11,   79,  218,    7,
 /*   190 */   220,   83,    7,  124,   91,   10,   93,   16,   90,   14,
 /*   200 */    91,   93,   17,  102,  103,  215,  124,  217,  238,    7,
 /*   210 */   240,   19,  111,  112,  113,  114,  115,  116,  117,  118,
 /*   220 */    18,    7,  102,  103,   93,  102,  103,   60,   61,  128,
 /*   230 */    63,  130,   65,  242,  124,   93,    7,  136,  102,  103,
 /*   240 */   139,  162,  102,  103,   59,  144,  204,  124,  147,  207,
 /*   250 */   114,  115,  112,  113,  114,  115,  116,  117,  118,    7,
 /*   260 */    93,   59,  161,  199,  200,  164,  202,   85,  128,   87,
 /*   270 */   130,   89,   91,   88,  151,   93,  136,   92,   93,  139,
 /*   280 */    60,  102,  103,   69,  144,   71,    7,  147,  152,  153,
 /*   290 */   154,  155,  172,  173,   92,   93,  102,  161,  102,  103,
 /*   300 */   164,  161,  182,  183,  164,    5,  186,   93,  244,    7,
 /*   310 */   121,  102,  103,   84,   35,   36,   37,  102,  103,  102,
 /*   320 */   103,   92,   93,  114,  115,  124,  102,    6,  192,    7,
 /*   330 */   194,  209,  196,  211,    9,  234,    9,  236,   59,    9,
 /*   340 */     7,  162,  163,   91,  143,  166,  167,  168,  169,  170,
 /*   350 */   171,   72,  156,  174,    6,  176,  160,  178,  179,    9,
 /*   360 */   181,  152,  153,  154,  155,  102,  103,    8,   66,   67,
 /*   370 */   161,   92,   93,  164,  234,  124,  236,  114,  115,  102,
 /*   380 */   103,    6,  102,  103,    6,  102,  103,  102,  103,  165,
 /*   390 */    99,  114,  115,  102,  103,   93,    7,    9,  115,    6,
 /*   400 */   191,  192,  185,  194,  187,  188,  189,  190,    6,    9,
 /*   410 */   193,    6,  195,   91,  197,  152,  153,  154,  155,   86,
 /*   420 */   102,  103,  102,  103,  161,  140,   93,  164,  143,  152,
 /*   430 */   153,  154,  155,  115,  114,  115,  129,    9,  161,  132,
 /*   440 */     6,  164,  227,  228,    9,  230,  231,  232,  233,    6,
 /*   450 */   235,   62,  237,    9,  239,  102,   67,  194,    6,  196,
 /*   460 */   102,  103,    9,  102,  103,  145,  146,  243,  191,  149,
 /*   470 */   150,  194,  221,  115,  223,  224,  225,  119,  120,    6,
 /*   480 */   122,  161,   93,  200,  164,  102,  103,    9,  102,  103,
 /*   490 */     9,    7,    6,  102,  103,  137,  138,  114,  115,  141,
 /*   500 */   142,  115,  219,  102,  103,  222,  115,  227,  102,  103,
 /*   510 */   230,  231,  232,  233,    6,  235,  115,  237,  165,  239,
 /*   520 */   119,  120,  231,  122,  233,    9,  235,  244,  145,    6,
 /*   530 */   245,    7,  149,  150,  102,  103,  245,  219,  137,    7,
 /*   540 */   222,   19,  141,  142,  161,  184,    7,  164,  187,  188,
 /*   550 */   189,  190,   68,   69,  193,   71,  195,  102,  197,   35,
 /*   560 */    36,   37,  244,  102,  103,    9,  102,  103,  102,  103,
 /*   570 */     6,  102,  103,  102,  103,    7,  115,   93,  172,  124,
 /*   580 */     9,  124,  100,   59,  102,  103,  200,    4,  182,  183,
 /*   590 */     7,  102,  186,   61,   70,   63,  243,   65,   15,  213,
 /*   600 */   102,  103,  216,    7,  213,    7,   99,  216,  101,  102,
 /*   610 */   103,    6,  180,  124,  182,  183,   92,   93,  186,   80,
 /*   620 */   102,    9,  124,  102,   99,   93,  101,  102,  103,    6,
 /*   630 */   244,   92,   93,  102,   99,  244,  101,  102,  103,  173,
 /*   640 */     9,  177,  124,    1,  173,  124,  182,  183,  182,  183,
 /*   650 */   186,    6,  186,  182,  183,  124,  158,  186,  160,   91,
 /*   660 */   199,  206,   64,  202,    0,   67,    2,    3,  124,    7,
 /*   670 */    74,    7,  102,  103,  124,   92,   93,  102,    9,  102,
 /*   680 */   223,  224,  225,  165,  102,    7,  165,  102,   92,   93,
 /*   690 */    99,   93,    6,  102,  103,  206,  165,    9,  243,  124,
 /*   700 */   231,  124,  233,    6,  235,  244,  124,    9,  226,  124,
 /*   710 */   102,  229,   99,  124,  245,  102,  103,    6,  148,  175,
 /*   720 */    19,  151,  133,  134,  135,  175,  131,  245,  133,  134,
 /*   730 */   135,  102,  243,  125,  102,    7,  102,  102,  102,  102,
 /*   740 */   165,  102,  165,    9,   16,   67,    6,  165,    9,   87,
 /*   750 */   165,  102,  245,  124,    6,   93,  124,   93,  124,  124,
 /*   760 */   124,  243,  125,  124,  243,  102,  103,   38,   39,   40,
 /*   770 */   245,   93,    9,  124,  243,    6,    9,    6,    6,    9,
 /*   780 */   245,  246,   81,   82,    9,  241,  242,    6,    9,    6,
 /*   790 */   246,  241,  242,    9,    6,    9,    6,  246,    9,    6,
 /*   800 */     6,    9,    6,  246,    9,    6,    9,    6,  246,    9,
 /*   810 */   246,    9,    6,    6,    9,  246,    6,    9,  243,  246,
 /*   820 */   243,   93,    9,    6,    9,  243,  246,    6,  243,    6,
 /*   830 */   246,    9,    6,    9,    9,    6,  245,    9,    6,    9,
 /*   840 */     6,  246,    9,  246,  246,  246,  246,  246,  246,  246,
 /*   850 */   246,  246,  246,  246,  246,  246,  246,  246,  245,  246,
 /*   860 */   246,  246,  246,  246,  246,  246,  246,  246,  246,  246,
 /*   870 */   246,  246,  243,  246,  246,  243,  246,  243,  243,  243,
 /*   880 */   246,  246,  243,  246,  246,  246,  246,  246,  246,  246,
 /*   890 */   246,  246,  243,  246,  246,  246,  246,  246,  246,  246,
 /*   900 */   246,  246,  246,  246,  246,  246,  246,  246,  245,
};
#define YY_SHIFT_USE_DFLT (909)
#define YY_SHIFT_COUNT    (186)
#define YY_SHIFT_MIN      (-57)
#define YY_SHIFT_MAX      (834)
static const short yy_shift_ofst[] = {
 /*     0 */   142,  108,  108,  185,  185,  167,  279,  524,  279,  524,
 /*    10 */   532,  182,  484,  202,  583,  182,  214,  202,  583,  229,
 /*    20 */   539,  596,  389,  662,  229,  539,  596,  302,  598,  389,
 /*    30 */   678,  678,  662,  333,   -7,  728,  109,   12,   12,   12,
 /*    40 */    12,   13,  103,  131,  664,   74,   74,  252,  109,  252,
 /*    50 */   252,  252,  252,  252,    2,    2,    2,  252,  252,   12,
 /*    60 */   322,   12,    6,  252,  252,  252,  252,  252,  252,  252,
 /*    70 */   252,  568,   12,   26,   26,   67,  729,  181,    4,   19,
 /*    80 */    26,   26,  175,   21,   21,  192,   21,  220,   26,  300,
 /*    90 */    26,  701,  -57,  164,  321,  325,  327,  348,  375,  330,
 /*   100 */   378,  350,  393,  388,  402,  400,  405,  428,  434,  435,
 /*   110 */   443,  444,  452,  453,  473,  478,  486,  481,  508,  516,
 /*   120 */   523,  556,  564,  571,  605,  612,  623,  631,  645,  669,
 /*   130 */   686,  688,  697,  698,  711,  734,  740,  739,  522,  748,
 /*   140 */   763,  769,  767,  771,  770,  772,  775,  781,  779,  783,
 /*   150 */   784,  788,  786,  790,  789,  793,  792,  794,  795,  796,
 /*   160 */   797,  799,  800,  801,  802,  806,  805,  807,  808,  810,
 /*   170 */   813,  817,  815,  821,  822,  823,  824,  826,  825,  828,
 /*   180 */   359,  829,  832,  830,  833,  834,  642,
};
#define YY_REDUCE_USE_DFLT (-110)
#define YY_REDUCE_COUNT (90)
#define YY_REDUCE_MIN   (-109)
#define YY_REDUCE_MAX   (663)
static const short yy_reduce_ofst[] = {
 /*     0 */    45, -101,  -30,  101,  140,  179,  136,  209,  263,  277,
 /*    10 */   -80,  215,  217,  320,  358,  280,  361,  383,  401,  283,
 /*    20 */   386,   64,  120,  291,  318,  391,  461,  432,  464,  406,
 /*    30 */   466,  471,  469,  482,  498,  285,  251,  -73,  507,  525,
 /*    40 */   535,  196,  123,  570,  -87,  455,  489,  518,  457,  -10,
 /*    50 */   521,  531,  575,  577,  -72,  544,  550,  582,  585,  591,
 /*    60 */   589,  613,  595,  629,  -71,  632,  634,  635,  636,  639,
 /*    70 */   649,   -6,  663,  224,  353, -109,  -74,  201,  122,   42,
 /*    80 */   608,  637,  307,   69,   82,   -9,  110,   79,  194,  189,
 /*    90 */   194,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*    10 */   891, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*    20 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*    30 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1037, 1037, 1037,
 /*    40 */  1037, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*    50 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*    60 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*    70 */  1046, 1046, 1036, 1046, 1046, 1046, 1046, 1046,  963,  956,
 /*    80 */   784,  793, 1046, 1046, 1046, 1021, 1046, 1046,  785, 1046,
 /*    90 */   794, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*   100 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*   110 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*   120 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*   130 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*   140 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*   150 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*   160 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*   170 */  1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 /*   180 */  1046, 1046, 1046, 1046, 1046, 1046, 1046,
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
  "HTMLTEXT",      "ENTER",         "error",         "start",       
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
  "tagcontrolblockproperties",  "tagcontrolblockblockclose",  "tagcontrolblockcontent",  "tagcontrolblockproperty",
  "tagdatablockfullopen",  "tagdatablockblockclosefull",  "tagdatablockcontents",  "tagdatablockopen",
  "tagdatablockproperties",  "tagdatablockblockclose",  "tagdatablockcontent",  "tagdatablockproperty",
  "taginput",      "taginput_with_block",  "taginput_without_block",  "taginputopen",
  "taginputproperties",  "taginputblockclosefull",  "taginputshortclose",  "taginputblockclose",
  "taginputproperty",  "tagtablefullopen",  "tagtableblockclosefull",  "tablecontent",
  "tagtableopen",  "tagproperties",  "tablecontentparts",  "tablecontentpart",
  "tagthead",      "tagtbody",      "tagtfoot",      "tagtheadfullopen",
  "tagtheadblockclosefull",  "tagtablerows",  "tagtheadopen",  "tagpropertieswithreturnvaluesall",
  "tagtfootfullopen",  "tagtfootblockclosefull",  "tagtfootopen",  "tagtbodyfullopen",
  "tagtbodyblockclosefull",  "tagtbodyopen",  "tagtablerow",   "tagtablerowfullopen",
  "tagtablecols",  "tagtablerowblockclosefull",  "tagtablerowopen",  "tagtablecol", 
  "tagtablecoltd",  "tagtablecolth",  "tagtablecoltdfullopen",  "tagtablecoltdblockclosefull",
  "tagtablecolcontents",  "tagtablecoltdopen",  "tagtablecolcontent",  "tagtablecolthfullopen",
  "tagtablecolthblockclosefull",  "tagtablecolthopen",  "tagtitlefullopen",  "tagtitleblockclosefull",
  "htmlandspaces",  "tagtitleopen",  "tagtitleblockclose",  "taglinkfullopen",
  "taglinkblockclosefull",  "taglinkopen",   "tagshortclose",  "taglinkblockclose",
  "tagmetafullopen",  "tagmetablockclosefull",  "tagmetaopen",   "tagmetablockclose",
  "tagstylefullopen",  "tagstyleblockclosefull",  "tagstyleopen",  "tagstyleproperties",
  "tagstyleblockclose",  "tagstyleproperty",  "tagscriptfullopen",  "tagscriptblockclosefull",
  "tagscriptopen",  "tagscriptproperties",  "tagscriptblockclose",  "tagscriptproperty",
  "tagscriptpropertyscripttype",  "tagscriptpropertysrc",  "taghtmlfullopen",  "taghtmlblockclosefull",
  "taghtmlcontents",  "taghtmlopen",   "taghtmlcontent",  "tagbody",     
  "taghead",       "tagbodyfullopen",  "tagbodyblockclosefull",  "tagbodyopen", 
  "tagbodyblockclose",  "tagheadfullopen",  "tagheadblockclosefull",  "tagheadopen", 
  "tagheadblockclose",  "tagpropertieswithreturnvalues",  "tagpropertywithreturnvalue",  "tagproperty", 
  "htmlandspace",  "spaces_enter",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "start ::= expressions",
 /*   1 */ "expressions ::= expressions expression",
 /*   2 */ "expressions ::= expression",
 /*   3 */ "expression ::= tagdoctype spaces_enters taghtml opt__spaces_enters END_OF_FILE",
 /*   4 */ "expression ::= space",
 /*   5 */ "expression ::= enter",
 /*   6 */ "tagheadcontents ::= tagheadcontents tagheadcontent",
 /*   7 */ "tagheadcontents ::= tagheadcontent",
 /*   8 */ "tagheadcontent ::= space",
 /*   9 */ "tagheadcontent ::= enter",
 /*  10 */ "tagheadcontent ::= tagtitle",
 /*  11 */ "tagheadcontent ::= tagscript",
 /*  12 */ "tagheadcontent ::= tagstyle",
 /*  13 */ "tagheadcontent ::= taglink",
 /*  14 */ "tagheadcontent ::= tagmeta",
 /*  15 */ "tagbodycontents ::= tagbodycontents tagbodycontent",
 /*  16 */ "tagbodycontents ::= tagbodycontent",
 /*  17 */ "tagbodycontent ::= htsqls",
 /*  18 */ "tagbodycontent ::= tagtable",
 /*  19 */ "tagbodycontent ::= space",
 /*  20 */ "tagbodycontent ::= enter",
 /*  21 */ "tagbodycontent ::= htmltext",
 /*  22 */ "htsqls ::= tagdatablock",
 /*  23 */ "htsqls ::= tagcontrolblock",
 /*  24 */ "htsqls ::= tagdatalist",
 /*  25 */ "tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD",
 /*  26 */ "tagdoctype ::= TAG_DOCTYPE_HTML",
 /*  27 */ "tagtree ::= tagtreefullopen tagtreeblockclosefull",
 /*  28 */ "tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar",
 /*  29 */ "tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces",
 /*  30 */ "tagtreeopen ::= TAG_TREE_OPEN",
 /*  31 */ "tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE",
 /*  32 */ "tagtreeproperties ::= tagtreeproperties tagtreeproperty",
 /*  33 */ "tagtreeproperties ::= tagtreeproperty",
 /*  34 */ "tagtreeproperty ::= tagtreepropertyid PROPERTYDATA",
 /*  35 */ "tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT",
 /*  36 */ "tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull",
 /*  37 */ "tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar",
 /*  38 */ "tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces",
 /*  39 */ "tagdatalistopen ::= TAG_DATALIST_OPEN",
 /*  40 */ "tagdatalistblockclosefull ::= tagdatalistblockclose",
 /*  41 */ "tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE",
 /*  42 */ "datalistproperties ::= datalistproperties datalistproperty",
 /*  43 */ "datalistproperties ::= datalistproperty",
 /*  44 */ "datalistproperty ::= tagdatalistpropertyid PROPERTYDATA",
 /*  45 */ "tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT",
 /*  46 */ "datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA",
 /*  47 */ "tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT",
 /*  48 */ "tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull",
 /*  49 */ "tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull",
 /*  50 */ "tagcontrolblockfullopen ::= tagcontrolblockopen spaces_enters tagcontrolblockproperties tagclosechar",
 /*  51 */ "tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN",
 /*  52 */ "tagcontrolblockclosefull ::= tagcontrolblockblockclose",
 /*  53 */ "tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE",
 /*  54 */ "tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent",
 /*  55 */ "tagcontrolblockcontents ::= tagcontrolblockcontent",
 /*  56 */ "tagcontrolblockcontent ::= tagtree",
 /*  57 */ "tagcontrolblockcontent ::= space",
 /*  58 */ "tagcontrolblockcontent ::= enter",
 /*  59 */ "tagcontrolblockcontent ::= htmltext",
 /*  60 */ "tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty",
 /*  61 */ "tagcontrolblockproperties ::= tagcontrolblockproperty",
 /*  62 */ "tagcontrolblockproperty ::= PROP_CONTROLBLOCK_BLOCK_NAME opt__spaces_enters ASSIGMENT opt__spaces_enters PROPERTYDATA",
 /*  63 */ "tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull",
 /*  64 */ "tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull",
 /*  65 */ "tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar",
 /*  66 */ "tagdatablockopen ::= TAG_DATABLOCK_OPEN",
 /*  67 */ "tagdatablockblockclosefull ::= tagdatablockblockclose",
 /*  68 */ "tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE",
 /*  69 */ "tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent",
 /*  70 */ "tagdatablockcontents ::= tagdatablockcontent",
 /*  71 */ "tagdatablockcontent ::= tagtable",
 /*  72 */ "tagdatablockcontent ::= space",
 /*  73 */ "tagdatablockcontent ::= enter",
 /*  74 */ "tagdatablockcontent ::= htmltext",
 /*  75 */ "tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty",
 /*  76 */ "tagdatablockproperties ::= tagdatablockproperty",
 /*  77 */ "tagdatablockproperty ::= space",
 /*  78 */ "tagdatablockproperty ::= enter",
 /*  79 */ "tagdatablockproperty ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /*  80 */ "tagdatablockproperty ::= PROP_BLOCK_JOIN_CONDITION ASSIGMENT PROPERTYDATA",
 /*  81 */ "tagdatablockproperty ::= PROP_BLOCK_CONNECTION_NAME ASSIGMENT PROPERTYDATA",
 /*  82 */ "tagdatablockproperty ::= PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT PROPERTYDATA",
 /*  83 */ "tagdatablockproperty ::= PROP_BLOCK_RECORD_COUNT ASSIGMENT PROPERTYDATA",
 /*  84 */ "tagdatablockproperty ::= PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT PROPERTYDATA",
 /*  85 */ "tagdatablockproperty ::= PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT PROPERTYDATA",
 /*  86 */ "tagdatablockproperty ::= PROP_BLOCK_BLOCK_NAME ASSIGMENT PROPERTYDATA",
 /*  87 */ "tagdatablockproperty ::= PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT PROPERTYDATA",
 /*  88 */ "tagdatablockproperty ::= PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT PROPERTYDATA",
 /*  89 */ "tagdatablockproperty ::= PROP_BLOCK_INSERT_ALLOWED ASSIGMENT PROPERTYDATA",
 /*  90 */ "tagdatablockproperty ::= PROP_BLOCK_DELETE_ALLOWED ASSIGMENT PROPERTYDATA",
 /*  91 */ "tagdatablockproperty ::= PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT PROPERTYDATA",
 /*  92 */ "tagdatablockproperty ::= PROP_BLOCK_WHERE_CLAUSE ASSIGMENT PROPERTYDATA",
 /*  93 */ "tagdatablockproperty ::= PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT PROPERTYDATA",
 /*  94 */ "taginput ::= taginput_with_block",
 /*  95 */ "taginput ::= taginput_without_block",
 /*  96 */ "taginput_with_block ::= taginputopen taginputproperties tagclosechar opt__spaces_enters taginputblockclosefull",
 /*  97 */ "taginput_without_block ::= taginputopen taginputproperties taginputshortclose",
 /*  98 */ "taginputshortclose ::= TAG_SHORT_CLOSE",
 /*  99 */ "taginputopen ::= TAG_INPUT_OPEN",
 /* 100 */ "taginputopen ::= TAG_SELECT_OPEN",
 /* 101 */ "taginputopen ::= TAG_TEXTAREA_OPEN",
 /* 102 */ "taginputblockclosefull ::= taginputblockclose",
 /* 103 */ "taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE",
 /* 104 */ "taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE",
 /* 105 */ "taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE",
 /* 106 */ "taginputproperties ::= taginputproperties taginputproperty",
 /* 107 */ "taginputproperties ::= taginputproperty",
 /* 108 */ "taginputproperty ::= space",
 /* 109 */ "taginputproperty ::= enter",
 /* 110 */ "taginputproperty ::= PROP_INPUT_CHECKED_VALUE ASSIGMENT PROPERTYDATA",
 /* 111 */ "taginputproperty ::= PROP_INPUT_UNCHECKED_VALUE ASSIGMENT PROPERTYDATA",
 /* 112 */ "taginputproperty ::= PROP_INPUT_NAME ASSIGMENT PROPERTYDATA",
 /* 113 */ "taginputproperty ::= PROP_INPUT_SEQUENCE_NAME ASSIGMENT PROPERTYDATA",
 /* 114 */ "taginputproperty ::= PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT PROPERTYDATA",
 /* 115 */ "taginputproperty ::= PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT PROPERTYDATA",
 /* 116 */ "taginputproperty ::= PROP_INPUT_TYPE ASSIGMENT PROPERTYDATA",
 /* 117 */ "taginputproperty ::= PROP_INPUT_VALUE ASSIGMENT PROPERTYDATA",
 /* 118 */ "taginputproperty ::= PROP_INPUT_DEFAULT_VALUE ASSIGMENT PROPERTYDATA",
 /* 119 */ "taginputproperty ::= PROP_INPUT_COLUMN_NAME ASSIGMENT PROPERTYDATA",
 /* 120 */ "taginputproperty ::= PROP_INPUT_FORMAT_MASK ASSIGMENT PROPERTYDATA",
 /* 121 */ "taginputproperty ::= PROP_INPUT_DATA_TYPE ASSIGMENT PROPERTYDATA",
 /* 122 */ "taginputproperty ::= PROP_INPUT_MAX_LENGTH ASSIGMENT PROPERTYDATA",
 /* 123 */ "taginputproperty ::= PROP_INPUT_INSERT_ALLOWED ASSIGMENT PROPERTYDATA",
 /* 124 */ "taginputproperty ::= PROP_INPUT_UPDATE_ALLOWED ASSIGMENT PROPERTYDATA",
 /* 125 */ "taginputproperty ::= PROP_INPUT_DATALIST_NAME ASSIGMENT PROPERTYDATA",
 /* 126 */ "taginputproperty ::= PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT PROPERTYDATA",
 /* 127 */ "taginputproperty ::= PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT PROPERTYDATA",
 /* 128 */ "taginputproperty ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 129 */ "tagtable ::= tagtablefullopen tagtableblockclosefull",
 /* 130 */ "tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull",
 /* 131 */ "tagtablefullopen ::= tagtableopen tagclosechar",
 /* 132 */ "tagtablefullopen ::= tagtableopen tagproperties tagclosechar",
 /* 133 */ "tagtableopen ::= TAG_TABLE_OPEN",
 /* 134 */ "tagtableblockclosefull ::= TAG_TABLE_BLOCK_CLOSE",
 /* 135 */ "tablecontent ::= tablecontentparts",
 /* 136 */ "tablecontentparts ::= tablecontentparts tablecontentpart",
 /* 137 */ "tablecontentparts ::= tablecontentpart",
 /* 138 */ "tablecontentpart ::= space",
 /* 139 */ "tablecontentpart ::= enter",
 /* 140 */ "tablecontentpart ::= tagthead",
 /* 141 */ "tablecontentpart ::= tagtbody",
 /* 142 */ "tablecontentpart ::= tagtfoot",
 /* 143 */ "tagthead ::= tagtheadfullopen tagtheadblockclosefull",
 /* 144 */ "tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull",
 /* 145 */ "tagtheadfullopen ::= tagtheadopen tagclosechar",
 /* 146 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 147 */ "tagtheadopen ::= TAG_THEAD_OPEN",
 /* 148 */ "tagtheadblockclosefull ::= TAG_THEAD_BLOCK_CLOSE",
 /* 149 */ "tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull",
 /* 150 */ "tagtfootfullopen ::= tagtfootopen tagclosechar",
 /* 151 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar",
 /* 152 */ "tagtfootopen ::= TAG_TFOOT_OPEN",
 /* 153 */ "tagtfootblockclosefull ::= TAG_TFOOT_BLOCK_CLOSE",
 /* 154 */ "tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull",
 /* 155 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar",
 /* 156 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar",
 /* 157 */ "tagtbodyopen ::= TAG_TBODY_OPEN",
 /* 158 */ "tagtbodyblockclosefull ::= TAG_TBODY_BLOCK_CLOSE",
 /* 159 */ "tagtablerows ::= tagtablerows tagtablerow",
 /* 160 */ "tagtablerows ::= tagtablerow",
 /* 161 */ "tagtablerow ::= space",
 /* 162 */ "tagtablerow ::= enter",
 /* 163 */ "tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull",
 /* 164 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar",
 /* 165 */ "tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 166 */ "tagtablerowopen ::= TAG_TR_OPEN",
 /* 167 */ "tagtablerowblockclosefull ::= TAG_TR_BLOCK_CLOSE",
 /* 168 */ "tagtablecols ::= tagtablecols tagtablecol",
 /* 169 */ "tagtablecols ::= tagtablecol",
 /* 170 */ "tagtablecol ::= space",
 /* 171 */ "tagtablecol ::= enter",
 /* 172 */ "tagtablecol ::= tagtablecoltd",
 /* 173 */ "tagtablecol ::= tagtablecolth",
 /* 174 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull",
 /* 175 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull",
 /* 176 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar",
 /* 177 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar",
 /* 178 */ "tagtablecoltdopen ::= TAG_TD_OPEN",
 /* 179 */ "tagtablecoltdblockclosefull ::= TAG_TD_BLOCK_CLOSE",
 /* 180 */ "tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent",
 /* 181 */ "tagtablecolcontents ::= tagtablecolcontent",
 /* 182 */ "tagtablecolcontent ::= taginput",
 /* 183 */ "tagtablecolcontent ::= htmltext",
 /* 184 */ "tagtablecolcontent ::= tagtable",
 /* 185 */ "tagtablecolcontent ::= space",
 /* 186 */ "tagtablecolcontent ::= enter",
 /* 187 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull",
 /* 188 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull",
 /* 189 */ "tagtablecolthfullopen ::= tagtablecolthopen tagclosechar",
 /* 190 */ "tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 191 */ "tagtablecolthopen ::= TAG_TH_OPEN",
 /* 192 */ "tagtablecolthblockclosefull ::= TAG_TH_BLOCK_CLOSE",
 /* 193 */ "tagtitle ::= tagtitlefullopen tagtitleblockclosefull",
 /* 194 */ "tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull",
 /* 195 */ "tagtitlefullopen ::= tagtitleopen tagclosechar",
 /* 196 */ "tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar",
 /* 197 */ "tagtitleblockclosefull ::= tagtitleblockclose",
 /* 198 */ "tagtitleopen ::= TAG_TITLE_OPEN",
 /* 199 */ "tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE",
 /* 200 */ "taglink ::= taglinkfullopen",
 /* 201 */ "taglink ::= taglinkfullopen taglinkblockclosefull",
 /* 202 */ "taglinkfullopen ::= taglinkopen tagproperties tagclosechar",
 /* 203 */ "taglinkfullopen ::= taglinkopen tagproperties tagshortclose",
 /* 204 */ "taglinkblockclosefull ::= taglinkblockclose",
 /* 205 */ "taglinkopen ::= TAG_LINK_OPEN",
 /* 206 */ "taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE",
 /* 207 */ "tagmeta ::= tagmetafullopen",
 /* 208 */ "tagmeta ::= tagmetafullopen tagmetablockclosefull",
 /* 209 */ "tagmetafullopen ::= tagmetaopen tagproperties tagclosechar",
 /* 210 */ "tagmetafullopen ::= tagmetaopen tagproperties tagshortclose",
 /* 211 */ "tagmetablockclosefull ::= tagmetablockclose",
 /* 212 */ "tagmetaopen ::= TAG_META_OPEN",
 /* 213 */ "tagmetablockclose ::= TAG_META_BLOCK_CLOSE",
 /* 214 */ "tagstyle ::= tagstylefullopen tagstyleblockclosefull",
 /* 215 */ "tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull",
 /* 216 */ "tagstylefullopen ::= tagstyleopen tagclosechar",
 /* 217 */ "tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar",
 /* 218 */ "tagstyleblockclosefull ::= tagstyleblockclose",
 /* 219 */ "tagstyleopen ::= TAG_STYLE_OPEN",
 /* 220 */ "tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE",
 /* 221 */ "tagstyleproperties ::= tagstyleproperties tagstyleproperty",
 /* 222 */ "tagstyleproperties ::= tagstyleproperty",
 /* 223 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA",
 /* 224 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA",
 /* 225 */ "tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 226 */ "tagscript ::= tagscriptfullopen tagscriptblockclosefull",
 /* 227 */ "tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull",
 /* 228 */ "tagscriptfullopen ::= tagscriptopen tagclosechar",
 /* 229 */ "tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar",
 /* 230 */ "tagscriptblockclosefull ::= tagscriptblockclose",
 /* 231 */ "tagscriptopen ::= TAG_SCRIPT_OPEN",
 /* 232 */ "tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE",
 /* 233 */ "tagscriptproperties ::= tagscriptproperties tagscriptproperty",
 /* 234 */ "tagscriptproperties ::= tagscriptproperty",
 /* 235 */ "tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA",
 /* 236 */ "tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT",
 /* 237 */ "tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA",
 /* 238 */ "tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT",
 /* 239 */ "taghtml ::= taghtmlfullopen taghtmlblockclosefull",
 /* 240 */ "taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull",
 /* 241 */ "taghtmlfullopen ::= taghtmlopen tagclosechar",
 /* 242 */ "taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar",
 /* 243 */ "taghtmlblockclosefull ::= TAG_HTML_BLOCK_CLOSE",
 /* 244 */ "taghtmlopen ::= TAG_HTML_OPEN",
 /* 245 */ "taghtmlcontents ::= taghtmlcontents taghtmlcontent",
 /* 246 */ "taghtmlcontents ::= taghtmlcontent",
 /* 247 */ "taghtmlcontent ::= space",
 /* 248 */ "taghtmlcontent ::= enter",
 /* 249 */ "taghtmlcontent ::= tagbody",
 /* 250 */ "taghtmlcontent ::= taghead tagbody",
 /* 251 */ "taghtmlcontent ::= taghead spaces_enters tagbody",
 /* 252 */ "tagbody ::= tagbodyfullopen tagbodyblockclosefull",
 /* 253 */ "tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull",
 /* 254 */ "tagbodyfullopen ::= tagbodyopen tagclosechar",
 /* 255 */ "tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar",
 /* 256 */ "tagbodyblockclosefull ::= tagbodyblockclose",
 /* 257 */ "tagbodyopen ::= TAG_BODY_OPEN",
 /* 258 */ "tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE",
 /* 259 */ "taghead ::= tagheadfullopen tagheadblockclosefull",
 /* 260 */ "taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull",
 /* 261 */ "tagheadfullopen ::= tagheadopen",
 /* 262 */ "tagheadblockclosefull ::= tagheadblockclose",
 /* 263 */ "tagheadopen ::= TAG_HEAD_OPEN",
 /* 264 */ "tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE",
 /* 265 */ "tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues",
 /* 266 */ "tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue",
 /* 267 */ "tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue",
 /* 268 */ "tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 269 */ "tagproperties ::= tagproperties tagproperty",
 /* 270 */ "tagproperties ::= tagproperty",
 /* 271 */ "tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 272 */ "tagclosechar ::= TAG_CLOSE",
 /* 273 */ "tagshortclose ::= TAG_SHORT_CLOSE",
 /* 274 */ "htmlandspaces ::= htmlandspaces htmlandspace",
 /* 275 */ "htmlandspaces ::= htmlandspace",
 /* 276 */ "htmlandspace ::= htmltext",
 /* 277 */ "htmlandspace ::= space",
 /* 278 */ "htmlandspace ::= enter",
 /* 279 */ "htmltext ::= HTMLTEXT",
 /* 280 */ "opt__spaces_enters ::= spaces_enters",
 /* 281 */ "opt__spaces_enters ::=",
 /* 282 */ "spaces_enters ::= spaces_enters spaces_enter",
 /* 283 */ "spaces_enters ::= spaces_enter",
 /* 284 */ "spaces_enter ::= space",
 /* 285 */ "spaces_enter ::= enter",
 /* 286 */ "spaces ::= spaces space",
 /* 287 */ "spaces ::= space",
 /* 288 */ "space ::= SPACE",
 /* 289 */ "enter ::= ENTER",
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
    case 93: /* ENTER */
{
#line 37 "lemon.html.yy"

    Token *token = (yypminor->yy0);
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
    }

#line 1138 "lemon.html.c"
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
    case 141: /* tagcontrolblockblockclose */
    case 142: /* tagcontrolblockcontent */
    case 143: /* tagcontrolblockproperty */
    case 144: /* tagdatablockfullopen */
    case 145: /* tagdatablockblockclosefull */
    case 146: /* tagdatablockcontents */
    case 147: /* tagdatablockopen */
    case 148: /* tagdatablockproperties */
    case 149: /* tagdatablockblockclose */
    case 150: /* tagdatablockcontent */
    case 151: /* tagdatablockproperty */
    case 152: /* taginput */
    case 153: /* taginput_with_block */
    case 154: /* taginput_without_block */
    case 155: /* taginputopen */
    case 156: /* taginputproperties */
    case 157: /* taginputblockclosefull */
    case 158: /* taginputshortclose */
    case 159: /* taginputblockclose */
    case 160: /* taginputproperty */
    case 161: /* tagtablefullopen */
    case 162: /* tagtableblockclosefull */
    case 163: /* tablecontent */
    case 164: /* tagtableopen */
    case 165: /* tagproperties */
    case 166: /* tablecontentparts */
    case 167: /* tablecontentpart */
    case 168: /* tagthead */
    case 169: /* tagtbody */
    case 170: /* tagtfoot */
    case 171: /* tagtheadfullopen */
    case 172: /* tagtheadblockclosefull */
    case 173: /* tagtablerows */
    case 174: /* tagtheadopen */
    case 175: /* tagpropertieswithreturnvaluesall */
    case 176: /* tagtfootfullopen */
    case 177: /* tagtfootblockclosefull */
    case 178: /* tagtfootopen */
    case 179: /* tagtbodyfullopen */
    case 180: /* tagtbodyblockclosefull */
    case 181: /* tagtbodyopen */
    case 182: /* tagtablerow */
    case 183: /* tagtablerowfullopen */
    case 184: /* tagtablecols */
    case 185: /* tagtablerowblockclosefull */
    case 186: /* tagtablerowopen */
    case 187: /* tagtablecol */
    case 188: /* tagtablecoltd */
    case 189: /* tagtablecolth */
    case 190: /* tagtablecoltdfullopen */
    case 191: /* tagtablecoltdblockclosefull */
    case 192: /* tagtablecolcontents */
    case 193: /* tagtablecoltdopen */
    case 194: /* tagtablecolcontent */
    case 195: /* tagtablecolthfullopen */
    case 196: /* tagtablecolthblockclosefull */
    case 197: /* tagtablecolthopen */
    case 198: /* tagtitlefullopen */
    case 199: /* tagtitleblockclosefull */
    case 200: /* htmlandspaces */
    case 201: /* tagtitleopen */
    case 202: /* tagtitleblockclose */
    case 203: /* taglinkfullopen */
    case 204: /* taglinkblockclosefull */
    case 205: /* taglinkopen */
    case 206: /* tagshortclose */
    case 207: /* taglinkblockclose */
    case 208: /* tagmetafullopen */
    case 209: /* tagmetablockclosefull */
    case 210: /* tagmetaopen */
    case 211: /* tagmetablockclose */
    case 212: /* tagstylefullopen */
    case 213: /* tagstyleblockclosefull */
    case 214: /* tagstyleopen */
    case 215: /* tagstyleproperties */
    case 216: /* tagstyleblockclose */
    case 217: /* tagstyleproperty */
    case 218: /* tagscriptfullopen */
    case 219: /* tagscriptblockclosefull */
    case 220: /* tagscriptopen */
    case 221: /* tagscriptproperties */
    case 222: /* tagscriptblockclose */
    case 223: /* tagscriptproperty */
    case 224: /* tagscriptpropertyscripttype */
    case 225: /* tagscriptpropertysrc */
    case 226: /* taghtmlfullopen */
    case 227: /* taghtmlblockclosefull */
    case 228: /* taghtmlcontents */
    case 229: /* taghtmlopen */
    case 230: /* taghtmlcontent */
    case 231: /* tagbody */
    case 232: /* taghead */
    case 233: /* tagbodyfullopen */
    case 234: /* tagbodyblockclosefull */
    case 235: /* tagbodyopen */
    case 236: /* tagbodyblockclose */
    case 237: /* tagheadfullopen */
    case 238: /* tagheadblockclosefull */
    case 239: /* tagheadopen */
    case 240: /* tagheadblockclose */
    case 241: /* tagpropertieswithreturnvalues */
    case 242: /* tagpropertywithreturnvalue */
    case 243: /* tagproperty */
    case 244: /* htmlandspace */
    case 245: /* spaces_enter */
{
#line 54 "lemon.html.yy"



#line 1299 "lemon.html.c"
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
  { 137, 1 },
  { 141, 1 },
  { 138, 2 },
  { 138, 1 },
  { 142, 1 },
  { 142, 1 },
  { 142, 1 },
  { 142, 1 },
  { 140, 2 },
  { 140, 1 },
  { 143, 5 },
  { 116, 2 },
  { 116, 3 },
  { 144, 3 },
  { 147, 1 },
  { 145, 1 },
  { 149, 1 },
  { 146, 2 },
  { 146, 1 },
  { 150, 1 },
  { 150, 1 },
  { 150, 1 },
  { 150, 1 },
  { 148, 2 },
  { 148, 1 },
  { 151, 1 },
  { 151, 1 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 151, 3 },
  { 152, 1 },
  { 152, 1 },
  { 153, 5 },
  { 154, 3 },
  { 158, 1 },
  { 155, 1 },
  { 155, 1 },
  { 155, 1 },
  { 157, 1 },
  { 159, 1 },
  { 159, 1 },
  { 159, 1 },
  { 156, 2 },
  { 156, 1 },
  { 160, 1 },
  { 160, 1 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 160, 3 },
  { 114, 2 },
  { 114, 3 },
  { 161, 2 },
  { 161, 3 },
  { 164, 1 },
  { 162, 1 },
  { 163, 1 },
  { 166, 2 },
  { 166, 1 },
  { 167, 1 },
  { 167, 1 },
  { 167, 1 },
  { 167, 1 },
  { 167, 1 },
  { 168, 2 },
  { 168, 3 },
  { 171, 2 },
  { 171, 3 },
  { 174, 1 },
  { 172, 1 },
  { 170, 3 },
  { 176, 2 },
  { 176, 3 },
  { 178, 1 },
  { 177, 1 },
  { 169, 3 },
  { 179, 2 },
  { 179, 3 },
  { 181, 1 },
  { 180, 1 },
  { 173, 2 },
  { 173, 1 },
  { 182, 1 },
  { 182, 1 },
  { 182, 3 },
  { 183, 2 },
  { 183, 3 },
  { 186, 1 },
  { 185, 1 },
  { 184, 2 },
  { 184, 1 },
  { 187, 1 },
  { 187, 1 },
  { 187, 1 },
  { 187, 1 },
  { 188, 2 },
  { 188, 3 },
  { 190, 2 },
  { 190, 3 },
  { 193, 1 },
  { 191, 1 },
  { 192, 2 },
  { 192, 1 },
  { 194, 1 },
  { 194, 1 },
  { 194, 1 },
  { 194, 1 },
  { 194, 1 },
  { 189, 2 },
  { 189, 3 },
  { 195, 2 },
  { 195, 3 },
  { 197, 1 },
  { 196, 1 },
  { 106, 2 },
  { 106, 3 },
  { 198, 2 },
  { 198, 3 },
  { 199, 1 },
  { 201, 1 },
  { 202, 1 },
  { 109, 1 },
  { 109, 2 },
  { 203, 3 },
  { 203, 3 },
  { 204, 1 },
  { 205, 1 },
  { 207, 1 },
  { 110, 1 },
  { 110, 2 },
  { 208, 3 },
  { 208, 3 },
  { 209, 1 },
  { 210, 1 },
  { 211, 1 },
  { 108, 2 },
  { 108, 3 },
  { 212, 2 },
  { 212, 3 },
  { 213, 1 },
  { 214, 1 },
  { 216, 1 },
  { 215, 2 },
  { 215, 1 },
  { 217, 4 },
  { 217, 4 },
  { 217, 4 },
  { 107, 2 },
  { 107, 3 },
  { 218, 2 },
  { 218, 3 },
  { 219, 1 },
  { 220, 1 },
  { 222, 1 },
  { 221, 2 },
  { 221, 1 },
  { 223, 2 },
  { 224, 3 },
  { 223, 2 },
  { 225, 3 },
  { 100, 2 },
  { 100, 3 },
  { 226, 2 },
  { 226, 3 },
  { 227, 1 },
  { 229, 1 },
  { 228, 2 },
  { 228, 1 },
  { 230, 1 },
  { 230, 1 },
  { 230, 1 },
  { 230, 2 },
  { 230, 3 },
  { 231, 2 },
  { 231, 3 },
  { 233, 2 },
  { 233, 3 },
  { 234, 1 },
  { 235, 1 },
  { 236, 1 },
  { 232, 2 },
  { 232, 3 },
  { 237, 1 },
  { 238, 1 },
  { 239, 1 },
  { 240, 1 },
  { 175, 1 },
  { 241, 2 },
  { 241, 1 },
  { 242, 3 },
  { 165, 2 },
  { 165, 1 },
  { 243, 4 },
  { 124, 1 },
  { 206, 1 },
  { 200, 2 },
  { 200, 1 },
  { 244, 1 },
  { 244, 1 },
  { 244, 1 },
  { 115, 1 },
  { 101, 1 },
  { 101, 0 },
  { 99, 2 },
  { 99, 1 },
  { 245, 1 },
  { 245, 1 },
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
      case 0: /* start ::= expressions */
{  yy_destructor(yypParser,96,&yymsp[0].minor);
#line 58 "lemon.html.yy"
{
}
#line 1899 "lemon.html.c"
}
        break;
      case 1: /* expressions ::= expressions expression */
{  yy_destructor(yypParser,96,&yymsp[-1].minor);
#line 60 "lemon.html.yy"
{
}
#line 1907 "lemon.html.c"
  yy_destructor(yypParser,97,&yymsp[0].minor);
}
        break;
      case 2: /* expressions ::= expression */
{  yy_destructor(yypParser,97,&yymsp[0].minor);
#line 61 "lemon.html.yy"
{
}
#line 1916 "lemon.html.c"
}
        break;
      case 3: /* expression ::= tagdoctype spaces_enters taghtml opt__spaces_enters END_OF_FILE */
{  yy_destructor(yypParser,98,&yymsp[-4].minor);
#line 63 "lemon.html.yy"
{
}
#line 1924 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-3].minor);
  yy_destructor(yypParser,100,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,1,&yymsp[0].minor);
}
        break;
      case 4: /* expression ::= space */
      case 8: /* tagheadcontent ::= space */ yytestcase(yyruleno==8);
      case 19: /* tagbodycontent ::= space */ yytestcase(yyruleno==19);
      case 57: /* tagcontrolblockcontent ::= space */ yytestcase(yyruleno==57);
      case 72: /* tagdatablockcontent ::= space */ yytestcase(yyruleno==72);
      case 77: /* tagdatablockproperty ::= space */ yytestcase(yyruleno==77);
      case 108: /* taginputproperty ::= space */ yytestcase(yyruleno==108);
      case 138: /* tablecontentpart ::= space */ yytestcase(yyruleno==138);
      case 161: /* tagtablerow ::= space */ yytestcase(yyruleno==161);
      case 170: /* tagtablecol ::= space */ yytestcase(yyruleno==170);
      case 185: /* tagtablecolcontent ::= space */ yytestcase(yyruleno==185);
      case 247: /* taghtmlcontent ::= space */ yytestcase(yyruleno==247);
      case 277: /* htmlandspace ::= space */ yytestcase(yyruleno==277);
      case 284: /* spaces_enter ::= space */ yytestcase(yyruleno==284);
      case 287: /* spaces ::= space */ yytestcase(yyruleno==287);
{  yy_destructor(yypParser,102,&yymsp[0].minor);
#line 65 "lemon.html.yy"
{
}
#line 1950 "lemon.html.c"
}
        break;
      case 5: /* expression ::= enter */
      case 9: /* tagheadcontent ::= enter */ yytestcase(yyruleno==9);
      case 20: /* tagbodycontent ::= enter */ yytestcase(yyruleno==20);
      case 58: /* tagcontrolblockcontent ::= enter */ yytestcase(yyruleno==58);
      case 73: /* tagdatablockcontent ::= enter */ yytestcase(yyruleno==73);
      case 78: /* tagdatablockproperty ::= enter */ yytestcase(yyruleno==78);
      case 109: /* taginputproperty ::= enter */ yytestcase(yyruleno==109);
      case 139: /* tablecontentpart ::= enter */ yytestcase(yyruleno==139);
      case 162: /* tagtablerow ::= enter */ yytestcase(yyruleno==162);
      case 171: /* tagtablecol ::= enter */ yytestcase(yyruleno==171);
      case 186: /* tagtablecolcontent ::= enter */ yytestcase(yyruleno==186);
      case 248: /* taghtmlcontent ::= enter */ yytestcase(yyruleno==248);
      case 278: /* htmlandspace ::= enter */ yytestcase(yyruleno==278);
      case 285: /* spaces_enter ::= enter */ yytestcase(yyruleno==285);
{  yy_destructor(yypParser,103,&yymsp[0].minor);
#line 67 "lemon.html.yy"
{
}
#line 1971 "lemon.html.c"
}
        break;
      case 6: /* tagheadcontents ::= tagheadcontents tagheadcontent */
{  yy_destructor(yypParser,104,&yymsp[-1].minor);
#line 70 "lemon.html.yy"
{
}
#line 1979 "lemon.html.c"
  yy_destructor(yypParser,105,&yymsp[0].minor);
}
        break;
      case 7: /* tagheadcontents ::= tagheadcontent */
{  yy_destructor(yypParser,105,&yymsp[0].minor);
#line 71 "lemon.html.yy"
{
}
#line 1988 "lemon.html.c"
}
        break;
      case 10: /* tagheadcontent ::= tagtitle */
{  yy_destructor(yypParser,106,&yymsp[0].minor);
#line 75 "lemon.html.yy"
{
}
#line 1996 "lemon.html.c"
}
        break;
      case 11: /* tagheadcontent ::= tagscript */
{  yy_destructor(yypParser,107,&yymsp[0].minor);
#line 76 "lemon.html.yy"
{
}
#line 2004 "lemon.html.c"
}
        break;
      case 12: /* tagheadcontent ::= tagstyle */
{  yy_destructor(yypParser,108,&yymsp[0].minor);
#line 77 "lemon.html.yy"
{
}
#line 2012 "lemon.html.c"
}
        break;
      case 13: /* tagheadcontent ::= taglink */
{  yy_destructor(yypParser,109,&yymsp[0].minor);
#line 78 "lemon.html.yy"
{
}
#line 2020 "lemon.html.c"
}
        break;
      case 14: /* tagheadcontent ::= tagmeta */
{  yy_destructor(yypParser,110,&yymsp[0].minor);
#line 79 "lemon.html.yy"
{
}
#line 2028 "lemon.html.c"
}
        break;
      case 15: /* tagbodycontents ::= tagbodycontents tagbodycontent */
{  yy_destructor(yypParser,111,&yymsp[-1].minor);
#line 81 "lemon.html.yy"
{
}
#line 2036 "lemon.html.c"
  yy_destructor(yypParser,112,&yymsp[0].minor);
}
        break;
      case 16: /* tagbodycontents ::= tagbodycontent */
{  yy_destructor(yypParser,112,&yymsp[0].minor);
#line 82 "lemon.html.yy"
{
}
#line 2045 "lemon.html.c"
}
        break;
      case 17: /* tagbodycontent ::= htsqls */
{  yy_destructor(yypParser,113,&yymsp[0].minor);
#line 84 "lemon.html.yy"
{
}
#line 2053 "lemon.html.c"
}
        break;
      case 18: /* tagbodycontent ::= tagtable */
      case 71: /* tagdatablockcontent ::= tagtable */ yytestcase(yyruleno==71);
      case 184: /* tagtablecolcontent ::= tagtable */ yytestcase(yyruleno==184);
{  yy_destructor(yypParser,114,&yymsp[0].minor);
#line 85 "lemon.html.yy"
{
}
#line 2063 "lemon.html.c"
}
        break;
      case 21: /* tagbodycontent ::= htmltext */
      case 59: /* tagcontrolblockcontent ::= htmltext */ yytestcase(yyruleno==59);
      case 74: /* tagdatablockcontent ::= htmltext */ yytestcase(yyruleno==74);
      case 183: /* tagtablecolcontent ::= htmltext */ yytestcase(yyruleno==183);
      case 276: /* htmlandspace ::= htmltext */ yytestcase(yyruleno==276);
{  yy_destructor(yypParser,115,&yymsp[0].minor);
#line 88 "lemon.html.yy"
{
}
#line 2075 "lemon.html.c"
}
        break;
      case 22: /* htsqls ::= tagdatablock */
{  yy_destructor(yypParser,116,&yymsp[0].minor);
#line 90 "lemon.html.yy"
{
}
#line 2083 "lemon.html.c"
}
        break;
      case 23: /* htsqls ::= tagcontrolblock */
{  yy_destructor(yypParser,117,&yymsp[0].minor);
#line 91 "lemon.html.yy"
{
}
#line 2091 "lemon.html.c"
}
        break;
      case 24: /* htsqls ::= tagdatalist */
{  yy_destructor(yypParser,118,&yymsp[0].minor);
#line 92 "lemon.html.yy"
{
}
#line 2099 "lemon.html.c"
}
        break;
      case 25: /* tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD */
{  yy_destructor(yypParser,2,&yymsp[0].minor);
#line 94 "lemon.html.yy"
{
}
#line 2107 "lemon.html.c"
}
        break;
      case 26: /* tagdoctype ::= TAG_DOCTYPE_HTML */
{  yy_destructor(yypParser,3,&yymsp[0].minor);
#line 96 "lemon.html.yy"
{
}
#line 2115 "lemon.html.c"
}
        break;
      case 27: /* tagtree ::= tagtreefullopen tagtreeblockclosefull */
{  yy_destructor(yypParser,120,&yymsp[-1].minor);
#line 103 "lemon.html.yy"
{
}
#line 2123 "lemon.html.c"
  yy_destructor(yypParser,121,&yymsp[0].minor);
}
        break;
      case 28: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar */
{  yy_destructor(yypParser,122,&yymsp[-2].minor);
#line 104 "lemon.html.yy"
{
}
#line 2132 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 29: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces */
{  yy_destructor(yypParser,122,&yymsp[-3].minor);
#line 105 "lemon.html.yy"
{
}
#line 2142 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 30: /* tagtreeopen ::= TAG_TREE_OPEN */
{  yy_destructor(yypParser,4,&yymsp[0].minor);
#line 107 "lemon.html.yy"
{
}
#line 2153 "lemon.html.c"
}
        break;
      case 31: /* tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE */
{  yy_destructor(yypParser,5,&yymsp[0].minor);
#line 109 "lemon.html.yy"
{
}
#line 2161 "lemon.html.c"
}
        break;
      case 32: /* tagtreeproperties ::= tagtreeproperties tagtreeproperty */
{  yy_destructor(yypParser,123,&yymsp[-1].minor);
#line 111 "lemon.html.yy"
{
}
#line 2169 "lemon.html.c"
  yy_destructor(yypParser,126,&yymsp[0].minor);
}
        break;
      case 33: /* tagtreeproperties ::= tagtreeproperty */
{  yy_destructor(yypParser,126,&yymsp[0].minor);
#line 112 "lemon.html.yy"
{
}
#line 2178 "lemon.html.c"
}
        break;
      case 34: /* tagtreeproperty ::= tagtreepropertyid PROPERTYDATA */
{  yy_destructor(yypParser,127,&yymsp[-1].minor);
#line 114 "lemon.html.yy"
{
}
#line 2186 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 35: /* tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 116 "lemon.html.yy"
{
}
#line 2195 "lemon.html.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 36: /* tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull */
{  yy_destructor(yypParser,128,&yymsp[-1].minor);
#line 122 "lemon.html.yy"
{
}
#line 2205 "lemon.html.c"
  yy_destructor(yypParser,129,&yymsp[0].minor);
}
        break;
      case 37: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar */
{  yy_destructor(yypParser,130,&yymsp[-2].minor);
#line 123 "lemon.html.yy"
{
}
#line 2214 "lemon.html.c"
  yy_destructor(yypParser,131,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 38: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces */
{  yy_destructor(yypParser,130,&yymsp[-3].minor);
#line 124 "lemon.html.yy"
{
}
#line 2224 "lemon.html.c"
  yy_destructor(yypParser,131,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 39: /* tagdatalistopen ::= TAG_DATALIST_OPEN */
{  yy_destructor(yypParser,10,&yymsp[0].minor);
#line 126 "lemon.html.yy"
{
}
#line 2235 "lemon.html.c"
}
        break;
      case 40: /* tagdatalistblockclosefull ::= tagdatalistblockclose */
{  yy_destructor(yypParser,132,&yymsp[0].minor);
#line 128 "lemon.html.yy"
{
}
#line 2243 "lemon.html.c"
}
        break;
      case 41: /* tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE */
{  yy_destructor(yypParser,11,&yymsp[0].minor);
#line 130 "lemon.html.yy"
{
}
#line 2251 "lemon.html.c"
}
        break;
      case 42: /* datalistproperties ::= datalistproperties datalistproperty */
{  yy_destructor(yypParser,131,&yymsp[-1].minor);
#line 132 "lemon.html.yy"
{
}
#line 2259 "lemon.html.c"
  yy_destructor(yypParser,133,&yymsp[0].minor);
}
        break;
      case 43: /* datalistproperties ::= datalistproperty */
{  yy_destructor(yypParser,133,&yymsp[0].minor);
#line 133 "lemon.html.yy"
{
}
#line 2268 "lemon.html.c"
}
        break;
      case 44: /* datalistproperty ::= tagdatalistpropertyid PROPERTYDATA */
{  yy_destructor(yypParser,134,&yymsp[-1].minor);
#line 135 "lemon.html.yy"
{
}
#line 2276 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 45: /* tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 137 "lemon.html.yy"
{
}
#line 2285 "lemon.html.c"
  yy_destructor(yypParser,12,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 46: /* datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA */
{  yy_destructor(yypParser,135,&yymsp[-1].minor);
#line 139 "lemon.html.yy"
{
}
#line 2295 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 47: /* tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 141 "lemon.html.yy"
{
}
#line 2304 "lemon.html.c"
  yy_destructor(yypParser,13,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 48: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull */
{  yy_destructor(yypParser,136,&yymsp[-1].minor);
#line 148 "lemon.html.yy"
{
}
#line 2314 "lemon.html.c"
  yy_destructor(yypParser,137,&yymsp[0].minor);
}
        break;
      case 49: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull */
{  yy_destructor(yypParser,136,&yymsp[-2].minor);
#line 149 "lemon.html.yy"
{
}
#line 2323 "lemon.html.c"
  yy_destructor(yypParser,138,&yymsp[-1].minor);
  yy_destructor(yypParser,137,&yymsp[0].minor);
}
        break;
      case 50: /* tagcontrolblockfullopen ::= tagcontrolblockopen spaces_enters tagcontrolblockproperties tagclosechar */
{  yy_destructor(yypParser,139,&yymsp[-3].minor);
#line 151 "lemon.html.yy"
{
}
#line 2333 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-2].minor);
  yy_destructor(yypParser,140,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 51: /* tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN */
{  yy_destructor(yypParser,14,&yymsp[0].minor);
#line 153 "lemon.html.yy"
{
}
#line 2344 "lemon.html.c"
}
        break;
      case 52: /* tagcontrolblockclosefull ::= tagcontrolblockblockclose */
{  yy_destructor(yypParser,141,&yymsp[0].minor);
#line 155 "lemon.html.yy"
{
}
#line 2352 "lemon.html.c"
}
        break;
      case 53: /* tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 156 "lemon.html.yy"
{
}
#line 2360 "lemon.html.c"
}
        break;
      case 54: /* tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent */
{  yy_destructor(yypParser,138,&yymsp[-1].minor);
#line 158 "lemon.html.yy"
{
}
#line 2368 "lemon.html.c"
  yy_destructor(yypParser,142,&yymsp[0].minor);
}
        break;
      case 55: /* tagcontrolblockcontents ::= tagcontrolblockcontent */
{  yy_destructor(yypParser,142,&yymsp[0].minor);
#line 159 "lemon.html.yy"
{
}
#line 2377 "lemon.html.c"
}
        break;
      case 56: /* tagcontrolblockcontent ::= tagtree */
{  yy_destructor(yypParser,119,&yymsp[0].minor);
#line 161 "lemon.html.yy"
{
}
#line 2385 "lemon.html.c"
}
        break;
      case 60: /* tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty */
{  yy_destructor(yypParser,140,&yymsp[-1].minor);
#line 166 "lemon.html.yy"
{
}
#line 2393 "lemon.html.c"
  yy_destructor(yypParser,143,&yymsp[0].minor);
}
        break;
      case 61: /* tagcontrolblockproperties ::= tagcontrolblockproperty */
{  yy_destructor(yypParser,143,&yymsp[0].minor);
#line 167 "lemon.html.yy"
{
}
#line 2402 "lemon.html.c"
}
        break;
      case 62: /* tagcontrolblockproperty ::= PROP_CONTROLBLOCK_BLOCK_NAME opt__spaces_enters ASSIGMENT opt__spaces_enters PROPERTYDATA */
{  yy_destructor(yypParser,16,&yymsp[-4].minor);
#line 169 "lemon.html.yy"
{
}
#line 2410 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[-3].minor);
  yy_destructor(yypParser,9,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 63: /* tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull */
{  yy_destructor(yypParser,144,&yymsp[-1].minor);
#line 178 "lemon.html.yy"
{
}
#line 2422 "lemon.html.c"
  yy_destructor(yypParser,145,&yymsp[0].minor);
}
        break;
      case 64: /* tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull */
{  yy_destructor(yypParser,144,&yymsp[-2].minor);
#line 179 "lemon.html.yy"
{
}
#line 2431 "lemon.html.c"
  yy_destructor(yypParser,146,&yymsp[-1].minor);
  yy_destructor(yypParser,145,&yymsp[0].minor);
}
        break;
      case 65: /* tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar */
{  yy_destructor(yypParser,147,&yymsp[-2].minor);
#line 180 "lemon.html.yy"
{
}
#line 2441 "lemon.html.c"
  yy_destructor(yypParser,148,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 66: /* tagdatablockopen ::= TAG_DATABLOCK_OPEN */
{  yy_destructor(yypParser,17,&yymsp[0].minor);
#line 182 "lemon.html.yy"
{
}
#line 2451 "lemon.html.c"
}
        break;
      case 67: /* tagdatablockblockclosefull ::= tagdatablockblockclose */
{  yy_destructor(yypParser,149,&yymsp[0].minor);
#line 184 "lemon.html.yy"
{
}
#line 2459 "lemon.html.c"
}
        break;
      case 68: /* tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE */
{  yy_destructor(yypParser,18,&yymsp[0].minor);
#line 186 "lemon.html.yy"
{
}
#line 2467 "lemon.html.c"
}
        break;
      case 69: /* tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent */
{  yy_destructor(yypParser,146,&yymsp[-1].minor);
#line 189 "lemon.html.yy"
{
}
#line 2475 "lemon.html.c"
  yy_destructor(yypParser,150,&yymsp[0].minor);
}
        break;
      case 70: /* tagdatablockcontents ::= tagdatablockcontent */
{  yy_destructor(yypParser,150,&yymsp[0].minor);
#line 190 "lemon.html.yy"
{
}
#line 2484 "lemon.html.c"
}
        break;
      case 75: /* tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty */
{  yy_destructor(yypParser,148,&yymsp[-1].minor);
#line 197 "lemon.html.yy"
{
}
#line 2492 "lemon.html.c"
  yy_destructor(yypParser,151,&yymsp[0].minor);
}
        break;
      case 76: /* tagdatablockproperties ::= tagdatablockproperty */
{  yy_destructor(yypParser,151,&yymsp[0].minor);
#line 199 "lemon.html.yy"
{
}
#line 2501 "lemon.html.c"
}
        break;
      case 79: /* tagdatablockproperty ::= PROPERTYID ASSIGMENT PROPERTYDATA */
      case 128: /* taginputproperty ::= PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==128);
      case 268: /* tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==268);
{  yy_destructor(yypParser,19,&yymsp[-2].minor);
#line 204 "lemon.html.yy"
{
}
#line 2511 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 80: /* tagdatablockproperty ::= PROP_BLOCK_JOIN_CONDITION ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,20,&yymsp[-2].minor);
#line 206 "lemon.html.yy"
{
}
#line 2521 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 81: /* tagdatablockproperty ::= PROP_BLOCK_CONNECTION_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,21,&yymsp[-2].minor);
#line 208 "lemon.html.yy"
{
}
#line 2531 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 82: /* tagdatablockproperty ::= PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,22,&yymsp[-2].minor);
#line 210 "lemon.html.yy"
{
}
#line 2541 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 83: /* tagdatablockproperty ::= PROP_BLOCK_RECORD_COUNT ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,23,&yymsp[-2].minor);
#line 212 "lemon.html.yy"
{
}
#line 2551 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 84: /* tagdatablockproperty ::= PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,24,&yymsp[-2].minor);
#line 214 "lemon.html.yy"
{
}
#line 2561 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 85: /* tagdatablockproperty ::= PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,25,&yymsp[-2].minor);
#line 216 "lemon.html.yy"
{
}
#line 2571 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 86: /* tagdatablockproperty ::= PROP_BLOCK_BLOCK_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,26,&yymsp[-2].minor);
#line 218 "lemon.html.yy"
{
}
#line 2581 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 87: /* tagdatablockproperty ::= PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,27,&yymsp[-2].minor);
#line 220 "lemon.html.yy"
{
}
#line 2591 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 88: /* tagdatablockproperty ::= PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,28,&yymsp[-2].minor);
#line 222 "lemon.html.yy"
{
}
#line 2601 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 89: /* tagdatablockproperty ::= PROP_BLOCK_INSERT_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,29,&yymsp[-2].minor);
#line 224 "lemon.html.yy"
{
}
#line 2611 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 90: /* tagdatablockproperty ::= PROP_BLOCK_DELETE_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,30,&yymsp[-2].minor);
#line 226 "lemon.html.yy"
{
}
#line 2621 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 91: /* tagdatablockproperty ::= PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,31,&yymsp[-2].minor);
#line 228 "lemon.html.yy"
{
}
#line 2631 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 92: /* tagdatablockproperty ::= PROP_BLOCK_WHERE_CLAUSE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,32,&yymsp[-2].minor);
#line 230 "lemon.html.yy"
{
}
#line 2641 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 93: /* tagdatablockproperty ::= PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,33,&yymsp[-2].minor);
#line 232 "lemon.html.yy"
{
}
#line 2651 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 94: /* taginput ::= taginput_with_block */
{  yy_destructor(yypParser,153,&yymsp[0].minor);
#line 240 "lemon.html.yy"
{
}
#line 2661 "lemon.html.c"
}
        break;
      case 95: /* taginput ::= taginput_without_block */
{  yy_destructor(yypParser,154,&yymsp[0].minor);
#line 241 "lemon.html.yy"
{
}
#line 2669 "lemon.html.c"
}
        break;
      case 96: /* taginput_with_block ::= taginputopen taginputproperties tagclosechar opt__spaces_enters taginputblockclosefull */
{  yy_destructor(yypParser,155,&yymsp[-4].minor);
#line 243 "lemon.html.yy"
{
}
#line 2677 "lemon.html.c"
  yy_destructor(yypParser,156,&yymsp[-3].minor);
  yy_destructor(yypParser,124,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,157,&yymsp[0].minor);
}
        break;
      case 97: /* taginput_without_block ::= taginputopen taginputproperties taginputshortclose */
{  yy_destructor(yypParser,155,&yymsp[-2].minor);
#line 245 "lemon.html.yy"
{
}
#line 2689 "lemon.html.c"
  yy_destructor(yypParser,156,&yymsp[-1].minor);
  yy_destructor(yypParser,158,&yymsp[0].minor);
}
        break;
      case 98: /* taginputshortclose ::= TAG_SHORT_CLOSE */
      case 273: /* tagshortclose ::= TAG_SHORT_CLOSE */ yytestcase(yyruleno==273);
{  yy_destructor(yypParser,34,&yymsp[0].minor);
#line 248 "lemon.html.yy"
{
}
#line 2700 "lemon.html.c"
}
        break;
      case 99: /* taginputopen ::= TAG_INPUT_OPEN */
{  yy_destructor(yypParser,35,&yymsp[0].minor);
#line 251 "lemon.html.yy"
{
}
#line 2708 "lemon.html.c"
}
        break;
      case 100: /* taginputopen ::= TAG_SELECT_OPEN */
{  yy_destructor(yypParser,36,&yymsp[0].minor);
#line 253 "lemon.html.yy"
{
}
#line 2716 "lemon.html.c"
}
        break;
      case 101: /* taginputopen ::= TAG_TEXTAREA_OPEN */
{  yy_destructor(yypParser,37,&yymsp[0].minor);
#line 255 "lemon.html.yy"
{
}
#line 2724 "lemon.html.c"
}
        break;
      case 102: /* taginputblockclosefull ::= taginputblockclose */
{  yy_destructor(yypParser,159,&yymsp[0].minor);
#line 257 "lemon.html.yy"
{
}
#line 2732 "lemon.html.c"
}
        break;
      case 103: /* taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE */
{  yy_destructor(yypParser,38,&yymsp[0].minor);
#line 259 "lemon.html.yy"
{
}
#line 2740 "lemon.html.c"
}
        break;
      case 104: /* taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE */
{  yy_destructor(yypParser,39,&yymsp[0].minor);
#line 261 "lemon.html.yy"
{
}
#line 2748 "lemon.html.c"
}
        break;
      case 105: /* taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE */
{  yy_destructor(yypParser,40,&yymsp[0].minor);
#line 263 "lemon.html.yy"
{
}
#line 2756 "lemon.html.c"
}
        break;
      case 106: /* taginputproperties ::= taginputproperties taginputproperty */
{  yy_destructor(yypParser,156,&yymsp[-1].minor);
#line 266 "lemon.html.yy"
{
}
#line 2764 "lemon.html.c"
  yy_destructor(yypParser,160,&yymsp[0].minor);
}
        break;
      case 107: /* taginputproperties ::= taginputproperty */
{  yy_destructor(yypParser,160,&yymsp[0].minor);
#line 268 "lemon.html.yy"
{
}
#line 2773 "lemon.html.c"
}
        break;
      case 110: /* taginputproperty ::= PROP_INPUT_CHECKED_VALUE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,41,&yymsp[-2].minor);
#line 275 "lemon.html.yy"
{
}
#line 2781 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 111: /* taginputproperty ::= PROP_INPUT_UNCHECKED_VALUE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,42,&yymsp[-2].minor);
#line 277 "lemon.html.yy"
{
}
#line 2791 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 112: /* taginputproperty ::= PROP_INPUT_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,43,&yymsp[-2].minor);
#line 279 "lemon.html.yy"
{
}
#line 2801 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 113: /* taginputproperty ::= PROP_INPUT_SEQUENCE_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,44,&yymsp[-2].minor);
#line 281 "lemon.html.yy"
{
}
#line 2811 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 114: /* taginputproperty ::= PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,45,&yymsp[-2].minor);
#line 283 "lemon.html.yy"
{
}
#line 2821 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 115: /* taginputproperty ::= PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,46,&yymsp[-2].minor);
#line 285 "lemon.html.yy"
{
}
#line 2831 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 116: /* taginputproperty ::= PROP_INPUT_TYPE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,47,&yymsp[-2].minor);
#line 287 "lemon.html.yy"
{
}
#line 2841 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 117: /* taginputproperty ::= PROP_INPUT_VALUE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,48,&yymsp[-2].minor);
#line 289 "lemon.html.yy"
{
}
#line 2851 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 118: /* taginputproperty ::= PROP_INPUT_DEFAULT_VALUE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,49,&yymsp[-2].minor);
#line 291 "lemon.html.yy"
{
}
#line 2861 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 119: /* taginputproperty ::= PROP_INPUT_COLUMN_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,50,&yymsp[-2].minor);
#line 293 "lemon.html.yy"
{
}
#line 2871 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 120: /* taginputproperty ::= PROP_INPUT_FORMAT_MASK ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,51,&yymsp[-2].minor);
#line 295 "lemon.html.yy"
{
}
#line 2881 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 121: /* taginputproperty ::= PROP_INPUT_DATA_TYPE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,52,&yymsp[-2].minor);
#line 297 "lemon.html.yy"
{
}
#line 2891 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 122: /* taginputproperty ::= PROP_INPUT_MAX_LENGTH ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,53,&yymsp[-2].minor);
#line 299 "lemon.html.yy"
{
}
#line 2901 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 123: /* taginputproperty ::= PROP_INPUT_INSERT_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,54,&yymsp[-2].minor);
#line 301 "lemon.html.yy"
{
}
#line 2911 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 124: /* taginputproperty ::= PROP_INPUT_UPDATE_ALLOWED ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,55,&yymsp[-2].minor);
#line 303 "lemon.html.yy"
{
}
#line 2921 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 125: /* taginputproperty ::= PROP_INPUT_DATALIST_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,56,&yymsp[-2].minor);
#line 305 "lemon.html.yy"
{
}
#line 2931 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 126: /* taginputproperty ::= PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,57,&yymsp[-2].minor);
#line 307 "lemon.html.yy"
{
}
#line 2941 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 127: /* taginputproperty ::= PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,58,&yymsp[-2].minor);
#line 309 "lemon.html.yy"
{
}
#line 2951 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 129: /* tagtable ::= tagtablefullopen tagtableblockclosefull */
{  yy_destructor(yypParser,161,&yymsp[-1].minor);
#line 318 "lemon.html.yy"
{
}
#line 2961 "lemon.html.c"
  yy_destructor(yypParser,162,&yymsp[0].minor);
}
        break;
      case 130: /* tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull */
{  yy_destructor(yypParser,161,&yymsp[-2].minor);
#line 319 "lemon.html.yy"
{
}
#line 2970 "lemon.html.c"
  yy_destructor(yypParser,163,&yymsp[-1].minor);
  yy_destructor(yypParser,162,&yymsp[0].minor);
}
        break;
      case 131: /* tagtablefullopen ::= tagtableopen tagclosechar */
{  yy_destructor(yypParser,164,&yymsp[-1].minor);
#line 321 "lemon.html.yy"
{
}
#line 2980 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 132: /* tagtablefullopen ::= tagtableopen tagproperties tagclosechar */
{  yy_destructor(yypParser,164,&yymsp[-2].minor);
#line 322 "lemon.html.yy"
{
}
#line 2989 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 133: /* tagtableopen ::= TAG_TABLE_OPEN */
{  yy_destructor(yypParser,59,&yymsp[0].minor);
#line 324 "lemon.html.yy"
{
}
#line 2999 "lemon.html.c"
}
        break;
      case 134: /* tagtableblockclosefull ::= TAG_TABLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,60,&yymsp[0].minor);
#line 326 "lemon.html.yy"
{
}
#line 3007 "lemon.html.c"
}
        break;
      case 135: /* tablecontent ::= tablecontentparts */
{  yy_destructor(yypParser,166,&yymsp[0].minor);
#line 330 "lemon.html.yy"
{
}
#line 3015 "lemon.html.c"
}
        break;
      case 136: /* tablecontentparts ::= tablecontentparts tablecontentpart */
{  yy_destructor(yypParser,166,&yymsp[-1].minor);
#line 332 "lemon.html.yy"
{
}
#line 3023 "lemon.html.c"
  yy_destructor(yypParser,167,&yymsp[0].minor);
}
        break;
      case 137: /* tablecontentparts ::= tablecontentpart */
{  yy_destructor(yypParser,167,&yymsp[0].minor);
#line 333 "lemon.html.yy"
{
}
#line 3032 "lemon.html.c"
}
        break;
      case 140: /* tablecontentpart ::= tagthead */
{  yy_destructor(yypParser,168,&yymsp[0].minor);
#line 337 "lemon.html.yy"
{
}
#line 3040 "lemon.html.c"
}
        break;
      case 141: /* tablecontentpart ::= tagtbody */
{  yy_destructor(yypParser,169,&yymsp[0].minor);
#line 338 "lemon.html.yy"
{
}
#line 3048 "lemon.html.c"
}
        break;
      case 142: /* tablecontentpart ::= tagtfoot */
{  yy_destructor(yypParser,170,&yymsp[0].minor);
#line 339 "lemon.html.yy"
{
}
#line 3056 "lemon.html.c"
}
        break;
      case 143: /* tagthead ::= tagtheadfullopen tagtheadblockclosefull */
{  yy_destructor(yypParser,171,&yymsp[-1].minor);
#line 347 "lemon.html.yy"
{
}
#line 3064 "lemon.html.c"
  yy_destructor(yypParser,172,&yymsp[0].minor);
}
        break;
      case 144: /* tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull */
{  yy_destructor(yypParser,171,&yymsp[-2].minor);
#line 348 "lemon.html.yy"
{
}
#line 3073 "lemon.html.c"
  yy_destructor(yypParser,173,&yymsp[-1].minor);
  yy_destructor(yypParser,172,&yymsp[0].minor);
}
        break;
      case 145: /* tagtheadfullopen ::= tagtheadopen tagclosechar */
{  yy_destructor(yypParser,174,&yymsp[-1].minor);
#line 349 "lemon.html.yy"
{
}
#line 3083 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 146: /* tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,174,&yymsp[-2].minor);
#line 350 "lemon.html.yy"
{
}
#line 3092 "lemon.html.c"
  yy_destructor(yypParser,175,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 147: /* tagtheadopen ::= TAG_THEAD_OPEN */
{  yy_destructor(yypParser,61,&yymsp[0].minor);
#line 352 "lemon.html.yy"
{
}
#line 3102 "lemon.html.c"
}
        break;
      case 148: /* tagtheadblockclosefull ::= TAG_THEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,62,&yymsp[0].minor);
#line 354 "lemon.html.yy"
{
}
#line 3110 "lemon.html.c"
}
        break;
      case 149: /* tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull */
{  yy_destructor(yypParser,176,&yymsp[-2].minor);
#line 362 "lemon.html.yy"
{
}
#line 3118 "lemon.html.c"
  yy_destructor(yypParser,173,&yymsp[-1].minor);
  yy_destructor(yypParser,177,&yymsp[0].minor);
}
        break;
      case 150: /* tagtfootfullopen ::= tagtfootopen tagclosechar */
{  yy_destructor(yypParser,178,&yymsp[-1].minor);
#line 363 "lemon.html.yy"
{
}
#line 3128 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 151: /* tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar */
{  yy_destructor(yypParser,178,&yymsp[-2].minor);
#line 364 "lemon.html.yy"
{
}
#line 3137 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 152: /* tagtfootopen ::= TAG_TFOOT_OPEN */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 366 "lemon.html.yy"
{
}
#line 3147 "lemon.html.c"
}
        break;
      case 153: /* tagtfootblockclosefull ::= TAG_TFOOT_BLOCK_CLOSE */
{  yy_destructor(yypParser,64,&yymsp[0].minor);
#line 368 "lemon.html.yy"
{
}
#line 3155 "lemon.html.c"
}
        break;
      case 154: /* tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull */
{  yy_destructor(yypParser,179,&yymsp[-2].minor);
#line 376 "lemon.html.yy"
{
}
#line 3163 "lemon.html.c"
  yy_destructor(yypParser,173,&yymsp[-1].minor);
  yy_destructor(yypParser,180,&yymsp[0].minor);
}
        break;
      case 155: /* tagtbodyfullopen ::= tagtbodyopen tagclosechar */
{  yy_destructor(yypParser,181,&yymsp[-1].minor);
#line 377 "lemon.html.yy"
{
}
#line 3173 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 156: /* tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,181,&yymsp[-2].minor);
#line 378 "lemon.html.yy"
{
}
#line 3182 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 157: /* tagtbodyopen ::= TAG_TBODY_OPEN */
{  yy_destructor(yypParser,65,&yymsp[0].minor);
#line 380 "lemon.html.yy"
{
}
#line 3192 "lemon.html.c"
}
        break;
      case 158: /* tagtbodyblockclosefull ::= TAG_TBODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,66,&yymsp[0].minor);
#line 382 "lemon.html.yy"
{
}
#line 3200 "lemon.html.c"
}
        break;
      case 159: /* tagtablerows ::= tagtablerows tagtablerow */
{  yy_destructor(yypParser,173,&yymsp[-1].minor);
#line 390 "lemon.html.yy"
{
}
#line 3208 "lemon.html.c"
  yy_destructor(yypParser,182,&yymsp[0].minor);
}
        break;
      case 160: /* tagtablerows ::= tagtablerow */
{  yy_destructor(yypParser,182,&yymsp[0].minor);
#line 391 "lemon.html.yy"
{
}
#line 3217 "lemon.html.c"
}
        break;
      case 163: /* tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull */
{  yy_destructor(yypParser,183,&yymsp[-2].minor);
#line 396 "lemon.html.yy"
{
}
#line 3225 "lemon.html.c"
  yy_destructor(yypParser,184,&yymsp[-1].minor);
  yy_destructor(yypParser,185,&yymsp[0].minor);
}
        break;
      case 164: /* tagtablerowfullopen ::= tagtablerowopen tagclosechar */
{  yy_destructor(yypParser,186,&yymsp[-1].minor);
#line 397 "lemon.html.yy"
{
}
#line 3235 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 165: /* tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,186,&yymsp[-2].minor);
#line 398 "lemon.html.yy"
{
}
#line 3244 "lemon.html.c"
  yy_destructor(yypParser,175,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 166: /* tagtablerowopen ::= TAG_TR_OPEN */
{  yy_destructor(yypParser,67,&yymsp[0].minor);
#line 400 "lemon.html.yy"
{
}
#line 3254 "lemon.html.c"
}
        break;
      case 167: /* tagtablerowblockclosefull ::= TAG_TR_BLOCK_CLOSE */
{  yy_destructor(yypParser,68,&yymsp[0].minor);
#line 402 "lemon.html.yy"
{
}
#line 3262 "lemon.html.c"
}
        break;
      case 168: /* tagtablecols ::= tagtablecols tagtablecol */
{  yy_destructor(yypParser,184,&yymsp[-1].minor);
#line 406 "lemon.html.yy"
{
}
#line 3270 "lemon.html.c"
  yy_destructor(yypParser,187,&yymsp[0].minor);
}
        break;
      case 169: /* tagtablecols ::= tagtablecol */
{  yy_destructor(yypParser,187,&yymsp[0].minor);
#line 407 "lemon.html.yy"
{
}
#line 3279 "lemon.html.c"
}
        break;
      case 172: /* tagtablecol ::= tagtablecoltd */
{  yy_destructor(yypParser,188,&yymsp[0].minor);
#line 411 "lemon.html.yy"
{
}
#line 3287 "lemon.html.c"
}
        break;
      case 173: /* tagtablecol ::= tagtablecolth */
{  yy_destructor(yypParser,189,&yymsp[0].minor);
#line 412 "lemon.html.yy"
{
}
#line 3295 "lemon.html.c"
}
        break;
      case 174: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,190,&yymsp[-1].minor);
#line 418 "lemon.html.yy"
{
}
#line 3303 "lemon.html.c"
  yy_destructor(yypParser,191,&yymsp[0].minor);
}
        break;
      case 175: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,190,&yymsp[-2].minor);
#line 419 "lemon.html.yy"
{
}
#line 3312 "lemon.html.c"
  yy_destructor(yypParser,192,&yymsp[-1].minor);
  yy_destructor(yypParser,191,&yymsp[0].minor);
}
        break;
      case 176: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar */
{  yy_destructor(yypParser,193,&yymsp[-1].minor);
#line 420 "lemon.html.yy"
{
}
#line 3322 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 177: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar */
{  yy_destructor(yypParser,193,&yymsp[-2].minor);
#line 422 "lemon.html.yy"
{
}
#line 3331 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 178: /* tagtablecoltdopen ::= TAG_TD_OPEN */
{  yy_destructor(yypParser,69,&yymsp[0].minor);
#line 424 "lemon.html.yy"
{
}
#line 3341 "lemon.html.c"
}
        break;
      case 179: /* tagtablecoltdblockclosefull ::= TAG_TD_BLOCK_CLOSE */
{  yy_destructor(yypParser,70,&yymsp[0].minor);
#line 426 "lemon.html.yy"
{
}
#line 3349 "lemon.html.c"
}
        break;
      case 180: /* tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent */
{  yy_destructor(yypParser,192,&yymsp[-1].minor);
#line 430 "lemon.html.yy"
{
}
#line 3357 "lemon.html.c"
  yy_destructor(yypParser,194,&yymsp[0].minor);
}
        break;
      case 181: /* tagtablecolcontents ::= tagtablecolcontent */
{  yy_destructor(yypParser,194,&yymsp[0].minor);
#line 431 "lemon.html.yy"
{
}
#line 3366 "lemon.html.c"
}
        break;
      case 182: /* tagtablecolcontent ::= taginput */
{  yy_destructor(yypParser,152,&yymsp[0].minor);
#line 433 "lemon.html.yy"
{
}
#line 3374 "lemon.html.c"
}
        break;
      case 187: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull */
{  yy_destructor(yypParser,195,&yymsp[-1].minor);
#line 443 "lemon.html.yy"
{
}
#line 3382 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[0].minor);
}
        break;
      case 188: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull */
{  yy_destructor(yypParser,195,&yymsp[-2].minor);
#line 444 "lemon.html.yy"
{
}
#line 3391 "lemon.html.c"
  yy_destructor(yypParser,192,&yymsp[-1].minor);
  yy_destructor(yypParser,196,&yymsp[0].minor);
}
        break;
      case 189: /* tagtablecolthfullopen ::= tagtablecolthopen tagclosechar */
{  yy_destructor(yypParser,197,&yymsp[-1].minor);
#line 445 "lemon.html.yy"
{
}
#line 3401 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 190: /* tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,197,&yymsp[-2].minor);
#line 447 "lemon.html.yy"
{
}
#line 3410 "lemon.html.c"
  yy_destructor(yypParser,175,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 191: /* tagtablecolthopen ::= TAG_TH_OPEN */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 449 "lemon.html.yy"
{
}
#line 3420 "lemon.html.c"
}
        break;
      case 192: /* tagtablecolthblockclosefull ::= TAG_TH_BLOCK_CLOSE */
{  yy_destructor(yypParser,72,&yymsp[0].minor);
#line 451 "lemon.html.yy"
{
}
#line 3428 "lemon.html.c"
}
        break;
      case 193: /* tagtitle ::= tagtitlefullopen tagtitleblockclosefull */
{  yy_destructor(yypParser,198,&yymsp[-1].minor);
#line 459 "lemon.html.yy"
{
}
#line 3436 "lemon.html.c"
  yy_destructor(yypParser,199,&yymsp[0].minor);
}
        break;
      case 194: /* tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull */
{  yy_destructor(yypParser,198,&yymsp[-2].minor);
#line 460 "lemon.html.yy"
{
}
#line 3445 "lemon.html.c"
  yy_destructor(yypParser,200,&yymsp[-1].minor);
  yy_destructor(yypParser,199,&yymsp[0].minor);
}
        break;
      case 195: /* tagtitlefullopen ::= tagtitleopen tagclosechar */
{  yy_destructor(yypParser,201,&yymsp[-1].minor);
#line 461 "lemon.html.yy"
{
}
#line 3455 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 196: /* tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar */
{  yy_destructor(yypParser,201,&yymsp[-2].minor);
#line 462 "lemon.html.yy"
{
}
#line 3464 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 197: /* tagtitleblockclosefull ::= tagtitleblockclose */
{  yy_destructor(yypParser,202,&yymsp[0].minor);
#line 463 "lemon.html.yy"
{
}
#line 3474 "lemon.html.c"
}
        break;
      case 198: /* tagtitleopen ::= TAG_TITLE_OPEN */
{  yy_destructor(yypParser,73,&yymsp[0].minor);
#line 464 "lemon.html.yy"
{
}
#line 3482 "lemon.html.c"
}
        break;
      case 199: /* tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,74,&yymsp[0].minor);
#line 465 "lemon.html.yy"
{
}
#line 3490 "lemon.html.c"
}
        break;
      case 200: /* taglink ::= taglinkfullopen */
{  yy_destructor(yypParser,203,&yymsp[0].minor);
#line 471 "lemon.html.yy"
{
}
#line 3498 "lemon.html.c"
}
        break;
      case 201: /* taglink ::= taglinkfullopen taglinkblockclosefull */
{  yy_destructor(yypParser,203,&yymsp[-1].minor);
#line 472 "lemon.html.yy"
{
}
#line 3506 "lemon.html.c"
  yy_destructor(yypParser,204,&yymsp[0].minor);
}
        break;
      case 202: /* taglinkfullopen ::= taglinkopen tagproperties tagclosechar */
{  yy_destructor(yypParser,205,&yymsp[-2].minor);
#line 473 "lemon.html.yy"
{
}
#line 3515 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 203: /* taglinkfullopen ::= taglinkopen tagproperties tagshortclose */
{  yy_destructor(yypParser,205,&yymsp[-2].minor);
#line 474 "lemon.html.yy"
{
}
#line 3525 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,206,&yymsp[0].minor);
}
        break;
      case 204: /* taglinkblockclosefull ::= taglinkblockclose */
{  yy_destructor(yypParser,207,&yymsp[0].minor);
#line 476 "lemon.html.yy"
{
}
#line 3535 "lemon.html.c"
}
        break;
      case 205: /* taglinkopen ::= TAG_LINK_OPEN */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 478 "lemon.html.yy"
{
}
#line 3543 "lemon.html.c"
}
        break;
      case 206: /* taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE */
{  yy_destructor(yypParser,76,&yymsp[0].minor);
#line 479 "lemon.html.yy"
{
}
#line 3551 "lemon.html.c"
}
        break;
      case 207: /* tagmeta ::= tagmetafullopen */
{  yy_destructor(yypParser,208,&yymsp[0].minor);
#line 486 "lemon.html.yy"
{
}
#line 3559 "lemon.html.c"
}
        break;
      case 208: /* tagmeta ::= tagmetafullopen tagmetablockclosefull */
{  yy_destructor(yypParser,208,&yymsp[-1].minor);
#line 487 "lemon.html.yy"
{
}
#line 3567 "lemon.html.c"
  yy_destructor(yypParser,209,&yymsp[0].minor);
}
        break;
      case 209: /* tagmetafullopen ::= tagmetaopen tagproperties tagclosechar */
{  yy_destructor(yypParser,210,&yymsp[-2].minor);
#line 488 "lemon.html.yy"
{
}
#line 3576 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 210: /* tagmetafullopen ::= tagmetaopen tagproperties tagshortclose */
{  yy_destructor(yypParser,210,&yymsp[-2].minor);
#line 489 "lemon.html.yy"
{
}
#line 3586 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,206,&yymsp[0].minor);
}
        break;
      case 211: /* tagmetablockclosefull ::= tagmetablockclose */
{  yy_destructor(yypParser,211,&yymsp[0].minor);
#line 491 "lemon.html.yy"
{
}
#line 3596 "lemon.html.c"
}
        break;
      case 212: /* tagmetaopen ::= TAG_META_OPEN */
{  yy_destructor(yypParser,77,&yymsp[0].minor);
#line 493 "lemon.html.yy"
{
}
#line 3604 "lemon.html.c"
}
        break;
      case 213: /* tagmetablockclose ::= TAG_META_BLOCK_CLOSE */
{  yy_destructor(yypParser,78,&yymsp[0].minor);
#line 494 "lemon.html.yy"
{
}
#line 3612 "lemon.html.c"
}
        break;
      case 214: /* tagstyle ::= tagstylefullopen tagstyleblockclosefull */
{  yy_destructor(yypParser,212,&yymsp[-1].minor);
#line 501 "lemon.html.yy"
{
}
#line 3620 "lemon.html.c"
  yy_destructor(yypParser,213,&yymsp[0].minor);
}
        break;
      case 215: /* tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull */
{  yy_destructor(yypParser,212,&yymsp[-2].minor);
#line 502 "lemon.html.yy"
{
}
#line 3629 "lemon.html.c"
  yy_destructor(yypParser,200,&yymsp[-1].minor);
  yy_destructor(yypParser,213,&yymsp[0].minor);
}
        break;
      case 216: /* tagstylefullopen ::= tagstyleopen tagclosechar */
{  yy_destructor(yypParser,214,&yymsp[-1].minor);
#line 503 "lemon.html.yy"
{
}
#line 3639 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 217: /* tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar */
{  yy_destructor(yypParser,214,&yymsp[-2].minor);
#line 504 "lemon.html.yy"
{
}
#line 3648 "lemon.html.c"
  yy_destructor(yypParser,215,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 218: /* tagstyleblockclosefull ::= tagstyleblockclose */
{  yy_destructor(yypParser,216,&yymsp[0].minor);
#line 506 "lemon.html.yy"
{
}
#line 3658 "lemon.html.c"
}
        break;
      case 219: /* tagstyleopen ::= TAG_STYLE_OPEN */
{  yy_destructor(yypParser,79,&yymsp[0].minor);
#line 508 "lemon.html.yy"
{
}
#line 3666 "lemon.html.c"
}
        break;
      case 220: /* tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,80,&yymsp[0].minor);
#line 509 "lemon.html.yy"
{
}
#line 3674 "lemon.html.c"
}
        break;
      case 221: /* tagstyleproperties ::= tagstyleproperties tagstyleproperty */
{  yy_destructor(yypParser,215,&yymsp[-1].minor);
#line 512 "lemon.html.yy"
{
}
#line 3682 "lemon.html.c"
  yy_destructor(yypParser,217,&yymsp[0].minor);
}
        break;
      case 222: /* tagstyleproperties ::= tagstyleproperty */
{  yy_destructor(yypParser,217,&yymsp[0].minor);
#line 513 "lemon.html.yy"
{
}
#line 3691 "lemon.html.c"
}
        break;
      case 223: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 515 "lemon.html.yy"
{
}
#line 3699 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 224: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 516 "lemon.html.yy"
{
}
#line 3710 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 225: /* tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */
      case 271: /* tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==271);
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 517 "lemon.html.yy"
{
}
#line 3722 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 226: /* tagscript ::= tagscriptfullopen tagscriptblockclosefull */
{  yy_destructor(yypParser,218,&yymsp[-1].minor);
#line 524 "lemon.html.yy"
{
}
#line 3733 "lemon.html.c"
  yy_destructor(yypParser,219,&yymsp[0].minor);
}
        break;
      case 227: /* tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull */
{  yy_destructor(yypParser,218,&yymsp[-2].minor);
#line 525 "lemon.html.yy"
{
}
#line 3742 "lemon.html.c"
  yy_destructor(yypParser,200,&yymsp[-1].minor);
  yy_destructor(yypParser,219,&yymsp[0].minor);
}
        break;
      case 228: /* tagscriptfullopen ::= tagscriptopen tagclosechar */
{  yy_destructor(yypParser,220,&yymsp[-1].minor);
#line 526 "lemon.html.yy"
{
}
#line 3752 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 229: /* tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar */
{  yy_destructor(yypParser,220,&yymsp[-2].minor);
#line 527 "lemon.html.yy"
{
}
#line 3761 "lemon.html.c"
  yy_destructor(yypParser,221,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 230: /* tagscriptblockclosefull ::= tagscriptblockclose */
{  yy_destructor(yypParser,222,&yymsp[0].minor);
#line 529 "lemon.html.yy"
{
}
#line 3771 "lemon.html.c"
}
        break;
      case 231: /* tagscriptopen ::= TAG_SCRIPT_OPEN */
{  yy_destructor(yypParser,83,&yymsp[0].minor);
#line 531 "lemon.html.yy"
{
}
#line 3779 "lemon.html.c"
}
        break;
      case 232: /* tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE */
{  yy_destructor(yypParser,84,&yymsp[0].minor);
#line 532 "lemon.html.yy"
{
}
#line 3787 "lemon.html.c"
}
        break;
      case 233: /* tagscriptproperties ::= tagscriptproperties tagscriptproperty */
{  yy_destructor(yypParser,221,&yymsp[-1].minor);
#line 536 "lemon.html.yy"
{
}
#line 3795 "lemon.html.c"
  yy_destructor(yypParser,223,&yymsp[0].minor);
}
        break;
      case 234: /* tagscriptproperties ::= tagscriptproperty */
{  yy_destructor(yypParser,223,&yymsp[0].minor);
#line 537 "lemon.html.yy"
{
}
#line 3804 "lemon.html.c"
}
        break;
      case 235: /* tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA */
{  yy_destructor(yypParser,224,&yymsp[-1].minor);
#line 539 "lemon.html.yy"
{
}
#line 3812 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 236: /* tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 541 "lemon.html.yy"
{
}
#line 3821 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 237: /* tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA */
{  yy_destructor(yypParser,225,&yymsp[-1].minor);
#line 543 "lemon.html.yy"
{
}
#line 3831 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 238: /* tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 545 "lemon.html.yy"
{
}
#line 3840 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 239: /* taghtml ::= taghtmlfullopen taghtmlblockclosefull */
{  yy_destructor(yypParser,226,&yymsp[-1].minor);
#line 551 "lemon.html.yy"
{
}
#line 3850 "lemon.html.c"
  yy_destructor(yypParser,227,&yymsp[0].minor);
}
        break;
      case 240: /* taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull */
{  yy_destructor(yypParser,226,&yymsp[-2].minor);
#line 552 "lemon.html.yy"
{
}
#line 3859 "lemon.html.c"
  yy_destructor(yypParser,228,&yymsp[-1].minor);
  yy_destructor(yypParser,227,&yymsp[0].minor);
}
        break;
      case 241: /* taghtmlfullopen ::= taghtmlopen tagclosechar */
{  yy_destructor(yypParser,229,&yymsp[-1].minor);
#line 553 "lemon.html.yy"
{
}
#line 3869 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 242: /* taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar */
{  yy_destructor(yypParser,229,&yymsp[-2].minor);
#line 554 "lemon.html.yy"
{
}
#line 3878 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 243: /* taghtmlblockclosefull ::= TAG_HTML_BLOCK_CLOSE */
{  yy_destructor(yypParser,85,&yymsp[0].minor);
#line 556 "lemon.html.yy"
{
}
#line 3888 "lemon.html.c"
}
        break;
      case 244: /* taghtmlopen ::= TAG_HTML_OPEN */
{  yy_destructor(yypParser,86,&yymsp[0].minor);
#line 558 "lemon.html.yy"
{
}
#line 3896 "lemon.html.c"
}
        break;
      case 245: /* taghtmlcontents ::= taghtmlcontents taghtmlcontent */
{  yy_destructor(yypParser,228,&yymsp[-1].minor);
#line 560 "lemon.html.yy"
{
}
#line 3904 "lemon.html.c"
  yy_destructor(yypParser,230,&yymsp[0].minor);
}
        break;
      case 246: /* taghtmlcontents ::= taghtmlcontent */
{  yy_destructor(yypParser,230,&yymsp[0].minor);
#line 561 "lemon.html.yy"
{
}
#line 3913 "lemon.html.c"
}
        break;
      case 249: /* taghtmlcontent ::= tagbody */
{  yy_destructor(yypParser,231,&yymsp[0].minor);
#line 565 "lemon.html.yy"
{
}
#line 3921 "lemon.html.c"
}
        break;
      case 250: /* taghtmlcontent ::= taghead tagbody */
{  yy_destructor(yypParser,232,&yymsp[-1].minor);
#line 566 "lemon.html.yy"
{
}
#line 3929 "lemon.html.c"
  yy_destructor(yypParser,231,&yymsp[0].minor);
}
        break;
      case 251: /* taghtmlcontent ::= taghead spaces_enters tagbody */
{  yy_destructor(yypParser,232,&yymsp[-2].minor);
#line 567 "lemon.html.yy"
{
}
#line 3938 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-1].minor);
  yy_destructor(yypParser,231,&yymsp[0].minor);
}
        break;
      case 252: /* tagbody ::= tagbodyfullopen tagbodyblockclosefull */
{  yy_destructor(yypParser,233,&yymsp[-1].minor);
#line 574 "lemon.html.yy"
{
}
#line 3948 "lemon.html.c"
  yy_destructor(yypParser,234,&yymsp[0].minor);
}
        break;
      case 253: /* tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull */
{  yy_destructor(yypParser,233,&yymsp[-2].minor);
#line 575 "lemon.html.yy"
{
}
#line 3957 "lemon.html.c"
  yy_destructor(yypParser,111,&yymsp[-1].minor);
  yy_destructor(yypParser,234,&yymsp[0].minor);
}
        break;
      case 254: /* tagbodyfullopen ::= tagbodyopen tagclosechar */
{  yy_destructor(yypParser,235,&yymsp[-1].minor);
#line 577 "lemon.html.yy"
{
}
#line 3967 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 255: /* tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,235,&yymsp[-2].minor);
#line 579 "lemon.html.yy"
{
}
#line 3976 "lemon.html.c"
  yy_destructor(yypParser,165,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 256: /* tagbodyblockclosefull ::= tagbodyblockclose */
{  yy_destructor(yypParser,236,&yymsp[0].minor);
#line 581 "lemon.html.yy"
{
}
#line 3986 "lemon.html.c"
}
        break;
      case 257: /* tagbodyopen ::= TAG_BODY_OPEN */
{  yy_destructor(yypParser,87,&yymsp[0].minor);
#line 583 "lemon.html.yy"
{
}
#line 3994 "lemon.html.c"
}
        break;
      case 258: /* tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,88,&yymsp[0].minor);
#line 585 "lemon.html.yy"
{
}
#line 4002 "lemon.html.c"
}
        break;
      case 259: /* taghead ::= tagheadfullopen tagheadblockclosefull */
{  yy_destructor(yypParser,237,&yymsp[-1].minor);
#line 593 "lemon.html.yy"
{
}
#line 4010 "lemon.html.c"
  yy_destructor(yypParser,238,&yymsp[0].minor);
}
        break;
      case 260: /* taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull */
{  yy_destructor(yypParser,237,&yymsp[-2].minor);
#line 594 "lemon.html.yy"
{
}
#line 4019 "lemon.html.c"
  yy_destructor(yypParser,104,&yymsp[-1].minor);
  yy_destructor(yypParser,238,&yymsp[0].minor);
}
        break;
      case 261: /* tagheadfullopen ::= tagheadopen */
{  yy_destructor(yypParser,239,&yymsp[0].minor);
#line 596 "lemon.html.yy"
{
}
#line 4029 "lemon.html.c"
}
        break;
      case 262: /* tagheadblockclosefull ::= tagheadblockclose */
{  yy_destructor(yypParser,240,&yymsp[0].minor);
#line 598 "lemon.html.yy"
{
}
#line 4037 "lemon.html.c"
}
        break;
      case 263: /* tagheadopen ::= TAG_HEAD_OPEN */
{  yy_destructor(yypParser,89,&yymsp[0].minor);
#line 600 "lemon.html.yy"
{
}
#line 4045 "lemon.html.c"
}
        break;
      case 264: /* tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,90,&yymsp[0].minor);
#line 602 "lemon.html.yy"
{
}
#line 4053 "lemon.html.c"
}
        break;
      case 265: /* tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues */
{  yy_destructor(yypParser,241,&yymsp[0].minor);
#line 610 "lemon.html.yy"
{
}
#line 4061 "lemon.html.c"
}
        break;
      case 266: /* tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue */
{  yy_destructor(yypParser,241,&yymsp[-1].minor);
#line 612 "lemon.html.yy"
{
}
#line 4069 "lemon.html.c"
  yy_destructor(yypParser,242,&yymsp[0].minor);
}
        break;
      case 267: /* tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue */
{  yy_destructor(yypParser,242,&yymsp[0].minor);
#line 614 "lemon.html.yy"
{
}
#line 4078 "lemon.html.c"
}
        break;
      case 269: /* tagproperties ::= tagproperties tagproperty */
{  yy_destructor(yypParser,165,&yymsp[-1].minor);
#line 623 "lemon.html.yy"
{
}
#line 4086 "lemon.html.c"
  yy_destructor(yypParser,243,&yymsp[0].minor);
}
        break;
      case 270: /* tagproperties ::= tagproperty */
{  yy_destructor(yypParser,243,&yymsp[0].minor);
#line 624 "lemon.html.yy"
{
}
#line 4095 "lemon.html.c"
}
        break;
      case 272: /* tagclosechar ::= TAG_CLOSE */
{  yy_destructor(yypParser,91,&yymsp[0].minor);
#line 630 "lemon.html.yy"
{
}
#line 4103 "lemon.html.c"
}
        break;
      case 274: /* htmlandspaces ::= htmlandspaces htmlandspace */
{  yy_destructor(yypParser,200,&yymsp[-1].minor);
#line 639 "lemon.html.yy"
{
}
#line 4111 "lemon.html.c"
  yy_destructor(yypParser,244,&yymsp[0].minor);
}
        break;
      case 275: /* htmlandspaces ::= htmlandspace */
{  yy_destructor(yypParser,244,&yymsp[0].minor);
#line 640 "lemon.html.yy"
{
}
#line 4120 "lemon.html.c"
}
        break;
      case 279: /* htmltext ::= HTMLTEXT */
{  yy_destructor(yypParser,92,&yymsp[0].minor);
#line 646 "lemon.html.yy"
{
}
#line 4128 "lemon.html.c"
}
        break;
      case 280: /* opt__spaces_enters ::= spaces_enters */
{  yy_destructor(yypParser,99,&yymsp[0].minor);
#line 653 "lemon.html.yy"
{
}
#line 4136 "lemon.html.c"
}
        break;
      case 282: /* spaces_enters ::= spaces_enters spaces_enter */
{  yy_destructor(yypParser,99,&yymsp[-1].minor);
#line 656 "lemon.html.yy"
{
}
#line 4144 "lemon.html.c"
  yy_destructor(yypParser,245,&yymsp[0].minor);
}
        break;
      case 283: /* spaces_enters ::= spaces_enter */
{  yy_destructor(yypParser,245,&yymsp[0].minor);
#line 657 "lemon.html.yy"
{
}
#line 4153 "lemon.html.c"
}
        break;
      case 286: /* spaces ::= spaces space */
{  yy_destructor(yypParser,125,&yymsp[-1].minor);
#line 663 "lemon.html.yy"
{
}
#line 4161 "lemon.html.c"
  yy_destructor(yypParser,102,&yymsp[0].minor);
}
        break;
      case 288: /* space ::= SPACE */
{  yy_destructor(yypParser,7,&yymsp[0].minor);
#line 668 "lemon.html.yy"
{
}
#line 4170 "lemon.html.c"
}
        break;
      case 289: /* enter ::= ENTER */
{  yy_destructor(yypParser,93,&yymsp[0].minor);
#line 670 "lemon.html.yy"
{
}
#line 4178 "lemon.html.c"
}
        break;
      default:
      /* (281) opt__spaces_enters ::= */ yytestcase(yyruleno==281);
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
#line 4243 "lemon.html.c"
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
