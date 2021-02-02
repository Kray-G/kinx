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
  790,  791,  792,  793,  794,  795,  796,  797,  798,  799,
  800,  801,  802,  804,  803,  111,  805,  806,  807,  816,
  818,  817,  226,  826,  827,  828,  830,  832,  187,  188,
  131,  132,  824,  825,  121,   81,   82,   83,   84,   85,
   86,   87,   88,   89,   90,   91,   92,   93,  348,   16,
  349,  819,  820,  821,  114,  822,  823,  350,  369,  348,
   16,  349,   50,    0,   30,  814,-32766,  815,  350,  808,
  809,  810,  811,  812,  813,  416,  788,   39,  161,  162,
  540,  789,  542,  541,  543,  405,  544,   95,   41,  568,
  834,  545,  546,  406,   66,  547,  839,  840,  838,  503,
  829,  831,  833,  835,  836,  837,  911,  912,  913,  914,
  915,  916,  917,  918,  919,  920,  921,  922,  923,  251,
  924, -360,  925,  926,  927,  935,  937,  936, -360,  947,
  948,  949,  951,  953,    5,  762,  763,   41,  945,  946,
   39,  114,   44,  116,   43,  548,   60,  163, 1023,   50,
  549,   30,  551,  550,  113,  320,  580,  938,  939,  940,
  321,  941,  942,  539,  530,  786,  133,  134,  135,  538,
  787,  933,  125,  934,   99,   39,  928,  929,  930,  931,
  932,-32766,  999,    4,  115,  108,  369,  943,  944,  113,
  110,  385,   51,   48,   31,   27,  955,   41,   49,  386,
   28,   69,  960,  961,  959,  237,  950,  952,  954,  956,
  957,  958,  167,  390,  878,  391,   10,  392,  882,  312,
  884,  885,  233,  234,  393,  106,  351,  890,  352,  159,
  230,  231,  313,   54,   61,  298,  122,  102,-32766,-32766,
