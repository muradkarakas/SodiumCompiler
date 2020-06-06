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
#define YY_MIN_SHIFTREDUCE   524
#define YY_MAX_SHIFTREDUCE   858
#define YY_MIN_REDUCE        859
#define YY_MAX_REDUCE        1193
#define YY_ERROR_ACTION      1194
#define YY_ACCEPT_ACTION     1195
#define YY_NO_ACTION         1196
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
#define YY_ACTTAB_COUNT (891)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   104,    4,    4,    4,    4,    4,    4,    4,    4,    4,
 /*    10 */   180,  704, 1195,   33,   33,   53,  729,  857,   33,   33,
 /*    20 */   179,  857,  632,  104,  104,  531,  531,  203,  531,  531,
 /*    30 */   531,  531,  531,  531,  725,  855,   97,  733,  733,  733,
 /*    40 */     9,  732,  744,   50,  759,  631,   12,  104,   41,  631,
 /*    50 */   798,  221,  220,  219,  218,  217,  216,  215,  214,  213,
 /*    60 */   212,  211,  210,  209,  208,  207,  206,  205,  204,  633,
 /*    70 */   129,  642,  222,  201,  200,  199,  198,  197,  196,  195,
 /*    80 */   194,  193,  192,  191,  190,  189,  188,  187,  186,  185,
 /*    90 */   590,  729,    1,  132,  843,    1,  222,  201,  200,  199,
 /*   100 */   198,  197,  196,  195,  194,  193,  192,  191,  190,  189,
 /*   110 */   188,  187,  186,  185,  744,  786,  759,  599,  161,  160,
 /*   120 */   159,  158,  157,  156,  155,  154,  153,  152,  151,  150,
 /*   130 */   149,  148,  857,   38,   75,   74,   46,   57,   80,  710,
 /*   140 */    72,  719,   55,   79,   49,   71,   54,   35,   48,   45,
 /*   150 */   722,  729,  857,   34,  843,   29,  796,   38,  739,  796,
 /*   160 */    46,   93,   80,   60,   72,   60,   60,   79,  682,   71,
 /*   170 */   849,   35,  682,   45,  830,  764,  830,   34,  764,   29,
 /*   180 */     6,    6,   57,   44,   22,   44,  141,  138,  857,    6,
 /*   190 */     6,    6,    6,    6,    6,    6,    6,   22,  831,  130,
 /*   200 */   831,   22,  127,  143,   76,  778,  103,  778,   56,  137,
 /*   210 */   814,   13,   13,  101,   18,  557,  229,  100,  858,  573,
 /*   220 */    22,  846,   17,  573,   22,    8,  695,   30,  816,  816,
 /*   230 */    83,  815,  828,  710,  834,  540,  540,  769,  858,   30,
 /*   240 */    23,  228,   62,   40,   62,  540,  540,  540,  540,  540,
 /*   250 */   540,  540,  550,  551,  768,  848,  775,  857,  782,  719,
 /*   260 */   789,  103,  696,   56,  801,  227,   83,  147,  145,   18,
 /*   270 */    20,  835,  100,   51,  858,  723,   23,   17,    7,   40,
 /*   280 */     8,    7,  161,  160,  159,  158,  157,  156,  155,  154,
 /*   290 */   153,  152,  151,  150,  149,  148,  177,  849,  689,  175,
 /*   300 */   174,  173,  172,  171,  170,  169,  168,  167,  166,  165,
 /*   310 */   164,  163,  162,  714,  783,   86,  723,   23,  776,   25,
 /*   320 */    40,   25,   25,  108,  844,   20,  177,  183,   51,  175,
 /*   330 */   174,  173,  172,  171,  170,  169,  168,  167,  166,  165,
 /*   340 */   164,  163,  162,  858,  135,   60,  108,  857,   10,  823,
 /*   350 */   564,  823,  713,  855,  576,  729,  555,  109,  591,  857,
 /*   360 */    15,   91,  635,  636,  637,   94,   91,  578,  131,  566,
 /*   370 */   844,   10,  809,   13,  802,  809,   13,   13,   24,    5,
 /*   380 */   109,   47,  848,    3,  799,    3,  687,   14,   91,  810,
 /*   390 */   226,  224,  810,  816,  816,   24,    5,  747,   47,  687,
 /*   400 */     3,  855,    3,  705,  824,   98,  824,  748,   91,   58,
 /*   410 */   723,   23,   92,   77,   40,    2,   81,   92,   77,  850,
 /*   420 */     2,   36,  784,  183,  771,  784,  857,  771,  829,  635,
 /*   430 */   636,  637,  850,  858,  110,  594,  183,  728,   20,   92,
 /*   440 */    77,   51,    2,   20,  850,  779,   51,  594,  594,  851,
 /*   450 */   851,  758,  843,  687,   58,  748,   91,  110,  772,   92,
 /*   460 */    77,  857,    2,  748,   91,   20,  762,   26,   51,   26,
 /*   470 */    26,  737,   15,  593,   93,   15,  738,   16,  589,   93,
 /*   480 */    16,  183,  589,  594,  184,   20,  850,  821,   51,    5,
 /*   490 */   527,   47,  179,   42,  851,  851,  857,  763,   59,   14,
 /*   500 */   763,   25,   14,  811,  755,   36,   90,   92,   77,   82,
 /*   510 */     2,  634,  858,  687,  579,   92,   77,   21,    2,  803,
 /*   520 */   141,  138,  748,  837,  756,   20,   90,  579,   51,   21,
 /*   530 */    21,  579,  127,   20,   76,  859,   51,  550,  551,  849,
 /*   540 */   183,   20,  857,   59,   51,  183,  850,  525,   53,  574,
 /*   550 */   857,  525,  525,  574,  579,   89,  111,  757,  232,  231,
 /*   560 */   588,   21,  765,  780,  588,   21,  740,  825,  843,   93,
 /*   570 */   748,  851,  851,  556,  741,   61,  773,   93,  748,  111,
 /*   580 */   681,   99,  858,  552,  681,   28,   73,  183,   27,   19,
 /*   590 */   105,   39,  857,   19,   19,   19,    9,  183,   54,   50,
 /*   600 */    48,  840,   12,  183,   41,  183,  857,   20,  183,   85,
 /*   610 */    51,  183,  790,  747,  840,  822,  184,    5,  807,   47,
 /*   620 */   635,  636,  637,  132,  848,   88,  808,  742,  858,  851,
 /*   630 */    96,  102,  805,  812,   63,   31,  106,  844,  107,   64,
 /*   640 */   567,  233,  230,  845,  687,  787,  528,   31,   23,   26,
 /*   650 */   183,   40,  857,   32,   11,  747,  183,   43,   52,   61,
 /*   660 */    52,  233,  230,  117,  117,   32,   23,  183,  183,   40,
 /*   670 */   689,  701,  766,  183,  851,  719,  183,  850,  826,  184,
 /*   680 */   797,   65,  134,  797,  785,  136,  828,  785,  133,   84,
 /*   690 */    87,   37,  858,  806,  693,  743,  575,   66,   95,   67,
 /*   700 */   843,   55,   69,   49,  139,  140,  846,  691,  180,  117,
 /*   710 */   117,  117,  117,  690,  844,  584,  846,  112,   63,   54,
 /*   720 */    55,   48,   49,   64,   70,  113,  114,   70,  229,  639,
 /*   730 */   640,  641,  115,  226,  224,  116,  118,  119,  858,  120,
 /*   740 */   112,  121,  795,   78,   68,  122,   78,  123,  113,  114,
 /*   750 */   124,  851,  142,  125,  126,  115,  128,  794,  116,  118,
 /*   760 */   119,  144,  120,  843,  121,   65,  843,   68,  122,  843,
 /*   770 */   123,  793,  843,  124,  791,   37,  125,  126,  146,  128,
 /*   780 */   628,   66,  561,   67,  626,  561,   69,  232,  231,  840,
 /*   790 */   624,  622,  843,  620,  618,  616,  614,  612,  610,  608,
 /*   800 */   606,  604,  602,  844,  861,  601,  629,  627,  844,  625,
 /*   810 */   623,  621,  619,  181,  861,  176,  617,  615,  613,  611,
 /*   820 */   609,  607,  605,  861,  839,  178,  603,  842,  840,  678,
 /*   830 */   228,  182,  676,  674,  840,  672,  670,  202,  668,  666,
 /*   840 */   664,  662,  660,  658,  644,  840,  840,  656,  654,  652,
 /*   850 */   650,  840,  648,  646,  840,  680,  861,  679,  861,  677,
 /*   860 */   675,  673,  671,  669,  667,  665,  861,  663,  861,  661,
 /*   870 */   659,  657,  655,  653,  651,  649,  861,  647,  587,  645,
 /*   880 */   223,  586,  225,  560,  559,  571,  861,  861,  569,  572,
 /*   890 */   570,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   101,  101,  102,  103,  104,  105,  106,  107,  108,  109,
 /*    10 */     7,   62,   95,   96,   97,   98,   67,    7,  101,  102,
 /*    20 */    17,    7,  123,  124,  101,  101,  102,   17,  104,  105,
 /*    30 */   106,  107,  108,  109,  217,  101,  219,  220,  221,  222,
 /*    40 */   223,   68,   69,  226,   71,  167,  229,  124,  231,  171,
 /*    50 */   123,   41,   42,   43,   44,   45,   46,   47,   48,   49,
 /*    60 */    50,   51,   52,   53,   54,   55,   56,   57,   58,  170,
 /*    70 */     7,  172,  173,  174,  175,  176,  177,  178,  179,  180,
 /*    80 */   181,  182,  183,  184,  185,  186,  187,  188,  189,  190,
 /*    90 */   123,   67,  169,  101,   91,  172,  173,  174,  175,  176,
 /*   100 */   177,  178,  179,  180,  181,  182,  183,  184,  185,  186,
 /*   110 */   187,  188,  189,  190,   69,  123,   71,  150,  151,  152,
 /*   120 */   153,  154,  155,  156,  157,  158,  159,  160,  161,  162,
 /*   130 */   163,  164,    7,  233,  198,  199,  236,  235,  238,   63,
 /*   140 */   240,   65,  206,  243,  208,  245,  210,  247,  212,  249,
 /*   150 */    66,   67,    7,  253,   91,  255,  254,  233,  224,  257,
 /*   160 */   236,  227,  238,   99,  240,  101,  102,  243,  192,  245,
 /*   170 */     7,  247,  196,  249,  274,  234,  276,  253,  237,  255,
 /*   180 */   101,  102,  280,  256,  101,  258,  259,  260,    7,  110,
 /*   190 */   111,  112,  113,  114,  115,  116,  117,  114,  274,    7,
 /*   200 */   276,  118,  119,   17,  121,  244,  127,  246,  129,    7,
 /*   210 */    85,  101,  102,  123,  135,  125,  126,  138,   93,  136,
 /*   220 */   137,  280,  143,  140,  141,  146,  201,  202,  101,  102,
 /*   230 */   205,   86,   87,   63,   89,  101,  102,   74,   93,  214,
 /*   240 */   215,    8,  250,  218,  252,  111,  112,  113,  114,  115,
 /*   250 */   116,  117,    2,    3,   73,   92,   75,    7,   77,   65,
 /*   260 */    79,  127,  201,  129,   83,    7,  205,   81,   82,  135,
 /*   270 */   191,   90,  138,  194,   93,  214,  215,  143,  147,  218,
 /*   280 */   146,  150,  151,  152,  153,  154,  155,  156,  157,  158,
 /*   290 */   159,  160,  161,  162,  163,  164,   17,    7,   60,   20,
 /*   300 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   310 */    31,   32,   33,  211,   78,  213,  214,  215,   76,   99,
 /*   320 */   218,  101,  102,  101,   91,  191,   17,  101,  194,   20,
 /*   330 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   340 */    31,   32,   33,   93,    7,  281,  124,    7,  101,  270,
 /*   350 */    10,  272,   64,  101,   14,   67,    4,  101,   18,    7,
 /*   360 */   113,  114,   35,   36,   37,  113,  114,   15,    7,   11,
 /*   370 */    91,  124,  262,  263,   84,  265,  266,  267,  268,  269,
 /*   380 */   124,  271,   92,  273,  123,  275,   59,  113,  114,  262,
 /*   390 */    16,   17,  265,  266,  267,  268,  269,   70,  271,   59,
 /*   400 */   273,  101,  275,  207,  270,  209,  272,  113,  114,  235,
 /*   410 */   214,  215,  165,  166,  218,  168,  123,  165,  166,   92,
 /*   420 */   168,  195,  248,  101,  239,  251,    7,  242,   88,   35,
 /*   430 */    36,   37,   92,   93,  101,  101,  101,  123,  191,  165,
 /*   440 */   166,  194,  168,  191,   92,  123,  194,  113,  114,  101,
 /*   450 */   102,  123,   91,   59,  280,  113,  114,  124,  123,  165,
 /*   460 */   166,    7,  168,  113,  114,  191,   72,   99,  194,  101,
 /*   470 */   102,  224,  225,   19,  227,  228,  224,  225,  144,  227,
 /*   480 */   228,  101,  148,  149,    7,  191,   92,  267,  194,  269,
 /*   490 */     1,  271,   17,  100,  101,  102,    7,  234,  235,  225,
 /*   500 */   237,  281,  228,  123,  230,  279,  232,  165,  166,  123,
 /*   510 */   168,   34,   93,   59,  101,  165,  166,  101,  168,  258,
 /*   520 */   259,  260,  228,  278,  230,  191,  232,  114,  194,  113,
 /*   530 */   114,  118,  119,  191,  121,    0,  194,    2,    3,    7,
 /*   540 */   101,  191,    7,  280,  194,  101,   92,   97,   98,  136,
 /*   550 */     7,  101,  102,  140,  141,  123,  101,  123,   12,   13,
 /*   560 */   144,  145,  123,  241,  148,  149,  224,  123,   91,  227,
 /*   570 */   228,  101,  102,    5,  224,  195,  241,  227,  228,  124,
 /*   580 */   192,  193,   93,  120,  196,  197,  198,  101,  200,  216,
 /*   590 */   204,  203,    7,  220,  221,  222,  223,  101,  210,  226,
 /*   600 */   212,  279,  229,  101,  231,  101,    7,  191,  101,  123,
 /*   610 */   194,  101,   80,   70,  279,  267,    7,  269,    6,  271,
 /*   620 */    35,   36,   37,  101,   92,  123,    9,  123,   93,  281,
 /*   630 */   123,  123,    6,  123,  195,  202,  204,   91,  204,  195,
 /*   640 */   132,  133,  134,   34,   59,  123,    1,  214,  215,  281,
 /*   650 */   101,  218,    7,  202,  261,   70,  101,  264,  130,  279,
 /*   660 */   132,  133,  134,  277,  278,  214,  215,  101,  101,  218,
 /*   670 */    60,   61,  123,  101,  281,   65,  101,   92,  123,    7,
 /*   680 */   254,  195,    7,  257,  248,    7,   87,  251,    7,  123,
 /*   690 */   123,  195,   93,    9,  199,  123,  123,  195,  123,  195,
 /*   700 */    91,  206,  195,  208,   81,   82,  280,  198,    7,  277,
 /*   710 */   278,  277,  278,  199,   91,  142,  280,  101,  279,  210,
 /*   720 */   206,  212,  208,  279,  122,  101,  101,  125,  126,   38,
 /*   730 */    39,   40,  101,   16,   17,  101,  101,  101,   93,  101,
 /*   740 */   124,  101,    6,  139,  101,  101,  142,  101,  124,  124,
 /*   750 */   101,  281,    9,  101,  101,  124,  101,    6,  124,  124,
 /*   760 */   124,    9,  124,   91,  124,  279,   91,  124,  124,   91,
 /*   770 */   124,    6,   91,  124,  252,  279,  124,  124,    9,  124,
 /*   780 */     6,  279,  128,  279,    6,  131,  279,   12,   13,  279,
 /*   790 */     6,    6,   91,    6,    6,    6,    6,    6,    6,    6,
 /*   800 */     6,    6,    6,   91,  282,    6,    9,    9,   91,    9,
 /*   810 */     9,    9,    9,    9,  282,    9,    9,    9,    9,    9,
 /*   820 */     9,    9,    9,  282,    6,    9,    9,    6,  279,    6,
 /*   830 */     8,   17,    6,    6,  279,    6,    6,    9,    6,    6,
 /*   840 */     6,    6,    6,    6,    6,  279,  279,    6,    6,    6,
 /*   850 */     6,  279,    6,    6,  279,    6,  282,    9,  282,    9,
 /*   860 */     9,    9,    9,    9,    9,    9,  282,    9,  282,    9,
 /*   870 */     9,    9,    9,    9,    9,    9,  282,    9,    6,    9,
 /*   880 */     9,    6,    9,    9,    6,    6,  282,  282,    6,    9,
 /*   890 */     9,
};
#define YY_SHIFT_USE_DFLT (891)
#define YY_SHIFT_COUNT    (233)
#define YY_SHIFT_MIN      (-51)
#define YY_SHIFT_MAX      (882)
static const short yy_shift_ofst[] = {
 /*     0 */   250,  477,   14,  181,  181,  340,  340,   63,  192,  585,
 /*    10 */   585,  145,  394,  145,  394,  327,  327,  454,  352,  -27,
 /*    20 */   610,  454,  352,   45,  599,  599,  125,  -51,   76,  361,
 /*    30 */   -51,   84,  288,  535,  290,  532,  609,  609,  163,    3,
 /*    40 */     3,    3,  489,  672,  361,  672,  672,  672,  672,  672,
 /*    50 */   672,  672,  675,  419,   24,   24,  202,  290,  532,  163,
 /*    60 */   645,  672,  672,  672,  672,  672,  672,  672,  543,  672,
 /*    70 */   678,   14,   14,  170,  194,  170,  258,  691,  681,  236,
 /*    80 */   242,   14,   14,   14,   14,   14,   14,   14,   14,   14,
 /*    90 */    14,   14,   14,   14,   14,   14,   14,   14,   14,  238,
 /*   100 */   337,   14,   14,  358,   10,  701,  701,  701,   14,   14,
 /*   110 */    14,   14,   14,   14,   14,   14,   14,  475,   14,   14,
 /*   120 */    14,   14,   14,   14,   14,   14,   14,  568,   14,  279,
 /*   130 */   309,  623,  186,  717,  546,  374,  233,  775,  612,  617,
 /*   140 */   684,  626,  736,  743,  751,  752,  765,  769,  774,  778,
 /*   150 */   784,  785,  787,  788,  789,  790,  791,  792,  793,  794,
 /*   160 */   795,  796,  797,  798,  800,  801,  802,  803,  807,  808,
 /*   170 */   809,  810,  811,  812,  813,  817,  799,  806,  818,  816,
 /*   180 */   712,  821,  804,  814,  712,  823,  826,  827,  829,  830,
 /*   190 */   832,  833,  834,  835,  836,  837,  841,  842,  843,  844,
 /*   200 */   846,  847,  849,  828,  848,  850,  851,  852,  853,  854,
 /*   210 */   855,  856,  858,  860,  861,  862,  863,  864,  865,  866,
 /*   220 */   868,  870,  838,  872,  871,  875,  873,  822,  874,  878,
 /*   230 */   879,  880,  881,  882,
};
#define YY_REDUCE_USE_DFLT (-184)
#define YY_REDUCE_COUNT (128)
#define YY_REDUCE_MIN   (-183)
#define YY_REDUCE_MAX   (655)
static const short yy_reduce_ofst[] = {
 /*     0 */   -83, -101,  -77, -100,  -76,   79,  134,  -33,  131,  247,
 /*    10 */   252,  110,  274,  127,  294,  342,  350,  416,   83, -183,
 /*    20 */   388,  334,  413,  373,  220,  348,  393,   25,  -64,  -73,
 /*    30 */    61,  102,  196,  450,  -98,  174,  322,  335,  263,  386,
 /*    40 */   432,  434,   64,  380,  261,   -8,  439,  444,  486,  502,
 /*    50 */   504,  507,  508,  368,  433,  451,  528,  426,  436,  -59,
 /*    60 */   470,  510,  522,  549,  555,  566,  567,  572,  -66,  575,
 /*    70 */    90,  226,  496,  495,  509,  514,  602, -122,  573,  -39,
 /*    80 */   185,  222,  256,  333,  455,  616,  624,  625,  631,  634,
 /*    90 */   635,  636,  638,  640,  643,  644,  646,  649,  652,  -24,
 /*   100 */   604,  653,  655,  654,  300,  293,  314,  328,  300,  300,
 /*   110 */   300,  300,  300,  300,  300,  300,  300,  245,  300,  300,
 /*   120 */   300,  300,  300,  300,  300,  300,  300,  463,  300,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*    10 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*    20 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*    30 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*    40 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*    50 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*    60 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*    70 */  1194, 1194, 1194, 1029, 1194, 1027, 1194,  965, 1194, 1112,
 /*    80 */  1105, 1034, 1032, 1037, 1052, 1050, 1055, 1043, 1041, 1061,
 /*    90 */  1095, 1087, 1085, 1080, 1089, 1020, 1018, 1065, 1046, 1194,
 /*   100 */  1194,  888,  897, 1194, 1194, 1194, 1194, 1194, 1035, 1033,
 /*   110 */  1038, 1053, 1051, 1056, 1044, 1042, 1062, 1171, 1096, 1088,
 /*   120 */  1086, 1081, 1021, 1019, 1066, 1047,  889, 1194,  898, 1194,
 /*   130 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*   140 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*   150 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*   160 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*   170 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*   180 */  1194, 1194, 1194, 1194, 1192, 1194, 1194, 1194, 1194, 1194,
 /*   190 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*   200 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*   210 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*   220 */  1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194, 1194,
 /*   230 */  1194, 1194, 1194, 1194,
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
  "expressions",   "expression",    "tagdoctype",    "spaces_enters",
  "taghtml",       "space",         "enter",         "tagheadcontents",
  "tagheadcontent",  "tagtitle",      "tagscript",     "tagstyle",    
  "taglink",       "tagmeta",       "tagbodycontents",  "tagbodycontent",
  "htsqls",        "tagtable",      "htmltext",      "tagdatablock",
  "tagcontrolblock",  "tagdatalist",   "tagtree",       "tagtreefullopen",
  "tagtreeblockclosefull",  "tagtreeopen",   "tagtreeproperties",  "tagclosechar",
  "spaces",        "tagtreeproperty",  "tagtreepropertyid",  "tagdatalistfullopen",
  "tagdatalistblockclosefull",  "tagdatalistopen",  "datalistproperties",  "tagdatalistblockclose",
  "datalistproperty",  "tagdatalistpropertyid",  "tagdatalistpropertyconnectionname",  "tagcontrolblockfullopen",
  "tagcontrolblockclosefull",  "tagcontrolblockcontents",  "tagcontrolblockopen",  "tagcontrolblockproperties",
  "tagcontrolblockblockclose",  "tagcontrolblockcontent",  "tagcontrolblockproperty",  "tagdatablockfullopen",
  "tagdatablockblockclosefull",  "tagdatablockcontents",  "tagdatablockopen",  "tagdatablockproperties",
  "tagdatablockblockclose",  "tagdatablockcontent",  "tagdatablockproperty",  "tagdatablockpropertyjoincondition",
  "tagdatablockpropertyconnectionname",  "tagdatablockpropertyautogeneratedcolumns",  "tagdatablockpropertyrecordcount",  "tagdatablockpropertysourcename",
  "tagdatablockpropertyschemaname",  "tagdatablockpropertyblockname",  "tagdatablockpropertykeycolumnname",  "tagdatablockpropertymasterblockname",
  "tagdatablockpropertyinsertallowed",  "tagdatablockpropertydeleteallowed",  "tagdatablockpropertyupdateallowed",  "tagdatablockpropertywhereclause",
  "tagdatablockpropertyorderbyclause",  "taginput",      "taginputfullopen",  "taginputblockclosefull",
  "taginputopen",  "taginputproperties",  "taginputshortclose",  "taginputblockclose",
  "taginputproperty",  "taginputcheckedvalue",  "taginputuncheckedvalue",  "taginputpropertyinputname",
  "taginputpropertysequencename",  "taginputpropertysequenceschemaname",  "taginputpropertymasteritemname",  "taginputpropertyinputtype",
  "taginputpropertyinputvalue",  "taginputpropertydefaultvalue",  "taginputpropertycolumnname",  "taginputpropertyformatmask",
  "taginputpropertydatatype",  "taginputpropertymaxlength",  "taginputpropertyinsertallowed",  "taginputpropertyupdateallowed",
  "taginputpropertydatalistname",  "taginputpropertylookupitemname",  "taginputpropertylookupitemblockname",  "tagtablefullopen",
  "tagtableblockclosefull",  "tablecontent",  "tagtableopen",  "tagproperties",
  "tagtableblockclose",  "tagthead",      "tagtbody",      "tagtfoot",    
  "tagtheadfullopen",  "tagtheadblockclosefull",  "tagtablerows",  "tagtheadopen",
  "tagpropertieswithreturnvaluesall",  "tagtheadblockclose",  "tagtfootfullopen",  "tagtfootblockclosefull",
  "tagtfootopen",  "tagtfootblockclose",  "tagtbodyfullopen",  "tagtbodyblockclosefull",
  "tagtbodyopen",  "tagtbodyblockclose",  "tagtablerow",   "tagtablerowfullopen",
  "tagtablecols",  "tagtablerowblockclosefull",  "tagtablerowopen",  "tagtablerowblockclose",
  "tagtablecol",   "tagtablecoltd",  "tagtablecolth",  "tagtablecoltdfullopen",
  "tagtablecoltdblockclosefull",  "tagtablecolcontents",  "tagtablecoltdopen",  "tagtablecoltdblockclose",
  "tagtablecolcontent",  "tagtablecolthfullopen",  "tagtablecolthblockclosefull",  "tagtablecolthopen",
  "tagtablecolthblockclose",  "tagtitlefullopen",  "tagtitleblockclosefull",  "htmlandspaces",
  "tagtitleopen",  "tagtitleblockclose",  "taglinkfullopen",  "taglinkblockclosefull",
  "taglinkopen",   "tagshortclose",  "taglinkblockclose",  "tagmetafullopen",
  "tagmetablockclosefull",  "tagmetaopen",   "tagmetablockclose",  "tagstylefullopen",
  "tagstyleblockclosefull",  "tagstyleopen",  "tagstyleproperties",  "tagstyleblockclose",
  "tagstyleproperty",  "tagscriptfullopen",  "tagscriptblockclosefull",  "tagscriptopen",
  "tagscriptproperties",  "tagscriptblockclose",  "tagscriptproperty",  "tagscriptpropertyscripttype",
  "tagscriptpropertysrc",  "taghtmlfullopen",  "taghtmlblockclosefull",  "taghtmlcontents",
  "taghtmlopen",   "taghtmlblockclose",  "taghtmlcontent",  "tagbody",     
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
 /*   3 */ "expression ::= tagdoctype spaces_enters taghtml END_OF_FILE",
 /*   4 */ "expression ::= tagdoctype spaces_enters taghtml spaces_enters END_OF_FILE",
 /*   5 */ "expression ::= space",
 /*   6 */ "expression ::= enter",
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
#line 34 "lemon.html.yy"

    if ((yypminor->yy0)->tokenStr != NULL) {
        if ((yypminor->yy0)->tokenStr[0] == '\n') {
            printf("\n%4d: ", session->lineNumberOuter);
        } else {
            printf("%.*s", (yypminor->yy0)->tokenStrLength, (yypminor->yy0)->tokenStr);
        }
    }

#line 1193 "lemon.html.c"
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
  { 97, 4 },
  { 97, 5 },
  { 97, 1 },
  { 97, 1 },
  { 103, 2 },
  { 103, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 110, 2 },
  { 110, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 112, 1 },
  { 112, 1 },
  { 112, 1 },
  { 98, 1 },
  { 98, 1 },
  { 118, 2 },
  { 119, 3 },
  { 119, 4 },
  { 121, 1 },
  { 120, 1 },
  { 122, 2 },
  { 122, 1 },
  { 125, 2 },
  { 126, 3 },
  { 117, 2 },
  { 127, 3 },
  { 127, 4 },
  { 129, 1 },
  { 128, 1 },
  { 131, 1 },
  { 130, 2 },
  { 130, 1 },
  { 132, 2 },
  { 133, 3 },
  { 132, 2 },
  { 134, 3 },
  { 116, 2 },
  { 116, 3 },
  { 135, 3 },
  { 138, 1 },
  { 136, 1 },
  { 140, 1 },
  { 137, 2 },
  { 137, 1 },
  { 141, 1 },
  { 141, 1 },
  { 141, 1 },
  { 139, 2 },
  { 139, 1 },
  { 142, 4 },
  { 142, 4 },
  { 115, 2 },
  { 115, 3 },
  { 143, 3 },
  { 146, 1 },
  { 144, 1 },
  { 148, 1 },
  { 145, 2 },
  { 145, 1 },
  { 149, 1 },
  { 149, 1 },
  { 149, 1 },
  { 147, 2 },
  { 147, 1 },
  { 150, 4 },
  { 150, 2 },
  { 151, 3 },
  { 150, 2 },
  { 152, 3 },
  { 150, 2 },
  { 153, 3 },
  { 150, 2 },
  { 154, 3 },
  { 150, 2 },
  { 155, 3 },
  { 150, 2 },
  { 156, 3 },
  { 150, 2 },
  { 157, 3 },
  { 150, 2 },
  { 158, 3 },
  { 150, 2 },
  { 159, 3 },
  { 150, 2 },
  { 160, 3 },
  { 150, 2 },
  { 161, 3 },
  { 150, 2 },
  { 162, 3 },
  { 150, 2 },
  { 163, 3 },
  { 150, 2 },
  { 164, 3 },
  { 165, 1 },
  { 165, 2 },
  { 166, 3 },
  { 166, 3 },
  { 170, 1 },
  { 168, 1 },
  { 168, 1 },
  { 168, 1 },
  { 167, 1 },
  { 171, 1 },
  { 171, 1 },
  { 171, 1 },
  { 169, 2 },
  { 169, 1 },
  { 172, 2 },
  { 173, 3 },
  { 172, 2 },
  { 174, 3 },
  { 172, 2 },
  { 175, 3 },
  { 172, 2 },
  { 176, 3 },
  { 172, 2 },
  { 177, 3 },
  { 172, 2 },
  { 178, 3 },
  { 172, 2 },
  { 179, 3 },
  { 172, 2 },
  { 180, 3 },
  { 172, 2 },
  { 181, 3 },
  { 172, 2 },
  { 182, 3 },
  { 172, 2 },
  { 183, 3 },
  { 172, 2 },
  { 184, 3 },
  { 172, 2 },
  { 185, 3 },
  { 172, 2 },
  { 186, 3 },
  { 172, 2 },
  { 187, 3 },
  { 172, 2 },
  { 188, 3 },
  { 172, 2 },
  { 189, 3 },
  { 172, 2 },
  { 190, 3 },
  { 172, 4 },
  { 113, 2 },
  { 113, 3 },
  { 191, 2 },
  { 191, 3 },
  { 191, 3 },
  { 191, 4 },
  { 194, 1 },
  { 192, 1 },
  { 196, 1 },
  { 193, 3 },
  { 193, 3 },
  { 193, 2 },
  { 193, 2 },
  { 193, 1 },
  { 197, 2 },
  { 197, 3 },
  { 200, 2 },
  { 200, 3 },
  { 200, 3 },
  { 200, 4 },
  { 203, 1 },
  { 201, 1 },
  { 201, 2 },
  { 205, 1 },
  { 199, 3 },
  { 206, 2 },
  { 206, 3 },
  { 206, 3 },
  { 206, 4 },
  { 208, 1 },
  { 207, 1 },
  { 207, 2 },
  { 209, 1 },
  { 198, 3 },
  { 210, 2 },
  { 210, 3 },
  { 210, 3 },
  { 210, 4 },
  { 212, 1 },
  { 211, 1 },
  { 211, 2 },
  { 213, 1 },
  { 202, 2 },
  { 202, 1 },
  { 214, 3 },
  { 215, 2 },
  { 215, 3 },
  { 215, 3 },
  { 218, 1 },
  { 217, 1 },
  { 217, 2 },
  { 219, 1 },
  { 216, 2 },
  { 216, 1 },
  { 220, 1 },
  { 220, 1 },
  { 221, 2 },
  { 221, 3 },
  { 221, 5 },
  { 221, 3 },
  { 221, 4 },
  { 223, 2 },
  { 223, 3 },
  { 226, 1 },
  { 224, 1 },
  { 224, 2 },
  { 227, 1 },
  { 225, 2 },
  { 225, 1 },
  { 228, 1 },
  { 228, 2 },
  { 228, 1 },
  { 228, 2 },
  { 228, 1 },
  { 222, 2 },
  { 222, 3 },
  { 229, 2 },
  { 229, 3 },
  { 231, 1 },
  { 230, 1 },
  { 230, 2 },
  { 232, 1 },
  { 105, 2 },
  { 105, 3 },
  { 233, 2 },
  { 233, 3 },
  { 234, 1 },
  { 236, 1 },
  { 237, 1 },
  { 108, 1 },
  { 108, 2 },
  { 238, 3 },
  { 238, 3 },
  { 239, 1 },
  { 240, 1 },
  { 242, 1 },
  { 109, 1 },
  { 109, 2 },
  { 243, 3 },
  { 243, 3 },
  { 244, 1 },
  { 245, 1 },
  { 246, 1 },
  { 107, 2 },
  { 107, 3 },
  { 247, 2 },
  { 247, 3 },
  { 248, 1 },
  { 249, 1 },
  { 251, 1 },
  { 250, 2 },
  { 250, 1 },
  { 252, 4 },
  { 252, 4 },
  { 252, 4 },
  { 106, 2 },
  { 106, 3 },
  { 253, 2 },
  { 253, 3 },
  { 254, 1 },
  { 255, 1 },
  { 257, 1 },
  { 256, 2 },
  { 256, 1 },
  { 258, 2 },
  { 259, 3 },
  { 258, 2 },
  { 260, 3 },
  { 100, 2 },
  { 100, 3 },
  { 261, 2 },
  { 261, 3 },
  { 262, 1 },
  { 264, 1 },
  { 265, 1 },
  { 263, 2 },
  { 263, 1 },
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
  { 204, 1 },
  { 277, 2 },
  { 277, 1 },
  { 278, 3 },
  { 195, 2 },
  { 195, 1 },
  { 279, 4 },
  { 123, 1 },
  { 123, 2 },
  { 241, 1 },
  { 235, 2 },
  { 235, 1 },
  { 280, 1 },
  { 280, 1 },
  { 114, 1 },
  { 99, 2 },
  { 99, 1 },
  { 281, 1 },
  { 281, 1 },
  { 124, 2 },
  { 124, 1 },
  { 101, 1 },
  { 102, 1 },
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
      case 3: /* expression ::= tagdoctype spaces_enters taghtml END_OF_FILE */
      case 4: /* expression ::= tagdoctype spaces_enters taghtml spaces_enters END_OF_FILE */ yytestcase(yyruleno==4);
#line 49 "lemon.html.yy"
{
}
#line 1838 "lemon.html.c"
  yy_destructor(yypParser,1,&yymsp[0].minor);
        break;
      case 26: /* tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD */
{  yy_destructor(yypParser,2,&yymsp[0].minor);
#line 78 "lemon.html.yy"
{
}
#line 1846 "lemon.html.c"
}
        break;
      case 27: /* tagdoctype ::= TAG_DOCTYPE_HTML */
{  yy_destructor(yypParser,3,&yymsp[0].minor);
#line 80 "lemon.html.yy"
{
}
#line 1854 "lemon.html.c"
}
        break;
      case 31: /* tagtreeopen ::= TAG_TREE_OPEN */
{  yy_destructor(yypParser,4,&yymsp[0].minor);
#line 91 "lemon.html.yy"
{
}
#line 1862 "lemon.html.c"
}
        break;
      case 32: /* tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE */
{  yy_destructor(yypParser,5,&yymsp[0].minor);
#line 93 "lemon.html.yy"
{
}
#line 1870 "lemon.html.c"
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
#line 98 "lemon.html.yy"
{
}
#line 1913 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 36: /* tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 100 "lemon.html.yy"
{
}
#line 1921 "lemon.html.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 40: /* tagdatalistopen ::= TAG_DATALIST_OPEN */
{  yy_destructor(yypParser,10,&yymsp[0].minor);
#line 110 "lemon.html.yy"
{
}
#line 1931 "lemon.html.c"
}
        break;
      case 42: /* tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE */
{  yy_destructor(yypParser,11,&yymsp[0].minor);
#line 114 "lemon.html.yy"
{
}
#line 1939 "lemon.html.c"
}
        break;
      case 46: /* tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 121 "lemon.html.yy"
{
}
#line 1947 "lemon.html.c"
  yy_destructor(yypParser,12,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 48: /* tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 125 "lemon.html.yy"
{
}
#line 1957 "lemon.html.c"
  yy_destructor(yypParser,13,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 52: /* tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN */
{  yy_destructor(yypParser,14,&yymsp[0].minor);
#line 137 "lemon.html.yy"
{
}
#line 1967 "lemon.html.c"
}
        break;
      case 54: /* tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 140 "lemon.html.yy"
{
}
#line 1975 "lemon.html.c"
}
        break;
      case 62: /* tagcontrolblockproperty ::= SPACE PROP_CONTROLBLOCK_BLOCK_NAME ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,7,&yymsp[-3].minor);
#line 153 "lemon.html.yy"
{
}
#line 1983 "lemon.html.c"
  yy_destructor(yypParser,16,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 63: /* tagcontrolblockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA */
      case 77: /* tagdatablockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==77);
{  yy_destructor(yypParser,7,&yymsp[-3].minor);
#line 155 "lemon.html.yy"
{
}
#line 1995 "lemon.html.c"
  yy_destructor(yypParser,17,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 67: /* tagdatablockopen ::= TAG_DATABLOCK_OPEN */
{  yy_destructor(yypParser,18,&yymsp[0].minor);
#line 167 "lemon.html.yy"
{
}
#line 2006 "lemon.html.c"
}
        break;
      case 69: /* tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE */
{  yy_destructor(yypParser,19,&yymsp[0].minor);
#line 171 "lemon.html.yy"
{
}
#line 2014 "lemon.html.c"
}
        break;
      case 79: /* tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 189 "lemon.html.yy"
{
}
#line 2022 "lemon.html.c"
  yy_destructor(yypParser,20,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 81: /* tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 194 "lemon.html.yy"
{
}
#line 2032 "lemon.html.c"
  yy_destructor(yypParser,21,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 83: /* tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 199 "lemon.html.yy"
{
}
#line 2042 "lemon.html.c"
  yy_destructor(yypParser,22,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 85: /* tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 203 "lemon.html.yy"
{
}
#line 2052 "lemon.html.c"
  yy_destructor(yypParser,23,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 87: /* tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 207 "lemon.html.yy"
{
}
#line 2062 "lemon.html.c"
  yy_destructor(yypParser,24,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 89: /* tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 212 "lemon.html.yy"
{
}
#line 2072 "lemon.html.c"
  yy_destructor(yypParser,25,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 91: /* tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 216 "lemon.html.yy"
{
}
#line 2082 "lemon.html.c"
  yy_destructor(yypParser,26,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 93: /* tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 220 "lemon.html.yy"
{
}
#line 2092 "lemon.html.c"
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 95: /* tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 224 "lemon.html.yy"
{
}
#line 2102 "lemon.html.c"
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 97: /* tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 228 "lemon.html.yy"
{
}
#line 2112 "lemon.html.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 99: /* tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 232 "lemon.html.yy"
{
}
#line 2122 "lemon.html.c"
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 101: /* tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 236 "lemon.html.yy"
{
}
#line 2132 "lemon.html.c"
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 103: /* tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 241 "lemon.html.yy"
{
}
#line 2142 "lemon.html.c"
  yy_destructor(yypParser,32,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 105: /* tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 245 "lemon.html.yy"
{
}
#line 2152 "lemon.html.c"
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 110: /* taginputshortclose ::= TAG_SHORT_CLOSE */
      case 321: /* tagshortclose ::= TAG_SHORT_CLOSE */ yytestcase(yyruleno==321);
{  yy_destructor(yypParser,34,&yymsp[0].minor);
#line 259 "lemon.html.yy"
{
}
#line 2163 "lemon.html.c"
}
        break;
      case 111: /* taginputopen ::= TAG_INPUT_OPEN */
{  yy_destructor(yypParser,35,&yymsp[0].minor);
#line 262 "lemon.html.yy"
{
}
#line 2171 "lemon.html.c"
}
        break;
      case 112: /* taginputopen ::= TAG_SELECT_OPEN */
{  yy_destructor(yypParser,36,&yymsp[0].minor);
#line 264 "lemon.html.yy"
{
}
#line 2179 "lemon.html.c"
}
        break;
      case 113: /* taginputopen ::= TAG_TEXTAREA_OPEN */
{  yy_destructor(yypParser,37,&yymsp[0].minor);
#line 266 "lemon.html.yy"
{
}
#line 2187 "lemon.html.c"
}
        break;
      case 115: /* taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE */
{  yy_destructor(yypParser,38,&yymsp[0].minor);
#line 270 "lemon.html.yy"
{
}
#line 2195 "lemon.html.c"
}
        break;
      case 116: /* taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE */
{  yy_destructor(yypParser,39,&yymsp[0].minor);
#line 272 "lemon.html.yy"
{
}
#line 2203 "lemon.html.c"
}
        break;
      case 117: /* taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE */
{  yy_destructor(yypParser,40,&yymsp[0].minor);
#line 274 "lemon.html.yy"
{
}
#line 2211 "lemon.html.c"
}
        break;
      case 121: /* taginputcheckedvalue ::= spaces PROP_INPUT_CHECKED_VALUE ASSIGMENT */
#line 282 "lemon.html.yy"
{
}
#line 2218 "lemon.html.c"
  yy_destructor(yypParser,41,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 123: /* taginputuncheckedvalue ::= spaces PROP_INPUT_UNCHECKED_VALUE ASSIGMENT */
#line 286 "lemon.html.yy"
{
}
#line 2226 "lemon.html.c"
  yy_destructor(yypParser,42,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 125: /* taginputpropertyinputname ::= spaces PROP_INPUT_NAME ASSIGMENT */
#line 290 "lemon.html.yy"
{
}
#line 2234 "lemon.html.c"
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 127: /* taginputpropertysequencename ::= spaces PROP_INPUT_SEQUENCE_NAME ASSIGMENT */
#line 294 "lemon.html.yy"
{
}
#line 2242 "lemon.html.c"
  yy_destructor(yypParser,44,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 129: /* taginputpropertysequenceschemaname ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT */
#line 298 "lemon.html.yy"
{
}
#line 2250 "lemon.html.c"
  yy_destructor(yypParser,45,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 131: /* taginputpropertymasteritemname ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT */
#line 303 "lemon.html.yy"
{
}
#line 2258 "lemon.html.c"
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 133: /* taginputpropertyinputtype ::= spaces PROP_INPUT_TYPE ASSIGMENT */
#line 307 "lemon.html.yy"
{
}
#line 2266 "lemon.html.c"
  yy_destructor(yypParser,47,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 135: /* taginputpropertyinputvalue ::= spaces PROP_INPUT_VALUE ASSIGMENT */
#line 311 "lemon.html.yy"
{
}
#line 2274 "lemon.html.c"
  yy_destructor(yypParser,48,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 137: /* taginputpropertydefaultvalue ::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT */
#line 315 "lemon.html.yy"
{
}
#line 2282 "lemon.html.c"
  yy_destructor(yypParser,49,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 139: /* taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT */
#line 319 "lemon.html.yy"
{
}
#line 2290 "lemon.html.c"
  yy_destructor(yypParser,50,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 141: /* taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT */
#line 323 "lemon.html.yy"
{
}
#line 2298 "lemon.html.c"
  yy_destructor(yypParser,51,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 143: /* taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT */
#line 327 "lemon.html.yy"
{
}
#line 2306 "lemon.html.c"
  yy_destructor(yypParser,52,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 145: /* taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT */
#line 331 "lemon.html.yy"
{
}
#line 2314 "lemon.html.c"
  yy_destructor(yypParser,53,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 147: /* taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED ASSIGMENT */
#line 335 "lemon.html.yy"
{
}
#line 2322 "lemon.html.c"
  yy_destructor(yypParser,54,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 149: /* taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT */
#line 339 "lemon.html.yy"
{
}
#line 2330 "lemon.html.c"
  yy_destructor(yypParser,55,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 151: /* taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT */
#line 343 "lemon.html.yy"
{
}
#line 2338 "lemon.html.c"
  yy_destructor(yypParser,56,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 153: /* taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT */
#line 347 "lemon.html.yy"
{
}
#line 2346 "lemon.html.c"
  yy_destructor(yypParser,57,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 155: /* taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT */
#line 351 "lemon.html.yy"
{
}
#line 2354 "lemon.html.c"
  yy_destructor(yypParser,58,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 156: /* taginputproperty ::= spaces PROPERTYID ASSIGMENT PROPERTYDATA */
      case 271: /* tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==271);
      case 318: /* tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==318);
#line 353 "lemon.html.yy"
{
}
#line 2364 "lemon.html.c"
  yy_destructor(yypParser,17,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 163: /* tagtableopen ::= TAG_TABLE_OPEN */
{  yy_destructor(yypParser,59,&yymsp[0].minor);
#line 368 "lemon.html.yy"
{
}
#line 2374 "lemon.html.c"
}
        break;
      case 165: /* tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,60,&yymsp[0].minor);
#line 372 "lemon.html.yy"
{
}
#line 2382 "lemon.html.c"
}
        break;
      case 177: /* tagtheadopen ::= TAG_THEAD_OPEN */
{  yy_destructor(yypParser,61,&yymsp[0].minor);
#line 395 "lemon.html.yy"
{
}
#line 2390 "lemon.html.c"
}
        break;
      case 180: /* tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,62,&yymsp[0].minor);
#line 400 "lemon.html.yy"
{
}
#line 2398 "lemon.html.c"
}
        break;
      case 186: /* tagtfootopen ::= TAG_TFOOT_OPEN */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 413 "lemon.html.yy"
{
}
#line 2406 "lemon.html.c"
}
        break;
      case 189: /* tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE */
{  yy_destructor(yypParser,64,&yymsp[0].minor);
#line 418 "lemon.html.yy"
{
}
#line 2414 "lemon.html.c"
}
        break;
      case 195: /* tagtbodyopen ::= TAG_TBODY_OPEN */
{  yy_destructor(yypParser,65,&yymsp[0].minor);
#line 431 "lemon.html.yy"
{
}
#line 2422 "lemon.html.c"
}
        break;
      case 198: /* tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,66,&yymsp[0].minor);
#line 436 "lemon.html.yy"
{
}
#line 2430 "lemon.html.c"
}
        break;
      case 205: /* tagtablerowopen ::= TAG_TR_OPEN */
{  yy_destructor(yypParser,67,&yymsp[0].minor);
#line 452 "lemon.html.yy"
{
}
#line 2438 "lemon.html.c"
}
        break;
      case 208: /* tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE */
{  yy_destructor(yypParser,68,&yymsp[0].minor);
#line 457 "lemon.html.yy"
{
}
#line 2446 "lemon.html.c"
}
        break;
      case 220: /* tagtablecoltdopen ::= TAG_TD_OPEN */
{  yy_destructor(yypParser,69,&yymsp[0].minor);
#line 480 "lemon.html.yy"
{
}
#line 2454 "lemon.html.c"
}
        break;
      case 223: /* tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE */
{  yy_destructor(yypParser,70,&yymsp[0].minor);
#line 485 "lemon.html.yy"
{
}
#line 2462 "lemon.html.c"
}
        break;
      case 235: /* tagtablecolthopen ::= TAG_TH_OPEN */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 507 "lemon.html.yy"
{
}
#line 2470 "lemon.html.c"
}
        break;
      case 238: /* tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE */
{  yy_destructor(yypParser,72,&yymsp[0].minor);
#line 512 "lemon.html.yy"
{
}
#line 2478 "lemon.html.c"
}
        break;
      case 244: /* tagtitleopen ::= TAG_TITLE_OPEN */
{  yy_destructor(yypParser,73,&yymsp[0].minor);
#line 525 "lemon.html.yy"
{
}
#line 2486 "lemon.html.c"
}
        break;
      case 245: /* tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,74,&yymsp[0].minor);
#line 526 "lemon.html.yy"
{
}
#line 2494 "lemon.html.c"
}
        break;
      case 251: /* taglinkopen ::= TAG_LINK_OPEN */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 539 "lemon.html.yy"
{
}
#line 2502 "lemon.html.c"
}
        break;
      case 252: /* taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE */
{  yy_destructor(yypParser,76,&yymsp[0].minor);
#line 540 "lemon.html.yy"
{
}
#line 2510 "lemon.html.c"
}
        break;
      case 258: /* tagmetaopen ::= TAG_META_OPEN */
{  yy_destructor(yypParser,77,&yymsp[0].minor);
#line 554 "lemon.html.yy"
{
}
#line 2518 "lemon.html.c"
}
        break;
      case 259: /* tagmetablockclose ::= TAG_META_BLOCK_CLOSE */
{  yy_destructor(yypParser,78,&yymsp[0].minor);
#line 555 "lemon.html.yy"
{
}
#line 2526 "lemon.html.c"
}
        break;
      case 265: /* tagstyleopen ::= TAG_STYLE_OPEN */
{  yy_destructor(yypParser,79,&yymsp[0].minor);
#line 569 "lemon.html.yy"
{
}
#line 2534 "lemon.html.c"
}
        break;
      case 266: /* tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,80,&yymsp[0].minor);
#line 570 "lemon.html.yy"
{
}
#line 2542 "lemon.html.c"
}
        break;
      case 269: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA */
#line 576 "lemon.html.yy"
{
}
#line 2549 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 270: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA */
#line 577 "lemon.html.yy"
{
}
#line 2558 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 277: /* tagscriptopen ::= TAG_SCRIPT_OPEN */
{  yy_destructor(yypParser,83,&yymsp[0].minor);
#line 592 "lemon.html.yy"
{
}
#line 2568 "lemon.html.c"
}
        break;
      case 278: /* tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE */
{  yy_destructor(yypParser,84,&yymsp[0].minor);
#line 593 "lemon.html.yy"
{
}
#line 2576 "lemon.html.c"
}
        break;
      case 282: /* tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 602 "lemon.html.yy"
{
}
#line 2584 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 284: /* tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 606 "lemon.html.yy"
{
}
#line 2594 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 290: /* taghtmlopen ::= TAG_HTML_OPEN */
{  yy_destructor(yypParser,85,&yymsp[0].minor);
#line 619 "lemon.html.yy"
{
}
#line 2604 "lemon.html.c"
}
        break;
      case 291: /* taghtmlblockclose ::= TAG_HTML_BLOCK_CLOSE */
{  yy_destructor(yypParser,86,&yymsp[0].minor);
#line 621 "lemon.html.yy"
{
}
#line 2612 "lemon.html.c"
}
        break;
      case 304: /* tagbodyopen ::= TAG_BODY_OPEN */
{  yy_destructor(yypParser,87,&yymsp[0].minor);
#line 646 "lemon.html.yy"
{
}
#line 2620 "lemon.html.c"
}
        break;
      case 305: /* tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,88,&yymsp[0].minor);
#line 648 "lemon.html.yy"
{
}
#line 2628 "lemon.html.c"
}
        break;
      case 310: /* tagheadopen ::= TAG_HEAD_OPEN */
{  yy_destructor(yypParser,89,&yymsp[0].minor);
#line 663 "lemon.html.yy"
{
}
#line 2636 "lemon.html.c"
}
        break;
      case 311: /* tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,90,&yymsp[0].minor);
#line 665 "lemon.html.yy"
{
}
#line 2644 "lemon.html.c"
}
        break;
      case 315: /* tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,17,&yymsp[-2].minor);
#line 679 "lemon.html.yy"
{
}
#line 2652 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 319: /* tagclosechar ::= TAG_CLOSE */
{  yy_destructor(yypParser,91,&yymsp[0].minor);
#line 693 "lemon.html.yy"
{
}
#line 2662 "lemon.html.c"
}
        break;
      case 320: /* tagclosechar ::= SPACE TAG_CLOSE */
{  yy_destructor(yypParser,7,&yymsp[-1].minor);
#line 694 "lemon.html.yy"
{
}
#line 2670 "lemon.html.c"
  yy_destructor(yypParser,91,&yymsp[0].minor);
}
        break;
      case 324: /* htmlandspace ::= HTMLTEXT */
      case 326: /* htmltext ::= HTMLTEXT */ yytestcase(yyruleno==326);
{  yy_destructor(yypParser,92,&yymsp[0].minor);
#line 706 "lemon.html.yy"
{
}
#line 2680 "lemon.html.c"
}
        break;
      case 325: /* htmlandspace ::= SPACE */
      case 333: /* space ::= SPACE */ yytestcase(yyruleno==333);
{  yy_destructor(yypParser,7,&yymsp[0].minor);
#line 707 "lemon.html.yy"
{
}
#line 2689 "lemon.html.c"
}
        break;
      case 334: /* enter ::= ENTER */
{  yy_destructor(yypParser,93,&yymsp[0].minor);
#line 731 "lemon.html.yy"
{
}
#line 2697 "lemon.html.c"
}
        break;
      default:
      /* (0) start ::= expressions */ yytestcase(yyruleno==0);
      /* (1) expressions ::= expressions expression */ yytestcase(yyruleno==1);
      /* (2) expressions ::= expression (OPTIMIZED OUT) */ assert(yyruleno!=2);
      /* (5) expression ::= space (OPTIMIZED OUT) */ assert(yyruleno!=5);
      /* (6) expression ::= enter (OPTIMIZED OUT) */ assert(yyruleno!=6);
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
#line 2956 "lemon.html.c"
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
