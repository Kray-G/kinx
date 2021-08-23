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
    name_t        strinfo;  /* NAME with location */
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
#define FALLTHROUGH 274
#define NEW 275
#define VAR 276
#define CONST 277
#define RETURN 278
#define THROW 279
#define YIELD 280
#define MIXIN 281
#define EQEQ 282
#define NEQ 283
#define LE 284
#define GE 285
#define LGE 286
#define LOR 287
#define LAND 288
#define INC 289
#define DEC 290
#define SHL 291
#define SHR 292
#define POW 293
#define LUNDEF 294
#define PIPEOPL2R 295
#define PIPEOPR2L 296
#define FCOMPOSL2R 297
#define FCOMPOSR2L 298
#define ADDEQ 299
#define SUBEQ 300
#define MULEQ 301
#define DIVEQ 302
#define MODEQ 303
#define ANDEQ 304
#define OREQ 305
#define XOREQ 306
#define LANDEQ 307
#define LOREQ 308
#define LUNDEFEQ 309
#define SHLEQ 310
#define SHREQ 311
#define REGEQ 312
#define REGNE 313
#define NUL 314
#define TRUE 315
#define FALSE 316
#define AS 317
#define IMPORT 318
#define USING 319
#define DARROW 320
#define SQ 321
#define DQ 322
#define MLSTR 323
#define BINEND 324
#define DOTS2 325
#define DOTS3 326
#define REGPF 327
#define NAMESPACE 328
#define SYSNS 329
#define SYSRET_NV 330
#define CLASS 331
#define SYSCLASS 332
#define MODULE 333
#define SYSMODULE 334
#define NATIVE 335
#define FUNCTION 336
#define SYSFUNC 337
#define PUBLIC 338
#define PRIVATE 339
#define PROTECTED 340
#define COROUTINE 341
#define NAME 342
#define STR 343
#define SRCFILE 344
#define BIGINT 345
#define INT 346
#define TYPE 347
#define TYPEOF 348
#define LBBR 349
#define RBBR 350
#define LMBR 351
#define RMBR 352
#define DBL 353
#define BIN 354
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
#line 1127 "src/kinx.y"

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
  "FALLTHROUGH",
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
  "PIPEOPL2R",
  "PIPEOPR2L",
  "FCOMPOSL2R",
  "FCOMPOSR2L",
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
  "'|'",
  "'^'",
  "'&'",
  "'?'",
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
  "LabelStatement : NAME ':' ':' LabelledStatement",
  "LabelStatement : NAME ':' ':' BlockStatement",
  "IfStatement : IF '(' AssignExpressionList ')' Statement",
  "IfStatement : IF '(' AssignExpressionList ')' Statement ELSE Statement",
  "WhileStatement : WHILE '(' AssignExpressionList ')' Statement",
  "DoWhileStatement : DO Statement WHILE '(' AssignExpressionList ')' ';'",
  "SwitchCaseStatement : SWITCH '(' AssignExpressionList ')' BlockStatement",
  "SwitchCaseStatement : CaseStatement",
  "CaseStatement : CASE AssignExpression ':'",
  "CaseStatement : DEFAULT ':'",
  "CaseStatement : WHEN AssignExpression ':'",
  "CaseStatement : ELSE ':'",
  "ForStatement : FOR '(' VAR DeclAssignExpressionList ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement",
  "ForStatement : FOR '(' AssignExpressionList ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement",
  "ForStatement : FOR '(' ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement",
  "ForStatement : FOR '(' VarName IN AssignExpressionList ')' Statement",
  "ForStatement : FOR '(' VAR VarName IN AssignExpressionList ')' Statement",
  "ForStatement : FOR '(' ForInVariable IN AssignExpressionList ')' Statement",
  "ForStatement : FOR '(' VAR ForInVariable IN AssignExpressionList ')' Statement",
  "ForInVariable : Array",
  "ForInVariable : Object",
  "TryCatchStatement : TRY BlockStatement CatchStatement_Opt FinallyStatement_Opt",
  "CatchStatement_Opt : /* empty */",
  "CatchStatement_Opt : CATCH CatchVariable BlockStatement",
  "CatchVariable : /* empty */",
  "CatchVariable : '(' NAME ')'",
  "FinallyStatement_Opt : /* empty */",
  "FinallyStatement_Opt : FINALLY BlockStatement",
  "BreakStatement : BREAK Modifier_Opt ';'",
  "BreakStatement : BREAK NAME Modifier_Opt ';'",
  "BreakStatement : CONTINUE Modifier_Opt ';'",
  "BreakStatement : CONTINUE NAME Modifier_Opt ';'",
  "BreakStatement : FALLTHROUGH ';'",
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
  "Modifier_Opt : Modifier",
  "Modifier : IF '(' AssignExpressionList ')'",
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
  "WhenClause : WHEN WhenConditionRangeList ':' WhenClauseBody",
  "WhenClause : WHEN WhenConditionRangeList WhenClauseBodyBlock",
  "WhenClause : WHEN WhenConditionRangeList Modifier Colon_Opt WhenClauseBody",
  "WhenConditionRangeList : WhenConditionRange",
  "WhenConditionRangeList : WhenConditionRangeList '|' WhenConditionRange",
  "WhenConditionRangeList : WhenConditionRangeList LOR WhenConditionRange",
  "WhenConditionRange : WhenAnonymousFunctionDeclExpression",
  "WhenConditionRange : WhenPostfixExpression",
  "WhenConditionRange : '^' WhenPostfixExpression",
  "WhenConditionRange : Array",
  "WhenConditionRange : Object",
  "WhenConditionRange : SimpleFuncCallFactor",
  "WhenConditionRange : '.' PropertyName",
  "WhenConditionRange : '.' TYPEOF",
  "WhenConditionRange : WhenPostfixExpression DOTS2",
  "WhenConditionRange : WhenPostfixExpression DOTS2 WhenPostfixExpression",
  "WhenConditionRange : WhenPostfixExpression DOTS3",
  "WhenConditionRange : WhenPostfixExpression DOTS3 WhenPostfixExpression",
  "WhenAnonymousFunctionDeclExpression : FUNCTION '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "WhenAnonymousFunctionDeclExpression : SYSFUNC '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "WhenAnonymousFunctionDeclExpression : COROUTINE '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "WhenAnonymousFunctionDeclExpression : NativeKeyword '(' ArgumentList_Opts ')' NativeType_Opt BlockStatement",
  "WhenAnonymousFunctionDeclExpression : '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW BlockStatement",
  "WhenAnonymousFunctionDeclExpression : '&' FunctionType_Opt BlockStatement",
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
  "WhenClauseBody : WhenClauseBodyBlock",
  "WhenClauseBody : TernaryExpression",
  "WhenClauseBodyBlock : BlockStatement",
  "Colon_Opt : /* empty */",
  "Colon_Opt : ':'",
  "TernaryExpression : AnonymousFunctionDeclExpression",
  "TernaryExpression : PipelineExpression",
  "TernaryExpression : PipelineExpression '?' TernaryExpression ':' TernaryExpression",
  "PipelineExpression : FunctionCompositionExpression",
  "PipelineExpression : PipelineExpression PIPEOPL2R FunctionCompositionExpression",
  "PipelineExpression : PipelineExpression PIPEOPR2L FunctionCompositionExpression",
  "FunctionCompositionExpression : LogicalUndefExpression",
  "FunctionCompositionExpression : FunctionCompositionExpression FCOMPOSL2R LogicalUndefExpression",
  "FunctionCompositionExpression : FunctionCompositionExpression FCOMPOSR2L LogicalUndefExpression",
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
  "SimpleFuncCallFactor : LBBR FunctionType_Opt DARROW AssignExpression RBBR",
  "SimpleFuncCallFactor : LBBR '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW AssignExpression RBBR",
  "SimpleFuncCallFactor : LBBR '&' '(' ArgumentList_Opts ')' FunctionType_Opt StatementList RBBR",
  "PostIncDec : INC",
  "PostIncDec : DEC",
  "Factor : INT",
  "Factor : DBL",
  "Factor : BIGINT",
  "Factor : NUL",
  "Factor : TRUE",
  "Factor : FALSE",
  "Factor : SRCFILE",
  "Factor : VarName",
  "Factor : Binary",
  "Factor : Array",
  "Factor : Object",
  "Factor : Regex",
  "Factor : SimpleFuncCallFactor",
  "Factor : IMPORT '(' '(' STR ')' ')'",
  "Factor : '(' AssignExpression ')'",
  "Factor : '(' ObjectSpecialSyntax ')'",
  "Factor : '(' STR ')'",
  "Factor : NEW Factor",
  "Factor : '.' PropertyName",
  "Factor : '.' TYPEOF",
  "Factor : '@' PropertyName",
  "Factor : '@' TYPEOF",
  "VarName : NAME",
  "VarName : TYPE",
  "PropertyName : NAME",
  "PropertyName : TYPE",
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
  "PropertyName : PIPEOPL2R",
  "PropertyName : POW",
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
  "KeyValue : CastExpression",
  "ValueOfKeyValue : AssignExpression",
  "ValueOfKeyValue : '^' AssignExpression",
  "ValueOfKeyValue : ObjectSpecialSyntax",
  "KeySpecialName : IF",
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
  "KeySpecialName : NATIVE",
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
  "ClassFunctionSpecialName : POW",
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
  "NormalFunctionDeclStatement : FUNCTION NAME '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "NormalFunctionDeclStatement : SYSFUNC NAME '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "NormalFunctionDeclStatement : NativeKeyword NAME '(' ArgumentList_Opts ')' NativeType_Opt BlockStatement",
  "NativeKeyword : NATIVE",
  "FunctionType_Opt : /* empty */",
  "FunctionType_Opt : ':' TypeName",
  "NativeType_Opt : /* empty */",
  "NativeType_Opt : ':' TypeName",
  "AnonymousFunctionDeclExpression : FUNCTION '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "AnonymousFunctionDeclExpression : SYSFUNC '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "AnonymousFunctionDeclExpression : COROUTINE '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "AnonymousFunctionDeclExpression : NativeKeyword '(' ArgumentList_Opts ')' NativeType_Opt BlockStatement",
  "AnonymousFunctionDeclExpression : '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW AssignExpression",
  "AnonymousFunctionDeclExpression : '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW BlockStatement",
  "AnonymousFunctionDeclExpression : '&' FunctionType_Opt BlockStatement",
  "ClassFunctionDeclStatement : PUBLIC ClassFunctionName '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "ClassFunctionDeclStatement : PRIVATE ClassFunctionName '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
  "ClassFunctionDeclStatement : PROTECTED ClassFunctionName '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement",
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
  "ArgumentList_Opts : ArgumentList Comma_Opt",
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
  "CallArgumentList_Opts : CallArgumentList Comma_Opt",
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
    0,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  114,  116,  116,  116,  112,  105,  116,
  100,  101,  110,  109,   98,   97,  102,  111,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,   99,   96,
  107,   95,  108,  106,  115,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  104,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  103,  116,  113,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  116,  116,  116,  116,    1,  116,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
   64,  116,  116,  116,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,   92,   93,   94,  116
