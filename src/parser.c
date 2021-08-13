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
#line 1123 "src/kinx.y"

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
  833,  834,  835,  836,  837,  838,  839,  840,  841,  842,
  843,  844,  845,  847,  846,   94,    0,  848,  849,  850,
  859,  861,  860,-32766,  871,  872,  873,  875,  877,  198,
  199,  407, 1088,  869,  870,  868,   78,  867,   37,   37,
   79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
   89,   90,   91,  117,  407,  118,  862,  863,  864,  829,
  865,  866,  888,   48,  830,   28,   40,  898,   43,  265,
  857,   17,  858,  109,  851,  852,  853,  854,  855,  856,
  822,  831,  147,  148,  149,  574,  832,  576,  575,  577,
  446,  578,   93,  166,  239,  879,  579,  580,  447,    1,
  581,  884,  885,  883,  450,  874,  876,  878,  880,  881,
  882,  956,  957,  958,  959,  960,  961,  962,  963,  964,
  965,  966,  967,  968,   58,  969,   98,   78,  970,  971,
  972,  980,  982,  981,  -79,  993,  994,  995,  997,  999,
  383,  384,   14,  385,  991,  992,  990,    2,   96,  110,
  386,  112,  387,  104, 1071,  582,  -78,   46,  898,   25,
  583,  336,  585,  584,  109,  342,  337,  983,  984,  985,
   64,  986,  987,  573,  564,  829,  617,  330,  166,  572,
  830,  978,  100,  979,  126,  127,  973,  974,  975,  976,
  977,-32766, 1047,  138,  139,  140,  115,  988,  989, 1088,
  119,  424,  805,  806, -370,   37, 1001,  340,   49,  425,
   29, -370, 1006, 1007, 1005,  166,  996,  998, 1000, 1002,
 1003, 1004,  172,  429,  383,  430,    9,  431,  926,  325,
  928,  929,  245,  246,  432,  107,  387,  108,  388,  389,
  164,  242,  243,  326,   52,   59,  313,  308,   67,  118,
  417,  124,  249,  383,  384,   14,  385,   48,  145,   28,
 -108,  114,   37,  386,  103,  387,  104,  599,  602,   47,
  146,   26,  141,  142,  248,  131,  309,  521,  539,  433,
  434,  435,  150,  281,  953, -485,  132,   78,   77, -108,
  315,  316,  390,  436,  392,  437,  394,  438,  282,  283,
   33,   34,   35,    2,  439,  110,  381,   36,  167,  440,
  955,    1,  590,   46,  130,   25, -400, -104,  899,  101,
  247,   57,  136,  137,  109,  922,  263,  923,  924,  925,
  926,  927,  928,  929,  930,  931,  932,  933,  113,  934,
   37,  324,  164,  936,  937,  946,  948,  947,  648,  200,
  461,  891,  469,  445,  117,   97,-32766,-32766,   37,   37,
  143,  144,-32766, 1032,  491,  492,  264,    3,  518,  493,
  128,  129,  154,  155,  156,  157,  121,   39,  462,   43,
  168,  433,  434,  435,  309,  456,  953,  321,  322,   27,
   77,  197,  266,  323,  308,  944,  459,  945,  649,  938,
  939,  940,  941,  942,  943,-32766,  457,  449,  603,  423,
  422,  440,  955,  522,  911,  596,  650, 1058,  524,  464,
-32766,  502,  247,   57,-32766,-32766,-32766,  520,  458,  600,
-32766,  319,-32766,-32766,  700,  680,-32766,-32766,  922,  828,
  923,  924,  925,  926,  927,  928,  929,  930,  931,  932,
  933,  826,  934,-32766,  797,  164,  936,  937,  946,  948,
  947,  715,  893,   38,    3,    5,    4,  265,    1,-32766,
-32766,   36,   37,  678,  597,  802,  803,  244,  509,  526,
    0, 1075,  886,  889, 1008,  795,  713, 1074, 1056,    0,
    0,  501,  306,  302,  433,  434,  435,   99,  456,  953,
   72,   66,   65,   77,  637,  614,  563,  640,  944,  647,
  945,  638,  938,  939,  940,  941,  942,  943,-32766,  457,
  636,  642, 1016, 1015,  440,  955,   69,  676,  635,  651,
  641,  639,  376,-32766,   73,  247,   57,   71,   70,   68,
  214,  458,  495,  231,  111,-32766,-32766,   60,   51,-32766,
-32766,  922,  116,  923,  924,  925,  926,  927,  928,  929,
  930,  931,  932,  933,   41,  934,  619,  617,  164,  936,
  937,  946,  948,  947, -406,  200, -403, -402, -401, -398,
 -390,   42,-32766,-32766,   53,  733,  618,  620,  547,  252,
  250,   54,   55, -399,  125,  247,  201,    0,  223,  229,
  213,  212,   95,   92,   76,   75,   74,  433,  434,  435,
   50,  456,  953,  490,  463,  419,   77,  418,  215,  251,
  230,  944,  228,  945,  227,  938,  939,  940,  941,  942,
  943,-32766,  457,  226,  225,  224,  222,  440,  955,  221,
  909,  220,  219,  218,  217,  216,-32766,   15,  247,   57,
  133,   16,   18,   19,  458,  341,  528,  658,-32766,-32766,
  821,  718,-32766,-32766,  922, 1079,  923,  924,  925,  926,
  927,  928,  929,  930,  931,  932,  933, 1077,  934,  716,
  820,  164,  936,  937,  946,  948,  947,  725,  632,  681,
 1060,  798, 1014,  887,  823,-32766,-32766, 1009,  525,  512,
   20,  375,  374,  373,  372,  365,  363,  362,  360,  359,
  358,  356,  353,  350,  349,  348,  347,  346,   22,   21,
  433,  434,  435,  134,  456,  953,  458,  135,  890,   77,
    0,    0,    0,    0,  944,    0,  945,    0,  938,  939,
  940,  941,  942,  943,-32766,  457,    0,    0,    0,    0,
  440,  955,    0,    0,    0,    0,    0,    0,    0,-32766,
    0,  247,   57,    0,    0,    0,    0,  458,    0,    0,
    0,-32766,-32766,    0,    0,-32766,-32766,  922,    0,  923,
  924,  925,  926,  927,  928,  929,  930,  931,  932,  933,
    0,  934,    0,    0,  164,  936,  937,  946,  948,  947,
    0,    0,    0,    0,    0,    0,    0,    0,-32766,-32766,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  433,  434,  435,    0,  456,  953,    0,
    0,    0,   77,    0,    0,    0,    0,  944,    0,  945,
    0,  938,  939,  940,  941,  942,  943,-32766,  457,    0,
    0,    0,    0,  440,  955,    0,    0,    0,    0,    0,
    0,    0,-32766,    0,    0,   57,    0,    0,    0,    0,
