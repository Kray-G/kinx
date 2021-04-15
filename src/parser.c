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
#line 1121 "src/kinx.y"

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
  "ForStatement : FOR '(' ForInVariable IN AssignExpressionList ')' Statement",
  "ForStatement : FOR '(' VAR ForInVariable IN AssignExpressionList ')' Statement",
  "ForInVariable : VarName",
  "ForInVariable : Array",
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
  830,  831,  832,  833,  834,  835,  836,  837,  838,  839,
  840,  841,  842,  844,  843,  100,    0,  845,  846,  847,
  856,  858,  857,-32766,  868,  869,  870,  872,  874,  198,
  199,  406, 1085,  866,  867,  865,   78,  864,   37,   37,
   79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
   89,   90,   91,  117,  406,  118,  859,  860,  861,  826,
  862,  863,  885,   48,  827,   28,   40,  895,   43,  645,
  854,  460,  855,  109,  848,  849,  850,  851,  852,  853,
  341,  828,  147,  148,  149,  573,  829,  575,  574,  576,
  445,  577,   93,  166,  238,  876,  578,  579,  446,    1,
  580,  881,  882,  880,   17,  871,  873,  875,  877,  878,
  879,  953,  954,  955,  956,  957,  958,  959,  960,  961,
  962,  963,  964,  965,   58,  966,  802,  803,  967,  968,
  969,  977,  979,  978,  449,  990,  991,  992,  994,  996,
  382,  383,   14,  384,  988,  989,  987,    2,  119,  110,
  385,  112,  386,  104, 1068,  581,   49,   46,   29,   25,
  582,  335,  584,  583,  -76,  166,  336,  980,  981,  982,
   64,  983,  984,  572,  563, -368,  138,  139,  140,  571,
  264,  975, -368,  976,  115,  114,  970,  971,  972,  973,
  974,  819, 1044,   47,  308,   26,   96,  985,  986,  167,
  118,  423,  126,  127,   98,  601,  998, -106,   48,  424,
   28,  -77, 1003, 1004, 1002,  538,  993,  995,  997,  999,
 1000, 1001,  172,  428,  382,  429,    9,  430,  923,  324,
  925,  926,  244,  245,  431,  107,  386,  108,  387,  388,
  164,  241,  242,  325,   52,   59,  312,  307,  614,   94,
   37,  382,  383,   14,  384,  141,  142,  339,    3,   36,
 -106,  385,  103,  386,  104,  598, 1085,  121, -398,  124,
  145,  168,   37,  826,  329,  520,   78,  247,  827,  432,
  433,  434,  146,  280,  950, -483,  136,  137,   77,-32766,
  314,  315,  389,  435,  391,  436,  393,  437,  281,  282,
   33,   34,   35,-32766,  438,  416,    2,  895,  110,  439,
  952,    1,  589,  109,  166,   67,   46, -102,   25,  248,
  246,   57,   78,  143,  144,  919,  262,  920,  921,  922,
  923,  924,  925,  926,  927,  928,  929,  930,   37,  931,
  128,  129,  164,  933,  934,  943,  945,  944, 1029,  490,
  491,  131,  117,  896,  492,  444,-32766,-32766,  132,  109,
  130,   37,   39,  468,   43,-32766,-32766,-32766,  150,   37,
  380,-32766,  154,  155,   27,  113,  197,  265,  156,  157,
  888,  432,  433,  434,  263,  455,  950,  323,  101,  523,
   77,  421,   97,  422,-32766,  941,  448,  942,  501,  935,
  936,  937,  938,  939,  940,-32766,  456,  677,  599,    3,
  321,  439,  952,  320,  906,  461,  322,  307,  308,  647,
-32766,  595,  246,   57,  646,  458,  517,  521,  457,  519,
  463,  596,-32766,-32766,  602,  644,-32766,-32766,  919,  697,
  920,  921,  922,  923,  924,  925,  926,  927,  928,  929,
  930, 1055,  931,  794,  823,  164,  933,  934,  943,  945,
  944,  825,  712,  508,   38,   37,    1,    4,  264,-32766,
-32766,  318,    5,   36,   99,  890,  800,  799,  494,  525,
    0, 1071, 1072,  883,  675,  886, 1005, 1053,  710,  792,
    0,    0,   72,   66,  432,  433,  434,   65,  455,  950,
  500,  305,  301,   77,  635,  633,  639,  637,  941,  562,
  942,  634,  935,  936,  937,  938,  939,  940,-32766,  456,
  632,  648,  638,  636,  439,  952,   73,  908,   71,   70,
   69,   68,  375,-32766,  611,  246,   57, 1012, 1013,  614,
   15,  457,  111,   60,   51,-32766,-32766,   41,  116,-32766,
-32766,  919,  243,  920,  921,  922,  923,  924,  925,  926,
  927,  928,  929,  930,  230,  931,  616, -404,  164,  933,
  934,  943,  945,  944, -401, -400, -399, -396, -388,   42,
   53,   54,-32766,-32766,  730,  615,  617,  546,  251,  249,
   55,  125,  200, -397,  246,    0,  214,  222,  228,  213,
  212,  211,   95,   92,   76,   75,   74,  432,  433,  434,
   50,  455,  950,  489,  462,  418,   77,  417,  250,  215,
  229,  941,  227,  942,  226,  935,  936,  937,  938,  939,
  940,-32766,  456,  225,  224,  223,  221,  439,  952,  220,
  673,  219,  218,  217,  216,  457,-32766,   16,  246,   57,
  133,   18,   19,  340,  457,  527,  655,  818,-32766,-32766,
  715, 1076,-32766,-32766,  919, 1074,  920,  921,  922,  923,
  924,  925,  926,  927,  928,  929,  930,  713,  931,  817,
  722,  164,  933,  934,  943,  945,  944,  629,  678, 1057,
  795, 1011,  884,  820, 1006,-32766,-32766,  524,  511,   20,
  374,  373,  372,  371,  364,  362,  361,  359,  358,  357,
  355,  352,  349,  348,  347,  346,  345,   22,   21,    0,
  432,  433,  434,  134,  455,  950,  135,    0,  887,   77,
    0,    0,    0,    0,  941,    0,  942,    0,  935,  936,
  937,  938,  939,  940,-32766,  456,    0,    0,    0,    0,
  439,  952,    0,    0,    0,    0,    0,    0,    0,-32766,
    0,  246,   57,    0,    0,    0,    0,  457,    0,    0,
    0,-32766,-32766,    0,    0,-32766,-32766,  919,    0,  920,
  921,  922,  923,  924,  925,  926,  927,  928,  929,  930,
    0,  931,    0,    0,  164,  933,  934,  943,  945,  944,
    0,    0,    0,    0,    0,    0,    0,    0,-32766,-32766,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  432,  433,  434,    0,  455,  950,    0,
    0,    0,   77,    0,    0,    0,    0,  941,    0,  942,
    0,  935,  936,  937,  938,  939,  940,-32766,  456,    0,
    0,    0,    0,  439,  952,    0,    0,    0,    0,    0,
    0,    0,-32766,    0,    0,   57,    0,    0,    0,    0,
