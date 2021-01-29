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
#line 1061 "src/kinx.y"

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
  "WhenConditionRange : Array",
  "WhenConditionRange : Object",
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
  "WhenCondition : NEW Factor",
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
#define YYNONTERMS 116

static short yyaction[] = {
  750,  751,  752,  753,  754,  755,  756,  757,  758,  759,
  760,  761,  762,  764,  763,    0,  765,  766,  767,  776,
  778,  777,  214,  787,  788,  789,  791,  793,  138,  139,
  140,  353,  785,  786,   19,   65,   66,   67,   68,   69,
   70,   71,   72,   73,   74,   75,   76,   77,-32766,-32766,
-32766,  779,  780,  781,-32766,  782,  783,  107,  392,  332,
   16,  333,   40,  179,  314,  774,  290,  775,  334,  768,
  769,  770,  771,  772,  773,  -75,  749,  179,-32766, -106,
  515,  784,  517,  516,  518,  389,  519,   78,   40,  107,
  795,  520,  521,  390,   88,  522,  353,  800,  801,  799,
  790,  792,  794,  796,  797,  798,  871,  872,  873,  874,
  875,  876,  877,  878,  879,  880,  881,  882,  883,  241,
  884,  107,  885,  886,  887,  895,  897,  896,   40,  907,
  908,  909,  911,  913,  102,  723,  724, -374,  905,  906,
   38,  555,   41,  289,   44,  523,  332,   16,  333,  240,
  524,   82,  526,  525,  223,  334, -106,  898,  899,  900,
   37,  901,  902,  514,  505,  129,  130,  131, 1000,  513,
  747,  893,  107,  894,   38,  748,  888,  889,  890,  891,
  892,  107,  959,    4,   53,  109,  387,  903,  904,  107,
  111,  369,   38,   45, -348,   26,  915,  -74,   46,  370,
   27, -348,   43,  920,  921,  919,  910,  912,  914,  916,
  917,  918,  160,  374,  838,  375,   10,  376,  842,  299,
  844,  845,  221,  222,  377,  108,  335,  850,  336,  155,
  218,  219,  300,   62,   55,  281,   64,    4,   79,  109,
  132,  133,  136,   40,   37,  100,  414,   45,   80,   26,
  179,  983,   38, -375,  137, 1000,  180,  181,  309,   40,
   38,   38,  804,  310,  378,  379,  380,  814,  255,  868,
  117,   40,  311,   63,  121,  283,  284,  337,  381,  339,
  382,  341,  113,  256,  257,   34,   35,   36,  113,  230,
   47,  107,   28,  116,  383,  870,   47,  531,   28,  117,
   84,   48, -101,   29,  464,   64,   52,   41,-32766,   44,
   40,  156,  239,  837,  838,  839,  840,  841,  842,  843,
  844,  845,  846,  847,  848,  849,   64,  850,   40,  851,
  852,  853,  861,  863,  862,  118,  815,  585,  122,  404,
  263,  400,  543,  540,  127,  128,  616,  618,  619,   40,
-32766,  742,  478,  465,  362,   60,  123,  814,  141,  225,
  134,  135,   38,  114,  864,  865,  866,  807,  867,  868,
  117,  747,  430,   63,  615,  613,  748,  295,  859,  296,
  860,  368,  614,  854,  855,  856,  857,  858,   86,  398,
  145,  146,  147,  148,  869,  870,  402,  160,  331,  461,
  332,   16,  333,  444,  280,  367,  399,  236,  237,  334,
  106,  335,  400,  336,  298,  215,  216,  484,   87,   83,
  281,  405,  289,  290,  297,  587,  537,  160,  331,  586,
  332,   16,  333,  466,  280,  407,  435,  236,  237,  334,
  106,  335,  468,  336,  544,  215,  216,  484,   87,   83,
  281,  541,  712,  242,  611,  117,  651,  746,  970,  802,
  283,  284,  337,  338,  339,  340,  341,  292,  243,  244,
   31,   32,   33,    7,  343,  263,   40,    6,   38,   37,
   39, -381,  531,  242,    5,  115,  538, -101,  718,  809,
  283,  284,  337,  338,  339,  340,  341,  239,  243,  244,
   31,   32,   33,  717,  343,  824,  647,  826,   58,  470,
  455,  197,  719,  986,   81,  987,  922, -101,  160,  331,
    8,  332,   16,  333,  968,  280,  609,  649,  236,  237,
  334,  106,  335,  710,  336,  805,  215,  216,  484,   87,
   83,  281,  275,  279,  443,   59,   61,  621,  570,  160,
  331,   90,  332,   16,  333,   91,  280,  553,  504,  236,
  237,  334,  106,  335,  575,  336,  574,  215,  216,  484,
   87,   83,  281,  584,  242,  573,  120,  571,  577,  930,
  929,  283,  284,  337,  338,  339,  340,  341,  572,  243,
  244,   31,   32,   33,   92,  343,  588,  576,   93,   89,
  740,  124,  112,  719,   54,  242,  220,  436, -101,  208,
  406,    8,  283,  284,  337,  338,  339,  340,  341,  110,
  243,  244,   31,   32,   33,   85,  343,   42,  364,  628,
  556,  487,   -1,  160,  331,  226,  332,   16,  333, -101,
  280,  224, -352,  236,  237,  334,  106,  335,  217,  336,
  119,  215,  216,  484,   87,   83,  281,  104,  101,   98,
 -373,  160,  331, -376,  332,   16,  333, -377,  280, -378,
  595,  236,  237,  334,  106,  335,  363,  336,  227,  215,
  216,  484,   87,   83,  281,  207,  206,  205,  203,  242,
  202,  201,  200,  199,  198,  196,  283,  284,  337,  338,
  339,  340,  341,  195,  243,  244,   31,   32,   33,  194,
  343,   99,   97,   96,   95,   94,   51,  242,  204,  434,
    0,  472,  312, -101,  283,  284,  337,  338,  339,  340,
  341,   21,  243,  244,   31,   32,   33,   20,  343,   18,
   17,  991,  989,  612,  739,  620,  531,  652,  972,  160,
  331, -101,  332,   16,  333,  713,  280,  928,  803,  236,
  237,  334,  106,  335,  741,  336,  743,  215,  216,  484,
   87,   83,  281,  923,  469,  462,  454,  160,  331,  451,
  332,   16,  333,  330,  280,  329,  328,  236,  237,  334,
  106,  335,  327,  336,  326,  215,  216,  484,   87,   83,
  281,  325,  324,  322,  320,  242,  319,  318,   24,   23,
   22,    3,  283,  284,  337,  338,  339,  340,  341,    2,
  243,  244,   31,   32,   33,  125,  343,  126,    0,    0,
  806,    0,    0,  242,  722,    0,    0,    0,    0, -101,
  283,  284,  337,  338,  339,  340,  341,    0,  243,  244,
   31,   32,   33,    0,  343,    0,    0,    0,    0,    0,
    0,    0,  721,    0,    0,  160,  331, -101,  332,   16,
  333,    0,  280,    0,    0,  236,  237,  334,  106,  335,
    0,  336,    0,  215,  216,  484,   87,   83,  281,    0,
    0,    0,    0,  160,  331,    0,  332,   16,  333,    0,
  280,    0,    0,  236,  237,  334,  106,  335,    0,  336,
    0,  215,  216,  484,   87,   83,  281,    0,    0,    0,
    0,  242,    0,    0,    0,    0,    0,    0,  283,  284,
  337,  338,  339,  340,  341,    0,  243,  244,   31,   32,
   33,    0,  343,    0,    0,    0,    0,    0,    0,  242,
  720,    0,    0,    0,    0, -101,  283,  284,  337,  338,
  339,  340,  341,    0,  243,  244,   31,   32,   33,    0,
  343,    0,    0,    0,    0,    0,    0,    0,  536,    0,
    0,  160,  331, -101,  332,   16,  333,    0,  280,    0,
    0,  236,  237,  334,  106,  335,    0,  336,    0,  215,
  216,  484,   87,   83,  281,    0,    0,    0,    0,  160,
  331,    0,  332,   16,  333,    0,  280,    0,    0,  236,
  237,  334,  106,  335,    0,  336,    0,  215,  216,  484,
   87,   83,  281,    0,    0,    0,    0,  242,    0,    0,
    0,    0,    0,    0,  283,  284,  337,  338,  339,  340,
  341,    0,  243,  244,   31,   32,   33,    0,  343,    0,
    0,    0,    0,    0,    0,  242,  535,    0,    0,    0,
    0, -101,  283,  284,  337,  338,  339,  340,  341,    0,
  243,  244,   31,   32,   33,    0,  343,    0,    0,    0,
    0,    0,    0,    0,  534,    0,    0,  160,  331, -101,
  332,   16,  333,    0,  280,    0,    0,  236,  237,  334,
  106,  335,    0,  336,    0,  215,  216,  484,   87,   83,
  281,    0,    0,    0,    0,  160,  331,    0,  332,   16,
  333,    0,  280,    0,    0,  236,  237,  334,  106,  335,
    0,  336,    0,  215,  216,  484,   87,   83,  281,    0,
    0,    0,    0,  242,    0,    0,    0,    0,    0,    0,
  283,  284,  337,  338,  339,  340,  341,    0,  243,  244,
   31,   32,   33,    0,  343,    0,    0,    0,    0,    0,
    0,  242,  533,    0,    0,    0,    0, -101,  283,  284,
  337,  338,  339,  340,  341,    0,  243,  244,   31,   32,
   33,    0,  343,    0,    0,    0,    0,    0,    0,    0,
  532,    0,    0,  160,  331, -101,  332,   16,  333,    0,
  280,    0,    0,  236,  237,  334,  106,  335,    0,  336,
    0,  215,  216,  484,   87,   83,  281,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  154,    0,    0,    0,    0,    0,    0,    0,    0,  242,
    0,    0,    0,    0,  149,  150,  283,  284,  337,  338,
  339,  340,  341,  485,  243,  244,   31,   32,   33,    0,
  343,    0,    0,    0,    0,  728,  730,  731,    0,  356,
    0,    0,    0, -101,    0,  282,    0,    0,    0,    0,
    0,    0,    0,  946,  357,  358,-32766,-32766,    0,  342,
  747,    0,  732,  727,  725,  748,    0,    1,    0,   44,
    0,  726,    0,    0,  151,    0,    0,   50,    0,   30,
    0,    0,    0,  238,  285,    0,  152,  142,  486,    0,
  143,  144,   25,    0,    0,-32766,-32766,-32766,    0,    0,
    0,-32766,    0,    0,    0,    0,    0,    0,    0,   40,
    0,    0,    0,    0,    0,    0,-32766,    0,    0,    0,
    0,    0,    0,    0,    0,-32766,    0,    0,-32766,-32766,
    0,    0,-32766,-32766
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1394

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,    0,   18,   19,   20,   21,
   22,   23,   19,   25,   26,   27,   28,   29,  105,  106,
  107,    2,   34,   35,    3,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   71,   72,
   73,   53,   54,   55,   77,   57,   58,   14,    4,    4,
    5,    6,   85,   16,    3,   67,   78,   69,   13,   71,
   72,   73,   74,   75,   76,    7,   78,   16,  101,   91,
    2,   83,    4,    5,    6,   87,    8,   90,   85,   14,
   92,   13,   14,   95,   91,   17,    2,   99,  100,  101,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   62,
   16,   14,   18,   19,   20,   21,   22,   23,   85,   25,
   26,   27,   28,   29,    7,   32,   33,   94,   34,   35,
   85,   94,   85,   78,   87,   67,    4,    5,    6,    9,
   72,   62,   74,   75,   56,   13,   91,   53,   54,   55,
   85,   57,   58,   85,   86,   27,   28,   29,   79,   91,
   78,   67,   14,   69,   85,   83,   72,   73,   74,   75,
   76,   14,   78,   85,   90,   87,   79,   83,   84,   14,
   87,   87,   85,   95,   86,   97,   92,    7,   95,   95,
   97,   93,   94,   99,  100,  101,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   62,   85,   62,   87,
  102,  103,   92,   85,   85,    7,   79,   95,   62,   97,
   16,   71,   85,   94,  104,   79,   61,   62,   78,   85,
   85,   85,   88,   83,   53,   54,   55,   93,   57,   58,
   59,   85,   10,   62,   37,   64,   65,   66,   67,   68,
   69,   70,   87,   72,   73,   74,   75,   76,   87,   78,
   95,   14,   97,   87,   83,   84,   95,   86,   97,   59,
   23,   95,   91,   97,   79,   62,   95,   85,   59,   87,
   85,   18,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   62,   16,   85,   18,
   19,   20,   21,   22,   23,   98,   93,   91,   30,   93,
   85,  101,   82,   82,   25,   26,   53,   54,   55,   85,
  101,   96,   92,   92,   19,   90,   31,   93,   36,   94,
   34,   35,   85,   59,   53,   54,   55,   60,   57,   58,
   59,   78,   78,   62,   81,   82,   83,   78,   67,   78,
   69,   78,   89,   72,   73,   74,   75,   76,   95,   78,
   51,   52,   61,   62,   83,   84,   78,    1,    2,   78,
    4,    5,    6,   79,    8,   78,   95,   11,   12,   13,
   14,   15,  101,   17,   78,   19,   20,   21,   22,   23,
   24,   78,   78,   78,   78,   78,   78,    1,    2,   78,
    4,    5,    6,   78,    8,   79,   79,   11,   12,   13,
   14,   15,   79,   17,   82,   19,   20,   21,   22,   23,
   24,   82,   84,   57,   84,   59,   84,   84,   84,   88,
   64,   65,   66,   67,   68,   69,   70,   85,   72,   73,
   74,   75,   76,   85,   78,   85,   85,   85,   85,   85,
   85,   94,   86,   57,   85,   59,   86,   91,   86,   86,
   64,   65,   66,   67,   68,   69,   70,  101,   72,   73,
   74,   75,   76,   86,   78,   86,   86,   86,   90,   87,
   87,   95,   86,   88,   90,   88,   88,   91,    1,    2,
   94,    4,    5,    6,   88,    8,   88,   88,   11,   12,
   13,   14,   15,   88,   17,   88,   19,   20,   21,   22,
   23,   24,   90,   90,   90,   90,   90,   96,   91,    1,
    2,   91,    4,    5,    6,   91,    8,   91,   91,   11,
   12,   13,   14,   15,   91,   17,   91,   19,   20,   21,
   22,   23,   24,   91,   57,   91,   59,   91,   91,   91,
   91,   64,   65,   66,   67,   68,   69,   70,   91,   72,
   73,   74,   75,   76,   91,   78,   91,   91,   91,   91,
   96,   99,   93,   86,   93,   57,   93,   93,   91,   93,
   95,   94,   64,   65,   66,   67,   68,   69,   70,   93,
   72,   73,   74,   75,   76,   93,   78,   93,   95,   94,
   94,   94,    0,    1,    2,   94,    4,    5,    6,   91,
    8,   94,   94,   11,   12,   13,   14,   15,   94,   17,
   94,   19,   20,   21,   22,   23,   24,   94,   94,   94,
   94,    1,    2,   94,    4,    5,    6,   94,    8,   94,
   96,   11,   12,   13,   14,   15,   95,   17,   95,   19,
   20,   21,   22,   23,   24,   95,   95,   95,   95,   57,
   95,   95,   95,   95,   95,   95,   64,   65,   66,   67,
   68,   69,   70,   95,   72,   73,   74,   75,   76,   95,
   78,   95,   95,   95,   95,   95,   95,   57,   95,   95,
   -1,   96,   96,   91,   64,   65,   66,   67,   68,   69,
   70,   96,   72,   73,   74,   75,   76,   96,   78,   96,
   96,   96,   96,   96,   96,   96,   86,   96,   96,    1,
    2,   91,    4,    5,    6,   96,    8,   96,   96,   11,
   12,   13,   14,   15,   96,   17,   96,   19,   20,   21,
   22,   23,   24,   96,   96,   96,   96,    1,    2,   96,
    4,    5,    6,   96,    8,   96,   96,   11,   12,   13,
   14,   15,   96,   17,   96,   19,   20,   21,   22,   23,
   24,   96,   96,   96,   96,   57,   96,   96,   96,   96,
   96,   96,   64,   65,   66,   67,   68,   69,   70,   96,
   72,   73,   74,   75,   76,  100,   78,  101,   -1,   -1,
  103,   -1,   -1,   57,   86,   -1,   -1,   -1,   -1,   91,
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
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   18,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   57,
   -1,   -1,   -1,   -1,   32,   33,   64,   65,   66,   67,
   68,   69,   70,   41,   72,   73,   74,   75,   76,   -1,
   78,   -1,   -1,   -1,   -1,   53,   54,   55,   -1,   57,
   -1,   -1,   -1,   91,   -1,   63,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   71,   72,   73,   32,   33,   -1,   77,
   78,   -1,   80,   81,   82,   83,   -1,   85,   -1,   87,
   -1,   89,   -1,   -1,   92,   -1,   -1,   95,   -1,   97,
   -1,   -1,   -1,  101,  102,   -1,  104,  105,  106,   -1,
  108,  109,  110,   -1,   -1,   71,   72,   73,   -1,   -1,
   -1,   77,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   85,
   -1,   -1,   -1,   -1,   -1,   -1,   92,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  101,   -1,   -1,  104,  105,
   -1,   -1,  108,  109
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1212,  211,  426,  517,  396,  660, 1096, 1008,  864,  632,
  548, 1124,  980,  892,  776,  748, 1212, 1212, 1212, 1212,
 1212, 1212, 1212, 1212, 1212,  373,  368,  372,  370,  374,
   -2,  104,  104,  104,  104,  104,  104,  419,  420,  421,
  311,  249,  249,   55,  174,  176,  176,  176,  176,  264,
  107,    3,  167,  277,   89,   43,  243,   75,  175,  175,
  175,  175,  159,  175,  175,  175,  175,  175,  175,  175,
  175,  175,  175,  175,  175,  175,  175,  175,  175,  175,
  175,  175,  175,  158,  158,  186,  225,  394,  394,  394,
  394,  394,  394,  394,  391,  391,  391,  391,  393,  391,
  391,  393,  391, 1242,  393, 1242,  391,  391,  391,  391,
  395,  391,  391,  391, 1242, 1242,  391,  391,  391,  391,
  391,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,
  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,
  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23, 1284,
 1284, 1284, 1284, 1284, 1284, 1284, 1284,   47,  234,   94,
   78,  504,  445,  439,  451,  438,  436,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,  222,
  293,  293,   98,  255,  195,  152,  152,  152,  152,  390,
  390,  390,  390,  390,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,  201,
  201,  138,  138,  138,  222,  222,  222,  142,  222,  222,
  222,   65,  -12,  180,  180,  180,  180,  180,  206,  -77,
  108,  -77,  -77,  190,   61,   61,  344,  345,  416,  623,
  624,   92,  335,  327,  303,  237,  319,  326,  150,  339,
  331,  265,  489,  488,  246,  335,  327,  303,  294,  644,
  643,  508,  626,  240,  319,  326,  326,  326,  326,  326,
  150,  150,  339,  460,  574,  261,  625,  641,  635,  260,
  399,  351,  533,  348,  348,  727,   29,  547,  140,   29,
   29,  547,  318,   29,  533,  599,  599,  399,  399,  399,
  566,  534,  533,  262,  514,   29,   29,  537,  537,  423,
  423,  399,  399,   29,  535,  583,  399,  399,  399,  399,
  399,  535,  399,  583,  399,  399,  399,  399,  399,  399,
  399,  620,  619,  621,  618,  536,  382,  506,  299,  301,
  346,  336,  600,  554,   15,  505,  308,  325,  502,  725,
  726,  322,   54,  617,  457,  497,  581,  614,  608,  418,
  455,  526,  343,  515,  356,  392,  388,  598,  597,  428,
  677,  596,  595,  593,  620,  619,  621,  618,  569,  573,
  575,  299,  346,  387,  565,  447,  532,  670,  668,  371,
  662,  487,  616,  238,   68,  190,  486,  484,  564,  357,
  591,  592,  452,  482,  347,  454,  324,  661,  541,  711,
  516,  710,  708,  417,  683,  403,  532,  680,  307,  308,
  556,  325,  502,  725,  726,  322,  322,  322,  659,  511,
  590,  127,  418,  464,  321,  679,  355,  400,  424,  424,
  424,  475,  473,  363,  678,  652,  707,  706,  705,  698,
  696,  563,  723,  651,  304,  425,  422,  422,  690,   31,
  503,  689,  563,  715,  649,  369,  453,  456,  467,  648,
  427,  687,  466,  507,  714,  647,  646,  713,  362,  424,
  402,  712,  402,  645,    0,    0,    0,    0, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242,   -2,   -2,   -2,   -2,   -2,    0,    0,
    0,    0,    0,    0,    0,  311,  311,  311,    0,  311,
  311, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242,    0, 1242,    0, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242,    0,    0, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242,   -3,   -3,   -3,    0,   -3,
   -3,   -3,   -3,   -3,   -3,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  293,    0,    0,
  103,  103,  103,  103,  103,  103,  103,  103,  103,  103,
  103,  103,   92,   92,   92,   92,   92,   92,   92,   92,
   92,   92,   92,   92,   92,   92,   92,  103,  103,    0,
    0,    0,   92,   92,   92,    0,   92,   92,   92,   29,
   29,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  265,    0,    0,   29,   29,  399,  399,  399,    0,
  581,  614,  608,    0,    0,    0,    0,    0,    0,    0,
  513,  513,    0,  581,  614,  608,  592,  509,  509,  509,
  509,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  513,  509,    0,  509,  509,  509
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 279

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  368,  369,  370,32767,32767,32767,
32767,32767,  323,32767,32767,  504,  504,  504,  504,32767,
32767,32767,32767,32767,32767,   92,32767,  104,32767,32767,
32767,32767,  104,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   92,   95,  330,32767,  104,  104,  104,
  104,  104,  104,  104,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  361,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  206,  208,32767,
32767,32767,32767,32767,32767,  363,32767,32767,32767,  106,
32767,32767,32767,32767,32767,32767,32767,  335,   90,  328,
  333,  510,  337,  343,  345,  331,   93,  334,  341,32767,
  115,  117,  218,32767,  112,  216,  217,  214,  213,  157,
  511,  344,  346,  342,  485,  485,  485,  485,  485,  485,
  485,  485,  485,  485,  485,  485,  485,  485,32767,  116,
  118,  182,  183,  184,32767,32767,32767,32767,  364,  365,
32767,  358,  359,32767,32767,32767,32767,32767,  502,  194,
  259,  196,  195,  445,  135,  135,  106,  106,32767,32767,
32767,32767,32767,32767,32767,  169,  180,  185,  191,  201,
  203,  445,32767,32767,32767,  379,  366,  367,32767,32767,
32767,32767,32767,32767,  181,  187,  189,  190,  186,  188,
  192,  193,  202,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  320,  106,  459,   77,  106,
  106,  459,32767,  106,32767,  483,  483,32767,32767,  355,
  513,  322,32767,   80,  322,  106,  106,  477,  477,  497,
  497,32767,32767,  106,  139,  500,32767,32767,32767,32767,
32767,  139,32767,  500,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  259,32767,32767,  170,  172,  174,  176,
  178,  197,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  105,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  349,  351,  353,  360,  240,  242,
  243,  371,  372,  260,32767,32767,  324,32767,32767,32767,
32767,32767,32767,32767,  245,  241,32767,32767,  348,32767,
32767,32767,   51,32767,32767,32767,32767,32767,  489,32767,
  486,32767,32767,32767,32767,32767,  325,32767,32767,  171,
32767,  173,  175,  177,  179,  198,  199,  200,32767,  505,
32767,32767,   75,32767,32767,32767,  323,32767,  449,  450,
  447,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  255,32767,32767,32767,32767,  496,  494,32767,   62,
32767,32767,32767,32767,32767,32767,   54,  446,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  448,
  465,32767,32767,32767,  513,  439,  439,  513
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  173,  169,  171,  171,  171,  171,  169,  161,  170,  161,
  418,  171,  168,  169,  167,  549,  273,  395,  253,  167,
  828,  253,  625,  996,  625,  703,  699,  700,  692,  693,
  695,  697,  416,  954,  954,  711,  650,  610,  969,  738,
  168,  176,  175,  164,  167,  167,  167,  167,  167,  167,
  167,  170,  170,  170,  170,  174,  170,  170,  173,  170,
  599,  178,  419,  157,  158,  157,  162,  172,  163,  177,
  165,  644,  925,  166,  212,  213,  644,  644,  644,  644,
  924,  644,  644,  644,  644,  644,  644,  644,  644,  644,
  644,  644,  644,  644,  644,  644,  644,  644,  644,  644,
  644,  715,  270,  271,  715,  715,  715,  715,  411,  412,
  417,  445,  446,  447,  448,  449,  450,  452,  458,  463,
  471,  626,  709,  626,  608,  709,  709,  709,  709,  453,
  475,  483,  953,  480,  421,  413,  420,  655,  482,  265,
  266,  267,  268,  269,  422,  617,  617,  617,  394,  608,
  608,  372,  373,  423,  372,  373,  424,  955,  955,  566,
  408,  408,  408,  408,  408,  408,  408,  408,  408,  408,
  408,  408,  408,  408,  408,  231,  232,  305,  209,  210,
  233,  251,  251,  264,  251,  251,  251,  716,  653,  549,
  716,  716,  716,  716,  653,  653,  653,  653,  653,  288,
   14,   14,  272,  235,   12,   13,   15,  981,  433,  460,
  473,  474,  477,  481,  598,  598,  963,  964,  288,  259,
  260,  262,  274,  976,  276,  277,  932,  278,  431,  596,
  569,  554,  439,  440,  479,  961,  962,  949,  950,  951,
  366,  943,  401,  944,  956,  957,  958,  952,  567,  945,
  287,  287,  287,  287,  287,  287,  287,  287,  287,  287,
  287,  287,  287,  287,  287,  287,  287,  287,  287,  287,
  287,  287,  287,  287,  287,  388,  601,  388,  308,  437,
  579,  317,  306,  185,  186,  187,  188,  948,  315,  323,
  476,  979,  979,  979,  979,  979,  979,  979,  979,  979,
  979,  979,  979,  979,  979,  979,  602,  457,  579,  582,
  105,  432,  359,  359,  978,  359,  359,  359,  425,  426,
  427,  980,  980,  980,  980,  980,  980,  980,  980,  980,
  980,  980,  980,  980,  980,  980,  590,  302,  630,  153,
    0,  360,  360,  360,    0,  360,  360,  360,  835,  817,
  633,  634,  635,  636,  637,  638,  639,  640,  641,  642,
  643,  631,  632,  630,  995,  820,  940,  997,  490,  967,
  744,  744,  622,    0,    0,    0,    0,  491,  352,  493,
  493,  493,  493,  493,  352,  459,  552,  551,  560,  561,
  559,  558,  557,  191,    0,  190,  190,  190,  190,  355,
  183,    0,  183,    0,  190,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  355,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  192,    0,
    0,  191,    0,    0,  193,    0,    0,    0,    0,    0,
    0,    0,    0,  391,    0,    0,  396,  397,    0,    0,
  403,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  441,  442,    0,    0,    0,    0,    0,    0,
  321
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 491

static char yygcheck[] = {
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   65,   35,   35,   35,   35,   33,   77,   72,   77,   35,
   71,   77,    7,   98,    7,   54,   54,   54,   54,   54,
   54,   54,   66,    7,    7,   57,   57,   57,   57,   57,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
  111,   35,   42,   35,   35,   35,   35,   35,   35,   35,
   35,   39,   64,   35,   48,   48,   39,   39,   39,   39,
   64,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   39,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   39,    7,   50,   50,    7,    7,    7,    7,   91,   91,
   91,   91,   91,   91,   91,   91,   91,   91,   91,   91,
   91,   39,   58,   39,   58,   58,   58,   58,   58,   96,
   96,   96,   39,   39,   43,   39,   39,   39,   39,   49,
   49,   49,   49,   49,   44,   72,   72,   72,   61,   58,
   58,   74,   74,   45,   74,   74,   46,    7,    7,    7,
   72,   72,   72,   72,   72,   72,   72,   72,   72,   72,
   72,   72,   72,   72,   72,   51,   51,   38,  108,  108,
   72,   72,   72,   47,   72,   72,   72,   95,   95,   33,
   95,   95,   95,   95,   95,   95,   95,   95,   95,    7,
    3,    3,   53,  105,    3,    3,    3,   72,   38,   38,
   38,   38,   38,   38,  106,  106,    7,    7,    7,   68,
   68,   68,   68,   93,   68,   68,   78,   68,   19,  110,
    7,    7,   79,   79,   79,    7,    7,    7,    7,    7,
    9,    7,   99,    7,    7,    7,    7,    7,    7,    7,
   80,   80,   80,   80,   80,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,  104,   61,  104,   89,  112,
  104,   87,  104,   56,   56,   56,   56,  100,  100,  100,
  100,   61,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,   62,  101,  104,  104,
  113,   61,   61,   61,  102,   61,   61,   61,   52,   52,
   52,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   30,  115,   36,  103,
   -1,   62,   62,   62,   -1,   62,   62,   62,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,    4,   59,
   59,   59,   59,   -1,   -1,   -1,   -1,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,   37,   -1,   37,   37,   37,   37,   30,
   37,   -1,   37,   -1,   37,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   30,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   37,   -1,
   -1,   37,   -1,   -1,   37,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   30,   -1,   -1,   30,   30,   -1,   -1,
   30,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   30,   30,   -1,   -1,   -1,   -1,   -1,   -1,
   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  198,  368,    0,    0,  -81,    0,  -44,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   14,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  177,    0,    0,  -28,    0,  -43,  285,  350,  120,   18,
    0,    0,  -59,   12,   21,   29,   31,   57,  -53,   10,
  -32,   39,  180,   61, -117,    0,  134,    9,  -60,  216,
    0,   97,  127,    0, -222,  -39,  -24,    0,  125,    0,
    0,  -22,  -34,    0,  119,    0,    0, -198,    6,  173,
  250,    0,    0,    0,    0,    0,    0,  -27,    0,  -18,
    0,  -87,    0,   15,    0,    5,   83,    0,  -31,  -49,
   63,   -3,   -9, -148,  225,   45,  -20,    0,   -2,    0,
   -6,  -45,  -25,  -11,    0, -149
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  344,    9,   11,  492,  495,  494,  496,  497,  365,
  498,  304,  511,  499,  527,  528,  529,  500,  530,  393,
  501,  303,  564,  506,  507,  286,  508,  509,  254,  510,
  354,  512,  502,  503,  345,  159,  939,  189,  293,  629,
  654,  245,  346,  347,  348,  349,  350,  246,  211,  247,
  248,  229,  351,  249,  250,  698,  182,  745,  648,  708,
  734,  733,  735,  737,  926,  385,  386,   56,  261,  361,
  301,  827,  729,  384,  371,  960,  545,  252,  931,  438,
  291,  546,  941,  656,  942,  547,  548,  316,  228,  307,
  966,  409,  410,  975,  714,  736,  428,  429,  994,  258,
  707,  456,  467,   57,  646,  234,  597,  313,  184,  607,
  591,  624,  415,  103,   49,  294
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
   29,   34,   34,   34,   38,   38,   30,   30,  104,  105,
  105,  106,  107,  107,  107,  107,  107,  107,  107,  108,
  108,  108,  108,  108,  108,  109,  109,  109,  109,  109,
  109,  109,  109,  109,  109,  110,  110,  111,  111,  113,
  113,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   36,   36,   36,   37,
   37,   37,   37,   37,   37,   37,   39,   39,   40,   40,
   41,   41,   42,   42,   43,   43,   44,   44,   45,   45,
   46,   46,   47,   47,   47,   48,   48,   48,   48,   48,
   48,   49,   49,   49,   50,   50,   50,   51,   51,   51,
   51,   52,   52,   53,   53,   53,   53,   53,   53,   53,
   54,   54,   54,   54,   54,   54,   54,   54,   55,   55,
   56,   56,   56,   56,   56,   56,   56,   94,   94,   95,
   95,   95,   95,   95,   95,   58,   58,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   72,
   72,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   61,   61,   60,   60,
  114,   62,  112,  112,   65,   65,   67,   67,   66,   66,
   66,   66,   66,   68,   68,   69,   69,   69,   69,   70,
   70,   71,   71,   71,   71,   71,   71,   71,   71,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   63,   63,   63,  115,
   64,   76,   76,   77,   77,   78,   78,   78,   78,   78,
   78,   79,   79,   81,   81,   82,   82,   82,   80,   99,
   99,   83,   83,   83,   83,   83,   83,   83,   84,   84,
   84,   74,   74,   85,   85,   86,   86,   87,   87,   88,
   88,   88,   88,   89,   89,   91,   91,   92,   92,   93,
   93,   93,   93,   93,  100,  100,  100,  101,  101,  101,
  102,  102,   90,   90,   96,   96,   97,   97,   97,   97,
   98,   98,   98,  103
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
    0,    2,    3,    4,    3,    4,    5,    5,    2,    3,
    2,    2,    1,    4,    4,    3,    4,    3,    1,    3,
    2,    0,    2,    4,    0,    1,    0,    4,    4,    1,
    2,    5,    1,    1,    1,    2,    3,    2,    3,    1,
    2,    4,    3,    3,    4,    1,    1,    1,    1,    1,
    1,    1,    3,    3,    2,    0,    3,    1,    1,    0,
    1,    1,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    1,    1,    1,    2,
    2,    4,    3,    3,    4,    2,    1,    5,    1,    1,
    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
    1,    3,    1,    3,    3,    1,    3,    3,    3,    3,
    3,    1,    3,    3,    1,    3,    3,    1,    3,    3,
    3,    1,    3,    1,    3,    3,    2,    3,    2,    3,
    1,    2,    2,    2,    2,    2,    2,    2,    1,    3,
    1,    2,    4,    3,    3,    4,    2,    1,    1,    4,
    8,    6,    7,    7,    8,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    6,    3,    3,    3,    3,    2,    2,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    2,    2,    2,    3,    2,    4,
    0,    4,    0,    1,    1,    2,    1,    2,    1,    2,
    2,    3,    4,    1,    3,    1,    2,    3,    4,    1,
    3,    5,    5,    3,    3,    3,    3,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    2,    2,    3,    3,    2,    0,
    3,    3,    3,    1,    3,    1,    4,    3,    6,    3,
    3,    1,    3,    1,    1,    6,    6,    7,    1,    0,
    2,    5,    5,    5,    6,    6,    6,    2,    6,    6,
    6,    1,    1,    5,    5,    3,    3,    0,    4,    1,
    4,    3,    3,    0,    3,    0,    1,    1,    3,    1,
    4,    1,    1,    2,    2,    1,    2,    0,    2,    3,
    0,    3,    0,    3,    0,    1,    1,    2,    3,    4,
    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 893
#define YYNLSTATES 488
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
#line 171 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 176 "src/kinx.y"
{ kx_ast_root = yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 5:
#line 181 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 16:
#line 198 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strval, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 17:
#line 199 "src/kinx.y"
{ yyerrok; } break;
        case 25:
#line 210 "src/kinx.y"
{ yyerrok; } break;
        case 26:
#line 211 "src/kinx.y"
{ yy_restart(LBBR); yyerrok; } break;
        case 27:
#line 212 "src/kinx.y"
{ yy_restart(IF); yyerrok; } break;
        case 28:
#line 213 "src/kinx.y"
{ yy_restart(DO); yyerrok; } break;
        case 29:
#line 214 "src/kinx.y"
{ yy_restart(WHILE); yyerrok; } break;
        case 30:
#line 215 "src/kinx.y"
{ yy_restart(FOR); yyerrok; } break;
        case 31:
#line 216 "src/kinx.y"
{ yy_restart(TRY); yyerrok; } break;
        case 32:
#line 217 "src/kinx.y"
{ yy_restart(SWITCH); yyerrok; } break;
        case 33:
#line 218 "src/kinx.y"
{ yy_restart(CASE); yyerrok; } break;
        case 34:
#line 219 "src/kinx.y"
{ yy_restart(ENUM); yyerrok; } break;
        case 35:
#line 220 "src/kinx.y"
{ yy_restart(CLASS); yyerrok; } break;
        case 36:
#line 221 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; } break;
        case 37:
#line 222 "src/kinx.y"
{ yy_restart(PRIVATE); yyerrok; } break;
        case 38:
#line 223 "src/kinx.y"
{ yy_restart(PUBLIC); yyerrok; } break;
        case 43:
#line 234 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 44:
#line 235 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 45:
#line 239 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 240 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 47:
#line 241 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 242 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 49:
#line 246 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strval); } break;
        case 50:
#line 250 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 51:
#line 254 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strval); } break;
        case 52:
#line 255 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strval, YYASP(3-3).intval); } break;
        case 53:
#line 256 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strval, -YYASP(4-4).intval); } break;
        case 54:
#line 257 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strval)); } break;
        case 55:
#line 258 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strval, YYASP(5-5).intval)); } break;
        case 56:
#line 259 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strval, -YYASP(6-6).intval)); } break;
        case 61:
#line 270 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 62:
#line 274 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 63:
#line 275 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 64:
#line 279 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 65:
#line 283 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 66:
#line 287 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 291 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 292 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 297 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 70:
#line 304 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 71:
#line 311 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 72:
#line 318 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 73:
#line 320 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 74:
#line 324 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 76:
#line 329 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 77:
#line 333 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 78:
#line 334 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, "_e", YYASP(2-2).obj, NULL); } break;
        case 79:
#line 335 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(3-5).strval, YYASP(5-5).obj, NULL); } break;
        case 80:
#line 339 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 81:
#line 340 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 82:
#line 344 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 83:
#line 345 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strval)); } break;
        case 84:
#line 346 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 85:
#line 347 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strval)); } break;
        case 86:
#line 351 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 87:
#line 352 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 88:
#line 353 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 89:
#line 357 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 90:
#line 361 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 91:
#line 362 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 92:
#line 363 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 93:
#line 364 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 94:
#line 365 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 95:
#line 366 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 96:
#line 370 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 97:
#line 374 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 98:
#line 378 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object(YYASP(1-1).strval, KX_OBJ_T), NULL); } break;
        case 99:
#line 379 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object(YYASP(3-3).strval, KX_OBJ_T), NULL); } break;
        case 100:
#line 383 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 101:
#line 387 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 102:
#line 388 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 103:
#line 389 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj), NULL, NULL); } break;
        case 104:
#line 393 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 106:
#line 398 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 107:
#line 399 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 108:
#line 403 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 110:
#line 408 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 111:
#line 412 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 115:
#line 419 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 116:
#line 420 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 117:
#line 421 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 118:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 120:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 121:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 122:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 123:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 124:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 125:
#line 435 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 126:
#line 436 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 127:
#line 437 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 128:
#line 438 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 129:
#line 439 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 130:
#line 440 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 131:
#line 441 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 132:
#line 442 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 133:
#line 443 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 134:
#line 444 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 135:
#line 448 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 136:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 137:
#line 453 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 142:
#line 464 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 143:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 144:
#line 466 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 145:
#line 467 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 146:
#line 468 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 147:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 148:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 149:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 150:
#line 472 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 151:
#line 473 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 152:
#line 474 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 153:
#line 475 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 154:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 155:
#line 477 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 159:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 160:
#line 488 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 161:
#line 489 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 162:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 163:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 164:
#line 492 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 165:
#line 493 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 167:
#line 498 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 171:
#line 508 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 173:
#line 513 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 175:
#line 518 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 177:
#line 523 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 179:
#line 528 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 181:
#line 533 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 183:
#line 538 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 184:
#line 539 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 186:
#line 544 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 187:
#line 545 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 188:
#line 546 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 189:
#line 547 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 190:
#line 548 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 553 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 193:
#line 554 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 559 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 560 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 565 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 199:
#line 566 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 200:
#line 567 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 572 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 205:
#line 578 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 206:
#line 579 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 207:
#line 580 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 208:
#line 581 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 209:
#line 582 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 211:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 212:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 213:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 214:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 215:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 216:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 217:
#line 593 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 219:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 221:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 222:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 223:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 224:
#line 606 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 225:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 226:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 227:
#line 612 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 229:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 230:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 231:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 232:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 233:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 234:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 235:
#line 626 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 236:
#line 627 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 237:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 238:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 239:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 240:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 241:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 242:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 243:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 244:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 250:
#line 644 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 251:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 252:
#line 646 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 253:
#line 647 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 254:
#line 648 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 255:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 256:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 257:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 258:
#line 652 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 259:
#line 656 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 260:
#line 657 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 261:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 262:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 263:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 264:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 265:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 266:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 267:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 268:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 269:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 270:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 271:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 272:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 273:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 274:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 275:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 276:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 277:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 278:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 279:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 280:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 281:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 282:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 283:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 284:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 285:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 286:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 287:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 288:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 289:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 290:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 291:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 292:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 293:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 294:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 295:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 296:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 297:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 298:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 299:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 300:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 301:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 302:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 303:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 304:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 305:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 306:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 307:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 308:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 309:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 310:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 311:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 312:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 313:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 314:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 315:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 316:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 317:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 318:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 319:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 320:
#line 729 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 321:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 322:
#line 737 "src/kinx.y"
{} break;
        case 324:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 325:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 326:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 327:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 329:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 330:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 331:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 332:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 334:
#line 761 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 336:
#line 766 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 337:
#line 767 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 338:
#line 768 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 340:
#line 773 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 341:
#line 777 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 342:
#line 778 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 343:
#line 779 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 344:
#line 780 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 345:
#line 781 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 346:
#line 782 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 347:
#line 783 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 348:
#line 784 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-1).strval, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T)); } break;
        case 349:
#line 788 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 350:
#line 789 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 351:
#line 790 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 352:
#line 791 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 353:
#line 792 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 354:
#line 793 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 355:
#line 794 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 356:
#line 795 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 357:
#line 796 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 358:
#line 797 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 359:
#line 798 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 360:
#line 799 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 361:
#line 800 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 362:
#line 801 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 363:
#line 802 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 364:
#line 803 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 365:
#line 804 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 366:
#line 805 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 367:
#line 806 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 368:
#line 807 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 369:
#line 808 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 370:
#line 809 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 371:
#line 810 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 372:
#line 811 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 373:
#line 812 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 374:
#line 813 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 375:
#line 814 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 376:
#line 815 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 377:
#line 816 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 378:
#line 817 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 379:
#line 818 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 380:
#line 819 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 381:
#line 820 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 382:
#line 821 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 383:
#line 825 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 384:
#line 826 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 385:
#line 827 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 386:
#line 828 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 387:
#line 829 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 388:
#line 830 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 389:
#line 831 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 390:
#line 832 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 391:
#line 833 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 392:
#line 834 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 393:
#line 835 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 394:
#line 836 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 395:
#line 837 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 396:
#line 838 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 397:
#line 839 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 398:
#line 840 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 399:
#line 841 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 400:
#line 842 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 401:
#line 843 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 402:
#line 844 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 403:
#line 845 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 404:
#line 846 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 405:
#line 847 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 406:
#line 848 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 407:
#line 849 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 408:
#line 850 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 409:
#line 851 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 410:
#line 852 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 411:
#line 853 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 412:
#line 854 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 413:
#line 855 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 414:
#line 856 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 415:
#line 857 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 416:
#line 858 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 417:
#line 859 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 418:
#line 860 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 419:
#line 861 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 420:
#line 862 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 421:
#line 863 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 422:
#line 864 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 423:
#line 865 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 424:
#line 866 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 425:
#line 867 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 426:
#line 868 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 427:
#line 869 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 428:
#line 870 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 429:
#line 871 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 430:
#line 872 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 431:
#line 873 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 432:
#line 874 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 433:
#line 875 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 434:
#line 876 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 435:
#line 877 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 436:
#line 881 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 437:
#line 882 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 438:
#line 883 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 439:
#line 887 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 440:
#line 891 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 441:
#line 895 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 442:
#line 896 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 444:
#line 901 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 445:
#line 905 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 446:
#line 906 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 447:
#line 907 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 448:
#line 908 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 449:
#line 909 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 450:
#line 910 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 452:
#line 915 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 453:
#line 919 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 454:
#line 920 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 455:
#line 924 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 456:
#line 925 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 457:
#line 926 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 458:
#line 930 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 459:
#line 934 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 460:
#line 935 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 461:
#line 939 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 462:
#line 940 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 463:
#line 941 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 464:
#line 942 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 465:
#line 943 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 466:
#line 944 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 467:
#line 945 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 468:
#line 949 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 469:
#line 950 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 470:
#line 951 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 473:
#line 960 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 474:
#line 961 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 475:
#line 965 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 476:
#line 966 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 477:
#line 970 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 478:
#line 972 "src/kinx.y"
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
        case 480:
#line 988 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 481:
#line 989 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 482:
#line 990 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 483:
#line 994 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 484:
#line 995 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 485:
#line 999 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 488:
#line 1005 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 489:
#line 1009 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 490:
#line 1010 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 491:
#line 1011 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 492:
#line 1012 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 493:
#line 1013 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 494:
#line 1017 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 495:
#line 1018 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 496:
#line 1019 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 497:
#line 1023 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 498:
#line 1024 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 499:
#line 1025 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 500:
#line 1029 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 501:
#line 1030 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 502:
#line 1034 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 503:
#line 1035 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 504:
#line 1039 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 507:
#line 1045 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 508:
#line 1046 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 509:
#line 1047 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 512:
#line 1053 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 513:
#line 1057 "src/kinx.y"
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
