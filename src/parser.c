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
#line 1097 "src/kinx.y"

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
  "WhenAnonymousFunctionDeclExpression : FUNCTION '(' ArgumentList_Opts ')' BlockStatement",
  "WhenAnonymousFunctionDeclExpression : SYSFUNC '(' ArgumentList_Opts ')' BlockStatement",
  "WhenAnonymousFunctionDeclExpression : COROUTINE '(' ArgumentList_Opts ')' BlockStatement",
  "WhenAnonymousFunctionDeclExpression : NativeKeyword NativeType_Opt '(' ArgumentList_Opts ')' BlockStatement",
  "WhenAnonymousFunctionDeclExpression : '&' '(' ArgumentList_Opts ')' DARROW BlockStatement",
  "WhenAnonymousFunctionDeclExpression : '&' BlockStatement",
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
#define YYNONTERMS 121

static short yyaction[] = {
  788,  789,  790,  791,  792,  793,  794,  795,  796,  797,
  798,  799,  800,  802,  801,  111,  803,  804,  805,  814,
  816,  815,  226,  824,  825,  826,  828,  830,  187,  188,
   69,  369,  822,  823,  237,   81,   82,   83,   84,   85,
   86,   87,   88,   89,   90,   91,   92,   93,  348,   16,
  349,  817,  818,  819,  114,  820,  821,  350,  121,  348,
   16,  349,   50,  161,   30,  812,   99,  813,  350,  806,
  807,  808,  809,  810,  811,-32766,  786,   39,  125,  162,
  538,  787,  540,  539,  541,  405,  542,   95,   41,   41,
  832,  543,  544,  406,   66,  545,  837,  838,  836,  416,
  827,  829,  831,  833,  834,  835,  909,  910,  911,  912,
  913,  914,  915,  916,  917,  918,  919,  920,  921,   60,
  922, -360,  923,  924,  925,  933,  935,  934, -360,  945,
  946,  947,  949,  951,    5,  760,  761,   80,  943,  944,
   39,  578,  122,  116, 1021,  546,   41,  163,    0,  430,
  547,  320,  549,  548,  113,   39,  321,  936,  937,  938,
   41,  939,  940,  537,  528,  133,  134,  135,  852,  536,
  275,  931,   39,  932,  107,   19,  926,  927,  928,  929,
  930,  777,  997,    4,  115,  108,  113,  941,  942,  369,
  110,  385,   51,   48,   31,   27,  953,  408,   49,  386,
   28,   98,  958,  959,  957,  -74,  948,  950,  952,  954,
  955,  956,  875,  876,  877,  878,  879,  880,  881,  882,
  883,  884,  885,  886,  887,   80,  888,   96,  159,  890,
  891,  899,  901,  900,  -75,  102,  142,  143,  144,  566,
  136,  137,-32766,-32766, 1038,  984,  451,  452,   41,  501,
   39,  453, 1038,  325,  131,  132,  851,  294,   39,   41,
  235,   45,  107,  394,  395,  396,  161,  414,  906,  121,
 -102,   29,   79,  186,  252,  100,  605,  897,  420,  898,
   80,-32766,  892,  893,  894,  895,  896,-32766,  415,    4,
  114,  108,  140,  400,  908,   41,  862,-32766,   50,   48,
   30,   27,-32766,   41,  141,   59,  841,   38,  784,  250,
  416,  851,  322,  785,-32766,-32766, -390,  107,-32766,-32766,
  875,  876,  877,  878,  879,  880,  881,  882,  883,  884,
  885,  886,  887,  293,  888,  563,  159,  890,  891,  899,
  901,  900,  404,  480,   41,  482, -102,-32766,   39,   41,
-32766,-32766,  784, -389,-32766,-32766,-32766,  785,  161,   42,
-32766,   45,  138,  139,  149,  150,  151,  152,   41,  378,
  126,  394,  395,  396,  127,  414,  906,  121,  119,  345,
   79,  145,  844,-32766,  293,  897,  251,  898,  311,-32766,
  892,  893,  894,  895,  896,-32766,  415,  564,  567,  309,
  561,  400,  908,   41,  864,  308,   57,  383,  607,  560,
-32766,  423,  606,   59,  310,  384,  483,  294,  416,  478,
   41,  202,-32766,-32766,  446,  421,-32766,-32766,  875,  876,
  877,  878,  879,  880,  881,  882,  883,  884,  885,  886,
  887,  418,  888,  461,  159,  890,  891,  899,  901,  900,
  485,  637,  749, 1008,  672,  291,  783,  781,-32766,-32766,
  657,  755,  275,  306,    7,    6,   38,   39,   40,    5,
  675,  846,  754,    0,  487,  472,    0,  960,  747,  394,
  395,  396,  670,  414,  906,  121, 1025, 1024,   79,  839,
 1006,  842,  635,  897, -393,  898,  287,-32766,  892,  893,
  894,  895,  896,-32766,  415,  101,   74,   68,   67,  400,
  908,   41,  633,  460,  232,  527,  597,  209,-32766,  604,
  596,   59,  594,  576,  968,  967,  416,  595,  593,  608,
-32766,-32766,  598,   75,-32766,-32766,  167,  390,  876,  391,
   10,  392,  880,  312,  882,  883,  233,  234,  393,  106,
  351,  888,  352,  159,  230,  231,  313,   54,   61,  298,
   73,   72,   71,   70,  599,  128,  130,  112,   43,   53,
  454,  218,  109,   62,    0,  690,  579,  510,  238,  236,
  229,  123, -396,   56,   55,   44, -388, -391,  394,  395,
  396, -392,  266,  906,  121,  216,  380,   79,  379,  300,
  301,  353,  397,  355,  398,  357,  239,  267,  268,   35,
   36,   37,  217,  399,  215,  214,  213,  212,  400,  908,
  211,  554,  210,  208,  207,  206,  -98,  205,  204,  203,
   59,  201,  200,  199,   97,  249,  875,  876,  877,  878,
  879,  880,  881,  882,  883,  884,  885,  886,  887,   94,
  888,   78,  159,  890,  891,  899,  901,  900,   77,   76,
   52,  422,  450,  843,  776,  615,-32766,-32766,  489,  323,
   21,   20,   18,   17, 1029, 1027,  673,  775,  682,  638,
 1010,  750,  966,  840,  778,  961,  499,  394,  395,  396,
  486,  414,  906,  121,  471,  468,   79,  346,  344,  343,
  342,  897,  341,  898,  340,-32766,  892,  893,  894,  895,
  896,-32766,  415,  339,  338,  337,  336,  400,  908,   41,
  335,  333,  331,  330,  329,   24,-32766,   23,   22,   59,
    0,    3,    2,    0,  416,    0,  129,    0,-32766,-32766,
    0,    0,-32766,-32766,  875,  876,  877,  878,  879,  880,
  881,  882,  883,  884,  885,  886,  887,    0,  888,    0,
  159,  890,  891,  899,  901,  900,    0,    0,    0,    0,
    0,    0,    0,    0,-32766,-32766,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  394,  395,  396,    0,  414,
  906,    0,    0,    0,   79,    0,    0,    0,    0,  897,
    0,  898,    0,-32766,  892,  893,  894,  895,  896,-32766,
  415,    0,    0,    0,    0,  400,  908,   41,    0,    0,
    0,    0,    0,    0,-32766,    0,    0,   59,    0,    0,
    0,    0,-32766,    0,    0,    0,-32766,-32766,    0,    0,
-32766,-32766,  167,  347,    0,  348,   16,  349,    0,  297,
    0,    0,  245,  246,  350,  103,  351,    0,  352,    0,
  227,  228,  507,   64,  104,  298,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  253,    0,
  121,    0,    0,    0,    0,  300,  301,  353,  354,  355,
  356,  357,    0,  254,  255,   32,   33,   34,    0,  359,
    0,    0,    0,    0,    0,    0,    0,  554,    0,    0,
    0,    0,  -98,  167,  347,    0,  348,   16,  349,    0,
  297,  249,    0,  245,  246,  350,  103,  351,    0,  352,
    0,  227,  228,  507,   64,  104,  298,    0,    0,    0,
    0,    0,    0,    0,  167,  347,    0,  348,   16,  349,
    0,  297,    0,    0,  245,  246,  350,  103,  351,    0,
  352,    0,  227,  228,  507,   64,  104,  298,    0,  253,
    0,  124,    0,    0,    0,    0,  300,  301,  353,  354,
  355,  356,  357,    0,  254,  255,   32,   33,   34,    0,
  359,    0,    0,    0,    0,    0,    0,    0,  756,    0,
  253,    0,  120,  -98,    0,    0,    8,  300,  301,  353,
  354,  355,  356,  357,    0,  254,  255,   32,   33,   34,
    0,  359,    0,    0,    0,    0,    0,    0,    0,  756,
    0,    0,    0,    0,  -98,  167,  347,    8,  348,   16,
  349,    0,  297,    0,    0,  245,  246,  350,  103,  351,
    0,  352,    0,  227,  228,  507,   64,  104,  298,    0,
    0,    0,    0,    0,    0,   -1,  167,  347,    0,  348,
   16,  349,    0,  297,    0,    0,  245,  246,  350,  103,
  351,    0,  352,    0,  227,  228,  507,   64,  104,  298,
    0,  253,    0,    0,    0,    0,    0,    0,  300,  301,
  353,  354,  355,  356,  357,    0,  254,  255,   32,   33,
   34,    0,  359,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  253,    0,    0,  -98,    0,    0, -367,  300,
  301,  353,  354,  355,  356,  357,    0,  254,  255,   32,
   33,   34,    0,  359,    0,    0,    0,  167,  347,    0,
  348,   16,  349,    0,  297,    0,  -98,  245,  246,  350,
  103,  351,    0,  352,    0,  227,  228,  507,   64,  104,
  298,    0,    0,    0,    0,  167,  347,    0,  348,   16,
  349,    0,  297,    0,    0,  245,  246,  350,  103,  351,
    0,  352,    0,  227,  228,  507,   64,  104,  298,    0,
    0,    0,    0,  253,    0,    0,    0,    0,    0,    0,
  300,  301,  353,  354,  355,  356,  357,    0,  254,  255,
   32,   33,   34,    0,  359,    0,    0,    0,    0,    0,
    0,  253,  758,    0,    0,    0,    0,  -98,  300,  301,
  353,  354,  355,  356,  357,    0,  254,  255,   32,   33,
   34,    0,  359,    0,    0,    0,    0,    0,    0,    0,
  757,    0,    0,  167,  347,  -98,  348,   16,  349,    0,
  297,    0,    0,  245,  246,  350,  103,  351,    0,  352,
    0,  227,  228,  507,   64,  104,  298,    0,    0,    0,
    0,  167,  347,    0,  348,   16,  349,    0,  297,    0,
    0,  245,  246,  350,  103,  351,    0,  352,    0,  227,
  228,  507,   64,  104,  298,    0,    0,    0,    0,  253,
    0,    0,    0,    0,    0,    0,  300,  301,  353,  354,
  355,  356,  357,    0,  254,  255,   32,   33,   34,    0,
  359,    0,    0,    0,    0,    0,    0,  253,  759,    0,
    0,    0,    0,  -98,  300,  301,  353,  354,  355,  356,
  357,    0,  254,  255,   32,   33,   34,    0,  359,    0,
    0,    0,    0,    0,    0,    0,  558,    0,    0,  167,
  347,  -98,  348,   16,  349,    0,  297,    0,    0,  245,
  246,  350,  103,  351,    0,  352,    0,  227,  228,  507,
   64,  104,  298,    0,    0,    0,    0,  167,  347,    0,
  348,   16,  349,    0,  297,    0,    0,  245,  246,  350,
  103,  351,    0,  352,    0,  227,  228,  507,   64,  104,
  298,    0,    0,    0,    0,  253,    0,    0,    0,    0,
    0,    0,  300,  301,  353,  354,  355,  356,  357,    0,
  254,  255,   32,   33,   34,    0,  359,    0,    0,    0,
    0,    0,    0,  253,  557,    0,    0,    0,    0,  -98,
  300,  301,  353,  354,  355,  356,  357,    0,  254,  255,
   32,   33,   34,    0,  359,    0,    0,    0,    0,    0,
    0,    0,  556,    0,    0,  167,  347,  -98,  348,   16,
  349,    0,  297,    0,    0,  245,  246,  350,  103,  351,
    0,  352,    0,  227,  228,  507,   64,  104,  298,    0,
    0,    0,    0,  167,  347,    0,  348,   16,  349,    0,
  297,    0,    0,  245,  246,  350,  103,  351,    0,  352,
    0,  227,  228,  507,   64,  104,  298,    0,    0,    0,
    0,  253,    0,    0,    0,    0,    0,    0,  300,  301,
  353,  354,  355,  356,  357,    0,  254,  255,   32,   33,
   34,    0,  359,    0,    0,    0,    0,    0,    0,  253,
  555,    0,    0,    0,    0,  -98,  300,  301,  353,  354,
  355,  356,  357,    0,  254,  255,   32,   33,   34,    0,
  359,    0,    0,    0,    0,    0,    0,    0,  554,    0,
    0,  167,  347,  -98,  348,   16,  349,    0,  297,    0,
    0,  245,  246,  350,  103,  351,    0,  352,    0,  227,
  228,  507,   64,  104,  298,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  105,    0,    0,    0,  158,    0,
    0,    0,    0,    0,    0,    0,    0,  253,    0,    0,
    0,    0,  153,  154,  300,  301,  353,  354,  355,  356,
  357,  508,  254,  255,   32,   33,   34,    0,  359,    0,
    0,    0,    0,  765,  767,  768,  559,  372,    0,    0,
    0,  -98,    0,  299,    0,    0,    0,    0,    0,    0,
    0,  984,  373,  374,    0,    0,    0,  358,  784,    0,
  769,  764,  762,  785,    0,    1,    0,   45,    0,  763,
    0,    0,  155,    0,    0,   58,    0,   25,    0,    0,
  248,    0,  302,    0,  156,  146,  509,    0,  147,  148,
   26,  167,  347,    0,  348,   16,  349,    0,  297,    0,
    0,  245,  246,  350,  103,  351,    0,  352,    0,  227,
  228,  507,   64,  104,  298,-32766,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,-32766,-32766,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  253,  160,    0,
    0,    0,    0,    0,  300,  301,  353,  354,  355,  356,
  357,    0,  254,  255,   32,   33,   34,    0,  359,    0,
    0,    0,-32766,-32766,-32766,    0,    0,    0,-32766,    0,
    0,  -98,    0,  679,  680,  681,   41,    0,    0,    0,
    0,    0,    0,-32766,    0,    0,    0,    0,    0,    0,
    0,-32766,    0,    0,    0,-32766,-32766,    0,  784,-32766,
-32766,  678,  676,  785,    0,    0,    0,    0,    0,  677,
    0,    0,    0,    0,    0,   63
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1916

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   23,   18,   19,   20,   21,
   22,   23,   19,   25,   26,   27,   28,   29,   61,   62,
   90,    2,   34,   35,   94,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,    4,    5,
    6,   53,   54,   55,   87,   57,   58,   13,   59,    4,
    5,    6,   95,   16,   97,   67,   62,   69,   13,   71,
   72,   73,   74,   75,   76,   14,   78,   85,   37,   30,
    2,   83,    4,    5,    6,   87,    8,   90,   85,   85,
   92,   13,   14,   95,   91,   17,   98,   99,  100,  100,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   90,
   16,   86,   18,   19,   20,   21,   22,   23,   93,   25,
   26,   27,   28,   29,   85,   32,   33,   62,   34,   35,
   85,   94,  101,   94,   71,   67,   85,   98,    0,   79,
   72,   78,   74,   75,   99,   85,   83,   53,   54,   55,
   85,   57,   58,   85,   86,   27,   28,   29,   93,   91,
   85,   67,   85,   69,   99,    3,   72,   73,   74,   75,
   76,   96,   78,   85,   87,   87,   99,   83,   84,    2,
   87,   87,   95,   95,   97,   97,   92,    4,   95,   95,
   97,    7,   98,   99,  100,    7,  102,  103,  104,  105,
  106,  107,    2,    3,    4,    5,    6,    7,    8,    9,
   10,   11,   12,   13,   14,   62,   16,   62,   18,   19,
   20,   21,   22,   23,    7,   62,  105,  106,  107,   82,
  102,  103,   32,   33,   79,   71,   72,   73,   85,   92,
   85,   77,   79,    3,   25,   26,   93,   78,   85,   85,
   56,   87,   99,   53,   54,   55,   16,   57,   58,   59,
   91,   97,   62,   99,  100,    7,   91,   67,   93,   69,
   62,   71,   72,   73,   74,   75,   76,   77,   78,   85,
   87,   87,   92,   83,   84,   85,   86,   14,   95,   95,
   97,   97,   92,   85,  104,   95,   88,   85,   78,    9,
  100,   93,   10,   83,  104,  105,   94,   99,  108,  109,
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   78,   16,   82,   18,   19,   20,   21,
   22,   23,   79,   79,   85,   92,   91,   14,   85,   85,
   32,   33,   78,   94,   71,   72,   73,   83,   16,   85,
   77,   87,   34,   35,   51,   52,   61,   62,   85,   19,
   30,   53,   54,   55,   31,   57,   58,   59,   59,   59,
   62,   36,   60,  100,   78,   67,   62,   69,   78,   71,
   72,   73,   74,   75,   76,   77,   78,   82,   82,   78,
   86,   83,   84,   85,   86,   78,   94,   78,   78,   78,
   92,   79,   78,   95,   78,   78,   78,   78,  100,   78,
   85,   95,  104,  105,   78,   78,  108,  109,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   78,   16,   79,   18,   19,   20,   21,   22,   23,
   79,   84,   84,   84,   84,   90,   84,   84,   32,   33,
   84,   86,   85,   85,   85,   85,   85,   85,   85,   85,
   96,   86,   86,   -1,   87,   87,   -1,   88,   88,   53,
   54,   55,   88,   57,   58,   59,   88,   88,   62,   88,
   88,   88,   88,   67,   94,   69,   90,   71,   72,   73,
   74,   75,   76,   77,   78,   90,   90,   90,   90,   83,
   84,   85,   86,   90,   93,   91,   91,   95,   92,   91,
   91,   95,   91,   91,   91,   91,  100,   91,   91,   91,
  104,  105,   91,   91,  108,  109,    1,    2,    3,    4,
    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
   91,   91,   91,   91,   91,   98,  100,   93,   93,   93,
   93,   93,   93,   93,   -1,   94,   94,   94,   94,   94,
   94,   94,   94,   94,   94,   94,   94,   94,   53,   54,
   55,   94,   57,   58,   59,   95,   95,   62,   95,   64,
   65,   66,   67,   68,   69,   70,   95,   72,   73,   74,
   75,   76,   95,   78,   95,   95,   95,   95,   83,   84,
   95,   86,   95,   95,   95,   95,   91,   95,   95,   95,
   95,   95,   95,   95,   95,  100,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   95,
   16,   95,   18,   19,   20,   21,   22,   23,   95,   95,
   95,   95,   95,  103,   96,   96,   32,   33,   96,   96,
   96,   96,   96,   96,   96,   96,   96,   96,   96,   96,
   96,   96,   96,   96,   96,   96,   96,   53,   54,   55,
   96,   57,   58,   59,   96,   96,   62,   96,   96,   96,
   96,   67,   96,   69,   96,   71,   72,   73,   74,   75,
   76,   77,   78,   96,   96,   96,   96,   83,   84,   85,
   96,   96,   96,   96,   96,   96,   92,   96,   96,   95,
   -1,   96,   96,   -1,  100,   -1,   99,   -1,  104,  105,
   -1,   -1,  108,  109,    2,    3,    4,    5,    6,    7,
    8,    9,   10,   11,   12,   13,   14,   -1,   16,   -1,
   18,   19,   20,   21,   22,   23,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   32,   33,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   53,   54,   55,   -1,   57,
   58,   -1,   -1,   -1,   62,   -1,   -1,   -1,   -1,   67,
   -1,   69,   -1,   71,   72,   73,   74,   75,   76,   77,
   78,   -1,   -1,   -1,   -1,   83,   84,   85,   -1,   -1,
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
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   86,   -1,   -1,
   -1,   -1,   91,    1,    2,   -1,    4,    5,    6,   -1,
    8,  100,   -1,   11,   12,   13,   14,   15,   -1,   17,
   -1,   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,    1,    2,   -1,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   -1,
   17,   -1,   19,   20,   21,   22,   23,   24,   -1,   57,
   -1,   59,   -1,   -1,   -1,   -1,   64,   65,   66,   67,
   68,   69,   70,   -1,   72,   73,   74,   75,   76,   -1,
   78,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   86,   -1,
   57,   -1,   59,   91,   -1,   -1,   94,   64,   65,   66,
   67,   68,   69,   70,   -1,   72,   73,   74,   75,   76,
   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   86,
   -1,   -1,   -1,   -1,   91,    1,    2,   94,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   -1,   17,   -1,   19,   20,   21,   22,   23,   24,   -1,
   -1,   -1,   -1,   -1,   -1,    0,    1,    2,   -1,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   -1,   17,   -1,   19,   20,   21,   22,   23,   24,
   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,   64,   65,
   66,   67,   68,   69,   70,   -1,   72,   73,   74,   75,
   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   57,   -1,   -1,   91,   -1,   -1,   94,   64,
   65,   66,   67,   68,   69,   70,   -1,   72,   73,   74,
   75,   76,   -1,   78,   -1,   -1,   -1,    1,    2,   -1,
    4,    5,    6,   -1,    8,   -1,   91,   11,   12,   13,
   14,   15,   -1,   17,   -1,   19,   20,   21,   22,   23,
   24,   -1,   -1,   -1,   -1,    1,    2,   -1,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   -1,   17,   -1,   19,   20,   21,   22,   23,   24,   -1,
   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,
   64,   65,   66,   67,   68,   69,   70,   -1,   72,   73,
   74,   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,
   -1,   57,   86,   -1,   -1,   -1,   -1,   91,   64,   65,
   66,   67,   68,   69,   70,   -1,   72,   73,   74,   75,
   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   86,   -1,   -1,    1,    2,   91,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   -1,   17,
   -1,   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,
   -1,    1,    2,   -1,    4,    5,    6,   -1,    8,   -1,
   -1,   11,   12,   13,   14,   15,   -1,   17,   -1,   19,
   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,   57,
   -1,   -1,   -1,   -1,   -1,   -1,   64,   65,   66,   67,
   68,   69,   70,   -1,   72,   73,   74,   75,   76,   -1,
   78,   -1,   -1,   -1,   -1,   -1,   -1,   57,   86,   -1,
   -1,   -1,   -1,   91,   64,   65,   66,   67,   68,   69,
   70,   -1,   72,   73,   74,   75,   76,   -1,   78,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   86,   -1,   -1,    1,
    2,   91,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   -1,   17,   -1,   19,   20,   21,
   22,   23,   24,   -1,   -1,   -1,   -1,    1,    2,   -1,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   -1,   17,   -1,   19,   20,   21,   22,   23,
   24,   -1,   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,
   -1,   -1,   64,   65,   66,   67,   68,   69,   70,   -1,
   72,   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,
   -1,   -1,   -1,   57,   86,   -1,   -1,   -1,   -1,   91,
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
   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   14,   -1,   -1,   -1,   18,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   57,   -1,   -1,
   -1,   -1,   32,   33,   64,   65,   66,   67,   68,   69,
   70,   41,   72,   73,   74,   75,   76,   -1,   78,   -1,
   -1,   -1,   -1,   53,   54,   55,   86,   57,   -1,   -1,
   -1,   91,   -1,   63,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   71,   72,   73,   -1,   -1,   -1,   77,   78,   -1,
   80,   81,   82,   83,   -1,   85,   -1,   87,   -1,   89,
   -1,   -1,   92,   -1,   -1,   95,   -1,   97,   -1,   -1,
  100,   -1,  102,   -1,  104,  105,  106,   -1,  108,  109,
  110,    1,    2,   -1,    4,    5,    6,   -1,    8,   -1,
   -1,   11,   12,   13,   14,   15,   -1,   17,   -1,   19,
   20,   21,   22,   23,   24,   14,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   32,   33,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   57,   18,   -1,
   -1,   -1,   -1,   -1,   64,   65,   66,   67,   68,   69,
   70,   -1,   72,   73,   74,   75,   76,   -1,   78,   -1,
   -1,   -1,   71,   72,   73,   -1,   -1,   -1,   77,   -1,
   -1,   91,   -1,   53,   54,   55,   85,   -1,   -1,   -1,
   -1,   -1,   -1,   92,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  100,   -1,   -1,   -1,  104,  105,   -1,   78,  108,
  109,   81,   82,   83,   -1,   -1,   -1,   -1,   -1,   89,
   -1,   -1,   -1,   -1,   -1,   95
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1780,  535,  973,  942,  851, 1552, 1436, 1408, 1204, 1095,
 1064, 1524, 1320, 1640, 1176, 1292, 1780, 1780, 1780, 1780,
 1780, 1780, 1780, 1780, 1780,  373,  372,  368,  367,  376,
  370,  369,  104,  104,  104,  104,  104,  104,  210,  426,
  318,  634,  742,  742,   55,  218,  163,   75,  165,  165,
  165,  165,    3,  173,  222,   87,   87,   87,  263,   70,
   -8,  259,    4,  264,  381,  381,  381,  382,  382,  382,
  381,  381,  381,  381,  382,  381,  335,  335,  335,  382,
  382,  382,  382,  382,  382,  382,  382,  382,  382,  382,
  382,  382,  382,  382,  335,  382,  382,  335,  335,  382,
  335,  382,  382,  335,  335,  335,  335,  335,  335,  383,
  335,  335,  335,  335,  335,  335,  333,  333,  333,  333,
  333,   61,   61,   61,   61,  283,  283,  283,  283,  283,
  283,  283,  283,  283,  283,  283,  283,  283,  283,  283,
  283,  283,  283,  283,  283,  283,  283,  283,  283,  283,
  283,  283,  283, 1791, 1791, 1791, 1791, 1791, 1791, 1791,
 1791,  174,  174,  174,   47,   29,  342,   78,  568,  390,
  404,  374,  394,  402,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3, 1820, 1820, 1820,  204,
   85,  -33,   98,   98,   98,   98,  377,  377,  377,  324,
  324,  324,  324,  324,  324,  324,  324,  324,  324,  324,
  324,  324,  324,  324,  324,  324,  324,  324,  324,   49,
  203,  203,  203,  138,  138,  138,  274,  274,  274,   44,
  274,  274,  274,  255,  179,   73,   73,   73,   73,   73,
   97,  131,  131,  131,  198,  306,  339,  250,  326,  422,
  567,  230,  500,  350,  329,  337,   41,  229,  328,  200,
  313,  305,  -60,  434,  433,  185,  350,  329,  337,   35,
  346,  577,  576,  472,  573,   -1,  229,  328,  328,  328,
  328,  328,  200,  200,  313,  471,  569,  253,  572,  575,
  574,  157,  187,  187,  187,  187,  187,  384,  334,  501,
  331,  331,  560,  485,  300,  485,  363,  501,  534,  534,
  384,  384,  384,  492,  475,  501,  302,  477,  483,  483,
  388,  388,  384,  384,  485,  481,  511,  384,  384,  384,
  384,  384,  481,  384,  511,  384,  384,  384,  384,  384,
  384,  384,  384,  384,  384,  384,  384,  564,  563,  565,
  556,  482,  378,  441,  327,  321,  336,  310,  536,  486,
  148,  438,  340,  343,  467,  637,  466,  345,  193,  554,
  437,  436,  503,  538,  537,  418,  417,  479,  347,  566,
  332,  380,  379,  533,  532,  389,  589,  530,  529,  528,
  564,  563,  565,  556,  493,  497,  400,  327,  336,  491,
  488,  490,  403,  480,  588,  401,  587,  473,  539,  194,
  227,  198,  431,  429,  503,  489,  525,  527,  406,  428,
  330,  423,  364,  586,  484,  628,  478,  627,  626,  386,
  599,  385,  480,  598,  322,  340,  487,  343,  467,  637,
  466,  345,  345,  345,  585,  476,  522,  268,  418,  470,
  341,  521,  520,  519,  338,  314,  415,  415,  415,  425,
  371,  594,  584,  625,  624,  620,  619,  618,  312,  636,
  583,  319,  399,  387,  387,  617,  172,  469,  608,  635,
  582,  517,  315,  365,  416,  424,  581,  398,  606,  432,
  442,  632,  604,  603,  602,  590,  580,  579,  631,  320,
  601,  316,  415,  375,  629,  375,  578,    0,    0,    0,
    0, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670,   -2,   -2,   -2,   -2,
   -2,   -2,   -2,    0,    0,    0,    0,    0,    0, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670, 1670,
 1670, 1670, 1820, 1820, 1820,   -3,   -3,   -3,    0,   -3,
   -3,   -3,   -3,   -3,   -3,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  103,  103,  103,  103,  103,  103,  103,  103,  103,  103,
  274,  274,  274,  274,  274,  274,  274,  274,  274,  274,
  274,  274,  274,  274,  274,  274,  274,  274,  274,  274,
  187,  103,  103,  103,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  187,  187,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -60,  187,  187,    0,  384,
  384,  384,    0,  384,  503,  538,  537,    0,    0,    0,
    0,    0,    0,    0,  421,  421,    0,  503,  538,  537,
    0,  527,  474,  474,  474,  474,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  421,  474,    0,  474,
  474,  474
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 291

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  383,  384,  385,32767,32767,
32767,32767,32767,  337,32767,32767,32767,32767,  519,  519,
  519,  519,32767,32767,  100,32767,32767,32767,32767,32767,
32767,   90,  345,32767,  100,  100,  100,32767,32767,32767,
  100,  100,  100,  100,32767,  100,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,   90,32767,  376,32767,32767,32767,
32767,   92,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  220,  222,32767,32767,32767,32767,32767,32767,  378,
32767,32767,32767,32767,32767,  102,32767,32767,32767,32767,
32767,32767,32767,32767,  350,   89,  342,  348,  343,  525,
  352,  361,  346,   91,  349,  362,32767,  147,  149,  232,
32767,  140,  230,  231,  228,  227,  121,  526,  363,  500,
  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,
  500,  500,  500,  500,  500,  500,  500,  500,32767,32767,
  141,  148,  150,  196,  197,  198,32767,32767,32767,32767,
  379,  380,32767,  373,  374,32767,32767,32767,32767,32767,
  517,  208,  210,  209,  460,  102,  102,  173,32767,32767,
32767,32767,32767,32767,32767,32767,  183,  194,  199,  205,
  215,  217,  460,32767,32767,32767,  394,  381,  382,  224,
32767,32767,32767,32767,32767,32767,  195,  201,  203,  204,
  200,  202,  206,  207,  216,32767,32767,32767,32767,32767,
32767,32767,  102,  102,  102,  102,  102,32767,32767,32767,
32767,32767,  334,  474,   77,  474,32767,32767,  498,  498,
32767,32767,  370,  528,  336,32767,   80,  336,  492,  492,
  512,  512,32767,32767,  474,  178,  515,32767,32767,32767,
32767,32767,  178,32767,  515,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  273,
32767,32767,  184,  186,  188,  190,  192,  211,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  101,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  364,  366,  368,  375,  254,  256,  257,  386,  387,  273,
  274,32767,32767,  338,32767,32767,32767,32767,32767,32767,
  260,  255,32767,32767,  394,  273,32767,32767,   51,32767,
32767,32767,32767,32767,  504,32767,  501,32767,32767,32767,
32767,32767,  339,32767,32767,  185,32767,  187,  189,  191,
  193,  212,  213,  214,32767,  520,32767,32767,   75,32767,
32767,32767,32767,32767,  337,32767,  464,  465,  462,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  267,32767,
32767,32767,32767,  511,  509,32767,   62,32767,32767,32767,
32767,32767,32767,   54,  461,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  463,  480,32767,32767,32767,  528,  454,  454,
  528
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  181,  176,  176,  176,  179,  179,  179,  179,  177,  179,
  174,  181,  181,  181,  168,  168,  963,  175,  182,  171,
  174,  174,  174,  866,  962,  411,  174,  174,  174,  174,
  417,  174,  177,  177,  177,  688,  688,  688,  992,  992,
  687,  687,  687,  991,  503,  429,  436,  692,  505,  481,
  177,  457,  458,  177,  177,  434,  177,  502,  432,  164,
  175,  166,  164,  178,  169,  180,  170,  183,  184,  185,
  172,  173,  685,  646,  303,  303,  303,  303,  303,  303,
  303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
  303,  303,  303,  303,  303,  303,  303,  303,  303,  634,
  669,  192,  193,  194,  195,  634,  634,  634,  752,  224,
  225,  752,  752,  752,  752,  740,  736,  737,  729,  730,
  732,  734, 1034,  410,  277,  278,  279,  280,  281,  669,
  669,  669,  282,  283,  674,  674,  674,  438,  688,  427,
  428,  433,  462,  463,  464,  465,  466,  467,  469,  475,
  479,  488,  492,  493,  494,  495,  500,  242,  243,  674,
  674,  674,  388,  389,  435,  388,  389,  993,  993,  589,
  437,  667,  424,  424,  424,  424,  424,  424,  424,  424,
  424,  424,  424,  424,  424,  424,  424,  424,  424,  424,
  424,  424,  782,  748,  636,  656,  671, 1007,  439,  244,
  262,  262,  440,  262,  262,  262,  198,  470,  496,  506,
  197,  197,  197,  197,  276,  197,  304,  198,  198,  198,
  190,  190,   14,   14, 1019,  284,   12,   13,   15, 1001,
 1002,  304,  653,  653,  653,  324,  324,  324,  285, 1014,
  264,  592,  577,  264,  645,  572,  999, 1000,  987,  988,
  989,  332,  981,  269,  982,  994,  995,  996,  990,  590,
  983,  662,  663,  664,  666,  665,  654,  654,  654,  447,
 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017,
 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017,
  871,  871,  871,  871,  871,  871,  970,  448,  375,  375,
  643,  375,  375,  375, 1018, 1018, 1018, 1018, 1018, 1018,
 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018,
 1018, 1018, 1018, 1018, 1005,  779,  779,  683,  441,  442,
  443,  376,  376,  376,  631,  376,  376,  376,  220,  221,
  222,  631,  631,  631,  986,  326,  334,  497,  631,  655,
  655,  655,  382,  631,  631,  631,  631,  631,  631,  631,
  631,  631,  631,  631,  631,  631,  631,  631,  617,  631,
  631,  610,  869,  631,  867,  631,  631,  753,  639,  455,
  753,  753,  753,  753,  639,  639,  639,  870,  855,  620,
  621,  622,  623,  624,  625,  626,  627,  628,  629,  630,
  618,  619,  513,  617, 1033,  649,  648,  858,  319,  978,
 1035,  514,  368,  516,  516,  516,  516,  516,  368,  476,
  575,  574,  583,  584,  582,  581,  580,  271,  272,  274,
  572,  296,  449,  328,  474,  118,  477,  490,  491,  498,
  371,  504,  315, 1016,  157,  286,    0,    0,  288,  289,
    0,  290,  371,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  407,  412,
  413,  419,  459
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 503

static char yygcheck[] = {
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   65,   36,   36,   36,
   36,   36,   36,   72,   65,   74,   36,   36,   36,   36,
  101,   36,   36,   36,   36,    7,    7,    7,    7,    7,
   40,   40,   40,   40,   40,   40,   40,   40,   40,  101,
   36,   81,   81,   36,   36,   66,   36,   81,   67,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,  115,  115,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   59,
   59,   57,   57,   57,   57,   59,   59,   59,    7,   49,
   49,    7,    7,    7,    7,   55,   55,   55,   55,   55,
   55,   55,  100,   62,   50,   50,   50,   50,   50,   59,
   59,   59,   51,   51,   74,   74,   74,   45,    7,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   52,   52,   74,
   74,   74,   76,   76,   43,   76,   76,    7,    7,    7,
   44,    7,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   58,   58,   58,   58,   58,   58,   46,   74,
   74,   74,   47,   74,   74,   74,   38,   98,   98,   98,
   38,   38,   38,   38,   48,   38,    7,   38,   38,   38,
   38,   38,    3,    3,   74,   54,    3,    3,    3,    7,
    7,    7,   62,   62,   62,   82,   82,   82,   79,   95,
   79,    7,    7,   79,  116,   34,    7,    7,    7,    7,
    7,   31,    7,   56,    7,    7,    7,    7,    7,    7,
    7,    7,    7,    7,    7,    7,   63,   63,   63,   19,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   56,   56,   56,   56,   56,   56,   80,   62,   62,   62,
  108,   62,   62,   62,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   60,   60,   60,   60,   53,   53,
   53,   63,   63,   63,  106,   63,   63,   63,  111,  111,
  111,  106,  106,  106,  102,  102,  102,  102,  106,   97,
   97,   97,    9,  106,  106,  106,  106,  106,  106,  106,
  106,  106,  106,  106,  106,  106,  106,  106,   37,  106,
  106,   30,   73,  106,   73,  106,  106,   97,   97,  117,
   97,   97,   97,   97,   97,   97,   97,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,    4,   37,   37,  110,  110,   37,   91,   37,
   37,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,   69,   69,   69,
   34,   39,   39,   89,  103,  118,   39,   39,   39,   39,
   30,   39,  120,  104,  105,   69,   -1,   -1,   69,   69,
   -1,   69,   30,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   30,   30,
   30,   30,   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  220,  402,    0,    0,  -81,    0,   51,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   43,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  206,   32,    0,    0,  201,    0,  -44,  308,  162,  366,
  -76,    0,    0,   39,   44,   10,   70,   73,   84,  -22,
   -9,   -6,   17,  186,   80,  -31,  252,  -52,  166,  -91,
  167,    0,   71,  105,    0, -291,    9,   11,    0,  351,
    0,    0,  -20,  317,  -27,    0,  129,    0,    0,   12,
   64,  -17,   74,    0,    0,    0,    0,    0,    0,  114,
    0,   99,    0,  -61,    0,   21,    0,  188,  158,    0,
   69, -275,  108,  113,  109,  -66,  274,    0,   53,    0,
  243,  152,    0,    0,    0,  -45,   25,   62,  103,    0,
  -67
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  360,    9,   11,  515,  518,  517,  519,  520,  381,
  521,  317,  534,  522,  550,  551,  552,  523,  553,  409,
  524,  316,  587,  529,  530,  292,  531,  532,  265,  533,
  370,  614,  535,  525,  526,  361,  165,  977,  196,  295,
  640,  691,  256,  362,  363,  364,  365,  366,  257,  223,
  258,  259,  241,  367,  260,  261,  735,  189,  780,  746,
  745,  770,  771,  772,  773,  964,  402,  403,   47,  273,
  377,  314,  865,  868,  766,  401,  387,  998,  568,  263,
  969,  456,  305,  569,  979,  693,  980,  570,  571,  327,
  240,  318, 1004,  425,  426, 1013,  751,  774,  444,  445,
 1032,  270,  744,  473,  484,   65,  616,  247,  642,  219,
  647,  191,  650,  668,  641,  644,  686,  431,  117,   46,
  307
#line 205 "build/utility/kmyacc.c.parser"
};

static char yylhs[] = {
    0,    1,    2,    2,    3,    3,    4,    4,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,   34,
   34,   34,   34,    7,    7,    8,    8,    8,    8,    9,
   10,   11,   11,   11,   11,   11,   11,   12,   12,   12,
   12,   33,   13,   13,   14,   15,   16,   17,   17,   18,
   18,   18,   18,   18,   19,   19,   20,   21,   21,   21,
   22,   22,   32,   32,   32,   32,   23,   23,   24,   25,
   25,   25,   25,   26,   27,   28,   28,   29,   35,   35,
   39,   39,   30,   30,   31,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   37,   37,   38,   38,   38,   38,   38,   38,   38,  106,
  106,  107,  107,  108,  108,  108,  109,  109,  109,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  112,  112,  112,  112,  112,  112,  111,  111,  111,
  111,  111,  111,  113,  113,  113,  113,  113,  113,  113,
  113,  113,  113,  114,  114,  115,  115,  116,  118,  118,
   40,   40,   41,   41,   42,   42,   43,   43,   44,   44,
   45,   45,   46,   46,   47,   47,   48,   48,   48,   49,
   49,   49,   49,   49,   49,   50,   50,   50,   51,   51,
   51,   52,   52,   52,   52,   53,   53,   54,   54,   54,
   54,   54,   54,   54,   55,   55,   55,   55,   55,   55,
   55,   55,   56,   56,   57,   57,   57,   57,   57,   57,
   57,   96,   96,   97,   97,   97,   97,   97,   97,   59,
   59,   60,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   74,   74,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   62,   62,   61,   61,  119,   63,  117,  117,   66,   66,
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
   77,   64,   64,   64,  120,   65,   78,   78,   79,   79,
   80,   80,   80,   80,   80,   80,   81,   81,   83,   83,
   84,   84,   84,   82,  101,  101,   85,   85,   85,   85,
   85,   85,   85,   86,   86,   86,   76,   76,   87,   87,
   88,   88,   89,   89,   90,   90,   90,   90,   91,   91,
   93,   93,   94,   94,   95,   95,   95,   95,   95,  102,
  102,  102,  103,  103,  103,  104,  104,   92,   92,   98,
   98,   99,   99,   99,   99,  100,  100,  100,  105
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
    0,    1,    0,    1,    4,    1,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    1,    1,    2,    2,    4,    3,    3,    4,    2,    1,
    4,    1,    2,    4,    3,    5,    1,    3,    3,    1,
    1,    2,    1,    1,    1,    2,    2,    2,    3,    2,
    3,    5,    5,    5,    6,    6,    2,    1,    2,    4,
    3,    3,    4,    1,    3,    1,    1,    1,    1,    1,
    1,    3,    2,    0,    3,    1,    1,    1,    0,    1,
    1,    5,    1,    1,    1,    3,    1,    3,    1,    3,
    1,    3,    1,    3,    1,    3,    1,    3,    3,    1,
    3,    3,    3,    3,    3,    1,    3,    3,    1,    3,
    3,    1,    3,    3,    3,    1,    3,    1,    3,    3,
    2,    3,    2,    3,    1,    2,    2,    2,    2,    2,
    2,    2,    1,    3,    1,    2,    4,    3,    3,    4,
    2,    1,    1,    4,    8,    6,    7,    7,    8,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    6,    3,    3,    3,    2,    2,
    2,    2,    2,    1,    1,    1,    1,    1,    1,    1,
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
    1,    1,    1,    1,    1,    1,    1,    1,    1,    2,
    2,    3,    3,    2,    0,    3,    3,    3,    1,    3,
    1,    4,    3,    6,    3,    3,    1,    3,    1,    1,
    6,    6,    7,    1,    0,    2,    5,    5,    5,    6,
    6,    6,    2,    6,    6,    6,    1,    1,    5,    5,
    3,    3,    0,    4,    1,    4,    3,    3,    0,    3,
    0,    1,    1,    3,    1,    4,    1,    1,    2,    2,
    1,    2,    0,    2,    3,    0,    3,    0,    3,    0,
    1,    1,    2,    3,    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 927
#define YYNLSTATES 511
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
#line 176 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 181 "src/kinx.y"
{ kx_ast_root = yyval.obj = (YYASP(2-2).obj == NULL ? YYASP(1-2).obj : kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 5:
#line 186 "src/kinx.y"
{ yyval.obj = (YYASP(2-2).obj == NULL ? YYASP(1-2).obj : kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 16:
#line 203 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strval, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 17:
#line 204 "src/kinx.y"
{ yyerrok; yyval.obj = NULL; } break;
        case 25:
#line 215 "src/kinx.y"
{                       yyerrok; yyval.obj = NULL; } break;
        case 26:
#line 216 "src/kinx.y"
{ yy_restart(LBBR);     yyerrok; yyval.obj = NULL; } break;
        case 27:
#line 217 "src/kinx.y"
{ yy_restart(IF);       yyerrok; yyval.obj = NULL; } break;
        case 28:
#line 218 "src/kinx.y"
{ yy_restart(DO);       yyerrok; yyval.obj = NULL; } break;
        case 29:
#line 219 "src/kinx.y"
{ yy_restart(WHILE);    yyerrok; yyval.obj = NULL; } break;
        case 30:
#line 220 "src/kinx.y"
{ yy_restart(FOR);      yyerrok; yyval.obj = NULL; } break;
        case 31:
#line 221 "src/kinx.y"
{ yy_restart(TRY);      yyerrok; yyval.obj = NULL; } break;
        case 32:
#line 222 "src/kinx.y"
{ yy_restart(SWITCH);   yyerrok; yyval.obj = NULL; } break;
        case 33:
#line 223 "src/kinx.y"
{ yy_restart(CASE);     yyerrok; yyval.obj = NULL; } break;
        case 34:
#line 224 "src/kinx.y"
{ yy_restart(ENUM);     yyerrok; yyval.obj = NULL; } break;
        case 35:
#line 225 "src/kinx.y"
{ yy_restart(CLASS);    yyerrok; yyval.obj = NULL; } break;
        case 36:
#line 226 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; yyval.obj = NULL; } break;
        case 37:
#line 227 "src/kinx.y"
{ yy_restart(PRIVATE);  yyerrok; yyval.obj = NULL; } break;
        case 38:
#line 228 "src/kinx.y"
{ yy_restart(PUBLIC);   yyerrok; yyval.obj = NULL; } break;
        case 43:
#line 239 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 44:
#line 240 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 45:
#line 244 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 245 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 47:
#line 246 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 247 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 49:
#line 251 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strval); } break;
        case 50:
#line 255 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 51:
#line 259 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strval); } break;
        case 52:
#line 260 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strval, YYASP(3-3).intval); } break;
        case 53:
#line 261 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strval, -YYASP(4-4).intval); } break;
        case 54:
#line 262 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strval)); } break;
        case 55:
#line 263 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strval, YYASP(5-5).intval)); } break;
        case 56:
#line 264 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strval, -YYASP(6-6).intval)); } break;
        case 61:
#line 275 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 62:
#line 279 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 63:
#line 280 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 64:
#line 284 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 65:
#line 288 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 66:
#line 292 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 296 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 297 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 302 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 70:
#line 309 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 71:
#line 316 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 72:
#line 323 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 73:
#line 325 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 74:
#line 329 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 76:
#line 334 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 77:
#line 338 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 78:
#line 339 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, "_e", YYASP(2-2).obj, NULL); } break;
        case 79:
#line 340 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(3-5).strval, YYASP(5-5).obj, NULL); } break;
        case 80:
#line 344 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 81:
#line 345 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 82:
#line 349 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 83:
#line 350 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strval)); } break;
        case 84:
#line 351 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 85:
#line 352 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strval)); } break;
        case 86:
#line 356 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 87:
#line 357 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 88:
#line 361 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 89:
#line 365 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 90:
#line 366 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 91:
#line 367 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 92:
#line 368 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 93:
#line 372 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 94:
#line 376 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 95:
#line 380 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object(YYASP(1-1).strval, KX_OBJ_T), NULL); } break;
        case 96:
#line 381 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object(YYASP(3-3).strval, KX_OBJ_T), NULL); } break;
        case 97:
#line 385 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 98:
#line 389 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 99:
#line 390 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 100:
#line 394 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 102:
#line 399 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 104:
#line 404 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 106:
#line 409 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 107:
#line 410 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 108:
#line 411 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 109:
#line 412 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 110:
#line 413 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 111:
#line 414 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 415 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 416 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 417 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 418 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 419 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 420 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 421 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 119:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 122:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 123:
#line 432 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 124:
#line 433 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 125:
#line 434 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 126:
#line 435 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 127:
#line 436 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 128:
#line 437 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 130:
#line 442 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 132:
#line 447 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 133:
#line 451 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-4).obj, YYASP(4-4).obj, NULL); } break;
        case 134:
#line 452 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 135:
#line 453 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 137:
#line 458 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 138:
#line 459 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 141:
#line 465 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 145:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 146:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 147:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 148:
#line 472 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 149:
#line 473 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 150:
#line 474 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 151:
#line 479 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 152:
#line 480 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 153:
#line 481 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 154:
#line 482 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 155:
#line 483 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 156:
#line 484 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 158:
#line 489 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 159:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 160:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 161:
#line 492 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 162:
#line 493 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 163:
#line 497 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 164:
#line 498 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 165:
#line 499 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 166:
#line 500 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 167:
#line 501 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 168:
#line 502 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 169:
#line 503 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 170:
#line 504 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 171:
#line 505 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 172:
#line 506 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 173:
#line 510 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 174:
#line 511 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 177:
#line 520 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 181:
#line 530 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 185:
#line 540 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 187:
#line 545 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 189:
#line 550 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 191:
#line 555 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 193:
#line 560 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 565 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 197:
#line 570 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 571 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 200:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 578 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 203:
#line 579 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 580 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 206:
#line 585 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 207:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 209:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 210:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 212:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 213:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 214:
#line 599 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 216:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 218:
#line 609 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 219:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 220:
#line 611 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 221:
#line 612 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 222:
#line 613 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 223:
#line 614 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 225:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 226:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 227:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 228:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 229:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 230:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 231:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 233:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 235:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 236:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 237:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 238:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 239:
#line 639 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 240:
#line 640 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 241:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 243:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 244:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 245:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 246:
#line 652 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 247:
#line 653 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 248:
#line 654 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 249:
#line 658 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 250:
#line 659 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 251:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 252:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 253:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 254:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 255:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 256:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 257:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 258:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 264:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 265:
#line 677 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 266:
#line 678 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 267:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 268:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 269:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 270:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 271:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 272:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 273:
#line 688 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 274:
#line 689 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 275:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 276:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 277:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 278:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 279:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 280:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 281:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 282:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 283:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 284:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 285:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 286:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 287:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 288:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 289:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 290:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 291:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 292:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 293:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 294:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 295:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 296:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 297:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 298:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 299:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 300:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 301:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 302:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 303:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 304:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 305:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 306:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 307:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 308:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 309:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 310:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 311:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 312:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 313:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 314:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 315:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 316:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 317:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 318:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 319:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 320:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 321:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 322:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 323:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 324:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 325:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 326:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 327:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 328:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 329:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 330:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 331:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 332:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 333:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 334:
#line 761 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 335:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 336:
#line 769 "src/kinx.y"
{} break;
        case 338:
#line 774 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 339:
#line 775 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 340:
#line 779 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 341:
#line 780 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 343:
#line 785 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 344:
#line 786 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 345:
#line 787 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 346:
#line 788 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 347:
#line 789 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 349:
#line 794 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 351:
#line 799 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 352:
#line 800 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 353:
#line 801 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 355:
#line 806 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 356:
#line 810 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 357:
#line 811 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 358:
#line 812 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 359:
#line 813 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 360:
#line 814 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 362:
#line 819 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 364:
#line 824 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 365:
#line 825 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 366:
#line 826 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 367:
#line 827 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 368:
#line 828 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 369:
#line 829 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 370:
#line 830 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 371:
#line 831 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 372:
#line 832 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 373:
#line 833 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 374:
#line 834 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 375:
#line 835 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 376:
#line 836 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 377:
#line 837 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 378:
#line 838 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 379:
#line 839 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 380:
#line 840 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 381:
#line 841 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 382:
#line 842 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 383:
#line 843 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 384:
#line 844 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 385:
#line 845 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 386:
#line 846 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 387:
#line 847 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 388:
#line 848 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 389:
#line 849 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 390:
#line 850 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 391:
#line 851 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 392:
#line 852 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 393:
#line 853 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 394:
#line 854 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 395:
#line 855 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 396:
#line 856 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 397:
#line 857 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 398:
#line 861 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 399:
#line 862 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 400:
#line 863 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 401:
#line 864 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 402:
#line 865 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 403:
#line 866 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 404:
#line 867 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 405:
#line 868 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 406:
#line 869 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 407:
#line 870 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 408:
#line 871 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 409:
#line 872 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 410:
#line 873 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 411:
#line 874 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 412:
#line 875 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 413:
#line 876 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 414:
#line 877 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 415:
#line 878 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 416:
#line 879 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 417:
#line 880 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 418:
#line 881 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 419:
#line 882 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 420:
#line 883 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 421:
#line 884 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 422:
#line 885 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 423:
#line 886 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 424:
#line 887 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 425:
#line 888 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 426:
#line 889 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 427:
#line 890 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 428:
#line 891 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 429:
#line 892 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 430:
#line 893 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 431:
#line 894 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 432:
#line 895 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 433:
#line 896 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 434:
#line 897 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 435:
#line 898 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 436:
#line 899 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 437:
#line 900 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 438:
#line 901 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 439:
#line 902 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 440:
#line 903 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 441:
#line 904 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 442:
#line 905 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 443:
#line 906 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 444:
#line 907 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 445:
#line 908 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 446:
#line 909 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 447:
#line 910 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 448:
#line 911 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 449:
#line 912 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 450:
#line 913 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 451:
#line 917 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 452:
#line 918 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 453:
#line 919 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 454:
#line 923 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 455:
#line 927 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 456:
#line 931 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 457:
#line 932 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 459:
#line 937 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 460:
#line 941 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 461:
#line 942 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 462:
#line 943 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 463:
#line 944 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 464:
#line 945 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 465:
#line 946 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 467:
#line 951 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 468:
#line 955 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 469:
#line 956 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 470:
#line 960 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 471:
#line 961 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 472:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 473:
#line 966 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 474:
#line 970 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 475:
#line 971 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 476:
#line 975 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 477:
#line 976 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 478:
#line 977 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 479:
#line 978 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 480:
#line 979 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 481:
#line 980 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 482:
#line 981 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 483:
#line 985 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 484:
#line 986 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 485:
#line 987 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 488:
#line 996 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 489:
#line 997 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 490:
#line 1001 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 491:
#line 1002 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 492:
#line 1006 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 493:
#line 1008 "src/kinx.y"
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
#line 1024 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 496:
#line 1025 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 497:
#line 1026 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 498:
#line 1030 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 499:
#line 1031 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 500:
#line 1035 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 503:
#line 1041 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 504:
#line 1045 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 505:
#line 1046 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 506:
#line 1047 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 507:
#line 1048 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 508:
#line 1049 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 509:
#line 1053 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 510:
#line 1054 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 511:
#line 1055 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 512:
#line 1059 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 513:
#line 1060 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 514:
#line 1061 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 515:
#line 1065 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 516:
#line 1066 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 517:
#line 1070 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 518:
#line 1071 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 519:
#line 1075 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 522:
#line 1081 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 523:
#line 1082 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 524:
#line 1083 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 527:
#line 1089 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 528:
#line 1093 "src/kinx.y"
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
