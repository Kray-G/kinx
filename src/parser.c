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
#define ADDEQ 297
#define SUBEQ 298
#define MULEQ 299
#define DIVEQ 300
#define MODEQ 301
#define ANDEQ 302
#define OREQ 303
#define XOREQ 304
#define LANDEQ 305
#define LOREQ 306
#define LUNDEFEQ 307
#define SHLEQ 308
#define SHREQ 309
#define REGEQ 310
#define REGNE 311
#define NUL 312
#define TRUE 313
#define FALSE 314
#define AS 315
#define IMPORT 316
#define USING 317
#define DARROW 318
#define SQ 319
#define DQ 320
#define MLSTR 321
#define BINEND 322
#define DOTS2 323
#define DOTS3 324
#define REGPF 325
#define NAMESPACE 326
#define SYSNS 327
#define SYSRET_NV 328
#define CLASS 329
#define SYSCLASS 330
#define MODULE 331
#define SYSMODULE 332
#define NATIVE 333
#define FUNCTION 334
#define SYSFUNC 335
#define PUBLIC 336
#define PRIVATE 337
#define PROTECTED 338
#define COROUTINE 339
#define NAME 340
#define STR 341
#define SRCFILE 342
#define BIGINT 343
#define INT 344
#define TYPE 345
#define TYPEOF 346
#define LBBR 347
#define RBBR 348
#define LMBR 349
#define RMBR 350
#define DBL 351
#define BIN 352
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
#line 1114 "src/kinx.y"

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
  "PipelineExpression : LogicalUndefExpression",
  "PipelineExpression : PipelineExpression PIPEOPL2R LogicalUndefExpression",
  "PipelineExpression : PipelineExpression PIPEOPR2L LogicalUndefExpression",
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
  "SimpleFuncCallFactor : LBBR FunctionType_Opt DARROW TernaryExpression RBBR",
  "SimpleFuncCallFactor : LBBR '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW TernaryExpression RBBR",
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
  "AnonymousFunctionDeclExpression : '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW TernaryExpression",
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
    0,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  112,  114,  114,  114,  110,  103,  114,
   98,   99,  108,  107,   96,   95,  100,  109,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,   97,   94,
  105,   93,  106,  104,  113,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  102,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  101,  114,  111,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  114,  114,    1,  114,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   57,   58,   59,   60,   61,   62,  114,
  114,  114,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,   92,  114
#line 165 "build/utility/kmyacc.c.parser"
};

#define YYBADCH 114
#define YYMAXLEX 353
#define YYTERMS 114
#define YYNONTERMS 123