-32766,    0,    0,    0,-32766,-32766,    0,    0,-32766,-32766,
  172,  382,  383,  384,   14,  385,    0,  312,    0,    0,
  259,  260,  386,  103,  387,  104,  388,  389,    0,  240,
  241,  544,   62,  105,  313,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  267,    0, -485,    0,    0,    0,    0,  315,  316,
  390,  391,  392,  393,  394,    0,  268,  269,   30,   31,
   32,    0,  396,    0,    0,    0,    0,    0,    0,    1,
  590,    0,    0,    0,    0, -104,    0,    0,  247,    0,
    0,    0,    0,    0,  263,  172,  382,  383,  384,   14,
  385,    0,  312,    0,    0,  259,  260,  386,  103,  387,
  104,  388,  389,    0,  240,  241,  544,   62,  105,  313,
    0,    0,    0,    0,    0,   -1,  172,  382,  383,  384,
   14,  385,    0,  312,    0,    0,  259,  260,  386,  103,
  387,  104,  388,  389,    0,  240,  241,  544,   62,  105,
  313,    0,    0,    0,    0,    0,  267,    0,    0,    0,
    0,    0,    0,  315,  316,  390,  391,  392,  393,  394,
    0,  268,  269,   30,   31,   32,    0,  396,    0,    0,
    0,    0,    0,    0,    1,    0,    0,  267,    0,    0,
 -104,    0,    0, -376,  315,  316,  390,  391,  392,  393,
  394,    0,  268,  269,   30,   31,   32,    0,  396,    0,
    0,    0,    0,    0,    0,    1,    0,    0,    0,    0,
    0, -104,  172,  382,  383,  384,   14,  385,    0,  312,
    0,    0,  259,  260,  386,  103,  387,  104,  388,  389,
    0,  240,  241,  544,   62,  105,  313,    0,    0,    0,
    0,  172,  382,  383,  384,   14,  385,    0,  312,    0,
    0,  259,  260,  386,  103,  387,  104,  388,  389,    0,
  240,  241,  544,   62,  105,  313,    0,    0,    0,    0,
    0,    0,    0,  267,    0,  120,    0,    0,    0,    0,
  315,  316,  390,  391,  392,  393,  394,    0,  268,  269,
   30,   31,   32,    0,  396,    0,    0,    0,    0,    0,
    0,    1,  267,    0,    0,    0,    0, -104,    0,  315,
  316,  390,  391,  392,  393,  394,    0,  268,  269,   30,
   31,   32,    0,  396,    0,    0,    0,    0,    0,    0,
    1,  804,    0,    0,    0,    0, -104,  172,  382,  383,
  384,   14,  385,    0,  312,    0,    0,  259,  260,  386,
  103,  387,  104,  388,  389,    0,  240,  241,  544,   62,
  105,  313,    0,    0,    0,    0,    0,  172,  382,  383,
  384,   14,  385,    0,  312,    0,    0,  259,  260,  386,
  103,  387,  104,  388,  389,    0,  240,  241,  544,   62,
  105,  313,    0,    0,    0,    0,    0,    0,  267,    0,
    0,    0,    0,    0,    0,  315,  316,  390,  391,  392,
  393,  394,    0,  268,  269,   30,   31,   32,    0,  396,
    0,    0,    0,    0,    0,    0,    1,  595,  267,    0,
    0,    0, -104,    0,    0,  315,  316,  390,  391,  392,
  393,  394,    0,  268,  269,   30,   31,   32,    0,  396,
    0,    0,    0,    0,    0,    0,    1,  594,    0,    0,
    0,    0, -104,  172,  382,  383,  384,   14,  385,    0,
  312,    0,    0,  259,  260,  386,  103,  387,  104,  388,
  389,    0,  240,  241,  544,   62,  105,  313,    0,    0,
    0,    0,    0,  172,  382,  383,  384,   14,  385,    0,
  312,    0,    0,  259,  260,  386,  103,  387,  104,  388,
  389,    0,  240,  241,  544,   62,  105,  313,    0,    0,
    0,    0,    0,    0,  267,    0,    0,    0,    0,    0,
    0,  315,  316,  390,  391,  392,  393,  394,    0,  268,
  269,   30,   31,   32,    0,  396,    0,    0,    0,    0,
    0,    0,    1,  593,  267,    0,    0,    0, -104,    0,
    0,  315,  316,  390,  391,  392,  393,  394,    0,  268,
  269,   30,   31,   32,    0,  396,    0,    0,    0,    0,
    0,    0,    1,  592,    0,    0,    0,    0, -104,  172,
  382,  383,  384,   14,  385,    0,  312,    0,    0,  259,
  260,  386,  103,  387,  104,  388,  389,    0,  240,  241,
  544,   62,  105,  313,    0,    0,    0,    0,    0,  172,
  382,  383,  384,   14,  385,    0,  312,    0,    0,  259,
  260,  386,  103,  387,  104,  388,  389,    0,  240,  241,
  544,   62,  105,  313,    0,    0,    0,    0,    0,    0,
  267,    0,    0,    0,    0,    0,    0,  315,  316,  390,
  391,  392,  393,  394,    0,  268,  269,   30,   31,   32,
    0,  396,    0,    0,    0,    0,    0,    0,    1,  591,
  267,    0,    0,    0, -104,    0,    0,  315,  316,  390,
  391,  392,  393,  394,    0,  268,  269,   30,   31,   32,
    0,  396,    0,    0,    0,    0,    0,    0,    1,  590,
    0,    0,    0,    0, -104,  172,  382,  383,  384,   14,
  385,    0,  312,    0,    0,  259,  260,  386,  103,  387,
  104,  388,  389,    0,  240,  241,  544,   62,  105,  313,
    0,    0,    0,    0,  172,  382,  383,  384,   14,  385,
    0,  312,    0,    0,  259,  260,  386,  103,  387,  104,
  388,  389,    0,  240,  241,  544,   62,  105,  313,    0,
    0,    0,    0,    0,    0,    0,  267,    0,  102,    0,
    0,    0,    0,  315,  316,  390,  391,  392,  393,  394,
    0,  268,  269,   30,   31,   32,    0,  396,    0,    0,
    0,    0,    0,    0,    1,  267,    0,    0,    0,    0,
 -104,    0,  315,  316,  390,  391,  392,  393,  394,    0,
  268,  269,   30,   31,   32,  106,  396,    0,    0,    0,
  163,    0,    0,    1,    0,    0,    0,    0,    0, -104,
    0,    0,    0,    0,  158,  159,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  545,    0,    0,
    0,    0,    0,    0,    0,-32766,    0,    0,    0,  810,
  811,  812,    0,  410,    0,    0,    0,    0,    0,  314,
    0,    0,    0,    0,-32766,-32766,    0, 1032,  411,  412,
    0,    0,    0,  395,  829,    0,  813,  809,  807,  830,
    0,   39,  165,   43,    0,  808,    0,    0,  160,    0,
    0,   56,    0,   23,    0,    0,  262,    0,  317,    0,
  161,  151,  546,    0,  152,  153,   24,-32766,-32766,-32766,
    0,    0,    0,-32766,    0,    0,    0,    0,    0,    0,
    0,  722,  723,  724,    0,    0,    0,    0,-32766,    0,
    0,    0,    0,    0,    0,    0,-32766,    0,    0,    0,
