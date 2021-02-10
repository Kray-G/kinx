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
#define ADDEQ 295
#define SUBEQ 296
#define MULEQ 297
#define DIVEQ 298
#define MODEQ 299
#define ANDEQ 300
#define OREQ 301
#define XOREQ 302
#define LANDEQ 303
#define LOREQ 304
#define LUNDEFEQ 305
#define SHLEQ 306
#define SHREQ 307
#define REGEQ 308
#define REGNE 309
#define NUL 310
#define TRUE 311
#define FALSE 312
#define AS 313
#define IMPORT 314
#define USING 315
#define DARROW 316
#define SQ 317
#define DQ 318
#define MLSTR 319
#define BINEND 320
#define DOTS2 321
#define DOTS3 322
#define REGPF 323
#define NAMESPACE 324
#define SYSNS 325
#define SYSRET_NV 326
#define CLASS 327
#define SYSCLASS 328
#define MODULE 329
#define SYSMODULE 330
#define NATIVE 331
#define FUNCTION 332
#define SYSFUNC 333
#define PUBLIC 334
#define PRIVATE 335
#define PROTECTED 336
#define COROUTINE 337
#define NAME 338
#define STR 339
#define SRCFILE 340
#define BIGINT 341
#define INT 342
#define TYPE 343
#define TYPEOF 344
#define LBBR 345
#define RBBR 346
#define LMBR 347
#define RMBR 348
#define DBL 349
#define BIN 350
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
#line 1109 "src/kinx.y"

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
    0,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  110,  112,  112,  112,  108,  101,  112,
   96,   97,  106,  105,   94,   93,   98,  107,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,   95,   92,
  103,   91,  104,  102,  111,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  100,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,   99,  112,  109,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  112,  112,  112,  112,    1,  112,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   57,   58,   59,   60,  112,  112,  112,
   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
  112
#line 165 "build/utility/kmyacc.c.parser"
};

#define YYBADCH 112
#define YYMAXLEX 351
#define YYTERMS 112
#define YYNONTERMS 123

