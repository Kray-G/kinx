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
#define OTHERWISE 273
#define ENUM 274
#define FALLTHROUGH 275
#define NEW 276
#define VAR 277
#define CONST 278
#define RETURN 279
#define THROW 280
#define YIELD 281
#define MIXIN 282
#define EQEQ 283
#define NEQ 284
#define LE 285
#define GE 286
#define LGE 287
#define LOR 288
#define LAND 289
#define INC 290
#define DEC 291
#define SHL 292
#define SHR 293
#define POW 294
#define LUNDEF 295
#define PIPEOPL2R 296
#define PIPEOPR2L 297
#define FCOMPOSL2R 298
#define FCOMPOSR2L 299
#define ADDEQ 300
#define SUBEQ 301
#define MULEQ 302
#define DIVEQ 303
#define MODEQ 304
#define ANDEQ 305
#define OREQ 306
#define XOREQ 307
#define LANDEQ 308
#define LOREQ 309
#define LUNDEFEQ 310
#define SHLEQ 311
#define SHREQ 312
#define REGEQ 313
#define REGNE 314
#define NUL 315
#define TRUE 316
#define FALSE 317
#define AS 318
#define IMPORT 319
#define USING 320
#define DARROW 321
#define SQ 322
#define DQ 323
#define MLSTR 324
#define BINEND 325
#define DOTS2 326
#define DOTS3 327
#define REGPF 328
#define NAMESPACE 329
#define SYSNS 330
#define SYSRET_NV 331
#define CLASS 332
#define SYSCLASS 333
#define MODULE 334
#define SYSMODULE 335
#define NATIVE 336
#define FUNCTION 337
#define SYSFUNC 338
#define PUBLIC 339
#define PRIVATE 340
#define PROTECTED 341
#define COROUTINE 342
#define NAME 343
#define STR 344
#define SRCFILE 345
#define BIGINT 346
#define INT 347
#define TYPE 348
#define TYPEOF 349
#define LBBR 350
#define RBBR 351
#define LMBR 352
#define RMBR 353
#define DBL 354
#define BIN 355
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
#line 1131 "src/kinx.y"

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
  "OTHERWISE",
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
  "CaseStatement : OTHERWISE ':'",
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
  "CaseElseClause : OTHERWISE Colon_Opt WhenClauseBody",
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
  "PropertyName : OTHERWISE",
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
  "ClassFunctionSpecialName : OTHERWISE",
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
    0,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  115,  117,  117,  117,  113,  106,  117,
  101,  102,  111,  110,   99,   98,  103,  112,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  100,   97,
  108,   96,  109,  107,  116,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  105,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  104,  117,  114,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
  117,  117,  117,  117,  117,  117,    1,  117,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
   64,   65,  117,  117,  117,   66,   67,   68,   69,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,   92,   93,   94,   95,  117
#line 165 "build/utility/kmyacc.c.parser"
};

#define YYBADCH 117
#define YYMAXLEX 356
#define YYTERMS 117
#define YYNONTERMS 124

