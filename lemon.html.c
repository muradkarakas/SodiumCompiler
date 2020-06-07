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

#include <stdint.h>
#include "html.parser.imp.h"

#include <assert.h>

#line 48 "lemon.html.c"
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
#define YYCODETYPE unsigned short int
#define YYNOCODE 283
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
#define YYNSTATE             234
#define YYNRULE              335
#define YY_MAX_SHIFT         233
#define YY_MIN_SHIFTREDUCE   522
#define YY_MAX_SHIFTREDUCE   856
#define YY_MIN_REDUCE        857
#define YY_MAX_REDUCE        1191
#define YY_ERROR_ACTION      1192
#define YY_ACCEPT_ACTION     1193
#define YY_NO_ACTION         1194
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
#define YY_ACTTAB_COUNT (901)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   107,    4,    4,    4,    4,    4,    4,    4,    4,    4,
 /*    10 */   702,   25,  102,   86,   25,   25,  855,  720,   23,  855,
 /*    20 */   701,   44,  629,  107,  107,  726,  528,  528,  203,  528,
 /*    30 */   528,  528,  528,  528,  528, 1193,   37,   37,   57,  133,
 /*    40 */   849,  849,  523,  524,  686,  698,  726,  107,  135,  716,
 /*    50 */   221,  220,  219,  218,  217,  216,  215,  214,  213,  212,
 /*    60 */   211,  210,  209,  208,  207,  206,  205,  204,  132,  630,
 /*    70 */   783,  639,  222,  201,  200,  199,  198,  197,  196,  195,
 /*    80 */   194,  193,  192,  191,  190,  189,  188,  187,  186,  185,
 /*    90 */   587,  741,    1,  756,  108,    1,  222,  201,  200,  199,
 /*   100 */   198,  197,  196,  195,  194,  193,  192,  191,  190,  189,
 /*   110 */   188,  187,  186,  185,  636,  637,  638,  596,  162,  161,
 /*   120 */   160,  159,  158,  157,  156,  155,  154,  153,  152,  151,
 /*   130 */   150,  149,  690,   42,   79,   78,   49,  855,   84,   59,
 /*   140 */    76,   52,   59,   83,   52,   75,   58,   39,   51,   48,
 /*   150 */   138,  855,  839,   38,  134,   30,  760,   63,   42,  760,
 /*   160 */   628,   49,  590,   84,  628,   76,  120,  120,   83,  855,
 /*   170 */    75,  111,   39,  826,   48,  826,    6,    6,   38,  817,
 /*   180 */    30,    5,  855,   50,  707,    6,    6,    6,    6,    6,
 /*   190 */     6,    6,    6,   25,  111,   17,   17,   65,  827,   65,
 /*   200 */   827,   63,  106,  684,   60,  818,  226,    5,  853,   50,
 /*   210 */    16,  849,  849,   55,  537,  537,  716,  824,   19,  849,
 /*   220 */    93,    8,  754,  856,  537,  537,  537,  537,  537,  537,
 /*   230 */   537,   74,  744,  224,   74,   74,  846,  707,  839,  716,
 /*   240 */   106,  722,   60,  101,  730,  730,  730,    9,   16,   82,
 /*   250 */    53,   55,   82,   11,  855,   45,   19,  561,  775,    8,
 /*   260 */   775,  573,  112,  845,  588,  796,   21,    7,  856,   54,
 /*   270 */     7,  162,  161,  160,  159,  158,  157,  156,  155,  154,
 /*   280 */   153,  152,  151,  150,  149,  112,  178,  176,  175,  174,
 /*   290 */   173,  172,  171,  170,  169,  168,  167,  166,  165,  164,
 /*   300 */   163,  109,  227,  110,   21,  183,  684,   54,  178,  176,
 /*   310 */   175,  174,  173,  172,  171,  170,  169,  168,  167,  166,
 /*   320 */   165,  164,  163,  780,   10,   13,   95,  776,  686,  853,
 /*   330 */   766,  736,  576,  576,   97,  825,   14,   95,  773,  846,
 /*   340 */   856,   98,   95,  855,  819,  576,  819,   10,  844,  576,
 /*   350 */   130,   74,   80,  225,   74,   74,  806,   17,  840,   17,
 /*   360 */    17,   24,    5,  563,   50,  184,    3,  571,    3,  845,
 /*   370 */    85,  571,  576,  120,  120,  120,  120,   96,   81,  679,
 /*   380 */     2,  113,  820,  679,  820,  840,  745,   95,   96,   81,
 /*   390 */   849,    2,  631,   96,   81,  725,    2,  812,  812,  845,
 /*   400 */   800,  142,  139,   21,  113,   20,   54,  745,   95,   20,
 /*   410 */    20,   20,    9,   74,   21,   53,  855,   54,   11,   21,
 /*   420 */    45,  810,   54,  824,  855,  830,  745,   95,   56,  856,
 /*   430 */    56,  232,  229,   35,  632,  633,  634,   13,   96,   81,
 /*   440 */    13,    2,  752,  795,   94,  777,  799,  734,   14,  839,
 /*   450 */    97,   14,  735,   15,  844,   97,   15,  144,  684,   96,
 /*   460 */    81,  183,    2,   36,   21,  849,  849,   54,  853,  678,
 /*   470 */   103,  759,  787,  678,   28,   77,  833,   27,   96,   81,
 /*   480 */    43,    2,  836,  808,  844,   21,  688,   58,   54,   51,
 /*   490 */    74,  846,  233,   74,   74,  811,   18,   18,   58,   22,
 /*   500 */    51,  745,  856,  753,   21,   94,  755,   54,  180,   18,
 /*   510 */   856,   22,   22,   18,  130,  855,   80,  183,  737,  148,
 /*   520 */   146,   97,  745,  855,  553,  632,  633,  634,  804,  547,
 /*   530 */   548,  570,   18,   74,  855,  570,   18,  738,  183,  769,
 /*   540 */    97,  745,  585,   22,  114,  552,  585,   22,  855,  684,
 /*   550 */   572,  632,  633,  634,  768,   64,  575,  768,  807,  591,
 /*   560 */   744,  812,  812,   24,    5,  549,   50,  114,    3,  582,
 /*   570 */     3,  591,  591,  231,  230,  684,   47,  183,   47,  142,
 /*   580 */   139,  765,  846,  772,  805,  779,  744,  786,  115,   21,
 /*   590 */   183,  798,   54,  711,  105,   90,  720,   23,  831,  762,
 /*   600 */    44,  856,  586,  564,  232,  229,  586,  591,  846,  692,
 /*   610 */    31,  115,  809,   87,  860,  223,  547,  548,  719,  726,
 /*   620 */   856,  855,   31,   23,   61,   12,   44,  180,   46,  803,
 /*   630 */   526,   57,   40,  846,  856,  523,  524,  693,   64,  183,
 /*   640 */    62,   87,  183,  793,  849,  183,  793,  802,  183,   21,
 /*   650 */   720,   23,   54,  781,   44,  183,  781,  770,  183,   29,
 /*   660 */   840,  821,   29,   29,   89,  849,  849,   92,   61,   32,
 /*   670 */   739,   66,   74,  184,   33,   26,  184,  100,   26,   26,
 /*   680 */   794,   32,   23,  794,   62,   44,   33,   23,  782,  135,
 /*   690 */    44,  782,  729,  741,  836,  756,  183,  136,  761,  839,
 /*   700 */   183,  761,  183,  841,  183,  842,  183,  856,  183,  137,
 /*   710 */   104,  784,  554,  228,  687,   40,  223,  710,  763,  842,
 /*   720 */   726,   59,  822,   52,   88,   35,   91,  116,  740,  223,
 /*   730 */    99,  140,  141,   67,   73,  117,   68,   73,  228,   69,
 /*   740 */   118,  840,   70,  842,  231,  230,  119,  121,  122,   72,
 /*   750 */   116,  123,   41,  124,   66,  792,   71,  839,  117,  125,
 /*   760 */   839,  126,  127,  118,  128,  129,  131,  836,  143,  119,
 /*   770 */   121,  122,  558,  791,  123,  558,  124,  145,  790,   71,
 /*   780 */   147,  839,  125,  625,  126,  127,  623,  128,  129,  131,
 /*   790 */   621,  619,  617,  839,  615,  613,  611,  609,  607,  605,
 /*   800 */   839,  603,  601,  599,  859,  522,  182,  626,  624,  622,
 /*   810 */   620,  618,  616,  839,  859,  227,   67,  614,  612,   68,
 /*   820 */   610,  608,   69,  840,  859,   70,  606,  604,  602,  600,
 /*   830 */   598,  177,   72,  835,  859,   41,  838,  179,  181,  675,
 /*   840 */   788,   29,  673,  671,  849,  669,  667,  665,  663,  661,
 /*   850 */   659,  657,  655,  653,  651,  649,  647,   26,  645,  643,
 /*   860 */   677,  859,  859,  859,  202,  676,  674,  672,  670,  668,
 /*   870 */   666,  859,  859,  836,  664,  662,  660,  836,  658,  836,
 /*   880 */   656,  836,  641,  836,  654,  836,  652,  650,  648,  646,
 /*   890 */   644,  642,  584,   34,  557,  556,  568,  569,  566,  859,
 /*   900 */   567,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   102,  102,  103,  104,  105,  106,  107,  108,  109,  110,
 /*    10 */   208,   99,  210,  124,  102,  103,    7,  215,  216,    7,
 /*    20 */    62,  219,  124,  125,  102,   67,  102,  103,   19,  105,
 /*    30 */   106,  107,  108,  109,  110,   95,   96,   97,   98,    7,
 /*    40 */   102,  103,  102,  103,   60,   61,   67,  125,  102,   65,
 /*    50 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    60 */    51,   52,   53,   54,   55,   56,   57,   58,    7,  171,
 /*    70 */   124,  173,  174,  175,  176,  177,  178,  179,  180,  181,
 /*    80 */   182,  183,  184,  185,  186,  187,  188,  189,  190,  191,
 /*    90 */   124,   69,  170,   71,  205,  173,  174,  175,  176,  177,
 /*   100 */   178,  179,  180,  181,  182,  183,  184,  185,  186,  187,
 /*   110 */   188,  189,  190,  191,   38,   39,   40,  151,  152,  153,
 /*   120 */   154,  155,  156,  157,  158,  159,  160,  161,  162,  163,
 /*   130 */   164,  165,  200,  234,  199,  200,  237,    7,  239,  207,
 /*   140 */   241,  209,  207,  244,  209,  246,  211,  248,  213,  250,
 /*   150 */     7,    7,   91,  254,    7,  256,  235,  236,  234,  238,
 /*   160 */   168,  237,   18,  239,  172,  241,  277,  278,  244,    7,
 /*   170 */   246,  102,  248,  274,  250,  276,  102,  103,  254,  267,
 /*   180 */   256,  269,    7,  271,   63,  111,  112,  113,  114,  115,
 /*   190 */   116,  117,  118,  281,  125,  102,  103,  251,  274,  253,
 /*   200 */   276,  280,  128,   59,  130,  267,    7,  269,  102,  271,
 /*   210 */   136,  102,  103,  139,  102,  103,   65,   87,  144,  281,
 /*   220 */   124,  147,  124,   93,  112,  113,  114,  115,  116,  117,
 /*   230 */   118,   99,   70,  101,  102,  103,   92,   63,   91,   65,
 /*   240 */   128,  218,  130,  220,  221,  222,  223,  224,  136,  140,
 /*   250 */   227,  139,  143,  230,    7,  232,  144,   10,  245,  147,
 /*   260 */   247,   14,  102,    7,   17,  124,  192,  148,   93,  195,
 /*   270 */   151,  152,  153,  154,  155,  156,  157,  158,  159,  160,
 /*   280 */   161,  162,  163,  164,  165,  125,   19,   20,   21,   22,
 /*   290 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   300 */    33,  205,    8,  205,  192,  102,   59,  195,   19,   20,
 /*   310 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   320 */    31,   32,   33,   78,  102,  114,  115,  124,   60,  102,
 /*   330 */    74,  225,  102,  103,  228,   88,  114,  115,   76,   92,
 /*   340 */    93,  114,  115,    7,  270,  115,  272,  125,   92,  119,
 /*   350 */   120,   99,  122,  101,  102,  103,  263,  264,   91,  266,
 /*   360 */   267,  268,  269,   11,  271,    7,  273,  137,  275,    7,
 /*   370 */   124,  141,  142,  277,  278,  277,  278,  166,  167,  193,
 /*   380 */   169,  102,  270,  197,  272,   91,  114,  115,  166,  167,
 /*   390 */   281,  169,   34,  166,  167,  124,  169,  102,  103,    7,
 /*   400 */   259,  260,  261,  192,  125,  217,  195,  114,  115,  221,
 /*   410 */   222,  223,  224,  281,  192,  227,    7,  195,  230,  192,
 /*   420 */   232,   85,  195,   87,    7,   89,  114,  115,  131,   93,
 /*   430 */   133,  134,  135,   16,   35,   36,   37,  226,  166,  167,
 /*   440 */   229,  169,  231,  124,  233,  242,   84,  225,  226,   91,
 /*   450 */   228,  229,  225,  226,   92,  228,  229,   19,   59,  166,
 /*   460 */   167,  102,  169,  100,  192,  102,  103,  195,  102,  193,
 /*   470 */   194,   72,   80,  197,  198,  199,  278,  201,  166,  167,
 /*   480 */   204,  169,  279,  124,   92,  192,  199,  211,  195,  213,
 /*   490 */    99,   92,  101,  102,  103,   86,  102,  103,  211,  102,
 /*   500 */   213,  229,   93,  231,  192,  233,  124,  195,   19,  115,
 /*   510 */    93,  114,  115,  119,  120,    7,  122,  102,  225,   81,
 /*   520 */    82,  228,  229,    7,    5,   35,   36,   37,    6,    2,
 /*   530 */     3,  137,  138,  281,    7,  141,  142,  225,  102,  124,
 /*   540 */   228,  229,  145,  146,  102,    4,  149,  150,    7,   59,
 /*   550 */   124,   35,   36,   37,  240,  196,   15,  243,  263,  102,
 /*   560 */    70,  266,  267,  268,  269,  121,  271,  125,  273,  143,
 /*   570 */   275,  114,  115,   12,   13,   59,  257,  102,  259,  260,
 /*   580 */   261,   73,   92,   75,    9,   77,   70,   79,  102,  192,
 /*   590 */   102,   83,  195,  212,  124,  214,  215,  216,   90,  124,
 /*   600 */   219,   93,  145,  133,  134,  135,  149,  150,   92,  202,
 /*   610 */   203,  125,  124,  206,    0,    7,    2,    3,   66,   67,
 /*   620 */    93,    7,  215,  216,  236,  262,  219,   19,  265,    9,
 /*   630 */    97,   98,  196,   92,   93,  102,  103,  202,  279,  102,
 /*   640 */   236,  206,  102,  255,  281,  102,  258,    6,  102,  192,
 /*   650 */   215,  216,  195,  249,  219,  102,  252,  242,  102,   99,
 /*   660 */    91,  124,  102,  103,  124,  102,  103,  124,  280,  203,
 /*   670 */   124,  196,  281,    7,  203,   99,    7,  124,  102,  103,
 /*   680 */   255,  215,  216,  258,  280,  219,  215,  216,  249,  102,
 /*   690 */   219,  252,   68,   69,  279,   71,  102,    7,  235,   91,
 /*   700 */   102,  238,  102,   34,  102,  280,  102,   93,  102,    7,
 /*   710 */   124,  124,  126,  127,  200,  279,    7,   64,  124,  280,
 /*   720 */    67,  207,  124,  209,  124,   16,  124,  102,  124,    7,
 /*   730 */   124,   81,   82,  196,  123,  102,  196,  126,  127,  196,
 /*   740 */   102,   91,  196,  280,   12,   13,  102,  102,  102,  196,
 /*   750 */   125,  102,  196,  102,  279,    6,  102,   91,  125,  102,
 /*   760 */    91,  102,  102,  125,  102,  102,  102,  279,    9,  125,
 /*   770 */   125,  125,  129,    6,  125,  132,  125,    9,    6,  125,
 /*   780 */     9,   91,  125,    6,  125,  125,    6,  125,  125,  125,
 /*   790 */     6,    6,    6,   91,    6,    6,    6,    6,    6,    6,
 /*   800 */    91,    6,    6,    6,  282,    1,   19,    9,    9,    9,
 /*   810 */     9,    9,    9,   91,  282,    8,  279,    9,    9,  279,
 /*   820 */     9,    9,  279,   91,  282,  279,    9,    9,    9,    9,
 /*   830 */     6,    9,  279,    6,  282,  279,    6,    9,    9,    6,
 /*   840 */   253,  281,    6,    6,  281,    6,    6,    6,    6,    6,
 /*   850 */     6,    6,    6,    6,    6,    6,    6,  281,    6,    6,
 /*   860 */     6,  282,  282,  282,    9,    9,    9,    9,    9,    9,
 /*   870 */     9,  282,  282,  279,    9,    9,    9,  279,    9,  279,
 /*   880 */     9,  279,    6,  279,    9,  279,    9,    9,    9,    9,
 /*   890 */     9,    9,    6,    9,    9,    6,    6,    9,    6,  282,
 /*   900 */     9,
};
#define YY_SHIFT_USE_DFLT (901)
#define YY_SHIFT_COUNT    (233)
#define YY_SHIFT_MIN      (-42)
#define YY_SHIFT_MAX      (892)
static const short yy_shift_ofst[] = {
 /*     0 */   527,  358,   12,  508,  508,  247,  247,   61,   32,  516,
 /*    10 */   516,  399,  336,  399,  490,  490,  541,  336,  541,  144,
 /*    20 */   624,  -16,  144,   22,  130,  130,  409,  -42,  174,  417,
 /*    30 */   147,  -42,  552,  653,  175,  175,  175,  614,  362,  392,
 /*    40 */   669,  669,  256,  608,  608,  608,  666,  147,  666,  666,
 /*    50 */   666,  666,  666,  666,  666,  175,  690,  175,  -21,  -21,
 /*    60 */   143,  362,  392,  256,  666,  666,  666,  666,  666,  666,
 /*    70 */   666,  162,  666,  702,  175,   12,   12,  121,  151,  121,
 /*    80 */   199,   76,  709,  245,  262,   12,   12,   12,   12,   12,
 /*    90 */    12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
 /*   100 */    12,   12,   12,  268,   12,   12,  352,    9,  722,  722,
 /*   110 */   722,   12,   12,   12,   12,   12,   12,   12,   12,   12,
 /*   120 */   489,   12,   12,   12,   12,   12,   12,   12,   12,   12,
 /*   130 */   519,   12,  267,  289,  650,  438,  732,  294,  561,  522,
 /*   140 */   575,  620,  641,  749,  759,  767,  768,  772,  771,  777,
 /*   150 */   780,  784,  785,  786,  788,  789,  790,  791,  792,  793,
 /*   160 */   795,  796,  797,  798,  799,  800,  801,  802,  803,  808,
 /*   170 */   809,  811,  812,  817,  818,  819,  820,  824,  822,  827,
 /*   180 */   828,  830,  829,  787,  569,  833,  836,  837,  839,  840,
 /*   190 */   841,  842,  843,  844,  845,  846,  847,  848,  849,  850,
 /*   200 */   852,  853,  854,  855,  856,  857,  858,  859,  860,  861,
 /*   210 */   865,  866,  867,  869,  871,  875,  877,  878,  879,  880,
 /*   220 */   881,  882,  876,  569,  886,  884,  807,  885,  889,  890,
 /*   230 */   888,  891,  892,  804,
};
#define YY_REDUCE_USE_DFLT (-199)
#define YY_REDUCE_COUNT (131)
#define YY_REDUCE_MIN   (-198)
#define YY_REDUCE_MAX   (664)
static const short yy_reduce_ofst[] = {
 /*     0 */   -60, -102,  -78, -101,  -76,   74,  112,  -34,  119,  222,
 /*    10 */   227,  211,   93,  272,  293,  312,  394,  295,  230,  397,
 /*    20 */    23,  276,  457,  188,  -88,  -62,  363,  407,  -65,  109,
 /*    30 */   319,  435,  381, -198,  132,  252,  391,  533,  388,  404,
 /*    40 */   203,  415,  -79, -111,   96,   98,  359,  141,  -54,  475,
 /*    50 */   537,  540,  543,  546,  553,  560,  470,  576,  466,  471,
 /*    60 */   297,  425,  439,  463,  488,  587,  594,  598,  600,  602,
 /*    70 */   604,  106,  606,  586,  563,  436,  556,  -68,  287,  514,
 /*    80 */   611,   -8,  426,   13,  314,   69,  160,  279,  442,  486,
 /*    90 */   625,  633,  638,  644,  645,  646,  649,  651,  654,  657,
 /*   100 */   659,  660,  662,  186,  663,  664,  643,  366,  246,  271,
 /*   110 */   382,  366,  366,  366,  366,  366,  366,  366,  366,  366,
 /*   120 */   198,  366,  366,  366,  366,  366,  366,  366,  366,  366,
 /*   130 */   444,  366,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*    10 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*    20 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*    30 */  1192, 1192, 1192, 1192, 1183, 1183, 1183, 1192, 1192, 1192,
 /*    40 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*    50 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*    60 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*    70 */  1192, 1192, 1192, 1192, 1182, 1192, 1192, 1026, 1192, 1024,
 /*    80 */  1192,  962, 1192, 1109, 1102, 1031, 1029, 1034, 1049, 1047,
 /*    90 */  1052, 1040, 1038, 1058, 1092, 1084, 1082, 1077, 1086, 1017,
 /*   100 */  1015, 1062, 1043, 1192,  885,  894, 1192, 1192, 1192, 1192,
 /*   110 */  1192, 1032, 1030, 1035, 1050, 1048, 1053, 1041, 1039, 1059,
 /*   120 */  1167, 1093, 1085, 1083, 1078, 1018, 1016, 1063, 1044,  886,
 /*   130 */  1192,  895, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*   140 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*   150 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*   160 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*   170 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*   180 */  1192, 1192, 1192, 1192, 1190, 1192, 1192, 1192, 1192, 1192,
 /*   190 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*   200 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*   210 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*   220 */  1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192, 1192,
 /*   230 */  1192, 1192, 1192, 1192,
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
  "tagdatablockpropertyjoincondition",  "tagdatablockpropertyconnectionname",  "tagdatablockpropertyautogeneratedcolumns",  "tagdatablockpropertyrecordcount",
  "tagdatablockpropertysourcename",  "tagdatablockpropertyschemaname",  "tagdatablockpropertyblockname",  "tagdatablockpropertykeycolumnname",
  "tagdatablockpropertymasterblockname",  "tagdatablockpropertyinsertallowed",  "tagdatablockpropertydeleteallowed",  "tagdatablockpropertyupdateallowed",
  "tagdatablockpropertywhereclause",  "tagdatablockpropertyorderbyclause",  "taginput",      "taginputfullopen",
  "taginputblockclosefull",  "taginputopen",  "taginputproperties",  "taginputshortclose",
  "taginputblockclose",  "taginputproperty",  "taginputcheckedvalue",  "taginputuncheckedvalue",
  "taginputpropertyinputname",  "taginputpropertysequencename",  "taginputpropertysequenceschemaname",  "taginputpropertymasteritemname",
  "taginputpropertyinputtype",  "taginputpropertyinputvalue",  "taginputpropertydefaultvalue",  "taginputpropertycolumnname",
  "taginputpropertyformatmask",  "taginputpropertydatatype",  "taginputpropertymaxlength",  "taginputpropertyinsertallowed",
  "taginputpropertyupdateallowed",  "taginputpropertydatalistname",  "taginputpropertylookupitemname",  "taginputpropertylookupitemblockname",
  "tagtablefullopen",  "tagtableblockclosefull",  "tablecontent",  "tagtableopen",
  "tagproperties",  "tagtableblockclose",  "tagthead",      "tagtbody",    
  "tagtfoot",      "tagtheadfullopen",  "tagtheadblockclosefull",  "tagtablerows",
  "tagtheadopen",  "tagpropertieswithreturnvaluesall",  "tagtheadblockclose",  "tagtfootfullopen",
  "tagtfootblockclosefull",  "tagtfootopen",  "tagtfootblockclose",  "tagtbodyfullopen",
  "tagtbodyblockclosefull",  "tagtbodyopen",  "tagtbodyblockclose",  "tagtablerow", 
  "tagtablerowfullopen",  "tagtablecols",  "tagtablerowblockclosefull",  "tagtablerowopen",
  "tagtablerowblockclose",  "tagtablecol",   "tagtablecoltd",  "tagtablecolth",
  "tagtablecoltdfullopen",  "tagtablecoltdblockclosefull",  "tagtablecolcontents",  "tagtablecoltdopen",
  "tagtablecoltdblockclose",  "tagtablecolcontent",  "tagtablecolthfullopen",  "tagtablecolthblockclosefull",
  "tagtablecolthopen",  "tagtablecolthblockclose",  "tagtitlefullopen",  "tagtitleblockclosefull",
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
 /*   0 */ "expression ::= tagdoctype spaces_enters taghtml opt__spaces_enters END_OF_FILE",
 /*   1 */ "expression ::= space",
 /*   2 */ "expression ::= enter",
 /*   3 */ "start ::= expressions",
 /*   4 */ "expressions ::= expressions expression",
 /*   5 */ "expressions ::= expression",
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
 /*  73 */ "tagdatablockcontent ::= htmltext",
 /*  74 */ "tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty",
 /*  75 */ "tagdatablockproperties ::= tagdatablockproperty",
 /*  76 */ "tagdatablockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA",
 /*  77 */ "tagdatablockproperty ::= tagdatablockpropertyjoincondition PROPERTYDATA",
 /*  78 */ "tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION ASSIGMENT",
 /*  79 */ "tagdatablockproperty ::= tagdatablockpropertyconnectionname PROPERTYDATA",
 /*  80 */ "tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME ASSIGMENT",
 /*  81 */ "tagdatablockproperty ::= tagdatablockpropertyautogeneratedcolumns PROPERTYDATA",
 /*  82 */ "tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT",
 /*  83 */ "tagdatablockproperty ::= tagdatablockpropertyrecordcount PROPERTYDATA",
 /*  84 */ "tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT",
 /*  85 */ "tagdatablockproperty ::= tagdatablockpropertysourcename PROPERTYDATA",
 /*  86 */ "tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT",
 /*  87 */ "tagdatablockproperty ::= tagdatablockpropertyschemaname PROPERTYDATA",
 /*  88 */ "tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT",
 /*  89 */ "tagdatablockproperty ::= tagdatablockpropertyblockname PROPERTYDATA",
 /*  90 */ "tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT",
 /*  91 */ "tagdatablockproperty ::= tagdatablockpropertykeycolumnname PROPERTYDATA",
 /*  92 */ "tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT",
 /*  93 */ "tagdatablockproperty ::= tagdatablockpropertymasterblockname PROPERTYDATA",
 /*  94 */ "tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT",
 /*  95 */ "tagdatablockproperty ::= tagdatablockpropertyinsertallowed PROPERTYDATA",
 /*  96 */ "tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT",
 /*  97 */ "tagdatablockproperty ::= tagdatablockpropertydeleteallowed PROPERTYDATA",
 /*  98 */ "tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT",
 /*  99 */ "tagdatablockproperty ::= tagdatablockpropertyupdateallowed PROPERTYDATA",
 /* 100 */ "tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT",
 /* 101 */ "tagdatablockproperty ::= tagdatablockpropertywhereclause PROPERTYDATA",
 /* 102 */ "tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE ASSIGMENT",
 /* 103 */ "tagdatablockproperty ::= tagdatablockpropertyorderbyclause PROPERTYDATA",
 /* 104 */ "tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT",
 /* 105 */ "taginput ::= taginputfullopen",
 /* 106 */ "taginput ::= taginputfullopen taginputblockclosefull",
 /* 107 */ "taginputfullopen ::= taginputopen taginputproperties tagclosechar",
 /* 108 */ "taginputfullopen ::= taginputopen taginputproperties taginputshortclose",
 /* 109 */ "taginputshortclose ::= TAG_SHORT_CLOSE",
 /* 110 */ "taginputopen ::= TAG_INPUT_OPEN",
 /* 111 */ "taginputopen ::= TAG_SELECT_OPEN",
 /* 112 */ "taginputopen ::= TAG_TEXTAREA_OPEN",
 /* 113 */ "taginputblockclosefull ::= taginputblockclose",
 /* 114 */ "taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE",
 /* 115 */ "taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE",
 /* 116 */ "taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE",
 /* 117 */ "taginputproperties ::= taginputproperties taginputproperty",
 /* 118 */ "taginputproperties ::= taginputproperty",
 /* 119 */ "taginputproperty ::= taginputcheckedvalue PROPERTYDATA",
 /* 120 */ "taginputcheckedvalue ::= spaces PROP_INPUT_CHECKED_VALUE ASSIGMENT",
 /* 121 */ "taginputproperty ::= taginputuncheckedvalue PROPERTYDATA",
 /* 122 */ "taginputuncheckedvalue ::= spaces PROP_INPUT_UNCHECKED_VALUE ASSIGMENT",
 /* 123 */ "taginputproperty ::= taginputpropertyinputname PROPERTYDATA",
 /* 124 */ "taginputpropertyinputname ::= spaces PROP_INPUT_NAME ASSIGMENT",
 /* 125 */ "taginputproperty ::= taginputpropertysequencename PROPERTYDATA",
 /* 126 */ "taginputpropertysequencename ::= spaces PROP_INPUT_SEQUENCE_NAME ASSIGMENT",
 /* 127 */ "taginputproperty ::= taginputpropertysequenceschemaname PROPERTYDATA",
 /* 128 */ "taginputpropertysequenceschemaname ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT",
 /* 129 */ "taginputproperty ::= taginputpropertymasteritemname PROPERTYDATA",
 /* 130 */ "taginputpropertymasteritemname ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT",
 /* 131 */ "taginputproperty ::= taginputpropertyinputtype PROPERTYDATA",
 /* 132 */ "taginputpropertyinputtype ::= spaces PROP_INPUT_TYPE ASSIGMENT",
 /* 133 */ "taginputproperty ::= taginputpropertyinputvalue PROPERTYDATA",
 /* 134 */ "taginputpropertyinputvalue ::= spaces PROP_INPUT_VALUE ASSIGMENT",
 /* 135 */ "taginputproperty ::= taginputpropertydefaultvalue PROPERTYDATA",
 /* 136 */ "taginputpropertydefaultvalue ::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT",
 /* 137 */ "taginputproperty ::= taginputpropertycolumnname PROPERTYDATA",
 /* 138 */ "taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT",
 /* 139 */ "taginputproperty ::= taginputpropertyformatmask PROPERTYDATA",
 /* 140 */ "taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT",
 /* 141 */ "taginputproperty ::= taginputpropertydatatype PROPERTYDATA",
 /* 142 */ "taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT",
 /* 143 */ "taginputproperty ::= taginputpropertymaxlength PROPERTYDATA",
 /* 144 */ "taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT",
 /* 145 */ "taginputproperty ::= taginputpropertyinsertallowed PROPERTYDATA",
 /* 146 */ "taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED ASSIGMENT",
 /* 147 */ "taginputproperty ::= taginputpropertyupdateallowed PROPERTYDATA",
 /* 148 */ "taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT",
 /* 149 */ "taginputproperty ::= taginputpropertydatalistname PROPERTYDATA",
 /* 150 */ "taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT",
 /* 151 */ "taginputproperty ::= taginputpropertylookupitemname PROPERTYDATA",
 /* 152 */ "taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT",
 /* 153 */ "taginputproperty ::= taginputpropertylookupitemblockname PROPERTYDATA",
 /* 154 */ "taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT",
 /* 155 */ "taginputproperty ::= spaces PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 156 */ "tagtable ::= tagtablefullopen tagtableblockclosefull",
 /* 157 */ "tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull",
 /* 158 */ "tagtablefullopen ::= tagtableopen tagclosechar",
 /* 159 */ "tagtablefullopen ::= tagtableopen tagclosechar spaces",
 /* 160 */ "tagtablefullopen ::= tagtableopen tagproperties tagclosechar",
 /* 161 */ "tagtablefullopen ::= tagtableopen tagproperties tagclosechar spaces",
 /* 162 */ "tagtableopen ::= TAG_TABLE_OPEN",
 /* 163 */ "tagtableblockclosefull ::= tagtableblockclose",
 /* 164 */ "tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE",
 /* 165 */ "tablecontent ::= tagthead tagtbody tagtfoot",
 /* 166 */ "tablecontent ::= tagthead tagtfoot tagtbody",
 /* 167 */ "tablecontent ::= tagthead tagtbody",
 /* 168 */ "tablecontent ::= tagtbody tagtfoot",
 /* 169 */ "tablecontent ::= tagtbody",
 /* 170 */ "tagthead ::= tagtheadfullopen tagtheadblockclosefull",
 /* 171 */ "tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull",
 /* 172 */ "tagtheadfullopen ::= tagtheadopen tagclosechar",
 /* 173 */ "tagtheadfullopen ::= tagtheadopen tagclosechar spaces",
 /* 174 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 175 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces",
 /* 176 */ "tagtheadopen ::= TAG_THEAD_OPEN",
 /* 177 */ "tagtheadblockclosefull ::= tagtheadblockclose",
 /* 178 */ "tagtheadblockclosefull ::= tagtheadblockclose spaces",
 /* 179 */ "tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE",
 /* 180 */ "tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull",
 /* 181 */ "tagtfootfullopen ::= tagtfootopen tagclosechar",
 /* 182 */ "tagtfootfullopen ::= tagtfootopen tagclosechar spaces",
 /* 183 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar",
 /* 184 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar spaces",
 /* 185 */ "tagtfootopen ::= TAG_TFOOT_OPEN",
 /* 186 */ "tagtfootblockclosefull ::= tagtfootblockclose",
 /* 187 */ "tagtfootblockclosefull ::= tagtfootblockclose spaces",
 /* 188 */ "tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE",
 /* 189 */ "tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull",
 /* 190 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar",
 /* 191 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar spaces",
 /* 192 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar",
 /* 193 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar spaces",
 /* 194 */ "tagtbodyopen ::= TAG_TBODY_OPEN",
 /* 195 */ "tagtbodyblockclosefull ::= tagtbodyblockclose",
 /* 196 */ "tagtbodyblockclosefull ::= tagtbodyblockclose spaces",
 /* 197 */ "tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE",
 /* 198 */ "tagtablerows ::= tagtablerows tagtablerow",
 /* 199 */ "tagtablerows ::= tagtablerow",
 /* 200 */ "tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull",
 /* 201 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar",
 /* 202 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces",
 /* 203 */ "tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 204 */ "tagtablerowopen ::= TAG_TR_OPEN",
 /* 205 */ "tagtablerowblockclosefull ::= tagtablerowblockclose",
 /* 206 */ "tagtablerowblockclosefull ::= tagtablerowblockclose spaces",
 /* 207 */ "tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE",
 /* 208 */ "tagtablecols ::= tagtablecols tagtablecol",
 /* 209 */ "tagtablecols ::= tagtablecol",
 /* 210 */ "tagtablecol ::= tagtablecoltd",
 /* 211 */ "tagtablecol ::= tagtablecolth",
 /* 212 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull",
 /* 213 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull",
 /* 214 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull",
 /* 215 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull",
 /* 216 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull",
 /* 217 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar",
 /* 218 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar",
 /* 219 */ "tagtablecoltdopen ::= TAG_TD_OPEN",
 /* 220 */ "tagtablecoltdblockclosefull ::= tagtablecoltdblockclose",
 /* 221 */ "tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces",
 /* 222 */ "tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE",
 /* 223 */ "tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent",
 /* 224 */ "tagtablecolcontents ::= tagtablecolcontent",
 /* 225 */ "tagtablecolcontent ::= taginput",
 /* 226 */ "tagtablecolcontent ::= taginput spaces",
 /* 227 */ "tagtablecolcontent ::= htmltext",
 /* 228 */ "tagtablecolcontent ::= htmltext spaces",
 /* 229 */ "tagtablecolcontent ::= tagtable",
 /* 230 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull",
 /* 231 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull",
 /* 232 */ "tagtablecolthfullopen ::= tagtablecolthopen tagclosechar",
 /* 233 */ "tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 234 */ "tagtablecolthopen ::= TAG_TH_OPEN",
 /* 235 */ "tagtablecolthblockclosefull ::= tagtablecolthblockclose",
 /* 236 */ "tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces",
 /* 237 */ "tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE",
 /* 238 */ "tagtitle ::= tagtitlefullopen tagtitleblockclosefull",
 /* 239 */ "tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull",
 /* 240 */ "tagtitlefullopen ::= tagtitleopen tagclosechar",
 /* 241 */ "tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar",
 /* 242 */ "tagtitleblockclosefull ::= tagtitleblockclose",
 /* 243 */ "tagtitleopen ::= TAG_TITLE_OPEN",
 /* 244 */ "tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE",
 /* 245 */ "taglink ::= taglinkfullopen",
 /* 246 */ "taglink ::= taglinkfullopen taglinkblockclosefull",
 /* 247 */ "taglinkfullopen ::= taglinkopen tagproperties tagclosechar",
 /* 248 */ "taglinkfullopen ::= taglinkopen tagproperties tagshortclose",
 /* 249 */ "taglinkblockclosefull ::= taglinkblockclose",
 /* 250 */ "taglinkopen ::= TAG_LINK_OPEN",
 /* 251 */ "taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE",
 /* 252 */ "tagmeta ::= tagmetafullopen",
 /* 253 */ "tagmeta ::= tagmetafullopen tagmetablockclosefull",
 /* 254 */ "tagmetafullopen ::= tagmetaopen tagproperties tagclosechar",
 /* 255 */ "tagmetafullopen ::= tagmetaopen tagproperties tagshortclose",
 /* 256 */ "tagmetablockclosefull ::= tagmetablockclose",
 /* 257 */ "tagmetaopen ::= TAG_META_OPEN",
 /* 258 */ "tagmetablockclose ::= TAG_META_BLOCK_CLOSE",
 /* 259 */ "tagstyle ::= tagstylefullopen tagstyleblockclosefull",
 /* 260 */ "tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull",
 /* 261 */ "tagstylefullopen ::= tagstyleopen tagclosechar",
 /* 262 */ "tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar",
 /* 263 */ "tagstyleblockclosefull ::= tagstyleblockclose",
 /* 264 */ "tagstyleopen ::= TAG_STYLE_OPEN",
 /* 265 */ "tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE",
 /* 266 */ "tagstyleproperties ::= tagstyleproperties tagstyleproperty",
 /* 267 */ "tagstyleproperties ::= tagstyleproperty",
 /* 268 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA",
 /* 269 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA",
 /* 270 */ "tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 271 */ "tagscript ::= tagscriptfullopen tagscriptblockclosefull",
 /* 272 */ "tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull",
 /* 273 */ "tagscriptfullopen ::= tagscriptopen tagclosechar",
 /* 274 */ "tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar",
 /* 275 */ "tagscriptblockclosefull ::= tagscriptblockclose",
 /* 276 */ "tagscriptopen ::= TAG_SCRIPT_OPEN",
 /* 277 */ "tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE",
 /* 278 */ "tagscriptproperties ::= tagscriptproperties tagscriptproperty",
 /* 279 */ "tagscriptproperties ::= tagscriptproperty",
 /* 280 */ "tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA",
 /* 281 */ "tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT",
 /* 282 */ "tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA",
 /* 283 */ "tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT",
 /* 284 */ "taghtml ::= taghtmlfullopen taghtmlblockclosefull",
 /* 285 */ "taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull",
 /* 286 */ "taghtmlfullopen ::= taghtmlopen tagclosechar",
 /* 287 */ "taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar",
 /* 288 */ "taghtmlblockclosefull ::= TAG_HTML_BLOCK_CLOSE",
 /* 289 */ "taghtmlopen ::= TAG_HTML_OPEN",
 /* 290 */ "taghtmlcontents ::= taghtmlcontents taghtmlcontent",
 /* 291 */ "taghtmlcontents ::= taghtmlcontent",
 /* 292 */ "taghtmlcontent ::= space",
 /* 293 */ "taghtmlcontent ::= enter",
 /* 294 */ "taghtmlcontent ::= tagbody",
 /* 295 */ "taghtmlcontent ::= taghead tagbody",
 /* 296 */ "taghtmlcontent ::= taghead spaces_enters tagbody",
 /* 297 */ "tagbody ::= tagbodyfullopen tagbodyblockclosefull",
 /* 298 */ "tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull",
 /* 299 */ "tagbodyfullopen ::= tagbodyopen tagclosechar",
 /* 300 */ "tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar",
 /* 301 */ "tagbodyblockclosefull ::= tagbodyblockclose",
 /* 302 */ "tagbodyopen ::= TAG_BODY_OPEN",
 /* 303 */ "tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE",
 /* 304 */ "taghead ::= tagheadfullopen tagheadblockclosefull",
 /* 305 */ "taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull",
 /* 306 */ "tagheadfullopen ::= tagheadopen",
 /* 307 */ "tagheadblockclosefull ::= tagheadblockclose",
 /* 308 */ "tagheadopen ::= TAG_HEAD_OPEN",
 /* 309 */ "tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE",
 /* 310 */ "tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues",
 /* 311 */ "tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue",
 /* 312 */ "tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue",
 /* 313 */ "tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 314 */ "tagproperties ::= tagproperties tagproperty",
 /* 315 */ "tagproperties ::= tagproperty",
 /* 316 */ "tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 317 */ "tagclosechar ::= TAG_CLOSE",
 /* 318 */ "tagclosechar ::= SPACE TAG_CLOSE",
 /* 319 */ "tagshortclose ::= TAG_SHORT_CLOSE",
 /* 320 */ "htmlandspaces ::= htmlandspaces htmlandspace",
 /* 321 */ "htmlandspaces ::= htmlandspace",
 /* 322 */ "htmlandspace ::= HTMLTEXT",
 /* 323 */ "htmlandspace ::= SPACE",
 /* 324 */ "htmltext ::= HTMLTEXT",
 /* 325 */ "opt__spaces_enters ::= spaces_enters",
 /* 326 */ "opt__spaces_enters ::=",
 /* 327 */ "spaces_enters ::= spaces_enters spaces_enter",
 /* 328 */ "spaces_enters ::= spaces_enter",
 /* 329 */ "spaces_enter ::= space",
 /* 330 */ "spaces_enter ::= enter",
 /* 331 */ "spaces ::= spaces space",
 /* 332 */ "spaces ::= space",
 /* 333 */ "space ::= SPACE",
 /* 334 */ "enter ::= ENTER",
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
#line 34 "lemon.html.yy"

    Token *token = (yypminor->yy0);
    if (token) {
        if (token->tokenStr != NULL) {
            if (token->tokenStr[0] == '\n') {
                printf("\n%4d: ", session->lineNumberOuter);
            } else {
                printf("%.*s", token->tokenStrLength, token->tokenStr);
            }
        }
        // TODO: make a linked list then free it
        //mkFree(session->heapHandle, token);
    }

#line 1201 "lemon.html.c"
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
    case 152: /* tagdatablockpropertyjoincondition */
    case 153: /* tagdatablockpropertyconnectionname */
    case 154: /* tagdatablockpropertyautogeneratedcolumns */
    case 155: /* tagdatablockpropertyrecordcount */
    case 156: /* tagdatablockpropertysourcename */
    case 157: /* tagdatablockpropertyschemaname */
    case 158: /* tagdatablockpropertyblockname */
    case 159: /* tagdatablockpropertykeycolumnname */
    case 160: /* tagdatablockpropertymasterblockname */
    case 161: /* tagdatablockpropertyinsertallowed */
    case 162: /* tagdatablockpropertydeleteallowed */
    case 163: /* tagdatablockpropertyupdateallowed */
    case 164: /* tagdatablockpropertywhereclause */
    case 165: /* tagdatablockpropertyorderbyclause */
    case 166: /* taginput */
    case 167: /* taginputfullopen */
    case 168: /* taginputblockclosefull */
    case 169: /* taginputopen */
    case 170: /* taginputproperties */
    case 171: /* taginputshortclose */
    case 172: /* taginputblockclose */
    case 173: /* taginputproperty */
    case 174: /* taginputcheckedvalue */
    case 175: /* taginputuncheckedvalue */
    case 176: /* taginputpropertyinputname */
    case 177: /* taginputpropertysequencename */
    case 178: /* taginputpropertysequenceschemaname */
    case 179: /* taginputpropertymasteritemname */
    case 180: /* taginputpropertyinputtype */
    case 181: /* taginputpropertyinputvalue */
    case 182: /* taginputpropertydefaultvalue */
    case 183: /* taginputpropertycolumnname */
    case 184: /* taginputpropertyformatmask */
    case 185: /* taginputpropertydatatype */
    case 186: /* taginputpropertymaxlength */
    case 187: /* taginputpropertyinsertallowed */
    case 188: /* taginputpropertyupdateallowed */
    case 189: /* taginputpropertydatalistname */
    case 190: /* taginputpropertylookupitemname */
    case 191: /* taginputpropertylookupitemblockname */
    case 192: /* tagtablefullopen */
    case 193: /* tagtableblockclosefull */
    case 194: /* tablecontent */
    case 195: /* tagtableopen */
    case 196: /* tagproperties */
    case 197: /* tagtableblockclose */
    case 198: /* tagthead */
    case 199: /* tagtbody */
    case 200: /* tagtfoot */
    case 201: /* tagtheadfullopen */
    case 202: /* tagtheadblockclosefull */
    case 203: /* tagtablerows */
    case 204: /* tagtheadopen */
    case 205: /* tagpropertieswithreturnvaluesall */
    case 206: /* tagtheadblockclose */
    case 207: /* tagtfootfullopen */
    case 208: /* tagtfootblockclosefull */
    case 209: /* tagtfootopen */
    case 210: /* tagtfootblockclose */
    case 211: /* tagtbodyfullopen */
    case 212: /* tagtbodyblockclosefull */
    case 213: /* tagtbodyopen */
    case 214: /* tagtbodyblockclose */
    case 215: /* tagtablerow */
    case 216: /* tagtablerowfullopen */
    case 217: /* tagtablecols */
    case 218: /* tagtablerowblockclosefull */
    case 219: /* tagtablerowopen */
    case 220: /* tagtablerowblockclose */
    case 221: /* tagtablecol */
    case 222: /* tagtablecoltd */
    case 223: /* tagtablecolth */
    case 224: /* tagtablecoltdfullopen */
    case 225: /* tagtablecoltdblockclosefull */
    case 226: /* tagtablecolcontents */
    case 227: /* tagtablecoltdopen */
    case 228: /* tagtablecoltdblockclose */
    case 229: /* tagtablecolcontent */
    case 230: /* tagtablecolthfullopen */
    case 231: /* tagtablecolthblockclosefull */
    case 232: /* tagtablecolthopen */
    case 233: /* tagtablecolthblockclose */
    case 234: /* tagtitlefullopen */
    case 235: /* tagtitleblockclosefull */
    case 236: /* htmlandspaces */
    case 237: /* tagtitleopen */
    case 238: /* tagtitleblockclose */
    case 239: /* taglinkfullopen */
    case 240: /* taglinkblockclosefull */
    case 241: /* taglinkopen */
    case 242: /* tagshortclose */
    case 243: /* taglinkblockclose */
    case 244: /* tagmetafullopen */
    case 245: /* tagmetablockclosefull */
    case 246: /* tagmetaopen */
    case 247: /* tagmetablockclose */
    case 248: /* tagstylefullopen */
    case 249: /* tagstyleblockclosefull */
    case 250: /* tagstyleopen */
    case 251: /* tagstyleproperties */
    case 252: /* tagstyleblockclose */
    case 253: /* tagstyleproperty */
    case 254: /* tagscriptfullopen */
    case 255: /* tagscriptblockclosefull */
    case 256: /* tagscriptopen */
    case 257: /* tagscriptproperties */
    case 258: /* tagscriptblockclose */
    case 259: /* tagscriptproperty */
    case 260: /* tagscriptpropertyscripttype */
    case 261: /* tagscriptpropertysrc */
    case 262: /* taghtmlfullopen */
    case 263: /* taghtmlblockclosefull */
    case 264: /* taghtmlcontents */
    case 265: /* taghtmlopen */
    case 266: /* taghtmlcontent */
    case 267: /* tagbody */
    case 268: /* taghead */
    case 269: /* tagbodyfullopen */
    case 270: /* tagbodyblockclosefull */
    case 271: /* tagbodyopen */
    case 272: /* tagbodyblockclose */
    case 273: /* tagheadfullopen */
    case 274: /* tagheadblockclosefull */
    case 275: /* tagheadopen */
    case 276: /* tagheadblockclose */
    case 277: /* tagpropertieswithreturnvalues */
    case 278: /* tagpropertywithreturnvalue */
    case 279: /* tagproperty */
    case 280: /* htmlandspace */
    case 281: /* spaces_enter */
{
#line 49 "lemon.html.yy"



#line 1398 "lemon.html.c"
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
  { 97, 5 },
  { 97, 1 },
  { 97, 1 },
  { 95, 1 },
  { 96, 2 },
  { 96, 1 },
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
  { 148, 2 },
  { 148, 1 },
  { 151, 4 },
  { 151, 2 },
  { 152, 3 },
  { 151, 2 },
  { 153, 3 },
  { 151, 2 },
  { 154, 3 },
  { 151, 2 },
  { 155, 3 },
  { 151, 2 },
  { 156, 3 },
  { 151, 2 },
  { 157, 3 },
  { 151, 2 },
  { 158, 3 },
  { 151, 2 },
  { 159, 3 },
  { 151, 2 },
  { 160, 3 },
  { 151, 2 },
  { 161, 3 },
  { 151, 2 },
  { 162, 3 },
  { 151, 2 },
  { 163, 3 },
  { 151, 2 },
  { 164, 3 },
  { 151, 2 },
  { 165, 3 },
  { 166, 1 },
  { 166, 2 },
  { 167, 3 },
  { 167, 3 },
  { 171, 1 },
  { 169, 1 },
  { 169, 1 },
  { 169, 1 },
  { 168, 1 },
  { 172, 1 },
  { 172, 1 },
  { 172, 1 },
  { 170, 2 },
  { 170, 1 },
  { 173, 2 },
  { 174, 3 },
  { 173, 2 },
  { 175, 3 },
  { 173, 2 },
  { 176, 3 },
  { 173, 2 },
  { 177, 3 },
  { 173, 2 },
  { 178, 3 },
  { 173, 2 },
  { 179, 3 },
  { 173, 2 },
  { 180, 3 },
  { 173, 2 },
  { 181, 3 },
  { 173, 2 },
  { 182, 3 },
  { 173, 2 },
  { 183, 3 },
  { 173, 2 },
  { 184, 3 },
  { 173, 2 },
  { 185, 3 },
  { 173, 2 },
  { 186, 3 },
  { 173, 2 },
  { 187, 3 },
  { 173, 2 },
  { 188, 3 },
  { 173, 2 },
  { 189, 3 },
  { 173, 2 },
  { 190, 3 },
  { 173, 2 },
  { 191, 3 },
  { 173, 4 },
  { 114, 2 },
  { 114, 3 },
  { 192, 2 },
  { 192, 3 },
  { 192, 3 },
  { 192, 4 },
  { 195, 1 },
  { 193, 1 },
  { 197, 1 },
  { 194, 3 },
  { 194, 3 },
  { 194, 2 },
  { 194, 2 },
  { 194, 1 },
  { 198, 2 },
  { 198, 3 },
  { 201, 2 },
  { 201, 3 },
  { 201, 3 },
  { 201, 4 },
  { 204, 1 },
  { 202, 1 },
  { 202, 2 },
  { 206, 1 },
  { 200, 3 },
  { 207, 2 },
  { 207, 3 },
  { 207, 3 },
  { 207, 4 },
  { 209, 1 },
  { 208, 1 },
  { 208, 2 },
  { 210, 1 },
  { 199, 3 },
  { 211, 2 },
  { 211, 3 },
  { 211, 3 },
  { 211, 4 },
  { 213, 1 },
  { 212, 1 },
  { 212, 2 },
  { 214, 1 },
  { 203, 2 },
  { 203, 1 },
  { 215, 3 },
  { 216, 2 },
  { 216, 3 },
  { 216, 3 },
  { 219, 1 },
  { 218, 1 },
  { 218, 2 },
  { 220, 1 },
  { 217, 2 },
  { 217, 1 },
  { 221, 1 },
  { 221, 1 },
  { 222, 2 },
  { 222, 3 },
  { 222, 5 },
  { 222, 3 },
  { 222, 4 },
  { 224, 2 },
  { 224, 3 },
  { 227, 1 },
  { 225, 1 },
  { 225, 2 },
  { 228, 1 },
  { 226, 2 },
  { 226, 1 },
  { 229, 1 },
  { 229, 2 },
  { 229, 1 },
  { 229, 2 },
  { 229, 1 },
  { 223, 2 },
  { 223, 3 },
  { 230, 2 },
  { 230, 3 },
  { 232, 1 },
  { 231, 1 },
  { 231, 2 },
  { 233, 1 },
  { 106, 2 },
  { 106, 3 },
  { 234, 2 },
  { 234, 3 },
  { 235, 1 },
  { 237, 1 },
  { 238, 1 },
  { 109, 1 },
  { 109, 2 },
  { 239, 3 },
  { 239, 3 },
  { 240, 1 },
  { 241, 1 },
  { 243, 1 },
  { 110, 1 },
  { 110, 2 },
  { 244, 3 },
  { 244, 3 },
  { 245, 1 },
  { 246, 1 },
  { 247, 1 },
  { 108, 2 },
  { 108, 3 },
  { 248, 2 },
  { 248, 3 },
  { 249, 1 },
  { 250, 1 },
  { 252, 1 },
  { 251, 2 },
  { 251, 1 },
  { 253, 4 },
  { 253, 4 },
  { 253, 4 },
  { 107, 2 },
  { 107, 3 },
  { 254, 2 },
  { 254, 3 },
  { 255, 1 },
  { 256, 1 },
  { 258, 1 },
  { 257, 2 },
  { 257, 1 },
  { 259, 2 },
  { 260, 3 },
  { 259, 2 },
  { 261, 3 },
  { 100, 2 },
  { 100, 3 },
  { 262, 2 },
  { 262, 3 },
  { 263, 1 },
  { 265, 1 },
  { 264, 2 },
  { 264, 1 },
  { 266, 1 },
  { 266, 1 },
  { 266, 1 },
  { 266, 2 },
  { 266, 3 },
  { 267, 2 },
  { 267, 3 },
  { 269, 2 },
  { 269, 3 },
  { 270, 1 },
  { 271, 1 },
  { 272, 1 },
  { 268, 2 },
  { 268, 3 },
  { 273, 1 },
  { 274, 1 },
  { 275, 1 },
  { 276, 1 },
  { 205, 1 },
  { 277, 2 },
  { 277, 1 },
  { 278, 3 },
  { 196, 2 },
  { 196, 1 },
  { 279, 4 },
  { 124, 1 },
  { 124, 2 },
  { 242, 1 },
  { 236, 2 },
  { 236, 1 },
  { 280, 1 },
  { 280, 1 },
  { 115, 1 },
  { 101, 1 },
  { 101, 0 },
  { 99, 2 },
  { 99, 1 },
  { 281, 1 },
  { 281, 1 },
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
      case 0: /* expression ::= tagdoctype spaces_enters taghtml opt__spaces_enters END_OF_FILE */
{  yy_destructor(yypParser,98,&yymsp[-4].minor);
#line 59 "lemon.html.yy"
{
    int a = 111;
    a = 111;
}
#line 2045 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-3].minor);
  yy_destructor(yypParser,100,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,1,&yymsp[0].minor);
}
        break;
      case 1: /* expression ::= space */
{  yy_destructor(yypParser,102,&yymsp[0].minor);
#line 64 "lemon.html.yy"
{
    int a = 111;
    a = 111;
}
#line 2059 "lemon.html.c"
}
        break;
      case 2: /* expression ::= enter */
{  yy_destructor(yypParser,103,&yymsp[0].minor);
#line 69 "lemon.html.yy"
{
    int a = 111;
    a = 111;
}
#line 2069 "lemon.html.c"
}
        break;
      case 3: /* start ::= expressions */
{  yy_destructor(yypParser,96,&yymsp[0].minor);
#line 53 "lemon.html.yy"
{
}
#line 2077 "lemon.html.c"
}
        break;
      case 4: /* expressions ::= expressions expression */
{  yy_destructor(yypParser,96,&yymsp[-1].minor);
#line 55 "lemon.html.yy"
{
}
#line 2085 "lemon.html.c"
  yy_destructor(yypParser,97,&yymsp[0].minor);
}
        break;
      case 5: /* expressions ::= expression */
{  yy_destructor(yypParser,97,&yymsp[0].minor);
#line 56 "lemon.html.yy"
{
}
#line 2094 "lemon.html.c"
}
        break;
      case 6: /* tagheadcontents ::= tagheadcontents tagheadcontent */
{  yy_destructor(yypParser,104,&yymsp[-1].minor);
#line 74 "lemon.html.yy"
{
}
#line 2102 "lemon.html.c"
  yy_destructor(yypParser,105,&yymsp[0].minor);
}
        break;
      case 7: /* tagheadcontents ::= tagheadcontent */
{  yy_destructor(yypParser,105,&yymsp[0].minor);
#line 75 "lemon.html.yy"
{
}
#line 2111 "lemon.html.c"
}
        break;
      case 8: /* tagheadcontent ::= space */
      case 19: /* tagbodycontent ::= space */ yytestcase(yyruleno==19);
      case 57: /* tagcontrolblockcontent ::= space */ yytestcase(yyruleno==57);
      case 72: /* tagdatablockcontent ::= space */ yytestcase(yyruleno==72);
      case 292: /* taghtmlcontent ::= space */ yytestcase(yyruleno==292);
      case 329: /* spaces_enter ::= space */ yytestcase(yyruleno==329);
      case 332: /* spaces ::= space */ yytestcase(yyruleno==332);
{  yy_destructor(yypParser,102,&yymsp[0].minor);
#line 77 "lemon.html.yy"
{
}
#line 2125 "lemon.html.c"
}
        break;
      case 9: /* tagheadcontent ::= enter */
      case 20: /* tagbodycontent ::= enter */ yytestcase(yyruleno==20);
      case 58: /* tagcontrolblockcontent ::= enter */ yytestcase(yyruleno==58);
      case 293: /* taghtmlcontent ::= enter */ yytestcase(yyruleno==293);
      case 330: /* spaces_enter ::= enter */ yytestcase(yyruleno==330);
{  yy_destructor(yypParser,103,&yymsp[0].minor);
#line 78 "lemon.html.yy"
{
}
#line 2137 "lemon.html.c"
}
        break;
      case 10: /* tagheadcontent ::= tagtitle */
{  yy_destructor(yypParser,106,&yymsp[0].minor);
#line 79 "lemon.html.yy"
{
}
#line 2145 "lemon.html.c"
}
        break;
      case 11: /* tagheadcontent ::= tagscript */
{  yy_destructor(yypParser,107,&yymsp[0].minor);
#line 80 "lemon.html.yy"
{
}
#line 2153 "lemon.html.c"
}
        break;
      case 12: /* tagheadcontent ::= tagstyle */
{  yy_destructor(yypParser,108,&yymsp[0].minor);
#line 81 "lemon.html.yy"
{
}
#line 2161 "lemon.html.c"
}
        break;
      case 13: /* tagheadcontent ::= taglink */
{  yy_destructor(yypParser,109,&yymsp[0].minor);
#line 82 "lemon.html.yy"
{
}
#line 2169 "lemon.html.c"
}
        break;
      case 14: /* tagheadcontent ::= tagmeta */
{  yy_destructor(yypParser,110,&yymsp[0].minor);
#line 83 "lemon.html.yy"
{
}
#line 2177 "lemon.html.c"
}
        break;
      case 15: /* tagbodycontents ::= tagbodycontents tagbodycontent */
{  yy_destructor(yypParser,111,&yymsp[-1].minor);
#line 85 "lemon.html.yy"
{
}
#line 2185 "lemon.html.c"
  yy_destructor(yypParser,112,&yymsp[0].minor);
}
        break;
      case 16: /* tagbodycontents ::= tagbodycontent */
{  yy_destructor(yypParser,112,&yymsp[0].minor);
#line 86 "lemon.html.yy"
{
}
#line 2194 "lemon.html.c"
}
        break;
      case 17: /* tagbodycontent ::= htsqls */
{  yy_destructor(yypParser,113,&yymsp[0].minor);
#line 88 "lemon.html.yy"
{
}
#line 2202 "lemon.html.c"
}
        break;
      case 18: /* tagbodycontent ::= tagtable */
      case 71: /* tagdatablockcontent ::= tagtable */ yytestcase(yyruleno==71);
      case 229: /* tagtablecolcontent ::= tagtable */ yytestcase(yyruleno==229);
{  yy_destructor(yypParser,114,&yymsp[0].minor);
#line 89 "lemon.html.yy"
{
}
#line 2212 "lemon.html.c"
}
        break;
      case 21: /* tagbodycontent ::= htmltext */
      case 59: /* tagcontrolblockcontent ::= htmltext */ yytestcase(yyruleno==59);
      case 73: /* tagdatablockcontent ::= htmltext */ yytestcase(yyruleno==73);
      case 227: /* tagtablecolcontent ::= htmltext */ yytestcase(yyruleno==227);
{  yy_destructor(yypParser,115,&yymsp[0].minor);
#line 92 "lemon.html.yy"
{
}
#line 2223 "lemon.html.c"
}
        break;
      case 22: /* htsqls ::= tagdatablock */
{  yy_destructor(yypParser,116,&yymsp[0].minor);
#line 94 "lemon.html.yy"
{
}
#line 2231 "lemon.html.c"
}
        break;
      case 23: /* htsqls ::= tagcontrolblock */
{  yy_destructor(yypParser,117,&yymsp[0].minor);
#line 95 "lemon.html.yy"
{
}
#line 2239 "lemon.html.c"
}
        break;
      case 24: /* htsqls ::= tagdatalist */
{  yy_destructor(yypParser,118,&yymsp[0].minor);
#line 96 "lemon.html.yy"
{
}
#line 2247 "lemon.html.c"
}
        break;
      case 25: /* tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD */
{  yy_destructor(yypParser,2,&yymsp[0].minor);
#line 98 "lemon.html.yy"
{
}
#line 2255 "lemon.html.c"
}
        break;
      case 26: /* tagdoctype ::= TAG_DOCTYPE_HTML */
{  yy_destructor(yypParser,3,&yymsp[0].minor);
#line 100 "lemon.html.yy"
{
}
#line 2263 "lemon.html.c"
}
        break;
      case 27: /* tagtree ::= tagtreefullopen tagtreeblockclosefull */
{  yy_destructor(yypParser,120,&yymsp[-1].minor);
#line 107 "lemon.html.yy"
{
}
#line 2271 "lemon.html.c"
  yy_destructor(yypParser,121,&yymsp[0].minor);
}
        break;
      case 28: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar */
{  yy_destructor(yypParser,122,&yymsp[-2].minor);
#line 108 "lemon.html.yy"
{
}
#line 2280 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 29: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces */
{  yy_destructor(yypParser,122,&yymsp[-3].minor);
#line 109 "lemon.html.yy"
{
}
#line 2290 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 30: /* tagtreeopen ::= TAG_TREE_OPEN */
{  yy_destructor(yypParser,4,&yymsp[0].minor);
#line 111 "lemon.html.yy"
{
}
#line 2301 "lemon.html.c"
}
        break;
      case 31: /* tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE */
{  yy_destructor(yypParser,5,&yymsp[0].minor);
#line 113 "lemon.html.yy"
{
}
#line 2309 "lemon.html.c"
}
        break;
      case 32: /* tagtreeproperties ::= tagtreeproperties tagtreeproperty */
{  yy_destructor(yypParser,123,&yymsp[-1].minor);
#line 115 "lemon.html.yy"
{
}
#line 2317 "lemon.html.c"
  yy_destructor(yypParser,126,&yymsp[0].minor);
}
        break;
      case 33: /* tagtreeproperties ::= tagtreeproperty */
{  yy_destructor(yypParser,126,&yymsp[0].minor);
#line 116 "lemon.html.yy"
{
}
#line 2326 "lemon.html.c"
}
        break;
      case 34: /* tagtreeproperty ::= tagtreepropertyid PROPERTYDATA */
{  yy_destructor(yypParser,127,&yymsp[-1].minor);
#line 118 "lemon.html.yy"
{
}
#line 2334 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 35: /* tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 120 "lemon.html.yy"
{
}
#line 2343 "lemon.html.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 36: /* tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull */
{  yy_destructor(yypParser,128,&yymsp[-1].minor);
#line 126 "lemon.html.yy"
{
}
#line 2353 "lemon.html.c"
  yy_destructor(yypParser,129,&yymsp[0].minor);
}
        break;
      case 37: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar */
{  yy_destructor(yypParser,130,&yymsp[-2].minor);
#line 127 "lemon.html.yy"
{
}
#line 2362 "lemon.html.c"
  yy_destructor(yypParser,131,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 38: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces */
{  yy_destructor(yypParser,130,&yymsp[-3].minor);
#line 128 "lemon.html.yy"
{
}
#line 2372 "lemon.html.c"
  yy_destructor(yypParser,131,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 39: /* tagdatalistopen ::= TAG_DATALIST_OPEN */
{  yy_destructor(yypParser,10,&yymsp[0].minor);
#line 130 "lemon.html.yy"
{
}
#line 2383 "lemon.html.c"
}
        break;
      case 40: /* tagdatalistblockclosefull ::= tagdatalistblockclose */
{  yy_destructor(yypParser,132,&yymsp[0].minor);
#line 132 "lemon.html.yy"
{
}
#line 2391 "lemon.html.c"
}
        break;
      case 41: /* tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE */
{  yy_destructor(yypParser,11,&yymsp[0].minor);
#line 134 "lemon.html.yy"
{
}
#line 2399 "lemon.html.c"
}
        break;
      case 42: /* datalistproperties ::= datalistproperties datalistproperty */
{  yy_destructor(yypParser,131,&yymsp[-1].minor);
#line 136 "lemon.html.yy"
{
}
#line 2407 "lemon.html.c"
  yy_destructor(yypParser,133,&yymsp[0].minor);
}
        break;
      case 43: /* datalistproperties ::= datalistproperty */
{  yy_destructor(yypParser,133,&yymsp[0].minor);
#line 137 "lemon.html.yy"
{
}
#line 2416 "lemon.html.c"
}
        break;
      case 44: /* datalistproperty ::= tagdatalistpropertyid PROPERTYDATA */
{  yy_destructor(yypParser,134,&yymsp[-1].minor);
#line 139 "lemon.html.yy"
{
}
#line 2424 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 45: /* tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 141 "lemon.html.yy"
{
}
#line 2433 "lemon.html.c"
  yy_destructor(yypParser,12,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 46: /* datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA */
{  yy_destructor(yypParser,135,&yymsp[-1].minor);
#line 143 "lemon.html.yy"
{
}
#line 2443 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 47: /* tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 145 "lemon.html.yy"
{
}
#line 2452 "lemon.html.c"
  yy_destructor(yypParser,13,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 48: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull */
{  yy_destructor(yypParser,136,&yymsp[-1].minor);
#line 152 "lemon.html.yy"
{
}
#line 2462 "lemon.html.c"
  yy_destructor(yypParser,137,&yymsp[0].minor);
}
        break;
      case 49: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull */
{  yy_destructor(yypParser,136,&yymsp[-2].minor);
#line 153 "lemon.html.yy"
{
}
#line 2471 "lemon.html.c"
  yy_destructor(yypParser,138,&yymsp[-1].minor);
  yy_destructor(yypParser,137,&yymsp[0].minor);
}
        break;
      case 50: /* tagcontrolblockfullopen ::= tagcontrolblockopen spaces_enters tagcontrolblockproperties tagclosechar */
{  yy_destructor(yypParser,139,&yymsp[-3].minor);
#line 155 "lemon.html.yy"
{
}
#line 2481 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-2].minor);
  yy_destructor(yypParser,140,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 51: /* tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN */
{  yy_destructor(yypParser,14,&yymsp[0].minor);
#line 157 "lemon.html.yy"
{
}
#line 2492 "lemon.html.c"
}
        break;
      case 52: /* tagcontrolblockclosefull ::= tagcontrolblockblockclose */
{  yy_destructor(yypParser,141,&yymsp[0].minor);
#line 159 "lemon.html.yy"
{
}
#line 2500 "lemon.html.c"
}
        break;
      case 53: /* tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 160 "lemon.html.yy"
{
}
#line 2508 "lemon.html.c"
}
        break;
      case 54: /* tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent */
{  yy_destructor(yypParser,138,&yymsp[-1].minor);
#line 162 "lemon.html.yy"
{
}
#line 2516 "lemon.html.c"
  yy_destructor(yypParser,142,&yymsp[0].minor);
}
        break;
      case 55: /* tagcontrolblockcontents ::= tagcontrolblockcontent */
{  yy_destructor(yypParser,142,&yymsp[0].minor);
#line 163 "lemon.html.yy"
{
}
#line 2525 "lemon.html.c"
}
        break;
      case 56: /* tagcontrolblockcontent ::= tagtree */
{  yy_destructor(yypParser,119,&yymsp[0].minor);
#line 165 "lemon.html.yy"
{
}
#line 2533 "lemon.html.c"
}
        break;
      case 60: /* tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty */
{  yy_destructor(yypParser,140,&yymsp[-1].minor);
#line 170 "lemon.html.yy"
{
}
#line 2541 "lemon.html.c"
  yy_destructor(yypParser,143,&yymsp[0].minor);
}
        break;
      case 61: /* tagcontrolblockproperties ::= tagcontrolblockproperty */
{  yy_destructor(yypParser,143,&yymsp[0].minor);
#line 171 "lemon.html.yy"
{
}
#line 2550 "lemon.html.c"
}
        break;
      case 62: /* tagcontrolblockproperty ::= PROP_CONTROLBLOCK_BLOCK_NAME opt__spaces_enters ASSIGMENT opt__spaces_enters PROPERTYDATA */
{  yy_destructor(yypParser,16,&yymsp[-4].minor);
#line 173 "lemon.html.yy"
{
}
#line 2558 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[-3].minor);
  yy_destructor(yypParser,9,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 63: /* tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull */
{  yy_destructor(yypParser,144,&yymsp[-1].minor);
#line 182 "lemon.html.yy"
{
}
#line 2570 "lemon.html.c"
  yy_destructor(yypParser,145,&yymsp[0].minor);
}
        break;
      case 64: /* tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull */
{  yy_destructor(yypParser,144,&yymsp[-2].minor);
#line 183 "lemon.html.yy"
{
}
#line 2579 "lemon.html.c"
  yy_destructor(yypParser,146,&yymsp[-1].minor);
  yy_destructor(yypParser,145,&yymsp[0].minor);
}
        break;
      case 65: /* tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar */
{  yy_destructor(yypParser,147,&yymsp[-2].minor);
#line 184 "lemon.html.yy"
{
}
#line 2589 "lemon.html.c"
  yy_destructor(yypParser,148,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 66: /* tagdatablockopen ::= TAG_DATABLOCK_OPEN */
{  yy_destructor(yypParser,17,&yymsp[0].minor);
#line 186 "lemon.html.yy"
{
}
#line 2599 "lemon.html.c"
}
        break;
      case 67: /* tagdatablockblockclosefull ::= tagdatablockblockclose */
{  yy_destructor(yypParser,149,&yymsp[0].minor);
#line 188 "lemon.html.yy"
{
}
#line 2607 "lemon.html.c"
}
        break;
      case 68: /* tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE */
{  yy_destructor(yypParser,18,&yymsp[0].minor);
#line 190 "lemon.html.yy"
{
}
#line 2615 "lemon.html.c"
}
        break;
      case 69: /* tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent */
{  yy_destructor(yypParser,146,&yymsp[-1].minor);
#line 193 "lemon.html.yy"
{
}
#line 2623 "lemon.html.c"
  yy_destructor(yypParser,150,&yymsp[0].minor);
}
        break;
      case 70: /* tagdatablockcontents ::= tagdatablockcontent */
{  yy_destructor(yypParser,150,&yymsp[0].minor);
#line 194 "lemon.html.yy"
{
}
#line 2632 "lemon.html.c"
}
        break;
      case 74: /* tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty */
{  yy_destructor(yypParser,148,&yymsp[-1].minor);
#line 200 "lemon.html.yy"
{
}
#line 2640 "lemon.html.c"
  yy_destructor(yypParser,151,&yymsp[0].minor);
}
        break;
      case 75: /* tagdatablockproperties ::= tagdatablockproperty */
{  yy_destructor(yypParser,151,&yymsp[0].minor);
#line 202 "lemon.html.yy"
{
}
#line 2649 "lemon.html.c"
}
        break;
      case 76: /* tagdatablockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,7,&yymsp[-3].minor);
#line 204 "lemon.html.yy"
{
}
#line 2657 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 77: /* tagdatablockproperty ::= tagdatablockpropertyjoincondition PROPERTYDATA */
{  yy_destructor(yypParser,152,&yymsp[-1].minor);
#line 206 "lemon.html.yy"
{
}
#line 2668 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 78: /* tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 208 "lemon.html.yy"
{
}
#line 2677 "lemon.html.c"
  yy_destructor(yypParser,20,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 79: /* tagdatablockproperty ::= tagdatablockpropertyconnectionname PROPERTYDATA */
{  yy_destructor(yypParser,153,&yymsp[-1].minor);
#line 211 "lemon.html.yy"
{
}
#line 2687 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 80: /* tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 213 "lemon.html.yy"
{
}
#line 2696 "lemon.html.c"
  yy_destructor(yypParser,21,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 81: /* tagdatablockproperty ::= tagdatablockpropertyautogeneratedcolumns PROPERTYDATA */
{  yy_destructor(yypParser,154,&yymsp[-1].minor);
#line 216 "lemon.html.yy"
{
}
#line 2706 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 82: /* tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 218 "lemon.html.yy"
{
}
#line 2715 "lemon.html.c"
  yy_destructor(yypParser,22,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 83: /* tagdatablockproperty ::= tagdatablockpropertyrecordcount PROPERTYDATA */
{  yy_destructor(yypParser,155,&yymsp[-1].minor);
#line 220 "lemon.html.yy"
{
}
#line 2725 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 84: /* tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 222 "lemon.html.yy"
{
}
#line 2734 "lemon.html.c"
  yy_destructor(yypParser,23,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 85: /* tagdatablockproperty ::= tagdatablockpropertysourcename PROPERTYDATA */
{  yy_destructor(yypParser,156,&yymsp[-1].minor);
#line 224 "lemon.html.yy"
{
}
#line 2744 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 86: /* tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 226 "lemon.html.yy"
{
}
#line 2753 "lemon.html.c"
  yy_destructor(yypParser,24,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 87: /* tagdatablockproperty ::= tagdatablockpropertyschemaname PROPERTYDATA */
{  yy_destructor(yypParser,157,&yymsp[-1].minor);
#line 229 "lemon.html.yy"
{
}
#line 2763 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 88: /* tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 231 "lemon.html.yy"
{
}
#line 2772 "lemon.html.c"
  yy_destructor(yypParser,25,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 89: /* tagdatablockproperty ::= tagdatablockpropertyblockname PROPERTYDATA */
{  yy_destructor(yypParser,158,&yymsp[-1].minor);
#line 233 "lemon.html.yy"
{
}
#line 2782 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 90: /* tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 235 "lemon.html.yy"
{
}
#line 2791 "lemon.html.c"
  yy_destructor(yypParser,26,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 91: /* tagdatablockproperty ::= tagdatablockpropertykeycolumnname PROPERTYDATA */
{  yy_destructor(yypParser,159,&yymsp[-1].minor);
#line 237 "lemon.html.yy"
{
}
#line 2801 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 92: /* tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 239 "lemon.html.yy"
{
}
#line 2810 "lemon.html.c"
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 93: /* tagdatablockproperty ::= tagdatablockpropertymasterblockname PROPERTYDATA */
{  yy_destructor(yypParser,160,&yymsp[-1].minor);
#line 241 "lemon.html.yy"
{
}
#line 2820 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 94: /* tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 243 "lemon.html.yy"
{
}
#line 2829 "lemon.html.c"
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 95: /* tagdatablockproperty ::= tagdatablockpropertyinsertallowed PROPERTYDATA */
{  yy_destructor(yypParser,161,&yymsp[-1].minor);
#line 245 "lemon.html.yy"
{
}
#line 2839 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 96: /* tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 247 "lemon.html.yy"
{
}
#line 2848 "lemon.html.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 97: /* tagdatablockproperty ::= tagdatablockpropertydeleteallowed PROPERTYDATA */
{  yy_destructor(yypParser,162,&yymsp[-1].minor);
#line 249 "lemon.html.yy"
{
}
#line 2858 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 98: /* tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 251 "lemon.html.yy"
{
}
#line 2867 "lemon.html.c"
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 99: /* tagdatablockproperty ::= tagdatablockpropertyupdateallowed PROPERTYDATA */
{  yy_destructor(yypParser,163,&yymsp[-1].minor);
#line 253 "lemon.html.yy"
{
}
#line 2877 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 100: /* tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 255 "lemon.html.yy"
{
}
#line 2886 "lemon.html.c"
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 101: /* tagdatablockproperty ::= tagdatablockpropertywhereclause PROPERTYDATA */
{  yy_destructor(yypParser,164,&yymsp[-1].minor);
#line 258 "lemon.html.yy"
{
}
#line 2896 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 102: /* tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 260 "lemon.html.yy"
{
}
#line 2905 "lemon.html.c"
  yy_destructor(yypParser,32,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 103: /* tagdatablockproperty ::= tagdatablockpropertyorderbyclause PROPERTYDATA */
{  yy_destructor(yypParser,165,&yymsp[-1].minor);
#line 262 "lemon.html.yy"
{
}
#line 2915 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 104: /* tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 264 "lemon.html.yy"
{
}
#line 2924 "lemon.html.c"
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 105: /* taginput ::= taginputfullopen */
{  yy_destructor(yypParser,167,&yymsp[0].minor);
#line 272 "lemon.html.yy"
{
}
#line 2934 "lemon.html.c"
}
        break;
      case 106: /* taginput ::= taginputfullopen taginputblockclosefull */
{  yy_destructor(yypParser,167,&yymsp[-1].minor);
#line 273 "lemon.html.yy"
{
}
#line 2942 "lemon.html.c"
  yy_destructor(yypParser,168,&yymsp[0].minor);
}
        break;
      case 107: /* taginputfullopen ::= taginputopen taginputproperties tagclosechar */
{  yy_destructor(yypParser,169,&yymsp[-2].minor);
#line 274 "lemon.html.yy"
{
}
#line 2951 "lemon.html.c"
  yy_destructor(yypParser,170,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 108: /* taginputfullopen ::= taginputopen taginputproperties taginputshortclose */
{  yy_destructor(yypParser,169,&yymsp[-2].minor);
#line 275 "lemon.html.yy"
{
}
#line 2961 "lemon.html.c"
  yy_destructor(yypParser,170,&yymsp[-1].minor);
  yy_destructor(yypParser,171,&yymsp[0].minor);
}
        break;
      case 109: /* taginputshortclose ::= TAG_SHORT_CLOSE */
      case 319: /* tagshortclose ::= TAG_SHORT_CLOSE */ yytestcase(yyruleno==319);
{  yy_destructor(yypParser,34,&yymsp[0].minor);
#line 278 "lemon.html.yy"
{
}
#line 2972 "lemon.html.c"
}
        break;
      case 110: /* taginputopen ::= TAG_INPUT_OPEN */
{  yy_destructor(yypParser,35,&yymsp[0].minor);
#line 281 "lemon.html.yy"
{
}
#line 2980 "lemon.html.c"
}
        break;
      case 111: /* taginputopen ::= TAG_SELECT_OPEN */
{  yy_destructor(yypParser,36,&yymsp[0].minor);
#line 283 "lemon.html.yy"
{
}
#line 2988 "lemon.html.c"
}
        break;
      case 112: /* taginputopen ::= TAG_TEXTAREA_OPEN */
{  yy_destructor(yypParser,37,&yymsp[0].minor);
#line 285 "lemon.html.yy"
{
}
#line 2996 "lemon.html.c"
}
        break;
      case 113: /* taginputblockclosefull ::= taginputblockclose */
{  yy_destructor(yypParser,172,&yymsp[0].minor);
#line 287 "lemon.html.yy"
{
}
#line 3004 "lemon.html.c"
}
        break;
      case 114: /* taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE */
{  yy_destructor(yypParser,38,&yymsp[0].minor);
#line 289 "lemon.html.yy"
{
}
#line 3012 "lemon.html.c"
}
        break;
      case 115: /* taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE */
{  yy_destructor(yypParser,39,&yymsp[0].minor);
#line 291 "lemon.html.yy"
{
}
#line 3020 "lemon.html.c"
}
        break;
      case 116: /* taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE */
{  yy_destructor(yypParser,40,&yymsp[0].minor);
#line 293 "lemon.html.yy"
{
}
#line 3028 "lemon.html.c"
}
        break;
      case 117: /* taginputproperties ::= taginputproperties taginputproperty */
{  yy_destructor(yypParser,170,&yymsp[-1].minor);
#line 295 "lemon.html.yy"
{
}
#line 3036 "lemon.html.c"
  yy_destructor(yypParser,173,&yymsp[0].minor);
}
        break;
      case 118: /* taginputproperties ::= taginputproperty */
{  yy_destructor(yypParser,173,&yymsp[0].minor);
#line 297 "lemon.html.yy"
{
}
#line 3045 "lemon.html.c"
}
        break;
      case 119: /* taginputproperty ::= taginputcheckedvalue PROPERTYDATA */
{  yy_destructor(yypParser,174,&yymsp[-1].minor);
#line 299 "lemon.html.yy"
{
}
#line 3053 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 120: /* taginputcheckedvalue ::= spaces PROP_INPUT_CHECKED_VALUE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 301 "lemon.html.yy"
{
}
#line 3062 "lemon.html.c"
  yy_destructor(yypParser,41,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 121: /* taginputproperty ::= taginputuncheckedvalue PROPERTYDATA */
{  yy_destructor(yypParser,175,&yymsp[-1].minor);
#line 303 "lemon.html.yy"
{
}
#line 3072 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 122: /* taginputuncheckedvalue ::= spaces PROP_INPUT_UNCHECKED_VALUE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 305 "lemon.html.yy"
{
}
#line 3081 "lemon.html.c"
  yy_destructor(yypParser,42,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 123: /* taginputproperty ::= taginputpropertyinputname PROPERTYDATA */
{  yy_destructor(yypParser,176,&yymsp[-1].minor);
#line 307 "lemon.html.yy"
{
}
#line 3091 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 124: /* taginputpropertyinputname ::= spaces PROP_INPUT_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 309 "lemon.html.yy"
{
}
#line 3100 "lemon.html.c"
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 125: /* taginputproperty ::= taginputpropertysequencename PROPERTYDATA */
{  yy_destructor(yypParser,177,&yymsp[-1].minor);
#line 311 "lemon.html.yy"
{
}
#line 3110 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 126: /* taginputpropertysequencename ::= spaces PROP_INPUT_SEQUENCE_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 313 "lemon.html.yy"
{
}
#line 3119 "lemon.html.c"
  yy_destructor(yypParser,44,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 127: /* taginputproperty ::= taginputpropertysequenceschemaname PROPERTYDATA */
{  yy_destructor(yypParser,178,&yymsp[-1].minor);
#line 315 "lemon.html.yy"
{
}
#line 3129 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 128: /* taginputpropertysequenceschemaname ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 317 "lemon.html.yy"
{
}
#line 3138 "lemon.html.c"
  yy_destructor(yypParser,45,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 129: /* taginputproperty ::= taginputpropertymasteritemname PROPERTYDATA */
{  yy_destructor(yypParser,179,&yymsp[-1].minor);
#line 320 "lemon.html.yy"
{
}
#line 3148 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 130: /* taginputpropertymasteritemname ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 322 "lemon.html.yy"
{
}
#line 3157 "lemon.html.c"
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 131: /* taginputproperty ::= taginputpropertyinputtype PROPERTYDATA */
{  yy_destructor(yypParser,180,&yymsp[-1].minor);
#line 324 "lemon.html.yy"
{
}
#line 3167 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 132: /* taginputpropertyinputtype ::= spaces PROP_INPUT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 326 "lemon.html.yy"
{
}
#line 3176 "lemon.html.c"
  yy_destructor(yypParser,47,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 133: /* taginputproperty ::= taginputpropertyinputvalue PROPERTYDATA */
{  yy_destructor(yypParser,181,&yymsp[-1].minor);
#line 328 "lemon.html.yy"
{
}
#line 3186 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 134: /* taginputpropertyinputvalue ::= spaces PROP_INPUT_VALUE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 330 "lemon.html.yy"
{
}
#line 3195 "lemon.html.c"
  yy_destructor(yypParser,48,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 135: /* taginputproperty ::= taginputpropertydefaultvalue PROPERTYDATA */
{  yy_destructor(yypParser,182,&yymsp[-1].minor);
#line 332 "lemon.html.yy"
{
}
#line 3205 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 136: /* taginputpropertydefaultvalue ::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 334 "lemon.html.yy"
{
}
#line 3214 "lemon.html.c"
  yy_destructor(yypParser,49,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 137: /* taginputproperty ::= taginputpropertycolumnname PROPERTYDATA */
{  yy_destructor(yypParser,183,&yymsp[-1].minor);
#line 336 "lemon.html.yy"
{
}
#line 3224 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 138: /* taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 338 "lemon.html.yy"
{
}
#line 3233 "lemon.html.c"
  yy_destructor(yypParser,50,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 139: /* taginputproperty ::= taginputpropertyformatmask PROPERTYDATA */
{  yy_destructor(yypParser,184,&yymsp[-1].minor);
#line 340 "lemon.html.yy"
{
}
#line 3243 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 140: /* taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 342 "lemon.html.yy"
{
}
#line 3252 "lemon.html.c"
  yy_destructor(yypParser,51,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 141: /* taginputproperty ::= taginputpropertydatatype PROPERTYDATA */
{  yy_destructor(yypParser,185,&yymsp[-1].minor);
#line 344 "lemon.html.yy"
{
}
#line 3262 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 142: /* taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 346 "lemon.html.yy"
{
}
#line 3271 "lemon.html.c"
  yy_destructor(yypParser,52,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 143: /* taginputproperty ::= taginputpropertymaxlength PROPERTYDATA */
{  yy_destructor(yypParser,186,&yymsp[-1].minor);
#line 348 "lemon.html.yy"
{
}
#line 3281 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 144: /* taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 350 "lemon.html.yy"
{
}
#line 3290 "lemon.html.c"
  yy_destructor(yypParser,53,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 145: /* taginputproperty ::= taginputpropertyinsertallowed PROPERTYDATA */
{  yy_destructor(yypParser,187,&yymsp[-1].minor);
#line 352 "lemon.html.yy"
{
}
#line 3300 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 146: /* taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 354 "lemon.html.yy"
{
}
#line 3309 "lemon.html.c"
  yy_destructor(yypParser,54,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 147: /* taginputproperty ::= taginputpropertyupdateallowed PROPERTYDATA */
{  yy_destructor(yypParser,188,&yymsp[-1].minor);
#line 356 "lemon.html.yy"
{
}
#line 3319 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 148: /* taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 358 "lemon.html.yy"
{
}
#line 3328 "lemon.html.c"
  yy_destructor(yypParser,55,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 149: /* taginputproperty ::= taginputpropertydatalistname PROPERTYDATA */
{  yy_destructor(yypParser,189,&yymsp[-1].minor);
#line 360 "lemon.html.yy"
{
}
#line 3338 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 150: /* taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 362 "lemon.html.yy"
{
}
#line 3347 "lemon.html.c"
  yy_destructor(yypParser,56,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 151: /* taginputproperty ::= taginputpropertylookupitemname PROPERTYDATA */
{  yy_destructor(yypParser,190,&yymsp[-1].minor);
#line 364 "lemon.html.yy"
{
}
#line 3357 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 152: /* taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 366 "lemon.html.yy"
{
}
#line 3366 "lemon.html.c"
  yy_destructor(yypParser,57,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 153: /* taginputproperty ::= taginputpropertylookupitemblockname PROPERTYDATA */
{  yy_destructor(yypParser,191,&yymsp[-1].minor);
#line 368 "lemon.html.yy"
{
}
#line 3376 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 154: /* taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 370 "lemon.html.yy"
{
}
#line 3385 "lemon.html.c"
  yy_destructor(yypParser,58,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 155: /* taginputproperty ::= spaces PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,125,&yymsp[-3].minor);
#line 372 "lemon.html.yy"
{
}
#line 3395 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 156: /* tagtable ::= tagtablefullopen tagtableblockclosefull */
{  yy_destructor(yypParser,192,&yymsp[-1].minor);
#line 379 "lemon.html.yy"
{
}
#line 3406 "lemon.html.c"
  yy_destructor(yypParser,193,&yymsp[0].minor);
}
        break;
      case 157: /* tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull */
{  yy_destructor(yypParser,192,&yymsp[-2].minor);
#line 380 "lemon.html.yy"
{
}
#line 3415 "lemon.html.c"
  yy_destructor(yypParser,194,&yymsp[-1].minor);
  yy_destructor(yypParser,193,&yymsp[0].minor);
}
        break;
      case 158: /* tagtablefullopen ::= tagtableopen tagclosechar */
{  yy_destructor(yypParser,195,&yymsp[-1].minor);
#line 382 "lemon.html.yy"
{
}
#line 3425 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 159: /* tagtablefullopen ::= tagtableopen tagclosechar spaces */
{  yy_destructor(yypParser,195,&yymsp[-2].minor);
#line 383 "lemon.html.yy"
{
}
#line 3434 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 160: /* tagtablefullopen ::= tagtableopen tagproperties tagclosechar */
{  yy_destructor(yypParser,195,&yymsp[-2].minor);
#line 384 "lemon.html.yy"
{
}
#line 3444 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 161: /* tagtablefullopen ::= tagtableopen tagproperties tagclosechar spaces */
{  yy_destructor(yypParser,195,&yymsp[-3].minor);
#line 385 "lemon.html.yy"
{
}
#line 3454 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 162: /* tagtableopen ::= TAG_TABLE_OPEN */
{  yy_destructor(yypParser,59,&yymsp[0].minor);
#line 387 "lemon.html.yy"
{
}
#line 3465 "lemon.html.c"
}
        break;
      case 163: /* tagtableblockclosefull ::= tagtableblockclose */
{  yy_destructor(yypParser,197,&yymsp[0].minor);
#line 389 "lemon.html.yy"
{
}
#line 3473 "lemon.html.c"
}
        break;
      case 164: /* tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,60,&yymsp[0].minor);
#line 391 "lemon.html.yy"
{
}
#line 3481 "lemon.html.c"
}
        break;
      case 165: /* tablecontent ::= tagthead tagtbody tagtfoot */
{  yy_destructor(yypParser,198,&yymsp[-2].minor);
#line 397 "lemon.html.yy"
{
}
#line 3489 "lemon.html.c"
  yy_destructor(yypParser,199,&yymsp[-1].minor);
  yy_destructor(yypParser,200,&yymsp[0].minor);
}
        break;
      case 166: /* tablecontent ::= tagthead tagtfoot tagtbody */
{  yy_destructor(yypParser,198,&yymsp[-2].minor);
#line 398 "lemon.html.yy"
{
}
#line 3499 "lemon.html.c"
  yy_destructor(yypParser,200,&yymsp[-1].minor);
  yy_destructor(yypParser,199,&yymsp[0].minor);
}
        break;
      case 167: /* tablecontent ::= tagthead tagtbody */
{  yy_destructor(yypParser,198,&yymsp[-1].minor);
#line 399 "lemon.html.yy"
{
}
#line 3509 "lemon.html.c"
  yy_destructor(yypParser,199,&yymsp[0].minor);
}
        break;
      case 168: /* tablecontent ::= tagtbody tagtfoot */
{  yy_destructor(yypParser,199,&yymsp[-1].minor);
#line 400 "lemon.html.yy"
{
}
#line 3518 "lemon.html.c"
  yy_destructor(yypParser,200,&yymsp[0].minor);
}
        break;
      case 169: /* tablecontent ::= tagtbody */
{  yy_destructor(yypParser,199,&yymsp[0].minor);
#line 401 "lemon.html.yy"
{
}
#line 3527 "lemon.html.c"
}
        break;
      case 170: /* tagthead ::= tagtheadfullopen tagtheadblockclosefull */
{  yy_destructor(yypParser,201,&yymsp[-1].minor);
#line 408 "lemon.html.yy"
{
}
#line 3535 "lemon.html.c"
  yy_destructor(yypParser,202,&yymsp[0].minor);
}
        break;
      case 171: /* tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull */
{  yy_destructor(yypParser,201,&yymsp[-2].minor);
#line 409 "lemon.html.yy"
{
}
#line 3544 "lemon.html.c"
  yy_destructor(yypParser,203,&yymsp[-1].minor);
  yy_destructor(yypParser,202,&yymsp[0].minor);
}
        break;
      case 172: /* tagtheadfullopen ::= tagtheadopen tagclosechar */
{  yy_destructor(yypParser,204,&yymsp[-1].minor);
#line 410 "lemon.html.yy"
{
}
#line 3554 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 173: /* tagtheadfullopen ::= tagtheadopen tagclosechar spaces */
{  yy_destructor(yypParser,204,&yymsp[-2].minor);
#line 411 "lemon.html.yy"
{
}
#line 3563 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 174: /* tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,204,&yymsp[-2].minor);
#line 412 "lemon.html.yy"
{
}
#line 3573 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 175: /* tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces */
{  yy_destructor(yypParser,204,&yymsp[-3].minor);
#line 413 "lemon.html.yy"
{
}
#line 3583 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 176: /* tagtheadopen ::= TAG_THEAD_OPEN */
{  yy_destructor(yypParser,61,&yymsp[0].minor);
#line 414 "lemon.html.yy"
{
}
#line 3594 "lemon.html.c"
}
        break;
      case 177: /* tagtheadblockclosefull ::= tagtheadblockclose */
{  yy_destructor(yypParser,206,&yymsp[0].minor);
#line 416 "lemon.html.yy"
{
}
#line 3602 "lemon.html.c"
}
        break;
      case 178: /* tagtheadblockclosefull ::= tagtheadblockclose spaces */
{  yy_destructor(yypParser,206,&yymsp[-1].minor);
#line 417 "lemon.html.yy"
{
}
#line 3610 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 179: /* tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,62,&yymsp[0].minor);
#line 419 "lemon.html.yy"
{
}
#line 3619 "lemon.html.c"
}
        break;
      case 180: /* tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull */
{  yy_destructor(yypParser,207,&yymsp[-2].minor);
#line 427 "lemon.html.yy"
{
}
#line 3627 "lemon.html.c"
  yy_destructor(yypParser,203,&yymsp[-1].minor);
  yy_destructor(yypParser,208,&yymsp[0].minor);
}
        break;
      case 181: /* tagtfootfullopen ::= tagtfootopen tagclosechar */
{  yy_destructor(yypParser,209,&yymsp[-1].minor);
#line 428 "lemon.html.yy"
{
}
#line 3637 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 182: /* tagtfootfullopen ::= tagtfootopen tagclosechar spaces */
{  yy_destructor(yypParser,209,&yymsp[-2].minor);
#line 429 "lemon.html.yy"
{
}
#line 3646 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 183: /* tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar */
{  yy_destructor(yypParser,209,&yymsp[-2].minor);
#line 430 "lemon.html.yy"
{
}
#line 3656 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 184: /* tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar spaces */
{  yy_destructor(yypParser,209,&yymsp[-3].minor);
#line 431 "lemon.html.yy"
{
}
#line 3666 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 185: /* tagtfootopen ::= TAG_TFOOT_OPEN */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 432 "lemon.html.yy"
{
}
#line 3677 "lemon.html.c"
}
        break;
      case 186: /* tagtfootblockclosefull ::= tagtfootblockclose */
{  yy_destructor(yypParser,210,&yymsp[0].minor);
#line 434 "lemon.html.yy"
{
}
#line 3685 "lemon.html.c"
}
        break;
      case 187: /* tagtfootblockclosefull ::= tagtfootblockclose spaces */
{  yy_destructor(yypParser,210,&yymsp[-1].minor);
#line 435 "lemon.html.yy"
{
}
#line 3693 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 188: /* tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE */
{  yy_destructor(yypParser,64,&yymsp[0].minor);
#line 437 "lemon.html.yy"
{
}
#line 3702 "lemon.html.c"
}
        break;
      case 189: /* tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull */
{  yy_destructor(yypParser,211,&yymsp[-2].minor);
#line 445 "lemon.html.yy"
{
}
#line 3710 "lemon.html.c"
  yy_destructor(yypParser,203,&yymsp[-1].minor);
  yy_destructor(yypParser,212,&yymsp[0].minor);
}
        break;
      case 190: /* tagtbodyfullopen ::= tagtbodyopen tagclosechar */
{  yy_destructor(yypParser,213,&yymsp[-1].minor);
#line 446 "lemon.html.yy"
{
}
#line 3720 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 191: /* tagtbodyfullopen ::= tagtbodyopen tagclosechar spaces */
{  yy_destructor(yypParser,213,&yymsp[-2].minor);
#line 447 "lemon.html.yy"
{
}
#line 3729 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 192: /* tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,213,&yymsp[-2].minor);
#line 448 "lemon.html.yy"
{
}
#line 3739 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 193: /* tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar spaces */
{  yy_destructor(yypParser,213,&yymsp[-3].minor);
#line 449 "lemon.html.yy"
{
}
#line 3749 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 194: /* tagtbodyopen ::= TAG_TBODY_OPEN */
{  yy_destructor(yypParser,65,&yymsp[0].minor);
#line 450 "lemon.html.yy"
{
}
#line 3760 "lemon.html.c"
}
        break;
      case 195: /* tagtbodyblockclosefull ::= tagtbodyblockclose */
{  yy_destructor(yypParser,214,&yymsp[0].minor);
#line 452 "lemon.html.yy"
{
}
#line 3768 "lemon.html.c"
}
        break;
      case 196: /* tagtbodyblockclosefull ::= tagtbodyblockclose spaces */
{  yy_destructor(yypParser,214,&yymsp[-1].minor);
#line 453 "lemon.html.yy"
{
}
#line 3776 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 197: /* tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,66,&yymsp[0].minor);
#line 455 "lemon.html.yy"
{
}
#line 3785 "lemon.html.c"
}
        break;
      case 198: /* tagtablerows ::= tagtablerows tagtablerow */
{  yy_destructor(yypParser,203,&yymsp[-1].minor);
#line 463 "lemon.html.yy"
{
}
#line 3793 "lemon.html.c"
  yy_destructor(yypParser,215,&yymsp[0].minor);
}
        break;
      case 199: /* tagtablerows ::= tagtablerow */
{  yy_destructor(yypParser,215,&yymsp[0].minor);
#line 464 "lemon.html.yy"
{
}
#line 3802 "lemon.html.c"
}
        break;
      case 200: /* tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull */
{  yy_destructor(yypParser,216,&yymsp[-2].minor);
#line 466 "lemon.html.yy"
{
}
#line 3810 "lemon.html.c"
  yy_destructor(yypParser,217,&yymsp[-1].minor);
  yy_destructor(yypParser,218,&yymsp[0].minor);
}
        break;
      case 201: /* tagtablerowfullopen ::= tagtablerowopen tagclosechar */
{  yy_destructor(yypParser,219,&yymsp[-1].minor);
#line 467 "lemon.html.yy"
{
}
#line 3820 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 202: /* tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces */
{  yy_destructor(yypParser,219,&yymsp[-2].minor);
#line 468 "lemon.html.yy"
{
}
#line 3829 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 203: /* tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,219,&yymsp[-2].minor);
#line 469 "lemon.html.yy"
{
}
#line 3839 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 204: /* tagtablerowopen ::= TAG_TR_OPEN */
{  yy_destructor(yypParser,67,&yymsp[0].minor);
#line 471 "lemon.html.yy"
{
}
#line 3849 "lemon.html.c"
}
        break;
      case 205: /* tagtablerowblockclosefull ::= tagtablerowblockclose */
{  yy_destructor(yypParser,220,&yymsp[0].minor);
#line 473 "lemon.html.yy"
{
}
#line 3857 "lemon.html.c"
}
        break;
      case 206: /* tagtablerowblockclosefull ::= tagtablerowblockclose spaces */
{  yy_destructor(yypParser,220,&yymsp[-1].minor);
#line 474 "lemon.html.yy"
{
}
#line 3865 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 207: /* tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE */
{  yy_destructor(yypParser,68,&yymsp[0].minor);
#line 476 "lemon.html.yy"
{
}
#line 3874 "lemon.html.c"
}
        break;
      case 208: /* tagtablecols ::= tagtablecols tagtablecol */
{  yy_destructor(yypParser,217,&yymsp[-1].minor);
#line 480 "lemon.html.yy"
{
}
#line 3882 "lemon.html.c"
  yy_destructor(yypParser,221,&yymsp[0].minor);
}
        break;
      case 209: /* tagtablecols ::= tagtablecol */
{  yy_destructor(yypParser,221,&yymsp[0].minor);
#line 481 "lemon.html.yy"
{
}
#line 3891 "lemon.html.c"
}
        break;
      case 210: /* tagtablecol ::= tagtablecoltd */
{  yy_destructor(yypParser,222,&yymsp[0].minor);
#line 483 "lemon.html.yy"
{
}
#line 3899 "lemon.html.c"
}
        break;
      case 211: /* tagtablecol ::= tagtablecolth */
{  yy_destructor(yypParser,223,&yymsp[0].minor);
#line 484 "lemon.html.yy"
{
}
#line 3907 "lemon.html.c"
}
        break;
      case 212: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-1].minor);
#line 490 "lemon.html.yy"
{
}
#line 3915 "lemon.html.c"
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 213: /* tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-2].minor);
#line 491 "lemon.html.yy"
{
}
#line 3924 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 214: /* tagtablecoltd ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-4].minor);
#line 492 "lemon.html.yy"
{
}
#line 3934 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[-3].minor);
  yy_destructor(yypParser,114,&yymsp[-2].minor);
  yy_destructor(yypParser,125,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 215: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-2].minor);
#line 493 "lemon.html.yy"
{
}
#line 3946 "lemon.html.c"
  yy_destructor(yypParser,226,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 216: /* tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-3].minor);
#line 494 "lemon.html.yy"
{
}
#line 3956 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[-2].minor);
  yy_destructor(yypParser,226,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 217: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar */
{  yy_destructor(yypParser,227,&yymsp[-1].minor);
#line 495 "lemon.html.yy"
{
}
#line 3967 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 218: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar */
{  yy_destructor(yypParser,227,&yymsp[-2].minor);
#line 497 "lemon.html.yy"
{
}
#line 3976 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 219: /* tagtablecoltdopen ::= TAG_TD_OPEN */
{  yy_destructor(yypParser,69,&yymsp[0].minor);
#line 499 "lemon.html.yy"
{
}
#line 3986 "lemon.html.c"
}
        break;
      case 220: /* tagtablecoltdblockclosefull ::= tagtablecoltdblockclose */
{  yy_destructor(yypParser,228,&yymsp[0].minor);
#line 501 "lemon.html.yy"
{
}
#line 3994 "lemon.html.c"
}
        break;
      case 221: /* tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces */
{  yy_destructor(yypParser,228,&yymsp[-1].minor);
#line 502 "lemon.html.yy"
{
}
#line 4002 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 222: /* tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE */
{  yy_destructor(yypParser,70,&yymsp[0].minor);
#line 504 "lemon.html.yy"
{
}
#line 4011 "lemon.html.c"
}
        break;
      case 223: /* tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent */
{  yy_destructor(yypParser,226,&yymsp[-1].minor);
#line 507 "lemon.html.yy"
{
}
#line 4019 "lemon.html.c"
  yy_destructor(yypParser,229,&yymsp[0].minor);
}
        break;
      case 224: /* tagtablecolcontents ::= tagtablecolcontent */
{  yy_destructor(yypParser,229,&yymsp[0].minor);
#line 508 "lemon.html.yy"
{
}
#line 4028 "lemon.html.c"
}
        break;
      case 225: /* tagtablecolcontent ::= taginput */
{  yy_destructor(yypParser,166,&yymsp[0].minor);
#line 510 "lemon.html.yy"
{
}
#line 4036 "lemon.html.c"
}
        break;
      case 226: /* tagtablecolcontent ::= taginput spaces */
{  yy_destructor(yypParser,166,&yymsp[-1].minor);
#line 511 "lemon.html.yy"
{
}
#line 4044 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 228: /* tagtablecolcontent ::= htmltext spaces */
{  yy_destructor(yypParser,115,&yymsp[-1].minor);
#line 513 "lemon.html.yy"
{
}
#line 4053 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 230: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull */
{  yy_destructor(yypParser,230,&yymsp[-1].minor);
#line 520 "lemon.html.yy"
{
}
#line 4062 "lemon.html.c"
  yy_destructor(yypParser,231,&yymsp[0].minor);
}
        break;
      case 231: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull */
{  yy_destructor(yypParser,230,&yymsp[-2].minor);
#line 521 "lemon.html.yy"
{
}
#line 4071 "lemon.html.c"
  yy_destructor(yypParser,226,&yymsp[-1].minor);
  yy_destructor(yypParser,231,&yymsp[0].minor);
}
        break;
      case 232: /* tagtablecolthfullopen ::= tagtablecolthopen tagclosechar */
{  yy_destructor(yypParser,232,&yymsp[-1].minor);
#line 522 "lemon.html.yy"
{
}
#line 4081 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 233: /* tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,232,&yymsp[-2].minor);
#line 524 "lemon.html.yy"
{
}
#line 4090 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 234: /* tagtablecolthopen ::= TAG_TH_OPEN */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 526 "lemon.html.yy"
{
}
#line 4100 "lemon.html.c"
}
        break;
      case 235: /* tagtablecolthblockclosefull ::= tagtablecolthblockclose */
{  yy_destructor(yypParser,233,&yymsp[0].minor);
#line 528 "lemon.html.yy"
{
}
#line 4108 "lemon.html.c"
}
        break;
      case 236: /* tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces */
{  yy_destructor(yypParser,233,&yymsp[-1].minor);
#line 529 "lemon.html.yy"
{
}
#line 4116 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 237: /* tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE */
{  yy_destructor(yypParser,72,&yymsp[0].minor);
#line 531 "lemon.html.yy"
{
}
#line 4125 "lemon.html.c"
}
        break;
      case 238: /* tagtitle ::= tagtitlefullopen tagtitleblockclosefull */
{  yy_destructor(yypParser,234,&yymsp[-1].minor);
#line 539 "lemon.html.yy"
{
}
#line 4133 "lemon.html.c"
  yy_destructor(yypParser,235,&yymsp[0].minor);
}
        break;
      case 239: /* tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull */
{  yy_destructor(yypParser,234,&yymsp[-2].minor);
#line 540 "lemon.html.yy"
{
}
#line 4142 "lemon.html.c"
  yy_destructor(yypParser,236,&yymsp[-1].minor);
  yy_destructor(yypParser,235,&yymsp[0].minor);
}
        break;
      case 240: /* tagtitlefullopen ::= tagtitleopen tagclosechar */
{  yy_destructor(yypParser,237,&yymsp[-1].minor);
#line 541 "lemon.html.yy"
{
}
#line 4152 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 241: /* tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar */
{  yy_destructor(yypParser,237,&yymsp[-2].minor);
#line 542 "lemon.html.yy"
{
}
#line 4161 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 242: /* tagtitleblockclosefull ::= tagtitleblockclose */
{  yy_destructor(yypParser,238,&yymsp[0].minor);
#line 543 "lemon.html.yy"
{
}
#line 4171 "lemon.html.c"
}
        break;
      case 243: /* tagtitleopen ::= TAG_TITLE_OPEN */
{  yy_destructor(yypParser,73,&yymsp[0].minor);
#line 544 "lemon.html.yy"
{
}
#line 4179 "lemon.html.c"
}
        break;
      case 244: /* tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,74,&yymsp[0].minor);
#line 545 "lemon.html.yy"
{
}
#line 4187 "lemon.html.c"
}
        break;
      case 245: /* taglink ::= taglinkfullopen */
{  yy_destructor(yypParser,239,&yymsp[0].minor);
#line 551 "lemon.html.yy"
{
}
#line 4195 "lemon.html.c"
}
        break;
      case 246: /* taglink ::= taglinkfullopen taglinkblockclosefull */
{  yy_destructor(yypParser,239,&yymsp[-1].minor);
#line 552 "lemon.html.yy"
{
}
#line 4203 "lemon.html.c"
  yy_destructor(yypParser,240,&yymsp[0].minor);
}
        break;
      case 247: /* taglinkfullopen ::= taglinkopen tagproperties tagclosechar */
{  yy_destructor(yypParser,241,&yymsp[-2].minor);
#line 553 "lemon.html.yy"
{
}
#line 4212 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 248: /* taglinkfullopen ::= taglinkopen tagproperties tagshortclose */
{  yy_destructor(yypParser,241,&yymsp[-2].minor);
#line 554 "lemon.html.yy"
{
}
#line 4222 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,242,&yymsp[0].minor);
}
        break;
      case 249: /* taglinkblockclosefull ::= taglinkblockclose */
{  yy_destructor(yypParser,243,&yymsp[0].minor);
#line 556 "lemon.html.yy"
{
}
#line 4232 "lemon.html.c"
}
        break;
      case 250: /* taglinkopen ::= TAG_LINK_OPEN */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 558 "lemon.html.yy"
{
}
#line 4240 "lemon.html.c"
}
        break;
      case 251: /* taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE */
{  yy_destructor(yypParser,76,&yymsp[0].minor);
#line 559 "lemon.html.yy"
{
}
#line 4248 "lemon.html.c"
}
        break;
      case 252: /* tagmeta ::= tagmetafullopen */
{  yy_destructor(yypParser,244,&yymsp[0].minor);
#line 566 "lemon.html.yy"
{
}
#line 4256 "lemon.html.c"
}
        break;
      case 253: /* tagmeta ::= tagmetafullopen tagmetablockclosefull */
{  yy_destructor(yypParser,244,&yymsp[-1].minor);
#line 567 "lemon.html.yy"
{
}
#line 4264 "lemon.html.c"
  yy_destructor(yypParser,245,&yymsp[0].minor);
}
        break;
      case 254: /* tagmetafullopen ::= tagmetaopen tagproperties tagclosechar */
{  yy_destructor(yypParser,246,&yymsp[-2].minor);
#line 568 "lemon.html.yy"
{
}
#line 4273 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 255: /* tagmetafullopen ::= tagmetaopen tagproperties tagshortclose */
{  yy_destructor(yypParser,246,&yymsp[-2].minor);
#line 569 "lemon.html.yy"
{
}
#line 4283 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,242,&yymsp[0].minor);
}
        break;
      case 256: /* tagmetablockclosefull ::= tagmetablockclose */
{  yy_destructor(yypParser,247,&yymsp[0].minor);
#line 571 "lemon.html.yy"
{
}
#line 4293 "lemon.html.c"
}
        break;
      case 257: /* tagmetaopen ::= TAG_META_OPEN */
{  yy_destructor(yypParser,77,&yymsp[0].minor);
#line 573 "lemon.html.yy"
{
}
#line 4301 "lemon.html.c"
}
        break;
      case 258: /* tagmetablockclose ::= TAG_META_BLOCK_CLOSE */
{  yy_destructor(yypParser,78,&yymsp[0].minor);
#line 574 "lemon.html.yy"
{
}
#line 4309 "lemon.html.c"
}
        break;
      case 259: /* tagstyle ::= tagstylefullopen tagstyleblockclosefull */
{  yy_destructor(yypParser,248,&yymsp[-1].minor);
#line 581 "lemon.html.yy"
{
}
#line 4317 "lemon.html.c"
  yy_destructor(yypParser,249,&yymsp[0].minor);
}
        break;
      case 260: /* tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull */
{  yy_destructor(yypParser,248,&yymsp[-2].minor);
#line 582 "lemon.html.yy"
{
}
#line 4326 "lemon.html.c"
  yy_destructor(yypParser,236,&yymsp[-1].minor);
  yy_destructor(yypParser,249,&yymsp[0].minor);
}
        break;
      case 261: /* tagstylefullopen ::= tagstyleopen tagclosechar */
{  yy_destructor(yypParser,250,&yymsp[-1].minor);
#line 583 "lemon.html.yy"
{
}
#line 4336 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 262: /* tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar */
{  yy_destructor(yypParser,250,&yymsp[-2].minor);
#line 584 "lemon.html.yy"
{
}
#line 4345 "lemon.html.c"
  yy_destructor(yypParser,251,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 263: /* tagstyleblockclosefull ::= tagstyleblockclose */
{  yy_destructor(yypParser,252,&yymsp[0].minor);
#line 586 "lemon.html.yy"
{
}
#line 4355 "lemon.html.c"
}
        break;
      case 264: /* tagstyleopen ::= TAG_STYLE_OPEN */
{  yy_destructor(yypParser,79,&yymsp[0].minor);
#line 588 "lemon.html.yy"
{
}
#line 4363 "lemon.html.c"
}
        break;
      case 265: /* tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,80,&yymsp[0].minor);
#line 589 "lemon.html.yy"
{
}
#line 4371 "lemon.html.c"
}
        break;
      case 266: /* tagstyleproperties ::= tagstyleproperties tagstyleproperty */
{  yy_destructor(yypParser,251,&yymsp[-1].minor);
#line 592 "lemon.html.yy"
{
}
#line 4379 "lemon.html.c"
  yy_destructor(yypParser,253,&yymsp[0].minor);
}
        break;
      case 267: /* tagstyleproperties ::= tagstyleproperty */
{  yy_destructor(yypParser,253,&yymsp[0].minor);
#line 593 "lemon.html.yy"
{
}
#line 4388 "lemon.html.c"
}
        break;
      case 268: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 595 "lemon.html.yy"
{
}
#line 4396 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 269: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 596 "lemon.html.yy"
{
}
#line 4407 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 270: /* tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */
      case 316: /* tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==316);
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 597 "lemon.html.yy"
{
}
#line 4419 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 271: /* tagscript ::= tagscriptfullopen tagscriptblockclosefull */
{  yy_destructor(yypParser,254,&yymsp[-1].minor);
#line 604 "lemon.html.yy"
{
}
#line 4430 "lemon.html.c"
  yy_destructor(yypParser,255,&yymsp[0].minor);
}
        break;
      case 272: /* tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull */
{  yy_destructor(yypParser,254,&yymsp[-2].minor);
#line 605 "lemon.html.yy"
{
}
#line 4439 "lemon.html.c"
  yy_destructor(yypParser,236,&yymsp[-1].minor);
  yy_destructor(yypParser,255,&yymsp[0].minor);
}
        break;
      case 273: /* tagscriptfullopen ::= tagscriptopen tagclosechar */
{  yy_destructor(yypParser,256,&yymsp[-1].minor);
#line 606 "lemon.html.yy"
{
}
#line 4449 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 274: /* tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar */
{  yy_destructor(yypParser,256,&yymsp[-2].minor);
#line 607 "lemon.html.yy"
{
}
#line 4458 "lemon.html.c"
  yy_destructor(yypParser,257,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 275: /* tagscriptblockclosefull ::= tagscriptblockclose */
{  yy_destructor(yypParser,258,&yymsp[0].minor);
#line 609 "lemon.html.yy"
{
}
#line 4468 "lemon.html.c"
}
        break;
      case 276: /* tagscriptopen ::= TAG_SCRIPT_OPEN */
{  yy_destructor(yypParser,83,&yymsp[0].minor);
#line 611 "lemon.html.yy"
{
}
#line 4476 "lemon.html.c"
}
        break;
      case 277: /* tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE */
{  yy_destructor(yypParser,84,&yymsp[0].minor);
#line 612 "lemon.html.yy"
{
}
#line 4484 "lemon.html.c"
}
        break;
      case 278: /* tagscriptproperties ::= tagscriptproperties tagscriptproperty */
{  yy_destructor(yypParser,257,&yymsp[-1].minor);
#line 616 "lemon.html.yy"
{
}
#line 4492 "lemon.html.c"
  yy_destructor(yypParser,259,&yymsp[0].minor);
}
        break;
      case 279: /* tagscriptproperties ::= tagscriptproperty */
{  yy_destructor(yypParser,259,&yymsp[0].minor);
#line 617 "lemon.html.yy"
{
}
#line 4501 "lemon.html.c"
}
        break;
      case 280: /* tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA */
{  yy_destructor(yypParser,260,&yymsp[-1].minor);
#line 619 "lemon.html.yy"
{
}
#line 4509 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 281: /* tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 621 "lemon.html.yy"
{
}
#line 4518 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 282: /* tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA */
{  yy_destructor(yypParser,261,&yymsp[-1].minor);
#line 623 "lemon.html.yy"
{
}
#line 4528 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 283: /* tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 625 "lemon.html.yy"
{
}
#line 4537 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 284: /* taghtml ::= taghtmlfullopen taghtmlblockclosefull */
{  yy_destructor(yypParser,262,&yymsp[-1].minor);
#line 631 "lemon.html.yy"
{
}
#line 4547 "lemon.html.c"
  yy_destructor(yypParser,263,&yymsp[0].minor);
}
        break;
      case 285: /* taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull */
{  yy_destructor(yypParser,262,&yymsp[-2].minor);
#line 632 "lemon.html.yy"
{
}
#line 4556 "lemon.html.c"
  yy_destructor(yypParser,264,&yymsp[-1].minor);
  yy_destructor(yypParser,263,&yymsp[0].minor);
}
        break;
      case 286: /* taghtmlfullopen ::= taghtmlopen tagclosechar */
{  yy_destructor(yypParser,265,&yymsp[-1].minor);
#line 633 "lemon.html.yy"
{
}
#line 4566 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 287: /* taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar */
{  yy_destructor(yypParser,265,&yymsp[-2].minor);
#line 634 "lemon.html.yy"
{
}
#line 4575 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 288: /* taghtmlblockclosefull ::= TAG_HTML_BLOCK_CLOSE */
{  yy_destructor(yypParser,85,&yymsp[0].minor);
#line 636 "lemon.html.yy"
{
}
#line 4585 "lemon.html.c"
}
        break;
      case 289: /* taghtmlopen ::= TAG_HTML_OPEN */
{  yy_destructor(yypParser,86,&yymsp[0].minor);
#line 638 "lemon.html.yy"
{
}
#line 4593 "lemon.html.c"
}
        break;
      case 290: /* taghtmlcontents ::= taghtmlcontents taghtmlcontent */
{  yy_destructor(yypParser,264,&yymsp[-1].minor);
#line 640 "lemon.html.yy"
{
}
#line 4601 "lemon.html.c"
  yy_destructor(yypParser,266,&yymsp[0].minor);
}
        break;
      case 291: /* taghtmlcontents ::= taghtmlcontent */
{  yy_destructor(yypParser,266,&yymsp[0].minor);
#line 641 "lemon.html.yy"
{
}
#line 4610 "lemon.html.c"
}
        break;
      case 294: /* taghtmlcontent ::= tagbody */
{  yy_destructor(yypParser,267,&yymsp[0].minor);
#line 645 "lemon.html.yy"
{
}
#line 4618 "lemon.html.c"
}
        break;
      case 295: /* taghtmlcontent ::= taghead tagbody */
{  yy_destructor(yypParser,268,&yymsp[-1].minor);
#line 646 "lemon.html.yy"
{
}
#line 4626 "lemon.html.c"
  yy_destructor(yypParser,267,&yymsp[0].minor);
}
        break;
      case 296: /* taghtmlcontent ::= taghead spaces_enters tagbody */
{  yy_destructor(yypParser,268,&yymsp[-2].minor);
#line 647 "lemon.html.yy"
{
}
#line 4635 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-1].minor);
  yy_destructor(yypParser,267,&yymsp[0].minor);
}
        break;
      case 297: /* tagbody ::= tagbodyfullopen tagbodyblockclosefull */
{  yy_destructor(yypParser,269,&yymsp[-1].minor);
#line 654 "lemon.html.yy"
{
}
#line 4645 "lemon.html.c"
  yy_destructor(yypParser,270,&yymsp[0].minor);
}
        break;
      case 298: /* tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull */
{  yy_destructor(yypParser,269,&yymsp[-2].minor);
#line 655 "lemon.html.yy"
{
}
#line 4654 "lemon.html.c"
  yy_destructor(yypParser,111,&yymsp[-1].minor);
  yy_destructor(yypParser,270,&yymsp[0].minor);
}
        break;
      case 299: /* tagbodyfullopen ::= tagbodyopen tagclosechar */
{  yy_destructor(yypParser,271,&yymsp[-1].minor);
#line 657 "lemon.html.yy"
{
}
#line 4664 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 300: /* tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,271,&yymsp[-2].minor);
#line 659 "lemon.html.yy"
{
}
#line 4673 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 301: /* tagbodyblockclosefull ::= tagbodyblockclose */
{  yy_destructor(yypParser,272,&yymsp[0].minor);
#line 661 "lemon.html.yy"
{
}
#line 4683 "lemon.html.c"
}
        break;
      case 302: /* tagbodyopen ::= TAG_BODY_OPEN */
{  yy_destructor(yypParser,87,&yymsp[0].minor);
#line 663 "lemon.html.yy"
{
}
#line 4691 "lemon.html.c"
}
        break;
      case 303: /* tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,88,&yymsp[0].minor);
#line 665 "lemon.html.yy"
{
}
#line 4699 "lemon.html.c"
}
        break;
      case 304: /* taghead ::= tagheadfullopen tagheadblockclosefull */
{  yy_destructor(yypParser,273,&yymsp[-1].minor);
#line 673 "lemon.html.yy"
{
}
#line 4707 "lemon.html.c"
  yy_destructor(yypParser,274,&yymsp[0].minor);
}
        break;
      case 305: /* taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull */
{  yy_destructor(yypParser,273,&yymsp[-2].minor);
#line 674 "lemon.html.yy"
{
}
#line 4716 "lemon.html.c"
  yy_destructor(yypParser,104,&yymsp[-1].minor);
  yy_destructor(yypParser,274,&yymsp[0].minor);
}
        break;
      case 306: /* tagheadfullopen ::= tagheadopen */
{  yy_destructor(yypParser,275,&yymsp[0].minor);
#line 676 "lemon.html.yy"
{
}
#line 4726 "lemon.html.c"
}
        break;
      case 307: /* tagheadblockclosefull ::= tagheadblockclose */
{  yy_destructor(yypParser,276,&yymsp[0].minor);
#line 678 "lemon.html.yy"
{
}
#line 4734 "lemon.html.c"
}
        break;
      case 308: /* tagheadopen ::= TAG_HEAD_OPEN */
{  yy_destructor(yypParser,89,&yymsp[0].minor);
#line 680 "lemon.html.yy"
{
}
#line 4742 "lemon.html.c"
}
        break;
      case 309: /* tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,90,&yymsp[0].minor);
#line 682 "lemon.html.yy"
{
}
#line 4750 "lemon.html.c"
}
        break;
      case 310: /* tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues */
{  yy_destructor(yypParser,277,&yymsp[0].minor);
#line 690 "lemon.html.yy"
{
}
#line 4758 "lemon.html.c"
}
        break;
      case 311: /* tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue */
{  yy_destructor(yypParser,277,&yymsp[-1].minor);
#line 692 "lemon.html.yy"
{
}
#line 4766 "lemon.html.c"
  yy_destructor(yypParser,278,&yymsp[0].minor);
}
        break;
      case 312: /* tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue */
{  yy_destructor(yypParser,278,&yymsp[0].minor);
#line 694 "lemon.html.yy"
{
}
#line 4775 "lemon.html.c"
}
        break;
      case 313: /* tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,19,&yymsp[-2].minor);
#line 696 "lemon.html.yy"
{
}
#line 4783 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 314: /* tagproperties ::= tagproperties tagproperty */
{  yy_destructor(yypParser,196,&yymsp[-1].minor);
#line 703 "lemon.html.yy"
{
}
#line 4793 "lemon.html.c"
  yy_destructor(yypParser,279,&yymsp[0].minor);
}
        break;
      case 315: /* tagproperties ::= tagproperty */
{  yy_destructor(yypParser,279,&yymsp[0].minor);
#line 704 "lemon.html.yy"
{
}
#line 4802 "lemon.html.c"
}
        break;
      case 317: /* tagclosechar ::= TAG_CLOSE */
{  yy_destructor(yypParser,91,&yymsp[0].minor);
#line 710 "lemon.html.yy"
{
}
#line 4810 "lemon.html.c"
}
        break;
      case 318: /* tagclosechar ::= SPACE TAG_CLOSE */
{  yy_destructor(yypParser,7,&yymsp[-1].minor);
#line 711 "lemon.html.yy"
{
}
#line 4818 "lemon.html.c"
  yy_destructor(yypParser,91,&yymsp[0].minor);
}
        break;
      case 320: /* htmlandspaces ::= htmlandspaces htmlandspace */
{  yy_destructor(yypParser,236,&yymsp[-1].minor);
#line 720 "lemon.html.yy"
{
}
#line 4827 "lemon.html.c"
  yy_destructor(yypParser,280,&yymsp[0].minor);
}
        break;
      case 321: /* htmlandspaces ::= htmlandspace */
{  yy_destructor(yypParser,280,&yymsp[0].minor);
#line 721 "lemon.html.yy"
{
}
#line 4836 "lemon.html.c"
}
        break;
      case 322: /* htmlandspace ::= HTMLTEXT */
      case 324: /* htmltext ::= HTMLTEXT */ yytestcase(yyruleno==324);
{  yy_destructor(yypParser,92,&yymsp[0].minor);
#line 723 "lemon.html.yy"
{
}
#line 4845 "lemon.html.c"
}
        break;
      case 323: /* htmlandspace ::= SPACE */
      case 333: /* space ::= SPACE */ yytestcase(yyruleno==333);
{  yy_destructor(yypParser,7,&yymsp[0].minor);
#line 724 "lemon.html.yy"
{
}
#line 4854 "lemon.html.c"
}
        break;
      case 325: /* opt__spaces_enters ::= spaces_enters */
{  yy_destructor(yypParser,99,&yymsp[0].minor);
#line 733 "lemon.html.yy"
{
}
#line 4862 "lemon.html.c"
}
        break;
      case 327: /* spaces_enters ::= spaces_enters spaces_enter */
{  yy_destructor(yypParser,99,&yymsp[-1].minor);
#line 736 "lemon.html.yy"
{
}
#line 4870 "lemon.html.c"
  yy_destructor(yypParser,281,&yymsp[0].minor);
}
        break;
      case 328: /* spaces_enters ::= spaces_enter */
{  yy_destructor(yypParser,281,&yymsp[0].minor);
#line 737 "lemon.html.yy"
{
}
#line 4879 "lemon.html.c"
}
        break;
      case 331: /* spaces ::= spaces space */
{  yy_destructor(yypParser,125,&yymsp[-1].minor);
#line 743 "lemon.html.yy"
{
}
#line 4887 "lemon.html.c"
  yy_destructor(yypParser,102,&yymsp[0].minor);
}
        break;
      case 334: /* enter ::= ENTER */
{  yy_destructor(yypParser,93,&yymsp[0].minor);
#line 750 "lemon.html.yy"
{
}
#line 4896 "lemon.html.c"
}
        break;
      default:
      /* (326) opt__spaces_enters ::= */ yytestcase(yyruleno==326);
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
#line 29 "lemon.html.yy"

    printf("--SYNTAX ERROR--");
    exit(100);
#line 4961 "lemon.html.c"
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
