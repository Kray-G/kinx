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
#line 1106 "src/kinx.y"

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
  "CatchStatement_Opt : CATCH CatchVariable BlockStatement",
  "CatchVariable : /* empty */",
  "CatchVariable : '(' NAME ')'",
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
    0,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  109,  111,  111,  111,  107,  100,  111,
   95,   96,  105,  104,   93,   92,   97,  106,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,   94,   91,
  102,   90,  103,  101,  110,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,   99,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,   98,  111,  108,  111,  111,  111,
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
#define YYNONTERMS 123

static short yyaction[] = {
  803,  804,  805,  806,  807,  808,  809,  810,  811,  812,
  813,  814,  815,  817,  816,    0,  818,  819,  820,  829,
  831,  830,  224,  839,  840,  841,  843,  845,  185,  186,
   67,  385,  837,  838,  235,   79,   80,   81,   82,   83,
   84,   85,   86,   87,   88,   89,   90,   91,  364,   14,
  365,  832,  833,  834,  112,  835,  836,  366,  799,  364,
   14,  365,   48,  800,   28,  827,  109,  828,  366,  821,
  822,  823,  824,  825,  826,   37,  801,-32766,  159,  160,
  555,  802,  557,  556,  558,  423,  559,   93,  385,  111,
  847,  560,  561,  424,   64,  562,  852,  853,  851,   17,
  842,  844,  846,  848,  849,  850,  924,  925,  926,  927,
  928,  929,  930,  931,  932,  933,  934,  935,  936,   58,
  937,  427,  938,  939,  940,  948,  950,  949,   37,  960,
  961,  962,  964,  966,    3,  775,  776,  799,  958,  959,
   37,  113,  800,  114,   40,  563,   43,  161,    1,   49,
  564,   29,  566,  565,  111,   78,  595,  951,  952,  953,
  138,  954,  955,  554,  545,  580,  131,  132,  133,  553,
   98,  946,  139,  947,  321,  499,  941,  942,  943,  944,
  945,-32766, 1014,    2,  323,  106,  867,  956,  957,   96,
  108,  402,  105,   46,  123,   25,  968,  159,   47,  403,
   26,  -74,  973,  974,  972,  -75,  963,  965,  967,  969,
  970,  971,  165,  407,  891,  408,    9,  409,  895,  308,
  897,  898,  231,  232,  410,  104,  367,  903,  368,  157,
  228,  229,  309,   52,   59,  296, 1038,   94,-32766,-32766,
-32766,  134,  135,  318,-32766,  112,  250,   36,  319,  140,
  141,  142,  313,   48, 1055,   28, -388,  792,  119,  234,
   37,  291,   78,-32766,  411,  412,  413,-32766,  266,  921,
 -472,  395,  583,   77, -103,  298,  299,  369,  414,  371,
  415,  373,  517,  267,  268,   33,   34,   35,    2,  416,
  106,  292,  159,  866,  417,  923,    1,  571,   46,  105,
   25, -358,  -99,  422, -103,  233,   57,  124, -358,   37,
  125,  248,  890,  891,  892,  893,  894,  895,  896,  897,
  898,  899,  900,  901,  902,  143,  903,  100,  157,  905,
  906,  914,  916,  915,  447,  623,  291,  438,  129,  130,
   37,  117,-32766,-32766, 1055,  999,  468,  469,  136,  137,
   37,  470,  147,  148,  149,  150,  362,  120,  249,   39,
  859,   43,  304,  411,  412,  413,   78,  433,  921,   97,
  306,   27,   77,  184,  251,  767,  581,  912,  479,  913,
  305,-32766,  907,  908,  909,  910,  911,-32766,  434,  625,
  577,  584,  856,  417,  923,  292,  651,  866,  624,  307,
  400,  401,-32766,  105,  233,   57,  500,  496,  439,  436,
  435,  426,   38,  502,-32766,-32766,  498,  441,-32766,-32766,
  890,  891,  892,  893,  894,  895,  896,  897,  898,  899,
  900,  901,  902,  796,  903,  798,  157,  905,  906,  914,
  916,  915,  675, 1025,  690,  655,   72,   36,  250,  302,
-32766,-32766,    5,    4,    3,   37,   65,  578,  772,  861,
  773,   15,  504,  486,    0, 1041,  653, 1023,  854,  975,
  857,  411,  412,  413, 1042,  433,  921,  688,  765,  614,
   77,  289,  478,   99,  285,  912,   66,  913,  612,-32766,
  907,  908,  909,  910,  911,-32766,  434,  622,  983,  982,
  613,  417,  923,  611,  877,  626,  616,   73,   71,  633,
-32766,   70,  233,   57,   69,   68,  593,  544,  435,  615,
  617, -394,-32766,-32766,  110,  472,-32766,-32766,  890,  891,
  892,  893,  894,  895,  896,  897,  898,  899,  900,  901,
  902,  230,  903,  107,  157,  905,  906,  914,  916,  915,
   60,   51,   41,  216,  126, -391, -390, -389,-32766,-32766,
 -386,   42,   53,   54,   55,  708,  596,  527,  238,  236,
  121,  227,  233, -387,    0,  200,  208,  214,  201,  411,
  412,  413,  198,  433,  921,  197,   95,   92,   77,   76,
   75,   74,  199,  912,  467,  913,  440,-32766,  907,  908,
  909,  910,  911,-32766,  434,  397,  396,  237,  202,  417,
  923,  215,  879,  213,  212,  211,  210,  209,-32766,  207,
  233,   57,  206,  205,  204,  203,  435,   50,  858,   16,
-32766,-32766,   18,   19,-32766,-32766,  890,  891,  892,  893,
  894,  895,  896,  897,  898,  899,  900,  901,  902,  322,
  903,  506,  157,  905,  906,  914,  916,  915,  693,  791,
   20, 1046, 1044,  691,  790,  700,-32766,-32766,  608,  656,
 1027,  768,  981,  855,  793,  976,  503,  489,  357,  356,
  355,  354,  353,  346,  344,  343,  341,  411,  412,  413,
  340,  433,  921,  339,  337,  334,   77,  331,  330,  329,
  328,  912,  327,  913,   22,-32766,  907,  908,  909,  910,
  911,-32766,  434,   21,  127,    0,  128,  417,  923,  435,
    0,    0,    0,    0,    0,    0,-32766,    0,  233,   57,
    0,    0,    0,    0,  435,    0,    0,    0,-32766,-32766,
    0,    0,-32766,-32766,  890,  891,  892,  893,  894,  895,
  896,  897,  898,  899,  900,  901,  902,    0,  903,    0,
  157,  905,  906,  914,  916,  915,    0,    0,    0,    0,
    0,    0,    0,    0,-32766,-32766,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  411,  412,  413,    0,  433,
  921,    0,    0,    0,   77,    0,    0,    0,    0,  912,
    0,  913,    0,-32766,  907,  908,  909,  910,  911,-32766,
  434,    0,    0,    0,    0,  417,  923,    0,    0,    0,
    0,    0,    0,    0,-32766,    0,    0,   57,    0,    0,
    0,    0,-32766,    0,    0,    0,-32766,-32766,    0,    0,
-32766,-32766,  165,  363,    0,  364,   14,  365,    0,  295,
    0,    0,  244,  245,  366,  101,  367,    0,  368,    0,
  225,  226,  524,   62,  102,  296,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  252,    0,
 -472,    0,    0,    0,    0,  298,  299,  369,  370,  371,
  372,  373,    0,  253,  254,   30,   31,   32,    0,  375,
    0,    0,    0,    0,    0,    0,    1,  571,    0,    0,
    0,    0,  -99,  165,  363,  233,  364,   14,  365,    0,
  295,  248,    0,  244,  245,  366,  101,  367,    0,  368,
    0,  225,  226,  524,   62,  102,  296,    0,    0,    0,
    0,    0,    0,   -1,  165,  363,    0,  364,   14,  365,
    0,  295,    0,    0,  244,  245,  366,  101,  367,    0,
  368,    0,  225,  226,  524,   62,  102,  296,    0,  252,
    0,    0,    0,    0,    0,    0,  298,  299,  369,  370,
  371,  372,  373,    0,  253,  254,   30,   31,   32,    0,
  375,    0,    0,    0,    0,    0,    0,    1,    0,    0,
  252,    0,    0,  -99,    0,    0, -365,  298,  299,  369,
  370,  371,  372,  373,    0,  253,  254,   30,   31,   32,
    0,  375,    0,    0,    0,    0,  165,  363,    1,  364,
   14,  365,    0,  295,  -99,    0,  244,  245,  366,  101,
  367,    0,  368,    0,  225,  226,  524,   62,  102,  296,
    0,    0,    0,    0,    0,    0,  165,  363,    0,  364,
   14,  365,    0,  295,    0,    0,  244,  245,  366,  101,
  367,    0,  368,    0,  225,  226,  524,   62,  102,  296,
    0,    0,  252,    0,    0,    0,    0,    0,    0,  298,
  299,  369,  370,  371,  372,  373,    0,  253,  254,   30,
   31,   32,    0,  375,    0,    0,    0,    0,    0,    0,
    1,  576,  252,    0,    0,    0,  -99,    0,    0,  298,
  299,  369,  370,  371,  372,  373,    0,  253,  254,   30,
   31,   32,    0,  375,    0,    0,    0,    0,    0,    0,
    1,  575,    0,    0,  165,  363,  -99,  364,   14,  365,
    0,  295,    0,    0,  244,  245,  366,  101,  367,    0,
  368,    0,  225,  226,  524,   62,  102,  296,    0,    0,
    0,    0,    0,    0,  165,  363,    0,  364,   14,  365,
    0,  295,    0,    0,  244,  245,  366,  101,  367,    0,
  368,    0,  225,  226,  524,   62,  102,  296,    0,    0,
  252,    0,    0,    0,    0,    0,    0,  298,  299,  369,
  370,  371,  372,  373,    0,  253,  254,   30,   31,   32,
    0,  375,    0,    0,    0,    0,    0,    0,    1,  574,
  252,    0,    0,    0,  -99,    0,    0,  298,  299,  369,
  370,  371,  372,  373,    0,  253,  254,   30,   31,   32,
    0,  375,    0,    0,    0,    0,    0,    0,    1,  573,
    0,    0,  165,  363,  -99,  364,   14,  365,    0,  295,
    0,    0,  244,  245,  366,  101,  367,    0,  368,    0,
  225,  226,  524,   62,  102,  296,    0,    0,    0,    0,
    0,    0,  165,  363,    0,  364,   14,  365,    0,  295,
    0,    0,  244,  245,  366,  101,  367,    0,  368,    0,
  225,  226,  524,   62,  102,  296,    0,    0,  252,    0,
    0,    0,    0,    0,    0,  298,  299,  369,  370,  371,
  372,  373,    0,  253,  254,   30,   31,   32,    0,  375,
    0,    0,    0,    0,    0,    0,    1,  572,  252,    0,
    0,    0,  -99,    0,    0,  298,  299,  369,  370,  371,
  372,  373,    0,  253,  254,   30,   31,   32,    0,  375,
    0,    0,    0,    0,    0,    0,    1,  774,    0,    0,
  165,  363,  -99,  364,   14,  365,    0,  295,    0,    0,
  244,  245,  366,  101,  367,    0,  368,    0,  225,  226,
  524,   62,  102,  296,    0,    0,    0,    0,    0,  165,
  363,    0,  364,   14,  365,    0,  295,    0,    0,  244,
  245,  366,  101,  367,    0,  368,    0,  225,  226,  524,
   62,  102,  296,    0,    0,    0,  252,    0,  122,    0,
    0,    0,    0,  298,  299,  369,  370,  371,  372,  373,
    0,  253,  254,   30,   31,   32,    0,  375,    0,    0,
    0,    0,    0,    0,    1,  252,    0,  118,    0,    0,
  -99,    0,  298,  299,  369,  370,  371,  372,  373,    0,
  253,  254,   30,   31,   32,    0,  375,    0,    0,    0,
    0,  165,  363,    1,  364,   14,  365,    0,  295,  -99,
    0,  244,  245,  366,  101,  367,    0,  368,    0,  225,
  226,  524,   62,  102,  296,    0,    0,    0,    0,    0,
    0,  165,  363,    0,  364,   14,  365,    0,  295,    0,
    0,  244,  245,  366,  101,  367,    0,  368,    0,  225,
  226,  524,   62,  102,  296,    0,    0,  252,    0,    0,
    0,    0,    0,    0,  298,  299,  369,  370,  371,  372,
  373,    0,  253,  254,   30,   31,   32,    0,  375,    0,
    0,    0,    0,    0,    0,    1,  571,  252,    0,    0,
    0,  -99,    0,    0,  298,  299,  369,  370,  371,  372,
  373,    0,  253,  254,   30,   31,   32,  103,  375,    0,
    0,  156,    0,    0,    0,    1,    0,    0,    0,    0,
    0,  -99,    0,    0,    0,  151,  152,    0,    0,    0,
    0,    0,    0,    0,  525,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  780,  781,  782,-32766,
  388,    0,    0,    0,    0,    0,  297,    0,    0,    0,
    0,    0,    0,    0,  999,  389,  390,-32766,-32766,    0,
  374,  799,    0,  783,  779,  777,  800,    0,   39,    0,
   43,    0,  778,    0,    0,  153,  158,    0,   56,    0,
   23,    0,    0,  247,    0,  300,    0,  154,  144,  526,
    0,  145,  146,   24,    0,    0,-32766,-32766,-32766,    0,
    0,    0,-32766,    0,    0,    0,    0,    0,    0,    0,
    0,  697,  698,  699,    0,    0,    0,-32766,    0,    0,
    0,    0,    0,    0,    0,-32766,    0,    0,    0,-32766,
-32766,    0,    0,-32766,-32766,    0,  799,    0,    0,  696,
  694,  800,    0,    0,    0,    0,    0,  695,    0,    0,
    0,    0,    0,   61
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1784

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,    0,   18,   19,   20,   21,
   22,   23,   19,   25,   26,   27,   28,   29,   61,   62,
   90,    2,   34,   35,   94,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,    4,    5,
    6,   53,   54,   55,   87,   57,   58,   13,   78,    4,
    5,    6,   95,   83,   97,   67,   23,   69,   13,   71,
   72,   73,   74,   75,   76,   85,   78,   14,   16,   30,
    2,   83,    4,    5,    6,   87,    8,   90,    2,   99,
   92,   13,   14,   95,   91,   17,   98,   99,  100,    3,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   90,
   16,    4,   18,   19,   20,   21,   22,   23,   85,   25,
   26,   27,   28,   29,   85,   32,   33,   78,   34,   35,
   85,   87,   83,   94,   85,   67,   87,   98,   85,   95,
   72,   97,   74,   75,   99,   62,   94,   53,   54,   55,
   92,   57,   58,   85,   86,   82,   27,   28,   29,   91,
    7,   67,  104,   69,   10,   92,   72,   73,   74,   75,
   76,   14,   78,   85,    3,   87,   93,   83,   84,    7,
   87,   87,   99,   95,   37,   97,   92,   16,   95,   95,
   97,    7,   98,   99,  100,    7,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   71,   62,   71,   72,
   73,  102,  103,   78,   77,   87,   85,   85,   83,  105,
  106,  107,    9,   95,   79,   97,   94,   96,  101,   56,
   85,   78,   62,   14,   53,   54,   55,  100,   57,   58,
   59,   19,   82,   62,   91,   64,   65,   66,   67,   68,
   69,   70,   92,   72,   73,   74,   75,   76,   85,   78,
   87,   78,   16,   93,   83,   84,   85,   86,   95,   99,
   97,   86,   91,   79,   91,   94,   95,   30,   93,   85,
   31,  100,    2,    3,    4,    5,    6,    7,    8,    9,
   10,   11,   12,   13,   14,   36,   16,   62,   18,   19,
   20,   21,   22,   23,   79,   91,   78,   93,   25,   26,
   85,   59,   32,   33,   79,   71,   72,   73,   34,   35,
   85,   77,   51,   52,   61,   62,   59,   59,   62,   85,
   60,   87,   78,   53,   54,   55,   62,   57,   58,   62,
   78,   97,   62,   99,  100,   84,   82,   67,   79,   69,
   78,   71,   72,   73,   74,   75,   76,   77,   78,   78,
   78,   82,   88,   83,   84,   78,   86,   93,   78,   78,
   78,   78,   92,   99,   94,   95,   78,   78,   78,   78,
  100,   78,   85,   79,  104,  105,   79,   79,  108,  109,
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   84,   16,   84,   18,   19,   20,   21,
   22,   23,   84,   84,   84,   84,   90,   85,   85,   85,
   32,   33,   85,   85,   85,   85,   90,   86,   86,   86,
   86,   96,   87,   87,   -1,   88,   88,   88,   88,   88,
   88,   53,   54,   55,   88,   57,   58,   88,   88,   91,
   62,   90,   90,   90,   90,   67,   90,   69,   91,   71,
   72,   73,   74,   75,   76,   77,   78,   91,   91,   91,
   91,   83,   84,   91,   86,   91,   91,   91,   91,   96,
   92,   91,   94,   95,   91,   91,   91,   91,  100,   91,
   91,   94,  104,  105,   93,   93,  108,  109,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   93,   16,   93,   18,   19,   20,   21,   22,   23,
   93,   93,   93,   93,   98,   94,   94,   94,   32,   33,
   94,   94,   94,   94,   94,   94,   94,   94,   94,   94,
   94,   94,   94,   94,   -1,   95,   95,   95,   95,   53,
   54,   55,   95,   57,   58,   95,   95,   95,   62,   95,
   95,   95,   95,   67,   95,   69,   95,   71,   72,   73,
   74,   75,   76,   77,   78,   95,   95,   95,   95,   83,
   84,   95,   86,   95,   95,   95,   95,   95,   92,   95,
   94,   95,   95,   95,   95,   95,  100,   95,  103,   96,
  104,  105,   96,   96,  108,  109,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   96,
   16,   96,   18,   19,   20,   21,   22,   23,   96,   96,
   96,   96,   96,   96,   96,   96,   32,   33,   96,   96,
   96,   96,   96,   96,   96,   96,   96,   96,   96,   96,
   96,   96,   96,   96,   96,   96,   96,   53,   54,   55,
   96,   57,   58,   96,   96,   96,   62,   96,   96,   96,
   96,   67,   96,   69,   96,   71,   72,   73,   74,   75,
   76,   77,   78,   96,   99,   -1,  100,   83,   84,  100,
   -1,   -1,   -1,   -1,   -1,   -1,   92,   -1,   94,   95,
   -1,   -1,   -1,   -1,  100,   -1,   -1,   -1,  104,  105,
   -1,   -1,  108,  109,    2,    3,    4,    5,    6,    7,
    8,    9,   10,   11,   12,   13,   14,   -1,   16,   -1,
   18,   19,   20,   21,   22,   23,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   32,   33,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   53,   54,   55,   -1,   57,
   58,   -1,   -1,   -1,   62,   -1,   -1,   -1,   -1,   67,
   -1,   69,   -1,   71,   72,   73,   74,   75,   76,   77,
   78,   -1,   -1,   -1,   -1,   83,   84,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   92,   -1,   -1,   95,   -1,   -1,
   -1,   -1,  100,   -1,   -1,   -1,  104,  105,   -1,   -1,
  108,  109,    1,    2,   -1,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   -1,   17,   -1,
   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   57,   -1,
   59,   -1,   -1,   -1,   -1,   64,   65,   66,   67,   68,
   69,   70,   -1,   72,   73,   74,   75,   76,   -1,   78,
   -1,   -1,   -1,   -1,   -1,   -1,   85,   86,   -1,   -1,
   -1,   -1,   91,    1,    2,   94,    4,    5,    6,   -1,
    8,  100,   -1,   11,   12,   13,   14,   15,   -1,   17,
   -1,   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,
   -1,   -1,   -1,    0,    1,    2,   -1,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   -1,
   17,   -1,   19,   20,   21,   22,   23,   24,   -1,   57,
   -1,   -1,   -1,   -1,   -1,   -1,   64,   65,   66,   67,
   68,   69,   70,   -1,   72,   73,   74,   75,   76,   -1,
   78,   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,   -1,
   57,   -1,   -1,   91,   -1,   -1,   94,   64,   65,   66,
   67,   68,   69,   70,   -1,   72,   73,   74,   75,   76,
   -1,   78,   -1,   -1,   -1,   -1,    1,    2,   85,    4,
    5,    6,   -1,    8,   91,   -1,   11,   12,   13,   14,
   15,   -1,   17,   -1,   19,   20,   21,   22,   23,   24,
   -1,   -1,   -1,   -1,   -1,   -1,    1,    2,   -1,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   -1,   17,   -1,   19,   20,   21,   22,   23,   24,
   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,   64,
   65,   66,   67,   68,   69,   70,   -1,   72,   73,   74,
   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,
   85,   86,   57,   -1,   -1,   -1,   91,   -1,   -1,   64,
   65,   66,   67,   68,   69,   70,   -1,   72,   73,   74,
   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,
   85,   86,   -1,   -1,    1,    2,   91,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   -1,
   17,   -1,   19,   20,   21,   22,   23,   24,   -1,   -1,
   -1,   -1,   -1,   -1,    1,    2,   -1,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   -1,
   17,   -1,   19,   20,   21,   22,   23,   24,   -1,   -1,
   57,   -1,   -1,   -1,   -1,   -1,   -1,   64,   65,   66,
   67,   68,   69,   70,   -1,   72,   73,   74,   75,   76,
   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   85,   86,
   57,   -1,   -1,   -1,   91,   -1,   -1,   64,   65,   66,
   67,   68,   69,   70,   -1,   72,   73,   74,   75,   76,
   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   85,   86,
   -1,   -1,    1,    2,   91,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   -1,   17,   -1,
   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,
   -1,   -1,    1,    2,   -1,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   -1,   17,   -1,
   19,   20,   21,   22,   23,   24,   -1,   -1,   57,   -1,
   -1,   -1,   -1,   -1,   -1,   64,   65,   66,   67,   68,
   69,   70,   -1,   72,   73,   74,   75,   76,   -1,   78,
   -1,   -1,   -1,   -1,   -1,   -1,   85,   86,   57,   -1,
   -1,   -1,   91,   -1,   -1,   64,   65,   66,   67,   68,
   69,   70,   -1,   72,   73,   74,   75,   76,   -1,   78,
   -1,   -1,   -1,   -1,   -1,   -1,   85,   86,   -1,   -1,
    1,    2,   91,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   14,   15,   -1,   17,   -1,   19,   20,
   21,   22,   23,   24,   -1,   -1,   -1,   -1,   -1,    1,
    2,   -1,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   -1,   17,   -1,   19,   20,   21,
   22,   23,   24,   -1,   -1,   -1,   57,   -1,   59,   -1,
   -1,   -1,   -1,   64,   65,   66,   67,   68,   69,   70,
   -1,   72,   73,   74,   75,   76,   -1,   78,   -1,   -1,
   -1,   -1,   -1,   -1,   85,   57,   -1,   59,   -1,   -1,
   91,   -1,   64,   65,   66,   67,   68,   69,   70,   -1,
   72,   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,
   -1,    1,    2,   85,    4,    5,    6,   -1,    8,   91,
   -1,   11,   12,   13,   14,   15,   -1,   17,   -1,   19,
   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,   -1,
   -1,    1,    2,   -1,    4,    5,    6,   -1,    8,   -1,
   -1,   11,   12,   13,   14,   15,   -1,   17,   -1,   19,
   20,   21,   22,   23,   24,   -1,   -1,   57,   -1,   -1,
   -1,   -1,   -1,   -1,   64,   65,   66,   67,   68,   69,
   70,   -1,   72,   73,   74,   75,   76,   -1,   78,   -1,
   -1,   -1,   -1,   -1,   -1,   85,   86,   57,   -1,   -1,
   -1,   91,   -1,   -1,   64,   65,   66,   67,   68,   69,
   70,   -1,   72,   73,   74,   75,   76,   14,   78,   -1,
   -1,   18,   -1,   -1,   -1,   85,   -1,   -1,   -1,   -1,
   -1,   91,   -1,   -1,   -1,   32,   33,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   41,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   53,   54,   55,   14,
   57,   -1,   -1,   -1,   -1,   -1,   63,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   71,   72,   73,   32,   33,   -1,
   77,   78,   -1,   80,   81,   82,   83,   -1,   85,   -1,
   87,   -1,   89,   -1,   -1,   92,   18,   -1,   95,   -1,
   97,   -1,   -1,  100,   -1,  102,   -1,  104,  105,  106,
   -1,  108,  109,  110,   -1,   -1,   71,   72,   73,   -1,
   -1,   -1,   77,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   53,   54,   55,   -1,   -1,   -1,   92,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  100,   -1,   -1,   -1,  104,
  105,   -1,   -1,  108,  109,   -1,   78,   -1,   -1,   81,
   82,   83,   -1,   -1,   -1,   -1,   -1,   89,   -1,   -1,
   -1,   -1,   -1,   95
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1550,  211,  851, 1520, 1203, 1173, 1438, 1409,  973,  942,
 1291, 1085, 1055, 1321, 1550, 1550, 1550, 1550, 1550, 1550,
 1550, 1550, 1550,  349,  351,  291,  361,  358,  360,  359,
  104,  104,  104,  104,  104,  104,  418,  310,  526,  634,
  742,  742,   55,  304,  200,   93,  175,  175,  175,  175,
    3,  265,  162,  -10,  -10,  -10,  224,  255,   43,  479,
  307,  337,  362,  362,  362,  370,  370,  370,  362,  362,
  362,  362,  370,  362, 1613, 1613, 1613,  370,  370,  370,
  370,  370,  370,  370,  370,  370,  370,  370,  370,  370,
  370,  370, 1613,  370,  370, 1613, 1613,  370, 1613,  370,
  370, 1613, 1613, 1613, 1613, 1613, 1613,  327, 1613, 1613,
 1613, 1613, 1613, 1613,   63,   63,   63,   63,   63,  249,
  249,  249,  249,  167,  167,  167,  167,  167,  167,  167,
  167,  167,  167,  167,  167,  167,  167,  167,  167,  167,
  167,  167,  167,  167,  167,  167,  167,  167,  167,  167,
  167, 1655, 1655, 1655, 1655, 1655, 1655, 1655, 1655,  274,
  274,  274,   62,   29,  276,   78,  563,  390,  378,  562,
  389,  379,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3, 1688, 1688, 1688,  203,  161,  -33,
   98,   98,   98,   98,  363,  363,  363,  296,  296,  296,
  296,  296,  296,  296,  296,  296,  296,  296,  296,  296,
  296,  296,  296,  296,  296,  296,  296,   49,  158,  158,
  158,  139,  139,  139,   59,   59,   59,   44,   59,   59,
   59,  183,  213,  165,  165,  165,  165,  165,  165,   54,
  144,  144,  144,  194,  258,  317,  181,  480,  481,  -20,
  619,  482,  252,  322,  323,  157,  313,  314,   68,  301,
  293,  333,  -60,  408,  407,  244,  252,  322,  323,  215,
  365,  533,  424,  553,  313,  314,  314,  314,  314,  314,
   68,   68,  301,  423,  413,   83,  555,  536,  537,  190,
   86,   86,   86,   86,   86,  369,  320,  510,  312,  312,
  525,  243,  331,  510,  513,  513,  369,  369,  369,  466,
  459,  369,  510,  499,  164,  432,  473,  473,  376,  376,
  369,  369,  369,  471,  512,  369,  369,  478,  478,  478,
  478,  474,  369,  471,  478,  512,  369,  478,  369,  478,
  478,  478,  369,  478,  474,  369,  478,  369,  369,  369,
  369,  369,  369,  478,  478,  478,  478,  474,  369,  369,
  369,  369,  369,  496,  495,  532,  494,  472,  364,  415,
  284,  302,  292,  321,  497,  477,   15,  414,  277,  279,
  456,  615,  616,  289,  117,  492,  412,  409,  511,  490,
  487,  483,  366,  396,  450,  330,  501,  338,  368,  367,
  530,  529,  381,  579,  528,  527,  524,  496,  495,  532,
  494,  463,  462,  461,  284,  292,  467,  427,  468,  298,
  382,  457,  578,  380,  577,  429,  522,  491,  182,  198,
  194,  397,  388,  511,  469,  521,  394,  406,  311,  392,
  299,  576,  475,  606,  460,  604,  603,  581,  373,  457,
  602,  300,  277,  476,  279,  456,  615,  616,  289,  289,
  289,  575,  458,  601,  163,  366,  420,  329,  520,  519,
  518,  516,  328,  371,  393,  393,  393,  428,  334,  580,
  574,  599,  598,  597,  594,  590,  377,  375,  375,  470,
  589,  372,  573,  588,   96,  417,  572,  587,  569,  294,
  391,  356,  426,  568,  386,  282,  425,  416,  564,  586,
  585,  584,  583,  582,  567,  566,  617,  309,  393,  608,
  297,  565,  374,  374,    0,    0,    0,    0, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
 1613,   -2,   -2,   -2,   -2,   -2,   -2,   -2,    0,    0,
    0,    0,    0,    0, 1613, 1613, 1613, 1613, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
 1613, 1613,    0,    0,    0, 1613, 1613, 1613, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
    0, 1613, 1613,    0,    0, 1613,    0, 1613, 1613,    0,
    0,    0,    0,    0,    0, 1613,    0,    0,    0,    0,
    0,    0, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1613,
 1613, 1613, 1613, 1613, 1613, 1613, 1613, 1688, 1688, 1688,
   -3,   -3,   -3,    0,   -3,   -3,   -3,   -3,   -3,   -3,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  103,  103,  103,  103,  103,
  103,  103,  103,  103,  103,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   86,  103,  103,  103,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   86,
   86,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -60,   86,   86,    0,  478,  478,    0,  478,  478,
  511,  490,  487,    0,    0,    0,    0,    0,    0,  483,
    0,  448,  448,    0,  511,  490,  487,    0,  431,  431,
  431,  431,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  448,  431,    0,  431,  431,  431
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 289

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  381,  382,  383,  472,  472,  472,  472,
32767,  335,32767,32767,32767,32767,  519,  519,  519,  519,
32767,32767,  101,32767,32767,32767,32767,32767,32767,   91,
  343,32767,  101,  101,  101,32767,32767,32767,  101,  101,
  101,  101,32767,  101,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,   91,32767,  374,32767,32767,32767,32767,   93,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  221,
  223,32767,32767,32767,32767,32767,32767,  376,32767,32767,
32767,32767,32767,  103,32767,32767,32767,32767,32767,32767,
32767,32767,  348,   90,  340,  346,  341,  525,  350,  359,
  344,   92,  347,  360,32767,  148,  150,  233,32767,  141,
  231,  232,  229,  228,  122,  526,  361,  500,  500,  500,
  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
  500,  500,  500,  500,  500,  500,32767,32767,  142,  149,
  151,  197,  198,  199,32767,32767,32767,32767,  377,  378,
32767,  371,  372,32767,32767,32767,32767,32767,32767,  517,
  209,  211,  210,  458,  103,  103,  174,  472,  472,32767,
  472,  472,32767,32767,32767,  184,  195,  200,  206,  216,
  218,32767,  458,32767,32767,32767,  392,  379,  380,  225,
32767,32767,32767,32767,  196,  202,  204,  205,  201,  203,
  207,  208,  217,32767,32767,32767,32767,32767,32767,32767,
  103,  103,  103,  103,  103,32767,32767,32767,32767,32767,
  332,   77,32767,32767,  498,  498,32767,32767,  368,  528,
  334,32767,32767,   79,   81,  334,  492,  492,  512,  512,
32767,32767,32767,  179,  515,32767,32767,  472,  472,  472,
  472,  474,32767,  179,  472,  515,32767,  472,32767,  472,
  472,  472,32767,  472,  474,32767,  472,32767,32767,32767,
32767,32767,32767,  472,  472,  472,  472,  474,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  271,32767,32767,  185,  187,
  189,  191,  193,  212,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  102,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  362,  364,  366,
  373,  252,  253,  254,  384,  385,  271,  272,32767,32767,
32767,  336,32767,32767,32767,32767,32767,32767,32767,  258,
  256,32767,32767,  392,  271,32767,   51,32767,32767,32767,
32767,32767,  504,32767,  501,32767,32767,32767,32767,  337,
32767,32767,  186,32767,  188,  190,  192,  194,  213,  214,
  215,32767,  520,32767,32767,   75,32767,32767,32767,32767,
32767,32767,  335,32767,  462,  463,  460,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  511,  509,  265,
32767,32767,32767,32767,   62,32767,32767,32767,32767,32767,
   54,  459,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  461,32767,
32767,32767,  480,32767,  528,  452,  452,  528
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  179,  174,  174,  174,  177,  177,  177,  177,  175,  177,
  172,  179,  179,  179,  166,  166,  430,  173,  180,  169,
  172,  172,  172,  492,  514,  521,  172,  172,  172,  172,
  881,  172,  175,  175,  175,  706,  706,  706, 1009, 1009,
  705,  705,  705, 1008,  522,  453,  491,  710,  523,  978,
  175,  475,  476,  175,  175,  451,  175,  518,  977,  162,
  173,  164,  162,  176,  167,  178,  168,  181,  182,  183,
  170,  171,  222,  223,  261,  261,  261,  261,  261,  261,
  261,  261,  261,  261,  261,  261,  261,  261,  261,  261,
  261,  261,  261,  261,  261,  261,  261,  458,  459,  460,
  673,  673,  673,  275,  276,  277,  278,  279,  770,  703,
  664,  770,  770,  770,  770,  652,  687,  352,  269,  280,
  281,  652,  652,  652,  449,  692,  692,  692,  771,  657,
  361,  771,  771,  771,  771,  657,  657,  657,  706,  429,
  762,  324,  335,  515, 1003,  687,  687,  687,  241,  242,
  692,  692,  692,  886,  886,  886,  886,  886,  886,   11,
   12,   13,   13,  442,  442,  442,  442,  442,  442,  442,
  442,  442,  442,  442,  442,  442,  442,  442,  442,  442,
  442,  442,  442,  758,  754,  755,  747,  748,  750,  752,
  243,  262,  262,  589,  262,  262,  262,  445,  446,  450,
  463,  480,  481,  482,  483,  484,  485,  490,  493,  497,
  509,  510,  511,  512,  513, 1036,  301,  797,  766,  654,
  674,  689, 1024,  190,  191,  192,  193, 1018, 1019,  301,
  667,  666, 1010,  471,  471,  471,  405,  406, 1051,  405,
  406,  606,  610,  594,  452,  455, 1016, 1017,  671,  671,
  671,  454,  884,  685,  882,  456,  283, 1004,  264, 1005,
  457,  264,  274, 1006, 1031,  282, 1007,  663,  996,  997,
 1011, 1012, 1013,  998, 1022,  794,  794,  701,  333,  680,
  681,  682,  683,  684,  464,  985, 1034, 1034, 1034, 1034,
 1034, 1034, 1034, 1034, 1034, 1034, 1034, 1034, 1034, 1034,
 1034, 1034, 1034, 1034, 1034, 1034,  672,  672,  672,  218,
  219,  220,  530,  465,  392,  392,  399,  392,  392,  392,
  531,  384,  533,  533,  533,  533,  384,  494,  592,  591,
  600,  601,  599,  598,  597,  317,  661,  473,  326,  488,
  116, 1033,  312,    0, 1035, 1035, 1035, 1035, 1035, 1035,
 1035, 1035, 1035, 1035, 1035, 1035, 1035, 1035, 1035, 1035,
 1035, 1035, 1035, 1035,  155,    0,    0,    0,    0,    0,
    0,  393,  393,  393,  649,  393,  393,  393,  589,    0,
    0,  649,  649,  649,    0,  311,  311,  628,  649,  332,
    0,    0,    0,  649,  649,  649,  649,  649,  649,  649,
  649,  649,  649,  649,  649,  649,  649,  649,  635,  649,
  649,    0,    0,  649,    0,  649,  649,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  885,  870,  638,
  639,  640,  641,  642,  643,  644,  645,  646,  647,  648,
  636,  637,    0,  635, 1050,    0,    0,  873,  196,  993,
 1052,    0,  195,  195,  195,  195,  387,  195,    0,  196,
  196,  196,  188,  188,    0,  336,  338,  342,  505,  387,
    0,    0,  347,    0,    0,  348,    0,  349,  350,  351,
    0,    6,    0,    0,    7,  270,  271,  273,    0,    0,
    0,  358,  359,  360,  520,    0,    0,    0,    0,    0,
    0,    0,    0,  284,    0,    0,  286,  287,    0,  288,
    0,    0,    0,    0,  425,  431,  432,  437,  477,  294,
  466,    0,    0,    0,  495,  507,  508,  516,    0,  519
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 530

static char yygcheck[] = {
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   75,   37,   37,   37,
   37,   37,   37,   99,   99,   99,   37,   37,   37,   37,
   73,   37,   37,   37,   37,    7,    7,    7,    7,    7,
   41,   41,   41,   41,   41,   41,   41,   41,   41,   66,
   37,   82,   82,   37,   37,   67,   37,   82,   66,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   50,   50,   83,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   54,   54,   54,
   98,   98,   98,   51,   51,   51,   51,   51,    7,  117,
  117,    7,    7,    7,    7,   60,   60,  103,   57,   52,
   52,   60,   60,   60,   68,   75,   75,   75,   98,   98,
  103,   98,   98,   98,   98,   98,   98,   98,    7,   63,
  104,  104,  104,  104,  104,   60,   60,   60,   53,   53,
   75,   75,   75,   57,   57,   57,   57,   57,   57,    3,
    3,    3,    3,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   56,   56,   56,   56,   56,   56,   56,
   75,   75,   75,   35,   75,   75,   75,   94,   94,   94,
   94,   94,   94,   94,   94,   94,   94,   94,   94,   94,
   94,   94,   94,   94,   94,   75,    7,   59,   59,   59,
   59,   59,   59,   58,   58,   58,   58,    7,    7,    7,
  112,  112,    7,   83,   83,   83,   77,   77,  101,   77,
   77,    7,    7,    7,   44,   46,    7,    7,   63,   63,
   63,   45,   74,    7,   74,   47,   80,    7,   80,    7,
   48,   80,   49,    7,   96,   55,    7,  118,    7,    7,
    7,    7,    7,    7,   61,   61,   61,   61,   32,    7,
    7,    7,    7,    7,   19,   81,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   64,   64,   64,  113,
  113,  113,    4,   63,   63,   63,    9,   63,   63,   63,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,   92,  110,  119,   90,  105,
  120,  106,  122,   -1,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,  107,   -1,   -1,   -1,   -1,   -1,
   -1,   64,   64,   64,  108,   64,   64,   64,   35,   -1,
   -1,  108,  108,  108,   -1,  102,  102,   31,  108,  102,
   -1,   -1,   -1,  108,  108,  108,  108,  108,  108,  108,
  108,  108,  108,  108,  108,  108,  108,  108,   38,  108,
  108,   -1,   -1,  108,   -1,  108,  108,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   -1,   38,   38,   -1,   -1,   38,   39,   38,
   38,   -1,   39,   39,   39,   39,   31,   39,   -1,   39,
   39,   39,   39,   39,   -1,  102,  102,  102,  102,   31,
   -1,   -1,  102,   -1,   -1,  102,   -1,  102,  102,  102,
   -1,  102,   -1,   -1,  102,   70,   70,   70,   -1,   -1,
   -1,  102,  102,  102,  102,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   70,   -1,   -1,   70,   70,   -1,   70,
   -1,   -1,   -1,   -1,   31,   31,   31,   31,   31,   40,
   40,   -1,   -1,   -1,   40,   40,   40,   40,   -1,   40
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  155,  312,    0,    0,  -79,    0,   17,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   60,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  224,   61,    0,    0,  151,    0,  -42,  350,  406,
  456,  -74,    0,    0,  121,  127,  120,  129,  133,  134,
  -57,  -28,  -17,   10,  -43,  122,   39,  117,   72,  193,
  -73,  119,    0,   89,  147,    0, -254,   11,   79,    0,
  411,    0,    0,  -11,  199,  -34,    0,  205,    0,    0,
   32,   55,  -15,   74,    0,    0,    0,    0,    0,    0,
   21,    0,   30,    0,   -1,    0,   48,    0,  -59,  -24,
    0,  187,  138, -227,  -94,   20,    6, -163,  316,    0,
   90,    0,   70,  125,    0,    0,    0,   -6,   50,   22,
    7,    0, -184
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  376,    8,   10,  532,  535,  534,  536,  537,  398,
  538,  315,  551,  539,  567,  568,  569,  540,  570,  428,
  541,  314,  320,  604,  546,  547,  290,  548,  549,  265,
  550,  386,  632,  552,  542,  543,  377,  163,  992,  194,
  293,  658,  709,  255,  378,  379,  380,  381,  382,  256,
  221,  257,  258,  240,  383,  259,  260,  753,  187,  795,
  764,  763,  785,  786,  787,  788,  979,  420,  421,   45,
  272,  394,  310,  880,  883,  784,  418,  404, 1015,  585,
  263,  984,  474,  391,  586,  994,  711,  995,  587,  588,
  325,  239,  316, 1021,  443,  444, 1030,  769,  789,  461,
  462, 1049,  419,  345, 1001,  487,  501,   63,  634,  246,
  660,  217,  665,  189,  668,  686,  659,  662,  704,  448,
  115,   44,  303
#line 205 "build/utility/kmyacc.c.parser"
};

static char yylhs[] = {
    0,    1,    2,    2,    3,    3,    4,    4,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,   35,
   35,   35,   35,    7,    7,    8,    8,    8,    8,    9,
   10,   11,   11,   11,   11,   11,   11,   12,   12,   12,
   12,   34,   13,   13,   14,   15,   16,   17,   17,   18,
   18,   18,   18,   18,   19,   19,   20,   21,   21,   22,
   22,   23,   23,   33,   33,   33,   33,   24,   24,   25,
   26,   26,   26,   26,   27,   28,   29,   29,   30,   36,
   36,   40,   40,   31,   31,   32,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   38,   38,   39,   39,   39,   39,   39,   39,   39,
  108,  108,  109,  109,  110,  110,  110,  111,  111,  111,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
  112,  112,  114,  114,  114,  114,  114,  114,  113,  113,
  113,  113,  113,  113,  115,  115,  115,  115,  115,  115,
  115,  115,  115,  115,  116,  116,  117,  117,  118,  120,
  120,   41,   41,   42,   42,   43,   43,   44,   44,   45,
   45,   46,   46,   47,   47,   48,   48,   49,   49,   49,
   50,   50,   50,   50,   50,   50,   51,   51,   51,   52,
   52,   52,   53,   53,   53,   53,   54,   54,   55,   55,
   55,   55,   55,   55,   55,   56,   56,   56,   56,   56,
   56,   56,   56,   57,   57,   58,   58,   58,   58,   58,
   58,   58,   97,   97,   98,   98,   98,   60,   60,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   75,   75,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   63,   63,
   62,   62,  121,   64,  119,  119,   67,   67,   69,   69,
   68,   68,   68,   68,   68,   68,   70,   70,   71,   71,
   71,   71,   72,   72,   73,   73,   73,   73,   73,   74,
   74,   74,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   65,
   65,   65,  122,   66,   79,   79,   80,   80,   81,   81,
   81,   81,   81,   81,   82,   82,   84,   84,   85,   85,
   85,   83,  102,  102,  103,  103,   86,   86,   86,   86,
   86,   86,   86,   87,   87,   87,   77,   77,   88,   88,
   89,   89,   90,   90,   91,   91,   91,   91,   92,   92,
   94,   94,   95,   95,   96,   96,   96,   96,   96,  104,
  104,  104,  105,  105,  105,  106,  106,   93,   93,   99,
   99,  100,  100,  100,  100,  101,  101,  101,  107
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
    9,    8,    7,    8,    1,    1,    4,    0,    3,    0,
    3,    0,    2,    3,    4,    3,    4,    5,    2,    3,
    2,    1,    4,    3,    4,    3,    1,    3,    2,    0,
    2,    0,    1,    0,    1,    4,    1,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    1,    1,    2,    2,    4,    3,    3,    4,    2,
    1,    4,    1,    2,    4,    3,    5,    1,    3,    3,
    1,    1,    2,    1,    1,    1,    2,    2,    2,    3,
    2,    3,    6,    6,    6,    6,    7,    3,    1,    2,
    4,    3,    3,    4,    1,    3,    1,    1,    1,    1,
    1,    1,    3,    2,    0,    3,    1,    1,    1,    0,
    1,    1,    5,    1,    1,    1,    3,    1,    3,    1,
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
    1,    1,    1,    1,    1,    1,    1,    2,    2,    3,
    3,    2,    0,    3,    3,    3,    1,    3,    1,    4,
    3,    6,    3,    3,    1,    3,    1,    1,    7,    7,
    7,    1,    0,    2,    0,    2,    6,    6,    6,    6,
    7,    7,    3,    7,    7,    7,    1,    1,    5,    5,
    3,    3,    0,    4,    1,    4,    3,    3,    0,    3,
    0,    1,    1,    3,    1,    4,    1,    1,    2,    2,
    1,    2,    0,    2,    3,    0,    3,    0,    3,    0,
    1,    1,    2,    3,    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 942
#define YYNLSTATES 528
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
        case 16:
#line 206 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strinfo.name, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 17:
#line 207 "src/kinx.y"
{ yyerrok; yyval.obj = NULL; } break;
        case 25:
#line 218 "src/kinx.y"
{                       yyerrok; yyval.obj = NULL; } break;
        case 26:
#line 219 "src/kinx.y"
{ yy_restart(LBBR);     yyerrok; yyval.obj = NULL; } break;
        case 27:
#line 220 "src/kinx.y"
{ yy_restart(IF);       yyerrok; yyval.obj = NULL; } break;
        case 28:
#line 221 "src/kinx.y"
{ yy_restart(DO);       yyerrok; yyval.obj = NULL; } break;
        case 29:
#line 222 "src/kinx.y"
{ yy_restart(WHILE);    yyerrok; yyval.obj = NULL; } break;
        case 30:
#line 223 "src/kinx.y"
{ yy_restart(FOR);      yyerrok; yyval.obj = NULL; } break;
        case 31:
#line 224 "src/kinx.y"
{ yy_restart(TRY);      yyerrok; yyval.obj = NULL; } break;
        case 32:
#line 225 "src/kinx.y"
{ yy_restart(SWITCH);   yyerrok; yyval.obj = NULL; } break;
        case 33:
#line 226 "src/kinx.y"
{ yy_restart(CASE);     yyerrok; yyval.obj = NULL; } break;
        case 34:
#line 227 "src/kinx.y"
{ yy_restart(ENUM);     yyerrok; yyval.obj = NULL; } break;
        case 35:
#line 228 "src/kinx.y"
{ yy_restart(CLASS);    yyerrok; yyval.obj = NULL; } break;
        case 36:
#line 229 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; yyval.obj = NULL; } break;
        case 37:
#line 230 "src/kinx.y"
{ yy_restart(PRIVATE);  yyerrok; yyval.obj = NULL; } break;
        case 38:
#line 231 "src/kinx.y"
{ yy_restart(PUBLIC);   yyerrok; yyval.obj = NULL; } break;
        case 43:
#line 242 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 44:
#line 243 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 45:
#line 247 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 248 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 47:
#line 249 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 250 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 49:
#line 254 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strinfo.name); } break;
        case 50:
#line 258 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 51:
#line 262 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strinfo.name); } break;
        case 52:
#line 263 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strinfo.name, YYASP(3-3).intval); } break;
        case 53:
#line 264 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strinfo.name, -YYASP(4-4).intval); } break;
        case 54:
#line 265 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strinfo.name)); } break;
        case 55:
#line 266 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strinfo.name, YYASP(5-5).intval)); } break;
        case 56:
#line 267 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strinfo.name, -YYASP(6-6).intval)); } break;
        case 61:
#line 278 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 62:
#line 282 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 63:
#line 283 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 64:
#line 287 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 65:
#line 291 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 66:
#line 295 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 299 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 300 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 305 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 70:
#line 312 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 71:
#line 319 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 72:
#line 326 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 73:
#line 328 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 76:
#line 337 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 77:
#line 341 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 78:
#line 342 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 79:
#line 346 "src/kinx.y"
{ yyval.obj = kx_gen_var_object("_e", KX_UNKNOWN_T); } break;
        case 80:
#line 347 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(2-3).strinfo.name, KX_UNKNOWN_T, YYASP(2-3).strinfo.line, YYASP(2-3).strinfo.pos1, YYASP(2-3).strinfo.pos2); } break;
        case 81:
#line 351 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 82:
#line 352 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 83:
#line 356 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 84:
#line 357 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strinfo.name)); } break;
        case 85:
#line 358 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 86:
#line 359 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strinfo.name)); } break;
        case 87:
#line 363 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 88:
#line 364 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 89:
#line 368 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 90:
#line 372 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 91:
#line 373 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 92:
#line 374 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 93:
#line 375 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 94:
#line 379 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 95:
#line 383 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 96:
#line 387 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_OBJ_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2), NULL); } break;
        case 97:
#line 388 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object_line_pos(YYASP(3-3).strinfo.name, KX_OBJ_T, YYASP(3-3).strinfo.line, YYASP(3-3).strinfo.pos1, YYASP(3-3).strinfo.pos2), NULL); } break;
        case 98:
#line 392 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 99:
#line 396 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 100:
#line 397 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 101:
#line 401 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 103:
#line 406 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 105:
#line 411 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 107:
#line 416 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 108:
#line 417 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 109:
#line 418 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 110:
#line 419 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 111:
#line 420 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 421 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 423 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 425 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 119:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 120:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 123:
#line 438 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 124:
#line 439 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 125:
#line 440 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 126:
#line 441 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 127:
#line 442 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 128:
#line 443 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 129:
#line 444 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 131:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 133:
#line 454 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 134:
#line 458 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-4).obj, YYASP(4-4).obj, NULL); } break;
        case 135:
#line 459 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 136:
#line 460 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 138:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 139:
#line 466 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 142:
#line 472 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 146:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 147:
#line 477 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 148:
#line 478 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 149:
#line 479 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 150:
#line 480 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 151:
#line 481 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 152:
#line 486 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 153:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 154:
#line 488 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 155:
#line 489 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 156:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 157:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 159:
#line 496 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 160:
#line 497 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 161:
#line 498 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 162:
#line 499 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 163:
#line 500 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 165:
#line 505 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 166:
#line 506 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 167:
#line 507 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 168:
#line 508 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 169:
#line 509 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 170:
#line 510 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 171:
#line 511 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 172:
#line 512 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 173:
#line 513 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 174:
#line 517 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 175:
#line 518 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 178:
#line 527 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 182:
#line 537 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 186:
#line 547 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 188:
#line 552 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 190:
#line 557 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 562 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 194:
#line 567 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 572 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 199:
#line 578 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 583 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 584 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 203:
#line 585 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 205:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 207:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 208:
#line 593 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 210:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 211:
#line 599 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 213:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 214:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 215:
#line 606 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 217:
#line 611 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 219:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 220:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 221:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 222:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 223:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 224:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 226:
#line 626 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 227:
#line 627 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 228:
#line 628 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 229:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 230:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 231:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 232:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 234:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 236:
#line 642 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 237:
#line 643 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 238:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 239:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 240:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 241:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 242:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 244:
#line 656 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-5).arraytype, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(4-5).obj, NULL, NULL), NULL); } break;
        case 245:
#line 657 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-9).arraytype, NULL, YYASP(4-9).obj, kx_gen_stmt_object(KXST_RET, YYASP(8-9).obj, NULL, NULL), NULL); } break;
        case 246:
#line 658 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-8).arraytype, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 247:
#line 662 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 248:
#line 663 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 249:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 250:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 251:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 252:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 253:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 254:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 255:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 262:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 263:
#line 681 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 264:
#line 682 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 265:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 266:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 267:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 268:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 269:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 270:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 271:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_UNKNOWN_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2); } break;
        case 272:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(kx_gen_typestr_object(YYASP(1-1).intval), KX_UNKNOWN_T); } break;
        case 273:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strinfo.name); } break;
        case 274:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 275:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 276:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 277:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 278:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 279:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 280:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 281:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 282:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 283:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 284:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 285:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 286:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 287:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 288:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 289:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 290:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 291:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 292:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 293:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 294:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 295:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 296:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 297:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 298:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 299:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 300:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 301:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 302:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 303:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 304:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 305:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 306:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 307:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 308:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 309:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 310:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 311:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 312:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 313:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 314:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 315:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 316:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 317:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 318:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 319:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 320:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 321:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 322:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 323:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 324:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 325:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 326:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 327:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 328:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 329:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 330:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 331:
#line 761 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 332:
#line 765 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 333:
#line 769 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 334:
#line 773 "src/kinx.y"
{} break;
        case 336:
#line 778 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 337:
#line 779 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 338:
#line 783 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 339:
#line 784 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 341:
#line 789 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 342:
#line 790 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 343:
#line 791 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 344:
#line 792 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 345:
#line 793 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 347:
#line 798 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 349:
#line 803 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 350:
#line 804 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 351:
#line 805 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 353:
#line 810 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 354:
#line 814 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 355:
#line 815 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 356:
#line 816 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 357:
#line 817 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 358:
#line 818 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 360:
#line 823 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 362:
#line 828 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 363:
#line 829 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 364:
#line 830 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 365:
#line 831 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 366:
#line 832 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 367:
#line 833 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 368:
#line 834 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 369:
#line 835 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 370:
#line 836 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 371:
#line 837 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 372:
#line 838 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 373:
#line 839 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 374:
#line 840 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 375:
#line 841 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 376:
#line 842 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 377:
#line 843 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 378:
#line 844 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 379:
#line 845 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 380:
#line 846 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 381:
#line 847 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 382:
#line 848 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 383:
#line 849 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 384:
#line 850 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 385:
#line 851 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 386:
#line 852 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 387:
#line 853 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 388:
#line 854 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 389:
#line 855 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 390:
#line 856 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 391:
#line 857 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 392:
#line 858 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 393:
#line 859 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 394:
#line 860 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 395:
#line 861 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 396:
#line 865 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 397:
#line 866 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 398:
#line 867 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 399:
#line 868 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 400:
#line 869 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 401:
#line 870 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 402:
#line 871 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 403:
#line 872 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 404:
#line 873 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 405:
#line 874 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 406:
#line 875 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 407:
#line 876 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 408:
#line 877 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 409:
#line 878 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 410:
#line 879 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 411:
#line 880 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 412:
#line 881 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 413:
#line 882 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 414:
#line 883 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 415:
#line 884 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 416:
#line 885 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 417:
#line 886 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 418:
#line 887 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 419:
#line 888 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 420:
#line 889 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 421:
#line 890 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 422:
#line 891 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 423:
#line 892 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 424:
#line 893 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 425:
#line 894 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 426:
#line 895 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 427:
#line 896 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 428:
#line 897 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 429:
#line 898 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 430:
#line 899 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 431:
#line 900 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 432:
#line 901 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 433:
#line 902 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 434:
#line 903 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 435:
#line 904 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 436:
#line 905 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 437:
#line 906 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 438:
#line 907 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 439:
#line 908 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 440:
#line 909 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 441:
#line 910 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 442:
#line 911 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 443:
#line 912 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 444:
#line 913 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 445:
#line 914 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 446:
#line 915 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 447:
#line 916 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 448:
#line 917 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 449:
#line 921 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 450:
#line 922 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 451:
#line 923 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 452:
#line 927 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 453:
#line 931 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 454:
#line 935 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 455:
#line 936 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 457:
#line 941 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 458:
#line 945 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-1).obj, NULL); } break;
        case 459:
#line 946 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 460:
#line 947 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 461:
#line 948 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).obj, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 462:
#line 949 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 463:
#line 950 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 465:
#line 955 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 466:
#line 959 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 467:
#line 960 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 468:
#line 964 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 469:
#line 965 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 470:
#line 966 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, 0, YYASP(6-7).arraytype, YYASP(2-7).strinfo.name, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 471:
#line 970 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 472:
#line 974 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_UNKNOWN_T }; } break;
        case 473:
#line 975 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 474:
#line 979 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 475:
#line 980 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 476:
#line 984 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 477:
#line 985 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 478:
#line 986 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 479:
#line 987 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, 0, YYASP(5-6).arraytype, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 480:
#line 988 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-7).obj, NULL, NULL), NULL); } break;
        case 481:
#line 989 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(5-7).arraytype, NULL, YYASP(3-7).obj, YYASP(7-7).obj, NULL); } break;
        case 482:
#line 990 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, YYASP(2-3).arraytype, NULL, NULL, YYASP(3-3).obj, NULL); } break;
        case 483:
#line 994 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 484:
#line 995 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 485:
#line 996 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, YYASP(6-7).arraytype, YYASP(2-7).strval, YYASP(4-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 486:
#line 1000 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strinfo.name; } break;
        case 488:
#line 1005 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 489:
#line 1006 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 490:
#line 1010 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 491:
#line 1011 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 492:
#line 1015 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 493:
#line 1017 "src/kinx.y"
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
        case 495:
#line 1033 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 496:
#line 1034 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 497:
#line 1035 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 498:
#line 1039 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 499:
#line 1040 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 500:
#line 1044 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 503:
#line 1050 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 505:
#line 1055 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 506:
#line 1056 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 507:
#line 1057 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 508:
#line 1058 "src/kinx.y"
{ YYASP(2-2).obj->var_type = KX_SPR_T; yyval.obj = YYASP(2-2).obj; } break;
        case 509:
#line 1062 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 510:
#line 1063 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 511:
#line 1064 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strinfo.name) }; } break;
        case 512:
#line 1068 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 513:
#line 1069 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 514:
#line 1070 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 515:
#line 1074 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 516:
#line 1075 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 517:
#line 1079 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 518:
#line 1080 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 519:
#line 1084 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 522:
#line 1090 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 523:
#line 1091 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 524:
#line 1092 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 527:
#line 1098 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 528:
#line 1102 "src/kinx.y"
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
