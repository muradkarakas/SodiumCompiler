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
#define YYNOCODE 284
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
#define YYNRULE              337
#define YY_MAX_SHIFT         233
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
#define YY_ACTTAB_COUNT (908)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   108,    4,    4,    4,    4,    4,    4,    4,    4,    4,
 /*    10 */  1199,   36,   36,   57,  859,  859,   36,   36,  732,  744,
 /*    20 */   134,  759,  632,  108,  108,  531,  531,  204,  531,  531,
 /*    30 */   531,  531,  531,  531,  725,  857,  102,  733,  733,  733,
 /*    40 */     9,  853,  853,   53,  722,  729,   12,  108,   44,  222,
 /*    50 */   221,  220,  219,  218,  217,  216,  215,  214,  213,  212,
 /*    60 */   211,  210,  209,  208,  207,  206,  205,  185,  232,  231,
 /*    70 */   633,  133,  642,  223,  202,  201,  200,  199,  198,  197,
 /*    80 */   196,  195,  194,  193,  192,  191,  190,  189,  188,  187,
 /*    90 */   186,  590,  713,    1,  634,  729,    1,  223,  202,  201,
 /*   100 */   200,  199,  198,  197,  196,  195,  194,  193,  192,  191,
 /*   110 */   190,  189,  188,  187,  186,  729,   45,  853,  853,  599,
 /*   120 */   163,  162,  161,  160,  159,  158,  157,  156,  155,  154,
 /*   130 */   153,  152,  151,  150,   41,   80,   79,   49,   61,   85,
 /*   140 */   594,   77,  710,   59,   84,   52,   76,   58,   38,   51,
 /*   150 */    48,  843,  594,  594,   37,  843,   30,  796,   41,  739,
 /*   160 */   796,   49,   98,   85,  719,   77,  689,  701,   84,  139,
 /*   170 */    76,  719,   38,   87,   48,  830,  859,  830,   37,  527,
 /*   180 */    30,    6,    6,   61,  589,  859,  691,  593,  589,  594,
 /*   190 */     6,    6,    6,    6,    6,    6,    6,    6,   58,  831,
 /*   200 */    51,  831,  227,   18,   18,  853,  853,  107,  822,   60,
 /*   210 */     5,  744,   50,  759,  764,   17,   18,  764,   55,  783,
 /*   220 */    18,  131,  853,   81,   19,   13,   13,    8,  687,  859,
 /*   230 */    74,   21,   74,   74,   54,  776,  540,  540,  573,   18,
 /*   240 */   695,   31,  573,   18,   88,  689,  540,  540,  540,  540,
 /*   250 */   540,  540,  540,   31,   23,  109,  857,   43,  816,  816,
 /*   260 */   846,  850,  107,   64,   60,   64,   64,  799,   99,   96,
 /*   270 */    17,  860,   21,   55,  225,   54,  135,  859,   11,   19,
 /*   280 */     7,   46,    8,    7,  163,  162,  161,  160,  159,  158,
 /*   290 */   157,  156,  155,  154,  153,  152,  151,  150,  853,  179,
 /*   300 */   177,  176,  175,  174,  173,  172,  171,  170,  169,  168,
 /*   310 */   167,  166,  165,  164,  566,  860,  859,  853,  853,  564,
 /*   320 */   798,   97,   82,  576,    2,  112,  591,   21,  121,  121,
 /*   330 */    54,  179,  177,  176,  175,  174,  173,  172,  171,  170,
 /*   340 */   169,  168,  167,  166,  165,  164,  185,   21,  112,   10,
 /*   350 */    54,  823,  710,  823,  719,   83,  815,  828,   83,  834,
 /*   360 */   843,   15,   96,  860,  185,   14,   96,  861,  687,  550,
 /*   370 */   551,  844,   10,  845,  859,  635,  636,  637,  857,   86,
 /*   380 */   738,   16,  859,   98,   16,  137,  853,  809,   13,  728,
 /*   390 */   809,   13,   13,   24,    5,  138,   50,  829,    3,  687,
 /*   400 */     3,  850,  860,  803,  143,  140,  824,  859,  824,  748,
 /*   410 */    96,  849,  762,   74,   97,   82,  758,    2,   97,   82,
 /*   420 */   810,    2,  837,  810,  816,  816,   24,    5,  184,   50,
 /*   430 */   843,    3,  850,    3,  525,   57,  748,   96,  525,  525,
 /*   440 */    21,  748,   96,   54,   21,  747,   64,   54,  843,   25,
 /*   450 */   779,   25,   25,  181,   47,   22,   47,  143,  140,  556,
 /*   460 */   860,  704,   97,   82,  184,    2,  729,   22,   22,  843,
 /*   470 */   550,  551,  859,  737,   15,  859,   98,   15,   14,  843,
 /*   480 */   778,   14,  778,  755,  790,   95,  772,  828,   21,   97,
 /*   490 */    82,   54,    2,  860,   97,   82,  848,    2,  853,  588,
 /*   500 */    22,  681,  104,  588,   22,  681,   28,   78,  859,   27,
 /*   510 */   552,  555,   42,  785,  859,   21,  785,  113,   54,   58,
 /*   520 */    21,   51,  578,   54,  696,  748,   94,  756,   88,   95,
 /*   530 */   771,  807,  714,  771,   91,  723,   23,  723,   23,   43,
 /*   540 */   113,   43,  579,  579,  757,  846,   21,  114,  740,   54,
 /*   550 */   814,   98,  748,  741,  575,  579,   98,  748,  860,  579,
 /*   560 */   131,  860,   81,  183,  705,   74,  103,   74,   74,  780,
 /*   570 */   114,  723,   23,  585,  768,   43,  775,  574,  782,   62,
 /*   580 */   789,  574,  579,   20,  801,  859,  849,   20,   20,   20,
 /*   590 */     9,  835,  784,   53,  860,  784,   12,  184,   44,  850,
 /*   600 */   860,  136,  844,  763,   63,  773,  763,  840,  110,  226,
 /*   610 */   635,  636,  637,  635,  636,  637,  184,  184,  821,  811,
 /*   620 */     5,  224,   50,  786,   62,  184,  111,  859,  184,  184,
 /*   630 */   184,  106,   25,  181,  687,  115,   35,  687,  765,  825,
 /*   640 */   567,  233,  230,  840,  184,  747,  184,   90,  747,   63,
 /*   650 */    93,  742,  101,   29,  136,   29,   29,   26,  115,   26,
 /*   660 */    26,   32,  528,  802,  849,  805,  812,  850,  859,  184,
 /*   670 */   850,  848,   33,   32,   23,  797,  787,   43,  797,  232,
 /*   680 */   231,  121,  121,  224,   33,   23,  184,   56,   43,   56,
 /*   690 */   233,  230,   65,  184,  184,  184,  184,  184,  145,  121,
 /*   700 */   121,  846,  228,  795,  105,  843,  557,  229,  766,  116,
 /*   710 */   631,   67,   68,  860,  631,  826,   89,   92,  743,  100,
 /*   720 */    69,  693,  808,   70,   71,   73,  690,  224,   59,  117,
 /*   730 */    52,  769,  116,   59,   75,   52,   35,   75,  229,  118,
 /*   740 */   119,   39,  120,  639,  640,  641,  141,  142,   74,  848,
 /*   750 */   122,   66,  117,   66,  860,  123,  844,  124,  844,  125,
 /*   760 */   149,  147,  118,  119,   40,  120,  806,  843,  144,   72,
 /*   770 */   126,  127,  794,  122,  128,  129,   65,  682,  123,  130,
 /*   780 */   124,  682,  125,  561,  146,  844,  561,  132,  793,  148,
 /*   790 */   628,  626,   72,  126,  127,   67,   68,  128,  129,  624,
 /*   800 */   622,  620,  130,  618,   69,  616,  791,   70,   71,   73,
 /*   810 */   132,  843,  614,  612,  610,  608,  606,  604,  602,  863,
 /*   820 */   601,  863,  629,  840,  627,   39,  625,  623,  621,  863,
 /*   830 */   178,  863,  619,  617,  615,  613,   29,  611,  609,  228,
 /*   840 */    26,  863,  607,  605,  603,  839,  180,  842,   40,  560,
 /*   850 */   678,  676,  182,  674,  672,  670,  559,  668,  666,  664,
 /*   860 */   662,  660,  658,  571,  656,  840,  654,  652,  650,  648,
 /*   870 */   569,  646,  840,  840,  840,  840,  840,  203,  680,  679,
 /*   880 */   863,  863,  677,  675,  673,  671,  669,  667,  665,  663,
 /*   890 */   863,  863,  661,  659,  657,  655,  653,  651,  649,  647,
 /*   900 */   644,  587,  645,  863,  863,   34,  572,  570,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   101,  101,  102,  103,  104,  105,  106,  107,  108,  109,
 /*    10 */    95,   96,   97,   98,    7,    7,  101,  102,   68,   69,
 /*    20 */     7,   71,  123,  124,  101,  101,  102,   19,  104,  105,
 /*    30 */   106,  107,  108,  109,  218,  101,  220,  221,  222,  223,
 /*    40 */   224,  101,  102,  227,   66,   67,  230,  124,  232,   41,
 /*    50 */    42,   43,   44,   45,   46,   47,   48,   49,   50,   51,
 /*    60 */    52,   53,   54,   55,   56,   57,   58,    7,   12,   13,
 /*    70 */   171,    7,  173,  174,  175,  176,  177,  178,  179,  180,
 /*    80 */   181,  182,  183,  184,  185,  186,  187,  188,  189,  190,
 /*    90 */   191,  123,   64,  170,   34,   67,  173,  174,  175,  176,
 /*   100 */   177,  178,  179,  180,  181,  182,  183,  184,  185,  186,
 /*   110 */   187,  188,  189,  190,  191,   67,  100,  101,  102,  151,
 /*   120 */   152,  153,  154,  155,  156,  157,  158,  159,  160,  161,
 /*   130 */   162,  163,  164,  165,  234,  199,  200,  237,  236,  239,
 /*   140 */   101,  241,   63,  207,  244,  209,  246,  211,  248,  213,
 /*   150 */   250,   91,  113,  114,  254,   91,  256,  255,  234,  225,
 /*   160 */   258,  237,  228,  239,   65,  241,   60,   61,  244,    7,
 /*   170 */   246,   65,  248,  123,  250,  275,    7,  277,  254,    1,
 /*   180 */   256,  101,  102,  281,  145,    7,  199,   18,  149,  150,
 /*   190 */   110,  111,  112,  113,  114,  115,  116,  117,  211,  275,
 /*   200 */   213,  277,    7,  101,  102,  101,  102,  127,  268,  129,
 /*   210 */   270,   69,  272,   71,  235,  135,  114,  238,  138,   78,
 /*   220 */   118,  119,  282,  121,  144,  101,  102,  147,   59,    7,
 /*   230 */    99,  192,  101,  102,  195,   76,  101,  102,  136,  137,
 /*   240 */   202,  203,  140,  141,  206,   60,  111,  112,  113,  114,
 /*   250 */   115,  116,  117,  215,  216,  205,  101,  219,  101,  102,
 /*   260 */   281,   92,  127,   99,  129,  101,  102,  123,  113,  114,
 /*   270 */   135,   93,  192,  138,  143,  195,    7,    7,  262,  144,
 /*   280 */   148,  265,  147,  151,  152,  153,  154,  155,  156,  157,
 /*   290 */   158,  159,  160,  161,  162,  163,  164,  165,  282,   19,
 /*   300 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   310 */    30,   31,   32,   33,   11,   93,    7,  101,  102,   10,
 /*   320 */   123,  166,  167,   14,  169,  101,   17,  192,  278,  279,
 /*   330 */   195,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   340 */    28,   29,   30,   31,   32,   33,    7,  192,  124,  101,
 /*   350 */   195,  271,   63,  273,   65,  139,   86,   87,  142,   89,
 /*   360 */    91,  113,  114,   93,    7,  113,  114,    0,   59,    2,
 /*   370 */     3,   91,  124,   34,    7,   35,   36,   37,  101,  123,
 /*   380 */   225,  226,    7,  228,  229,    7,  282,  263,  264,  123,
 /*   390 */   266,  267,  268,  269,  270,    7,  272,   88,  274,   59,
 /*   400 */   276,   92,   93,  259,  260,  261,  271,    7,  273,  113,
 /*   410 */   114,    7,   72,  282,  166,  167,  123,  169,  166,  167,
 /*   420 */   263,  169,  279,  266,  267,  268,  269,  270,  101,  272,
 /*   430 */    91,  274,   92,  276,   97,   98,  113,  114,  101,  102,
 /*   440 */   192,  113,  114,  195,  192,   70,  282,  195,   91,   99,
 /*   450 */   123,  101,  102,   19,  257,  101,  259,  260,  261,    5,
 /*   460 */    93,   62,  166,  167,  101,  169,   67,  113,  114,   91,
 /*   470 */     2,    3,    7,  225,  226,    7,  228,  229,  226,   91,
 /*   480 */   245,  229,  247,  231,   80,  233,  123,   87,  192,  166,
 /*   490 */   167,  195,  169,   93,  166,  167,   92,  169,  282,  145,
 /*   500 */   146,  193,  194,  149,  150,  197,  198,  199,    7,  201,
 /*   510 */   120,    4,  204,  249,    7,  192,  252,  101,  195,  211,
 /*   520 */   192,  213,   15,  195,  202,  229,  123,  231,  206,  233,
 /*   530 */   240,    6,  212,  243,  214,  215,  216,  215,  216,  219,
 /*   540 */   124,  219,  101,  102,  123,  281,  192,  101,  225,  195,
 /*   550 */    85,  228,  229,  225,  123,  114,  228,  229,   93,  118,
 /*   560 */   119,   93,  121,   19,  208,   99,  210,  101,  102,  242,
 /*   570 */   124,  215,  216,  142,   73,  219,   75,  136,   77,  236,
 /*   580 */    79,  140,  141,  217,   83,    7,    7,  221,  222,  223,
 /*   590 */   224,   90,  249,  227,   93,  252,  230,  101,  232,   92,
 /*   600 */    93,  101,   91,  235,  236,  242,  238,  280,  205,  143,
 /*   610 */    35,   36,   37,   35,   36,   37,  101,  101,  268,  123,
 /*   620 */   270,    7,  272,  123,  281,  101,  205,    7,  101,  101,
 /*   630 */   101,  123,  282,   19,   59,  101,   16,   59,  123,  123,
 /*   640 */   132,  133,  134,  280,  101,   70,  101,  123,   70,  281,
 /*   650 */   123,  123,  123,   99,  101,  101,  102,   99,  124,  101,
 /*   660 */   102,  203,    1,   84,    7,    6,  123,   92,    7,  101,
 /*   670 */    92,   92,  203,  215,  216,  255,  123,  219,  258,   12,
 /*   680 */    13,  278,  279,    7,  215,  216,  101,  130,  219,  132,
 /*   690 */   133,  134,  196,  101,  101,  101,  101,  101,   19,  278,
 /*   700 */   279,  281,    8,    6,  123,   91,  125,  126,  123,  101,
 /*   710 */   168,  196,  196,   93,  172,  123,  123,  123,  123,  123,
 /*   720 */   196,  200,    9,  196,  196,  196,  200,    7,  207,  101,
 /*   730 */   209,   74,  124,  207,  122,  209,   16,  125,  126,  101,
 /*   740 */   101,  196,  101,   38,   39,   40,   81,   82,  282,   92,
 /*   750 */   101,  251,  124,  253,   93,  101,   91,  101,   91,  101,
 /*   760 */    81,   82,  124,  124,  196,  124,    9,   91,    9,  101,
 /*   770 */   101,  101,    6,  124,  101,  101,  280,  193,  124,  101,
 /*   780 */   124,  197,  124,  128,    9,   91,  131,  101,    6,    9,
 /*   790 */     6,    6,  124,  124,  124,  280,  280,  124,  124,    6,
 /*   800 */     6,    6,  124,    6,  280,    6,  253,  280,  280,  280,
 /*   810 */   124,   91,    6,    6,    6,    6,    6,    6,    6,  283,
 /*   820 */     6,  283,    9,  280,    9,  280,    9,    9,    9,  283,
 /*   830 */     9,  283,    9,    9,    9,    9,  282,    9,    9,    8,
 /*   840 */   282,  283,    9,    9,    9,    6,    9,    6,  280,    9,
 /*   850 */     6,    6,    9,    6,    6,    6,    6,    6,    6,    6,
 /*   860 */     6,    6,    6,    6,    6,  280,    6,    6,    6,    6,
 /*   870 */     6,    6,  280,  280,  280,  280,  280,    9,    6,    9,
 /*   880 */   283,  283,    9,    9,    9,    9,    9,    9,    9,    9,
 /*   890 */   283,  283,    9,    9,    9,    9,    9,    9,    9,    9,
 /*   900 */     6,    6,    9,  283,  283,    9,    9,    9,
};
#define YY_SHIFT_USE_DFLT (908)
#define YY_SHIFT_COUNT    (233)
#define YY_SHIFT_MIN      (-50)
#define YY_SHIFT_MAX      (898)
static const short yy_shift_ofst[] = {
 /*     0 */   468,   60,    7,  501,  501,  309,  309,   64,   13,  578,
 /*    10 */   578,  270,  340,  270,  340,  575,  575,  507,  507,  169,
 /*    20 */   -50,  106,  169,  142,  400,  400,  465,  399,  289,  620,
 /*    30 */   269,  399,  -22,   28,  222,  222,  367,  579,  404,  339,
 /*    40 */   339,  657,  614,  614,  614,  178,  357,  269,  357,  357,
 /*    50 */   357,  357,  357,  357,  357,  222,  378,  222,   48,   48,
 /*    60 */   162,  579,  404,  657,  661,  357,  357,  357,  357,  357,
 /*    70 */   357,  357,  375,  357,  222,  388,    7,    7,   79,   99,
 /*    80 */    79,  195,  705,  720,  141,  159,    7,    7,    7,    7,
 /*    90 */     7,    7,    7,    7,    7,    7,    7,    7,    7,    7,
 /*   100 */     7,    7,    7,    7,  185,    7,    7,  303,    8,  676,
 /*   110 */   676,  676,    7,    7,    7,    7,    7,    7,    7,    7,
 /*   120 */     7,  434,    7,    7,    7,    7,    7,    7,    7,    7,
 /*   130 */     7,  454,    7,  280,  312,  665,  679,  667,  694,   56,
 /*   140 */   525,  713,  757,  659,  697,  759,  766,  775,  782,  780,
 /*   150 */   784,  785,  793,  794,  795,  797,  799,  806,  807,  808,
 /*   160 */   809,  810,  811,  812,  813,  815,  817,  818,  819,  823,
 /*   170 */   824,  825,  826,  828,  829,  833,  834,  835,  814,  821,
 /*   180 */   839,  837,  841,  843,  544,  511,  844,  845,  847,  848,
 /*   190 */   849,  851,  852,  853,  854,  855,  856,  858,  860,  861,
 /*   200 */   862,  863,  865,  872,  868,  870,  873,  874,  875,  876,
 /*   210 */   877,  878,  879,  880,  883,  884,  885,  886,  887,  888,
 /*   220 */   889,  890,  893,  894,  511,  895,  896,  831,  840,  850,
 /*   230 */   857,  897,  898,  864,
};
#define YY_REDUCE_USE_DFLT (-185)
#define YY_REDUCE_COUNT (132)
#define YY_REDUCE_MIN   (-184)
#define YY_REDUCE_MAX   (686)
static const short yy_reduce_ofst[] = {
 /*     0 */   -85, -101,  -77, -100,  -76,   80,  135,  -32,  132,  248,
 /*    10 */   155,  124,  252,  157,  296,  323,  328,  102,  441,  354,
 /*    20 */  -184,  308,   39,  366,  350,  -60,   16,   38,  -64,  216,
 /*    30 */   197,  322,  320,  356,  131,  466,  337,  -98,  343,  327,
 /*    40 */   363,  368,   50,  403,  421,  164,  496,  144,  500,  515,
 /*    50 */   516,  524,  527,  528,  529,  554,  508,  558,  458,  469,
 /*    60 */   557,  420,  264,  -21,  104,  543,  553,  585,  592,  593,
 /*    70 */   594,  595,  -66,  596,  104,  581,  545,  568,  521,  -13,
 /*    80 */   526,  612,  542,  431,  235,  290,  224,  416,  446,  534,
 /*    90 */   608,  628,  638,  639,  641,  649,  654,  656,  658,  668,
 /*   100 */   669,  670,  673,  674,  584,  678,  686,  655,  277,  256,
 /*   110 */   266,  293,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   120 */   277,  143,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   130 */   277,  390,  277,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    10 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    20 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    30 */  1198, 1198, 1198, 1198, 1189, 1189, 1198, 1198, 1198, 1198,
 /*    40 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    50 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    60 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*    70 */  1198, 1198, 1198, 1198, 1188, 1198, 1198, 1198, 1031, 1198,
 /*    80 */  1029, 1198,  967, 1198, 1114, 1107, 1036, 1034, 1039, 1054,
 /*    90 */  1052, 1057, 1045, 1043, 1063, 1097, 1089, 1087, 1082, 1091,
 /*   100 */  1022, 1020, 1067, 1048, 1198,  890,  899, 1198, 1198, 1198,
 /*   110 */  1198, 1198, 1037, 1035, 1040, 1055, 1053, 1058, 1046, 1044,
 /*   120 */  1064, 1173, 1098, 1090, 1088, 1083, 1023, 1021, 1068, 1049,
 /*   130 */   891, 1198,  900, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   140 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   150 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   160 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   170 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   180 */  1198, 1198, 1198, 1198, 1198, 1196, 1198, 1198, 1198, 1198,
 /*   190 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   200 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   210 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   220 */  1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 /*   230 */  1198, 1198, 1198, 1198,
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
  "tagcontrolblockblockclose",  "tagcontrolblockcontent",  "tagcontrolblockproperty",  "opt__spaces_enters",
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
 /*  51 */ "tagcontrolblockfullopen ::= tagcontrolblockopen spaces_enters tagcontrolblockproperties tagclosechar",
 /*  52 */ "tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN",
 /*  53 */ "tagcontrolblockclosefull ::= tagcontrolblockblockclose",
 /*  54 */ "tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE",
 /*  55 */ "tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent",
 /*  56 */ "tagcontrolblockcontents ::= tagcontrolblockcontent",
 /*  57 */ "tagcontrolblockcontent ::= tagtree",
 /*  58 */ "tagcontrolblockcontent ::= space",
 /*  59 */ "tagcontrolblockcontent ::= enter",
 /*  60 */ "tagcontrolblockcontent ::= htmltext",
 /*  61 */ "tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty",
 /*  62 */ "tagcontrolblockproperties ::= tagcontrolblockproperty",
 /*  63 */ "tagcontrolblockproperty ::= PROP_CONTROLBLOCK_BLOCK_NAME opt__spaces_enters ASSIGMENT opt__spaces_enters PROPERTYDATA",
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
 /* 327 */ "opt__spaces_enters ::= spaces_enters",
 /* 328 */ "opt__spaces_enters ::=",
 /* 329 */ "spaces_enters ::= spaces_enters spaces_enter",
 /* 330 */ "spaces_enters ::= spaces_enter",
 /* 331 */ "spaces_enter ::= space",
 /* 332 */ "spaces_enter ::= enter",
 /* 333 */ "spaces ::= spaces space",
 /* 334 */ "spaces ::= space",
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

    Token *token = (yypminor->yy0);
    if (token->tokenStr != NULL) {
        if (token->tokenStr[0] == '\n') {
            printf("\n%4d: ", session->lineNumberOuter);
        } else {
            printf("%.*s", token->tokenStrLength, token->tokenStr);
        }
    }

#line 1199 "lemon.html.c"
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
    case 101: /* space */
    case 102: /* enter */
    case 103: /* tagheadcontents */
    case 104: /* tagheadcontent */
    case 105: /* tagtitle */
    case 106: /* tagscript */
    case 107: /* tagstyle */
    case 108: /* taglink */
    case 109: /* tagmeta */
    case 110: /* tagbodycontents */
    case 111: /* tagbodycontent */
    case 112: /* htsqls */
    case 113: /* tagtable */
    case 114: /* htmltext */
    case 115: /* tagdatablock */
    case 116: /* tagcontrolblock */
    case 117: /* tagdatalist */
    case 118: /* tagtree */
    case 119: /* tagtreefullopen */
    case 120: /* tagtreeblockclosefull */
    case 121: /* tagtreeopen */
    case 122: /* tagtreeproperties */
    case 123: /* tagclosechar */
    case 124: /* spaces */
    case 125: /* tagtreeproperty */
    case 126: /* tagtreepropertyid */
    case 127: /* tagdatalistfullopen */
    case 128: /* tagdatalistblockclosefull */
    case 129: /* tagdatalistopen */
    case 130: /* datalistproperties */
    case 131: /* tagdatalistblockclose */
    case 132: /* datalistproperty */
    case 133: /* tagdatalistpropertyid */
    case 134: /* tagdatalistpropertyconnectionname */
    case 135: /* tagcontrolblockfullopen */
    case 136: /* tagcontrolblockclosefull */
    case 137: /* tagcontrolblockcontents */
    case 138: /* tagcontrolblockopen */
    case 139: /* tagcontrolblockproperties */
    case 140: /* tagcontrolblockblockclose */
    case 141: /* tagcontrolblockcontent */
    case 142: /* tagcontrolblockproperty */
    case 143: /* opt__spaces_enters */
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
    case 266: /* taghtmlblockclose */
    case 267: /* taghtmlcontent */
    case 268: /* tagbody */
    case 269: /* taghead */
    case 270: /* tagbodyfullopen */
    case 271: /* tagbodyblockclosefull */
    case 272: /* tagbodyopen */
    case 273: /* tagbodyblockclose */
    case 274: /* tagheadfullopen */
    case 275: /* tagheadblockclosefull */
    case 276: /* tagheadopen */
    case 277: /* tagheadblockclose */
    case 278: /* tagpropertieswithreturnvalues */
    case 279: /* tagpropertywithreturnvalue */
    case 280: /* tagproperty */
    case 281: /* htmlandspace */
    case 282: /* spaces_enter */
{
#line 45 "lemon.html.yy"

    /*Token *token = (yypminor->yy0);
    if (token->tokenStr != NULL) {
        if (token->tokenStr[0] == '\n') {
            printf("\n%4d: ", session->lineNumberOuter);
        } else {
            printf("%.*s", token->tokenStrLength, token->tokenStr);
        }
    }*/

#line 1404 "lemon.html.c"
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
  { 135, 4 },
  { 138, 1 },
  { 136, 1 },
  { 140, 1 },
  { 137, 2 },
  { 137, 1 },
  { 141, 1 },
  { 141, 1 },
  { 141, 1 },
  { 141, 1 },
  { 139, 2 },
  { 139, 1 },
  { 142, 5 },
  { 115, 2 },
  { 115, 3 },
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
  { 113, 2 },
  { 113, 3 },
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
  { 105, 2 },
  { 105, 3 },
  { 234, 2 },
  { 234, 3 },
  { 235, 1 },
  { 237, 1 },
  { 238, 1 },
  { 108, 1 },
  { 108, 2 },
  { 239, 3 },
  { 239, 3 },
  { 240, 1 },
  { 241, 1 },
  { 243, 1 },
  { 109, 1 },
  { 109, 2 },
  { 244, 3 },
  { 244, 3 },
  { 245, 1 },
  { 246, 1 },
  { 247, 1 },
  { 107, 2 },
  { 107, 3 },
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
  { 106, 2 },
  { 106, 3 },
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
  { 270, 2 },
  { 270, 3 },
  { 271, 1 },
  { 272, 1 },
  { 273, 1 },
  { 269, 2 },
  { 269, 3 },
  { 274, 1 },
  { 275, 1 },
  { 276, 1 },
  { 277, 1 },
  { 205, 1 },
  { 278, 2 },
  { 278, 1 },
  { 279, 3 },
  { 196, 2 },
  { 196, 1 },
  { 280, 4 },
  { 123, 1 },
  { 123, 2 },
  { 242, 1 },
  { 236, 2 },
  { 236, 1 },
  { 281, 1 },
  { 281, 1 },
  { 114, 1 },
  { 143, 1 },
  { 143, 0 },
  { 99, 2 },
  { 99, 1 },
  { 282, 1 },
  { 282, 1 },
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
      case 0: /* start ::= expressions */
{  yy_destructor(yypParser,96,&yymsp[0].minor);
#line 56 "lemon.html.yy"
{
}
#line 2051 "lemon.html.c"
}
        break;
      case 1: /* expressions ::= expressions expression */
{  yy_destructor(yypParser,96,&yymsp[-1].minor);
#line 58 "lemon.html.yy"
{
}
#line 2059 "lemon.html.c"
  yy_destructor(yypParser,97,&yymsp[0].minor);
}
        break;
      case 2: /* expressions ::= expression */
{  yy_destructor(yypParser,97,&yymsp[0].minor);
#line 59 "lemon.html.yy"
{
}
#line 2068 "lemon.html.c"
}
        break;
      case 3: /* expression ::= tagdoctype spaces_enters taghtml END_OF_FILE */
{  yy_destructor(yypParser,98,&yymsp[-3].minor);
#line 61 "lemon.html.yy"
{
}
#line 2076 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-2].minor);
  yy_destructor(yypParser,100,&yymsp[-1].minor);
  yy_destructor(yypParser,1,&yymsp[0].minor);
}
        break;
      case 4: /* expression ::= tagdoctype spaces_enters taghtml spaces_enters END_OF_FILE */
{  yy_destructor(yypParser,98,&yymsp[-4].minor);
#line 62 "lemon.html.yy"
{
}
#line 2087 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-3].minor);
  yy_destructor(yypParser,100,&yymsp[-2].minor);
  yy_destructor(yypParser,99,&yymsp[-1].minor);
  yy_destructor(yypParser,1,&yymsp[0].minor);
}
        break;
      case 5: /* expression ::= space */
      case 9: /* tagheadcontent ::= space */ yytestcase(yyruleno==9);
      case 20: /* tagbodycontent ::= space */ yytestcase(yyruleno==20);
      case 58: /* tagcontrolblockcontent ::= space */ yytestcase(yyruleno==58);
      case 73: /* tagdatablockcontent ::= space */ yytestcase(yyruleno==73);
      case 294: /* taghtmlcontent ::= space */ yytestcase(yyruleno==294);
      case 331: /* spaces_enter ::= space */ yytestcase(yyruleno==331);
      case 334: /* spaces ::= space */ yytestcase(yyruleno==334);
{  yy_destructor(yypParser,101,&yymsp[0].minor);
#line 63 "lemon.html.yy"
{
}
#line 2106 "lemon.html.c"
}
        break;
      case 6: /* expression ::= enter */
      case 10: /* tagheadcontent ::= enter */ yytestcase(yyruleno==10);
      case 21: /* tagbodycontent ::= enter */ yytestcase(yyruleno==21);
      case 59: /* tagcontrolblockcontent ::= enter */ yytestcase(yyruleno==59);
      case 295: /* taghtmlcontent ::= enter */ yytestcase(yyruleno==295);
      case 332: /* spaces_enter ::= enter */ yytestcase(yyruleno==332);
{  yy_destructor(yypParser,102,&yymsp[0].minor);
#line 64 "lemon.html.yy"
{
}
#line 2119 "lemon.html.c"
}
        break;
      case 7: /* tagheadcontents ::= tagheadcontents tagheadcontent */
{  yy_destructor(yypParser,103,&yymsp[-1].minor);
#line 66 "lemon.html.yy"
{
}
#line 2127 "lemon.html.c"
  yy_destructor(yypParser,104,&yymsp[0].minor);
}
        break;
      case 8: /* tagheadcontents ::= tagheadcontent */
{  yy_destructor(yypParser,104,&yymsp[0].minor);
#line 67 "lemon.html.yy"
{
}
#line 2136 "lemon.html.c"
}
        break;
      case 11: /* tagheadcontent ::= tagtitle */
{  yy_destructor(yypParser,105,&yymsp[0].minor);
#line 71 "lemon.html.yy"
{
}
#line 2144 "lemon.html.c"
}
        break;
      case 12: /* tagheadcontent ::= tagscript */
{  yy_destructor(yypParser,106,&yymsp[0].minor);
#line 72 "lemon.html.yy"
{
}
#line 2152 "lemon.html.c"
}
        break;
      case 13: /* tagheadcontent ::= tagstyle */
{  yy_destructor(yypParser,107,&yymsp[0].minor);
#line 73 "lemon.html.yy"
{
}
#line 2160 "lemon.html.c"
}
        break;
      case 14: /* tagheadcontent ::= taglink */
{  yy_destructor(yypParser,108,&yymsp[0].minor);
#line 74 "lemon.html.yy"
{
}
#line 2168 "lemon.html.c"
}
        break;
      case 15: /* tagheadcontent ::= tagmeta */
{  yy_destructor(yypParser,109,&yymsp[0].minor);
#line 75 "lemon.html.yy"
{
}
#line 2176 "lemon.html.c"
}
        break;
      case 16: /* tagbodycontents ::= tagbodycontents tagbodycontent */
{  yy_destructor(yypParser,110,&yymsp[-1].minor);
#line 77 "lemon.html.yy"
{
}
#line 2184 "lemon.html.c"
  yy_destructor(yypParser,111,&yymsp[0].minor);
}
        break;
      case 17: /* tagbodycontents ::= tagbodycontent */
{  yy_destructor(yypParser,111,&yymsp[0].minor);
#line 78 "lemon.html.yy"
{
}
#line 2193 "lemon.html.c"
}
        break;
      case 18: /* tagbodycontent ::= htsqls */
{  yy_destructor(yypParser,112,&yymsp[0].minor);
#line 80 "lemon.html.yy"
{
}
#line 2201 "lemon.html.c"
}
        break;
      case 19: /* tagbodycontent ::= tagtable */
      case 72: /* tagdatablockcontent ::= tagtable */ yytestcase(yyruleno==72);
      case 230: /* tagtablecolcontent ::= tagtable */ yytestcase(yyruleno==230);
{  yy_destructor(yypParser,113,&yymsp[0].minor);
#line 81 "lemon.html.yy"
{
}
#line 2211 "lemon.html.c"
}
        break;
      case 22: /* tagbodycontent ::= htmltext */
      case 60: /* tagcontrolblockcontent ::= htmltext */ yytestcase(yyruleno==60);
      case 74: /* tagdatablockcontent ::= htmltext */ yytestcase(yyruleno==74);
      case 228: /* tagtablecolcontent ::= htmltext */ yytestcase(yyruleno==228);
{  yy_destructor(yypParser,114,&yymsp[0].minor);
#line 84 "lemon.html.yy"
{
}
#line 2222 "lemon.html.c"
}
        break;
      case 23: /* htsqls ::= tagdatablock */
{  yy_destructor(yypParser,115,&yymsp[0].minor);
#line 86 "lemon.html.yy"
{
}
#line 2230 "lemon.html.c"
}
        break;
      case 24: /* htsqls ::= tagcontrolblock */
{  yy_destructor(yypParser,116,&yymsp[0].minor);
#line 87 "lemon.html.yy"
{
}
#line 2238 "lemon.html.c"
}
        break;
      case 25: /* htsqls ::= tagdatalist */
{  yy_destructor(yypParser,117,&yymsp[0].minor);
#line 88 "lemon.html.yy"
{
}
#line 2246 "lemon.html.c"
}
        break;
      case 26: /* tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD */
{  yy_destructor(yypParser,2,&yymsp[0].minor);
#line 90 "lemon.html.yy"
{
}
#line 2254 "lemon.html.c"
}
        break;
      case 27: /* tagdoctype ::= TAG_DOCTYPE_HTML */
{  yy_destructor(yypParser,3,&yymsp[0].minor);
#line 92 "lemon.html.yy"
{
}
#line 2262 "lemon.html.c"
}
        break;
      case 28: /* tagtree ::= tagtreefullopen tagtreeblockclosefull */
{  yy_destructor(yypParser,119,&yymsp[-1].minor);
#line 99 "lemon.html.yy"
{
}
#line 2270 "lemon.html.c"
  yy_destructor(yypParser,120,&yymsp[0].minor);
}
        break;
      case 29: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar */
{  yy_destructor(yypParser,121,&yymsp[-2].minor);
#line 100 "lemon.html.yy"
{
}
#line 2279 "lemon.html.c"
  yy_destructor(yypParser,122,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 30: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces */
{  yy_destructor(yypParser,121,&yymsp[-3].minor);
#line 101 "lemon.html.yy"
{
}
#line 2289 "lemon.html.c"
  yy_destructor(yypParser,122,&yymsp[-2].minor);
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 31: /* tagtreeopen ::= TAG_TREE_OPEN */
{  yy_destructor(yypParser,4,&yymsp[0].minor);
#line 103 "lemon.html.yy"
{
}
#line 2300 "lemon.html.c"
}
        break;
      case 32: /* tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE */
{  yy_destructor(yypParser,5,&yymsp[0].minor);
#line 105 "lemon.html.yy"
{
}
#line 2308 "lemon.html.c"
}
        break;
      case 33: /* tagtreeproperties ::= tagtreeproperties tagtreeproperty */
{  yy_destructor(yypParser,122,&yymsp[-1].minor);
#line 107 "lemon.html.yy"
{
}
#line 2316 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 34: /* tagtreeproperties ::= tagtreeproperty */
{  yy_destructor(yypParser,125,&yymsp[0].minor);
#line 108 "lemon.html.yy"
{
}
#line 2325 "lemon.html.c"
}
        break;
      case 35: /* tagtreeproperty ::= tagtreepropertyid PROPERTYDATA */
{  yy_destructor(yypParser,126,&yymsp[-1].minor);
#line 110 "lemon.html.yy"
{
}
#line 2333 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 36: /* tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 112 "lemon.html.yy"
{
}
#line 2342 "lemon.html.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 37: /* tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull */
{  yy_destructor(yypParser,127,&yymsp[-1].minor);
#line 118 "lemon.html.yy"
{
}
#line 2352 "lemon.html.c"
  yy_destructor(yypParser,128,&yymsp[0].minor);
}
        break;
      case 38: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar */
{  yy_destructor(yypParser,129,&yymsp[-2].minor);
#line 119 "lemon.html.yy"
{
}
#line 2361 "lemon.html.c"
  yy_destructor(yypParser,130,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 39: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces */
{  yy_destructor(yypParser,129,&yymsp[-3].minor);
#line 120 "lemon.html.yy"
{
}
#line 2371 "lemon.html.c"
  yy_destructor(yypParser,130,&yymsp[-2].minor);
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 40: /* tagdatalistopen ::= TAG_DATALIST_OPEN */
{  yy_destructor(yypParser,10,&yymsp[0].minor);
#line 122 "lemon.html.yy"
{
}
#line 2382 "lemon.html.c"
}
        break;
      case 41: /* tagdatalistblockclosefull ::= tagdatalistblockclose */
{  yy_destructor(yypParser,131,&yymsp[0].minor);
#line 124 "lemon.html.yy"
{
}
#line 2390 "lemon.html.c"
}
        break;
      case 42: /* tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE */
{  yy_destructor(yypParser,11,&yymsp[0].minor);
#line 126 "lemon.html.yy"
{
}
#line 2398 "lemon.html.c"
}
        break;
      case 43: /* datalistproperties ::= datalistproperties datalistproperty */
{  yy_destructor(yypParser,130,&yymsp[-1].minor);
#line 128 "lemon.html.yy"
{
}
#line 2406 "lemon.html.c"
  yy_destructor(yypParser,132,&yymsp[0].minor);
}
        break;
      case 44: /* datalistproperties ::= datalistproperty */
{  yy_destructor(yypParser,132,&yymsp[0].minor);
#line 129 "lemon.html.yy"
{
}
#line 2415 "lemon.html.c"
}
        break;
      case 45: /* datalistproperty ::= tagdatalistpropertyid PROPERTYDATA */
{  yy_destructor(yypParser,133,&yymsp[-1].minor);
#line 131 "lemon.html.yy"
{
}
#line 2423 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 46: /* tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 133 "lemon.html.yy"
{
}
#line 2432 "lemon.html.c"
  yy_destructor(yypParser,12,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 47: /* datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA */
{  yy_destructor(yypParser,134,&yymsp[-1].minor);
#line 135 "lemon.html.yy"
{
}
#line 2442 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 48: /* tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 137 "lemon.html.yy"
{
}
#line 2451 "lemon.html.c"
  yy_destructor(yypParser,13,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 49: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull */
{  yy_destructor(yypParser,135,&yymsp[-1].minor);
#line 144 "lemon.html.yy"
{
}
#line 2461 "lemon.html.c"
  yy_destructor(yypParser,136,&yymsp[0].minor);
}
        break;
      case 50: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull */
{  yy_destructor(yypParser,135,&yymsp[-2].minor);
#line 145 "lemon.html.yy"
{
}
#line 2470 "lemon.html.c"
  yy_destructor(yypParser,137,&yymsp[-1].minor);
  yy_destructor(yypParser,136,&yymsp[0].minor);
}
        break;
      case 51: /* tagcontrolblockfullopen ::= tagcontrolblockopen spaces_enters tagcontrolblockproperties tagclosechar */
{  yy_destructor(yypParser,138,&yymsp[-3].minor);
#line 147 "lemon.html.yy"
{
}
#line 2480 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-2].minor);
  yy_destructor(yypParser,139,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 52: /* tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN */
{  yy_destructor(yypParser,14,&yymsp[0].minor);
#line 149 "lemon.html.yy"
{
}
#line 2491 "lemon.html.c"
}
        break;
      case 53: /* tagcontrolblockclosefull ::= tagcontrolblockblockclose */
{  yy_destructor(yypParser,140,&yymsp[0].minor);
#line 151 "lemon.html.yy"
{
}
#line 2499 "lemon.html.c"
}
        break;
      case 54: /* tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 152 "lemon.html.yy"
{
}
#line 2507 "lemon.html.c"
}
        break;
      case 55: /* tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent */
{  yy_destructor(yypParser,137,&yymsp[-1].minor);
#line 154 "lemon.html.yy"
{
}
#line 2515 "lemon.html.c"
  yy_destructor(yypParser,141,&yymsp[0].minor);
}
        break;
      case 56: /* tagcontrolblockcontents ::= tagcontrolblockcontent */
{  yy_destructor(yypParser,141,&yymsp[0].minor);
#line 155 "lemon.html.yy"
{
}
#line 2524 "lemon.html.c"
}
        break;
      case 57: /* tagcontrolblockcontent ::= tagtree */
{  yy_destructor(yypParser,118,&yymsp[0].minor);
#line 157 "lemon.html.yy"
{
}
#line 2532 "lemon.html.c"
}
        break;
      case 61: /* tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty */
{  yy_destructor(yypParser,139,&yymsp[-1].minor);
#line 162 "lemon.html.yy"
{
}
#line 2540 "lemon.html.c"
  yy_destructor(yypParser,142,&yymsp[0].minor);
}
        break;
      case 62: /* tagcontrolblockproperties ::= tagcontrolblockproperty */
{  yy_destructor(yypParser,142,&yymsp[0].minor);
#line 163 "lemon.html.yy"
{
}
#line 2549 "lemon.html.c"
}
        break;
      case 63: /* tagcontrolblockproperty ::= PROP_CONTROLBLOCK_BLOCK_NAME opt__spaces_enters ASSIGMENT opt__spaces_enters PROPERTYDATA */
{  yy_destructor(yypParser,16,&yymsp[-4].minor);
#line 165 "lemon.html.yy"
{
}
#line 2557 "lemon.html.c"
  yy_destructor(yypParser,143,&yymsp[-3].minor);
  yy_destructor(yypParser,9,&yymsp[-2].minor);
  yy_destructor(yypParser,143,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 64: /* tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull */
{  yy_destructor(yypParser,144,&yymsp[-1].minor);
#line 174 "lemon.html.yy"
{
}
#line 2569 "lemon.html.c"
  yy_destructor(yypParser,145,&yymsp[0].minor);
}
        break;
      case 65: /* tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull */
{  yy_destructor(yypParser,144,&yymsp[-2].minor);
#line 175 "lemon.html.yy"
{
}
#line 2578 "lemon.html.c"
  yy_destructor(yypParser,146,&yymsp[-1].minor);
  yy_destructor(yypParser,145,&yymsp[0].minor);
}
        break;
      case 66: /* tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar */
{  yy_destructor(yypParser,147,&yymsp[-2].minor);
#line 176 "lemon.html.yy"
{
}
#line 2588 "lemon.html.c"
  yy_destructor(yypParser,148,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 67: /* tagdatablockopen ::= TAG_DATABLOCK_OPEN */
{  yy_destructor(yypParser,17,&yymsp[0].minor);
#line 178 "lemon.html.yy"
{
}
#line 2598 "lemon.html.c"
}
        break;
      case 68: /* tagdatablockblockclosefull ::= tagdatablockblockclose */
{  yy_destructor(yypParser,149,&yymsp[0].minor);
#line 180 "lemon.html.yy"
{
}
#line 2606 "lemon.html.c"
}
        break;
      case 69: /* tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE */
{  yy_destructor(yypParser,18,&yymsp[0].minor);
#line 182 "lemon.html.yy"
{
}
#line 2614 "lemon.html.c"
}
        break;
      case 70: /* tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent */
{  yy_destructor(yypParser,146,&yymsp[-1].minor);
#line 185 "lemon.html.yy"
{
}
#line 2622 "lemon.html.c"
  yy_destructor(yypParser,150,&yymsp[0].minor);
}
        break;
      case 71: /* tagdatablockcontents ::= tagdatablockcontent */
{  yy_destructor(yypParser,150,&yymsp[0].minor);
#line 186 "lemon.html.yy"
{
}
#line 2631 "lemon.html.c"
}
        break;
      case 75: /* tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty */
{  yy_destructor(yypParser,148,&yymsp[-1].minor);
#line 192 "lemon.html.yy"
{
}
#line 2639 "lemon.html.c"
  yy_destructor(yypParser,151,&yymsp[0].minor);
}
        break;
      case 76: /* tagdatablockproperties ::= tagdatablockproperty */
{  yy_destructor(yypParser,151,&yymsp[0].minor);
#line 194 "lemon.html.yy"
{
}
#line 2648 "lemon.html.c"
}
        break;
      case 77: /* tagdatablockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,7,&yymsp[-3].minor);
#line 196 "lemon.html.yy"
{
}
#line 2656 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 78: /* tagdatablockproperty ::= tagdatablockpropertyjoincondition PROPERTYDATA */
{  yy_destructor(yypParser,152,&yymsp[-1].minor);
#line 198 "lemon.html.yy"
{
}
#line 2667 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 79: /* tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 200 "lemon.html.yy"
{
}
#line 2676 "lemon.html.c"
  yy_destructor(yypParser,20,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 80: /* tagdatablockproperty ::= tagdatablockpropertyconnectionname PROPERTYDATA */
{  yy_destructor(yypParser,153,&yymsp[-1].minor);
#line 203 "lemon.html.yy"
{
}
#line 2686 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 81: /* tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 205 "lemon.html.yy"
{
}
#line 2695 "lemon.html.c"
  yy_destructor(yypParser,21,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 82: /* tagdatablockproperty ::= tagdatablockpropertyautogeneratedcolumns PROPERTYDATA */
{  yy_destructor(yypParser,154,&yymsp[-1].minor);
#line 208 "lemon.html.yy"
{
}
#line 2705 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 83: /* tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 210 "lemon.html.yy"
{
}
#line 2714 "lemon.html.c"
  yy_destructor(yypParser,22,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 84: /* tagdatablockproperty ::= tagdatablockpropertyrecordcount PROPERTYDATA */
{  yy_destructor(yypParser,155,&yymsp[-1].minor);
#line 212 "lemon.html.yy"
{
}
#line 2724 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 85: /* tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 214 "lemon.html.yy"
{
}
#line 2733 "lemon.html.c"
  yy_destructor(yypParser,23,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 86: /* tagdatablockproperty ::= tagdatablockpropertysourcename PROPERTYDATA */
{  yy_destructor(yypParser,156,&yymsp[-1].minor);
#line 216 "lemon.html.yy"
{
}
#line 2743 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 87: /* tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 218 "lemon.html.yy"
{
}
#line 2752 "lemon.html.c"
  yy_destructor(yypParser,24,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 88: /* tagdatablockproperty ::= tagdatablockpropertyschemaname PROPERTYDATA */
{  yy_destructor(yypParser,157,&yymsp[-1].minor);
#line 221 "lemon.html.yy"
{
}
#line 2762 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 89: /* tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 223 "lemon.html.yy"
{
}
#line 2771 "lemon.html.c"
  yy_destructor(yypParser,25,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 90: /* tagdatablockproperty ::= tagdatablockpropertyblockname PROPERTYDATA */
{  yy_destructor(yypParser,158,&yymsp[-1].minor);
#line 225 "lemon.html.yy"
{
}
#line 2781 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 91: /* tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 227 "lemon.html.yy"
{
}
#line 2790 "lemon.html.c"
  yy_destructor(yypParser,26,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 92: /* tagdatablockproperty ::= tagdatablockpropertykeycolumnname PROPERTYDATA */
{  yy_destructor(yypParser,159,&yymsp[-1].minor);
#line 229 "lemon.html.yy"
{
}
#line 2800 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 93: /* tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 231 "lemon.html.yy"
{
}
#line 2809 "lemon.html.c"
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 94: /* tagdatablockproperty ::= tagdatablockpropertymasterblockname PROPERTYDATA */
{  yy_destructor(yypParser,160,&yymsp[-1].minor);
#line 233 "lemon.html.yy"
{
}
#line 2819 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 95: /* tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 235 "lemon.html.yy"
{
}
#line 2828 "lemon.html.c"
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 96: /* tagdatablockproperty ::= tagdatablockpropertyinsertallowed PROPERTYDATA */
{  yy_destructor(yypParser,161,&yymsp[-1].minor);
#line 237 "lemon.html.yy"
{
}
#line 2838 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 97: /* tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 239 "lemon.html.yy"
{
}
#line 2847 "lemon.html.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 98: /* tagdatablockproperty ::= tagdatablockpropertydeleteallowed PROPERTYDATA */
{  yy_destructor(yypParser,162,&yymsp[-1].minor);
#line 241 "lemon.html.yy"
{
}
#line 2857 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 99: /* tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 243 "lemon.html.yy"
{
}
#line 2866 "lemon.html.c"
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 100: /* tagdatablockproperty ::= tagdatablockpropertyupdateallowed PROPERTYDATA */
{  yy_destructor(yypParser,163,&yymsp[-1].minor);
#line 245 "lemon.html.yy"
{
}
#line 2876 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 101: /* tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 247 "lemon.html.yy"
{
}
#line 2885 "lemon.html.c"
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 102: /* tagdatablockproperty ::= tagdatablockpropertywhereclause PROPERTYDATA */
{  yy_destructor(yypParser,164,&yymsp[-1].minor);
#line 250 "lemon.html.yy"
{
}
#line 2895 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 103: /* tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 252 "lemon.html.yy"
{
}
#line 2904 "lemon.html.c"
  yy_destructor(yypParser,32,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 104: /* tagdatablockproperty ::= tagdatablockpropertyorderbyclause PROPERTYDATA */
{  yy_destructor(yypParser,165,&yymsp[-1].minor);
#line 254 "lemon.html.yy"
{
}
#line 2914 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 105: /* tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 256 "lemon.html.yy"
{
}
#line 2923 "lemon.html.c"
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 106: /* taginput ::= taginputfullopen */
{  yy_destructor(yypParser,167,&yymsp[0].minor);
#line 264 "lemon.html.yy"
{
}
#line 2933 "lemon.html.c"
}
        break;
      case 107: /* taginput ::= taginputfullopen taginputblockclosefull */
{  yy_destructor(yypParser,167,&yymsp[-1].minor);
#line 265 "lemon.html.yy"
{
}
#line 2941 "lemon.html.c"
  yy_destructor(yypParser,168,&yymsp[0].minor);
}
        break;
      case 108: /* taginputfullopen ::= taginputopen taginputproperties tagclosechar */
{  yy_destructor(yypParser,169,&yymsp[-2].minor);
#line 266 "lemon.html.yy"
{
}
#line 2950 "lemon.html.c"
  yy_destructor(yypParser,170,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 109: /* taginputfullopen ::= taginputopen taginputproperties taginputshortclose */
{  yy_destructor(yypParser,169,&yymsp[-2].minor);
#line 267 "lemon.html.yy"
{
}
#line 2960 "lemon.html.c"
  yy_destructor(yypParser,170,&yymsp[-1].minor);
  yy_destructor(yypParser,171,&yymsp[0].minor);
}
        break;
      case 110: /* taginputshortclose ::= TAG_SHORT_CLOSE */
      case 321: /* tagshortclose ::= TAG_SHORT_CLOSE */ yytestcase(yyruleno==321);
{  yy_destructor(yypParser,34,&yymsp[0].minor);
#line 270 "lemon.html.yy"
{
}
#line 2971 "lemon.html.c"
}
        break;
      case 111: /* taginputopen ::= TAG_INPUT_OPEN */
{  yy_destructor(yypParser,35,&yymsp[0].minor);
#line 273 "lemon.html.yy"
{
}
#line 2979 "lemon.html.c"
}
        break;
      case 112: /* taginputopen ::= TAG_SELECT_OPEN */
{  yy_destructor(yypParser,36,&yymsp[0].minor);
#line 275 "lemon.html.yy"
{
}
#line 2987 "lemon.html.c"
}
        break;
      case 113: /* taginputopen ::= TAG_TEXTAREA_OPEN */
{  yy_destructor(yypParser,37,&yymsp[0].minor);
#line 277 "lemon.html.yy"
{
}
#line 2995 "lemon.html.c"
}
        break;
      case 114: /* taginputblockclosefull ::= taginputblockclose */
{  yy_destructor(yypParser,172,&yymsp[0].minor);
#line 279 "lemon.html.yy"
{
}
#line 3003 "lemon.html.c"
}
        break;
      case 115: /* taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE */
{  yy_destructor(yypParser,38,&yymsp[0].minor);
#line 281 "lemon.html.yy"
{
}
#line 3011 "lemon.html.c"
}
        break;
      case 116: /* taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE */
{  yy_destructor(yypParser,39,&yymsp[0].minor);
#line 283 "lemon.html.yy"
{
}
#line 3019 "lemon.html.c"
}
        break;
      case 117: /* taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE */
{  yy_destructor(yypParser,40,&yymsp[0].minor);
#line 285 "lemon.html.yy"
{
}
#line 3027 "lemon.html.c"
}
        break;
      case 118: /* taginputproperties ::= taginputproperties taginputproperty */
{  yy_destructor(yypParser,170,&yymsp[-1].minor);
#line 287 "lemon.html.yy"
{
}
#line 3035 "lemon.html.c"
  yy_destructor(yypParser,173,&yymsp[0].minor);
}
        break;
      case 119: /* taginputproperties ::= taginputproperty */
{  yy_destructor(yypParser,173,&yymsp[0].minor);
#line 289 "lemon.html.yy"
{
}
#line 3044 "lemon.html.c"
}
        break;
      case 120: /* taginputproperty ::= taginputcheckedvalue PROPERTYDATA */
{  yy_destructor(yypParser,174,&yymsp[-1].minor);
#line 291 "lemon.html.yy"
{
}
#line 3052 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 121: /* taginputcheckedvalue ::= spaces PROP_INPUT_CHECKED_VALUE ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 293 "lemon.html.yy"
{
}
#line 3061 "lemon.html.c"
  yy_destructor(yypParser,41,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 122: /* taginputproperty ::= taginputuncheckedvalue PROPERTYDATA */
{  yy_destructor(yypParser,175,&yymsp[-1].minor);
#line 295 "lemon.html.yy"
{
}
#line 3071 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 123: /* taginputuncheckedvalue ::= spaces PROP_INPUT_UNCHECKED_VALUE ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 297 "lemon.html.yy"
{
}
#line 3080 "lemon.html.c"
  yy_destructor(yypParser,42,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 124: /* taginputproperty ::= taginputpropertyinputname PROPERTYDATA */
{  yy_destructor(yypParser,176,&yymsp[-1].minor);
#line 299 "lemon.html.yy"
{
}
#line 3090 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 125: /* taginputpropertyinputname ::= spaces PROP_INPUT_NAME ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 301 "lemon.html.yy"
{
}
#line 3099 "lemon.html.c"
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 126: /* taginputproperty ::= taginputpropertysequencename PROPERTYDATA */
{  yy_destructor(yypParser,177,&yymsp[-1].minor);
#line 303 "lemon.html.yy"
{
}
#line 3109 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 127: /* taginputpropertysequencename ::= spaces PROP_INPUT_SEQUENCE_NAME ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 305 "lemon.html.yy"
{
}
#line 3118 "lemon.html.c"
  yy_destructor(yypParser,44,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 128: /* taginputproperty ::= taginputpropertysequenceschemaname PROPERTYDATA */
{  yy_destructor(yypParser,178,&yymsp[-1].minor);
#line 307 "lemon.html.yy"
{
}
#line 3128 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 129: /* taginputpropertysequenceschemaname ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 309 "lemon.html.yy"
{
}
#line 3137 "lemon.html.c"
  yy_destructor(yypParser,45,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 130: /* taginputproperty ::= taginputpropertymasteritemname PROPERTYDATA */
{  yy_destructor(yypParser,179,&yymsp[-1].minor);
#line 312 "lemon.html.yy"
{
}
#line 3147 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 131: /* taginputpropertymasteritemname ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 314 "lemon.html.yy"
{
}
#line 3156 "lemon.html.c"
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 132: /* taginputproperty ::= taginputpropertyinputtype PROPERTYDATA */
{  yy_destructor(yypParser,180,&yymsp[-1].minor);
#line 316 "lemon.html.yy"
{
}
#line 3166 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 133: /* taginputpropertyinputtype ::= spaces PROP_INPUT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 318 "lemon.html.yy"
{
}
#line 3175 "lemon.html.c"
  yy_destructor(yypParser,47,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 134: /* taginputproperty ::= taginputpropertyinputvalue PROPERTYDATA */
{  yy_destructor(yypParser,181,&yymsp[-1].minor);
#line 320 "lemon.html.yy"
{
}
#line 3185 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 135: /* taginputpropertyinputvalue ::= spaces PROP_INPUT_VALUE ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 322 "lemon.html.yy"
{
}
#line 3194 "lemon.html.c"
  yy_destructor(yypParser,48,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 136: /* taginputproperty ::= taginputpropertydefaultvalue PROPERTYDATA */
{  yy_destructor(yypParser,182,&yymsp[-1].minor);
#line 324 "lemon.html.yy"
{
}
#line 3204 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 137: /* taginputpropertydefaultvalue ::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 326 "lemon.html.yy"
{
}
#line 3213 "lemon.html.c"
  yy_destructor(yypParser,49,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 138: /* taginputproperty ::= taginputpropertycolumnname PROPERTYDATA */
{  yy_destructor(yypParser,183,&yymsp[-1].minor);
#line 328 "lemon.html.yy"
{
}
#line 3223 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 139: /* taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 330 "lemon.html.yy"
{
}
#line 3232 "lemon.html.c"
  yy_destructor(yypParser,50,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 140: /* taginputproperty ::= taginputpropertyformatmask PROPERTYDATA */
{  yy_destructor(yypParser,184,&yymsp[-1].minor);
#line 332 "lemon.html.yy"
{
}
#line 3242 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 141: /* taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 334 "lemon.html.yy"
{
}
#line 3251 "lemon.html.c"
  yy_destructor(yypParser,51,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 142: /* taginputproperty ::= taginputpropertydatatype PROPERTYDATA */
{  yy_destructor(yypParser,185,&yymsp[-1].minor);
#line 336 "lemon.html.yy"
{
}
#line 3261 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 143: /* taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 338 "lemon.html.yy"
{
}
#line 3270 "lemon.html.c"
  yy_destructor(yypParser,52,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 144: /* taginputproperty ::= taginputpropertymaxlength PROPERTYDATA */
{  yy_destructor(yypParser,186,&yymsp[-1].minor);
#line 340 "lemon.html.yy"
{
}
#line 3280 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 145: /* taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 342 "lemon.html.yy"
{
}
#line 3289 "lemon.html.c"
  yy_destructor(yypParser,53,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 146: /* taginputproperty ::= taginputpropertyinsertallowed PROPERTYDATA */
{  yy_destructor(yypParser,187,&yymsp[-1].minor);
#line 344 "lemon.html.yy"
{
}
#line 3299 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 147: /* taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 346 "lemon.html.yy"
{
}
#line 3308 "lemon.html.c"
  yy_destructor(yypParser,54,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 148: /* taginputproperty ::= taginputpropertyupdateallowed PROPERTYDATA */
{  yy_destructor(yypParser,188,&yymsp[-1].minor);
#line 348 "lemon.html.yy"
{
}
#line 3318 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 149: /* taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 350 "lemon.html.yy"
{
}
#line 3327 "lemon.html.c"
  yy_destructor(yypParser,55,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 150: /* taginputproperty ::= taginputpropertydatalistname PROPERTYDATA */
{  yy_destructor(yypParser,189,&yymsp[-1].minor);
#line 352 "lemon.html.yy"
{
}
#line 3337 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 151: /* taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 354 "lemon.html.yy"
{
}
#line 3346 "lemon.html.c"
  yy_destructor(yypParser,56,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 152: /* taginputproperty ::= taginputpropertylookupitemname PROPERTYDATA */
{  yy_destructor(yypParser,190,&yymsp[-1].minor);
#line 356 "lemon.html.yy"
{
}
#line 3356 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 153: /* taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 358 "lemon.html.yy"
{
}
#line 3365 "lemon.html.c"
  yy_destructor(yypParser,57,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 154: /* taginputproperty ::= taginputpropertylookupitemblockname PROPERTYDATA */
{  yy_destructor(yypParser,191,&yymsp[-1].minor);
#line 360 "lemon.html.yy"
{
}
#line 3375 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 155: /* taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,124,&yymsp[-2].minor);
#line 362 "lemon.html.yy"
{
}
#line 3384 "lemon.html.c"
  yy_destructor(yypParser,58,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 156: /* taginputproperty ::= spaces PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,124,&yymsp[-3].minor);
#line 364 "lemon.html.yy"
{
}
#line 3394 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 157: /* tagtable ::= tagtablefullopen tagtableblockclosefull */
{  yy_destructor(yypParser,192,&yymsp[-1].minor);
#line 371 "lemon.html.yy"
{
}
#line 3405 "lemon.html.c"
  yy_destructor(yypParser,193,&yymsp[0].minor);
}
        break;
      case 158: /* tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull */
{  yy_destructor(yypParser,192,&yymsp[-2].minor);
#line 372 "lemon.html.yy"
{
}
#line 3414 "lemon.html.c"
  yy_destructor(yypParser,194,&yymsp[-1].minor);
  yy_destructor(yypParser,193,&yymsp[0].minor);
}
        break;
      case 159: /* tagtablefullopen ::= tagtableopen tagclosechar */
{  yy_destructor(yypParser,195,&yymsp[-1].minor);
#line 374 "lemon.html.yy"
{
}
#line 3424 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 160: /* tagtablefullopen ::= tagtableopen tagclosechar spaces */
{  yy_destructor(yypParser,195,&yymsp[-2].minor);
#line 375 "lemon.html.yy"
{
}
#line 3433 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 161: /* tagtablefullopen ::= tagtableopen tagproperties tagclosechar */
{  yy_destructor(yypParser,195,&yymsp[-2].minor);
#line 376 "lemon.html.yy"
{
}
#line 3443 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 162: /* tagtablefullopen ::= tagtableopen tagproperties tagclosechar spaces */
{  yy_destructor(yypParser,195,&yymsp[-3].minor);
#line 377 "lemon.html.yy"
{
}
#line 3453 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-2].minor);
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 163: /* tagtableopen ::= TAG_TABLE_OPEN */
{  yy_destructor(yypParser,59,&yymsp[0].minor);
#line 379 "lemon.html.yy"
{
}
#line 3464 "lemon.html.c"
}
        break;
      case 164: /* tagtableblockclosefull ::= tagtableblockclose */
{  yy_destructor(yypParser,197,&yymsp[0].minor);
#line 381 "lemon.html.yy"
{
}
#line 3472 "lemon.html.c"
}
        break;
      case 165: /* tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,60,&yymsp[0].minor);
#line 383 "lemon.html.yy"
{
}
#line 3480 "lemon.html.c"
}
        break;
      case 166: /* tablecontent ::= tagthead tagtbody tagtfoot */
{  yy_destructor(yypParser,198,&yymsp[-2].minor);
#line 389 "lemon.html.yy"
{
}
#line 3488 "lemon.html.c"
  yy_destructor(yypParser,199,&yymsp[-1].minor);
  yy_destructor(yypParser,200,&yymsp[0].minor);
}
        break;
      case 167: /* tablecontent ::= tagthead tagtfoot tagtbody */
{  yy_destructor(yypParser,198,&yymsp[-2].minor);
#line 390 "lemon.html.yy"
{
}
#line 3498 "lemon.html.c"
  yy_destructor(yypParser,200,&yymsp[-1].minor);
  yy_destructor(yypParser,199,&yymsp[0].minor);
}
        break;
      case 168: /* tablecontent ::= tagthead tagtbody */
{  yy_destructor(yypParser,198,&yymsp[-1].minor);
#line 391 "lemon.html.yy"
{
}
#line 3508 "lemon.html.c"
  yy_destructor(yypParser,199,&yymsp[0].minor);
}
        break;
      case 169: /* tablecontent ::= tagtbody tagtfoot */
{  yy_destructor(yypParser,199,&yymsp[-1].minor);
#line 392 "lemon.html.yy"
{
}
#line 3517 "lemon.html.c"
  yy_destructor(yypParser,200,&yymsp[0].minor);
}
        break;
      case 170: /* tablecontent ::= tagtbody */
{  yy_destructor(yypParser,199,&yymsp[0].minor);
#line 393 "lemon.html.yy"
{
}
#line 3526 "lemon.html.c"
}
        break;
      case 171: /* tagthead ::= tagtheadfullopen tagtheadblockclosefull */
{  yy_destructor(yypParser,201,&yymsp[-1].minor);
#line 400 "lemon.html.yy"
{
}
#line 3534 "lemon.html.c"
  yy_destructor(yypParser,202,&yymsp[0].minor);
}
        break;
      case 172: /* tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull */
{  yy_destructor(yypParser,201,&yymsp[-2].minor);
#line 401 "lemon.html.yy"
{
}
#line 3543 "lemon.html.c"
  yy_destructor(yypParser,203,&yymsp[-1].minor);
  yy_destructor(yypParser,202,&yymsp[0].minor);
}
        break;
      case 173: /* tagtheadfullopen ::= tagtheadopen tagclosechar */
{  yy_destructor(yypParser,204,&yymsp[-1].minor);
#line 402 "lemon.html.yy"
{
}
#line 3553 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 174: /* tagtheadfullopen ::= tagtheadopen tagclosechar spaces */
{  yy_destructor(yypParser,204,&yymsp[-2].minor);
#line 403 "lemon.html.yy"
{
}
#line 3562 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 175: /* tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,204,&yymsp[-2].minor);
#line 404 "lemon.html.yy"
{
}
#line 3572 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 176: /* tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces */
{  yy_destructor(yypParser,204,&yymsp[-3].minor);
#line 405 "lemon.html.yy"
{
}
#line 3582 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-2].minor);
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 177: /* tagtheadopen ::= TAG_THEAD_OPEN */
{  yy_destructor(yypParser,61,&yymsp[0].minor);
#line 406 "lemon.html.yy"
{
}
#line 3593 "lemon.html.c"
}
        break;
      case 178: /* tagtheadblockclosefull ::= tagtheadblockclose */
{  yy_destructor(yypParser,206,&yymsp[0].minor);
#line 408 "lemon.html.yy"
{
}
#line 3601 "lemon.html.c"
}
        break;
      case 179: /* tagtheadblockclosefull ::= tagtheadblockclose spaces */
{  yy_destructor(yypParser,206,&yymsp[-1].minor);
#line 409 "lemon.html.yy"
{
}
#line 3609 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 180: /* tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,62,&yymsp[0].minor);
#line 411 "lemon.html.yy"
{
}
#line 3618 "lemon.html.c"
}
        break;
      case 181: /* tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull */
{  yy_destructor(yypParser,207,&yymsp[-2].minor);
#line 419 "lemon.html.yy"
{
}
#line 3626 "lemon.html.c"
  yy_destructor(yypParser,203,&yymsp[-1].minor);
  yy_destructor(yypParser,208,&yymsp[0].minor);
}
        break;
      case 182: /* tagtfootfullopen ::= tagtfootopen tagclosechar */
{  yy_destructor(yypParser,209,&yymsp[-1].minor);
#line 420 "lemon.html.yy"
{
}
#line 3636 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 183: /* tagtfootfullopen ::= tagtfootopen tagclosechar spaces */
{  yy_destructor(yypParser,209,&yymsp[-2].minor);
#line 421 "lemon.html.yy"
{
}
#line 3645 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 184: /* tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar */
{  yy_destructor(yypParser,209,&yymsp[-2].minor);
#line 422 "lemon.html.yy"
{
}
#line 3655 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 185: /* tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar spaces */
{  yy_destructor(yypParser,209,&yymsp[-3].minor);
#line 423 "lemon.html.yy"
{
}
#line 3665 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-2].minor);
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 186: /* tagtfootopen ::= TAG_TFOOT_OPEN */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 424 "lemon.html.yy"
{
}
#line 3676 "lemon.html.c"
}
        break;
      case 187: /* tagtfootblockclosefull ::= tagtfootblockclose */
{  yy_destructor(yypParser,210,&yymsp[0].minor);
#line 426 "lemon.html.yy"
{
}
#line 3684 "lemon.html.c"
}
        break;
      case 188: /* tagtfootblockclosefull ::= tagtfootblockclose spaces */
{  yy_destructor(yypParser,210,&yymsp[-1].minor);
#line 427 "lemon.html.yy"
{
}
#line 3692 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 189: /* tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE */
{  yy_destructor(yypParser,64,&yymsp[0].minor);
#line 429 "lemon.html.yy"
{
}
#line 3701 "lemon.html.c"
}
        break;
      case 190: /* tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull */
{  yy_destructor(yypParser,211,&yymsp[-2].minor);
#line 437 "lemon.html.yy"
{
}
#line 3709 "lemon.html.c"
  yy_destructor(yypParser,203,&yymsp[-1].minor);
  yy_destructor(yypParser,212,&yymsp[0].minor);
}
        break;
      case 191: /* tagtbodyfullopen ::= tagtbodyopen tagclosechar */
{  yy_destructor(yypParser,213,&yymsp[-1].minor);
#line 438 "lemon.html.yy"
{
}
#line 3719 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 192: /* tagtbodyfullopen ::= tagtbodyopen tagclosechar spaces */
{  yy_destructor(yypParser,213,&yymsp[-2].minor);
#line 439 "lemon.html.yy"
{
}
#line 3728 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 193: /* tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,213,&yymsp[-2].minor);
#line 440 "lemon.html.yy"
{
}
#line 3738 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 194: /* tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar spaces */
{  yy_destructor(yypParser,213,&yymsp[-3].minor);
#line 441 "lemon.html.yy"
{
}
#line 3748 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-2].minor);
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 195: /* tagtbodyopen ::= TAG_TBODY_OPEN */
{  yy_destructor(yypParser,65,&yymsp[0].minor);
#line 442 "lemon.html.yy"
{
}
#line 3759 "lemon.html.c"
}
        break;
      case 196: /* tagtbodyblockclosefull ::= tagtbodyblockclose */
{  yy_destructor(yypParser,214,&yymsp[0].minor);
#line 444 "lemon.html.yy"
{
}
#line 3767 "lemon.html.c"
}
        break;
      case 197: /* tagtbodyblockclosefull ::= tagtbodyblockclose spaces */
{  yy_destructor(yypParser,214,&yymsp[-1].minor);
#line 445 "lemon.html.yy"
{
}
#line 3775 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 198: /* tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,66,&yymsp[0].minor);
#line 447 "lemon.html.yy"
{
}
#line 3784 "lemon.html.c"
}
        break;
      case 199: /* tagtablerows ::= tagtablerows tagtablerow */
{  yy_destructor(yypParser,203,&yymsp[-1].minor);
#line 455 "lemon.html.yy"
{
}
#line 3792 "lemon.html.c"
  yy_destructor(yypParser,215,&yymsp[0].minor);
}
        break;
      case 200: /* tagtablerows ::= tagtablerow */
{  yy_destructor(yypParser,215,&yymsp[0].minor);
#line 456 "lemon.html.yy"
{
}
#line 3801 "lemon.html.c"
}
        break;
      case 201: /* tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull */
{  yy_destructor(yypParser,216,&yymsp[-2].minor);
#line 458 "lemon.html.yy"
{
}
#line 3809 "lemon.html.c"
  yy_destructor(yypParser,217,&yymsp[-1].minor);
  yy_destructor(yypParser,218,&yymsp[0].minor);
}
        break;
      case 202: /* tagtablerowfullopen ::= tagtablerowopen tagclosechar */
{  yy_destructor(yypParser,219,&yymsp[-1].minor);
#line 459 "lemon.html.yy"
{
}
#line 3819 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 203: /* tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces */
{  yy_destructor(yypParser,219,&yymsp[-2].minor);
#line 460 "lemon.html.yy"
{
}
#line 3828 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 204: /* tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,219,&yymsp[-2].minor);
#line 461 "lemon.html.yy"
{
}
#line 3838 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 205: /* tagtablerowopen ::= TAG_TR_OPEN */
{  yy_destructor(yypParser,67,&yymsp[0].minor);
#line 463 "lemon.html.yy"
{
}
#line 3848 "lemon.html.c"
}
        break;
      case 206: /* tagtablerowblockclosefull ::= tagtablerowblockclose */
{  yy_destructor(yypParser,220,&yymsp[0].minor);
#line 465 "lemon.html.yy"
{
}
#line 3856 "lemon.html.c"
}
        break;
      case 207: /* tagtablerowblockclosefull ::= tagtablerowblockclose spaces */
{  yy_destructor(yypParser,220,&yymsp[-1].minor);
#line 466 "lemon.html.yy"
{
}
#line 3864 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 208: /* tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE */
{  yy_destructor(yypParser,68,&yymsp[0].minor);
#line 468 "lemon.html.yy"
{
}
#line 3873 "lemon.html.c"
}
        break;
      case 209: /* tagtablecols ::= tagtablecols tagtablecol */
{  yy_destructor(yypParser,217,&yymsp[-1].minor);
#line 472 "lemon.html.yy"
{
}
#line 3881 "lemon.html.c"
  yy_destructor(yypParser,221,&yymsp[0].minor);
}
        break;
      case 210: /* tagtablecols ::= tagtablecol */
{  yy_destructor(yypParser,221,&yymsp[0].minor);
#line 473 "lemon.html.yy"
{
}
#line 3890 "lemon.html.c"
}
        break;
      case 211: /* tagtablecol ::= tagtablecoltd */
{  yy_destructor(yypParser,222,&yymsp[0].minor);
#line 475 "lemon.html.yy"
{
}
#line 3898 "lemon.html.c"
}
        break;
      case 212: /* tagtablecol ::= tagtablecolth */
{  yy_destructor(yypParser,223,&yymsp[0].minor);
#line 476 "lemon.html.yy"
{
}
#line 3906 "lemon.html.c"
}
        break;
      case 213: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-1].minor);
#line 482 "lemon.html.yy"
{
}
#line 3914 "lemon.html.c"
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 214: /* tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-2].minor);
#line 483 "lemon.html.yy"
{
}
#line 3923 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 215: /* tagtablecoltd ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-4].minor);
#line 484 "lemon.html.yy"
{
}
#line 3933 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-3].minor);
  yy_destructor(yypParser,113,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 216: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-2].minor);
#line 485 "lemon.html.yy"
{
}
#line 3945 "lemon.html.c"
  yy_destructor(yypParser,226,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 217: /* tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-3].minor);
#line 486 "lemon.html.yy"
{
}
#line 3955 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-2].minor);
  yy_destructor(yypParser,226,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 218: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar */
{  yy_destructor(yypParser,227,&yymsp[-1].minor);
#line 487 "lemon.html.yy"
{
}
#line 3966 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 219: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar */
{  yy_destructor(yypParser,227,&yymsp[-2].minor);
#line 489 "lemon.html.yy"
{
}
#line 3975 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 220: /* tagtablecoltdopen ::= TAG_TD_OPEN */
{  yy_destructor(yypParser,69,&yymsp[0].minor);
#line 491 "lemon.html.yy"
{
}
#line 3985 "lemon.html.c"
}
        break;
      case 221: /* tagtablecoltdblockclosefull ::= tagtablecoltdblockclose */
{  yy_destructor(yypParser,228,&yymsp[0].minor);
#line 493 "lemon.html.yy"
{
}
#line 3993 "lemon.html.c"
}
        break;
      case 222: /* tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces */
{  yy_destructor(yypParser,228,&yymsp[-1].minor);
#line 494 "lemon.html.yy"
{
}
#line 4001 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 223: /* tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE */
{  yy_destructor(yypParser,70,&yymsp[0].minor);
#line 496 "lemon.html.yy"
{
}
#line 4010 "lemon.html.c"
}
        break;
      case 224: /* tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent */
{  yy_destructor(yypParser,226,&yymsp[-1].minor);
#line 499 "lemon.html.yy"
{
}
#line 4018 "lemon.html.c"
  yy_destructor(yypParser,229,&yymsp[0].minor);
}
        break;
      case 225: /* tagtablecolcontents ::= tagtablecolcontent */
{  yy_destructor(yypParser,229,&yymsp[0].minor);
#line 500 "lemon.html.yy"
{
}
#line 4027 "lemon.html.c"
}
        break;
      case 226: /* tagtablecolcontent ::= taginput */
{  yy_destructor(yypParser,166,&yymsp[0].minor);
#line 502 "lemon.html.yy"
{
}
#line 4035 "lemon.html.c"
}
        break;
      case 227: /* tagtablecolcontent ::= taginput spaces */
{  yy_destructor(yypParser,166,&yymsp[-1].minor);
#line 503 "lemon.html.yy"
{
}
#line 4043 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 229: /* tagtablecolcontent ::= htmltext spaces */
{  yy_destructor(yypParser,114,&yymsp[-1].minor);
#line 505 "lemon.html.yy"
{
}
#line 4052 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 231: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull */
{  yy_destructor(yypParser,230,&yymsp[-1].minor);
#line 512 "lemon.html.yy"
{
}
#line 4061 "lemon.html.c"
  yy_destructor(yypParser,231,&yymsp[0].minor);
}
        break;
      case 232: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull */
{  yy_destructor(yypParser,230,&yymsp[-2].minor);
#line 513 "lemon.html.yy"
{
}
#line 4070 "lemon.html.c"
  yy_destructor(yypParser,226,&yymsp[-1].minor);
  yy_destructor(yypParser,231,&yymsp[0].minor);
}
        break;
      case 233: /* tagtablecolthfullopen ::= tagtablecolthopen tagclosechar */
{  yy_destructor(yypParser,232,&yymsp[-1].minor);
#line 514 "lemon.html.yy"
{
}
#line 4080 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 234: /* tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,232,&yymsp[-2].minor);
#line 516 "lemon.html.yy"
{
}
#line 4089 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 235: /* tagtablecolthopen ::= TAG_TH_OPEN */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 518 "lemon.html.yy"
{
}
#line 4099 "lemon.html.c"
}
        break;
      case 236: /* tagtablecolthblockclosefull ::= tagtablecolthblockclose */
{  yy_destructor(yypParser,233,&yymsp[0].minor);
#line 520 "lemon.html.yy"
{
}
#line 4107 "lemon.html.c"
}
        break;
      case 237: /* tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces */
{  yy_destructor(yypParser,233,&yymsp[-1].minor);
#line 521 "lemon.html.yy"
{
}
#line 4115 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 238: /* tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE */
{  yy_destructor(yypParser,72,&yymsp[0].minor);
#line 523 "lemon.html.yy"
{
}
#line 4124 "lemon.html.c"
}
        break;
      case 239: /* tagtitle ::= tagtitlefullopen tagtitleblockclosefull */
{  yy_destructor(yypParser,234,&yymsp[-1].minor);
#line 531 "lemon.html.yy"
{
}
#line 4132 "lemon.html.c"
  yy_destructor(yypParser,235,&yymsp[0].minor);
}
        break;
      case 240: /* tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull */
{  yy_destructor(yypParser,234,&yymsp[-2].minor);
#line 532 "lemon.html.yy"
{
}
#line 4141 "lemon.html.c"
  yy_destructor(yypParser,236,&yymsp[-1].minor);
  yy_destructor(yypParser,235,&yymsp[0].minor);
}
        break;
      case 241: /* tagtitlefullopen ::= tagtitleopen tagclosechar */
{  yy_destructor(yypParser,237,&yymsp[-1].minor);
#line 533 "lemon.html.yy"
{
}
#line 4151 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 242: /* tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar */
{  yy_destructor(yypParser,237,&yymsp[-2].minor);
#line 534 "lemon.html.yy"
{
}
#line 4160 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 243: /* tagtitleblockclosefull ::= tagtitleblockclose */
{  yy_destructor(yypParser,238,&yymsp[0].minor);
#line 535 "lemon.html.yy"
{
}
#line 4170 "lemon.html.c"
}
        break;
      case 244: /* tagtitleopen ::= TAG_TITLE_OPEN */
{  yy_destructor(yypParser,73,&yymsp[0].minor);
#line 536 "lemon.html.yy"
{
}
#line 4178 "lemon.html.c"
}
        break;
      case 245: /* tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,74,&yymsp[0].minor);
#line 537 "lemon.html.yy"
{
}
#line 4186 "lemon.html.c"
}
        break;
      case 246: /* taglink ::= taglinkfullopen */
{  yy_destructor(yypParser,239,&yymsp[0].minor);
#line 543 "lemon.html.yy"
{
}
#line 4194 "lemon.html.c"
}
        break;
      case 247: /* taglink ::= taglinkfullopen taglinkblockclosefull */
{  yy_destructor(yypParser,239,&yymsp[-1].minor);
#line 544 "lemon.html.yy"
{
}
#line 4202 "lemon.html.c"
  yy_destructor(yypParser,240,&yymsp[0].minor);
}
        break;
      case 248: /* taglinkfullopen ::= taglinkopen tagproperties tagclosechar */
{  yy_destructor(yypParser,241,&yymsp[-2].minor);
#line 545 "lemon.html.yy"
{
}
#line 4211 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 249: /* taglinkfullopen ::= taglinkopen tagproperties tagshortclose */
{  yy_destructor(yypParser,241,&yymsp[-2].minor);
#line 546 "lemon.html.yy"
{
}
#line 4221 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,242,&yymsp[0].minor);
}
        break;
      case 250: /* taglinkblockclosefull ::= taglinkblockclose */
{  yy_destructor(yypParser,243,&yymsp[0].minor);
#line 548 "lemon.html.yy"
{
}
#line 4231 "lemon.html.c"
}
        break;
      case 251: /* taglinkopen ::= TAG_LINK_OPEN */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 550 "lemon.html.yy"
{
}
#line 4239 "lemon.html.c"
}
        break;
      case 252: /* taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE */
{  yy_destructor(yypParser,76,&yymsp[0].minor);
#line 551 "lemon.html.yy"
{
}
#line 4247 "lemon.html.c"
}
        break;
      case 253: /* tagmeta ::= tagmetafullopen */
{  yy_destructor(yypParser,244,&yymsp[0].minor);
#line 558 "lemon.html.yy"
{
}
#line 4255 "lemon.html.c"
}
        break;
      case 254: /* tagmeta ::= tagmetafullopen tagmetablockclosefull */
{  yy_destructor(yypParser,244,&yymsp[-1].minor);
#line 559 "lemon.html.yy"
{
}
#line 4263 "lemon.html.c"
  yy_destructor(yypParser,245,&yymsp[0].minor);
}
        break;
      case 255: /* tagmetafullopen ::= tagmetaopen tagproperties tagclosechar */
{  yy_destructor(yypParser,246,&yymsp[-2].minor);
#line 560 "lemon.html.yy"
{
}
#line 4272 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 256: /* tagmetafullopen ::= tagmetaopen tagproperties tagshortclose */
{  yy_destructor(yypParser,246,&yymsp[-2].minor);
#line 561 "lemon.html.yy"
{
}
#line 4282 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,242,&yymsp[0].minor);
}
        break;
      case 257: /* tagmetablockclosefull ::= tagmetablockclose */
{  yy_destructor(yypParser,247,&yymsp[0].minor);
#line 563 "lemon.html.yy"
{
}
#line 4292 "lemon.html.c"
}
        break;
      case 258: /* tagmetaopen ::= TAG_META_OPEN */
{  yy_destructor(yypParser,77,&yymsp[0].minor);
#line 565 "lemon.html.yy"
{
}
#line 4300 "lemon.html.c"
}
        break;
      case 259: /* tagmetablockclose ::= TAG_META_BLOCK_CLOSE */
{  yy_destructor(yypParser,78,&yymsp[0].minor);
#line 566 "lemon.html.yy"
{
}
#line 4308 "lemon.html.c"
}
        break;
      case 260: /* tagstyle ::= tagstylefullopen tagstyleblockclosefull */
{  yy_destructor(yypParser,248,&yymsp[-1].minor);
#line 573 "lemon.html.yy"
{
}
#line 4316 "lemon.html.c"
  yy_destructor(yypParser,249,&yymsp[0].minor);
}
        break;
      case 261: /* tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull */
{  yy_destructor(yypParser,248,&yymsp[-2].minor);
#line 574 "lemon.html.yy"
{
}
#line 4325 "lemon.html.c"
  yy_destructor(yypParser,236,&yymsp[-1].minor);
  yy_destructor(yypParser,249,&yymsp[0].minor);
}
        break;
      case 262: /* tagstylefullopen ::= tagstyleopen tagclosechar */
{  yy_destructor(yypParser,250,&yymsp[-1].minor);
#line 575 "lemon.html.yy"
{
}
#line 4335 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 263: /* tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar */
{  yy_destructor(yypParser,250,&yymsp[-2].minor);
#line 576 "lemon.html.yy"
{
}
#line 4344 "lemon.html.c"
  yy_destructor(yypParser,251,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 264: /* tagstyleblockclosefull ::= tagstyleblockclose */
{  yy_destructor(yypParser,252,&yymsp[0].minor);
#line 578 "lemon.html.yy"
{
}
#line 4354 "lemon.html.c"
}
        break;
      case 265: /* tagstyleopen ::= TAG_STYLE_OPEN */
{  yy_destructor(yypParser,79,&yymsp[0].minor);
#line 580 "lemon.html.yy"
{
}
#line 4362 "lemon.html.c"
}
        break;
      case 266: /* tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,80,&yymsp[0].minor);
#line 581 "lemon.html.yy"
{
}
#line 4370 "lemon.html.c"
}
        break;
      case 267: /* tagstyleproperties ::= tagstyleproperties tagstyleproperty */
{  yy_destructor(yypParser,251,&yymsp[-1].minor);
#line 584 "lemon.html.yy"
{
}
#line 4378 "lemon.html.c"
  yy_destructor(yypParser,253,&yymsp[0].minor);
}
        break;
      case 268: /* tagstyleproperties ::= tagstyleproperty */
{  yy_destructor(yypParser,253,&yymsp[0].minor);
#line 585 "lemon.html.yy"
{
}
#line 4387 "lemon.html.c"
}
        break;
      case 269: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,101,&yymsp[-3].minor);
#line 587 "lemon.html.yy"
{
}
#line 4395 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 270: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,101,&yymsp[-3].minor);
#line 588 "lemon.html.yy"
{
}
#line 4406 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 271: /* tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */
      case 318: /* tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==318);
{  yy_destructor(yypParser,101,&yymsp[-3].minor);
#line 589 "lemon.html.yy"
{
}
#line 4418 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 272: /* tagscript ::= tagscriptfullopen tagscriptblockclosefull */
{  yy_destructor(yypParser,254,&yymsp[-1].minor);
#line 596 "lemon.html.yy"
{
}
#line 4429 "lemon.html.c"
  yy_destructor(yypParser,255,&yymsp[0].minor);
}
        break;
      case 273: /* tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull */
{  yy_destructor(yypParser,254,&yymsp[-2].minor);
#line 597 "lemon.html.yy"
{
}
#line 4438 "lemon.html.c"
  yy_destructor(yypParser,236,&yymsp[-1].minor);
  yy_destructor(yypParser,255,&yymsp[0].minor);
}
        break;
      case 274: /* tagscriptfullopen ::= tagscriptopen tagclosechar */
{  yy_destructor(yypParser,256,&yymsp[-1].minor);
#line 598 "lemon.html.yy"
{
}
#line 4448 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 275: /* tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar */
{  yy_destructor(yypParser,256,&yymsp[-2].minor);
#line 599 "lemon.html.yy"
{
}
#line 4457 "lemon.html.c"
  yy_destructor(yypParser,257,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 276: /* tagscriptblockclosefull ::= tagscriptblockclose */
{  yy_destructor(yypParser,258,&yymsp[0].minor);
#line 601 "lemon.html.yy"
{
}
#line 4467 "lemon.html.c"
}
        break;
      case 277: /* tagscriptopen ::= TAG_SCRIPT_OPEN */
{  yy_destructor(yypParser,83,&yymsp[0].minor);
#line 603 "lemon.html.yy"
{
}
#line 4475 "lemon.html.c"
}
        break;
      case 278: /* tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE */
{  yy_destructor(yypParser,84,&yymsp[0].minor);
#line 604 "lemon.html.yy"
{
}
#line 4483 "lemon.html.c"
}
        break;
      case 279: /* tagscriptproperties ::= tagscriptproperties tagscriptproperty */
{  yy_destructor(yypParser,257,&yymsp[-1].minor);
#line 608 "lemon.html.yy"
{
}
#line 4491 "lemon.html.c"
  yy_destructor(yypParser,259,&yymsp[0].minor);
}
        break;
      case 280: /* tagscriptproperties ::= tagscriptproperty */
{  yy_destructor(yypParser,259,&yymsp[0].minor);
#line 609 "lemon.html.yy"
{
}
#line 4500 "lemon.html.c"
}
        break;
      case 281: /* tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA */
{  yy_destructor(yypParser,260,&yymsp[-1].minor);
#line 611 "lemon.html.yy"
{
}
#line 4508 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 282: /* tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 613 "lemon.html.yy"
{
}
#line 4517 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 283: /* tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA */
{  yy_destructor(yypParser,261,&yymsp[-1].minor);
#line 615 "lemon.html.yy"
{
}
#line 4527 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 284: /* tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 617 "lemon.html.yy"
{
}
#line 4536 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 285: /* taghtml ::= taghtmlfullopen taghtmlblockclosefull */
{  yy_destructor(yypParser,262,&yymsp[-1].minor);
#line 623 "lemon.html.yy"
{
}
#line 4546 "lemon.html.c"
  yy_destructor(yypParser,263,&yymsp[0].minor);
}
        break;
      case 286: /* taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull */
{  yy_destructor(yypParser,262,&yymsp[-2].minor);
#line 624 "lemon.html.yy"
{
}
#line 4555 "lemon.html.c"
  yy_destructor(yypParser,264,&yymsp[-1].minor);
  yy_destructor(yypParser,263,&yymsp[0].minor);
}
        break;
      case 287: /* taghtmlfullopen ::= taghtmlopen tagclosechar */
{  yy_destructor(yypParser,265,&yymsp[-1].minor);
#line 625 "lemon.html.yy"
{
}
#line 4565 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 288: /* taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar */
{  yy_destructor(yypParser,265,&yymsp[-2].minor);
#line 626 "lemon.html.yy"
{
}
#line 4574 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 289: /* taghtmlblockclosefull ::= taghtmlblockclose */
{  yy_destructor(yypParser,266,&yymsp[0].minor);
#line 628 "lemon.html.yy"
{
}
#line 4584 "lemon.html.c"
}
        break;
      case 290: /* taghtmlopen ::= TAG_HTML_OPEN */
{  yy_destructor(yypParser,85,&yymsp[0].minor);
#line 630 "lemon.html.yy"
{
}
#line 4592 "lemon.html.c"
}
        break;
      case 291: /* taghtmlblockclose ::= TAG_HTML_BLOCK_CLOSE */
{  yy_destructor(yypParser,86,&yymsp[0].minor);
#line 632 "lemon.html.yy"
{
}
#line 4600 "lemon.html.c"
}
        break;
      case 292: /* taghtmlcontents ::= taghtmlcontents taghtmlcontent */
{  yy_destructor(yypParser,264,&yymsp[-1].minor);
#line 634 "lemon.html.yy"
{
}
#line 4608 "lemon.html.c"
  yy_destructor(yypParser,267,&yymsp[0].minor);
}
        break;
      case 293: /* taghtmlcontents ::= taghtmlcontent */
{  yy_destructor(yypParser,267,&yymsp[0].minor);
#line 635 "lemon.html.yy"
{
}
#line 4617 "lemon.html.c"
}
        break;
      case 296: /* taghtmlcontent ::= tagbody */
{  yy_destructor(yypParser,268,&yymsp[0].minor);
#line 639 "lemon.html.yy"
{
}
#line 4625 "lemon.html.c"
}
        break;
      case 297: /* taghtmlcontent ::= taghead tagbody */
{  yy_destructor(yypParser,269,&yymsp[-1].minor);
#line 640 "lemon.html.yy"
{
}
#line 4633 "lemon.html.c"
  yy_destructor(yypParser,268,&yymsp[0].minor);
}
        break;
      case 298: /* taghtmlcontent ::= taghead spaces_enters tagbody */
{  yy_destructor(yypParser,269,&yymsp[-2].minor);
#line 641 "lemon.html.yy"
{
}
#line 4642 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-1].minor);
  yy_destructor(yypParser,268,&yymsp[0].minor);
}
        break;
      case 299: /* tagbody ::= tagbodyfullopen tagbodyblockclosefull */
{  yy_destructor(yypParser,270,&yymsp[-1].minor);
#line 648 "lemon.html.yy"
{
}
#line 4652 "lemon.html.c"
  yy_destructor(yypParser,271,&yymsp[0].minor);
}
        break;
      case 300: /* tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull */
{  yy_destructor(yypParser,270,&yymsp[-2].minor);
#line 649 "lemon.html.yy"
{
}
#line 4661 "lemon.html.c"
  yy_destructor(yypParser,110,&yymsp[-1].minor);
  yy_destructor(yypParser,271,&yymsp[0].minor);
}
        break;
      case 301: /* tagbodyfullopen ::= tagbodyopen tagclosechar */
{  yy_destructor(yypParser,272,&yymsp[-1].minor);
#line 651 "lemon.html.yy"
{
}
#line 4671 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 302: /* tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,272,&yymsp[-2].minor);
#line 653 "lemon.html.yy"
{
}
#line 4680 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,123,&yymsp[0].minor);
}
        break;
      case 303: /* tagbodyblockclosefull ::= tagbodyblockclose */
{  yy_destructor(yypParser,273,&yymsp[0].minor);
#line 655 "lemon.html.yy"
{
}
#line 4690 "lemon.html.c"
}
        break;
      case 304: /* tagbodyopen ::= TAG_BODY_OPEN */
{  yy_destructor(yypParser,87,&yymsp[0].minor);
#line 657 "lemon.html.yy"
{
}
#line 4698 "lemon.html.c"
}
        break;
      case 305: /* tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,88,&yymsp[0].minor);
#line 659 "lemon.html.yy"
{
}
#line 4706 "lemon.html.c"
}
        break;
      case 306: /* taghead ::= tagheadfullopen tagheadblockclosefull */
{  yy_destructor(yypParser,274,&yymsp[-1].minor);
#line 667 "lemon.html.yy"
{
}
#line 4714 "lemon.html.c"
  yy_destructor(yypParser,275,&yymsp[0].minor);
}
        break;
      case 307: /* taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull */
{  yy_destructor(yypParser,274,&yymsp[-2].minor);
#line 668 "lemon.html.yy"
{
}
#line 4723 "lemon.html.c"
  yy_destructor(yypParser,103,&yymsp[-1].minor);
  yy_destructor(yypParser,275,&yymsp[0].minor);
}
        break;
      case 308: /* tagheadfullopen ::= tagheadopen */
{  yy_destructor(yypParser,276,&yymsp[0].minor);
#line 670 "lemon.html.yy"
{
}
#line 4733 "lemon.html.c"
}
        break;
      case 309: /* tagheadblockclosefull ::= tagheadblockclose */
{  yy_destructor(yypParser,277,&yymsp[0].minor);
#line 672 "lemon.html.yy"
{
}
#line 4741 "lemon.html.c"
}
        break;
      case 310: /* tagheadopen ::= TAG_HEAD_OPEN */
{  yy_destructor(yypParser,89,&yymsp[0].minor);
#line 674 "lemon.html.yy"
{
}
#line 4749 "lemon.html.c"
}
        break;
      case 311: /* tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,90,&yymsp[0].minor);
#line 676 "lemon.html.yy"
{
}
#line 4757 "lemon.html.c"
}
        break;
      case 312: /* tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues */
{  yy_destructor(yypParser,278,&yymsp[0].minor);
#line 684 "lemon.html.yy"
{
}
#line 4765 "lemon.html.c"
}
        break;
      case 313: /* tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue */
{  yy_destructor(yypParser,278,&yymsp[-1].minor);
#line 686 "lemon.html.yy"
{
}
#line 4773 "lemon.html.c"
  yy_destructor(yypParser,279,&yymsp[0].minor);
}
        break;
      case 314: /* tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue */
{  yy_destructor(yypParser,279,&yymsp[0].minor);
#line 688 "lemon.html.yy"
{
}
#line 4782 "lemon.html.c"
}
        break;
      case 315: /* tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,19,&yymsp[-2].minor);
#line 690 "lemon.html.yy"
{
}
#line 4790 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 316: /* tagproperties ::= tagproperties tagproperty */
{  yy_destructor(yypParser,196,&yymsp[-1].minor);
#line 697 "lemon.html.yy"
{
}
#line 4800 "lemon.html.c"
  yy_destructor(yypParser,280,&yymsp[0].minor);
}
        break;
      case 317: /* tagproperties ::= tagproperty */
{  yy_destructor(yypParser,280,&yymsp[0].minor);
#line 698 "lemon.html.yy"
{
}
#line 4809 "lemon.html.c"
}
        break;
      case 319: /* tagclosechar ::= TAG_CLOSE */
{  yy_destructor(yypParser,91,&yymsp[0].minor);
#line 704 "lemon.html.yy"
{
}
#line 4817 "lemon.html.c"
}
        break;
      case 320: /* tagclosechar ::= SPACE TAG_CLOSE */
{  yy_destructor(yypParser,7,&yymsp[-1].minor);
#line 705 "lemon.html.yy"
{
}
#line 4825 "lemon.html.c"
  yy_destructor(yypParser,91,&yymsp[0].minor);
}
        break;
      case 322: /* htmlandspaces ::= htmlandspaces htmlandspace */
{  yy_destructor(yypParser,236,&yymsp[-1].minor);
#line 714 "lemon.html.yy"
{
}
#line 4834 "lemon.html.c"
  yy_destructor(yypParser,281,&yymsp[0].minor);
}
        break;
      case 323: /* htmlandspaces ::= htmlandspace */
{  yy_destructor(yypParser,281,&yymsp[0].minor);
#line 715 "lemon.html.yy"
{
}
#line 4843 "lemon.html.c"
}
        break;
      case 324: /* htmlandspace ::= HTMLTEXT */
      case 326: /* htmltext ::= HTMLTEXT */ yytestcase(yyruleno==326);
{  yy_destructor(yypParser,92,&yymsp[0].minor);
#line 717 "lemon.html.yy"
{
}
#line 4852 "lemon.html.c"
}
        break;
      case 325: /* htmlandspace ::= SPACE */
      case 335: /* space ::= SPACE */ yytestcase(yyruleno==335);
{  yy_destructor(yypParser,7,&yymsp[0].minor);
#line 718 "lemon.html.yy"
{
}
#line 4861 "lemon.html.c"
}
        break;
      case 327: /* opt__spaces_enters ::= spaces_enters */
{  yy_destructor(yypParser,99,&yymsp[0].minor);
#line 727 "lemon.html.yy"
{
}
#line 4869 "lemon.html.c"
}
        break;
      case 329: /* spaces_enters ::= spaces_enters spaces_enter */
{  yy_destructor(yypParser,99,&yymsp[-1].minor);
#line 730 "lemon.html.yy"
{
}
#line 4877 "lemon.html.c"
  yy_destructor(yypParser,282,&yymsp[0].minor);
}
        break;
      case 330: /* spaces_enters ::= spaces_enter */
{  yy_destructor(yypParser,282,&yymsp[0].minor);
#line 731 "lemon.html.yy"
{
}
#line 4886 "lemon.html.c"
}
        break;
      case 333: /* spaces ::= spaces space */
{  yy_destructor(yypParser,124,&yymsp[-1].minor);
#line 737 "lemon.html.yy"
{
}
#line 4894 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[0].minor);
}
        break;
      case 336: /* enter ::= ENTER */
{  yy_destructor(yypParser,93,&yymsp[0].minor);
#line 744 "lemon.html.yy"
{
}
#line 4903 "lemon.html.c"
}
        break;
      default:
      /* (328) opt__spaces_enters ::= */ yytestcase(yyruleno==328);
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
#line 4968 "lemon.html.c"
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
