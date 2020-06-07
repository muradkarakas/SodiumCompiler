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
#include "lemon.html.h" //  must be removed for the first time compile since this file will not be exists

#include <assert.h>

#line 49 "lemon.html.c"
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
#define YYNSTATE             237
#define YYNRULE              334
#define YY_MAX_SHIFT         236
#define YY_MIN_SHIFTREDUCE   528
#define YY_MAX_SHIFTREDUCE   861
#define YY_MIN_REDUCE        862
#define YY_MAX_REDUCE        1195
#define YY_ERROR_ACTION      1196
#define YY_ACCEPT_ACTION     1197
#define YY_NO_ACTION         1198
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
#define YY_ACTTAB_COUNT (936)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   112,    4,    4,    4,    4,    4,    4,    4,    4,    4,
 /*    10 */   746,   26,  761,   93,   26,   26,  860,   81,  860,   84,
 /*    20 */    81,   81,  636,  112,  112,  116,  534,  534,  206,  534,
 /*    30 */   534,  534,  534,  534,  534,  643,  644,  645,  854,  854,
 /*    40 */   136,   81,  703,   25,   81,   81,  721,  112,  116,  850,
 /*    50 */   224,  223,  222,  221,  220,  219,  218,  217,  216,  215,
 /*    60 */   214,  213,  212,  211,  210,  209,  208,  207,  860,  637,
 /*    70 */   731,  646,  225,  204,  203,  202,  201,  200,  199,  198,
 /*    80 */   197,  196,  195,  194,  193,  192,  191,  190,  189,  188,
 /*    90 */   593,  117,    1,  858,  113,    1,  225,  204,  203,  202,
 /*   100 */   201,  200,  199,  198,  197,  196,  195,  194,  193,  192,
 /*   110 */   191,  190,  189,  188,  117,  860,  771,  603,  165,  164,
 /*   120 */   163,  162,  161,  160,  159,  158,  157,  156,  155,  154,
 /*   130 */   153,  152,  706,   49,  849,  685,   56,  731,   91,  685,
 /*   140 */    83,  734,  746,   90,  761,   82,  815,   46,  829,   55,
 /*   150 */   835,  860,   40,   45,  861,   33,   39,   30,   49,   28,
 /*   160 */    42,   56,   50,   91,  141,   83,  125,  125,   90,   65,
 /*   170 */    82,   58,   46,  831,   55,  831,    6,    6,   45,  822,
 /*   180 */    33,    5,  860,   57,  712,    6,    6,    6,    6,    6,
 /*   190 */     6,    6,    6,   26,  816,   18,   18,  721,  832,   81,
 /*   200 */   832,  861,  111,  823,   67,    5,  109,   57,  560,  231,
 /*   210 */    17,  854,  854,   62,  543,  543,  741,  854,   16,  104,
 /*   220 */   100,    8,  229,   81,  543,  543,  543,  543,  543,  543,
 /*   230 */   543, 1197,   44,   44,   64,  691,  186,  861,   44,   44,
 /*   240 */   111,  727,   67,  106,  735,  735,  735,    9,   17,   89,
 /*   250 */    60,   62,   89,   11,  860,   52,   16,  567,  781,    8,
 /*   260 */   799,  579,  773,  799,  594,  773,   23,    7,  861,   61,
 /*   270 */     7,  165,  164,  163,  162,  161,  160,  159,  158,  157,
 /*   280 */   156,  155,  154,  153,  152,  847,  181,  179,  178,  177,
 /*   290 */   176,  175,  174,  173,  172,  171,  170,  169,  168,  167,
 /*   300 */   166,  114,  724,  731,   23,  186,   37,   61,  181,  179,
 /*   310 */   178,  177,  176,  175,  174,  173,  172,  171,  170,  169,
 /*   320 */   168,  167,  166,  759,   10,   13,  102,  813,  712,  858,
 /*   330 */   721,  564,  582,  582,  564,  830,   14,  102,  800,  851,
 /*   340 */   861,  105,  102,  860,  824,  582,  824,   10,  787,  582,
 /*   350 */   133,  787,   87,  860,  596,  785,  811,   18,  845,   18,
 /*   360 */    18,   24,    5,  778,   57,  187,    3,  577,    3,  234,
 /*   370 */   233,  577,  582,  125,  125,  569,  782,  103,   88,  847,
 /*   380 */     2,  850,  825,  780,  825,  780,  750,  102,  103,   88,
 /*   390 */   854,    2,  638,  103,   88,   37,    2,  817,  817,   71,
 /*   400 */   691,  858,  860,   23,  115,   21,   61,  750,  102,   21,
 /*   410 */    21,   21,    9,  841,   23,   60,  749,   61,   11,   23,
 /*   420 */    52,   81,   61,   86,   81,   81,  750,  102,  851,  861,
 /*   430 */   639,  640,  641,  639,  640,  641,  183,   13,  103,   88,
 /*   440 */    13,    2,  757,   43,  101,  854,  854,  739,   14,  844,
 /*   450 */   104,   14,  740,   15,   37,  104,   15,   37,  804,  103,
 /*   460 */    88,  707,    2,  107,   23,  749,  849,   61,  725,   22,
 /*   470 */   764,   54,   51,   54,  145,  142,  125,  125,  103,   88,
 /*   480 */    92,    2,   71,   19,   19,   23,  558,  851,   61,  860,
 /*   490 */   851,  862,  730,  553,  554,   19,   19,  581,  860,   20,
 /*   500 */    20,  750,  226,  758,   23,  101,  716,   61,   97,  725,
 /*   510 */    22,  860,   20,   51,  183,  860,   20,  133,  742,   87,
 /*   520 */    35,  104,  750,  529,   64,  187,  591,   19,  529,  529,
 /*   530 */   591,   19,   35,   22,  576,   20,   51,  743,  576,   20,
 /*   540 */   104,  750,  597,  597,  801,  186,  186,  639,  640,  641,
 /*   550 */   765,   70,  846,  765,  597,  597,  138,  118,  812,  854,
 /*   560 */   854,  817,  817,   24,    5,  760,   57,  774,    3,   68,
 /*   570 */     3,   37,  555,   23,  851,  861,   61,  770,  788,  777,
 /*   580 */   118,  784,  749,  791,  861,  592,  844,  803,  798,  592,
 /*   590 */   597,  798,  186,  559,  836,   70,   32,  861,  698,   32,
 /*   600 */    32,  861,   94,   81,  851,   12,  697,   34,   53,  844,
 /*   610 */    94,  725,   22,   68,  767,   51,  838,   31,   36,   34,
 /*   620 */    22,  553,  554,   51,  854,   66,  860,   59,  860,   65,
 /*   630 */   186,   58,   23,  186,   81,   61,   85,   81,   81,   81,
 /*   640 */    47,  689,   81,   81,  850,  186,   69,   81,  135,   29,
 /*   650 */    81,   81,  826,  809,   81,   96,  108,   81,   81,  786,
 /*   660 */   860,   81,  786,  227,   81,   81,   81,   99,  228,   81,
 /*   670 */    81,   81,  186,  236,   81,   81,  137,  186,  110,  805,
 /*   680 */   145,  142,  186,  187,  186,  775,   73,  570,  235,  232,
 /*   690 */    69,  139,   27,  138,  744,   27,   27,   38,  766,  687,
 /*   700 */    63,  766,   63,  235,  232,   72,  814,   72,  829,   38,
 /*   710 */    22,  186,  861,   51,  861,  789, 1187,  792,  186,  147,
 /*   720 */   186,  226,  841,   47,   74,  186,  186,   75,  186,  849,
 /*   730 */    42,   80,  844,  768,   80,  231,  234,  233,  854,   76,
 /*   740 */   827,  140,   95,  847,  695,  693,  861,   98,  745,  692,
 /*   750 */   688,   66,  230,   59,  143,  144,   66,   65,   59,   58,
 /*   760 */   844,  119,  715,  120,  845,  731,   77,  844,  635,   73,
 /*   770 */   578,   79,  635,  121,  122,  844,   48,  123,   32,  124,
 /*   780 */   126,  151,  149,  127,  119,  128,  120,  226,  129,  588,
 /*   790 */    78,  130,  810,  808,  131,  686,  121,  122,  807,  686,
 /*   800 */   123,  132,  124,  126,  134,  844,  127,   74,  128,  797,
 /*   810 */    75,  129,  796,   78,  130,  845,   81,  131,  146,  148,
 /*   820 */   795,   81,   76,  185,  132,  844,  150,  134,  632,   81,
 /*   830 */   633,  630,  628,  626,  624,  845,   81,  605,  622,  620,
 /*   840 */   618,  616,  614,   81,  793,  612,  610,  608,   81,   77,
 /*   850 */   606,  631,  629,   81,   79,  627,  625,  623,  621,   48,
 /*   860 */   619,  841,  617,  615,  613,  611,  609,  607,  180,  840,
 /*   870 */   182,  844,  843,  184,   27,  682,  845,  680,  678,  676,
 /*   880 */   674,  672,  670,  668,  666,  664,  662,  660,  841,  658,
 /*   890 */   656,  654,  652,  650,  684,  841,  864,  841,  205,  683,
 /*   900 */   681,  679,  841,  841,  677,  841,  864,  675,  673,  671,
 /*   910 */   669,  667,  665,  663,  661,  659,  531,  657,  655,  653,
 /*   920 */   651,  649,  648,   41,  590,  864,  864,  230,  562,  563,
 /*   930 */   574,  864,  575,  864,  573,  572,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   102,  102,  103,  104,  105,  106,  107,  108,  109,  110,
 /*    10 */    69,   99,   71,  124,  102,  103,    7,   99,    7,  101,
 /*    20 */   102,  103,  124,  125,  102,  102,  102,  103,   19,  105,
 /*    30 */   106,  107,  108,  109,  110,   38,   39,   40,  102,  103,
 /*    40 */     7,   99,   61,  101,  102,  103,   65,  125,  125,    7,
 /*    50 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    60 */    51,   52,   53,   54,   55,   56,   57,   58,    7,  171,
 /*    70 */    67,  173,  174,  175,  176,  177,  178,  179,  180,  181,
 /*    80 */   182,  183,  184,  185,  186,  187,  188,  189,  190,  191,
 /*    90 */   124,  102,  170,  102,  205,  173,  174,  175,  176,  177,
 /*   100 */   178,  179,  180,  181,  182,  183,  184,  185,  186,  187,
 /*   110 */   188,  189,  190,  191,  125,    7,   74,  151,  152,  153,
 /*   120 */   154,  155,  156,  157,  158,  159,  160,  161,  162,  163,
 /*   130 */   164,  165,   62,  234,   92,  193,  237,   67,  239,  197,
 /*   140 */   241,   68,   69,  244,   71,  246,   85,  248,   87,  250,
 /*   150 */    89,    7,  194,  254,   93,  256,  198,  199,  234,  201,
 /*   160 */    16,  237,  204,  239,    7,  241,  277,  278,  244,  211,
 /*   170 */   246,  213,  248,  274,  250,  276,  102,  103,  254,  267,
 /*   180 */   256,  269,    7,  271,   63,  111,  112,  113,  114,  115,
 /*   190 */   116,  117,  118,  281,   86,  102,  103,   65,  274,  281,
 /*   200 */   276,   93,  128,  267,  130,  269,  124,  271,  126,  127,
 /*   210 */   136,  102,  103,  139,  102,  103,  225,  281,  144,  228,
 /*   220 */   124,  147,    7,  281,  112,  113,  114,  115,  116,  117,
 /*   230 */   118,   95,   96,   97,   98,   60,  102,   93,  102,  103,
 /*   240 */   128,  218,  130,  220,  221,  222,  223,  224,  136,  140,
 /*   250 */   227,  139,  143,  230,    7,  232,  144,   10,  124,  147,
 /*   260 */   255,   14,  240,  258,   17,  243,  192,  148,   93,  195,
 /*   270 */   151,  152,  153,  154,  155,  156,  157,  158,  159,  160,
 /*   280 */   161,  162,  163,  164,  165,  280,   19,   20,   21,   22,
 /*   290 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   300 */    33,  205,   66,   67,  192,  102,   59,  195,   19,   20,
 /*   310 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   320 */    31,   32,   33,  124,  102,  114,  115,  124,   63,  102,
 /*   330 */    65,  129,  102,  103,  132,   88,  114,  115,  124,   92,
 /*   340 */    93,  114,  115,    7,  270,  115,  272,  125,  249,  119,
 /*   350 */   120,  252,  122,    7,   18,   78,  263,  264,   91,  266,
 /*   360 */   267,  268,  269,   76,  271,    7,  273,  137,  275,   12,
 /*   370 */    13,  141,  142,  277,  278,   11,  242,  166,  167,  280,
 /*   380 */   169,    7,  270,  245,  272,  247,  114,  115,  166,  167,
 /*   390 */   281,  169,   34,  166,  167,   59,  169,  102,  103,  196,
 /*   400 */    60,  102,    7,  192,  205,  217,  195,  114,  115,  221,
 /*   410 */   222,  223,  224,  279,  192,  227,   70,  195,  230,  192,
 /*   420 */   232,   99,  195,  101,  102,  103,  114,  115,   92,   93,
 /*   430 */    35,   36,   37,   35,   36,   37,   19,  226,  166,  167,
 /*   440 */   229,  169,  231,  100,  233,  102,  103,  225,  226,   91,
 /*   450 */   228,  229,  225,  226,   59,  228,  229,   59,   84,  166,
 /*   460 */   167,  208,  169,  210,  192,   70,   92,  195,  215,  216,
 /*   470 */    72,  257,  219,  259,  260,  261,  277,  278,  166,  167,
 /*   480 */   124,  169,  279,  102,  103,  192,    4,   92,  195,    7,
 /*   490 */    92,    0,  124,    2,    3,  114,  115,   15,    7,  102,
 /*   500 */   103,  229,    7,  231,  192,  233,  212,  195,  214,  215,
 /*   510 */   216,    7,  115,  219,   19,    7,  119,  120,  225,  122,
 /*   520 */   203,  228,  229,   97,   98,    7,  145,  146,  102,  103,
 /*   530 */   149,  150,  215,  216,  137,  138,  219,  225,  141,  142,
 /*   540 */   228,  229,  102,  103,  124,  102,  102,   35,   36,   37,
 /*   550 */   235,  236,   34,  238,  114,  115,  102,  102,  263,  102,
 /*   560 */   103,  266,  267,  268,  269,  124,  271,  124,  273,  236,
 /*   570 */   275,   59,  121,  192,   92,   93,  195,   73,  124,   75,
 /*   580 */   125,   77,   70,   79,   93,  145,   91,   83,  255,  149,
 /*   590 */   150,  258,  102,    5,   90,  280,   99,   93,  202,  102,
 /*   600 */   103,   93,  206,  281,   92,  262,  202,  203,  265,   91,
 /*   610 */   206,  215,  216,  280,  124,  219,  278,  199,  200,  215,
 /*   620 */   216,    2,    3,  219,  281,  207,    7,  209,    7,  211,
 /*   630 */   102,  213,  192,  102,   99,  195,  101,  102,  103,   99,
 /*   640 */   196,  101,  102,  103,    7,  102,  236,   99,    7,  101,
 /*   650 */   102,  103,  124,    6,   99,  124,  101,  102,  103,  249,
 /*   660 */     7,   99,  252,  101,  102,  103,   99,  124,  101,  102,
 /*   670 */   103,   99,  102,  101,  102,  103,    7,  102,  124,  259,
 /*   680 */   260,  261,  102,    7,  102,  242,  196,  133,  134,  135,
 /*   690 */   280,    7,   99,  102,  124,  102,  103,  203,  235,  124,
 /*   700 */   131,  238,  133,  134,  135,  251,  124,  253,   87,  215,
 /*   710 */   216,  102,   93,  219,   93,  124,   63,   80,  102,   19,
 /*   720 */   102,    7,  279,  279,  196,  102,  102,  196,  102,   92,
 /*   730 */    16,  123,   91,  124,  126,  127,   12,   13,  281,  196,
 /*   740 */   124,    7,  124,  280,  200,  199,   93,  124,  124,  200,
 /*   750 */   124,  207,    8,  209,   81,   82,  207,  211,  209,  213,
 /*   760 */    91,  102,   64,  102,   91,   67,  196,   91,  168,  279,
 /*   770 */   124,  196,  172,  102,  102,   91,  196,  102,  281,  102,
 /*   780 */   102,   81,   82,  102,  125,  102,  125,    7,  102,  143,
 /*   790 */   102,  102,    9,    9,  102,  193,  125,  125,    6,  197,
 /*   800 */   125,  102,  125,  125,  102,   91,  125,  279,  125,    6,
 /*   810 */   279,  125,    6,  125,  125,   91,  281,  125,    9,    9,
 /*   820 */     6,  281,  279,   19,  125,   91,    9,  125,    6,  281,
 /*   830 */     9,    6,    6,    6,    6,   91,  281,    6,    6,    6,
 /*   840 */     6,    6,    6,  281,  253,    6,    6,    6,  281,  279,
 /*   850 */     6,    9,    9,  281,  279,    9,    9,    9,    9,  279,
 /*   860 */     9,  279,    9,    9,    9,    9,    9,    9,    9,    6,
 /*   870 */     9,   91,    6,    9,  281,    6,   91,    6,    6,    6,
 /*   880 */     6,    6,    6,    6,    6,    6,    6,    6,  279,    6,
 /*   890 */     6,    6,    6,    6,    6,  279,  282,  279,    9,    9,
 /*   900 */     9,    9,  279,  279,    9,  279,  282,    9,    9,    9,
 /*   910 */     9,    9,    9,    9,    9,    9,    1,    9,    9,    9,
 /*   920 */     9,    9,    6,    9,    6,  282,  282,    8,    6,    9,
 /*   930 */     6,  282,    9,  282,    9,    6,
};
#define YY_SHIFT_USE_DFLT (936)
#define YY_SHIFT_COUNT    (236)
#define YY_SHIFT_MIN      (-59)
#define YY_SHIFT_MAX      (929)
static const short yy_shift_ofst[] = {
 /*     0 */   619,  358,   11,  504,  504,  247,  247,  641,   33,  395,
 /*    10 */   395,  398,   61,  398,  512,  512,  336,  482,   61,  336,
 /*    20 */   482,   73,  -59,  175,  621,  -19,  621,  108,   70,  265,
 /*    30 */   653,  653,  144,  669,   70,  236,  508,  508,  698,  508,
 /*    40 */   508,  508,  508,  508,  491,  374,  637,  518,  518,   42,
 /*    50 */   495,  495,  495,  676,  669,  676,  676,  676,  676,  676,
 /*    60 */   676,  676,  508,  684,  508,    3,    3,  157,  374,  637,
 /*    70 */    42,  676,  676,  676,  676,  676,  676,  676,  346,  676,
 /*    80 */   734,  508,   11,   11,  121,  132,  121,  215,   -3,  714,
 /*    90 */   277,  287,   11,   11,   11,   11,   11,   11,   11,   11,
 /*   100 */    11,   11,   11,   11,   11,   11,   11,   11,  340,   11,
 /*   110 */    11,  364,    9,  780,  780,  780,   11,   11,   11,   11,
 /*   120 */    11,   11,   11,   11,   11,  417,   11,   11,   11,   11,
 /*   130 */    11,   11,   11,  588,   11,  267,  289,  673,  700,  724,
 /*   140 */   744,  357,  647,  783,  784,  792,  803,  809,  806,  810,
 /*   150 */   814,  817,  822,  825,  826,  827,  828,  832,  833,  834,
 /*   160 */   835,  836,  839,  840,  841,  844,  821,  842,  843,  846,
 /*   170 */   847,  848,  849,  851,  853,  854,  855,  856,  857,  858,
 /*   180 */   831,  859,  863,  861,  866,  864,  804,  785,  869,  871,
 /*   190 */   872,  873,  874,  875,  876,  877,  878,  879,  880,  881,
 /*   200 */   883,  884,  885,  886,  887,  888,  889,  890,  891,  892,
 /*   210 */   895,  898,  899,  900,  901,  902,  903,  904,  905,  906,
 /*   220 */   908,  909,  910,  911,  912,  916,  785,  918,  914,  919,
 /*   230 */   920,  922,  924,  923,  925,  929,  915,
};
#define YY_REDUCE_USE_DFLT (-112)
#define YY_REDUCE_COUNT (134)
#define YY_REDUCE_MIN   (-111)
#define YY_REDUCE_MAX   (702)
static const short yy_reduce_ofst[] = {
 /*     0 */   136, -102,  -78, -101,  -76,   74,  112,  -34,  119,  222,
 /*    10 */   227,  211,   93,  272,  293,  312,  381,  397,  295,  440,
 /*    20 */   230,   23,  188,  -58,  -88,  -42,  -64,  343,  404,  418,
 /*    30 */   -82,  322,  109,  214,  396,  294,  535,  540,  253,  548,
 /*    40 */   555,  562,  567,  572,  426,  333,  410,  134,  443,  315,
 /*    50 */  -111,   96,  199,  203,  420,  454,  490,  528,  531,  543,
 /*    60 */   570,  575,  497,  554,  593,  317,  494,  569,    5,   99,
 /*    70 */   463,  582,  591,  609,  616,  618,  623,  624,   -9,  626,
 /*    80 */    82,  457,  444,  580,  544,  546,  549,  608,  600,  646,
 /*    90 */   138,   22,  -77,  -11,  455,  659,  661,  671,  672,  675,
 /*   100 */   677,  678,  681,  683,  686,  688,  689,  692,  602,  699,
 /*   110 */   702,  202,  299,  356,  368,  441,  299,  299,  299,  299,
 /*   120 */   299,  299,  299,  299,  299,  338,  299,  299,  299,  299,
 /*   130 */   299,  299,  299,  451,  299,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*    10 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*    20 */  1196, 1196, 1196, 1187, 1196, 1196, 1196, 1196, 1196, 1196,
 /*    30 */  1030, 1028, 1196, 1196, 1196, 1196, 1187, 1187, 1196, 1187,
 /*    40 */  1187, 1187, 1187, 1187, 1196, 1196, 1196, 1196, 1196, 1196,
 /*    50 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*    60 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*    70 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*    80 */  1196, 1186, 1196, 1196, 1196, 1196, 1196, 1196,  968, 1196,
 /*    90 */  1113, 1106, 1035, 1033, 1038, 1053, 1051, 1056, 1044, 1042,
 /*   100 */  1062, 1096, 1088, 1086, 1081, 1090, 1066, 1047, 1196,  890,
 /*   110 */   899, 1196, 1196, 1196, 1196, 1196, 1036, 1034, 1039, 1054,
 /*   120 */  1052, 1057, 1045, 1043, 1063, 1171, 1097, 1089, 1087, 1082,
 /*   130 */  1067, 1048,  891, 1196,  900, 1196, 1196, 1196, 1196, 1196,
 /*   140 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*   150 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*   160 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*   170 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*   180 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1194, 1196, 1196,
 /*   190 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*   200 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*   210 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*   220 */  1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196, 1196,
 /*   230 */  1196, 1196, 1196, 1196, 1196, 1196, 1196,
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
 /* 158 */ "tagtable ::= tagtablefullopen opt__spaces_enters tablecontent opt__spaces_enters tagtableblockclosefull",
 /* 159 */ "tagtablefullopen ::= tagtableopen tagclosechar",
 /* 160 */ "tagtablefullopen ::= tagtableopen tagproperties tagclosechar",
 /* 161 */ "tagtableopen ::= TAG_TABLE_OPEN opt__spaces_enters",
 /* 162 */ "tagtableblockclosefull ::= tagtableblockclose",
 /* 163 */ "tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE",
 /* 164 */ "tablecontent ::= tagthead opt__spaces_enters tagtbody opt__spaces_enters tagtfoot",
 /* 165 */ "tablecontent ::= tagthead opt__spaces_enters tagtfoot opt__spaces_enters tagtbody",
 /* 166 */ "tablecontent ::= tagthead opt__spaces_enters tagtbody",
 /* 167 */ "tablecontent ::= tagtbody opt__spaces_enters tagtfoot",
 /* 168 */ "tablecontent ::= tagtbody",
 /* 169 */ "tagthead ::= tagtheadfullopen tagtheadblockclosefull",
 /* 170 */ "tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull",
 /* 171 */ "tagtheadfullopen ::= tagtheadopen tagclosechar",
 /* 172 */ "tagtheadfullopen ::= tagtheadopen tagclosechar spaces",
 /* 173 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 174 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces",
 /* 175 */ "tagtheadopen ::= TAG_THEAD_OPEN",
 /* 176 */ "tagtheadblockclosefull ::= tagtheadblockclose",
 /* 177 */ "tagtheadblockclosefull ::= tagtheadblockclose spaces",
 /* 178 */ "tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE",
 /* 179 */ "tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull",
 /* 180 */ "tagtfootfullopen ::= tagtfootopen tagclosechar",
 /* 181 */ "tagtfootfullopen ::= tagtfootopen tagclosechar spaces",
 /* 182 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar",
 /* 183 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar spaces",
 /* 184 */ "tagtfootopen ::= TAG_TFOOT_OPEN",
 /* 185 */ "tagtfootblockclosefull ::= tagtfootblockclose",
 /* 186 */ "tagtfootblockclosefull ::= tagtfootblockclose spaces",
 /* 187 */ "tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE",
 /* 188 */ "tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull",
 /* 189 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar",
 /* 190 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar spaces",
 /* 191 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar",
 /* 192 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar spaces",
 /* 193 */ "tagtbodyopen ::= TAG_TBODY_OPEN",
 /* 194 */ "tagtbodyblockclosefull ::= tagtbodyblockclose",
 /* 195 */ "tagtbodyblockclosefull ::= tagtbodyblockclose spaces",
 /* 196 */ "tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE",
 /* 197 */ "tagtablerows ::= tagtablerows tagtablerow",
 /* 198 */ "tagtablerows ::= tagtablerow",
 /* 199 */ "tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull",
 /* 200 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar",
 /* 201 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces",
 /* 202 */ "tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 203 */ "tagtablerowopen ::= TAG_TR_OPEN",
 /* 204 */ "tagtablerowblockclosefull ::= tagtablerowblockclose",
 /* 205 */ "tagtablerowblockclosefull ::= tagtablerowblockclose spaces",
 /* 206 */ "tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE",
 /* 207 */ "tagtablecols ::= tagtablecols tagtablecol",
 /* 208 */ "tagtablecols ::= tagtablecol",
 /* 209 */ "tagtablecol ::= tagtablecoltd",
 /* 210 */ "tagtablecol ::= tagtablecolth",
 /* 211 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull",
 /* 212 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull",
 /* 213 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull",
 /* 214 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull",
 /* 215 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull",
 /* 216 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar",
 /* 217 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar",
 /* 218 */ "tagtablecoltdopen ::= TAG_TD_OPEN",
 /* 219 */ "tagtablecoltdblockclosefull ::= tagtablecoltdblockclose",
 /* 220 */ "tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces",
 /* 221 */ "tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE",
 /* 222 */ "tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent",
 /* 223 */ "tagtablecolcontents ::= tagtablecolcontent",
 /* 224 */ "tagtablecolcontent ::= taginput",
 /* 225 */ "tagtablecolcontent ::= taginput spaces",
 /* 226 */ "tagtablecolcontent ::= htmltext",
 /* 227 */ "tagtablecolcontent ::= htmltext spaces",
 /* 228 */ "tagtablecolcontent ::= tagtable",
 /* 229 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull",
 /* 230 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull",
 /* 231 */ "tagtablecolthfullopen ::= tagtablecolthopen tagclosechar",
 /* 232 */ "tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 233 */ "tagtablecolthopen ::= TAG_TH_OPEN",
 /* 234 */ "tagtablecolthblockclosefull ::= tagtablecolthblockclose",
 /* 235 */ "tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces",
 /* 236 */ "tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE",
 /* 237 */ "tagtitle ::= tagtitlefullopen tagtitleblockclosefull",
 /* 238 */ "tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull",
 /* 239 */ "tagtitlefullopen ::= tagtitleopen tagclosechar",
 /* 240 */ "tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar",
 /* 241 */ "tagtitleblockclosefull ::= tagtitleblockclose",
 /* 242 */ "tagtitleopen ::= TAG_TITLE_OPEN",
 /* 243 */ "tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE",
 /* 244 */ "taglink ::= taglinkfullopen",
 /* 245 */ "taglink ::= taglinkfullopen taglinkblockclosefull",
 /* 246 */ "taglinkfullopen ::= taglinkopen tagproperties tagclosechar",
 /* 247 */ "taglinkfullopen ::= taglinkopen tagproperties tagshortclose",
 /* 248 */ "taglinkblockclosefull ::= taglinkblockclose",
 /* 249 */ "taglinkopen ::= TAG_LINK_OPEN",
 /* 250 */ "taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE",
 /* 251 */ "tagmeta ::= tagmetafullopen",
 /* 252 */ "tagmeta ::= tagmetafullopen tagmetablockclosefull",
 /* 253 */ "tagmetafullopen ::= tagmetaopen tagproperties tagclosechar",
 /* 254 */ "tagmetafullopen ::= tagmetaopen tagproperties tagshortclose",
 /* 255 */ "tagmetablockclosefull ::= tagmetablockclose",
 /* 256 */ "tagmetaopen ::= TAG_META_OPEN",
 /* 257 */ "tagmetablockclose ::= TAG_META_BLOCK_CLOSE",
 /* 258 */ "tagstyle ::= tagstylefullopen tagstyleblockclosefull",
 /* 259 */ "tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull",
 /* 260 */ "tagstylefullopen ::= tagstyleopen tagclosechar",
 /* 261 */ "tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar",
 /* 262 */ "tagstyleblockclosefull ::= tagstyleblockclose",
 /* 263 */ "tagstyleopen ::= TAG_STYLE_OPEN",
 /* 264 */ "tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE",
 /* 265 */ "tagstyleproperties ::= tagstyleproperties tagstyleproperty",
 /* 266 */ "tagstyleproperties ::= tagstyleproperty",
 /* 267 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA",
 /* 268 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA",
 /* 269 */ "tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 270 */ "tagscript ::= tagscriptfullopen tagscriptblockclosefull",
 /* 271 */ "tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull",
 /* 272 */ "tagscriptfullopen ::= tagscriptopen tagclosechar",
 /* 273 */ "tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar",
 /* 274 */ "tagscriptblockclosefull ::= tagscriptblockclose",
 /* 275 */ "tagscriptopen ::= TAG_SCRIPT_OPEN",
 /* 276 */ "tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE",
 /* 277 */ "tagscriptproperties ::= tagscriptproperties tagscriptproperty",
 /* 278 */ "tagscriptproperties ::= tagscriptproperty",
 /* 279 */ "tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA",
 /* 280 */ "tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT",
 /* 281 */ "tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA",
 /* 282 */ "tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT",
 /* 283 */ "taghtml ::= taghtmlfullopen taghtmlblockclosefull",
 /* 284 */ "taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull",
 /* 285 */ "taghtmlfullopen ::= taghtmlopen tagclosechar",
 /* 286 */ "taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar",
 /* 287 */ "taghtmlblockclosefull ::= TAG_HTML_BLOCK_CLOSE",
 /* 288 */ "taghtmlopen ::= TAG_HTML_OPEN",
 /* 289 */ "taghtmlcontents ::= taghtmlcontents taghtmlcontent",
 /* 290 */ "taghtmlcontents ::= taghtmlcontent",
 /* 291 */ "taghtmlcontent ::= space",
 /* 292 */ "taghtmlcontent ::= enter",
 /* 293 */ "taghtmlcontent ::= tagbody",
 /* 294 */ "taghtmlcontent ::= taghead tagbody",
 /* 295 */ "taghtmlcontent ::= taghead spaces_enters tagbody",
 /* 296 */ "tagbody ::= tagbodyfullopen tagbodyblockclosefull",
 /* 297 */ "tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull",
 /* 298 */ "tagbodyfullopen ::= tagbodyopen tagclosechar",
 /* 299 */ "tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar",
 /* 300 */ "tagbodyblockclosefull ::= tagbodyblockclose",
 /* 301 */ "tagbodyopen ::= TAG_BODY_OPEN",
 /* 302 */ "tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE",
 /* 303 */ "taghead ::= tagheadfullopen tagheadblockclosefull",
 /* 304 */ "taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull",
 /* 305 */ "tagheadfullopen ::= tagheadopen",
 /* 306 */ "tagheadblockclosefull ::= tagheadblockclose",
 /* 307 */ "tagheadopen ::= TAG_HEAD_OPEN",
 /* 308 */ "tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE",
 /* 309 */ "tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues",
 /* 310 */ "tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue",
 /* 311 */ "tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue",
 /* 312 */ "tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 313 */ "tagproperties ::= tagproperties tagproperty",
 /* 314 */ "tagproperties ::= tagproperty",
 /* 315 */ "tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 316 */ "tagclosechar ::= TAG_CLOSE",
 /* 317 */ "tagclosechar ::= SPACE TAG_CLOSE",
 /* 318 */ "tagshortclose ::= TAG_SHORT_CLOSE",
 /* 319 */ "htmlandspaces ::= htmlandspaces htmlandspace",
 /* 320 */ "htmlandspaces ::= htmlandspace",
 /* 321 */ "htmlandspace ::= HTMLTEXT",
 /* 322 */ "htmlandspace ::= SPACE",
 /* 323 */ "htmltext ::= HTMLTEXT",
 /* 324 */ "opt__spaces_enters ::= spaces_enters",
 /* 325 */ "opt__spaces_enters ::=",
 /* 326 */ "spaces_enters ::= spaces_enters spaces_enter",
 /* 327 */ "spaces_enters ::= spaces_enter",
 /* 328 */ "spaces_enter ::= space",
 /* 329 */ "spaces_enter ::= enter",
 /* 330 */ "spaces ::= spaces space",
 /* 331 */ "spaces ::= space",
 /* 332 */ "space ::= SPACE",
 /* 333 */ "enter ::= ENTER",
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
#line 35 "lemon.html.yy"

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

#line 1209 "lemon.html.c"
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
#line 52 "lemon.html.yy"



#line 1406 "lemon.html.c"
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
  { 114, 5 },
  { 192, 2 },
  { 192, 3 },
  { 195, 2 },
  { 193, 1 },
  { 197, 1 },
  { 194, 5 },
  { 194, 5 },
  { 194, 3 },
  { 194, 3 },
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
      case 0: /* start ::= expressions */
{  yy_destructor(yypParser,96,&yymsp[0].minor);
#line 56 "lemon.html.yy"
{
}
#line 2050 "lemon.html.c"
}
        break;
      case 1: /* expressions ::= expressions expression */
{  yy_destructor(yypParser,96,&yymsp[-1].minor);
#line 58 "lemon.html.yy"
{
}
#line 2058 "lemon.html.c"
  yy_destructor(yypParser,97,&yymsp[0].minor);
}
        break;
      case 2: /* expressions ::= expression */
{  yy_destructor(yypParser,97,&yymsp[0].minor);
#line 59 "lemon.html.yy"
{
}
#line 2067 "lemon.html.c"
}
        break;
      case 3: /* expression ::= tagdoctype spaces_enters taghtml opt__spaces_enters END_OF_FILE */
{  yy_destructor(yypParser,98,&yymsp[-4].minor);
#line 61 "lemon.html.yy"
{
}
#line 2075 "lemon.html.c"
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
      case 291: /* taghtmlcontent ::= space */ yytestcase(yyruleno==291);
      case 328: /* spaces_enter ::= space */ yytestcase(yyruleno==328);
      case 331: /* spaces ::= space */ yytestcase(yyruleno==331);
{  yy_destructor(yypParser,102,&yymsp[0].minor);
#line 63 "lemon.html.yy"
{
}
#line 2094 "lemon.html.c"
}
        break;
      case 5: /* expression ::= enter */
      case 9: /* tagheadcontent ::= enter */ yytestcase(yyruleno==9);
      case 20: /* tagbodycontent ::= enter */ yytestcase(yyruleno==20);
      case 58: /* tagcontrolblockcontent ::= enter */ yytestcase(yyruleno==58);
      case 73: /* tagdatablockcontent ::= enter */ yytestcase(yyruleno==73);
      case 292: /* taghtmlcontent ::= enter */ yytestcase(yyruleno==292);
      case 329: /* spaces_enter ::= enter */ yytestcase(yyruleno==329);
{  yy_destructor(yypParser,103,&yymsp[0].minor);
#line 65 "lemon.html.yy"
{
}
#line 2108 "lemon.html.c"
}
        break;
      case 6: /* tagheadcontents ::= tagheadcontents tagheadcontent */
{  yy_destructor(yypParser,104,&yymsp[-1].minor);
#line 68 "lemon.html.yy"
{
}
#line 2116 "lemon.html.c"
  yy_destructor(yypParser,105,&yymsp[0].minor);
}
        break;
      case 7: /* tagheadcontents ::= tagheadcontent */
{  yy_destructor(yypParser,105,&yymsp[0].minor);
#line 69 "lemon.html.yy"
{
}
#line 2125 "lemon.html.c"
}
        break;
      case 10: /* tagheadcontent ::= tagtitle */
{  yy_destructor(yypParser,106,&yymsp[0].minor);
#line 73 "lemon.html.yy"
{
}
#line 2133 "lemon.html.c"
}
        break;
      case 11: /* tagheadcontent ::= tagscript */
{  yy_destructor(yypParser,107,&yymsp[0].minor);
#line 74 "lemon.html.yy"
{
}
#line 2141 "lemon.html.c"
}
        break;
      case 12: /* tagheadcontent ::= tagstyle */
{  yy_destructor(yypParser,108,&yymsp[0].minor);
#line 75 "lemon.html.yy"
{
}
#line 2149 "lemon.html.c"
}
        break;
      case 13: /* tagheadcontent ::= taglink */
{  yy_destructor(yypParser,109,&yymsp[0].minor);
#line 76 "lemon.html.yy"
{
}
#line 2157 "lemon.html.c"
}
        break;
      case 14: /* tagheadcontent ::= tagmeta */
{  yy_destructor(yypParser,110,&yymsp[0].minor);
#line 77 "lemon.html.yy"
{
}
#line 2165 "lemon.html.c"
}
        break;
      case 15: /* tagbodycontents ::= tagbodycontents tagbodycontent */
{  yy_destructor(yypParser,111,&yymsp[-1].minor);
#line 79 "lemon.html.yy"
{
}
#line 2173 "lemon.html.c"
  yy_destructor(yypParser,112,&yymsp[0].minor);
}
        break;
      case 16: /* tagbodycontents ::= tagbodycontent */
{  yy_destructor(yypParser,112,&yymsp[0].minor);
#line 80 "lemon.html.yy"
{
}
#line 2182 "lemon.html.c"
}
        break;
      case 17: /* tagbodycontent ::= htsqls */
{  yy_destructor(yypParser,113,&yymsp[0].minor);
#line 82 "lemon.html.yy"
{
}
#line 2190 "lemon.html.c"
}
        break;
      case 18: /* tagbodycontent ::= tagtable */
      case 71: /* tagdatablockcontent ::= tagtable */ yytestcase(yyruleno==71);
      case 228: /* tagtablecolcontent ::= tagtable */ yytestcase(yyruleno==228);
{  yy_destructor(yypParser,114,&yymsp[0].minor);
#line 83 "lemon.html.yy"
{
}
#line 2200 "lemon.html.c"
}
        break;
      case 21: /* tagbodycontent ::= htmltext */
      case 59: /* tagcontrolblockcontent ::= htmltext */ yytestcase(yyruleno==59);
      case 74: /* tagdatablockcontent ::= htmltext */ yytestcase(yyruleno==74);
      case 226: /* tagtablecolcontent ::= htmltext */ yytestcase(yyruleno==226);
{  yy_destructor(yypParser,115,&yymsp[0].minor);
#line 86 "lemon.html.yy"
{
}
#line 2211 "lemon.html.c"
}
        break;
      case 22: /* htsqls ::= tagdatablock */
{  yy_destructor(yypParser,116,&yymsp[0].minor);
#line 88 "lemon.html.yy"
{
}
#line 2219 "lemon.html.c"
}
        break;
      case 23: /* htsqls ::= tagcontrolblock */
{  yy_destructor(yypParser,117,&yymsp[0].minor);
#line 89 "lemon.html.yy"
{
}
#line 2227 "lemon.html.c"
}
        break;
      case 24: /* htsqls ::= tagdatalist */
{  yy_destructor(yypParser,118,&yymsp[0].minor);
#line 90 "lemon.html.yy"
{
}
#line 2235 "lemon.html.c"
}
        break;
      case 25: /* tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD */
{  yy_destructor(yypParser,2,&yymsp[0].minor);
#line 92 "lemon.html.yy"
{
}
#line 2243 "lemon.html.c"
}
        break;
      case 26: /* tagdoctype ::= TAG_DOCTYPE_HTML */
{  yy_destructor(yypParser,3,&yymsp[0].minor);
#line 94 "lemon.html.yy"
{
}
#line 2251 "lemon.html.c"
}
        break;
      case 27: /* tagtree ::= tagtreefullopen tagtreeblockclosefull */
{  yy_destructor(yypParser,120,&yymsp[-1].minor);
#line 101 "lemon.html.yy"
{
}
#line 2259 "lemon.html.c"
  yy_destructor(yypParser,121,&yymsp[0].minor);
}
        break;
      case 28: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar */
{  yy_destructor(yypParser,122,&yymsp[-2].minor);
#line 102 "lemon.html.yy"
{
}
#line 2268 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 29: /* tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces */
{  yy_destructor(yypParser,122,&yymsp[-3].minor);
#line 103 "lemon.html.yy"
{
}
#line 2278 "lemon.html.c"
  yy_destructor(yypParser,123,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 30: /* tagtreeopen ::= TAG_TREE_OPEN */
{  yy_destructor(yypParser,4,&yymsp[0].minor);
#line 105 "lemon.html.yy"
{
}
#line 2289 "lemon.html.c"
}
        break;
      case 31: /* tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE */
{  yy_destructor(yypParser,5,&yymsp[0].minor);
#line 107 "lemon.html.yy"
{
}
#line 2297 "lemon.html.c"
}
        break;
      case 32: /* tagtreeproperties ::= tagtreeproperties tagtreeproperty */
{  yy_destructor(yypParser,123,&yymsp[-1].minor);
#line 109 "lemon.html.yy"
{
}
#line 2305 "lemon.html.c"
  yy_destructor(yypParser,126,&yymsp[0].minor);
}
        break;
      case 33: /* tagtreeproperties ::= tagtreeproperty */
{  yy_destructor(yypParser,126,&yymsp[0].minor);
#line 110 "lemon.html.yy"
{
}
#line 2314 "lemon.html.c"
}
        break;
      case 34: /* tagtreeproperty ::= tagtreepropertyid PROPERTYDATA */
{  yy_destructor(yypParser,127,&yymsp[-1].minor);
#line 112 "lemon.html.yy"
{
}
#line 2322 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 35: /* tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 114 "lemon.html.yy"
{
}
#line 2331 "lemon.html.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 36: /* tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull */
{  yy_destructor(yypParser,128,&yymsp[-1].minor);
#line 120 "lemon.html.yy"
{
}
#line 2341 "lemon.html.c"
  yy_destructor(yypParser,129,&yymsp[0].minor);
}
        break;
      case 37: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar */
{  yy_destructor(yypParser,130,&yymsp[-2].minor);
#line 121 "lemon.html.yy"
{
}
#line 2350 "lemon.html.c"
  yy_destructor(yypParser,131,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 38: /* tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces */
{  yy_destructor(yypParser,130,&yymsp[-3].minor);
#line 122 "lemon.html.yy"
{
}
#line 2360 "lemon.html.c"
  yy_destructor(yypParser,131,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 39: /* tagdatalistopen ::= TAG_DATALIST_OPEN */
{  yy_destructor(yypParser,10,&yymsp[0].minor);
#line 124 "lemon.html.yy"
{
}
#line 2371 "lemon.html.c"
}
        break;
      case 40: /* tagdatalistblockclosefull ::= tagdatalistblockclose */
{  yy_destructor(yypParser,132,&yymsp[0].minor);
#line 126 "lemon.html.yy"
{
}
#line 2379 "lemon.html.c"
}
        break;
      case 41: /* tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE */
{  yy_destructor(yypParser,11,&yymsp[0].minor);
#line 128 "lemon.html.yy"
{
}
#line 2387 "lemon.html.c"
}
        break;
      case 42: /* datalistproperties ::= datalistproperties datalistproperty */
{  yy_destructor(yypParser,131,&yymsp[-1].minor);
#line 130 "lemon.html.yy"
{
}
#line 2395 "lemon.html.c"
  yy_destructor(yypParser,133,&yymsp[0].minor);
}
        break;
      case 43: /* datalistproperties ::= datalistproperty */
{  yy_destructor(yypParser,133,&yymsp[0].minor);
#line 131 "lemon.html.yy"
{
}
#line 2404 "lemon.html.c"
}
        break;
      case 44: /* datalistproperty ::= tagdatalistpropertyid PROPERTYDATA */
{  yy_destructor(yypParser,134,&yymsp[-1].minor);
#line 133 "lemon.html.yy"
{
}
#line 2412 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 45: /* tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 135 "lemon.html.yy"
{
}
#line 2421 "lemon.html.c"
  yy_destructor(yypParser,12,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 46: /* datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA */
{  yy_destructor(yypParser,135,&yymsp[-1].minor);
#line 137 "lemon.html.yy"
{
}
#line 2431 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 47: /* tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 139 "lemon.html.yy"
{
}
#line 2440 "lemon.html.c"
  yy_destructor(yypParser,13,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 48: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull */
{  yy_destructor(yypParser,136,&yymsp[-1].minor);
#line 146 "lemon.html.yy"
{
}
#line 2450 "lemon.html.c"
  yy_destructor(yypParser,137,&yymsp[0].minor);
}
        break;
      case 49: /* tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull */
{  yy_destructor(yypParser,136,&yymsp[-2].minor);
#line 147 "lemon.html.yy"
{
}
#line 2459 "lemon.html.c"
  yy_destructor(yypParser,138,&yymsp[-1].minor);
  yy_destructor(yypParser,137,&yymsp[0].minor);
}
        break;
      case 50: /* tagcontrolblockfullopen ::= tagcontrolblockopen spaces_enters tagcontrolblockproperties tagclosechar */
{  yy_destructor(yypParser,139,&yymsp[-3].minor);
#line 149 "lemon.html.yy"
{
}
#line 2469 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-2].minor);
  yy_destructor(yypParser,140,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 51: /* tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN */
{  yy_destructor(yypParser,14,&yymsp[0].minor);
#line 151 "lemon.html.yy"
{
}
#line 2480 "lemon.html.c"
}
        break;
      case 52: /* tagcontrolblockclosefull ::= tagcontrolblockblockclose */
{  yy_destructor(yypParser,141,&yymsp[0].minor);
#line 153 "lemon.html.yy"
{
}
#line 2488 "lemon.html.c"
}
        break;
      case 53: /* tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 154 "lemon.html.yy"
{
}
#line 2496 "lemon.html.c"
}
        break;
      case 54: /* tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent */
{  yy_destructor(yypParser,138,&yymsp[-1].minor);
#line 156 "lemon.html.yy"
{
}
#line 2504 "lemon.html.c"
  yy_destructor(yypParser,142,&yymsp[0].minor);
}
        break;
      case 55: /* tagcontrolblockcontents ::= tagcontrolblockcontent */
{  yy_destructor(yypParser,142,&yymsp[0].minor);
#line 157 "lemon.html.yy"
{
}
#line 2513 "lemon.html.c"
}
        break;
      case 56: /* tagcontrolblockcontent ::= tagtree */
{  yy_destructor(yypParser,119,&yymsp[0].minor);
#line 159 "lemon.html.yy"
{
}
#line 2521 "lemon.html.c"
}
        break;
      case 60: /* tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty */
{  yy_destructor(yypParser,140,&yymsp[-1].minor);
#line 164 "lemon.html.yy"
{
}
#line 2529 "lemon.html.c"
  yy_destructor(yypParser,143,&yymsp[0].minor);
}
        break;
      case 61: /* tagcontrolblockproperties ::= tagcontrolblockproperty */
{  yy_destructor(yypParser,143,&yymsp[0].minor);
#line 165 "lemon.html.yy"
{
}
#line 2538 "lemon.html.c"
}
        break;
      case 62: /* tagcontrolblockproperty ::= PROP_CONTROLBLOCK_BLOCK_NAME opt__spaces_enters ASSIGMENT opt__spaces_enters PROPERTYDATA */
{  yy_destructor(yypParser,16,&yymsp[-4].minor);
#line 167 "lemon.html.yy"
{
}
#line 2546 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[-3].minor);
  yy_destructor(yypParser,9,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 63: /* tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull */
{  yy_destructor(yypParser,144,&yymsp[-1].minor);
#line 176 "lemon.html.yy"
{
}
#line 2558 "lemon.html.c"
  yy_destructor(yypParser,145,&yymsp[0].minor);
}
        break;
      case 64: /* tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull */
{  yy_destructor(yypParser,144,&yymsp[-2].minor);
#line 177 "lemon.html.yy"
{
}
#line 2567 "lemon.html.c"
  yy_destructor(yypParser,146,&yymsp[-1].minor);
  yy_destructor(yypParser,145,&yymsp[0].minor);
}
        break;
      case 65: /* tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar */
{  yy_destructor(yypParser,147,&yymsp[-2].minor);
#line 178 "lemon.html.yy"
{
}
#line 2577 "lemon.html.c"
  yy_destructor(yypParser,148,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 66: /* tagdatablockopen ::= TAG_DATABLOCK_OPEN */
{  yy_destructor(yypParser,17,&yymsp[0].minor);
#line 180 "lemon.html.yy"
{
}
#line 2587 "lemon.html.c"
}
        break;
      case 67: /* tagdatablockblockclosefull ::= tagdatablockblockclose */
{  yy_destructor(yypParser,149,&yymsp[0].minor);
#line 182 "lemon.html.yy"
{
}
#line 2595 "lemon.html.c"
}
        break;
      case 68: /* tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE */
{  yy_destructor(yypParser,18,&yymsp[0].minor);
#line 184 "lemon.html.yy"
{
}
#line 2603 "lemon.html.c"
}
        break;
      case 69: /* tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent */
{  yy_destructor(yypParser,146,&yymsp[-1].minor);
#line 187 "lemon.html.yy"
{
}
#line 2611 "lemon.html.c"
  yy_destructor(yypParser,150,&yymsp[0].minor);
}
        break;
      case 70: /* tagdatablockcontents ::= tagdatablockcontent */
{  yy_destructor(yypParser,150,&yymsp[0].minor);
#line 188 "lemon.html.yy"
{
}
#line 2620 "lemon.html.c"
}
        break;
      case 75: /* tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty */
{  yy_destructor(yypParser,148,&yymsp[-1].minor);
#line 195 "lemon.html.yy"
{
}
#line 2628 "lemon.html.c"
  yy_destructor(yypParser,151,&yymsp[0].minor);
}
        break;
      case 76: /* tagdatablockproperties ::= tagdatablockproperty */
{  yy_destructor(yypParser,151,&yymsp[0].minor);
#line 197 "lemon.html.yy"
{
}
#line 2637 "lemon.html.c"
}
        break;
      case 77: /* tagdatablockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,7,&yymsp[-3].minor);
#line 199 "lemon.html.yy"
{
}
#line 2645 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 78: /* tagdatablockproperty ::= tagdatablockpropertyjoincondition PROPERTYDATA */
{  yy_destructor(yypParser,152,&yymsp[-1].minor);
#line 201 "lemon.html.yy"
{
}
#line 2656 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 79: /* tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 203 "lemon.html.yy"
{
}
#line 2665 "lemon.html.c"
  yy_destructor(yypParser,20,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 80: /* tagdatablockproperty ::= tagdatablockpropertyconnectionname PROPERTYDATA */
{  yy_destructor(yypParser,153,&yymsp[-1].minor);
#line 206 "lemon.html.yy"
{
}
#line 2675 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 81: /* tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 208 "lemon.html.yy"
{
}
#line 2684 "lemon.html.c"
  yy_destructor(yypParser,21,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 82: /* tagdatablockproperty ::= tagdatablockpropertyautogeneratedcolumns PROPERTYDATA */
{  yy_destructor(yypParser,154,&yymsp[-1].minor);
#line 211 "lemon.html.yy"
{
}
#line 2694 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 83: /* tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 213 "lemon.html.yy"
{
}
#line 2703 "lemon.html.c"
  yy_destructor(yypParser,22,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 84: /* tagdatablockproperty ::= tagdatablockpropertyrecordcount PROPERTYDATA */
{  yy_destructor(yypParser,155,&yymsp[-1].minor);
#line 215 "lemon.html.yy"
{
}
#line 2713 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 85: /* tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 217 "lemon.html.yy"
{
}
#line 2722 "lemon.html.c"
  yy_destructor(yypParser,23,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 86: /* tagdatablockproperty ::= tagdatablockpropertysourcename PROPERTYDATA */
{  yy_destructor(yypParser,156,&yymsp[-1].minor);
#line 219 "lemon.html.yy"
{
}
#line 2732 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 87: /* tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 221 "lemon.html.yy"
{
}
#line 2741 "lemon.html.c"
  yy_destructor(yypParser,24,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 88: /* tagdatablockproperty ::= tagdatablockpropertyschemaname PROPERTYDATA */
{  yy_destructor(yypParser,157,&yymsp[-1].minor);
#line 224 "lemon.html.yy"
{
}
#line 2751 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 89: /* tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 226 "lemon.html.yy"
{
}
#line 2760 "lemon.html.c"
  yy_destructor(yypParser,25,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 90: /* tagdatablockproperty ::= tagdatablockpropertyblockname PROPERTYDATA */
{  yy_destructor(yypParser,158,&yymsp[-1].minor);
#line 228 "lemon.html.yy"
{
}
#line 2770 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 91: /* tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 230 "lemon.html.yy"
{
}
#line 2779 "lemon.html.c"
  yy_destructor(yypParser,26,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 92: /* tagdatablockproperty ::= tagdatablockpropertykeycolumnname PROPERTYDATA */
{  yy_destructor(yypParser,159,&yymsp[-1].minor);
#line 232 "lemon.html.yy"
{
}
#line 2789 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 93: /* tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 234 "lemon.html.yy"
{
}
#line 2798 "lemon.html.c"
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 94: /* tagdatablockproperty ::= tagdatablockpropertymasterblockname PROPERTYDATA */
{  yy_destructor(yypParser,160,&yymsp[-1].minor);
#line 236 "lemon.html.yy"
{
}
#line 2808 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 95: /* tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 238 "lemon.html.yy"
{
}
#line 2817 "lemon.html.c"
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 96: /* tagdatablockproperty ::= tagdatablockpropertyinsertallowed PROPERTYDATA */
{  yy_destructor(yypParser,161,&yymsp[-1].minor);
#line 240 "lemon.html.yy"
{
}
#line 2827 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 97: /* tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 242 "lemon.html.yy"
{
}
#line 2836 "lemon.html.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 98: /* tagdatablockproperty ::= tagdatablockpropertydeleteallowed PROPERTYDATA */
{  yy_destructor(yypParser,162,&yymsp[-1].minor);
#line 244 "lemon.html.yy"
{
}
#line 2846 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 99: /* tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 246 "lemon.html.yy"
{
}
#line 2855 "lemon.html.c"
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 100: /* tagdatablockproperty ::= tagdatablockpropertyupdateallowed PROPERTYDATA */
{  yy_destructor(yypParser,163,&yymsp[-1].minor);
#line 248 "lemon.html.yy"
{
}
#line 2865 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 101: /* tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 250 "lemon.html.yy"
{
}
#line 2874 "lemon.html.c"
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 102: /* tagdatablockproperty ::= tagdatablockpropertywhereclause PROPERTYDATA */
{  yy_destructor(yypParser,164,&yymsp[-1].minor);
#line 253 "lemon.html.yy"
{
}
#line 2884 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 103: /* tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 255 "lemon.html.yy"
{
}
#line 2893 "lemon.html.c"
  yy_destructor(yypParser,32,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 104: /* tagdatablockproperty ::= tagdatablockpropertyorderbyclause PROPERTYDATA */
{  yy_destructor(yypParser,165,&yymsp[-1].minor);
#line 257 "lemon.html.yy"
{
}
#line 2903 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 105: /* tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 259 "lemon.html.yy"
{
}
#line 2912 "lemon.html.c"
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 106: /* taginput ::= taginputfullopen */
{  yy_destructor(yypParser,167,&yymsp[0].minor);
#line 267 "lemon.html.yy"
{
}
#line 2922 "lemon.html.c"
}
        break;
      case 107: /* taginput ::= taginputfullopen taginputblockclosefull */
{  yy_destructor(yypParser,167,&yymsp[-1].minor);
#line 268 "lemon.html.yy"
{
}
#line 2930 "lemon.html.c"
  yy_destructor(yypParser,168,&yymsp[0].minor);
}
        break;
      case 108: /* taginputfullopen ::= taginputopen taginputproperties tagclosechar */
{  yy_destructor(yypParser,169,&yymsp[-2].minor);
#line 269 "lemon.html.yy"
{
}
#line 2939 "lemon.html.c"
  yy_destructor(yypParser,170,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 109: /* taginputfullopen ::= taginputopen taginputproperties taginputshortclose */
{  yy_destructor(yypParser,169,&yymsp[-2].minor);
#line 270 "lemon.html.yy"
{
}
#line 2949 "lemon.html.c"
  yy_destructor(yypParser,170,&yymsp[-1].minor);
  yy_destructor(yypParser,171,&yymsp[0].minor);
}
        break;
      case 110: /* taginputshortclose ::= TAG_SHORT_CLOSE */
      case 318: /* tagshortclose ::= TAG_SHORT_CLOSE */ yytestcase(yyruleno==318);
{  yy_destructor(yypParser,34,&yymsp[0].minor);
#line 273 "lemon.html.yy"
{
}
#line 2960 "lemon.html.c"
}
        break;
      case 111: /* taginputopen ::= TAG_INPUT_OPEN */
{  yy_destructor(yypParser,35,&yymsp[0].minor);
#line 276 "lemon.html.yy"
{
}
#line 2968 "lemon.html.c"
}
        break;
      case 112: /* taginputopen ::= TAG_SELECT_OPEN */
{  yy_destructor(yypParser,36,&yymsp[0].minor);
#line 278 "lemon.html.yy"
{
}
#line 2976 "lemon.html.c"
}
        break;
      case 113: /* taginputopen ::= TAG_TEXTAREA_OPEN */
{  yy_destructor(yypParser,37,&yymsp[0].minor);
#line 280 "lemon.html.yy"
{
}
#line 2984 "lemon.html.c"
}
        break;
      case 114: /* taginputblockclosefull ::= taginputblockclose */
{  yy_destructor(yypParser,172,&yymsp[0].minor);
#line 282 "lemon.html.yy"
{
}
#line 2992 "lemon.html.c"
}
        break;
      case 115: /* taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE */
{  yy_destructor(yypParser,38,&yymsp[0].minor);
#line 284 "lemon.html.yy"
{
}
#line 3000 "lemon.html.c"
}
        break;
      case 116: /* taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE */
{  yy_destructor(yypParser,39,&yymsp[0].minor);
#line 286 "lemon.html.yy"
{
}
#line 3008 "lemon.html.c"
}
        break;
      case 117: /* taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE */
{  yy_destructor(yypParser,40,&yymsp[0].minor);
#line 288 "lemon.html.yy"
{
}
#line 3016 "lemon.html.c"
}
        break;
      case 118: /* taginputproperties ::= taginputproperties taginputproperty */
{  yy_destructor(yypParser,170,&yymsp[-1].minor);
#line 290 "lemon.html.yy"
{
}
#line 3024 "lemon.html.c"
  yy_destructor(yypParser,173,&yymsp[0].minor);
}
        break;
      case 119: /* taginputproperties ::= taginputproperty */
{  yy_destructor(yypParser,173,&yymsp[0].minor);
#line 292 "lemon.html.yy"
{
}
#line 3033 "lemon.html.c"
}
        break;
      case 120: /* taginputproperty ::= taginputcheckedvalue PROPERTYDATA */
{  yy_destructor(yypParser,174,&yymsp[-1].minor);
#line 294 "lemon.html.yy"
{
}
#line 3041 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 121: /* taginputcheckedvalue ::= spaces PROP_INPUT_CHECKED_VALUE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 296 "lemon.html.yy"
{
}
#line 3050 "lemon.html.c"
  yy_destructor(yypParser,41,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 122: /* taginputproperty ::= taginputuncheckedvalue PROPERTYDATA */
{  yy_destructor(yypParser,175,&yymsp[-1].minor);
#line 298 "lemon.html.yy"
{
}
#line 3060 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 123: /* taginputuncheckedvalue ::= spaces PROP_INPUT_UNCHECKED_VALUE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 300 "lemon.html.yy"
{
}
#line 3069 "lemon.html.c"
  yy_destructor(yypParser,42,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 124: /* taginputproperty ::= taginputpropertyinputname PROPERTYDATA */
{  yy_destructor(yypParser,176,&yymsp[-1].minor);
#line 302 "lemon.html.yy"
{
}
#line 3079 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 125: /* taginputpropertyinputname ::= spaces PROP_INPUT_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 304 "lemon.html.yy"
{
}
#line 3088 "lemon.html.c"
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 126: /* taginputproperty ::= taginputpropertysequencename PROPERTYDATA */
{  yy_destructor(yypParser,177,&yymsp[-1].minor);
#line 306 "lemon.html.yy"
{
}
#line 3098 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 127: /* taginputpropertysequencename ::= spaces PROP_INPUT_SEQUENCE_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 308 "lemon.html.yy"
{
}
#line 3107 "lemon.html.c"
  yy_destructor(yypParser,44,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 128: /* taginputproperty ::= taginputpropertysequenceschemaname PROPERTYDATA */
{  yy_destructor(yypParser,178,&yymsp[-1].minor);
#line 310 "lemon.html.yy"
{
}
#line 3117 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 129: /* taginputpropertysequenceschemaname ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 312 "lemon.html.yy"
{
}
#line 3126 "lemon.html.c"
  yy_destructor(yypParser,45,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 130: /* taginputproperty ::= taginputpropertymasteritemname PROPERTYDATA */
{  yy_destructor(yypParser,179,&yymsp[-1].minor);
#line 315 "lemon.html.yy"
{
}
#line 3136 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 131: /* taginputpropertymasteritemname ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 317 "lemon.html.yy"
{
}
#line 3145 "lemon.html.c"
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 132: /* taginputproperty ::= taginputpropertyinputtype PROPERTYDATA */
{  yy_destructor(yypParser,180,&yymsp[-1].minor);
#line 319 "lemon.html.yy"
{
}
#line 3155 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 133: /* taginputpropertyinputtype ::= spaces PROP_INPUT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 321 "lemon.html.yy"
{
}
#line 3164 "lemon.html.c"
  yy_destructor(yypParser,47,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 134: /* taginputproperty ::= taginputpropertyinputvalue PROPERTYDATA */
{  yy_destructor(yypParser,181,&yymsp[-1].minor);
#line 323 "lemon.html.yy"
{
}
#line 3174 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 135: /* taginputpropertyinputvalue ::= spaces PROP_INPUT_VALUE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 325 "lemon.html.yy"
{
}
#line 3183 "lemon.html.c"
  yy_destructor(yypParser,48,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 136: /* taginputproperty ::= taginputpropertydefaultvalue PROPERTYDATA */
{  yy_destructor(yypParser,182,&yymsp[-1].minor);
#line 327 "lemon.html.yy"
{
}
#line 3193 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 137: /* taginputpropertydefaultvalue ::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 329 "lemon.html.yy"
{
}
#line 3202 "lemon.html.c"
  yy_destructor(yypParser,49,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 138: /* taginputproperty ::= taginputpropertycolumnname PROPERTYDATA */
{  yy_destructor(yypParser,183,&yymsp[-1].minor);
#line 331 "lemon.html.yy"
{
}
#line 3212 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 139: /* taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 333 "lemon.html.yy"
{
}
#line 3221 "lemon.html.c"
  yy_destructor(yypParser,50,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 140: /* taginputproperty ::= taginputpropertyformatmask PROPERTYDATA */
{  yy_destructor(yypParser,184,&yymsp[-1].minor);
#line 335 "lemon.html.yy"
{
}
#line 3231 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 141: /* taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 337 "lemon.html.yy"
{
}
#line 3240 "lemon.html.c"
  yy_destructor(yypParser,51,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 142: /* taginputproperty ::= taginputpropertydatatype PROPERTYDATA */
{  yy_destructor(yypParser,185,&yymsp[-1].minor);
#line 339 "lemon.html.yy"
{
}
#line 3250 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 143: /* taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 341 "lemon.html.yy"
{
}
#line 3259 "lemon.html.c"
  yy_destructor(yypParser,52,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 144: /* taginputproperty ::= taginputpropertymaxlength PROPERTYDATA */
{  yy_destructor(yypParser,186,&yymsp[-1].minor);
#line 343 "lemon.html.yy"
{
}
#line 3269 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 145: /* taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 345 "lemon.html.yy"
{
}
#line 3278 "lemon.html.c"
  yy_destructor(yypParser,53,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 146: /* taginputproperty ::= taginputpropertyinsertallowed PROPERTYDATA */
{  yy_destructor(yypParser,187,&yymsp[-1].minor);
#line 347 "lemon.html.yy"
{
}
#line 3288 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 147: /* taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 349 "lemon.html.yy"
{
}
#line 3297 "lemon.html.c"
  yy_destructor(yypParser,54,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 148: /* taginputproperty ::= taginputpropertyupdateallowed PROPERTYDATA */
{  yy_destructor(yypParser,188,&yymsp[-1].minor);
#line 351 "lemon.html.yy"
{
}
#line 3307 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 149: /* taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 353 "lemon.html.yy"
{
}
#line 3316 "lemon.html.c"
  yy_destructor(yypParser,55,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 150: /* taginputproperty ::= taginputpropertydatalistname PROPERTYDATA */
{  yy_destructor(yypParser,189,&yymsp[-1].minor);
#line 355 "lemon.html.yy"
{
}
#line 3326 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 151: /* taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 357 "lemon.html.yy"
{
}
#line 3335 "lemon.html.c"
  yy_destructor(yypParser,56,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 152: /* taginputproperty ::= taginputpropertylookupitemname PROPERTYDATA */
{  yy_destructor(yypParser,190,&yymsp[-1].minor);
#line 359 "lemon.html.yy"
{
}
#line 3345 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 153: /* taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 361 "lemon.html.yy"
{
}
#line 3354 "lemon.html.c"
  yy_destructor(yypParser,57,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 154: /* taginputproperty ::= taginputpropertylookupitemblockname PROPERTYDATA */
{  yy_destructor(yypParser,191,&yymsp[-1].minor);
#line 363 "lemon.html.yy"
{
}
#line 3364 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 155: /* taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,125,&yymsp[-2].minor);
#line 365 "lemon.html.yy"
{
}
#line 3373 "lemon.html.c"
  yy_destructor(yypParser,58,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 156: /* taginputproperty ::= spaces PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,125,&yymsp[-3].minor);
#line 367 "lemon.html.yy"
{
}
#line 3383 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 157: /* tagtable ::= tagtablefullopen tagtableblockclosefull */
{  yy_destructor(yypParser,192,&yymsp[-1].minor);
#line 374 "lemon.html.yy"
{
}
#line 3394 "lemon.html.c"
  yy_destructor(yypParser,193,&yymsp[0].minor);
}
        break;
      case 158: /* tagtable ::= tagtablefullopen opt__spaces_enters tablecontent opt__spaces_enters tagtableblockclosefull */
{  yy_destructor(yypParser,192,&yymsp[-4].minor);
#line 375 "lemon.html.yy"
{
}
#line 3403 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[-3].minor);
  yy_destructor(yypParser,194,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,193,&yymsp[0].minor);
}
        break;
      case 159: /* tagtablefullopen ::= tagtableopen tagclosechar */
{  yy_destructor(yypParser,195,&yymsp[-1].minor);
#line 377 "lemon.html.yy"
{
}
#line 3415 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 160: /* tagtablefullopen ::= tagtableopen tagproperties tagclosechar */
{  yy_destructor(yypParser,195,&yymsp[-2].minor);
#line 378 "lemon.html.yy"
{
}
#line 3424 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 161: /* tagtableopen ::= TAG_TABLE_OPEN opt__spaces_enters */
{  yy_destructor(yypParser,59,&yymsp[-1].minor);
#line 380 "lemon.html.yy"
{
}
#line 3434 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[0].minor);
}
        break;
      case 162: /* tagtableblockclosefull ::= tagtableblockclose */
{  yy_destructor(yypParser,197,&yymsp[0].minor);
#line 382 "lemon.html.yy"
{
}
#line 3443 "lemon.html.c"
}
        break;
      case 163: /* tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,60,&yymsp[0].minor);
#line 384 "lemon.html.yy"
{
}
#line 3451 "lemon.html.c"
}
        break;
      case 164: /* tablecontent ::= tagthead opt__spaces_enters tagtbody opt__spaces_enters tagtfoot */
{  yy_destructor(yypParser,198,&yymsp[-4].minor);
#line 390 "lemon.html.yy"
{
}
#line 3459 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[-3].minor);
  yy_destructor(yypParser,199,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,200,&yymsp[0].minor);
}
        break;
      case 165: /* tablecontent ::= tagthead opt__spaces_enters tagtfoot opt__spaces_enters tagtbody */
{  yy_destructor(yypParser,198,&yymsp[-4].minor);
#line 391 "lemon.html.yy"
{
}
#line 3471 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[-3].minor);
  yy_destructor(yypParser,200,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,199,&yymsp[0].minor);
}
        break;
      case 166: /* tablecontent ::= tagthead opt__spaces_enters tagtbody */
{  yy_destructor(yypParser,198,&yymsp[-2].minor);
#line 392 "lemon.html.yy"
{
}
#line 3483 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,199,&yymsp[0].minor);
}
        break;
      case 167: /* tablecontent ::= tagtbody opt__spaces_enters tagtfoot */
{  yy_destructor(yypParser,199,&yymsp[-2].minor);
#line 393 "lemon.html.yy"
{
}
#line 3493 "lemon.html.c"
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,200,&yymsp[0].minor);
}
        break;
      case 168: /* tablecontent ::= tagtbody */
{  yy_destructor(yypParser,199,&yymsp[0].minor);
#line 394 "lemon.html.yy"
{
}
#line 3503 "lemon.html.c"
}
        break;
      case 169: /* tagthead ::= tagtheadfullopen tagtheadblockclosefull */
{  yy_destructor(yypParser,201,&yymsp[-1].minor);
#line 401 "lemon.html.yy"
{
}
#line 3511 "lemon.html.c"
  yy_destructor(yypParser,202,&yymsp[0].minor);
}
        break;
      case 170: /* tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull */
{  yy_destructor(yypParser,201,&yymsp[-2].minor);
#line 402 "lemon.html.yy"
{
}
#line 3520 "lemon.html.c"
  yy_destructor(yypParser,203,&yymsp[-1].minor);
  yy_destructor(yypParser,202,&yymsp[0].minor);
}
        break;
      case 171: /* tagtheadfullopen ::= tagtheadopen tagclosechar */
{  yy_destructor(yypParser,204,&yymsp[-1].minor);
#line 403 "lemon.html.yy"
{
}
#line 3530 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 172: /* tagtheadfullopen ::= tagtheadopen tagclosechar spaces */
{  yy_destructor(yypParser,204,&yymsp[-2].minor);
#line 404 "lemon.html.yy"
{
}
#line 3539 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 173: /* tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,204,&yymsp[-2].minor);
#line 405 "lemon.html.yy"
{
}
#line 3549 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 174: /* tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces */
{  yy_destructor(yypParser,204,&yymsp[-3].minor);
#line 406 "lemon.html.yy"
{
}
#line 3559 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 175: /* tagtheadopen ::= TAG_THEAD_OPEN */
{  yy_destructor(yypParser,61,&yymsp[0].minor);
#line 407 "lemon.html.yy"
{
}
#line 3570 "lemon.html.c"
}
        break;
      case 176: /* tagtheadblockclosefull ::= tagtheadblockclose */
{  yy_destructor(yypParser,206,&yymsp[0].minor);
#line 409 "lemon.html.yy"
{
}
#line 3578 "lemon.html.c"
}
        break;
      case 177: /* tagtheadblockclosefull ::= tagtheadblockclose spaces */
{  yy_destructor(yypParser,206,&yymsp[-1].minor);
#line 410 "lemon.html.yy"
{
}
#line 3586 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 178: /* tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,62,&yymsp[0].minor);
#line 412 "lemon.html.yy"
{
}
#line 3595 "lemon.html.c"
}
        break;
      case 179: /* tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull */
{  yy_destructor(yypParser,207,&yymsp[-2].minor);
#line 420 "lemon.html.yy"
{
}
#line 3603 "lemon.html.c"
  yy_destructor(yypParser,203,&yymsp[-1].minor);
  yy_destructor(yypParser,208,&yymsp[0].minor);
}
        break;
      case 180: /* tagtfootfullopen ::= tagtfootopen tagclosechar */
{  yy_destructor(yypParser,209,&yymsp[-1].minor);
#line 421 "lemon.html.yy"
{
}
#line 3613 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 181: /* tagtfootfullopen ::= tagtfootopen tagclosechar spaces */
{  yy_destructor(yypParser,209,&yymsp[-2].minor);
#line 422 "lemon.html.yy"
{
}
#line 3622 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 182: /* tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar */
{  yy_destructor(yypParser,209,&yymsp[-2].minor);
#line 423 "lemon.html.yy"
{
}
#line 3632 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 183: /* tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar spaces */
{  yy_destructor(yypParser,209,&yymsp[-3].minor);
#line 424 "lemon.html.yy"
{
}
#line 3642 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 184: /* tagtfootopen ::= TAG_TFOOT_OPEN */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 425 "lemon.html.yy"
{
}
#line 3653 "lemon.html.c"
}
        break;
      case 185: /* tagtfootblockclosefull ::= tagtfootblockclose */
{  yy_destructor(yypParser,210,&yymsp[0].minor);
#line 427 "lemon.html.yy"
{
}
#line 3661 "lemon.html.c"
}
        break;
      case 186: /* tagtfootblockclosefull ::= tagtfootblockclose spaces */
{  yy_destructor(yypParser,210,&yymsp[-1].minor);
#line 428 "lemon.html.yy"
{
}
#line 3669 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 187: /* tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE */
{  yy_destructor(yypParser,64,&yymsp[0].minor);
#line 430 "lemon.html.yy"
{
}
#line 3678 "lemon.html.c"
}
        break;
      case 188: /* tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull */
{  yy_destructor(yypParser,211,&yymsp[-2].minor);
#line 438 "lemon.html.yy"
{
}
#line 3686 "lemon.html.c"
  yy_destructor(yypParser,203,&yymsp[-1].minor);
  yy_destructor(yypParser,212,&yymsp[0].minor);
}
        break;
      case 189: /* tagtbodyfullopen ::= tagtbodyopen tagclosechar */
{  yy_destructor(yypParser,213,&yymsp[-1].minor);
#line 439 "lemon.html.yy"
{
}
#line 3696 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 190: /* tagtbodyfullopen ::= tagtbodyopen tagclosechar spaces */
{  yy_destructor(yypParser,213,&yymsp[-2].minor);
#line 440 "lemon.html.yy"
{
}
#line 3705 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 191: /* tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,213,&yymsp[-2].minor);
#line 441 "lemon.html.yy"
{
}
#line 3715 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 192: /* tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar spaces */
{  yy_destructor(yypParser,213,&yymsp[-3].minor);
#line 442 "lemon.html.yy"
{
}
#line 3725 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-2].minor);
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 193: /* tagtbodyopen ::= TAG_TBODY_OPEN */
{  yy_destructor(yypParser,65,&yymsp[0].minor);
#line 443 "lemon.html.yy"
{
}
#line 3736 "lemon.html.c"
}
        break;
      case 194: /* tagtbodyblockclosefull ::= tagtbodyblockclose */
{  yy_destructor(yypParser,214,&yymsp[0].minor);
#line 445 "lemon.html.yy"
{
}
#line 3744 "lemon.html.c"
}
        break;
      case 195: /* tagtbodyblockclosefull ::= tagtbodyblockclose spaces */
{  yy_destructor(yypParser,214,&yymsp[-1].minor);
#line 446 "lemon.html.yy"
{
}
#line 3752 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 196: /* tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,66,&yymsp[0].minor);
#line 448 "lemon.html.yy"
{
}
#line 3761 "lemon.html.c"
}
        break;
      case 197: /* tagtablerows ::= tagtablerows tagtablerow */
{  yy_destructor(yypParser,203,&yymsp[-1].minor);
#line 456 "lemon.html.yy"
{
}
#line 3769 "lemon.html.c"
  yy_destructor(yypParser,215,&yymsp[0].minor);
}
        break;
      case 198: /* tagtablerows ::= tagtablerow */
{  yy_destructor(yypParser,215,&yymsp[0].minor);
#line 457 "lemon.html.yy"
{
}
#line 3778 "lemon.html.c"
}
        break;
      case 199: /* tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull */
{  yy_destructor(yypParser,216,&yymsp[-2].minor);
#line 459 "lemon.html.yy"
{
}
#line 3786 "lemon.html.c"
  yy_destructor(yypParser,217,&yymsp[-1].minor);
  yy_destructor(yypParser,218,&yymsp[0].minor);
}
        break;
      case 200: /* tagtablerowfullopen ::= tagtablerowopen tagclosechar */
{  yy_destructor(yypParser,219,&yymsp[-1].minor);
#line 460 "lemon.html.yy"
{
}
#line 3796 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 201: /* tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces */
{  yy_destructor(yypParser,219,&yymsp[-2].minor);
#line 461 "lemon.html.yy"
{
}
#line 3805 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[-1].minor);
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 202: /* tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,219,&yymsp[-2].minor);
#line 462 "lemon.html.yy"
{
}
#line 3815 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 203: /* tagtablerowopen ::= TAG_TR_OPEN */
{  yy_destructor(yypParser,67,&yymsp[0].minor);
#line 464 "lemon.html.yy"
{
}
#line 3825 "lemon.html.c"
}
        break;
      case 204: /* tagtablerowblockclosefull ::= tagtablerowblockclose */
{  yy_destructor(yypParser,220,&yymsp[0].minor);
#line 466 "lemon.html.yy"
{
}
#line 3833 "lemon.html.c"
}
        break;
      case 205: /* tagtablerowblockclosefull ::= tagtablerowblockclose spaces */
{  yy_destructor(yypParser,220,&yymsp[-1].minor);
#line 467 "lemon.html.yy"
{
}
#line 3841 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 206: /* tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE */
{  yy_destructor(yypParser,68,&yymsp[0].minor);
#line 469 "lemon.html.yy"
{
}
#line 3850 "lemon.html.c"
}
        break;
      case 207: /* tagtablecols ::= tagtablecols tagtablecol */
{  yy_destructor(yypParser,217,&yymsp[-1].minor);
#line 473 "lemon.html.yy"
{
}
#line 3858 "lemon.html.c"
  yy_destructor(yypParser,221,&yymsp[0].minor);
}
        break;
      case 208: /* tagtablecols ::= tagtablecol */
{  yy_destructor(yypParser,221,&yymsp[0].minor);
#line 474 "lemon.html.yy"
{
}
#line 3867 "lemon.html.c"
}
        break;
      case 209: /* tagtablecol ::= tagtablecoltd */
{  yy_destructor(yypParser,222,&yymsp[0].minor);
#line 476 "lemon.html.yy"
{
}
#line 3875 "lemon.html.c"
}
        break;
      case 210: /* tagtablecol ::= tagtablecolth */
{  yy_destructor(yypParser,223,&yymsp[0].minor);
#line 477 "lemon.html.yy"
{
}
#line 3883 "lemon.html.c"
}
        break;
      case 211: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-1].minor);
#line 483 "lemon.html.yy"
{
}
#line 3891 "lemon.html.c"
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 212: /* tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-2].minor);
#line 484 "lemon.html.yy"
{
}
#line 3900 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 213: /* tagtablecoltd ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-4].minor);
#line 485 "lemon.html.yy"
{
}
#line 3910 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[-3].minor);
  yy_destructor(yypParser,114,&yymsp[-2].minor);
  yy_destructor(yypParser,125,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 214: /* tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-2].minor);
#line 486 "lemon.html.yy"
{
}
#line 3922 "lemon.html.c"
  yy_destructor(yypParser,226,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 215: /* tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull */
{  yy_destructor(yypParser,224,&yymsp[-3].minor);
#line 487 "lemon.html.yy"
{
}
#line 3932 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[-2].minor);
  yy_destructor(yypParser,226,&yymsp[-1].minor);
  yy_destructor(yypParser,225,&yymsp[0].minor);
}
        break;
      case 216: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar */
{  yy_destructor(yypParser,227,&yymsp[-1].minor);
#line 488 "lemon.html.yy"
{
}
#line 3943 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 217: /* tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar */
{  yy_destructor(yypParser,227,&yymsp[-2].minor);
#line 490 "lemon.html.yy"
{
}
#line 3952 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 218: /* tagtablecoltdopen ::= TAG_TD_OPEN */
{  yy_destructor(yypParser,69,&yymsp[0].minor);
#line 492 "lemon.html.yy"
{
}
#line 3962 "lemon.html.c"
}
        break;
      case 219: /* tagtablecoltdblockclosefull ::= tagtablecoltdblockclose */
{  yy_destructor(yypParser,228,&yymsp[0].minor);
#line 494 "lemon.html.yy"
{
}
#line 3970 "lemon.html.c"
}
        break;
      case 220: /* tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces */
{  yy_destructor(yypParser,228,&yymsp[-1].minor);
#line 495 "lemon.html.yy"
{
}
#line 3978 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 221: /* tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE */
{  yy_destructor(yypParser,70,&yymsp[0].minor);
#line 497 "lemon.html.yy"
{
}
#line 3987 "lemon.html.c"
}
        break;
      case 222: /* tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent */
{  yy_destructor(yypParser,226,&yymsp[-1].minor);
#line 500 "lemon.html.yy"
{
}
#line 3995 "lemon.html.c"
  yy_destructor(yypParser,229,&yymsp[0].minor);
}
        break;
      case 223: /* tagtablecolcontents ::= tagtablecolcontent */
{  yy_destructor(yypParser,229,&yymsp[0].minor);
#line 501 "lemon.html.yy"
{
}
#line 4004 "lemon.html.c"
}
        break;
      case 224: /* tagtablecolcontent ::= taginput */
{  yy_destructor(yypParser,166,&yymsp[0].minor);
#line 503 "lemon.html.yy"
{
}
#line 4012 "lemon.html.c"
}
        break;
      case 225: /* tagtablecolcontent ::= taginput spaces */
{  yy_destructor(yypParser,166,&yymsp[-1].minor);
#line 504 "lemon.html.yy"
{
}
#line 4020 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 227: /* tagtablecolcontent ::= htmltext spaces */
{  yy_destructor(yypParser,115,&yymsp[-1].minor);
#line 506 "lemon.html.yy"
{
}
#line 4029 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 229: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull */
{  yy_destructor(yypParser,230,&yymsp[-1].minor);
#line 513 "lemon.html.yy"
{
}
#line 4038 "lemon.html.c"
  yy_destructor(yypParser,231,&yymsp[0].minor);
}
        break;
      case 230: /* tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull */
{  yy_destructor(yypParser,230,&yymsp[-2].minor);
#line 514 "lemon.html.yy"
{
}
#line 4047 "lemon.html.c"
  yy_destructor(yypParser,226,&yymsp[-1].minor);
  yy_destructor(yypParser,231,&yymsp[0].minor);
}
        break;
      case 231: /* tagtablecolthfullopen ::= tagtablecolthopen tagclosechar */
{  yy_destructor(yypParser,232,&yymsp[-1].minor);
#line 515 "lemon.html.yy"
{
}
#line 4057 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 232: /* tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar */
{  yy_destructor(yypParser,232,&yymsp[-2].minor);
#line 517 "lemon.html.yy"
{
}
#line 4066 "lemon.html.c"
  yy_destructor(yypParser,205,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 233: /* tagtablecolthopen ::= TAG_TH_OPEN */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 519 "lemon.html.yy"
{
}
#line 4076 "lemon.html.c"
}
        break;
      case 234: /* tagtablecolthblockclosefull ::= tagtablecolthblockclose */
{  yy_destructor(yypParser,233,&yymsp[0].minor);
#line 521 "lemon.html.yy"
{
}
#line 4084 "lemon.html.c"
}
        break;
      case 235: /* tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces */
{  yy_destructor(yypParser,233,&yymsp[-1].minor);
#line 522 "lemon.html.yy"
{
}
#line 4092 "lemon.html.c"
  yy_destructor(yypParser,125,&yymsp[0].minor);
}
        break;
      case 236: /* tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE */
{  yy_destructor(yypParser,72,&yymsp[0].minor);
#line 524 "lemon.html.yy"
{
}
#line 4101 "lemon.html.c"
}
        break;
      case 237: /* tagtitle ::= tagtitlefullopen tagtitleblockclosefull */
{  yy_destructor(yypParser,234,&yymsp[-1].minor);
#line 532 "lemon.html.yy"
{
}
#line 4109 "lemon.html.c"
  yy_destructor(yypParser,235,&yymsp[0].minor);
}
        break;
      case 238: /* tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull */
{  yy_destructor(yypParser,234,&yymsp[-2].minor);
#line 533 "lemon.html.yy"
{
}
#line 4118 "lemon.html.c"
  yy_destructor(yypParser,236,&yymsp[-1].minor);
  yy_destructor(yypParser,235,&yymsp[0].minor);
}
        break;
      case 239: /* tagtitlefullopen ::= tagtitleopen tagclosechar */
{  yy_destructor(yypParser,237,&yymsp[-1].minor);
#line 534 "lemon.html.yy"
{
}
#line 4128 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 240: /* tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar */
{  yy_destructor(yypParser,237,&yymsp[-2].minor);
#line 535 "lemon.html.yy"
{
}
#line 4137 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 241: /* tagtitleblockclosefull ::= tagtitleblockclose */
{  yy_destructor(yypParser,238,&yymsp[0].minor);
#line 536 "lemon.html.yy"
{
}
#line 4147 "lemon.html.c"
}
        break;
      case 242: /* tagtitleopen ::= TAG_TITLE_OPEN */
{  yy_destructor(yypParser,73,&yymsp[0].minor);
#line 537 "lemon.html.yy"
{
}
#line 4155 "lemon.html.c"
}
        break;
      case 243: /* tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,74,&yymsp[0].minor);
#line 538 "lemon.html.yy"
{
}
#line 4163 "lemon.html.c"
}
        break;
      case 244: /* taglink ::= taglinkfullopen */
{  yy_destructor(yypParser,239,&yymsp[0].minor);
#line 544 "lemon.html.yy"
{
}
#line 4171 "lemon.html.c"
}
        break;
      case 245: /* taglink ::= taglinkfullopen taglinkblockclosefull */
{  yy_destructor(yypParser,239,&yymsp[-1].minor);
#line 545 "lemon.html.yy"
{
}
#line 4179 "lemon.html.c"
  yy_destructor(yypParser,240,&yymsp[0].minor);
}
        break;
      case 246: /* taglinkfullopen ::= taglinkopen tagproperties tagclosechar */
{  yy_destructor(yypParser,241,&yymsp[-2].minor);
#line 546 "lemon.html.yy"
{
}
#line 4188 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 247: /* taglinkfullopen ::= taglinkopen tagproperties tagshortclose */
{  yy_destructor(yypParser,241,&yymsp[-2].minor);
#line 547 "lemon.html.yy"
{
}
#line 4198 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,242,&yymsp[0].minor);
}
        break;
      case 248: /* taglinkblockclosefull ::= taglinkblockclose */
{  yy_destructor(yypParser,243,&yymsp[0].minor);
#line 549 "lemon.html.yy"
{
}
#line 4208 "lemon.html.c"
}
        break;
      case 249: /* taglinkopen ::= TAG_LINK_OPEN */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 551 "lemon.html.yy"
{
}
#line 4216 "lemon.html.c"
}
        break;
      case 250: /* taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE */
{  yy_destructor(yypParser,76,&yymsp[0].minor);
#line 552 "lemon.html.yy"
{
}
#line 4224 "lemon.html.c"
}
        break;
      case 251: /* tagmeta ::= tagmetafullopen */
{  yy_destructor(yypParser,244,&yymsp[0].minor);
#line 559 "lemon.html.yy"
{
}
#line 4232 "lemon.html.c"
}
        break;
      case 252: /* tagmeta ::= tagmetafullopen tagmetablockclosefull */
{  yy_destructor(yypParser,244,&yymsp[-1].minor);
#line 560 "lemon.html.yy"
{
}
#line 4240 "lemon.html.c"
  yy_destructor(yypParser,245,&yymsp[0].minor);
}
        break;
      case 253: /* tagmetafullopen ::= tagmetaopen tagproperties tagclosechar */
{  yy_destructor(yypParser,246,&yymsp[-2].minor);
#line 561 "lemon.html.yy"
{
}
#line 4249 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 254: /* tagmetafullopen ::= tagmetaopen tagproperties tagshortclose */
{  yy_destructor(yypParser,246,&yymsp[-2].minor);
#line 562 "lemon.html.yy"
{
}
#line 4259 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,242,&yymsp[0].minor);
}
        break;
      case 255: /* tagmetablockclosefull ::= tagmetablockclose */
{  yy_destructor(yypParser,247,&yymsp[0].minor);
#line 564 "lemon.html.yy"
{
}
#line 4269 "lemon.html.c"
}
        break;
      case 256: /* tagmetaopen ::= TAG_META_OPEN */
{  yy_destructor(yypParser,77,&yymsp[0].minor);
#line 566 "lemon.html.yy"
{
}
#line 4277 "lemon.html.c"
}
        break;
      case 257: /* tagmetablockclose ::= TAG_META_BLOCK_CLOSE */
{  yy_destructor(yypParser,78,&yymsp[0].minor);
#line 567 "lemon.html.yy"
{
}
#line 4285 "lemon.html.c"
}
        break;
      case 258: /* tagstyle ::= tagstylefullopen tagstyleblockclosefull */
{  yy_destructor(yypParser,248,&yymsp[-1].minor);
#line 574 "lemon.html.yy"
{
}
#line 4293 "lemon.html.c"
  yy_destructor(yypParser,249,&yymsp[0].minor);
}
        break;
      case 259: /* tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull */
{  yy_destructor(yypParser,248,&yymsp[-2].minor);
#line 575 "lemon.html.yy"
{
}
#line 4302 "lemon.html.c"
  yy_destructor(yypParser,236,&yymsp[-1].minor);
  yy_destructor(yypParser,249,&yymsp[0].minor);
}
        break;
      case 260: /* tagstylefullopen ::= tagstyleopen tagclosechar */
{  yy_destructor(yypParser,250,&yymsp[-1].minor);
#line 576 "lemon.html.yy"
{
}
#line 4312 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 261: /* tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar */
{  yy_destructor(yypParser,250,&yymsp[-2].minor);
#line 577 "lemon.html.yy"
{
}
#line 4321 "lemon.html.c"
  yy_destructor(yypParser,251,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 262: /* tagstyleblockclosefull ::= tagstyleblockclose */
{  yy_destructor(yypParser,252,&yymsp[0].minor);
#line 579 "lemon.html.yy"
{
}
#line 4331 "lemon.html.c"
}
        break;
      case 263: /* tagstyleopen ::= TAG_STYLE_OPEN */
{  yy_destructor(yypParser,79,&yymsp[0].minor);
#line 581 "lemon.html.yy"
{
}
#line 4339 "lemon.html.c"
}
        break;
      case 264: /* tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,80,&yymsp[0].minor);
#line 582 "lemon.html.yy"
{
}
#line 4347 "lemon.html.c"
}
        break;
      case 265: /* tagstyleproperties ::= tagstyleproperties tagstyleproperty */
{  yy_destructor(yypParser,251,&yymsp[-1].minor);
#line 585 "lemon.html.yy"
{
}
#line 4355 "lemon.html.c"
  yy_destructor(yypParser,253,&yymsp[0].minor);
}
        break;
      case 266: /* tagstyleproperties ::= tagstyleproperty */
{  yy_destructor(yypParser,253,&yymsp[0].minor);
#line 586 "lemon.html.yy"
{
}
#line 4364 "lemon.html.c"
}
        break;
      case 267: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 588 "lemon.html.yy"
{
}
#line 4372 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 268: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 589 "lemon.html.yy"
{
}
#line 4383 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 269: /* tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */
      case 315: /* tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==315);
{  yy_destructor(yypParser,102,&yymsp[-3].minor);
#line 590 "lemon.html.yy"
{
}
#line 4395 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 270: /* tagscript ::= tagscriptfullopen tagscriptblockclosefull */
{  yy_destructor(yypParser,254,&yymsp[-1].minor);
#line 597 "lemon.html.yy"
{
}
#line 4406 "lemon.html.c"
  yy_destructor(yypParser,255,&yymsp[0].minor);
}
        break;
      case 271: /* tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull */
{  yy_destructor(yypParser,254,&yymsp[-2].minor);
#line 598 "lemon.html.yy"
{
}
#line 4415 "lemon.html.c"
  yy_destructor(yypParser,236,&yymsp[-1].minor);
  yy_destructor(yypParser,255,&yymsp[0].minor);
}
        break;
      case 272: /* tagscriptfullopen ::= tagscriptopen tagclosechar */
{  yy_destructor(yypParser,256,&yymsp[-1].minor);
#line 599 "lemon.html.yy"
{
}
#line 4425 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 273: /* tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar */
{  yy_destructor(yypParser,256,&yymsp[-2].minor);
#line 600 "lemon.html.yy"
{
}
#line 4434 "lemon.html.c"
  yy_destructor(yypParser,257,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 274: /* tagscriptblockclosefull ::= tagscriptblockclose */
{  yy_destructor(yypParser,258,&yymsp[0].minor);
#line 602 "lemon.html.yy"
{
}
#line 4444 "lemon.html.c"
}
        break;
      case 275: /* tagscriptopen ::= TAG_SCRIPT_OPEN */
{  yy_destructor(yypParser,83,&yymsp[0].minor);
#line 604 "lemon.html.yy"
{
}
#line 4452 "lemon.html.c"
}
        break;
      case 276: /* tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE */
{  yy_destructor(yypParser,84,&yymsp[0].minor);
#line 605 "lemon.html.yy"
{
}
#line 4460 "lemon.html.c"
}
        break;
      case 277: /* tagscriptproperties ::= tagscriptproperties tagscriptproperty */
{  yy_destructor(yypParser,257,&yymsp[-1].minor);
#line 609 "lemon.html.yy"
{
}
#line 4468 "lemon.html.c"
  yy_destructor(yypParser,259,&yymsp[0].minor);
}
        break;
      case 278: /* tagscriptproperties ::= tagscriptproperty */
{  yy_destructor(yypParser,259,&yymsp[0].minor);
#line 610 "lemon.html.yy"
{
}
#line 4477 "lemon.html.c"
}
        break;
      case 279: /* tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA */
{  yy_destructor(yypParser,260,&yymsp[-1].minor);
#line 612 "lemon.html.yy"
{
}
#line 4485 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 280: /* tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 614 "lemon.html.yy"
{
}
#line 4494 "lemon.html.c"
  yy_destructor(yypParser,82,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 281: /* tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA */
{  yy_destructor(yypParser,261,&yymsp[-1].minor);
#line 616 "lemon.html.yy"
{
}
#line 4504 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 282: /* tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 618 "lemon.html.yy"
{
}
#line 4513 "lemon.html.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 283: /* taghtml ::= taghtmlfullopen taghtmlblockclosefull */
{  yy_destructor(yypParser,262,&yymsp[-1].minor);
#line 624 "lemon.html.yy"
{
}
#line 4523 "lemon.html.c"
  yy_destructor(yypParser,263,&yymsp[0].minor);
}
        break;
      case 284: /* taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull */
{  yy_destructor(yypParser,262,&yymsp[-2].minor);
#line 625 "lemon.html.yy"
{
}
#line 4532 "lemon.html.c"
  yy_destructor(yypParser,264,&yymsp[-1].minor);
  yy_destructor(yypParser,263,&yymsp[0].minor);
}
        break;
      case 285: /* taghtmlfullopen ::= taghtmlopen tagclosechar */
{  yy_destructor(yypParser,265,&yymsp[-1].minor);
#line 626 "lemon.html.yy"
{
}
#line 4542 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 286: /* taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar */
{  yy_destructor(yypParser,265,&yymsp[-2].minor);
#line 627 "lemon.html.yy"
{
}
#line 4551 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 287: /* taghtmlblockclosefull ::= TAG_HTML_BLOCK_CLOSE */
{  yy_destructor(yypParser,85,&yymsp[0].minor);
#line 629 "lemon.html.yy"
{
}
#line 4561 "lemon.html.c"
}
        break;
      case 288: /* taghtmlopen ::= TAG_HTML_OPEN */
{  yy_destructor(yypParser,86,&yymsp[0].minor);
#line 631 "lemon.html.yy"
{
}
#line 4569 "lemon.html.c"
}
        break;
      case 289: /* taghtmlcontents ::= taghtmlcontents taghtmlcontent */
{  yy_destructor(yypParser,264,&yymsp[-1].minor);
#line 633 "lemon.html.yy"
{
}
#line 4577 "lemon.html.c"
  yy_destructor(yypParser,266,&yymsp[0].minor);
}
        break;
      case 290: /* taghtmlcontents ::= taghtmlcontent */
{  yy_destructor(yypParser,266,&yymsp[0].minor);
#line 634 "lemon.html.yy"
{
}
#line 4586 "lemon.html.c"
}
        break;
      case 293: /* taghtmlcontent ::= tagbody */
{  yy_destructor(yypParser,267,&yymsp[0].minor);
#line 638 "lemon.html.yy"
{
}
#line 4594 "lemon.html.c"
}
        break;
      case 294: /* taghtmlcontent ::= taghead tagbody */
{  yy_destructor(yypParser,268,&yymsp[-1].minor);
#line 639 "lemon.html.yy"
{
}
#line 4602 "lemon.html.c"
  yy_destructor(yypParser,267,&yymsp[0].minor);
}
        break;
      case 295: /* taghtmlcontent ::= taghead spaces_enters tagbody */
{  yy_destructor(yypParser,268,&yymsp[-2].minor);
#line 640 "lemon.html.yy"
{
}
#line 4611 "lemon.html.c"
  yy_destructor(yypParser,99,&yymsp[-1].minor);
  yy_destructor(yypParser,267,&yymsp[0].minor);
}
        break;
      case 296: /* tagbody ::= tagbodyfullopen tagbodyblockclosefull */
{  yy_destructor(yypParser,269,&yymsp[-1].minor);
#line 647 "lemon.html.yy"
{
}
#line 4621 "lemon.html.c"
  yy_destructor(yypParser,270,&yymsp[0].minor);
}
        break;
      case 297: /* tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull */
{  yy_destructor(yypParser,269,&yymsp[-2].minor);
#line 648 "lemon.html.yy"
{
}
#line 4630 "lemon.html.c"
  yy_destructor(yypParser,111,&yymsp[-1].minor);
  yy_destructor(yypParser,270,&yymsp[0].minor);
}
        break;
      case 298: /* tagbodyfullopen ::= tagbodyopen tagclosechar */
{  yy_destructor(yypParser,271,&yymsp[-1].minor);
#line 650 "lemon.html.yy"
{
}
#line 4640 "lemon.html.c"
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 299: /* tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar */
{  yy_destructor(yypParser,271,&yymsp[-2].minor);
#line 652 "lemon.html.yy"
{
}
#line 4649 "lemon.html.c"
  yy_destructor(yypParser,196,&yymsp[-1].minor);
  yy_destructor(yypParser,124,&yymsp[0].minor);
}
        break;
      case 300: /* tagbodyblockclosefull ::= tagbodyblockclose */
{  yy_destructor(yypParser,272,&yymsp[0].minor);
#line 654 "lemon.html.yy"
{
}
#line 4659 "lemon.html.c"
}
        break;
      case 301: /* tagbodyopen ::= TAG_BODY_OPEN */
{  yy_destructor(yypParser,87,&yymsp[0].minor);
#line 656 "lemon.html.yy"
{
}
#line 4667 "lemon.html.c"
}
        break;
      case 302: /* tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,88,&yymsp[0].minor);
#line 658 "lemon.html.yy"
{
}
#line 4675 "lemon.html.c"
}
        break;
      case 303: /* taghead ::= tagheadfullopen tagheadblockclosefull */
{  yy_destructor(yypParser,273,&yymsp[-1].minor);
#line 666 "lemon.html.yy"
{
}
#line 4683 "lemon.html.c"
  yy_destructor(yypParser,274,&yymsp[0].minor);
}
        break;
      case 304: /* taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull */
{  yy_destructor(yypParser,273,&yymsp[-2].minor);
#line 667 "lemon.html.yy"
{
}
#line 4692 "lemon.html.c"
  yy_destructor(yypParser,104,&yymsp[-1].minor);
  yy_destructor(yypParser,274,&yymsp[0].minor);
}
        break;
      case 305: /* tagheadfullopen ::= tagheadopen */
{  yy_destructor(yypParser,275,&yymsp[0].minor);
#line 669 "lemon.html.yy"
{
}
#line 4702 "lemon.html.c"
}
        break;
      case 306: /* tagheadblockclosefull ::= tagheadblockclose */
{  yy_destructor(yypParser,276,&yymsp[0].minor);
#line 671 "lemon.html.yy"
{
}
#line 4710 "lemon.html.c"
}
        break;
      case 307: /* tagheadopen ::= TAG_HEAD_OPEN */
{  yy_destructor(yypParser,89,&yymsp[0].minor);
#line 673 "lemon.html.yy"
{
}
#line 4718 "lemon.html.c"
}
        break;
      case 308: /* tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,90,&yymsp[0].minor);
#line 675 "lemon.html.yy"
{
}
#line 4726 "lemon.html.c"
}
        break;
      case 309: /* tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues */
{  yy_destructor(yypParser,277,&yymsp[0].minor);
#line 683 "lemon.html.yy"
{
}
#line 4734 "lemon.html.c"
}
        break;
      case 310: /* tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue */
{  yy_destructor(yypParser,277,&yymsp[-1].minor);
#line 685 "lemon.html.yy"
{
}
#line 4742 "lemon.html.c"
  yy_destructor(yypParser,278,&yymsp[0].minor);
}
        break;
      case 311: /* tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue */
{  yy_destructor(yypParser,278,&yymsp[0].minor);
#line 687 "lemon.html.yy"
{
}
#line 4751 "lemon.html.c"
}
        break;
      case 312: /* tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,19,&yymsp[-2].minor);
#line 689 "lemon.html.yy"
{
}
#line 4759 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 313: /* tagproperties ::= tagproperties tagproperty */
{  yy_destructor(yypParser,196,&yymsp[-1].minor);
#line 696 "lemon.html.yy"
{
}
#line 4769 "lemon.html.c"
  yy_destructor(yypParser,279,&yymsp[0].minor);
}
        break;
      case 314: /* tagproperties ::= tagproperty */
{  yy_destructor(yypParser,279,&yymsp[0].minor);
#line 697 "lemon.html.yy"
{
}
#line 4778 "lemon.html.c"
}
        break;
      case 316: /* tagclosechar ::= TAG_CLOSE */
{  yy_destructor(yypParser,91,&yymsp[0].minor);
#line 703 "lemon.html.yy"
{
}
#line 4786 "lemon.html.c"
}
        break;
      case 317: /* tagclosechar ::= SPACE TAG_CLOSE */
{  yy_destructor(yypParser,7,&yymsp[-1].minor);
#line 704 "lemon.html.yy"
{
}
#line 4794 "lemon.html.c"
  yy_destructor(yypParser,91,&yymsp[0].minor);
}
        break;
      case 319: /* htmlandspaces ::= htmlandspaces htmlandspace */
{  yy_destructor(yypParser,236,&yymsp[-1].minor);
#line 713 "lemon.html.yy"
{
}
#line 4803 "lemon.html.c"
  yy_destructor(yypParser,280,&yymsp[0].minor);
}
        break;
      case 320: /* htmlandspaces ::= htmlandspace */
{  yy_destructor(yypParser,280,&yymsp[0].minor);
#line 714 "lemon.html.yy"
{
}
#line 4812 "lemon.html.c"
}
        break;
      case 321: /* htmlandspace ::= HTMLTEXT */
      case 323: /* htmltext ::= HTMLTEXT */ yytestcase(yyruleno==323);
{  yy_destructor(yypParser,92,&yymsp[0].minor);
#line 716 "lemon.html.yy"
{
}
#line 4821 "lemon.html.c"
}
        break;
      case 322: /* htmlandspace ::= SPACE */
      case 332: /* space ::= SPACE */ yytestcase(yyruleno==332);
{  yy_destructor(yypParser,7,&yymsp[0].minor);
#line 717 "lemon.html.yy"
{
}
#line 4830 "lemon.html.c"
}
        break;
      case 324: /* opt__spaces_enters ::= spaces_enters */
{  yy_destructor(yypParser,99,&yymsp[0].minor);
#line 726 "lemon.html.yy"
{
}
#line 4838 "lemon.html.c"
}
        break;
      case 326: /* spaces_enters ::= spaces_enters spaces_enter */
{  yy_destructor(yypParser,99,&yymsp[-1].minor);
#line 729 "lemon.html.yy"
{
}
#line 4846 "lemon.html.c"
  yy_destructor(yypParser,281,&yymsp[0].minor);
}
        break;
      case 327: /* spaces_enters ::= spaces_enter */
{  yy_destructor(yypParser,281,&yymsp[0].minor);
#line 730 "lemon.html.yy"
{
}
#line 4855 "lemon.html.c"
}
        break;
      case 330: /* spaces ::= spaces space */
{  yy_destructor(yypParser,125,&yymsp[-1].minor);
#line 736 "lemon.html.yy"
{
}
#line 4863 "lemon.html.c"
  yy_destructor(yypParser,102,&yymsp[0].minor);
}
        break;
      case 333: /* enter ::= ENTER */
{  yy_destructor(yypParser,93,&yymsp[0].minor);
#line 743 "lemon.html.yy"
{
}
#line 4872 "lemon.html.c"
}
        break;
      default:
      /* (325) opt__spaces_enters ::= */ yytestcase(yyruleno==325);
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
#line 30 "lemon.html.yy"

    printf("--SYNTAX ERROR--");
    exit(100);
#line 4937 "lemon.html.c"
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