-32766,    0,    0,    0,-32766,-32766,    0,    0,-32766,-32766,
  172,  381,  382,  383,   14,  384,    0,  311,    0,    0,
  258,  259,  385,  103,  386,  104,  387,  388,    0,  239,
  240,  543,   62,  105,  312,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  266,    0, -483,    0,    0,    0,    0,  314,  315,
  389,  390,  391,  392,  393,    0,  267,  268,   30,   31,
   32,    0,  395,    0,    0,    0,    0,    0,    0,    1,
  589,    0,    0,    0,    0, -102,    0,    0,  246,    0,
    0,    0,    0,    0,  262,  172,  381,  382,  383,   14,
  384,    0,  311,    0,    0,  258,  259,  385,  103,  386,
  104,  387,  388,    0,  239,  240,  543,   62,  105,  312,
    0,    0,    0,    0,    0,   -1,  172,  381,  382,  383,
   14,  384,    0,  311,    0,    0,  258,  259,  385,  103,
  386,  104,  387,  388,    0,  239,  240,  543,   62,  105,
  312,    0,    0,    0,    0,    0,  266,    0,    0,    0,
    0,    0,    0,  314,  315,  389,  390,  391,  392,  393,
    0,  267,  268,   30,   31,   32,    0,  395,    0,    0,
    0,    0,    0,    0,    1,    0,    0,  266,    0,    0,
 -102,    0,    0, -374,  314,  315,  389,  390,  391,  392,
  393,    0,  267,  268,   30,   31,   32,    0,  395,    0,
    0,    0,    0,    0,    0,    1,    0,    0,    0,    0,
    0, -102,  172,  381,  382,  383,   14,  384,    0,  311,
    0,    0,  258,  259,  385,  103,  386,  104,  387,  388,
    0,  239,  240,  543,   62,  105,  312,    0,    0,    0,
    0,    0,  172,  381,  382,  383,   14,  384,    0,  311,
    0,    0,  258,  259,  385,  103,  386,  104,  387,  388,
    0,  239,  240,  543,   62,  105,  312,    0,    0,    0,
    0,    0,    0,  266,    0,    0,    0,    0,    0,    0,
  314,  315,  389,  390,  391,  392,  393,    0,  267,  268,
   30,   31,   32,    0,  395,    0,    0,    0,    0,    0,
    0,    1,  801,  266,    0,    0,    0, -102,    0,    0,
  314,  315,  389,  390,  391,  392,  393,    0,  267,  268,
   30,   31,   32,    0,  395,    0,    0,    0,    0,    0,
    0,    1,  594,    0,    0,    0,    0, -102,  172,  381,
  382,  383,   14,  384,    0,  311,    0,    0,  258,  259,
  385,  103,  386,  104,  387,  388,    0,  239,  240,  543,
   62,  105,  312,    0,    0,    0,    0,    0,  172,  381,
  382,  383,   14,  384,    0,  311,    0,    0,  258,  259,
  385,  103,  386,  104,  387,  388,    0,  239,  240,  543,
   62,  105,  312,    0,    0,    0,    0,    0,    0,  266,
    0,    0,    0,    0,    0,    0,  314,  315,  389,  390,
  391,  392,  393,    0,  267,  268,   30,   31,   32,    0,
  395,    0,    0,    0,    0,    0,    0,    1,  593,  266,
    0,    0,    0, -102,    0,    0,  314,  315,  389,  390,
  391,  392,  393,    0,  267,  268,   30,   31,   32,    0,
  395,    0,    0,    0,    0,    0,    0,    1,  592,    0,
    0,    0,    0, -102,  172,  381,  382,  383,   14,  384,
    0,  311,    0,    0,  258,  259,  385,  103,  386,  104,
  387,  388,    0,  239,  240,  543,   62,  105,  312,    0,
    0,    0,    0,    0,  172,  381,  382,  383,   14,  384,
    0,  311,    0,    0,  258,  259,  385,  103,  386,  104,
  387,  388,    0,  239,  240,  543,   62,  105,  312,    0,
    0,    0,    0,    0,    0,  266,    0,    0,    0,    0,
    0,    0,  314,  315,  389,  390,  391,  392,  393,    0,
  267,  268,   30,   31,   32,    0,  395,    0,    0,    0,
    0,    0,    0,    1,  591,  266,    0,    0,    0, -102,
    0,    0,  314,  315,  389,  390,  391,  392,  393,    0,
  267,  268,   30,   31,   32,    0,  395,    0,    0,    0,
    0,    0,    0,    1,  590,    0,    0,    0,    0, -102,
  172,  381,  382,  383,   14,  384,    0,  311,    0,    0,
  258,  259,  385,  103,  386,  104,  387,  388,    0,  239,
  240,  543,   62,  105,  312,    0,    0,    0,    0,    0,
  172,  381,  382,  383,   14,  384,    0,  311,    0,    0,
  258,  259,  385,  103,  386,  104,  387,  388,    0,  239,
  240,  543,   62,  105,  312,    0,    0,    0,    0,    0,
    0,  266,    0,    0,    0,    0,    0,    0,  314,  315,
  389,  390,  391,  392,  393,    0,  267,  268,   30,   31,
   32,    0,  395,    0,    0,    0,    0,    0,    0,    1,
  589,  266,    0,  120,    0, -102,    0,    0,  314,  315,
  389,  390,  391,  392,  393,    0,  267,  268,   30,   31,
   32,    0,  395,    0,    0,    0,    0,    0,    0,    1,
    0,    0,    0,    0,    0, -102,  172,  381,  382,  383,
   14,  384,    0,  311,    0,    0,  258,  259,  385,  103,
  386,  104,  387,  388,    0,  239,  240,  543,   62,  105,
  312,    0,    0,    0,    0,  172,  381,  382,  383,   14,
  384,    0,  311,    0,    0,  258,  259,  385,  103,  386,
  104,  387,  388,    0,  239,  240,  543,   62,  105,  312,
    0,    0,    0,    0,    0,    0,    0,  266,    0,  102,
    0,    0,    0,    0,  314,  315,  389,  390,  391,  392,
  393,    0,  267,  268,   30,   31,   32,    0,  395,    0,
    0,    0,    0,    0,    0,    1,  266,    0,    0,    0,
    0, -102,    0,  314,  315,  389,  390,  391,  392,  393,
    0,  267,  268,   30,   31,   32,  106,  395,    0,    0,
    0,  163,    0,    0,    1,    0,    0,    0,    0,    0,
 -102,    0,    0,    0,    0,  158,  159,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  544,    0,
    0,    0,    0,    0,    0,    0,-32766,    0,    0,    0,
  807,  808,  809,    0,  409,    0,    0,    0,    0,    0,
  313,    0,    0,    0,    0,-32766,-32766,    0, 1029,  410,
  411,    0,    0,    0,  394,  826,    0,  810,  806,  804,
  827,    0,   39,  165,   43,    0,  805,    0,    0,  160,
    0,    0,   56,    0,   23,    0,    0,  261,    0,  316,
    0,  161,  151,  545,    0,  152,  153,   24,-32766,-32766,