-32766,  136,  137,  325,-32766,  142,  143,  144,  294,  293,
-32766,  140,   41,   44, 1040,   43,  161,  138,  139,  235,
   39, -102, -102,  141,  394,  395,  396,-32766,  266,  908,
  121,   19,  607,   79,  420,  300,  301,  353,  397,  355,
  398,  357,   96,  267,  268,   35,   36,   37,    4,  399,
  108,-32766,  275,  408,  400,  910,  250,  556,   48, 1040,
   27,  404,  -98,  779,   80,   39,   59,   39,  151,  152,
  160,  249,  877,  878,  879,  880,  881,  882,  883,  884,
  885,  886,  887,  888,  889,   80,  890,   41,  891,  892,
  893,  901,  903,  902,  565,  853,  482,  149,  150,  -75,
   38,  107,   41,   41,  484,  681,  682,  683,   41, -390,
  100,  843, -389,  430,   98,  -74,  853,  161,-32766,   39,
  322,  378,  107,  904,  905,  906,   80,  907,  908,  121,
  786,  127,   79,  680,  678,  787,  126,  899,  345,  900,
  119,  679,  894,  895,  896,  897,  898,   63,  414,   41,
  145,  846,  446,  400,  910,  308,  309,  854,  421,  785,
  479,  310,  294,  107,  293,  415,  609,  562,  167,  347,
  416,  348,   16,  349,  608,  297,  311,  383,  245,  246,
  350,  103,  351,  485,  352, 1027,  227,  228,  509,   64,
  104,  298,  986,  452,  453,  384,  418,  566,  454,  487,
 1010,  423,  462,  451,   40,  232,   41,  569,   43,  677,
  639,  674,  659,  751,  783,    0,   39,  306,   29,    7,
  186,  252,    6,  275,  253,   38,  121,   41,    5, 1026,
  864,  300,  301,  353,  354,  355,  356,  357,  635,  254,
  255,   32,   33,   34,  866,  359,  848,  563,  757,  756,
  529,  473,  489,  556,  841,  128,  844,  962,  -98,  167,
  347, 1008,  348,   16,  349,  672,  297,  249,  637,  245,
  246,  350,  103,  351,  749,  352,  599,  227,  228,  509,
   64,  104,  298,  291,  287,  101,   74,   68,   67,  461,
  167,  347,  606,  348,   16,  349,  598,  297,  596,  578,
  245,  246,  350,  103,  351,  970,  352,  969,  227,  228,
  509,   64,  104,  298,  597,  253,  595,  120,  610,  600,
   75,   73,  300,  301,  353,  354,  355,  356,  357,   72,
  254,  255,   32,   33,   34,   71,  359,   70,  601,   57,
  129,  112,   45,   53,  758,  455,  253,  218,  124,  -98,
  109,  202,    8,  300,  301,  353,  354,  355,  356,  357,
   62,  254,  255,   32,   33,   34, -393,  359,  692,  581,
  512,  238,  236,  229,  123,  758, -396,   56,   55,   42,
  -98,  167,  347,    8,  348,   16,  349, -388,  297, -391,
 -392,  245,  246,  350,  103,  351,  209,  352,  216,  227,
  228,  509,   64,  104,  298,  380,  379,  239,  217,  215,
  214,   -1,  167,  347,  213,  348,   16,  349,  212,  297,
  211,  210,  245,  246,  350,  103,  351,  208,  352,  207,
  227,  228,  509,   64,  104,  298,  206,  253,  205,  204,
  203,  201,  200,  199,  300,  301,  353,  354,  355,  356,
  357,   97,  254,  255,   32,   33,   34,   94,  359,   78,
   77,   76,   52,  422,  450,    0,  778,  617,  253,  491,
  323,  -98,   21,   20, -367,  300,  301,  353,  354,  355,
  356,  357,   18,  254,  255,   32,   33,   34,   17,  359,
 1031, 1029,  675,  167,  347,  777,  348,   16,  349,  684,
  297,  640,  -98,  245,  246,  350,  103,  351, 1012,  352,
  752,  227,  228,  509,   64,  104,  298,  968,  842,  780,
  963,  167,  347,  501,  348,   16,  349,  488,  297,  480,
  472,  245,  246,  350,  103,  351,  469,  352,  346,  227,
  228,  509,   64,  104,  298,  344,  343,  342,  341,  253,
  340,  339,  338,  337,  336,  335,  300,  301,  353,  354,
  355,  356,  357,  333,  254,  255,   32,   33,   34,  331,
  359,  330,  329,   24,   23,   22,    3,  253,  558,    2,
    0,  130,    0,  -98,  300,  301,  353,  354,  355,  356,
  357,  845,  254,  255,   32,   33,   34,    0,  359,    0,
    0,    0,    0,    0,    0,    0,  557,    0,    0,  167,
  347,  -98,  348,   16,  349,    0,  297,    0,    0,  245,
  246,  350,  103,  351,    0,  352,    0,  227,  228,  509,
   64,  104,  298,    0,    0,    0,    0,  167,  347,    0,
  348,   16,  349,    0,  297,    0,    0,  245,  246,  350,
  103,  351,    0,  352,    0,  227,  228,  509,   64,  104,
  298,    0,    0,    0,    0,  253,    0,    0,    0,    0,
    0,    0,  300,  301,  353,  354,  355,  356,  357,    0,
  254,  255,   32,   33,   34,    0,  359,    0,    0,    0,
    0,    0,    0,  253,  556,    0,    0,    0,    0,  -98,
  300,  301,  353,  354,  355,  356,  357,    0,  254,  255,
   32,   33,   34,    0,  359,    0,    0,    0,    0,    0,
    0,    0,  761,    0,    0,  167,  347,  -98,  348,   16,
  349,    0,  297,    0,    0,  245,  246,  350,  103,  351,
    0,  352,    0,  227,  228,  509,   64,  104,  298,    0,
    0,    0,    0,  167,  347,    0,  348,   16,  349,    0,
  297,    0,    0,  245,  246,  350,  103,  351,    0,  352,
    0,  227,  228,  509,   64,  104,  298,    0,    0,    0,
    0,  253,    0,    0,    0,    0,    0,    0,  300,  301,
  353,  354,  355,  356,  357,    0,  254,  255,   32,   33,
   34,    0,  359,    0,    0,    0,    0,    0,    0,  253,
  760,    0,    0,    0,    0,  -98,  300,  301,  353,  354,
  355,  356,  357,    0,  254,  255,   32,   33,   34,    0,
  359,    0,    0,    0,    0,    0,    0,    0,  759,    0,
    0,  167,  347,  -98,  348,   16,  349,    0,  297,    0,
    0,  245,  246,  350,  103,  351,    0,  352,    0,  227,
  228,  509,   64,  104,  298,    0,    0,    0,    0,  167,
  347,    0,  348,   16,  349,    0,  297,    0,    0,  245,
  246,  350,  103,  351,    0,  352,    0,  227,  228,  509,
   64,  104,  298,    0,    0,    0,    0,  253,    0,    0,
    0,    0,    0,    0,  300,  301,  353,  354,  355,  356,
  357,    0,  254,  255,   32,   33,   34,    0,  359,    0,
    0,    0,    0,    0,    0,  253,  561,    0,    0,    0,
    0,  -98,  300,  301,  353,  354,  355,  356,  357,    0,
  254,  255,   32,   33,   34,    0,  359,    0,    0,    0,
    0,    0,    0,    0,  560,    0,    0,  167,  347,  -98,
  348,   16,  349,    0,  297,    0,    0,  245,  246,  350,
  103,  351,    0,  352,    0,  227,  228,  509,   64,  104,
  298,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  105,    0,    0,    0,  158,    0,    0,    0,    0,    0,
    0,    0,    0,  253,    0,    0,    0,    0,  153,  154,
  300,  301,  353,  354,  355,  356,  357,  510,  254,  255,
   32,   33,   34,    0,  359,    0,    0,    0,    0,  767,
  769,  770,  559,  372,    0,    0,    0,  -98,    0,  299,
    0,    0,    0,    0,    0,    0,    0,  986,  373,  374,
    0,    0,    0,  358,  786,    0,  771,  766,  764,  787,
    0,    1,    0,   43,    0,  765,    0,    0,  155,    0,
    0,   58,    0,   25,    0,    0,  248,    0,  302,    0,
  156,  146,  511,    0,  147,  148,   26,  167,  347,    0,
  348,   16,  349,    0,  297,    0,    0,  245,  246,  350,
  103,  351,    0,  352,    0,  227,  228,  509,   64,  104,
  298,-32766,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,-32766,