-32766,-32766,    0,    0,-32766,-32766,  829,    0,    0,  721,
  719,  830,    0,    0,    0,    0,    0,  720,    0,    0,
    0,    0,    0,   61
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1894

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
   96,   62,   63,   90,   91,   83,   99,    9,   16,   96,
   88,   72,   67,   74,   39,   40,   77,   78,   79,   80,
   81,   14,   83,   28,   29,   30,   24,   88,   89,   84,
   92,   92,   33,   34,   91,   90,   97,   10,  100,  100,
  102,   98,  103,  104,  105,   16,  107,  108,  109,  110,
  111,  112,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   25,   83,   95,   92,
   20,  106,   99,    3,    4,    5,    6,  100,   97,  102,
   96,   92,   90,   13,   14,   15,   16,   87,   87,  100,
  109,  102,  107,  108,   61,   31,   83,   97,   97,   58,
   59,   60,   37,   62,   63,   64,   32,   67,   67,   96,
   69,   70,   71,   72,   73,   74,   75,   76,   77,   78,
   79,   80,   81,   90,   83,   92,   64,   90,   31,   88,
   89,   90,   91,  100,   38,  102,   99,   96,   98,   64,
   99,  100,   26,   27,  104,    2,  105,    4,    5,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   64,   16,
   90,   83,   19,   20,   21,   22,   23,   24,   96,   99,
   98,   65,   84,   84,  104,   67,   33,   34,   90,   90,
   35,   36,   14,   76,   77,   78,   67,   90,   83,   82,
   41,   42,   56,   57,   66,   67,   99,   90,   83,   92,
  103,   58,   59,   60,   83,   62,   63,   83,   83,  102,
   67,  104,  105,   83,   83,   72,   83,   74,   83,   76,
   77,   78,   79,   80,   81,   82,   83,   83,   87,   83,
   83,   88,   89,   83,   91,   83,   83,   89,   84,   84,
   97,   84,   99,  100,   76,   77,   78,   84,  105,   87,
   82,   90,  109,  110,   89,   89,  113,  114,    2,   89,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   89,   16,  105,   89,   19,   20,   21,   22,   23,
   24,   89,   91,   90,   90,   90,   90,   90,   90,   33,
   34,   90,   90,   93,   91,   91,   91,   98,   92,   92,
   -1,   93,   93,   93,   93,   93,   93,   93,   93,   -1,
   -1,   95,   95,   95,   58,   59,   60,   95,   62,   63,
   95,   95,   95,   67,   96,   96,   96,   96,   72,   96,
   74,   96,   76,   77,   78,   79,   80,   81,   82,   83,
   96,   96,   96,   96,   88,   89,   96,   91,   96,   96,
   96,   96,  101,   97,   96,   99,  100,   96,   96,   96,
  100,  105,   98,   98,   98,  109,  110,   98,   98,  113,
  114,    2,   98,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   98,   16,   99,   99,   19,   20,
   21,   22,   23,   24,   99,   99,   99,   99,   99,   99,
   99,   99,   33,   34,   99,   99,   99,   99,   99,   99,
   99,   99,   99,   99,   99,   99,   99,   -1,  100,  100,
  100,  100,  100,  100,  100,  100,  100,   58,   59,   60,
  100,   62,   63,  100,  100,  100,   67,  100,  100,  100,
  100,   72,  100,   74,  100,   76,   77,   78,   79,   80,
   81,   82,   83,  100,  100,  100,  100,   88,   89,  100,
   91,  100,  100,  100,  100,  100,   97,  101,   99,  100,
  103,  101,  101,  101,  105,  101,  101,  101,  109,  110,
  101,  101,  113,  114,    2,  101,    4,    5,    6,    7,
    8,    9,   10,   11,   12,   13,   14,  101,   16,  101,
  101,   19,   20,   21,   22,   23,   24,  101,  101,  101,
  101,  101,  101,  101,  101,   33,   34,  101,  101,  101,
  101,  101,  101,  101,  101,  101,  101,  101,  101,  101,
  101,  101,  101,  101,  101,  101,  101,  101,  101,  101,
   58,   59,   60,  104,   62,   63,  105,  105,  108,   67,
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
   -1,    1,    2,    3,    4,    5,    6,   -1,    8,   -1,
   -1,   11,   12,   13,   14,   15,   16,   17,   18,   -1,
   20,   21,   22,   23,   24,   25,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   62,   -1,   64,   -1,   -1,   -1,   -1,
   69,   70,   71,   72,   73,   74,   75,   -1,   77,   78,
   79,   80,   81,   -1,   83,   -1,   -1,   -1,   -1,   -1,
   -1,   90,   62,   -1,   -1,   -1,   -1,   96,   -1,   69,
   70,   71,   72,   73,   74,   75,   -1,   77,   78,   79,
   80,   81,   -1,   83,   -1,   -1,   -1,   -1,   -1,   -1,
   90,   91,   -1,   -1,   -1,   -1,   96,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   -1,   -1,   -1,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   -1,   -1,   -1,   -1,   62,   -1,
   -1,   -1,   -1,   -1,   -1,   69,   70,   71,   72,   73,
   74,   75,   -1,   77,   78,   79,   80,   81,   -1,   83,
   -1,   -1,   -1,   -1,   -1,   -1,   90,   91,   62,   -1,
   -1,   -1,   96,   -1,   -1,   69,   70,   71,   72,   73,
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
   -1,   -1,   -1,   -1,    1,    2,    3,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   17,   18,   -1,   20,   21,   22,   23,   24,   25,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   62,   -1,   64,   -1,
   -1,   -1,   -1,   69,   70,   71,   72,   73,   74,   75,
   -1,   77,   78,   79,   80,   81,   -1,   83,   -1,   -1,
   -1,   -1,   -1,   -1,   90,   62,   -1,   -1,   -1,   -1,
   96,   -1,   69,   70,   71,   72,   73,   74,   75,   -1,
   77,   78,   79,   80,   81,   14,   83,   -1,   -1,   -1,
   19,   -1,   -1,   90,   -1,   -1,   -1,   -1,   -1,   96,
   -1,   -1,   -1,   -1,   33,   34,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   46,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   14,   -1,   -1,   -1,   58,
   59,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   68,
   -1,   -1,   -1,   -1,   33,   34,   -1,   76,   77,   78,
   -1,   -1,   -1,   82,   83,   -1,   85,   86,   87,   88,
   -1,   90,   19,   92,   -1,   94,   -1,   -1,   97,   -1,
   -1,  100,   -1,  102,   -1,   -1,  105,   -1,  107,   -1,
  109,  110,  111,   -1,  113,  114,  115,   76,   77,   78,
   -1,   -1,   -1,   82,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   58,   59,   60,   -1,   -1,   -1,   -1,   97,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  105,   -1,   -1,   -1,
  109,  110,   -1,   -1,  113,  114,   83,   -1,   -1,   86,
   87,   88,   -1,   -1,   -1,   -1,   -1,   94,   -1,   -1,
   -1,   -1,   -1,  100
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1653,  221,  889, 1528, 1402, 1372, 1624, 1121, 1025,  994,
 1498, 1276, 1246, 1150, 1653, 1653, 1653, 1653, 1653, 1653,
 1653, 1653, 1653,  362,  350,  365,  346,  345,  372,  328,
  109,  109,  109,  109,  109,  109,  549,  436,  323,  662,
  775,  775,  250,  -31,   60,  220,  -52,  -52,  -52,  -52,
   74,  115,  217,  -51,  -51,  -51,  269,  268,  172,  494,
  288,  343,  381,  381,  381,  382,  382,  382,  381,  381,
  381,  381,  382,  381, 1721, 1721, 1721,  382,  382,  382,
  382,  382,  382,  382,  382,  382,  382,  382,  382,  382,
  382,  382, 1721,  382,  382, 1721, 1721,  382, 1721,  382,
  382,  378,  378, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721,  373, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721,    9,    9,    9,  177,  177,  348,  348,  348,  348,
  348,  348,  348,  348,  348,  348,  348,  348,  348,  348,
  348,  348,  348,  348,  348,  348,  348,  348,  348,  348,
  348,  348,  348,  348,  348,  348,  348,  348, 1761, 1761,
 1761, 1761, 1761, 1761, 1761, 1761,  287,  287,  287,   77,
   29,  199,   83,  467,  559,  392,  468,  384,  380,  560,
  393,  395,  385,  385,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3, 1793, 1793, 1793,
  374,  476,  213,  -21,  -37,   57,   57,   57,   57,  377,
  377,  377,  299,  299,  299,  299,  299,  299,  299,  299,
  299,  299,  299,  299,  299,  299,  299,  299,  299,  299,
  299,  299,  277,  157,  157,  157,  165,  165,  165,  -24,
  -24,  -24,  -24,  -24,  -24,  164,  193,   78,   78,   78,
   78,   78,   78,  108,  -28,  145,  -28,  -28,  149,  311,
  301,  162,  518,  498,   92,  621,  499,  230,  327,  326,
  296,  325,  161,  316,  308,  324,  329,  153,  427,  426,
  252,  230,  327,  326,  113,  546,  550,  443,  554,  296,
  325,  325,  325,  325,  325,  161,  161,  316,  329,  329,
  430,  556,  180,  555,  551,  552,  181,   52,   52,   52,
   52,   52,  374,  315,  515,  332,  332,  620,  168,  313,
  515,  544,  544,  374,  374,  374,  480,  466,  374,  515,
  513,  197,  444,  489,  489,  445,  386,  386,  450,  374,
  374,  374,  486,  519,  374,  374,  496,  496,  496,  496,
  490,  374,  486,  496,  519,  374,  496,  374,  496,  496,
  496,  374,  496,  490,  374,  496,  374,  374,  374,  374,
  374,  374,  496,  496,  496,  496,  490,  374,  374,  374,
  374,  374,  506,  488,  505,  510,  504,  487,  341,  435,
  434,  304,  305,  310,  258,  440,  497,   16,  433,  276,
  244,  254,  547,  619,  622,  245,  100,  503,  432,  408,
  517,  501,  500,  545,  407,  406,  446,  295,  514,  335,
  376,  375,  543,  542,  391,  596,  541,  539,  536,  506,
  505,  510,  504,  479,  478,  477,  304,  310,  481,  482,
  475,  485,  274,  390,  449,  593,  389,  592,  425,  535,
  502,  141,  127,  149,  424,  415,  517,  492,  534,  398,
  413,  333,  396,  337,  591,  491,  616,  615,  614,  598,
  371,  449,  613,  286,  244,  254,  547,  619,  622,  245,
  245,  245,  590,  612,  495,  276,  276,  119,  407,  442,
  285,  533,  524,  522,  520,  330,  383,  402,  402,  402,
  411,  334,  597,  589,  611,  610,  609,  608,  607,  394,
  387,  387,  493,  606,  588,  605,   68,  441,  587,  604,
  586,  342,  397,  405,  410,  579,  388,  255,  409,  438,
  599,  603,  602,  601,  600,  431,  578,  576,  618,  321,
  402,  617,  242,  564,    0,    0,    0,    0, 1721, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721,   -2,   -2,   -2,   -2,   -2,   -2,   -2,    0,    0,
    0,    0,    0,    0, 1721, 1721, 1721, 1721, 1721, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721, 1721,    0,    0,    0, 1721, 1721, 1721, 1721, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
    0, 1721, 1721,    0,    0, 1721,    0, 1721, 1721, 1721,
 1721,    0,    0,    0,    0,    0,    0,    0,    0, 1721,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721, 1721,
 1721, 1721, 1721, 1721, 1793, 1793, 1793,   -3,   -3,   -3,
    0,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  137,  137,
  169,  169,  169,  169,  169,  169,  169,  169,  169,  169,
  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,
  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,
   52,  169,  169,  169,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   52,   52,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  153,   52,   52,    0,
  496,  496,    0,  496,  496,  517,  501,  500,    0,    0,
    0,    0,    0,  545,    0,    0,  379,  379,    0,  517,
  501,  500,    0,  454,  454,  454,  454,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  379,  454,
    0,  454,  454,  454
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 306

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  393,  394,  395,  485,  485,  485,  485,
32767,  347,32767,32767,32767,32767,  532,  532,  532,  532,
32767,  347,  106,32767,32767,32767,32767,32767,32767,   96,
  355,32767,  106,  106,  106,32767,32767,32767,  106,  106,
  106,  106,32767,  106,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,   96,32767,  385,  386,32767,
