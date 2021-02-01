#line 1 "build/utility/kmyacc.c.parser"
/* -*-c-*-  Prototype file of KM-yacc parser for C.
 *
 * Written by MORI Koichiro
 *
 * This file is PUBLIC DOMAIN.
 */


#line 1 "src/kinx.y"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <kvec.h>
#include <kinx.h>
#define KX_NO_INCLUDE_PARSER_TAB_H
#include <kxastobject.h>

// #define YYDEBUG 1
static inline void yy_restart(int token)
{
    kx_lexinfo.tempbuf[0] = token;
    kx_lexinfo.tempbuf[1] = kx_lexinfo.ch;
    kx_lexinfo.tempbuf[2] = 0;
    kx_lexinfo.restart = kx_lexinfo.tempbuf;
    kx_lexinfo.ch = ' ';
}

#line 14 "build/utility/kmyacc.c.parser"

#line 20 "build/utility/kmyacc.c.parser"

#line 24 "build/utility/kmyacc.c.parser"

/* declarations */
#line 28 "build/utility/kmyacc.c.parser"
typedef union
{
    kx_object_t   *obj;
    int           incdec;
    int64_t       intval;
    double        dblval;
    const char    *strval;
    const uint8_t *binval;
    arytype_t     arraytype;
    named_stmt_t  namedstmt;
}
#line 30 "build/utility/kmyacc.c.parser"
YYSTYPE;
#line 38 "build/utility/kmyacc.c.parser"
extern YYSTYPE kx_yylval;

#define YYERRTOK 256
#define ERROR 257
#define IF 258
#define ELSE 259
#define WHILE 260
#define DO 261
#define FOR 262
#define IN 263
#define TRY 264
#define CATCH 265
#define FINALLY 266
#define BREAK 267
#define CONTINUE 268
#define SWITCH 269
#define CASE 270
#define DEFAULT 271
#define WHEN 272
#define ENUM 273
#define NEW 274
#define VAR 275
#define CONST 276
#define RETURN 277
#define THROW 278
#define YIELD 279
#define MIXIN 280
#define EQEQ 281
#define NEQ 282
#define LE 283
#define GE 284
#define LGE 285
#define LOR 286
#define LAND 287
#define INC 288
#define DEC 289
#define SHL 290
#define SHR 291
#define POW 292
#define LUNDEF 293
#define ADDEQ 294
#define SUBEQ 295
#define MULEQ 296
#define DIVEQ 297
#define MODEQ 298
#define ANDEQ 299
#define OREQ 300
#define XOREQ 301
#define LANDEQ 302
#define LOREQ 303
#define LUNDEFEQ 304
#define SHLEQ 305
#define SHREQ 306
#define REGEQ 307
#define REGNE 308
#define NUL 309
#define TRUE 310
#define FALSE 311
#define AS 312
#define IMPORT 313
#define USING 314
#define DARROW 315
#define SQ 316
#define DQ 317
#define MLSTR 318
#define BINEND 319
#define DOTS2 320
#define DOTS3 321
#define REGPF 322
#define NAMESPACE 323
#define SYSNS 324
#define SYSRET_NV 325
#define CLASS 326
#define SYSCLASS 327
#define MODULE 328
#define SYSMODULE 329
#define NATIVE 330
#define FUNCTION 331
#define SYSFUNC 332
#define PUBLIC 333
#define PRIVATE 334
#define PROTECTED 335
#define COROUTINE 336
#define NAME 337
#define STR 338
#define SRCFILE 339
#define BIGINT 340
#define INT 341
#define TYPE 342
#define TYPEOF 343
#define LBBR 344
#define RBBR 345
#define LMBR 346
#define RMBR 347
#define DBL 348
#define BIN 349
#line 44 "build/utility/kmyacc.c.parser"

/* -p option */
#line 47 "build/utility/kmyacc.c.parser"
#define yyparse kx_yyparse
#define yylex kx_yylex
#define yyerror kx_yyerror
#define yylval kx_yylval
#define yydebug kx_yydebug
#line 53 "build/utility/kmyacc.c.parser"


#ifndef YYMAXDEPTH
# define YYMAXDEPTH 512
#endif /* !YYMAXDEPTH */

#ifndef YYASP
# define YYASP(n) yyasp[n]
#endif /* !YYASP */

#define yyclearin (yychar = -1)
#define yyerrok (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

#define YYACCEPT  return (0)
#define YYABORT  return (1)
#define YYERROR  goto yyerrlab




#if YYDEBUG
int yydebug;
#endif /* YYDEBUG */

#if 0
int yylex();
int yyerror();
#endif

#if !YYPURE
int yychar;
YYSTYPE yylval;
#endif


/* code after %% in *.y */
#line 1068 "src/kinx.y"

int yyerror(const char *msg)
{
    ++g_yyerror;
    if (!kx_lexinfo.quiet) {
        if (kx_lexinfo.file) {
            return printf("Error: %s near the <%s>:%d\n", msg, kx_lexinfo.file, kx_lexinfo.line);
        } else {
            return printf("Error: %s near the <eval>:%d\n", msg, kx_lexinfo.line);
        }
    }
    return 0;
}

int kx_yyerror_line(const char *msg, const char* file, const int line)
{
    ++g_yyerror;
    if (!kx_lexinfo.quiet) {
        return printf("Error: %s near the <%s>:%d\n", msg, file, line);
    }
    return 0;
}

int kx_yyerror_line_fmt(const char *msg, const char* file, const int line, ...)
{
    ++g_yyerror;
    if (!kx_lexinfo.quiet) {
        va_list list;
        int r = printf("Error: ");
        va_start(list, line);
        r += vprintf(msg, list);
        va_end(list);
        r += printf(" near the <%s>:%d\n", file, line);
        return r;
    }
    return 0;
}

int kx_yywarning(const char *msg)
{
    ++g_yywarning;
    if (!kx_lexinfo.quiet) {
        if (kx_lexinfo.file) {
            return printf("Warning: %s near the <%s>:%d\n", msg, kx_lexinfo.file, kx_lexinfo.line);
        } else {
            return printf("Warning: %s near the <eval>:%d\n", msg, kx_lexinfo.line);
        }
    }
    return 0;
}
#line 91 "build/utility/kmyacc.c.parser"


#if !YYDEBUG

#define YYTRACE_DCL
#define YYTRACE_NEWSTATE(st, tok)
#define YYTRACE_READ(tok)
#define YYTRACE_SHIFT(tok)
#define YYTRACE_ACCEPT()
#define YYTRACE_REDUCE(n)
#define YYTRACE_POP(st)
#define YYTRACE_DISCARD(tok)

#endif /* !YYDEBUG */


#if YYDEBUG

#ifndef EOF
#include <stdio.h>
#endif

#ifndef YYTRACEF
#define YYTRACEF stderr
#endif /* !YYTRACEF */

static char *yyterminals[] = {
  "$EOF",
  "error",
  "IF",
  "ELSE",
  "WHILE",
  "DO",
  "FOR",
  "IN",
  "TRY",
  "CATCH",
  "FINALLY",
  "BREAK",
  "CONTINUE",
  "SWITCH",
  "CASE",
  "DEFAULT",
  "WHEN",
  "ENUM",
  "NEW",
  "VAR",
  "CONST",
  "RETURN",
  "THROW",
  "YIELD",
  "MIXIN",
  "EQEQ",
  "NEQ",
  "LE",
  "GE",
  "LGE",
  "LOR",
  "LAND",
  "INC",
  "DEC",
  "SHL",
  "SHR",
  "POW",
  "LUNDEF",
  "ADDEQ",
  "SUBEQ",
  "MULEQ",
  "DIVEQ",
  "MODEQ",
  "ANDEQ",
  "OREQ",
  "XOREQ",
  "LANDEQ",
  "LOREQ",
  "LUNDEFEQ",
  "SHLEQ",
  "SHREQ",
  "REGEQ",
  "REGNE",
  "NUL",
  "TRUE",
  "FALSE",
  "AS",
  "IMPORT",
  "USING",
  "DARROW",
  "BINEND",
  "DOTS2",
  "DOTS3",
  "REGPF",
  "NAMESPACE",
  "SYSNS",
  "SYSRET_NV",
  "CLASS",
  "SYSCLASS",
  "MODULE",
  "SYSMODULE",
  "NATIVE",
  "FUNCTION",
  "SYSFUNC",
  "PUBLIC",
  "PRIVATE",
  "PROTECTED",
  "COROUTINE",
  "NAME",
  "STR",
  "SRCFILE",
  "BIGINT",
  "INT",
  "TYPE",
  "TYPEOF",
  "LBBR",
  "RBBR",
  "LMBR",
  "RMBR",
  "DBL",
  "'='",
  "';'",
  "'-'",
  "','",
  "':'",
  "'('",
  "')'",
  "'.'",
  "'^'",
  "'?'",
  "'|'",
  "'&'",
  "'<'",
  "'>'",
  "'+'",
  "'*'",
  "'/'",
  "'%'",
  "'~'",
  "'!'",
  "'@'"
#line 119 "build/utility/kmyacc.c.parser"
  , "???"
};

