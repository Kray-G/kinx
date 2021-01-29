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
#line 1078 "src/kinx.y"

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
  "'?'",
  "'|'",
  "'^'",
  "'&'",
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
  "ForInVariable : LMBR ArrayItemList RMBR",
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
  "ReturnStatement : RETURN GetLineNumber CaseWhenExpression Modifier_Opt ';'",
  "ReturnStatement : SYSRET_NV ';'",
  "YieldStatement : YieldExpression Modifier_Opt ';'",
  "YieldExpression : YIELD AssignExpression",
  "YieldExpression : YIELD CaseWhenExpression",
  "YieldExpression : YIELD",
  "YieldExpression : AssignExpression '=' YIELD AssignExpression",
  "YieldExpression : AssignExpression '=' YIELD CaseWhenExpression",
  "YieldExpression : AssignExpression '=' YIELD",
  "ThrowStatement : THROW AssignExpressionList_Opt Modifier_Opt ';'",
  "MixinStatement : MIXIN MixinModuleList ';'",
  "MixinModuleList : NAME",
  "MixinModuleList : MixinModuleList ',' NAME",
  "ExpressionStatement : AssignExpression_Opt ';'",
  "AssignExpression_Opt : /* empty */",
  "AssignExpression_Opt : AssignExpression Modifier_Opt",
  "AssignExpression_Opt : CASE AssignExpression WhenClauseList CaseElseClause",
  "AssignExpressionList_Opt : /* empty */",
  "AssignExpressionList_Opt : AssignExpressionObjList",
  "Modifier_Opt : /* empty */",
  "Modifier_Opt : IF '(' AssignExpressionList ')'",
  "CaseWhenExpression : CASE AssignExpression WhenClauseList CaseElseClause",
  "WhenClauseList : WhenClause",
  "WhenClauseList : WhenClauseList WhenClause",
  "WhenClause : WHEN WhenConditionRange Modifier_Opt Colon_Opt WhenClauseBody",
  "WhenConditionRange : WhenPostfixExpression",
  "WhenConditionRange : LMBR ArrayItemList RMBR",
  "WhenConditionRange : LBBR ArrayItemList RBBR",
  "WhenConditionRange : WhenPostfixExpression DOTS2",
  "WhenConditionRange : WhenPostfixExpression DOTS2 WhenPostfixExpression",
  "WhenConditionRange : WhenPostfixExpression DOTS3",
  "WhenConditionRange : WhenPostfixExpression DOTS3 WhenPostfixExpression",
  "WhenPostfixExpression : WhenCondition",
  "WhenPostfixExpression : WhenPostfixExpression PostIncDec",
  "WhenPostfixExpression : WhenPostfixExpression LMBR AssignExpression RMBR",
  "WhenPostfixExpression : WhenPostfixExpression '.' PropertyName",
  "WhenPostfixExpression : WhenPostfixExpression '.' TYPEOF",
  "WhenPostfixExpression : WhenPostfixExpression '(' CallArgumentList_Opts ')'",
  "WhenCondition : INT",
  "WhenCondition : DBL",
  "WhenCondition : BIGINT",
  "WhenCondition : NUL",
  "WhenCondition : VarName",
  "WhenCondition : TRUE",
  "WhenCondition : FALSE",
  "WhenCondition : '(' STR ')'",
  "WhenCondition : '(' AssignExpression ')'",
  "CaseElseClause : /* empty */",
  "CaseElseClause : ELSE Colon_Opt WhenClauseBody",
  "WhenClauseBody : BlockStatement",
  "WhenClauseBody : TernaryExpression",
  "Colon_Opt : /* empty */",
  "Colon_Opt : ':'",
  "AssignExpression : TernaryExpression",
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
  "AssignRightHandSide : TernaryExpression",
  "AssignRightHandSide : ObjectSpecialSyntax",
  "AssignRightHandSide : CaseWhenExpression",
  "ObjectSpecialSyntax : LBBR RBBR",
  "ObjectSpecialSyntax : ObjectSpecialSyntax PostIncDec",
  "ObjectSpecialSyntax : ObjectSpecialSyntax LMBR AssignExpression RMBR",
  "ObjectSpecialSyntax : ObjectSpecialSyntax '.' PropertyName",
  "ObjectSpecialSyntax : ObjectSpecialSyntax '.' TYPEOF",
  "ObjectSpecialSyntax : ObjectSpecialSyntax '(' CallArgumentList_Opts ')'",
  "ObjectSpecialSyntax : ObjectSpecialSyntax SimpleFuncCallFactor",
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
  "Factor : Array",
  "Factor : Binary",
  "Factor : Object",
  "Factor : SimpleFuncCallFactor",
  "Factor : Regex",
  "Factor : '.' PropertyName",
  "Factor : IMPORT '(' '(' STR ')' ')'",
  "Factor : '(' AssignExpression ')'",
  "Factor : '(' CaseWhenExpression ')'",
  "Factor : '(' ObjectSpecialSyntax ')'",
  "Factor : '(' STR ')'",
  "Factor : NEW Factor",
  "Factor : '@' PropertyName",
  "Factor : '@' TYPEOF",
  "VarName : NAME",
  "VarName : TYPE",
  "PropertyName : NAME",
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
  "PropertyName : TYPE",
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
  "ArrayItemListCore : NAME ':' ArrayItemListCoreRight",
  "ArrayItemListCore : KeySpecialName ':' ArrayItemListCoreRight",
  "ArrayItemListCore : DOTS3 AssignRightHandSide",
  "ArrayItemListCore : ArrayItemListCore ','",
  "ArrayItemListCore : ArrayItemListCore ',' AssignExpression",
  "ArrayItemListCore : ArrayItemListCore ',' NAME ':' ArrayItemListCoreRight",
  "ArrayItemListCore : ArrayItemListCore ',' KeySpecialName ':' ArrayItemListCoreRight",
  "ArrayItemListCore : ArrayItemListCore ',' DOTS3 AssignRightHandSide",
  "ArrayItemListCoreRight : INT",
  "ArrayItemListCoreRight : DBL",
  "ArrayItemListCoreRight : BIGINT",
  "ArrayItemListCoreRight : NUL",
  "ArrayItemListCoreRight : VarName",
  "ArrayItemListCoreRight : TRUE",
  "ArrayItemListCoreRight : FALSE",
  "ArrayItemListCoreRight : '(' STR ')'",
  "ArrayItemListCoreRight : LMBR ArrayItemList RMBR",
  "ArrayItemListCoreRight : LBBR ArrayItemList RBBR",
  "AssignExpressionList : AssignExpression",
  "AssignExpressionList : AssignExpressionList ',' AssignExpression",
  "AssignExpressionObjList : AssignExpression",
  "AssignExpressionObjList : LBBR RBBR",
  "AssignExpressionObjList : AssignExpressionObjList ',' AssignExpression",
  "AssignExpressionObjList : AssignExpressionObjList ',' LBBR RBBR",
  "KeyValueList : KeyValue",
  "KeyValueList : KeyValueList ',' KeyValue",
  "KeyValue : '(' STR ')' ':' AssignExpression",
  "KeyValue : '(' STR ')' ':' ObjectSpecialSyntax",
  "KeyValue : NAME ':' AssignExpression",
  "KeyValue : NAME ':' ObjectSpecialSyntax",
  "KeyValue : KeySpecialName ':' AssignExpression",
  "KeyValue : KeySpecialName ':' ObjectSpecialSyntax",
  "KeyValue : DOTS3 AssignRightHandSide",
  "KeyValue : NAME",
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
  "DeclAssignExpression : LMBR ArrayItemList RMBR '=' DeclAssignRightHandSide",
  "DeclAssignExpression : LBBR ArrayItemList RBBR '=' DeclAssignRightHandSide",
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
  "Argument : LMBR ArrayItemList RMBR",
  "Argument : LBBR ArrayItemList RBBR",
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
  111,  111,  111,  109,  111,  111,  111,  107,  101,  111,
   95,   96,  105,  104,   93,   92,   97,  106,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,   94,   91,
  102,   90,  103,   98,  110,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  100,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,   99,  111,  108,  111,  111,  111,
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
#define YYNONTERMS 117