static short yyaction[] = {
  848,  849,  851,  852,  853,  854,  855,  856,  857,  858,
  859,  860,  861,  863,  862,  850,   96,  171,  864,  865,
  866,  875,  877,  876,  479,  887,  888,  889,  891,  893,
   39,  820,  821, 1105,  885,  886,  884,   80,  883,   39,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,   92,   93,  391,  392,   14,  393,  878,  879,  880,
    0,  881,  882,  394,  116,  395,  108,  396,  915,  131,
  132,  873,  104,  874,  113,  867,  868,  869,  870,  871,
  872,  150,  846,  143,  144,  145,  270,  847,-32766, 1105,
  118,  455,   95,  151,  416,   39,  895,  837,   49,  456,
   28,  628,  900,  901,  899,-32766,  890,  892,  894,  896,
  897,  898,  972,  973,  975,  976,  977,  978,  979,  980,
  981,  982,  983,  984,  985,  172,  986,  974,   17,  349,
  987,  988,  989,  997,  999,  998,  129, 1010, 1011, 1012,
 1014, 1016,  171,  350,  119,  610, 1008, 1009, 1007,  844,
   80,-32766,-32766,-32766,  845,  532,   42,-32766,   45,  152,
  153,  154,  146,  147,  459,  391,  392,   14,  393, 1000,
 1001, 1002,  -82, 1003, 1004,  394,  107,  395,  108,  396,
-32766,  914,    1,  995,    3,  996,  416,  113,  990,  991,
  992,  993,  994,  125, 1064, 1088,  123,  173,  244, 1005,
 1006,  102,  343,  433,   51, -375,   31,  344, 1018,  101,
   39,  434, -375,   69, 1023, 1024, 1022,  255, 1013, 1015,
 1017, 1019, 1020, 1021,  177,  438,  391,  439,    9,  440,
  942,  332,  944,  945,  250,  251,  441,  111,  395,  112,
  396,  397,  398,  169,  247,  248,  333,   54,   61,  320,
 1049,  502,  503,   39,   38,  662,  504,  471,    2,  316,
  114,  122,  202, -405,   41,  337,   45,  121,   48,   50,
   27,   30, -111,   99,   66,  613,   29,  254,  204,  271,
   60,   98,  442,  443,  444,  550,  286,  969, -491,  141,
  142,   79,  -81,  322,  323,  399,  445,  401,  446,  403,
  447,  287,  288,   35,   36,   37,    2,  448,  114,  315,
  347,   39,  449,  971,    1,  601,   48,  171,   27,-32766,
 -107,  454, -111,  253,   59,  121,   80,   39,  938,  268,
  939,  940,  941,  942,  943,  944,  945,  946,  947,  948,
  949,  426,  950,  205,  206,  136,  169,  952,  953,  962,
  964,  963,  904,  844,  148,  149,  137,  914,  845,  155,
-32766,-32766,  105,  113,  133,  134,  159,  160,  135,  122,
  161,  162,  389,  117,  269,  328,  907,   50,  329,   30,
  100,  513,  330,  331,   39,  442,  443,  444,  431,  466,
  969,  103, 1075,  222,   79,  432,  140,  906,  316,  960,
  315,  961,  474,  954,  955,  956,  957,  958,  959,-32766,
  467,  458,  469,  611,  664,  449,  971,  585,  690,  587,
  586,  588,  472,  589,-32766,  607,  253,   59,  590,  591,
  663,  529,  468,  592,  533,  843,-32766,-32766,  535,  531,
-32766,-32766,  938,  614,  939,  940,  941,  942,  943,  944,
  945,  946,  947,  948,  949,  729,  950,  694,  841,  812,
  169,  952,  953,  962,  964,  963,  714,  608,  270,    3,
   38,   40,    1,  326,-32766,-32766,    5,    4,  902,  817,
  909,  818,  506,  520,  537,    0, 1092, 1091,  593,  905,
 1073, 1025,  727,  594,  692,  596,  595,  810,   74,  442,
  443,  444,   68,  466,  969,   67,  584,  575,   79,  512,
  313,  249,  583,  960,  307,  961,  661,  954,  955,  956,
  957,  958,  959,-32766,  467,  652,  650,  656,  654,  449,
  971,  574,  925,  651,  649,  665,  655,   22,-32766,  653,
  253,   59,   75,   73,   72,   71,  468,   70,  625, 1032,
-32766,-32766, 1033,  115,-32766,-32766,  938,   62,  939,  940,
  941,  942,  943,  944,  945,  946,  947,  948,  949,   53,
  950,   43,  120,  236,  169,  952,  953,  962,  964,  963,
 -406,  628,  630,  202, -411, -408, -407, -403,-32766,-32766,
 -395,   44,   55,   56,   57,  748,  632,  629,  631,  558,
  258,  256, -404,  130,  203,  253,    0,  220,  228,  221,
  219,  218,  217,  442,  443,  444,   97,  466,  969,   94,
  223,   78,   79,   77,   76,  501,  473,  960,  428,  961,
  234,  954,  955,  956,  957,  958,  959,-32766,  467,  427,
  257,  235,  233,  449,  971,  232,  927,  231,  230,  229,
  227,  226,-32766,  225,  253,   59,  224,   52,  139,   15,
  468,   16,   18,   19,-32766,-32766,   20,   21,-32766,-32766,
  938,  348,  939,  940,  941,  942,  943,  944,  945,  946,
  947,  948,  949,  539,  950,  672,  836,  732,  169,  952,
  953,  962,  964,  963, 1096, 1094,  730,  835,  739,  646,
  695, 1077,-32766,-32766,  813, 1031,  903,  838, 1026,  536,
  523,  384,  383,  382,  381,  380,  373,  371,  370,  368,
  367,  366,  364,  361,  358,  357,  356,  442,  443,  444,
  355,  466,  969,  354,   24,   23,   79,    0,  138,    0,
    0,  960,  468,  961,    0,  954,  955,  956,  957,  958,
  959,-32766,  467,    0,    0,    0,    0,  449,  971,    0,
    0,    0,    0,    0,    0,    0,-32766,    0,  253,   59,
    0,    0,    0,    0,  468,    0,    0,    0,-32766,-32766,
    0,    0,-32766,-32766,  938,    0,  939,  940,  941,  942,
  943,  944,  945,  946,  947,  948,  949,    0,  950,    0,
    0,    0,  169,  952,  953,  962,  964,  963,    0,    0,
    0,    0,    0,    0,    0,    0,-32766,-32766,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  442,  443,  444,    0,  466,  969,    0,    0,    0,
   79,    0,    0,    0,    0,  960,    0,  961,    0,  954,
  955,  956,  957,  958,  959,-32766,  467,    0,    0,    0,
    0,  449,  971,    0,    0,    0,    0,    0,    0,    0,
-32766,    0,    0,   59,    0,    0,    0,    0,-32766,    0,
    0,    0,-32766,-32766,    0,    0,-32766,-32766,  177,  390,
  391,  392,   14,  393,    0,  319,    0,    0,  265,  266,
  394,  107,  395,  108,  396,  397,  398,    0,  245,  246,
  555,   64,  109,  320,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  272,    0, -491,    0,    0,    0,    0,  322,  323,  399,
  400,  401,  402,  403,    0,  273,  274,   32,   33,   34,
    0,  405,    0,    0,    0,    0,    0,    0,    1,  601,
    0,    0,    0,    0, -107,    0,    0,  253,    0,    0,
    0,    0,    0,  268,  177,  390,  391,  392,   14,  393,
    0,  319,    0,    0,  265,  266,  394,  107,  395,  108,
  396,  397,  398,    0,  245,  246,  555,   64,  109,  320,
    0,    0,    0,    0,   -1,  177,  390,  391,  392,   14,
  393,    0,  319,    0,    0,  265,  266,  394,  107,  395,
  108,  396,  397,  398,    0,  245,  246,  555,   64,  109,
  320,    0,    0,    0,    0,    0,  272,    0,    0,    0,
    0,    0,    0,  322,  323,  399,  400,  401,  402,  403,
    0,  273,  274,   32,   33,   34,    0,  405,    0,    0,
    0,    0,    0,    0,    1,    0,    0,  272,    0,    0,
 -107,    0,    0, -381,  322,  323,  399,  400,  401,  402,
  403,    0,  273,  274,   32,   33,   34,    0,  405,    0,
    0,    0,    0,    0,    0,    1,    0,    0,    0,    0,
    0, -107,  177,  390,  391,  392,   14,  393,    0,  319,
    0,    0,  265,  266,  394,  107,  395,  108,  396,  397,
  398,    0,  245,  246,  555,   64,  109,  320,    0,    0,
    0,    0,  177,  390,  391,  392,   14,  393,    0,  319,
    0,    0,  265,  266,  394,  107,  395,  108,  396,  397,
  398,    0,  245,  246,  555,   64,  109,  320,    0,    0,
    0,    0,    0,    0,  272,    0,    0,    0,    0,    0,
    0,  322,  323,  399,  400,  401,  402,  403,    0,  273,
  274,   32,   33,   34,    0,  405,    0,    0,    0,    0,
    0,    0,    1,  819,  272,    0,    0,    0, -107,    0,
    0,  322,  323,  399,  400,  401,  402,  403,    0,  273,
  274,   32,   33,   34,    0,  405,    0,    0,    0,    0,
    0,    0,    1,  606,    0,    0,    0,    0, -107,  177,
  390,  391,  392,   14,  393,    0,  319,    0,    0,  265,
  266,  394,  107,  395,  108,  396,  397,  398,    0,  245,
  246,  555,   64,  109,  320,    0,    0,    0,    0,  177,
  390,  391,  392,   14,  393,    0,  319,    0,    0,  265,
  266,  394,  107,  395,  108,  396,  397,  398,    0,  245,
  246,  555,   64,  109,  320,    0,    0,    0,    0,    0,
    0,  272,    0,    0,    0,    0,    0,    0,  322,  323,
  399,  400,  401,  402,  403,    0,  273,  274,   32,   33,
   34,    0,  405,    0,    0,    0,    0,    0,    0,    1,
  605,  272,    0,    0,    0, -107,    0,    0,  322,  323,
  399,  400,  401,  402,  403,    0,  273,  274,   32,   33,
   34,    0,  405,    0,    0,    0,    0,    0,    0,    1,
  604,    0,    0,    0,    0, -107,  177,  390,  391,  392,
   14,  393,    0,  319,    0,    0,  265,  266,  394,  107,
  395,  108,  396,  397,  398,    0,  245,  246,  555,   64,
  109,  320,    0,    0,    0,    0,  177,  390,  391,  392,
   14,  393,    0,  319,    0,    0,  265,  266,  394,  107,
  395,  108,  396,  397,  398,    0,  245,  246,  555,   64,
  109,  320,    0,    0,    0,    0,    0,    0,  272,    0,
    0,    0,    0,    0,    0,  322,  323,  399,  400,  401,
  402,  403,    0,  273,  274,   32,   33,   34,    0,  405,
    0,    0,    0,    0,    0,    0,    1,  603,  272,    0,
  124,    0, -107,    0,    0,  322,  323,  399,  400,  401,
  402,  403,    0,  273,  274,   32,   33,   34,    0,  405,
    0,    0,    0,    0,    0,    0,    1,    0,    0,    0,
    0,    0, -107,  177,  390,  391,  392,   14,  393,    0,
  319,    0,    0,  265,  266,  394,  107,  395,  108,  396,
  397,  398,    0,  245,  246,  555,   64,  109,  320,    0,
    0,    0,  177,  390,  391,  392,   14,  393,    0,  319,
    0,    0,  265,  266,  394,  107,  395,  108,  396,  397,
  398,    0,  245,  246,  555,   64,  109,  320,    0,    0,
    0,    0,    0,    0,    0,  272,    0,  106,    0,    0,
    0,    0,  322,  323,  399,  400,  401,  402,  403,    0,
  273,  274,   32,   33,   34,    0,  405,    0,    0,    0,
    0,    0,    0,    1,  272,    0,    0,    0,    0, -107,
    0,  322,  323,  399,  400,  401,  402,  403,    0,  273,
  274,   32,   33,   34,    0,  405,    0,    0,    0,    0,
    0,    0,    1,  601,    0,    0,    0,    0, -107,  177,
  390,  391,  392,   14,  393,    0,  319,    0,    0,  265,
  266,  394,  107,  395,  108,  396,  397,  398,    0,  245,
  246,  555,   64,  109,  320,    0,    0,    0,    0,  177,
  390,  391,  392,   14,  393,    0,  319,    0,    0,  265,
  266,  394,  107,  395,  108,  396,  397,  398,    0,  245,
  246,  555,   64,  109,  320,    0,    0,    0,    0,    0,
    0,  272,    0,    0,    0,    0,    0,    0,  322,  323,
  399,  400,  401,  402,  403,    0,  273,  274,   32,   33,
   34,    0,  405,    0,    0,    0,    0,    0,    0,    1,
  602,  272,    0,    0,    0, -107,    0,    0,  322,  323,
  399,  400,  401,  402,  403,    0,  273,  274,   32,   33,
   34,  110,  405,    0,    0,    0,    0,  168,    0,    1,
    0,    0,    0,    0,    0, -107,    0,    0,    0,    0,
    0,  163,  164,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  556,    0,    0,    0,    0,    0,
    0,-32766,    0,    0,    0,    0,  825,  826,  827,    0,
  419,    0,    0,    0,    0,    0,  321,    0,    0,    0,
    0,-32766,-32766,    0, 1049,  420,  421,    0,    0,    0,
  404,  844,    0,  828,  824,  822,  845,    0,   41,  170,
   45,    0,  823,    0,    0,  165,    0,    0,   58,    0,
   25,    0,    0,  267,    0,  324,    0,  166,  156,  557,
    0,  157,  158,   26,-32766,-32766,-32766,    0,    0,    0,
-32766,    0,    0,    0,    0,    0,    0,    0,  736,  737,
  738,    0,    0,    0,    0,-32766,    0,    0,    0,    0,
    0,    0,    0,-32766,    0,    0,    0,-32766,-32766,    0,
    0,-32766,-32766,  844,    0,    0,  735,  733,  845,    0,
    0,    0,    0,    0,  734,    0,    0,    0,    0,    0,
   63
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1911

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   17,   68,   16,   20,   21,
   22,   23,   24,   25,   85,   27,   28,   29,   30,   31,
   91,   34,   35,   85,   36,   37,   38,   68,   40,   91,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,    3,    4,    5,    6,   59,   60,   61,
    0,   63,   64,   13,   14,   15,   16,   17,   99,   40,
   41,   73,   68,   75,  105,   77,   78,   79,   80,   81,
   82,   98,   84,   29,   30,   31,   91,   89,   14,   85,
   93,   93,   96,  110,    2,   91,   98,  102,  101,  101,
  103,  100,  104,  105,  106,   14,  108,  109,  110,  111,
  112,  113,    2,    3,    4,    5,    6,    7,    8,    9,
   10,   11,   12,   13,   14,   32,   16,   17,    3,    3,
   20,   21,   22,   23,   24,   25,  107,   27,   28,   29,
   30,   31,   16,   17,   25,   88,   36,   37,   38,   84,
   68,   77,   78,   79,   89,   98,   91,   83,   93,  111,
  112,  113,  108,  109,    4,    3,    4,    5,    6,   59,
   60,   61,    7,   63,   64,   13,   14,   15,   16,   17,
  106,   99,   91,   73,   91,   75,    2,  105,   78,   79,
   80,   81,   82,  100,   84,   77,   93,  104,   21,   89,
   90,    7,   84,   93,  101,   92,  103,   89,   98,    7,
   91,  101,   99,   96,  104,  105,  106,  100,  108,  109,
  110,  111,  112,  113,    1,    2,    3,    4,    5,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
   77,   78,   79,   91,   91,   97,   83,   99,   91,   84,
   93,   93,  100,  100,   91,    9,   93,  105,  101,  101,
  103,  103,   97,    7,   97,   88,  103,   62,  105,  106,
   96,    7,   59,   60,   61,   98,   63,   64,   65,   27,
   28,   68,    7,   70,   71,   72,   73,   74,   75,   76,
   77,   78,   79,   80,   81,   82,   91,   84,   93,   84,
   10,   91,   89,   90,   91,   92,  101,   16,  103,   14,
   97,   85,   97,  100,  101,  105,   68,   91,    2,  106,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   21,   16,   67,   68,   32,   20,   21,   22,   23,
   24,   25,   94,   84,   36,   37,   33,   99,   89,   38,
   34,   35,   65,  105,   42,   43,   57,   58,   39,   93,
   67,   68,   65,   65,   68,   84,   66,  101,   84,  103,
   68,   85,   84,   84,   91,   59,   60,   61,   84,   63,
   64,   96,   90,  101,   68,   84,  106,  109,   84,   73,
   84,   75,   85,   77,   78,   79,   80,   81,   82,   83,
   84,   84,   84,   88,   84,   89,   90,    2,   92,    4,
    5,    6,   84,    8,   98,   84,  100,  101,   13,   14,
   84,   84,  106,   18,   84,   90,  110,  111,   85,   85,
  114,  115,    2,   88,    4,    5,    6,    7,    8,    9,
   10,   11,   12,   13,   14,   90,   16,   90,   90,   90,
   20,   21,   22,   23,   24,   25,   90,   92,   91,   91,
   91,   91,   91,   91,   34,   35,   91,   91,   94,   92,
   92,   92,   99,   93,   93,   -1,   94,   94,   73,   94,
   94,   94,   94,   78,   94,   80,   81,   94,   96,   59,
   60,   61,   96,   63,   64,   96,   91,   92,   68,   96,
   96,   99,   97,   73,   96,   75,   97,   77,   78,   79,
   80,   81,   82,   83,   84,   97,   97,   97,   97,   89,
   90,   97,   92,   97,   97,   97,   97,  102,   98,   97,
  100,  101,   97,   97,   97,   97,  106,   97,   97,   97,
  110,  111,   97,   99,  114,  115,    2,   99,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   99,
   16,   99,   99,   99,   20,   21,   22,   23,   24,   25,
  100,  100,  100,  100,  100,  100,  100,  100,   34,   35,
  100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
  100,  100,  100,  100,  100,  100,   -1,  101,  101,  101,
  101,  101,  101,   59,   60,   61,  101,   63,   64,  101,
  101,  101,   68,  101,  101,  101,  101,   73,  101,   75,
  101,   77,   78,   79,   80,   81,   82,   83,   84,  101,
  101,  101,  101,   89,   90,  101,   92,  101,  101,  101,
  101,  101,   98,  101,  100,  101,  101,  101,  105,  102,
  106,  102,  102,  102,  110,  111,  102,  102,  114,  115,
    2,  102,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,  102,   16,  102,  102,  102,   20,   21,
   22,   23,   24,   25,  102,  102,  102,  102,  102,  102,
  102,  102,   34,   35,  102,  102,  102,  102,  102,  102,
  102,  102,  102,  102,  102,  102,  102,  102,  102,  102,
  102,  102,  102,  102,  102,  102,  102,   59,   60,   61,
  102,   63,   64,  102,  102,  102,   68,   -1,  104,   -1,
   -1,   73,  106,   75,   -1,   77,   78,   79,   80,   81,
   82,   83,   84,   -1,   -1,   -1,   -1,   89,   90,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   98,   -1,  100,  101,
   -1,   -1,   -1,   -1,  106,   -1,   -1,   -1,  110,  111,
   -1,   -1,  114,  115,    2,   -1,    4,    5,    6,    7,
    8,    9,   10,   11,   12,   13,   14,   -1,   16,   -1,
   -1,   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   34,   35,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   59,   60,   61,   -1,   63,   64,   -1,   -1,   -1,
   68,   -1,   -1,   -1,   -1,   73,   -1,   75,   -1,   77,
   78,   79,   80,   81,   82,   83,   84,   -1,   -1,   -1,
   -1,   89,   90,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   98,   -1,   -1,  101,   -1,   -1,   -1,   -1,  106,   -1,
   -1,   -1,  110,  111,   -1,   -1,  114,  115,    1,    2,
    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   17,   18,   19,   -1,   21,   22,
   23,   24,   25,   26,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   63,   -1,   65,   -1,   -1,   -1,   -1,   70,   71,   72,
   73,   74,   75,   76,   -1,   78,   79,   80,   81,   82,
   -1,   84,   -1,   -1,   -1,   -1,   -1,   -1,   91,   92,
   -1,   -1,   -1,   -1,   97,   -1,   -1,  100,   -1,   -1,
   -1,   -1,   -1,  106,    1,    2,    3,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   17,   18,   19,   -1,   21,   22,   23,   24,   25,   26,
   -1,   -1,   -1,   -1,    0,    1,    2,    3,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   -1,   21,   22,   23,   24,   25,
   26,   -1,   -1,   -1,   -1,   -1,   63,   -1,   -1,   -1,
   -1,   -1,   -1,   70,   71,   72,   73,   74,   75,   76,
   -1,   78,   79,   80,   81,   82,   -1,   84,   -1,   -1,
   -1,   -1,   -1,   -1,   91,   -1,   -1,   63,   -1,   -1,
   97,   -1,   -1,  100,   70,   71,   72,   73,   74,   75,
   76,   -1,   78,   79,   80,   81,   82,   -1,   84,   -1,
   -1,   -1,   -1,   -1,   -1,   91,   -1,   -1,   -1,   -1,
   -1,   97,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   -1,   21,   22,   23,   24,   25,   26,   -1,   -1,
   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   -1,   21,   22,   23,   24,   25,   26,   -1,   -1,
   -1,   -1,   -1,   -1,   63,   -1,   -1,   -1,   -1,   -1,
   -1,   70,   71,   72,   73,   74,   75,   76,   -1,   78,
   79,   80,   81,   82,   -1,   84,   -1,   -1,   -1,   -1,
   -1,   -1,   91,   92,   63,   -1,   -1,   -1,   97,   -1,
   -1,   70,   71,   72,   73,   74,   75,   76,   -1,   78,
   79,   80,   81,   82,   -1,   84,   -1,   -1,   -1,   -1,
   -1,   -1,   91,   92,   -1,   -1,   -1,   -1,   97,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   19,   -1,   21,
   22,   23,   24,   25,   26,   -1,   -1,   -1,   -1,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   19,   -1,   21,
   22,   23,   24,   25,   26,   -1,   -1,   -1,   -1,   -1,
   -1,   63,   -1,   -1,   -1,   -1,   -1,   -1,   70,   71,
   72,   73,   74,   75,   76,   -1,   78,   79,   80,   81,
   82,   -1,   84,   -1,   -1,   -1,   -1,   -1,   -1,   91,
   92,   63,   -1,   -1,   -1,   97,   -1,   -1,   70,   71,
   72,   73,   74,   75,   76,   -1,   78,   79,   80,   81,
   82,   -1,   84,   -1,   -1,   -1,   -1,   -1,   -1,   91,
   92,   -1,   -1,   -1,   -1,   97,    1,    2,    3,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   16,   17,   18,   19,   -1,   21,   22,   23,   24,
   25,   26,   -1,   -1,   -1,   -1,    1,    2,    3,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   16,   17,   18,   19,   -1,   21,   22,   23,   24,
   25,   26,   -1,   -1,   -1,   -1,   -1,   -1,   63,   -1,
   -1,   -1,   -1,   -1,   -1,   70,   71,   72,   73,   74,
   75,   76,   -1,   78,   79,   80,   81,   82,   -1,   84,
   -1,   -1,   -1,   -1,   -1,   -1,   91,   92,   63,   -1,
   65,   -1,   97,   -1,   -1,   70,   71,   72,   73,   74,
   75,   76,   -1,   78,   79,   80,   81,   82,   -1,   84,
   -1,   -1,   -1,   -1,   -1,   -1,   91,   -1,   -1,   -1,
   -1,   -1,   97,    1,    2,    3,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   16,   17,
   18,   19,   -1,   21,   22,   23,   24,   25,   26,   -1,
   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   -1,   21,   22,   23,   24,   25,   26,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   63,   -1,   65,   -1,   -1,
   -1,   -1,   70,   71,   72,   73,   74,   75,   76,   -1,
   78,   79,   80,   81,   82,   -1,   84,   -1,   -1,   -1,
   -1,   -1,   -1,   91,   63,   -1,   -1,   -1,   -1,   97,
   -1,   70,   71,   72,   73,   74,   75,   76,   -1,   78,
   79,   80,   81,   82,   -1,   84,   -1,   -1,   -1,   -1,
   -1,   -1,   91,   92,   -1,   -1,   -1,   -1,   97,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   19,   -1,   21,
   22,   23,   24,   25,   26,   -1,   -1,   -1,   -1,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   19,   -1,   21,
   22,   23,   24,   25,   26,   -1,   -1,   -1,   -1,   -1,
   -1,   63,   -1,   -1,   -1,   -1,   -1,   -1,   70,   71,
   72,   73,   74,   75,   76,   -1,   78,   79,   80,   81,
   82,   -1,   84,   -1,   -1,   -1,   -1,   -1,   -1,   91,
   92,   63,   -1,   -1,   -1,   97,   -1,   -1,   70,   71,
   72,   73,   74,   75,   76,   -1,   78,   79,   80,   81,
   82,   14,   84,   -1,   -1,   -1,   -1,   20,   -1,   91,
   -1,   -1,   -1,   -1,   -1,   97,   -1,   -1,   -1,   -1,
   -1,   34,   35,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   47,   -1,   -1,   -1,   -1,   -1,
   -1,   14,   -1,   -1,   -1,   -1,   59,   60,   61,   -1,
   63,   -1,   -1,   -1,   -1,   -1,   69,   -1,   -1,   -1,
   -1,   34,   35,   -1,   77,   78,   79,   -1,   -1,   -1,
   83,   84,   -1,   86,   87,   88,   89,   -1,   91,   20,
   93,   -1,   95,   -1,   -1,   98,   -1,   -1,  101,   -1,
  103,   -1,   -1,  106,   -1,  108,   -1,  110,  111,  112,
   -1,  114,  115,  116,   77,   78,   79,   -1,   -1,   -1,
   83,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,   60,
   61,   -1,   -1,   -1,   -1,   98,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  106,   -1,   -1,   -1,  110,  111,   -1,
   -1,  114,  115,   84,   -1,   -1,   87,   88,   89,   -1,
   -1,   -1,   -1,   -1,   95,   -1,   -1,   -1,   -1,   -1,
  101
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1668,  223,  897, 1541, 1385, 1288, 1512, 1415, 1034, 1003,
 1638, 1258, 1161, 1131, 1668, 1668, 1668, 1668, 1668, 1668,
 1668, 1668, 1668, 1668, 1668,  368,  345,  369,  367,  376,
  365,  302,  110,  110,  110,  110,  110,  110,  440,  326,
  554,  668,  782,  782,  162,  258,   82,  -31,  -52,  -52,
  -52,  -52,  177,    4,  163,  220,  220,  220,  236,  -61,
  119,  502,  312,  354,  379,  379,  379,  293,  293,  293,
  379,  379,  379,  379,  293,  379, 1737, 1737, 1737,  293,
  293,  293,  293,  293,  293,  293,  293,  293,  293,  293,
  293,  293,  293,  293, 1737,  293,  293, 1737, 1737, 1737,
  293, 1737, 1737,  293,  293,  381,  381, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737,  380, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737,   91,   91,   91,   91,  305,
  305,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74, 1777, 1777, 1777, 1777, 1777, 1777, 1777,
 1777,  173,  173,  173,    1,  184,  301,  415,  482,  584,
  403,  481,  387,  400,  585,  398,  396,  389,  389,   -4,
   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
   -4,   -4,  378,  483, 1809, 1809, 1809,  215,   -5,  276,
  167,  167,  167,  167,  377,  377,  377,  306,  306,  306,
  306,  306,  306,  306,  306,  306,  306,  306,  306,  306,
  306,  306,  306,  306,  306,  306,  306,   93,  168,  168,
  168,   54,   54,   54,   65,   65,   65,   65,   65,   65,
  225,  175,  126,  118,  118,  118,  118,  118,  118,  103,
   48,   29,   48,   48,  194,  316,  314,  506,  507,  269,
  636,  529,  320,  304,  311,  262,  318,  -17,  309,  303,
  327,  322,  117,  452,  455,  158,  320,  304,  311,  113,
  557,  559,  450,  569,  262,  318,  318,  318,  318,  318,
  -17,  -17,  309,  322,  322,  448,  583,   57,  581,  560,
  561,  564,  565,  187,   92,   92,   92,   92,   92,  378,
  346,  527,  341,  341,  288,  256,  328,  527,  292,  292,
  378,  378,  378,  487,  472,  378,  527,  524,  300,  383,
  499,  499,  474,  390,  390,  470,  378,  378,  378,  495,
  495,  539,  378,  378,  505,  505,  505,  505,  500,  378,
  495,  505,  539,  378,  505,  378,  505,  505,  505,  378,
  505,  500,  378,  505,  378,  378,  378,  378,  378,  378,
  505,  505,  505,  505,  500,  378,  378,  378,  378,  378,
  523,  498,  522,  556,  520,  497,  496,  382,  442,  439,
  291,  294,  298,  299,  509,  504,   60,  438,  329,  313,
  323,  634,  553,  290,  321,  160,  518,  437,  436,  538,
  511,  510,  508,  409,  406,  454,  338,  525,  317,  386,
  385,  519,  555,  397,  606,  552,  550,  549,  523,  522,
  556,  520,  480,  486,  485,  291,  298,  490,  491,  484,
  492,  308,  395,  458,  605,  384,  604,  430,  548,  515,
  274,  285,  165,  266,  429,  428,  538,  493,  547,  418,
  419,  330,  413,  296,  603,  501,  631,  628,  624,  608,
  388,  458,  623,  310,  313,  323,  634,  553,  290,  321,
  321,  321,  602,  622,  503,  329,  329,  202,  409,  406,
  447,  347,  546,  544,  541,  540,  350,  375,  295,  295,
  295,  431,  353,  607,  599,  621,  620,  619,  618,  617,
  393,  391,  391,  494,  616,  598,  615,  125,  446,  597,
  614,  596,  325,  414,  402,  434,  595,  392,  297,  451,
  445,  435,  613,  612,  611,  610,  609,  594,  593,  633,
  355,  295,  632,  307,  592,    0,    0,    0,    0, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737,   -2,   -2,   -2,   -2,   -2,   -2,
   -2,    0,    0,    0,    0,    0,    0, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737,    0,    0,    0, 1737, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737,    0, 1737, 1737,    0,    0,    0, 1737,
    0,    0, 1737, 1737, 1737, 1737,    0,    0,    0,    0,
    0,    0,    0,    0, 1737,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737, 1737,
 1809, 1809, 1809,   -4,   -4,   -4,    0,   -4,   -4,   -4,
   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   50,   50,    0,    0,    0,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   65,   65,   65,   65,
   65,   65,   65,   65,   65,   65,   65,   65,   65,   65,
   65,   65,   65,   65,   65,   65,   92,   -3,   -3,   -3,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   92,
   92,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  117,   92,   92,  505,  505,    0,  505,
  505,  538,  511,  510,    0,    0,    0,    0,    0,  508,
    0,    0,  412,  412,    0,  538,  511,  510,    0,  473,
  473,  473,  473,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  412,  473,    0,  473,  473,  473,
  473,  473
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 313

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  398,  399,  400,  491,  491,
  491,  491,32767,  352,32767,32767,32767,32767,  538,  538,
  538,  538,32767,  352,  109,32767,32767,32767,32767,32767,
32767,   99,  360,32767,  109,  109,  109,32767,32767,32767,
  109,  109,  109,  109,32767,  109,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,   99,
32767,  390,  391,32767,32767,32767,32767,32767,32767,  101,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  235,  237,32767,32767,32767,32767,32767,32767,  392,
32767,32767,32767,32767,32767,  111,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  499,32767,  365,
   98,  357,  363,  358,  544,  367,  376,  361,  100,  364,
  377,  499,32767,32767,32767,  156,  158,  247,32767,  149,
  245,  246,  243,  242,  130,  545,  378,  519,  519,  519,
  519,  519,  519,  519,  519,  519,  519,  519,  519,  519,
  519,  519,  519,  519,  519,  519,  352,32767,  150,  157,
  159,  211,  212,  213,32767,32767,32767,  393,  394,32767,
  387,  388,  182,32767,32767,32767,32767,32767,32767,  536,
  223,  191,  225,  224,  477,  111,  111,  491,  491,32767,
  491,  491,32767,32767,32767,  209,  214,  220,  230,  232,
32767,  193,  477,32767,32767,32767,  409,  396,  397,  239,
32767,32767,32767,32767,  210,  216,  218,  219,  215,  217,
  221,  222,  231,  194,  195,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  111,  111,  111,  111,  111,32767,
32767,32767,32767,32767,  349,   84,32767,32767,  517,  517,
32767,32767,  384,  547,  351,32767,32767,   86,   88,  351,
  511,  511,  351,  531,  531,  351,32767,32767,32767,  188,
  188,  534,32767,32767,  491,  491,  491,  491,  493,32767,
  188,  491,  534,32767,  491,32767,  491,  491,  491,32767,
  491,  493,32767,  491,32767,32767,32767,32767,32767,32767,
  491,  491,  491,  491,  493,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  285,32767,32767,  196,  199,
  201,  203,  205,  207,  226,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  110,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  379,  380,
  382,  389,  266,  267,  268,  401,  402,  490,  285,  286,
32767,32767,32767,  353,32767,32767,32767,32767,32767,32767,
32767,  272,  273,  270,32767,32767,  409,  285,32767,   50,
32767,32767,32767,32767,32767,  523,32767,32767,32767,32767,
32767,  354,32767,32767,  200,  202,  204,  206,  208,  227,
  228,  229,32767,32767,32767,  197,  198,32767,   81,   82,
32767,32767,32767,32767,32767,32767,  352,32767,  481,  482,
  479,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  530,  528,  279,32767,32767,32767,   63,32767,32767,
32767,32767,32767,   53,  478,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  480,32767,32767,32767,  547,  471,  471,  547
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  196,  191,  191,  191,  194,  194,  194,  194,  192,  194,
  189,  196,  196,  196,  179,  179,  463,  190,  197,  184,
  189,  189,  189, 1059, 1059,  929,  189,  189,  189,  189,
  483,  189,  192,  192,  192,  667,  803,  799,  800,  792,
  793,  795,  797,  746,  746,  746,  746,  379,  436,  437,
  192,  436,  437,  192,  192,  192,  481,  192,  192, 1101,
  388,  201,  187,  174,  178,  190,  176,  174,  178,  193,
  180,  195,  181,  182,  183,  198,  199,  200,  185,  186,
  188,  303,  304,  280,  280,  280,  280,  280,  280,  280,
  280,  280,  280,  280,  280,  280,  280,  280,  280,  280,
  280,  280,  280,  280,  280,  280,  280,  280,  525,  547,
  554,  418,  295,  296,  297,  298,  299,  712,  712,  712,
  621,  290,  291,  293,  127,  815,  418,  485,  815,  815,
  815,  815,  509,  510,  128,  731,  731,  731,  551,  306,
  495,  496,  308,  309,  310,  484,  311,  312,  461,   11,
   12,   13,   13,  816,  696,  746,  816,  816,  816,  816,
  696,  696,  696,  305,  289,  284,  486,  284,  731,  731,
  731,  489,  490,  491,  457,  464,  465,  470,  511,  487,
  619,  475,  475,  475,  475,  475,  475,  475,  475,  475,
  475,  475,  475,  475,  475,  475,  475,  475,  475,  475,
  475,  934,  934,  934,  934,  934,  934,  561,  264,  282,
  282,  282,  282,  282,  462,  562,  415,  564,  564,  564,
  564,  415,  527,  624,  623,  638,  636,  639,  637,  635,
  634,  633,  488, 1086,  318,  500,  932,  325,  930,  528,
  540,  541,  549, 1028,  552,  742,  743,  703, 1068, 1069,
  325,  294, 1027, 1060,  505,  505,  505,  242,  243,  335,
  335,  300,  301,  359,  644,  648,  626,  710,  710,  710,
 1066, 1067,  807,  351,  362,  548, 1053,  724,  691,  726,
  302, 1054, 1081, 1055,  691,  691,  691, 1056,  262,  263,
 1057,  360, 1046, 1047, 1061, 1062, 1063, 1048,  210,  211,
  212,  213,  702,  719,  720,  721,  722,  723,  726,  726,
  726,  706,  705, 1084, 1084, 1084, 1084, 1084, 1084, 1084,
 1084, 1084, 1084, 1084, 1084, 1084, 1084, 1084, 1084, 1084,
 1084, 1084, 1084,  711,  711,  711,  497, 1035,  620,  619,
  498,  423,  423,  423,  423,  423,  363,  365,  369,  538,
  700,  507,  341,  374, 1079,  430,  375, 1098,  376,  377,
  378,  353,    6, 1083,  336,    7,  842,  811,  693,  713,
  728, 1074,  385,  386,  387,  553,  238,  239,  240, 1085,
 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085,
 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085,  745,
  745,  745,  745,  494,  751,  688,  499,  424,  424,  424,
  424,  424,  688,  688,  688, 1072,  839,  839,  740,  688,
  522,  167,    0,    0,  688,  688,  688,  688,  688,  688,
  688,  688,  688,  688,  688,  688,  688,  688,  688,  674,
  688,  688,    0,    0,    0,  688,    0,    0,  688,  688,
    0,    0,    0,    0,    0,    0,    0,    0,  933,  918,
  677,  678,  679,  680,  681,  682,  683,  684,  685,  686,
  687,  675,  676,    0,  674, 1100,    0,    0,    0,  921,
    0,    0, 1043, 1102,  477,  478,  482,  493,  514,  515,
  516,  517,  518,  519,  524,  526,  530,  542,  543,  544,
  545,  546,  216,    0,    0,    0,  215,  215,  215,  215,
    0,  215,    0,  216,  216,  216,  208,  208
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 518

static char yygcheck[] = {
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   74,   37,   37,   37,
   37,   37,   37,    7,    7,   72,   37,   37,   37,   37,
   66,   37,   37,   37,   37,   31,   55,   55,   55,   55,
   55,   55,   55,    7,    7,    7,    7,  102,   76,   76,
   37,   76,   76,   37,   37,   37,   67,   37,   37,  100,
  102,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,  108,  108,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   98,   98,
   98,   31,   50,   50,   50,   50,   50,   97,   97,   97,
    7,   69,   69,   69,  121,    7,   31,   44,    7,    7,
    7,    7,   81,   81,  121,   74,   74,   74,   81,   69,
   42,   42,   69,   69,   69,   43,   69,   69,   62,    3,
    3,    3,    3,   97,   97,    7,   97,   97,   97,   97,
   97,   97,   97,   79,   56,   79,   45,   79,   74,   74,
   74,   53,   53,   53,   31,   31,   31,   31,   31,   46,
   35,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   56,   56,   56,   56,   56,   56,    4,   74,   74,
   74,   74,   74,   74,   63,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,   47,   74,   40,   40,   73,    7,   73,   40,
   40,   40,   40,   65,   40,  118,  118,  118,    7,    7,
    7,   48,   65,    7,   82,   82,   82,   49,   49,  101,
  101,   51,   51,  101,    7,    7,    7,   62,   62,   62,
    7,    7,  103,  103,  103,  103,  103,    7,   59,   59,
   54,    7,   95,    7,   59,   59,   59,    7,   52,   52,
    7,   32,    7,    7,    7,    7,    7,    7,   57,   57,
   57,   57,  119,    7,    7,    7,    7,    7,   59,   59,
   59,  113,  113,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   63,   63,   63,   19,   80,   35,   35,
   62,   62,   62,   62,   62,   62,  101,  101,  101,  101,
  111,  120,   91,  101,  120,    9,  101,  120,  101,  101,
  101,   89,  101,  105,  123,  101,   58,   58,   58,   58,
   58,   58,  101,  101,  101,  101,  114,  114,  114,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   41,
   41,   41,   41,   41,   41,  109,   63,   63,   63,   63,
   63,   63,  109,  109,  109,   60,   60,   60,   60,  109,
  104,  106,   -1,   -1,  109,  109,  109,  109,  109,  109,
  109,  109,  109,  109,  109,  109,  109,  109,  109,   38,
  109,  109,   -1,   -1,   -1,  109,   -1,   -1,  109,  109,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   38,   -1,   38,   38,   -1,   -1,   -1,   38,
   -1,   -1,   38,   38,   93,   93,   93,   93,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   93,   93,   39,   -1,   -1,   -1,   39,   39,   39,   39,
   -1,   39,   -1,   39,   39,   39,   39,   39
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  145,  207,    0,    0,  -82,    0,   32,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   92,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -140,   54,    0,    0,  136,    0,  -44,  379,  458,
  169,  274,    7,   10,   -9,   29,   41,   93,  111,  116,
  -31,  113,  138,   19,  125, -120,  163,  135,  340,   70,
  248,    0,   96,  162,    0,  -84,  -16,    9,    0,   45,
    0,    0,  -18,  181,  -36,    0,   15,    0,    0,  -81,
   88,   64,   83,    0,    0,    0,    0,    0,    0,   20,
    0,   23,    0,  266,    0,   46,    0,  -54,   59,    0,
    6,   -8, -324,   18,   76,    1, -137,    0,  -50,  345,
    0,   98,    0,  139,  172,    0,    0,    0,  119,   65,
   12, -226,    0, -193
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  406,    8,   10,  563,  566,  565,  567,  568,  429,
  569,  339,  581,  570,  597,  598,  599,  627,  600,  460,
  571,  338,  346,  642,  576,  577,  314,  578,  579,  285,
  580,  417,  671,  582,  572,  573,  407,  175, 1042,  214,
  317,  697,  408,  409,  410,  411,  412,  413,  275,  241,
  276,  277,  260,  414,  278,  279,  798,  207,  840,  809,
  808,  830,  831,  832,  833, 1029,  452,  453,   47,  292,
  425,  334,  928,  931,  829,  450,  435, 1065,  615,  283,
 1034,  508,  422,  616, 1044,  749, 1045,  617,  618,  352,
  259,  340, 1071,  476,  342, 1080,  814,  834,  492,  345,
 1099,  451,  372, 1051,  521,  534,   65,  261,  281,  673,
  252,  699,  237,  704,  209,  707,  725,  698,  701,  744,
  480,  126,   46,  327
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
   17,   17,   17,   17,   18,   18,   18,   18,   18,   18,
   18,   19,   19,   20,   21,   21,   22,   22,   23,   23,
   33,   33,   33,   33,   33,   24,   24,   25,   26,   26,
   26,   26,   27,   28,   29,   29,   30,   36,   36,   40,
   40,   31,   31,   32,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   38,
   38,   39,   39,   39,   39,   39,   39,   39,  109,  109,
  110,  110,  111,  111,  111,  112,  112,  112,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  115,  115,  115,  115,  115,  115,  114,  114,  114,  114,
  114,  114,  116,  116,  116,  116,  116,  116,  116,  116,
  116,  116,  117,  117,  117,  118,  118,  119,  121,  121,
   41,   41,   41,  107,  107,  107,  108,  108,  108,   42,
   42,   43,   43,   44,   44,   45,   45,   46,   46,   47,
   47,   48,   48,   48,   49,   49,   49,   49,   49,   49,
   50,   50,   50,   51,   51,   51,   52,   52,   52,   52,
   53,   53,   54,   54,   54,   54,   54,   54,   54,   55,
   55,   55,   55,   55,   55,   55,   55,   56,   56,   57,
   57,   57,   57,   57,   57,   57,   96,   96,   97,   97,
   97,   59,   59,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   60,   60,   74,   74,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   62,   62,   61,   61,  122,
   63,  120,  120,   66,   66,   68,   68,   67,   67,   67,
   67,   67,   67,   69,   69,   70,   70,   70,   70,   71,
   71,   72,   72,   72,   72,   72,   73,   73,   73,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   64,   64,
   64,  123,   65,   78,   78,   79,   79,   80,   80,   80,
   80,   80,   80,   81,   81,   83,   83,   84,   84,   84,
   82,  101,  101,  102,  102,   85,   85,   85,   85,   85,
   85,   85,   86,   86,   86,   76,   76,   87,   87,   88,
   88,   89,   89,   90,   90,   90,   90,   91,   91,   93,
   93,   94,   94,   95,   95,   95,   95,   95,  103,  103,
  103,  104,  104,  104,  105,  105,   92,   92,   98,   98,
   99,   99,   99,   99,  100,  100,  100,  106
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
    2,    3,    2,    2,   10,    9,    8,    7,    8,    7,
    8,    1,    1,    4,    0,    3,    0,    3,    0,    2,
    3,    4,    3,    4,    2,    5,    2,    3,    2,    1,
    4,    3,    4,    3,    1,    3,    2,    0,    2,    0,
    1,    0,    1,    4,    1,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    1,
    1,    2,    2,    4,    3,    3,    4,    2,    1,    4,
    1,    2,    4,    3,    5,    1,    3,    3,    1,    1,
    2,    1,    1,    1,    2,    2,    2,    3,    2,    3,
    6,    6,    6,    6,    7,    3,    1,    2,    4,    3,
    3,    4,    1,    3,    1,    1,    1,    1,    1,    1,
    3,    2,    0,    3,    3,    1,    1,    1,    0,    1,
    1,    1,    5,    1,    3,    3,    1,    3,    3,    1,
    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
    3,    1,    3,    3,    1,    3,    3,    3,    3,    3,
    1,    3,    3,    1,    3,    3,    1,    3,    3,    3,
    1,    3,    1,    3,    3,    2,    3,    2,    3,    1,
    2,    2,    2,    2,    2,    2,    2,    1,    3,    1,
    2,    4,    3,    3,    4,    2,    1,    1,    5,    9,
    8,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    6,    3,    3,    3,
    2,    2,    2,    2,    2,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    2,    2,    3,    2,    4,    0,
    4,    0,    1,    1,    2,    1,    2,    1,    2,    2,
    2,    3,    4,    1,    3,    1,    2,    3,    4,    1,
    3,    5,    3,    3,    2,    1,    1,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    2,    3,    3,
    2,    0,    3,    3,    3,    1,    3,    1,    4,    3,
    6,    3,    3,    1,    3,    1,    1,    7,    7,    7,
    1,    0,    2,    0,    2,    6,    6,    6,    6,    7,
    7,    3,    7,    7,    7,    1,    1,    5,    5,    3,
    3,    0,    4,    1,    4,    3,    3,    0,    3,    0,
    2,    1,    3,    1,    4,    1,    1,    2,    2,    1,
    2,    0,    2,    3,    0,    3,    0,    3,    0,    2,
    1,    2,    3,    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 987
#define YYNLSTATES 559
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
#line 306 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_ELSE, NULL); } break;
        case 74:
#line 311 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 75:
#line 318 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 76:
#line 325 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 77:
#line 332 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0, 0); } break;
        case 78:
#line 334 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1, 0); } break;
        case 79:
#line 336 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0, 1); } break;
        case 80:
#line 338 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1, 1); } break;
        case 83:
#line 347 "src/kinx.y"
{ yyval.obj = kx_gen_try_stmt_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 84:
#line 351 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 85:
#line 352 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 86:
#line 356 "src/kinx.y"
{ yyval.obj = kx_gen_var_object("_e", KX_UNKNOWN_T); } break;
        case 87:
#line 357 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(2-3).strinfo.name, KX_UNKNOWN_T, YYASP(2-3).strinfo.line, YYASP(2-3).strinfo.pos1, YYASP(2-3).strinfo.pos2); } break;
        case 88:
#line 361 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 89:
#line 362 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 90:
#line 366 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 91:
#line 367 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strinfo.name)); } break;
        case 92:
#line 368 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 93:
#line 369 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strinfo.name)); } break;
        case 94:
#line 370 "src/kinx.y"
{ yyval.obj = kx_gen_break_object(KXST_FALLTHROUGH, NULL); } break;
        case 95:
#line 374 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 96:
#line 375 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 97:
#line 379 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 98:
#line 383 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 99:
#line 384 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 100:
#line 385 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 101:
#line 386 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 102:
#line 390 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 103:
#line 394 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 104:
#line 398 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_OBJ_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2), NULL); } break;
        case 105:
#line 399 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object_line_pos(YYASP(3-3).strinfo.name, KX_OBJ_T, YYASP(3-3).strinfo.line, YYASP(3-3).strinfo.pos1, YYASP(3-3).strinfo.pos2), NULL); } break;
        case 106:
#line 403 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 107:
#line 407 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 108:
#line 408 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 109:
#line 412 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 111:
#line 417 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 113:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 115:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 116:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 117:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 118:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 119:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 120:
#line 432 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 121:
#line 433 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 122:
#line 434 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 123:
#line 435 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 124:
#line 436 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 125:
#line 437 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 126:
#line 438 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 127:
#line 439 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 128:
#line 440 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 131:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 132:
#line 450 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 133:
#line 451 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 134:
#line 452 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 135:
#line 453 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 136:
#line 454 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 137:
#line 455 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 139:
#line 460 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 141:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 142:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-4).obj, YYASP(4-4).obj, NULL); } break;
        case 143:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 144:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 146:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 147:
#line 477 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 150:
#line 483 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 154:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 155:
#line 488 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 156:
#line 489 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 157:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 158:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 159:
#line 492 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 160:
#line 497 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 161:
#line 498 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 162:
#line 499 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 163:
#line 500 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 164:
#line 501 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 165:
#line 502 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 167:
#line 507 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 168:
#line 508 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 169:
#line 509 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 170:
#line 510 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 171:
#line 511 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 173:
#line 516 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 174:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 175:
#line 518 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 176:
#line 519 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 177:
#line 520 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 178:
#line 521 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 179:
#line 522 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 180:
#line 523 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 181:
#line 524 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 182:
#line 528 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 183:
#line 529 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 184:
#line 530 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 187:
#line 539 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 192:
#line 550 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 194:
#line 555 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALLPL, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 195:
#line 556 "src/kinx.y"
{ yyval.obj = kx_gen_expr_right_object(KXOP_CALLPR, KXOP_CALLPR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 197:
#line 561 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_COMPOSITL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 562 "src/kinx.y"
{ yyval.obj = kx_gen_expr_right_object(KXOP_COMPOSITR, KXOP_COMPOSITR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 200:
#line 567 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 572 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 206:
#line 582 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 208:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 210:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 212:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 213:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 215:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 216:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 217:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 218:
#line 606 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 219:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 221:
#line 612 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 222:
#line 613 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 224:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 225:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 227:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 228:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 229:
#line 626 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 231:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 233:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 234:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 235:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 236:
#line 639 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 237:
#line 640 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 238:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 240:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 241:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 242:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 243:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 244:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 245:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 246:
#line 652 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 248:
#line 657 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 250:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 251:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 252:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 253:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 254:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 255:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 256:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 258:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-5).arraytype, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(4-5).obj, NULL, NULL), NULL); } break;
        case 259:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-9).arraytype, NULL, YYASP(4-9).obj, kx_gen_stmt_object(KXST_RET, YYASP(8-9).obj, NULL, NULL), NULL); } break;
        case 260:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-8).arraytype, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 261:
#line 682 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 262:
#line 683 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 263:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 264:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 265:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 266:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 267:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 268:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 269:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 276:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 277:
#line 701 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 278:
#line 702 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 279:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 280:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 281:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 282:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 283:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 284:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 285:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_UNKNOWN_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2); } break;
        case 286:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(kx_gen_typestr_object(YYASP(1-1).intval), KX_UNKNOWN_T); } break;
        case 287:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object_pos(YYASP(1-1).strinfo); } break;
        case 288:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 289:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 290:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 291:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("otherwise"); } break;
        case 292:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 293:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 294:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 295:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 296:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 297:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 298:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 299:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 300:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 301:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 302:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 303:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 304:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 305:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 306:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 307:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 308:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 309:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 310:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 311:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 312:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 313:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 314:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 315:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 316:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 317:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 318:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 319:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 320:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 321:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 322:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 323:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 324:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|>"); } break;
        case 325:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("**"); } break;
        case 326:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 327:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 328:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 329:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 330:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 331:
#line 761 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 332:
#line 762 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 333:
#line 763 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 334:
#line 764 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 335:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 336:
#line 766 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 337:
#line 767 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 338:
#line 768 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 339:
#line 769 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 340:
#line 770 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 341:
#line 771 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 342:
#line 772 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 343:
#line 773 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 344:
#line 774 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 345:
#line 778 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 346:
#line 779 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 347:
#line 783 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 348:
#line 784 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 349:
#line 788 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 350:
#line 792 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 351:
#line 796 "src/kinx.y"
{} break;
        case 353:
#line 801 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 354:
#line 802 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 355:
#line 806 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 356:
#line 807 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 358:
#line 812 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 359:
#line 813 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 360:
#line 814 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 361:
#line 815 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 362:
#line 816 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 364:
#line 821 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 366:
#line 826 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 367:
#line 827 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 368:
#line 828 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 370:
#line 833 "src/kinx.y"
{ yyval.obj = kx_gen_exprlist(YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 371:
#line 837 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 372:
#line 838 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 373:
#line 839 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 374:
#line 840 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 375:
#line 841 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 377:
#line 846 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 379:
#line 851 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 380:
#line 852 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 381:
#line 853 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 382:
#line 854 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 383:
#line 855 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 384:
#line 856 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 385:
#line 857 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 386:
#line 858 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 387:
#line 859 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 388:
#line 860 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 389:
#line 861 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 390:
#line 862 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 391:
#line 863 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 392:
#line 864 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 393:
#line 865 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 394:
#line 866 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 395:
#line 867 "src/kinx.y"
{ yyval.strval = "native"; } break;
        case 396:
#line 868 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 397:
#line 869 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 398:
#line 870 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 399:
#line 871 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 400:
#line 872 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 401:
#line 873 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 402:
#line 874 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 403:
#line 875 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 404:
#line 876 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 405:
#line 877 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 406:
#line 878 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 407:
#line 879 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 408:
#line 880 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 409:
#line 881 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 410:
#line 882 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 411:
#line 883 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 412:
#line 884 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 413:
#line 888 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 414:
#line 889 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 415:
#line 890 "src/kinx.y"
{ yyval.strval = "otherwise"; } break;
        case 416:
#line 891 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 417:
#line 892 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 418:
#line 893 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 419:
#line 894 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 420:
#line 895 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 421:
#line 896 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 422:
#line 897 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 423:
#line 898 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 424:
#line 899 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 425:
#line 900 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 426:
#line 901 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 427:
#line 902 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 428:
#line 903 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 429:
#line 904 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 430:
#line 905 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 431:
#line 906 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 432:
#line 907 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 433:
#line 908 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 434:
#line 909 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 435:
#line 910 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 436:
#line 911 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 437:
#line 912 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 438:
#line 913 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 439:
#line 914 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 440:
#line 915 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 441:
#line 916 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 442:
#line 917 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 443:
#line 918 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 444:
#line 919 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 445:
#line 920 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 446:
#line 921 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 447:
#line 922 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 448:
#line 923 "src/kinx.y"
{ yyval.strval = "**"; } break;
        case 449:
#line 924 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 450:
#line 925 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 451:
#line 926 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 452:
#line 927 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 453:
#line 928 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 454:
#line 929 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 455:
#line 930 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 456:
#line 931 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 457:
#line 932 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 458:
#line 933 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 459:
#line 934 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 460:
#line 935 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 461:
#line 936 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 462:
#line 937 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 463:
#line 938 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 464:
#line 939 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 465:
#line 940 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 466:
#line 941 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 467:
#line 942 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 468:
#line 946 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 469:
#line 947 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 470:
#line 948 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 471:
#line 952 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 472:
#line 956 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 473:
#line 960 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 474:
#line 961 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 476:
#line 966 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 477:
#line 970 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-1).obj, NULL); } break;
        case 478:
#line 971 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 479:
#line 972 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 480:
#line 973 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).obj, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 481:
#line 974 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 482:
#line 975 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 484:
#line 980 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 485:
#line 984 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 486:
#line 985 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 487:
#line 989 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 488:
#line 990 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 489:
#line 991 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, 0, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 490:
#line 995 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 491:
#line 999 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_UNKNOWN_T }; } break;
        case 492:
#line 1000 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 493:
#line 1004 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 494:
#line 1005 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 495:
#line 1009 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 496:
#line 1010 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 497:
#line 1011 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 498:
#line 1012 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 499:
#line 1013 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-7).obj, NULL, NULL), NULL); } break;
        case 500:
#line 1014 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 501:
#line 1015 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 502:
#line 1019 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 503:
#line 1020 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 504:
#line 1021 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 505:
#line 1025 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strinfo.name; } break;
        case 507:
#line 1030 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 508:
#line 1031 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 509:
#line 1035 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 510:
#line 1036 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 511:
#line 1040 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 512:
#line 1042 "src/kinx.y"
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
        case 514:
#line 1058 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 515:
#line 1059 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 516:
#line 1060 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 517:
#line 1064 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 518:
#line 1065 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 519:
#line 1069 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 522:
#line 1075 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 524:
#line 1080 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 525:
#line 1081 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 526:
#line 1082 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 527:
#line 1083 "src/kinx.y"
{ YYASP(2-2).obj->var_type = KX_SPR_T; yyval.obj = YYASP(2-2).obj; } break;
        case 528:
#line 1087 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 529:
#line 1088 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 530:
#line 1089 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strinfo.name) }; } break;
        case 531:
#line 1093 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 532:
#line 1094 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 533:
#line 1095 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 534:
#line 1099 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 535:
#line 1100 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 536:
#line 1104 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 537:
#line 1105 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 538:
#line 1109 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 541:
#line 1115 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 542:
#line 1116 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 543:
#line 1117 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 546:
#line 1123 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 547:
#line 1127 "src/kinx.y"
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