#line 165 "build/utility/kmyacc.c.parser"
};

#define YYBADCH 116
#define YYMAXLEX 355
#define YYTERMS 116
#define YYNONTERMS 124

static short yyaction[] = {
  843,  844,  845,  846,  847,  848,  849,  850,  851,  852,
  853,  854,  855,  857,  856,  104,    0,  858,  859,  860,
  869,  871,  870,-32766,  881,  882,  883,  885,  887,  202,
  203,  413, 1098,  879,  880,  878,   80,  877,   39,   39,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,   92,   93,  121,  413,  122,  872,  873,  874,  839,
  875,  876,  898,   50,  840,   30,   42,  908,   45,  269,
  867,   17,  868,  113,  861,  862,  863,  864,  865,  866,
  832,  841,  151,  152,  153,  582,  842,  584,  583,  585,
  452,  586,   95,  170,  243,  889,  587,  588,  453,    1,
  589,  894,  895,  893,  456,  884,  886,  888,  890,  891,
  892,  966,  967,  968,  969,  970,  971,  972,  973,  974,
  975,  976,  977,  978,   60,  979,   99,   80,  980,  981,
  982,  990,  992,  991,  102, 1003, 1004, 1005, 1007, 1009,
  389,  390,   14,  391, 1001, 1002, 1000,    2,  101,  114,
  392,  116,  393,  108, 1081,  590,   98,   48,  908,   27,
  591,  342,  593,  592,  113,  348,  343,  993,  994,  995,
   66,  996,  997,  581,  572,  839,  625,  -80,  170,  580,
  840,  988,   96,  989,  130,  131,  983,  984,  985,  986,
  987,  -81, 1057,  142,  143,  144,  119,  998,  999, 1098,
  122,  430,  815,  816, -372,   39, 1011,  336,   50,  431,
   30, -372, 1016, 1017, 1015,  346, 1006, 1008, 1010, 1012,
 1013, 1014,  176,  435,  389,  436,    9,  437,  936,  331,
  938,  939,  249,  250,  438,  111,  393,  112,  394,  395,
  168,  246,  247,  332,   54,   61,  319,  314,   69,  123,
-32766,  128,  253,  389,  390,   14,  391,   51,  149,   31,
 -110,  118,   39,  392,  107,  393,  108,  607,  610,   49,
  150,   28,  145,  146,  252,  170,  315,  529,  547,  439,
  440,  441,  423,  285,  963, -487,  135,   80,   79, -110,
  321,  322,  396,  442,  398,  443,  400,  444,  286,  287,
   35,   36,   37,    2,  445,  114,  136,   38,  171,  446,
  965,    1,  598,   48,  134,   27, -402, -106,  909,  154,
  251,   59,  140,  141,  113,  932,  267,  933,  934,  935,
  936,  937,  938,  939,  940,  941,  942,  943,  901,  944,
   39,  315,  168,  946,  947,  956,  958,  957,  658,  204,
  468,  268,  476,  451,  121,  105,-32766,-32766,   39,   39,
  147,  148,-32766, 1042,  499,  500,  117,    3,  387,  501,
  132,  133,  158,  159,  160,  161,  125,   41,  100,   45,
  172,  439,  440,  441,  469,  463,  963,  510,  314,   29,
   79,  201,  270,  329,  611,  954,  330,  955,  530,  948,
  949,  950,  951,  952,  953,-32766,  464,  428,  608,  429,
  327,  446,  965,  604,  686,  455,  328,  660,  659,  466,
-32766,  526,  251,   59,-32766,-32766,-32766,  528,  465,  471,
-32766,  532,-32766,-32766,  325,  725,-32766,-32766,  932,  838,
  933,  934,  935,  936,  937,  938,  939,  940,  941,  942,
  943,  807,  944,-32766,  690,  168,  946,  947,  956,  958,
  957, 1068,  710,  836,  723,    3,    4,    1,   39,-32766,
-32766,  269,    5,   40,   38,  509,  813,  605,  812,  903,
  520,  534,  517,    0, 1085, 1066, 1084,  896,  899,  805,
  688, 1018,    0,    0,  439,  440,  441,  312,  463,  963,
  306,  103,   74,   79,   68,   67,  248,  647,  954,  622,
  955,  571,  948,  949,  950,  951,  952,  953,-32766,  464,
  650,  657,  648,  646,  446,  965,  652,  921, 1026, 1025,
   71,  645,   15,-32766,  661,  251,   59,  651,  649,   75,
   73,  465,   72,   70,  625,-32766,-32766,  503,  235,-32766,
-32766,  932,  115,  933,  934,  935,  936,  937,  938,  939,
  940,  941,  942,  943,   62,  944,   53,  120,  168,  946,
  947,  956,  958,  957,   43,  221,  627, -408,  204, -405,
 -404, -403,-32766,-32766, -400, -392,   44,   55,   56,   57,
  743,  626,  628,  555,  256,  254,  129, -401,  205,  251,
    0,  219,  233,  220,  218,  217,  216,  439,  440,  441,
   97,  463,  963,   94,   78,   77,   79,   76,   52,  498,
  470,  954,  425,  955,  227,  948,  949,  950,  951,  952,
  953,-32766,  464,  424,  255,  234,  232,  446,  965,  231,
  919,  230,  229,  228,  226,  225,-32766,  224,  251,   59,
  223,  222,  138,   16,  465,   18,   19,   20,-32766,-32766,
   21,  347,-32766,-32766,  932,  536,  933,  934,  935,  936,
  937,  938,  939,  940,  941,  942,  943,  668,  944,  831,
  728,  168,  946,  947,  956,  958,  957, 1089, 1087,  726,
  830,  735,  642,  691, 1070,-32766,-32766,  808, 1024,  897,
  833, 1019,  533,   22,  382,  381,  380,  379,  378,  371,
  369,  368,  366,  365,  364,  362,  359,  356,  355,  354,
  439,  440,  441,  353,  463,  963,  352,   24,   23,   79,
    0,  137,  900,    0,  954,  465,  955,  139,  948,  949,
  950,  951,  952,  953,-32766,  464,    0,    0,    0,    0,
  446,  965,    0,    0,    0,    0,    0,    0,    0,-32766,
    0,  251,   59,    0,    0,    0,    0,  465,    0,    0,
    0,-32766,-32766,    0,    0,-32766,-32766,  932,    0,  933,
  934,  935,  936,  937,  938,  939,  940,  941,  942,  943,
    0,  944,    0,    0,  168,  946,  947,  956,  958,  957,
    0,    0,    0,    0,    0,    0,    0,    0,-32766,-32766,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  439,  440,  441,    0,  463,  963,    0,
    0,    0,   79,    0,    0,    0,    0,  954,    0,  955,
    0,  948,  949,  950,  951,  952,  953,-32766,  464,    0,
    0,    0,    0,  446,  965,    0,    0,    0,    0,    0,
    0,    0,-32766,    0,    0,   59,    0,    0,    0,    0,
-32766,    0,    0,    0,-32766,-32766,    0,    0,-32766,-32766,
  176,  388,  389,  390,   14,  391,    0,  318,    0,    0,
  263,  264,  392,  107,  393,  108,  394,  395,    0,  244,
  245,  552,   64,  109,  319,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  271,    0, -487,    0,    0,    0,    0,  321,  322,
  396,  397,  398,  399,  400,    0,  272,  273,   32,   33,
   34,    0,  402,    0,    0,    0,    0,    0,    0,    1,
  598,    0,    0,    0,    0, -106,    0,    0,  251,    0,
    0,    0,    0,    0,  267,  176,  388,  389,  390,   14,
  391,    0,  318,    0,    0,  263,  264,  392,  107,  393,
  108,  394,  395,    0,  244,  245,  552,   64,  109,  319,
    0,    0,    0,    0,    0,   -1,  176,  388,  389,  390,
   14,  391,    0,  318,    0,    0,  263,  264,  392,  107,
  393,  108,  394,  395,    0,  244,  245,  552,   64,  109,
  319,    0,    0,    0,    0,    0,  271,    0,    0,    0,
    0,    0,    0,  321,  322,  396,  397,  398,  399,  400,
    0,  272,  273,   32,   33,   34,    0,  402,    0,    0,
    0,    0,    0,    0,    1,    0,    0,  271,    0,    0,
 -106,    0,    0, -378,  321,  322,  396,  397,  398,  399,
  400,    0,  272,  273,   32,   33,   34,    0,  402,    0,
    0,    0,    0,    0,    0,    1,    0,    0,    0,    0,
    0, -106,  176,  388,  389,  390,   14,  391,    0,  318,
    0,    0,  263,  264,  392,  107,  393,  108,  394,  395,
    0,  244,  245,  552,   64,  109,  319,    0,    0,    0,
    0,    0,  176,  388,  389,  390,   14,  391,    0,  318,
    0,    0,  263,  264,  392,  107,  393,  108,  394,  395,
    0,  244,  245,  552,   64,  109,  319,    0,    0,    0,
    0,    0,    0,  271,    0,    0,    0,    0,    0,    0,
  321,  322,  396,  397,  398,  399,  400,    0,  272,  273,
   32,   33,   34,    0,  402,    0,    0,    0,    0,    0,
    0,    1,  814,  271,    0,  124,    0, -106,    0,    0,
  321,  322,  396,  397,  398,  399,  400,    0,  272,  273,
   32,   33,   34,    0,  402,    0,    0,    0,    0,    0,
    0,    1,    0,    0,    0,    0,    0, -106,  176,  388,
  389,  390,   14,  391,    0,  318,    0,    0,  263,  264,
  392,  107,  393,  108,  394,  395,    0,  244,  245,  552,
   64,  109,  319,    0,    0,    0,    0,  176,  388,  389,
  390,   14,  391,    0,  318,    0,    0,  263,  264,  392,
  107,  393,  108,  394,  395,    0,  244,  245,  552,   64,
  109,  319,    0,    0,    0,    0,    0,    0,    0,  271,
    0,  106,    0,    0,    0,    0,  321,  322,  396,  397,
  398,  399,  400,    0,  272,  273,   32,   33,   34,    0,
  402,    0,    0,    0,    0,    0,    0,    1,  271,    0,
    0,    0,    0, -106,    0,  321,  322,  396,  397,  398,
  399,  400,    0,  272,  273,   32,   33,   34,    0,  402,
    0,    0,    0,    0,    0,    0,    1,  602,    0,    0,
    0,    0, -106,  176,  388,  389,  390,   14,  391,    0,
  318,    0,    0,  263,  264,  392,  107,  393,  108,  394,
  395,    0,  244,  245,  552,   64,  109,  319,    0,    0,
    0,    0,    0,  176,  388,  389,  390,   14,  391,    0,
  318,    0,    0,  263,  264,  392,  107,  393,  108,  394,
  395,    0,  244,  245,  552,   64,  109,  319,    0,    0,
    0,    0,    0,    0,  271,    0,    0,    0,    0,    0,
    0,  321,  322,  396,  397,  398,  399,  400,    0,  272,
  273,   32,   33,   34,    0,  402,    0,    0,    0,    0,
    0,    0,    1,  601,  271,    0,    0,    0, -106,    0,
    0,  321,  322,  396,  397,  398,  399,  400,    0,  272,
  273,   32,   33,   34,    0,  402,    0,    0,    0,    0,
    0,    0,    1,  600,    0,    0,    0,    0, -106,  176,
  388,  389,  390,   14,  391,    0,  318,    0,    0,  263,
  264,  392,  107,  393,  108,  394,  395,    0,  244,  245,
  552,   64,  109,  319,    0,    0,    0,    0,    0,  176,
  388,  389,  390,   14,  391,    0,  318,    0,    0,  263,
  264,  392,  107,  393,  108,  394,  395,    0,  244,  245,
  552,   64,  109,  319,    0,    0,    0,    0,    0,    0,
  271,    0,    0,    0,    0,    0,    0,  321,  322,  396,
  397,  398,  399,  400,    0,  272,  273,   32,   33,   34,
    0,  402,    0,    0,    0,    0,    0,    0,    1,  599,
  271,    0,    0,    0, -106,    0,    0,  321,  322,  396,
  397,  398,  399,  400,    0,  272,  273,   32,   33,   34,
    0,  402,    0,    0,    0,    0,    0,    0,    1,  598,
    0,    0,    0,    0, -106,  176,  388,  389,  390,   14,
  391,    0,  318,    0,    0,  263,  264,  392,  107,  393,
  108,  394,  395,    0,  244,  245,  552,   64,  109,  319,
    0,    0,    0,    0,    0,  176,  388,  389,  390,   14,
  391,    0,  318,    0,    0,  263,  264,  392,  107,  393,
  108,  394,  395,    0,  244,  245,  552,   64,  109,  319,
    0,    0,    0,    0,    0,    0,  271,    0,    0,    0,
    0,    0,    0,  321,  322,  396,  397,  398,  399,  400,
    0,  272,  273,   32,   33,   34,    0,  402,    0,    0,
    0,    0,    0,    0,    1,  603,  271,    0,    0,    0,
 -106,    0,    0,  321,  322,  396,  397,  398,  399,  400,
    0,  272,  273,   32,   33,   34,  110,  402,    0,    0,
    0,  167,    0,    0,    1,    0,    0,    0,    0,    0,
 -106,    0,    0,    0,    0,  162,  163,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  553,    0,
    0,    0,    0,    0,    0,    0,-32766,    0,    0,    0,
  820,  821,  822,    0,  416,    0,    0,    0,    0,    0,
  320,    0,    0,    0,    0,-32766,-32766,    0, 1042,  417,
  418,    0,    0,    0,  401,  839,    0,  823,  819,  817,
  840,    0,   41,  169,   45,    0,  818,    0,    0,  164,
    0,    0,   58,    0,   25,    0,    0,  266,    0,  323,
    0,  165,  155,  554,    0,  156,  157,   26,-32766,-32766,
-32766,    0,    0,    0,-32766,    0,    0,    0,    0,    0,
    0,    0,  732,  733,  734,    0,    0,    0,    0,-32766,
    0,    0,    0,    0,    0,    0,    0,-32766,    0,    0,
    0,-32766,-32766,    0,    0,-32766,-32766,  839,    0,    0,
  731,  729,  840,    0,    0,    0,    0,    0,  730,    0,
    0,    0,    0,    0,   63
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1895

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   67,    0,   19,   20,   21,
   22,   23,   24,   14,   26,   27,   28,   29,   30,   66,
   67,    2,   84,   35,   36,   37,   67,   39,   90,   90,
   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,
   53,   54,   55,  104,    2,   92,   58,   59,   60,   83,
   62,   63,   93,  100,   88,  102,   90,   98,   92,   90,
   72,    3,   74,  104,   76,   77,   78,   79,   80,   81,
  101,   83,  110,  111,  112,    2,   88,    4,    5,    6,
   92,    8,   95,   16,   20,   97,   13,   14,  100,   90,
   17,  103,  104,  105,    4,  107,  108,  109,  110,  111,
  112,    2,    3,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   95,   16,    7,   67,   19,   20,
   21,   22,   23,   24,    7,   26,   27,   28,   29,   30,
    3,    4,    5,    6,   35,   36,   37,   90,    7,   92,
   13,   14,   15,   16,   76,   72,    7,  100,   98,  102,
   77,   83,   79,   80,  104,    3,   88,   58,   59,   60,
   96,   62,   63,   90,   91,   83,   99,    7,   16,   96,
   88,   72,   67,   74,   39,   40,   77,   78,   79,   80,
   81,    7,   83,   28,   29,   30,   24,   88,   89,   84,
   92,   92,   33,   34,   91,   90,   97,    9,  100,  100,
  102,   98,  103,  104,  105,   10,  107,  108,  109,  110,
  111,  112,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   25,   83,   95,   92,
   14,  106,   99,    3,    4,    5,    6,  100,   97,  102,
   96,   92,   90,   13,   14,   15,   16,   87,   87,  100,
  109,  102,  107,  108,   61,   16,   83,   97,   97,   58,
   59,   60,   20,   62,   63,   64,   31,   67,   67,   96,
   69,   70,   71,   72,   73,   74,   75,   76,   77,   78,
   79,   80,   81,   90,   83,   92,   32,   90,   31,   88,
   89,   90,   91,  100,   38,  102,   99,   96,   98,   37,
   99,  100,   26,   27,  104,    2,  105,    4,    5,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   65,   16,
   90,   83,   19,   20,   21,   22,   23,   24,   96,   99,
   98,   67,   84,   84,  104,   64,   33,   34,   90,   90,
   35,   36,   14,   76,   77,   78,   64,   90,   64,   82,
   41,   42,   56,   57,   66,   67,   99,   90,   67,   92,
  103,   58,   59,   60,   83,   62,   63,   84,   83,  102,
   67,  104,  105,   83,   87,   72,   83,   74,   83,   76,
   77,   78,   79,   80,   81,   82,   83,   83,   87,   83,
   83,   88,   89,   83,   91,   83,   83,   83,   83,   83,
   97,   83,   99,  100,   76,   77,   78,   84,  105,   84,
   82,   84,  109,  110,   90,   89,  113,  114,    2,   89,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   89,   16,  105,   89,   19,   20,   21,   22,   23,
   24,   89,   89,   89,   93,   90,   90,   90,   90,   33,
   34,   90,   90,   90,   90,   95,   91,   91,   91,   91,
  101,   92,   92,   -1,   93,   93,   93,   93,   93,   93,
   93,   93,   -1,   -1,   58,   59,   60,   95,   62,   63,
   95,   95,   95,   67,   95,   95,   98,   96,   72,   96,
   74,   96,   76,   77,   78,   79,   80,   81,   82,   83,
   96,   96,   96,   96,   88,   89,   96,   91,   96,   96,
   96,   96,  101,   97,   96,   99,  100,   96,   96,   96,
   96,  105,   96,   96,   99,  109,  110,   98,   98,  113,
  114,    2,   98,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   98,   16,   98,   98,   19,   20,
   21,   22,   23,   24,   98,  100,   99,   99,   99,   99,
   99,   99,   33,   34,   99,   99,   99,   99,   99,   99,
   99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
   -1,  100,  100,  100,  100,  100,  100,   58,   59,   60,
  100,   62,   63,  100,  100,  100,   67,  100,  100,  100,
  100,   72,  100,   74,  100,   76,   77,   78,   79,   80,
   81,   82,   83,  100,  100,  100,  100,   88,   89,  100,
   91,  100,  100,  100,  100,  100,   97,  100,   99,  100,
  100,  100,  104,  101,  105,  101,  101,  101,  109,  110,
  101,  101,  113,  114,    2,  101,    4,    5,    6,    7,
    8,    9,   10,   11,   12,   13,   14,  101,   16,  101,
  101,   19,   20,   21,   22,   23,   24,  101,  101,  101,
  101,  101,  101,  101,  101,   33,   34,  101,  101,  101,
  101,  101,  101,  101,  101,  101,  101,  101,  101,  101,
  101,  101,  101,  101,  101,  101,  101,  101,  101,  101,
   58,   59,   60,  101,   62,   63,  101,  101,  101,   67,
   -1,  103,  108,   -1,   72,  105,   74,  105,   76,   77,
   78,   79,   80,   81,   82,   83,   -1,   -1,   -1,   -1,
   88,   89,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   97,
   -1,   99,  100,   -1,   -1,   -1,   -1,  105,   -1,   -1,
   -1,  109,  110,   -1,   -1,  113,  114,    2,   -1,    4,
    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   -1,   16,   -1,   -1,   19,   20,   21,   22,   23,   24,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   33,   34,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   58,   59,   60,   -1,   62,   63,   -1,
   -1,   -1,   67,   -1,   -1,   -1,   -1,   72,   -1,   74,
   -1,   76,   77,   78,   79,   80,   81,   82,   83,   -1,
   -1,   -1,   -1,   88,   89,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   97,   -1,   -1,  100,   -1,   -1,   -1,   -1,
  105,   -1,   -1,   -1,  109,  110,   -1,   -1,  113,  114,
    1,    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   14,   15,   16,   17,   18,   -1,   20,
   21,   22,   23,   24,   25,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   62,   -1,   64,   -1,   -1,   -1,   -1,   69,   70,
   71,   72,   73,   74,   75,   -1,   77,   78,   79,   80,
   81,   -1,   83,   -1,   -1,   -1,   -1,   -1,   -1,   90,
   91,   -1,   -1,   -1,   -1,   96,   -1,   -1,   99,   -1,
   -1,   -1,   -1,   -1,  105,    1,    2,    3,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   17,   18,   -1,   20,   21,   22,   23,   24,   25,
   -1,   -1,   -1,   -1,   -1,    0,    1,    2,    3,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   16,   17,   18,   -1,   20,   21,   22,   23,   24,
   25,   -1,   -1,   -1,   -1,   -1,   62,   -1,   -1,   -1,
   -1,   -1,   -1,   69,   70,   71,   72,   73,   74,   75,
   -1,   77,   78,   79,   80,   81,   -1,   83,   -1,   -1,
   -1,   -1,   -1,   -1,   90,   -1,   -1,   62,   -1,   -1,
   96,   -1,   -1,   99,   69,   70,   71,   72,   73,   74,
   75,   -1,   77,   78,   79,   80,   81,   -1,   83,   -1,
   -1,   -1,   -1,   -1,   -1,   90,   -1,   -1,   -1,   -1,
   -1,   96,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,   -1,
   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,   -1,
   -1,   -1,   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,
   69,   70,   71,   72,   73,   74,   75,   -1,   77,   78,
   79,   80,   81,   -1,   83,   -1,   -1,   -1,   -1,   -1,
   -1,   90,   91,   62,   -1,   64,   -1,   96,   -1,   -1,
   69,   70,   71,   72,   73,   74,   75,   -1,   77,   78,
   79,   80,   81,   -1,   83,   -1,   -1,   -1,   -1,   -1,
   -1,   90,   -1,   -1,   -1,   -1,   -1,   96,    1,    2,
    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   17,   18,   -1,   20,   21,   22,
   23,   24,   25,   -1,   -1,   -1,   -1,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   62,
   -1,   64,   -1,   -1,   -1,   -1,   69,   70,   71,   72,
   73,   74,   75,   -1,   77,   78,   79,   80,   81,   -1,
   83,   -1,   -1,   -1,   -1,   -1,   -1,   90,   62,   -1,
   -1,   -1,   -1,   96,   -1,   69,   70,   71,   72,   73,
   74,   75,   -1,   77,   78,   79,   80,   81,   -1,   83,
   -1,   -1,   -1,   -1,   -1,   -1,   90,   91,   -1,   -1,
   -1,   -1,   96,    1,    2,    3,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   16,   17,
   18,   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,
   -1,   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   16,   17,
   18,   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,
   -1,   -1,   -1,   -1,   62,   -1,   -1,   -1,   -1,   -1,
   -1,   69,   70,   71,   72,   73,   74,   75,   -1,   77,
   78,   79,   80,   81,   -1,   83,   -1,   -1,   -1,   -1,
   -1,   -1,   90,   91,   62,   -1,   -1,   -1,   96,   -1,
   -1,   69,   70,   71,   72,   73,   74,   75,   -1,   77,
   78,   79,   80,   81,   -1,   83,   -1,   -1,   -1,   -1,
   -1,   -1,   90,   91,   -1,   -1,   -1,   -1,   96,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   -1,   20,   21,
   22,   23,   24,   25,   -1,   -1,   -1,   -1,   -1,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   -1,   20,   21,
   22,   23,   24,   25,   -1,   -1,   -1,   -1,   -1,   -1,
   62,   -1,   -1,   -1,   -1,   -1,   -1,   69,   70,   71,
   72,   73,   74,   75,   -1,   77,   78,   79,   80,   81,
   -1,   83,   -1,   -1,   -1,   -1,   -1,   -1,   90,   91,
   62,   -1,   -1,   -1,   96,   -1,   -1,   69,   70,   71,
   72,   73,   74,   75,   -1,   77,   78,   79,   80,   81,
   -1,   83,   -1,   -1,   -1,   -1,   -1,   -1,   90,   91,
   -1,   -1,   -1,   -1,   96,    1,    2,    3,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   17,   18,   -1,   20,   21,   22,   23,   24,   25,
   -1,   -1,   -1,   -1,   -1,    1,    2,    3,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   17,   18,   -1,   20,   21,   22,   23,   24,   25,
   -1,   -1,   -1,   -1,   -1,   -1,   62,   -1,   -1,   -1,
   -1,   -1,   -1,   69,   70,   71,   72,   73,   74,   75,
   -1,   77,   78,   79,   80,   81,   -1,   83,   -1,   -1,
   -1,   -1,   -1,   -1,   90,   91,   62,   -1,   -1,   -1,
   96,   -1,   -1,   69,   70,   71,   72,   73,   74,   75,
   -1,   77,   78,   79,   80,   81,   14,   83,   -1,   -1,
   -1,   19,   -1,   -1,   90,   -1,   -1,   -1,   -1,   -1,
   96,   -1,   -1,   -1,   -1,   33,   34,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   46,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   14,   -1,   -1,   -1,
   58,   59,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,
   68,   -1,   -1,   -1,   -1,   33,   34,   -1,   76,   77,
   78,   -1,   -1,   -1,   82,   83,   -1,   85,   86,   87,
   88,   -1,   90,   19,   92,   -1,   94,   -1,   -1,   97,
   -1,   -1,  100,   -1,  102,   -1,   -1,  105,   -1,  107,
   -1,  109,  110,  111,   -1,  113,  114,  115,   76,   77,
   78,   -1,   -1,   -1,   82,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   58,   59,   60,   -1,   -1,   -1,   -1,   97,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  105,   -1,   -1,
   -1,  109,  110,   -1,   -1,  113,  114,   83,   -1,   -1,
   86,   87,   88,   -1,   -1,   -1,   -1,   -1,   94,   -1,
   -1,   -1,   -1,   -1,  100
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1654,  221,  889, 1528, 1402, 1372, 1247, 1151, 1025,  994,
 1498, 1276, 1624, 1121, 1654, 1654, 1654, 1654, 1654, 1654,
 1654, 1654, 1654, 1654, 1654,  374,  350,  362,  365,  373,
  346,  372,  109,  109,  109,  109,  109,  109,  549,  323,
  436,  662,  775,  775,  250,  -31,   60,  220,  115,  115,
  115,  115,   74,  -52,  217,  -51,  -51,  -51,  269,  268,
  172,  498,  311,  343,  384,  384,  384,  378,  378,  378,
  384,  384,  384,  384,  378,  384, 1722, 1722, 1722,  378,
  378,  378,  378,  378,  378,  378,  378,  378,  378,  378,
  378,  378,  378,  378, 1722,  378,  378, 1722, 1722, 1722,
  378, 1722, 1722,  378,  378,  377,  377, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722,  383, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722,    9,    9,    9,  236,  236,
  348,  348,  348,  348,  348,  348,  348,  348,  348,  348,
  348,  348,  348,  348,  348,  348,  348,  348,  348,  348,
  348,  348,  348,  348,  348,  348,  348,  348,  348,  348,
  348,  348, 1762, 1762, 1762, 1762, 1762, 1762, 1762, 1762,
  287,  287,  287,   77,   29,  259,   83,  477,  578,  396,
  445,  387,  397,  579,  371,  392,  385,  385,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3, 1794, 1794, 1794,  375,  479,  213,  -21,  -37,   57,
   57,   57,   57,  381,  381,  381,  284,  284,  284,  284,
  284,  284,  284,  284,  284,  284,  284,  284,  284,  284,
  284,  284,  284,  284,  284,  284,  277,  108,  108,  108,
  165,  165,  165,  -24,  -24,  -24,  -24,  -24,  -24,  164,
  193,   78,   78,   78,   78,   78,   78,  157,  -28,  145,
  -28,  -28,  127,  305,  258,  162,  501,  524,   92,  630,
  502,  262,  324,  326,  296,  325,  161,  316,  308,  332,
  329,  153,  433,  432,  252,  262,  324,  326,  113,  431,
  552,  447,  560,  296,  325,  325,  325,  325,  325,  161,
  161,  316,  329,  329,  434,  576,  180,  564,  554,  555,
  556,  559,  181,   52,   52,   52,   52,   52,  375,  335,
  522,  330,  330,  624,  198,  336,  522,  475,  475,  375,
  375,  375,  485,  476,  375,  522,  519,  205,  449,  494,
  494,  450,  390,  390,  468,  375,  375,  375,  491,  534,
  375,  375,  500,  500,  500,  500,  495,  375,  491,  500,
  534,  375,  500,  375,  500,  500,  500,  375,  500,  495,
  375,  500,  375,  375,  375,  375,  375,  375,  500,  500,
  500,  500,  495,  375,  375,  375,  375,  375,  517,  493,
  515,  518,  514,  492,  344,  442,  441,  327,  333,  310,
  313,  504,  499,   16,  438,  276,  255,  274,  628,  548,
  632,  282,  100,  513,  435,  411,  533,  506,  505,  503,
  410,  409,  454,  301,  520,  345,  376,  382,  551,  550,
  398,  600,  547,  545,  544,  517,  515,  518,  514,  482,
  481,  480,  327,  310,  486,  487,  478,  488,  302,  395,
  466,  599,  394,  598,  430,  543,  510,  149,  170,  184,
  119,  427,  426,  533,  489,  542,  405,  425,  334,  380,
  303,  597,  496,  625,  622,  618,  379,  388,  466,  617,
  273,  255,  274,  628,  548,  632,  282,  282,  282,  596,
  616,  497,  276,  276,  141,  410,  409,  446,  338,  541,
  539,  536,  535,  315,  386,  406,  406,  406,  424,  347,
  601,  593,  615,  614,  613,  612,  611,  393,  389,  389,
  490,  610,  592,  609,   68,  444,  591,  608,  590,  321,
  402,  407,  415,  589,  391,  291,  413,  443,  602,  607,
  606,  605,  604,  603,  588,  587,  627,  307,  406,  626,
  304,  586,    0,    0,    0,    0, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722,   -2,   -2,   -2,   -2,   -2,   -2,   -2,    0,    0,
    0,    0,    0,    0, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722,    0,    0,    0, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
    0, 1722, 1722,    0,    0,    0, 1722,    0,    0, 1722,
 1722, 1722, 1722,    0,    0,    0,    0,    0,    0,    0,
    0, 1722,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1794, 1794, 1794,   -3,
   -3,   -3,    0,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  137,  137,  169,  169,  169,  169,  169,  169,  169,  169,
  169,  169,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,
  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,
  -24,  -24,   52,  169,  169,  169,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   52,   52,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  153,   52,
   52,    0,  500,  500,    0,  500,  500,  533,  506,  505,
    0,    0,    0,    0,    0,  503,    0,    0,  408,  408,
    0,  533,  506,  505,    0,  469,  469,  469,  469,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  408,  469,    0,  469,  469,  469,  469,  469
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 312

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  395,  396,  397,  487,  487,
  487,  487,32767,  349,32767,32767,32767,32767,  534,  534,
  534,  534,32767,  349,  108,32767,32767,32767,32767,32767,
32767,   98,  357,32767,  108,  108,  108,32767,32767,32767,
  108,  108,  108,  108,32767,  108,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,   98,
32767,  387,  388,32767,32767,32767,32767,32767,32767,  100,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  233,  235,32767,32767,32767,32767,32767,32767,  389,32767,
32767,32767,32767,32767,  110,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  495,32767,  362,   97,
  354,  360,  355,  540,  364,  373,  358,   99,  361,  374,
  495,32767,  155,  157,32767,32767,  245,32767,  148,  243,
  244,  241,  240,  129,  541,  375,  515,  515,  515,  515,
  515,  515,  515,  515,  515,  515,  515,  515,  515,  515,
  515,  515,  515,  515,  515,  349,32767,  149,  156,  158,
  209,  210,  211,32767,32767,32767,  390,  391,32767,  384,
  385,32767,32767,32767,32767,32767,32767,  532,  221,  189,
  223,  222,  473,  110,  110,  181,  487,  487,32767,  487,
  487,32767,32767,32767,  207,  212,  218,  228,  230,32767,
  191,  473,32767,32767,32767,  406,  393,  394,  237,32767,
32767,32767,32767,  208,  214,  216,  217,  213,  215,  219,
  220,  229,  192,  193,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  110,  110,  110,  110,  110,32767,32767,
32767,32767,32767,  346,   83,32767,32767,  513,  513,32767,
32767,  381,  543,  348,32767,32767,   85,   87,  348,  507,
  507,  348,  527,  527,  348,32767,32767,32767,  186,  530,
32767,32767,  487,  487,  487,  487,  489,32767,  186,  487,
  530,32767,  487,32767,  487,  487,  487,32767,  487,  489,
32767,  487,32767,32767,32767,32767,32767,32767,  487,  487,
  487,  487,  489,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  283,32767,32767,  194,  197,  199,  201,  203,
  205,  224,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  109,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  376,  377,  379,  386,  264,
  265,  266,  398,  399,  486,  283,  284,32767,32767,32767,
  350,32767,32767,32767,32767,32767,32767,32767,  270,  271,
  268,32767,32767,  406,  283,32767,   50,32767,32767,32767,
32767,32767,  519,32767,32767,32767,32767,32767,  351,32767,
32767,  198,  200,  202,  204,  206,  225,  226,  227,32767,
32767,32767,  195,  196,32767,   80,   81,32767,32767,32767,
32767,32767,32767,  349,32767,  477,  478,  475,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  526,  524,
  277,32767,32767,32767,   63,32767,32767,32767,32767,32767,
   53,  474,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  476,32767,
32767,32767,  543,  467,  467,  543
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  195,  190,  190,  190,  193,  193,  193,  193,  191,  193,
  188,  195,  195,  195,  178,  178,  460,  189,  196,  183,
  188,  188,  188, 1052, 1052,  923,  188,  188,  188,  188,
  480,  188,  191,  191,  191,  837,  806,  689,  709,  724,
 1067,  317,  497,  741,  741,  741,  525,  537,  538,  546,
  191,  549,  478,  191,  191,  191, 1094,  191,  191,  738,
  699,  200,  186,  173,  177,  189,  175,  173,  177,  192,
  179,  194,  180,  181,  182,  197,  198,  199,  184,  185,
  187,  302,  303,  279,  279,  279,  279,  279,  279,  279,
  279,  279,  279,  279,  279,  279,  279,  279,  279,  279,
  279,  279,  279,  279,  279,  279,  279,  279,  708,  708,
  708,  481,  798,  794,  795,  787,  788,  790,  792,  506,
  507,  482,  618,  616,  810,  548,  484,  810,  810,  810,
  810,  288, 1021,  483,  727,  727,  727,  289,  290,  292,
  504, 1020,  458, 1072,  811,  692, 1091,  811,  811,  811,
  811,  692,  692,  692,  741,  305,  492,  493,  307,  308,
  309,  485,  310,  311,  293,  727,  727,  727,  928,  928,
  928,  928,  928,  928,   11,   12,   13,   13,  459, 1074,
  472,  472,  472,  472,  472,  472,  472,  472,  472,  472,
  472,  472,  472,  472,  472,  472,  472,  472,  472,  472,
  740,  740,  740,  491,  746,  558,  301,  262,  281,  281,
  281,  281,  281,  559,  412,  561,  561,  561,  561,  412,
  524,  621,  620,  634,  632,  635,  633,  631,  630,  629,
  433,  434, 1079,  433,  434,  358,  324,  294,  295,  296,
  297,  298,  802,  349,  360,  545, 1046, 1061, 1062,  324,
  241,  242, 1053,  502,  502,  502,  209,  210,  211,  212,
  706,  706,  706,  640,  644,  623,  698,  377, 1059, 1060,
 1065,  834,  834,  736,  304,  720,  283,  494,  283, 1047,
  386, 1048,  696,  617,  616, 1049, 1028,  926, 1050,  924,
 1039, 1040, 1054, 1055, 1056, 1041,  707,  707,  707,  299,
  300,  715,  716,  717,  718,  719, 1077, 1077, 1077, 1077,
 1077, 1077, 1077, 1077, 1077, 1077, 1077, 1077, 1077, 1077,
 1077, 1077, 1077, 1077, 1077, 1077,  522,  544,  551,  663,
  486,  487,  488,  495,  420,  420,  420,  420,  420,  237,
  238,  239, 1078, 1078, 1078, 1078, 1078, 1078, 1078, 1078,
 1078, 1078, 1078, 1078, 1078, 1078, 1078, 1078, 1078, 1078,
 1078, 1078,  334,  334,  260,  261,  357,  427,  684,  496,
  421,  421,  421,  421,  421,  684,  684,  684,  702,  701,
  351,  340,  684,  335,  519,  127, 1076,  684,  684,  684,
  684,  684,  684,  684,  684,  684,  684,  684,  684,  684,
  684,  684,  670,  684,  684,  415,  166,    0,  684,  687,
  722,  684,  684,    0,    0,  687,  687,  687,    0,  415,
    0,  927,  912,  673,  674,  675,  676,  677,  678,  679,
  680,  681,  682,  683,  671,  672,    0,  670, 1093,  722,
  722,  722,  915,    0,    0, 1036, 1095,    0,  361,  363,
  367,  535,    0,    0,    0,  372,    0,    0,  373,    0,
  374,  375,  376,    0,    6,    0,    0,    7,  454,  461,
  462,  467,  508,    0,  383,  384,  385,  550,  474,  475,
  479,  490,  511,  512,  513,  514,  515,  516,  521,  523,
  527,  539,  540,  541,  542,  543,  215,    0,    0,    0,
  214,  214,  214,  214,    0,  214,    0,  215,  215,  215,
  207,  207
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 512

static char yygcheck[] = {
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   74,   37,   37,   37,
   37,   37,   37,    7,    7,   72,   37,   37,   37,   37,
   66,   37,   37,   37,   37,   58,   58,   58,   58,   58,
   58,   40,   40,    7,    7,    7,   40,   40,   40,   40,
   37,   40,   67,   37,   37,   37,  100,   37,   37,  118,
  118,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,  108,  108,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   97,   97,
   97,   43,   55,   55,   55,   55,   55,   55,   55,   81,
   81,   44,    7,   35,    7,   81,   46,    7,    7,    7,
    7,   56,   65,   45,   74,   74,   74,   69,   69,   69,
  120,   65,   62,  120,   97,   97,  120,   97,   97,   97,
   97,   97,   97,   97,    7,   69,   42,   42,   69,   69,
   69,   47,   69,   69,   48,   74,   74,   74,   56,   56,
   56,   56,   56,   56,    3,    3,    3,    3,   63,   95,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   41,   41,   41,   41,   41,    4,   54,   74,   74,   74,
   74,   74,   74,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
   76,   76,   74,   76,   76,   32,    7,   50,   50,   50,
   50,   50,  103,  103,  103,  103,  103,    7,    7,    7,
   49,   49,    7,   82,   82,   82,   57,   57,   57,   57,
   62,   62,   62,    7,    7,    7,  119,  102,    7,    7,
   60,   60,   60,   60,   79,    7,   79,   19,   79,    7,
  102,    7,  111,   35,   35,    7,   80,   73,    7,   73,
    7,    7,    7,    7,    7,    7,   63,   63,   63,   51,
   51,    7,    7,    7,    7,    7,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   98,   98,   98,   31,
   53,   53,   53,   62,   62,   62,   62,   62,   62,  114,
  114,  114,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,  101,  101,   52,   52,  101,    9,  109,   63,
   63,   63,   63,   63,   63,  109,  109,  109,  113,  113,
   89,   91,  109,  123,  104,  121,  105,  109,  109,  109,
  109,  109,  109,  109,  109,  109,  109,  109,  109,  109,
  109,  109,   38,  109,  109,   31,  106,   -1,  109,   59,
   59,  109,  109,   -1,   -1,   59,   59,   59,   -1,   31,
   -1,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   -1,   38,   38,   59,
   59,   59,   38,   -1,   -1,   38,   38,   -1,  101,  101,
  101,  101,   -1,   -1,   -1,  101,   -1,   -1,  101,   -1,
  101,  101,  101,   -1,  101,   -1,   -1,  101,   31,   31,
   31,   31,   31,   -1,  101,  101,  101,  101,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   93,   93,   93,   93,   93,   93,   39,   -1,   -1,   -1,
   39,   39,   39,   39,   -1,   39,   -1,   39,   39,   39,
   39,   39
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  170,  205,    0,    0,  -82,    0,   45,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   34,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  155,   -1,    0,    0,   79,    0,  -44,  342,  452,
  -24,   75,   24,  -23,  -14,   -3,  -11,   23,   25,  110,
   95,  152,  215,  179,   52,  -43,  130,   94,    9,  202,
  104,    0,   90,  126,    0, -194,  -16,    5,    0,   61,
    0,    0,  -18,  232,  -36,    0,  197,    0,    0,   31,
   38,   51,   83,    0,    0,    0,    0,    0,    0,   40,
    0,   53,    0,  261,    0,  -56,    0,  -62,  277,    0,
    3,   96, -102,  -10,   41,   26, -149,    0,  -49,  308,
    0,   17,    0,  207,  138,    0,    0,    0,  -67,   30,
 -198,   27,    0, -171
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  403,    8,   10,  560,  563,  562,  564,  565,  426,
  566,  338,  578,  567,  594,  595,  596,  624,  597,  457,
  568,  337,  345,  638,  573,  574,  313,  575,  576,  284,
  577,  414,  667,  579,  569,  570,  404,  174, 1035,  213,
  316,  693,  405,  406,  407,  408,  409,  410,  274,  240,
  275,  276,  258,  411,  277,  278,  793,  206,  835,  804,
  803,  825,  826,  827,  828, 1022,  449,  450,   47,  291,
  422,  333,  922,  925,  824,  447,  432, 1058,  612,  282,
 1027,  505,  419,  613, 1037,  744, 1038,  614,  615,  350,
  257,  339, 1064,  473,  341, 1073,  809,  829,  489,  344,
 1092,  448,  370, 1044,  518,  531,   65,  259,  280,  669,
  265,  695,  236,  700,  208,  703,  721,  694,  697,  739,
  477,  126,   46,  326
#line 205 "build/utility/kmyacc.c.parser"
};

static char yylhs[] = {
    0,    1,    2,    2,    3,    3,    4,    4,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,   35,   35,
   35,   35,    7,    7,    8,    8,    8,    8,    9,   10,
   11,   11,   11,   11,   11,   11,   12,   12,   12,   12,
   34,   34,   34,   13,   13,   14,   15,   16,   16,   17,
   17,   17,   17,   18,   18,   18,   18,   18,   18,   18,
   19,   19,   20,   21,   21,   22,   22,   23,   23,   33,
   33,   33,   33,   33,   24,   24,   25,   26,   26,   26,
   26,   27,   28,   29,   29,   30,   36,   36,   40,   40,
   31,   31,   32,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   38,   38,
   39,   39,   39,   39,   39,   39,   39,  109,  109,  110,
  110,  111,  111,  111,  112,  112,  112,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  115,
  115,  115,  115,  115,  115,  114,  114,  114,  114,  114,
  114,  116,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  117,  117,  118,  118,  119,  121,  121,   41,   41,
   41,  107,  107,  107,  108,  108,  108,   42,   42,   43,
   43,   44,   44,   45,   45,   46,   46,   47,   47,   48,
   48,   48,   49,   49,   49,   49,   49,   49,   50,   50,
   50,   51,   51,   51,   52,   52,   52,   52,   53,   53,
   54,   54,   54,   54,   54,   54,   54,   55,   55,   55,
   55,   55,   55,   55,   55,   56,   56,   57,   57,   57,
   57,   57,   57,   57,   96,   96,   97,   97,   97,   59,
   59,   60,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   74,   74,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   62,   62,   61,   61,  122,   63,  120,  120,
   66,   66,   68,   68,   67,   67,   67,   67,   67,   67,
   69,   69,   70,   70,   70,   70,   71,   71,   72,   72,
   72,   72,   72,   73,   73,   73,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   64,   64,   64,  123,   65,   78,
   78,   79,   79,   80,   80,   80,   80,   80,   80,   81,
   81,   83,   83,   84,   84,   84,   82,  101,  101,  102,
  102,   85,   85,   85,   85,   85,   85,   85,   86,   86,
   86,   76,   76,   87,   87,   88,   88,   89,   89,   90,
   90,   90,   90,   91,   91,   93,   93,   94,   94,   95,
   95,   95,   95,   95,  103,  103,  103,  104,  104,  104,
  105,  105,   92,   92,   98,   98,   99,   99,   99,   99,
  100,  100,  100,  106
#line 209 "build/utility/kmyacc.c.parser"
};

static char yylen[] = {
    1,    1,    1,    2,    1,    2,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    6,    2,    1,    1,    1,
    1,    1,    1,    1,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    1,    1,
    1,    1,    2,    3,    4,    4,    5,    5,    1,    5,
    1,    3,    4,    3,    5,    6,    1,    1,    1,    1,
    3,    4,    4,    5,    7,    5,    7,    5,    1,    3,
    2,    3,    2,   10,    9,    8,    7,    8,    7,    8,
    1,    1,    4,    0,    3,    0,    3,    0,    2,    3,
    4,    3,    4,    2,    5,    2,    3,    2,    1,    4,
    3,    4,    3,    1,    3,    2,    0,    2,    0,    1,
    0,    1,    4,    1,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    1,    1,
    2,    2,    4,    3,    3,    4,    2,    1,    4,    1,
    2,    4,    3,    5,    1,    3,    3,    1,    1,    2,
    1,    1,    1,    2,    2,    2,    3,    2,    3,    6,
    6,    6,    6,    7,    3,    1,    2,    4,    3,    3,
    4,    1,    3,    1,    1,    1,    1,    1,    1,    3,
    2,    0,    3,    1,    1,    1,    0,    1,    1,    1,
    5,    1,    3,    3,    1,    3,    3,    1,    3,    1,
    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
    3,    3,    1,    3,    3,    3,    3,    3,    1,    3,
    3,    1,    3,    3,    1,    3,    3,    3,    1,    3,
    1,    3,    3,    2,    3,    2,    3,    1,    2,    2,
    2,    2,    2,    2,    2,    1,    3,    1,    2,    4,
    3,    3,    4,    2,    1,    1,    5,    9,    8,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    6,    3,    3,    3,    2,    2,
    2,    2,    2,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    2,    2,    3,    2,    4,    0,    4,    0,    1,
    1,    2,    1,    2,    1,    2,    2,    2,    3,    4,
    1,    3,    1,    2,    3,    4,    1,    3,    5,    3,
    3,    2,    1,    1,    2,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    2,    3,    3,    2,    0,    3,    3,
    3,    1,    3,    1,    4,    3,    6,    3,    3,    1,
    3,    1,    1,    7,    7,    7,    1,    0,    2,    0,
    2,    6,    6,    6,    6,    7,    7,    3,    7,    7,
    7,    1,    1,    5,    5,    3,    3,    0,    4,    1,
    4,    3,    3,    0,    3,    0,    2,    1,    3,    1,
    4,    1,    1,    2,    2,    1,    2,    0,    2,    3,
    0,    3,    0,    3,    0,    2,    1,    2,    3,    4,
    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 980
#define YYNLSTATES 556
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
#line 180 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 185 "src/kinx.y"
{ kx_ast_root = yyval.obj = (YYASP(2-2).obj == NULL ? YYASP(1-2).obj : kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 5:
#line 190 "src/kinx.y"
{ yyval.obj = (YYASP(2-2).obj == NULL ? YYASP(1-2).obj : kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 15:
#line 206 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strinfo.name, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 16:
#line 207 "src/kinx.y"
{ yyerrok; yyval.obj = NULL; } break;
        case 24:
#line 218 "src/kinx.y"
{                       yyerrok; yyval.obj = NULL; } break;
        case 25:
#line 219 "src/kinx.y"
{ yy_restart(LBBR);     yyerrok; yyval.obj = NULL; } break;
        case 26:
#line 220 "src/kinx.y"
{ yy_restart(IF);       yyerrok; yyval.obj = NULL; } break;
        case 27:
#line 221 "src/kinx.y"
{ yy_restart(DO);       yyerrok; yyval.obj = NULL; } break;
        case 28:
#line 222 "src/kinx.y"
{ yy_restart(WHILE);    yyerrok; yyval.obj = NULL; } break;
        case 29:
#line 223 "src/kinx.y"
{ yy_restart(FOR);      yyerrok; yyval.obj = NULL; } break;
        case 30:
#line 224 "src/kinx.y"
{ yy_restart(TRY);      yyerrok; yyval.obj = NULL; } break;
        case 31:
#line 225 "src/kinx.y"
{ yy_restart(SWITCH);   yyerrok; yyval.obj = NULL; } break;
        case 32:
#line 226 "src/kinx.y"
{ yy_restart(CASE);     yyerrok; yyval.obj = NULL; } break;
        case 33:
#line 227 "src/kinx.y"
{ yy_restart(ENUM);     yyerrok; yyval.obj = NULL; } break;
        case 34:
#line 228 "src/kinx.y"
{ yy_restart(CLASS);    yyerrok; yyval.obj = NULL; } break;
        case 35:
#line 229 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; yyval.obj = NULL; } break;
        case 36:
#line 230 "src/kinx.y"
{ yy_restart(PRIVATE);  yyerrok; yyval.obj = NULL; } break;
        case 37:
#line 231 "src/kinx.y"
{ yy_restart(PUBLIC);   yyerrok; yyval.obj = NULL; } break;
        case 42:
#line 242 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 43:
#line 243 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 44:
#line 247 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 45:
#line 248 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 249 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 47:
#line 250 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 254 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strinfo.name); } break;
        case 49:
#line 258 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 50:
#line 262 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strinfo.name); } break;
        case 51:
#line 263 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strinfo.name, YYASP(3-3).intval); } break;
        case 52:
#line 264 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strinfo.name, -YYASP(4-4).intval); } break;
        case 53:
#line 265 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strinfo.name)); } break;
        case 54:
#line 266 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strinfo.name, YYASP(5-5).intval)); } break;
        case 55:
#line 267 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strinfo.name, -YYASP(6-6).intval)); } break;
        case 60:
#line 278 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 61:
#line 279 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-4).strinfo.name, YYASP(4-4).obj); } break;
        case 62:
#line 280 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-4).strinfo.name, YYASP(4-4).obj); } break;
        case 63:
#line 284 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 64:
#line 285 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 65:
#line 289 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 66:
#line 293 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 67:
#line 297 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 69:
#line 302 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 70:
#line 303 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 71:
#line 304 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_WHEN, YYASP(2-3).obj); } break;
        case 72:
#line 305 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_ELSE, NULL); } break;
        case 73:
#line 310 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 74:
#line 317 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 75:
#line 324 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 76:
#line 331 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0, 0); } break;
        case 77:
#line 333 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1, 0); } break;
        case 78:
#line 335 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0, 1); } break;
        case 79:
#line 337 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1, 1); } break;
        case 82:
#line 346 "src/kinx.y"
{ yyval.obj = kx_gen_try_stmt_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 83:
#line 350 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 84:
#line 351 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 85:
#line 355 "src/kinx.y"
{ yyval.obj = kx_gen_var_object("_e", KX_UNKNOWN_T); } break;
        case 86:
#line 356 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(2-3).strinfo.name, KX_UNKNOWN_T, YYASP(2-3).strinfo.line, YYASP(2-3).strinfo.pos1, YYASP(2-3).strinfo.pos2); } break;
        case 87:
#line 360 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 88:
#line 361 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 89:
#line 365 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 90:
#line 366 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strinfo.name)); } break;
        case 91:
#line 367 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 92:
#line 368 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strinfo.name)); } break;
        case 93:
#line 369 "src/kinx.y"
{ yyval.obj = kx_gen_break_object(KXST_FALLTHROUGH, NULL); } break;
        case 94:
#line 373 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 95:
#line 374 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 96:
#line 378 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 97:
#line 382 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 98:
#line 383 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 99:
#line 384 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 100:
#line 385 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 101:
#line 389 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 102:
#line 393 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 103:
#line 397 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_OBJ_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2), NULL); } break;
        case 104:
#line 398 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object_line_pos(YYASP(3-3).strinfo.name, KX_OBJ_T, YYASP(3-3).strinfo.line, YYASP(3-3).strinfo.pos1, YYASP(3-3).strinfo.pos2), NULL); } break;
        case 105:
#line 402 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 106:
#line 406 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 107:
#line 407 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 108:
#line 411 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 110:
#line 416 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 112:
#line 421 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 114:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 115:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 116:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 117:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 118:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 119:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 120:
#line 432 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 121:
#line 433 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 122:
#line 434 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 123:
#line 435 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 124:
#line 436 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 125:
#line 437 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 126:
#line 438 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 127:
#line 439 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 130:
#line 448 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 131:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 132:
#line 450 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 133:
#line 451 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 134:
#line 452 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 135:
#line 453 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 136:
#line 454 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 138:
#line 459 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 140:
#line 464 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 141:
#line 468 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-4).obj, YYASP(4-4).obj, NULL); } break;
        case 142:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 143:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 145:
#line 475 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 146:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 149:
#line 482 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 153:
#line 486 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 154:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 155:
#line 488 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 156:
#line 489 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 157:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 158:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 159:
#line 496 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 160:
#line 497 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 161:
#line 498 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 162:
#line 499 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 163:
#line 500 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 164:
#line 501 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 166:
#line 506 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 167:
#line 507 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 168:
#line 508 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 169:
#line 509 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 170:
#line 510 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 172:
#line 515 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 173:
#line 516 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 174:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 175:
#line 518 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 176:
#line 519 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 177:
#line 520 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 178:
#line 521 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 179:
#line 522 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 180:
#line 523 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 181:
#line 527 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 182:
#line 528 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 185:
#line 537 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 190:
#line 548 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 192:
#line 553 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALLPL, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 193:
#line 554 "src/kinx.y"
{ yyval.obj = kx_gen_expr_right_object(KXOP_CALLPR, KXOP_CALLPR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 559 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_COMPOSITL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 560 "src/kinx.y"
{ yyval.obj = kx_gen_expr_right_object(KXOP_COMPOSITR, KXOP_COMPOSITR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 565 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 200:
#line 570 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 575 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 580 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 206:
#line 585 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 208:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 210:
#line 595 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 211:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 213:
#line 601 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 214:
#line 602 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 215:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 216:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 217:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 219:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 220:
#line 611 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 222:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 223:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 225:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 226:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 227:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 229:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 231:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 232:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 233:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 234:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 235:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 236:
#line 639 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 238:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 239:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 240:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 241:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 242:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 243:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 244:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 246:
#line 655 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 248:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 249:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 250:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 251:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 252:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 253:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 254:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 256:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-5).arraytype, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(4-5).obj, NULL, NULL), NULL); } break;
        case 257:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-9).arraytype, NULL, YYASP(4-9).obj, kx_gen_stmt_object(KXST_RET, YYASP(8-9).obj, NULL, NULL), NULL); } break;
        case 258:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-8).arraytype, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 259:
#line 680 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 260:
#line 681 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 261:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 262:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 263:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 264:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 265:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 266:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 267:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 274:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 275:
#line 699 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 276:
#line 700 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 277:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 278:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 279:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 280:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 281:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 282:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 283:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_UNKNOWN_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2); } break;
        case 284:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(kx_gen_typestr_object(YYASP(1-1).intval), KX_UNKNOWN_T); } break;
        case 285:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object_pos(YYASP(1-1).strinfo); } break;
        case 286:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 287:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 288:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 289:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 290:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 291:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 292:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 293:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 294:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 295:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 296:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 297:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 298:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 299:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 300:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 301:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 302:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 303:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 304:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 305:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 306:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 307:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 308:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 309:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 310:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 311:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 312:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 313:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 314:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 315:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 316:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 317:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 318:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 319:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 320:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 321:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|>"); } break;
        case 322:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("**"); } break;
        case 323:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 324:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 325:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 326:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 327:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 328:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 329:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 330:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 331:
#line 761 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 332:
#line 762 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 333:
#line 763 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 334:
#line 764 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 335:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 336:
#line 766 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 337:
#line 767 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 338:
#line 768 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 339:
#line 769 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 340:
#line 770 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 341:
#line 771 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 342:
#line 775 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 343:
#line 776 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 344:
#line 780 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 345:
#line 781 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 346:
#line 785 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 347:
#line 789 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 348:
#line 793 "src/kinx.y"
{} break;
        case 350:
#line 798 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 351:
#line 799 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 352:
#line 803 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 353:
#line 804 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 355:
#line 809 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 356:
#line 810 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 357:
#line 811 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 358:
#line 812 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 359:
#line 813 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 361:
#line 818 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 363:
#line 823 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 364:
#line 824 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 365:
#line 825 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 367:
#line 830 "src/kinx.y"
{ yyval.obj = kx_gen_exprlist(YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 368:
#line 834 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 369:
#line 835 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 370:
#line 836 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 371:
#line 837 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 372:
#line 838 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 374:
#line 843 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 376:
#line 848 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 377:
#line 849 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 378:
#line 850 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 379:
#line 851 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 380:
#line 852 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 381:
#line 853 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 382:
#line 854 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 383:
#line 855 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 384:
#line 856 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 385:
#line 857 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 386:
#line 858 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 387:
#line 859 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 388:
#line 860 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 389:
#line 861 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 390:
#line 862 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 391:
#line 863 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 392:
#line 864 "src/kinx.y"
{ yyval.strval = "native"; } break;
        case 393:
#line 865 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 394:
#line 866 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 395:
#line 867 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 396:
#line 868 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 397:
#line 869 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 398:
#line 870 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 399:
#line 871 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 400:
#line 872 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 401:
#line 873 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 402:
#line 874 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 403:
#line 875 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 404:
#line 876 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 405:
#line 877 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 406:
#line 878 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 407:
#line 879 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 408:
#line 880 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 409:
#line 881 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 410:
#line 885 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 411:
#line 886 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 412:
#line 887 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 413:
#line 888 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 414:
#line 889 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 415:
#line 890 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 416:
#line 891 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 417:
#line 892 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 418:
#line 893 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 419:
#line 894 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 420:
#line 895 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 421:
#line 896 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 422:
#line 897 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 423:
#line 898 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 424:
#line 899 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 425:
#line 900 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 426:
#line 901 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 427:
#line 902 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 428:
#line 903 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 429:
#line 904 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 430:
#line 905 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 431:
#line 906 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 432:
#line 907 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 433:
#line 908 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 434:
#line 909 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 435:
#line 910 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 436:
#line 911 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 437:
#line 912 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 438:
#line 913 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 439:
#line 914 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 440:
#line 915 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 441:
#line 916 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 442:
#line 917 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 443:
#line 918 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 444:
#line 919 "src/kinx.y"
{ yyval.strval = "**"; } break;
        case 445:
#line 920 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 446:
#line 921 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 447:
#line 922 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 448:
#line 923 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 449:
#line 924 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 450:
#line 925 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 451:
#line 926 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 452:
#line 927 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 453:
#line 928 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 454:
#line 929 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 455:
#line 930 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 456:
#line 931 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 457:
#line 932 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 458:
#line 933 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 459:
#line 934 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 460:
#line 935 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 461:
#line 936 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 462:
#line 937 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 463:
#line 938 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 464:
#line 942 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 465:
#line 943 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 466:
#line 944 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 467:
#line 948 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 468:
#line 952 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 469:
#line 956 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 470:
#line 957 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 472:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 473:
#line 966 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-1).obj, NULL); } break;
        case 474:
#line 967 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 475:
#line 968 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 476:
#line 969 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).obj, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 477:
#line 970 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 478:
#line 971 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 480:
#line 976 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 481:
#line 980 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 482:
#line 981 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 483:
#line 985 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 484:
#line 986 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 485:
#line 987 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, 0, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 486:
#line 991 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 487:
#line 995 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_UNKNOWN_T }; } break;
        case 488:
#line 996 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 489:
#line 1000 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 490:
#line 1001 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 491:
#line 1005 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 492:
#line 1006 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 493:
#line 1007 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 494:
#line 1008 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 495:
#line 1009 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-7).obj, NULL, NULL), NULL); } break;
        case 496:
#line 1010 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 497:
#line 1011 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 498:
#line 1015 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 499:
#line 1016 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 500:
#line 1017 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 501:
#line 1021 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strinfo.name; } break;
        case 503:
#line 1026 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 504:
#line 1027 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 505:
#line 1031 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 506:
#line 1032 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 507:
#line 1036 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 508:
#line 1038 "src/kinx.y"
{
            yyval.namedstmt = (named_stmt_t){
                .name = kx_check_the_name(YYASP(3-4).obj),
                .stmt =
                    kx_gen_bexpr_object(KXST_STMTLIST,
                        kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object_line("this", KX_OBJ_T, YYASP(2-4).intval),
                            kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, YYASP(3-4).obj, kx_gen_str_object("create")), YYASP(4-4).obj)),
                        kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object_line("super", KX_OBJ_T, YYASP(2-4).intval),
                            kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
                    ),
            };
        } break;
        case 510:
#line 1054 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 511:
#line 1055 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 512:
#line 1056 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 513:
#line 1060 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 514:
#line 1061 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 515:
#line 1065 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 518:
#line 1071 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 520:
#line 1076 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 521:
#line 1077 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 522:
#line 1078 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 523:
#line 1079 "src/kinx.y"
{ YYASP(2-2).obj->var_type = KX_SPR_T; yyval.obj = YYASP(2-2).obj; } break;
        case 524:
#line 1083 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 525:
#line 1084 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 526:
#line 1085 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strinfo.name) }; } break;
        case 527:
#line 1089 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 528:
#line 1090 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 529:
#line 1091 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 530:
#line 1095 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 531:
#line 1096 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 532:
#line 1100 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 533:
#line 1101 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 534:
#line 1105 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 537:
#line 1111 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 538:
#line 1112 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 539:
#line 1113 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 542:
#line 1119 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 543:
#line 1123 "src/kinx.y"
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