-32766,    0,    0,    0,-32766,    0,    0,    0,    0,    0,
    0,    0,  719,  720,  721,    0,    0,    0,    0,-32766,
    0,    0,    0,    0,    0,    0,    0,-32766,    0,    0,
    0,-32766,-32766,    0,    0,-32766,-32766,  826,    0,    0,
  718,  716,  827,    0,    0,    0,    0,    0,  717,    0,
    0,    0,    0,    0,   61
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
   62,   63,   93,  100,   88,  102,   90,   98,   92,   96,
   72,   98,   74,  104,   76,   77,   78,   79,   80,   81,
    3,   83,  110,  111,  112,    2,   88,    4,    5,    6,
   92,    8,   95,   16,   20,   97,   13,   14,  100,   90,
   17,  103,  104,  105,    3,  107,  108,  109,  110,  111,
  112,    2,    3,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   95,   16,   33,   34,   19,   20,
   21,   22,   23,   24,    4,   26,   27,   28,   29,   30,
    3,    4,    5,    6,   35,   36,   37,   90,   92,   92,
   13,   14,   15,   16,   76,   72,  100,  100,  102,  102,
   77,   83,   79,   80,    7,   16,   88,   58,   59,   60,
   96,   62,   63,   90,   91,   91,   28,   29,   30,   96,
   90,   72,   98,   74,   24,   92,   77,   78,   79,   80,
   81,  101,   83,  100,   83,  102,    7,   88,   89,   31,
   92,   92,   39,   40,    7,   87,   97,   96,  100,  100,
  102,    7,  103,  104,  105,   97,  107,  108,  109,  110,
  111,  112,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   25,   83,   99,   67,
   90,    3,    4,    5,    6,  107,  108,   10,   90,   90,
   96,   13,   14,   15,   16,   87,   84,   99,   99,  106,
   97,  103,   90,   83,    9,   97,   67,   61,   88,   58,
   59,   60,  109,   62,   63,   64,   26,   27,   67,   14,
   69,   70,   71,   72,   73,   74,   75,   76,   77,   78,
   79,   80,   81,   14,   83,   20,   90,   98,   92,   88,
   89,   90,   91,  104,   16,   95,  100,   96,  102,   99,
   99,  100,   67,   35,   36,    2,  105,    4,    5,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   90,   16,
   41,   42,   19,   20,   21,   22,   23,   24,   76,   77,
   78,   31,  104,   98,   82,   84,   33,   34,   32,  104,
   38,   90,   90,   84,   92,   76,   77,   78,   37,   90,
   64,   82,   56,   57,  102,   64,  104,  105,   66,   67,
   65,   58,   59,   60,   67,   62,   63,   83,   64,   84,
   67,   83,   67,   83,  105,   72,   83,   74,   84,   76,
   77,   78,   79,   80,   81,   82,   83,   89,   87,   90,
   83,   88,   89,   83,   91,   83,   83,   83,   83,   83,
   97,   83,   99,  100,   83,   83,   83,   83,  105,   84,
   84,   91,  109,  110,   87,   96,  113,  114,    2,   89,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   89,   16,   89,   89,   19,   20,   21,   22,   23,
   24,   89,   89,   92,   90,   90,   90,   90,   90,   33,
   34,   90,   90,   90,   95,   91,   91,   91,   98,   92,
   -1,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   -1,   -1,   95,   95,   58,   59,   60,   95,   62,   63,
   95,   95,   95,   67,   96,   96,   96,   96,   72,   96,
   74,   96,   76,   77,   78,   79,   80,   81,   82,   83,
   96,   96,   96,   96,   88,   89,   96,   91,   96,   96,
   96,   96,  101,   97,   96,   99,  100,   96,   96,   99,
  101,  105,   98,   98,   98,  109,  110,   98,   98,  113,
  114,    2,   98,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   98,   16,   99,   99,   19,   20,
   21,   22,   23,   24,   99,   99,   99,   99,   99,   99,
   99,   99,   33,   34,   99,   99,   99,   99,   99,   99,
   99,   99,   99,   99,   99,   -1,  100,  100,  100,  100,
  100,  100,  100,  100,  100,  100,  100,   58,   59,   60,
  100,   62,   63,  100,  100,  100,   67,  100,  100,  100,
  100,   72,  100,   74,  100,   76,   77,   78,   79,   80,
   81,   82,   83,  100,  100,  100,  100,   88,   89,  100,
   91,  100,  100,  100,  100,  105,   97,  101,   99,  100,
  103,  101,  101,  101,  105,  101,  101,  101,  109,  110,
  101,  101,  113,  114,    2,  101,    4,    5,    6,    7,
    8,    9,   10,   11,   12,   13,   14,  101,   16,  101,
  101,   19,   20,   21,   22,   23,   24,  101,  101,  101,
  101,  101,  101,  101,  101,   33,   34,  101,  101,  101,
  101,  101,  101,  101,  101,  101,  101,  101,  101,  101,
  101,  101,  101,  101,  101,  101,  101,  101,  101,   -1,
   58,   59,   60,  104,   62,   63,  105,   -1,  108,   67,
   -1,   -1,   -1,   -1,   72,   -1,   74,   -1,   76,   77,
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
   -1,   90,   91,   62,   -1,   -1,   -1,   96,   -1,   -1,
   69,   70,   71,   72,   73,   74,   75,   -1,   77,   78,
   79,   80,   81,   -1,   83,   -1,   -1,   -1,   -1,   -1,
   -1,   90,   91,   -1,   -1,   -1,   -1,   96,    1,    2,
    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   17,   18,   -1,   20,   21,   22,
   23,   24,   25,   -1,   -1,   -1,   -1,   -1,    1,    2,
    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   17,   18,   -1,   20,   21,   22,
   23,   24,   25,   -1,   -1,   -1,   -1,   -1,   -1,   62,
   -1,   -1,   -1,   -1,   -1,   -1,   69,   70,   71,   72,
   73,   74,   75,   -1,   77,   78,   79,   80,   81,   -1,
   83,   -1,   -1,   -1,   -1,   -1,   -1,   90,   91,   62,
   -1,   -1,   -1,   96,   -1,   -1,   69,   70,   71,   72,
   73,   74,   75,   -1,   77,   78,   79,   80,   81,   -1,
   83,   -1,   -1,   -1,   -1,   -1,   -1,   90,   91,   -1,
   -1,   -1,   -1,   96,    1,    2,    3,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   17,   18,   -1,   20,   21,   22,   23,   24,   25,   -1,
   -1,   -1,   -1,   -1,    1,    2,    3,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   17,   18,   -1,   20,   21,   22,   23,   24,   25,   -1,
   -1,   -1,   -1,   -1,   -1,   62,   -1,   -1,   -1,   -1,
   -1,   -1,   69,   70,   71,   72,   73,   74,   75,   -1,
   77,   78,   79,   80,   81,   -1,   83,   -1,   -1,   -1,
   -1,   -1,   -1,   90,   91,   62,   -1,   -1,   -1,   96,
   -1,   -1,   69,   70,   71,   72,   73,   74,   75,   -1,
   77,   78,   79,   80,   81,   -1,   83,   -1,   -1,   -1,
   -1,   -1,   -1,   90,   91,   -1,   -1,   -1,   -1,   96,
    1,    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   14,   15,   16,   17,   18,   -1,   20,
   21,   22,   23,   24,   25,   -1,   -1,   -1,   -1,   -1,
    1,    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   14,   15,   16,   17,   18,   -1,   20,
   21,   22,   23,   24,   25,   -1,   -1,   -1,   -1,   -1,
   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,   69,   70,
   71,   72,   73,   74,   75,   -1,   77,   78,   79,   80,
   81,   -1,   83,   -1,   -1,   -1,   -1,   -1,   -1,   90,
   91,   62,   -1,   64,   -1,   96,   -1,   -1,   69,   70,
   71,   72,   73,   74,   75,   -1,   77,   78,   79,   80,
   81,   -1,   83,   -1,   -1,   -1,   -1,   -1,   -1,   90,
   -1,   -1,   -1,   -1,   -1,   96,    1,    2,    3,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   16,   17,   18,   -1,   20,   21,   22,   23,   24,
   25,   -1,   -1,   -1,   -1,    1,    2,    3,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   17,   18,   -1,   20,   21,   22,   23,   24,   25,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   62,   -1,   64,
   -1,   -1,   -1,   -1,   69,   70,   71,   72,   73,   74,
   75,   -1,   77,   78,   79,   80,   81,   -1,   83,   -1,
   -1,   -1,   -1,   -1,   -1,   90,   62,   -1,   -1,   -1,
   -1,   96,   -1,   69,   70,   71,   72,   73,   74,   75,
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
 1654,  221,  889, 1499, 1373, 1277, 1625, 1529, 1025,  994,
 1403, 1247, 1151, 1121, 1654, 1654, 1654, 1654, 1654, 1654,
 1654, 1654, 1654,  365,  372,  364,  318,  350,  373,  362,
  109,  109,  109,  109,  109,  109,  323,  549,  436,  662,
  775,  775,  248,  -31,  209,  255,  182,  182,  182,  182,
   74,  -52,  169,  -51,  -51,  -51,  271,  279,  160,  494,
  325,  345,  383,  383,  383,  375,  375,  375,  383,  383,
  383,  383,  375,  383, 1722, 1722, 1722,  375,  375,  375,
  375,  375,  375,  375,  375,  375,  375,  375,  375,  375,
  375,  375, 1722,  375,  375, 1722, 1722,  375, 1722,  375,
  375,  376,  376, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722,  374, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722,    9,    9,    9,  275,  275,  289,  289,  289,  289,
  289,  289,  289,  289,  289,  289,  289,  289,  289,  289,
  289,  289,  289,  289,  289,  289,  289,  289,  289,  289,
  289,  289,  289,  289,  289,  289,  289,  289, 1762, 1762,
 1762, 1762, 1762, 1762, 1762, 1762,  272,  272,  272,  149,
   29,  298,   83,  467,  556,  396,  440,  386,  391,  559,
  395,  394,  385,  385,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3, 1794, 1794, 1794,
  137,  216,   90,  -37,   57,   57,   57,   57,  378,  378,
  378,  317,  317,  317,  317,  317,  317,  317,  317,  317,
  317,  317,  317,  317,  317,  317,  317,  317,  317,  317,
  317,  168,  108,  108,  108,  148,  148,  148,  -24,  -24,
  -24,  -24,  -24,  -24,  164,  111,   78,   78,   78,   78,
   78,   78,   56,  -28,  163,  -28,  -28,  157,  334,  335,
   77,  496,  497,  190,  540,  498,  285,  308,  310,  260,
  288,  173,  316,  312,  313,  299,  220,  441,  442,  -27,
  285,  308,  310,   84,  439,  546,  435,  552,  260,  288,
  288,  288,  288,  288,  173,  173,  316,  299,  299,  434,
  555,  178,  554,  550,  551,  118,   52,   52,   52,   52,
   52,  319,  341,  515,  338,  338,  620,  265,  342,  515,
  544,  544,  319,  319,  319,  478,  449,  319,  515,  513,
  247,  380,  488,  488,  466,  371,  371,  446,  319,  319,
  319,  485,  518,  319,  319,  495,  495,  495,  495,  489,
  319,  485,  495,  518,  319,  495,  319,  495,  495,  495,
  319,  495,  489,  319,  495,  319,  319,  319,  319,  319,
  319,  495,  495,  495,  495,  489,  319,  319,  319,  319,
  319,  506,  487,  505,  510,  504,  486,  381,  427,  426,
  330,  327,  333,  304,  499,  493,   16,  425,  322,  320,
  326,  547,  619,  621,  331,  130,  503,  424,  415,  517,
  501,  500,  519,  402,  398,  444,  332,  514,  346,  377,
  382,  543,  542,  393,  593,  541,  539,  536,  506,  505,
  510,  504,  477,  476,  475,  330,  333,  479,  480,  468,
  481,  311,  392,  445,  592,  390,  591,  410,  535,  502,
  189,  204,  157,  409,  408,  517,  482,  534,  407,  339,
  336,  405,  314,  590,  490,  615,  614,  613,  597,  384,
  445,  612,  315,  320,  326,  547,  619,  621,  331,  331,
  331,  589,  611,  492,  322,  322,  197,  402,  433,  343,
  533,  524,  522,  520,  344,  340,  379,  379,  379,  411,
  305,  596,  588,  610,  609,  608,  607,  606,  388,  387,
  387,  491,  605,  587,  604,  101,  432,  586,  603,  579,
  321,  406,  397,  413,  578,  389,  324,  438,  430,  598,
  602,  601,  600,  599,  431,  576,  564,  617,  347,  379,
  616,  306,  560,    0,    0,    0,    0, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
   -2,   -2,   -2,   -2,   -2,   -2,   -2,    0,    0,    0,
    0,    0,    0, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722,    0,    0,    0, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,    0,
 1722, 1722,    0,    0, 1722,    0, 1722, 1722, 1722, 1722,
    0,    0,    0,    0,    0,    0,    0,    0, 1722,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722, 1722,
 1722, 1722, 1722, 1794, 1794, 1794,   -3,   -3,   -3,    0,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   93,  -24,  -24,
  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,
  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,   52,   93,
   93,   93,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   52,   52,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  220,   52,   52,    0,  495,  495,
    0,  495,  495,  517,  501,  500,    0,    0,    0,    0,
    0,  519,    0,    0,  454,  454,    0,  517,  501,  500,
    0,  450,  450,  450,  450,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  454,  450,    0,  450,
  450,  450
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 305

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  391,  392,  393,  483,  483,  483,  483,
32767,  345,32767,32767,32767,32767,  530,  530,  530,  530,
32767,  345,  104,32767,32767,32767,32767,32767,32767,   94,
  353,32767,  104,  104,  104,32767,32767,32767,  104,  104,
  104,  104,32767,  104,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,   94,32767,  383,  384,32767,
