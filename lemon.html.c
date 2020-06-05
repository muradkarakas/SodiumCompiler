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
#define YYNOCODE 296
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
#define YYNSTATE             263
#define YYNRULE              350
#define YY_MAX_SHIFT         262
#define YY_MIN_SHIFTREDUCE   548
#define YY_MAX_SHIFTREDUCE   897
#define YY_MIN_REDUCE        898
#define YY_MAX_REDUCE        1247
#define YY_ERROR_ACTION      1248
#define YY_ACCEPT_ACTION     1249
#define YY_NO_ACTION         1250
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
#define YY_ACTTAB_COUNT (899)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   112,    4,  623,  624, 1249,   55,   55,   73,   55,   55,
 /*    10 */    55,  897,   53,    4,    4,    4,    4,    4,    4,    4,
 /*    20 */     4,    4,  897,  897,  112,  836,  722,  112,   79,  621,
 /*    30 */    17,  111,  624,   51,   17,   17,   17,    9,  224,  109,
 /*    40 */    46,   26,  619,   11,  818,   38,  826,  624,  834,   16,
 /*    50 */   842,  112,  106,   53,  853,  625,  626,   15,  628,  149,
 /*    60 */     8,  879,  242,  241,  240,  239,  238,  237,  236,  235,
 /*    70 */   234,  233,  232,  231,  230,  229,  228,  227,  226,  225,
 /*    80 */   627,  866,  872,  723,  118,  724,  243,  222,  221,  220,
 /*    90 */   219,  218,  217,  216,  215,  214,  213,  212,  211,  210,
 /*   100 */   209,  208,  207,  206,  821,   18,    1,   82,   47,    1,
 /*   110 */   243,  222,  221,  220,  219,  218,  217,  216,  215,  214,
 /*   120 */   213,  212,  211,  210,  209,  208,  207,  206,  247,  245,
 /*   130 */   655,  110,    6,    6,    6,    6,    6,    6,    6,  151,
 /*   140 */   676,  262,  259,  655,  655,  655,  655,  655,  655,  655,
 /*   150 */   655,  851,  780,  752,  103,  786,  786,  786,    9,  566,
 /*   160 */   111,   46,   51,  624,   11,   49,   38,   44,  109,   25,
 /*   170 */    26,   25,  258,  253,  252,  251,   75,  852,   16,   75,
 /*   180 */   867,  106,   86,   19,  639,   39,   15,  639,  639,    8,
 /*   190 */   648,  648,  648,  648,  648,  648,  709,  182,  181,  180,
 /*   200 */   179,  178,  177,  176,  175,  174,  173,  172,  171,  170,
 /*   210 */   169,  645,  548,  549,  204,    7,   52,  897,    7,  182,
 /*   220 */   181,  180,  179,  178,  177,  176,  175,  174,  173,  172,
 /*   230 */   171,  170,  169,  556,   18,  849,  556,   47,   78,  198,
 /*   240 */   830,  158,  196,  195,  194,  193,  192,  191,  190,  189,
 /*   250 */   188,  187,  186,  185,  184,  183,  198,   52,  620,  196,
 /*   260 */   195,  194,  193,  192,  191,  190,  189,  188,  187,  186,
 /*   270 */   185,  184,  183,   35,  617,  618,   42,  204,   83,  622,
 /*   280 */    67,  988,  645,   81,  895,   66,  721,   32,  897,   41,
 /*   290 */   593,  897,   10,   31,   40,   27,   40,  162,  159,  100,
 /*   300 */    97,  634,  893,  822,  590,  591,  592,   13,   97,  868,
 /*   310 */   873,   86,  119,  888,   12,   97,  897,   88,  204,   10,
 /*   320 */   799,   97,  855,  162,  159,  590,  591,  592,  616,  116,
 /*   330 */    35,  799,   97,   42,  568,   83,  893,   67,  261,  260,
 /*   340 */    81,  629,   66,  622,   32,  895,   41,  799,   97,  616,
 /*   350 */    31,  248,   27,   85,   85,   72,  116,  590,  591,  592,
 /*   360 */   627,  894,   98,   74,  626,    3,  628,  874,  831,  119,
 /*   370 */    98,   74,  550,    3,  616,  897,  850,   98,   74,   78,
 /*   380 */     3,  616,  894,   98,   74,  854,    3,  672,   18,  692,
 /*   390 */   672,   47,  627,  892,   98,   74,   18,    3,  890,   47,
 /*   400 */   745,   20,  884,   18,  745,   95,   47,  894,  113,   18,
 /*   410 */    98,   74,   47,    3,  894,  843,   20,   20,  872,  153,
 /*   420 */    18,  791,   14,   47,   99,   14,   33,  892,  204,  790,
 /*   430 */    13,  823,   99,   13,  754,  835,   18,   12,  634,   47,
 /*   440 */    12,   50,  806,   45,   96,  838,  799,  757,  807,  813,
 /*   450 */    96,   89,   84,  793,   76,  827,   99,  799,  701,   20,
 /*   460 */   778,   22,  701,   20,   37,  884,  894,  808,   21,  794,
 /*   470 */   205,  837,   99,  799,   79,  744,  105,  135,  135,  744,
 /*   480 */    24,   68,  792,   23,   21,   99,   36,  204,  153,   21,
 /*   490 */   145,  890,   71,   49,  897,   44,  114,  552,  689,  890,
 /*   500 */   704,  557,  764,  589,  104,   18,   33,  690,   47,  778,
 /*   510 */    22,  567,  647,   37,  839,  704,  704,  687,   21,  866,
 /*   520 */   641,  687,   21,  693,   70,   69,  859,  698,  859,    2,
 /*   530 */   204,   43,   50,    5,   45,  637,   49,  617,   44,  693,
 /*   540 */   257,  256,  255,  254,  693,  145,  893,   71,  261,  260,
 /*   550 */   756,   28,  616,  204,   89,  156,   77,  702,  115,  205,
 /*   560 */   887,  702,  704,   28,   22,  135,  135,   37,  558,  108,
 /*   570 */   148,  771,  688,   92,  778,   22,  688,  693,   37,  814,
 /*   580 */   553,  636,   57,  204,   57,  894,  683,  258,  253,  252,
 /*   590 */   251,  150,  889,  812,   54,   34,   84,  204,  204,  204,
 /*   600 */   204,   29,  152,  204,   18,  895,  201,   47,   48,  635,
 /*   610 */    48,  262,  259,   29,   22,  205,  884,   37,   30,  819,
 /*   620 */   204,  888,  200,  815,   91,   94,  795,  135,  135,  102,
 /*   630 */    30,   22,  204,  888,   37,   54,  204,  892,   56,  204,
 /*   640 */   204,  257,  256,  255,  254,  107,  869,  668,  250,  887,
 /*   650 */   751,  164,   65,  844,  155,   65,  250,   50,   90,   45,
 /*   660 */   887,   58,   93,  160,  161,  796,  101,  594,  595,  596,
 /*   670 */   247,  245,  157,  888,  620,   34,  622,  154,  201,  878,
 /*   680 */    87,  887,  117,  120,  829,  121,   80,    2,  783,   43,
 /*   690 */   122,   59,  887,  123,  124,   19,  887,   39,  125,  126,
 /*   700 */   860,  127,  860,  128,  249,  887,   60,   61,   62,  117,
 /*   710 */   120,   64,  121,  809,  876,  168,  166,  122,   56,  129,
 /*   720 */   123,  124,  130,  131,  132,  125,  126,  133,  127,  134,
 /*   730 */   128,  136,  137,  200,  138,  881,  139,   63,  140,  141,
 /*   740 */   551,   58,  142,  143,  887,  888,  129,  144,  146,  130,
 /*   750 */   131,  132,  633,  858,  133,  147,  134,  857,  136,  137,
 /*   760 */   632,  138,  887,  139,   63,  140,  141,  887,  887,  142,
 /*   770 */   143,   59,  665,  848,  144,  146,  847,  163,  165,  846,
 /*   780 */   167,  587,  147,  585,  584,  884,   60,   61,   62,  583,
 /*   790 */   582,   64,  581,  888,  580,  579,  577,  575,  574,  573,
 /*   800 */   571,  569,  888,  203,  900,  588,  586,  719,  884,  718,
 /*   810 */   717,  716,  202,  223,  900,  715,  714,  578,  576,  713,
 /*   820 */   884,  712,  743,  742,  884,  572,  570,  884,  884,  197,
 /*   830 */   199,  711,  883,  886,  614,  613,  612,  611,  610,  609,
 /*   840 */   608,  607,  606,  605,  604,  603,  602,  601,  600,  599,
 /*   850 */   598,  615,  900,  900,  900,  741,  740,  739,  738,  737,
 /*   860 */   736,  735,  900,  900,  900,  734,  733,  732,  731,  730,
 /*   870 */   729,  728,  900,  900,  597,  727,  726,  700,  244,  246,
 /*   880 */   249,  565,  900,  670,  564,  671,  562,  560,  686,  900,
 /*   890 */   900,  563,  559,  561,  685,  555,  679,  678,  554,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   105,  105,   72,   73,  100,  101,  102,  103,  104,  105,
 /*    10 */   106,    7,  253,  117,  118,  119,  120,  121,  122,  123,
 /*    20 */   124,  125,    7,    7,  105,  266,  131,  132,  269,   70,
 /*    30 */   234,  135,   73,  137,  238,  239,  240,  241,   23,  143,
 /*    40 */   244,  145,   68,  247,   79,  249,   81,   73,   83,  153,
 /*    50 */    85,  132,  156,  294,   89,   74,   75,  161,   77,    7,
 /*    60 */   164,   96,   47,   48,   49,   50,   51,   52,   53,   54,
 /*    70 */    55,   56,   57,   58,   59,   60,   61,   62,   63,   64,
 /*    80 */    76,   92,   93,  188,   95,  190,  191,  192,  193,  194,
 /*    90 */   195,  196,  197,  198,  199,  200,  201,  202,  203,  204,
 /*   100 */   205,  206,  207,  208,  257,  209,  187,  260,  212,  190,
 /*   110 */   191,  192,  193,  194,  195,  196,  197,  198,  199,  200,
 /*   120 */   201,  202,  203,  204,  205,  206,  207,  208,   22,   23,
 /*   130 */   105,  131,  110,  111,  112,  113,  114,  115,  116,    7,
 /*   140 */   140,  141,  142,  118,  119,  120,  121,  122,  123,  124,
 /*   150 */   125,  131,  235,  216,  237,  238,  239,  240,  241,  131,
 /*   160 */   135,  244,  137,   73,  247,  228,  249,  230,  143,  146,
 /*   170 */   145,  148,  149,  150,  151,  152,  157,  131,  153,  160,
 /*   180 */   284,  156,  286,  279,  102,  281,  161,  105,  106,  164,
 /*   190 */   111,  112,  113,  114,  115,  116,  168,  169,  170,  171,
 /*   200 */   172,  173,  174,  175,  176,  177,  178,  179,  180,  181,
 /*   210 */   182,    1,    2,    3,  105,  165,  253,    7,  168,  169,
 /*   220 */   170,  171,  172,  173,  174,  175,  176,  177,  178,  179,
 /*   230 */   180,  181,  182,  144,  209,  272,  147,  212,  275,   23,
 /*   240 */   131,    7,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   250 */    34,   35,   36,   37,   38,   39,   23,  294,   69,   26,
 /*   260 */    27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
 /*   270 */    37,   38,   39,  251,   66,   67,  254,  105,  256,   71,
 /*   280 */   258,    0,    1,  261,  105,  263,  185,  265,    7,  267,
 /*   290 */   189,    7,  105,  271,  274,  273,  276,  277,  278,  120,
 /*   300 */   121,   91,    7,  131,   41,   42,   43,  120,  121,  284,
 /*   310 */   288,  286,  290,   97,  120,  121,    7,  131,  105,  132,
 /*   320 */   120,  121,  276,  277,  278,   41,   42,   43,   65,  105,
 /*   330 */   251,  120,  121,  254,   25,  256,    7,  258,   12,   13,
 /*   340 */   261,   78,  263,   71,  265,  105,  267,  120,  121,   65,
 /*   350 */   271,    7,  273,  107,  108,  109,  132,   41,   42,   43,
 /*   360 */    76,   98,  183,  184,   75,  186,   77,  288,  259,  290,
 /*   370 */   183,  184,    4,  186,   65,    7,  272,  183,  184,  275,
 /*   380 */   186,   65,   98,  183,  184,   90,  186,  136,  209,   21,
 /*   390 */   139,  212,   76,   98,  183,  184,  209,  186,  294,  212,
 /*   400 */   210,  105,  293,  209,  214,  131,  212,   98,  222,  209,
 /*   410 */   183,  184,  212,  186,   98,   86,  120,  121,   93,  105,
 /*   420 */   209,  242,  243,  212,  245,  246,  213,   98,  105,  242,
 /*   430 */   243,  259,  245,  246,  217,   84,  209,  243,   91,  212,
 /*   440 */   246,  224,  248,  226,  250,  131,  246,  219,  248,  252,
 /*   450 */   250,  223,  255,  242,  131,   82,  245,  246,  162,  163,
 /*   460 */   232,  233,  166,  167,  236,  293,   98,  131,  105,  242,
 /*   470 */     7,  266,  245,  246,  269,  210,  211,  291,  292,  214,
 /*   480 */   215,  216,  242,  218,  121,  245,  221,  105,  105,  126,
 /*   490 */   127,  294,  129,  228,    7,  230,  222,   10,  131,  294,
 /*   500 */   105,   14,  225,   40,  227,  209,  293,   20,  212,  232,
 /*   510 */   233,   24,  108,  236,  131,  120,  121,  154,  155,   92,
 /*   520 */   104,  158,  159,  105,  216,  217,  280,  160,  282,  283,
 /*   530 */   105,  285,  224,  287,  226,  289,  228,   66,  230,  121,
 /*   540 */    16,   17,   18,   19,  126,  127,    7,  129,   12,   13,
 /*   550 */   219,  220,   65,  105,  223,    7,  131,  162,  222,    7,
 /*   560 */    97,  166,  167,  232,  233,  291,  292,  236,   15,  131,
 /*   570 */     7,  229,  154,  231,  232,  233,  158,  159,  236,  131,
 /*   580 */    11,   94,  268,  105,  270,   98,  148,  149,  150,  151,
 /*   590 */   152,    7,   40,  252,  253,  213,  255,  105,  105,  105,
 /*   600 */   105,  220,    7,  105,  209,  105,    7,  212,  138,  131,
 /*   610 */   140,  141,  142,  232,  233,    7,  293,  236,  220,   80,
 /*   620 */   105,   97,   23,  131,  131,  131,  131,  291,  292,  131,
 /*   630 */   232,  233,  105,   97,  236,  294,  105,   98,  213,  105,
 /*   640 */   105,   16,   17,   18,   19,  131,  131,  133,  134,   97,
 /*   650 */   217,   23,  130,  270,    7,  133,  134,  224,  131,  226,
 /*   660 */    97,  213,  131,   87,   88,  131,  131,   44,   45,   46,
 /*   670 */    22,   23,    7,   97,   69,  293,   71,    7,    7,  105,
 /*   680 */   131,   97,  105,  105,  262,  105,  264,  283,  131,  285,
 /*   690 */   105,  213,   97,  105,  105,  279,   97,  281,  105,  105,
 /*   700 */   280,  105,  282,  105,    8,   97,  213,  213,  213,  132,
 /*   710 */   132,  213,  132,  131,  105,   87,   88,  132,  293,  105,
 /*   720 */   132,  132,  105,  105,  105,  132,  132,  105,  132,  105,
 /*   730 */   132,  105,  105,   23,  105,  292,  105,  105,  105,  105,
 /*   740 */     5,  293,  105,  105,   97,   97,  132,  105,  105,  132,
 /*   750 */   132,  132,    6,    9,  132,  105,  132,    9,  132,  132,
 /*   760 */     6,  132,   97,  132,  132,  132,  132,   97,   97,  132,
 /*   770 */   132,  293,  128,    6,  132,  132,    6,    9,    9,    6,
 /*   780 */     9,    6,  132,    6,    6,  293,  293,  293,  293,    6,
 /*   790 */     6,  293,    6,   97,    6,    6,    6,    6,    6,    6,
 /*   800 */     6,    6,   97,   23,  295,    9,    9,    9,  293,    9,
 /*   810 */     9,    9,    9,    9,  295,    9,    9,    9,    9,    9,
 /*   820 */   293,    9,    9,    9,  293,    9,    9,  293,  293,    9,
 /*   830 */     9,    6,    6,    6,    6,    6,    6,    6,    6,    6,
 /*   840 */     6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
 /*   850 */     6,    6,  295,  295,  295,    9,    9,    9,    9,    9,
 /*   860 */     9,    9,  295,  295,  295,    9,    9,    9,    9,    9,
 /*   870 */     9,    9,  295,  295,    6,    9,    9,    6,    9,    9,
 /*   880 */     8,    6,  295,    6,    6,    9,    6,    6,    9,  295,
 /*   890 */   295,    9,    6,    9,    9,    6,    9,    9,    6,
};
#define YY_SHIFT_USE_DFLT (899)
#define YY_SHIFT_COUNT    (262)
#define YY_SHIFT_MIN      (-70)
#define YY_SHIFT_MAX      (892)
static const short yy_shift_ofst[] = {
 /*     0 */   210,  463,  487,   16,  487,  -35,  -35,  563,   52,  284,
 /*    10 */   284,  263,  263,  316,  316,  309,  368,  -19,  208,  -11,
 /*    20 */   309,  368,  289,  -26,  605,  584,  132,  595,  -26,  -70,
 /*    30 */   -41,  295,  329,  552,  552,  539,  599,  599,  599,  608,
 /*    40 */   595,  608,  608,  608,  608,  608,  608,  608,  647,   90,
 /*    50 */    90,  234,  295,  329,  539,  281,  608,  608,  608,  608,
 /*    60 */   608,  608,  608,    4,  608,  665,   16,   16,  189,  272,
 /*    70 */   189,  344,  325,  347,  623,  670,   16,   16,   16,   16,
 /*    80 */    16,  351,   16,  373,   16,  427,   16,   16,   16,   16,
 /*    90 */    16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
 /*   100 */    16,   16,   16,   16,   16,  471,  548,   16,   16,  553,
 /*   110 */    16,  569,   15,  671,  671,  671,   16,   16,   16,   16,
 /*   120 */    16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
 /*   130 */    16,   16,   16,   16,   16,  710,   16,   16,   16,   16,
 /*   140 */    16,   16,   16,   16,   16,  735,   16,   16,  216,  233,
 /*   150 */   524,  625,  576,  628,  648,  536,  106,  696,  326,  746,
 /*   160 */   744,  748,  754,  767,  768,  770,  769,  773,  771,  775,
 /*   170 */   777,  778,  783,  784,  786,  788,  789,  790,  791,  792,
 /*   180 */   793,  794,  795,  796,  797,  798,  800,  801,  802,  806,
 /*   190 */   807,  808,  809,  810,  812,  816,  817,  825,  820,  826,
 /*   200 */   821,  705,  827,  803,  780,  705,  828,  829,  830,  831,
 /*   210 */   832,  833,  834,  835,  836,  837,  838,  839,  840,  841,
 /*   220 */   842,  843,  844,  845,  804,  813,  814,  846,  847,  848,
 /*   230 */   849,  850,  851,  852,  856,  857,  858,  859,  860,  861,
 /*   240 */   862,  866,  867,  868,  871,  869,  875,  870,  872,  876,
 /*   250 */   877,  878,  880,  881,  879,  882,  884,  885,  886,  889,
 /*   260 */   887,  888,  892,
};
#define YY_REDUCE_USE_DFLT (-242)
#define YY_REDUCE_COUNT (147)
#define YY_REDUCE_MIN   (-241)
#define YY_REDUCE_MAX   (650)
static const short yy_reduce_ofst[] = {
 /*     0 */   -96, -105, -104,  -81,   25,   22,   79,   28,   50,  187,
 /*    10 */   179,  194,  200,  211,  227,  296,  363,  -83,  265,  246,
 /*    20 */   395,  418, -204,  331,  308,  438,   23,   20,  228,  342,
 /*    30 */   277,  -37, -241,  109,  172,  341,  186,  274,  336,  425,
 /*    40 */    46,  314,  448,  478,  493,  494,  495,  498,    0,  381,
 /*    50 */   398,  470,  104,  205,  197,   82,  323,  383,  492,  515,
 /*    60 */   527,  531,  534,  240,  535,  514,  213,  382,  217,  -63,
 /*    70 */   433,  522,  404,  416,  101,  367,  224,  577,  578,  580,
 /*    80 */   585,  422,  588, -153,  589,  420,  593,  594,  596,  598,
 /*    90 */   614,  617,  618,  619,  622,  624,  626,  627,  629,  631,
 /*   100 */   632,  633,  634,  637,  638,  190,   19,  642,  643,   89,
 /*   110 */   650,  251,  500,  549,  557,  582,  500,  500,  574,  609,
 /*   120 */   500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
 /*   130 */   500,  500,  500,  500,  500,  443,  500,  500,  500,  500,
 /*   140 */   500,  500,  500,  500,  500,  644,  500,  500,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*    10 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*    20 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*    30 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*    40 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*    50 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*    60 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1105, 1248,
 /*    70 */  1103, 1248, 1248, 1248, 1070, 1248, 1213, 1211,  980, 1190,
 /*    80 */  1182, 1178, 1174, 1170, 1166, 1248, 1220, 1110, 1108, 1112,
 /*    90 */  1124, 1122, 1126, 1117, 1115, 1131, 1160, 1153, 1151, 1147,
 /*   100 */  1155, 1098, 1096, 1134, 1119, 1248, 1248, 1016, 1030, 1248,
 /*   110 */  1023, 1248, 1248, 1248, 1248, 1248, 1214, 1212, 1227, 1225,
 /*   120 */   981, 1191, 1183, 1175, 1167, 1221, 1111, 1109, 1113, 1125,
 /*   130 */  1123, 1127, 1118, 1116, 1132, 1230, 1161, 1154, 1152, 1148,
 /*   140 */  1099, 1097, 1135, 1120, 1017, 1248, 1031, 1024, 1248, 1248,
 /*   150 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   160 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   170 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   180 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   190 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   200 */  1248, 1248, 1248, 1248, 1248, 1247, 1248, 1248, 1248, 1248,
 /*   210 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   220 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   230 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   240 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   250 */  1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,
 /*   260 */  1248, 1248, 1248,
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
  "$",             "HTML_END_OF_FILE",  "TAG_DOCTYPE_HTSQL_DTD",  "TAG_DOCTYPE_HTML",
  "TAG_TREE_OPEN",  "TAG_TREE_BLOCK_CLOSE",  "PROPERTYDATA",  "SPACE",       
  "PROP_TREE_NAME",  "ASSIGMENT",     "TAG_DATALIST_OPEN",  "TAG_DATALIST_BLOCK_CLOSE",
  "PROP_DATALIST_DATALIST_NAME",  "PROP_DATALIST_CONNECTION_NAME",  "TAG_CONNECTION_OPEN",  "TAG_CONNECTION_BLOCK_CLOSE",
  "PROP_CONNECTION_CONNECTION_NAME",  "PROP_CONNECTION_USER_NAME",  "PROP_CONNECTION_USER_PASSWORD",  "PROP_CONNECTION_INSTANCE_NAME",
  "TAG_CONTROLBLOCK_OPEN",  "TAG_CONTROLBLOCK_CLOSE",  "PROP_CONTROLBLOCK_BLOCK_NAME",  "PROPERTYID",  
  "TAG_DATABLOCK_OPEN",  "TAG_DATABLOCK_BLOCK_CLOSE",  "PROP_BLOCK_JOIN_CONDITION",  "PROP_BLOCK_CONNECTION_NAME",
  "PROP_BLOCK_AUTO_GENERATED_COLUMNS",  "PROP_BLOCK_RECORD_COUNT",  "PROP_BLOCK_DATA_SOURCE_NAME",  "PROP_BLOCK_DATA_SCHEMA_NAME",
  "PROP_BLOCK_BLOCK_NAME",  "PROP_BLOCK_KEY_COLUMN_NAME",  "PROP_BLOCK_MASTER_BLOCK_NAME",  "PROP_BLOCK_INSERT_ALLOWED",
  "PROP_BLOCK_DELETE_ALLOWED",  "PROP_BLOCK_UPDATE_ALLOWED",  "PROP_BLOCK_WHERE_CLAUSE",  "PROP_BLOCK_OREDERBY_CLAUSE",
  "TAG_SHORT_CLOSE",  "TAG_INPUT_OPEN",  "TAG_SELECT_OPEN",  "TAG_TEXTAREA_OPEN",
  "TAG_INPUT_BLOCK_CLOSE",  "TAG_SELECT_BLOCK_CLOSE",  "TAG_TEXTAREA_BLOCK_CLOSE",  "PROP_INPUT_CHECKED_VALUE",
  "PROP_INPUT_UNCHECKED_VALUE",  "PROP_INPUT_NAME",  "PROP_INPUT_SEQUENCE_NAME",  "PROP_INPUT_SEQUENCE_SCHEMA_NAME",
  "PROP_INPUT_MASTER_ITEM_NAME",  "PROP_INPUT_TYPE",  "PROP_INPUT_VALUE",  "PROP_INPUT_DEFAULT_VALUE",
  "PROP_INPUT_COLUMN_NAME",  "PROP_INPUT_FORMAT_MASK",  "PROP_INPUT_DATA_TYPE",  "PROP_INPUT_MAX_LENGTH",
  "PROP_INPUT_INSERT_ALLOWED",  "PROP_INPUT_UPDATE_ALLOWED",  "PROP_INPUT_DATALIST_NAME",  "PROP_INPUT_LOOKUP_ITEM_NAME",
  "PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME",  "TAG_TABLE_OPEN",  "TAG_TABLE_BLOCK_CLOSE",  "TAG_THEAD_OPEN",
  "TAG_THEAD_BLOCK_CLOSE",  "TAG_TFOOT_OPEN",  "TAG_TFOOT_BLOCK_CLOSE",  "TAG_TBODY_OPEN",
  "TAG_TBODY_BLOCK_CLOSE",  "TAG_TR_OPEN",   "TAG_TR_BLOCK_CLOSE",  "TAG_TD_OPEN", 
  "TAG_TD_BLOCK_CLOSE",  "TAG_TH_OPEN",   "TAG_TH_BLOCK_CLOSE",  "TAG_TITLE_OPEN",
  "TAG_TITLE_BLOCK_CLOSE",  "TAG_LINK_OPEN",  "TAG_LINK_BLOCK_CLOSE",  "TAG_META_OPEN",
  "TAG_META_BLOCK_CLOSE",  "TAG_STYLE_OPEN",  "TAG_STYLE_BLOCK_CLOSE",  "PROPERTYID_SCRIPT_SRC",
  "PROPERTYID_SCRIPT_TYPE",  "TAG_SCRIPT_OPEN",  "TAG_SCRIPT_BLOCK_CLOSE",  "TAG_HTML_OPEN",
  "TAG_HTML_BLOCK_CLOSE",  "TAG_BODY_OPEN",  "TAG_BODY_BLOCK_CLOSE",  "TAG_HEAD_OPEN",
  "TAG_HEAD_BLOCK_CLOSE",  "TAG_CLOSE",     "HTMLTEXT",      "error",       
  "start",         "expressions",   "expression",    "tagdoctype",  
  "taghtml",       "space",         "endoffile",     "taghtmlcontents",
  "tagbody",       "taghead",       "tagheadcontents",  "tagheadcontent",
  "tagtitle",      "tagscript",     "tagstyle",      "taglink",     
  "tagmeta",       "tagbodycontents",  "tagbodycontent",  "htsqls",      
  "tagtable",      "htmltext",      "tagconnection",  "tagdatablock",
  "tagcontrolblock",  "tagdatalist",   "tagtree",       "tagtreefullopen",
  "tagtreeblockclosefull",  "tagtreeopen",   "tagtreeproperties",  "tagclosechar",
  "spaces",        "tagtreeproperty",  "tagtreepropertyid",  "tagdatalistfullopen",
  "tagdatalistblockclosefull",  "tagdatalistopen",  "datalistproperties",  "tagdatalistblockclose",
  "datalistproperty",  "tagdatalistpropertyid",  "tagdatalistpropertyconnectionname",  "tagconnectionfullopen",
  "tagconnectionblockclosefull",  "tagconnectionopen",  "connectionproperties",  "tagconnectionblockclose",
  "connectionproperty",  "connectionpropertyconnectionname",  "connectionpropertyusername",  "connectionpropertyuserpassword",
  "connectionpropertyinstancename",  "tagcontrolblockfullopen",  "tagcontrolblockclosefull",  "tagcontrolblockcontents",
  "tagcontrolblockopen",  "tagcontrolblockproperties",  "tagcontrolblockblockclose",  "tagcontrolblockcontent",
  "tagcontrolblockproperty",  "tagdatablockfullopen",  "tagdatablockblockclosefull",  "tagdatablockcontents",
  "tagdatablockopen",  "tagdatablockproperties",  "tagdatablockblockclose",  "tagdatablockcontent",
  "tagdatablockproperty",  "tagdatablockpropertyjoincondition",  "tagdatablockpropertyconnectionname",  "tagdatablockpropertyautogeneratedcolumns",
  "tagdatablockpropertyrecordcount",  "tagdatablockpropertysourcename",  "tagdatablockpropertyschemaname",  "tagdatablockpropertyblockname",
  "tagdatablockpropertykeycolumnname",  "tagdatablockpropertymasterblockname",  "tagdatablockpropertyinsertallowed",  "tagdatablockpropertydeleteallowed",
  "tagdatablockpropertyupdateallowed",  "tagdatablockpropertywhereclause",  "tagdatablockpropertyorderbyclause",  "taginput",    
  "taginputfullopen",  "taginputblockclosefull",  "taginputopen",  "taginputproperties",
  "taginputshortclose",  "taginputblockclose",  "taginputproperty",  "taginputcheckedvalue",
  "taginputuncheckedvalue",  "taginputpropertyinputname",  "taginputpropertysequencename",  "taginputpropertysequenceschemaname",
  "taginputpropertymasteritemname",  "taginputpropertyinputtype",  "taginputpropertyinputvalue",  "taginputpropertydefaultvalue",
  "taginputpropertycolumnname",  "taginputpropertyformatmask",  "taginputpropertydatatype",  "taginputpropertymaxlength",
  "taginputpropertyinsertallowed",  "taginputpropertyupdateallowed",  "taginputpropertydatalistname",  "taginputpropertylookupitemname",
  "taginputpropertylookupitemblockname",  "tagtablefullopen",  "tagtableblockclosefull",  "tablecontent",
  "tagtableopen",  "tagproperties",  "tagtableblockclose",  "tagthead",    
  "tagtbody",      "tagtfoot",      "tagtheadfullopen",  "tagtheadblockclosefull",
  "tagtablerows",  "tagtheadopen",  "tagpropertieswithreturnvaluesall",  "tagtheadblockclose",
  "tagtfootfullopen",  "tagtfootblockclosefull",  "tagtfootopen",  "tagtfootblockclose",
  "tagtbodyfullopen",  "tagtbodyblockclosefull",  "tagtbodyopen",  "tagtbodyblockclose",
  "tagtablerow",   "tagtablerowfullopen",  "tagtablecols",  "tagtablerowblockclosefull",
  "tagtablerowopen",  "tagtablerowblockclose",  "tagtablecol",   "tagtablecoltd",
  "tagtablecolth",  "tagtablecoltdfullopen",  "tagtablecoltdblockclosefull",  "tagtablecolcontents",
  "tagtablecoltdopen",  "tagtablecoltdblockclose",  "tagtablecolcontent",  "tagtablecolthfullopen",
  "tagtablecolthblockclosefull",  "tagtablecolthopen",  "tagtablecolthblockclose",  "tagtitlefullopen",
  "tagtitleblockclosefull",  "htmlandspaces",  "tagtitleopen",  "tagtitleblockclose",
  "taglinkfullopen",  "taglinkblockclosefull",  "taglinkopen",   "tagshortclose",
  "taglinkblockclose",  "tagmetafullopen",  "tagmetablockclosefull",  "tagmetaopen", 
  "tagmetablockclose",  "tagstylefullopen",  "tagstyleblockclosefull",  "tagstyleopen",
  "tagstyleproperties",  "tagstyleblockclose",  "tagstyleproperty",  "tagscriptfullopen",
  "tagscriptblockclosefull",  "tagscriptopen",  "tagscriptproperties",  "tagscriptblockclose",
  "tagscriptproperty",  "tagscriptpropertyscripttype",  "tagscriptpropertysrc",  "taghtmlfullopen",
  "taghtmlblockclosefull",  "taghtmlopen",   "taghtmlblockclose",  "tagbodyfullopen",
  "tagbodyblockclosefull",  "tagbodyopen",   "tagbodyblockclose",  "tagheadfullopen",
  "tagheadblockclosefull",  "tagheadopen",   "tagheadblockclose",  "tagpropertieswithreturnvalues",
  "tagpropertywithreturnvalue",  "tagproperty",   "htmlandspace",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD",
 /*   1 */ "tagdoctype ::= TAG_DOCTYPE_HTML",
 /*   2 */ "tagtreeopen ::= TAG_TREE_OPEN",
 /*   3 */ "tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE",
 /*   4 */ "tagdatalistopen ::= TAG_DATALIST_OPEN",
 /*   5 */ "tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE",
 /*   6 */ "datalistproperty ::= tagdatalistpropertyid PROPERTYDATA",
 /*   7 */ "datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA",
 /*   8 */ "tagconnection ::= tagconnectionfullopen tagconnectionblockclosefull",
 /*   9 */ "tagconnectionopen ::= TAG_CONNECTION_OPEN",
 /*  10 */ "tagconnectionblockclose ::= TAG_CONNECTION_BLOCK_CLOSE",
 /*  11 */ "connectionproperty ::= connectionpropertyconnectionname PROPERTYDATA",
 /*  12 */ "connectionproperty ::= connectionpropertyusername PROPERTYDATA",
 /*  13 */ "connectionpropertyusername ::= SPACE PROP_CONNECTION_USER_NAME ASSIGMENT",
 /*  14 */ "connectionproperty ::= connectionpropertyuserpassword PROPERTYDATA",
 /*  15 */ "connectionpropertyuserpassword ::= SPACE PROP_CONNECTION_USER_PASSWORD ASSIGMENT",
 /*  16 */ "connectionproperty ::= connectionpropertyinstancename PROPERTYDATA",
 /*  17 */ "tagcontrolblockproperty ::= SPACE PROP_CONTROLBLOCK_BLOCK_NAME ASSIGMENT PROPERTYDATA",
 /*  18 */ "tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar",
 /*  19 */ "tagdatablockopen ::= TAG_DATABLOCK_OPEN",
 /*  20 */ "tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE",
 /*  21 */ "tagdatablockproperty ::= tagdatablockpropertyjoincondition PROPERTYDATA",
 /*  22 */ "tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION ASSIGMENT",
 /*  23 */ "tagdatablockproperty ::= tagdatablockpropertyconnectionname PROPERTYDATA",
 /*  24 */ "tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME ASSIGMENT",
 /*  25 */ "tagdatablockproperty ::= tagdatablockpropertyautogeneratedcolumns PROPERTYDATA",
 /*  26 */ "tagdatablockproperty ::= tagdatablockpropertyrecordcount PROPERTYDATA",
 /*  27 */ "tagdatablockproperty ::= tagdatablockpropertysourcename PROPERTYDATA",
 /*  28 */ "tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT",
 /*  29 */ "tagdatablockproperty ::= tagdatablockpropertyschemaname PROPERTYDATA",
 /*  30 */ "tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT",
 /*  31 */ "tagdatablockproperty ::= tagdatablockpropertyblockname PROPERTYDATA",
 /*  32 */ "tagdatablockproperty ::= tagdatablockpropertykeycolumnname PROPERTYDATA",
 /*  33 */ "tagdatablockproperty ::= tagdatablockpropertymasterblockname PROPERTYDATA",
 /*  34 */ "tagdatablockproperty ::= tagdatablockpropertyinsertallowed PROPERTYDATA",
 /*  35 */ "tagdatablockproperty ::= tagdatablockpropertydeleteallowed PROPERTYDATA",
 /*  36 */ "tagdatablockproperty ::= tagdatablockpropertyupdateallowed PROPERTYDATA",
 /*  37 */ "tagdatablockproperty ::= tagdatablockpropertywhereclause PROPERTYDATA",
 /*  38 */ "tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE ASSIGMENT",
 /*  39 */ "tagdatablockproperty ::= tagdatablockpropertyorderbyclause PROPERTYDATA",
 /*  40 */ "tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT",
 /*  41 */ "taginputshortclose ::= TAG_SHORT_CLOSE",
 /*  42 */ "taginputopen ::= TAG_INPUT_OPEN",
 /*  43 */ "taginputopen ::= TAG_SELECT_OPEN",
 /*  44 */ "taginputopen ::= TAG_TEXTAREA_OPEN",
 /*  45 */ "taginputblockclosefull ::= taginputblockclose",
 /*  46 */ "taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE",
 /*  47 */ "taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE",
 /*  48 */ "taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE",
 /*  49 */ "taginputproperty ::= taginputcheckedvalue PROPERTYDATA",
 /*  50 */ "taginputproperty ::= taginputuncheckedvalue PROPERTYDATA",
 /*  51 */ "taginputproperty ::= taginputpropertyinputname PROPERTYDATA",
 /*  52 */ "taginputproperty ::= taginputpropertysequencename PROPERTYDATA",
 /*  53 */ "taginputproperty ::= taginputpropertysequenceschemaname PROPERTYDATA",
 /*  54 */ "taginputproperty ::= taginputpropertymasteritemname PROPERTYDATA",
 /*  55 */ "taginputproperty ::= taginputpropertyinputtype PROPERTYDATA",
 /*  56 */ "taginputproperty ::= taginputpropertyinputvalue PROPERTYDATA",
 /*  57 */ "taginputproperty ::= taginputpropertydefaultvalue PROPERTYDATA",
 /*  58 */ "taginputproperty ::= taginputpropertycolumnname PROPERTYDATA",
 /*  59 */ "taginputproperty ::= taginputpropertyformatmask PROPERTYDATA",
 /*  60 */ "taginputproperty ::= taginputpropertydatatype PROPERTYDATA",
 /*  61 */ "taginputproperty ::= taginputpropertymaxlength PROPERTYDATA",
 /*  62 */ "taginputproperty ::= taginputpropertyinsertallowed PROPERTYDATA",
 /*  63 */ "taginputproperty ::= taginputpropertyupdateallowed PROPERTYDATA",
 /*  64 */ "taginputproperty ::= taginputpropertydatalistname PROPERTYDATA",
 /*  65 */ "taginputproperty ::= taginputpropertylookupitemname PROPERTYDATA",
 /*  66 */ "taginputproperty ::= taginputpropertylookupitemblockname PROPERTYDATA",
 /*  67 */ "taginputproperty ::= spaces PROPERTYID ASSIGMENT PROPERTYDATA",
 /*  68 */ "tagtableopen ::= TAG_TABLE_OPEN",
 /*  69 */ "tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE",
 /*  70 */ "tagtheadopen ::= TAG_THEAD_OPEN",
 /*  71 */ "tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE",
 /*  72 */ "tagtfootopen ::= TAG_TFOOT_OPEN",
 /*  73 */ "tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE",
 /*  74 */ "tagtbodyopen ::= TAG_TBODY_OPEN",
 /*  75 */ "tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE",
 /*  76 */ "tagtablerowopen ::= TAG_TR_OPEN",
 /*  77 */ "tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE",
 /*  78 */ "tagtablecoltdopen ::= TAG_TD_OPEN",
 /*  79 */ "tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE",
 /*  80 */ "tagtablecolthopen ::= TAG_TH_OPEN",
 /*  81 */ "tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE",
 /*  82 */ "tagscriptblockclosefull ::= tagscriptblockclose",
 /*  83 */ "tagscriptblockclosefull ::= tagscriptblockclose spaces",
 /*  84 */ "tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA",
 /*  85 */ "tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA",
 /*  86 */ "taghtmlopen ::= TAG_HTML_OPEN",
 /*  87 */ "tagbodyfullopen ::= tagbodyopen tagclosechar",
 /*  88 */ "tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE",
 /*  89 */ "tagheadfullopen ::= tagheadopen",
 /*  90 */ "start ::= expressions",
 /*  91 */ "expressions ::= expressions expression",
 /*  92 */ "expressions ::= expression",
 /*  93 */ "expressions ::= tagdoctype taghtml",
 /*  94 */ "expressions ::= taghtml",
 /*  95 */ "expression ::= space",
 /*  96 */ "expression ::= endoffile",
 /*  97 */ "endoffile ::= HTML_END_OF_FILE",
 /*  98 */ "taghtmlcontents ::= tagbody",
 /*  99 */ "taghtmlcontents ::= taghead tagbody",
 /* 100 */ "tagheadcontents ::= tagheadcontents tagheadcontent",
 /* 101 */ "tagheadcontents ::= tagheadcontent",
 /* 102 */ "tagheadcontent ::= tagtitle",
 /* 103 */ "tagheadcontent ::= tagscript",
 /* 104 */ "tagheadcontent ::= tagstyle",
 /* 105 */ "tagheadcontent ::= taglink",
 /* 106 */ "tagheadcontent ::= tagmeta",
 /* 107 */ "tagbodycontents ::= tagbodycontents tagbodycontent",
 /* 108 */ "tagbodycontents ::= tagbodycontent",
 /* 109 */ "tagbodycontent ::= htsqls",
 /* 110 */ "tagbodycontent ::= tagtable",
 /* 111 */ "tagbodycontent ::= space",
 /* 112 */ "tagbodycontent ::= htmltext",
 /* 113 */ "htsqls ::= tagconnection",
 /* 114 */ "htsqls ::= tagdatablock",
 /* 115 */ "htsqls ::= tagcontrolblock",
 /* 116 */ "htsqls ::= tagdatalist",
 /* 117 */ "tagtree ::= tagtreefullopen tagtreeblockclosefull",
 /* 118 */ "tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar",
 /* 119 */ "tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces",
 /* 120 */ "tagtreeproperties ::= tagtreeproperties tagtreeproperty",
 /* 121 */ "tagtreeproperties ::= tagtreeproperty",
 /* 122 */ "tagtreeproperty ::= tagtreepropertyid PROPERTYDATA",
 /* 123 */ "tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT",
 /* 124 */ "tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull",
 /* 125 */ "tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar",
 /* 126 */ "tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces",
 /* 127 */ "tagdatalistblockclosefull ::= tagdatalistblockclose",
 /* 128 */ "datalistproperties ::= datalistproperties datalistproperty",
 /* 129 */ "datalistproperties ::= datalistproperty",
 /* 130 */ "tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT",
 /* 131 */ "tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT",
 /* 132 */ "tagconnectionfullopen ::= tagconnectionopen connectionproperties tagclosechar",
 /* 133 */ "tagconnectionfullopen ::= tagconnectionopen connectionproperties tagclosechar spaces",
 /* 134 */ "tagconnectionblockclosefull ::= tagconnectionblockclose",
 /* 135 */ "connectionproperties ::= connectionproperties connectionproperty",
 /* 136 */ "connectionproperties ::= connectionproperty",
 /* 137 */ "connectionpropertyconnectionname ::= SPACE PROP_CONNECTION_CONNECTION_NAME ASSIGMENT",
 /* 138 */ "connectionpropertyinstancename ::= SPACE PROP_CONNECTION_INSTANCE_NAME ASSIGMENT",
 /* 139 */ "tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull",
 /* 140 */ "tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull",
 /* 141 */ "tagcontrolblockfullopen ::= tagcontrolblockopen tagcontrolblockproperties tagclosechar",
 /* 142 */ "tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN",
 /* 143 */ "tagcontrolblockclosefull ::= tagcontrolblockblockclose",
 /* 144 */ "tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE",
 /* 145 */ "tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent",
 /* 146 */ "tagcontrolblockcontents ::= tagcontrolblockcontent",
 /* 147 */ "tagcontrolblockcontent ::= tagtree",
 /* 148 */ "tagcontrolblockcontent ::= space",
 /* 149 */ "tagcontrolblockcontent ::= htmltext",
 /* 150 */ "tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty",
 /* 151 */ "tagcontrolblockproperties ::= tagcontrolblockproperty",
 /* 152 */ "tagcontrolblockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 153 */ "tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull",
 /* 154 */ "tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull",
 /* 155 */ "tagdatablockblockclosefull ::= tagdatablockblockclose",
 /* 156 */ "tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent",
 /* 157 */ "tagdatablockcontents ::= tagdatablockcontent",
 /* 158 */ "tagdatablockcontent ::= tagtable",
 /* 159 */ "tagdatablockcontent ::= space",
 /* 160 */ "tagdatablockcontent ::= htmltext",
 /* 161 */ "tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty",
 /* 162 */ "tagdatablockproperties ::= tagdatablockproperty",
 /* 163 */ "tagdatablockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 164 */ "tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT",
 /* 165 */ "tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT",
 /* 166 */ "tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT",
 /* 167 */ "tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT",
 /* 168 */ "tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT",
 /* 169 */ "tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT",
 /* 170 */ "tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT",
 /* 171 */ "tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT",
 /* 172 */ "taginput ::= taginputfullopen",
 /* 173 */ "taginput ::= taginputfullopen taginputblockclosefull",
 /* 174 */ "taginputfullopen ::= taginputopen taginputproperties tagclosechar",
 /* 175 */ "taginputfullopen ::= taginputopen taginputproperties taginputshortclose",
 /* 176 */ "taginputproperties ::= taginputproperties taginputproperty",
 /* 177 */ "taginputproperties ::= taginputproperty",
 /* 178 */ "taginputcheckedvalue ::= spaces PROP_INPUT_CHECKED_VALUE ASSIGMENT",
 /* 179 */ "taginputuncheckedvalue ::= spaces PROP_INPUT_UNCHECKED_VALUE ASSIGMENT",
 /* 180 */ "taginputpropertyinputname ::= spaces PROP_INPUT_NAME ASSIGMENT",
 /* 181 */ "taginputpropertysequencename ::= spaces PROP_INPUT_SEQUENCE_NAME ASSIGMENT",
 /* 182 */ "taginputpropertysequenceschemaname ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT",
 /* 183 */ "taginputpropertymasteritemname ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT",
 /* 184 */ "taginputpropertyinputtype ::= spaces PROP_INPUT_TYPE ASSIGMENT",
 /* 185 */ "taginputpropertyinputvalue ::= spaces PROP_INPUT_VALUE ASSIGMENT",
 /* 186 */ "taginputpropertydefaultvalue ::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT",
 /* 187 */ "taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT",
 /* 188 */ "taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT",
 /* 189 */ "taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT",
 /* 190 */ "taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT",
 /* 191 */ "taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED ASSIGMENT",
 /* 192 */ "taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT",
 /* 193 */ "taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT",
 /* 194 */ "taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT",
 /* 195 */ "taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT",
 /* 196 */ "tagtable ::= tagtablefullopen tagtableblockclosefull",
 /* 197 */ "tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull",
 /* 198 */ "tagtablefullopen ::= tagtableopen tagclosechar",
 /* 199 */ "tagtablefullopen ::= tagtableopen tagclosechar spaces",
 /* 200 */ "tagtablefullopen ::= tagtableopen tagproperties tagclosechar",
 /* 201 */ "tagtablefullopen ::= tagtableopen tagproperties tagclosechar spaces",
 /* 202 */ "tagtableblockclosefull ::= tagtableblockclose",
 /* 203 */ "tablecontent ::= tagthead tagtbody tagtfoot",
 /* 204 */ "tablecontent ::= tagthead tagtfoot tagtbody",
 /* 205 */ "tablecontent ::= tagthead tagtbody",
 /* 206 */ "tablecontent ::= tagtbody tagtfoot",
 /* 207 */ "tablecontent ::= tagtbody",
 /* 208 */ "tagthead ::= tagtheadfullopen tagtheadblockclosefull",
 /* 209 */ "tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull",
 /* 210 */ "tagtheadfullopen ::= tagtheadopen tagclosechar",
 /* 211 */ "tagtheadfullopen ::= tagtheadopen tagclosechar spaces",
 /* 212 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 213 */ "tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces",
 /* 214 */ "tagtheadblockclosefull ::= tagtheadblockclose",
 /* 215 */ "tagtheadblockclosefull ::= tagtheadblockclose spaces",
 /* 216 */ "tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull",
 /* 217 */ "tagtfootfullopen ::= tagtfootopen tagclosechar",
 /* 218 */ "tagtfootfullopen ::= tagtfootopen tagclosechar spaces",
 /* 219 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar",
 /* 220 */ "tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar spaces",
 /* 221 */ "tagtfootblockclosefull ::= tagtfootblockclose",
 /* 222 */ "tagtfootblockclosefull ::= tagtfootblockclose spaces",
 /* 223 */ "tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull",
 /* 224 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar",
 /* 225 */ "tagtbodyfullopen ::= tagtbodyopen tagclosechar spaces",
 /* 226 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar",
 /* 227 */ "tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar spaces",
 /* 228 */ "tagtbodyblockclosefull ::= tagtbodyblockclose",
 /* 229 */ "tagtbodyblockclosefull ::= tagtbodyblockclose spaces",
 /* 230 */ "tagtablerows ::= tagtablerows tagtablerow",
 /* 231 */ "tagtablerows ::= tagtablerow",
 /* 232 */ "tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull",
 /* 233 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar",
 /* 234 */ "tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces",
 /* 235 */ "tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 236 */ "tagtablerowblockclosefull ::= tagtablerowblockclose",
 /* 237 */ "tagtablerowblockclosefull ::= tagtablerowblockclose spaces",
 /* 238 */ "tagtablecols ::= tagtablecols tagtablecol",
 /* 239 */ "tagtablecols ::= tagtablecol",
 /* 240 */ "tagtablecol ::= tagtablecoltd",
 /* 241 */ "tagtablecol ::= tagtablecolth",
 /* 242 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull",
 /* 243 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull",
 /* 244 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull",
 /* 245 */ "tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull",
 /* 246 */ "tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull",
 /* 247 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar",
 /* 248 */ "tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar",
 /* 249 */ "tagtablecoltdblockclosefull ::= tagtablecoltdblockclose",
 /* 250 */ "tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces",
 /* 251 */ "tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent",
 /* 252 */ "tagtablecolcontents ::= tagtablecolcontent",
 /* 253 */ "tagtablecolcontent ::= taginput",
 /* 254 */ "tagtablecolcontent ::= taginput spaces",
 /* 255 */ "tagtablecolcontent ::= htmltext",
 /* 256 */ "tagtablecolcontent ::= htmltext spaces",
 /* 257 */ "tagtablecolcontent ::= tagtable",
 /* 258 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull",
 /* 259 */ "tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull",
 /* 260 */ "tagtablecolthfullopen ::= tagtablecolthopen tagclosechar",
 /* 261 */ "tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar",
 /* 262 */ "tagtablecolthblockclosefull ::= tagtablecolthblockclose",
 /* 263 */ "tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces",
 /* 264 */ "tagtitle ::= tagtitlefullopen tagtitleblockclosefull",
 /* 265 */ "tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull",
 /* 266 */ "tagtitlefullopen ::= tagtitleopen tagclosechar",
 /* 267 */ "tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar",
 /* 268 */ "tagtitleblockclosefull ::= tagtitleblockclose",
 /* 269 */ "tagtitleblockclosefull ::= tagtitleblockclose spaces",
 /* 270 */ "tagtitleopen ::= TAG_TITLE_OPEN",
 /* 271 */ "tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE",
 /* 272 */ "taglink ::= taglinkfullopen",
 /* 273 */ "taglink ::= taglinkfullopen taglinkblockclosefull",
 /* 274 */ "taglinkfullopen ::= taglinkopen tagproperties tagclosechar",
 /* 275 */ "taglinkfullopen ::= taglinkopen tagproperties tagshortclose",
 /* 276 */ "taglinkblockclosefull ::= taglinkblockclose",
 /* 277 */ "taglinkblockclosefull ::= taglinkblockclose spaces",
 /* 278 */ "taglinkopen ::= TAG_LINK_OPEN",
 /* 279 */ "taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE",
 /* 280 */ "tagmeta ::= tagmetafullopen",
 /* 281 */ "tagmeta ::= tagmetafullopen tagmetablockclosefull",
 /* 282 */ "tagmetafullopen ::= tagmetaopen tagproperties tagclosechar",
 /* 283 */ "tagmetafullopen ::= tagmetaopen tagproperties tagshortclose",
 /* 284 */ "tagmetablockclosefull ::= tagmetablockclose",
 /* 285 */ "tagmetablockclosefull ::= tagmetablockclose spaces",
 /* 286 */ "tagmetaopen ::= TAG_META_OPEN",
 /* 287 */ "tagmetablockclose ::= TAG_META_BLOCK_CLOSE",
 /* 288 */ "tagstyle ::= tagstylefullopen tagstyleblockclosefull",
 /* 289 */ "tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull",
 /* 290 */ "tagstylefullopen ::= tagstyleopen tagclosechar",
 /* 291 */ "tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar",
 /* 292 */ "tagstyleblockclosefull ::= tagstyleblockclose",
 /* 293 */ "tagstyleblockclosefull ::= tagstyleblockclose spaces",
 /* 294 */ "tagstyleopen ::= TAG_STYLE_OPEN",
 /* 295 */ "tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE",
 /* 296 */ "tagstyleproperties ::= tagstyleproperties tagstyleproperty",
 /* 297 */ "tagstyleproperties ::= tagstyleproperty",
 /* 298 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA",
 /* 299 */ "tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA",
 /* 300 */ "tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 301 */ "tagscript ::= tagscriptfullopen tagscriptblockclosefull",
 /* 302 */ "tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull",
 /* 303 */ "tagscriptfullopen ::= tagscriptopen tagclosechar",
 /* 304 */ "tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar",
 /* 305 */ "tagscriptopen ::= TAG_SCRIPT_OPEN",
 /* 306 */ "tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE",
 /* 307 */ "tagscriptproperties ::= tagscriptproperties tagscriptproperty",
 /* 308 */ "tagscriptproperties ::= tagscriptproperty",
 /* 309 */ "tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT",
 /* 310 */ "tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT",
 /* 311 */ "taghtml ::= taghtmlfullopen taghtmlblockclosefull",
 /* 312 */ "taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull",
 /* 313 */ "taghtmlfullopen ::= taghtmlopen tagclosechar",
 /* 314 */ "taghtmlfullopen ::= taghtmlopen tagclosechar spaces",
 /* 315 */ "taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar",
 /* 316 */ "taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar spaces",
 /* 317 */ "taghtmlblockclosefull ::= taghtmlblockclose",
 /* 318 */ "taghtmlblockclose ::= TAG_HTML_BLOCK_CLOSE",
 /* 319 */ "tagbody ::= tagbodyfullopen tagbodyblockclosefull",
 /* 320 */ "tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull",
 /* 321 */ "tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar",
 /* 322 */ "tagbodyblockclosefull ::= tagbodyblockclose",
 /* 323 */ "tagbodyblockclosefull ::= tagbodyblockclose spaces",
 /* 324 */ "tagbodyopen ::= TAG_BODY_OPEN",
 /* 325 */ "taghead ::= tagheadfullopen tagheadblockclosefull",
 /* 326 */ "taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull",
 /* 327 */ "tagheadblockclosefull ::= tagheadblockclose",
 /* 328 */ "tagheadblockclosefull ::= tagheadblockclose space",
 /* 329 */ "tagheadopen ::= TAG_HEAD_OPEN",
 /* 330 */ "tagheadopen ::= TAG_HEAD_OPEN space",
 /* 331 */ "tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE",
 /* 332 */ "tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues",
 /* 333 */ "tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue",
 /* 334 */ "tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue",
 /* 335 */ "tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 336 */ "tagproperties ::= tagproperties tagproperty",
 /* 337 */ "tagproperties ::= tagproperty",
 /* 338 */ "tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA",
 /* 339 */ "tagclosechar ::= TAG_CLOSE",
 /* 340 */ "tagclosechar ::= SPACE TAG_CLOSE",
 /* 341 */ "tagshortclose ::= TAG_SHORT_CLOSE",
 /* 342 */ "htmlandspaces ::= htmlandspaces htmlandspace",
 /* 343 */ "htmlandspaces ::= htmlandspace",
 /* 344 */ "htmlandspace ::= HTMLTEXT",
 /* 345 */ "htmlandspace ::= SPACE",
 /* 346 */ "htmltext ::= HTMLTEXT",
 /* 347 */ "spaces ::= spaces space",
 /* 348 */ "spaces ::= space",
 /* 349 */ "space ::= SPACE",
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
    case 1: /* HTML_END_OF_FILE */
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
    case 14: /* TAG_CONNECTION_OPEN */
    case 15: /* TAG_CONNECTION_BLOCK_CLOSE */
    case 16: /* PROP_CONNECTION_CONNECTION_NAME */
    case 17: /* PROP_CONNECTION_USER_NAME */
    case 18: /* PROP_CONNECTION_USER_PASSWORD */
    case 19: /* PROP_CONNECTION_INSTANCE_NAME */
    case 20: /* TAG_CONTROLBLOCK_OPEN */
    case 21: /* TAG_CONTROLBLOCK_CLOSE */
    case 22: /* PROP_CONTROLBLOCK_BLOCK_NAME */
    case 23: /* PROPERTYID */
    case 24: /* TAG_DATABLOCK_OPEN */
    case 25: /* TAG_DATABLOCK_BLOCK_CLOSE */
    case 26: /* PROP_BLOCK_JOIN_CONDITION */
    case 27: /* PROP_BLOCK_CONNECTION_NAME */
    case 28: /* PROP_BLOCK_AUTO_GENERATED_COLUMNS */
    case 29: /* PROP_BLOCK_RECORD_COUNT */
    case 30: /* PROP_BLOCK_DATA_SOURCE_NAME */
    case 31: /* PROP_BLOCK_DATA_SCHEMA_NAME */
    case 32: /* PROP_BLOCK_BLOCK_NAME */
    case 33: /* PROP_BLOCK_KEY_COLUMN_NAME */
    case 34: /* PROP_BLOCK_MASTER_BLOCK_NAME */
    case 35: /* PROP_BLOCK_INSERT_ALLOWED */
    case 36: /* PROP_BLOCK_DELETE_ALLOWED */
    case 37: /* PROP_BLOCK_UPDATE_ALLOWED */
    case 38: /* PROP_BLOCK_WHERE_CLAUSE */
    case 39: /* PROP_BLOCK_OREDERBY_CLAUSE */
    case 40: /* TAG_SHORT_CLOSE */
    case 41: /* TAG_INPUT_OPEN */
    case 42: /* TAG_SELECT_OPEN */
    case 43: /* TAG_TEXTAREA_OPEN */
    case 44: /* TAG_INPUT_BLOCK_CLOSE */
    case 45: /* TAG_SELECT_BLOCK_CLOSE */
    case 46: /* TAG_TEXTAREA_BLOCK_CLOSE */
    case 47: /* PROP_INPUT_CHECKED_VALUE */
    case 48: /* PROP_INPUT_UNCHECKED_VALUE */
    case 49: /* PROP_INPUT_NAME */
    case 50: /* PROP_INPUT_SEQUENCE_NAME */
    case 51: /* PROP_INPUT_SEQUENCE_SCHEMA_NAME */
    case 52: /* PROP_INPUT_MASTER_ITEM_NAME */
    case 53: /* PROP_INPUT_TYPE */
    case 54: /* PROP_INPUT_VALUE */
    case 55: /* PROP_INPUT_DEFAULT_VALUE */
    case 56: /* PROP_INPUT_COLUMN_NAME */
    case 57: /* PROP_INPUT_FORMAT_MASK */
    case 58: /* PROP_INPUT_DATA_TYPE */
    case 59: /* PROP_INPUT_MAX_LENGTH */
    case 60: /* PROP_INPUT_INSERT_ALLOWED */
    case 61: /* PROP_INPUT_UPDATE_ALLOWED */
    case 62: /* PROP_INPUT_DATALIST_NAME */
    case 63: /* PROP_INPUT_LOOKUP_ITEM_NAME */
    case 64: /* PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME */
    case 65: /* TAG_TABLE_OPEN */
    case 66: /* TAG_TABLE_BLOCK_CLOSE */
    case 67: /* TAG_THEAD_OPEN */
    case 68: /* TAG_THEAD_BLOCK_CLOSE */
    case 69: /* TAG_TFOOT_OPEN */
    case 70: /* TAG_TFOOT_BLOCK_CLOSE */
    case 71: /* TAG_TBODY_OPEN */
    case 72: /* TAG_TBODY_BLOCK_CLOSE */
    case 73: /* TAG_TR_OPEN */
    case 74: /* TAG_TR_BLOCK_CLOSE */
    case 75: /* TAG_TD_OPEN */
    case 76: /* TAG_TD_BLOCK_CLOSE */
    case 77: /* TAG_TH_OPEN */
    case 78: /* TAG_TH_BLOCK_CLOSE */
    case 79: /* TAG_TITLE_OPEN */
    case 80: /* TAG_TITLE_BLOCK_CLOSE */
    case 81: /* TAG_LINK_OPEN */
    case 82: /* TAG_LINK_BLOCK_CLOSE */
    case 83: /* TAG_META_OPEN */
    case 84: /* TAG_META_BLOCK_CLOSE */
    case 85: /* TAG_STYLE_OPEN */
    case 86: /* TAG_STYLE_BLOCK_CLOSE */
    case 87: /* PROPERTYID_SCRIPT_SRC */
    case 88: /* PROPERTYID_SCRIPT_TYPE */
    case 89: /* TAG_SCRIPT_OPEN */
    case 90: /* TAG_SCRIPT_BLOCK_CLOSE */
    case 91: /* TAG_HTML_OPEN */
    case 92: /* TAG_HTML_BLOCK_CLOSE */
    case 93: /* TAG_BODY_OPEN */
    case 94: /* TAG_BODY_BLOCK_CLOSE */
    case 95: /* TAG_HEAD_OPEN */
    case 96: /* TAG_HEAD_BLOCK_CLOSE */
    case 97: /* TAG_CLOSE */
    case 98: /* HTMLTEXT */
{
#line 51 "lemon.html.yy"

    if ((yypminor->yy0).tokenStr != NULL) {
        printf("%s", (yypminor->yy0).tokenStr);
        mkFree(session->heapHandle, (yypminor->yy0).tokenStr);
        (yypminor->yy0).tokenStr = NULL;
    }

#line 1222 "lemon.html.c"
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
  { 103, 1 },
  { 103, 1 },
  { 129, 1 },
  { 128, 1 },
  { 137, 1 },
  { 139, 1 },
  { 140, 2 },
  { 140, 2 },
  { 122, 2 },
  { 145, 1 },
  { 147, 1 },
  { 148, 2 },
  { 148, 2 },
  { 150, 3 },
  { 148, 2 },
  { 151, 3 },
  { 148, 2 },
  { 160, 4 },
  { 161, 3 },
  { 164, 1 },
  { 166, 1 },
  { 168, 2 },
  { 169, 3 },
  { 168, 2 },
  { 170, 3 },
  { 168, 2 },
  { 168, 2 },
  { 168, 2 },
  { 173, 3 },
  { 168, 2 },
  { 174, 3 },
  { 168, 2 },
  { 168, 2 },
  { 168, 2 },
  { 168, 2 },
  { 168, 2 },
  { 168, 2 },
  { 168, 2 },
  { 181, 3 },
  { 168, 2 },
  { 182, 3 },
  { 188, 1 },
  { 186, 1 },
  { 186, 1 },
  { 186, 1 },
  { 185, 1 },
  { 189, 1 },
  { 189, 1 },
  { 189, 1 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 2 },
  { 190, 4 },
  { 212, 1 },
  { 214, 1 },
  { 221, 1 },
  { 223, 1 },
  { 226, 1 },
  { 227, 1 },
  { 230, 1 },
  { 231, 1 },
  { 236, 1 },
  { 237, 1 },
  { 244, 1 },
  { 245, 1 },
  { 249, 1 },
  { 250, 1 },
  { 272, 1 },
  { 272, 2 },
  { 276, 2 },
  { 276, 2 },
  { 281, 1 },
  { 283, 2 },
  { 286, 1 },
  { 287, 1 },
  { 100, 1 },
  { 101, 2 },
  { 101, 1 },
  { 101, 2 },
  { 101, 1 },
  { 102, 1 },
  { 102, 1 },
  { 106, 1 },
  { 107, 1 },
  { 107, 2 },
  { 110, 2 },
  { 110, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 117, 2 },
  { 117, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 126, 2 },
  { 127, 3 },
  { 127, 4 },
  { 130, 2 },
  { 130, 1 },
  { 133, 2 },
  { 134, 3 },
  { 125, 2 },
  { 135, 3 },
  { 135, 4 },
  { 136, 1 },
  { 138, 2 },
  { 138, 1 },
  { 141, 3 },
  { 142, 3 },
  { 143, 3 },
  { 143, 4 },
  { 144, 1 },
  { 146, 2 },
  { 146, 1 },
  { 149, 3 },
  { 152, 3 },
  { 124, 2 },
  { 124, 3 },
  { 153, 3 },
  { 156, 1 },
  { 154, 1 },
  { 158, 1 },
  { 155, 2 },
  { 155, 1 },
  { 159, 1 },
  { 159, 1 },
  { 159, 1 },
  { 157, 2 },
  { 157, 1 },
  { 160, 4 },
  { 123, 2 },
  { 123, 3 },
  { 162, 1 },
  { 163, 2 },
  { 163, 1 },
  { 167, 1 },
  { 167, 1 },
  { 167, 1 },
  { 165, 2 },
  { 165, 1 },
  { 168, 4 },
  { 171, 3 },
  { 172, 3 },
  { 175, 3 },
  { 176, 3 },
  { 177, 3 },
  { 178, 3 },
  { 179, 3 },
  { 180, 3 },
  { 183, 1 },
  { 183, 2 },
  { 184, 3 },
  { 184, 3 },
  { 187, 2 },
  { 187, 1 },
  { 191, 3 },
  { 192, 3 },
  { 193, 3 },
  { 194, 3 },
  { 195, 3 },
  { 196, 3 },
  { 197, 3 },
  { 198, 3 },
  { 199, 3 },
  { 200, 3 },
  { 201, 3 },
  { 202, 3 },
  { 203, 3 },
  { 204, 3 },
  { 205, 3 },
  { 206, 3 },
  { 207, 3 },
  { 208, 3 },
  { 120, 2 },
  { 120, 3 },
  { 209, 2 },
  { 209, 3 },
  { 209, 3 },
  { 209, 4 },
  { 210, 1 },
  { 211, 3 },
  { 211, 3 },
  { 211, 2 },
  { 211, 2 },
  { 211, 1 },
  { 215, 2 },
  { 215, 3 },
  { 218, 2 },
  { 218, 3 },
  { 218, 3 },
  { 218, 4 },
  { 219, 1 },
  { 219, 2 },
  { 217, 3 },
  { 224, 2 },
  { 224, 3 },
  { 224, 3 },
  { 224, 4 },
  { 225, 1 },
  { 225, 2 },
  { 216, 3 },
  { 228, 2 },
  { 228, 3 },
  { 228, 3 },
  { 228, 4 },
  { 229, 1 },
  { 229, 2 },
  { 220, 2 },
  { 220, 1 },
  { 232, 3 },
  { 233, 2 },
  { 233, 3 },
  { 233, 3 },
  { 235, 1 },
  { 235, 2 },
  { 234, 2 },
  { 234, 1 },
  { 238, 1 },
  { 238, 1 },
  { 239, 2 },
  { 239, 3 },
  { 239, 5 },
  { 239, 3 },
  { 239, 4 },
  { 241, 2 },
  { 241, 3 },
  { 242, 1 },
  { 242, 2 },
  { 243, 2 },
  { 243, 1 },
  { 246, 1 },
  { 246, 2 },
  { 246, 1 },
  { 246, 2 },
  { 246, 1 },
  { 240, 2 },
  { 240, 3 },
  { 247, 2 },
  { 247, 3 },
  { 248, 1 },
  { 248, 2 },
  { 112, 2 },
  { 112, 3 },
  { 251, 2 },
  { 251, 3 },
  { 252, 1 },
  { 252, 2 },
  { 254, 1 },
  { 255, 1 },
  { 115, 1 },
  { 115, 2 },
  { 256, 3 },
  { 256, 3 },
  { 257, 1 },
  { 257, 2 },
  { 258, 1 },
  { 260, 1 },
  { 116, 1 },
  { 116, 2 },
  { 261, 3 },
  { 261, 3 },
  { 262, 1 },
  { 262, 2 },
  { 263, 1 },
  { 264, 1 },
  { 114, 2 },
  { 114, 3 },
  { 265, 2 },
  { 265, 3 },
  { 266, 1 },
  { 266, 2 },
  { 267, 1 },
  { 269, 1 },
  { 268, 2 },
  { 268, 1 },
  { 270, 4 },
  { 270, 4 },
  { 270, 4 },
  { 113, 2 },
  { 113, 3 },
  { 271, 2 },
  { 271, 3 },
  { 273, 1 },
  { 275, 1 },
  { 274, 2 },
  { 274, 1 },
  { 277, 3 },
  { 278, 3 },
  { 104, 2 },
  { 104, 3 },
  { 279, 2 },
  { 279, 3 },
  { 279, 3 },
  { 279, 4 },
  { 280, 1 },
  { 282, 1 },
  { 108, 2 },
  { 108, 3 },
  { 283, 3 },
  { 284, 1 },
  { 284, 2 },
  { 285, 1 },
  { 109, 2 },
  { 109, 3 },
  { 288, 1 },
  { 288, 2 },
  { 289, 1 },
  { 289, 2 },
  { 290, 1 },
  { 222, 1 },
  { 291, 2 },
  { 291, 1 },
  { 292, 3 },
  { 213, 2 },
  { 213, 1 },
  { 293, 4 },
  { 131, 1 },
  { 131, 2 },
  { 259, 1 },
  { 253, 2 },
  { 253, 1 },
  { 294, 1 },
  { 294, 1 },
  { 121, 1 },
  { 132, 2 },
  { 132, 1 },
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
      case 0: /* tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD */
{  yy_destructor(yypParser,2,&yymsp[0].minor);
#line 97 "lemon.html.yy"
{
	
}
#line 1883 "lemon.html.c"
}
        break;
      case 1: /* tagdoctype ::= TAG_DOCTYPE_HTML */
{  yy_destructor(yypParser,3,&yymsp[0].minor);
#line 101 "lemon.html.yy"
{
	
}
#line 1892 "lemon.html.c"
}
        break;
      case 2: /* tagtreeopen ::= TAG_TREE_OPEN */
      case 3: /* tagtreeblockclosefull ::= TAG_TREE_BLOCK_CLOSE */ yytestcase(yyruleno==3);
      case 6: /* datalistproperty ::= tagdatalistpropertyid PROPERTYDATA */ yytestcase(yyruleno==6);
      case 7: /* datalistproperty ::= tagdatalistpropertyconnectionname PROPERTYDATA */ yytestcase(yyruleno==7);
      case 8: /* tagconnection ::= tagconnectionfullopen tagconnectionblockclosefull */ yytestcase(yyruleno==8);
      case 12: /* connectionproperty ::= connectionpropertyusername PROPERTYDATA */ yytestcase(yyruleno==12);
      case 13: /* connectionpropertyusername ::= SPACE PROP_CONNECTION_USER_NAME ASSIGMENT */ yytestcase(yyruleno==13);
      case 14: /* connectionproperty ::= connectionpropertyuserpassword PROPERTYDATA */ yytestcase(yyruleno==14);
      case 15: /* connectionpropertyuserpassword ::= SPACE PROP_CONNECTION_USER_PASSWORD ASSIGMENT */ yytestcase(yyruleno==15);
      case 17: /* tagcontrolblockproperty ::= SPACE PROP_CONTROLBLOCK_BLOCK_NAME ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==17);
      case 18: /* tagdatablockfullopen ::= tagdatablockopen tagdatablockproperties tagclosechar */ yytestcase(yyruleno==18);
      case 20: /* tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE */ yytestcase(yyruleno==20);
      case 21: /* tagdatablockproperty ::= tagdatablockpropertyjoincondition PROPERTYDATA */ yytestcase(yyruleno==21);
      case 26: /* tagdatablockproperty ::= tagdatablockpropertyrecordcount PROPERTYDATA */ yytestcase(yyruleno==26);
      case 27: /* tagdatablockproperty ::= tagdatablockpropertysourcename PROPERTYDATA */ yytestcase(yyruleno==27);
      case 32: /* tagdatablockproperty ::= tagdatablockpropertykeycolumnname PROPERTYDATA */ yytestcase(yyruleno==32);
      case 33: /* tagdatablockproperty ::= tagdatablockpropertymasterblockname PROPERTYDATA */ yytestcase(yyruleno==33);
      case 34: /* tagdatablockproperty ::= tagdatablockpropertyinsertallowed PROPERTYDATA */ yytestcase(yyruleno==34);
      case 35: /* tagdatablockproperty ::= tagdatablockpropertydeleteallowed PROPERTYDATA */ yytestcase(yyruleno==35);
      case 36: /* tagdatablockproperty ::= tagdatablockpropertyupdateallowed PROPERTYDATA */ yytestcase(yyruleno==36);
      case 37: /* tagdatablockproperty ::= tagdatablockpropertywhereclause PROPERTYDATA */ yytestcase(yyruleno==37);
      case 39: /* tagdatablockproperty ::= tagdatablockpropertyorderbyclause PROPERTYDATA */ yytestcase(yyruleno==39);
      case 42: /* taginputopen ::= TAG_INPUT_OPEN */ yytestcase(yyruleno==42);
      case 43: /* taginputopen ::= TAG_SELECT_OPEN */ yytestcase(yyruleno==43);
      case 48: /* taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE */ yytestcase(yyruleno==48);
      case 49: /* taginputproperty ::= taginputcheckedvalue PROPERTYDATA */ yytestcase(yyruleno==49);
      case 50: /* taginputproperty ::= taginputuncheckedvalue PROPERTYDATA */ yytestcase(yyruleno==50);
      case 52: /* taginputproperty ::= taginputpropertysequencename PROPERTYDATA */ yytestcase(yyruleno==52);
      case 53: /* taginputproperty ::= taginputpropertysequenceschemaname PROPERTYDATA */ yytestcase(yyruleno==53);
      case 54: /* taginputproperty ::= taginputpropertymasteritemname PROPERTYDATA */ yytestcase(yyruleno==54);
      case 55: /* taginputproperty ::= taginputpropertyinputtype PROPERTYDATA */ yytestcase(yyruleno==55);
      case 56: /* taginputproperty ::= taginputpropertyinputvalue PROPERTYDATA */ yytestcase(yyruleno==56);
      case 57: /* taginputproperty ::= taginputpropertydefaultvalue PROPERTYDATA */ yytestcase(yyruleno==57);
      case 58: /* taginputproperty ::= taginputpropertycolumnname PROPERTYDATA */ yytestcase(yyruleno==58);
      case 59: /* taginputproperty ::= taginputpropertyformatmask PROPERTYDATA */ yytestcase(yyruleno==59);
      case 60: /* taginputproperty ::= taginputpropertydatatype PROPERTYDATA */ yytestcase(yyruleno==60);
      case 61: /* taginputproperty ::= taginputpropertymaxlength PROPERTYDATA */ yytestcase(yyruleno==61);
      case 62: /* taginputproperty ::= taginputpropertyinsertallowed PROPERTYDATA */ yytestcase(yyruleno==62);
      case 63: /* taginputproperty ::= taginputpropertyupdateallowed PROPERTYDATA */ yytestcase(yyruleno==63);
      case 67: /* taginputproperty ::= spaces PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==67);
      case 76: /* tagtablerowopen ::= TAG_TR_OPEN */ yytestcase(yyruleno==76);
      case 88: /* tagbodyblockclose ::= TAG_BODY_BLOCK_CLOSE */ yytestcase(yyruleno==88);
#line 114 "lemon.html.yy"
{
    
}
#line 1941 "lemon.html.c"
        break;
      case 4: /* tagdatalistopen ::= TAG_DATALIST_OPEN */
{  yy_destructor(yypParser,10,&yymsp[0].minor);
#line 139 "lemon.html.yy"
{
    
}
#line 1949 "lemon.html.c"
}
        break;
      case 5: /* tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE */
{  yy_destructor(yypParser,11,&yymsp[0].minor);
#line 146 "lemon.html.yy"
{
    
}
#line 1958 "lemon.html.c"
}
        break;
      case 9: /* tagconnectionopen ::= TAG_CONNECTION_OPEN */
{  yy_destructor(yypParser,14,&yymsp[0].minor);
#line 178 "lemon.html.yy"
{
   
}
#line 1967 "lemon.html.c"
}
        break;
      case 10: /* tagconnectionblockclose ::= TAG_CONNECTION_BLOCK_CLOSE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 185 "lemon.html.yy"
{

}
#line 1976 "lemon.html.c"
}
        break;
      case 11: /* connectionproperty ::= connectionpropertyconnectionname PROPERTYDATA */
      case 16: /* connectionproperty ::= connectionpropertyinstancename PROPERTYDATA */ yytestcase(yyruleno==16);
      case 23: /* tagdatablockproperty ::= tagdatablockpropertyconnectionname PROPERTYDATA */ yytestcase(yyruleno==23);
      case 31: /* tagdatablockproperty ::= tagdatablockpropertyblockname PROPERTYDATA */ yytestcase(yyruleno==31);
      case 65: /* taginputproperty ::= taginputpropertylookupitemname PROPERTYDATA */ yytestcase(yyruleno==65);
#line 192 "lemon.html.yy"
{
   
}
#line 1988 "lemon.html.c"
        break;
      case 19: /* tagdatablockopen ::= TAG_DATABLOCK_OPEN */
{  yy_destructor(yypParser,24,&yymsp[0].minor);
#line 266 "lemon.html.yy"
{
    
}
#line 1996 "lemon.html.c"
}
        break;
      case 22: /* tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION ASSIGMENT */
      case 24: /* tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME ASSIGMENT */ yytestcase(yyruleno==24);
      case 38: /* tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE ASSIGMENT */ yytestcase(yyruleno==38);
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 294 "lemon.html.yy"
{

}
#line 2007 "lemon.html.c"
}
        break;
      case 25: /* tagdatablockproperty ::= tagdatablockpropertyautogeneratedcolumns PROPERTYDATA */
      case 29: /* tagdatablockproperty ::= tagdatablockpropertyschemaname PROPERTYDATA */ yytestcase(yyruleno==29);
      case 51: /* taginputproperty ::= taginputpropertyinputname PROPERTYDATA */ yytestcase(yyruleno==51);
      case 66: /* taginputproperty ::= taginputpropertylookupitemblockname PROPERTYDATA */ yytestcase(yyruleno==66);
      case 82: /* tagscriptblockclosefull ::= tagscriptblockclose */ yytestcase(yyruleno==82);
      case 83: /* tagscriptblockclosefull ::= tagscriptblockclose spaces */ yytestcase(yyruleno==83);
      case 84: /* tagscriptproperty ::= tagscriptpropertyscripttype PROPERTYDATA */ yytestcase(yyruleno==84);
      case 85: /* tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA */ yytestcase(yyruleno==85);
      case 89: /* tagheadfullopen ::= tagheadopen */ yytestcase(yyruleno==89);
#line 308 "lemon.html.yy"
{
	
}
#line 2023 "lemon.html.c"
        break;
      case 28: /* tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME ASSIGMENT */
      case 30: /* tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME ASSIGMENT */ yytestcase(yyruleno==30);
      case 40: /* tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE ASSIGMENT */ yytestcase(yyruleno==40);
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 324 "lemon.html.yy"
{
	
}
#line 2033 "lemon.html.c"
}
        break;
      case 41: /* taginputshortclose ::= TAG_SHORT_CLOSE */
{  yy_destructor(yypParser,40,&yymsp[0].minor);
#line 404 "lemon.html.yy"
{
	
}
#line 2042 "lemon.html.c"
}
        break;
      case 44: /* taginputopen ::= TAG_TEXTAREA_OPEN */
      case 46: /* taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE */ yytestcase(yyruleno==46);
      case 47: /* taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE */ yytestcase(yyruleno==47);
      case 64: /* taginputproperty ::= taginputpropertydatalistname PROPERTYDATA */ yytestcase(yyruleno==64);
      case 87: /* tagbodyfullopen ::= tagbodyopen tagclosechar */ yytestcase(yyruleno==87);