static short yyaction[] = {
  780,  781,  782,  783,  784,  785,  786,  787,  788,  789,
  790,  791,  792,  794,  793,    0,  795,  796,  797,  806,
  808,  807,  365,  817,  818,  819,  821,  823,  192,  193,
   19,  365,  815,  816,  253,   75,   76,   77,   78,   79,
   80,   81,   82,   83,   84,   85,   86,   87,    4,  145,
  118,  809,  810,  811,  122,  812,  813,   30,   57,   31,
   40,  146,   59,  116,   42,  804,  326,  805,  252,  798,
  799,  800,  801,  802,  803,  116,  779,  275,-32766,  187,
  546,  814,  548,  547,  549,  404,  550,   88,  772,-32766,
  825,  551,  552,  405,  407,  553,  187,  830,  831,  829,
  820,  822,  824,  826,  827,  828,  915,  916,  917,  918,
  919,  920,  921,  922,  923,  924,  925,  926,  927,   64,
  928,-32766,  929,  930,  931,  939,  941,  940,  402,  951,
  952,  953,  955,  957,   52,-32766,-32766,-32766,  949,  950,
 -361,-32766,  344,   16,  345,  554,   54, -361,   56,   54,
  555,  346,  557,  556,  489, -387,  -74,  942,  943,  944,
   54,  945,  946,  545,  536,-32766,  116,-32766,-32766,  544,
  111,  937,  227,  938,  586,   94,  932,  933,  934,  935,
  936,  130, 1003,  138,  139,  140,  116,  947,  948,  301,
-32766,  379,   51,  147,  148,  149,  959,  753,  754,  380,
-32766, -388, -106,  964,  965,  963,  954,  956,  958,  960,
  961,  962,  168,  384,  882,  385,   10,  386,  886,  311,
  888,  889,  233,  234,  387,  117,  347,  894,  348,  164,
  230,  231,  312,   72,   66,  293,  302,   52,   54,   51,
   26, 1027,  127,  -75,   97,  344,   16,  345,  321, -106,
  109,  430,  120,  322,  346,-32766,  323,   52,  141,  142,
   58,   54,   41,-32766,  388,  389,  390,  777,  267,  912,
  126,   53,  778,   73,  116,  295,  296,  349,  391,  351,
  392,  353,  116,  268,  269,   48,   49,   50,  125,  242,
-32766,  122,-32766,  187,  393,  914,   60,  562,   43,   59,
  116,   42, -101,   27,  372,   32,   63,  647,  649,  650,
  132,  235,  251,  881,  882,  883,  884,  885,  886,  887,
  888,  889,  890,  891,  892,  893,   52,  894,-32766,  895,
  896,  897,  905,  907,  906,  646,  644,  131,   92,   33,
    4,   34,  118,  645,  150,   52,  647,  649,  650,   95,
   57,  123,   40,   51,  126, 1044,-32766,  574,   27,  308,
   28,   52,  571,   52,  908,  909,  910,  509,  911,  912,
  126,   54,  490,   73,  646,  644,   89,   68,  903,  837,
  904,  237,  645,  898,  899,  900,  901,  902,   95,  412,
  616,  302,  420, 1044,  913,  914,  414,  423,-32766,   52,
  136,  137,  143,  144,  154,  155,  413,  858,  860,  861,
  156,  157,  414,  881,  882,  883,  884,  885,  886,  887,
  888,  889,  890,  891,  892,  893,  416,  894,  307,  164,
  896,  897,  905,  907,  906,  857,  855,  618,  568,   35,
  378,   36,  617,  856,  301,  377,  304,  310,  491,  471,
  484,  446,  421,  575,  309,  459,  493,  497,  451,  460,
  836,    0,  133,  572,  388,  389,  390,  642,  395,  912,
 1014,  742,-32766,   74,  681,  776,  498,    7,  903,    6,
  904,    5,  275,  396,  397,  900,  901,  902,  677,  398,
-32766,-32766,  569,  870,  393,  914,   54,  476,  748,  834,
  864,  454,  747,  839,  844,  881,  882,  883,  884,  885,
  886,  887,  888,  889,  890,  891,  892,  893,  633,  894,
 1024,  164,  896,  897,  905,  907,  906,  868,  740,-32766,
-32766,-32766, 1012, 1031,  863,-32766,  632, 1030, 1023,  832,
  835,  966,  501,   54,  482,  455,  973,  679,  640,    0,
-32766,  291,  287,   91,   71,   70,  388,  389,  390,-32766,
  395,  912,-32766,-32766,   69,   74,-32766,-32766,  584,  535,
  903,  606,  904,  605,  615,  396,  397,  900,  901,  902,
  604,  398,  602,  608,  974,  100,  393,  914,   54,  603,
  601,  619,  607,  102,    0,  101,  845,  881,  882,  883,
  884,  885,  886,  887,  888,  889,  890,  891,  892,  893,
   99,  894,   98,  164,  896,  897,  905,  907,  906,  220,
  119,   65,   55,   38,  121,  232,  452,    0, -386, -391,
 -390, -389,  107,  110,  113,  128,  188,  189,  190,  191,
  658,  587,  518,  238,  236,  226, -394,    0,  388,  389,
  390,  208,  395,  912,  207,  108,  106,   74,  105,  104,
  209,  206,  903,  216,  904,  450,  103,  396,  397,  900,
  901,  902,  210,  398,  422,  374,  373,  239,  393,  914,
   54,  219,  218,  217,  215,  214,  213,  212,  844,  881,
  882,  883,  884,  885,  886,  887,  888,  889,  890,  891,
  892,  893,  211,  894,   62,  164,  896,  897,  905,  907,
  906,  168,  343,   18,  344,   16,  345,   20,  292,  652,
   21,  248,  249,  346,  324,  347,  500,  348,  626,  228,
  229,  515,   96,   93,  293,  770,   17, 1035, 1033,  643,
  388,  389,  390,  862,  395,  912,  769,  651,  682,   90,
 1016,  743,  972,  833,  903,  771,  904,  773,  967,  396,
  397,  900,  901,  902,  494,  472,  485,  254,  475,  126,
  393,  914,   54,  469,  295,  296,  349,  350,  351,  352,
  353,  342,  255,  256,   45,   46,   47,  341,  355,  340,
  339,  338,  337,  336,  334,  332,  562,  331,  330,   24,
   23, -101,  168,  343,   22,  344,   16,  345,    3,  292,
    2,  251,  248,  249,  346,  134,  347,  135,  348,    0,
  228,  229,  515,   96,   93,  293,    0,    0,    0,    0,
    0,    0,    0,  168,  343,    0,  344,   16,  345,    0,
  292,    0,    0,  248,  249,  346,    0,  347,    0,  348,
    0,  228,  229,  515,   96,   93,  293,    0,  254,    0,
  124,    0,    0,    0,    0,  295,  296,  349,  350,  351,
  352,  353,    0,  255,  256,   45,   46,   47,    0,  355,
    0,    0,    0,    0,    0,    0,    0,  749,    0,  254,
    0,  129, -101,    0,    0,    8,  295,  296,  349,  350,
  351,  352,  353,    0,  255,  256,   45,   46,   47,  115,
  355,    0,    0,  163,    0,    0,    0,    0,  749,    0,
    0,    0,    0, -101,    0,    0,    8,  158,  159,    0,
    0,    0,    0,    0,    0,    0,  516,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  758,  760,
  761,    0,  368,    0,    0,    0,    0,    0,  294,    0,
    0,    0,    0,    0,    0,    0,  990,  369,  370,    0,
    0,    0,  354,  777,    0,  762,  757,  755,  778,    0,
    1,    0,   25,    0,  756,    0,    0,  160,    0,    0,
   61,    0,   44,    0,    0,    0,  250,  297,    0,  161,
  151,  517,    0,  152,  153,   39,  168,  343,    0,  344,
   16,  345,    0,  292,    0,    0,  248,  249,  346,    0,
  347,    0,  348,    0,  228,  229,  515,   96,   93,  293,
    0,    0,    0,    0,    0,    0,   -1,  168,  343,    0,
  344,   16,  345,    0,  292,    0,    0,  248,  249,  346,
    0,  347,    0,  348,    0,  228,  229,  515,   96,   93,
  293,    0,  254,    0,    0,    0,    0,    0,    0,  295,
  296,  349,  350,  351,  352,  353,    0,  255,  256,   45,
   46,   47,    0,  355,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  254,    0,    0, -101,    0,    0, -365,
  295,  296,  349,  350,  351,  352,  353,    0,  255,  256,
   45,   46,   47,    0,  355,    0,    0,    0,  168,  343,
    0,  344,   16,  345,    0,  292,    0, -101,  248,  249,
  346,    0,  347,    0,  348,    0,  228,  229,  515,   96,
   93,  293,    0,    0,    0,    0,  168,  343,    0,  344,
   16,  345,    0,  292,    0,    0,  248,  249,  346,    0,
  347,    0,  348,    0,  228,  229,  515,   96,   93,  293,
    0,    0,    0,    0,  254,    0,    0,    0,    0,    0,
    0,  295,  296,  349,  350,  351,  352,  353,    0,  255,
  256,   45,   46,   47,    0,  355,    0,    0,    0,    0,
    0,    0,  254,  567,    0,    0,    0,    0, -101,  295,
  296,  349,  350,  351,  352,  353,    0,  255,  256,   45,
   46,   47,    0,  355,    0,    0,    0,    0,    0,    0,
    0,  566,    0,    0,  168,  343, -101,  344,   16,  345,
    0,  292,    0,    0,  248,  249,  346,    0,  347,    0,
  348,    0,  228,  229,  515,   96,   93,  293,    0,    0,
    0,    0,  168,  343,    0,  344,   16,  345,    0,  292,
    0,    0,  248,  249,  346,    0,  347,    0,  348,    0,
  228,  229,  515,   96,   93,  293,    0,    0,    0,    0,
  254,    0,    0,    0,    0,    0,    0,  295,  296,  349,
  350,  351,  352,  353,    0,  255,  256,   45,   46,   47,
    0,  355,    0,    0,    0,    0,    0,    0,  254,  565,
    0,    0,    0,    0, -101,  295,  296,  349,  350,  351,
  352,  353,    0,  255,  256,   45,   46,   47,    0,  355,
    0,    0,    0,    0,    0,    0,    0,  564,    0,    0,
  168,  343, -101,  344,   16,  345,    0,  292,    0,    0,
  248,  249,  346,    0,  347,    0,  348,    0,  228,  229,
  515,   96,   93,  293,    0,    0,    0,    0,  168,  343,
    0,  344,   16,  345,    0,  292,    0,    0,  248,  249,
  346,    0,  347,    0,  348,    0,  228,  229,  515,   96,
   93,  293,    0,    0,    0,    0,  254,    0,    0,    0,
    0,    0,    0,  295,  296,  349,  350,  351,  352,  353,
    0,  255,  256,   45,   46,   47,    0,  355,    0,    0,
    0,    0,    0,    0,  254,  563,    0,    0,    0,    0,
 -101,  295,  296,  349,  350,  351,  352,  353,    0,  255,
  256,   45,   46,   47,    0,  355,    0,    0,    0,    0,
    0,    0,    0,  562,    0,    0,  168,  343, -101,  344,
   16,  345,    0,  292,    0,    0,  248,  249,  346,    0,
  347,    0,  348,    0,  228,  229,  515,   96,   93,  293,
    0,    0,    0,    0,  168,  343,    0,  344,   16,  345,
    0,  292,    0,    0,  248,  249,  346,    0,  347,    0,
  348,    0,  228,  229,  515,   96,   93,  293,    0,    0,
    0,    0,  254,    0,    0,    0,    0,    0,    0,  295,
  296,  349,  350,  351,  352,  353,    0,  255,  256,   45,
   46,   47,    0,  355,    0,    0,    0,    0,    0,    0,
  254,  751,    0,    0,    0,    0, -101,  295,  296,  349,
  350,  351,  352,  353,    0,  255,  256,   45,   46,   47,
    0,  355,    0,    0,    0,    0,    0,    0,    0,  750,
    0,    0,  168,  343, -101,  344,   16,  345,    0,  292,
    0,    0,  248,  249,  346,    0,  347,    0,  348,    0,
  228,  229,  515,   96,   93,  293,    0,    0,    0,    0,
  168,  343,    0,  344,   16,  345,    0,  292,    0,    0,
  248,  249,  346,    0,  347,    0,  348,    0,  228,  229,
  515,   96,   93,  293,    0,    0,    0,    0,  254,    0,
    0,    0,    0,    0,    0,  295,  296,  349,  350,  351,
  352,  353,    0,  255,  256,   45,   46,   47,    0,  355,
    0,    0,    0,    0,    0,    0,  254,  752,    0,    0,
    0,    0, -101,  295,  296,  349,  350,  351,  352,  353,
    0,  255,  256,   45,   46,   47,    0,  355,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -101
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1701

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,    0,   18,   19,   20,   21,
   22,   23,    2,   25,   26,   27,   28,   29,   61,   62,
    3,    2,   34,   35,   62,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   85,   92,
   87,   53,   54,   55,   87,   57,   58,   85,   95,   87,
   97,  104,   95,   14,   97,   67,    3,   69,    9,   71,
   72,   73,   74,   75,   76,   14,   78,   85,   14,   16,
    2,   83,    4,    5,    6,   87,    8,   90,   96,   14,
   92,   13,   14,   95,    4,   17,   16,   99,  100,  101,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   90,
   16,   14,   18,   19,   20,   21,   22,   23,   79,   25,
   26,   27,   28,   29,   85,   71,   72,   73,   34,   35,
   86,   77,    4,    5,    6,   67,   85,   93,   94,   85,
   72,   13,   74,   75,   79,   94,    7,   53,   54,   55,
   85,   57,   58,   85,   86,  101,   14,   14,   14,   91,
    7,   67,   19,   69,   94,   23,   72,   73,   74,   75,
   76,   37,   78,   27,   28,   29,   14,   83,   84,   78,
   14,   87,   85,  105,  106,  107,   92,   32,   33,   95,
   14,   94,   91,   99,  100,  101,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   78,   85,   85,   85,
   87,   71,   98,    7,   91,    4,    5,    6,   78,   91,
    7,   79,   87,   83,   13,   14,   10,   85,  102,  103,
   95,   85,   97,   14,   53,   54,   55,   78,   57,   58,
   59,   85,   83,   62,   14,   64,   65,   66,   67,   68,
   69,   70,   14,   72,   73,   74,   75,   76,   87,   78,
   14,   87,   14,   16,   83,   84,   95,   86,   97,   95,
   14,   97,   91,   85,   19,   87,   95,   53,   54,   55,
   31,   56,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   85,   16,   14,   18,
   19,   20,   21,   22,   23,   81,   82,   30,   62,   85,
   85,   87,   87,   89,   36,   85,   53,   54,   55,   95,
   95,   59,   97,   85,   59,   79,   59,   82,   85,   78,
   87,   85,   82,   85,   53,   54,   55,   92,   57,   58,
   59,   85,   92,   62,   81,   82,   62,   90,   67,   60,
   69,   94,   89,   72,   73,   74,   75,   76,   95,   78,
   91,   78,   93,   79,   83,   84,  101,   79,  101,   85,
   25,   26,   34,   35,   51,   52,   95,   53,   54,   55,
   61,   62,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   78,   16,   78,   18,
   19,   20,   21,   22,   23,   81,   82,   78,   78,   85,
   78,   87,   78,   89,   78,   78,   85,   78,   78,   95,
   78,   78,   78,   82,   78,   90,   79,   79,   79,   79,
  103,   -1,   99,   82,   53,   54,   55,   84,   57,   58,
   84,   84,   14,   62,   84,   84,   87,   85,   67,   85,
   69,   85,   85,   72,   73,   74,   75,   76,   86,   78,
   32,   33,   86,   86,   83,   84,   85,   87,   86,   88,
   86,   86,   86,   86,   93,    2,    3,    4,    5,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   86,   16,
   86,   18,   19,   20,   21,   22,   23,   86,   88,   71,
   72,   73,   88,   88,   88,   77,   88,   88,   88,   88,
   88,   88,   88,   85,   88,   88,   91,   88,   88,   -1,
   92,   90,   90,   90,   90,   90,   53,   54,   55,  101,
   57,   58,  104,  105,   90,   62,  108,  109,   91,   91,
   67,   91,   69,   91,   91,   72,   73,   74,   75,   76,
   91,   78,   91,   91,   91,   91,   83,   84,   85,   91,
   91,   91,   91,   91,   -1,   91,   93,    2,    3,    4,
    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   91,   16,   91,   18,   19,   20,   21,   22,   23,   93,
   93,   93,   93,   93,   93,   93,   93,   -1,   94,   94,
   94,   94,   94,   94,   94,   94,   94,   94,   94,   94,
   94,   94,   94,   94,   94,   94,   94,   -1,   53,   54,
   55,   95,   57,   58,   95,   95,   95,   62,   95,   95,
   95,   95,   67,   95,   69,   95,   95,   72,   73,   74,
   75,   76,   95,   78,   95,   95,   95,   95,   83,   84,
   85,   95,   95,   95,   95,   95,   95,   95,   93,    2,
    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   95,   16,   95,   18,   19,   20,   21,   22,
   23,    1,    2,   96,    4,    5,    6,   96,    8,   96,
   96,   11,   12,   13,   96,   15,   96,   17,   96,   19,
   20,   21,   22,   23,   24,   96,   96,   96,   96,   96,
   53,   54,   55,   96,   57,   58,   96,   96,   96,   62,
   96,   96,   96,   96,   67,   96,   69,   96,   96,   72,
   73,   74,   75,   76,   96,   78,   96,   57,   96,   59,
   83,   84,   85,   96,   64,   65,   66,   67,   68,   69,
   70,   96,   72,   73,   74,   75,   76,   96,   78,   96,
   96,   96,   96,   96,   96,   96,   86,   96,   96,   96,
   96,   91,    1,    2,   96,    4,    5,    6,   96,    8,
   96,  101,   11,   12,   13,  100,   15,  101,   17,   -1,
   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,    1,    2,   -1,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   -1,   15,   -1,   17,
   -1,   19,   20,   21,   22,   23,   24,   -1,   57,   -1,
   59,   -1,   -1,   -1,   -1,   64,   65,   66,   67,   68,
   69,   70,   -1,   72,   73,   74,   75,   76,   -1,   78,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   86,   -1,   57,
   -1,   59,   91,   -1,   -1,   94,   64,   65,   66,   67,
   68,   69,   70,   -1,   72,   73,   74,   75,   76,   14,
   78,   -1,   -1,   18,   -1,   -1,   -1,   -1,   86,   -1,
   -1,   -1,   -1,   91,   -1,   -1,   94,   32,   33,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   41,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   53,   54,
   55,   -1,   57,   -1,   -1,   -1,   -1,   -1,   63,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   71,   72,   73,   -1,
   -1,   -1,   77,   78,   -1,   80,   81,   82,   83,   -1,
   85,   -1,   87,   -1,   89,   -1,   -1,   92,   -1,   -1,
   95,   -1,   97,   -1,   -1,   -1,  101,  102,   -1,  104,
  105,  106,   -1,  108,  109,  110,    1,    2,   -1,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   -1,
   15,   -1,   17,   -1,   19,   20,   21,   22,   23,   24,
   -1,   -1,   -1,   -1,   -1,   -1,    0,    1,    2,   -1,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   -1,   15,   -1,   17,   -1,   19,   20,   21,   22,   23,
   24,   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,   64,
   65,   66,   67,   68,   69,   70,   -1,   72,   73,   74,
   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   57,   -1,   -1,   91,   -1,   -1,   94,
   64,   65,   66,   67,   68,   69,   70,   -1,   72,   73,
   74,   75,   76,   -1,   78,   -1,   -1,   -1,    1,    2,
   -1,    4,    5,    6,   -1,    8,   -1,   91,   11,   12,
   13,   -1,   15,   -1,   17,   -1,   19,   20,   21,   22,
   23,   24,   -1,   -1,   -1,   -1,    1,    2,   -1,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   -1,
   15,   -1,   17,   -1,   19,   20,   21,   22,   23,   24,
   -1,   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,
   -1,   64,   65,   66,   67,   68,   69,   70,   -1,   72,
   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,   -1,
   -1,   -1,   57,   86,   -1,   -1,   -1,   -1,   91,   64,
   65,   66,   67,   68,   69,   70,   -1,   72,   73,   74,
   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   86,   -1,   -1,    1,    2,   91,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   -1,   15,   -1,
   17,   -1,   19,   20,   21,   22,   23,   24,   -1,   -1,
   -1,   -1,    1,    2,   -1,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   -1,   15,   -1,   17,   -1,
   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,
   57,   -1,   -1,   -1,   -1,   -1,   -1,   64,   65,   66,
   67,   68,   69,   70,   -1,   72,   73,   74,   75,   76,
   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   57,   86,
   -1,   -1,   -1,   -1,   91,   64,   65,   66,   67,   68,
   69,   70,   -1,   72,   73,   74,   75,   76,   -1,   78,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   86,   -1,   -1,
    1,    2,   91,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   -1,   15,   -1,   17,   -1,   19,   20,
   21,   22,   23,   24,   -1,   -1,   -1,   -1,    1,    2,
   -1,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   -1,   15,   -1,   17,   -1,   19,   20,   21,   22,
   23,   24,   -1,   -1,   -1,   -1,   57,   -1,   -1,   -1,
   -1,   -1,   -1,   64,   65,   66,   67,   68,   69,   70,
   -1,   72,   73,   74,   75,   76,   -1,   78,   -1,   -1,
   -1,   -1,   -1,   -1,   57,   86,   -1,   -1,   -1,   -1,
   91,   64,   65,   66,   67,   68,   69,   70,   -1,   72,
   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   86,   -1,   -1,    1,    2,   91,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   -1,
   15,   -1,   17,   -1,   19,   20,   21,   22,   23,   24,
   -1,   -1,   -1,   -1,    1,    2,   -1,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   -1,   15,   -1,
   17,   -1,   19,   20,   21,   22,   23,   24,   -1,   -1,
   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,   64,
   65,   66,   67,   68,   69,   70,   -1,   72,   73,   74,
   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,
   57,   86,   -1,   -1,   -1,   -1,   91,   64,   65,   66,
   67,   68,   69,   70,   -1,   72,   73,   74,   75,   76,
   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   86,
   -1,   -1,    1,    2,   91,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   -1,   15,   -1,   17,   -1,
   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,
    1,    2,   -1,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   -1,   15,   -1,   17,   -1,   19,   20,
   21,   22,   23,   24,   -1,   -1,   -1,   -1,   57,   -1,
   -1,   -1,   -1,   -1,   -1,   64,   65,   66,   67,   68,
   69,   70,   -1,   72,   73,   74,   75,   76,   -1,   78,
   -1,   -1,   -1,   -1,   -1,   -1,   57,   86,   -1,   -1,
   -1,   -1,   91,   64,   65,   66,   67,   68,   69,   70,
   -1,   72,   73,   74,   75,   76,   -1,   78,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   91
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1609,  211,  801,  832,  710, 1377, 1261, 1233, 1493, 1036,
 1005, 1349, 1145, 1117, 1465, 1581, 1609, 1609, 1609, 1609,
 1609, 1609, 1609, 1609, 1609,  411,  411,  595,  595,  595,
  595,  595,  595,  595,  595,  595,  595,  503,  687,  391,
  387,  390,  383,  386,   -2,  104,  104,  104,  104,  104,
  104,  441,  402,  407,  311,  297,  241,  314,  314,  314,
  314,   49,  153,  172,  152,  276,   61,  268,  260,  260,
  260,  260,  107,  260,  260,  260,  260,  260,  260,  260,
  260,  260,  260,  260,  260,  260,  260,  260,  260,  260,
  260,  260,  260,  286,  286,   75,  154,  154,  154,  154,
  154,  154,  154,  176,  176,  176,  176,  278,  176,  176,
  278,  176,  249,  278,  249,  176,  176,  176,  176,  186,
  176,  176,  176,  249,  249,  176,  176,  176,  176,  176,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,  458,  458,
  458,  458,  458,  458,  458,   80,  277,   29,   78,  639,
  440,  459,  623,  460,  444,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,  254,  354,  354,
  354,  354,  293,  293,  255,   -8,  -33,  -37,  -37,  -37,
  -37,  397,  397,  397,  397,  397,  -28,  -28,  -28,  -28,
  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,
  -28,  204,  204,  156,  156,  156,  138,  218,  273,  273,
  273,  273,  273,  111,  158,  170,  170,  170,  170,  170,
  201,   88,   54,   88,   88,  149,   63,   63,  366,  313,
  565,  568,  570,  189,  285,  367,  362,  144,  375,  368,
  -43,  353,  349,  287,  455,  493,  299,  285,  367,  362,
  373,  640,  617,  521,  628,  295,  375,  368,  368,  368,
  368,  368,  -43,  -43,  353,  519,  632,  280,  630,  621,
  624,  275,  396,  364,  580,  360,  360,  357,   20,  550,
   59,   20,   20,  550,  348,   20,  580,  577,  577,  396,
  396,  396,  534,  529,  580,  246,  533,   20,   20,  548,
  548,  410,  410,  396,  396,   20,  546,  582,  396,  396,
  396,  396,  396,  546,  396,  582,  396,  396,  396,  396,
  396,  396,  396,  571,  564,  609,  563,  547,  361,  501,
  350,  281,  376,  369,  556,  551,   15,  500,  307,  279,
  363,  715,  716,  308,   90,  561,  499,  498,  581,  566,
  559,  527,  374,  579,  318,  394,  392,  607,  592,  453,
  662,  591,  590,  589,  571,  564,  609,  563,  537,  536,
  535,  350,  376,  552,  538,  581,  566,  559,  542,  452,
  530,  543,  661,  659,  451,  657,  492,  560,  243,  149,
  491,  489,  539,  379,  587,  588,  462,  415,  457,  483,
  359,  365,  380,  656,  549,  702,  526,  701,  699,  416,
  677,  417,  530,  672,  319,  307,  541,  279,  363,  715,
  716,  308,  308,  308,  655,  528,  586,  163,  456,  494,
  372,  670,  370,  406,  474,  465,  463,  482,  480,  377,
  668,  654,  698,  434,  450,  697,  696,  695,  694,  540,
  714,  378,  544,  545,  652,  292,  449,  389,  389,  693,
   27,  454,  236,  504,  691,  540,  712,  432,  448,  651,
  381,  461,  464,  478,  650,  414,  446,  647,  445,  685,
  477,  465,  502,  708,  643,  463,  463,  642,  704,  371,
  463,  412,  703,  412,  641,    0,    0,    0,    0,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,   -2,   -2,
   -2,   -2,   -2,    0,    0,    0,    0,    0,    0,    0,
  311,  311,  311,    0,  311,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,   -3,   -3,   -3,    0,   -3,   -3,
   -3,   -3,   -3,   -3,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  189,  189,  189,  189,
  189,  189,  189,  165,  165,  165,  165,  165,  165,  165,
  165,  165,  165,  165,  165,  189,  189,  189,  189,  189,
  189,  189,  189,  189,  189,  189,  189,  189,  189,  189,
  165,  165,    0,    0,    0,    0,  189,  189,  189,  189,
  189,  189,   20,   20,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  287,    0,    0,   20,   20,  396,
  396,  396,    0,  581,  566,  559,    0,    0,    0,    0,
    0,    0,    0,  532,  532,    0,  581,  566,  559,  588,
  531,  531,  531,  531,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  532,  531,    0,  531,  531,  531
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 291

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  331,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  381,  382,
  383,32767,32767,32767,32767,  322,32767,  517,  517,  517,
  517,32767,32767,32767,32767,32767,   92,  104,32767,32767,
32767,32767,  104,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   92,   95,32767,  104,  104,  104,  104,
  104,  104,  104,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  374,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  205,  207,32767,32767,
32767,32767,32767,32767,  376,32767,32767,  106,32767,32767,
32767,32767,32767,32767,32767,  348,   90,  327,  346,  523,
  350,  356,  358,  332,   93,  347,  354,32767,32767,32767,
32767,32767,  115,  117,  217,32767,  112,  215,  216,  213,
  212,  156,  524,  357,  359,  355,  498,  498,  498,  498,
  498,  498,  498,  498,  498,  498,  498,  498,  498,  498,
32767,  116,  118,  181,  182,  183,32767,32767,32767,32767,
  377,  378,32767,  371,  372,32767,32767,32767,32767,32767,
  515,  193,  258,  195,  194,  458,  134,  134,  106,  106,
32767,32767,32767,32767,32767,32767,32767,  168,  179,  184,
  190,  200,  202,  458,32767,32767,32767,  392,  379,  380,
32767,32767,32767,32767,32767,32767,  180,  186,  188,  189,
  185,  187,  191,  192,  201,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  319,  106,  472,
   77,  106,  106,  472,32767,  106,32767,  496,  496,32767,
32767,  368,  526,  321,32767,   80,  321,  106,  106,  490,
  490,  510,  510,32767,32767,  106,  138,  513,32767,32767,
32767,32767,32767,  138,32767,  513,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  258,32767,32767,  169,  171,
  173,  175,  177,  196,32767,32767,32767,32767,32767,32767,
32767,  105,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  362,  364,  366,  373,  239,  241,
  242,  384,  385,  259,32767,  392,  379,  380,  258,32767,
  323,32767,32767,32767,32767,32767,32767,32767,32767,  240,
32767,32767,  361,32767,32767,32767,   51,32767,32767,32767,
32767,32767,32767,32767,  502,32767,  499,32767,32767,32767,
32767,32767,  324,32767,32767,  170,32767,  172,  174,  176,
  178,  197,  198,  199,32767,  518,32767,32767,32767,32767,
32767,32767,  322,32767,32767,32767,  460,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  254,
32767,32767,  258,32767,32767,32767,32767,  509,  507,32767,
   62,32767,  316,32767,32767,32767,32767,32767,32767,32767,
32767,   54,  459,32767,32767,32767,32767,32767,32767,32767,
32767,   75,32767,32767,32767,  463,  462,32767,32767,32767,
  461,  478,32767,32767,32767,  526,  452,  452,  526
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  177,  177,  177,  177,  177,  177,  177,  177,  177,  177,
  177,  177,  177,  183,  432,  969,  739, 1040,  639,  739,
  739,  739,  739,  968,  409,  741,  680,  641, 1013,  768,
  317,  181,  179,  179,  179,  179,  169,  178,  169,  872,
  179,  176,  175,  639,  639,  630,  655,  175,  655,  733,
  729,  730,  722,  723,  725,  727,  435,  998,  998,  437,
  449,  483,  502,  503,  508,  512,  224,  225,  176,  184,
  172,  175,  175,  175,  175,  175,  175,  175,  178,  178,
  178,  178,  182,  178,  178,  181,  178,  438,  186,  439,
  165,  166,  165,  170,  180,  171,  185,  173,  674,  580,
  174,  440,  674,  674,  674,  674,  276,  674,  674,  674,
  674,  674,  674,  674,  674,  674,  674,  674,  674,  674,
  674,  674,  674,  674,  674,  674,  674,  247,  745,  282,
  283,  745,  745,  745,  745,  448,  417,  418,  434,  463,
  464,  481,  487,  488,  495,  496,  656,  284,  656,  648,
  859,  859,  859,  859,  648,  648, 1020,  997,  511,  447,
  429,  436,  685,  513,  197,  198,  199,  200,  424,  424,
  424,  424,  424,  424,  424,  424,  424,  424,  424,  424,
  424,  424,  424,  976,  999,  999,  597,  521,  627,  245,
  263,  263,  263,  263,  263,  376,  522,  364,  524,  524,
  524,  524,  524,  364,  480,  583,  582,  591,  592,  590,
  589,  588,  415,  746,  683, 1025,  746,  746,  746,  746,
  683,  683,  683,  683,  683,  320,  300,  427,  428,  433,
  461,  462,  465,  466,  467,  468,  470,  479,  486,  499,
  474,  504,  514, 1007, 1008,  300,  271,  272,  274,  286,
 1022,  288,  289,  453,  290,   14,   14,  600,  585,   12,
   13,   15, 1005, 1006,  993,  994,  995,  329,  987,  580,
  988, 1000, 1001, 1002,  996,  598,  989,  299,  299,  299,
  299,  299,  299,  299,  299,  299,  299,  299,  299,  299,
  299,  299,  299,  299,  299,  299,  299,  299,  299,  299,
  299,  299,  660,  478,  621,  394,  277,  278,  279,  280,
  281,  879,  849,  663,  664,  665,  666,  667,  668,  669,
  670,  671,  672,  673,  661,  662,  660, 1039,  854,  984,
 1041,  203,  202,  202,  202,  202,  195,  114,  195,  162,
  202,  403,  473,  403,  243,  244,  610,  318,  382,  383,
  314,  382,  383,  221,  222,  394,  394,  394,  394,  394,
  992,  327,  335,  507,    0,  285,    0,  265,    0,  265,
    0,  367,    0,  610,  613,  505,  506,  510,  441,  442,
  443,    0,  204,    0,    0,  203,  367,    0,  205, 1011,
  774,  774,  848,  852,  853,  629,  629,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  406,    0,    0,  410,  411,
    0,    0,  419,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  457,  458,    0,    0,    0,    0,
    0,    0,  333
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 463

static char yygcheck[] = {
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   66,   64,   58,   99,   58,   58,
   58,   58,   58,   64,   73,   57,   57,   57,   57,   57,
   38,   35,   35,   35,   35,   35,   35,   35,   35,   72,
   35,   35,   35,   58,   58,  112,    7,   35,    7,   54,
   54,   54,   54,   54,   54,   54,   42,    7,    7,   43,
   38,   38,   38,   38,   38,   38,   48,   48,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   44,   35,   45,
   35,   35,   35,   35,   35,   35,   35,   35,   39,   33,
   35,   46,   39,   39,   39,   39,   47,   39,   39,   39,
   39,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   39,   39,   39,   39,   39,   39,   39,  106,    7,   50,
   50,    7,    7,    7,    7,   65,   65,   65,   65,   65,
   65,   65,   65,   65,   65,   65,   39,   53,   39,   73,
   73,   73,   73,   73,   73,   73,   94,   39,   39,   19,
   39,   39,   39,   39,   56,   56,   56,   56,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   79,    7,    7,    7,    4,  111,   73,
   73,   73,   73,   73,   73,    9,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,  100,   96,   96,   73,   96,   96,   96,   96,
   96,   96,   96,   96,   96,   90,    7,   92,   92,   92,
   92,   92,   92,   92,   92,   92,   92,   92,   92,   92,
   97,   97,   97,    7,    7,    7,   69,   69,   69,   69,
  103,   69,   69,  113,   69,    3,    3,    7,    7,    3,
    3,    3,    7,    7,    7,    7,    7,   88,    7,   33,
    7,    7,    7,    7,    7,    7,    7,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   81,   81,   36,  102,   30,   74,   49,   49,   49,   49,
   49,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   37,   37,   37,   37,   37,   37,  114,   37,  104,
   37,  105,   74,  105,   51,   51,  105,  105,   75,   75,
  116,   75,   75,  109,  109,   74,   74,   74,   74,   74,
  101,  101,  101,  101,   -1,   78,   -1,   78,   -1,   78,
   -1,   30,   -1,  105,  105,   80,   80,   80,   52,   52,
   52,   -1,   37,   -1,   -1,   37,   30,   -1,   37,   59,
   59,   59,   67,   67,   67,  107,  107,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   30,   -1,   -1,   30,   30,
   -1,   -1,   30,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   30,   30,   -1,   -1,   -1,   -1,
   -1,   -1,   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  253,  187,    0,    0,  -66,    0, -101,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -68,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  137,    0,    0,   43,    0,  -25,  238,  275,  -37,   34,
    0,    0,  -74,  -72,  -45,  -44,  -33,  -29,  -70,  168,
  -14,  199,  231,   -3, -102,    0,    6,  -15, -178,  227,
    0,    0,    0,    0, -291,  109,  -23,  203,    0,  143,
    0,    0,  -16,  -38,  304,  302,    0,    0,  138,  -49,
  306,  277,    0,    0,    0,    0,    0,    0,  -53,    0,
  -83,    0,   20,    0,  -64,    0,   19,  182,    0,  -48,
  -91,  124,  -19,  -85, -179,  280,  -39,  149,    0,  161,
    0,  -59,  -69,  -63,    4,    0, -167
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  356,    9,   11,  523,  526,  525,  527,  528,  375,
  529,  316,  542,  530,  558,  559,  560,  531,  561,  408,
  532,  315,  595,  537,  538,  298,  539,  540,  266,  541,
  366,  543,  533,  534,  357,  167,  983,  201,  305,  659,
  684,  257,  358,  359,  360,  361,  362,  258,  223,  259,
  260,  241,  363,  261,  262,  728,  194,  775,  678,  738,
  764,  763,  765,  767,  970,  399,  400,  847,   37,  273,
  371,  313,  871,  759,  401,  381, 1004,  576,  264,  975,
  456,  303,  577,  985,  686,  986,  578,  579,  328,  240,
  319, 1010,  425,  426, 1019,  744,  766,  444,  445, 1038,
  270,  737,  477,  492,   67,  676,  246,  628,  325,  196,
  638,  622,  654,  431,  112,   29,  306
#line 205 "build/utility/kmyacc.c.parser"
};

static char yylhs[] = {
    0,    1,    2,    2,    3,    3,    4,    4,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,   33,
   33,   33,   33,    7,    7,    8,    8,    8,    8,    9,
   10,   11,   11,   11,   11,   11,   11,   12,   12,   12,
   12,   32,   13,   13,   14,   15,   16,   17,   17,   18,
   18,   18,   18,   18,   19,   19,   20,   21,   21,   21,
   22,   22,   31,   31,   31,   31,   23,   23,   23,   24,
   25,   25,   25,   25,   25,   25,   26,   27,   28,   28,
   29,   34,   34,   34,   38,   38,   30,   30,  105,  106,
  106,  107,  108,  108,  108,  108,  108,  108,  108,  109,
  109,  109,  109,  109,  109,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  111,  111,  112,  112,  114,  114,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   36,   36,   36,   37,   37,
   37,   37,   37,   37,   37,   39,   39,   40,   40,   41,
   41,   42,   42,   43,   43,   44,   44,   45,   45,   46,
   46,   47,   47,   47,   48,   48,   48,   48,   48,   48,
   49,   49,   49,   50,   50,   50,   51,   51,   51,   51,
   52,   52,   53,   53,   53,   53,   53,   53,   53,   54,
   54,   54,   54,   54,   54,   54,   54,   55,   55,   56,
   56,   56,   56,   56,   56,   56,   95,   95,   96,   96,
   96,   96,   96,   96,   58,   58,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   73,   73,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   61,   61,   60,   60,  115,
   62,  113,  113,   65,   65,   68,   68,   66,   66,   66,
   66,   66,   66,   66,   66,   66,   67,   67,   67,   67,
   67,   67,   67,   67,   67,   67,   69,   69,   70,   70,
   70,   70,   71,   71,   72,   72,   72,   72,   72,   72,
   72,   72,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   63,
   63,   63,  116,   64,   77,   77,   78,   78,   79,   79,
   79,   79,   79,   79,   80,   80,   82,   82,   83,   83,
   83,   81,  100,  100,   84,   84,   84,   84,   84,   84,
   84,   85,   85,   85,   75,   75,   86,   86,   87,   87,
   88,   88,   89,   89,   89,   89,   90,   90,   92,   92,
   93,   93,   94,   94,   94,   94,   94,  101,  101,  101,
  102,  102,  102,  103,  103,   91,   91,   97,   97,   98,
   98,   98,   98,   99,   99,   99,  104
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
    9,    8,    7,    8,    1,    3,    4,    0,    2,    5,
    0,    2,    3,    4,    3,    4,    5,    5,    2,    3,
    2,    2,    1,    4,    4,    3,    4,    3,    1,    3,
    2,    0,    2,    4,    0,    1,    0,    4,    4,    1,
    2,    5,    1,    3,    3,    2,    3,    2,    3,    1,
    2,    4,    3,    3,    4,    1,    1,    1,    1,    1,
    1,    1,    3,    3,    0,    3,    1,    1,    0,    1,
    1,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    1,    1,    1,    2,    2,
    4,    3,    3,    4,    2,    1,    5,    1,    1,    1,
    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
    3,    1,    3,    3,    1,    3,    3,    3,    3,    3,
    1,    3,    3,    1,    3,    3,    1,    3,    3,    3,
    1,    3,    1,    3,    3,    2,    3,    2,    3,    1,
    2,    2,    2,    2,    2,    2,    2,    1,    3,    1,
    2,    4,    3,    3,    4,    2,    1,    1,    4,    8,
    6,    7,    7,    8,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    2,
    6,    3,    3,    3,    3,    2,    2,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    2,    2,    3,    2,    4,    0,
    4,    0,    1,    1,    2,    1,    2,    1,    3,    3,
    2,    2,    3,    5,    5,    4,    1,    1,    1,    1,
    1,    1,    1,    3,    3,    3,    1,    3,    1,    2,
    3,    4,    1,    3,    5,    5,    3,    3,    3,    3,
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
    3,    6,    5,    5,    1,    3,    1,    1,    6,    6,
    7,    1,    0,    2,    5,    5,    5,    6,    6,    6,
    2,    6,    6,    6,    1,    1,    5,    5,    3,    3,
    0,    4,    1,    4,    3,    3,    0,    3,    0,    1,
    1,    3,    1,    4,    3,    3,    2,    2,    1,    2,
    0,    2,    3,    0,    3,    0,    3,    0,    1,    1,
    2,    3,    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 937
#define YYNLSTATES 519
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
#line 172 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 177 "src/kinx.y"
{ kx_ast_root = yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 5:
#line 182 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 16:
#line 199 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strval, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 17:
#line 200 "src/kinx.y"
{ yyerrok; } break;
        case 25:
#line 211 "src/kinx.y"
{ yyerrok; } break;
        case 26:
#line 212 "src/kinx.y"
{ yy_restart(LBBR); yyerrok; } break;
        case 27:
#line 213 "src/kinx.y"
{ yy_restart(IF); yyerrok; } break;
        case 28:
#line 214 "src/kinx.y"
{ yy_restart(DO); yyerrok; } break;
        case 29:
#line 215 "src/kinx.y"
{ yy_restart(WHILE); yyerrok; } break;
        case 30:
#line 216 "src/kinx.y"
{ yy_restart(FOR); yyerrok; } break;
        case 31:
#line 217 "src/kinx.y"
{ yy_restart(TRY); yyerrok; } break;
        case 32:
#line 218 "src/kinx.y"
{ yy_restart(SWITCH); yyerrok; } break;
        case 33:
#line 219 "src/kinx.y"
{ yy_restart(CASE); yyerrok; } break;
        case 34:
#line 220 "src/kinx.y"
{ yy_restart(ENUM); yyerrok; } break;
        case 35:
#line 221 "src/kinx.y"
{ yy_restart(CLASS); yyerrok; } break;
        case 36:
#line 222 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; } break;
        case 37:
#line 223 "src/kinx.y"
{ yy_restart(PRIVATE); yyerrok; } break;
        case 38:
#line 224 "src/kinx.y"
{ yy_restart(PUBLIC); yyerrok; } break;
        case 43:
#line 235 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 44:
#line 236 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 45:
#line 240 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 241 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 47:
#line 242 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 243 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 49:
#line 247 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strval); } break;
        case 50:
#line 251 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 51:
#line 255 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strval); } break;
        case 52:
#line 256 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strval, YYASP(3-3).intval); } break;
        case 53:
#line 257 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strval, -YYASP(4-4).intval); } break;
        case 54:
#line 258 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strval)); } break;
        case 55:
#line 259 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strval, YYASP(5-5).intval)); } break;
        case 56:
#line 260 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strval, -YYASP(6-6).intval)); } break;
        case 61:
#line 271 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 62:
#line 275 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 63:
#line 276 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 64:
#line 280 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 65:
#line 284 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 66:
#line 288 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 292 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 293 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 298 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 70:
#line 305 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 71:
#line 312 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 72:
#line 319 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 73:
#line 321 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 74:
#line 325 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 75:
#line 326 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 76:
#line 330 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 77:
#line 334 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 78:
#line 335 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, "_e", YYASP(2-2).obj, NULL); } break;
        case 79:
#line 336 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(3-5).strval, YYASP(5-5).obj, NULL); } break;
        case 80:
#line 340 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 81:
#line 341 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 82:
#line 345 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 83:
#line 346 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strval)); } break;
        case 84:
#line 347 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 85:
#line 348 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strval)); } break;
        case 86:
#line 352 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 87:
#line 353 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 88:
#line 354 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 89:
#line 358 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 90:
#line 362 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 91:
#line 363 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 92:
#line 364 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 93:
#line 365 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 94:
#line 366 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 95:
#line 367 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 96:
#line 371 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 97:
#line 375 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 98:
#line 379 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object(YYASP(1-1).strval, KX_OBJ_T), NULL); } break;
        case 99:
#line 380 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object(YYASP(3-3).strval, KX_OBJ_T), NULL); } break;
        case 100:
#line 384 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 101:
#line 388 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 102:
#line 389 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 103:
#line 390 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj), NULL, NULL); } break;
        case 104:
#line 394 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 106:
#line 399 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 107:
#line 400 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 108:
#line 404 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 110:
#line 409 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 111:
#line 413 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 113:
#line 418 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 114:
#line 419 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 115:
#line 420 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 116:
#line 421 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 117:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 118:
#line 423 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 120:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 121:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 122:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 123:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 124:
#line 432 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 125:
#line 436 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 126:
#line 437 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 127:
#line 438 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 128:
#line 439 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 129:
#line 440 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 130:
#line 441 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 131:
#line 442 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 132:
#line 443 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 133:
#line 444 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 134:
#line 448 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 135:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 136:
#line 453 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 141:
#line 464 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 142:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 143:
#line 466 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 144:
#line 467 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 145:
#line 468 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 146:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 147:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 148:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 149:
#line 472 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 150:
#line 473 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 151:
#line 474 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 152:
#line 475 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 153:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 154:
#line 477 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 158:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 159:
#line 488 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 160:
#line 489 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 161:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 162:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 163:
#line 492 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 164:
#line 493 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 166:
#line 498 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 170:
#line 508 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 172:
#line 513 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 174:
#line 518 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 176:
#line 523 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 178:
#line 528 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 180:
#line 533 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 182:
#line 538 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 183:
#line 539 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 185:
#line 544 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 186:
#line 545 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 187:
#line 546 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 188:
#line 547 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 189:
#line 548 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 191:
#line 553 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 554 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 194:
#line 559 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 560 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 197:
#line 565 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 566 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 199:
#line 567 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 572 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 203:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 578 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 205:
#line 579 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 206:
#line 580 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 207:
#line 581 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 208:
#line 582 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 210:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 211:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 212:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 213:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 214:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 215:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 216:
#line 593 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 218:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 220:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 221:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 222:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 223:
#line 606 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 224:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 225:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 226:
#line 612 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 228:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 229:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 230:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 231:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 232:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 233:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 234:
#line 626 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 235:
#line 627 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 236:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 237:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 238:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 239:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 240:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 241:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 242:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 243:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 249:
#line 644 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 250:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 251:
#line 646 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 252:
#line 647 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 253:
#line 648 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 254:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 255:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 256:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 257:
#line 652 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 258:
#line 656 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 259:
#line 657 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 260:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 261:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 262:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 263:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 264:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 265:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 266:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 267:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 268:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 269:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 270:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 271:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 272:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 273:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 274:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 275:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 276:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 277:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 278:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 279:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 280:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 281:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 282:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 283:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 284:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 285:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 286:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 287:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 288:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 289:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 290:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 291:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 292:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 293:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 294:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 295:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 296:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 297:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 298:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 299:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 300:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 301:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 302:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 303:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 304:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 305:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 306:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 307:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 308:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 309:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 310:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 311:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 312:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 313:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 314:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 315:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 316:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 317:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 318:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 319:
#line 729 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 320:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 321:
#line 737 "src/kinx.y"
{} break;
        case 323:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 324:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 325:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 326:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 328:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 329:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 330:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 331:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 332:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 333:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_keyvalue_object(YYASP(3-5).strval, YYASP(5-5).obj)); } break;
        case 334:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_keyvalue_object(YYASP(3-5).strval, YYASP(5-5).obj)); } break;
        case 335:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 336:
#line 764 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 337:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 338:
#line 766 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 339:
#line 767 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 340:
#line 768 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 341:
#line 769 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 342:
#line 770 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 343:
#line 771 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 344:
#line 772 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 345:
#line 773 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 347:
#line 778 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 349:
#line 783 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 350:
#line 784 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 351:
#line 785 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 353:
#line 790 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 354:
#line 794 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 355:
#line 795 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 356:
#line 796 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 357:
#line 797 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 358:
#line 798 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 359:
#line 799 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 360:
#line 800 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 361:
#line 801 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-1).strval, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T)); } break;
        case 362:
#line 805 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 363:
#line 806 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 364:
#line 807 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 365:
#line 808 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 366:
#line 809 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 367:
#line 810 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 368:
#line 811 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 369:
#line 812 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 370:
#line 813 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 371:
#line 814 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 372:
#line 815 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 373:
#line 816 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 374:
#line 817 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 375:
#line 818 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 376:
#line 819 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 377:
#line 820 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 378:
#line 821 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 379:
#line 822 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 380:
#line 823 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 381:
#line 824 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 382:
#line 825 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 383:
#line 826 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 384:
#line 827 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 385:
#line 828 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 386:
#line 829 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 387:
#line 830 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 388:
#line 831 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 389:
#line 832 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 390:
#line 833 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 391:
#line 834 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 392:
#line 835 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 393:
#line 836 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 394:
#line 837 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 395:
#line 838 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 396:
#line 842 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 397:
#line 843 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 398:
#line 844 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 399:
#line 845 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 400:
#line 846 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 401:
#line 847 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 402:
#line 848 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 403:
#line 849 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 404:
#line 850 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 405:
#line 851 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 406:
#line 852 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 407:
#line 853 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 408:
#line 854 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 409:
#line 855 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 410:
#line 856 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 411:
#line 857 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 412:
#line 858 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 413:
#line 859 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 414:
#line 860 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 415:
#line 861 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 416:
#line 862 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 417:
#line 863 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 418:
#line 864 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 419:
#line 865 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 420:
#line 866 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 421:
#line 867 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 422:
#line 868 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 423:
#line 869 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 424:
#line 870 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 425:
#line 871 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 426:
#line 872 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 427:
#line 873 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 428:
#line 874 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 429:
#line 875 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 430:
#line 876 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 431:
#line 877 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 432:
#line 878 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 433:
#line 879 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 434:
#line 880 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 435:
#line 881 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 436:
#line 882 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 437:
#line 883 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 438:
#line 884 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 439:
#line 885 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 440:
#line 886 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 441:
#line 887 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 442:
#line 888 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 443:
#line 889 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 444:
#line 890 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 445:
#line 891 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 446:
#line 892 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 447:
#line 893 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 448:
#line 894 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 449:
#line 898 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 450:
#line 899 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 451:
#line 900 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 452:
#line 904 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 453:
#line 908 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 454:
#line 912 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 455:
#line 913 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 457:
#line 918 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 458:
#line 922 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 459:
#line 923 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 460:
#line 924 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 461:
#line 925 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 462:
#line 926 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 463:
#line 927 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 465:
#line 932 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 466:
#line 936 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 467:
#line 937 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 468:
#line 941 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 469:
#line 942 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 470:
#line 943 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 471:
#line 947 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 472:
#line 951 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 473:
#line 952 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 474:
#line 956 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 475:
#line 957 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 476:
#line 958 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 477:
#line 959 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 478:
#line 960 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 479:
#line 961 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 480:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 481:
#line 966 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 482:
#line 967 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 483:
#line 968 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 486:
#line 977 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 487:
#line 978 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 488:
#line 982 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 489:
#line 983 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 490:
#line 987 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 491:
#line 989 "src/kinx.y"
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
        case 493:
#line 1005 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 494:
#line 1006 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 495:
#line 1007 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 496:
#line 1011 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 497:
#line 1012 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 498:
#line 1016 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 501:
#line 1022 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 502:
#line 1026 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 503:
#line 1027 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 504:
#line 1028 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LARY_T); } break;
        case 505:
#line 1029 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LOBJ_T); } break;
        case 506:
#line 1030 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 507:
#line 1034 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 508:
#line 1035 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 509:
#line 1036 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 510:
#line 1040 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 511:
#line 1041 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 512:
#line 1042 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 513:
#line 1046 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 514:
#line 1047 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 515:
#line 1051 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 516:
#line 1052 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 517:
#line 1056 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 520:
#line 1062 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 521:
#line 1063 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 522:
#line 1064 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 525:
#line 1070 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 526:
#line 1074 "src/kinx.y"
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