32767,32767,32767,32767,32767,   96,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  229,  231,32767,32767,
32767,32767,32767,32767,  385,32767,32767,32767,32767,32767,
  106,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  491,32767,  358,   93,  350,  356,  351,  536,
  360,  369,  354,   95,  357,  370,  491,32767,  151,  153,
32767,  241,32767,  144,  239,  240,  237,  236,  125,  537,
  371,  511,  511,  511,  511,  511,  511,  511,  511,  511,
  511,  511,  511,  511,  511,  511,  511,  511,  511,  511,
  345,32767,  145,  152,  154,  205,  206,  207,32767,32767,
32767,  386,  387,32767,  380,  381,32767,32767,32767,32767,
32767,32767,  528,  217,  185,  219,  218,  469,  106,  106,
  177,  483,  483,32767,  483,  483,32767,32767,32767,  203,
  208,  214,  224,  226,32767,  187,  469,32767,32767,32767,
  402,  389,  390,  233,32767,32767,32767,32767,  204,  210,
  212,  213,  209,  211,  215,  216,  225,  188,  189,32767,
32767,32767,32767,32767,32767,32767,  106,  106,  106,  106,
  106,32767,32767,32767,32767,32767,  342,   79,32767,32767,
  509,  509,32767,32767,  377,  539,  344,32767,32767,   81,
   83,  344,  503,  503,  344,  523,  523,  344,32767,32767,