-32766,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  253,    0,    0,    0,    0,    0,    0,
  300,  301,  353,  354,  355,  356,  357,    0,  254,  255,
   32,   33,   34,    0,  359,    0,    0,    0,-32766,-32766,
-32766,    0,    0,    0,-32766,    0,    0,  -98,    0,    0,
    0,    0,   41,    0,    0,    0,    0,    0,    0,-32766,
    0,    0,    0,    0,    0,    0,    0,-32766,    0,    0,
    0,-32766,-32766,    0,    0,-32766,-32766
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1457

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   23,   18,   19,   20,   21,
   22,   23,   19,   25,   26,   27,   28,   29,   61,   62,
   25,   26,   34,   35,   59,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,    4,    5,
    6,   53,   54,   55,   87,   57,   58,   13,    2,    4,
    5,    6,   95,    0,   97,   67,   14,   69,   13,   71,
   72,   73,   74,   75,   76,  100,   78,   85,   16,   30,
    2,   83,    4,    5,    6,   87,    8,   90,   85,   82,
   92,   13,   14,   95,   91,   17,   98,   99,  100,   92,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   62,
   16,   86,   18,   19,   20,   21,   22,   23,   93,   25,
   26,   27,   28,   29,   85,   32,   33,   85,   34,   35,
   85,   87,   85,   94,   87,   67,   90,   98,   71,   95,
   72,   97,   74,   75,   99,   78,   94,   53,   54,   55,
   83,   57,   58,   85,   86,   78,   27,   28,   29,   91,
   83,   67,   37,   69,   62,   85,   72,   73,   74,   75,
   76,   14,   78,   85,   87,   87,    2,   83,   84,   99,
   87,   87,   95,   95,   97,   97,   92,   85,   95,   95,
   97,   90,   98,   99,  100,   94,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,  101,   62,   71,   72,
   73,  102,  103,    3,   77,  105,  106,  107,   78,   78,
   59,   92,   85,   85,   79,   87,   16,   34,   35,   56,
   85,   91,   91,  104,   53,   54,   55,  100,   57,   58,
   59,    3,   91,   62,   93,   64,   65,   66,   67,   68,
   69,   70,   62,   72,   73,   74,   75,   76,   85,   78,
   87,  100,   85,    4,   83,   84,    9,   86,   95,   79,
   97,   79,   91,   96,   62,   85,   95,   85,   61,   62,
   18,  100,    2,    3,    4,    5,    6,    7,    8,    9,
   10,   11,   12,   13,   14,   62,   16,   85,   18,   19,
   20,   21,   22,   23,   82,   93,   79,   51,   52,    7,
   85,   99,   85,   85,   92,   53,   54,   55,   85,   94,
    7,   88,   94,   79,    7,    7,   93,   16,   14,   85,
   10,   19,   99,   53,   54,   55,   62,   57,   58,   59,
   78,   31,   62,   81,   82,   83,   30,   67,   59,   69,
   59,   89,   72,   73,   74,   75,   76,   95,   78,   85,
   36,   60,   78,   83,   84,   78,   78,   93,   78,   84,
   78,   78,   78,   99,   78,   95,   78,   78,    1,    2,
  100,    4,    5,    6,   78,    8,   78,   78,   11,   12,
   13,   14,   15,   78,   17,   88,   19,   20,   21,   22,
   23,   24,   71,   72,   73,   78,   78,   82,   77,   79,
   84,   79,   79,   79,   85,   93,   85,   82,   87,   96,
   84,   84,   84,   84,   84,   -1,   85,   85,   97,   85,
   99,  100,   85,   85,   57,   85,   59,   85,   85,   88,
   86,   64,   65,   66,   67,   68,   69,   70,   86,   72,
   73,   74,   75,   76,   86,   78,   86,   86,   86,   86,
   91,   87,   87,   86,   88,   98,   88,   88,   91,    1,
    2,   88,    4,    5,    6,   88,    8,  100,   88,   11,
   12,   13,   14,   15,   88,   17,   91,   19,   20,   21,
   22,   23,   24,   90,   90,   90,   90,   90,   90,   90,
    1,    2,   91,    4,    5,    6,   91,    8,   91,   91,
   11,   12,   13,   14,   15,   91,   17,   91,   19,   20,
   21,   22,   23,   24,   91,   57,   91,   59,   91,   91,
   91,   91,   64,   65,   66,   67,   68,   69,   70,   91,
   72,   73,   74,   75,   76,   91,   78,   91,   91,   94,
   99,   93,   93,   93,   86,   93,   57,   93,   59,   91,
   93,   95,   94,   64,   65,   66,   67,   68,   69,   70,
   93,   72,   73,   74,   75,   76,   94,   78,   94,   94,
   94,   94,   94,   94,   94,   86,   94,   94,   94,   94,
   91,    1,    2,   94,    4,    5,    6,   94,    8,   94,
   94,   11,   12,   13,   14,   15,   95,   17,   95,   19,
   20,   21,   22,   23,   24,   95,   95,   95,   95,   95,
   95,    0,    1,    2,   95,    4,    5,    6,   95,    8,
   95,   95,   11,   12,   13,   14,   15,   95,   17,   95,
   19,   20,   21,   22,   23,   24,   95,   57,   95,   95,
   95,   95,   95,   95,   64,   65,   66,   67,   68,   69,
   70,   95,   72,   73,   74,   75,   76,   95,   78,   95,
   95,   95,   95,   95,   95,   -1,   96,   96,   57,   96,
   96,   91,   96,   96,   94,   64,   65,   66,   67,   68,
   69,   70,   96,   72,   73,   74,   75,   76,   96,   78,
   96,   96,   96,    1,    2,   96,    4,    5,    6,   96,
    8,   96,   91,   11,   12,   13,   14,   15,   96,   17,
   96,   19,   20,   21,   22,   23,   24,   96,   96,   96,
   96,    1,    2,   96,    4,    5,    6,   96,    8,   96,
   96,   11,   12,   13,   14,   15,   96,   17,   96,   19,
   20,   21,   22,   23,   24,   96,   96,   96,   96,   57,
   96,   96,   96,   96,   96,   96,   64,   65,   66,   67,
   68,   69,   70,   96,   72,   73,   74,   75,   76,   96,
   78,   96,   96,   96,   96,   96,   96,   57,   86,   96,
   -1,  100,   -1,   91,   64,   65,   66,   67,   68,   69,
   70,  103,   72,   73,   74,   75,   76,   -1,   78,   -1,
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
   24,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   14,   -1,   -1,   -1,   18,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   32,   33,
   64,   65,   66,   67,   68,   69,   70,   41,   72,   73,
   74,   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   53,
   54,   55,   86,   57,   -1,   -1,   -1,   91,   -1,   63,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   71,   72,   73,
   -1,   -1,   -1,   77,   78,   -1,   80,   81,   82,   83,
   -1,   85,   -1,   87,   -1,   89,   -1,   -1,   92,   -1,
   -1,   95,   -1,   97,   -1,   -1,  100,   -1,  102,   -1,
  104,  105,  106,   -1,  108,  109,  110,    1,    2,   -1,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   -1,   17,   -1,   19,   20,   21,   22,   23,
   24,   14,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   32,
   33,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,
   64,   65,   66,   67,   68,   69,   70,   -1,   72,   73,
   74,   75,   76,   -1,   78,   -1,   -1,   -1,   71,   72,
   73,   -1,   -1,   -1,   77,   -1,   -1,   91,   -1,   -1,
   -1,   -1,   85,   -1,   -1,   -1,   -1,   -1,   -1,   92,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  100,   -1,   -1,
   -1,  104,  105,   -1,   -1,  108,  109
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1336,  211,  498,  529,  407,  848,  732, 1196,  992,  651,
  620,  760, 1108, 1080,  964,  876, 1336, 1336, 1336, 1336,
 1336, 1336, 1336, 1336, 1336,  370,  315,  369,  366,  368,
  367,  356,  104,  104,  104,  104,  104,  104,  384,  392,
  398,  310,   55,  263,  191,  191,  242,  304,  220,  220,
  220,  220,    3,  175,  255,   90,   90,   90,  222,  274,
   -8,  258,  112,  257,  380,  380,  380,  371,  371,  371,
  380,  380,  380,  380,  371,  380,  382,  382,  382,  371,
  371,  371,  371,  371,  371,  371,  371,  371,  371,  371,
  371,  371,  371,  371,  382,  371,  371,  382,  382,  371,
  382,  371,  371,  382,  382,  382,  382,  382,  382,  359,
  382,  382,  382,  382,  382,  382,  344,  344,  344,  344,
  344,   52,   52,   52,   52,  167,  167,  167,  167,  167,
  167,  167,  167,  167,  167,  167,  167,  167,  167,  167,
  167,  167,  167,  167,  167,  167,  167,  167,  167,  167,
  167,  167,  167, 1347, 1347, 1347, 1347, 1347, 1347, 1347,
 1347,  361,  361,  361,   62,   56,  341,   78,  610,  426,
  420,  353,  417,  413,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,  292,  292,  292,  203,
  207,  -33,   98,   98,   98,   98,  378,  378,  378,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   49,
   54,   54,   54,  139,  139,  139,  168,  168,  168,   44,
  168,  168,  168,  171,  170,   77,   77,   77,   77,   77,
   97,  140,  140,  140,  348,  326,  324,  240,  496,  541,
  609,   87,  543,  342,  339,  357,  135,    5,  223,  159,
  286,  247,  111,  456,  454,  181,  342,  339,  357,   35,
  314,  632,  626,  486,  614,  -25,    5,  223,  223,  223,
  223,  223,  159,  159,  286,  484,  611,  252,  613,  617,
  616,    7,  184,  184,  184,  184,  184,  383,  336,  550,
  329,  329,  728,  518,  287,  518,  358,  550,  585,  585,
  383,  383,  383,  533,  489,  550,  350,  492,  516,  516,
  404,  404,  383,  383,  518,  514,  552,  383,  383,  383,
  383,  383,  514,  383,  552,  383,  383,  383,  383,  383,
  383,  383,  383,  383,  383,  383,  383,  606,  605,  607,
  604,  515,  372,  468,  317,  318,  323,  338,  586,  519,
   63,  467,  346,  340,  397,  481,  721,  354,  289,  602,
  465,  463,  551,  588,  587,  438,  437,  497,  320,  608,
  362,  377,  374,  584,  583,  409,  664,  581,  574,  572,
  606,  605,  607,  604,  535,  536,  512,  317,  323,  525,
  522,  524,  408,  507,  663,  406,  662,  487,  596,  347,
  332,  348,  447,  445,  523,  364,  565,  566,  434,  441,
  328,  439,  363,  661,  517,  716,  494,  715,  713,  403,
  680,  400,  507,  674,  331,  346,  520,  340,  397,  481,
  721,  354,  354,  354,  654,  490,  563,  343,  438,  478,
  322,  673,  559,  555,  554,  345,  401,  435,  435,  435,
  425,  360,  671,  652,  707,  699,  698,  697,  696,  485,
  723,  645,  321,  381,  405,  405,  695,  268,  470,  694,
  485,  720,  643,  553,  355,  433,  436,  399,  639,  337,
  692,  448,  469,  719,  691,  690,  689,  667,  636,  635,
  718,  319,  682,  365,  435,  402,  717,  402,  634,    0,
    0,    0,    0, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,   -2,   -2,
   -2,   -2,   -2,   -2,   -2,    0,    0,    0,    0,    0,
    0,  310,  310,  310,    0, 1226, 1226,  310,  310, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226, 1226,
 1226, 1226, 1226, 1226,  292,  292,  292,   -3,   -3,   -3,
    0,   -3,   -3,   -3,   -3,   -3,   -3,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  103,  103,  103,  103,  103,  103,  103,  103,
  103,  103,   87,   87,   87,   87,   87,   87,   87,   87,
   87,   87,   87,   87,   87,   87,   87,   87,   87,   87,
   87,   87,  184,  103,  103,  103,    0,    0,    0,   87,
   87,   87,    0,   87,   87,   87,  184,  184,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  111,  184,  184,
    0,  383,  383,  383,    0,  383,  551,  588,  587,    0,
    0,    0,    0,    0,    0,    0,  352,  352,    0,  551,
  588,  587,    0,  566,  488,  488,  488,  488,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  352,  488,
    0,  488,  488,  488
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 291

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  383,  384,  385,32767,32767,
32767,32767,32767,32767,32767,  337,32767,32767,  519,  519,
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
  215,  217,  460,32767,32767,32767,  394,  381,  382,  255,
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
  260,  255,32767,32767,  273,32767,32767,32767,   51,32767,
