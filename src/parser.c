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
#define PIPEOP 295
#define ADDEQ 296
#define SUBEQ 297
#define MULEQ 298
#define DIVEQ 299
#define MODEQ 300
#define ANDEQ 301
#define OREQ 302
#define XOREQ 303
#define LANDEQ 304
#define LOREQ 305
#define LUNDEFEQ 306
#define SHLEQ 307
#define SHREQ 308
#define REGEQ 309
#define REGNE 310
#define NUL 311
#define TRUE 312
#define FALSE 313
#define AS 314
#define IMPORT 315
#define USING 316
#define DARROW 317
#define SQ 318
#define DQ 319
#define MLSTR 320
#define BINEND 321
#define DOTS2 322
#define DOTS3 323
#define REGPF 324
#define NAMESPACE 325
#define SYSNS 326
#define SYSRET_NV 327
#define CLASS 328
#define SYSCLASS 329
#define MODULE 330
#define SYSMODULE 331
#define NATIVE 332
#define FUNCTION 333
#define SYSFUNC 334
#define PUBLIC 335
#define PRIVATE 336
#define PROTECTED 337
#define COROUTINE 338
#define NAME 339
#define STR 340
#define SRCFILE 341
#define BIGINT 342
#define INT 343
#define TYPE 344
#define TYPEOF 345
#define LBBR 346
#define RBBR 347
#define LMBR 348
#define RMBR 349
#define DBL 350
#define BIN 351
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
#line 1110 "src/kinx.y"

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
  "PIPEOP",
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
  "PipelineExpression : PipelineExpression PIPEOP LogicalUndefExpression",
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
    0,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  111,  113,  113,  113,  109,  102,  113,
   97,   98,  107,  106,   95,   94,   99,  108,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,   96,   93,
  104,   92,  105,  103,  112,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  101,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  100,  113,  110,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  113,  113,  113,    1,  113,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   57,   58,   59,   60,   61,  113,  113,
  113,   62,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,  113
#line 165 "build/utility/kmyacc.c.parser"
};

#define YYBADCH 113
#define YYMAXLEX 352
#define YYTERMS 113
#define YYNONTERMS 123