32767,  182,  526,32767,32767,  483,  483,  483,  483,  485,
32767,  182,  483,  526,32767,  483,32767,  483,  483,  483,
32767,  483,  485,32767,  483,32767,32767,32767,32767,32767,
32767,  483,  483,  483,  483,  485,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  279,32767,32767,  190,  193,
  195,  197,  199,  201,  220,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  105,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  372,  373,
  375,  382,  260,  261,  262,  394,  395,  482,  279,  280,
32767,32767,32767,  346,32767,32767,32767,32767,32767,32767,
32767,  266,  264,32767,32767,  402,  279,32767,   50,32767,
32767,32767,32767,32767,  515,32767,32767,32767,32767,32767,
  347,32767,32767,  194,  196,  198,  200,  202,  221,  222,
  223,32767,32767,32767,  191,  192,32767,   77,32767,32767,
32767,32767,32767,32767,  345,32767,  473,  474,  471,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  522,
  520,  273,32767,32767,32767,   61,32767,32767,32767,32767,
32767,   53,  470,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  472,
32767,32767,32767,  539,  463,  463,  539
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  191,  186,  186,  186,  189,  189,  189,  189,  187,  189,
  184,  191,  191,  191,  174,  174,  452,  185,  192,  179,
  184,  184,  184, 1039, 1039,  910,  184,  184,  184,  184,
  650,  184,  187,  187,  187,  694,  694,  694,  513,  535,
  542,  310,  488,  728,  728,  728,  516,  528,  529,  537,
  187,  540,  495,  187,  187, 1059,  187,  472, 1078,  196,
  182,  169,  173,  185,  171,  169,  173,  188,  175,  190,
  176,  177,  178,  193,  194,  195,  180,  181,  183,  470,
 1065, 1065, 1065, 1065, 1065, 1065, 1065, 1065, 1065, 1065,
 1065, 1065, 1065, 1065, 1065, 1065, 1065, 1065, 1065, 1065,
  284,  285,  287,  725,  686,  408,  607,  414,  414,  414,
  414,  414,  414,  727,  727,  727,  483,  733,  300,  408,
 1081,  302,  303,  797,  304,  473,  797,  797,  797,  797,
  674,  709,  714,  714,  714,  474,  674,  674,  674,  370,
  327,  327,  484,  485,  350,  824,  793,  676,  696,  711,
 1054,  451,  379,  728,  289,  290,  291,  292,  293,  475,
  709,  709,  709,  714,  714,  714,  447,  453,  454,  459,
  499,   11,   12,   13,   13,  283,  476,  464,  464,  464,
  464,  464,  464,  464,  464,  464,  464,  464,  464,  464,
  464,  464,  464,  464,  464,  464,  464,  785,  781,  782,
  774,  775,  777,  779,  257,  276,  276,  276,  276,  276,
  915,  915,  915,  915,  915,  915,  789,  342,  353,  536,
 1033, 1008,  497,  498,  354,  356,  360,  526,  539, 1066,
 1007,  365,  477,  317,  366,  288,  367,  368,  369,  913,
    6,  911,  296,    7, 1048, 1049,  317,  236,  237, 1040,
  376,  377,  378,  541,  426,  427,  685,  426,  427, 1061,
  627,  631,  612,  351,  607, 1046, 1047,  693,  693,  693,
  683,  299,  707,  278,  486,  278, 1034,  420, 1035,  478,
  479,  480, 1036,  297,  298, 1037,  333, 1026, 1027, 1041,
 1042, 1043, 1028,  204,  205,  206,  207, 1015,  702,  703,
  704,  705,  706, 1052,  821,  821,  723,  232,  233,  234,
  255,  256, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064,
 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064,
 1064, 1064,  294,  295,  344,  689,  688,  123,  510,  487,
  413,  413,  413,  413,  413,  274,  274,  274,  274,  274,
  274,  274,  274,  274,  274,  274,  274,  274,  274,  274,
  274,  274,  274,  274,  274,  274,  274,  274,  671,  328,
 1063,  162,    0,    0,    0,  671,  671,  671,    0,    0,
    0,    0,  671,    0,    0,    0,    0,  671,  671,  671,
  671,  671,  671,  671,  671,  671,  671,  671,  671,  671,
  671,  671,  657,  671,  671,    0,    0,  671,    0,  671,
  671,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  914,  899,  660,  661,  662,  663,  664,  665,  666,
  667,  668,  669,  670,  658,  659,    0,  657, 1080,    0,
    0,  902,    0, 1023, 1082,  466,  467,  471,  482,  502,
  503,  504,  505,  506,  507,  512,  514,  518,  530,  531,
  532,  533,  534,  549,  695,  695,  695,    0,    0,    0,
    0,  550,  405,  552,  552,  552,  552,  405,  515,  610,
  609,  621,  622,  620,  619,  618,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  798,
  679,    0,  798,  798,  798,  798,  679,  679,  679,    0,
  210,  493,  493,  493,  209,  209,  209,  209,    0,  209,
    0,  210,  210,  210,  202,  202
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 526

