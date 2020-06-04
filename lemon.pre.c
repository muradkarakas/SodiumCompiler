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
#line 2 "lemon.pre.yy"

  /**
  * This file is part of Sodium Language project
  *
  * Copyright © 2020 Murad Karakaş <muradkarakas@gmail.com>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License v3.0
  * as published by the Free Software Foundation; either
  * version 3 of the License, or (at your option) any later version.
  *
  *	https://choosealicense.com/licenses/gpl-3.0/
  */

#include <assert.h>
#include "pre.parser.imp.h"

#line 46 "lemon.pre.c"
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
**    preParseTOKENTYPE     is the data type used for minor type for terminal
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
**                       which is preParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    preParseARG_SDECL     A static variable declaration for the %extra_argument
**    preParseARG_PDECL     A parameter declaration for the %extra_argument
**    preParseARG_STORE     Code to store %extra_argument into yypParser
**    preParseARG_FETCH     Code to extract %extra_argument from yypParser
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
#define YYNOCODE 37
#define YYACTIONTYPE unsigned char
#define preParseTOKENTYPE  Token 
typedef union {
  int yyinit;
  preParseTOKENTYPE yy0;
  Token yy18;
  char * yy49;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define preParseARG_SDECL  SodiumCompiler *session ;
#define preParseARG_PDECL , SodiumCompiler *session 
#define preParseARG_FETCH  SodiumCompiler *session  = yypParser->session 
#define preParseARG_STORE yypParser->session  = session 
#define YYNSTATE             24
#define YYNRULE              35
#define YY_MAX_SHIFT         23
#define YY_MIN_SHIFTREDUCE   57
#define YY_MAX_SHIFTREDUCE   91
#define YY_MIN_REDUCE        92
#define YY_MAX_REDUCE        126
#define YY_ERROR_ACTION      127
#define YY_ACCEPT_ACTION     128
#define YY_NO_ACTION         129
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
#define YY_ACTTAB_COUNT (73)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   112,   82,   23,   17,    6,    7,    5,    4,    3,   13,
 /*    10 */     2,   82,   23,   76,    6,   86,    5,    4,    3,   13,
 /*    20 */     2,   89,  128,    1,    1,    1,    1,   71,   78,   78,
 /*    30 */    78,   85,   11,   68,   65,   10,   61,   19,   64,   10,
 /*    40 */    18,   20,   63,   10,   21,   66,   10,   22,   62,   10,
 /*    50 */    16,   75,    8,   15,   14,    8,   90,   91,   74,   70,
 /*    60 */    72,   12,   12,   69,   72,   73,    9,   60,   67,   59,
 /*    70 */    58,   57,   83,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     0,    1,    2,   29,    4,   31,    6,    7,    8,    9,
 /*    10 */    10,    1,    2,   14,    4,   35,    6,    7,    8,    9,
 /*    20 */    10,   15,   21,   22,   23,   24,   25,   19,   23,   24,
 /*    30 */    25,   33,   34,   26,   27,   28,    5,   26,   27,   28,
 /*    40 */    26,   26,   27,   28,   26,   27,   28,   26,   27,   28,
 /*    50 */     4,   26,   32,    7,    8,   35,   16,   17,   26,   12,
 /*    60 */    13,   19,   20,   12,   13,   26,   11,    5,   30,    5,
 /*    70 */     5,    5,    3,
};
#define YY_SHIFT_USE_DFLT (73)
#define YY_SHIFT_COUNT    (23)
#define YY_SHIFT_MIN      (-1)
#define YY_SHIFT_MAX      (69)
static const signed char yy_shift_ofst[] = {
 /*     0 */    10,    0,   -1,   -1,   -1,   -1,   -1,   46,   40,   47,
 /*    10 */     6,   46,   51,   -1,   -1,   -1,   -1,   55,   31,   62,
 /*    20 */    64,   65,   66,   69,
};
#define YY_REDUCE_USE_DFLT (-27)
#define YY_REDUCE_COUNT (17)
#define YY_REDUCE_MIN   (-26)
#define YY_REDUCE_MAX   (42)
static const signed char yy_reduce_ofst[] = {
 /*     0 */     1,    5,    7,   11,   15,   18,   21,   20,   -2,   42,
 /*    10 */   -26,  -20,    8,   14,   25,   32,   39,   38,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   127,  127,  127,  127,  127,  127,  127,  123,  127,  127,
 /*    10 */   127,  123,  127,  127,  127,  127,  127,  127,  127,  103,
 /*    20 */   103,  103,  103,  127,
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
  preParseARG_SDECL                /* A place to hold %extra_argument */
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
void preParseTrace(FILE *TraceFILE, char *zTracePrompt){
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
  "$",             "PRE_END_OF_FILE",  "PRE_COMMENT_START",  "PRE_COMMENT_END",
  "PRE_VARIABLE_TYPE_VARCHAR",  "PRE_SEMICOLON",  "PRE_VARIABLE_TYPE_BOOL",  "PRE_VARIABLE_TYPE_NUMBER",
  "PRE_VARIABLE_TYPE_DATE",  "PRE_VARIABLE_TYPE_REDIS",  "PRE_VARIABLE_TYPE_VOID",  "PRE_FUNCTION_BEGIN",
  "PRE_FUNCTION_END",  "PRE_FUNCTION_BODY_LINE",  "PRE_IDENTIFIER",  "PRE_OPEN_PARAN",
  "PRE_CLOSE_PARAN",  "PRE_COMMA",     "error",         "function_body_line",
  "function_body_lines",  "start",         "expressions",   "expression",  
  "comment",       "globals",       "identifier",    "funcdechead", 
  "funcdecid",     "parameterlist",  "htsqlfunctionbody",  "openparenthesis",
  "parameters",    "closeparenthesis",  "comma",         "parameter",   
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "globals ::= PRE_VARIABLE_TYPE_VARCHAR identifier PRE_SEMICOLON",
 /*   1 */ "globals ::= PRE_VARIABLE_TYPE_BOOL identifier PRE_SEMICOLON",
 /*   2 */ "globals ::= PRE_VARIABLE_TYPE_NUMBER identifier PRE_SEMICOLON",
 /*   3 */ "globals ::= PRE_VARIABLE_TYPE_DATE identifier PRE_SEMICOLON",
 /*   4 */ "globals ::= PRE_VARIABLE_TYPE_REDIS identifier PRE_SEMICOLON",
 /*   5 */ "globals ::= PRE_VARIABLE_TYPE_VARCHAR funcdechead",
 /*   6 */ "globals ::= PRE_VARIABLE_TYPE_NUMBER funcdechead",
 /*   7 */ "globals ::= PRE_VARIABLE_TYPE_DATE funcdechead",
 /*   8 */ "globals ::= PRE_VARIABLE_TYPE_VOID funcdechead",
 /*   9 */ "globals ::= PRE_VARIABLE_TYPE_BOOL funcdechead",
 /*  10 */ "funcdechead ::= funcdecid parameterlist htsqlfunctionbody",
 /*  11 */ "funcdecid ::= identifier",
 /*  12 */ "htsqlfunctionbody ::= PRE_FUNCTION_BEGIN function_body_lines PRE_FUNCTION_END",
 /*  13 */ "htsqlfunctionbody ::= PRE_FUNCTION_BEGIN PRE_FUNCTION_END",
 /*  14 */ "function_body_lines ::= function_body_lines function_body_line",
 /*  15 */ "function_body_line ::= PRE_FUNCTION_BODY_LINE",
 /*  16 */ "parameter ::= PRE_VARIABLE_TYPE_VARCHAR identifier",
 /*  17 */ "parameter ::= PRE_VARIABLE_TYPE_NUMBER identifier",
 /*  18 */ "parameter ::= PRE_VARIABLE_TYPE_DATE identifier",
 /*  19 */ "identifier ::= PRE_IDENTIFIER",
 /*  20 */ "start ::= expressions",
 /*  21 */ "expressions ::= expressions expression",
 /*  22 */ "expressions ::= expression",
 /*  23 */ "expression ::= comment",
 /*  24 */ "expression ::= globals",
 /*  25 */ "expression ::= PRE_END_OF_FILE",
 /*  26 */ "comment ::= PRE_COMMENT_START PRE_COMMENT_END",
 /*  27 */ "function_body_lines ::= function_body_line",
 /*  28 */ "parameterlist ::= openparenthesis parameters closeparenthesis",
 /*  29 */ "parameters ::= parameters comma parameter",
 /*  30 */ "parameters ::= parameter",
 /*  31 */ "parameter ::=",
 /*  32 */ "openparenthesis ::= PRE_OPEN_PARAN",
 /*  33 */ "closeparenthesis ::= PRE_CLOSE_PARAN",
 /*  34 */ "comma ::= PRE_COMMA",
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
** second argument to preParseAlloc() below.  This can be changed by
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
** to preParse and preParseFree.
*/
void *preParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
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
  preParseARG_FETCH;
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
    case 1: /* PRE_END_OF_FILE */
    case 2: /* PRE_COMMENT_START */
    case 3: /* PRE_COMMENT_END */
    case 4: /* PRE_VARIABLE_TYPE_VARCHAR */
    case 5: /* PRE_SEMICOLON */
    case 6: /* PRE_VARIABLE_TYPE_BOOL */
    case 7: /* PRE_VARIABLE_TYPE_NUMBER */
    case 8: /* PRE_VARIABLE_TYPE_DATE */
    case 9: /* PRE_VARIABLE_TYPE_REDIS */
    case 10: /* PRE_VARIABLE_TYPE_VOID */
    case 11: /* PRE_FUNCTION_BEGIN */
    case 12: /* PRE_FUNCTION_END */
    case 13: /* PRE_FUNCTION_BODY_LINE */
    case 14: /* PRE_IDENTIFIER */
    case 15: /* PRE_OPEN_PARAN */
    case 16: /* PRE_CLOSE_PARAN */
    case 17: /* PRE_COMMA */
{
#line 32 "lemon.pre.yy"

    if ((yypminor->yy0).tokenStr != NULL) {
        printf("%s", (yypminor->yy0).tokenStr);
        mkFree(session->heapHandle, (yypminor->yy0).tokenStr);
        (yypminor->yy0).tokenStr = NULL;
    }

#line 536 "lemon.pre.c"
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
void preParseFree(
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
int preParseStackPeak(void *p){
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
   preParseARG_FETCH;
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
   preParseARG_STORE; /* Suppress warning about unused %extra_argument var */
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
  preParseTOKENTYPE yyMinor        /* The minor token to shift in */
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
  { 25, 3 },
  { 25, 3 },
  { 25, 3 },
  { 25, 3 },
  { 25, 3 },
  { 25, 2 },
  { 25, 2 },
  { 25, 2 },
  { 25, 2 },
  { 25, 2 },
  { 27, 3 },
  { 28, 1 },
  { 30, 3 },
  { 30, 2 },
  { 20, 2 },
  { 19, 1 },
  { 35, 2 },
  { 35, 2 },
  { 35, 2 },
  { 26, 1 },
  { 21, 1 },
  { 22, 2 },
  { 22, 1 },
  { 23, 1 },
  { 23, 1 },
  { 23, 1 },
  { 24, 2 },
  { 20, 1 },
  { 29, 3 },
  { 32, 3 },
  { 32, 1 },
  { 35, 0 },
  { 31, 1 },
  { 33, 1 },
  { 34, 1 },
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
  preParseARG_FETCH;
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
        YYMINORTYPE yylhsminor;
      case 0: /* globals ::= PRE_VARIABLE_TYPE_VARCHAR identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,4,&yymsp[-2].minor);
#line 59 "lemon.pre.yy"
{
   
    // preTokenDestructor(session, yymsp[-1].minor.yy18);
}
#line 884 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 1: /* globals ::= PRE_VARIABLE_TYPE_BOOL identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,6,&yymsp[-2].minor);
#line 64 "lemon.pre.yy"
{
    
    // preTokenDestructor(session, yymsp[-1].minor.yy18);
}
#line 895 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 2: /* globals ::= PRE_VARIABLE_TYPE_NUMBER identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 69 "lemon.pre.yy"
{
    
    // preTokenDestructor(session, yymsp[-1].minor.yy18);
}
#line 906 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 3: /* globals ::= PRE_VARIABLE_TYPE_DATE identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,8,&yymsp[-2].minor);
#line 74 "lemon.pre.yy"
{
    
    // preTokenDestructor(session, yymsp[-1].minor.yy18);
}
#line 917 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 4: /* globals ::= PRE_VARIABLE_TYPE_REDIS identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,9,&yymsp[-2].minor);
#line 79 "lemon.pre.yy"
{
	
	// preTokenDestructor(session, yymsp[-1].minor.yy18);
}
#line 928 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 5: /* globals ::= PRE_VARIABLE_TYPE_VARCHAR funcdechead */
{  yy_destructor(yypParser,4,&yymsp[-1].minor);
#line 87 "lemon.pre.yy"
{
    
}
#line 938 "lemon.pre.c"
}
        break;
      case 6: /* globals ::= PRE_VARIABLE_TYPE_NUMBER funcdechead */
{  yy_destructor(yypParser,7,&yymsp[-1].minor);
#line 91 "lemon.pre.yy"
{
    
}
#line 947 "lemon.pre.c"
}
        break;
      case 7: /* globals ::= PRE_VARIABLE_TYPE_DATE funcdechead */
{  yy_destructor(yypParser,8,&yymsp[-1].minor);
#line 95 "lemon.pre.yy"
{
    
}
#line 956 "lemon.pre.c"
}
        break;
      case 8: /* globals ::= PRE_VARIABLE_TYPE_VOID funcdechead */
{  yy_destructor(yypParser,10,&yymsp[-1].minor);
#line 99 "lemon.pre.yy"
{
    
}
#line 965 "lemon.pre.c"
}
        break;
      case 9: /* globals ::= PRE_VARIABLE_TYPE_BOOL funcdechead */
{  yy_destructor(yypParser,6,&yymsp[-1].minor);
#line 103 "lemon.pre.yy"
{
    
}
#line 974 "lemon.pre.c"
}
        break;
      case 10: /* funcdechead ::= funcdecid parameterlist htsqlfunctionbody */
#line 108 "lemon.pre.yy"
{
	
}
#line 982 "lemon.pre.c"
        break;
      case 11: /* funcdecid ::= identifier */
#line 112 "lemon.pre.yy"
{
    
    // preTokenDestructor(session, yymsp[0].minor.yy18);
}
#line 990 "lemon.pre.c"
        break;
      case 12: /* htsqlfunctionbody ::= PRE_FUNCTION_BEGIN function_body_lines PRE_FUNCTION_END */
#line 120 "lemon.pre.yy"
{
    printf("\n%s\n%s\n%s", yymsp[-2].minor.yy0.tokenStr, yymsp[-1].minor.yy49, yymsp[0].minor.yy0.tokenStr); 
    // preTokenDestructor(session, yymsp[-2].minor.yy0);
    mkFree(session->heapHandle, yymsp[-1].minor.yy49);
    // preTokenDestructor(session, yymsp[0].minor.yy0);
}
#line 1000 "lemon.pre.c"
        break;
      case 13: /* htsqlfunctionbody ::= PRE_FUNCTION_BEGIN PRE_FUNCTION_END */
#line 127 "lemon.pre.yy"
{
        
    // preTokenDestructor(session, yymsp[-1].minor.yy0);
    // preTokenDestructor(session, yymsp[0].minor.yy0);
}
#line 1009 "lemon.pre.c"
        break;
      case 14: /* function_body_lines ::= function_body_lines function_body_line */
#line 135 "lemon.pre.yy"
{
    char *p1  = yymsp[-1].minor.yy49;
    char *p2  = yymsp[0].minor.yy49;
    char *ret = mkStrcat(session->heapHandle, __FILE__, __LINE__, p1, p2, NULL);
    yylhsminor.yy49 = ret;
    mkFree(session->heapHandle, p1);
    mkFree(session->heapHandle, p2);
}
#line 1021 "lemon.pre.c"
  yymsp[-1].minor.yy49 = yylhsminor.yy49;
        break;
      case 15: /* function_body_line ::= PRE_FUNCTION_BODY_LINE */
#line 146 "lemon.pre.yy"
{
    yylhsminor.yy49 = yymsp[0].minor.yy0.tokenStr;
}
#line 1029 "lemon.pre.c"
  yymsp[0].minor.yy49 = yylhsminor.yy49;
        break;
      case 16: /* parameter ::= PRE_VARIABLE_TYPE_VARCHAR identifier */
{  yy_destructor(yypParser,4,&yymsp[-1].minor);
#line 164 "lemon.pre.yy"
{
    
	// preTokenDestructor(session, yymsp[0].minor.yy18);
}
#line 1039 "lemon.pre.c"
}
        break;
      case 17: /* parameter ::= PRE_VARIABLE_TYPE_NUMBER identifier */
{  yy_destructor(yypParser,7,&yymsp[-1].minor);
#line 169 "lemon.pre.yy"
{
    
	// preTokenDestructor(session, yymsp[0].minor.yy18);
}
#line 1049 "lemon.pre.c"
}
        break;
      case 18: /* parameter ::= PRE_VARIABLE_TYPE_DATE identifier */
{  yy_destructor(yypParser,8,&yymsp[-1].minor);
#line 174 "lemon.pre.yy"
{
    
	// preTokenDestructor(session, yymsp[0].minor.yy18);
}
#line 1059 "lemon.pre.c"
}
        break;
      case 19: /* identifier ::= PRE_IDENTIFIER */
#line 186 "lemon.pre.yy"
{
	Token a = yymsp[0].minor.yy0;
	yylhsminor.yy18 = a;
}
#line 1068 "lemon.pre.c"
  yymsp[0].minor.yy18 = yylhsminor.yy18;
        break;
      case 25: /* expression ::= PRE_END_OF_FILE */
{  yy_destructor(yypParser,1,&yymsp[0].minor);
#line 53 "lemon.pre.yy"
{
}
#line 1076 "lemon.pre.c"
}
        break;
      case 26: /* comment ::= PRE_COMMENT_START PRE_COMMENT_END */
{  yy_destructor(yypParser,2,&yymsp[-1].minor);
#line 55 "lemon.pre.yy"
{
}
#line 1084 "lemon.pre.c"
  yy_destructor(yypParser,3,&yymsp[0].minor);
}
        break;
      case 32: /* openparenthesis ::= PRE_OPEN_PARAN */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 194 "lemon.pre.yy"
{
}
#line 1093 "lemon.pre.c"
}
        break;
      case 33: /* closeparenthesis ::= PRE_CLOSE_PARAN */
{  yy_destructor(yypParser,16,&yymsp[0].minor);
#line 195 "lemon.pre.yy"
{
}
#line 1101 "lemon.pre.c"
}
        break;
      case 34: /* comma ::= PRE_COMMA */
{  yy_destructor(yypParser,17,&yymsp[0].minor);
#line 197 "lemon.pre.yy"
{
}
#line 1109 "lemon.pre.c"
}
        break;
      default:
      /* (20) start ::= expressions */ yytestcase(yyruleno==20);
      /* (21) expressions ::= expressions expression */ yytestcase(yyruleno==21);
      /* (22) expressions ::= expression (OPTIMIZED OUT) */ assert(yyruleno!=22);
      /* (23) expression ::= comment (OPTIMIZED OUT) */ assert(yyruleno!=23);
      /* (24) expression ::= globals (OPTIMIZED OUT) */ assert(yyruleno!=24);
      /* (27) function_body_lines ::= function_body_line (OPTIMIZED OUT) */ assert(yyruleno!=27);
      /* (28) parameterlist ::= openparenthesis parameters closeparenthesis */ yytestcase(yyruleno==28);
      /* (29) parameters ::= parameters comma parameter */ yytestcase(yyruleno==29);
      /* (30) parameters ::= parameter (OPTIMIZED OUT) */ assert(yyruleno!=30);
      /* (31) parameter ::= */ yytestcase(yyruleno==31);
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
  preParseARG_FETCH;
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
  preParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  preParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  preParseARG_FETCH;
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 41 "lemon.pre.yy"


#line 1182 "lemon.pre.c"
/************ End %syntax_error code ******************************************/
  preParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  preParseARG_FETCH;
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
  preParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "preParseAlloc" which describes the current state of the parser.
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
void preParse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  preParseTOKENTYPE yyminor       /* The value for the token */
  preParseARG_PDECL               /* Optional %extra_argument parameter */
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
  preParseARG_STORE;

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