static short yyaction[] = {
  818,  819,  820,  821,  822,  823,  824,  825,  826,  827,
  828,  829,  830,  832,  831,  126,  329,  833,  834,  835,
  844,  846,  845,-32766,  854,  855,  856,  858,  860,  163,
  191,  192,   67,  852,  853,    0,  241,   79,   80,   81,
   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,
  144,  145,  146,  847,  848,  849,  115,  850,  851,  163,
  116,  135,  136,  137,   48,  394,   28,  842,   49,  843,
   29,  836,  837,  838,  839,  840,  841,   17,  816,  122,
  394,  437,  565,  817,  567,  566,  568,  433,  569,   93,
  164,  231,  862,  570,  571,  434,    1,  572,  867,  868,
  866,   96,  857,  859,  861,  863,  864,  865,  939,  940,
  941,  942,  943,  944,  945,  946,  947,  948,  949,  950,
  951,   78,  952,  790,  791,  953,  954,  955,  963,  965,
  964,   37,  975,  976,  977,  979,  981,  138,  139,  606,
  115,  973,  974,  140,  141,  114,    3,  871,   48,  573,
   28,   36,  881,   98,  574,  117,  576,  575,  107,  165,
 -392,  966,  967,  968,   64,  969,  970,  564,  555,  814,
   58,  100,  298,  563,  815,  961,   40,  962,   43,  111,
  956,  957,  958,  959,  960, -106, 1029,   47, 1070,   26,
 1053,  971,  972,  142,   37,  411,  112,  324,  256,  814,
  983,  -76,  325,  412,  815,  143,  988,  989,  987,  807,
  978,  980,  982,  984,  985,  986,  169,  416,  370,  417,
    9,  418,  909,  314,  911,  912,  237,  238,  419,  105,
  374,  106,  375,  376,  161,  234,  235,  315,   52,   59,
  302,  370,  371,   14,  372,  370,  371,   14,  372,  297,
   94,  373,  110,  374,  102,  373,  101,  374,  102,   37,
  432,  -77, -106,  457,  319,  240,   37, 1070,  593,   37,
  420,  421,  422,   37,  272,  936, -476,-32766,  528,   77,
  327,  304,  305,  377,  423,  379,  424,  381,  425,  273,
  274,   33,   34,   35,    2,  426,  108,    2,-32766,  108,
  427,  938,    1,  581,   46,  163,   25,   46, -102,   25,
  404,  239,   57,   78,  128,   78,  905,  254,  906,  907,
  908,  909,  910,  911,  912,  913,  914,  915,  916,   37,
  917,  129,  590,  161,  919,  920,  929,  931,  930, 1014,
  479,  480,  510,  114,  881,  481,  882,-32766,-32766, -362,
  107,  127,  107,   39,  147,   43, -362,-32766,-32766,-32766,
  637,  123,  448,-32766,  120,   27,  368,  190,  257,  420,
  421,  422,  874,  443,  936,  133,  134,  298,   77,  151,
  152,  153,  154,  927,  255,  928,-32766,  921,  922,  923,
  924,  925,  926,-32766,  444,   97,  311, 1040,  704,  427,
  938,  312,  892,  639,  587,  638,  591,  313,-32766,  310,
  239,   57,  409,  410,  297,  511,  445,  507,  449,  446,
-32766,-32766,  436,  308,-32766,-32766,  905,  490,  906,  907,
  908,  909,  910,  911,  912,  913,  914,  915,  916,  509,
  917,  513,  451,  161,  919,  920,  929,  931,  930,  594,
  782,  788,  811,  689,  669,  813,  207,-32766,-32766,    5,
    4,   38,    3,   37,   36,  256,  483,  588,  876,  787,
  130,  497,  515,    0,  872, 1057, 1056,  869, 1038,  420,
  421,  422,  702,  443,  936,  667,  990,  780,   77,  236,
   66,   65,  291,  927,  489,  928,   72,  921,  922,  923,
  924,  925,  926,-32766,  444,   99,  295,  109,  627,  427,
  938,  625,  894,  636,  998,  997,  626,   20,-32766,  624,
  239,   57,  640,  630,  628,   73,  445,   71,   70,   69,
-32766,-32766,   68,  603,-32766,-32766,  905,  554,  906,  907,
  908,  909,  910,  911,  912,  913,  914,  915,  916,  629,
  917,  631,  113,  161,  919,  920,  929,  931,  930,   60,
   51,   41,  223,  131, -394, -398, -395,-32766,-32766, -393,
  606,  608, -390, -382,   42,   53,   54,  722,  607,  609,
  538,  244,  242,   55,  124,  193, -391,  239,    0,  420,
  421,  422,  215,  443,  936,  221,  206,  205,   77,  204,
   95,   92,   76,  927,  209,  928,   75,  921,  922,  923,
  924,  925,  926,-32766,  444,   74,  478,  450,  406,  427,
  938,  405,  665,  243,  208,  222,  220,  219,-32766,  218,
  239,   57,  217,  216,  214,  213,  445,  212,  211,  210,
-32766,-32766,   50,    0,-32766,-32766,  905,   15,  906,  907,
  908,  909,  910,  911,  912,  913,  914,  915,  916,   16,
  917,   18,   19,  161,  919,  920,  929,  931,  930,  328,
  707,  806,  517,  647, 1061, 1059,  705,-32766,-32766,  805,
  714,  621,  670, 1042,  783,  996,  870,  808,  991,  514,
  500,  363,  362,  361,  360,  359,  352,  350,  349,  420,
  421,  422,  347,  443,  936,  346,  345,  343,   77,  340,
  337,  336,  335,  927,  334,  928,  333,  921,  922,  923,
  924,  925,  926,-32766,  444,   22,   21,  132,  445,  427,
  938,    0,    0,    0,  873,    0,    0,    0,-32766,    0,
  239,   57,    0,    0,    0,    0,  445,    0,    0,    0,
-32766,-32766,    0,    0,-32766,-32766,  905,    0,  906,  907,
  908,  909,  910,  911,  912,  913,  914,  915,  916,    0,
  917,    0,    0,  161,  919,  920,  929,  931,  930,    0,
    0,    0,    0,    0,    0,    0,    0,-32766,-32766,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  420,
  421,  422,    0,  443,  936,    0,    0,    0,   77,    0,
    0,    0,    0,  927,    0,  928,    0,  921,  922,  923,
  924,  925,  926,-32766,  444,    0,    0,    0,    0,  427,
  938,    0,    0,    0,    0,    0,    0,    0,-32766,    0,
    0,   57,    0,    0,    0,    0,-32766,    0,    0,    0,
-32766,-32766,    0,    0,-32766,-32766,  169,  369,  370,  371,
   14,  372,    0,  301,    0,    0,  250,  251,  373,  101,
  374,  102,  375,  376,    0,  232,  233,  535,   62,  103,
  302,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  258,    0, -476,    0,    0,    0,
    0,  304,  305,  377,  378,  379,  380,  381,    0,  259,
  260,   30,   31,   32,    0,  383,    0,    0,    0,    0,
    0,    0,    1,  581,    0,    0,    0,    0, -102,    0,
    0,  239,    0,    0,    0,    0,    0,  254,  169,  369,
  370,  371,   14,  372,    0,  301,    0,    0,  250,  251,
  373,  101,  374,  102,  375,  376,    0,  232,  233,  535,
   62,  103,  302,    0,    0,    0,    0,    0,   -1,  169,
  369,  370,  371,   14,  372,    0,  301,    0,    0,  250,
  251,  373,  101,  374,  102,  375,  376,    0,  232,  233,
  535,   62,  103,  302,    0,    0,  258,    0,    0,    0,
    0,    0,    0,  304,  305,  377,  378,  379,  380,  381,
    0,  259,  260,   30,   31,   32,    0,  383,    0,    0,
    0,    0,    0,    0,    1,    0,    0,  258,    0,    0,
 -102,    0,    0, -368,  304,  305,  377,  378,  379,  380,
  381,    0,  259,  260,   30,   31,   32,    0,  383,    0,
    0,    0,    0,    0,    0,    1,    0,    0,    0,    0,
    0, -102,  169,  369,  370,  371,   14,  372,    0,  301,
    0,    0,  250,  251,  373,  101,  374,  102,  375,  376,
    0,  232,  233,  535,   62,  103,  302,    0,    0,    0,
    0,    0,  169,  369,  370,  371,   14,  372,    0,  301,
    0,    0,  250,  251,  373,  101,  374,  102,  375,  376,
    0,  232,  233,  535,   62,  103,  302,    0,    0,    0,
  258,    0,    0,    0,    0,    0,    0,  304,  305,  377,
  378,  379,  380,  381,    0,  259,  260,   30,   31,   32,
    0,  383,    0,    0,    0,    0,    0,    0,    1,  789,
  258,    0,    0,    0, -102,    0,    0,  304,  305,  377,
  378,  379,  380,  381,    0,  259,  260,   30,   31,   32,
    0,  383,    0,    0,    0,    0,    0,    0,    1,  586,
    0,    0,    0,    0, -102,  169,  369,  370,  371,   14,
  372,    0,  301,    0,    0,  250,  251,  373,  101,  374,
  102,  375,  376,    0,  232,  233,  535,   62,  103,  302,
    0,    0,    0,    0,  169,  369,  370,  371,   14,  372,
    0,  301,    0,    0,  250,  251,  373,  101,  374,  102,
  375,  376,    0,  232,  233,  535,   62,  103,  302,    0,
    0,    0,    0,  258,    0,  121,    0,    0,    0,    0,
  304,  305,  377,  378,  379,  380,  381,    0,  259,  260,
   30,   31,   32,    0,  383,    0,    0,    0,    0,    0,
    0,    1,  258,    0,    0,    0,    0, -102,    0,  304,
  305,  377,  378,  379,  380,  381,    0,  259,  260,   30,
   31,   32,    0,  383,    0,    0,    0,    0,    0,    0,
    1,  584,    0,    0,    0,    0, -102,  169,  369,  370,
  371,   14,  372,    0,  301,    0,    0,  250,  251,  373,
  101,  374,  102,  375,  376,    0,  232,  233,  535,   62,
  103,  302,    0,    0,    0,    0,    0,  169,  369,  370,
  371,   14,  372,    0,  301,    0,    0,  250,  251,  373,
  101,  374,  102,  375,  376,    0,  232,  233,  535,   62,
  103,  302,    0,    0,    0,  258,    0,    0,    0,    0,
    0,    0,  304,  305,  377,  378,  379,  380,  381,    0,
  259,  260,   30,   31,   32,    0,  383,    0,    0,    0,
    0,    0,    0,    1,  583,  258,    0,    0,    0, -102,
    0,    0,  304,  305,  377,  378,  379,  380,  381,    0,
  259,  260,   30,   31,   32,    0,  383,    0,    0,    0,
    0,    0,    0,    1,  582,    0,    0,    0,    0, -102,
  169,  369,  370,  371,   14,  372,    0,  301,    0,    0,
  250,  251,  373,  101,  374,  102,  375,  376,    0,  232,
  233,  535,   62,  103,  302,    0,    0,    0,    0,    0,
  169,  369,  370,  371,   14,  372,    0,  301,    0,    0,
  250,  251,  373,  101,  374,  102,  375,  376,    0,  232,
  233,  535,   62,  103,  302,    0,    0,    0,  258,    0,
    0,    0,    0,    0,    0,  304,  305,  377,  378,  379,
  380,  381,    0,  259,  260,   30,   31,   32,    0,  383,
    0,    0,    0,    0,    0,    0,    1,  581,  258,    0,
  125,    0, -102,    0,    0,  304,  305,  377,  378,  379,
  380,  381,    0,  259,  260,   30,   31,   32,    0,  383,
    0,    0,    0,    0,    0,    0,    1,    0,    0,    0,
    0,    0, -102,  169,  369,  370,  371,   14,  372,    0,
  301,    0,    0,  250,  251,  373,  101,  374,  102,  375,
  376,    0,  232,  233,  535,   62,  103,  302,    0,    0,
    0,    0,    0,  169,  369,  370,  371,   14,  372,    0,
  301,    0,    0,  250,  251,  373,  101,  374,  102,  375,
  376,    0,  232,  233,  535,   62,  103,  302,    0,    0,
    0,  258,    0,    0,    0,    0,    0,-32766,  304,  305,
  377,  378,  379,  380,  381,    0,  259,  260,   30,   31,
   32,    0,  383,    0,    0,    0,-32766,-32766,    0,    1,
  585,  258,    0,    0,    0, -102,    0,    0,  304,  305,
  377,  378,  379,  380,  381,    0,  259,  260,   30,   31,
   32,  104,  383,    0,    0,    0,  160,    0,    0,    1,
    0,    0,    0,    0,    0, -102,-32766,-32766,-32766,    0,
  155,  156,-32766,    0,    0,    0,    0,    0,    0,    0,
  536,    0,    0,    0,    0,    0,    0,-32766,    0,    0,
    0,    0,  795,  796,  797,-32766,  397,    0,    0,-32766,
-32766,    0,  303,-32766,-32766,    0,    0,    0,    0,    0,
 1014,  398,  399,    0,  162,    0,  382,  814,    0,  798,
  794,  792,  815,    0,   39,    0,   43,    0,  793,    0,
    0,  157,    0,    0,   56,    0,   23,    0,    0,  253,
    0,  306,    0,  158,  148,  537,    0,  149,  150,   24,
  711,  712,  713,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  814,    0,    0,  710,  708,
  815,    0,    0,    0,    0,    0,  709,    0,    0,    0,
    0,    0,   61
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1833

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   39,    3,   19,   20,   21,
   22,   23,   24,   14,   26,   27,   28,   29,   30,   16,
   63,   64,   92,   35,   36,    0,   96,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,
  107,  108,  109,   55,   56,   57,   89,   59,   60,   16,
   89,   28,   29,   30,   97,    2,   99,   69,   97,   71,
   99,   73,   74,   75,   76,   77,   78,    3,   80,  103,
    2,    4,    2,   85,    4,    5,    6,   89,    8,   92,
   31,   20,   94,   13,   14,   97,   87,   17,  100,  101,
  102,    7,  104,  105,  106,  107,  108,  109,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   64,   16,   33,   34,   19,   20,   21,   22,   23,
   24,   87,   26,   27,   28,   29,   30,  104,  105,   96,
   89,   35,   36,   35,   36,  101,   87,   90,   97,   69,
   99,   87,   95,    7,   74,   96,   76,   77,  101,  100,
   96,   55,   56,   57,   93,   59,   60,   87,   88,   80,
   92,   64,   80,   93,   85,   69,   87,   71,   89,   89,
   74,   75,   76,   77,   78,   93,   80,   97,   81,   99,
   73,   85,   86,   94,   87,   89,   24,   80,   87,   80,
   94,    7,   85,   97,   85,  106,  100,  101,  102,   98,
  104,  105,  106,  107,  108,  109,    1,    2,    3,    4,
    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
   25,    3,    4,    5,    6,    3,    4,    5,    6,   80,
   64,   13,   14,   15,   16,   13,   14,   15,   16,   87,
   81,    7,   93,   81,    9,   58,   87,   81,   84,   87,
   55,   56,   57,   87,   59,   60,   61,   14,   94,   64,
   10,   66,   67,   68,   69,   70,   71,   72,   73,   74,
   75,   76,   77,   78,   87,   80,   89,   87,   14,   89,
   85,   86,   87,   88,   97,   16,   99,   97,   93,   99,
   20,   96,   97,   64,   31,   64,    2,  102,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   87,
   16,   32,   84,   19,   20,   21,   22,   23,   24,   73,
   74,   75,   94,  101,   95,   79,   95,   33,   34,   88,
  101,   38,  101,   87,   37,   89,   95,   73,   74,   75,
   93,   61,   95,   79,   61,   99,   61,  101,  102,   55,
   56,   57,   62,   59,   60,   26,   27,   80,   64,   53,
   54,   63,   64,   69,   64,   71,  102,   73,   74,   75,
   76,   77,   78,   79,   80,   64,   80,   86,   86,   85,
   86,   80,   88,   80,   80,   80,   84,   80,   94,   80,
   96,   97,   80,   80,   80,   80,  102,   80,   80,   80,
  106,  107,   80,   87,  110,  111,    2,   81,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   81,
   16,   81,   81,   19,   20,   21,   22,   23,   24,   84,
   86,   88,   86,   86,   86,   86,   97,   33,   34,   87,
   87,   87,   87,   87,   87,   87,   95,   88,   88,   88,
  100,   89,   89,   -1,   90,   90,   90,   90,   90,   55,
   56,   57,   90,   59,   60,   90,   90,   90,   64,   95,
   92,   92,   92,   69,   92,   71,   92,   73,   74,   75,
   76,   77,   78,   79,   80,   92,   92,   95,   93,   85,
   86,   93,   88,   93,   93,   93,   93,   98,   94,   93,
   96,   97,   93,   93,   93,   93,  102,   93,   93,   93,
  106,  107,   93,   93,  110,  111,    2,   93,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   93,
   16,   93,   95,   19,   20,   21,   22,   23,   24,   95,
   95,   95,   95,  101,   96,   96,   96,   33,   34,   96,
   96,   96,   96,   96,   96,   96,   96,   96,   96,   96,
   96,   96,   96,   96,   96,   96,   96,   96,   -1,   55,
   56,   57,   97,   59,   60,   97,   97,   97,   64,   97,
   97,   97,   97,   69,   97,   71,   97,   73,   74,   75,
   76,   77,   78,   79,   80,   97,   97,   97,   97,   85,
   86,   97,   88,   97,   97,   97,   97,   97,   94,   97,
   96,   97,   97,   97,   97,   97,  102,   97,   97,   97,
  106,  107,   97,   -1,  110,  111,    2,   98,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   98,
   16,   98,   98,   19,   20,   21,   22,   23,   24,   98,
   98,   98,   98,   98,   98,   98,   98,   33,   34,   98,
   98,   98,   98,   98,   98,   98,   98,   98,   98,   98,
   98,   98,   98,   98,   98,   98,   98,   98,   98,   55,
   56,   57,   98,   59,   60,   98,   98,   98,   64,   98,
   98,   98,   98,   69,   98,   71,   98,   73,   74,   75,
   76,   77,   78,   79,   80,   98,   98,  102,  102,   85,
   86,   -1,   -1,   -1,  105,   -1,   -1,   -1,   94,   -1,
   96,   97,   -1,   -1,   -1,   -1,  102,   -1,   -1,   -1,
  106,  107,   -1,   -1,  110,  111,    2,   -1,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   -1,
   16,   -1,   -1,   19,   20,   21,   22,   23,   24,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   33,   34,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   55,
   56,   57,   -1,   59,   60,   -1,   -1,   -1,   64,   -1,
   -1,   -1,   -1,   69,   -1,   71,   -1,   73,   74,   75,
   76,   77,   78,   79,   80,   -1,   -1,   -1,   -1,   85,
   86,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   94,   -1,
   -1,   97,   -1,   -1,   -1,   -1,  102,   -1,   -1,   -1,
  106,  107,   -1,   -1,  110,  111,    1,    2,    3,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   16,   17,   18,   -1,   20,   21,   22,   23,   24,
   25,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   59,   -1,   61,   -1,   -1,   -1,
   -1,   66,   67,   68,   69,   70,   71,   72,   -1,   74,
   75,   76,   77,   78,   -1,   80,   -1,   -1,   -1,   -1,
   -1,   -1,   87,   88,   -1,   -1,   -1,   -1,   93,   -1,
   -1,   96,   -1,   -1,   -1,   -1,   -1,  102,    1,    2,
    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   17,   18,   -1,   20,   21,   22,
   23,   24,   25,   -1,   -1,   -1,   -1,   -1,    0,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   -1,   20,   21,
   22,   23,   24,   25,   -1,   -1,   59,   -1,   -1,   -1,
   -1,   -1,   -1,   66,   67,   68,   69,   70,   71,   72,
   -1,   74,   75,   76,   77,   78,   -1,   80,   -1,   -1,
   -1,   -1,   -1,   -1,   87,   -1,   -1,   59,   -1,   -1,
   93,   -1,   -1,   96,   66,   67,   68,   69,   70,   71,
   72,   -1,   74,   75,   76,   77,   78,   -1,   80,   -1,
   -1,   -1,   -1,   -1,   -1,   87,   -1,   -1,   -1,   -1,
   -1,   93,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,   -1,
   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,   -1,
   59,   -1,   -1,   -1,   -1,   -1,   -1,   66,   67,   68,
   69,   70,   71,   72,   -1,   74,   75,   76,   77,   78,
   -1,   80,   -1,   -1,   -1,   -1,   -1,   -1,   87,   88,
   59,   -1,   -1,   -1,   93,   -1,   -1,   66,   67,   68,
   69,   70,   71,   72,   -1,   74,   75,   76,   77,   78,
   -1,   80,   -1,   -1,   -1,   -1,   -1,   -1,   87,   88,
   -1,   -1,   -1,   -1,   93,    1,    2,    3,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   17,   18,   -1,   20,   21,   22,   23,   24,   25,
   -1,   -1,   -1,   -1,    1,    2,    3,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   17,   18,   -1,   20,   21,   22,   23,   24,   25,   -1,
   -1,   -1,   -1,   59,   -1,   61,   -1,   -1,   -1,   -1,
   66,   67,   68,   69,   70,   71,   72,   -1,   74,   75,
   76,   77,   78,   -1,   80,   -1,   -1,   -1,   -1,   -1,
   -1,   87,   59,   -1,   -1,   -1,   -1,   93,   -1,   66,
   67,   68,   69,   70,   71,   72,   -1,   74,   75,   76,
   77,   78,   -1,   80,   -1,   -1,   -1,   -1,   -1,   -1,
   87,   88,   -1,   -1,   -1,   -1,   93,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   -1,   -1,   -1,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,
   -1,   -1,   66,   67,   68,   69,   70,   71,   72,   -1,
   74,   75,   76,   77,   78,   -1,   80,   -1,   -1,   -1,
   -1,   -1,   -1,   87,   88,   59,   -1,   -1,   -1,   93,
   -1,   -1,   66,   67,   68,   69,   70,   71,   72,   -1,
   74,   75,   76,   77,   78,   -1,   80,   -1,   -1,   -1,
   -1,   -1,   -1,   87,   88,   -1,   -1,   -1,   -1,   93,
    1,    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   14,   15,   16,   17,   18,   -1,   20,
   21,   22,   23,   24,   25,   -1,   -1,   -1,   -1,   -1,
    1,    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   14,   15,   16,   17,   18,   -1,   20,
   21,   22,   23,   24,   25,   -1,   -1,   -1,   59,   -1,
   -1,   -1,   -1,   -1,   -1,   66,   67,   68,   69,   70,
   71,   72,   -1,   74,   75,   76,   77,   78,   -1,   80,
   -1,   -1,   -1,   -1,   -1,   -1,   87,   88,   59,   -1,
   61,   -1,   93,   -1,   -1,   66,   67,   68,   69,   70,
   71,   72,   -1,   74,   75,   76,   77,   78,   -1,   80,
   -1,   -1,   -1,   -1,   -1,   -1,   87,   -1,   -1,   -1,
   -1,   -1,   93,    1,    2,    3,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   16,   17,
   18,   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,
   -1,   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   16,   17,
   18,   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,
   -1,   59,   -1,   -1,   -1,   -1,   -1,   14,   66,   67,
   68,   69,   70,   71,   72,   -1,   74,   75,   76,   77,
   78,   -1,   80,   -1,   -1,   -1,   33,   34,   -1,   87,
   88,   59,   -1,   -1,   -1,   93,   -1,   -1,   66,   67,
   68,   69,   70,   71,   72,   -1,   74,   75,   76,   77,
   78,   14,   80,   -1,   -1,   -1,   19,   -1,   -1,   87,
   -1,   -1,   -1,   -1,   -1,   93,   73,   74,   75,   -1,
   33,   34,   79,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   43,   -1,   -1,   -1,   -1,   -1,   -1,   94,   -1,   -1,
   -1,   -1,   55,   56,   57,  102,   59,   -1,   -1,  106,
  107,   -1,   65,  110,  111,   -1,   -1,   -1,   -1,   -1,
   73,   74,   75,   -1,   19,   -1,   79,   80,   -1,   82,
   83,   84,   85,   -1,   87,   -1,   89,   -1,   91,   -1,
   -1,   94,   -1,   -1,   97,   -1,   99,   -1,   -1,  102,
   -1,  104,   -1,  106,  107,  108,   -1,  110,  111,  112,
   55,   56,   57,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   80,   -1,   -1,   83,   84,
   85,   -1,   -1,   -1,   -1,   -1,   91,   -1,   -1,   -1,
   -1,   -1,   97
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1612,  215,  865, 1459, 1336, 1243, 1214, 1489,  998,  967,
 1366, 1582, 1121, 1091, 1612, 1612, 1612, 1612, 1612, 1612,
 1612, 1612, 1612,  366,  369,  364,  368,  367,  312,  311,
  106,  106,  106,  106,  106,  106,  314,  534,  424,  644,
  754,  754,  242,   57,  249,  251,  186,  186,  186,  186,
   71,  107,   64,   44,   44,   44,  179,  182,  172,  490,
  331,  358,  377,  377,  377,  376,  376,  376,  377,  377,
  377,  377,  376,  377, 1677, 1677, 1677,  376,  376,  376,
  376,  376,  376,  376,  376,  376,  376,  376,  376,  376,
  376,  376, 1677,  376,  376, 1677, 1677,  376, 1677,  376,
  376, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,  374,
 1677, 1677, 1677, 1677, 1677, 1677, 1677,    9,    9,    9,
    9,    9,  263,  263,  263,  263,  284,  284,  284,  284,
  284,  284,  284,  284,  284,  284,  284,  284,  284,  284,
  284,  284,  284,  284,  284,  284,  284,  284,  284,  284,
  284,  284,  284,  284,  284, 1633, 1633, 1633, 1633, 1633,
 1633, 1633, 1633,  266,  266,  266,   43,   78,  289,   80,
  475,  573,  397,  474,  395,  572,  392,  388,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
 1735, 1735, 1735,  238,  207,  111,  -33,  210,  210,  210,
  210,  378,  378,  378,  320,  320,  320,  320,  320,  320,
  320,  320,  320,  320,  320,  320,  320,  320,  320,  320,
  320,  320,  320,  320,   59,   51,   51,   51,   33,   33,
   33,   89,   89,   89,   89,   89,   89,  169,   92,  117,
  117,  117,  117,  117,  117,  -29,  -57,  -57,  -57,  194,
  334,  297,   13,  359,  495,  119,  626,  498,  290,  332,
  333,  349,  108,   99,  326,  318,  342,  -24,  -60,  422,
  421,  267,  290,  332,  333,  261,  549,  561,  439,  571,
  349,  108,  108,  108,  108,  108,   99,   99,  326,  436,
  575,  248,  574,  563,  564,  184,   63,   63,   63,   63,
   63,  375,  325,  521,  324,  324,  629,  255,  339,  521,
  507,  507,  375,  375,  375,  476,  466,  375,  521,  519,
  270,  371,  484,  484,  382,  382,  375,  375,  375,  481,
  526,  375,  375,  491,  491,  491,  491,  485,  375,  481,
  491,  526,  375,  491,  375,  491,  491,  491,  375,  491,
  485,  375,  491,  375,  375,  375,  375,  375,  375,  491,
  491,  491,  491,  485,  375,  375,  375,  375,  375,  518,
  483,  509,  545,  505,  482,  336,  431,  430,  329,  316,
  321,  327,  499,  489,   35,  429,  313,  283,  299,  370,
  462,  625,  317,   77,  504,  426,  423,  524,  502,  500,
  527,  399,  398,  412,  338,  520,  361,  373,  372,  542,
  541,  396,  590,  540,  538,  537,  518,  509,  545,  505,
  473,  468,  470,  329,  321,  477,  478,  469,  479,  300,
  384,  464,  589,  387,  588,  458,  536,  503,   94,  254,
  194,  418,  415,  524,  480,  535,  400,  420,  323,  402,
  346,  587,  486,  618,  467,  616,  614,  592,  380,  464,
  613,  310,  283,  299,  370,  462,  625,  317,  317,  317,
  586,  465,  612,  313,  488,  146,  399,  435,  337,  532,
  530,  529,  528,  335,  379,  413,  413,  413,  456,  360,
  591,  585,  611,  609,  608,  607,  604,  386,  383,  383,
  487,  600,  381,  584,  599,   74,  434,  583,  598,  582,
  322,  414,  404,  444,  581,  385,  303,  440,  432,  419,
  597,  596,  595,  594,  593,  578,  577,  628,  365,  413,
  627,  305,  576,  363,  363,    0,    0,    0,    0, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677, 1677,   -2,   -2,   -2,   -2,   -2,   -2,   -2,    0,
    0,    0,    0,    0,    0, 1677, 1677, 1677, 1677, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677, 1677, 1677,    0,    0,    0, 1677, 1677, 1677, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677,    0, 1677, 1677,    0,    0, 1677,    0, 1677, 1677,
    0,    0,    0,    0,    0,    0,    0,    0, 1677,    0,
    0,    0,    0,    0,    0,    0, 1677, 1677, 1677, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677, 1677,
 1677, 1677, 1735, 1735, 1735,   -3,   -3,   -3,    0,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   90,   90,   90,   90,   90,   90,   90,
   90,   90,   90,   89,   89,   89,   89,   89,   89,   89,
   89,   89,   89,   89,   89,   89,   89,   89,   89,   89,
   89,   89,   89,   63,   90,   90,   90,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   63,   63,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -60,   63,
   63,    0,  491,  491,    0,  491,  491,  524,  502,  500,
    0,    0,    0,    0,    0,  527,    0,    0,  394,  394,
    0,  524,  502,  500,    0,  457,  457,  457,  457,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  394,  457,
    0,  457,  457,  457
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 295

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  385,  386,  387,  476,  476,  476,  476,
32767,  339,32767,32767,32767,32767,  523,  523,  523,  523,
32767,32767,  104,32767,32767,32767,32767,32767,32767,   94,
  347,32767,  104,  104,  104,32767,32767,32767,  104,  104,
  104,  104,32767,  104,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   94,32767,  377,  378,32767,32767,32767,
32767,32767,   96,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  225,  227,32767,32767,32767,32767,32767,
32767,  379,32767,32767,32767,32767,32767,  106,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  352,   93,
  344,  350,  345,  529,  354,  363,  348,   95,  351,  364,
32767,  151,  153,32767,  237,32767,  144,  235,  236,  233,
  232,  125,  530,  365,  504,  504,  504,  504,  504,  504,
  504,  504,  504,  504,  504,  504,  504,  504,  504,  504,
  504,  504,  504,32767,32767,  145,  152,  154,  201,  202,
  203,32767,32767,32767,  380,  381,32767,  374,  375,32767,
32767,32767,32767,32767,32767,  521,  213,  215,  214,  462,
  106,  106,  177,  476,  476,32767,  476,  476,32767,32767,
32767,  199,  204,  210,  220,  222,32767,  185,  462,32767,
32767,32767,  396,  383,  384,  229,32767,32767,32767,32767,
  200,  206,  208,  209,  205,  207,  211,  212,  221,32767,
32767,32767,32767,32767,32767,32767,  106,  106,  106,  106,
  106,32767,32767,32767,32767,32767,  336,   79,32767,32767,
  502,  502,32767,32767,  371,  532,  338,32767,32767,   81,
   83,  338,  496,  496,  516,  516,32767,32767,32767,  182,
  519,32767,32767,  476,  476,  476,  476,  478,32767,  182,
  476,  519,32767,  476,32767,  476,  476,  476,32767,  476,
  478,32767,  476,32767,32767,32767,32767,32767,32767,  476,
  476,  476,  476,  478,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  275,32767,32767,  187,  189,  191,  193,
  195,  197,  216,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  105,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  366,  367,  369,  376,
  256,  257,  258,  388,  389,  475,  275,  276,32767,32767,
32767,  340,32767,32767,32767,32767,32767,32767,32767,  262,
  260,32767,32767,  396,  275,32767,   50,32767,32767,32767,
32767,32767,  508,32767,  505,32767,32767,32767,32767,  341,
32767,32767,  190,  192,  194,  196,  198,  217,  218,  219,
32767,  524,32767,  188,32767,32767,   77,32767,32767,32767,
32767,32767,32767,  339,32767,  466,  467,  464,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  515,  513,
  269,32767,32767,32767,32767,   61,32767,32767,32767,32767,
32767,   53,  463,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  465,
32767,32767,32767,  484,32767,  532,  456,  456,  532
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  185,  180,  180,  180,  183,  183,  183,  183,  181,  183,
  178,  185,  185,  185,  171,  171,  440,  179,  186,  175,
  178,  178,  178,  503,  525,  532,  178,  178,  178,  178,
  642,  178,  181,  181,  181,  720,  720,  720, 1024, 1024,
  719,  719,  719, 1023,  533,  474,  502,  725,  534,  993,
  181,  486,  487,  181,  181,  896,  181,  529,  992,  166,
  170,  179,  168,  166,  170,  182,  172,  184,  173,  174,
  187,  188,  189,  176,  177,  266,  266,  266,  266,  266,
  266,  266,  266,  266,  266,  266,  266,  266,  266,  266,
  266,  266,  266,  266,  266,  266,  266,  266,  300,  477,
  358,  396,  461,  506,  518,  519,  527,  599,  530,  687,
  687,  687,  785,  367,  396,  785,  785,  785,  785, 1066,
  666,  701,   11,   12,   13,   13,  666,  666,  666,  706,
  706,  706,  812,  781,  668,  688,  703, 1039,  439,  459,
  786,  671,  720,  786,  786,  786,  786,  671,  671,  671,
  701,  701,  701,  467,  468,  469,  706,  706,  706,  435,
  441,  442,  447,  488,  281,  282,  283,  284,  285,  473,
  452,  452,  452,  452,  452,  452,  452,  452,  452,  452,
  452,  452,  452,  452,  452,  452,  452,  452,  452,  452,
  777,  330,  341,  526, 1018,  541,  462,  249,  268,  268,
  268,  268,  268,  542,  393,  544,  544,  544,  544,  393,
  505,  602,  601,  613,  614,  612,  611,  610,  899,  307,
  897, 1051,  773,  769,  770,  762,  763,  765,  767,  463,
 1033, 1034,  307,  414,  415, 1025,  414,  415,  482,  482,
  482,  225,  226,  227,  619,  623,  604,  717,  678, 1031,
 1032,  685,  685,  685,  464,  289,  699,  270,  599,  270,
 1019,  465, 1020,  229,  230,  466, 1021,  286,  287, 1022,
  280, 1011, 1012, 1026, 1027, 1028, 1013,  275,  197,  198,
  199,  200,  694,  695,  696,  697,  698,  686,  686,  686,
  247,  248, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049, 1049,
 1049, 1049,  901,  901,  901,  901,  901,  901,  288,  476,
  401,  401,  401,  401,  401,  681,  680, 1046, 1050, 1050,
 1050, 1050, 1050, 1050, 1050, 1050, 1050, 1050, 1050, 1050,
 1050, 1050, 1050, 1050, 1050, 1050, 1050, 1050, 1037,  809,
  809,  715,  677,  475,  663,  402,  402,  402,  402,  402,
  402,  663,  663,  663,  339,  317,  317,  675,  663,  338,
  323, 1000,  408,  663,  663,  663,  663,  663,  663,  663,
  663,  663,  663,  663,  663,  663,  663,  663,  649,  663,
  663,  484,  119,  663,  332,  663,  663,  499, 1048,  318,
    0,    0,  159,    0,    0,    0,    0,  900,  885,  652,
  653,  654,  655,  656,  657,  658,  659,  660,  661,  662,
  650,  651,    0,  649, 1065,    0,    0,  888,  203, 1008,
 1067,    0,  202,  202,  202,  202,    0,  202,    0,  203,
  203,  203,  195,  195,    0,  342,  344,  348,  516,    0,
    0,    0,  353,    0,    0,  354,    0,  355,  356,  357,
    0,    6,    0,    0,    7,    0,    0,    0,    0,    0,
    0,  364,  365,  366,  531,  455,  456,  460,  472,  491,
  492,  493,  494,  495,  496,  501,  504,  508,  520,  521,
  522,  523,  524,  276,  277,  279,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  290,    0,    0,  292,  293,    0,  294
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 518

static char yygcheck[] = {
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   74,   37,   37,   37,
   37,   37,   37,   98,   98,   98,   37,   37,   37,   37,
   31,   37,   37,   37,   37,    7,    7,    7,    7,    7,
   41,   41,   41,   41,   41,   41,   41,   41,   41,   65,
   37,   81,   81,   37,   37,   72,   37,   81,   65,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   40,   40,
  102,   31,   66,   40,   40,   40,   40,   35,   40,   97,
   97,   97,    7,  102,   31,    7,    7,    7,    7,  100,
   59,   59,    3,    3,    3,    3,   59,   59,   59,   74,
   74,   74,   58,   58,   58,   58,   58,   58,   62,   67,
   97,   97,    7,   97,   97,   97,   97,   97,   97,   97,
   59,   59,   59,   53,   53,   53,   74,   74,   74,   31,
   31,   31,   31,   31,   50,   50,   50,   50,   50,   42,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
  103,  103,  103,  103,  103,    4,   43,   74,   74,   74,
   74,   74,   74,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,   73,    7,
   73,   74,   55,   55,   55,   55,   55,   55,   55,   44,
    7,    7,    7,   76,   76,    7,   76,   76,   82,   82,
   82,  113,  113,  113,    7,    7,    7,  117,  117,    7,
    7,   62,   62,   62,   45,   79,    7,   79,   35,   79,
    7,   46,    7,   49,   49,   47,    7,   51,   51,    7,
   48,    7,    7,    7,    7,    7,    7,   56,   57,   57,
   57,   57,    7,    7,    7,    7,    7,   63,   63,   63,
   52,   52,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   56,   56,   56,   56,   56,   56,   54,   62,
   62,   62,   62,   62,   62,  112,  112,   95,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   60,   60,
   60,   60,  118,   19,  108,   63,   63,   63,   63,   63,
   63,  108,  108,  108,   32,  101,  101,  110,  108,  101,
   91,   80,    9,  108,  108,  108,  108,  108,  108,  108,
  108,  108,  108,  108,  108,  108,  108,  108,   38,  108,
  108,  119,  120,  108,   89,  108,  108,  104,  105,  122,
   -1,   -1,  106,   -1,   -1,   -1,   -1,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   -1,   38,   38,   -1,   -1,   38,   39,   38,
   38,   -1,   39,   39,   39,   39,   -1,   39,   -1,   39,
   39,   39,   39,   39,   -1,  101,  101,  101,  101,   -1,
   -1,   -1,  101,   -1,   -1,  101,   -1,  101,  101,  101,
   -1,  101,   -1,   -1,  101,   -1,   -1,   -1,   -1,   -1,
   -1,  101,  101,  101,  101,   93,   93,   93,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   93,   93,   93,   69,   69,   69,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   69,   -1,   -1,   69,   69,   -1,   69
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  118,  195,    0,    0,  -82,    0,   67,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  122,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -137,  140,    0,    0,   65,    0,  -42,  330,  386,
   35,  -77,   43,   69,  101,  125,  131,  134,  138,  130,
   29,  127,  148,    9,  171,   74,  276,  123,  108,  -75,
  189,    0,   88,  124,    0, -260,   58,   94,    0,  419,
    0,    0,   14,  165,  -34,    0,  202,    0,    0,   24,
  135,  -15,   75,    0,    0,    0,    0,    0,    0,   71,
    0,   59,    0,  270,    0,  104,    0,  -54,  -24,    0,
   68,  112, -250,  -50,   72,   57, -136,    0,  296,    0,
  115,    0,  161,   51,    0,    0,    0,  129,  128,   70,
   53,    0, -138
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  384,    8,   10,  543,  546,  545,  547,  548,  407,
  549,  321,  561,  550,  577,  578,  579,  605,  580,  438,
  551,  320,  326,  617,  556,  557,  296,  558,  559,  271,
  560,  395,  646,  562,  552,  553,  385,  167, 1007,  201,
  299,  672,  386,  387,  388,  389,  390,  391,  261,  228,
  262,  263,  246,  392,  264,  265,  768,  194,  810,  779,
  778,  800,  801,  802,  803,  994,  430,  431,   45,  278,
  403,  316,  895,  898,  799,  428,  413, 1030,  595,  269,
  999,  485,  400,  596, 1009,  723, 1010,  597,  598,  331,
  245,  322, 1036,  453,  454, 1045,  784,  804,  470,  471,
 1064,  429,  351, 1016,  498,  512,   63,  267,  648,  252,
  674,  224,  679,  196,  682,  700,  673,  676,  718,  458,
  118,   44,  309
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
  117,  118,  120,  120,   41,   41,   41,  107,  107,   42,
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
   58,   58,   62,   62,   61,   61,  121,   63,  119,  119,
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
   77,   77,   77,   64,   64,   64,  122,   65,   78,   78,
   79,   79,   80,   80,   80,   80,   80,   80,   81,   81,
   83,   83,   84,   84,   84,   82,  101,  101,  102,  102,
   85,   85,   85,   85,   85,   85,   85,   86,   86,   86,
   76,   76,   87,   87,   88,   88,   89,   89,   90,   90,
   90,   90,   91,   91,   93,   93,   94,   94,   95,   95,
   95,   95,   95,  103,  103,  103,  104,  104,  104,  105,
  105,   92,   92,   98,   98,   99,   99,   99,   99,  100,
  100,  100,  106
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
    1,    1,    0,    1,    1,    1,    5,    1,    3,    1,
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
    1,    2,    2,    3,    3,    2,    0,    3,    3,    3,
    1,    3,    1,    4,    3,    6,    3,    3,    1,    3,
    1,    1,    7,    7,    7,    1,    0,    2,    0,    2,
    6,    6,    6,    6,    7,    7,    3,    7,    7,    7,
    1,    1,    5,    5,    3,    3,    0,    4,    1,    4,
    3,    3,    0,    3,    0,    1,    1,    3,    1,    4,
    1,    1,    2,    2,    1,    2,    0,    2,    3,    0,
    3,    0,    3,    0,    1,    1,    2,    3,    4,    1,
    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 955
#define YYNLSTATES 539
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
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 190:
#line 551 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 556 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 194:
#line 561 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 566 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 571 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 200:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 581 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 203:
#line 582 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 205:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 206:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 207:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 208:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 209:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 211:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 212:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 214:
#line 602 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 215:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 217:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 218:
#line 609 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 219:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 221:
#line 615 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 223:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 224:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 225:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 226:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 227:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 228:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 230:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 231:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 232:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 233:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 234:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 235:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 236:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 238:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 240:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 241:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 242:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 243:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 244:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 245:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 246:
#line 655 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 248:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-5).arraytype, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(4-5).obj, NULL, NULL), NULL); } break;
        case 249:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-9).arraytype, NULL, YYASP(4-9).obj, kx_gen_stmt_object(KXST_RET, YYASP(8-9).obj, NULL, NULL), NULL); } break;
        case 250:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-8).arraytype, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 251:
#line 666 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 252:
#line 667 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 253:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 254:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 255:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 256:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 257:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 258:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 259:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 266:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 267:
#line 685 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 268:
#line 686 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 269:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 270:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 271:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 272:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 273:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 274:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 275:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_UNKNOWN_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2); } break;
        case 276:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(kx_gen_typestr_object(YYASP(1-1).intval), KX_UNKNOWN_T); } break;
        case 277:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object_pos(YYASP(1-1).strinfo); } break;
        case 278:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 279:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 280:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 281:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 282:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 283:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 284:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 285:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 286:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 287:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 288:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 289:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 290:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 291:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 292:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 293:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 294:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 295:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 296:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 297:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 298:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 299:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 300:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 301:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 302:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 303:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 304:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 305:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 306:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 307:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 308:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 309:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 310:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 311:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 312:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 313:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 314:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 315:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 316:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 317:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 318:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 319:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 320:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 321:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 322:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 323:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 324:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 325:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 326:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 327:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 328:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 329:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 330:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 331:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 332:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 333:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 334:
#line 764 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 335:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 336:
#line 769 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 337:
#line 773 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 338:
#line 777 "src/kinx.y"
{} break;
        case 340:
#line 782 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 341:
#line 783 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 342:
#line 787 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 343:
#line 788 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 345:
#line 793 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 346:
#line 794 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 347:
#line 795 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 348:
#line 796 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 349:
#line 797 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 351:
#line 802 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 353:
#line 807 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 354:
#line 808 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 355:
#line 809 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 357:
#line 814 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 358:
#line 818 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 359:
#line 819 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 360:
#line 820 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 361:
#line 821 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 362:
#line 822 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 364:
#line 827 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 366:
#line 832 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 367:
#line 833 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 368:
#line 834 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 369:
#line 835 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 370:
#line 836 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 371:
#line 837 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 372:
#line 838 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 373:
#line 839 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 374:
#line 840 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 375:
#line 841 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 376:
#line 842 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 377:
#line 843 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 378:
#line 844 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 379:
#line 845 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 380:
#line 846 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 381:
#line 847 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 382:
#line 848 "src/kinx.y"
{ yyval.strval = "native"; } break;
        case 383:
#line 849 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 384:
#line 850 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 385:
#line 851 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 386:
#line 852 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 387:
#line 853 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 388:
#line 854 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 389:
#line 855 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 390:
#line 856 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 391:
#line 857 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 392:
#line 858 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 393:
#line 859 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 394:
#line 860 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 395:
#line 861 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 396:
#line 862 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 397:
#line 863 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 398:
#line 864 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 399:
#line 865 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 400:
#line 869 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 401:
#line 870 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 402:
#line 871 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 403:
#line 872 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 404:
#line 873 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 405:
#line 874 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 406:
#line 875 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 407:
#line 876 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 408:
#line 877 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 409:
#line 878 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 410:
#line 879 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 411:
#line 880 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 412:
#line 881 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 413:
#line 882 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 414:
#line 883 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 415:
#line 884 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 416:
#line 885 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 417:
#line 886 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 418:
#line 887 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 419:
#line 888 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 420:
#line 889 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 421:
#line 890 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 422:
#line 891 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 423:
#line 892 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 424:
#line 893 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 425:
#line 894 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 426:
#line 895 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 427:
#line 896 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 428:
#line 897 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 429:
#line 898 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 430:
#line 899 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 431:
#line 900 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 432:
#line 901 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 433:
#line 902 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 434:
#line 903 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 435:
#line 904 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 436:
#line 905 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 437:
#line 906 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 438:
#line 907 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 439:
#line 908 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 440:
#line 909 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 441:
#line 910 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 442:
#line 911 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 443:
#line 912 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 444:
#line 913 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 445:
#line 914 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 446:
#line 915 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 447:
#line 916 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 448:
#line 917 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 449:
#line 918 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 450:
#line 919 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 451:
#line 920 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 452:
#line 921 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 453:
#line 925 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 454:
#line 926 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 455:
#line 927 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 456:
#line 931 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 457:
#line 935 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 458:
#line 939 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 459:
#line 940 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 461:
#line 945 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 462:
#line 949 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-1).obj, NULL); } break;
        case 463:
#line 950 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 464:
#line 951 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 465:
#line 952 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).obj, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 466:
#line 953 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 467:
#line 954 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 469:
#line 959 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 470:
#line 963 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 471:
#line 964 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 472:
#line 968 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 473:
#line 969 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 474:
#line 970 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, 0, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 475:
#line 974 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 476:
#line 978 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_UNKNOWN_T }; } break;
        case 477:
#line 979 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 478:
#line 983 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 479:
#line 984 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 480:
#line 988 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 481:
#line 989 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 482:
#line 990 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 483:
#line 991 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 484:
#line 992 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-7).obj, NULL, NULL), NULL); } break;
        case 485:
#line 993 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 486:
#line 994 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 487:
#line 998 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 488:
#line 999 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 489:
#line 1000 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 490:
#line 1004 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strinfo.name; } break;
        case 492:
#line 1009 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 493:
#line 1010 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 494:
#line 1014 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 495:
#line 1015 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 496:
#line 1019 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 497:
#line 1021 "src/kinx.y"
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
        case 499:
#line 1037 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 500:
#line 1038 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 501:
#line 1039 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 502:
#line 1043 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 503:
#line 1044 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 504:
#line 1048 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 507:
#line 1054 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 509:
#line 1059 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 510:
#line 1060 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 511:
#line 1061 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 512:
#line 1062 "src/kinx.y"
{ YYASP(2-2).obj->var_type = KX_SPR_T; yyval.obj = YYASP(2-2).obj; } break;
        case 513:
#line 1066 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 514:
#line 1067 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 515:
#line 1068 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strinfo.name) }; } break;
        case 516:
#line 1072 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 517:
#line 1073 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 518:
#line 1074 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 519:
#line 1078 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 520:
#line 1079 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 521:
#line 1083 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 522:
#line 1084 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 523:
#line 1088 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 526:
#line 1094 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 527:
#line 1095 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 528:
#line 1096 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 531:
#line 1102 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 532:
#line 1106 "src/kinx.y"
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