32767,32767,32767,32767,  504,32767,  501,32767,32767,32767,
32767,32767,  339,32767,32767,  185,32767,  187,  189,  191,
  193,  212,  213,  214,32767,  520,32767,32767,   75,32767,
32767,32767,32767,32767,32767,  337,32767,  464,  465,  462,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  267,
32767,32767,32767,32767,  511,  509,32767,   62,32767,32767,
32767,32767,32767,32767,32767,   54,  461,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  463,  480,32767,32767,32767,  528,
  454,  454,  528
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  181,  176,  269,  574,  176,  176,  179,  179,  179,  179,
  177,  179,  174,  181,  181,  181,  168,  168,  410,  175,
  182,  171,  174,  174,  174,  471,  498,  508,  174,  174,
  174,  174,  417,  174,  177,  177,  177,  458,  459,  873,
  873,  873,  873,  504,  868,  873,  873,  656,  656,  656,
  434,  483,  177,  411,  432,  177,  177,  871,  177,  869,
  435,  164,  175,  166,  164,  178,  169,  180,  170,  183,
  184,  185,  172,  173, 1036,  689,  689,  689,  993,  505,
  429,  436,  694,  507,  438, 1020, 1020, 1020, 1020, 1020,
 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 1020, 1020, 1020, 1020, 1020,  784,  750,  638,  658,  673,
 1009,  437,  376,  376,  376,  439,  376,  376,  376,  388,
  389,  515,  388,  389,  657,  657,  657,  655,  655,  655,
  516,  368,  518,  518,  518,  518,  518,  368,  477,  577,
  576,  585,  586,  584,  583,  582,  965,  690,  690,  690,
  994,  994,  755,  641,  964,  755,  755,  755,  755,  641,
  641,  641,  676,  676,  676, 1019, 1019, 1019, 1019, 1019,
 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019,
 1019, 1019, 1019, 1019, 1019,  687,  648,  676,  676,  676,
  574,  440,  448,  375,  375,  276,  375,  375,  375,  284,
  424,  424,  424,  424,  424,  424,  424,  424,  424,  424,
  424,  424,  424,  424,  424,  424,  424,  424,  424,  424,
  754,  224,  225,  754,  754,  754,  754,  244,  262,  262,
  198,  262,  262,  262,  282,  283,  197,  197,  197,  197,
 1016,  197,  332,  198,  198,  198,  190,  190,  242,  243,
  690,  647, 1021,  303,  303,  303,  303,  303,  303,  303,
  303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
  303,  303,  303,  303,  303,  303,  303,  303,  633,  995,
  995,  591,  447,  669,  972,  633,  633,  633,  645,   14,
   14,  382,  633,   12,   13,   15,  456,  633,  633,  633,
  633,  633,  633,  633,  633,  633,  633,  633,  633,  633,
  633,  633,  319,  633,  633,  636,  671,  633,  475,  633,
  633,  636,  636,  636,  192,  193,  194,  195,  304,  296,
  449,  612,  328,  315,  478,  492,  493,  500,  118,  506,
  157, 1003, 1004,  304, 1018,  671,  671,  671,  277,  278,
  279,  280,  281,  594,  579,  441,  442,  443, 1001, 1002,
  989,  990,  991,  619,  983,    0,  984,  996,  997,  998,
  992,  592,  985,  664,  665,  666,  668,  667, 1007,  781,
  781,  685,  872,  857,  622,  623,  624,  625,  626,  627,
  628,  629,  630,  631,  632,  620,  621,    0,  619, 1035,
  371,    0,  860,    0,  980, 1037,  988,  326,  334,  499,
  651,  650,  371,    0,  324,  324,  324,  427,  428,  433,
  463,  464,  465,  466,  467,  468,  470,  476,  481,  490,
  494,  495,  496,  497,  502,  742,  738,  739,  731,  732,
  734,  736,  220,  221,  222,  271,  272,  274,  285,    0,
  264,    0,    0,  264,    0,    0,    0,    0,  407,  412,
  413,  419,  460,  286,    0,    0,  288,  289,    0,  290
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 470

