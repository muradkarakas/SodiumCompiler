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

#include "pch.h"

#include <stdint.h>
#include <assert.h>

#include "pre.parser.imp.hpp"

#include "ASTNode.hpp"
#include "ASTNode_Data_Type.hpp"
#include "ASTNode_Identifier.hpp"
#include "ASTNode_Statement_Function_Declaration.hpp"
#include "ASTNode_Statement_Variable_Declaration.hpp"

#include "ASTNode_Identifier.hpp"

    using namespace Sodium;
#line 59 "lemon.pre.c"
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
#define YYNOCODE 40
#define YYACTIONTYPE unsigned char
#define preParseTOKENTYPE  Token * 
typedef union {
  int yyinit;
  preParseTOKENTYPE yy0;
  const char * yy38;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define preParseARG_SDECL  SodiumCompiler * compiler ;
#define preParseARG_PDECL , SodiumCompiler * compiler 
#define preParseARG_FETCH  SodiumCompiler * compiler  = yypParser->compiler 
#define preParseARG_STORE yypParser->compiler  = compiler 
#define YYNSTATE             25
#define YYNRULE              39
#define YY_MAX_SHIFT         24
#define YY_MIN_SHIFTREDUCE   61
#define YY_MAX_SHIFTREDUCE   99
#define YY_MIN_REDUCE        100
#define YY_MAX_REDUCE        138
#define YY_ERROR_ACTION      139
#define YY_ACCEPT_ACTION     140
#define YY_NO_ACTION         141
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
#define YY_ACTTAB_COUNT (81)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   104,   71,   24,   17,    6,    7,    5,    4,    3,   13,
 /*    10 */     2,   64,   71,   24,   96,    6,   88,    5,    4,    3,
 /*    20 */    13,    2,   10,   62,   10,   96,   84,  140,    1,    1,
 /*    30 */     1,    1,   18,   66,   66,   66,   18,   97,   20,   79,
 /*    40 */    10,   98,   99,   18,   21,   78,   10,   18,   22,   80,
 /*    50 */    10,   23,   77,   10,   16,   19,    8,   15,   14,    8,
 /*    60 */    87,   11,   92,   83,   86,   12,   12,   82,   86,   91,
 /*    70 */    90,    9,   63,   96,   94,   61,   76,   75,   74,   73,
 /*    80 */    72,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     0,    1,    2,   31,    4,   33,    6,    7,    8,    9,
 /*    10 */    10,   15,    1,    2,   14,    4,   37,    6,    7,    8,
 /*    20 */     9,   10,   28,   29,   30,   14,   20,   22,   23,   24,
 /*    30 */    25,   26,   27,   24,   25,   26,   27,   16,   28,   29,
 /*    40 */    30,   17,   18,   38,   28,   29,   30,   38,   28,   29,
 /*    50 */    30,   28,   29,   30,    4,   28,   34,    7,    8,   37,
 /*    60 */    35,   36,   28,   12,   13,   20,   21,   12,   13,   28,
 /*    70 */    28,   11,   32,   14,   38,    5,    5,    5,    5,    5,
 /*    80 */     3,
};
#define YY_SHIFT_USE_DFLT (81)
#define YY_SHIFT_COUNT    (24)
#define YY_SHIFT_MIN      (-4)
#define YY_SHIFT_MAX      (77)
static const signed char yy_shift_ofst[] = {
 /*     0 */    11,    0,   -4,   -4,   -4,   -4,   -4,   50,   24,   51,
 /*    10 */    21,   50,   55,   -4,   -4,   -4,   -4,   60,   59,   70,
 /*    20 */    71,   72,   73,   74,   77,
};
#define YY_REDUCE_USE_DFLT (-29)
#define YY_REDUCE_COUNT (18)
#define YY_REDUCE_MIN   (-28)
#define YY_REDUCE_MAX   (45)
static const signed char yy_reduce_ofst[] = {
 /*     0 */     5,    9,   -6,   10,   16,   20,   23,   22,   25,   45,
 /*    10 */   -28,  -21,    6,   27,   34,   41,   42,   40,   36,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   139,  139,  139,  139,  139,  139,  139,  132,  139,  139,
 /*    10 */   139,  132,  139,  139,  139,  139,  139,  139,  109,  139,
 /*    20 */   120,  120,  120,  120,  139,
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
  "PRE_FUNCTION_END",  "PRE_FUNCTION_BODY_LINE",  "PRE_ENTER",     "PRE_IDENTIFIER",
  "PRE_OPEN_PARAN",  "PRE_CLOSE_PARAN",  "PRE_COMMA",     "error",       
  "function_body_line",  "function_body_lines",  "start",         "expressions", 
  "expression",    "comment",       "globals",       "enters",      
  "identifier",    "funcdechead",   "funcdecid",     "parameterlist",
  "htsqlfunctionbody",  "openparenthesis",  "parameters",    "closeparenthesis",
  "comma",         "parameter",     "enter",       
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "globals ::= PRE_VARIABLE_TYPE_REDIS identifier PRE_SEMICOLON",
 /*   1 */ "globals ::= PRE_VARIABLE_TYPE_VOID funcdechead",
 /*   2 */ "funcdechead ::= funcdecid parameterlist htsqlfunctionbody",
 /*   3 */ "identifier ::= PRE_IDENTIFIER",
 /*   4 */ "start ::= expressions",
 /*   5 */ "expressions ::= expressions expression",
 /*   6 */ "expressions ::= expression",
 /*   7 */ "expression ::= comment",
 /*   8 */ "expression ::= globals",
 /*   9 */ "expression ::= enters",
 /*  10 */ "expression ::= PRE_END_OF_FILE",
 /*  11 */ "comment ::= PRE_COMMENT_START PRE_COMMENT_END",
 /*  12 */ "globals ::= PRE_VARIABLE_TYPE_VARCHAR identifier PRE_SEMICOLON",
 /*  13 */ "globals ::= PRE_VARIABLE_TYPE_BOOL identifier PRE_SEMICOLON",
 /*  14 */ "globals ::= PRE_VARIABLE_TYPE_NUMBER identifier PRE_SEMICOLON",
 /*  15 */ "globals ::= PRE_VARIABLE_TYPE_DATE identifier PRE_SEMICOLON",
 /*  16 */ "globals ::= PRE_VARIABLE_TYPE_VARCHAR funcdechead",
 /*  17 */ "globals ::= PRE_VARIABLE_TYPE_NUMBER funcdechead",
 /*  18 */ "globals ::= PRE_VARIABLE_TYPE_DATE funcdechead",
 /*  19 */ "globals ::= PRE_VARIABLE_TYPE_BOOL funcdechead",
 /*  20 */ "funcdecid ::= identifier",
 /*  21 */ "htsqlfunctionbody ::= PRE_FUNCTION_BEGIN function_body_lines PRE_FUNCTION_END",
 /*  22 */ "htsqlfunctionbody ::= PRE_FUNCTION_BEGIN PRE_FUNCTION_END",
 /*  23 */ "function_body_lines ::= function_body_lines function_body_line",
 /*  24 */ "function_body_lines ::= function_body_line",
 /*  25 */ "function_body_line ::= PRE_FUNCTION_BODY_LINE",
 /*  26 */ "parameterlist ::= openparenthesis parameters closeparenthesis",
 /*  27 */ "parameters ::= parameters comma parameter",
 /*  28 */ "parameters ::= parameter",
 /*  29 */ "parameter ::= PRE_VARIABLE_TYPE_VARCHAR identifier",
 /*  30 */ "parameter ::= PRE_VARIABLE_TYPE_NUMBER identifier",
 /*  31 */ "parameter ::= PRE_VARIABLE_TYPE_DATE identifier",
 /*  32 */ "parameter ::=",
 /*  33 */ "enters ::= enters enter",
 /*  34 */ "enters ::= enter",
 /*  35 */ "enter ::= PRE_ENTER",
 /*  36 */ "openparenthesis ::= PRE_OPEN_PARAN",
 /*  37 */ "closeparenthesis ::= PRE_CLOSE_PARAN",
 /*  38 */ "comma ::= PRE_COMMA",
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
    case 14: /* PRE_ENTER */
    case 15: /* PRE_IDENTIFIER */
    case 16: /* PRE_OPEN_PARAN */
    case 17: /* PRE_CLOSE_PARAN */
    case 18: /* PRE_COMMA */
{
#line 44 "lemon.pre.yy"

    /*Token *token = (yypminor->yy0);
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
    }*/

#line 565 "lemon.pre.c"
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
  { 26, 3 },
  { 26, 2 },
  { 29, 3 },
  { 28, 1 },
  { 22, 1 },
  { 23, 2 },
  { 23, 1 },
  { 24, 1 },
  { 24, 1 },
  { 24, 1 },
  { 24, 1 },
  { 25, 2 },
  { 26, 3 },
  { 26, 3 },
  { 26, 3 },
  { 26, 3 },
  { 26, 2 },
  { 26, 2 },
  { 26, 2 },
  { 26, 2 },
  { 30, 1 },
  { 32, 3 },
  { 32, 2 },
  { 21, 2 },
  { 21, 1 },
  { 20, 1 },
  { 31, 3 },
  { 34, 3 },
  { 34, 1 },
  { 37, 2 },
  { 37, 2 },
  { 37, 2 },
  { 37, 0 },
  { 27, 2 },
  { 27, 1 },
  { 38, 1 },
  { 33, 1 },
  { 35, 1 },
  { 36, 1 },
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
      case 0: /* globals ::= PRE_VARIABLE_TYPE_REDIS identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,9,&yymsp[-2].minor);
#line 89 "lemon.pre.yy"
{
    ASTNode_Statement_Variable_Declaration* stmVarDeclaration = 
        new ASTNode_Statement_Variable_Declaration(yymsp[-1].minor.yy0, ASTNodePrimitiveDataType_Redis, "global");

    yymsp[-1].minor.yy0->ASTNodeInstance = stmVarDeclaration;

    //  adding variable declaration to the AST
    compiler->InsertASTNode(stmVarDeclaration);
}
#line 922 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 1: /* globals ::= PRE_VARIABLE_TYPE_VOID funcdechead */
{  yy_destructor(yypParser,10,&yymsp[-1].minor);
#line 108 "lemon.pre.yy"
{
    ASTNode_Statement_Function_Declaration* funcDecl = (ASTNode_Statement_Function_Declaration*)yymsp[0].minor.yy0->ASTNodeInstance;
    
    ASTNode_Data_Type* returnDataType =
        new ASTNode_Data_Type(yymsp[0].minor.yy0, "global", ASTNodePrimitiveDataType_Void);
    
    funcDecl->returnType = returnDataType;
}
#line 937 "lemon.pre.c"
}
        break;
      case 2: /* funcdechead ::= funcdecid parameterlist htsqlfunctionbody */
#line 121 "lemon.pre.yy"
{
    ASTNode_Statement_Function_Declaration* functionDeclaration =
        new ASTNode_Statement_Function_Declaration(yymsp[-2].minor.yy0, "global", (ASTNode_Identifier*) yymsp[-2].minor.yy0->ASTNodeInstance);

    //  adding variable declaration to the AST
    compiler->InsertASTNode(functionDeclaration);
    yylhsminor.yy0 = functionDeclaration->_token;
}
#line 950 "lemon.pre.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 3: /* identifier ::= PRE_IDENTIFIER */
#line 179 "lemon.pre.yy"
{
    ASTNode_Identifier * identifier = new ASTNode_Identifier(yymsp[0].minor.yy0, "global");
    //yymsp[0].minor.yy0->ASTNodeInstance = identifier;
    yylhsminor.yy0 = yymsp[0].minor.yy0;
}
#line 960 "lemon.pre.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 10: /* expression ::= PRE_END_OF_FILE */
{  yy_destructor(yypParser,1,&yymsp[0].minor);
#line 75 "lemon.pre.yy"
{
}
#line 968 "lemon.pre.c"
}
        break;
      case 11: /* comment ::= PRE_COMMENT_START PRE_COMMENT_END */
{  yy_destructor(yypParser,2,&yymsp[-1].minor);
#line 77 "lemon.pre.yy"
{
}
#line 976 "lemon.pre.c"
  yy_destructor(yypParser,3,&yymsp[0].minor);
}
        break;
      case 12: /* globals ::= PRE_VARIABLE_TYPE_VARCHAR identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,4,&yymsp[-2].minor);
#line 80 "lemon.pre.yy"
{
}
#line 985 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 13: /* globals ::= PRE_VARIABLE_TYPE_BOOL identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,6,&yymsp[-2].minor);
#line 82 "lemon.pre.yy"
{
}
#line 994 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 14: /* globals ::= PRE_VARIABLE_TYPE_NUMBER identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 84 "lemon.pre.yy"
{
}
#line 1003 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 15: /* globals ::= PRE_VARIABLE_TYPE_DATE identifier PRE_SEMICOLON */
{  yy_destructor(yypParser,8,&yymsp[-2].minor);
#line 86 "lemon.pre.yy"
{
}
#line 1012 "lemon.pre.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 16: /* globals ::= PRE_VARIABLE_TYPE_VARCHAR funcdechead */
      case 29: /* parameter ::= PRE_VARIABLE_TYPE_VARCHAR identifier */ yytestcase(yyruleno==29);
{  yy_destructor(yypParser,4,&yymsp[-1].minor);
#line 101 "lemon.pre.yy"
{
}
#line 1022 "lemon.pre.c"
}
        break;
      case 17: /* globals ::= PRE_VARIABLE_TYPE_NUMBER funcdechead */
      case 30: /* parameter ::= PRE_VARIABLE_TYPE_NUMBER identifier */ yytestcase(yyruleno==30);
{  yy_destructor(yypParser,7,&yymsp[-1].minor);
#line 103 "lemon.pre.yy"
{
}
#line 1031 "lemon.pre.c"
}
        break;
      case 18: /* globals ::= PRE_VARIABLE_TYPE_DATE funcdechead */
      case 31: /* parameter ::= PRE_VARIABLE_TYPE_DATE identifier */ yytestcase(yyruleno==31);
{  yy_destructor(yypParser,8,&yymsp[-1].minor);
#line 105 "lemon.pre.yy"
{
}
#line 1040 "lemon.pre.c"
}
        break;
      case 19: /* globals ::= PRE_VARIABLE_TYPE_BOOL funcdechead */
{  yy_destructor(yypParser,6,&yymsp[-1].minor);
#line 117 "lemon.pre.yy"
{
}
#line 1048 "lemon.pre.c"
}
        break;
      case 21: /* htsqlfunctionbody ::= PRE_FUNCTION_BEGIN function_body_lines PRE_FUNCTION_END */
{  yy_destructor(yypParser,11,&yymsp[-2].minor);
#line 135 "lemon.pre.yy"
{
}
#line 1056 "lemon.pre.c"
  yy_destructor(yypParser,12,&yymsp[0].minor);
}
        break;
      case 22: /* htsqlfunctionbody ::= PRE_FUNCTION_BEGIN PRE_FUNCTION_END */
{  yy_destructor(yypParser,11,&yymsp[-1].minor);
#line 137 "lemon.pre.yy"
{
}
#line 1065 "lemon.pre.c"
  yy_destructor(yypParser,12,&yymsp[0].minor);
}
        break;
      case 25: /* function_body_line ::= PRE_FUNCTION_BODY_LINE */
{  yy_destructor(yypParser,13,&yymsp[0].minor);
#line 145 "lemon.pre.yy"
{
}
#line 1074 "lemon.pre.c"
}
        break;
      case 35: /* enter ::= PRE_ENTER */
{  yy_destructor(yypParser,14,&yymsp[0].minor);
#line 174 "lemon.pre.yy"
{
}
#line 1082 "lemon.pre.c"
}
        break;
      case 36: /* openparenthesis ::= PRE_OPEN_PARAN */
{  yy_destructor(yypParser,16,&yymsp[0].minor);
#line 188 "lemon.pre.yy"
{
}
#line 1090 "lemon.pre.c"
}
        break;
      case 37: /* closeparenthesis ::= PRE_CLOSE_PARAN */
{  yy_destructor(yypParser,17,&yymsp[0].minor);
#line 189 "lemon.pre.yy"
{
}
#line 1098 "lemon.pre.c"
}
        break;
      case 38: /* comma ::= PRE_COMMA */
{  yy_destructor(yypParser,18,&yymsp[0].minor);
#line 191 "lemon.pre.yy"
{
}
#line 1106 "lemon.pre.c"
}
        break;
      default:
      /* (4) start ::= expressions */ yytestcase(yyruleno==4);
      /* (5) expressions ::= expressions expression */ yytestcase(yyruleno==5);
      /* (6) expressions ::= expression (OPTIMIZED OUT) */ assert(yyruleno!=6);
      /* (7) expression ::= comment (OPTIMIZED OUT) */ assert(yyruleno!=7);
      /* (8) expression ::= globals (OPTIMIZED OUT) */ assert(yyruleno!=8);
      /* (9) expression ::= enters */ yytestcase(yyruleno==9);
      /* (20) funcdecid ::= identifier */ yytestcase(yyruleno==20);
      /* (23) function_body_lines ::= function_body_lines function_body_line */ yytestcase(yyruleno==23);
      /* (24) function_body_lines ::= function_body_line (OPTIMIZED OUT) */ assert(yyruleno!=24);
      /* (26) parameterlist ::= openparenthesis parameters closeparenthesis */ yytestcase(yyruleno==26);
      /* (27) parameters ::= parameters comma parameter */ yytestcase(yyruleno==27);
      /* (28) parameters ::= parameter (OPTIMIZED OUT) */ assert(yyruleno!=28);
      /* (32) parameter ::= */ yytestcase(yyruleno==32);
      /* (33) enters ::= enters enter */ yytestcase(yyruleno==33);
      /* (34) enters ::= enter (OPTIMIZED OUT) */ assert(yyruleno!=34);
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
#line 62 "lemon.pre.yy"

    printf("\nsyntax error");
#line 1184 "lemon.pre.c"
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