static char *yyproduction[] = {
  "$start : Program",
  "Program : ToplevelStatementList",
  "ToplevelStatementList : Statement",
  "ToplevelStatementList : ToplevelStatementList Statement",
  "StatementList : Statement",
  "StatementList : StatementList Statement",
  "Statement : NonSemicolonStatement",
  "Statement : SemicolonStatement",
  "NonSemicolonStatement : BlockStatement",
  "NonSemicolonStatement : NamespaceStatement",
  "NonSemicolonStatement : EnumStatement",
  "NonSemicolonStatement : IfStatement",
  "NonSemicolonStatement : CaseStatement",
  "NonSemicolonStatement : TryCatchStatement",
  "NonSemicolonStatement : LabelStatement",
  "NonSemicolonStatement : LabelledStatement",
  "NonSemicolonStatement : IMPORT VAR NAME '=' STR ';'",
  "NonSemicolonStatement : error RBBR",
  "SemicolonStatement : ReturnStatement",
  "SemicolonStatement : YieldStatement",
  "SemicolonStatement : ThrowStatement",
  "SemicolonStatement : MixinStatement",
  "SemicolonStatement : ExpressionStatement",
  "SemicolonStatement : DefinitionStatement",
  "SemicolonStatement : BreakStatement",
  "SemicolonStatement : error ';'",
  "SemicolonStatement : error LBBR",
  "SemicolonStatement : error IF",
  "SemicolonStatement : error DO",
  "SemicolonStatement : error WHILE",
  "SemicolonStatement : error FOR",
  "SemicolonStatement : error TRY",
  "SemicolonStatement : error SWITCH",
  "SemicolonStatement : error CASE",
  "SemicolonStatement : error ENUM",
  "SemicolonStatement : error CLASS",
  "SemicolonStatement : error FUNCTION",
  "SemicolonStatement : error PRIVATE",
  "SemicolonStatement : error PUBLIC",
  "LabelledStatement : WhileStatement",
  "LabelledStatement : DoWhileStatement",
  "LabelledStatement : SwitchCaseStatement",
  "LabelledStatement : ForStatement",
  "BlockStatement : LBBR RBBR",
  "BlockStatement : LBBR StatementList RBBR",
  "NamespaceStatement : NAMESPACE NamespaceName LBBR RBBR",
  "NamespaceStatement : SYSNS NamespaceName LBBR RBBR",
  "NamespaceStatement : NAMESPACE NamespaceName LBBR StatementList RBBR",
  "NamespaceStatement : SYSNS NamespaceName LBBR StatementList RBBR",
  "NamespaceName : NAME",
  "EnumStatement : ENUM LBBR EnumList Comma_Opt RBBR",
  "EnumList : NAME",
  "EnumList : NAME '=' INT",
  "EnumList : NAME '=' '-' INT",
  "EnumList : EnumList ',' NAME",
  "EnumList : EnumList ',' NAME '=' INT",
  "EnumList : EnumList ',' NAME '=' '-' INT",
  "DefinitionStatement : VarDeclStatement",
  "DefinitionStatement : FunctionDeclStatement",
  "DefinitionStatement : ClassDeclStatement",
  "DefinitionStatement : ModuleDeclStatement",
  "LabelStatement : NAME ':' LabelledStatement",
  "IfStatement : IF '(' AssignExpressionList ')' Statement",
  "IfStatement : IF '(' AssignExpressionList ')' Statement ELSE Statement",
  "WhileStatement : WHILE '(' AssignExpressionList ')' Statement",
  "DoWhileStatement : DO Statement WHILE '(' AssignExpressionList ')' ';'",
  "SwitchCaseStatement : SWITCH '(' AssignExpressionList ')' BlockStatement",
  "CaseStatement : CASE AssignExpression ':'",
  "CaseStatement : DEFAULT ':'",
  "ForStatement : FOR '(' VAR DeclAssignExpressionList ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement",
  "ForStatement : FOR '(' AssignExpressionList ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement",
  "ForStatement : FOR '(' ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement",
  "ForStatement : FOR '(' ForInVariable IN AssignExpressionList ')' Statement",
  "ForStatement : FOR '(' VAR ForInVariable IN AssignExpressionList ')' Statement",
  "ForInVariable : VarName",
  "ForInVariable : Array",
  "TryCatchStatement : TRY BlockStatement CatchStatement_Opt FinallyStatement_Opt",
  "CatchStatement_Opt : /* empty */",
  "CatchStatement_Opt : CATCH BlockStatement",
  "CatchStatement_Opt : CATCH '(' NAME ')' BlockStatement",
  "FinallyStatement_Opt : /* empty */",
  "FinallyStatement_Opt : FINALLY BlockStatement",
  "BreakStatement : BREAK Modifier_Opt ';'",
  "BreakStatement : BREAK NAME Modifier_Opt ';'",
  "BreakStatement : CONTINUE Modifier_Opt ';'",
  "BreakStatement : CONTINUE NAME Modifier_Opt ';'",
  "ReturnStatement : RETURN GetLineNumber AssignExpressionList_Opt Modifier_Opt ';'",
  "ReturnStatement : SYSRET_NV ';'",
  "YieldStatement : YieldExpression Modifier_Opt ';'",
  "YieldExpression : YIELD AssignExpression",
  "YieldExpression : YIELD",
  "YieldExpression : AssignExpression '=' YIELD AssignExpression",
  "YieldExpression : AssignExpression '=' YIELD",
  "ThrowStatement : THROW AssignExpressionList_Opt Modifier_Opt ';'",
  "MixinStatement : MIXIN MixinModuleList ';'",
  "MixinModuleList : NAME",
  "MixinModuleList : MixinModuleList ',' NAME",
  "ExpressionStatement : AssignExpression_Opt ';'",
  "AssignExpression_Opt : /* empty */",
  "AssignExpression_Opt : AssignExpression Modifier_Opt",
  "AssignExpressionList_Opt : /* empty */",
  "AssignExpressionList_Opt : AssignExpressionObjList",
  "Modifier_Opt : /* empty */",
  "Modifier_Opt : IF '(' AssignExpressionList ')'",
  "AssignExpression : CaseWhenExpression",
  "AssignExpression : AssignExpression '=' AssignRightHandSide",
  "AssignExpression : AssignExpression SHLEQ AssignRightHandSide",
  "AssignExpression : AssignExpression SHREQ AssignRightHandSide",
  "AssignExpression : AssignExpression ADDEQ AssignRightHandSide",
  "AssignExpression : AssignExpression SUBEQ AssignRightHandSide",
  "AssignExpression : AssignExpression MULEQ AssignRightHandSide",
  "AssignExpression : AssignExpression DIVEQ AssignRightHandSide",
  "AssignExpression : AssignExpression MODEQ AssignRightHandSide",
  "AssignExpression : AssignExpression ANDEQ AssignRightHandSide",
  "AssignExpression : AssignExpression OREQ AssignRightHandSide",
  "AssignExpression : AssignExpression XOREQ AssignRightHandSide",
  "AssignExpression : AssignExpression LANDEQ AssignRightHandSide",
  "AssignExpression : AssignExpression LOREQ AssignRightHandSide",
  "AssignExpression : AssignExpression LUNDEFEQ AssignRightHandSide",
  "AssignRightHandSide : CaseWhenExpression",
  "AssignRightHandSide : ObjectSpecialSyntax",
  "ObjectSpecialSyntax : LBBR RBBR",
  "ObjectSpecialSyntax : ObjectSpecialSyntax PostIncDec",
  "ObjectSpecialSyntax : ObjectSpecialSyntax LMBR AssignExpression RMBR",
  "ObjectSpecialSyntax : ObjectSpecialSyntax '.' PropertyName",
  "ObjectSpecialSyntax : ObjectSpecialSyntax '.' TYPEOF",
  "ObjectSpecialSyntax : ObjectSpecialSyntax '(' CallArgumentList_Opts ')'",
  "ObjectSpecialSyntax : ObjectSpecialSyntax SimpleFuncCallFactor",
  "CaseWhenExpression : TernaryExpression",
  "CaseWhenExpression : CASE AssignExpression WhenClauseList CaseElseClause",
  "WhenClauseList : WhenClause",
  "WhenClauseList : WhenClauseList WhenClause",
  "WhenClause : WHEN WhenConditionRangeList Modifier_Opt Colon_Opt WhenClauseBody",
  "WhenConditionRangeList : WhenConditionRange",
  "WhenConditionRangeList : WhenConditionRangeList LOR WhenConditionRange",
  "WhenConditionRange : WhenPostfixExpression",
  "WhenConditionRange : '^' WhenPostfixExpression",
  "WhenConditionRange : Array",
  "WhenConditionRange : Object",
  "WhenConditionRange : WhenPostfixExpression DOTS2",
  "WhenConditionRange : WhenPostfixExpression DOTS2 WhenPostfixExpression",
  "WhenConditionRange : WhenPostfixExpression DOTS3",
  "WhenConditionRange : WhenPostfixExpression DOTS3 WhenPostfixExpression",
  "WhenPostfixExpression : WhenCondition",
  "WhenPostfixExpression : WhenPostfixExpression PostIncDec",
  "WhenPostfixExpression : WhenPostfixExpression LMBR AssignExpression RMBR",
  "WhenPostfixExpression : WhenPostfixExpression '.' PropertyName",
  "WhenPostfixExpression : WhenPostfixExpression '.' TYPEOF",
  "WhenPostfixExpression : WhenPostfixExpression '(' CallArgumentList_Opts ')'",
  "WhenCondition : VarName",
  "WhenCondition : '(' AssignExpression ')'",
  "WhenCondition : INT",
  "WhenCondition : DBL",
  "WhenCondition : BIGINT",
  "WhenCondition : NUL",
  "WhenCondition : TRUE",
  "WhenCondition : FALSE",
  "WhenCondition : '(' STR ')'",
  "WhenCondition : NEW Factor",
  "CaseElseClause : /* empty */",
  "CaseElseClause : ELSE Colon_Opt WhenClauseBody",
  "WhenClauseBody : BlockStatement",
  "WhenClauseBody : TernaryExpression",
  "Colon_Opt : /* empty */",
  "Colon_Opt : ':'",
  "TernaryExpression : FunctionExpression",
  "TernaryExpression : LogicalUndefExpression '?' TernaryExpression ':' TernaryExpression",
  "FunctionExpression : AnonymousFunctionDeclExpression",
  "FunctionExpression : LogicalUndefExpression",
  "LogicalUndefExpression : LogicalOrExpression",
  "LogicalUndefExpression : LogicalUndefExpression LUNDEF LogicalOrExpression",
  "LogicalOrExpression : LogicalAndExpression",
  "LogicalOrExpression : LogicalOrExpression LOR LogicalAndExpression",
  "LogicalAndExpression : BitOrExpression",
  "LogicalAndExpression : LogicalAndExpression LAND BitOrExpression",
  "BitOrExpression : BitXorExpression",
  "BitOrExpression : BitOrExpression '|' BitXorExpression",
  "BitXorExpression : BitAndExpression",
  "BitXorExpression : BitXorExpression '^' BitAndExpression",
  "BitAndExpression : CompareEqualExpression",
  "BitAndExpression : BitAndExpression '&' CompareEqualExpression",
  "CompareEqualExpression : CompareExpression",
  "CompareEqualExpression : CompareEqualExpression EQEQ CompareExpression",
  "CompareEqualExpression : CompareEqualExpression NEQ CompareExpression",
  "CompareExpression : ShiftExpression",
  "CompareExpression : CompareExpression '<' ShiftExpression",
  "CompareExpression : CompareExpression LE ShiftExpression",
  "CompareExpression : CompareExpression '>' ShiftExpression",
  "CompareExpression : CompareExpression GE ShiftExpression",
  "CompareExpression : CompareExpression LGE ShiftExpression",
  "ShiftExpression : Expression",
  "ShiftExpression : ShiftExpression SHL Expression",
  "ShiftExpression : ShiftExpression SHR Expression",
  "Expression : Term",
  "Expression : Expression '+' Term",
  "Expression : Expression '-' Term",
  "Term : Exponentiation",
  "Term : Term '*' Exponentiation",
  "Term : Term '/' Exponentiation",
  "Term : Term '%' Exponentiation",
  "Exponentiation : RegexMatch",
  "Exponentiation : Exponentiation POW RegexMatch",
  "RegexMatch : PrefixExpression",
  "RegexMatch : RegexMatch REGEQ PrefixExpression",
  "RegexMatch : RegexMatch REGNE PrefixExpression",
  "RegexMatch : PrefixExpression DOTS2",
  "RegexMatch : PrefixExpression DOTS2 PrefixExpression",
  "RegexMatch : PrefixExpression DOTS3",
  "RegexMatch : PrefixExpression DOTS3 PrefixExpression",
  "PrefixExpression : CastExpression",
  "PrefixExpression : '~' PrefixExpression",
  "PrefixExpression : '!' PrefixExpression",
  "PrefixExpression : '+' PostfixExpression",
  "PrefixExpression : '-' PostfixExpression",
  "PrefixExpression : '*' PrefixExpression",
  "PrefixExpression : INC PostfixExpression",
  "PrefixExpression : DEC PostfixExpression",
  "CastExpression : PostfixExpression",
  "CastExpression : PostfixExpression AS TypeName",
  "PostfixExpression : Factor",
  "PostfixExpression : PostfixExpression PostIncDec",
  "PostfixExpression : PostfixExpression LMBR AssignExpression RMBR",
  "PostfixExpression : PostfixExpression '.' PropertyName",
  "PostfixExpression : PostfixExpression '.' TYPEOF",
  "PostfixExpression : PostfixExpression '(' CallArgumentList_Opts ')'",
  "PostfixExpression : PostfixExpression SimpleFuncCallFactorOrBlock",
  "SimpleFuncCallFactorOrBlock : BlockStatement",
  "SimpleFuncCallFactorOrBlock : SimpleFuncCallFactor",
  "SimpleFuncCallFactor : LBBR DARROW TernaryExpression RBBR",
  "SimpleFuncCallFactor : LBBR '&' '(' ArgumentList_Opts ')' DARROW TernaryExpression RBBR",
  "SimpleFuncCallFactor : LBBR '&' '(' ArgumentList_Opts ')' RBBR",
  "SimpleFuncCallFactor : LBBR '&' '(' ArgumentList_Opts ')' ':' RBBR",
  "SimpleFuncCallFactor : LBBR '&' '(' ArgumentList_Opts ')' StatementList RBBR",
  "SimpleFuncCallFactor : LBBR '&' '(' ArgumentList_Opts ')' ':' StatementList RBBR",
  "PostIncDec : INC",
  "PostIncDec : DEC",
  "Factor : INT",
  "Factor : DBL",
  "Factor : BIGINT",
  "Factor : NUL",
  "Factor : VarName",
  "Factor : TRUE",
  "Factor : FALSE",
  "Factor : SRCFILE",
  "Factor : Array",
  "Factor : Binary",
  "Factor : Object",
  "Factor : SimpleFuncCallFactor",
  "Factor : Regex",
  "Factor : '.' PropertyName",
  "Factor : IMPORT '(' '(' STR ')' ')'",
  "Factor : '(' AssignExpression ')'",
  "Factor : '(' ObjectSpecialSyntax ')'",
  "Factor : '(' STR ')'",
  "Factor : NEW Factor",
  "Factor : '@' PropertyName",
  "Factor : '@' TYPEOF",
  "VarName : NAME",
  "VarName : TYPE",
  "PropertyName : NAME",
  "PropertyName : IF",
  "PropertyName : ELSE",
  "PropertyName : WHILE",
  "PropertyName : DO",
  "PropertyName : FOR",
  "PropertyName : IN",
  "PropertyName : TRY",
  "PropertyName : CATCH",
  "PropertyName : FINALLY",
  "PropertyName : BREAK",
  "PropertyName : CONTINUE",
  "PropertyName : SWITCH",
  "PropertyName : CASE",
  "PropertyName : WHEN",
  "PropertyName : DEFAULT",
  "PropertyName : NEW",
  "PropertyName : VAR",
  "PropertyName : CONST",
  "PropertyName : NATIVE",
  "PropertyName : FUNCTION",
  "PropertyName : SYSFUNC",
  "PropertyName : PUBLIC",
  "PropertyName : PRIVATE",
  "PropertyName : PROTECTED",
  "PropertyName : CLASS",
  "PropertyName : MODULE",
  "PropertyName : RETURN",
  "PropertyName : YIELD",
  "PropertyName : THROW",
  "PropertyName : NUL",
  "PropertyName : TRUE",
  "PropertyName : FALSE",
  "PropertyName : IMPORT",
  "PropertyName : USING",
  "PropertyName : TYPE",
  "PropertyName : SHL",
  "PropertyName : SHR",
  "PropertyName : EQEQ",
  "PropertyName : NEQ",
  "PropertyName : LE",
  "PropertyName : '<'",
  "PropertyName : GE",
  "PropertyName : '>'",
  "PropertyName : LGE",
  "PropertyName : '+'",
  "PropertyName : '-'",
  "PropertyName : '*'",
  "PropertyName : '/'",
  "PropertyName : '%'",
  "PropertyName : '&'",
  "PropertyName : '|'",
  "PropertyName : '^'",
  "PropertyName : LMBR RMBR",
  "PropertyName : '(' ')'",
  "Array : LMBR RMBR",
  "Array : LMBR ArrayItemList RMBR",
  "Binary : '<' '>'",
  "Binary : '<' BinStart ArrayItemList BINEND",
  "BinStart : /* empty */",
  "Object : LBBR KeyValueList Comma_Opt RBBR",
  "Comma_Opt : /* empty */",
  "Comma_Opt : ','",
  "ArrayItemList : ArrayItemListCore",
  "ArrayItemList : CommaList ArrayItemListCore",
  "CommaList : ','",
  "CommaList : CommaList ','",
  "ArrayItemListCore : AssignExpression",
  "ArrayItemListCore : '^' AssignExpression",
  "ArrayItemListCore : DOTS3 AssignRightHandSide",
  "ArrayItemListCore : ArrayItemListCore ','",
  "ArrayItemListCore : ArrayItemListCore ',' AssignExpression",
  "ArrayItemListCore : ArrayItemListCore ',' DOTS3 AssignRightHandSide",
  "AssignExpressionList : AssignExpression",
  "AssignExpressionList : AssignExpressionList ',' AssignExpression",
  "AssignExpressionObjList : AssignExpression",
  "AssignExpressionObjList : LBBR RBBR",
  "AssignExpressionObjList : AssignExpressionObjList ',' AssignExpression",
  "AssignExpressionObjList : AssignExpressionObjList ',' LBBR RBBR",
  "KeyValueList : KeyValue",
  "KeyValueList : KeyValueList ',' KeyValue",
  "KeyValue : '(' STR ')' ':' ValueOfKeyValue",
  "KeyValue : NAME ':' ValueOfKeyValue",
  "KeyValue : KeySpecialName ':' ValueOfKeyValue",
  "KeyValue : DOTS3 AssignRightHandSide",
  "KeyValue : VarName",
  "ValueOfKeyValue : AssignExpression",
  "ValueOfKeyValue : '^' AssignExpression",
  "ValueOfKeyValue : ObjectSpecialSyntax",
  "KeySpecialName : IF",
  "KeySpecialName : ELSE",
  "KeySpecialName : WHILE",
  "KeySpecialName : DO",
  "KeySpecialName : FOR",
  "KeySpecialName : IN",
  "KeySpecialName : TRY",
  "KeySpecialName : CATCH",
  "KeySpecialName : FINALLY",
  "KeySpecialName : BREAK",
  "KeySpecialName : CONTINUE",
  "KeySpecialName : SWITCH",
  "KeySpecialName : CASE",
  "KeySpecialName : WHEN",
  "KeySpecialName : NEW",
  "KeySpecialName : VAR",
  "KeySpecialName : CONST",
  "KeySpecialName : FUNCTION",
  "KeySpecialName : SYSFUNC",
  "KeySpecialName : PUBLIC",
  "KeySpecialName : PRIVATE",
  "KeySpecialName : PROTECTED",
  "KeySpecialName : CLASS",
  "KeySpecialName : MODULE",
  "KeySpecialName : RETURN",
  "KeySpecialName : YIELD",
  "KeySpecialName : THROW",
  "KeySpecialName : NUL",
  "KeySpecialName : TRUE",
  "KeySpecialName : FALSE",
  "KeySpecialName : IMPORT",
  "KeySpecialName : USING",
  "KeySpecialName : TYPE",
  "KeySpecialName : TYPEOF",
  "ClassFunctionSpecialName : IF",
  "ClassFunctionSpecialName : ELSE",
  "ClassFunctionSpecialName : WHILE",
  "ClassFunctionSpecialName : DO",
  "ClassFunctionSpecialName : FOR",
  "ClassFunctionSpecialName : IN",
  "ClassFunctionSpecialName : TRY",
  "ClassFunctionSpecialName : CATCH",
  "ClassFunctionSpecialName : FINALLY",
  "ClassFunctionSpecialName : BREAK",
  "ClassFunctionSpecialName : CONTINUE",
  "ClassFunctionSpecialName : SWITCH",
  "ClassFunctionSpecialName : CASE",
  "ClassFunctionSpecialName : WHEN",
  "ClassFunctionSpecialName : NEW",
  "ClassFunctionSpecialName : VAR",
  "ClassFunctionSpecialName : CONST",
  "ClassFunctionSpecialName : FUNCTION",
  "ClassFunctionSpecialName : SYSFUNC",
  "ClassFunctionSpecialName : PUBLIC",
  "ClassFunctionSpecialName : PRIVATE",
  "ClassFunctionSpecialName : PROTECTED",
  "ClassFunctionSpecialName : CLASS",
  "ClassFunctionSpecialName : MODULE",
  "ClassFunctionSpecialName : RETURN",
  "ClassFunctionSpecialName : YIELD",
  "ClassFunctionSpecialName : THROW",
  "ClassFunctionSpecialName : NUL",
  "ClassFunctionSpecialName : TRUE",
  "ClassFunctionSpecialName : FALSE",
  "ClassFunctionSpecialName : IMPORT",
  "ClassFunctionSpecialName : USING",
  "ClassFunctionSpecialName : TYPE",
  "ClassFunctionSpecialName : TYPEOF",
  "ClassFunctionSpecialName : SHL",
  "ClassFunctionSpecialName : SHR",
  "ClassFunctionSpecialName : EQEQ",
  "ClassFunctionSpecialName : NEQ",
  "ClassFunctionSpecialName : LE",
  "ClassFunctionSpecialName : '<'",
  "ClassFunctionSpecialName : GE",
  "ClassFunctionSpecialName : '>'",
  "ClassFunctionSpecialName : LGE",
  "ClassFunctionSpecialName : '+'",
  "ClassFunctionSpecialName : '-'",
  "ClassFunctionSpecialName : '*'",
  "ClassFunctionSpecialName : '/'",
  "ClassFunctionSpecialName : '%'",
  "ClassFunctionSpecialName : '&'",
  "ClassFunctionSpecialName : '|'",
  "ClassFunctionSpecialName : '^'",
  "ClassFunctionSpecialName : LMBR RMBR",
  "ClassFunctionSpecialName : '(' ')'",
  "Regex : '/' RegexStart RegexString",
  "Regex : DIVEQ RegexStart RegexString",
  "Regex : REGPF RegexString",
  "RegexStart : /* empty */",
  "RegexString : '(' STR ')'",
  "VarDeclStatement : VAR DeclAssignExpressionList ';'",
  "VarDeclStatement : CONST DeclAssignExpressionList ';'",
  "DeclAssignExpressionList : DeclAssignExpression",
  "DeclAssignExpressionList : DeclAssignExpressionList ',' DeclAssignExpression",
  "DeclAssignExpression : VarName",
  "DeclAssignExpression : VarName ':' TypeName ReturnType_Opt",
  "DeclAssignExpression : VarName '=' DeclAssignRightHandSide",
  "DeclAssignExpression : VarName ':' TypeName ReturnType_Opt '=' DeclAssignRightHandSide",
  "DeclAssignExpression : Array '=' DeclAssignRightHandSide",
  "DeclAssignExpression : Object '=' DeclAssignRightHandSide",
  "DeclAssignRightHandSide : AssignRightHandSide",
  "DeclAssignRightHandSide : DeclAssignRightHandSide '=' AssignRightHandSide",
  "FunctionDeclStatement : NormalFunctionDeclStatement",
  "FunctionDeclStatement : ClassFunctionDeclStatement",
  "NormalFunctionDeclStatement : FUNCTION NAME '(' ArgumentList_Opts ')' BlockStatement",
  "NormalFunctionDeclStatement : SYSFUNC NAME '(' ArgumentList_Opts ')' BlockStatement",
  "NormalFunctionDeclStatement : NativeKeyword NativeType_Opt NAME '(' ArgumentList_Opts ')' BlockStatement",
  "NativeKeyword : NATIVE",
  "NativeType_Opt : /* empty */",
  "NativeType_Opt : ':' TypeName",
  "AnonymousFunctionDeclExpression : FUNCTION '(' ArgumentList_Opts ')' BlockStatement",
  "AnonymousFunctionDeclExpression : SYSFUNC '(' ArgumentList_Opts ')' BlockStatement",
  "AnonymousFunctionDeclExpression : COROUTINE '(' ArgumentList_Opts ')' BlockStatement",
  "AnonymousFunctionDeclExpression : NativeKeyword NativeType_Opt '(' ArgumentList_Opts ')' BlockStatement",
  "AnonymousFunctionDeclExpression : '&' '(' ArgumentList_Opts ')' DARROW TernaryExpression",
  "AnonymousFunctionDeclExpression : '&' '(' ArgumentList_Opts ')' DARROW BlockStatement",
  "AnonymousFunctionDeclExpression : '&' BlockStatement",
  "ClassFunctionDeclStatement : PUBLIC ClassFunctionName '(' ArgumentList_Opts ')' BlockStatement",
  "ClassFunctionDeclStatement : PRIVATE ClassFunctionName '(' ArgumentList_Opts ')' BlockStatement",
  "ClassFunctionDeclStatement : PROTECTED ClassFunctionName '(' ArgumentList_Opts ')' BlockStatement",
  "ClassFunctionName : NAME",
  "ClassFunctionName : ClassFunctionSpecialName",
  "ClassDeclStatement : CLASS NAME ClassArgumentList_Opts Inherit_Opt BlockStatement",
  "ClassDeclStatement : SYSCLASS NAME ClassArgumentList_Opts Inherit_Opt BlockStatement",
  "ModuleDeclStatement : MODULE NAME BlockStatement",
  "ModuleDeclStatement : SYSMODULE NAME BlockStatement",
  "Inherit_Opt : /* empty */",
  "Inherit_Opt : ':' GetLineNumber InheritFactor ClassCallArgumentList_Opts",
  "InheritFactor : Factor",
  "InheritFactor : InheritFactor LMBR AssignExpression RMBR",
  "InheritFactor : InheritFactor '.' PropertyName",
  "InheritFactor : InheritFactor '.' TYPEOF",
  "ClassArgumentList_Opts : /* empty */",
  "ClassArgumentList_Opts : '(' ArgumentList_Opts ')'",
  "ArgumentList_Opts : /* empty */",
  "ArgumentList_Opts : ArgumentList",
  "ArgumentList : Argument",
  "ArgumentList : ArgumentList ',' Argument",
  "Argument : VarName",
  "Argument : VarName ':' TypeName ReturnType_Opt",
  "Argument : Array",
  "Argument : Object",
  "Argument : DOTS3 VarName",
  "TypeName : TYPE ArrayLevel",
  "TypeName : NATIVE",
  "TypeName : NAME ArrayLevel",
  "ArrayLevel : /* empty */",
  "ArrayLevel : LMBR RMBR",
  "ArrayLevel : ArrayLevel LMBR RMBR",
  "ReturnType_Opt : /* empty */",
  "ReturnType_Opt : '(' TypeName ')'",
  "ClassCallArgumentList_Opts : /* empty */",
  "ClassCallArgumentList_Opts : '(' CallArgumentList_Opts ')'",
  "CallArgumentList_Opts : /* empty */",
  "CallArgumentList_Opts : CallArgumentList",
  "CallArgumentList : CallArgument",
  "CallArgumentList : DOTS3 AssignRightHandSide",
  "CallArgumentList : CallArgumentList ',' CallArgument",
  "CallArgumentList : CallArgumentList ',' DOTS3 AssignRightHandSide",
  "CallArgument : AssignExpression",
  "CallArgument : ObjectSpecialSyntax",
  "CallArgument : STR",
  "GetLineNumber : /* empty */"
#line 124 "build/utility/kmyacc.c.parser"
};