static char yygcheck[] = {
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   74,   37,   37,   37,
   37,   37,   37,    7,    7,   72,   37,   37,   37,   37,
   31,   37,   37,   37,   37,   63,   63,   63,   98,   98,
   98,   40,   40,    7,    7,    7,   40,   40,   40,   40,
   37,   40,  120,   37,   37,  120,   37,   66,  120,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   67,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   69,   69,   69,  118,  118,   31,   35,   63,   63,   63,
   63,   63,   63,   41,   41,   41,   41,   41,   69,   31,
  100,   69,   69,    7,   69,   43,    7,    7,    7,    7,
   59,   59,   74,   74,   74,   44,   59,   59,   59,  102,
  101,  101,   42,   42,  101,   58,   58,   58,   58,   58,
   58,   62,  102,    7,   50,   50,   50,   50,   50,   45,
   59,   59,   59,   74,   74,   74,   31,   31,   31,   31,
   31,    3,    3,    3,    3,   56,   46,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   55,   55,   55,
   55,   55,   55,   55,   74,   74,   74,   74,   74,   74,
   56,   56,   56,   56,   56,   56,  103,  103,  103,  103,
  103,   65,   81,   81,  101,  101,  101,  101,   81,   74,
   65,  101,   47,    7,  101,   48,  101,  101,  101,   73,
  101,   73,   54,  101,    7,    7,    7,   49,   49,    7,
  101,  101,  101,  101,   76,   76,  119,   76,   76,   95,
    7,    7,    7,   32,   35,    7,    7,   62,   62,   62,
  111,   79,    7,   79,   19,   79,    7,    9,    7,   53,
   53,   53,    7,  108,  108,    7,   91,    7,    7,    7,
    7,    7,    7,   57,   57,   57,   57,   80,    7,    7,
    7,    7,    7,   60,   60,   60,   60,  114,  114,  114,
   52,   52,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   51,   51,   89,  113,  113,  121,  104,   62,
   62,   62,   62,   62,   62,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,  109,  123,
  105,  106,   -1,   -1,   -1,  109,  109,  109,   -1,   -1,
   -1,   -1,  109,   -1,   -1,   -1,   -1,  109,  109,  109,
  109,  109,  109,  109,  109,  109,  109,  109,  109,  109,
  109,  109,   38,  109,  109,   -1,   -1,  109,   -1,  109,
  109,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   -1,   38,   38,   -1,
   -1,   38,   -1,   38,   38,   93,   93,   93,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   93,   93,   93,    4,   97,   97,   97,   -1,   -1,   -1,
   -1,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   97,
   97,   -1,   97,   97,   97,   97,   97,   97,   97,   -1,
   39,   82,   82,   82,   39,   39,   39,   39,   -1,   39,
   -1,   39,   39,   39,   39,   39
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  167,  463,    0,    0,  -78,    0,  -38,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   36,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -140,   32,    0,    0,   64,    0,  -42,  344,  468,
  -22,   -8,   14,   -5,    4,   27,   43,   98,  100,  111,
   16,  189,  165,  132,   92,   46,  174,  135,  121,  -72,
  141,    0,  101, -131,    0,  -98,   13,   34,    0,   26,
    0,    0,  -16,  186,  -34,    0,  223,    0,    0,   33,
   54,  156,  345,    0,    0,    0,    0,    0,    0,    1,
    0,  -35,    0,  233,    0,   29,    0,  298,   -9,    0,
   69, -121, -223,  -31,    2,   17, -175,    0,  157,  310,
    0,   10,    0,  168,  110,    0,    0,    0,  -19,   25,
 -279,  -14,    0, -176
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  396,    8,   10,  551,  554,  553,  555,  556,  419,
  557,  331,  569,  558,  585,  586,  587,  613,  588,  450,
  559,  330,  338,  625,  564,  565,  306,  566,  567,  279,
  568,  407,  654,  570,  560,  561,  397,  170, 1022,  208,
  309,  680,  398,  399,  400,  401,  402,  403,  269,  235,
  270,  271,  253,  404,  272,  273,  780,  201,  822,  791,
  790,  812,  813,  814,  815, 1009,  442,  443,   45,  286,
  415,  326,  909,  912,  811,  440,  425, 1045,  603,  277,
 1014,  496,  412,  604, 1024,  731, 1025,  605,  606,  343,
  252,  332, 1051,  465,  334, 1060,  796,  816,  481,  337,
 1079,  441,  363, 1031,  509,  522,   63,  254,  275,  656,
  260,  682,  231,  687,  203,  690,  708,  681,  684,  726,
  469,  122,   44,  319
#line 205 "build/utility/kmyacc.c.parser"
};

static char yylhs[] = {
    0,    1,    2,    2,    3,    3,    4,    4,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,   35,   35,
   35,   35,    7,    7,    8,    8,    8,    8,    9,   10,
   11,   11,   11,   11,   11,   11,   12,   12,   12,   12,
   34,   13,   13,   14,   15,   16,   16,   17,   17,   17,
   17,   18,   18,   18,   18,   18,   19,   19,   20,   21,
   21,   22,   22,   23,   23,   33,   33,   33,   33,   33,
   24,   24,   25,   26,   26,   26,   26,   27,   28,   29,
   29,   30,   36,   36,   40,   40,   31,   31,   32,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   38,   38,   39,   39,   39,   39,
   39,   39,   39,  109,  109,  110,  110,  111,  111,  111,
  112,  112,  112,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  115,  115,  115,  115,  115,
  115,  114,  114,  114,  114,  114,  114,  116,  116,  116,
  116,  116,  116,  116,  116,  116,  116,  117,  117,  118,
  118,  119,  121,  121,   41,   41,   41,  107,  107,  107,
  108,  108,  108,   42,   42,   43,   43,   44,   44,   45,
   45,   46,   46,   47,   47,   48,   48,   48,   49,   49,
   49,   49,   49,   49,   50,   50,   50,   51,   51,   51,
   52,   52,   52,   52,   53,   53,   54,   54,   54,   54,
   54,   54,   54,   55,   55,   55,   55,   55,   55,   55,
   55,   56,   56,   57,   57,   57,   57,   57,   57,   57,
   96,   96,   97,   97,   97,   59,   59,   60,   60,   60,
   60,   60,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   60,   60,   60,   60,   60,   60,   74,
   74,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   62,   62,
   61,   61,  122,   63,  120,  120,   66,   66,   68,   68,
   67,   67,   67,   67,   67,   67,   69,   69,   70,   70,
   70,   70,   71,   71,   72,   72,   72,   72,   72,   73,
   73,   73,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   64,   64,   64,  123,   65,   78,   78,   79,   79,   80,
   80,   80,   80,   80,   80,   81,   81,   83,   83,   84,
   84,   84,   82,  101,  101,  102,  102,   85,   85,   85,
   85,   85,   85,   85,   86,   86,   86,   76,   76,   87,
   87,   88,   88,   89,   89,   90,   90,   90,   90,   91,
   91,   93,   93,   94,   94,   95,   95,   95,   95,   95,
  103,  103,  103,  104,  104,  104,  105,  105,   92,   92,
   98,   98,   99,   99,   99,   99,  100,  100,  100,  106
#line 209 "build/utility/kmyacc.c.parser"
};