#line 417 "lemon.html.yy"
{

}
#line 2054 "lemon.html.c"
        break;
      case 45: /* taginputblockclosefull ::= taginputblockclose */
#line 421 "lemon.html.yy"
{
  
}
#line 2061 "lemon.html.c"
        break;
      case 68: /* tagtableopen ::= TAG_TABLE_OPEN */
{  yy_destructor(yypParser,65,&yymsp[0].minor);
#line 573 "lemon.html.yy"
{
    
}
#line 2069 "lemon.html.c"
}
        break;
      case 69: /* tagtableblockclose ::= TAG_TABLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,66,&yymsp[0].minor);
#line 579 "lemon.html.yy"
{
    
}
#line 2078 "lemon.html.c"
}
        break;
      case 70: /* tagtheadopen ::= TAG_THEAD_OPEN */
{  yy_destructor(yypParser,67,&yymsp[0].minor);
#line 604 "lemon.html.yy"
{
	
}
#line 2087 "lemon.html.c"
}
        break;
      case 71: /* tagtheadblockclose ::= TAG_THEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,68,&yymsp[0].minor);
#line 611 "lemon.html.yy"
{
	
}
#line 2096 "lemon.html.c"
}
        break;
      case 72: /* tagtfootopen ::= TAG_TFOOT_OPEN */
{  yy_destructor(yypParser,69,&yymsp[0].minor);
#line 626 "lemon.html.yy"
{
	
}
#line 2105 "lemon.html.c"
}
        break;
      case 73: /* tagtfootblockclose ::= TAG_TFOOT_BLOCK_CLOSE */
{  yy_destructor(yypParser,70,&yymsp[0].minor);
#line 633 "lemon.html.yy"
{
	
}
#line 2114 "lemon.html.c"
}
        break;
      case 74: /* tagtbodyopen ::= TAG_TBODY_OPEN */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 648 "lemon.html.yy"
{
	
}
#line 2123 "lemon.html.c"
}
        break;
      case 75: /* tagtbodyblockclose ::= TAG_TBODY_BLOCK_CLOSE */
{  yy_destructor(yypParser,72,&yymsp[0].minor);
#line 655 "lemon.html.yy"
{
	
}
#line 2132 "lemon.html.c"
}
        break;
      case 77: /* tagtablerowblockclose ::= TAG_TR_BLOCK_CLOSE */
{  yy_destructor(yypParser,74,&yymsp[0].minor);
#line 680 "lemon.html.yy"
{
    
}
#line 2141 "lemon.html.c"
}
        break;
      case 78: /* tagtablecoltdopen ::= TAG_TD_OPEN */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 705 "lemon.html.yy"
{
    
}
#line 2150 "lemon.html.c"
}
        break;
      case 79: /* tagtablecoltdblockclose ::= TAG_TD_BLOCK_CLOSE */
{  yy_destructor(yypParser,76,&yymsp[0].minor);
#line 712 "lemon.html.yy"
{
    
}
#line 2159 "lemon.html.c"
}
        break;
      case 80: /* tagtablecolthopen ::= TAG_TH_OPEN */
{  yy_destructor(yypParser,77,&yymsp[0].minor);
#line 736 "lemon.html.yy"
{
    
}
#line 2168 "lemon.html.c"
}
        break;
      case 81: /* tagtablecolthblockclose ::= TAG_TH_BLOCK_CLOSE */
{  yy_destructor(yypParser,78,&yymsp[0].minor);
#line 743 "lemon.html.yy"
{
    
}
#line 2177 "lemon.html.c"
}
        break;
      case 86: /* taghtmlopen ::= TAG_HTML_OPEN */
{  yy_destructor(yypParser,91,&yymsp[0].minor);
#line 868 "lemon.html.yy"
{
	
}
#line 2186 "lemon.html.c"
}
        break;
      case 97: /* endoffile ::= HTML_END_OF_FILE */
{  yy_destructor(yypParser,1,&yymsp[0].minor);
#line 69 "lemon.html.yy"
{
}
#line 2194 "lemon.html.c"
}
        break;
      case 122: /* tagtreeproperty ::= tagtreepropertyid PROPERTYDATA */