/* Traditional Debug Mode */

#define YYTRACE_DCL /* empty */

#define YYTRACE_NEWSTATE(st, tok) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% State %d, Lookahead %s\n", \
		st, tok < 0 ? "--none--" : yyterminals[tok])

#define YYTRACE_READ(tok) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% Reading %s\n", yyterminals[tok])

#define YYTRACE_SHIFT(tok) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% Shift %s\n", yyterminals[tok])

#define YYTRACE_ACCEPT() \
    if (yydebug) fprintf(YYTRACEF, "%%%% Accepted.\n")

#define YYTRACE_REDUCE(n) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% Reduce by (%d) %s\n", \
		n, yyproduction[n])

#define YYTRACE_POP(st) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% Recovering, uncovers state %d\n", \
		st)

#define YYTRACE_DISCARD(tok) \
    if (yydebug) fprintf(YYTRACEF, "%%%% Discard %s\n", yyterminals[tok])

#endif /* YYDEBUG */



static char yytranslate[] = {
    0,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  109,  111,  111,  111,  107,  101,  111,
   95,   96,  105,  104,   93,   92,   97,  106,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,   94,   91,
  102,   90,  103,   99,  110,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,   98,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  100,  111,  108,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,    1,  111,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   57,   58,   59,  111,  111,  111,   60,
   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,   89,  111
#line 165 "build/utility/kmyacc.c.parser"
};

