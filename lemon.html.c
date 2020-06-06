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
#define YYNOCODE 285
#define YYACTIONTYPE unsigned short int
#define htmlParseTOKENTYPE  Token 
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
#define YYNSTATE             233
#define YYNRULE              337
#define YY_MAX_SHIFT         232
#define YY_MIN_SHIFTREDUCE   524
#define YY_MAX_SHIFTREDUCE   860
#define YY_MIN_REDUCE        861
#define YY_MAX_REDUCE        1197
#define YY_ERROR_ACTION      1198
#define YY_ACCEPT_ACTION     1199
#define YY_NO_ACTION         1200
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
#define YY_ACTTAB_COUNT (881)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   102,    4,    4,    4,    4,    4,    4,    4,    4,    4,
 /*    10 */   744,  714,  759,   83,  723,   23,  859,  590,   39,   56,
 /*    20 */   632,  102,  102,  531,  531,  531,  531,  531,  531,  531,
 /*    30 */   531,  705,  784,   95,  128,  784,  798,  797,  723,   23,
 /*    40 */   797,  729,   39,  102,  599,  160,  159,  158,  157,  156,
 /*    50 */   155,  154,  153,  152,  151,  150,  149,  148,  147,   50,
 /*    60 */   814,   50,  232,  229,  846,   56,  849,  633,  860,  642,
 /*    70 */   221,  200,  199,  198,  197,  196,  195,  194,  193,  192,
 /*    80 */   191,  190,  189,  188,  187,  186,  185,  184,    1,  799,
 /*    90 */   106,    1,  221,  200,  199,  198,  197,  196,  195,  194,
 /*   100 */   193,  192,  191,  190,  189,  188,  187,  186,  185,  184,
 /*   110 */     7,  106,  182,    7,  160,  159,  158,  157,  156,  155,
 /*   120 */   154,  153,  152,  151,  150,  149,  148,  147,  713,  859,
 /*   130 */   182,  729,  812,   37,   72,   71,   44,  859,   77,  790,
 /*   140 */    69,  135,   53,   76,   47,   68,   52,   34,   46,   43,
 /*   150 */   811,  848,  631,   33,   37,   29,  631,   44,  693,   77,
 /*   160 */   861,   69,  550,  551,   76,   53,   68,   47,   34,   42,
 /*   170 */    43,   42,  140,  137,   33,  830,   29,  830,    6,    6,
 /*   180 */   527,  101,  710,  527,  719,    6,    6,    6,    6,    6,
 /*   190 */     6,    6,    6,  859,  710,  768,  831,  775,  831,  782,
 /*   200 */   127,  789,  100,  202,   54,  801,   13,   13,  763,   57,
 /*   210 */    18,  763,  835,   97,  226,  860,  815,  828,   17,  834,
 /*   220 */   719,    8,   58,  860,  803,  140,  137,  220,  219,  218,
 /*   230 */   217,  216,  215,  214,  213,  212,  211,  210,  209,  208,
 /*   240 */   207,  206,  205,  204,  203,  814,   55,  783,  540,  540,
 /*   250 */   695,   30,  575,  182,   80,   57,  540,  540,  540,  540,
 /*   260 */   540,  540,  540,   30,   23,  796,   20,   39,  796,   49,
 /*   270 */   129,  584,  100,  725,   54,   94,  733,  733,  733,    9,
 /*   280 */    18,  689,   48,   97,  843,   12,   79,   40,   17,  840,
 /*   290 */   176,    8,   55,  174,  173,  172,  171,  170,  169,  168,
 /*   300 */   167,  166,  165,  164,  163,  162,  161,   58,  176,  816,
 /*   310 */   816,  174,  173,  172,  171,  170,  169,  168,  167,  166,
 /*   320 */   165,  164,  163,  162,  161,  776,  704,  555,   14,   88,
 /*   330 */   859,  729,   10,  748,   88,  183,   20,  849,  578,   49,
 /*   340 */   855,  133,   15,   88,   11,   35,  823,   41,  823,  785,
 /*   350 */    91,   88,  785,   10,  843,  748,   88, 1199,   28,  136,
 /*   360 */    28,  101,  634,   28,  844,  809,   13,  103,  809,   13,
 /*   370 */    13,   24,  682,    5,  142,   45,  682,    3,  182,    3,
 /*   380 */    89,   74,  846,    2,   75,   89,   74,   75,    2,  635,
 /*   390 */   636,  637,  851,  851,   89,   74,  566,    2,  779,  526,
 /*   400 */   550,  551,   89,   74,  769,    2,   20,   89,   74,   49,
 /*   410 */     2,   20,  182,  687,   49,  850,  824,  182,  824,  843,
 /*   420 */    20,  849,  848,   49,  732,  744,  762,  759,   20,   86,
 /*   430 */    35,   49,  765,   20,  748,   88,   49,  766,  146,  144,
 /*   440 */    14,  115,  115,   14,  183,  755,  850,   87,  748,   99,
 /*   450 */   756,  132,   87,  737,   15,  859,   90,   15,  567,  232,
 /*   460 */   229,  738,   16,  860,   90,   16,  740,  593,  810,   90,
 /*   470 */   748,  810,  816,  816,   24,  529,    5,  227,   45,  857,
 /*   480 */     3,  855,    3,  814,   21,   22,   89,   74,  182,    2,
 /*   490 */    25,   25,  722,  729,   21,   21,   22,  130,  802,   78,
 /*   500 */    22,  125,  859,   73,   60,  564,  848,  687,  772,  576,
 /*   510 */   104,  757,   20,  591,  728,   49,  780,  786,  573,   22,
 /*   520 */   758,  594,  573,   22,   11,  588,   21,   41,  843,  588,
 /*   530 */    21,  594,  594,  681,   96,  843,  178,  681,   27,   70,
 /*   540 */   850,   26,  556,   67,   38,  741,   67,  228,   90,  748,
 /*   550 */   182,   52,  859,   46,  687,  840,  822,  182,  579,    5,
 /*   560 */   844,   45,  589,  689,  701,  855,  589,  594,  719,  579,
 /*   570 */   825,  851,   20,  579,  125,   49,   73,   82,  859,  837,
 /*   580 */   635,  636,  637,  829,  115,  115,  552,  850,  860,   60,
 /*   590 */   862,  574,  105,   19,  840,  574,  579,   19,   19,   19,
 /*   600 */     9,  182,  182,   48,  687,  182,   12,  183,   40,   20,
 /*   610 */   696,  182,   49,  808,   80,  747,  635,  636,  637,   31,
 /*   620 */   859,   85,  742,  723,   23,   93,  773,   39,  179,  134,
 /*   630 */   764,   31,   23,  764,  845,   39,   11,  850,  178,   41,
 /*   640 */   687,  747,   61,  130,   59,  131,   59,  225,  223,   62,
 /*   650 */    98,  747,  557,  228,  821,  182,   25,    5,   32,   45,
 /*   660 */   182,  182,  182,  787,  182,  840,  115,  115,  807,   25,
 /*   670 */    32,   23,  806,  850,   39,  826,  691,  846,  231,  230,
 /*   680 */    81,   84,  743,  778,   92,  778,  739,  179,   52,   90,
 /*   690 */    46,  843,  690,   63,   64,  805,  107,   66,  108,   53,
 /*   700 */   828,   47,  109,   36,  138,  139,  860,  110,  639,  640,
 /*   710 */   641,  111,  843,  843,  844,  771,  112,  107,  771,  108,
 /*   720 */   113,  114,  844,  109,  116,  225,  223,   61,  110,  843,
 /*   730 */   117,  118,  111,  119,   62,  231,  230,  112,   65,  120,
 /*   740 */   121,  113,  114,  122,  123,  116,  124,  126,  795,  141,
 /*   750 */    51,  117,  118,  561,  119,   51,  561,  844,  794,   65,
 /*   760 */   120,  121,  143,  793,  122,  123,  844,  124,  126,  145,
 /*   770 */   628,  843,  626,  842,  624,  622,  620,  618,   63,   64,
 /*   780 */   181,  616,   66,  614,  612,  610,  608,  678,   36,  606,
 /*   790 */   604,  602,  791,  863,  676,  629,  627,  863,  625,  623,
 /*   800 */   621,  619,  617,  863,  201,  615,  613,  863,  611,  609,
 /*   810 */   607,  605,  603,  601,  679,  175,  839,  863,  177,  674,
 /*   820 */   180,  677,  672,  670,  675,  668,  666,  664,  863,  662,
 /*   830 */   660,  673,  840,  658,  656,  671,  654,  840,  840,  840,
 /*   840 */   652,  840,  669,  650,  648,  646,  680,  863,  863,  863,
 /*   850 */   667,  665,  663,  661,  659,  657,  655,  863,  863,  863,
 /*   860 */   653,  651,  649,  647,  645,  222,  224,  644,  587,  586,
 /*   870 */   863,  863,  227,  559,  560,  571,  863,  572,  863,  570,
 /*   880 */   569,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   104,  102,  103,  104,  105,  106,  107,  108,  109,  110,
 /*    10 */    69,  212,   71,  214,  215,  216,    7,  124,  219,  236,
 /*    20 */   124,  125,  104,  103,  104,  105,  106,  107,  108,  109,
 /*    30 */   110,  208,  249,  210,    7,  252,  124,  255,  215,  216,
 /*    40 */   258,   67,  219,  125,  151,  152,  153,  154,  155,  156,
 /*    50 */   157,  158,  159,  160,  161,  162,  163,  164,  165,  131,
 /*    60 */    85,  133,  134,  135,  282,  282,    7,  171,   93,  173,
 /*    70 */   174,  175,  176,  177,  178,  179,  180,  181,  182,  183,
 /*    80 */   184,  185,  186,  187,  188,  189,  190,  191,  170,  124,
 /*    90 */   104,  173,  174,  175,  176,  177,  178,  179,  180,  181,
 /*   100 */   182,  183,  184,  185,  186,  187,  188,  189,  190,  191,
 /*   110 */   148,  125,  104,  151,  152,  153,  154,  155,  156,  157,
 /*   120 */   158,  159,  160,  161,  162,  163,  164,  165,   64,    7,
 /*   130 */   104,   67,  124,  234,  199,  200,  237,    7,  239,   80,
 /*   140 */   241,    7,  207,  244,  209,  246,  211,  248,  213,  250,
 /*   150 */   124,   92,  168,  254,  234,  256,  172,  237,  200,  239,
 /*   160 */     0,  241,    2,    3,  244,  207,  246,  209,  248,  257,
 /*   170 */   250,  259,  260,  261,  254,  276,  256,  278,  104,  105,
 /*   180 */    98,   99,   63,  101,   65,  111,  112,  113,  114,  115,
 /*   190 */   116,  117,  118,    7,   63,   73,  276,   75,  278,   77,
 /*   200 */     7,   79,  128,   17,  130,   83,  104,  105,  235,  236,
 /*   210 */   136,  238,   90,  139,    7,   93,   86,   87,  144,   89,
 /*   220 */    65,  147,  196,   93,  259,  260,  261,   41,   42,   43,
 /*   230 */    44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
 /*   240 */    54,   55,   56,   57,   58,   85,  236,   78,  104,  105,
 /*   250 */   202,  203,  124,  104,  206,  282,  112,  113,  114,  115,
 /*   260 */   116,  117,  118,  215,  216,  255,  192,  219,  258,  195,
 /*   270 */     7,  143,  128,  218,  130,  220,  221,  222,  223,  224,
 /*   280 */   136,   60,  227,  139,   91,  230,  124,  232,  144,  281,
 /*   290 */    17,  147,  282,   20,   21,   22,   23,   24,   25,   26,
 /*   300 */    27,   28,   29,   30,   31,   32,   33,  281,   17,  104,
 /*   310 */   105,   20,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   320 */    29,   30,   31,   32,   33,   76,   62,    4,  114,  115,
 /*   330 */     7,   67,  104,  114,  115,    7,  192,    7,   15,  195,
 /*   340 */   104,    7,  114,  115,  262,  196,  272,  265,  274,  249,
 /*   350 */   114,  115,  252,  125,   91,  114,  115,   95,   96,   97,
 /*   360 */    98,   99,   34,  101,   91,  263,  264,  205,  266,  267,
 /*   370 */   268,  269,  193,  271,   17,  273,  197,  275,  104,  277,
 /*   380 */   166,  167,  282,  169,  140,  166,  167,  143,  169,   35,
 /*   390 */    36,   37,  104,  105,  166,  167,   11,  169,  124,    1,
 /*   400 */     2,    3,  166,  167,   74,  169,  192,  166,  167,  195,
 /*   410 */   169,  192,  104,   59,  195,   92,  272,  104,  274,   91,
 /*   420 */   192,    7,   92,  195,   68,   69,   72,   71,  192,  124,
 /*   430 */   281,  195,  124,  192,  114,  115,  195,  124,   81,   82,
 /*   440 */   226,  279,  280,  229,    7,  231,   92,  233,  229,  124,
 /*   450 */   231,    7,  233,  225,  226,    7,  228,  229,  133,  134,
 /*   460 */   135,  225,  226,   93,  228,  229,  225,   19,  263,  228,
 /*   470 */   229,  266,  267,  268,  269,  101,  271,    8,  273,  105,
 /*   480 */   275,  104,  277,   85,  104,  104,  166,  167,  104,  169,
 /*   490 */   104,  105,   66,   67,  114,  115,  115,  104,   84,  124,
 /*   500 */   119,  120,    7,  122,  196,   10,   92,   59,  124,   14,
 /*   510 */   205,  124,  192,   18,  124,  195,  242,  124,  137,  138,
 /*   520 */   124,  104,  141,  142,  262,  145,  146,  265,   91,  149,
 /*   530 */   150,  114,  115,  193,  194,   91,   17,  197,  198,  199,
 /*   540 */    92,  201,    5,  123,  204,  225,  126,  127,  228,  229,
 /*   550 */   104,  211,    7,  213,   59,  281,  268,  104,  104,  271,
 /*   560 */    91,  273,  145,   60,   61,  104,  149,  150,   65,  115,
 /*   570 */   124,  283,  192,  119,  120,  195,  122,  124,    7,  280,
 /*   580 */    35,   36,   37,   88,  279,  280,  121,   92,   93,  281,
 /*   590 */     0,  137,  205,  217,  281,  141,  142,  221,  222,  223,
 /*   600 */   224,  104,  104,  227,   59,  104,  230,    7,  232,  192,
 /*   610 */   202,  104,  195,    9,  206,   70,   35,   36,   37,  203,
 /*   620 */     7,  124,  124,  215,  216,  124,  242,  219,    7,    7,
 /*   630 */   235,  215,  216,  238,   34,  219,  262,   92,   17,  265,
 /*   640 */    59,   70,  196,  104,  251,    7,  253,   16,   17,  196,
 /*   650 */   124,   70,  126,  127,  268,  104,  270,  271,  203,  273,
 /*   660 */   104,  104,  104,  124,  104,  281,  279,  280,    6,  283,
 /*   670 */   215,  216,    9,   92,  219,  124,  199,  282,   12,   13,
 /*   680 */   124,  124,  124,  245,  124,  247,  225,    7,  211,  228,
 /*   690 */   213,   91,  200,  196,  196,    6,  104,  196,  104,  207,
 /*   700 */    87,  209,  104,  196,   81,   82,   93,  104,   38,   39,
 /*   710 */    40,  104,   91,   91,   91,  240,  104,  125,  243,  125,
 /*   720 */   104,  104,   91,  125,  104,   16,   17,  281,  125,   91,
 /*   730 */   104,  104,  125,  104,  281,   12,   13,  125,  104,  104,
 /*   740 */   104,  125,  125,  104,  104,  125,  104,  104,    6,    9,
 /*   750 */   100,  125,  125,  129,  125,  105,  132,   91,    6,  125,
 /*   760 */   125,  125,    9,    6,  125,  125,   91,  125,  125,    9,
 /*   770 */     6,   91,    6,    6,    6,    6,    6,    6,  281,  281,
 /*   780 */    17,    6,  281,    6,    6,    6,    6,    6,  281,    6,
 /*   790 */     6,    6,  253,  284,    6,    9,    9,  284,    9,    9,
 /*   800 */     9,    9,    9,  284,    9,    9,    9,  284,    9,    9,
 /*   810 */     9,    9,    9,    6,    9,    9,    6,  284,    9,    6,
 /*   820 */     9,    9,    6,    6,    9,    6,    6,    6,  284,    6,
 /*   830 */     6,    9,  281,    6,    6,    9,    6,  281,  281,  281,
 /*   840 */     6,  281,    9,    6,    6,    6,    6,  284,  284,  284,
 /*   850 */     9,    9,    9,    9,    9,    9,    9,  284,  284,  284,
 /*   860 */     9,    9,    9,    9,    9,    9,    9,    6,    6,    6,
 /*   870 */   284,  284,    8,    6,    9,    6,  284,    9,  284,    9,
 /*   880 */     6,
};
#define YY_SHIFT_USE_DFLT (881)
#define YY_SHIFT_COUNT    (232)
#define YY_SHIFT_MIN      (-59)
#define YY_SHIFT_MAX      (874)
static const short yy_shift_ofst[] = {
 /*     0 */   398,  328,    9,  122,  122,  495,  495,  193,   27,  545,
 /*    10 */   545,  130,  354,  130,  354,  581,  581,  448,  323,  356,
 /*    20 */   503,  448,  323,  -59,  613,  613,  264,  119,  160,  263,
 /*    30 */   264,  426,   64,  414,   59,  600,  600,  330,  621,  621,
 /*    40 */   621,  437,  263,  437,  437,  437,  437,  437,  437,  437,
 /*    50 */   444,  -25,  -26,  -26,  134,  414,   59,  330,  437,  437,
 /*    60 */   437,  437,  437,  437,  437,  571,  437,  622,    9,    9,
 /*    70 */   131,  155,  131,  207,  670,  638,  169,  249,    9,    9,
 /*    80 */     9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
 /*    90 */     9,    9,    9,    9,    9,    9,  221,  334,    9,    9,
 /*   100 */   385,  370,  186,  680,  680,  680,    9,    9,    9,    9,
 /*   110 */     9,    9,    9,    9,    9,  519,    9,    9,    9,    9,
 /*   120 */     9,    9,    9,    9,    9,  537,    9,  273,  291,  623,
 /*   130 */   357,  631,  666,  709,  469,  723,  590,  662,  604,  663,
 /*   140 */   689,  742,  740,  752,  753,  757,  760,  764,  766,  768,
 /*   150 */   769,  770,  771,  775,  777,  778,  779,  780,  783,  784,
 /*   160 */   785,  786,  787,  789,  790,  791,  792,  793,  796,  797,
 /*   170 */   799,  800,  801,  802,  803,  807,  806,  810,  809,  675,
 /*   180 */   767,  811,  763,  675,  781,  788,  813,  816,  817,  819,
 /*   190 */   820,  821,  823,  824,  827,  828,  830,  834,  837,  838,
 /*   200 */   839,  840,  795,  805,  812,  815,  822,  826,  833,  841,
 /*   210 */   842,  843,  844,  845,  846,  847,  851,  852,  853,  854,
 /*   220 */   855,  861,  862,  856,  863,  857,  864,  865,  867,  869,
 /*   230 */   868,  870,  874,
};
#define YY_REDUCE_USE_DFLT (-219)
#define YY_REDUCE_COUNT (126)
#define YY_REDUCE_MIN   (-218)
#define YY_REDUCE_MAX   (650)
static const short yy_reduce_ofst[] = {
 /*     0 */   262, -104,  -82, -101,  -80,   74,  144, -107,  -38,  228,
 /*    10 */   236,  102,  214,  205,  219,  241,  320,  380,  381,   55,
 /*    20 */   340,  417,  454,  376,  386,  288,   48,  -65,   82,  -88,
 /*    30 */   408, -201, -177,   10, -217,  274,  384,  -27,  162,  305,
 /*    40 */   387,   26,  -35,  393,  308,  446,  453,  497,  498,  501,
 /*    50 */   325,  374,  416,  455,  -72, -218,  100,  395,    8,  539,
 /*    60 */   313,  551,  556,  557,  558,  461,  560,  526,  149,  507,
 /*    70 */   -42,  477,  492,  420,  -16,  128,  438,  475,  -14,  592,
 /*    80 */   594,  598,  603,  607,  612,  616,  617,  620,  626,  627,
 /*    90 */   629,  634,  635,  636,  639,  640,  179,  244,  642,  643,
 /*   100 */   624,  650,  377,  375,  390,  396,  377,  377,  377,  377,
 /*   110 */   377,  377,  377,  377,  377,  299,  377,  377,  377,  377,
 /*   120 */   377,  377,  377,  377,  377,  465,  377,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    10 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    20 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    30 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    40 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    50 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    60 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    70 */  1031, 1198, 1029, 1198,  967, 1198, 1114, 1107, 1036, 1034,
 /*    80 */  1039, 1054, 1052, 1057, 1045, 1043, 1063, 1097, 1089, 1087,
 /*    90 */  1082, 1091, 1022, 1020, 1067, 1048, 1198, 1198,  890,  899,
 /*   100 */  1198, 1198, 1198, 1198, 1198, 1198, 1037, 1035, 1040, 1055,
 /*   110 */  1053, 1058, 1046, 1044, 1064, 1173, 1098, 1090, 1088, 1083,
 /*   120 */  1023, 1021, 1068, 1049,  891, 1198,  900, 1198, 1198, 1198,
 /*   130 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   140 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   150 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   160 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   170 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   180 */  1198, 1198, 1198, 1196, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   190 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   200 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   210 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   220 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   230 */  1198, 1198, 1198,
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
  "PROP_CONTROLBLOCK_BLOCK_NAME",  "PROPERTYID",    "TAG_DATABLOCK_OPEN",  "TAG_DATABLOCK_BLOCK_CLOSE",
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
  "TAG_SCRIPT_BLOCK_CLOSE",  "TAG_HTML_OPEN",  "TAG_HTML_BLOCK_CLOSE",  "TAG_BODY_OPEN",
  "TAG_BODY_BLOCK_CLOSE",  "TAG_HEAD_OPEN",  "TAG_HEAD_BLOCK_CLOSE",  "TAG_CLOSE",   
  "HTMLTEXT",      "ENTER",         "error",         "start",       
  "expressions",   "eof",           "expression",    "tagdoctype",  
  "enters",        "taghtml",       "tagheadcontents",  "tagheadcontent",
  "space",         "enter",         "tagtitle",      "tagscript",   
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
  "taghtmlcontents",  "taghtmlopen",   "taghtmlblockclose",  "taghtmlcontent",
  "tagbody",       "taghead",       "spaces_enters",  "tagbodyfullopen",
  "tagbodyblockclosefull",  "tagbodyopen",   "tagbodyblockclose",  "tagheadfullopen",
  "tagheadblockclosefull",  "tagheadopen",   "tagheadblockclose",  "tagpropertieswithreturnvalues",
  "tagpropertywithreturnvalue",  "tagproperty",   "htmlandspace",  "spaces_enter",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "start ::= expressions",
 /*   1 */ "start ::= eof",
 /*   2 */ "eof ::= END_OF_FILE",
 /*   3 */ "expressions ::= expressions expression",
 /*   4 */ "expressions ::= expression",
 /*   5 */ "expression ::= tagdoctype enters taghtml",
 /*   6 */ "expression ::= taghtml",
 /*   7 */ "tagheadcontents ::= tagheadcontents tagheadcontent",
 /*   8 */ "tagheadcontents ::= tagheadcontent",
 /*   9 */ "tagheadcontent ::= space",
 /*  10 */ "tagheadcontent ::= enter",
 /*  11 */ "tagheadcontent ::= tagtitle",
 /*  12 */ "tagheadcontent ::= tagscript",
 /*  13 */ "tagheadcontent ::= tagstyle",
 /*  14 */ "tagheadcontent ::= taglink",
 /*  15 */ "tagheadcontent ::= tagmeta",
 /*  16 */ "tagbodycontents ::= tagbodycontents tagbodycontent",
 /*  17 */ "tagbodycontents ::= tagbodycontent",
 /*  18 */ "tagbodycontent ::= htsqls",
 /*  19 */ "tagbodycontent ::= tagtable",
 /*  20 */ "tagbodycontent ::= space",
 /*  21 */ "tagbodycontent ::= enter",
 /*  22 */ "tagbodycontent ::= htmltext",
 /*  23 */ "htsqls ::= tagdatablock",
 /*  24 */ "htsqls ::= tagcontrolblock",
 /*  25 */ "htsqls ::= tagdatalist",
 /*  26 */ "tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD",
 /*  27 */ "tagdoctype ::= TAG_DOCTYPE_HTML",
 /*  28 */ "tagtree ::= tagtreefullopen tagtreeblockclosefull",
 /*  29 */ "tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar",
 /*  30 */ "tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces",
 /*  31 */ "tagtreeopen ::= TAG_TREE_OPEN",
 /*  32 */ "tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE",
 /*  33 */ "tagtreeproperties ::= tagtreeproperties tagtreeproperty",
 /*  34 */ "tagtreeproperties ::= tagtreeproperty",
 /*  35 */ "tagtreeproperty ::= tagtreepropertyid PROPERTYDATA",
 /*  36 */ "tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT",
 /*  37 */ "tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull",
 /*  38 */ "tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar",
 /*  39 */ "tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces",
 /*  40 */ "tagdatalistopen ::= TAG_DATALIST_OPEN",
 /*  41 */ "tagdatalistblockclosefull ::= tagdatalistblockclose",
 /*  42 */ "tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE",
 /*  43 */ "datalistproperties ::= datalistproperties datalistproperty",
 /*  44 */ "datalistproperties ::= datalistproperty",
 /*  45 */ "datalistproperty ::= tagdatalistpropertyid PROPERTYDATA",
 /*  46 */ "tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT",
 /*  47 */ "datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA",
 /*  48 */ "tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT",
 /*  49 */ "tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull",
 /*  50 */ "tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull",
 /*  51 */ "tagcontrolblockfullopen ::= tagcontrolblockopen tagcontrolblockproperties tagclosechar",
 /*  52 */ "tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN",
 /*  53 */ "tagcontrolblockclosefull ::= tagcontrolblockblockclose",
 /*  54 */ "tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE",
 /*  55 */ "tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent",
 /*  56 */ "tagcontrolblockcontents ::= tagcontrolblockcontent",
 /*  57 */ "tagcontrolblockcontent ::= tagtree",
 /*  58 */ "tagcontrolblockcontent ::= space",
 /*  59 */ "tagcontrolblockcontent ::= htmltext",
 /*  60 */ "tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty",
 /*  61 */ "tagcontrolblockproperties ::= tagcontrolblockproperty",
 /*  62 */ "tagcontrolblockproperty ::= SPACE PROP_CONTROLBLOCK_BLOCK_NAME ASSIGMENT PROPERTYDATA",
 /*  63 */ "tagcontrolblockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA",
 /*  64 */ "tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull",
 /*  65 */ "tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull",
 /*  66 */ "tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar",
 /*  67 */ "tagdatablockopen ::= TAG_DATABLOCK_OPEN",
 /*  68 */ "tagdatablockblockclosefull ::= tagdatablockblockclose",
 /*  69 */ "tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE",
 /*  70 */ "tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent",
 /*  71 */ "tagdatablockcontents ::= tagdatablockcontent",
 /*  72 */ "tagdatablockcontent ::= tagtable",
 /*  73 */ "tagdatablockcontent ::= space",
 /*  74 */ "tagdatablockcontent ::= htmltext",
 /*  75 */ "tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty",
 /*  76 */ "tagdatablockproperties ::= tagdatablockproperty",
 /*  77 */ "tagdatablockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA",
 /*  78 */ "tagdatablockproperty ::= tagdatablockpropertyjoincondition PROPERTYDATA",
 /*  79 */ "tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION ASSIGMENT",
 /*  80 */ "tagdatablockproperty ::= tagdatablockpropertyconnectionname PROPERTYDATA",
 /*  81 */ "tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME ASSIGMENT",
 /*  82 */ "tagdatablockproperty ::= tagdatablockpropertyautogeneratedcolumns PROPERTYDATA",
 /*  83 */ "tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT",
 /*  84 */ "tagdatablockproperty ::= tagdatablockpropertyrecordcount PROPERTYDATA",
 /*  85 */ "tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT",
 /*  86 */ "tagdatablockproperty ::= tagdatablockpropertysourcename PROPERTYDATA",
 /*  87 */ "tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT",
 /*  88 */ "tagdatablockproperty ::= tagdatablockpropertyschemaname PROPERTYDATA",
 /*  89 */ "tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT",
 /*  90 */ "tagdatablockproperty ::= tagdatablockpropertyblockname PROPERTYDATA",
 /*  91 */ "tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT",
 /*  92 */ "tagdatablockproperty ::= tagdatablockpropertykeycolumnname PROPERTYDATA",
 /*  93 */ "tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT",
 /*  94 */ "tagdatablockproperty ::= tagdatablockpropertymasterblockname PROPERTYDATA",
 /*  95 */ "tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT",
 /*  96 */ "tagdatablockproperty ::= tagdatablockpropertyinsertallowed PROPERTYDATA",
 /*  97 */ "tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT",
 /*  98 */ "tagdatablockproperty ::= tagdatablockpropertydeleteallowed PROPERTYDATA",
 /*  99 */ "tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT",
 /* 100 */ "tagdatablockproperty ::= tagdatablockpropertyupdateallowed PROPERTYDATA",
 /* 101 */ "tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT",
 /* 102 */ "tagdatablockproperty ::= tagdatablockpropertywhereclause PROPERTYDATA",
 /* 103 */ "tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE ASSIGMENT",
 /* 104 */ "tagdatablockproperty ::= tagdatablockpropertyorderbyclause PROPERTYDATA",
 /* 105 */ "tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT",
 /* 106 */ "taginput ::= taginputfullopen",
 /* 107 */ "taginput ::= taginputfullopen taginputblockclosefull",
 /* 108 */ "taginputfullopen ::= taginputopen taginputproperties tagclosechar",
 /* 109 */ "taginputfullopen ::= taginputopen taginputproperties taginputshortclose",
 /* 110 */ "taginputshortclose ::= TAG_SHORT_CLOSE",
 /* 111 */ "taginputopen ::= TAG_INPUT_OPEN",
 /* 112 */ "taginputopen ::= TAG_SELECT_OPEN",
 /* 113 */ "taginputopen ::= TAG_TEXTAREA_OPEN",
 /* 114 */ "taginputblockclosefull ::= taginputblockclose",
 /* 115 */ "taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE",
 /* 116 */ "taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE",
 /* 117 */ "taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE",
 /* 118 */ "taginputproperties ::= taginputproperties taginputproperty",
 /* 119 */ "taginputproperties ::= taginputproperty",
 /* 120 */ "taginputproperty ::= taginputcheckedvalue PROPERTYDATA",
 /* 121 */ "taginputcheckedvalue ::= spaces PROP_INPUT_CHECKED_VALUE ASSIGMENT",
 /* 122 */ "taginputproperty ::= taginputuncheckedvalue PROPERTYDATA",
 /* 123 */ "taginputuncheckedvalue ::= spaces PROP_INPUT_UNCHECKED_VALUE ASSIGMENT",
 /* 124 */ "taginputproperty ::= taginputpropertyinputname PROPERTYDATA",
 /* 125 */ "taginputpropertyinputname ::= spaces PROP_INPUT_NAME ASSIGMENT",
 /* 126 */ "taginputproperty ::= taginputpropertysequencename PROPERTYDATA",
 /* 127 */ "taginputpropertysequencename ::= spaces PROP_INPUT_SEQUENCE_NAME ASSIGMENT",
 /* 128 */ "taginputproperty ::= taginputpropertysequenceschemaname PROPERTYDATA",
 /* 129 */ "taginputpropertysequenceschemaname ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT",
 /* 130 */ "taginputproperty ::= taginputpropertymasteritemname PROPERTYDATA",
 /* 131 */ "taginputpropertymasteritemname ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT",
 /* 132 */ "taginputproperty ::= taginputpropertyinputtype PROPERTYDATA",
 /* 133 */ "taginputpropertyinputtype ::= spaces PROP_INPUT_TYPE ASSIGMENT",
 /* 134 */ "taginputproperty ::= taginputpropertyinputvalue PROPERTYDATA",
 /* 135 */ "taginputpropertyinputvalue ::= spaces PROP_INPUT_VALUE ASSIGMENT",
 /* 136 */ "taginputproperty ::= taginputpropertydefaultvalue PROPERTYDATA",
 /* 137 */ "taginputpropertydefaultvalue ::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT",
 /* 138 */ "taginputproperty ::= taginputpropertycolumnname PROPERTYDATA",
 /* 139 */ "taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT",
 /* 140 */ "taginputproperty ::= taginputpropertyformatmask PROPERTYDATA",
 /* 141 */ "taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT",
 /* 142 */ "taginputproperty ::= taginputpropertydatatype PROPERTYDATA",
 /* 143 */ "taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT",
 /* 144 */ "taginputproperty ::= taginputpropertymaxlength PROPERTYDATA",
 /* 145 */ "taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT",
 /* 146 */ "taginputproperty ::= taginputpropertyinsertallowed PROPERTYDATA",
 /* 147 */ "taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED ASSIGMENT",
 /* 148 */ "taginputproperty ::= taginputpropertyupdateallowed PROPERTYDATA",
 /* 149 */ "taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT",
 /* 150 */ "taginputproperty ::= taginputpropertydatalistname PROPERTYDATA",
 /* 151 */ "taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT",
 /* 152 */ "taginputproperty ::= taginputpropertylookupitemname PROPERTYDATA",
 /* 153 */ "taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT",
 /* 154 */ "taginputproperty ::= taginputpropertylookupitemblockname PROPERTYDATA",
 /* 155 */ "taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT",
 /* 156 */ "taginputproperty ::= spaces PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 157 */ "tagtable ::= tagtablefullopen tagtableblockclosefull",
 /* 158 */ "tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull",
 /* 159 */ "tagtablefullopen ::= tagtableopen tagclosechar",
 /* 160 */ "tagtablefullopen ::= tagtableopen tagclosechar spaces",
 /* 161 */ "tagtablefullopen ::= tagtableopen tagproperties tagclosechar",
 /* 162 */ "tagtablefullopen ::= tagtableopen tagproperties tagclosechar spaces",
 /* 163 */ "tagtableopen ::= TAG_TABLE_OPEN",
 /* 164 */ "tagtableblockclosefull ::= tagtableblockclose",
 /* 165 */ "tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE",
 /* 166 */ "tablecontent ::= tagthead tagtbody tagtfoot",
 /* 167 */ "tablecontent ::= tagthead tagtfoot tagtbody",
 /* 168 */ "tablecontent ::= tagthead tagtbody",
 /* 169 */ "tablecontent ::= tagtbody tagtfoot",
 /* 170 */ "tablecontent ::= tagtbody",
 /* 171 */ "tagthead ::= tagtheadfullopen tagtheadblockclosefull",
 /* 172 */ "tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull",
 /* 173 */ "tagtheadfullopen ::= tagtheadopen tagclosechar",
 /* 174 */ "tagtheadfullopen ::= tagtheadopen tagclosechar spaces",
 /* 175 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 176 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces",
 /* 177 */ "tagtheadopen ::= TAG_THEAD_OPEN",
 /* 178 */ "tagtheadblockclosefull ::= tagtheadblockclose",
 /* 179 */ "tagtheadblockclosefull ::= tagtheadblockclose spaces",
 /* 180 */ "tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE",
 /* 181 */ "tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull",
 /* 182 */ "tagtfootfullopen ::= tagtfootopen tagclosechar",
 /* 183 */ "tagtfootfullopen ::= tagtfootopen tagclosechar spaces",
 /* 184 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar",
 /* 185 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar spaces",
 /* 186 */ "tagtfootopen ::= TAG_TFOOT_OPEN",
 /* 187 */ "tagtfootblockclosefull ::= tagtfootblockclose",
 /* 188 */ "tagtfootblockclosefull ::= tagtfootblockclose spaces",
 /* 189 */ "tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE",
 /* 190 */ "tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull",
 /* 191 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar",
 /* 192 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar spaces",
 /* 193 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar",
 /* 194 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar spaces",
 /* 195 */ "tagtbodyopen ::= TAG_TBODY_OPEN",
 /* 196 */ "tagtbodyblockclosefull ::= tagtbodyblockclose",
 /* 197 */ "tagtbodyblockclosefull ::= tagtbodyblockclose spaces",
 /* 198 */ "tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE",
 /* 199 */ "tagtablerows ::= tagtablerows tagtablerow",
 /* 200 */ "tagtablerows ::= tagtablerow",
 /* 201 */ "tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull",
 /* 202 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar",
 /* 203 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces",
 /* 204 */ "tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 205 */ "tagtablerowopen ::= TAG_TR_OPEN",
 /* 206 */ "tagtablerowblockclosefull ::= tagtablerowblockclose",
 /* 207 */ "tagtablerowblockclosefull ::= tagtablerowblockclose spaces",
 /* 208 */ "tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE",
 /* 209 */ "tagtablecols ::= tagtablecols tagtablecol",
 /* 210 */ "tagtablecols ::= tagtablecol",
 /* 211 */ "tagtablecol ::= tagtablecoltd",
 /* 212 */ "tagtablecol ::= tagtablecolth",
 /* 213 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull",
 /* 214 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull",
 /* 215 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull",
 /* 216 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull",
 /* 217 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull",
 /* 218 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar",
 /* 219 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar",
 /* 220 */ "tagtablecoltdopen ::= TAG_TD_OPEN",
 /* 221 */ "tagtablecoltdblockclosefull ::= tagtablecoltdblockclose",
 /* 222 */ "tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces",
 /* 223 */ "tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE",
 /* 224 */ "tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent",
 /* 225 */ "tagtablecolcontents ::= tagtablecolcontent",
 /* 226 */ "tagtablecolcontent ::= taginput",
 /* 227 */ "tagtablecolcontent ::= taginput spaces",
 /* 228 */ "tagtablecolcontent ::= htmltext",
 /* 229 */ "tagtablecolcontent ::= htmltext spaces",
 /* 230 */ "tagtablecolcontent ::= tagtable",
 /* 231 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull",
 /* 232 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull",
 /* 233 */ "tagtablecolthfullopen ::= tagtablecolthopen tagclosechar",
 /* 234 */ "tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 235 */ "tagtablecolthopen ::= TAG_TH_OPEN",
 /* 236 */ "tagtablecolthblockclosefull ::= tagtablecolthblockclose",
 /* 237 */ "tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces",
 /* 238 */ "tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE",
 /* 239 */ "tagtitle ::= tagtitlefullopen tagtitleblockclosefull",
 /* 240 */ "tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull",
 /* 241 */ "tagtitlefullopen ::= tagtitleopen tagclosechar",
 /* 242 */ "tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar",
 /* 243 */ "tagtitleblockclosefull ::= tagtitleblockclose",
 /* 244 */ "tagtitleopen ::= TAG_TITLE_OPEN",
 /* 245 */ "tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE",
 /* 246 */ "taglink ::= taglinkfullopen",
 /* 247 */ "taglink ::= taglinkfullopen taglinkblockclosefull",
 /* 248 */ "taglinkfullopen ::= taglinkopen tagproperties tagclosechar",
 /* 249 */ "taglinkfullopen ::= taglinkopen tagproperties tagshortclose",
 /* 250 */ "taglinkblockclosefull ::= taglinkblockclose",
 /* 251 */ "taglinkopen ::= TAG_LINK_OPEN",
 /* 252 */ "taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE",
 /* 253 */ "tagmeta ::= tagmetafullopen",
 /* 254 */ "tagmeta ::= tagmetafullopen tagmetablockclosefull",
 /* 255 */ "tagmetafullopen ::= tagmetaopen tagproperties tagclosechar",
 /* 256 */ "tagmetafullopen ::= tagmetaopen tagproperties tagshortclose",
 /* 257 */ "tagmetablockclosefull ::= tagmetablockclose",
 /* 258 */ "tagmetaopen ::= TAG_META_OPEN",
 /* 259 */ "tagmetablockclose ::= TAG_META_BLOCK_CLOSE",
 /* 260 */ "tagstyle ::= tagstylefullopen tagstyleblockclosefull",
 /* 261 */ "tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull",
 /* 262 */ "tagstylefullopen ::= tagstyleopen tagclosechar",
 /* 263 */ "tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar",
 /* 264 */ "tagstyleblockclosefull ::= tagstyleblockclose",
 /* 265 */ "tagstyleopen ::= TAG_STYLE_OPEN",
 /* 266 */ "tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE",
 /* 267 */ "tagstyleproperties ::= tagstyleproperties tagstyleproperty",
 /* 268 */ "tagstyleproperties ::= tagstyleproperty",
 /* 269 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA",
 /* 270 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA",
 /* 271 */ "tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 272 */ "tagscript ::= tagscriptfullopen tagscriptblockclosefull",
 /* 273 */ "tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull",
 /* 274 */ "tagscriptfullopen ::= tagscriptopen tagclosechar",
 /* 275 */ "tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar",
 /* 276 */ "tagscriptblockclosefull ::= tagscriptblockclose",
 /* 277 */ "tagscriptopen ::= TAG_SCRIPT_OPEN",
 /* 278 */ "tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE",
 /* 279 */ "tagscriptproperties ::= tagscriptproperties tagscriptproperty",
 /* 280 */ "tagscriptproperties ::= tagscriptproperty",
 /* 281 */ "tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA",
 /* 282 */ "tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT",
 /* 283 */ "tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA",
 /* 284 */ "tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT",
 /* 285 */ "taghtml ::= taghtmlfullopen taghtmlblockclosefull",
 /* 286 */ "taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull",
 /* 287 */ "taghtmlfullopen ::= taghtmlopen tagclosechar",
 /* 288 */ "taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar",
 /* 289 */ "taghtmlblockclosefull ::= taghtmlblockclose",
 /* 290 */ "taghtmlopen ::= TAG_HTML_OPEN",
 /* 291 */ "taghtmlblockclose ::= TAG_HTML_BLOCK_CLOSE",
 /* 292 */ "taghtmlcontents ::= taghtmlcontents taghtmlcontent",
 /* 293 */ "taghtmlcontents ::= taghtmlcontent",
 /* 294 */ "taghtmlcontent ::= space",
 /* 295 */ "taghtmlcontent ::= enter",
 /* 296 */ "taghtmlcontent ::= tagbody",
 /* 297 */ "taghtmlcontent ::= taghead tagbody",
 /* 298 */ "taghtmlcontent ::= taghead spaces_enters tagbody",
 /* 299 */ "tagbody ::= tagbodyfullopen tagbodyblockclosefull",
 /* 300 */ "tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull",
 /* 301 */ "tagbodyfullopen ::= tagbodyopen tagclosechar",
 /* 302 */ "tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar",
 /* 303 */ "tagbodyblockclosefull ::= tagbodyblockclose",
 /* 304 */ "tagbodyopen ::= TAG_BODY_OPEN",
 /* 305 */ "tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE",
 /* 306 */ "taghead ::= tagheadfullopen tagheadblockclosefull",
 /* 307 */ "taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull",
 /* 308 */ "tagheadfullopen ::= tagheadopen",
 /* 309 */ "tagheadblockclosefull ::= tagheadblockclose",
 /* 310 */ "tagheadopen ::= TAG_HEAD_OPEN",
 /* 311 */ "tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE",
 /* 312 */ "tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues",
 /* 313 */ "tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue",
 /* 314 */ "tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue",
 /* 315 */ "tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 316 */ "tagproperties ::= tagproperties tagproperty",
 /* 317 */ "tagproperties ::= tagproperty",
 /* 318 */ "tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 319 */ "tagclosechar ::= TAG_CLOSE",
 /* 320 */ "tagclosechar ::= SPACE TAG_CLOSE",
 /* 321 */ "tagshortclose ::= TAG_SHORT_CLOSE",
 /* 322 */ "htmlandspaces ::= htmlandspaces htmlandspace",
 /* 323 */ "htmlandspaces ::= htmlandspace",
 /* 324 */ "htmlandspace ::= HTMLTEXT",
 /* 325 */ "htmlandspace ::= SPACE",
 /* 326 */ "htmltext ::= HTMLTEXT",
 /* 327 */ "spaces_enters ::= spaces_enters spaces_enter",
 /* 328 */ "spaces_enters ::= spaces_enter",
 /* 329 */ "spaces_enter ::= space",
 /* 330 */ "spaces_enter ::= enter",
 /* 331 */ "spaces ::= spaces space",
 /* 332 */ "spaces ::= space",
 /* 333 */ "enters ::= enters enter",
 /* 334 */ "enters ::= enter",
 /* 335 */ "space ::= SPACE",
 /* 336 */ "enter ::= ENTER",
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
    case 17: /* PROPERTYID */
    case 18: /* TAG_DATABLOCK_OPEN */
    case 19: /* TAG_DATABLOCK_BLOCK_CLOSE */
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
    case 85: /* TAG_HTML_OPEN */
    case 86: /* TAG_HTML_BLOCK_CLOSE */
    case 87: /* TAG_BODY_OPEN */
    case 88: /* TAG_BODY_BLOCK_CLOSE */
    case 89: /* TAG_HEAD_OPEN */
    case 90: /* TAG_HEAD_BLOCK_CLOSE */
    case 91: /* TAG_CLOSE */
    case 92: /* HTMLTEXT */
    case 93: /* ENTER */
{
#line 52 "lemon.html.yy"

    if ((yypminor->yy0).tokenStr != NULL) {
        printf("%.*s", (yypminor->yy0).tokenStrLength, (yypminor->yy0).tokenStr);
    }

#line 1189 "lemon.html.c"
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
  { 95, 1 },
  { 97, 1 },
  { 96, 2 },
  { 96, 1 },
  { 98, 3 },
  { 98, 1 },
  { 102, 2 },
  { 102, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
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
  { 99, 1 },
  { 99, 1 },
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
  { 136, 3 },
  { 139, 1 },
  { 137, 1 },
  { 141, 1 },
  { 138, 2 },
  { 138, 1 },
  { 142, 1 },
  { 142, 1 },
  { 142, 1 },
  { 140, 2 },
  { 140, 1 },
  { 143, 4 },
  { 143, 4 },
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
  { 101, 2 },
  { 101, 3 },
  { 262, 2 },
  { 262, 3 },
  { 263, 1 },
  { 265, 1 },
  { 266, 1 },
  { 264, 2 },
  { 264, 1 },
  { 267, 1 },
  { 267, 1 },
  { 267, 1 },
  { 267, 2 },
  { 267, 3 },
  { 268, 2 },
  { 268, 3 },
  { 271, 2 },
  { 271, 3 },
  { 272, 1 },
  { 273, 1 },
  { 274, 1 },
  { 269, 2 },
  { 269, 3 },
  { 275, 1 },
  { 276, 1 },
  { 277, 1 },
  { 278, 1 },
  { 205, 1 },
  { 279, 2 },
  { 279, 1 },
  { 280, 3 },
  { 196, 2 },
  { 196, 1 },
  { 281, 4 },
  { 124, 1 },
  { 124, 2 },
  { 242, 1 },
  { 236, 2 },
  { 236, 1 },
  { 282, 1 },
  { 282, 1 },
  { 115, 1 },
  { 270, 2 },
  { 270, 1 },
  { 283, 1 },
  { 283, 1 },
  { 125, 2 },
  { 125, 1 },
  { 100, 2 },
  { 100, 1 },
  { 104, 1 },
  { 105, 1 },
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
      case 2: /* eof ::= END_OF_FILE */
{  yy_destructor(yypParser,1,&yymsp[0].minor);
#line 61 "lemon.html.yy"
{
}
#line 1836 "lemon.html.c"
}
        break;
      case 26: /* tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD */
{  yy_destructor(yypParser,2,&yymsp[0].minor);
#line 94 "lemon.html.yy"
{
}
#line 1844 "lemon.html.c"
}
        break;
      case 27: /* tagdoctype ::= TAG_DOCTYPE_HTML */
{  yy_destructor(yypParser,3,&yymsp[0].minor);
#line 96 "lemon.html.yy"
{
}
#line 1852 "lemon.html.c"
}
        break;
      case 31: /* tagtreeopen ::= TAG_TREE_OPEN */
{  yy_destructor(yypParser,4,&yymsp[0].minor);
#line 107 "lemon.html.yy"
{
}
#line 1860 "lemon.html.c"
}
        break;
      case 32: /* tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE */
{  yy_destructor(yypParser,5,&yymsp[0].minor);
#line 109 "lemon.html.yy"
{
}
#line 1868 "lemon.html.c"
}
        break;
      case 35: /* tagtreeproperty ::= tagtreepropertyid PROPERTYDATA */
      case 45: /* datalistproperty ::= tagdatalistpropertyid PROPERTYDATA */ yytestcase(yyruleno==45);
      case 47: /* datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA */ yytestcase(yyruleno==47);
      case 78: /* tagdatablockproperty ::= tagdatablockpropertyjoincondition PROPERTYDATA */ yytestcase(yyruleno==78);
      case 80: /* tagdatablockproperty ::= tagdatablockpropertyconnectionname PROPERTYDATA */ yytestcase(yyruleno==80);
      case 82: /* tagdatablockproperty ::= tagdatablockpropertyautogeneratedcolumns PROPERTYDATA */ yytestcase(yyruleno==82);
      case 84: /* tagdatablockproperty ::= tagdatablockpropertyrecordcount PROPERTYDATA */ yytestcase(yyruleno==84);
      case 86: /* tagdatablockproperty ::= tagdatablockpropertysourcename PROPERTYDATA */ yytestcase(yyruleno==86);
      case 88: /* tagdatablockproperty ::= tagdatablockpropertyschemaname PROPERTYDATA */ yytestcase(yyruleno==88);
      case 90: /* tagdatablockproperty ::= tagdatablockpropertyblockname PROPERTYDATA */ yytestcase(yyruleno==90);
      case 92: /* tagdatablockproperty ::= tagdatablockpropertykeycolumnname PROPERTYDATA */ yytestcase(yyruleno==92);
      case 94: /* tagdatablockproperty ::= tagdatablockpropertymasterblockname PROPERTYDATA */ yytestcase(yyruleno==94);
      case 96: /* tagdatablockproperty ::= tagdatablockpropertyinsertallowed PROPERTYDATA */ yytestcase(yyruleno==96);
      case 98: /* tagdatablockproperty ::= tagdatablockpropertydeleteallowed PROPERTYDATA */ yytestcase(yyruleno==98);
      case 100: /* tagdatablockproperty ::= tagdatablockpropertyupdateallowed PROPERTYDATA */ yytestcase(yyruleno==100);
      case 102: /* tagdatablockproperty ::= tagdatablockpropertywhereclause PROPERTYDATA */ yytestcase(yyruleno==102);
      case 104: /* tagdatablockproperty ::= tagdatablockpropertyorderbyclause PROPERTYDATA */ yytestcase(yyruleno==104);
      case 120: /* taginputproperty ::= taginputcheckedvalue PROPERTYDATA */ yytestcase(yyruleno==120);
      case 122: /* taginputproperty ::= taginputuncheckedvalue PROPERTYDATA */ yytestcase(yyruleno==122);
      case 124: /* taginputproperty ::= taginputpropertyinputname PROPERTYDATA */ yytestcase(yyruleno==124);
      case 126: /* taginputproperty ::= taginputpropertysequencename PROPERTYDATA */ yytestcase(yyruleno==126);
      case 128: /* taginputproperty ::= taginputpropertysequenceschemaname PROPERTYDATA */ yytestcase(yyruleno==128);
      case 130: /* taginputproperty ::= taginputpropertymasteritemname PROPERTYDATA */ yytestcase(yyruleno==130);
      case 132: /* taginputproperty ::= taginputpropertyinputtype PROPERTYDATA */ yytestcase(yyruleno==132);
      case 134: /* taginputproperty ::= taginputpropertyinputvalue PROPERTYDATA */ yytestcase(yyruleno==134);
      case 136: /* taginputproperty ::= taginputpropertydefaultvalue PROPERTYDATA */ yytestcase(yyruleno==136);
      case 138: /* taginputproperty ::= taginputpropertycolumnname PROPERTYDATA */ yytestcase(yyruleno==138);
      case 140: /* taginputproperty ::= taginputpropertyformatmask PROPERTYDATA */ yytestcase(yyruleno==140);
      case 142: /* taginputproperty ::= taginputpropertydatatype PROPERTYDATA */ yytestcase(yyruleno==142);
      case 144: /* taginputproperty ::= taginputpropertymaxlength PROPERTYDATA */ yytestcase(yyruleno==144);
      case 146: /* taginputproperty ::= taginputpropertyinsertallowed PROPERTYDATA */ yytestcase(yyruleno==146);
      case 148: /* taginputproperty ::= taginputpropertyupdateallowed PROPERTYDATA */ yytestcase(yyruleno==148);
      case 150: /* taginputproperty ::= taginputpropertydatalistname PROPERTYDATA */ yytestcase(yyruleno==150);
      case 152: /* taginputproperty ::= taginputpropertylookupitemname PROPERTYDATA */ yytestcase(yyruleno==152);
      case 154: /* taginputproperty ::= taginputpropertylookupitemblockname PROPERTYDATA */ yytestcase(yyruleno==154);
      case 281: /* tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA */ yytestcase(yyruleno==281);
      case 283: /* tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA */ yytestcase(yyruleno==283);
#line 114 "lemon.html.yy"
{
}
#line 1911 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 36: /* tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 116 "lemon.html.yy"
{
}
#line 1919 "lemon.html.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 40: /* tagdatalistopen ::= TAG_DATALIST_OPEN */
{  yy_destructor(yypParser,10,&yymsp[0].minor);
#line 126 "lemon.html.yy"
{
}
#line 1929 "lemon.html.c"
}
        break;
      case 42: /* tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE */
{  yy_destructor(yypParser,11,&yymsp[0].minor);
#line 130 "lemon.html.yy"
{
}
#line 1937 "lemon.html.c"
}
        break;
      case 46: /* tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 137 "lemon.html.yy"
{
}
#line 1945 "lemon.html.c"
  yy_destructor(yypParser,12,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 48: /* tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 141 "lemon.html.yy"
{
}
#line 1955 "lemon.html.c"
  yy_destructor(yypParser,13,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 52: /* tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN */
{  yy_destructor(yypParser,14,&yymsp[0].minor);
#line 153 "lemon.html.yy"
{
}
#line 1965 "lemon.html.c"
}
        break;
      case 54: /* tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 156 "lemon.html.yy"
{
}
#line 1973 "lemon.html.c"
}
        break;
      case 62: /* tagcontrolblockproperty ::= SPACE PROP_CONTROLBLOCK_BLOCK_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,7,&yymsp[-3].minor);
#line 169 "lemon.html.yy"
{
}
#line 1981 "lemon.html.c"
  yy_destructor(yypParser,16,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 63: /* tagcontrolblockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA */
      case 77: /* tagdatablockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==77);
{  yy_destructor(yypParser,7,&yymsp[-3].minor);
#line 171 "lemon.html.yy"
{
}
#line 1993 "lemon.html.c"
  yy_destructor(yypParser,17,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 67: /* tagdatablockopen ::= TAG_DATABLOCK_OPEN */
{  yy_destructor(yypParser,18,&yymsp[0].minor);
#line 183 "lemon.html.yy"
{
}
#line 2004 "lemon.html.c"
}
        break;
      case 69: /* tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE */
{  yy_destructor(yypParser,19,&yymsp[0].minor);
#line 187 "lemon.html.yy"
{
}
#line 2012 "lemon.html.c"
}
        break;
      case 79: /* tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 205 "lemon.html.yy"
{
}
#line 2020 "lemon.html.c"
  yy_destructor(yypParser,20,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 81: /* tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 210 "lemon.html.yy"
{
}
#line 2030 "lemon.html.c"
  yy_destructor(yypParser,21,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 83: /* tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 215 "lemon.html.yy"
{
}
#line 2040 "lemon.html.c"
  yy_destructor(yypParser,22,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 85: /* tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 219 "lemon.html.yy"
{
}
#line 2050 "lemon.html.c"
  yy_destructor(yypParser,23,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 87: /* tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 223 "lemon.html.yy"
{
}
#line 2060 "lemon.html.c"
  yy_destructor(yypParser,24,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 89: /* tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 228 "lemon.html.yy"
{
}
#line 2070 "lemon.html.c"
  yy_destructor(yypParser,25,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 91: /* tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 232 "lemon.html.yy"
{
}
#line 2080 "lemon.html.c"
  yy_destructor(yypParser,26,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 93: /* tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 236 "lemon.html.yy"
{
}
#line 2090 "lemon.html.c"
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 95: /* tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 240 "lemon.html.yy"
{
}
#line 2100 "lemon.html.c"
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 97: /* tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 244 "lemon.html.yy"
{
}
#line 2110 "lemon.html.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 99: /* tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 248 "lemon.html.yy"
{
}
#line 2120 "lemon.html.c"
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 101: /* tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 252 "lemon.html.yy"
{
}
#line 2130 "lemon.html.c"
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 103: /* tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 257 "lemon.html.yy"
{
}
#line 2140 "lemon.html.c"
  yy_destructor(yypParser,32,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 105: /* tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 261 "lemon.html.yy"
{
}
#line 2150 "lemon.html.c"
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 110: /* taginputshortclose ::= TAG_SHORT_CLOSE */
      case 321: /* tagshortclose ::= TAG_SHORT_CLOSE */ yytestcase(yyruleno==321);
{  yy_destructor(yypParser,34,&yymsp[0].minor);
#line 275 "lemon.html.yy"
{
}
#line 2161 "lemon.html.c"
}
        break;
      case 111: /* taginputopen ::= TAG_INPUT_OPEN */
{  yy_destructor(yypParser,35,&yymsp[0].minor);
#line 278 "lemon.html.yy"
{
}
#line 2169 "lemon.html.c"
}
        break;
      case 112: /* taginputopen ::= TAG_SELECT_OPEN */
{  yy_destructor(yypParser,36,&yymsp[0].minor);
#line 280 "lemon.html.yy"
{
}
#line 2177 "lemon.html.c"
}
        break;
      case 113: /* taginputopen ::= TAG_TEXTAREA_OPEN */
{  yy_destructor(yypParser,37,&yymsp[0].minor);
#line 282 "lemon.html.yy"
{
}
#line 2185 "lemon.html.c"
}
        break;
      case 115: /* taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE */
{  yy_destructor(yypParser,38,&yymsp[0].minor);
#line 286 "lemon.html.yy"
{
}
#line 2193 "lemon.html.c"
}
        break;
      case 116: /* taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE */
{  yy_destructor(yypParser,39,&yymsp[0].minor);
#line 288 "lemon.html.yy"
{
}
#line 2201 "lemon.html.c"
}
        break;
      case 117: /* taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE */
{  yy_destructor(yypParser,40,&yymsp[0].minor);
#line 290 "lemon.html.yy"
{
}
#line 2209 "lemon.html.c"
}
        break;
      case 121: /* taginputcheckedvalue ::= spaces PROP_INPUT_CHECKED_VALUE ASSIGMENT */
#line 298 "lemon.html.yy"
{
}
#line 2216 "lemon.html.c"
  yy_destructor(yypParser,41,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 123: /* taginputuncheckedvalue ::= spaces PROP_INPUT_UNCHECKED_VALUE ASSIGMENT */
#line 302 "lemon.html.yy"
{
}
#line 2224 "lemon.html.c"
  yy_destructor(yypParser,42,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 125: /* taginputpropertyinputname ::= spaces PROP_INPUT_NAME ASSIGMENT */
#line 306 "lemon.html.yy"
{
}
#line 2232 "lemon.html.c"
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 127: /* taginputpropertysequencename ::= spaces PROP_INPUT_SEQUENCE_NAME ASSIGMENT */
#line 310 "lemon.html.yy"
{
}
#line 2240 "lemon.html.c"
  yy_destructor(yypParser,44,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 129: /* taginputpropertysequenceschemaname ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT */
#line 314 "lemon.html.yy"
{
}
#line 2248 "lemon.html.c"
  yy_destructor(yypParser,45,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 131: /* taginputpropertymasteritemname ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT */
#line 319 "lemon.html.yy"
{
}
#line 2256 "lemon.html.c"
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 133: /* taginputpropertyinputtype ::= spaces PROP_INPUT_TYPE ASSIGMENT */
#line 323 "lemon.html.yy"
{
}
#line 2264 "lemon.html.c"
  yy_destructor(yypParser,47,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 135: /* taginputpropertyinputvalue ::= spaces PROP_INPUT_VALUE ASSIGMENT */
#line 327 "lemon.html.yy"
{
}
#line 2272 "lemon.html.c"
  yy_destructor(yypParser,48,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 137: /* taginputpropertydefaultvalue ::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT */
#line 331 "lemon.html.yy"
{
}
#line 2280 "lemon.html.c"
  yy_destructor(yypParser,49,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 139: /* taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT */
#line 335 "lemon.html.yy"
{
}
#line 2288 "lemon.html.c"
  yy_destructor(yypParser,50,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 141: /* taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT */
#line 339 "lemon.html.yy"
{
}
#line 2296 "lemon.html.c"
  yy_destructor(yypParser,51,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 143: /* taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT */
#line 343 "lemon.html.yy"
{
}
#line 2304 "lemon.html.c"
  yy_destructor(yypParser,52,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 145: /* taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT */
#line 347 "lemon.html.yy"
{
}
#line 2312 "lemon.html.c"
  yy_destructor(yypParser,53,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 147: /* taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED ASSIGMENT */
#line 351 "lemon.html.yy"
{
}
#line 2320 "lemon.html.c"
  yy_destructor(yypParser,54,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 149: /* taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT */
#line 355 "lemon.html.yy"
{
}
#line 2328 "lemon.html.c"
  yy_destructor(yypParser,55,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 151: /* taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT */
#line 359 "lemon.html.yy"
{
}
#line 2336 "lemon.html.c"
  yy_destructor(yypParser,56,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 153: /* taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT */
#line 363 "lemon.html.yy"
{
}
#line 2344 "lemon.html.c"
  yy_destructor(yypParser,57,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 155: /* taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT */
#line 367 "lemon.html.yy"
{
}
#line 2352 "lemon.html.c"
  yy_destructor(yypParser,58,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 156: /* taginputproperty ::= spaces PROPERTYID ASSIGMENT PROPERTYDATA */
      case 271: /* tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==271);
      case 318: /* tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==318);
#line 369 "lemon.html.yy"
{
}
#line 2362 "lemon.html.c"
  yy_destructor(yypParser,17,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 163: /* tagtableopen ::= TAG_TABLE_OPEN */
{  yy_destructor(yypParser,59,&yymsp[0].minor);
#line 384 "lemon.html.yy"
{
}
#line 2372 "lemon.html.c"
}
        break;
      case 165: /* tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,60,&yymsp[0].minor);
#line 388 "lemon.html.yy"
{
}
#line 2380 "lemon.html.c"
}
        break;
      case 177: /* tagtheadopen ::= TAG_THEAD_OPEN */
{  yy_destructor(yypParser,61,&yymsp[0].minor);
#line 411 "lemon.html.yy"
{
}
#line 2388 "lemon.html.c"
}
        break;
      case 180: /* tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,62,&yymsp[0].minor);
#line 416 "lemon.html.yy"
{
}
#line 2396 "lemon.html.c"
}
        break;
      case 186: /* tagtfootopen ::= TAG_TFOOT_OPEN */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 429 "lemon.html.yy"
{
}
#line 2404 "lemon.html.c"
}
        break;
      case 189: /* tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE */
{  yy_destructor(yypParser,64,&yymsp[0].minor);
#line 434 "lemon.html.yy"
{
}
#line 2412 "lemon.html.c"
}
        break;
      case 195: /* tagtbodyopen ::= TAG_TBODY_OPEN */
{  yy_destructor(yypParser,65,&yymsp[0].minor);
#line 447 "lemon.html.yy"
{
}
#line 2420 "lemon.html.c"
}
        break;
      case 198: /* tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,66,&yymsp[0].minor);
#line 452 "lemon.html.yy"
{
}
#line 2428 "lemon.html.c"
}
        break;
      case 205: /* tagtablerowopen ::= TAG_TR_OPEN */
{  yy_destructor(yypParser,67,&yymsp[0].minor);
#line 468 "lemon.html.yy"
{
}
#line 2436 "lemon.html.c"
}
        break;
      case 208: /* tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE */
{  yy_destructor(yypParser,68,&yymsp[0].minor);
#line 473 "lemon.html.yy"
{
}
#line 2444 "lemon.html.c"
}
        break;
      case 220: /* tagtablecoltdopen ::= TAG_TD_OPEN */
{  yy_destructor(yypParser,69,&yymsp[0].minor);
#line 496 "lemon.html.yy"
{
}
#line 2452 "lemon.html.c"
}
        break;
      case 223: /* tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE */
{  yy_destructor(yypParser,70,&yymsp[0].minor);
#line 501 "lemon.html.yy"
{
}
#line 2460 "lemon.html.c"
}
        break;
      case 235: /* tagtablecolthopen ::= TAG_TH_OPEN */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 523 "lemon.html.yy"
{
}
#line 2468 "lemon.html.c"
}
        break;
      case 238: /* tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE */
{  yy_destructor(yypParser,72,&yymsp[0].minor);
#line 528 "lemon.html.yy"
{
}
#line 2476 "lemon.html.c"
}
        break;
      case 244: /* tagtitleopen ::= TAG_TITLE_OPEN */
{  yy_destructor(yypParser,73,&yymsp[0].minor);
#line 541 "lemon.html.yy"
{
}
#line 2484 "lemon.html.c"
}
        break;
      case 245: /* tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,74,&yymsp[0].minor);
#line 542 "lemon.html.yy"
{
}
#line 2492 "lemon.html.c"
}
        break;
      case 251: /* taglinkopen ::= TAG_LINK_OPEN */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 555 "lemon.html.yy"
{
}
#line 2500 "lemon.html.c"
}
        break;
      case 252: /* taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE */
{  yy_destructor(yypParser,76,&yymsp[0].minor);
#line 556 "lemon.html.yy"
{
}
#line 2508 "lemon.html.c"
}
        break;
      case 258: /* tagmetaopen ::= TAG_META_OPEN */
{  yy_destructor(yypParser,77,&yymsp[0].minor);
#line 570 "lemon.html.yy"
{
}
#line 2516 "lemon.html.c"
}
        break;
      case 259: /* tagmetablockclose ::= TAG_META_BLOCK_CLOSE */
{  yy_destructor(yypParser,78,&yymsp[0].minor);
#line 571 "lemon.html.yy"
{
}
#line 2524 "lemon.html.c"
}
        break;
      case 265: /* tagstyleopen ::= TAG_STYLE_OPEN */
{  yy_destructor(yypParser,79,&yymsp[0].minor);
#line 585 "lemon.html.yy"
{
}
#line 2532 "lemon.html.c"
}
        break;
      case 266: /* tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,80,&yymsp[0].minor);
#line 586 "lemon.html.yy"
{
}
#line 2540 "lemon.html.c"
}
        break;
      case 269: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA */
#line 592 "lemon.html.yy"
{
}
#line 2547 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 270: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA */
#line 593 "lemon.html.yy"
{
}
#line 2556 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 277: /* tagscriptopen ::= TAG_SCRIPT_OPEN */
{  yy_destructor(yypParser,83,&yymsp[0].minor);
#line 608 "lemon.html.yy"
{
}
#line 2566 "lemon.html.c"
}
        break;
      case 278: /* tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE */
{  yy_destructor(yypParser,84,&yymsp[0].minor);
#line 609 "lemon.html.yy"
{
}
#line 2574 "lemon.html.c"
}
        break;
      case 282: /* tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 618 "lemon.html.yy"
{
}
#line 2582 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 284: /* tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 622 "lemon.html.yy"
{
}
#line 2592 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 290: /* taghtmlopen ::= TAG_HTML_OPEN */
{  yy_destructor(yypParser,85,&yymsp[0].minor);
#line 635 "lemon.html.yy"
{
}
#line 2602 "lemon.html.c"
}
        break;
      case 291: /* taghtmlblockclose ::= TAG_HTML_BLOCK_CLOSE */
{  yy_destructor(yypParser,86,&yymsp[0].minor);
#line 637 "lemon.html.yy"
{
}
#line 2610 "lemon.html.c"
}
        break;
      case 304: /* tagbodyopen ::= TAG_BODY_OPEN */
{  yy_destructor(yypParser,87,&yymsp[0].minor);
#line 662 "lemon.html.yy"
{
}
#line 2618 "lemon.html.c"
}
        break;
      case 305: /* tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,88,&yymsp[0].minor);
#line 664 "lemon.html.yy"
{
}
#line 2626 "lemon.html.c"
}
        break;
      case 310: /* tagheadopen ::= TAG_HEAD_OPEN */
{  yy_destructor(yypParser,89,&yymsp[0].minor);
#line 679 "lemon.html.yy"
{
}
#line 2634 "lemon.html.c"
}
        break;
      case 311: /* tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,90,&yymsp[0].minor);
#line 681 "lemon.html.yy"
{
}
#line 2642 "lemon.html.c"
}
        break;
      case 315: /* tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,17,&yymsp[-2].minor);
#line 695 "lemon.html.yy"
{
}
#line 2650 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 319: /* tagclosechar ::= TAG_CLOSE */
{  yy_destructor(yypParser,91,&yymsp[0].minor);
#line 709 "lemon.html.yy"
{
}
#line 2660 "lemon.html.c"
}
        break;
      case 320: /* tagclosechar ::= SPACE TAG_CLOSE */
{  yy_destructor(yypParser,7,&yymsp[-1].minor);
#line 710 "lemon.html.yy"
{
}
#line 2668 "lemon.html.c"
  yy_destructor(yypParser,91,&yymsp[0].minor);
}
        break;
      case 324: /* htmlandspace ::= HTMLTEXT */
      case 326: /* htmltext ::= HTMLTEXT */ yytestcase(yyruleno==326);
{  yy_destructor(yypParser,92,&yymsp[0].minor);
#line 722 "lemon.html.yy"
{
}
#line 2678 "lemon.html.c"
}
        break;
      case 325: /* htmlandspace ::= SPACE */
      case 335: /* space ::= SPACE */ yytestcase(yyruleno==335);
{  yy_destructor(yypParser,7,&yymsp[0].minor);
#line 723 "lemon.html.yy"
{
}
#line 2687 "lemon.html.c"
}
        break;
      case 336: /* enter ::= ENTER */
{  yy_destructor(yypParser,93,&yymsp[0].minor);
#line 748 "lemon.html.yy"
{
}
#line 2695 "lemon.html.c"
}
        break;
      default:
      /* (0) start ::= expressions */ yytestcase(yyruleno==0);
      /* (1) start ::= eof */ yytestcase(yyruleno==1);
      /* (3) expressions ::= expressions expression */ yytestcase(yyruleno==3);
      /* (4) expressions ::= expression (OPTIMIZED OUT) */ assert(yyruleno!=4);
      /* (5) expression ::= tagdoctype enters taghtml */ yytestcase(yyruleno==5);
      /* (6) expression ::= taghtml (OPTIMIZED OUT) */ assert(yyruleno!=6);
      /* (7) tagheadcontents ::= tagheadcontents tagheadcontent */ yytestcase(yyruleno==7);
      /* (8) tagheadcontents ::= tagheadcontent (OPTIMIZED OUT) */ assert(yyruleno!=8);
      /* (9) tagheadcontent ::= space (OPTIMIZED OUT) */ assert(yyruleno!=9);
      /* (10) tagheadcontent ::= enter (OPTIMIZED OUT) */ assert(yyruleno!=10);
      /* (11) tagheadcontent ::= tagtitle (OPTIMIZED OUT) */ assert(yyruleno!=11);
      /* (12) tagheadcontent ::= tagscript (OPTIMIZED OUT) */ assert(yyruleno!=12);
      /* (13) tagheadcontent ::= tagstyle (OPTIMIZED OUT) */ assert(yyruleno!=13);
      /* (14) tagheadcontent ::= taglink (OPTIMIZED OUT) */ assert(yyruleno!=14);
      /* (15) tagheadcontent ::= tagmeta (OPTIMIZED OUT) */ assert(yyruleno!=15);
      /* (16) tagbodycontents ::= tagbodycontents tagbodycontent */ yytestcase(yyruleno==16);
      /* (17) tagbodycontents ::= tagbodycontent (OPTIMIZED OUT) */ assert(yyruleno!=17);
      /* (18) tagbodycontent ::= htsqls (OPTIMIZED OUT) */ assert(yyruleno!=18);
      /* (19) tagbodycontent ::= tagtable (OPTIMIZED OUT) */ assert(yyruleno!=19);
      /* (20) tagbodycontent ::= space (OPTIMIZED OUT) */ assert(yyruleno!=20);
      /* (21) tagbodycontent ::= enter (OPTIMIZED OUT) */ assert(yyruleno!=21);
      /* (22) tagbodycontent ::= htmltext (OPTIMIZED OUT) */ assert(yyruleno!=22);
      /* (23) htsqls ::= tagdatablock (OPTIMIZED OUT) */ assert(yyruleno!=23);
      /* (24) htsqls ::= tagcontrolblock (OPTIMIZED OUT) */ assert(yyruleno!=24);
      /* (25) htsqls ::= tagdatalist (OPTIMIZED OUT) */ assert(yyruleno!=25);
      /* (28) tagtree ::= tagtreefullopen tagtreeblockclosefull */ yytestcase(yyruleno==28);
      /* (29) tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar */ yytestcase(yyruleno==29);
      /* (30) tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces */ yytestcase(yyruleno==30);
      /* (33) tagtreeproperties ::= tagtreeproperties tagtreeproperty */ yytestcase(yyruleno==33);
      /* (34) tagtreeproperties ::= tagtreeproperty (OPTIMIZED OUT) */ assert(yyruleno!=34);
      /* (37) tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull */ yytestcase(yyruleno==37);
      /* (38) tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar */ yytestcase(yyruleno==38);
      /* (39) tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces */ yytestcase(yyruleno==39);
      /* (41) tagdatalistblockclosefull ::= tagdatalistblockclose (OPTIMIZED OUT) */ assert(yyruleno!=41);
      /* (43) datalistproperties ::= datalistproperties datalistproperty */ yytestcase(yyruleno==43);
      /* (44) datalistproperties ::= datalistproperty (OPTIMIZED OUT) */ assert(yyruleno!=44);
      /* (49) tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull */ yytestcase(yyruleno==49);
      /* (50) tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull */ yytestcase(yyruleno==50);
      /* (51) tagcontrolblockfullopen ::= tagcontrolblockopen tagcontrolblockproperties tagclosechar */ yytestcase(yyruleno==51);
      /* (53) tagcontrolblockclosefull ::= tagcontrolblockblockclose (OPTIMIZED OUT) */ assert(yyruleno!=53);
      /* (55) tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent */ yytestcase(yyruleno==55);
      /* (56) tagcontrolblockcontents ::= tagcontrolblockcontent (OPTIMIZED OUT) */ assert(yyruleno!=56);
      /* (57) tagcontrolblockcontent ::= tagtree (OPTIMIZED OUT) */ assert(yyruleno!=57);
      /* (58) tagcontrolblockcontent ::= space (OPTIMIZED OUT) */ assert(yyruleno!=58);
      /* (59) tagcontrolblockcontent ::= htmltext (OPTIMIZED OUT) */ assert(yyruleno!=59);
      /* (60) tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty */ yytestcase(yyruleno==60);
      /* (61) tagcontrolblockproperties ::= tagcontrolblockproperty (OPTIMIZED OUT) */ assert(yyruleno!=61);
      /* (64) tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull */ yytestcase(yyruleno==64);
      /* (65) tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull */ yytestcase(yyruleno==65);
      /* (66) tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar */ yytestcase(yyruleno==66);
      /* (68) tagdatablockblockclosefull ::= tagdatablockblockclose (OPTIMIZED OUT) */ assert(yyruleno!=68);
      /* (70) tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent */ yytestcase(yyruleno==70);
      /* (71) tagdatablockcontents ::= tagdatablockcontent (OPTIMIZED OUT) */ assert(yyruleno!=71);
      /* (72) tagdatablockcontent ::= tagtable (OPTIMIZED OUT) */ assert(yyruleno!=72);
      /* (73) tagdatablockcontent ::= space (OPTIMIZED OUT) */ assert(yyruleno!=73);
      /* (74) tagdatablockcontent ::= htmltext (OPTIMIZED OUT) */ assert(yyruleno!=74);
      /* (75) tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty */ yytestcase(yyruleno==75);
      /* (76) tagdatablockproperties ::= tagdatablockproperty (OPTIMIZED OUT) */ assert(yyruleno!=76);
      /* (106) taginput ::= taginputfullopen */ yytestcase(yyruleno==106);
      /* (107) taginput ::= taginputfullopen taginputblockclosefull */ yytestcase(yyruleno==107);
      /* (108) taginputfullopen ::= taginputopen taginputproperties tagclosechar */ yytestcase(yyruleno==108);
      /* (109) taginputfullopen ::= taginputopen taginputproperties taginputshortclose */ yytestcase(yyruleno==109);
      /* (114) taginputblockclosefull ::= taginputblockclose (OPTIMIZED OUT) */ assert(yyruleno!=114);
      /* (118) taginputproperties ::= taginputproperties taginputproperty */ yytestcase(yyruleno==118);
      /* (119) taginputproperties ::= taginputproperty (OPTIMIZED OUT) */ assert(yyruleno!=119);
      /* (157) tagtable ::= tagtablefullopen tagtableblockclosefull */ yytestcase(yyruleno==157);
      /* (158) tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull */ yytestcase(yyruleno==158);
      /* (159) tagtablefullopen ::= tagtableopen tagclosechar */ yytestcase(yyruleno==159);
      /* (160) tagtablefullopen ::= tagtableopen tagclosechar spaces */ yytestcase(yyruleno==160);
      /* (161) tagtablefullopen ::= tagtableopen tagproperties tagclosechar */ yytestcase(yyruleno==161);
      /* (162) tagtablefullopen ::= tagtableopen tagproperties tagclosechar spaces */ yytestcase(yyruleno==162);
      /* (164) tagtableblockclosefull ::= tagtableblockclose (OPTIMIZED OUT) */ assert(yyruleno!=164);
      /* (166) tablecontent ::= tagthead tagtbody tagtfoot */ yytestcase(yyruleno==166);
      /* (167) tablecontent ::= tagthead tagtfoot tagtbody */ yytestcase(yyruleno==167);
      /* (168) tablecontent ::= tagthead tagtbody */ yytestcase(yyruleno==168);
      /* (169) tablecontent ::= tagtbody tagtfoot */ yytestcase(yyruleno==169);
      /* (170) tablecontent ::= tagtbody */ yytestcase(yyruleno==170);
      /* (171) tagthead ::= tagtheadfullopen tagtheadblockclosefull */ yytestcase(yyruleno==171);
      /* (172) tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull */ yytestcase(yyruleno==172);
      /* (173) tagtheadfullopen ::= tagtheadopen tagclosechar */ yytestcase(yyruleno==173);
      /* (174) tagtheadfullopen ::= tagtheadopen tagclosechar spaces */ yytestcase(yyruleno==174);
      /* (175) tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar */ yytestcase(yyruleno==175);
      /* (176) tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces */ yytestcase(yyruleno==176);
      /* (178) tagtheadblockclosefull ::= tagtheadblockclose */ yytestcase(yyruleno==178);
      /* (179) tagtheadblockclosefull ::= tagtheadblockclose spaces */ yytestcase(yyruleno==179);
      /* (181) tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull */ yytestcase(yyruleno==181);
      /* (182) tagtfootfullopen ::= tagtfootopen tagclosechar */ yytestcase(yyruleno==182);
      /* (183) tagtfootfullopen ::= tagtfootopen tagclosechar spaces */ yytestcase(yyruleno==183);
      /* (184) tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar */ yytestcase(yyruleno==184);
      /* (185) tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar spaces */ yytestcase(yyruleno==185);
      /* (187) tagtfootblockclosefull ::= tagtfootblockclose */ yytestcase(yyruleno==187);
      /* (188) tagtfootblockclosefull ::= tagtfootblockclose spaces */ yytestcase(yyruleno==188);
      /* (190) tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull */ yytestcase(yyruleno==190);
      /* (191) tagtbodyfullopen ::= tagtbodyopen tagclosechar */ yytestcase(yyruleno==191);
      /* (192) tagtbodyfullopen ::= tagtbodyopen tagclosechar spaces */ yytestcase(yyruleno==192);
      /* (193) tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar */ yytestcase(yyruleno==193);
      /* (194) tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar spaces */ yytestcase(yyruleno==194);
      /* (196) tagtbodyblockclosefull ::= tagtbodyblockclose */ yytestcase(yyruleno==196);
      /* (197) tagtbodyblockclosefull ::= tagtbodyblockclose spaces */ yytestcase(yyruleno==197);
      /* (199) tagtablerows ::= tagtablerows tagtablerow */ yytestcase(yyruleno==199);
      /* (200) tagtablerows ::= tagtablerow (OPTIMIZED OUT) */ assert(yyruleno!=200);
      /* (201) tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull */ yytestcase(yyruleno==201);
      /* (202) tagtablerowfullopen ::= tagtablerowopen tagclosechar */ yytestcase(yyruleno==202);
      /* (203) tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces */ yytestcase(yyruleno==203);
      /* (204) tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar */ yytestcase(yyruleno==204);
      /* (206) tagtablerowblockclosefull ::= tagtablerowblockclose */ yytestcase(yyruleno==206);
      /* (207) tagtablerowblockclosefull ::= tagtablerowblockclose spaces */ yytestcase(yyruleno==207);
      /* (209) tagtablecols ::= tagtablecols tagtablecol */ yytestcase(yyruleno==209);
      /* (210) tagtablecols ::= tagtablecol (OPTIMIZED OUT) */ assert(yyruleno!=210);
      /* (211) tagtablecol ::= tagtablecoltd (OPTIMIZED OUT) */ assert(yyruleno!=211);
      /* (212) tagtablecol ::= tagtablecolth (OPTIMIZED OUT) */ assert(yyruleno!=212);
      /* (213) tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull */ yytestcase(yyruleno==213);
      /* (214) tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull */ yytestcase(yyruleno==214);
      /* (215) tagtablecoltd ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull */ yytestcase(yyruleno==215);
      /* (216) tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull */ yytestcase(yyruleno==216);
      /* (217) tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull */ yytestcase(yyruleno==217);
      /* (218) tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar */ yytestcase(yyruleno==218);
      /* (219) tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar */ yytestcase(yyruleno==219);
      /* (221) tagtablecoltdblockclosefull ::= tagtablecoltdblockclose */ yytestcase(yyruleno==221);
      /* (222) tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces */ yytestcase(yyruleno==222);
      /* (224) tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent */ yytestcase(yyruleno==224);
      /* (225) tagtablecolcontents ::= tagtablecolcontent (OPTIMIZED OUT) */ assert(yyruleno!=225);
      /* (226) tagtablecolcontent ::= taginput */ yytestcase(yyruleno==226);
      /* (227) tagtablecolcontent ::= taginput spaces */ yytestcase(yyruleno==227);
      /* (228) tagtablecolcontent ::= htmltext */ yytestcase(yyruleno==228);
      /* (229) tagtablecolcontent ::= htmltext spaces */ yytestcase(yyruleno==229);
      /* (230) tagtablecolcontent ::= tagtable */ yytestcase(yyruleno==230);
      /* (231) tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull */ yytestcase(yyruleno==231);
      /* (232) tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull */ yytestcase(yyruleno==232);
      /* (233) tagtablecolthfullopen ::= tagtablecolthopen tagclosechar */ yytestcase(yyruleno==233);
      /* (234) tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar */ yytestcase(yyruleno==234);
      /* (236) tagtablecolthblockclosefull ::= tagtablecolthblockclose */ yytestcase(yyruleno==236);
      /* (237) tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces */ yytestcase(yyruleno==237);
      /* (239) tagtitle ::= tagtitlefullopen tagtitleblockclosefull */ yytestcase(yyruleno==239);
      /* (240) tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull */ yytestcase(yyruleno==240);
      /* (241) tagtitlefullopen ::= tagtitleopen tagclosechar */ yytestcase(yyruleno==241);
      /* (242) tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar */ yytestcase(yyruleno==242);
      /* (243) tagtitleblockclosefull ::= tagtitleblockclose (OPTIMIZED OUT) */ assert(yyruleno!=243);
      /* (246) taglink ::= taglinkfullopen */ yytestcase(yyruleno==246);
      /* (247) taglink ::= taglinkfullopen taglinkblockclosefull */ yytestcase(yyruleno==247);
      /* (248) taglinkfullopen ::= taglinkopen tagproperties tagclosechar */ yytestcase(yyruleno==248);
      /* (249) taglinkfullopen ::= taglinkopen tagproperties tagshortclose */ yytestcase(yyruleno==249);
      /* (250) taglinkblockclosefull ::= taglinkblockclose (OPTIMIZED OUT) */ assert(yyruleno!=250);
      /* (253) tagmeta ::= tagmetafullopen */ yytestcase(yyruleno==253);
      /* (254) tagmeta ::= tagmetafullopen tagmetablockclosefull */ yytestcase(yyruleno==254);
      /* (255) tagmetafullopen ::= tagmetaopen tagproperties tagclosechar */ yytestcase(yyruleno==255);
      /* (256) tagmetafullopen ::= tagmetaopen tagproperties tagshortclose */ yytestcase(yyruleno==256);
      /* (257) tagmetablockclosefull ::= tagmetablockclose (OPTIMIZED OUT) */ assert(yyruleno!=257);
      /* (260) tagstyle ::= tagstylefullopen tagstyleblockclosefull */ yytestcase(yyruleno==260);
      /* (261) tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull */ yytestcase(yyruleno==261);
      /* (262) tagstylefullopen ::= tagstyleopen tagclosechar */ yytestcase(yyruleno==262);
      /* (263) tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar */ yytestcase(yyruleno==263);
      /* (264) tagstyleblockclosefull ::= tagstyleblockclose (OPTIMIZED OUT) */ assert(yyruleno!=264);
      /* (267) tagstyleproperties ::= tagstyleproperties tagstyleproperty */ yytestcase(yyruleno==267);
      /* (268) tagstyleproperties ::= tagstyleproperty (OPTIMIZED OUT) */ assert(yyruleno!=268);
      /* (272) tagscript ::= tagscriptfullopen tagscriptblockclosefull */ yytestcase(yyruleno==272);
      /* (273) tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull */ yytestcase(yyruleno==273);
      /* (274) tagscriptfullopen ::= tagscriptopen tagclosechar */ yytestcase(yyruleno==274);
      /* (275) tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar */ yytestcase(yyruleno==275);
      /* (276) tagscriptblockclosefull ::= tagscriptblockclose (OPTIMIZED OUT) */ assert(yyruleno!=276);
      /* (279) tagscriptproperties ::= tagscriptproperties tagscriptproperty */ yytestcase(yyruleno==279);
      /* (280) tagscriptproperties ::= tagscriptproperty (OPTIMIZED OUT) */ assert(yyruleno!=280);
      /* (285) taghtml ::= taghtmlfullopen taghtmlblockclosefull */ yytestcase(yyruleno==285);
      /* (286) taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull */ yytestcase(yyruleno==286);
      /* (287) taghtmlfullopen ::= taghtmlopen tagclosechar */ yytestcase(yyruleno==287);
      /* (288) taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar */ yytestcase(yyruleno==288);
      /* (289) taghtmlblockclosefull ::= taghtmlblockclose (OPTIMIZED OUT) */ assert(yyruleno!=289);
      /* (292) taghtmlcontents ::= taghtmlcontents taghtmlcontent */ yytestcase(yyruleno==292);
      /* (293) taghtmlcontents ::= taghtmlcontent (OPTIMIZED OUT) */ assert(yyruleno!=293);
      /* (294) taghtmlcontent ::= space (OPTIMIZED OUT) */ assert(yyruleno!=294);
      /* (295) taghtmlcontent ::= enter (OPTIMIZED OUT) */ assert(yyruleno!=295);
      /* (296) taghtmlcontent ::= tagbody (OPTIMIZED OUT) */ assert(yyruleno!=296);
      /* (297) taghtmlcontent ::= taghead tagbody */ yytestcase(yyruleno==297);
      /* (298) taghtmlcontent ::= taghead spaces_enters tagbody */ yytestcase(yyruleno==298);
      /* (299) tagbody ::= tagbodyfullopen tagbodyblockclosefull */ yytestcase(yyruleno==299);
      /* (300) tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull */ yytestcase(yyruleno==300);
      /* (301) tagbodyfullopen ::= tagbodyopen tagclosechar */ yytestcase(yyruleno==301);
      /* (302) tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar */ yytestcase(yyruleno==302);
      /* (303) tagbodyblockclosefull ::= tagbodyblockclose (OPTIMIZED OUT) */ assert(yyruleno!=303);
      /* (306) taghead ::= tagheadfullopen tagheadblockclosefull */ yytestcase(yyruleno==306);
      /* (307) taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull */ yytestcase(yyruleno==307);
      /* (308) tagheadfullopen ::= tagheadopen (OPTIMIZED OUT) */ assert(yyruleno!=308);
      /* (309) tagheadblockclosefull ::= tagheadblockclose (OPTIMIZED OUT) */ assert(yyruleno!=309);
      /* (312) tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues */ yytestcase(yyruleno==312);
      /* (313) tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue */ yytestcase(yyruleno==313);
      /* (314) tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue (OPTIMIZED OUT) */ assert(yyruleno!=314);
      /* (316) tagproperties ::= tagproperties tagproperty */ yytestcase(yyruleno==316);
      /* (317) tagproperties ::= tagproperty (OPTIMIZED OUT) */ assert(yyruleno!=317);
      /* (322) htmlandspaces ::= htmlandspaces htmlandspace */ yytestcase(yyruleno==322);
      /* (323) htmlandspaces ::= htmlandspace (OPTIMIZED OUT) */ assert(yyruleno!=323);
      /* (327) spaces_enters ::= spaces_enters spaces_enter */ yytestcase(yyruleno==327);
      /* (328) spaces_enters ::= spaces_enter (OPTIMIZED OUT) */ assert(yyruleno!=328);
      /* (329) spaces_enter ::= space (OPTIMIZED OUT) */ assert(yyruleno!=329);
      /* (330) spaces_enter ::= enter (OPTIMIZED OUT) */ assert(yyruleno!=330);
      /* (331) spaces ::= spaces space */ yytestcase(yyruleno==331);
      /* (332) spaces ::= space (OPTIMIZED OUT) */ assert(yyruleno!=332);
      /* (333) enters ::= enters enter */ yytestcase(yyruleno==333);
      /* (334) enters ::= enter (OPTIMIZED OUT) */ assert(yyruleno!=334);
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
    
    /*HTSQLPage *page = GetCurrentPage(session);
	char lineStr[10];
	sprintf_s(lineStr, sizeof(lineStr), "%d", session->sessionDebugInfo->lineNumberOuter);
    char *errMsg = mkStrcat(session->heapHandle, __FILE__, __LINE__, "HTML Syntax Error on line ", lineStr, ". Possible Tokens : (", NULL);
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
            int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
            if (a < YYNSTATE + YYNRULE) {
                char *tmp = mkStrcat(session->heapHandle, __FILE__, __LINE__, errMsg, " ", yyTokenName[i], NULL);
                mkFree(session->heapHandle, errMsg);
                errMsg = tmp;
            }
    }
    char *tempMsg = mkStrcat(session->heapHandle, __FILE__, __LINE__, errMsg, ")", NULL);
    mkFree(session->heapHandle, errMsg);
    errMsg = tempMsg;
	__sendErrorResponse(session, page, errMsg, "");
	CLOG(ERR_SYNTAX_ERROR_IN_FRMX_FILE, errMsg);*/
#line 2975 "lemon.html.c"
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