32767,32767,32767,32767,32767,   98,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  231,  233,32767,32767,
32767,32767,32767,32767,  387,32767,32767,32767,32767,32767,
  108,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  493,32767,  360,   95,  352,  358,  353,  538,
  362,  371,  356,   97,  359,  372,  493,32767,  153,  155,
32767,32767,  243,32767,  146,  241,  242,  239,  238,  127,
  539,  373,  513,  513,  513,  513,  513,  513,  513,  513,
  513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
  513,  347,32767,  147,  154,  156,  207,  208,  209,32767,
32767,32767,  388,  389,32767,  382,  383,32767,32767,32767,
32767,32767,32767,  530,  219,  187,  221,  220,  471,  108,
  108,  179,  485,  485,32767,  485,  485,32767,32767,32767,
  205,  210,  216,  226,  228,32767,  189,  471,32767,32767,
32767,  404,  391,  392,  235,32767,32767,32767,32767,  206,
  212,  214,  215,  211,  213,  217,  218,  227,  190,  191,
32767,32767,32767,32767,32767,32767,32767,  108,  108,  108,
  108,  108,32767,32767,32767,32767,32767,  344,   81,32767,
32767,  511,  511,32767,32767,  379,  541,  346,32767,32767,
   83,   85,  346,  505,  505,  346,  525,  525,  346,32767,