static short yyaction[] = {
  814,  815,  816,  817,  818,  819,  820,  821,  822,  823,
  824,  825,  826,  828,  827,   37,    0,  829,  830,  831,
  840,  842,  841, 1049,  850,  851,  852,  854,  856,  114,
  323,  392,  100,  848,  849,  324,   79,   80,   81,   82,
   83,   84,   85,   86,   87,   88,   89,   90,   91, 1066,
   36,  162,  843,  844,  845,   37,  846,  847,  455, -391,
  810,  134,  135,  136,   37,  811,  838,   40,  839,   43,
  832,  833,  834,  835,  836,  837,  112,  812,  143,  144,
  145,  562,  813,  564,  563,  565,  431,  566,   93,  163,
  392,  858,  567,  568,  432,-32766,  569,  863,  864,  862,
  230,  853,  855,  857,  859,  860,  861,  935,  936,  937,
  938,  939,  940,  941,  942,  943,  944,  945,  946,  947,
   58,  948,  786,  787,  949,  950,  951,  959,  961,  960,
  603,  971,  972,  973,  975,  977,  137,  138,   37,   78,
  969,  970, -361,   17,    3,   94,    2,  570,  108, -361,
  132,  133,  571,  117,  573,  572,   46,  164,   25,  962,
  963,  964, 1066,  965,  966,  561,  552,    1,   37,  810,
  878,  560,   64,  957,  811,  958,  107,  111,  952,  953,
  954,  955,  956,  126, 1025,   47,  116,   26,  435,  967,
  968,  430,  115,  409,   49,  141,   29,   37,  979,   67,
   48,  410,   28,  240,  984,  985,  983,  142,  974,  976,
  978,  980,  981,  982,  168,  414,  369,  415,    9,  416,
  905,  313,  907,  908,  236,  237,  417,  105,  373,  106,
  374,  375,  160,  233,  234,  314,   52,   59,  301,  369,
  370,   14,  371,  369,  370,   14,  371,  122,  328,  372,
  110,  373,  102,  372,  101,  373,  102,  296,  634,  -76,
  446,  162,  239,  255,  297,   78,   98,  418,  419,  420,
 -106,  271,  932, -475,  803,  -77,   77, -106,  303,  304,
  376,  421,  378,  422,  380,  423,  272,  273,   33,   34,
   35,    2,  424,  108,  587,   96,  877,  425,  934,    1,
  578,   46,  107,   25,  507, -102,  139,  140,  238,   57,
  150,  151,  318,  901,  253,  902,  903,  904,  905,  906,
  907,  908,  909,  910,  911,  912,   37,  913,  190,  191,
  160,  915,  916,  925,  927,  926,  590,  326,  152,  153,
  114,  162,-32766,  402,-32766,-32766,  525, 1010,  476,  477,
-32766,  127,  146,  478,  115,  120,  128,  367,  123,  254,
  870,   39,   48,   43,   28,  418,  419,  420,   78,  441,
  932,   97,  296,   27,   77,  189,  256,  591,   36,  923,
  310,  924,  506,  917,  918,  919,  920,  921,  922,-32766,
  442,  636,  584,  635,  867,  425,  934,  309,  888,  877,
  297,  311,  588,  307,-32766,  107,  238,   57,-32766,-32766,
-32766,  312,  443,  407,-32766,  449,-32766,-32766,  508,  408,
-32766,-32766,  901,  504,  902,  903,  904,  905,  906,  907,
  908,  909,  910,  911,  912,  447,  913,-32766,  444,  160,
  915,  916,  925,  927,  926,  434,  807,  487,  510,  701,
  666,  512,  624,-32766,-32766, 1036,  686,  778,  809,   20,
    5,    4,    3,   37,   38,  255,   15,  872,  784,  783,
  585,    0,  494,    0,  418,  419,  420, 1052,  441,  932,
 1053,  865,  986,   77, 1034,  699,  664,  776,  923,  868,
  924,  622,  917,  918,  919,  920,  921,  922,-32766,  442,
   72,   66,   65,  294,  425,  934,  486,  662,   99,  290,
  480,  628,  129,-32766,  994,  238,   57,  993,  626,  621,
  637,  443,  627,  625,   73,-32766,-32766,   71,   70,-32766,
-32766,  901,   69,  902,  903,  904,  905,  906,  907,  908,
  909,  910,  911,  912,   68,  913,  551,  600,  160,  915,
  916,  925,  927,  926,  633,  623, -393,   16,  235,  109,
   60,   51,-32766,-32766,   41,  113,  222,    0, -397, -394,
 -392, -389,  603,  605, -381,   42,   53,   54,  719,  604,
  606,  535,  243,  418,  419,  420,  241,  441,  932,   55,
  124,  192,   77, -390,  238,    0,  206,  923,  214,  924,
  220,  917,  918,  919,  920,  921,  922,-32766,  442,  205,
  204,  203,   95,  425,  934,   92,  890,   76,  208,   75,
   74,  475,-32766,  448,  238,   57,  404,  403,  242,  207,
  443,  221,  219,  218,-32766,-32766,  217,  216,-32766,-32766,
  901,  215,  902,  903,  904,  905,  906,  907,  908,  909,
  910,  911,  912,  213,  913,  212,  211,  160,  915,  916,
  925,  927,  926,  210,  209,   50,  130,   18,   19,  704,
  802,-32766,-32766,  327,  514,  644, 1057, 1055,  702,  801,
  711,  618,  667, 1038,  779,  992,  866,  804,  987,  511,
  497,  362,  418,  419,  420,  361,  441,  932,  360,  359,
  358,   77,  351,  349,  348,  346,  923,  345,  924,  344,
  917,  918,  919,  920,  921,  922,-32766,  442,  342,  339,
  336,  335,  425,  934,  334,  333,  332,   22,   21,  869,
    0,-32766,    0,  238,   57,  131,  443,    0,    0,  443,
    0,    0,    0,-32766,-32766,    0,    0,-32766,-32766,  901,
    0,  902,  903,  904,  905,  906,  907,  908,  909,  910,
  911,  912,    0,  913,    0,    0,  160,  915,  916,  925,
  927,  926,    0,    0,    0,    0,    0,    0,    0,    0,
-32766,-32766,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  418,  419,  420,    0,  441,  932,    0,    0,    0,
   77,    0,    0,    0,    0,  923,    0,  924,    0,  917,
  918,  919,  920,  921,  922,-32766,  442,    0,    0,    0,
    0,  425,  934,    0,    0,    0,    0,    0,    0,    0,
-32766,    0,    0,   57,    0,    0,    0,    0,-32766,    0,
    0,    0,-32766,-32766,    0,    0,-32766,-32766,  168,  368,
  369,  370,   14,  371,    0,  300,    0,    0,  249,  250,
  372,  101,  373,  102,  374,  375,    0,  231,  232,  532,
   62,  103,  301,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  257,    0, -475,    0,    0,
    0,    0,  303,  304,  376,  377,  378,  379,  380,    0,
  258,  259,   30,   31,   32,    0,  382,    0,    0,    0,
    0,    0,    0,    1,  578,    0,    0,    0,    0, -102,
    0,    0,  238,    0,    0,    0,    0,    0,  253,  168,
  368,  369,  370,   14,  371,    0,  300,    0,    0,  249,
  250,  372,  101,  373,  102,  374,  375,    0,  231,  232,
  532,   62,  103,  301,    0,    0,    0,    0,    0,   -1,
  168,  368,  369,  370,   14,  371,    0,  300,    0,    0,
  249,  250,  372,  101,  373,  102,  374,  375,    0,  231,
  232,  532,   62,  103,  301,    0,  257,    0,    0,    0,
    0,    0,    0,  303,  304,  376,  377,  378,  379,  380,
    0,  258,  259,   30,   31,   32,    0,  382,    0,    0,
    0,    0,    0,    0,    1,    0,    0,  257,    0,    0,
 -102,    0,    0, -367,  303,  304,  376,  377,  378,  379,
  380,    0,  258,  259,   30,   31,   32,    0,  382,    0,
    0,    0,    0,    0,    0,    1,    0,    0,    0,    0,
    0, -102,  168,  368,  369,  370,   14,  371,    0,  300,
    0,    0,  249,  250,  372,  101,  373,  102,  374,  375,
    0,  231,  232,  532,   62,  103,  301,    0,    0,    0,
    0,    0,  168,  368,  369,  370,   14,  371,    0,  300,
    0,    0,  249,  250,  372,  101,  373,  102,  374,  375,
    0,  231,  232,  532,   62,  103,  301,    0,    0,  257,
    0,    0,    0,    0,    0,    0,  303,  304,  376,  377,
  378,  379,  380,    0,  258,  259,   30,   31,   32,    0,
  382,    0,    0,    0,    0,    0,    0,    1,  785,  257,
    0,    0,    0, -102,    0,    0,  303,  304,  376,  377,
  378,  379,  380,    0,  258,  259,   30,   31,   32,    0,
  382,    0,    0,    0,    0,    0,    0,    1,  583,    0,
    0,    0,    0, -102,  168,  368,  369,  370,   14,  371,
    0,  300,    0,    0,  249,  250,  372,  101,  373,  102,
  374,  375,    0,  231,  232,  532,   62,  103,  301,    0,
    0,    0,    0,  168,  368,  369,  370,   14,  371,    0,
  300,    0,    0,  249,  250,  372,  101,  373,  102,  374,
  375,    0,  231,  232,  532,   62,  103,  301,    0,    0,
    0,  257,    0,  121,    0,    0,    0,    0,  303,  304,
  376,  377,  378,  379,  380,    0,  258,  259,   30,   31,
   32,    0,  382,    0,    0,    0,    0,    0,    0,    1,
  257,    0,    0,    0,    0, -102,    0,  303,  304,  376,
  377,  378,  379,  380,    0,  258,  259,   30,   31,   32,
    0,  382,    0,    0,    0,    0,    0,    0,    1,  581,
    0,    0,    0,    0, -102,  168,  368,  369,  370,   14,
  371,    0,  300,    0,    0,  249,  250,  372,  101,  373,
  102,  374,  375,    0,  231,  232,  532,   62,  103,  301,
    0,    0,    0,    0,    0,  168,  368,  369,  370,   14,
  371,    0,  300,    0,    0,  249,  250,  372,  101,  373,
  102,  374,  375,    0,  231,  232,  532,   62,  103,  301,
    0,    0,  257,    0,    0,    0,    0,    0,    0,  303,
  304,  376,  377,  378,  379,  380,    0,  258,  259,   30,
   31,   32,    0,  382,    0,    0,    0,    0,    0,    0,
    1,  580,  257,    0,    0,    0, -102,    0,    0,  303,
  304,  376,  377,  378,  379,  380,    0,  258,  259,   30,
   31,   32,    0,  382,    0,    0,    0,    0,    0,    0,
    1,  579,    0,    0,    0,    0, -102,  168,  368,  369,
  370,   14,  371,    0,  300,    0,    0,  249,  250,  372,
  101,  373,  102,  374,  375,    0,  231,  232,  532,   62,
  103,  301,    0,    0,    0,    0,    0,  168,  368,  369,
  370,   14,  371,    0,  300,    0,    0,  249,  250,  372,
  101,  373,  102,  374,  375,    0,  231,  232,  532,   62,
  103,  301,    0,    0,  257,    0,    0,    0,    0,    0,
    0,  303,  304,  376,  377,  378,  379,  380,    0,  258,
  259,   30,   31,   32,    0,  382,    0,    0,    0,    0,
    0,    0,    1,  578,  257,    0,    0,    0, -102,    0,
    0,  303,  304,  376,  377,  378,  379,  380,    0,  258,
  259,   30,   31,   32,    0,  382,    0,    0,    0,    0,
    0,    0,    1,  582,    0,    0,    0,    0, -102,  168,
  368,  369,  370,   14,  371,    0,  300,    0,    0,  249,
  250,  372,  101,  373,  102,  374,  375,    0,  231,  232,
  532,   62,  103,  301,    0,    0,    0,    0,  168,  368,
  369,  370,   14,  371,    0,  300,    0,    0,  249,  250,
  372,  101,  373,  102,  374,  375,    0,  231,  232,  532,
   62,  103,  301,    0,    0,    0,  257,    0,  125,    0,
    0,    0,    0,  303,  304,  376,  377,  378,  379,  380,
    0,  258,  259,   30,   31,   32,    0,  382,    0,  161,
    0,    0,    0,    0,    1,  257,    0,    0,    0,    0,
 -102,    0,  303,  304,  376,  377,  378,  379,  380,    0,
  258,  259,   30,   31,   32,  104,  382,    0,    0,    0,
  159,    0,    0,    1,  708,  709,  710,    0,    0, -102,
    0,    0,    0,    0,  154,  155,    0,    0,    0,    0,
    0,    0,    0,  533,    0,    0,    0,    0,    0,  810,
    0,    0,  707,  705,  811,  791,  792,  793,-32766,  395,
  706,    0,    0,    0,    0,  302,   61,    0,    0,    0,
    0,    0,    0, 1010,  396,  397,    0,-32766,-32766,  381,
  810,    0,  794,  790,  788,  811,    0,   39,    0,   43,
    0,  789,    0,    0,  156,    0,    0,   56,    0,   23,
    0,    0,  252,    0,  305,    0,  157,  147,  534,    0,
  148,  149,   24,    0,    0,    0,-32766,-32766,-32766,    0,
    0,    0,-32766,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,-32766,    0,    0,
    0,    0,    0,    0,    0,-32766,    0,    0,    0,-32766,
-32766,    0,    0,-32766,-32766
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1815

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   86,    0,   19,   20,   21,
   22,   23,   24,   72,   26,   27,   28,   29,   30,  100,
   79,    2,   63,   35,   36,   84,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   51,   80,
   86,   16,   54,   55,   56,   86,   58,   59,   80,   95,
   79,   28,   29,   30,   86,   84,   68,   86,   70,   88,
   72,   73,   74,   75,   76,   77,   24,   79,  106,  107,
  108,    2,   84,    4,    5,    6,   88,    8,   91,   31,
    2,   93,   13,   14,   96,   14,   17,   99,  100,  101,
   20,  103,  104,  105,  106,  107,  108,    2,    3,    4,
    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   91,   16,   33,   34,   19,   20,   21,   22,   23,   24,
   95,   26,   27,   28,   29,   30,  103,  104,   86,   63,
   35,   36,   87,    3,   86,   63,   86,   68,   88,   94,
   26,   27,   73,   95,   75,   76,   96,   99,   98,   54,
   55,   56,   80,   58,   59,   86,   87,   86,   86,   79,
   94,   92,   92,   68,   84,   70,  100,   88,   73,   74,
   75,   76,   77,   38,   79,   96,   88,   98,    4,   84,
   85,   80,   88,   88,   96,   93,   98,   86,   93,   91,
   96,   96,   98,   95,   99,  100,  101,  105,  103,  104,
  105,  106,  107,  108,    1,    2,    3,    4,    5,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
   17,   18,   19,   20,   21,   22,   23,   24,   25,    3,
    4,    5,    6,    3,    4,    5,    6,  102,    3,   13,
   14,   15,   16,   13,   14,   15,   16,   79,   92,    7,
   94,   16,   57,   86,   79,   63,    7,   54,   55,   56,
   92,   58,   59,   60,   97,    7,   63,   92,   65,   66,
   67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
   77,   86,   79,   88,   83,    7,   94,   84,   85,   86,
   87,   96,  100,   98,   93,   92,   35,   36,   95,   96,
   52,   53,    9,    2,  101,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   86,   16,   62,   63,
   19,   20,   21,   22,   23,   24,   83,   10,   62,   63,
  100,   16,   14,   20,   33,   34,   93,   72,   73,   74,
   14,   31,   37,   78,   88,   60,   32,   60,   60,   63,
   61,   86,   96,   88,   98,   54,   55,   56,   63,   58,
   59,   63,   79,   98,   63,  100,  101,   83,   86,   68,
   79,   70,   80,   72,   73,   74,   75,   76,   77,   78,
   79,   79,   79,   79,   89,   84,   85,   79,   87,   94,
   79,   79,   83,   86,   93,  100,   95,   96,   72,   73,
   74,   79,  101,   79,   78,   80,  105,  106,   79,   79,
  109,  110,    2,   79,    4,    5,    6,    7,    8,    9,
   10,   11,   12,   13,   14,   79,   16,  101,   79,   19,
   20,   21,   22,   23,   24,   79,   85,   80,   80,   85,
   85,   88,   92,   33,   34,   85,   85,   85,   85,   97,
   86,   86,   86,   86,   86,   86,   97,   87,   87,   87,
   87,   -1,   88,   -1,   54,   55,   56,   89,   58,   59,
   89,   89,   89,   63,   89,   89,   89,   89,   68,   89,
   70,   92,   72,   73,   74,   75,   76,   77,   78,   79,
   91,   91,   91,   91,   84,   85,   91,   87,   91,   91,
   94,   92,   99,   93,   92,   95,   96,   92,   92,   92,
   92,  101,   92,   92,   92,  105,  106,   92,   92,  109,
  110,    2,   92,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   92,   16,   92,   92,   19,   20,
   21,   22,   23,   24,   92,   92,   95,   97,   94,   94,
   94,   94,   33,   34,   94,   94,   94,   -1,   95,   95,
   95,   95,   95,   95,   95,   95,   95,   95,   95,   95,
   95,   95,   95,   54,   55,   56,   95,   58,   59,   95,
   95,   95,   63,   95,   95,   -1,   96,   68,   96,   70,
   96,   72,   73,   74,   75,   76,   77,   78,   79,   96,
   96,   96,   96,   84,   85,   96,   87,   96,   96,   96,
   96,   96,   93,   96,   95,   96,   96,   96,   96,   96,
  101,   96,   96,   96,  105,  106,   96,   96,  109,  110,
    2,   96,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   96,   16,   96,   96,   19,   20,   21,
   22,   23,   24,   96,   96,   96,  100,   97,   97,   97,
   97,   33,   34,   97,   97,   97,   97,   97,   97,   97,
   97,   97,   97,   97,   97,   97,   97,   97,   97,   97,
   97,   97,   54,   55,   56,   97,   58,   59,   97,   97,
   97,   63,   97,   97,   97,   97,   68,   97,   70,   97,
   72,   73,   74,   75,   76,   77,   78,   79,   97,   97,
   97,   97,   84,   85,   97,   97,   97,   97,   97,  104,
   -1,   93,   -1,   95,   96,  101,  101,   -1,   -1,  101,
   -1,   -1,   -1,  105,  106,   -1,   -1,  109,  110,    2,
   -1,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   -1,   16,   -1,   -1,   19,   20,   21,   22,
   23,   24,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   33,   34,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   54,   55,   56,   -1,   58,   59,   -1,   -1,   -1,
   63,   -1,   -1,   -1,   -1,   68,   -1,   70,   -1,   72,
   73,   74,   75,   76,   77,   78,   79,   -1,   -1,   -1,
   -1,   84,   85,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   93,   -1,   -1,   96,   -1,   -1,   -1,   -1,  101,   -1,
   -1,   -1,  105,  106,   -1,   -1,  109,  110,    1,    2,
    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   17,   18,   -1,   20,   21,   22,
   23,   24,   25,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   58,   -1,   60,   -1,   -1,
   -1,   -1,   65,   66,   67,   68,   69,   70,   71,   -1,
   73,   74,   75,   76,   77,   -1,   79,   -1,   -1,   -1,
   -1,   -1,   -1,   86,   87,   -1,   -1,   -1,   -1,   92,
   -1,   -1,   95,   -1,   -1,   -1,   -1,   -1,  101,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   -1,   20,   21,
   22,   23,   24,   25,   -1,   -1,   -1,   -1,   -1,    0,
    1,    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   14,   15,   16,   17,   18,   -1,   20,
   21,   22,   23,   24,   25,   -1,   58,   -1,   -1,   -1,
   -1,   -1,   -1,   65,   66,   67,   68,   69,   70,   71,
   -1,   73,   74,   75,   76,   77,   -1,   79,   -1,   -1,
   -1,   -1,   -1,   -1,   86,   -1,   -1,   58,   -1,   -1,
   92,   -1,   -1,   95,   65,   66,   67,   68,   69,   70,
   71,   -1,   73,   74,   75,   76,   77,   -1,   79,   -1,
   -1,   -1,   -1,   -1,   -1,   86,   -1,   -1,   -1,   -1,
   -1,   92,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,   -1,
   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   17,   18,
   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,   58,
   -1,   -1,   -1,   -1,   -1,   -1,   65,   66,   67,   68,
   69,   70,   71,   -1,   73,   74,   75,   76,   77,   -1,
   79,   -1,   -1,   -1,   -1,   -1,   -1,   86,   87,   58,
   -1,   -1,   -1,   92,   -1,   -1,   65,   66,   67,   68,
   69,   70,   71,   -1,   73,   74,   75,   76,   77,   -1,
   79,   -1,   -1,   -1,   -1,   -1,   -1,   86,   87,   -1,
   -1,   -1,   -1,   92,    1,    2,    3,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   17,   18,   -1,   20,   21,   22,   23,   24,   25,   -1,
   -1,   -1,   -1,    1,    2,    3,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   16,   17,
   18,   -1,   20,   21,   22,   23,   24,   25,   -1,   -1,
   -1,   58,   -1,   60,   -1,   -1,   -1,   -1,   65,   66,
   67,   68,   69,   70,   71,   -1,   73,   74,   75,   76,
   77,   -1,   79,   -1,   -1,   -1,   -1,   -1,   -1,   86,
   58,   -1,   -1,   -1,   -1,   92,   -1,   65,   66,   67,
   68,   69,   70,   71,   -1,   73,   74,   75,   76,   77,
   -1,   79,   -1,   -1,   -1,   -1,   -1,   -1,   86,   87,
   -1,   -1,   -1,   -1,   92,    1,    2,    3,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   17,   18,   -1,   20,   21,   22,   23,   24,   25,
   -1,   -1,   -1,   -1,   -1,    1,    2,    3,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   17,   18,   -1,   20,   21,   22,   23,   24,   25,
   -1,   -1,   58,   -1,   -1,   -1,   -1,   -1,   -1,   65,
   66,   67,   68,   69,   70,   71,   -1,   73,   74,   75,
   76,   77,   -1,   79,   -1,   -1,   -1,   -1,   -1,   -1,
   86,   87,   58,   -1,   -1,   -1,   92,   -1,   -1,   65,
   66,   67,   68,   69,   70,   71,   -1,   73,   74,   75,
   76,   77,   -1,   79,   -1,   -1,   -1,   -1,   -1,   -1,
   86,   87,   -1,   -1,   -1,   -1,   92,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   -1,   -1,   -1,    1,    2,    3,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   17,   18,   -1,   20,   21,   22,   23,
   24,   25,   -1,   -1,   58,   -1,   -1,   -1,   -1,   -1,
   -1,   65,   66,   67,   68,   69,   70,   71,   -1,   73,
   74,   75,   76,   77,   -1,   79,   -1,   -1,   -1,   -1,
   -1,   -1,   86,   87,   58,   -1,   -1,   -1,   92,   -1,
   -1,   65,   66,   67,   68,   69,   70,   71,   -1,   73,
   74,   75,   76,   77,   -1,   79,   -1,   -1,   -1,   -1,
   -1,   -1,   86,   87,   -1,   -1,   -1,   -1,   92,    1,
    2,    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   17,   18,   -1,   20,   21,
   22,   23,   24,   25,   -1,   -1,   -1,   -1,    1,    2,
    3,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   17,   18,   -1,   20,   21,   22,
   23,   24,   25,   -1,   -1,   -1,   58,   -1,   60,   -1,
   -1,   -1,   -1,   65,   66,   67,   68,   69,   70,   71,
   -1,   73,   74,   75,   76,   77,   -1,   79,   -1,   19,
   -1,   -1,   -1,   -1,   86,   58,   -1,   -1,   -1,   -1,
   92,   -1,   65,   66,   67,   68,   69,   70,   71,   -1,
   73,   74,   75,   76,   77,   14,   79,   -1,   -1,   -1,
   19,   -1,   -1,   86,   54,   55,   56,   -1,   -1,   92,
   -1,   -1,   -1,   -1,   33,   34,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   42,   -1,   -1,   -1,   -1,   -1,   79,
   -1,   -1,   82,   83,   84,   54,   55,   56,   14,   58,
   90,   -1,   -1,   -1,   -1,   64,   96,   -1,   -1,   -1,
   -1,   -1,   -1,   72,   73,   74,   -1,   33,   34,   78,
   79,   -1,   81,   82,   83,   84,   -1,   86,   -1,   88,
   -1,   90,   -1,   -1,   93,   -1,   -1,   96,   -1,   98,
   -1,   -1,  101,   -1,  103,   -1,  105,  106,  107,   -1,
  109,  110,  111,   -1,   -1,   -1,   72,   73,   74,   -1,
   -1,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  101,   -1,   -1,   -1,  105,
  106,   -1,   -1,  109,  110
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1597,  213,  857, 1446, 1324, 1232, 1203, 1568,  989,  958,
 1354, 1476, 1111, 1081, 1597, 1597, 1597, 1597, 1597, 1597,
 1597, 1597, 1597,  361,  373,  372,  365,  371,  364,  370,
  105,  105,  105,  105,  105,  105,  311,  420,  529,  638,
  747,  747,  240,  305,  202,   76,   82,   82,   82,   82,
   80,  -31,  -36,  -71,  -71,  -71,  111,  -22,   52,  498,
  308,  302,  292,  292,  292,  377,  377,  377,  292,  292,
  292,  292,  377,  292, 1661, 1661, 1661,  377,  377,  377,
  377,  377,  377,  377,  377,  377,  377,  377,  377,  377,
  377,  377, 1661,  377,  377, 1661, 1661,  377, 1661,  377,
  377, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,  378,
 1661, 1661, 1661, 1661, 1661, 1661, 1661,   81,   81,   81,
   81,   81,  328,  328,  328,  328,  336,  336,  336,  336,
  336,  336,  336,  336,  336,  336,  336,  336,  336,  336,
  336,  336,  336,  336,  336,  336,  336,  336,  336,  336,
  336,  336,  336,  336, 1704, 1704, 1704, 1704, 1704, 1704,
 1704, 1704,  275,  275,  275,   35,   29,  325,   79,  478,
  573,  398,  477,  397,  572,  396,  395,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3, 1630,
 1630, 1630,  236,  205,  177,  266,   60,   60,   60,   60,
  379,  379,  379,  296,  296,  296,  296,  296,  296,  296,
  296,  296,  296,  296,  296,  296,  296,  296,  296,  296,
  296,  296,  296,   58,  104,  104,  104,   33,   33,   33,
  -19,  -19,  -19,  -19,  -19,  -19,  178,  185,  -49,  -49,
  -49,  -49,  -49,  -49,   98,  -28,  -28,  -28,  252,  293,
  321,  245,  500,  502,   90,  635,  504,  323,  334,  340,
  145,  124,  271,  102,  258,  276,  366,  108,  425,  422,
  166,  323,  334,  340,   55,  369,  460,  452,  576,  124,
  271,  271,  271,  271,  271,  102,  102,  258,  440,  578,
  211,  577,  570,  571,  253,   88,   88,   88,   88,   88,
  376,  314,  530,  313,  313,  625,  303,  359,  530,  522,
  522,  376,  376,  376,  476,  470,  376,  530,  525,  327,
  416,  486,  486,  384,  384,  376,  376,  376,  483,  532,
  376,  376,  499,  499,  499,  499,  487,  376,  483,  499,
  532,  376,  499,  376,  499,  499,  499,  376,  499,  487,
  376,  499,  376,  376,  376,  376,  376,  376,  499,  499,
  499,  499,  487,  376,  376,  376,  376,  376,  524,  485,
  523,  569,  521,  484,  317,  431,  430,  318,  301,  322,
  332,  513,  496,   16,  428,  320,  324,  413,  566,  634,
  315,  184,  519,  427,  463,  531,  515,  514,  533,  411,
  410,  465,  356,  527,  335,  375,  374,  568,  567,  393,
  591,  560,  559,  557,  524,  523,  569,  521,  475,  461,
  474,  318,  322,  479,  480,  473,  481,  298,  400,  466,
  590,  392,  589,  419,  545,  516,  288,  268,  252,  399,
  360,  531,  482,  541,  418,  462,  312,  415,  367,  588,
  491,  629,  472,  628,  627,  593,  380,  466,  624,  299,
  320,  495,  324,  413,  566,  634,  315,  315,  315,  587,
  467,  623,  259,  411,  436,  344,  540,  537,  536,  535,
  339,  383,  417,  417,  417,  426,  368,  592,  586,  622,
  621,  612,  610,  608,  388,  363,  363,  494,  607,  382,
  585,  606,  140,  435,  584,  605,  583,  319,  412,  409,
  454,  582,  391,  295,  455,  432,  362,  603,  602,  601,
  598,  594,  581,  580,  631,  294,  417,  630,  297,  579,
  381,  381,    0,    0,    0,    0, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,   -2,
   -2,   -2,   -2,   -2,   -2,   -2,    0,    0,    0,    0,
    0,    0, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
    0,    0,    0, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,    0, 1661,
 1661,    0,    0, 1661,    0, 1661, 1661,    0,    0,    0,
    0,    0,    0,    0,    0, 1661,    0,    0,    0,    0,
    0,    0,    0, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661,
 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1661, 1630, 1630,
 1630,   -3,   -3,   -3,    0,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   89,
   89,   89,   89,   89,   89,   89,   89,   89,   89,  -19,
  -19,  -19,  -19,  -19,  -19,  -19,  -19,  -19,  -19,  -19,
  -19,  -19,  -19,  -19,  -19,  -19,  -19,  -19,  -19,   88,
   89,   89,   89,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   88,   88,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  108,   88,   88,    0,  499,  499,
    0,  499,  499,  531,  515,  514,    0,    0,    0,    0,
    0,    0,  533,    0,  464,  464,    0,  531,  515,  514,
    0,  471,  471,  471,  471,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  464,  471,    0,  471,  471,  471
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 294

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  384,  385,  386,  475,  475,  475,  475,
32767,  338,32767,32767,32767,32767,  522,  522,  522,  522,
32767,32767,  104,32767,32767,32767,32767,32767,32767,   94,
  346,32767,  104,  104,  104,32767,32767,32767,  104,  104,
  104,  104,32767,  104,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   94,32767,  376,  377,32767,32767,32767,
32767,32767,   96,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  224,  226,32767,32767,32767,32767,32767,32767,
  378,32767,32767,32767,32767,32767,  106,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  351,   93,  343,
  349,  344,  528,  353,  362,  347,   95,  350,  363,32767,
  151,  153,32767,  236,32767,  144,  234,  235,  232,  231,
  125,  529,  364,  503,  503,  503,  503,  503,  503,  503,
  503,  503,  503,  503,  503,  503,  503,  503,  503,  503,
  503,  503,32767,32767,  145,  152,  154,  200,  201,  202,
32767,32767,32767,  379,  380,32767,  373,  374,32767,32767,
32767,32767,32767,32767,  520,  212,  214,  213,  461,  106,
  106,  177,  475,  475,32767,  475,  475,32767,32767,32767,
  187,  198,  203,  209,  219,  221,32767,  461,32767,32767,
32767,  395,  382,  383,  228,32767,32767,32767,32767,  199,
  205,  207,  208,  204,  206,  210,  211,  220,32767,32767,
32767,32767,32767,32767,32767,  106,  106,  106,  106,  106,
32767,32767,32767,32767,32767,  335,   79,32767,32767,  501,
  501,32767,32767,  370,  531,  337,32767,32767,   81,   83,
  337,  495,  495,  515,  515,32767,32767,32767,  182,  518,
32767,32767,  475,  475,  475,  475,  477,32767,  182,  475,
  518,32767,  475,32767,  475,  475,  475,32767,  475,  477,
32767,  475,32767,32767,32767,32767,32767,32767,  475,  475,
  475,  475,  477,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  274,32767,32767,  188,  190,  192,  194,  196,
  215,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  105,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  365,  366,  368,  375,  255,  256,
  257,  387,  388,  474,  274,  275,32767,32767,32767,  339,
32767,32767,32767,32767,32767,32767,32767,  261,  259,32767,
32767,  395,  274,32767,   50,32767,32767,32767,32767,32767,
  507,32767,  504,32767,32767,32767,32767,  340,32767,32767,
  189,32767,  191,  193,  195,  197,  216,  217,  218,32767,
  523,32767,32767,   77,32767,32767,32767,32767,32767,32767,
  338,32767,  465,  466,  463,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  514,  512,  268,32767,32767,
32767,32767,   61,32767,32767,32767,32767,32767,   53,  462,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  464,32767,32767,32767,
  483,32767,  531,  455,  455,  531
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  184,  179,  179,  179,  182,  182,  182,  182,  180,  182,
  177,  184,  184,  184,  170,  170,  438,  178,  185,  174,
  177,  177,  177,  500,  522,  529,  177,  177,  177,  177,
  892,  177,  180,  180,  180,  717,  717,  717, 1020, 1020,
  716,  716,  716, 1019,  530,  461,  499,  721,  531,  989,
  180,  483,  484,  180,  180,  459,  180,  526,  988,  165,
  169,  178,  167,  165,  169,  181,  171,  183,  172,  173,
  186,  187,  188,  175,  176,  266,  266,  266,  266,  266,
  266,  266,  266,  266,  266,  266,  266,  266,  266,  266,
  266,  266,  266,  266,  266,  266,  266,  266,  714,  675,
  275,  276,  278,  280,  281,  282,  283,  284,  684,  684,
  684,  781,  596,  457,  781,  781,  781,  781,  289,  663,
  698,  291,  292,  274,  293,  663,  663,  663,  703,  703,
  703,  769,  765,  766,  758,  759,  761,  763,  437,  782,
  668,  717,  782,  782,  782,  782,  668,  668,  668,  698,
  698,  698,  466,  467,  468,  703,  703,  703,  897,  897,
  897,  897,  897,  897,  412,  413, 1062,  412,  413,  450,
  450,  450,  450,  450,  450,  450,  450,  450,  450,  450,
  450,  450,  450,  450,  450,  450,  450,  450,  450,  773,
  329,  340,  523, 1014,  538,  460,  248,  267,  267,  267,
  267,  267,  539,  391,  541,  541,  541,  541,  391,  502,
  599,  598,  610,  611,  609,  608,  607,  462,  306,  357,
 1047,  808,  777,  665,  685,  700, 1035,  228,  229, 1029,
 1030,  306,  366,  895, 1021,  893,  463,  479,  479,  479,
  224,  225,  226,  616,  620,  601,  285,  286, 1027, 1028,
  682,  682,  682,  465,  288,  696,  269,  464,  269, 1015,
  279, 1016,  596,  678,  677, 1017,  246,  247, 1018, 1042,
 1007, 1008, 1022, 1023, 1024, 1009,   11,   12,   13,   13,
  287,  691,  692,  693,  694,  695,  683,  683,  683,  674,
  338, 1045, 1045, 1045, 1045, 1045, 1045, 1045, 1045, 1045,
 1045, 1045, 1045, 1045, 1045, 1045, 1045, 1045, 1045, 1045,
 1045,  196,  197,  198,  199,  472,  996,  406,  473,  399,
  399,  399,  399,  399,  672,  322,  481, 1046, 1046, 1046,
 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1046,
 1046, 1046, 1046, 1046, 1046, 1046, 1046, 1033,  805,  805,
  712,  331,  496,  660,  400,  400,  400,  400,  400,  400,
  660,  660,  660,  119,  316,  316,  639,  660,  337,  317,
 1044,  158,  660,  660,  660,  660,  660,  660,  660,  660,
  660,  660,  660,  660,  660,  660,  660,  646,  660,  660,
    0,    0,  660,    0,  660,  660,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  896,  881,  649,  650,
  651,  652,  653,  654,  655,  656,  657,  658,  659,  647,
  648,    0,  646, 1061,    0,    0,  884,  202, 1004, 1063,
    0,  201,  201,  201,  201,    0,  201,  394,  202,  202,
  202,  194,  194,    0,  341,  343,  347,  513,    0,    0,
  394,  352,    0,    0,  353,    0,  354,  355,  356,    0,
    6,    0,    0,    7,    0,    0,    0,    0,    0,    0,
  363,  364,  365,  528,  453,  454,  458,  471,  488,  489,
  490,  491,  492,  493,  498,  501,  505,  517,  518,  519,
  520,  521,    0,    0,    0,  433,  439,  440,  445,  485,
  299,  474,    0,    0,    0,  503,  515,  516,  524,    0,
  527
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 511

static char yygcheck[] = {
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   75,   37,   37,   37,
   37,   37,   37,   99,   99,   99,   37,   37,   37,   37,
   73,   37,   37,   37,   37,    7,    7,    7,    7,    7,
   41,   41,   41,   41,   41,   41,   41,   41,   41,   66,
   37,   82,   82,   37,   37,   67,   37,   82,   66,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,  117,  117,
   70,   70,   70,   51,   51,   51,   51,   51,   98,   98,
   98,    7,   35,   68,    7,    7,    7,    7,   70,   60,
   60,   70,   70,   57,   70,   60,   60,   60,   75,   75,
   75,   56,   56,   56,   56,   56,   56,   56,   63,   98,
   98,    7,   98,   98,   98,   98,   98,   98,   98,   60,
   60,   60,   54,   54,   54,   75,   75,   75,   57,   57,
   57,   57,   57,   57,   77,   77,  101,   77,   77,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,  104,
  104,  104,  104,  104,    4,   44,   75,   75,   75,   75,
   75,   75,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,   45,    7,  103,
   75,   59,   59,   59,   59,   59,   59,   50,   50,    7,
    7,    7,  103,   74,    7,   74,   46,   83,   83,   83,
  113,  113,  113,    7,    7,    7,   52,   52,    7,    7,
   63,   63,   63,   48,   80,    7,   80,   47,   80,    7,
   49,    7,   35,  112,  112,    7,   53,   53,    7,   96,
    7,    7,    7,    7,    7,    7,    3,    3,    3,    3,
   55,    7,    7,    7,    7,    7,   64,   64,   64,  118,
   32,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   58,   58,   58,   58,   19,   81,    9,   63,   63,
   63,   63,   63,   63,  110,   92,  119,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   61,   61,   61,
   61,   90,  105,  108,   64,   64,   64,   64,   64,   64,
  108,  108,  108,  120,  102,  102,   31,  108,  102,  122,
  106,  107,  108,  108,  108,  108,  108,  108,  108,  108,
  108,  108,  108,  108,  108,  108,  108,   38,  108,  108,
   -1,   -1,  108,   -1,  108,  108,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   38,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   -1,   38,   38,   -1,   -1,   38,   39,   38,   38,
   -1,   39,   39,   39,   39,   -1,   39,   31,   39,   39,
   39,   39,   39,   -1,  102,  102,  102,  102,   -1,   -1,
   31,  102,   -1,   -1,  102,   -1,  102,  102,  102,   -1,
  102,   -1,   -1,  102,   -1,   -1,   -1,   -1,   -1,   -1,
  102,  102,  102,  102,   94,   94,   94,   94,   94,   94,
   94,   94,   94,   94,   94,   94,   94,   94,   94,   94,
   94,   94,   -1,   -1,   -1,   31,   31,   31,   31,   31,
   40,   40,   -1,   -1,   -1,   40,   40,   40,   40,   -1,
   40
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  272,  194,    0,    0,  -82,    0,   13,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   85,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  200,   67,    0,    0,   70,    0,  -42,  329,  385,
  437,  -77,    0,    0,   69,   90,  108,  128,  123,  129,
   95,  -31,  107,  125,    9,  134,  -16,  122,  157,  197,
  -75,  189,    0,   88,  124,    0, -259,   11,   68,    0,
   26,    0,    0,  -11,  180,  -34,    0,  133,    0,    0,
   24,   81,  -15,   75,    0,    0,    0,    0,    0,    0,
   29,    0,   15,    0,  270,    0,   47,    0,  -54,  -24,
    0,  115,  112, -130,  -50,   28,   30, -164,  295,    0,
   73,    0,  100,   51,    0,    0,    0,  -20,   66,    6,
   25,    0, -165
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  383,    8,   10,  540,  543,  542,  544,  545,  405,
  546,  320,  558,  547,  574,  575,  576,  602,  577,  436,
  548,  319,  325,  614,  553,  554,  295,  555,  556,  270,
  557,  393,  643,  559,  549,  550,  384,  166, 1003,  200,
  298,  669,  720,  260,  385,  386,  387,  388,  389,  261,
  227,  262,  263,  245,  390,  264,  265,  764,  193,  806,
  775,  774,  796,  797,  798,  799,  990,  428,  429,   45,
  277,  401,  315,  891,  894,  795,  426,  411, 1026,  592,
  268,  995,  482,  398,  593, 1005,  722, 1006,  594,  595,
  330,  244,  321, 1032,  451,  452, 1041,  780,  800,  469,
  470, 1060,  427,  350, 1012,  495,  509,   63,  645,  251,
  671,  223,  676,  195,  679,  697,  670,  673,  715,  456,
  118,   44,  308
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
  117,  118,  120,  120,   41,   41,   42,   42,   43,   43,
   44,   44,   45,   45,   46,   46,   47,   47,   48,   48,
   49,   49,   49,   50,   50,   50,   50,   50,   50,   51,
   51,   51,   52,   52,   52,   53,   53,   53,   53,   54,
   54,   55,   55,   55,   55,   55,   55,   55,   56,   56,
   56,   56,   56,   56,   56,   56,   57,   57,   58,   58,
   58,   58,   58,   58,   58,   97,   97,   98,   98,   98,
   60,   60,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   75,   75,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   63,   63,   62,   62,  121,   64,  119,  119,   67,
   67,   69,   69,   68,   68,   68,   68,   68,   68,   70,
   70,   71,   71,   71,   71,   72,   72,   73,   73,   73,
   73,   73,   74,   74,   74,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   65,   65,   65,  122,   66,   79,   79,   80,
   80,   81,   81,   81,   81,   81,   81,   82,   82,   84,
   84,   85,   85,   85,   83,  102,  102,  103,  103,   86,
   86,   86,   86,   86,   86,   86,   87,   87,   87,   77,
   77,   88,   88,   89,   89,   90,   90,   91,   91,   91,
   91,   92,   92,   94,   94,   95,   95,   96,   96,   96,
   96,   96,  104,  104,  104,  105,  105,  105,  106,  106,
   93,   93,   99,   99,  100,  100,  100,  100,  101,  101,
  101,  107
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
    1,    1,    0,    1,    1,    5,    1,    1,    1,    3,
    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
    1,    3,    3,    1,    3,    3,    3,    3,    3,    1,
    3,    3,    1,    3,    3,    1,    3,    3,    3,    1,
    3,    1,    3,    3,    2,    3,    2,    3,    1,    2,
    2,    2,    2,    2,    2,    2,    1,    3,    1,    2,
    4,    3,    3,    4,    2,    1,    1,    5,    9,    8,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    6,    3,    3,    3,    2,
    2,    2,    2,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    2,
    2,    2,    3,    2,    4,    0,    4,    0,    1,    1,
    2,    1,    2,    1,    2,    2,    2,    3,    4,    1,
    3,    1,    2,    3,    4,    1,    3,    5,    3,    3,
    2,    1,    1,    2,    1,    1,    1,    1,    1,    1,
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
    3,    0,    3,    0,    1,    1,    3,    1,    4,    1,
    1,    2,    2,    1,    2,    0,    2,    3,    0,    3,
    0,    3,    0,    1,    1,    2,    3,    4,    1,    1,
    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 953
#define YYNLSTATES 536
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
        case 185:
#line 540 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 189:
#line 550 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 191:
#line 555 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 193:
#line 560 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 565 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 197:
#line 570 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 199:
#line 575 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 580 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 581 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 205:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 206:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 207:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 208:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 210:
#line 595 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 211:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 213:
#line 601 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 214:
#line 602 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 216:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 217:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 218:
#line 609 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 220:
#line 614 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 222:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 223:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 224:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 225:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 226:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 227:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 229:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 230:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 231:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 232:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 233:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 234:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 235:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 237:
#line 640 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 239:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 240:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 241:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 242:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 243:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 244:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 245:
#line 654 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 247:
#line 659 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-5).arraytype, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(4-5).obj, NULL, NULL), NULL); } break;
        case 248:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-9).arraytype, NULL, YYASP(4-9).obj, kx_gen_stmt_object(KXST_RET, YYASP(8-9).obj, NULL, NULL), NULL); } break;
        case 249:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-8).arraytype, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 250:
#line 665 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 251:
#line 666 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 252:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 253:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 254:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 255:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 256:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 257:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 258:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 265:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 266:
#line 684 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 267:
#line 685 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 268:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 269:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 270:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 271:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 272:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 273:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 274:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_UNKNOWN_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2); } break;
        case 275:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(kx_gen_typestr_object(YYASP(1-1).intval), KX_UNKNOWN_T); } break;
        case 276:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object_pos(YYASP(1-1).strinfo); } break;
        case 277:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 278:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 279:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 280:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 281:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 282:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 283:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 284:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 285:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 286:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 287:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 288:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 289:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 290:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 291:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 292:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 293:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 294:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 295:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 296:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 297:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 298:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 299:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 300:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 301:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 302:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 303:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 304:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 305:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 306:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 307:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 308:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 309:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 310:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 311:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 312:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 313:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 314:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 315:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 316:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 317:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 318:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 319:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 320:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 321:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 322:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 323:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 324:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 325:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 326:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 327:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 328:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 329:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 330:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 331:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 332:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 333:
#line 763 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 334:
#line 764 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 335:
#line 768 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 336:
#line 772 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 337:
#line 776 "src/kinx.y"
{} break;
        case 339:
#line 781 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 340:
#line 782 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 341:
#line 786 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 342:
#line 787 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 344:
#line 792 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 345:
#line 793 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 346:
#line 794 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 347:
#line 795 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 348:
#line 796 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 350:
#line 801 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 352:
#line 806 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 353:
#line 807 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 354:
#line 808 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 356:
#line 813 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 357:
#line 817 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 358:
#line 818 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 359:
#line 819 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 360:
#line 820 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 361:
#line 821 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 363:
#line 826 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 365:
#line 831 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 366:
#line 832 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 367:
#line 833 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 368:
#line 834 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 369:
#line 835 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 370:
#line 836 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 371:
#line 837 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 372:
#line 838 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 373:
#line 839 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 374:
#line 840 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 375:
#line 841 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 376:
#line 842 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 377:
#line 843 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 378:
#line 844 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 379:
#line 845 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 380:
#line 846 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 381:
#line 847 "src/kinx.y"
{ yyval.strval = "native"; } break;
        case 382:
#line 848 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 383:
#line 849 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 384:
#line 850 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 385:
#line 851 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 386:
#line 852 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 387:
#line 853 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 388:
#line 854 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 389:
#line 855 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 390:
#line 856 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 391:
#line 857 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 392:
#line 858 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 393:
#line 859 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 394:
#line 860 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 395:
#line 861 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 396:
#line 862 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 397:
#line 863 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 398:
#line 864 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 399:
#line 868 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 400:
#line 869 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 401:
#line 870 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 402:
#line 871 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 403:
#line 872 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 404:
#line 873 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 405:
#line 874 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 406:
#line 875 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 407:
#line 876 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 408:
#line 877 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 409:
#line 878 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 410:
#line 879 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 411:
#line 880 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 412:
#line 881 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 413:
#line 882 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 414:
#line 883 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 415:
#line 884 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 416:
#line 885 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 417:
#line 886 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 418:
#line 887 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 419:
#line 888 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 420:
#line 889 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 421:
#line 890 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 422:
#line 891 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 423:
#line 892 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 424:
#line 893 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 425:
#line 894 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 426:
#line 895 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 427:
#line 896 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 428:
#line 897 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 429:
#line 898 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 430:
#line 899 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 431:
#line 900 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 432:
#line 901 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 433:
#line 902 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 434:
#line 903 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 435:
#line 904 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 436:
#line 905 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 437:
#line 906 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 438:
#line 907 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 439:
#line 908 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 440:
#line 909 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 441:
#line 910 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 442:
#line 911 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 443:
#line 912 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 444:
#line 913 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 445:
#line 914 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 446:
#line 915 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 447:
#line 916 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 448:
#line 917 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 449:
#line 918 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 450:
#line 919 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 451:
#line 920 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 452:
#line 924 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 453:
#line 925 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 454:
#line 926 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 455:
#line 930 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 456:
#line 934 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 457:
#line 938 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 458:
#line 939 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 460:
#line 944 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 461:
#line 948 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-1).obj, NULL); } break;
        case 462:
#line 949 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 463:
#line 950 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 464:
#line 951 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).obj, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 465:
#line 952 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 466:
#line 953 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 468:
#line 958 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 469:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 470:
#line 963 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 471:
#line 967 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 472:
#line 968 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 473:
#line 969 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, 0, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 474:
#line 973 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 475:
#line 977 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_UNKNOWN_T }; } break;
        case 476:
#line 978 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 477:
#line 982 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 478:
#line 983 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 479:
#line 987 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 480:
#line 988 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 481:
#line 989 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 482:
#line 990 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 483:
#line 991 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-7).obj, NULL, NULL), NULL); } break;
        case 484:
#line 992 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 485:
#line 993 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 486:
#line 997 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 487:
#line 998 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 488:
#line 999 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 489:
#line 1003 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strinfo.name; } break;
        case 491:
#line 1008 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 492:
#line 1009 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 493:
#line 1013 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 494:
#line 1014 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 495:
#line 1018 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 496:
#line 1020 "src/kinx.y"
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
        case 498:
#line 1036 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 499:
#line 1037 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 500:
#line 1038 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 501:
#line 1042 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 502:
#line 1043 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 503:
#line 1047 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 506:
#line 1053 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 508:
#line 1058 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 509:
#line 1059 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 510:
#line 1060 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 511:
#line 1061 "src/kinx.y"
{ YYASP(2-2).obj->var_type = KX_SPR_T; yyval.obj = YYASP(2-2).obj; } break;
        case 512:
#line 1065 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 513:
#line 1066 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 514:
#line 1067 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strinfo.name) }; } break;
        case 515:
#line 1071 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 516:
#line 1072 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 517:
#line 1073 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 518:
#line 1077 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 519:
#line 1078 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 520:
#line 1082 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 521:
#line 1083 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 522:
#line 1087 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 525:
#line 1093 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 526:
#line 1094 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 527:
#line 1095 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 530:
#line 1101 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 531:
#line 1105 "src/kinx.y"
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