static short yyaction[] = {
  821,  822,  823,  824,  825,  826,  827,  828,  829,  830,
  831,  832,  833,  835,  834,  126,  127,  836,  837,  838,
  847,  849,  848,-32766,  859,  860,  861,  863,  865,   78,
  433,  192,  193,  857,  858,  856,   37,  855,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,  145,  146,  147,  850,  851,  852,  115,  853,  854,
  886,  136,  137,  138, -365,   48,  107,   28,  845,    0,
  846, -365,  839,  840,  841,  842,  843,  844,   37,  819,
  122,  232,  112,  567,  820,  569,  568,  570,  434,  571,
   93,  165,  114,  867,  572,  573,  435,    1,  574,  872,
  873,  871,   17,  862,  864,  866,  868,  869,  870,  944,
  945,  946,  947,  948,  949,  950,  951,  952,  953,  954,
  955,  956,  595,  957,  793,  794,  958,  959,  960,  968,
  970,  969,  530,  981,  982,  983,  985,  987,  139,  140,
  817,   78,  979,  980,  978,  818,   37,   40,    3,   43,
    2,  575,  108,  330,  395,   64,  576,  117,  578,  577,
   46,  166,   25,  971,  972,  973,  164,  974,  975,  566,
  557,  164,  887,   94,   96,  565,  395,  966,  107,  967,
 1059,  111,  961,  962,  963,  964,  965,  325, 1035,   47,
 1076,   26,  326,  976,  977,  143,   37,  412,  299,  639,
  458,  449,  989,  141,  142,  413,   37,  144,  994,  995,
  993, -106,  984,  986,  988,  990,  991,  992,  170,  417,
  371,  418,    9,  419,  914,  315,  916,  917,  238,  239,
  420,  105,  375,  106,  376,  377,  162,  235,  236,  316,
   52,   59,  303,  371,  372,   14,  373,  371,  372,   14,
  373,  298,  608,  374,  110,  375,  102,  374,  101,  375,
  102,  817,  116,  438, -106,  258,  818,   58,  134,  135,
   49,  241,   29,  421,  422,  423,  810,  273,  941, -480,
  152,  153,   77,   98,  305,  306,  378,  424,  380,  425,
  382,  426,  274,  275,   33,   34,   35,   67,  427,-32766,
    2,  242,  108,  428,  943,    1,  583,  592,  115,  -76,
   46, -102,   25,  -77,  240,   57,   48,  512,   28,  910,
  256,  911,  912,  913,  914,  915,  916,  917,  918,  919,
  920,  921,   37,  922,  154,  155,  162,  924,  925,  934,
  936,  935, 1020,  481,  482,   36,  114,  320,  483,  100,
-32766,-32766,  328,   78, -395,-32766,   39,  405,   43,-32766,
-32766,-32766,  164,  129,  148,-32766, 1076,  130,   27,  128,
  191,  259,   37,  421,  422,  423,  123,  444,  941,  876,
  120,  369,   77,  879,  886,  299,  257,  932,-32766,  933,
  107,  926,  927,  928,  929,  930,  931,-32766,  445,   97,
  593,  596,  791,  428,  943,  312,  897,  313,  485,  641,
  589,  640,-32766,  309,  240,   57,   66,  314,  237,    0,
  446,  311,  590,    0,-32766,-32766,  410,    5,-32766,-32766,
  910,  411,  911,  912,  913,  914,  915,  916,  917,  918,
  919,  920,  921,  298,  922,  513,  509,  162,  924,  925,
  934,  936,  935,  450,  447,  437, 1046,  492,  511,  515,
  452,-32766,-32766,   65,  292, -397,  706,  785,  814,  691,
  671,  816,  878,    4,   38,    3,   37,   36,  258,    0,
  881,  790,    0,  499,  421,  422,  423,  517,  444,  941,
  877, 1063, 1062,   77,  874, 1044,  704,  669,  932,  996,
  933,  783,  926,  927,  928,  929,  930,  931,-32766,  445,
  491,   72,   99,  296,  428,  943,  629,  899,  627,  638,
 1004, 1003,   20,-32766,  628,  240,   57,  626,  642,  632,
  630,  446,   73,   71,   70,-32766,-32766,   69,   68,-32766,
-32766,  910,  605,  911,  912,  913,  914,  915,  916,  917,
  918,  919,  920,  921,  556,  922,  631,  633,  162,  924,
  925,  934,  936,  935,  109,  113,   60,   51,   41,  224,
  133, -401,-32766,-32766, -398, -396,  608,  610, -393, -385,
   42,   53,   54,  724,  609,  611,  540,  245,  243,   55,
  124,  194, -394,  240,    0,  421,  422,  423,  208,  444,
  941,  216,  222,  207,   77,  206,  205,   95,   92,  932,
   76,  933,  210,  926,  927,  928,  929,  930,  931,-32766,
  445,   75,   74,  480,  451,  428,  943,  407,  667,  406,
  244,  209,  223,  221,-32766,  220,  240,   57,  219,  218,
  217,  215,  446,  214,  213,  212,-32766,-32766,  211,   50,
-32766,-32766,  910,   15,  911,  912,  913,  914,  915,  916,
  917,  918,  919,  920,  921,   16,  922,   18,   19,  162,
  924,  925,  934,  936,  935,  329,  709,  809,  519,  649,
 1067, 1065,  707,-32766,-32766,  808,  716,  623,  672, 1048,
  786, 1002,  875,  811,  997,  516,  502,  364,  363,  362,
  361,  360,  353,  351,  350,  348,  421,  422,  423,  347,
  444,  941,  346,  344,  341,   77,  338,  337,  336,  335,
  932,  334,  933,   22,  926,  927,  928,  929,  930,  931,
-32766,  445,   21,  131,  446,    0,  428,  943,  132,    0,
    0,    0,    0,    0,    0,-32766,    0,  240,   57,    0,
    0,    0,    0,  446,    0,    0,    0,-32766,-32766,    0,
    0,-32766,-32766,  910,    0,  911,  912,  913,  914,  915,
  916,  917,  918,  919,  920,  921,    0,  922,    0,    0,
  162,  924,  925,  934,  936,  935,    0,    0,    0,    0,
    0,    0,    0,    0,-32766,-32766,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  421,  422,  423,
    0,  444,  941,    0,    0,    0,   77,    0,    0,    0,
    0,  932,    0,  933,    0,  926,  927,  928,  929,  930,
  931,-32766,  445,    0,    0,    0,    0,  428,  943,    0,
    0,    0,    0,    0,    0,    0,-32766,    0,    0,   57,
    0,    0,    0,    0,-32766,    0,    0,    0,-32766,-32766,
    0,    0,-32766,-32766,  170,  370,  371,  372,   14,  373,
    0,  302,    0,    0,  252,  253,  374,  101,  375,  102,
  376,  377,    0,  233,  234,  537,   62,  103,  303,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  260,    0, -480,    0,    0,    0,    0,
  305,  306,  378,  379,  380,  381,  382,    0,  261,  262,
   30,   31,   32,    0,  384,    0,    0,    0,    0,    0,
    0,    1,  583,    0,    0,    0,    0, -102,    0,    0,
  240,    0,    0,    0,    0,    0,  256,  170,  370,  371,
  372,   14,  373,    0,  302,    0,    0,  252,  253,  374,
  101,  375,  102,  376,  377,    0,  233,  234,  537,   62,
  103,  303,    0,    0,    0,    0,    0,   -1,  170,  370,
  371,  372,   14,  373,    0,  302,    0,    0,  252,  253,
  374,  101,  375,  102,  376,  377,    0,  233,  234,  537,
   62,  103,  303,    0,    0,    0,  260,    0,    0,    0,
    0,    0,    0,  305,  306,  378,  379,  380,  381,  382,
    0,  261,  262,   30,   31,   32,    0,  384,    0,    0,
    0,    0,    0,    0,    1,    0,    0,  260,    0,    0,
 -102,    0,    0, -371,  305,  306,  378,  379,  380,  381,
  382,    0,  261,  262,   30,   31,   32,    0,  384,    0,
    0,    0,    0,    0,    0,    1,    0,    0,    0,    0,
    0, -102,  170,  370,  371,  372,   14,  373,    0,  302,
    0,    0,  252,  253,  374,  101,  375,  102,  376,  377,
    0,  233,  234,  537,   62,  103,  303,    0,    0,    0,
    0,    0,  170,  370,  371,  372,   14,  373,    0,  302,
    0,    0,  252,  253,  374,  101,  375,  102,  376,  377,
    0,  233,  234,  537,   62,  103,  303,    0,    0,    0,
    0,  260,    0,    0,    0,    0,    0,    0,  305,  306,
  378,  379,  380,  381,  382,    0,  261,  262,   30,   31,
   32,    0,  384,    0,    0,    0,    0,    0,    0,    1,
  792,  260,    0,    0,    0, -102,    0,    0,  305,  306,
  378,  379,  380,  381,  382,    0,  261,  262,   30,   31,
   32,    0,  384,    0,    0,    0,    0,    0,    0,    1,
  588,    0,    0,    0,    0, -102,  170,  370,  371,  372,
   14,  373,    0,  302,    0,    0,  252,  253,  374,  101,
  375,  102,  376,  377,    0,  233,  234,  537,   62,  103,
  303,    0,    0,    0,    0,  170,  370,  371,  372,   14,
  373,    0,  302,    0,    0,  252,  253,  374,  101,  375,
  102,  376,  377,    0,  233,  234,  537,   62,  103,  303,
    0,    0,    0,    0,    0,  260,    0,  121,    0,    0,
    0,    0,  305,  306,  378,  379,  380,  381,  382,    0,
  261,  262,   30,   31,   32,    0,  384,    0,    0,    0,
    0,    0,    0,    1,  260,    0,    0,    0,    0, -102,
    0,  305,  306,  378,  379,  380,  381,  382,    0,  261,
  262,   30,   31,   32,    0,  384,    0,    0,    0,    0,
    0,    0,    1,  586,    0,    0,    0,    0, -102,  170,
  370,  371,  372,   14,  373,    0,  302,    0,    0,  252,
  253,  374,  101,  375,  102,  376,  377,    0,  233,  234,
  537,   62,  103,  303,    0,    0,    0,    0,    0,  170,
  370,  371,  372,   14,  373,    0,  302,    0,    0,  252,
  253,  374,  101,  375,  102,  376,  377,    0,  233,  234,
  537,   62,  103,  303,    0,    0,    0,    0,  260,    0,
    0,    0,    0,    0,    0,  305,  306,  378,  379,  380,
  381,  382,    0,  261,  262,   30,   31,   32,    0,  384,
    0,    0,    0,    0,    0,    0,    1,  585,  260,    0,
    0,    0, -102,    0,    0,  305,  306,  378,  379,  380,
  381,  382,    0,  261,  262,   30,   31,   32,    0,  384,
    0,    0,    0,    0,    0,    0,    1,  584,    0,    0,
    0,    0, -102,  170,  370,  371,  372,   14,  373,    0,
  302,    0,    0,  252,  253,  374,  101,  375,  102,  376,
  377,    0,  233,  234,  537,   62,  103,  303,    0,    0,
    0,    0,    0,  170,  370,  371,  372,   14,  373,    0,
  302,    0,    0,  252,  253,  374,  101,  375,  102,  376,
  377,    0,  233,  234,  537,   62,  103,  303,    0,    0,
    0,    0,  260,    0,    0,    0,    0,    0,    0,  305,
  306,  378,  379,  380,  381,  382,    0,  261,  262,   30,
   31,   32,    0,  384,    0,    0,    0,    0,    0,    0,
    1,  583,  260,    0,  125,    0, -102,    0,    0,  305,
  306,  378,  379,  380,  381,  382,    0,  261,  262,   30,
   31,   32,    0,  384,    0,    0,    0,    0,    0,    0,
    1,    0,    0,    0,    0,    0, -102,  170,  370,  371,
  372,   14,  373,    0,  302,    0,    0,  252,  253,  374,
  101,  375,  102,  376,  377,    0,  233,  234,  537,   62,
  103,  303,    0,    0,    0,    0,    0,  170,  370,  371,
  372,   14,  373,    0,  302,    0,    0,  252,  253,  374,
  101,  375,  102,  376,  377,    0,  233,  234,  537,   62,
  103,  303,    0,    0,    0,    0,  260,    0,    0,    0,
    0,    0,-32766,  305,  306,  378,  379,  380,  381,  382,
    0,  261,  262,   30,   31,   32,    0,  384,    0,    0,
    0,-32766,-32766,    0,    1,  587,  260,    0,    0,    0,
 -102,    0,    0,  305,  306,  378,  379,  380,  381,  382,
    0,  261,  262,   30,   31,   32,  104,  384,    0,    0,
    0,  161,    0,    0,    1,    0,    0,    0,    0,    0,
 -102,    0,-32766,-32766,-32766,  156,  157,    0,-32766,    0,
    0,    0,    0,    0,    0,    0,  538,    0,    0,    0,
    0,    0,    0,-32766,    0,    0,    0,    0,  798,  799,
  800,-32766,  398,    0,    0,-32766,-32766,    0,  304,-32766,
-32766,    0,    0,    0,    0,    0, 1020,  399,  400,  163,
    0,    0,  383,  817,    0,  801,  797,  795,  818,    0,
   39,    0,   43,    0,  796,    0,    0,  158,    0,    0,
   56,    0,   23,    0,    0,  255,    0,  307,    0,  159,
  149,  539,    0,  150,  151,   24,  713,  714,  715,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  817,    0,    0,  712,  710,  818,    0,    0,    0,
    0,    0,  711,    0,    0,    0,    0,    0,   61
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1849

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   39,   40,   19,   20,   21,
   22,   23,   24,   14,   26,   27,   28,   29,   30,   65,
   82,   64,   65,   35,   36,   37,   88,   39,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,
   53,  108,  109,  110,   56,   57,   58,   90,   60,   61,
   96,   28,   29,   30,   89,   98,  102,  100,   70,    0,
   72,   96,   74,   75,   76,   77,   78,   79,   88,   81,
  104,   20,   24,    2,   86,    4,    5,    6,   90,    8,
   93,   31,  102,   95,   13,   14,   98,   88,   17,  101,
  102,  103,    3,  105,  106,  107,  108,  109,  110,    2,
    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   85,   16,   33,   34,   19,   20,   21,   22,
   23,   24,   95,   26,   27,   28,   29,   30,  105,  106,
   81,   65,   35,   36,   37,   86,   88,   88,   88,   90,
   88,   70,   90,    3,    2,   94,   75,   97,   77,   78,
   98,  101,  100,   56,   57,   58,   16,   60,   61,   88,
   89,   16,   96,   65,    7,   94,    2,   70,  102,   72,
   74,   90,   75,   76,   77,   78,   79,   81,   81,   98,
   82,  100,   86,   86,   87,   95,   88,   90,   81,   94,
   82,   96,   95,   35,   36,   98,   88,  107,  101,  102,
  103,   94,  105,  106,  107,  108,  109,  110,    1,    2,
    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
   23,   24,   25,    3,    4,    5,    6,    3,    4,    5,
    6,   81,   97,   13,   14,   15,   16,   13,   14,   15,
   16,   81,   90,    4,   94,   88,   86,   93,   26,   27,
   98,   59,  100,   56,   57,   58,   99,   60,   61,   62,
   54,   55,   65,    7,   67,   68,   69,   70,   71,   72,
   73,   74,   75,   76,   77,   78,   79,   93,   81,   14,
   88,   97,   90,   86,   87,   88,   89,   85,   90,    7,
   98,   94,  100,    7,   97,   98,   98,   95,  100,    2,
  103,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   88,   16,   64,   65,   19,   20,   21,   22,
   23,   24,   74,   75,   76,   88,  102,    9,   80,   65,
   33,   34,   10,   65,   97,   14,   88,   20,   90,   74,
   75,   76,   16,   31,   37,   80,   82,   32,  100,   38,
  102,  103,   88,   56,   57,   58,   62,   60,   61,   91,
   62,   62,   65,   63,   96,   81,   65,   70,  103,   72,
  102,   74,   75,   76,   77,   78,   79,   80,   81,   65,
   85,   85,   89,   86,   87,   81,   89,   81,   96,   81,
   81,   81,   95,   88,   97,   98,   93,   81,   96,   -1,
  103,   81,   89,   -1,  107,  108,   81,   88,  111,  112,
    2,   81,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   81,   16,   81,   81,   19,   20,   21,
   22,   23,   24,   81,   81,   81,   87,   82,   82,   82,
   82,   33,   34,   93,   93,   97,   87,   87,   87,   87,
   87,   87,  106,   88,   88,   88,   88,   88,   88,   -1,
   89,   89,   -1,   90,   56,   57,   58,   90,   60,   61,
   91,   91,   91,   65,   91,   91,   91,   91,   70,   91,
   72,   91,   74,   75,   76,   77,   78,   79,   80,   81,
   93,   93,   93,   93,   86,   87,   94,   89,   94,   94,
   94,   94,   99,   95,   94,   97,   98,   94,   94,   94,
   94,  103,   94,   94,   94,  107,  108,   94,   94,  111,
  112,    2,   94,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   94,   16,   94,   94,   19,   20,
   21,   22,   23,   24,   96,   96,   96,   96,   96,   96,
  103,   97,   33,   34,   97,   97,   97,   97,   97,   97,
   97,   97,   97,   97,   97,   97,   97,   97,   97,   97,
   97,   97,   97,   97,   -1,   56,   57,   58,   98,   60,
   61,   98,   98,   98,   65,   98,   98,   98,   98,   70,
   98,   72,   98,   74,   75,   76,   77,   78,   79,   80,
   81,   98,   98,   98,   98,   86,   87,   98,   89,   98,
   98,   98,   98,   98,   95,   98,   97,   98,   98,   98,
   98,   98,  103,   98,   98,   98,  107,  108,   98,   98,
  111,  112,    2,   99,    4,    5,    6,    7,    8,    9,
   10,   11,   12,   13,   14,   99,   16,   99,   99,   19,
   20,   21,   22,   23,   24,   99,   99,   99,   99,   99,
   99,   99,   99,   33,   34,   99,   99,   99,   99,   99,
   99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
   99,   99,   99,   99,   99,   99,   56,   57,   58,   99,
   60,   61,   99,   99,   99,   65,   99,   99,   99,   99,
   70,   99,   72,   99,   74,   75,   76,   77,   78,   79,
   80,   81,   99,  101,  103,   -1,   86,   87,  102,   -1,
   -1,   -1,   -1,   -1,   -1,   95,   -1,   97,   98,   -1,
   -1,   -1,   -1,  103,   -1,   -1,   -1,  107,  108,   -1,
   -1,  111,  112,    2,   -1,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   -1,   16,   -1,   -1,
   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   33,   34,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   56,   57,   58,
   -1,   60,   61,   -1,   -1,   -1,   65,   -1,   -1,   -1,
   -1,   70,   -1,   72,   -1,   74,   75,   76,   77,   78,
   79,   80,   81,   -1,   -1,   -1,   -1,   86,   87,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   95,   -1,   -1,   98,
   -1,   -1,   -1,   -1,  103,   -1,   -1,   -1,  107,  108,
   -1,   -1,  111,  112,    1,    2,    3,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   17,   18,   -1,   20,   21,   22,   23,   24,   25,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   60,   -1,   62,   -1,   -1,   -1,   -1,
   67,   68,   69,   70,   71,   72,   73,   -1,   75,   76,
   77,   78,   79,   -1,   81,   -1,   -1,   -1,   -1,   -1,
   -1,   88,   89,   -1,   -1,   -1,   -1,   94,   -1,   -1,
   97,   -1,   -1,   -1,   -1,   -1,  103,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   -1,   -1,   -1,    0,    1,    2,
    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   17,   18,   -1,   20,   21,   22,
   23,   24,   25,   -1,   -1,   -1,   60,   -1,   -1,   -1,
   -1,   -1,   -1,   67,   68,   69,   70,   71,   72,   73,
   -1,   75,   76,   77,   78,   79,   -1,   81,   -1,   -1,
   -1,   -1,   -1,   -1,   88,   -1,   -1,   60,   -1,   -1,
   94,   -1,   -1,   97,   67,   68,   69,   70,   71,   72,
   73,   -1,   75,   76,   77,   78,   79,   -1,   81,   -1,
   -1,   -1,   -1,   -1,   -1,   88,   -1,   -1,   -1,   -1,
   -1,   94,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,   -1,
   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,   -1,
   -1,   60,   -1,   -1,   -1,   -1,   -1,   -1,   67,   68,
   69,   70,   71,   72,   73,   -1,   75,   76,   77,   78,
   79,   -1,   81,   -1,   -1,   -1,   -1,   -1,   -1,   88,
   89,   60,   -1,   -1,   -1,   94,   -1,   -1,   67,   68,
   69,   70,   71,   72,   73,   -1,   75,   76,   77,   78,
   79,   -1,   81,   -1,   -1,   -1,   -1,   -1,   -1,   88,
   89,   -1,   -1,   -1,   -1,   94,    1,    2,    3,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   16,   17,   18,   -1,   20,   21,   22,   23,   24,
   25,   -1,   -1,   -1,   -1,    1,    2,    3,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   17,   18,   -1,   20,   21,   22,   23,   24,   25,
   -1,   -1,   -1,   -1,   -1,   60,   -1,   62,   -1,   -1,
   -1,   -1,   67,   68,   69,   70,   71,   72,   73,   -1,
   75,   76,   77,   78,   79,   -1,   81,   -1,   -1,   -1,
   -1,   -1,   -1,   88,   60,   -1,   -1,   -1,   -1,   94,
   -1,   67,   68,   69,   70,   71,   72,   73,   -1,   75,
   76,   77,   78,   79,   -1,   81,   -1,   -1,   -1,   -1,
   -1,   -1,   88,   89,   -1,   -1,   -1,   -1,   94,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   -1,   20,   21,
   22,   23,   24,   25,   -1,   -1,   -1,   -1,   -1,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   -1,   20,   21,
   22,   23,   24,   25,   -1,   -1,   -1,   -1,   60,   -1,
   -1,   -1,   -1,   -1,   -1,   67,   68,   69,   70,   71,
   72,   73,   -1,   75,   76,   77,   78,   79,   -1,   81,
   -1,   -1,   -1,   -1,   -1,   -1,   88,   89,   60,   -1,
   -1,   -1,   94,   -1,   -1,   67,   68,   69,   70,   71,
   72,   73,   -1,   75,   76,   77,   78,   79,   -1,   81,
   -1,   -1,   -1,   -1,   -1,   -1,   88,   89,   -1,   -1,
   -1,   -1,   94,    1,    2,    3,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   16,   17,
   18,   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,
   -1,   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   16,   17,
   18,   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,
   -1,   -1,   60,   -1,   -1,   -1,   -1,   -1,   -1,   67,
   68,   69,   70,   71,   72,   73,   -1,   75,   76,   77,
   78,   79,   -1,   81,   -1,   -1,   -1,   -1,   -1,   -1,
   88,   89,   60,   -1,   62,   -1,   94,   -1,   -1,   67,
   68,   69,   70,   71,   72,   73,   -1,   75,   76,   77,
   78,   79,   -1,   81,   -1,   -1,   -1,   -1,   -1,   -1,
   88,   -1,   -1,   -1,   -1,   -1,   94,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   -1,   -1,   -1,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   -1,   -1,   60,   -1,   -1,   -1,
   -1,   -1,   14,   67,   68,   69,   70,   71,   72,   73,
   -1,   75,   76,   77,   78,   79,   -1,   81,   -1,   -1,
   -1,   33,   34,   -1,   88,   89,   60,   -1,   -1,   -1,
   94,   -1,   -1,   67,   68,   69,   70,   71,   72,   73,
   -1,   75,   76,   77,   78,   79,   14,   81,   -1,   -1,
   -1,   19,   -1,   -1,   88,   -1,   -1,   -1,   -1,   -1,
   94,   -1,   74,   75,   76,   33,   34,   -1,   80,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   44,   -1,   -1,   -1,
   -1,   -1,   -1,   95,   -1,   -1,   -1,   -1,   56,   57,
   58,  103,   60,   -1,   -1,  107,  108,   -1,   66,  111,
  112,   -1,   -1,   -1,   -1,   -1,   74,   75,   76,   19,
   -1,   -1,   80,   81,   -1,   83,   84,   85,   86,   -1,
   88,   -1,   90,   -1,   92,   -1,   -1,   95,   -1,   -1,
   98,   -1,  100,   -1,   -1,  103,   -1,  105,   -1,  107,
  108,  109,   -1,  111,  112,  113,   56,   57,   58,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   81,   -1,   -1,   84,   85,   86,   -1,   -1,   -1,
   -1,   -1,   92,   -1,   -1,   -1,   -1,   -1,   98
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1626,  217,  873, 1472, 1348, 1254, 1225, 1502, 1007,  976,
 1378, 1596, 1131, 1101, 1626, 1626, 1626, 1626, 1626, 1626,
 1626, 1626, 1626,  381,  384,  380,  383,  382,  379,  369,
  107,  107,  107,  107,  107,  107,  317,  539,  428,  650,
  761,  761,  244,  288,  -36,   76,  108,  108,  108,  108,
   61,  284,  257,  -10,  -10,  -10,  -52,  118,   58,  495,
  334,  376,  389,  389,  389,  388,  388,  388,  389,  389,
  389,  389,  388,  389, 1692, 1692, 1692,  388,  388,  388,
  388,  388,  388,  388,  388,  388,  388,  388,  388,  388,
  388,  388, 1692,  388,  388, 1692, 1692,  388, 1692,  388,
  388, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,  386,
 1692, 1692, 1692, 1692, 1692, 1692, 1692,    9,    9,    9,
    9,    9,  341,  341,  341,  341,  285,  285,  285,  285,
  285,  285,  285,  285,  285,  285,  285,  285,  285,  285,
  285,  285,  285,  285,  285,  285,  285,  285,  285,  285,
  285,  285,  285,  285,  285,  285, 1648, 1648, 1648, 1648,
 1648, 1648, 1648, 1648,  268,  268,  268,  155,  174,  346,
   81,  480,  578,  410,  479,  406,  577,  405,  404,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3, 1750, 1750, 1750,  240,  212,  177,  -33,   62,   62,
   62,   62,  390,  390,  390,  321,  321,  321,  321,  321,
  321,  321,  321,  321,  321,  321,  321,  321,  321,  321,
  321,  321,  321,  321,  321,   60,  218,  218,  218,   33,
   33,   33,   59,   59,   59,   59,   59,   59,  170,  117,
  106,  106,  106,  106,  106,  106,  172,  -57,  -24,  -57,
  -57,  302,  362,  304,  150,  500,  503,  180,  631,  504,
  337,  345,  350,  242,  168,  100,  226,  270,  374,  204,
  427,  426,  105,  337,  345,  350,  -25,  554,  566,  444,
  576,  242,  168,  168,  168,  168,  168,  100,  100,  226,
  443,  580,  222,  579,  568,  569,   37,  152,  152,  152,
  152,  152,  387,  330,  529,  329,  329,  366,  338,  373,
  529,  514,  514,  387,  387,  387,  481,  472,  387,  529,
  525,  342,  312,  489,  489,  393,  393,  387,  387,  387,
  486,  532,  387,  387,  496,  496,  496,  496,  490,  387,
  486,  496,  532,  387,  496,  387,  496,  496,  496,  387,
  496,  490,  387,  496,  387,  387,  387,  387,  387,  387,
  496,  496,  496,  496,  490,  387,  387,  387,  387,  387,
  524,  488,  523,  551,  512,  487,  325,  436,  435,  340,
  324,  326,  336,  505,  494,   69,  434,  331,  332,  335,
  632,  636,  467,  327,  259,  510,  433,  430,  531,  508,
  507,  533,  370,  323,  468,  372,  526,  378,  385,  339,
  550,  547,  408,  595,  546,  545,  543,  524,  523,  551,
  512,  478,  368,  477,  340,  326,  482,  483,  474,  484,
  314,  399,  470,  594,  403,  593,  463,  542,  509,  167,
  306,  302,  424,  422,  531,  485,  541,  371,  425,  328,
  417,  375,  592,  491,  622,  473,  620,  619,  597,  391,
  470,  618,  320,  332,  335,  632,  636,  467,  327,  327,
  327,  591,  471,  617,  331,  331,  493,  276,  370,  440,
  365,  540,  537,  535,  534,  364,  333,  419,  419,  419,
  462,  377,  596,  590,  615,  614,  613,  610,  606,  401,
  397,  397,  492,  605,  392,  589,  604,   99,  439,  588,
  603,  587,  315,  420,  418,  460,  586,  400,  318,  448,
  438,  423,  602,  601,  600,  599,  598,  583,  582,  633,
  316,  419,  624,  319,  581,  313,  313,    0,    0,    0,
    0, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692, 1692,   -2,   -2,   -2,   -2,   -2,   -2,
   -2,    0,    0,    0,    0,    0,    0, 1692, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692, 1692, 1692,    0,    0,    0, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692,    0, 1692, 1692,    0,    0, 1692,    0,
 1692, 1692,    0,    0,    0,    0,    0,    0,    0,    0,
 1692,    0,    0,    0,    0,    0,    0,    0, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692, 1692,
 1692, 1692, 1692, 1692, 1692, 1750, 1750, 1750,   -3,   -3,
   -3,    0,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   91,   91,   91,   91,
   91,   91,   91,   91,   91,   91,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,  152,   91,   91,   91,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  152,
  152,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  204,  152,  152,    0,  496,  496,    0,  496,
  496,  531,  508,  507,    0,    0,    0,    0,    0,  533,
    0,  322,  322,    0,  531,  508,  507,    0,  469,  469,
  469,  469,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  322,  469,    0,  469,  469,  469
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 296

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  388,  389,  390,  480,  480,  480,  480,
32767,  342,32767,32767,32767,32767,  527,  527,  527,  527,
32767,32767,  104,32767,32767,32767,32767,32767,32767,   94,
  350,32767,  104,  104,  104,32767,32767,32767,  104,  104,
  104,  104,32767,  104,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   94,32767,  380,  381,32767,32767,32767,
32767,32767,   96,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  226,  228,32767,32767,32767,32767,
32767,32767,  382,32767,32767,32767,32767,32767,  106,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  355,
   93,  347,  353,  348,  533,  357,  366,  351,   95,  354,
  367,32767,  151,  153,32767,  238,32767,  144,  236,  237,
  234,  233,  125,  534,  368,  508,  508,  508,  508,  508,
  508,  508,  508,  508,  508,  508,  508,  508,  508,  508,
  508,  508,  508,  508,32767,32767,  145,  152,  154,  202,
  203,  204,32767,32767,32767,  383,  384,32767,  377,  378,
32767,32767,32767,32767,32767,32767,  525,  214,  185,  216,
  215,  466,  106,  106,  177,  480,  480,32767,  480,  480,
32767,32767,32767,  200,  205,  211,  221,  223,32767,  466,
32767,32767,32767,  399,  386,  387,  230,32767,32767,32767,
32767,  201,  207,  209,  210,  206,  208,  212,  213,  222,
32767,32767,32767,32767,32767,32767,32767,  106,  106,  106,
  106,  106,32767,32767,32767,32767,32767,  339,   79,32767,
32767,  506,  506,32767,32767,  374,  536,  341,32767,32767,
   81,   83,  341,  500,  500,  520,  520,32767,32767,32767,
  182,  523,32767,32767,  480,  480,  480,  480,  482,32767,
  182,  480,  523,32767,  480,32767,  480,  480,  480,32767,
  480,  482,32767,  480,32767,32767,32767,32767,32767,32767,
  480,  480,  480,  480,  482,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  276,32767,32767,  187,  190,  192,
  194,  196,  198,  217,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  105,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  369,  370,  372,
  379,  257,  258,  259,  391,  392,  479,  276,  277,32767,
32767,32767,  343,32767,32767,32767,32767,32767,32767,32767,
  263,  261,32767,32767,  399,  276,32767,   50,32767,32767,
32767,32767,32767,  512,32767,  509,32767,32767,32767,32767,
  344,32767,32767,  191,  193,  195,  197,  199,  218,  219,
  220,32767,  528,32767,  188,  189,32767,32767,   77,32767,
32767,32767,32767,32767,32767,  342,32767,  470,  471,  468,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  519,  517,  270,32767,32767,32767,32767,   61,32767,32767,
32767,32767,32767,   53,  467,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  469,32767,32767,32767,  488,32767,  536,  460,  460,
  536
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  186,  181,  181,  181,  184,  184,  184,  184,  182,  184,
  179,  186,  186,  186,  172,  172,  441,  180,  187,  176,
  179,  179,  179,  505,  527,  534,  179,  179,  179,  179,
  901,  179,  182,  182,  182,  722,  722,  722, 1030, 1030,
  721,  721,  721, 1029,  535,  476,  504,  727,  536,  999,
  182,  488,  489,  182,  182,  462,  182,  531,  998,  167,
  171,  180,  169,  167,  171,  183,  173,  185,  174,  175,
  188,  189,  190,  177,  178,  268,  268,  268,  268,  268,
  268,  268,  268,  268,  268,  268,  268,  268,  268,  268,
  268,  268,  268,  268,  268,  268,  268,  268,  301,  479,
  468,  469,  470,  508,  520,  521,  529,  601,  532,  460,
  689,  689,  689,  788,  719,  680,  788,  788,  788,  788,
 1072,  668,  703,  226,  227,  228,  276,  668,  668,  668,
  708,  708,  708,  282,  283,  284,  285,  286,  440,  474,
  475,  789,  673,  722,  789,  789,  789,  789,  673,  673,
  673,  703,  703,  703,  904,  463,  902,  708,  708,  708,
  464,  906,  906,  906,  906,  906,  906,   11,   12,   13,
   13,  453,  453,  453,  453,  453,  453,  453,  453,  453,
  453,  453,  453,  453,  453,  453,  453,  453,  453,  453,
  453,  780,  331,  342,  528, 1024,  543,  465,  251,  269,
  269,  269,  269,  269,  544,  394,  546,  546,  546,  546,
  394,  507,  604,  603,  615,  616,  614,  613,  612,  281,
  308,  230,  231, 1057,  466,  815,  784,  670,  690,  705,
 1045, 1039, 1040,  308,  415,  416, 1031,  415,  416,  484,
  484,  484,  359,  287,  288,  621,  625,  606,  249,  250,
 1037, 1038,  687,  687,  687,  368,  290,  701,  271,  601,
  271, 1025,  467, 1026,  683,  682,  289, 1027, 1052,  477,
 1028,  679, 1017, 1018, 1032, 1033, 1034, 1019,  198,  199,
  200,  201,  340,  696,  697,  698,  699,  700,  688,  688,
  688, 1006,  677, 1055, 1055, 1055, 1055, 1055, 1055, 1055,
 1055, 1055, 1055, 1055, 1055, 1055, 1055, 1055, 1055, 1055,
 1055, 1055, 1055,  776,  772,  773,  765,  766,  768,  770,
  478,  402,  402,  402,  402,  402,  409,  324,  486, 1056,
 1056, 1056, 1056, 1056, 1056, 1056, 1056, 1056, 1056, 1056,
 1056, 1056, 1056, 1056, 1056, 1056, 1056, 1056, 1056, 1043,
  812,  812,  717,  333,  501,  665,  403,  403,  403,  403,
  403,  403,  665,  665,  665,  119,  318,  318,  644,  665,
  339,  319, 1054,  160,  665,  665,  665,  665,  665,  665,
  665,  665,  665,  665,  665,  665,  665,  665,  665,  651,
  665,  665,    0,    0,  665,    0,  665,  665,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  905,  890,
  654,  655,  656,  657,  658,  659,  660,  661,  662,  663,
  664,  652,  653,    0,  651, 1071,    0,    0,  893,  204,
 1014, 1073,    0,  203,  203,  203,  203,    0,  203,  397,
  204,  204,  204,  196,  196,  343,  345,  349,  518,    0,
    0,    0,  354,  397,    0,  355,    0,  356,  357,  358,
    0,    6,    0,    0,    7,    0,    0,    0,    0,    0,
    0,  365,  366,  367,  533,  456,  457,  461,  473,  493,
  494,  495,  496,  497,  498,  503,  506,  510,  522,  523,
  524,  525,  526,  277,  278,  280,    0,  436,  442,  443,
  448,  490,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  291,    0,    0,  293,  294,    0,  295
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 518

static char yygcheck[] = {
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   74,   37,   37,   37,
   37,   37,   37,   98,   98,   98,   37,   37,   37,   37,
   72,   37,   37,   37,   37,    7,    7,    7,    7,    7,
   41,   41,   41,   41,   41,   41,   41,   41,   41,   65,
   37,   81,   81,   37,   37,   66,   37,   81,   65,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   40,   40,
   53,   53,   53,   40,   40,   40,   40,   35,   40,   67,
   97,   97,   97,    7,  117,  117,    7,    7,    7,    7,
  100,   59,   59,  113,  113,  113,   56,   59,   59,   59,
   74,   74,   74,   50,   50,   50,   50,   50,   62,   42,
   42,   97,   97,    7,   97,   97,   97,   97,   97,   97,
   97,   59,   59,   59,   73,   43,   73,   74,   74,   74,
   44,   56,   56,   56,   56,   56,   56,    3,    3,    3,
    3,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,  103,  103,  103,  103,  103,    4,   45,   74,   74,
   74,   74,   74,   74,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,   48,
    7,   49,   49,   74,   46,   58,   58,   58,   58,   58,
   58,    7,    7,    7,   76,   76,    7,   76,   76,   82,
   82,   82,  102,   51,   51,    7,    7,    7,   52,   52,
    7,    7,   62,   62,   62,  102,   79,    7,   79,   35,
   79,    7,   47,    7,  112,  112,   54,    7,   95,   19,
    7,  118,    7,    7,    7,    7,    7,    7,   57,   57,
   57,   57,   32,    7,    7,    7,    7,    7,   63,   63,
   63,   80,  110,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   55,   55,   55,   55,   55,   55,   55,
   62,   62,   62,   62,   62,   62,    9,   91,  119,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   60,
   60,   60,   60,   89,  104,  108,   63,   63,   63,   63,
   63,   63,  108,  108,  108,  120,  101,  101,   31,  108,
  101,  122,  105,  106,  108,  108,  108,  108,  108,  108,
  108,  108,  108,  108,  108,  108,  108,  108,  108,   38,
  108,  108,   -1,   -1,  108,   -1,  108,  108,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   38,   -1,   38,   38,   -1,   -1,   38,   39,
   38,   38,   -1,   39,   39,   39,   39,   -1,   39,   31,
   39,   39,   39,   39,   39,  101,  101,  101,  101,   -1,
   -1,   -1,  101,   31,   -1,  101,   -1,  101,  101,  101,
   -1,  101,   -1,   -1,  101,   -1,   -1,   -1,   -1,   -1,
   -1,  101,  101,  101,  101,   93,   93,   93,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   93,   93,   93,   69,   69,   69,   -1,   31,   31,   31,
   31,   31,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   69,   -1,   -1,   69,   69,   -1,   69
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  163,  196,    0,    0,  -82,    0,   20,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   37,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  200,   57,    0,    0,   65,    0,  -42,  331,  387,
   35,  -77,   13,   27,   31,   67,   93,  130,   86,   87,
   -3,  102,  105,  -45,  118,  164,  125,  122,  201,  -75,
  189,    0,   88,  124,    0, -261,   11,   64,    0,  419,
    0,    0,  -11,  101,  -34,    0,  203,    0,    0,   24,
   54,  -15,   75,    0,    0,    0,    0,    0,    0,   29,
    0,   15,    0,  269,    0,   44,    0,  -54,  -24,    0,
   69,  111, -109,  -50,   28,   30, -167,    0,  297,    0,
   38,    0,   99,  -68,    0,    0,    0,   -4,   46,    6,
   25,    0, -168
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  385,    8,   10,  545,  548,  547,  549,  550,  408,
  551,  322,  563,  552,  579,  580,  581,  607,  582,  439,
  553,  321,  327,  619,  558,  559,  297,  560,  561,  272,
  562,  396,  648,  564,  554,  555,  386,  168, 1013,  202,
  300,  674,  387,  388,  389,  390,  391,  392,  263,  229,
  264,  265,  247,  393,  266,  267,  771,  195,  813,  782,
  781,  803,  804,  805,  806, 1000,  431,  432,   45,  279,
  404,  317,  900,  903,  802,  429,  414, 1036,  597,  270,
 1005,  487,  401,  598, 1015,  725, 1016,  599,  600,  332,
  246,  323, 1042,  454,  455, 1051,  787,  807,  471,  472,
 1070,  430,  352, 1022,  500,  514,   63,  248,  650,  254,
  676,  225,  681,  197,  684,  702,  675,  678,  720,  459,
  118,   44,  310
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
   39,   39,   39,  108,  108,  109,  109,  110,  110,  110,
  111,  111,  111,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  114,  114,  114,  114,  114,
  114,  113,  113,  113,  113,  113,  113,  115,  115,  115,
  115,  115,  115,  115,  115,  115,  115,  116,  116,  117,
  117,  118,  120,  120,   41,   41,   41,  107,  107,  107,
   42,   42,   43,   43,   44,   44,   45,   45,   46,   46,
   47,   47,   48,   48,   48,   49,   49,   49,   49,   49,
   49,   50,   50,   50,   51,   51,   51,   52,   52,   52,
   52,   53,   53,   54,   54,   54,   54,   54,   54,   54,
   55,   55,   55,   55,   55,   55,   55,   55,   56,   56,
   57,   57,   57,   57,   57,   57,   57,   96,   96,   97,
   97,   97,   59,   59,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   60,   60,   60,   74,   74,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   62,   62,   61,   61,  121,
   63,  119,  119,   66,   66,   68,   68,   67,   67,   67,
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
   77,   77,   77,   77,   77,   77,   77,   64,   64,   64,
  122,   65,   78,   78,   79,   79,   80,   80,   80,   80,
   80,   80,   81,   81,   83,   83,   84,   84,   84,   82,
  101,  101,  102,  102,   85,   85,   85,   85,   85,   85,
   85,   86,   86,   86,   76,   76,   87,   87,   88,   88,
   89,   89,   90,   90,   90,   90,   91,   91,   93,   93,
   94,   94,   95,   95,   95,   95,   95,  103,  103,  103,
  104,  104,  104,  105,  105,   92,   92,   98,   98,   99,
   99,   99,   99,  100,  100,  100,  106
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
    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
    1,    3,    1,    3,    3,    1,    3,    3,    3,    3,
    3,    1,    3,    3,    1,    3,    3,    1,    3,    3,
    3,    1,    3,    1,    3,    3,    2,    3,    2,    3,
    1,    2,    2,    2,    2,    2,    2,    2,    1,    3,
    1,    2,    4,    3,    3,    4,    2,    1,    1,    5,
    9,    8,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    6,    3,    3,
    3,    2,    2,    2,    2,    2,    1,    1,    1,    1,
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
    1,    1,    1,    1,    1,    2,    2,    3,    3,    2,
    0,    3,    3,    3,    1,    3,    1,    4,    3,    6,
    3,    3,    1,    3,    1,    1,    7,    7,    7,    1,
    0,    2,    0,    2,    6,    6,    6,    6,    7,    7,
    3,    7,    7,    7,    1,    1,    5,    5,    3,    3,
    0,    4,    1,    4,    3,    3,    0,    3,    0,    1,
    1,    3,    1,    4,    1,    1,    2,    2,    1,    2,
    0,    2,    3,    0,    3,    0,    3,    0,    1,    1,
    2,    3,    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 960
#define YYNLSTATES 541
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
#line 179 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 184 "src/kinx.y"
{ kx_ast_root = yyval.obj = (YYASP(2-2).obj == NULL ? YYASP(1-2).obj : kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 5:
#line 189 "src/kinx.y"
{ yyval.obj = (YYASP(2-2).obj == NULL ? YYASP(1-2).obj : kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 15:
#line 205 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strinfo.name, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 16:
#line 206 "src/kinx.y"
{ yyerrok; yyval.obj = NULL; } break;
        case 24:
#line 217 "src/kinx.y"
{                       yyerrok; yyval.obj = NULL; } break;
        case 25:
#line 218 "src/kinx.y"
{ yy_restart(LBBR);     yyerrok; yyval.obj = NULL; } break;
        case 26:
#line 219 "src/kinx.y"
{ yy_restart(IF);       yyerrok; yyval.obj = NULL; } break;
        case 27:
#line 220 "src/kinx.y"
{ yy_restart(DO);       yyerrok; yyval.obj = NULL; } break;
        case 28:
#line 221 "src/kinx.y"
{ yy_restart(WHILE);    yyerrok; yyval.obj = NULL; } break;
        case 29:
#line 222 "src/kinx.y"
{ yy_restart(FOR);      yyerrok; yyval.obj = NULL; } break;
        case 30:
#line 223 "src/kinx.y"
{ yy_restart(TRY);      yyerrok; yyval.obj = NULL; } break;
        case 31:
#line 224 "src/kinx.y"
{ yy_restart(SWITCH);   yyerrok; yyval.obj = NULL; } break;
        case 32:
#line 225 "src/kinx.y"
{ yy_restart(CASE);     yyerrok; yyval.obj = NULL; } break;
        case 33:
#line 226 "src/kinx.y"
{ yy_restart(ENUM);     yyerrok; yyval.obj = NULL; } break;
        case 34:
#line 227 "src/kinx.y"
{ yy_restart(CLASS);    yyerrok; yyval.obj = NULL; } break;
        case 35:
#line 228 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; yyval.obj = NULL; } break;
        case 36:
#line 229 "src/kinx.y"
{ yy_restart(PRIVATE);  yyerrok; yyval.obj = NULL; } break;
        case 37:
#line 230 "src/kinx.y"
{ yy_restart(PUBLIC);   yyerrok; yyval.obj = NULL; } break;
        case 42:
#line 241 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 43:
#line 242 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 44:
#line 246 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 45:
#line 247 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 248 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 47:
#line 249 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 253 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strinfo.name); } break;
        case 49:
#line 257 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 50:
#line 261 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strinfo.name); } break;
        case 51:
#line 262 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strinfo.name, YYASP(3-3).intval); } break;
        case 52:
#line 263 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strinfo.name, -YYASP(4-4).intval); } break;
        case 53:
#line 264 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strinfo.name)); } break;
        case 54:
#line 265 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strinfo.name, YYASP(5-5).intval)); } break;
        case 55:
#line 266 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strinfo.name, -YYASP(6-6).intval)); } break;
        case 60:
#line 277 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 61:
#line 281 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 62:
#line 282 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 63:
#line 286 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 64:
#line 290 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 65:
#line 294 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 299 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 300 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 301 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_WHEN, YYASP(2-3).obj); } break;
        case 70:
#line 302 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_ELSE, NULL); } break;
        case 71:
#line 307 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 72:
#line 314 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 73:
#line 321 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 74:
#line 328 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 75:
#line 330 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 78:
#line 339 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 79:
#line 343 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 80:
#line 344 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 81:
#line 348 "src/kinx.y"
{ yyval.obj = kx_gen_var_object("_e", KX_UNKNOWN_T); } break;
        case 82:
#line 349 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(2-3).strinfo.name, KX_UNKNOWN_T, YYASP(2-3).strinfo.line, YYASP(2-3).strinfo.pos1, YYASP(2-3).strinfo.pos2); } break;
        case 83:
#line 353 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 84:
#line 354 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 85:
#line 358 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 86:
#line 359 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strinfo.name)); } break;
        case 87:
#line 360 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 88:
#line 361 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strinfo.name)); } break;
        case 89:
#line 362 "src/kinx.y"
{ yyval.obj = kx_gen_break_object(KXST_FALLTHROUGH, NULL); } break;
        case 90:
#line 366 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 91:
#line 367 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 92:
#line 371 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 93:
#line 375 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 94:
#line 376 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 95:
#line 377 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 96:
#line 378 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 97:
#line 382 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 98:
#line 386 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 99:
#line 390 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_OBJ_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2), NULL); } break;
        case 100:
#line 391 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object_line_pos(YYASP(3-3).strinfo.name, KX_OBJ_T, YYASP(3-3).strinfo.line, YYASP(3-3).strinfo.pos1, YYASP(3-3).strinfo.pos2), NULL); } break;
        case 101:
#line 395 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 102:
#line 399 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 103:
#line 400 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 104:
#line 404 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 106:
#line 409 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 108:
#line 414 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 110:
#line 419 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 111:
#line 420 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 421 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 423 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 425 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 119:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 120:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 121:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 122:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 123:
#line 432 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 126:
#line 441 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 127:
#line 442 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 128:
#line 443 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 129:
#line 444 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 130:
#line 445 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 131:
#line 446 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 132:
#line 447 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 134:
#line 452 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 136:
#line 457 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 137:
#line 461 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-4).obj, YYASP(4-4).obj, NULL); } break;
        case 138:
#line 462 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 139:
#line 463 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 141:
#line 468 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 142:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 145:
#line 475 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 149:
#line 479 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 150:
#line 480 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 151:
#line 481 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 152:
#line 482 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 153:
#line 483 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 154:
#line 484 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 155:
#line 489 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 156:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 157:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 158:
#line 492 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 159:
#line 493 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 160:
#line 494 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 162:
#line 499 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 163:
#line 500 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 164:
#line 501 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 165:
#line 502 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 166:
#line 503 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 168:
#line 508 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 169:
#line 509 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 170:
#line 510 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 171:
#line 511 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 172:
#line 512 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 173:
#line 513 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 174:
#line 514 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 175:
#line 515 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 176:
#line 516 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 177:
#line 520 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 178:
#line 521 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 181:
#line 530 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 186:
#line 541 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 188:
#line 546 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALLP, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 189:
#line 547 "src/kinx.y"
{ yyval.obj = kx_gen_expr_right_object(KXOP_CALLP, KXOP_CALLP, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 191:
#line 552 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 193:
#line 557 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 562 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 197:
#line 567 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 199:
#line 572 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 203:
#line 582 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 583 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 206:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 207:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 208:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 209:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 210:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 212:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 213:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 215:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 216:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 218:
#line 609 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 219:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 220:
#line 611 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 222:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 224:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 225:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 226:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 227:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 228:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 229:
#line 626 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 231:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 232:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 233:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 234:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 235:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 236:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 237:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 239:
#line 642 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 241:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 242:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 243:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 244:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 245:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 246:
#line 652 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 247:
#line 656 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 249:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-5).arraytype, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(4-5).obj, NULL, NULL), NULL); } break;
        case 250:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-9).arraytype, NULL, YYASP(4-9).obj, kx_gen_stmt_object(KXST_RET, YYASP(8-9).obj, NULL, NULL), NULL); } break;
        case 251:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-8).arraytype, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 252:
#line 667 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 253:
#line 668 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 254:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 255:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 256:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 257:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 258:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 259:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 260:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 267:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 268:
#line 686 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 269:
#line 687 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 270:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 271:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 272:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 273:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 274:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 275:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 276:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_UNKNOWN_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2); } break;
        case 277:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(kx_gen_typestr_object(YYASP(1-1).intval), KX_UNKNOWN_T); } break;
        case 278:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object_pos(YYASP(1-1).strinfo); } break;
        case 279:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 280:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 281:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 282:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 283:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 284:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 285:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 286:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 287:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 288:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 289:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 290:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 291:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 292:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 293:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 294:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 295:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 296:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 297:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 298:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 299:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 300:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 301:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 302:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 303:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 304:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 305:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 306:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 307:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 308:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 309:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 310:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 311:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 312:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 313:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 314:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|>"); } break;
        case 315:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("**"); } break;
        case 316:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 317:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 318:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 319:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 320:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 321:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 322:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 323:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 324:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 325:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 326:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 327:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 328:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 329:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 330:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 331:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 332:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 333:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 334:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 335:
#line 762 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 336:
#line 763 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 337:
#line 767 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 338:
#line 768 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 339:
#line 772 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 340:
#line 776 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 341:
#line 780 "src/kinx.y"
{} break;
        case 343:
#line 785 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 344:
#line 786 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 345:
#line 790 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 346:
#line 791 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 348:
#line 796 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 349:
#line 797 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 350:
#line 798 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 351:
#line 799 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 352:
#line 800 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 354:
#line 805 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 356:
#line 810 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 357:
#line 811 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 358:
#line 812 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 360:
#line 817 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 361:
#line 821 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 362:
#line 822 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 363:
#line 823 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 364:
#line 824 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 365:
#line 825 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 367:
#line 830 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 369:
#line 835 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 370:
#line 836 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 371:
#line 837 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 372:
#line 838 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 373:
#line 839 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 374:
#line 840 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 375:
#line 841 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 376:
#line 842 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 377:
#line 843 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 378:
#line 844 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 379:
#line 845 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 380:
#line 846 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 381:
#line 847 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 382:
#line 848 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 383:
#line 849 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 384:
#line 850 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 385:
#line 851 "src/kinx.y"
{ yyval.strval = "native"; } break;
        case 386:
#line 852 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 387:
#line 853 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 388:
#line 854 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 389:
#line 855 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 390:
#line 856 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 391:
#line 857 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 392:
#line 858 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 393:
#line 859 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 394:
#line 860 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 395:
#line 861 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 396:
#line 862 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 397:
#line 863 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 398:
#line 864 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 399:
#line 865 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 400:
#line 866 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 401:
#line 867 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 402:
#line 868 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 403:
#line 872 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 404:
#line 873 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 405:
#line 874 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 406:
#line 875 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 407:
#line 876 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 408:
#line 877 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 409:
#line 878 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 410:
#line 879 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 411:
#line 880 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 412:
#line 881 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 413:
#line 882 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 414:
#line 883 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 415:
#line 884 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 416:
#line 885 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 417:
#line 886 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 418:
#line 887 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 419:
#line 888 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 420:
#line 889 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 421:
#line 890 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 422:
#line 891 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 423:
#line 892 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 424:
#line 893 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 425:
#line 894 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 426:
#line 895 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 427:
#line 896 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 428:
#line 897 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 429:
#line 898 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 430:
#line 899 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 431:
#line 900 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 432:
#line 901 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 433:
#line 902 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 434:
#line 903 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 435:
#line 904 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 436:
#line 905 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 437:
#line 906 "src/kinx.y"
{ yyval.strval = "**"; } break;
        case 438:
#line 907 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 439:
#line 908 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 440:
#line 909 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 441:
#line 910 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 442:
#line 911 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 443:
#line 912 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 444:
#line 913 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 445:
#line 914 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 446:
#line 915 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 447:
#line 916 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 448:
#line 917 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 449:
#line 918 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 450:
#line 919 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 451:
#line 920 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 452:
#line 921 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 453:
#line 922 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 454:
#line 923 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 455:
#line 924 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 456:
#line 925 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 457:
#line 929 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 458:
#line 930 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 459:
#line 931 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 460:
#line 935 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 461:
#line 939 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 462:
#line 943 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 463:
#line 944 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 465:
#line 949 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 466:
#line 953 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-1).obj, NULL); } break;
        case 467:
#line 954 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 468:
#line 955 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 469:
#line 956 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).obj, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 470:
#line 957 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 471:
#line 958 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 473:
#line 963 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 474:
#line 967 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 475:
#line 968 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 476:
#line 972 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 477:
#line 973 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 478:
#line 974 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, 0, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 479:
#line 978 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 480:
#line 982 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_UNKNOWN_T }; } break;
        case 481:
#line 983 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 482:
#line 987 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 483:
#line 988 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 484:
#line 992 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 485:
#line 993 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 486:
#line 994 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 487:
#line 995 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 488:
#line 996 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-7).obj, NULL, NULL), NULL); } break;
        case 489:
#line 997 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 490:
#line 998 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 491:
#line 1002 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 492:
#line 1003 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 493:
#line 1004 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 494:
#line 1008 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strinfo.name; } break;
        case 496:
#line 1013 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 497:
#line 1014 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 498:
#line 1018 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 499:
#line 1019 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 500:
#line 1023 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 501:
#line 1025 "src/kinx.y"
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
        case 503:
#line 1041 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 504:
#line 1042 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 505:
#line 1043 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 506:
#line 1047 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 507:
#line 1048 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 508:
#line 1052 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 511:
#line 1058 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 513:
#line 1063 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 514:
#line 1064 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 515:
#line 1065 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 516:
#line 1066 "src/kinx.y"
{ YYASP(2-2).obj->var_type = KX_SPR_T; yyval.obj = YYASP(2-2).obj; } break;
        case 517:
#line 1070 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 518:
#line 1071 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 519:
#line 1072 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strinfo.name) }; } break;
        case 520:
#line 1076 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 521:
#line 1077 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 522:
#line 1078 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 523:
#line 1082 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 524:
#line 1083 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 525:
#line 1087 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 526:
#line 1088 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 527:
#line 1092 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 530:
#line 1098 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 531:
#line 1099 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 532:
#line 1100 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 535:
#line 1106 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 536:
#line 1110 "src/kinx.y"
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