32767,32767,  184,  528,32767,32767,  485,  485,  485,  485,
  487,32767,  184,  485,  528,32767,  485,32767,  485,  485,
  485,32767,  485,  487,32767,  485,32767,32767,32767,32767,
32767,32767,  485,  485,  485,  485,  487,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  281,32767,32767,  192,
  195,  197,  199,  201,  203,  222,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  107,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  374,
  375,  377,  384,  262,  263,  264,  396,  397,  484,  281,
  282,32767,32767,32767,  348,32767,32767,32767,32767,32767,
32767,32767,  268,  266,32767,32767,  404,  281,32767,   50,
32767,32767,32767,32767,32767,  517,32767,32767,32767,32767,
32767,  349,32767,32767,  196,  198,  200,  202,  204,  223,
  224,  225,32767,32767,32767,  193,  194,32767,   79,32767,
32767,32767,32767,32767,32767,  347,32767,  475,  476,  473,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  524,  522,  275,32767,32767,32767,   63,32767,32767,32767,
32767,32767,   53,  472,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  474,32767,32767,32767,  541,  465,  465,  541
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  191,  186,  186,  186,  189,  189,  189,  189,  187,  189,
  184,  191,  191,  191,  174,  174,  453,  185,  192,  179,
  184,  184,  184, 1042, 1042,  913,  184,  184,  184,  184,
  473,  184,  187,  187,  187,  697,  697,  697,  514,  536,
  543,  311,  489,  731,  731,  731,  517,  529,  530,  538,
  187,  541,  496,  187,  187, 1062,  187,  471, 1081,  196,
  182,  169,  173,  185,  171,  169,  173,  188,  175,  190,
  176,  177,  178,  193,  194,  195,  180,  181,  183,  284,
 1084, 1068, 1068, 1068, 1068, 1068, 1068, 1068, 1068, 1068,
 1068, 1068, 1068, 1068, 1068, 1068, 1068, 1068, 1068, 1068,
 1068,  498,  499,  474,  698,  698,  698,  540,  415,  415,
  415,  415,  415,  415,  918,  918,  918,  918,  918,  918,
  475,  300,  610,  279,  800,  279, 1011,  800,  800,  800,
  800,  476,  717,  717,  717, 1010,  477,  285,  286,  288,
  801,  682,  452,  801,  801,  801,  801,  682,  682,  682,
   11,   12,   13,   13,  731,  301,  478,  371,  303,  304,
  289,  305,  211,  717,  717,  717,  210,  210,  210,  210,
  380,  210, 1064,  211,  211,  211,  203,  203,  465,  465,
  465,  465,  465,  465,  465,  465,  465,  465,  465,  465,
  465,  465,  465,  465,  465,  465,  465,  465,  788,  784,
  785,  777,  778,  780,  782,  258,  277,  277,  277,  277,
  277,  467,  468,  472,  483,  503,  504,  505,  506,  507,
  508,  513,  515,  519,  531,  532,  533,  534,  535,  297,
 1069,  479,  480,  481,  318,  827,  796,  679,  699,  714,
 1057,  205,  206,  207,  208, 1051, 1052,  318,  728,  689,
 1043,  730,  730,  730,  484,  736,  485,  486,  696,  696,
  696,  630,  634,  615,  677,  712, 1049, 1050,  298,  299,
  677,  677,  677,  710,  233,  234,  235, 1037,  688, 1038,
  608,  427,  428, 1039,  427,  428, 1040,  352, 1029, 1030,
 1044, 1045, 1046, 1031,  712,  712,  712,  237,  238,  705,
  706,  707,  708,  709, 1067, 1067, 1067, 1067, 1067, 1067,
 1067, 1067, 1067, 1067, 1067, 1067, 1067, 1067, 1067, 1067,
 1067, 1067, 1067, 1067,  290,  291,  292,  293,  294,  256,
  257,  488,  414,  414,  414,  414,  414,  275,  275,  275,
  275,  275,  275,  275,  275,  275,  275,  275,  275,  275,
  275,  275,  275,  275,  275,  275,  275,  275,  275,  275,
  674,  328,  328,  487,  916,  351,  914,  674,  674,  674,
  295,  296,  686,  653,  674, 1055,  824,  824,  726,  674,
  674,  674,  674,  674,  674,  674,  674,  674,  674,  674,
  674,  674,  674,  674,  660,  674,  674,  692,  691,  674,
 1018,  674,  674,  792,  343,  354,  537, 1036,  334,  421,
  345,  511,  123,  917,  902,  663,  664,  665,  666,  667,
  668,  669,  670,  671,  672,  673,  661,  662,  162,  660,
 1083,  329,    0,  905, 1066, 1026, 1085,    0,  609,  608,
    0,    0,    0,    0,    0,  355,  357,  361,  527,  409,
    0,    0,  366,    0,    0,  367,    0,  368,  369,  370,
    0,    6,    0,  409,    7,    0,    0,  550,    0,    0,
    0,  377,  378,  379,  542,  551,  406,  553,  553,  553,
  553,  406,  516,  613,  612,  624,  625,  623,  622,  621,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  494,  494,  494,    0,    0,    0,    0,
  448,  454,  455,  460,  500
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 515