#define YYBADCH 111
#define YYMAXLEX 350
#define YYTERMS 111
#define YYNONTERMS 118

static short yyaction[] = {
  748,  749,  750,  751,  752,  753,  754,  755,  756,  757,
  758,  759,  760,  762,  761,  110,  763,  764,  765,  774,
  776,  775,  217,  785,  786,  787,  789,  791,  184,  185,
    0,  354,  783,  784,  242,   80,   81,   82,   83,   84,
   85,   86,   87,   88,   89,   90,   91,   92,    4,  138,
  107,  777,  778,  779,  113,  780,  781,   43,   47,   42,
   26,  139,   49,-32766,   28,  772,   43,  773,   42,  766,
  767,  768,  769,  770,  771,  354,  747,   38,-32766,  183,
  515,  782,  517,  516,  518,  390,  519,   94,   40,   19,
  793,  520,  521,  391,   65,  522,  799,  393,  798,  797,
  788,  790,  792,  794,  795,  796,  870,  871,  872,  873,
  874,  875,  876,  877,  878,  879,  880,  881,  882,   59,
  883, -344,  884,  885,  886,  894,  896,  895, -344,  906,
  907,  908,  910,  912,   40,-32766,-32766,-32766,  904,  905,
   97,-32766,  333,   16,  334,  523,  113,  -74,  982,   40,
  524,  335,  526,  525,   49,  311,   28,  897,  898,  899,
  312,  900,  901,  514,  505,-32766,  333,   16,  334,  513,
  181,  892,   98,  893,  123,  335,  887,  888,  889,  890,
  891,  292,  958,  131,  132,  133,  266,  902,  903,  722,
  723,  370,  389,  114, -102,   40,  914,  740,   38,  371,
   99,   50,  920,   29,  919,  918,  909,  911,  913,  915,
  916,  917,  162,  375,  837,  376,   10,  377,  841,  302,
  843,  844,  224,  225,  378,  105,  336,  849,  337,  157,
  221,  222,  303,   53,   60,  284,  120,  -75,  101,  415,
   95,  140,  141,  142,  109,   38,  119,   38,  555,   68,
-32766,  745,   48,  228,   27,  999,  746,  999,  134,  135,
  112,   38,  226,   38,  379,  380,  381,  241,  257,  867,
  119,  313,  540,   78,-32766,  286,  287,  338,  382,  340,
  383,  342,  465,  258,  259,   34,   35,   36,  401,  384,
  543,    4,-32766,  107,  385,  869,  293,  531,   40,   37,
  478,   47,  -98,   26,  464,   79,   58, -373, -374, -102,
   40,  158,  240,  836,  837,  838,  839,  840,  841,  842,
  843,  844,  845,  846,  847,  848,   79,  849,   40,  850,
  851,  852,  860,  862,  861,  181,  813,  315,   38,  363,
   43,  106,   42,  582,  124,  405,  642,  643,  644,   40,
  181,  112,  802,  129,  130,  136,  137,  812,  147,  148,
  149,  150,  106,  182,  863,  864,  865,  125,  866,  867,
  119,  745,  117,   78,  641,  639,  746,  143,  858,  298,
  859,  299,  640,  853,  854,  855,  856,  857,   62,  399,
  805,  408,  544,  584,  385,  869,  537,  162,  332,  541,
  333,   16,  334,  583,  283,  300,  400,  237,  238,  335,
  102,  336,  401,  337,  436,  218,  219,  484,   63,  103,
  284,   79,  292,  293,  466,  461,  431,  162,  332,  406,
  333,   16,  334,  403,  283,  369,  368,  237,  238,  335,
  102,  336,  301,  337,   40,  218,  219,  484,   63,  103,
  284,  468,  812,  244,  444,  119,   39,  106,  744,  717,
  286,  287,  338,  339,  340,  341,  342,  711,  245,  246,
   31,   32,   33,  635,  344,  613,  969,  455,  295,    7,
   38,   61,  531,  244,   40,  118,   37,  -98,  266,    6,
  286,  287,  338,  339,  340,  341,  342,  240,  245,  246,
   31,   32,   33,    5,  344,  538,  807,  716,  825,  823,
  609, -376,  718,  800,  470,  126,  803,  -98,  162,  332,
    8,  333,   16,  334,  921,  283,  611,  633,  237,  238,
  335,  102,  336,  967,  337,  986,  218,  219,  484,   63,
  103,  284,  985,  709,  576,  108,   66,  282,  278,  162,
  332,   67,  333,   16,  334,  100,  283,   73,  443,  237,
  238,  335,  102,  336,  929,  337,  928,  218,  219,  484,
   63,  103,  284,  572,  244,  571,  122,  585,  575,   74,
   72,  286,  287,  338,  339,  340,  341,  342,   71,  245,
  246,   31,   32,   33,   70,  344,  573,  581,  504,  553,
  570,  574,   69,  718,  804,  244,   44,  210,  -98,  437,
  198,    8,  286,  287,  338,  339,  340,  341,  342,  223,
  245,  246,   31,   32,   33,  111,  344,   52,  197, -377,
 -375, -372,   -1,  162,  332,   41,  333,   16,  334,  -98,
  283,   54, -351,  237,  238,  335,  102,  336,   55,  337,
   56,  218,  219,  484,   63,  103,  284,  121,  220,  227,
  229,  162,  332,  652,  333,   16,  334,  556,  283,  487,
 -380,  237,  238,  335,  102,  336,   96,  337,   93,  218,
  219,  484,   63,  103,  284,   77,   76,  199,  206,  244,
  435,  196,   75,  200,  407,  365,  286,  287,  338,  339,
  340,  341,  342,  364,  245,  246,   31,   32,   33,  230,
  344,  209,  208,  207,  205,  204,  203,  244,  202,  201,
   51,    0,   18,  -98,  286,  287,  338,  339,  340,  341,
  342,   20,  245,  246,   31,   32,   33,  638,  344,   21,
  314,  472,  591,  739,   17,  990,  533,  988,  636,  162,
  332,  -98,  333,   16,  334,  738,  283,  645,  614,  237,
  238,  335,  102,  336,  971,  337,  712,  218,  219,  484,
   63,  103,  284,  927,  801,  741,  922,  162,  332,  469,
  333,   16,  334,  462,  283,  454,  451,  237,  238,  335,
  102,  336,  331,  337,  330,  218,  219,  484,   63,  103,
  284,  329,  328,  327,  326,  244,  325,  323,  321,  320,
  319,   24,  286,  287,  338,  339,  340,  341,  342,   23,
  245,  246,   31,   32,   33,   22,  344,    3,    2,  128,
    0,  127,    0,  244,  532,    0,    0,    0,    0,  -98,
  286,  287,  338,  339,  340,  341,  342,    0,  245,  246,
   31,   32,   33,    0,  344,    0,    0,    0,    0,    0,
    0,    0,  721,    0,    0,  162,  332,  -98,  333,   16,
  334,    0,  283,    0,    0,  237,  238,  335,  102,  336,
    0,  337,    0,  218,  219,  484,   63,  103,  284,    0,
    0,    0,    0,  162,  332,    0,  333,   16,  334,    0,
  283,    0,    0,  237,  238,  335,  102,  336,    0,  337,
    0,  218,  219,  484,   63,  103,  284,    0,    0,    0,
    0,  244,    0,    0,    0,    0,    0,    0,  286,  287,
  338,  339,  340,  341,  342,    0,  245,  246,   31,   32,
   33,    0,  344,    0,    0,    0,    0,    0,    0,  244,
  720,    0,    0,    0,    0,  -98,  286,  287,  338,  339,
  340,  341,  342,    0,  245,  246,   31,   32,   33,    0,
  344,    0,    0,    0,    0,    0,    0,    0,  719,    0,
    0,  162,  332,  -98,  333,   16,  334,    0,  283,    0,
    0,  237,  238,  335,  102,  336,    0,  337,    0,  218,
  219,  484,   63,  103,  284,    0,    0,    0,    0,  162,
  332,    0,  333,   16,  334,    0,  283,    0,    0,  237,
  238,  335,  102,  336,    0,  337,    0,  218,  219,  484,
   63,  103,  284,    0,    0,    0,    0,  244,    0,    0,
    0,    0,    0,    0,  286,  287,  338,  339,  340,  341,
  342,    0,  245,  246,   31,   32,   33,    0,  344,    0,
    0,    0,    0,    0,    0,  244,  536,    0,    0,    0,
    0,  -98,  286,  287,  338,  339,  340,  341,  342,    0,
  245,  246,   31,   32,   33,    0,  344,    0,    0,    0,
    0,    0,    0,    0,  535,    0,    0,  162,  332,  -98,
  333,   16,  334,    0,  283,    0,    0,  237,  238,  335,
  102,  336,    0,  337,    0,  218,  219,  484,   63,  103,
  284,    0,    0,    0,    0,  162,  332,    0,  333,   16,
  334,    0,  283,    0,    0,  237,  238,  335,  102,  336,
    0,  337,    0,  218,  219,  484,   63,  103,  284,    0,
    0,    0,    0,  244,    0,    0,    0,    0,    0,    0,
  286,  287,  338,  339,  340,  341,  342,    0,  245,  246,
   31,   32,   33,    0,  344,    0,    0,    0,    0,    0,
    0,  244,  534,    0,    0,    0,    0,  -98,  286,  287,
  338,  339,  340,  341,  342,    0,  245,  246,   31,   32,
   33,  104,  344,    0,    0,  156,    0,    0,    0,    0,
  531,    0,    0,    0,    0,  -98,    0,    0,    0,  151,
  152,    0,    0,    0,    0,    0,    0,    0,  485,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  727,  729,  730,    0,  357,    0,    0,    0,    0,    0,
  285,    0,    0,    0,    0,    0,    0,    0,  945,  358,
  359,    0,    0,    0,  343,  745,    0,  731,  726,  724,
  746,    0,    1,    0,   42,    0,  725,    0,    0,  153,
    0,    0,   57,    0,   30,    0,    0,    0,  239,  288,
    0,  154,  144,  486,    0,  145,  146,   25,  162,  332,
    0,  333,   16,  334,    0,  283,    0,    0,  237,  238,
  335,  102,  336,    0,  337,    0,  218,  219,  484,   63,
  103,  284,-32766,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
-32766,-32766,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  244,    0,    0,    0,    0,    0,
    0,  286,  287,  338,  339,  340,  341,  342,    0,  245,
  246,   31,   32,   33,    0,  344,    0,    0,    0,-32766,
-32766,-32766,    0,    0,    0,-32766,    0,    0,  -98,    0,
    0,    0,    0,   40,    0,    0,    0,    0,    0,    0,
-32766,    0,    0,    0,    0,    0,    0,    0,    0,-32766,
    0,    0,-32766,-32766,    0,    0,-32766,-32766
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1418

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   23,   18,   19,   20,   21,
   22,   23,   19,   25,   26,   27,   28,   29,   61,   62,
    0,    2,   34,   35,   62,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   85,   92,
   87,   53,   54,   55,   87,   57,   58,   85,   95,   87,
   97,  104,   95,   14,   97,   67,   85,   69,   87,   71,
   72,   73,   74,   75,   76,    2,   78,   85,   14,   98,
    2,   83,    4,    5,    6,   87,    8,   90,   85,    3,
   92,   13,   14,   95,   91,   17,   98,    4,  100,  101,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   90,
   16,   86,   18,   19,   20,   21,   22,   23,   93,   25,
   26,   27,   28,   29,   85,   71,   72,   73,   34,   35,
    7,   77,    4,    5,    6,   67,   87,    7,   71,   85,
   72,   13,   74,   75,   95,   78,   97,   53,   54,   55,
   83,   57,   58,   85,   86,  101,    4,    5,    6,   91,
   16,   67,   62,   69,   37,   13,   72,   73,   74,   75,
   76,   78,   78,   27,   28,   29,   85,   83,   84,   32,
   33,   87,   79,   87,   91,   85,   92,   96,   85,   95,
    7,   95,   98,   97,  100,  101,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   99,    7,   62,   79,
   62,  105,  106,  107,   87,   85,   59,   85,   94,   90,
   59,   78,   95,   94,   97,   79,   83,   79,  102,  103,
   98,   85,   56,   85,   53,   54,   55,    9,   57,   58,
   59,   10,   82,   62,   14,   64,   65,   66,   67,   68,
   69,   70,   92,   72,   73,   74,   75,   76,  101,   78,
   82,   85,  101,   87,   83,   84,   78,   86,   85,   85,
   92,   95,   91,   97,   79,   62,   95,   94,   94,   91,
   85,   18,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   62,   16,   85,   18,
   19,   20,   21,   22,   23,   16,   93,    3,   85,   19,
   85,   98,   87,   91,   30,   93,   53,   54,   55,   85,
   16,   98,   88,   25,   26,   34,   35,   93,   51,   52,
   61,   62,   98,   30,   53,   54,   55,   31,   57,   58,
   59,   78,   59,   62,   81,   82,   83,   36,   67,   78,
   69,   78,   89,   72,   73,   74,   75,   76,   95,   78,
   60,   79,   82,   78,   83,   84,   78,    1,    2,   82,
    4,    5,    6,   78,    8,   78,   95,   11,   12,   13,
   14,   15,  101,   17,   79,   19,   20,   21,   22,   23,
   24,   62,   78,   78,   78,   78,   78,    1,    2,   78,
    4,    5,    6,   78,    8,   78,   78,   11,   12,   13,
   14,   15,   78,   17,   85,   19,   20,   21,   22,   23,
   24,   79,   93,   57,   79,   59,   85,   98,   84,   86,
   64,   65,   66,   67,   68,   69,   70,   84,   72,   73,
   74,   75,   76,   84,   78,   84,   84,   87,   85,   85,
   85,   93,   86,   57,   85,   59,   85,   91,   85,   85,
   64,   65,   66,   67,   68,   69,   70,  101,   72,   73,
   74,   75,   76,   85,   78,   86,   86,   86,   86,   86,
   86,   94,   86,   88,   87,  100,   88,   91,    1,    2,
   94,    4,    5,    6,   88,    8,   88,   88,   11,   12,
   13,   14,   15,   88,   17,   88,   19,   20,   21,   22,
   23,   24,   88,   88,   91,   93,   90,   90,   90,    1,
    2,   90,    4,    5,    6,   90,    8,   90,   90,   11,
   12,   13,   14,   15,   91,   17,   91,   19,   20,   21,
   22,   23,   24,   91,   57,   91,   59,   91,   91,   91,
   91,   64,   65,   66,   67,   68,   69,   70,   91,   72,
   73,   74,   75,   76,   91,   78,   91,   91,   91,   91,
   91,   91,   91,   86,  103,   57,   93,   93,   91,   93,
   95,   94,   64,   65,   66,   67,   68,   69,   70,   93,
   72,   73,   74,   75,   76,   93,   78,   93,   95,   94,
   94,   94,    0,    1,    2,   94,    4,    5,    6,   91,
    8,   94,   94,   11,   12,   13,   14,   15,   94,   17,
   94,   19,   20,   21,   22,   23,   24,   94,   94,   94,
   94,    1,    2,   94,    4,    5,    6,   94,    8,   94,
   94,   11,   12,   13,   14,   15,   95,   17,   95,   19,
   20,   21,   22,   23,   24,   95,   95,   95,   95,   57,
   95,   95,   95,   95,   95,   95,   64,   65,   66,   67,
   68,   69,   70,   95,   72,   73,   74,   75,   76,   95,
   78,   95,   95,   95,   95,   95,   95,   57,   95,   95,
   95,   -1,   96,   91,   64,   65,   66,   67,   68,   69,
   70,   96,   72,   73,   74,   75,   76,   96,   78,   96,
   96,   96,   96,   96,   96,   96,   86,   96,   96,    1,
    2,   91,    4,    5,    6,   96,    8,   96,   96,   11,
   12,   13,   14,   15,   96,   17,   96,   19,   20,   21,
   22,   23,   24,   96,   96,   96,   96,    1,    2,   96,
    4,    5,    6,   96,    8,   96,   96,   11,   12,   13,
   14,   15,   96,   17,   96,   19,   20,   21,   22,   23,
   24,   96,   96,   96,   96,   57,   96,   96,   96,   96,
   96,   96,   64,   65,   66,   67,   68,   69,   70,   96,
   72,   73,   74,   75,   76,   96,   78,   96,   96,  101,
   -1,   98,   -1,   57,   86,   -1,   -1,   -1,   -1,   91,
   64,   65,   66,   67,   68,   69,   70,   -1,   72,   73,
   74,   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   86,   -1,   -1,    1,    2,   91,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   -1,   17,   -1,   19,   20,   21,   22,   23,   24,   -1,
   -1,   -1,   -1,    1,    2,   -1,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   -1,   17,
   -1,   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,
   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,   64,   65,
   66,   67,   68,   69,   70,   -1,   72,   73,   74,   75,
   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   57,
   86,   -1,   -1,   -1,   -1,   91,   64,   65,   66,   67,
   68,   69,   70,   -1,   72,   73,   74,   75,   76,   -1,
   78,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   86,   -1,
   -1,    1,    2,   91,    4,    5,    6,   -1,    8,   -1,
   -1,   11,   12,   13,   14,   15,   -1,   17,   -1,   19,
   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,    1,
    2,   -1,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   -1,   17,   -1,   19,   20,   21,
   22,   23,   24,   -1,   -1,   -1,   -1,   57,   -1,   -1,
   -1,   -1,   -1,   -1,   64,   65,   66,   67,   68,   69,
   70,   -1,   72,   73,   74,   75,   76,   -1,   78,   -1,
   -1,   -1,   -1,   -1,   -1,   57,   86,   -1,   -1,   -1,
   -1,   91,   64,   65,   66,   67,   68,   69,   70,   -1,
   72,   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   86,   -1,   -1,    1,    2,   91,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   -1,   17,   -1,   19,   20,   21,   22,   23,
   24,   -1,   -1,   -1,   -1,    1,    2,   -1,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   -1,   17,   -1,   19,   20,   21,   22,   23,   24,   -1,
   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,
   64,   65,   66,   67,   68,   69,   70,   -1,   72,   73,
   74,   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,
   -1,   57,   86,   -1,   -1,   -1,   -1,   91,   64,   65,
   66,   67,   68,   69,   70,   -1,   72,   73,   74,   75,
   76,   14,   78,   -1,   -1,   18,   -1,   -1,   -1,   -1,
   86,   -1,   -1,   -1,   -1,   91,   -1,   -1,   -1,   32,
   33,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   41,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   53,   54,   55,   -1,   57,   -1,   -1,   -1,   -1,   -1,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   71,   72,
   73,   -1,   -1,   -1,   77,   78,   -1,   80,   81,   82,
   83,   -1,   85,   -1,   87,   -1,   89,   -1,   -1,   92,
   -1,   -1,   95,   -1,   97,   -1,   -1,   -1,  101,  102,
   -1,  104,  105,  106,   -1,  108,  109,  110,    1,    2,
   -1,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   -1,   17,   -1,   19,   20,   21,   22,
   23,   24,   14,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   32,   33,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,
   -1,   64,   65,   66,   67,   68,   69,   70,   -1,   72,
   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,   71,
   72,   73,   -1,   -1,   -1,   77,   -1,   -1,   91,   -1,
   -1,   -1,   -1,   85,   -1,   -1,   -1,   -1,   -1,   -1,
   92,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  101,
   -1,   -1,  104,  105,   -1,   -1,  108,  109
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1297,  211,  426,  517,  396, 1124,  660, 1096,  892,  632,
  548,  748, 1008,  980,  864,  776, 1297, 1297, 1297, 1297,
 1297, 1297, 1297, 1297, 1297,  374,  383,  391,  389,  392,
   -2,  104,  104,  104,  104,  104,  104,  423,  424,  422,
  311,  162,  264,  191,  191,  359,  243,  178,  178,  178,
  178,    3,  176,  214,  253,  253,  253,  113,  160,   -8,
  213,  110,  225,  401,  401,  401,  395,  395,  395,  401,
  401,  401,  401,  395,  401,  399,  399,  399,  395,  395,
  395,  395,  395,  395,  395,  395,  395,  395,  395,  395,
  395,  395,  395,  399,  395,  395,  399,  399,  395,  399,
  395,  395,  399,  399,  399,  399,  399,  399,  371,  399,
  399,  399,  399,  399,  399,  260,  260,  260,  260,   49,
   49,   49,   49,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64, 1308, 1308, 1308, 1308, 1308, 1308, 1308, 1308,  154,
  319,   29,   78,  647,  455,  438,  641,  439,  445,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,  -19,  -19,  293,  293,  293,  206,  101,  -33,  -37,
  -37,  -37,  -37,  403,  403,  403,  -28,  -28,  -28,  -28,
  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,
  -28,   59,   59,   59,  156,  156,  156,  255,  255,  255,
  138,  255,  255,  255,  103,  218,   77,   77,   77,   77,
   77,  106,  136,  136,  136,  140,  334,  344,  345,  592,
  593,  595,  173,  333,  320,  358,  357,  137,  328,  321,
  -43,  307,  299,  159,  475,  473,  252,  320,  358,  357,
   35,  348,  648,  626,  511,  644,  187,  328,  321,  321,
  321,  321,  321,  -43,  -43,  307,  503,  646,  190,  645,
  635,  643,  208,  418,  325,  600,  318,  318,  501,   73,
  565,  258,   73,   73,  565,  355,   73,  600,  598,  598,
  418,  418,  418,  537,  513,  600,  261,  516,   73,  575,
  575,  390,  390,  418,  418,  569,  614,  418,  418,  418,
  418,  418,  569,  418,  614,  418,  418,  418,  418,  418,
  418,  418,  597,  591,  625,  590,  573,  393,  487,  301,
  303,  327,  364,  515,  564,   30,  486,  314,  336,  415,
  733,  728,  341,   93,  583,  509,  482,  608,  596,  533,
  456,  461,  452,  351,  599,  312,  404,  394,  624,  623,
  436,  680,  621,  620,  619,  597,  591,  625,  590,  536,
  417,  535,  301,  327,  541,  576,  547,  428,  388,  679,
  425,  678,  453,  581,  133,  230,  140,  484,  505,  554,
  335,  617,  618,  458,  506,  315,  468,  375,  677,  566,
  714,  514,  713,  712,  421,  690,  420,  388,  689,  330,
  314,  563,  336,  415,  733,  728,  341,  341,  341,  670,
  534,  616,  193,  456,  497,  347,  687,  346,  419,  465,
  465,  465,  510,  372,  683,  668,  711,  710,  708,  707,
  706,  556,  732,  662,  313,  454,  427,  427,  705,   86,
  489,  698,  556,  731,  661,  317,  457,  467,  507,  659,
  447,  696,  508,  488,  729,  652,  651,  723,  310,  465,
  373,  715,  373,  649,    0,    0,    0,    0, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187,   -2,   -2,   -2,   -2,   -2,    0,    0,
    0,    0,    0,    0,    0,  311,  311,  311,    0, 1187,
 1187,  311,  311, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187,   -3,   -3,   -3,
    0,   -3,   -3,   -3,   -3,   -3,   -3,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  293,
  293,    0,    0,    0,  157,  157,  157,  157,  157,  157,
  157,  157,  157,  157,  173,  173,  173,  173,  173,  173,
  173,  173,  173,  173,  173,  173,  173,  173,  173,  157,
  157,  157,    0,    0,    0,  173,  173,  173,    0,  173,
  173,  173,   73,   73,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  159,    0,   73,   73,  418,  418,  418,
    0,   73,  608,  596,  533,    0,    0,    0,    0,    0,
    0,    0,  526,  526,    0,  608,  596,  533,    0,  618,
  532,  532,  532,  532,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  526,  532,    0,  532,  532,  532
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 282

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  367,  368,  369,32767,32767,32767,
32767,32767,32767,32767,  321,32767,32767,  503,  503,  503,
  503,32767,32767,  100,32767,32767,32767,32767,32767,32767,
   90,  329,32767,  100,  100,  100,32767,32767,32767,  100,
  100,  100,  100,32767,  100,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   90,32767,  360,32767,32767,32767,32767,
   92,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  205,
  207,32767,32767,32767,32767,32767,32767,  362,32767,32767,
32767,  102,32767,32767,32767,32767,32767,32767,32767,  334,
   89,  326,  332,  327,  509,  336,  345,  330,   91,  333,
  346,32767,32767,32767,  139,  141,  217,32767,  135,  215,
  216,  213,  212,  120,  510,  347,  484,  484,  484,  484,
  484,  484,  484,  484,  484,  484,  484,  484,  484,  484,
32767,  136,  140,  142,  181,  182,  183,32767,32767,32767,
32767,  363,  364,32767,  357,  358,32767,32767,32767,32767,
32767,  501,  193,  195,  194,  444,  159,  102,  102,32767,
32767,32767,32767,  102,32767,32767,32767,  168,  179,  184,
  190,  200,  202,  444,32767,32767,32767,  378,  365,  366,
  240,32767,32767,32767,32767,32767,32767,  180,  186,  188,
  189,  185,  187,  191,  192,  201,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  318,  102,
  458,   77,  102,  102,  458,32767,  102,32767,  482,  482,
32767,32767,  354,  512,  320,32767,   80,  320,  102,  476,
  476,  496,  496,32767,32767,  163,  499,32767,32767,32767,
32767,32767,  163,32767,  499,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  257,32767,32767,  169,  171,  173,
  175,  177,  196,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  101,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  348,  350,  352,  359,  239,
  241,  242,  370,  371,  257,  258,32767,32767,  322,32767,
32767,32767,32767,32767,32767,  244,  240,32767,32767,  257,
32767,32767,32767,   51,32767,32767,32767,32767,32767,  488,
32767,  485,32767,32767,32767,32767,32767,  323,32767,32767,
  170,32767,  172,  174,  176,  178,  197,  198,  199,32767,
  504,32767,32767,   75,32767,32767,32767,  321,32767,  448,
  449,  446,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  253,32767,32767,32767,32767,  495,  493,32767,   62,
32767,32767,32767,32767,32767,32767,   54,  445,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  447,
  464,32767,32767,32767,  512,  438,  438,  512
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  176,  171,  827,  260,  171,  171,  174,  174,  174,  174,
  172,  174,  169,  176,  176,  176,  163,  163,  419,  170,
  177,  166,  169,  169,  169,  453,  475,  483,  169,  169,
  169,  169,  417,  169,  172,  172,  172,  440,  441,  832,
  832,  832,  832,  479,  995,  832,  832,  649,  649,  953,
  953,  549,  172,  396,  620,  172,  172,  830,  172,  828,
  420,  159,  170,  160,  159,  173,  164,  175,  165,  178,
  179,  180,  167,  168,  607,  710,  612,  634,  968,  737,
  422,  607,  607,  607,  924,   14,   14,  423,  607,   12,
   13,   15,  923,  607,  607,  607,  607,  607,  607,  607,
  607,  607,  607,  607,  607,  607,  607,  607,  424,  607,
  607,  425,  276,  607,  255,  607,  607,  255,  714,  215,
  216,  714,  714,  714,  714,  290,  290,  290,  290,  290,
  290,  290,  290,  290,  290,  290,  290,  290,  290,  290,
  290,  290,  290,  290,  290,  290,  290,  290,  290,  290,
  395,  412,  413,  418,  445,  446,  447,  448,  449,  450,
  452,  458,  463,  471,  189,  190,  191,  192,  610,  632,
  267,  954,  954,  566,  610,  610,  610,  268,  269,  270,
  271,  272,  275,  637,  637,  637,  637,  637,  966,  742,
  742,  646,  632,  632,  632,  426,  427,  428,  409,  409,
  409,  409,  409,  409,  409,  409,  409,  409,  409,  409,
  409,  409,  409,  373,  374,  291,  373,  374,  622,  235,
  253,  253,  975,  253,  253,  253,  947,  316,  324,  476,
  549,  432,  962,  963,  291,  650,  650,  952,  480,  414,
  421,  654,  482,  931,  980,  569,  554,  273,  274,  960,
  961,  948,  949,  950,  619,  942,  367,  943,  955,  956,
  957,  951,  567,  944,  715,  615,  402,  715,  715,  715,
  715,  615,  615,  615,  233,  234,  195,  211,  212,  213,
  625,  625,  194,  194,  194,  194,  310,  194,  318,  195,
  195,  195,  187,  187,  305,  978,  978,  978,  978,  978,
  978,  978,  978,  978,  978,  978,  978,  978,  978,  978,
  626,  626,  438,  457,  155,  116,  433,  360,  360,  977,
  360,  360,  360,    0,    0,  979,  979,  979,  979,  979,
  979,  979,  979,  979,  979,  979,  979,  979,  979,  979,
  593,  587,    0,    0,    0,    0,  361,  361,  361,    0,
  361,  361,  361,    0,    0,    0,    0,    0,    0,  831,
  816,  596,  597,  598,  599,  600,  601,  602,  603,  604,
  605,  606,  594,  595,  490,  593,  994,    0,    0,  819,
    0,  939,  996,  491,  353,  493,  493,  493,  493,  493,
  353,  459,  552,  551,  560,  561,  559,  558,  557,    0,
    0,    0,    0,    0,    0,  356,  262,  263,  265,  308,
  434,    0,    0,    0,  460,  473,  474,  477,  356,  481,
    0,    0,    0,  322,  277,    0,    0,  279,  280,    0,
  281,  702,  698,  699,  691,  692,  694,  696,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  392,
    0,    0,  397,  398,    0,    0,  404,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  442
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 489

static char yygcheck[] = {
   35,   35,   71,   73,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   65,   35,
   35,   35,   35,   35,   35,   97,   97,   97,   35,   35,
   35,   35,   66,   35,   35,   35,   35,   80,   80,   73,
   73,   73,   73,   80,   99,   73,   73,    7,    7,    7,
    7,   33,   35,   73,  113,   35,   35,   72,   35,   72,
   42,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,  105,   57,   57,   57,   57,   57,
   43,  105,  105,  105,   64,    3,    3,   44,  105,    3,
    3,    3,   64,  105,  105,  105,  105,  105,  105,  105,
  105,  105,  105,  105,  105,  105,  105,  105,   45,  105,
  105,   46,   78,  105,   78,  105,  105,   78,    7,   48,
   48,    7,    7,    7,    7,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   61,   92,   92,   92,   92,   92,   92,   92,   92,   92,
   92,   92,   92,   92,   56,   56,   56,   56,   58,   58,
   47,    7,    7,    7,   58,   58,   58,   49,   49,   49,
   49,   49,   53,   73,   73,   73,   73,   73,   59,   59,
   59,   59,   58,   58,   58,   52,   52,   52,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   75,   75,    7,   75,   75,  109,   73,
   73,   73,   94,   73,   73,   73,  101,  101,  101,  101,
   33,   19,    7,    7,    7,   39,   39,   39,   39,   39,
   39,   39,   39,   79,   73,    7,    7,   50,   50,    7,
    7,    7,    7,    7,  107,    7,    9,    7,    7,    7,
    7,    7,    7,    7,   96,   96,  100,   96,   96,   96,
   96,   96,   96,   96,   51,   51,   37,  110,  110,  110,
   61,   61,   37,   37,   37,   37,   90,   37,   88,   37,
   37,   37,   37,   37,  117,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   61,
   62,   62,  114,  102,  104,  115,   61,   61,   61,  103,
   61,   61,   61,   -1,   -1,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   36,   30,   -1,   -1,   -1,   -1,   62,   62,   62,   -1,
   62,   62,   62,   -1,   -1,   -1,   -1,   -1,   -1,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,    4,   36,   36,   -1,   -1,   36,
   -1,   36,   36,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,   -1,
   -1,   -1,   -1,   -1,   -1,   30,   68,   68,   68,   38,
   38,   -1,   -1,   -1,   38,   38,   38,   38,   30,   38,
   -1,   -1,   -1,   30,   68,   -1,   -1,   68,   68,   -1,
   68,   54,   54,   54,   54,   54,   54,   54,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   30,
   -1,   -1,   30,   30,   -1,   -1,   30,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,   83,  374,    0,    0,  -68,    0,  -31,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   14,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  180,    0,    0,   10,    0,  -41,  281,  235,  345,  120,
    0,    0,  -63,  -44,  -38,  -18,  -16,   42,  -10,   46,
  111,  136,   55,   39,  287,    0,   13,   49,  -19,   33,
    0,   99,  129,    0, -213,  -27,  -14,    0,  331,    0,
    0,  -42,    3,    2,    0,  181,    0,    0, -105,   20,
  -30,  125,    0,    0,    0,    0,    0,    0,  -22,    0,
  -13,    0,  -46,    0,   12,    0,   78,  -23,    0,   -8,
  -28,   -1,    1,   -5, -173,   15,    0,   18,    0,   36,
   94,    0,    0,  -62,    5,   -7,    0, -192
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  345,    9,   11,  492,  495,  494,  496,  497,  366,
  498,  307,  511,  499,  527,  528,  529,  500,  530,  394,
  501,  306,  564,  506,  507,  289,  508,  509,  256,  510,
  355,  512,  502,  503,  346,  161,  938,  193,  296,  616,
  653,  247,  347,  348,  349,  350,  351,  248,  214,  249,
  250,  232,  352,  251,  252,  697,  186,  743,  708,  707,
  733,  732,  734,  736,  925,  387,  388,   46,  264,  362,
  304,  826,  829,  728,  386,  372,  959,  545,  254,  930,
  439,  294,  546,  940,  655,  941,  547,  548,  317,  231,
  309,  965,  410,  411,  974,  713,  735,  429,  430,  993,
  261,  706,  456,  467,   64,  592,  236,  618,  243,  621,
  188,  631,  617,  648,  416,  115,   45,  297
#line 205 "build/utility/kmyacc.c.parser"
};

static char yylhs[] = {
    0,    1,    2,    2,    3,    3,    4,    4,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,   33,
   33,   33,   33,    7,    7,    8,    8,    8,    8,    9,
   10,   11,   11,   11,   11,   11,   11,   12,   12,   12,
   12,   32,   13,   13,   14,   15,   16,   17,   17,   18,
   18,   18,   18,   18,   19,   19,   20,   21,   21,   21,
   22,   22,   31,   31,   31,   31,   23,   23,   24,   25,
   25,   25,   25,   26,   27,   28,   28,   29,   34,   34,
   38,   38,   30,   30,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   36,
   36,   37,   37,   37,   37,   37,   37,   37,  105,  105,
  106,  106,  107,  108,  108,  109,  109,  109,  109,  109,
  109,  109,  109,  110,  110,  110,  110,  110,  110,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  112,
  112,  113,  113,  115,  115,   39,   39,   40,   40,   41,
   41,   42,   42,   43,   43,   44,   44,   45,   45,   46,
   46,   47,   47,   47,   48,   48,   48,   48,   48,   48,
   49,   49,   49,   50,   50,   50,   51,   51,   51,   51,
   52,   52,   53,   53,   53,   53,   53,   53,   53,   54,
   54,   54,   54,   54,   54,   54,   54,   55,   55,   56,
   56,   56,   56,   56,   56,   56,   95,   95,   96,   96,
   96,   96,   96,   96,   58,   58,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   73,   73,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   61,   61,   60,   60,  116,   62,
  114,  114,   65,   65,   67,   67,   66,   66,   66,   66,
   66,   66,   68,   68,   69,   69,   69,   69,   70,   70,
   71,   71,   71,   71,   71,   72,   72,   72,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   63,   63,   63,  117,   64,
   77,   77,   78,   78,   79,   79,   79,   79,   79,   79,
   80,   80,   82,   82,   83,   83,   83,   81,  100,  100,
   84,   84,   84,   84,   84,   84,   84,   85,   85,   85,
   75,   75,   86,   86,   87,   87,   88,   88,   89,   89,
   89,   89,   90,   90,   92,   92,   93,   93,   94,   94,
   94,   94,   94,  101,  101,  101,  102,  102,  102,  103,
  103,   91,   91,   97,   97,   98,   98,   98,   98,   99,
   99,   99,  104
#line 209 "build/utility/kmyacc.c.parser"
};

static char yylen[] = {
    1,    1,    1,    2,    1,    2,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    6,    2,    1,    1,
    1,    1,    1,    1,    1,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    1,
    1,    1,    1,    2,    3,    4,    4,    5,    5,    1,
    5,    1,    3,    4,    3,    5,    6,    1,    1,    1,
    1,    3,    5,    7,    5,    7,    5,    3,    2,   10,
    9,    8,    7,    8,    1,    1,    4,    0,    2,    5,
    0,    2,    3,    4,    3,    4,    5,    2,    3,    2,
    1,    4,    3,    4,    3,    1,    3,    2,    0,    2,
    0,    1,    0,    4,    1,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    1,
    1,    2,    2,    4,    3,    3,    4,    2,    1,    4,
    1,    2,    5,    1,    3,    1,    2,    1,    1,    2,
    3,    2,    3,    1,    2,    4,    3,    3,    4,    1,
    3,    1,    1,    1,    1,    1,    1,    3,    2,    0,
    3,    1,    1,    0,    1,    1,    5,    1,    1,    1,
    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
    3,    1,    3,    3,    1,    3,    3,    3,    3,    3,
    1,    3,    3,    1,    3,    3,    1,    3,    3,    3,
    1,    3,    1,    3,    3,    2,    3,    2,    3,    1,
    2,    2,    2,    2,    2,    2,    2,    1,    3,    1,
    2,    4,    3,    3,    4,    2,    1,    1,    4,    8,
    6,    7,    7,    8,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    2,
    6,    3,    3,    3,    2,    2,    2,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    2,    2,    3,    2,    4,    0,    4,
    0,    1,    1,    2,    1,    2,    1,    2,    2,    2,
    3,    4,    1,    3,    1,    2,    3,    4,    1,    3,
    5,    3,    3,    2,    1,    1,    2,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    2,    3,    3,    2,    0,    3,
    3,    3,    1,    3,    1,    4,    3,    6,    3,    3,
    1,    3,    1,    1,    6,    6,    7,    1,    0,    2,
    5,    5,    5,    6,    6,    6,    2,    6,    6,    6,
    1,    1,    5,    5,    3,    3,    0,    4,    1,    4,
    3,    3,    0,    3,    0,    1,    1,    3,    1,    4,
    1,    1,    2,    2,    1,    2,    0,    2,    3,    0,
    3,    0,    3,    0,    1,    1,    2,    3,    4,    1,
    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 893
#define YYNLSTATES 488
#define YYINTERRTOK 1
#define YYUNEXPECTED 32767
#define YYDEFAULT -32766


/*
 * Seek (st,ch) in action table, return true if found.
 * param n position in yyaction
 * param st current state
 * param ch input token
 */
#if YYPROBEONCE
#define found_in_action(n, st, ch) \
  ((unsigned)(n = yybase[st] + (ch)) < YYLAST && yycheck[n] == (ch))
#endif /* YYPROBEONCE */

#if !YYPROBEONCE
#define found_in_action(n, st, ch) \
  (((unsigned)(n = yybase[st] + (ch)) < YYLAST && yycheck[n] == (ch)) \
   || ((st) < YY2TBLSTATE \
       && (unsigned)(n = yybase[(st) + YYNLSTATES] + (ch)) < YYLAST \
       && yycheck[n] == (ch)))
#endif /* !YYPROBEONCE */

#define found_in_goto(n, st, ch) \
  ((unsigned)(n = yygbase[ch] + (st)) < YYGLAST && yygcheck[n] == (ch))


/*
 * Lexical analyzer interface
 */
#if YYPURE
#  ifdef YYLEX_PARAM
#    define YYLEX() yylex(&yylval, YYLEX_PARAM)
#  else
#    define YYLEX() yylex(&yylval)
#  endif /* YYLEX_PARAM */
#else
#  define YYLEX() yylex()
#endif /* YYPURE */


/*
 * Parser entry point
 */
#ifdef YYPARSE_PARAM
#  if __STDC__
#    define YYPARSE_ARG void *YYPARSE_PARAM
#    define YYPARSE_DECL
#  else
#    define YYPARSE_ARG YYPARSE_PARAM
#    define YYPARSE_DECL void *YYPARSE_PARAM;
#  endif /* __STDC__ */
#else
# define YYPARSE_ARG
# define YYPARSE_DECL
#endif /* YYPARSE_PARAM */

int yyparse(YYPARSE_ARG)
  YYPARSE_DECL
{
  YYSTYPE yyastk[YYMAXDEPTH];
  short yysstk[YYMAXDEPTH];
  short *yyssp;
  int yystate;
  int yyn;
  int yyp;
  int yyl;
  int yychar1;
#if YYPURE
  int yychar;
  YYSTYPE yylval;
#endif /* YYPURE */
  int yyerrflag;
  YYSTYPE *yyasp;
#ifndef YYACTFUN
  YYSTYPE yyval;
#endif /* !YYACTFUN */
  YYTRACE_DCL

  yyssp = yysstk;
  yyasp = yyastk - 1;
  *yyssp = yystate = 0;
  yychar1 = yychar = -1;
  yyerrflag = 0;
  for (;;) {
    YYTRACE_NEWSTATE(yystate, yychar1);

    if (yybase[yystate] == 0)
      yyn = yydefault[yystate];
    else {
      if (yychar < 0) {
        if ((yychar = YYLEX()) <= 0) yychar = 0;
        yychar1 = yychar < YYMAXLEX ? yytranslate[yychar] : YYBADCH;
        YYTRACE_READ(yychar1);
      }
      
      if (found_in_action(yyn, yystate, yychar1)
          && (yyn = yyaction[yyn]) != YYDEFAULT) {
        /*
         * >= YYNLSTATE: shift and reduce
         * > 0: shift
         * = 0: accept
         * < 0: reduce
         * = -YYUNEXPECTED: error
         */
        if (yyn > 0) {
          /* shift */
          YYTRACE_SHIFT(yychar1);
          if (yyssp >= yysstk + YYMAXDEPTH) {
            yyerror("parser stack overflow");
            YYABORT;
          }
          *++yyssp = yystate = yyn;
          *++yyasp = yylval;
          yychar1 = yychar = -1;

          if (yyerrflag > 0)
            yyerrflag--;
          if (yyn < YYNLSTATES)
            continue;

          /* yyn >= YYNLSTATES means shift-and-reduce */
          yyn -= YYNLSTATES;
        } else
          yyn = -yyn;
      } else
        yyn = yydefault[yystate];
    }

    for (;;) {
      /* reduce/error */
      if (yyn == 0) {
        /* accept */
        YYTRACE_ACCEPT();
        YYACCEPT;
      }
      else if (yyn != YYUNEXPECTED) {
        /* reduce */
        yyl = yylen[yyn];
        yyval = yyasp[1-yyl];
        YYTRACE_REDUCE(yyn);
#line 384 "build/utility/kmyacc.c.parser"
        switch(yyn) {
        case 1:
#line 173 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 178 "src/kinx.y"
{ kx_ast_root = yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 5:
#line 183 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 16:
#line 200 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strval, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 17:
#line 201 "src/kinx.y"
{ yyerrok; } break;
        case 25:
#line 212 "src/kinx.y"
{ yyerrok; } break;
        case 26:
#line 213 "src/kinx.y"
{ yy_restart(LBBR); yyerrok; } break;
        case 27:
#line 214 "src/kinx.y"
{ yy_restart(IF); yyerrok; } break;
        case 28:
#line 215 "src/kinx.y"
{ yy_restart(DO); yyerrok; } break;
        case 29:
#line 216 "src/kinx.y"
{ yy_restart(WHILE); yyerrok; } break;
        case 30:
#line 217 "src/kinx.y"
{ yy_restart(FOR); yyerrok; } break;
        case 31:
#line 218 "src/kinx.y"
{ yy_restart(TRY); yyerrok; } break;
        case 32:
#line 219 "src/kinx.y"
{ yy_restart(SWITCH); yyerrok; } break;
        case 33:
#line 220 "src/kinx.y"
{ yy_restart(CASE); yyerrok; } break;
        case 34:
#line 221 "src/kinx.y"
{ yy_restart(ENUM); yyerrok; } break;
        case 35:
#line 222 "src/kinx.y"
{ yy_restart(CLASS); yyerrok; } break;
        case 36:
#line 223 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; } break;
        case 37:
#line 224 "src/kinx.y"
{ yy_restart(PRIVATE); yyerrok; } break;
        case 38:
#line 225 "src/kinx.y"
{ yy_restart(PUBLIC); yyerrok; } break;
        case 43:
#line 236 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 44:
#line 237 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 45:
#line 241 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 242 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 47:
#line 243 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 244 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 49:
#line 248 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strval); } break;
        case 50:
#line 252 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 51:
#line 256 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strval); } break;
        case 52:
#line 257 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strval, YYASP(3-3).intval); } break;
        case 53:
#line 258 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strval, -YYASP(4-4).intval); } break;
        case 54:
#line 259 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strval)); } break;
        case 55:
#line 260 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strval, YYASP(5-5).intval)); } break;
        case 56:
#line 261 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strval, -YYASP(6-6).intval)); } break;
        case 61:
#line 272 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 62:
#line 276 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 63:
#line 277 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 64:
#line 281 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 65:
#line 285 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 66:
#line 289 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 293 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 294 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 299 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 70:
#line 306 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 71:
#line 313 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 72:
#line 320 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 73:
#line 322 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 74:
#line 326 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 76:
#line 331 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 77:
#line 335 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 78:
#line 336 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, "_e", YYASP(2-2).obj, NULL); } break;
        case 79:
#line 337 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(3-5).strval, YYASP(5-5).obj, NULL); } break;
        case 80:
#line 341 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 81:
#line 342 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 82:
#line 346 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 83:
#line 347 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strval)); } break;
        case 84:
#line 348 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 85:
#line 349 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strval)); } break;
        case 86:
#line 353 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 87:
#line 354 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 88:
#line 358 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 89:
#line 362 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 90:
#line 363 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 91:
#line 364 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 92:
#line 365 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 93:
#line 369 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 94:
#line 373 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 95:
#line 377 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object(YYASP(1-1).strval, KX_OBJ_T), NULL); } break;
        case 96:
#line 378 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object(YYASP(3-3).strval, KX_OBJ_T), NULL); } break;
        case 97:
#line 382 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 98:
#line 386 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 99:
#line 387 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 100:
#line 391 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 102:
#line 396 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 103:
#line 397 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 105:
#line 402 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 106:
#line 403 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 107:
#line 404 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 108:
#line 405 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 109:
#line 406 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 110:
#line 407 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 111:
#line 408 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 409 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 410 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 411 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 412 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 413 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 414 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 415 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 121:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 122:
#line 425 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 123:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 124:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 125:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 126:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 127:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 129:
#line 435 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 131:
#line 440 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 132:
#line 444 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 134:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 136:
#line 454 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 139:
#line 457 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 140:
#line 458 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 141:
#line 459 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 142:
#line 460 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 144:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 145:
#line 466 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 146:
#line 467 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 147:
#line 468 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 148:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 149:
#line 473 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 150:
#line 474 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 151:
#line 475 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 152:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 153:
#line 477 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 154:
#line 478 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 155:
#line 479 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 156:
#line 480 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 157:
#line 481 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 158:
#line 482 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 159:
#line 486 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 160:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 161:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 166:
#line 502 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 170:
#line 512 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 172:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 174:
#line 522 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 176:
#line 527 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 178:
#line 532 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 180:
#line 537 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 182:
#line 542 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 183:
#line 543 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 185:
#line 548 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 186:
#line 549 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 187:
#line 550 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 188:
#line 551 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 189:
#line 552 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 191:
#line 557 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 558 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 194:
#line 563 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 564 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 197:
#line 569 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 570 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 199:
#line 571 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 203:
#line 581 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 582 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 205:
#line 583 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 206:
#line 584 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 207:
#line 585 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 208:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 210:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 211:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 212:
#line 593 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 213:
#line 594 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 214:
#line 595 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 215:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 216:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 218:
#line 602 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 220:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 221:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 222:
#line 609 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 223:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 224:
#line 611 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 225:
#line 612 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 226:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 228:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 229:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 230:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 231:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 232:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 233:
#line 626 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 234:
#line 630 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 235:
#line 631 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 236:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 237:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 238:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 239:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 240:
#line 639 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 241:
#line 640 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 242:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 243:
#line 642 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 249:
#line 648 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 250:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 251:
#line 650 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 252:
#line 651 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 253:
#line 652 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 254:
#line 653 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 255:
#line 654 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 256:
#line 655 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 257:
#line 659 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 258:
#line 660 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 259:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 260:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 261:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 262:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 263:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 264:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 265:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 266:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 267:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 268:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 269:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 270:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 271:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 272:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 273:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 274:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 275:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 276:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 277:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 278:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 279:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 280:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 281:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 282:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 283:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 284:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 285:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 286:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 287:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 288:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 289:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 290:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 291:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 292:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 293:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 294:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 295:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 296:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 297:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 298:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 299:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 300:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 301:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 302:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 303:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 304:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 305:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 306:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 307:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 308:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 309:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 310:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 311:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 312:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 313:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 314:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 315:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 316:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 317:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 318:
#line 732 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 319:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 320:
#line 740 "src/kinx.y"
{} break;
        case 322:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 323:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 324:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 325:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 327:
#line 756 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 328:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 329:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 330:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 331:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 333:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 335:
#line 770 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 336:
#line 771 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 337:
#line 772 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 339:
#line 777 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 340:
#line 781 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 341:
#line 782 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 342:
#line 783 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 343:
#line 784 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 344:
#line 785 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-1).strval, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T)); } break;
        case 346:
#line 790 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 348:
#line 795 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 349:
#line 796 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 350:
#line 797 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 351:
#line 798 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 352:
#line 799 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 353:
#line 800 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 354:
#line 801 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 355:
#line 802 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 356:
#line 803 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 357:
#line 804 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 358:
#line 805 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 359:
#line 806 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 360:
#line 807 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 361:
#line 808 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 362:
#line 809 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 363:
#line 810 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 364:
#line 811 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 365:
#line 812 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 366:
#line 813 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 367:
#line 814 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 368:
#line 815 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 369:
#line 816 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 370:
#line 817 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 371:
#line 818 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 372:
#line 819 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 373:
#line 820 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 374:
#line 821 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 375:
#line 822 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 376:
#line 823 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 377:
#line 824 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 378:
#line 825 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 379:
#line 826 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 380:
#line 827 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 381:
#line 828 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 382:
#line 832 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 383:
#line 833 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 384:
#line 834 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 385:
#line 835 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 386:
#line 836 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 387:
#line 837 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 388:
#line 838 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 389:
#line 839 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 390:
#line 840 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 391:
#line 841 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 392:
#line 842 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 393:
#line 843 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 394:
#line 844 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 395:
#line 845 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 396:
#line 846 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 397:
#line 847 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 398:
#line 848 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 399:
#line 849 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 400:
#line 850 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 401:
#line 851 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 402:
#line 852 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 403:
#line 853 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 404:
#line 854 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 405:
#line 855 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 406:
#line 856 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 407:
#line 857 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 408:
#line 858 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 409:
#line 859 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 410:
#line 860 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 411:
#line 861 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 412:
#line 862 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 413:
#line 863 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 414:
#line 864 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 415:
#line 865 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 416:
#line 866 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 417:
#line 867 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 418:
#line 868 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 419:
#line 869 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 420:
#line 870 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 421:
#line 871 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 422:
#line 872 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 423:
#line 873 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 424:
#line 874 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 425:
#line 875 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 426:
#line 876 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 427:
#line 877 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 428:
#line 878 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 429:
#line 879 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 430:
#line 880 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 431:
#line 881 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 432:
#line 882 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 433:
#line 883 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 434:
#line 884 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 435:
#line 888 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 436:
#line 889 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 437:
#line 890 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 438:
#line 894 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 439:
#line 898 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 440:
#line 902 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 441:
#line 903 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 443:
#line 908 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 444:
#line 912 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 445:
#line 913 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 446:
#line 914 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 447:
#line 915 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 448:
#line 916 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 449:
#line 917 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 451:
#line 922 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 452:
#line 926 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 453:
#line 927 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 454:
#line 931 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 455:
#line 932 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 456:
#line 933 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 457:
#line 937 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 458:
#line 941 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 459:
#line 942 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 460:
#line 946 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 461:
#line 947 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 462:
#line 948 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 463:
#line 949 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 464:
#line 950 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 465:
#line 951 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 466:
#line 952 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 467:
#line 956 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 468:
#line 957 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 469:
#line 958 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 472:
#line 967 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 473:
#line 968 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 474:
#line 972 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 475:
#line 973 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 476:
#line 977 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 477:
#line 979 "src/kinx.y"
{
            yyval.namedstmt = (named_stmt_t){
                .name = kx_check_the_name(YYASP(3-4).obj),
                .stmt =
                    kx_gen_bexpr_object(KXST_STMTLIST,
                        kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object_line("this", KX_UNKNOWN_T, YYASP(2-4).intval),
                            kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, YYASP(3-4).obj, kx_gen_str_object("create")), YYASP(4-4).obj)),
                        kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object_line("super", KX_UNKNOWN_T, YYASP(2-4).intval),
                            kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
                    ),
            };
        } break;
        case 479:
#line 995 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 480:
#line 996 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 481:
#line 997 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 482:
#line 1001 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 483:
#line 1002 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 484:
#line 1006 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 487:
#line 1012 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 488:
#line 1016 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 489:
#line 1017 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 490:
#line 1018 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 491:
#line 1019 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 492:
#line 1020 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 493:
#line 1024 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 494:
#line 1025 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 495:
#line 1026 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 496:
#line 1030 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 497:
#line 1031 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 498:
#line 1032 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 499:
#line 1036 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 500:
#line 1037 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 501:
#line 1041 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 502:
#line 1042 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 503:
#line 1046 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 506:
#line 1052 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 507:
#line 1053 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 508:
#line 1054 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 511:
#line 1060 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 512:
#line 1064 "src/kinx.y"
{ yyval.intval = kx_lexinfo.line; } break;
#line 389 "build/utility/kmyacc.c.parser"
        }
#line 391 "build/utility/kmyacc.c.parser"

        /* Goto - shift nonterminal */
        yyasp -= yyl;
        yyssp -= yyl;
        yyn = yylhs[yyn];
        if (found_in_goto(yyp, *yyssp, yyn))
          yystate = yygoto[yyp];
        else
          yystate = yygdefault[yyn];

        if (yyssp >= yysstk + YYMAXDEPTH) {
          yyerror("parser stack overflow");
          YYABORT;
        }
        *++yyssp = yystate;
        *++yyasp = yyval;

      }
      else {
        /* error */
        switch (yyerrflag) {
        case 0:
        yyerrlab:
          yyerror("syntax error");
        case 1:
        case 2:
          yyerrflag = 3;
          /* Pop until error-expecting state uncovered */
          while (!found_in_action(yyn, yystate, YYINTERRTOK)) {
            if (yyssp <= yysstk)
              YYABORT;
            yystate = *--yyssp;
            yyasp--;
            YYTRACE_POP(yystate);
          }
          yyn = yyaction[yyn];
          YYTRACE_SHIFT(YYINTERRTOK);
          *++yyssp = yystate = yyn;
          ++yyasp;
          break;

        case 3:
          YYTRACE_DISCARD(yychar1);
          if (yychar == 0)
            YYABORT;
          yychar1 = yychar = -1;
          break;
        }
      }

      if (yystate < YYNLSTATES)
        break;
      /* >= YYNLSTATES means shift-and-reduce */
      yyn = yystate - YYNLSTATES;
    }
  }
}