static char yygcheck[] = {
   36,   36,   74,   34,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   62,   36,
   36,   36,   36,   36,   36,   98,   98,   98,   36,   36,
   36,   36,  101,   36,   36,   36,   36,   81,   81,   74,
   74,   74,   74,   81,   72,   74,   74,   63,   63,   63,
   66,  101,   36,   74,   67,   36,   36,   73,   36,   73,
   43,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,  100,   40,   40,   40,   40,   40,
   40,   40,   40,   40,   45,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   58,   58,   58,   58,   58,
   58,   44,   63,   63,   63,   46,   63,   63,   63,   76,
   76,    4,   76,   76,   97,   97,   97,   62,   62,   62,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,   65,    7,    7,    7,
    7,    7,   97,   97,   65,   97,   97,   97,   97,   97,
   97,   97,   74,   74,   74,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,  115,  115,   74,   74,   74,
   34,   47,   62,   62,   62,   48,   62,   62,   62,   54,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
    7,   49,   49,    7,    7,    7,    7,   74,   74,   74,
   38,   74,   74,   74,   51,   51,   38,   38,   38,   38,
   95,   38,   31,   38,   38,   38,   38,   38,   52,   52,
    7,  116,   74,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,  106,    7,
    7,    7,   19,    7,   80,  106,  106,  106,  108,    3,
    3,    9,  106,    3,    3,    3,  117,  106,  106,  106,
  106,  106,  106,  106,  106,  106,  106,  106,  106,  106,
  106,  106,   91,  106,  106,   59,   59,  106,  103,  106,
  106,   59,   59,   59,   57,   57,   57,   57,    7,   39,
   39,   30,   89,  120,   39,   39,   39,   39,  118,   39,
  105,    7,    7,    7,  104,   59,   59,   59,   50,   50,
   50,   50,   50,    7,    7,   53,   53,   53,    7,    7,
    7,    7,    7,   37,    7,   -1,    7,    7,    7,    7,
    7,    7,    7,    7,    7,    7,    7,    7,   60,   60,
   60,   60,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   -1,   37,   37,
   30,   -1,   37,   -1,   37,   37,  102,  102,  102,  102,
  110,  110,   30,   -1,   82,   82,   82,   93,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   93,   93,   93,   93,   93,   55,   55,   55,   55,   55,
   55,   55,  111,  111,  111,   69,   69,   69,   79,   -1,
   79,   -1,   -1,   79,   -1,   -1,   -1,   -1,   30,   30,
   30,   30,   30,   69,   -1,   -1,   69,   69,   -1,   69
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  287,  121,    0,    0,   31,    0,  -10,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   56,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  166,   23,    0,    0,  -39,    0,  -42,  303,  188,  264,
  -41,    0,    0,  -65,  -15,  -43,  -13,   62,   65,   90,
  215,   96,  108,  213,   54,  289,    0,  171,   79,  125,
  221,    0,  -34, -114,    0, -161,    4,    7,    0,  369,
    0,    0,   -1,    2,    1,    0,   86,    0,    0,  222,
   52,  -31,  253,    0,    0,    0,    0,    0,    0,   13,
    0,    3,    0,  217,    0,   22,    0,  -37,  -24,    0,
   21, -273,  170,   -3,   10, -172,  218,    0,   41,    0,
  248,  256,    0,    0,    0,   68,   32,  -21,    6,    0,
 -178
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  360,    9,   11,  517,  520,  519,  521,  522,  381,
  523,  317,  536,  524,  552,  553,  554,  525,  555,  409,
  526,  316,  589,  531,  532,  292,  533,  534,  265,  535,
  370,  616,  537,  527,  528,  361,  165,  979,  196,  295,
  642,  693,  256,  362,  363,  364,  365,  366,  257,  223,
  258,  259,  241,  367,  260,  261,  737,  189,  782,  748,
  747,  772,  773,  774,  775,  966,  402,  403,   47,  273,
  377,  314,  867,  870,  768,  401,  387, 1000,  570,  263,
  971,  457,  305,  571,  981,  695,  982,  572,  573,  327,
  240,  318, 1006,  425,  426, 1015,  753,  776,  444,  445,
 1034,  270,  746,  474,  486,   65,  618,  247,  644,  219,
  649,  191,  652,  670,  643,  646,  688,  431,  117,   46,
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

#define YYSTATES 934
#define YYNLSTATES 513
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
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
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
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-1).strval, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T)); } break;
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