static char yylen[] = {
    1,    1,    1,    2,    1,    2,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    6,    2,    1,    1,    1,
    1,    1,    1,    1,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    1,    1,
    1,    1,    2,    3,    4,    4,    5,    5,    1,    5,
    1,    3,    4,    3,    5,    6,    1,    1,    1,    1,
    3,    5,    7,    5,    7,    5,    1,    3,    2,    3,
    2,   10,    9,    8,    7,    8,    1,    1,    4,    0,
    3,    0,    3,    0,    2,    3,    4,    3,    4,    2,
    5,    2,    3,    2,    1,    4,    3,    4,    3,    1,
    3,    2,    0,    2,    0,    1,    0,    1,    4,    1,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    1,    1,    2,    2,    4,    3,
    3,    4,    2,    1,    4,    1,    2,    4,    3,    5,
    1,    3,    3,    1,    1,    2,    1,    1,    1,    2,
    2,    2,    3,    2,    3,    6,    6,    6,    6,    7,
    3,    1,    2,    4,    3,    3,    4,    1,    3,    1,
    1,    1,    1,    1,    1,    3,    2,    0,    3,    1,
    1,    1,    0,    1,    1,    1,    5,    1,    3,    3,
    1,    3,    3,    1,    3,    1,    3,    1,    3,    1,
    3,    1,    3,    1,    3,    1,    3,    3,    1,    3,
    3,    3,    3,    3,    1,    3,    3,    1,    3,    3,
    1,    3,    3,    3,    1,    3,    1,    3,    3,    2,
    3,    2,    3,    1,    2,    2,    2,    2,    2,    2,
    2,    1,    3,    1,    2,    4,    3,    3,    4,    2,
    1,    1,    5,    9,    8,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    6,    3,    3,    3,    2,    2,    2,    2,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    2,    2,    3,
    2,    4,    0,    4,    0,    1,    1,    2,    1,    2,
    1,    2,    2,    2,    3,    4,    1,    3,    1,    2,
    3,    4,    1,    3,    5,    3,    3,    2,    1,    1,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    2,    2,
    3,    3,    2,    0,    3,    3,    3,    1,    3,    1,
    4,    3,    6,    3,    3,    1,    3,    1,    1,    7,
    7,    7,    1,    0,    2,    0,    2,    6,    6,    6,
    6,    7,    7,    3,    7,    7,    7,    1,    1,    5,
    5,    3,    3,    0,    4,    1,    4,    3,    3,    0,
    3,    0,    2,    1,    3,    1,    4,    1,    1,    2,
    2,    1,    2,    0,    2,    3,    0,    3,    0,    3,
    0,    2,    1,    2,    3,    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 967
#define YYNLSTATES 547
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
#line 282 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 62:
#line 283 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 63:
#line 287 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 64:
#line 291 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 65:
#line 295 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 300 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 301 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 302 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_WHEN, YYASP(2-3).obj); } break;
        case 70:
#line 303 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_ELSE, NULL); } break;
        case 71:
#line 308 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 72:
#line 315 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 73:
#line 322 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 74:
#line 329 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 75:
#line 331 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 78:
#line 340 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 79:
#line 344 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 80:
#line 345 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 81:
#line 349 "src/kinx.y"
{ yyval.obj = kx_gen_var_object("_e", KX_UNKNOWN_T); } break;
        case 82:
#line 350 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(2-3).strinfo.name, KX_UNKNOWN_T, YYASP(2-3).strinfo.line, YYASP(2-3).strinfo.pos1, YYASP(2-3).strinfo.pos2); } break;
        case 83:
#line 354 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 84:
#line 355 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 85:
#line 359 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 86:
#line 360 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strinfo.name)); } break;
        case 87:
#line 361 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 88:
#line 362 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strinfo.name)); } break;
        case 89:
#line 363 "src/kinx.y"
{ yyval.obj = kx_gen_break_object(KXST_FALLTHROUGH, NULL); } break;
        case 90:
#line 367 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 91:
#line 368 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 92:
#line 372 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 93:
#line 376 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 94:
#line 377 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 95:
#line 378 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 96:
#line 379 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 97:
#line 383 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 98:
#line 387 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 99:
#line 391 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_OBJ_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2), NULL); } break;
        case 100:
#line 392 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object_line_pos(YYASP(3-3).strinfo.name, KX_OBJ_T, YYASP(3-3).strinfo.line, YYASP(3-3).strinfo.pos1, YYASP(3-3).strinfo.pos2), NULL); } break;
        case 101:
#line 396 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 102:
#line 400 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 103:
#line 401 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 104:
#line 405 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 106:
#line 410 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 108:
#line 415 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 110:
#line 420 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 111:
#line 421 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 423 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 425 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 119:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 120:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 121:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 122:
#line 432 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 123:
#line 433 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 126:
#line 442 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 127:
#line 443 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 128:
#line 444 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 129:
#line 445 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 130:
#line 446 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 131:
#line 447 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 132:
#line 448 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 134:
#line 453 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 136:
#line 458 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 137:
#line 462 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-4).obj, YYASP(4-4).obj, NULL); } break;
        case 138:
#line 463 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 139:
#line 464 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 141:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 142:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 145:
#line 476 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 149:
#line 480 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 150:
#line 481 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 151:
#line 482 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 152:
#line 483 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 153:
#line 484 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 154:
#line 485 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 155:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 156:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 157:
#line 492 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 158:
#line 493 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 159:
#line 494 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 160:
#line 495 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 162:
#line 500 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 163:
#line 501 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 164:
#line 502 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 165:
#line 503 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 166:
#line 504 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 168:
#line 509 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 169:
#line 510 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 170:
#line 511 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 171:
#line 512 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 172:
#line 513 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 173:
#line 514 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 174:
#line 515 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 175:
#line 516 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 176:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 177:
#line 521 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 178:
#line 522 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 181:
#line 531 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 186:
#line 542 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 188:
#line 547 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALLPL, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 189:
#line 548 "src/kinx.y"
{ yyval.obj = kx_gen_expr_right_object(KXOP_CALLPR, KXOP_CALLPR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 191:
#line 553 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_COMPOSITL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 554 "src/kinx.y"
{ yyval.obj = kx_gen_expr_right_object(KXOP_COMPOSITR, KXOP_COMPOSITR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 194:
#line 559 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 564 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 569 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 200:
#line 574 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 579 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 584 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 206:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 207:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 209:
#line 595 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 210:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 211:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 212:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 213:
#line 599 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 215:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 216:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 218:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 219:
#line 611 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 221:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 222:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 223:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 225:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 227:
#line 628 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 228:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 229:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 230:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 231:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 232:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 234:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 235:
#line 639 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 236:
#line 640 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 237:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 238:
#line 642 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 239:
#line 643 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 240:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 242:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 244:
#line 654 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 245:
#line 655 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 246:
#line 656 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 247:
#line 657 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 248:
#line 658 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 249:
#line 659 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 250:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 252:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-5).arraytype, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(4-5).obj, NULL, NULL), NULL); } break;
        case 253:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-9).arraytype, NULL, YYASP(4-9).obj, kx_gen_stmt_object(KXST_RET, YYASP(8-9).obj, NULL, NULL), NULL); } break;
        case 254:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-8).arraytype, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 255:
#line 674 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 256:
#line 675 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 257:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 258:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 259:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 260:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 261:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 262:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 263:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 270:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 271:
#line 693 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 272:
#line 694 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 273:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 274:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 275:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 276:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 277:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 278:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 279:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_UNKNOWN_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2); } break;
        case 280:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(kx_gen_typestr_object(YYASP(1-1).intval), KX_UNKNOWN_T); } break;
        case 281:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object_pos(YYASP(1-1).strinfo); } break;
        case 282:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 283:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 284:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 285:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 286:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 287:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 288:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 289:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 290:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 291:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 292:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 293:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 294:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 295:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 296:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 297:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 298:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 299:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 300:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 301:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 302:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 303:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 304:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 305:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 306:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 307:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 308:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 309:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 310:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 311:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 312:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 313:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 314:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 315:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 316:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 317:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|>"); } break;
        case 318:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("**"); } break;
        case 319:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 320:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 321:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 322:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 323:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 324:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 325:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 326:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 327:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 328:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 329:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 330:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 331:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 332:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 333:
#line 761 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 334:
#line 762 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 335:
#line 763 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 336:
#line 764 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 337:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 338:
#line 769 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 339:
#line 770 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 340:
#line 774 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 341:
#line 775 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 342:
#line 779 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 343:
#line 783 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 344:
#line 787 "src/kinx.y"
{} break;
        case 346:
#line 792 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 347:
#line 793 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 348:
#line 797 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 349:
#line 798 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 351:
#line 803 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 352:
#line 804 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 353:
#line 805 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 354:
#line 806 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 355:
#line 807 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 357:
#line 812 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 359:
#line 817 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 360:
#line 818 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 361:
#line 819 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 363:
#line 824 "src/kinx.y"
{ yyval.obj = kx_gen_exprlist(YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 364:
#line 828 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 365:
#line 829 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 366:
#line 830 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 367:
#line 831 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 368:
#line 832 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 370:
#line 837 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 372:
#line 842 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 373:
#line 843 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 374:
#line 844 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 375:
#line 845 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 376:
#line 846 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 377:
#line 847 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 378:
#line 848 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 379:
#line 849 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 380:
#line 850 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 381:
#line 851 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 382:
#line 852 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 383:
#line 853 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 384:
#line 854 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 385:
#line 855 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 386:
#line 856 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 387:
#line 857 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 388:
#line 858 "src/kinx.y"
{ yyval.strval = "native"; } break;
        case 389:
#line 859 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 390:
#line 860 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 391:
#line 861 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 392:
#line 862 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 393:
#line 863 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 394:
#line 864 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 395:
#line 865 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 396:
#line 866 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 397:
#line 867 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 398:
#line 868 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 399:
#line 869 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 400:
#line 870 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 401:
#line 871 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 402:
#line 872 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 403:
#line 873 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 404:
#line 874 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 405:
#line 875 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 406:
#line 879 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 407:
#line 880 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 408:
#line 881 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 409:
#line 882 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 410:
#line 883 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 411:
#line 884 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 412:
#line 885 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 413:
#line 886 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 414:
#line 887 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 415:
#line 888 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 416:
#line 889 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 417:
#line 890 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 418:
#line 891 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 419:
#line 892 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 420:
#line 893 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 421:
#line 894 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 422:
#line 895 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 423:
#line 896 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 424:
#line 897 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 425:
#line 898 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 426:
#line 899 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 427:
#line 900 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 428:
#line 901 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 429:
#line 902 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 430:
#line 903 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 431:
#line 904 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 432:
#line 905 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 433:
#line 906 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 434:
#line 907 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 435:
#line 908 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 436:
#line 909 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 437:
#line 910 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 438:
#line 911 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 439:
#line 912 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 440:
#line 913 "src/kinx.y"
{ yyval.strval = "**"; } break;
        case 441:
#line 914 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 442:
#line 915 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 443:
#line 916 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 444:
#line 917 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 445:
#line 918 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 446:
#line 919 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 447:
#line 920 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 448:
#line 921 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 449:
#line 922 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 450:
#line 923 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 451:
#line 924 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 452:
#line 925 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 453:
#line 926 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 454:
#line 927 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 455:
#line 928 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 456:
#line 929 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 457:
#line 930 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 458:
#line 931 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 459:
#line 932 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 460:
#line 936 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 461:
#line 937 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 462:
#line 938 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 463:
#line 942 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 464:
#line 946 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 465:
#line 950 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 466:
#line 951 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 468:
#line 956 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 469:
#line 960 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-1).obj, NULL); } break;
        case 470:
#line 961 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 471:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 472:
#line 963 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).obj, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 473:
#line 964 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 474:
#line 965 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 476:
#line 970 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 477:
#line 974 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 478:
#line 975 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 479:
#line 979 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 480:
#line 980 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 481:
#line 981 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, 0, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 482:
#line 985 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 483:
#line 989 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_UNKNOWN_T }; } break;
        case 484:
#line 990 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 485:
#line 994 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 486:
#line 995 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 487:
#line 999 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 488:
#line 1000 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 489:
#line 1001 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 490:
#line 1002 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 491:
#line 1003 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-7).obj, NULL, NULL), NULL); } break;
        case 492:
#line 1004 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 493:
#line 1005 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 494:
#line 1009 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 495:
#line 1010 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 496:
#line 1011 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 497:
#line 1015 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strinfo.name; } break;
        case 499:
#line 1020 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 500:
#line 1021 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 501:
#line 1025 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 502:
#line 1026 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 503:
#line 1030 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 504:
#line 1032 "src/kinx.y"
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
        case 506:
#line 1048 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 507:
#line 1049 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 508:
#line 1050 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 509:
#line 1054 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 510:
#line 1055 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 511:
#line 1059 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 514:
#line 1065 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 516:
#line 1070 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 517:
#line 1071 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 518:
#line 1072 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 519:
#line 1073 "src/kinx.y"
{ YYASP(2-2).obj->var_type = KX_SPR_T; yyval.obj = YYASP(2-2).obj; } break;
        case 520:
#line 1077 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 521:
#line 1078 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 522:
#line 1079 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strinfo.name) }; } break;
        case 523:
#line 1083 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 524:
#line 1084 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 525:
#line 1085 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 526:
#line 1089 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 527:
#line 1090 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 528:
#line 1094 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 529:
#line 1095 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 530:
#line 1099 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 533:
#line 1105 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 534:
#line 1106 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 535:
#line 1107 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 538:
#line 1113 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 539:
#line 1117 "src/kinx.y"
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