static char yygcheck[] = {
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   74,   37,   37,   37,
   37,   37,   37,    7,    7,   72,   37,   37,   37,   37,
   66,   37,   37,   37,   37,   63,   63,   63,   98,   98,
   98,   40,   40,    7,    7,    7,   40,   40,   40,   40,
   37,   40,  120,   37,   37,  120,   37,   67,  120,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   56,
  100,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   81,   81,   43,   97,   97,   97,   81,   63,   63,
   63,   63,   63,   63,   56,   56,   56,   56,   56,   56,
   44,   79,    7,   79,    7,   79,   65,    7,    7,    7,
    7,   45,   74,   74,   74,   65,   46,   69,   69,   69,
   97,   97,   62,   97,   97,   97,   97,   97,   97,   97,
    3,    3,    3,    3,    7,   69,   47,  102,   69,   69,
   48,   69,   39,   74,   74,   74,   39,   39,   39,   39,
  102,   39,   95,   39,   39,   39,   39,   39,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   55,   55,
   55,   55,   55,   55,   55,   74,   74,   74,   74,   74,
   74,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   93,   54,
   74,   53,   53,   53,    7,   58,   58,   58,   58,   58,
   58,   57,   57,   57,   57,    7,    7,    7,  118,  118,
    7,   41,   41,   41,   41,   41,   42,   42,   62,   62,
   62,    7,    7,    7,   59,   59,    7,    7,  108,  108,
   59,   59,   59,    7,  114,  114,  114,    7,  119,    7,
   35,   76,   76,    7,   76,   76,    7,   32,    7,    7,
    7,    7,    7,    7,   59,   59,   59,   49,   49,    7,
    7,    7,    7,    7,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   50,   50,   50,   50,   50,   52,
   52,   62,   62,   62,   62,   62,   62,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
  109,  101,  101,   19,   73,  101,   73,  109,  109,  109,
   51,   51,  111,   31,  109,   60,   60,   60,   60,  109,
  109,  109,  109,  109,  109,  109,  109,  109,  109,  109,
  109,  109,  109,  109,   38,  109,  109,  113,  113,  109,
   80,  109,  109,  103,  103,  103,  103,  103,   91,    9,
   89,  104,  121,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   38,  106,   38,
   38,  123,   -1,   38,  105,   38,   38,   -1,   35,   35,
   -1,   -1,   -1,   -1,   -1,  101,  101,  101,  101,   31,
   -1,   -1,  101,   -1,   -1,  101,   -1,  101,  101,  101,
   -1,  101,   -1,   31,  101,   -1,   -1,    4,   -1,   -1,
   -1,  101,  101,  101,  101,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   82,   82,   82,   -1,   -1,   -1,   -1,
   31,   31,   31,   31,   31
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  146,  467,    0,    0,  -78,    0,   93,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  124,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  203,   55,    0,    0,  238,    0,  -42,  336,  120,
  -22,  130,  128,  -27,  -11,   -1,    3,   22,   25,  161,
  186,  227,  184,   84,   79,   47,   78,   83,  211,   61,
  213,    0,   92, -131,    0, -194,  -14,   12,    0,   63,
    0,    0,  -16,  311,  -34,    0,  250,    0,    0, -118,
  156,   35,  337,    0,    0,    0,    0,    0,    0,   76,
    0,   86,    0,   -2,    0,  -59,    0,  -62,   -9,    0,
   29,   99, -206,  155,   74,   80, -119,    0,  142,  302,
    0,  111,    0,  230,   77,    0,    0,    0,  126,   46,
 -280,   60,    0, -115
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  397,    8,   10,  552,  555,  554,  556,  557,  420,
  558,  332,  570,  559,  586,  587,  588,  616,  589,  451,
  560,  331,  339,  628,  565,  566,  307,  567,  568,  280,
  569,  408,  657,  571,  561,  562,  398,  170, 1025,  209,
  310,  683,  399,  400,  401,  402,  403,  404,  270,  236,
  271,  272,  254,  405,  273,  274,  783,  202,  825,  794,
  793,  815,  816,  817,  818, 1012,  443,  444,   45,  287,
  416,  327,  912,  915,  814,  441,  426, 1048,  604,  278,
 1017,  497,  413,  605, 1027,  734, 1028,  606,  607,  344,
  253,  333, 1054,  466,  335, 1063,  799,  819,  482,  338,
 1082,  442,  364, 1034,  510,  523,   63,  255,  276,  659,
  261,  685,  232,  690,  204,  693,  711,  684,  687,  729,
  470,  122,   44,  320
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
   17,   17,   17,   18,   18,   18,   18,   18,   19,   19,
   20,   21,   21,   22,   22,   23,   23,   33,   33,   33,
   33,   33,   24,   24,   25,   26,   26,   26,   26,   27,
   28,   29,   29,   30,   36,   36,   40,   40,   31,   31,
   32,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   38,   38,   39,   39,
   39,   39,   39,   39,   39,  109,  109,  110,  110,  111,
  111,  111,  112,  112,  112,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  115,  115,  115,
  115,  115,  115,  114,  114,  114,  114,  114,  114,  116,
  116,  116,  116,  116,  116,  116,  116,  116,  116,  117,
  117,  118,  118,  119,  121,  121,   41,   41,   41,  107,
  107,  107,  108,  108,  108,   42,   42,   43,   43,   44,
   44,   45,   45,   46,   46,   47,   47,   48,   48,   48,
   49,   49,   49,   49,   49,   49,   50,   50,   50,   51,
   51,   51,   52,   52,   52,   52,   53,   53,   54,   54,
   54,   54,   54,   54,   54,   55,   55,   55,   55,   55,
   55,   55,   55,   56,   56,   57,   57,   57,   57,   57,
   57,   57,   96,   96,   97,   97,   97,   59,   59,   60,
   60,   60,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   74,   74,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   62,   62,   61,   61,  122,   63,  120,  120,   66,   66,
   68,   68,   67,   67,   67,   67,   67,   67,   69,   69,
   70,   70,   70,   70,   71,   71,   72,   72,   72,   72,
   72,   73,   73,   73,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   64,   64,   64,  123,   65,   78,   78,   79,
   79,   80,   80,   80,   80,   80,   80,   81,   81,   83,
   83,   84,   84,   84,   82,  101,  101,  102,  102,   85,
   85,   85,   85,   85,   85,   85,   86,   86,   86,   76,
   76,   87,   87,   88,   88,   89,   89,   90,   90,   90,
   90,   91,   91,   93,   93,   94,   94,   95,   95,   95,
   95,   95,  103,  103,  103,  104,  104,  104,  105,  105,
   92,   92,   98,   98,   99,   99,   99,   99,  100,  100,
  100,  106
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
    2,    3,    2,   10,    9,    8,    7,    8,    1,    1,
    4,    0,    3,    0,    3,    0,    2,    3,    4,    3,
    4,    2,    5,    2,    3,    2,    1,    4,    3,    4,
    3,    1,    3,    2,    0,    2,    0,    1,    0,    1,
    4,    1,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    1,    1,    2,    2,
    4,    3,    3,    4,    2,    1,    4,    1,    2,    4,
    3,    5,    1,    3,    3,    1,    1,    2,    1,    1,
    1,    2,    2,    2,    3,    2,    3,    6,    6,    6,
    6,    7,    3,    1,    2,    4,    3,    3,    4,    1,
    3,    1,    1,    1,    1,    1,    1,    3,    2,    0,
    3,    1,    1,    1,    0,    1,    1,    1,    5,    1,
    3,    3,    1,    3,    3,    1,    3,    1,    3,    1,
    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,
    1,    3,    3,    3,    3,    3,    1,    3,    3,    1,
    3,    3,    1,    3,    3,    3,    1,    3,    1,    3,
    3,    2,    3,    2,    3,    1,    2,    2,    2,    2,
    2,    2,    2,    1,    3,    1,    2,    4,    3,    3,
    4,    2,    1,    1,    5,    9,    8,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    6,    3,    3,    3,    2,    2,    2,    2,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    2,    2,
    2,    3,    2,    4,    0,    4,    0,    1,    1,    2,
    1,    2,    1,    2,    2,    2,    3,    4,    1,    3,
    1,    2,    3,    4,    1,    3,    5,    3,    3,    2,
    1,    1,    2,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    2,    3,    3,    2,    0,    3,    3,    3,    1,
    3,    1,    4,    3,    6,    3,    3,    1,    3,    1,
    1,    7,    7,    7,    1,    0,    2,    0,    2,    6,
    6,    6,    6,    7,    7,    3,    7,    7,    7,    1,
    1,    5,    5,    3,    3,    0,    4,    1,    4,    3,
    3,    0,    3,    0,    2,    1,    3,    1,    4,    1,
    1,    2,    2,    1,    2,    0,    2,    3,    0,    3,
    0,    3,    0,    2,    1,    2,    3,    4,    1,    1,
    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 970
#define YYNLSTATES 548
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
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 77:
#line 333 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 80:
#line 342 "src/kinx.y"
{ yyval.obj = kx_gen_try_stmt_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 81:
#line 346 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 82:
#line 347 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 83:
#line 351 "src/kinx.y"
{ yyval.obj = kx_gen_var_object("_e", KX_UNKNOWN_T); } break;
        case 84:
#line 352 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(2-3).strinfo.name, KX_UNKNOWN_T, YYASP(2-3).strinfo.line, YYASP(2-3).strinfo.pos1, YYASP(2-3).strinfo.pos2); } break;
        case 85:
#line 356 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 86:
#line 357 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 87:
#line 361 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 88:
#line 362 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strinfo.name)); } break;
        case 89:
#line 363 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 90:
#line 364 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strinfo.name)); } break;
        case 91:
#line 365 "src/kinx.y"
{ yyval.obj = kx_gen_break_object(KXST_FALLTHROUGH, NULL); } break;
        case 92:
#line 369 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 93:
#line 370 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 94:
#line 374 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 95:
#line 378 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 96:
#line 379 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 97:
#line 380 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 98:
#line 381 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 99:
#line 385 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 100:
#line 389 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 101:
#line 393 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_OBJ_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2), NULL); } break;
        case 102:
#line 394 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object_line_pos(YYASP(3-3).strinfo.name, KX_OBJ_T, YYASP(3-3).strinfo.line, YYASP(3-3).strinfo.pos1, YYASP(3-3).strinfo.pos2), NULL); } break;
        case 103:
#line 398 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 104:
#line 402 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 105:
#line 403 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 106:
#line 407 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 108:
#line 412 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 110:
#line 417 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 112:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 113:
#line 423 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 114:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 115:
#line 425 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 116:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 117:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 118:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 119:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 120:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 121:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 122:
#line 432 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 123:
#line 433 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 124:
#line 434 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 125:
#line 435 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_expr_right_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 128:
#line 444 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 129:
#line 445 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 130:
#line 446 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 131:
#line 447 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 132:
#line 448 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 133:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 134:
#line 450 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 136:
#line 455 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 138:
#line 460 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 139:
#line 464 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-4).obj, YYASP(4-4).obj, NULL); } break;
        case 140:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 141:
#line 466 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 143:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 144:
#line 472 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 147:
#line 478 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 151:
#line 482 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 152:
#line 483 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 153:
#line 484 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 154:
#line 485 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 155:
#line 486 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 156:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 157:
#line 492 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 158:
#line 493 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 159:
#line 494 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 160:
#line 495 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 161:
#line 496 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 162:
#line 497 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 164:
#line 502 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 165:
#line 503 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 166:
#line 504 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 167:
#line 505 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 168:
#line 506 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 170:
#line 511 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 171:
#line 512 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 172:
#line 513 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 173:
#line 514 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 174:
#line 515 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 175:
#line 516 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 176:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 177:
#line 518 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 178:
#line 519 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 179:
#line 523 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 180:
#line 524 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 183:
#line 533 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 188:
#line 544 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 190:
#line 549 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALLPL, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 191:
#line 550 "src/kinx.y"
{ yyval.obj = kx_gen_expr_right_object(KXOP_CALLPR, KXOP_CALLPR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 193:
#line 555 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_COMPOSITL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 194:
#line 556 "src/kinx.y"
{ yyval.obj = kx_gen_expr_right_object(KXOP_COMPOSITR, KXOP_COMPOSITR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 561 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 566 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 200:
#line 571 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 581 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 206:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 208:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 209:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 211:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 212:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 213:
#line 599 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 214:
#line 600 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 215:
#line 601 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 217:
#line 606 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 218:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 220:
#line 612 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 221:
#line 613 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 223:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 224:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 225:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 227:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 229:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 230:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 231:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 232:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 233:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 234:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 236:
#line 640 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 237:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 238:
#line 642 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 239:
#line 643 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 240:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 241:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 242:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 244:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 246:
#line 656 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 247:
#line 657 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 248:
#line 658 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 249:
#line 659 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 250:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 251:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 252:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 254:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-5).arraytype, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(4-5).obj, NULL, NULL), NULL); } break;
        case 255:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-9).arraytype, NULL, YYASP(4-9).obj, kx_gen_stmt_object(KXST_RET, YYASP(8-9).obj, NULL, NULL), NULL); } break;
        case 256:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-8).arraytype, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 257:
#line 676 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 258:
#line 677 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 259:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 260:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 261:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 262:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 263:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 264:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 265:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 272:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 273:
#line 695 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 274:
#line 696 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 275:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 276:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 277:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 278:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 279:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 280:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 281:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_UNKNOWN_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2); } break;
        case 282:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(kx_gen_typestr_object(YYASP(1-1).intval), KX_UNKNOWN_T); } break;
        case 283:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object_pos(YYASP(1-1).strinfo); } break;
        case 284:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 285:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 286:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 287:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 288:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 289:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 290:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 291:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 292:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 293:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 294:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 295:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 296:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 297:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 298:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 299:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 300:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 301:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 302:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 303:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 304:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 305:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 306:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 307:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 308:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 309:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 310:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 311:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 312:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 313:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 314:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 315:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 316:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 317:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 318:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 319:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|>"); } break;
        case 320:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("**"); } break;
        case 321:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 322:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 323:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 324:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 325:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 326:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 327:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 328:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 329:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 330:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 331:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 332:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 333:
#line 761 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 334:
#line 762 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 335:
#line 763 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 336:
#line 764 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 337:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 338:
#line 766 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 339:
#line 767 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 340:
#line 771 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 341:
#line 772 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 342:
#line 776 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 343:
#line 777 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 344:
#line 781 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 345:
#line 785 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 346:
#line 789 "src/kinx.y"
{} break;
        case 348:
#line 794 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 349:
#line 795 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 350:
#line 799 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 351:
#line 800 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 353:
#line 805 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 354:
#line 806 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 355:
#line 807 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 356:
#line 808 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 357:
#line 809 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 359:
#line 814 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 361:
#line 819 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 362:
#line 820 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 363:
#line 821 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 365:
#line 826 "src/kinx.y"
{ yyval.obj = kx_gen_exprlist(YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 366:
#line 830 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 367:
#line 831 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 368:
#line 832 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 369:
#line 833 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 370:
#line 834 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 372:
#line 839 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_PIN; } break;
        case 374:
#line 844 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 375:
#line 845 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 376:
#line 846 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 377:
#line 847 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 378:
#line 848 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 379:
#line 849 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 380:
#line 850 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 381:
#line 851 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 382:
#line 852 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 383:
#line 853 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 384:
#line 854 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 385:
#line 855 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 386:
#line 856 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 387:
#line 857 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 388:
#line 858 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 389:
#line 859 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 390:
#line 860 "src/kinx.y"
{ yyval.strval = "native"; } break;
        case 391:
#line 861 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 392:
#line 862 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 393:
#line 863 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 394:
#line 864 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 395:
#line 865 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 396:
#line 866 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 397:
#line 867 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 398:
#line 868 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 399:
#line 869 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 400:
#line 870 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 401:
#line 871 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 402:
#line 872 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 403:
#line 873 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 404:
#line 874 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 405:
#line 875 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 406:
#line 876 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 407:
#line 877 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 408:
#line 881 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 409:
#line 882 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 410:
#line 883 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 411:
#line 884 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 412:
#line 885 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 413:
#line 886 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 414:
#line 887 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 415:
#line 888 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 416:
#line 889 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 417:
#line 890 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 418:
#line 891 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 419:
#line 892 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 420:
#line 893 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 421:
#line 894 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 422:
#line 895 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 423:
#line 896 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 424:
#line 897 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 425:
#line 898 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 426:
#line 899 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 427:
#line 900 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 428:
#line 901 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 429:
#line 902 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 430:
#line 903 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 431:
#line 904 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 432:
#line 905 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 433:
#line 906 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 434:
#line 907 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 435:
#line 908 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 436:
#line 909 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 437:
#line 910 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 438:
#line 911 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 439:
#line 912 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 440:
#line 913 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 441:
#line 914 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 442:
#line 915 "src/kinx.y"
{ yyval.strval = "**"; } break;
        case 443:
#line 916 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 444:
#line 917 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 445:
#line 918 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 446:
#line 919 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 447:
#line 920 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 448:
#line 921 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 449:
#line 922 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 450:
#line 923 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 451:
#line 924 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 452:
#line 925 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 453:
#line 926 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 454:
#line 927 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 455:
#line 928 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 456:
#line 929 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 457:
#line 930 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 458:
#line 931 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 459:
#line 932 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 460:
#line 933 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 461:
#line 934 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 462:
#line 938 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 463:
#line 939 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 464:
#line 940 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 465:
#line 944 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 466:
#line 948 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 467:
#line 952 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 468:
#line 953 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 470:
#line 958 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 471:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-1).obj, NULL); } break;
        case 472:
#line 963 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 473:
#line 964 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 474:
#line 965 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).obj, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 475:
#line 966 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 476:
#line 967 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 478:
#line 972 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 479:
#line 976 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 480:
#line 977 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 481:
#line 981 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 482:
#line 982 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 483:
#line 983 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, 0, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 484:
#line 987 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 485:
#line 991 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_UNKNOWN_T }; } break;
        case 486:
#line 992 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 487:
#line 996 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 488:
#line 997 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 489:
#line 1001 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 490:
#line 1002 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 491:
#line 1003 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 492:
#line 1004 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 493:
#line 1005 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-7).obj, NULL, NULL), NULL); } break;
        case 494:
#line 1006 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 495:
#line 1007 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 496:
#line 1011 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 497:
#line 1012 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 498:
#line 1013 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 499:
#line 1017 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strinfo.name; } break;
        case 501:
#line 1022 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 502:
#line 1023 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 503:
#line 1027 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 504:
#line 1028 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 505:
#line 1032 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 506:
#line 1034 "src/kinx.y"
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
        case 508:
#line 1050 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 509:
#line 1051 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 510:
#line 1052 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 511:
#line 1056 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 512:
#line 1057 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 513:
#line 1061 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 516:
#line 1067 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 518:
#line 1072 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 519:
#line 1073 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 520:
#line 1074 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 521:
#line 1075 "src/kinx.y"
{ YYASP(2-2).obj->var_type = KX_SPR_T; yyval.obj = YYASP(2-2).obj; } break;
        case 522:
#line 1079 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 523:
#line 1080 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 524:
#line 1081 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strinfo.name) }; } break;
        case 525:
#line 1085 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 526:
#line 1086 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 527:
#line 1087 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 528:
#line 1091 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 529:
#line 1092 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 530:
#line 1096 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 531:
#line 1097 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 532:
#line 1101 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 535:
#line 1107 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 536:
#line 1108 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 537:
#line 1109 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 540:
#line 1115 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 541:
#line 1119 "src/kinx.y"
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