#line 126 "lemon.html.yy"
{
}
#line 2201 "lemon.html.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 123: /* tagtreepropertyid ::= SPACE PROP_TREE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 128 "lemon.html.yy"
{
}
#line 2209 "lemon.html.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 130: /* tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 156 "lemon.html.yy"
{
}
#line 2219 "lemon.html.c"
  yy_destructor(yypParser,12,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 131: /* tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 162 "lemon.html.yy"
{
}
#line 2229 "lemon.html.c"
  yy_destructor(yypParser,13,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 137: /* connectionpropertyconnectionname ::= SPACE PROP_CONNECTION_CONNECTION_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 195 "lemon.html.yy"
{
}
#line 2239 "lemon.html.c"
  yy_destructor(yypParser,16,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 138: /* connectionpropertyinstancename ::= SPACE PROP_CONNECTION_INSTANCE_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 219 "lemon.html.yy"
{
}
#line 2249 "lemon.html.c"
  yy_destructor(yypParser,19,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 142: /* tagcontrolblockopen ::= TAG_CONTROLBLOCK_OPEN */
{  yy_destructor(yypParser,20,&yymsp[0].minor);
#line 231 "lemon.html.yy"
{
}
#line 2259 "lemon.html.c"
}
        break;
      case 144: /* tagcontrolblockblockclose ::= TAG_CONTROLBLOCK_CLOSE */
{  yy_destructor(yypParser,21,&yymsp[0].minor);
#line 234 "lemon.html.yy"
{
}
#line 2267 "lemon.html.c"
}
        break;
      case 152: /* tagcontrolblockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA */
      case 163: /* tagdatablockproperty ::= SPACE PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==163);
{  yy_destructor(yypParser,7,&yymsp[-3].minor);
#line 251 "lemon.html.yy"
{
}
#line 2276 "lemon.html.c"
  yy_destructor(yypParser,23,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 164: /* tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 311 "lemon.html.yy"
{
}
#line 2287 "lemon.html.c"
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 165: /* tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 317 "lemon.html.yy"
{
}
#line 2297 "lemon.html.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 166: /* tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 341 "lemon.html.yy"
{
}
#line 2307 "lemon.html.c"
  yy_destructor(yypParser,32,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 167: /* tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 347 "lemon.html.yy"
{
}
#line 2317 "lemon.html.c"
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 168: /* tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 353 "lemon.html.yy"
{
}
#line 2327 "lemon.html.c"
  yy_destructor(yypParser,34,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 169: /* tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 359 "lemon.html.yy"
{
}
#line 2337 "lemon.html.c"
  yy_destructor(yypParser,35,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 170: /* tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 365 "lemon.html.yy"
{
}
#line 2347 "lemon.html.c"
  yy_destructor(yypParser,36,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 171: /* tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 371 "lemon.html.yy"
{
}
#line 2357 "lemon.html.c"
  yy_destructor(yypParser,37,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 178: /* taginputcheckedvalue ::= spaces PROP_INPUT_CHECKED_VALUE ASSIGMENT */
#line 449 "lemon.html.yy"
{
}
#line 2366 "lemon.html.c"
  yy_destructor(yypParser,47,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 179: /* taginputuncheckedvalue ::= spaces PROP_INPUT_UNCHECKED_VALUE ASSIGMENT */
#line 455 "lemon.html.yy"
{
}
#line 2374 "lemon.html.c"
  yy_destructor(yypParser,48,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 180: /* taginputpropertyinputname ::= spaces PROP_INPUT_NAME ASSIGMENT */
#line 461 "lemon.html.yy"
{
}
#line 2382 "lemon.html.c"
  yy_destructor(yypParser,49,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 181: /* taginputpropertysequencename ::= spaces PROP_INPUT_SEQUENCE_NAME ASSIGMENT */
#line 467 "lemon.html.yy"
{
}
#line 2390 "lemon.html.c"
  yy_destructor(yypParser,50,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 182: /* taginputpropertysequenceschemaname ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME ASSIGMENT */
#line 473 "lemon.html.yy"
{
}
#line 2398 "lemon.html.c"
  yy_destructor(yypParser,51,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 183: /* taginputpropertymasteritemname ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT */
#line 480 "lemon.html.yy"
{
}
#line 2406 "lemon.html.c"
  yy_destructor(yypParser,52,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 184: /* taginputpropertyinputtype ::= spaces PROP_INPUT_TYPE ASSIGMENT */
#line 486 "lemon.html.yy"
{
}
#line 2414 "lemon.html.c"
  yy_destructor(yypParser,53,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 185: /* taginputpropertyinputvalue ::= spaces PROP_INPUT_VALUE ASSIGMENT */
#line 492 "lemon.html.yy"
{
}
#line 2422 "lemon.html.c"
  yy_destructor(yypParser,54,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 186: /* taginputpropertydefaultvalue ::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT */
#line 499 "lemon.html.yy"
{
}
#line 2430 "lemon.html.c"
  yy_destructor(yypParser,55,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 187: /* taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT */
#line 505 "lemon.html.yy"
{
}
#line 2438 "lemon.html.c"
  yy_destructor(yypParser,56,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 188: /* taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT */
#line 511 "lemon.html.yy"
{
}
#line 2446 "lemon.html.c"
  yy_destructor(yypParser,57,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 189: /* taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT */
#line 517 "lemon.html.yy"
{
}
#line 2454 "lemon.html.c"
  yy_destructor(yypParser,58,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 190: /* taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT */
#line 523 "lemon.html.yy"
{
}
#line 2462 "lemon.html.c"
  yy_destructor(yypParser,59,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 191: /* taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED ASSIGMENT */
#line 529 "lemon.html.yy"
{
}
#line 2470 "lemon.html.c"
  yy_destructor(yypParser,60,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 192: /* taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT */
#line 535 "lemon.html.yy"
{
}
#line 2478 "lemon.html.c"
  yy_destructor(yypParser,61,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 193: /* taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT */
#line 541 "lemon.html.yy"
{
}
#line 2486 "lemon.html.c"
  yy_destructor(yypParser,62,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 194: /* taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT */
#line 547 "lemon.html.yy"
{
}
#line 2494 "lemon.html.c"
  yy_destructor(yypParser,63,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 195: /* taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT */
#line 553 "lemon.html.yy"
{
}
#line 2502 "lemon.html.c"
  yy_destructor(yypParser,64,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
        break;
      case 270: /* tagtitleopen ::= TAG_TITLE_OPEN */
{  yy_destructor(yypParser,79,&yymsp[0].minor);
#line 758 "lemon.html.yy"
{
}
#line 2511 "lemon.html.c"
}
        break;
      case 271: /* tagtitleblockclose ::= TAG_TITLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,80,&yymsp[0].minor);
#line 759 "lemon.html.yy"
{
}
#line 2519 "lemon.html.c"
}
        break;
      case 278: /* taglinkopen ::= TAG_LINK_OPEN */
{  yy_destructor(yypParser,81,&yymsp[0].minor);
#line 773 "lemon.html.yy"
{
}
#line 2527 "lemon.html.c"
}
        break;
      case 279: /* taglinkblockclose ::= TAG_LINK_BLOCK_CLOSE */
{  yy_destructor(yypParser,82,&yymsp[0].minor);
#line 774 "lemon.html.yy"
{
}
#line 2535 "lemon.html.c"
}
        break;
      case 286: /* tagmetaopen ::= TAG_META_OPEN */
{  yy_destructor(yypParser,83,&yymsp[0].minor);
#line 789 "lemon.html.yy"
{
}
#line 2543 "lemon.html.c"
}
        break;
      case 287: /* tagmetablockclose ::= TAG_META_BLOCK_CLOSE */
{  yy_destructor(yypParser,84,&yymsp[0].minor);
#line 790 "lemon.html.yy"
{
}
#line 2551 "lemon.html.c"
}
        break;
      case 294: /* tagstyleopen ::= TAG_STYLE_OPEN */
{  yy_destructor(yypParser,85,&yymsp[0].minor);
#line 805 "lemon.html.yy"
{
}
#line 2559 "lemon.html.c"
}
        break;
      case 295: /* tagstyleblockclose ::= TAG_STYLE_BLOCK_CLOSE */
{  yy_destructor(yypParser,86,&yymsp[0].minor);
#line 806 "lemon.html.yy"
{
}
#line 2567 "lemon.html.c"
}
        break;
      case 298: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA */
#line 812 "lemon.html.yy"
{
}
#line 2574 "lemon.html.c"
  yy_destructor(yypParser,87,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 299: /* tagstyleproperty ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA */
#line 813 "lemon.html.yy"
{
}
#line 2583 "lemon.html.c"
  yy_destructor(yypParser,88,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 300: /* tagstyleproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */
      case 338: /* tagproperty ::= space PROPERTYID ASSIGMENT PROPERTYDATA */ yytestcase(yyruleno==338);
#line 814 "lemon.html.yy"
{
}
#line 2593 "lemon.html.c"
  yy_destructor(yypParser,23,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
        break;
      case 305: /* tagscriptopen ::= TAG_SCRIPT_OPEN */
{  yy_destructor(yypParser,89,&yymsp[0].minor);
#line 834 "lemon.html.yy"
{
}
#line 2603 "lemon.html.c"
}
        break;
      case 306: /* tagscriptblockclose ::= TAG_SCRIPT_BLOCK_CLOSE */
{  yy_destructor(yypParser,90,&yymsp[0].minor);
#line 835 "lemon.html.yy"
{
}
#line 2611 "lemon.html.c"
}
        break;
      case 309: /* tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 846 "lemon.html.yy"
{
}
#line 2619 "lemon.html.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 310: /* tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 852 "lemon.html.yy"
{
}
#line 2629 "lemon.html.c"
  yy_destructor(yypParser,87,&yymsp[-1].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
        break;
      case 318: /* taghtmlblockclose ::= TAG_HTML_BLOCK_CLOSE */
{  yy_destructor(yypParser,92,&yymsp[0].minor);
#line 871 "lemon.html.yy"
{
}
#line 2639 "lemon.html.c"
}
        break;
      case 324: /* tagbodyopen ::= TAG_BODY_OPEN */
{  yy_destructor(yypParser,93,&yymsp[0].minor);
#line 891 "lemon.html.yy"
{
}
#line 2647 "lemon.html.c"
}
        break;
      case 329: /* tagheadopen ::= TAG_HEAD_OPEN */
{  yy_destructor(yypParser,95,&yymsp[0].minor);
#line 914 "lemon.html.yy"
{
}
#line 2655 "lemon.html.c"
}
        break;
      case 330: /* tagheadopen ::= TAG_HEAD_OPEN space */
{  yy_destructor(yypParser,95,&yymsp[-1].minor);
#line 915 "lemon.html.yy"
{
}
#line 2663 "lemon.html.c"
}
        break;
      case 331: /* tagheadblockclose ::= TAG_HEAD_BLOCK_CLOSE */
{  yy_destructor(yypParser,96,&yymsp[0].minor);
#line 917 "lemon.html.yy"
{
}
#line 2671 "lemon.html.c"
}
        break;
      case 335: /* tagpropertywithreturnvalue ::= PROPERTYID ASSIGMENT PROPERTYDATA */
{  yy_destructor(yypParser,23,&yymsp[-2].minor);
#line 931 "lemon.html.yy"
{
}
#line 2679 "lemon.html.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 339: /* tagclosechar ::= TAG_CLOSE */
{  yy_destructor(yypParser,97,&yymsp[0].minor);
#line 945 "lemon.html.yy"
{
}
#line 2689 "lemon.html.c"
}
        break;
      case 340: /* tagclosechar ::= SPACE TAG_CLOSE */
{  yy_destructor(yypParser,7,&yymsp[-1].minor);
#line 946 "lemon.html.yy"
{
}
#line 2697 "lemon.html.c"
  yy_destructor(yypParser,97,&yymsp[0].minor);
}
        break;
      case 341: /* tagshortclose ::= TAG_SHORT_CLOSE */
{  yy_destructor(yypParser,40,&yymsp[0].minor);
#line 948 "lemon.html.yy"
{
}
#line 2706 "lemon.html.c"
}
        break;
      case 344: /* htmlandspace ::= HTMLTEXT */
      case 346: /* htmltext ::= HTMLTEXT */ yytestcase(yyruleno==346);
{  yy_destructor(yypParser,98,&yymsp[0].minor);
#line 958 "lemon.html.yy"
{
}
#line 2715 "lemon.html.c"
}
        break;
      case 345: /* htmlandspace ::= SPACE */
      case 349: /* space ::= SPACE */ yytestcase(yyruleno==349);
{  yy_destructor(yypParser,7,&yymsp[0].minor);
#line 959 "lemon.html.yy"
{
}
#line 2724 "lemon.html.c"
}
        break;
      default:
      /* (90) start ::= expressions */ yytestcase(yyruleno==90);
      /* (91) expressions ::= expressions expression */ yytestcase(yyruleno==91);
      /* (92) expressions ::= expression (OPTIMIZED OUT) */ assert(yyruleno!=92);
      /* (93) expressions ::= tagdoctype taghtml */ yytestcase(yyruleno==93);
      /* (94) expressions ::= taghtml (OPTIMIZED OUT) */ assert(yyruleno!=94);
      /* (95) expression ::= space (OPTIMIZED OUT) */ assert(yyruleno!=95);
      /* (96) expression ::= endoffile (OPTIMIZED OUT) */ assert(yyruleno!=96);
      /* (98) taghtmlcontents ::= tagbody (OPTIMIZED OUT) */ assert(yyruleno!=98);
      /* (99) taghtmlcontents ::= taghead tagbody */ yytestcase(yyruleno==99);
      /* (100) tagheadcontents ::= tagheadcontents tagheadcontent */ yytestcase(yyruleno==100);
      /* (101) tagheadcontents ::= tagheadcontent (OPTIMIZED OUT) */ assert(yyruleno!=101);
      /* (102) tagheadcontent ::= tagtitle (OPTIMIZED OUT) */ assert(yyruleno!=102);
      /* (103) tagheadcontent ::= tagscript (OPTIMIZED OUT) */ assert(yyruleno!=103);
      /* (104) tagheadcontent ::= tagstyle (OPTIMIZED OUT) */ assert(yyruleno!=104);
      /* (105) tagheadcontent ::= taglink (OPTIMIZED OUT) */ assert(yyruleno!=105);
      /* (106) tagheadcontent ::= tagmeta (OPTIMIZED OUT) */ assert(yyruleno!=106);
      /* (107) tagbodycontents ::= tagbodycontents tagbodycontent */ yytestcase(yyruleno==107);
      /* (108) tagbodycontents ::= tagbodycontent (OPTIMIZED OUT) */ assert(yyruleno!=108);
      /* (109) tagbodycontent ::= htsqls (OPTIMIZED OUT) */ assert(yyruleno!=109);
      /* (110) tagbodycontent ::= tagtable (OPTIMIZED OUT) */ assert(yyruleno!=110);
      /* (111) tagbodycontent ::= space (OPTIMIZED OUT) */ assert(yyruleno!=111);
      /* (112) tagbodycontent ::= htmltext (OPTIMIZED OUT) */ assert(yyruleno!=112);
      /* (113) htsqls ::= tagconnection (OPTIMIZED OUT) */ assert(yyruleno!=113);
      /* (114) htsqls ::= tagdatablock (OPTIMIZED OUT) */ assert(yyruleno!=114);
      /* (115) htsqls ::= tagcontrolblock (OPTIMIZED OUT) */ assert(yyruleno!=115);
      /* (116) htsqls ::= tagdatalist (OPTIMIZED OUT) */ assert(yyruleno!=116);
      /* (117) tagtree ::= tagtreefullopen tagtreeblockclosefull */ yytestcase(yyruleno==117);
      /* (118) tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar */ yytestcase(yyruleno==118);
      /* (119) tagtreefullopen ::= tagtreeopen tagtreeproperties tagclosechar spaces */ yytestcase(yyruleno==119);
      /* (120) tagtreeproperties ::= tagtreeproperties tagtreeproperty */ yytestcase(yyruleno==120);
      /* (121) tagtreeproperties ::= tagtreeproperty (OPTIMIZED OUT) */ assert(yyruleno!=121);
      /* (124) tagdatalist ::= tagdatalistfullopen tagdatalistblockclosefull */ yytestcase(yyruleno==124);
      /* (125) tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar */ yytestcase(yyruleno==125);
      /* (126) tagdatalistfullopen ::= tagdatalistopen datalistproperties tagclosechar spaces */ yytestcase(yyruleno==126);
      /* (127) tagdatalistblockclosefull ::= tagdatalistblockclose (OPTIMIZED OUT) */ assert(yyruleno!=127);
      /* (128) datalistproperties ::= datalistproperties datalistproperty */ yytestcase(yyruleno==128);
      /* (129) datalistproperties ::= datalistproperty (OPTIMIZED OUT) */ assert(yyruleno!=129);
      /* (132) tagconnectionfullopen ::= tagconnectionopen connectionproperties tagclosechar */ yytestcase(yyruleno==132);
      /* (133) tagconnectionfullopen ::= tagconnectionopen connectionproperties tagclosechar spaces */ yytestcase(yyruleno==133);
      /* (134) tagconnectionblockclosefull ::= tagconnectionblockclose (OPTIMIZED OUT) */ assert(yyruleno!=134);
      /* (135) connectionproperties ::= connectionproperties connectionproperty */ yytestcase(yyruleno==135);
      /* (136) connectionproperties ::= connectionproperty (OPTIMIZED OUT) */ assert(yyruleno!=136);
      /* (139) tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockclosefull */ yytestcase(yyruleno==139);
      /* (140) tagcontrolblock ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull */ yytestcase(yyruleno==140);
      /* (141) tagcontrolblockfullopen ::= tagcontrolblockopen tagcontrolblockproperties tagclosechar */ yytestcase(yyruleno==141);
      /* (143) tagcontrolblockclosefull ::= tagcontrolblockblockclose (OPTIMIZED OUT) */ assert(yyruleno!=143);
      /* (145) tagcontrolblockcontents ::= tagcontrolblockcontents tagcontrolblockcontent */ yytestcase(yyruleno==145);
      /* (146) tagcontrolblockcontents ::= tagcontrolblockcontent (OPTIMIZED OUT) */ assert(yyruleno!=146);
      /* (147) tagcontrolblockcontent ::= tagtree (OPTIMIZED OUT) */ assert(yyruleno!=147);
      /* (148) tagcontrolblockcontent ::= space (OPTIMIZED OUT) */ assert(yyruleno!=148);
      /* (149) tagcontrolblockcontent ::= htmltext (OPTIMIZED OUT) */ assert(yyruleno!=149);
      /* (150) tagcontrolblockproperties ::= tagcontrolblockproperties tagcontrolblockproperty */ yytestcase(yyruleno==150);
      /* (151) tagcontrolblockproperties ::= tagcontrolblockproperty (OPTIMIZED OUT) */ assert(yyruleno!=151);
      /* (153) tagdatablock ::= tagdatablockfullopen tagdatablockblockclosefull */ yytestcase(yyruleno==153);
      /* (154) tagdatablock ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull */ yytestcase(yyruleno==154);
      /* (155) tagdatablockblockclosefull ::= tagdatablockblockclose (OPTIMIZED OUT) */ assert(yyruleno!=155);
      /* (156) tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent */ yytestcase(yyruleno==156);
      /* (157) tagdatablockcontents ::= tagdatablockcontent (OPTIMIZED OUT) */ assert(yyruleno!=157);
      /* (158) tagdatablockcontent ::= tagtable (OPTIMIZED OUT) */ assert(yyruleno!=158);
      /* (159) tagdatablockcontent ::= space (OPTIMIZED OUT) */ assert(yyruleno!=159);
      /* (160) tagdatablockcontent ::= htmltext (OPTIMIZED OUT) */ assert(yyruleno!=160);
      /* (161) tagdatablockproperties ::= tagdatablockproperties tagdatablockproperty */ yytestcase(yyruleno==161);
      /* (162) tagdatablockproperties ::= tagdatablockproperty (OPTIMIZED OUT) */ assert(yyruleno!=162);
      /* (172) taginput ::= taginputfullopen */ yytestcase(yyruleno==172);
      /* (173) taginput ::= taginputfullopen taginputblockclosefull */ yytestcase(yyruleno==173);
      /* (174) taginputfullopen ::= taginputopen taginputproperties tagclosechar */ yytestcase(yyruleno==174);
      /* (175) taginputfullopen ::= taginputopen taginputproperties taginputshortclose */ yytestcase(yyruleno==175);
      /* (176) taginputproperties ::= taginputproperties taginputproperty */ yytestcase(yyruleno==176);
      /* (177) taginputproperties ::= taginputproperty (OPTIMIZED OUT) */ assert(yyruleno!=177);
      /* (196) tagtable ::= tagtablefullopen tagtableblockclosefull */ yytestcase(yyruleno==196);
      /* (197) tagtable ::= tagtablefullopen tablecontent tagtableblockclosefull */ yytestcase(yyruleno==197);
      /* (198) tagtablefullopen ::= tagtableopen tagclosechar */ yytestcase(yyruleno==198);
      /* (199) tagtablefullopen ::= tagtableopen tagclosechar spaces */ yytestcase(yyruleno==199);
      /* (200) tagtablefullopen ::= tagtableopen tagproperties tagclosechar */ yytestcase(yyruleno==200);
      /* (201) tagtablefullopen ::= tagtableopen tagproperties tagclosechar spaces */ yytestcase(yyruleno==201);
      /* (202) tagtableblockclosefull ::= tagtableblockclose (OPTIMIZED OUT) */ assert(yyruleno!=202);
      /* (203) tablecontent ::= tagthead tagtbody tagtfoot */ yytestcase(yyruleno==203);
      /* (204) tablecontent ::= tagthead tagtfoot tagtbody */ yytestcase(yyruleno==204);
      /* (205) tablecontent ::= tagthead tagtbody */ yytestcase(yyruleno==205);
      /* (206) tablecontent ::= tagtbody tagtfoot */ yytestcase(yyruleno==206);
      /* (207) tablecontent ::= tagtbody */ yytestcase(yyruleno==207);
      /* (208) tagthead ::= tagtheadfullopen tagtheadblockclosefull */ yytestcase(yyruleno==208);
      /* (209) tagthead ::= tagtheadfullopen tagtablerows tagtheadblockclosefull */ yytestcase(yyruleno==209);
      /* (210) tagtheadfullopen ::= tagtheadopen tagclosechar */ yytestcase(yyruleno==210);
      /* (211) tagtheadfullopen ::= tagtheadopen tagclosechar spaces */ yytestcase(yyruleno==211);
      /* (212) tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar */ yytestcase(yyruleno==212);
      /* (213) tagtheadfullopen ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces */ yytestcase(yyruleno==213);
      /* (214) tagtheadblockclosefull ::= tagtheadblockclose */ yytestcase(yyruleno==214);
      /* (215) tagtheadblockclosefull ::= tagtheadblockclose spaces */ yytestcase(yyruleno==215);
      /* (216) tagtfoot ::= tagtfootfullopen tagtablerows tagtfootblockclosefull */ yytestcase(yyruleno==216);
      /* (217) tagtfootfullopen ::= tagtfootopen tagclosechar */ yytestcase(yyruleno==217);
      /* (218) tagtfootfullopen ::= tagtfootopen tagclosechar spaces */ yytestcase(yyruleno==218);
      /* (219) tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar */ yytestcase(yyruleno==219);
      /* (220) tagtfootfullopen ::= tagtfootopen tagproperties tagclosechar spaces */ yytestcase(yyruleno==220);
      /* (221) tagtfootblockclosefull ::= tagtfootblockclose */ yytestcase(yyruleno==221);
      /* (222) tagtfootblockclosefull ::= tagtfootblockclose spaces */ yytestcase(yyruleno==222);
      /* (223) tagtbody ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull */ yytestcase(yyruleno==223);
      /* (224) tagtbodyfullopen ::= tagtbodyopen tagclosechar */ yytestcase(yyruleno==224);
      /* (225) tagtbodyfullopen ::= tagtbodyopen tagclosechar spaces */ yytestcase(yyruleno==225);
      /* (226) tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar */ yytestcase(yyruleno==226);
      /* (227) tagtbodyfullopen ::= tagtbodyopen tagproperties tagclosechar spaces */ yytestcase(yyruleno==227);
      /* (228) tagtbodyblockclosefull ::= tagtbodyblockclose */ yytestcase(yyruleno==228);
      /* (229) tagtbodyblockclosefull ::= tagtbodyblockclose spaces */ yytestcase(yyruleno==229);
      /* (230) tagtablerows ::= tagtablerows tagtablerow */ yytestcase(yyruleno==230);
      /* (231) tagtablerows ::= tagtablerow (OPTIMIZED OUT) */ assert(yyruleno!=231);
      /* (232) tagtablerow ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull */ yytestcase(yyruleno==232);
      /* (233) tagtablerowfullopen ::= tagtablerowopen tagclosechar */ yytestcase(yyruleno==233);
      /* (234) tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces */ yytestcase(yyruleno==234);
      /* (235) tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar */ yytestcase(yyruleno==235);
      /* (236) tagtablerowblockclosefull ::= tagtablerowblockclose */ yytestcase(yyruleno==236);
      /* (237) tagtablerowblockclosefull ::= tagtablerowblockclose spaces */ yytestcase(yyruleno==237);
      /* (238) tagtablecols ::= tagtablecols tagtablecol */ yytestcase(yyruleno==238);
      /* (239) tagtablecols ::= tagtablecol (OPTIMIZED OUT) */ assert(yyruleno!=239);
      /* (240) tagtablecol ::= tagtablecoltd (OPTIMIZED OUT) */ assert(yyruleno!=240);
      /* (241) tagtablecol ::= tagtablecolth (OPTIMIZED OUT) */ assert(yyruleno!=241);
      /* (242) tagtablecoltd ::= tagtablecoltdfullopen tagtablecoltdblockclosefull */ yytestcase(yyruleno==242);
      /* (243) tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull */ yytestcase(yyruleno==243);
      /* (244) tagtablecoltd ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull */ yytestcase(yyruleno==244);
      /* (245) tagtablecoltd ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull */ yytestcase(yyruleno==245);
      /* (246) tagtablecoltd ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull */ yytestcase(yyruleno==246);
      /* (247) tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar */ yytestcase(yyruleno==247);
      /* (248) tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar */ yytestcase(yyruleno==248);
      /* (249) tagtablecoltdblockclosefull ::= tagtablecoltdblockclose */ yytestcase(yyruleno==249);
      /* (250) tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces */ yytestcase(yyruleno==250);
      /* (251) tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent */ yytestcase(yyruleno==251);
      /* (252) tagtablecolcontents ::= tagtablecolcontent (OPTIMIZED OUT) */ assert(yyruleno!=252);
      /* (253) tagtablecolcontent ::= taginput */ yytestcase(yyruleno==253);
      /* (254) tagtablecolcontent ::= taginput spaces */ yytestcase(yyruleno==254);
      /* (255) tagtablecolcontent ::= htmltext */ yytestcase(yyruleno==255);
      /* (256) tagtablecolcontent ::= htmltext spaces */ yytestcase(yyruleno==256);
      /* (257) tagtablecolcontent ::= tagtable */ yytestcase(yyruleno==257);
      /* (258) tagtablecolth ::= tagtablecolthfullopen tagtablecolthblockclosefull */ yytestcase(yyruleno==258);
      /* (259) tagtablecolth ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull */ yytestcase(yyruleno==259);
      /* (260) tagtablecolthfullopen ::= tagtablecolthopen tagclosechar */ yytestcase(yyruleno==260);
      /* (261) tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar */ yytestcase(yyruleno==261);
      /* (262) tagtablecolthblockclosefull ::= tagtablecolthblockclose */ yytestcase(yyruleno==262);
      /* (263) tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces */ yytestcase(yyruleno==263);
      /* (264) tagtitle ::= tagtitlefullopen tagtitleblockclosefull */ yytestcase(yyruleno==264);
      /* (265) tagtitle ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull */ yytestcase(yyruleno==265);
      /* (266) tagtitlefullopen ::= tagtitleopen tagclosechar */ yytestcase(yyruleno==266);
      /* (267) tagtitlefullopen ::= tagtitleopen tagproperties tagclosechar */ yytestcase(yyruleno==267);
      /* (268) tagtitleblockclosefull ::= tagtitleblockclose */ yytestcase(yyruleno==268);
      /* (269) tagtitleblockclosefull ::= tagtitleblockclose spaces */ yytestcase(yyruleno==269);
      /* (272) taglink ::= taglinkfullopen */ yytestcase(yyruleno==272);
      /* (273) taglink ::= taglinkfullopen taglinkblockclosefull */ yytestcase(yyruleno==273);
      /* (274) taglinkfullopen ::= taglinkopen tagproperties tagclosechar */ yytestcase(yyruleno==274);
      /* (275) taglinkfullopen ::= taglinkopen tagproperties tagshortclose */ yytestcase(yyruleno==275);
      /* (276) taglinkblockclosefull ::= taglinkblockclose */ yytestcase(yyruleno==276);
      /* (277) taglinkblockclosefull ::= taglinkblockclose spaces */ yytestcase(yyruleno==277);
      /* (280) tagmeta ::= tagmetafullopen */ yytestcase(yyruleno==280);
      /* (281) tagmeta ::= tagmetafullopen tagmetablockclosefull */ yytestcase(yyruleno==281);
      /* (282) tagmetafullopen ::= tagmetaopen tagproperties tagclosechar */ yytestcase(yyruleno==282);
      /* (283) tagmetafullopen ::= tagmetaopen tagproperties tagshortclose */ yytestcase(yyruleno==283);
      /* (284) tagmetablockclosefull ::= tagmetablockclose */ yytestcase(yyruleno==284);
      /* (285) tagmetablockclosefull ::= tagmetablockclose spaces */ yytestcase(yyruleno==285);
      /* (288) tagstyle ::= tagstylefullopen tagstyleblockclosefull */ yytestcase(yyruleno==288);
      /* (289) tagstyle ::= tagstylefullopen htmlandspaces tagstyleblockclosefull */ yytestcase(yyruleno==289);
      /* (290) tagstylefullopen ::= tagstyleopen tagclosechar */ yytestcase(yyruleno==290);
      /* (291) tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar */ yytestcase(yyruleno==291);
      /* (292) tagstyleblockclosefull ::= tagstyleblockclose */ yytestcase(yyruleno==292);
      /* (293) tagstyleblockclosefull ::= tagstyleblockclose spaces */ yytestcase(yyruleno==293);
      /* (296) tagstyleproperties ::= tagstyleproperties tagstyleproperty */ yytestcase(yyruleno==296);
      /* (297) tagstyleproperties ::= tagstyleproperty (OPTIMIZED OUT) */ assert(yyruleno!=297);
      /* (301) tagscript ::= tagscriptfullopen tagscriptblockclosefull */ yytestcase(yyruleno==301);
      /* (302) tagscript ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull */ yytestcase(yyruleno==302);
      /* (303) tagscriptfullopen ::= tagscriptopen tagclosechar */ yytestcase(yyruleno==303);
      /* (304) tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar */ yytestcase(yyruleno==304);
      /* (307) tagscriptproperties ::= tagscriptproperties tagscriptproperty */ yytestcase(yyruleno==307);
      /* (308) tagscriptproperties ::= tagscriptproperty (OPTIMIZED OUT) */ assert(yyruleno!=308);
      /* (311) taghtml ::= taghtmlfullopen taghtmlblockclosefull */ yytestcase(yyruleno==311);
      /* (312) taghtml ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull */ yytestcase(yyruleno==312);
      /* (313) taghtmlfullopen ::= taghtmlopen tagclosechar */ yytestcase(yyruleno==313);
      /* (314) taghtmlfullopen ::= taghtmlopen tagclosechar spaces */ yytestcase(yyruleno==314);
      /* (315) taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar */ yytestcase(yyruleno==315);
      /* (316) taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar spaces */ yytestcase(yyruleno==316);
      /* (317) taghtmlblockclosefull ::= taghtmlblockclose (OPTIMIZED OUT) */ assert(yyruleno!=317);
      /* (319) tagbody ::= tagbodyfullopen tagbodyblockclosefull */ yytestcase(yyruleno==319);
      /* (320) tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull */ yytestcase(yyruleno==320);
      /* (321) tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar */ yytestcase(yyruleno==321);
      /* (322) tagbodyblockclosefull ::= tagbodyblockclose */ yytestcase(yyruleno==322);
      /* (323) tagbodyblockclosefull ::= tagbodyblockclose spaces */ yytestcase(yyruleno==323);
      /* (325) taghead ::= tagheadfullopen tagheadblockclosefull */ yytestcase(yyruleno==325);
      /* (326) taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull */ yytestcase(yyruleno==326);
      /* (327) tagheadblockclosefull ::= tagheadblockclose */ yytestcase(yyruleno==327);
      /* (328) tagheadblockclosefull ::= tagheadblockclose space */ yytestcase(yyruleno==328);
      /* (332) tagpropertieswithreturnvaluesall ::= tagpropertieswithreturnvalues */ yytestcase(yyruleno==332);
      /* (333) tagpropertieswithreturnvalues ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue */ yytestcase(yyruleno==333);
      /* (334) tagpropertieswithreturnvalues ::= tagpropertywithreturnvalue (OPTIMIZED OUT) */ assert(yyruleno!=334);
      /* (336) tagproperties ::= tagproperties tagproperty */ yytestcase(yyruleno==336);
      /* (337) tagproperties ::= tagproperty (OPTIMIZED OUT) */ assert(yyruleno!=337);
      /* (342) htmlandspaces ::= htmlandspaces htmlandspace */ yytestcase(yyruleno==342);
      /* (343) htmlandspaces ::= htmlandspace (OPTIMIZED OUT) */ assert(yyruleno!=343);
      /* (347) spaces ::= spaces space */ yytestcase(yyruleno==347);
      /* (348) spaces ::= space (OPTIMIZED OUT) */ assert(yyruleno!=348);
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

    printf("\nsyntax error");
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
#line 2999 "lemon.html.c"
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
