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
#line 1060 "src/kinx.y"

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
  748,  749,  750,  751,  752,  753,  754,  755,  756,  757,
  758,  759,  760,  762,  761,    0,  763,  764,  765,  774,
  776,  775,  213,  785,  786,  787,  789,  791,  138,  139,
  140,  352,  783,  784,   19,   65,   66,   67,   68,   69,
   70,   71,   72,   73,   74,   75,   76,   77,-32766,-32766,
-32766,  777,  778,  779,-32766,  780,  781,  107,  391,  331,
   16,  332,   40,  178,  313,  772,  289,  773,  333,  766,
  767,  768,  769,  770,  771,  100,  747,  178,-32766, -106,
  514,  782,  516,  515,  517,  388,  518,   78,   40,  107,
  793,  519,  520,  389,   88,  521,  352,  798,  799,  797,
  788,  790,  792,  794,  795,  796,  869,  870,  871,  872,
  873,  874,  875,  876,  877,  878,  879,  880,  881,  240,
  882,  107,  883,  884,  885,  893,  895,  894,   40,  905,
  906,  907,  909,  911,  -75,  721,  722, -373,  903,  904,
   38,  554,   41,  288,   44,  522,  331,   16,  332,  239,
  523,   82,  525,  524,  222,  333, -106,  896,  897,  898,
   37,  899,  900,  513,  504,  129,  130,  131,  998,  512,
  -74,  891,  107,  892,   38,  107,  886,  887,  888,  889,
  890,   84,  957,    4,   53,  109,  413,  901,  902,  107,
  111,  368,   38,   45, -347,   26,  913,  102,   46,  369,
   27, -347,   43,  918,  919,  917,  908,  910,  912,  914,
  915,  916,  159,  373,  836,  374,   10,  375,  840,  298,
  842,  843,  220,  221,  376,  108,  334,  848,  335,  155,
  217,  218,  299,   62,   55,  280,   64,    4,   79,  109,
  132,  133,  116,   38,   37,  310,   40,   45,  178,   26,
   48,  981,   29, -374,  386,  998,  179,  180,  308,   40,
   38,   38,  802,  309,  377,  378,  379,  812,  254,  866,
  117,  107,  361,   63,  121,  282,  283,  336,  380,  338,
  381,  340,  113,  255,  256,   34,   35,   36,  113,  229,
   47,  136,   28,  262,  382,  868,   47,  530,   28,  117,
  539,-32766, -101,  137,  740,   64,   52,   60,  127,  128,
  464,  224,  238,  835,  836,  837,  838,  839,  840,  841,
  842,  843,  844,  845,  846,  847,   64,  848,   40,  849,
  850,  851,  859,  861,  860,  118,  812,   80,  463,  122,
  542,  399,   38,-32766,   40,  123,  615,  617,  618,   40,
  477,  745,   41,  584,   44,  403,  746,  813,  134,  135,
   40,  145,  146,  141,  862,  863,  864,  114,  865,  866,
  117,  745,  805,   63,  614,  612,  746,  294,  857,  297,
  858,  460,  613,  852,  853,  854,  855,  856,   86,  397,
  147,  148,  434,  367,  867,  868,  401,  159,  330,  429,
  331,   16,  332,  366,  279,  467,  398,  235,  236,  333,
  106,  334,  399,  335,  296,  214,  215,  483,   87,   83,
  280,  295,  288,  289,  465,  586,  536,  159,  330,  585,
  331,   16,  332,  404,  279,  443,  406,  235,  236,  333,
  106,  334,  543,  335,  540,  214,  215,  483,   87,   83,
  280,  968,  710,  241,  610,  117,  649,  744,  469,   37,
  282,  283,  336,  337,  338,  339,  340,  291,  242,  243,
   31,   32,   33,    7,  342,  262,    6,   39,   40,   38,
    5, -380,  530,  241,  537,  120,  716, -101,  807,  715,
  282,  283,  336,  337,  338,  339,  340,  238,  242,  243,
   31,   32,   33,  822,  342,  645,  824,  569,  454,   90,
  800,  984,  717,  985,   81,  920,  966, -101,  159,  330,
    8,  331,   16,  332,  608,  279,  647,  708,  235,  236,
  333,  106,  334,  803,  335,   91,  214,  215,  483,   87,
   83,  280,  274,  278,  442,   58,   59,   61,  124,  159,
  330,  552,  331,   16,  332,  503,  279,  574,  573,  235,
  236,  333,  106,  334,  583,  335,  572,  214,  215,  483,
   87,   83,  280,  570,  241,  576,  115,  928,  927,  571,
   92,  282,  283,  336,  337,  338,  339,  340,  587,  242,
  243,   31,   32,   33,  575,  342,   93,   89,  626,  125,
  112,   54,  219,  717,  435,  241,  207,  110, -101,   85,
  196,    8,  282,  283,  336,  337,  338,  339,  340,   42,
  242,  243,   31,   32,   33,  555,  342,  486,  225,  223,
  216,  119,   -1,  159,  330,  104,  331,   16,  332, -101,
  279,  101, -351,  235,  236,  333,  106,  334,   98,  335,
 -372,  214,  215,  483,   87,   83,  280, -375, -376, -377,
  126,  159,  330,  405,  331,   16,  332,  363,  279,  362,
  226,  235,  236,  333,  106,  334,  206,  335,  205,  214,
  215,  483,   87,   83,  280,  204,  202,  201,  200,  241,
  199,  198,  197,  195,  194,  193,  282,  283,  336,  337,
  338,  339,  340,   99,  242,  243,   31,   32,   33,   97,
  342,   96,   95,   94,   51,  203,  433,  241,  620,  738,
  594,  471,  311, -101,  282,  283,  336,  337,  338,  339,
  340,   21,  242,  243,   31,   32,   33,   20,  342,   18,
   17,  989,  987,  611,  737,  619,  530,  650,  970,  159,
  330, -101,  331,   16,  332,  711,  279,  926,  801,  235,
  236,  333,  106,  334,  739,  335,  741,  214,  215,  483,
   87,   83,  280,  921,  468,  461,  453,  159,  330,  450,
  331,   16,  332,  329,  279,  328,  327,  235,  236,  333,
  106,  334,  326,  335,  325,  214,  215,  483,   87,   83,
  280,  324,  323,  321,  319,  241,  318,  317,   24,   23,
   22,    3,  282,  283,  336,  337,  338,  339,  340,    2,
  242,  243,   31,   32,   33,  804,  342,    0,    0,    0,
    0,    0,    0,  241,  720,    0,    0,    0,    0, -101,
  282,  283,  336,  337,  338,  339,  340,    0,  242,  243,
   31,   32,   33,    0,  342,    0,    0,    0,    0,    0,
    0,    0,  719,    0,    0,  159,  330, -101,  331,   16,
  332,    0,  279,    0,    0,  235,  236,  333,  106,  334,
    0,  335,    0,  214,  215,  483,   87,   83,  280,    0,
    0,    0,    0,  159,  330,    0,  331,   16,  332,    0,
  279,    0,    0,  235,  236,  333,  106,  334,    0,  335,
    0,  214,  215,  483,   87,   83,  280,    0,    0,    0,
    0,  241,    0,    0,    0,    0,    0,    0,  282,  283,
  336,  337,  338,  339,  340,    0,  242,  243,   31,   32,
   33,    0,  342,    0,    0,    0,    0,    0,    0,  241,
  718,    0,    0,    0,    0, -101,  282,  283,  336,  337,
  338,  339,  340,    0,  242,  243,   31,   32,   33,    0,
  342,    0,    0,    0,    0,    0,    0,    0,  535,    0,
    0,  159,  330, -101,  331,   16,  332,    0,  279,    0,
    0,  235,  236,  333,  106,  334,    0,  335,    0,  214,
  215,  483,   87,   83,  280,    0,    0,    0,    0,  159,
  330,    0,  331,   16,  332,    0,  279,    0,    0,  235,
  236,  333,  106,  334,    0,  335,    0,  214,  215,  483,
   87,   83,  280,    0,    0,    0,    0,  241,    0,    0,
    0,    0,    0,    0,  282,  283,  336,  337,  338,  339,
  340,    0,  242,  243,   31,   32,   33,    0,  342,    0,
    0,    0,    0,    0,    0,  241,  534,    0,    0,    0,
    0, -101,  282,  283,  336,  337,  338,  339,  340,    0,
  242,  243,   31,   32,   33,    0,  342,    0,    0,    0,
    0,    0,    0,    0,  533,    0,    0,  159,  330, -101,
  331,   16,  332,    0,  279,    0,    0,  235,  236,  333,
  106,  334,    0,  335,    0,  214,  215,  483,   87,   83,
  280,    0,    0,    0,    0,  159,  330,    0,  331,   16,
  332,    0,  279,    0,    0,  235,  236,  333,  106,  334,
    0,  335,    0,  214,  215,  483,   87,   83,  280,    0,
    0,    0,    0,  241,    0,    0,    0,    0,    0,    0,
  282,  283,  336,  337,  338,  339,  340,    0,  242,  243,
   31,   32,   33,    0,  342,    0,    0,    0,    0,    0,
    0,  241,  532,    0,    0,    0,    0, -101,  282,  283,
  336,  337,  338,  339,  340,    0,  242,  243,   31,   32,
   33,    0,  342,    0,    0,    0,    0,    0,    0,    0,
  531,    0,    0,  159,  330, -101,  331,   16,  332,    0,
  279,    0,    0,  235,  236,  333,  106,  334,    0,  335,
    0,  214,  215,  483,   87,   83,  280,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  154,    0,    0,    0,    0,    0,    0,    0,    0,  241,
    0,    0,    0,    0,  149,  150,  282,  283,  336,  337,
  338,  339,  340,  484,  242,  243,   31,   32,   33,    0,
  342,    0,    0,    0,    0,  726,  728,  729,    0,  355,
    0,    0,    0, -101,    0,  281,    0,    0,    0,    0,
    0,    0,    0,  944,  356,  357,-32766,-32766,    0,  341,
  745,    0,  730,  725,  723,  746,    0,    1,    0,   44,
    0,  724,    0,    0,  151,    0,    0,   50,    0,   30,
    0,    0,    0,  237,  284,    0,  152,  142,  485,    0,
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
    7,   67,   14,   69,   85,   14,   72,   73,   74,   75,
   76,   23,   78,   85,   90,   87,   79,   83,   84,   14,
   87,   87,   85,   95,   86,   97,   92,    7,   95,   95,
   97,   93,   94,   99,  100,  101,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   62,   85,   62,   87,
  102,  103,   87,   85,   85,   10,   85,   95,   16,   97,
   95,   71,   97,   94,   79,   79,   61,   62,   78,   85,
   85,   85,   88,   83,   53,   54,   55,   93,   57,   58,
   59,   14,   19,   62,   37,   64,   65,   66,   67,   68,
   69,   70,   87,   72,   73,   74,   75,   76,   87,   78,
   95,   92,   97,   85,   83,   84,   95,   86,   97,   59,
   82,   59,   91,  104,   96,   62,   95,   90,   25,   26,
   92,   94,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   62,   16,   85,   18,
   19,   20,   21,   22,   23,   98,   93,   62,   79,   30,
   82,  101,   85,  101,   85,   31,   53,   54,   55,   85,
   92,   78,   85,   91,   87,   93,   83,   93,   34,   35,
   85,   51,   52,   36,   53,   54,   55,   59,   57,   58,
   59,   78,   60,   62,   81,   82,   83,   78,   67,   78,
   69,   78,   89,   72,   73,   74,   75,   76,   95,   78,
   61,   62,   79,   78,   83,   84,   78,    1,    2,   78,
    4,    5,    6,   78,    8,   79,   95,   11,   12,   13,
   14,   15,  101,   17,   78,   19,   20,   21,   22,   23,
   24,   78,   78,   78,   78,   78,   78,    1,    2,   78,
    4,    5,    6,   78,    8,   79,   79,   11,   12,   13,
   14,   15,   82,   17,   82,   19,   20,   21,   22,   23,
   24,   84,   84,   57,   84,   59,   84,   84,   87,   85,
   64,   65,   66,   67,   68,   69,   70,   85,   72,   73,
   74,   75,   76,   85,   78,   85,   85,   85,   85,   85,
   85,   94,   86,   57,   86,   59,   86,   91,   86,   86,
   64,   65,   66,   67,   68,   69,   70,  101,   72,   73,
   74,   75,   76,   86,   78,   86,   86,   91,   87,   91,
   88,   88,   86,   88,   90,   88,   88,   91,    1,    2,
   94,    4,    5,    6,   88,    8,   88,   88,   11,   12,
   13,   14,   15,   88,   17,   91,   19,   20,   21,   22,
   23,   24,   90,   90,   90,   90,   90,   90,   99,    1,
    2,   91,    4,    5,    6,   91,    8,   91,   91,   11,
   12,   13,   14,   15,   91,   17,   91,   19,   20,   21,
   22,   23,   24,   91,   57,   91,   59,   91,   91,   91,
   91,   64,   65,   66,   67,   68,   69,   70,   91,   72,
   73,   74,   75,   76,   91,   78,   91,   91,   94,  100,
   93,   93,   93,   86,   93,   57,   93,   93,   91,   93,
   95,   94,   64,   65,   66,   67,   68,   69,   70,   93,
   72,   73,   74,   75,   76,   94,   78,   94,   94,   94,
   94,   94,    0,    1,    2,   94,    4,    5,    6,   91,
    8,   94,   94,   11,   12,   13,   14,   15,   94,   17,
   94,   19,   20,   21,   22,   23,   24,   94,   94,   94,
  101,    1,    2,   95,    4,    5,    6,   95,    8,   95,
   95,   11,   12,   13,   14,   15,   95,   17,   95,   19,
   20,   21,   22,   23,   24,   95,   95,   95,   95,   57,
   95,   95,   95,   95,   95,   95,   64,   65,   66,   67,
   68,   69,   70,   95,   72,   73,   74,   75,   76,   95,
   78,   95,   95,   95,   95,   95,   95,   57,   96,   96,
   96,   96,   96,   91,   64,   65,   66,   67,   68,   69,
   70,   96,   72,   73,   74,   75,   76,   96,   78,   96,
   96,   96,   96,   96,   96,   96,   86,   96,   96,    1,
    2,   91,    4,    5,    6,   96,    8,   96,   96,   11,
   12,   13,   14,   15,   96,   17,   96,   19,   20,   21,
   22,   23,   24,   96,   96,   96,   96,    1,    2,   96,
    4,    5,    6,   96,    8,   96,   96,   11,   12,   13,
   14,   15,   96,   17,   96,   19,   20,   21,   22,   23,
   24,   96,   96,   96,   96,   57,   96,   96,   96,   96,
   96,   96,   64,   65,   66,   67,   68,   69,   70,   96,
   72,   73,   74,   75,   76,  103,   78,   -1,   -1,   -1,
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
 1212,  211,  517,  426,  396,  660, 1096, 1008,  864,  632,
  548, 1124,  980,  892,  776,  748, 1212, 1212, 1212, 1212,
 1212, 1212, 1212, 1212, 1212,  373,  368,  372,  370,  367,
   -2,  104,  104,  104,  104,  104,  104,  417,  419,  420,
  311,  242,  242,   55,  174,  176,  176,  176,  176,  243,
  175,    3,  107,  158,   89,   43,  264,   75,  257,  257,
  257,  257,  159,  257,  257,  257,  257,  257,  257,  257,
  257,  257,  257,  257,  257,  257,  257,  257,  257,  257,
  257,  257,  257,  161,  161,  275,  259,  374,  374,  374,
  374,  374,  374,  374,  393,  393,  393,  393,  394,  393,
  393,  394,  393, 1242,  394, 1242,  393,  393,  393,  393,
  392,  393,  393,  393, 1242, 1242,  393,  393,  393,  393,
  393,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,
  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,
  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23, 1284,
 1284, 1284, 1284, 1284, 1284, 1284,   47,  232,   94,   78,
  623,  439,  438,  622,  436,  428,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,  267,  293,
  293,   98,  208,  195,  152,  152,  152,  152,  390,  390,
  390,  390,  390,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,  201,  201,
  138,  138,  138,  267,  267,  267,  142,  267,  267,  267,
   65,  -12,  180,  180,  180,  180,  180,  155,  -77,  108,
  -77,  -77,  163,   61,   61,  344,  345,  515,  620,  621,
  273,  253,  325,  315,  237,  283,  324,  199,  310,  329,
  217,  487,  486,  262,  253,  325,  315,  321,  644,  643,
  506,  626,  240,  283,  324,  324,  324,  324,  324,  199,
  199,  310,  418,  624,  218,  625,  641,  635,  258,  395,
  351,  572,  348,  348,  722,   29,  535,  140,   29,   29,
  535,  318,   29,  572,  597,  597,  395,  395,  395,  556,
  526,  572,  235,  511,   29,   29,  533,  533,  421,  421,
  395,  395,   29,  504,  575,  395,  395,  395,  395,  395,
  504,  395,  575,  395,  395,  395,  395,  395,  395,  395,
  618,  617,  619,  616,  531,  382,  503,  299,  343,  336,
  301,  598,  536,   15,  497,  309,  314,  449,  499,  559,
  327,   54,  614,  416,  488,  574,  600,  599,  455,  456,
  514,  355,  568,  357,  391,  388,  596,  595,  427,  677,
  593,  592,  591,  618,  617,  619,  616,  563,  564,  565,
  299,  336,  387,  554,  445,  516,  670,  668,  422,  662,
  484,  608,   68,  127,  163,  482,  475,  547,  313,  583,
  590,  452,  473,  347,  454,  356,  661,  534,  711,  513,
  710,  708,  403,  683,  402,  516,  680,  312,  309,  537,
  314,  449,  499,  559,  327,  327,  327,  659,  508,  581,
  190,  455,  444,  303,  679,  346,  398,  424,  424,  424,
  467,  466,  326,  678,  652,  707,  706,  705,  698,  696,
  541,  723,  651,  308,  423,  371,  371,  690,   31,  489,
  689,  541,  715,  649,  362,  453,  457,  464,  648,  425,
  687,  460,  505,  714,  647,  646,  713,  360,  424,  400,
  712,  400,  645,    0,    0,    0,    0, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242,   -2,   -2,   -2,   -2,   -2,    0,    0,    0,
    0,    0,    0,    0,  311,  311,  311,    0,  311,  311,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
    0, 1242,    0, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242,    0,    0, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242, 1242,
 1242, 1242, 1242,   -3,   -3,   -3,    0,   -3,   -3,   -3,
   -3,   -3,   -3,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  293,    0,    0,  103,  103,
  103,  103,  103,  103,  103,  103,  103,  103,  103,  103,
  273,  273,  273,  273,  273,  273,  273,  273,  273,  273,
  273,  273,  273,  273,  273,  103,  103,    0,    0,    0,
  273,  273,  273,    0,  273,  273,  273,   29,   29,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  217,
    0,    0,   29,   29,  395,  395,  395,    0,  574,  600,
  599,    0,    0,    0,    0,    0,    0,    0,  509,  509,
    0,  574,  600,  599,  590,  507,  507,  507,  507,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  509,
  507,    0,  507,  507,  507
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 278

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  367,  368,  369,32767,32767,32767,
32767,32767,  322,32767,32767,  503,  503,  503,  503,32767,
32767,32767,32767,32767,32767,   92,32767,  104,32767,32767,
32767,32767,  104,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   92,   95,  329,32767,  104,  104,  104,
  104,  104,  104,  104,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  360,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  205,  207,32767,
32767,32767,32767,32767,32767,  362,32767,32767,  106,32767,
32767,32767,32767,32767,32767,32767,  334,   90,  327,  332,
  509,  336,  342,  344,  330,   93,  333,  340,32767,  115,
  117,  217,32767,  112,  215,  216,  213,  212,  156,  510,
  343,  345,  341,  484,  484,  484,  484,  484,  484,  484,
  484,  484,  484,  484,  484,  484,  484,32767,  116,  118,
  181,  182,  183,32767,32767,32767,32767,  363,  364,32767,
  357,  358,32767,32767,32767,32767,32767,  501,  193,  258,
  195,  194,  444,  134,  134,  106,  106,32767,32767,32767,
32767,32767,32767,32767,  168,  179,  184,  190,  200,  202,
  444,32767,32767,32767,  378,  365,  366,32767,32767,32767,
32767,32767,32767,  180,  186,  188,  189,  185,  187,  191,
  192,  201,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  319,  106,  458,   77,  106,  106,
  458,32767,  106,32767,  482,  482,32767,32767,  354,  512,
  321,32767,   80,  321,  106,  106,  476,  476,  496,  496,
32767,32767,  106,  138,  499,32767,32767,32767,32767,32767,
  138,32767,  499,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  258,32767,32767,  169,  171,  173,  175,  177,
  196,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  105,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  348,  350,  352,  359,  239,  241,  242,
  370,  371,  259,32767,32767,  323,32767,32767,32767,32767,
32767,32767,32767,  244,  240,32767,32767,  347,32767,32767,
32767,   51,32767,32767,32767,32767,32767,  488,32767,  485,
32767,32767,32767,32767,32767,  324,32767,32767,  170,32767,
  172,  174,  176,  178,  197,  198,  199,32767,  504,32767,
32767,   75,32767,32767,32767,  322,32767,  448,  449,  446,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  254,32767,32767,32767,32767,  495,  493,32767,   62,32767,
32767,32767,32767,32767,32767,   54,  445,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  447,  464,
32767,32767,32767,  512,  438,  438,  512
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  172,  168,  170,  170,  170,  170,  168,  160,  169,  160,
  417,  170,  167,  168,  166,  826,   14,   14,  394,  166,
   12,   13,   15,  623,  994,  623,  701,  697,  698,  690,
  691,  693,  695,  598,  952,  952,  184,  185,  186,  187,
  167,  175,  174,  163,  166,  166,  166,  166,  166,  166,
  166,  169,  169,  169,  169,  173,  169,  169,  172,  169,
  415,  177,  420,  156,  157,  156,  161,  171,  162,  176,
  164,  642,  923,  165,  211,  212,  642,  642,  642,  642,
  922,  642,  642,  642,  642,  642,  642,  642,  642,  642,
  642,  642,  642,  642,  642,  642,  642,  642,  642,  642,
  642,  713,  269,  270,  713,  713,  713,  713,  410,  411,
  416,  444,  445,  446,  447,  448,  449,  451,  457,  462,
  470,  624,  707,  624,  607,  707,  707,  707,  707,  272,
  418,  252,  951,  479,  252,  412,  419,  653,  481,  709,
  648,  609,  967,  736,  548,  616,  616,  616,  393,  607,
  607,  264,  265,  266,  267,  268,  421,  953,  953,  565,
  407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
  407,  407,  407,  407,  407,  371,  372,  304,  371,  372,
  232,  250,  250,  422,  250,  250,  250,  714,  651,  423,
  714,  714,  714,  714,  651,  651,  651,  651,  651,  287,
  946,  314,  322,  475,  452,  474,  482,  979,  432,  459,
  472,  473,  476,  480,  230,  231,  961,  962,  287,  258,
  259,  261,  273,  271,  275,  276,  263,  277,  208,  209,
  568,  553,  438,  439,  478,  959,  960,  947,  948,  949,
  234,  941,  974,  942,  954,  955,  956,  950,  566,  943,
  286,  286,  286,  286,  286,  286,  286,  286,  286,  286,
  286,  286,  286,  286,  286,  286,  286,  286,  286,  286,
  286,  286,  286,  286,  286,  600,  424,  425,  426,  965,
  742,  742,  430,  597,  597,  930,  595,  400,  365,  307,
  977,  977,  977,  977,  977,  977,  977,  977,  977,  977,
  977,  977,  977,  977,  977,  601,  436,  456,  316,  105,
  431,  358,  358,  976,  358,  358,  358,  548,  301,    0,
  978,  978,  978,  978,  978,  978,  978,  978,  978,  978,
  978,  978,  978,  978,  978,  589,  153,  628,    0,    0,
  359,  359,  359,    0,  359,  359,  359,  833,  815,  631,
  632,  633,  634,  635,  636,  637,  638,  639,  640,  641,
  629,  630,  628,  993,  818,  938,  995,  489,    0,    0,
    0,    0,    0,    0,    0,    0,  490,  351,  492,  492,
  492,  492,  492,  351,  458,  551,  550,  559,  560,  558,
  557,  556,  190,    0,  189,  189,  189,  189,  354,  182,
  387,  182,  387,  189,    0,  578,    0,  305,    0,    0,
    0,    0,    0,  354,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  578,  581,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  191,    0,    0,
  190,    0,    0,  192,    0,    0,    0,    0,    0,    0,
    0,    0,  390,    0,    0,  395,  396,    0,    0,  402,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  440,  441,    0,    0,    0,    0,    0,    0,  320
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 490

static char yygcheck[] = {
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   65,   35,   35,   35,   35,   71,    3,    3,   72,   35,
    3,    3,    3,    7,   98,    7,   54,   54,   54,   54,
   54,   54,   54,  111,    7,    7,   56,   56,   56,   56,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   66,   35,   43,   35,   35,   35,   35,   35,   35,   35,
   35,   39,   64,   35,   48,   48,   39,   39,   39,   39,
   64,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   39,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   39,    7,   50,   50,    7,    7,    7,    7,   91,   91,
   91,   91,   91,   91,   91,   91,   91,   91,   91,   91,
   91,   39,   58,   39,   58,   58,   58,   58,   58,   77,
   42,   77,   39,   39,   77,   39,   39,   39,   39,   57,
   57,   57,   57,   57,   33,   72,   72,   72,   61,   58,
   58,   49,   49,   49,   49,   49,   44,    7,    7,    7,
   72,   72,   72,   72,   72,   72,   72,   72,   72,   72,
   72,   72,   72,   72,   72,   74,   74,   38,   74,   74,
   72,   72,   72,   45,   72,   72,   72,   95,   95,   46,
   95,   95,   95,   95,   95,   95,   95,   95,   95,    7,
  100,  100,  100,  100,   96,   96,   96,   72,   38,   38,
   38,   38,   38,   38,   51,   51,    7,    7,    7,   68,
   68,   68,   68,   53,   68,   68,   47,   68,  108,  108,
    7,    7,   79,   79,   79,    7,    7,    7,    7,    7,
  105,    7,   93,    7,    7,    7,    7,    7,    7,    7,
   80,   80,   80,   80,   80,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,   61,   52,   52,   52,   59,
   59,   59,   19,  106,  106,   78,  110,   99,    9,   89,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   62,  112,  101,   87,  113,
   61,   61,   61,  102,   61,   61,   61,   33,  115,   -1,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   30,  103,   36,   -1,   -1,
   62,   62,   62,   -1,   62,   62,   62,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,    4,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,   37,   -1,   37,   37,   37,   37,   30,   37,
  104,   37,  104,   37,   -1,  104,   -1,  104,   -1,   -1,
   -1,   -1,   -1,   30,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  104,  104,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   37,   -1,   -1,
   37,   -1,   -1,   37,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   30,   -1,   -1,   30,   30,   -1,   -1,   30,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   30,   30,   -1,   -1,   -1,   -1,   -1,   -1,   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,   14,  367,    0,    0,  -80,    0,    5,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   69,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  177,    0,    0,  101,    0,  -43,  284,  349,  120,   18,
    0,    0,    9,  -60,   33,   59,   64,  100,  -53,   22,
  -32,   78,  138,   82, -116,    0, -113,  113,  -59,  126,
    0,   97,  127,    0, -221,  -39,    4,    0,  125,    0,
    0,  -27,  -33,    0,  143,    0,    0,  -84,   66,  173,
  250,    0,    0,    0,    0,    0,    0,    1,    0,   -6,
    0,  -86,    0,   35,    0,    6,  158,    0,  -30,   -3,
  -23,   -2,   -9, -150,  350,   83,   50,    0,   49,    0,
   52,  -72,    3,  -11,    0, -167
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  343,    9,   11,  491,  494,  493,  495,  496,  364,
  497,  303,  510,  498,  526,  527,  528,  499,  529,  392,
  500,  302,  563,  505,  506,  285,  507,  508,  253,  509,
  353,  511,  501,  502,  344,  158,  937,  188,  292,  627,
  652,  244,  345,  346,  347,  348,  349,  245,  210,  246,
  247,  228,  350,  248,  249,  696,  181,  743,  646,  706,
  732,  731,  733,  735,  924,  384,  385,   56,  260,  360,
  300,  825,  727,  383,  370,  958,  544,  251,  929,  437,
  290,  545,  939,  654,  940,  546,  547,  315,  227,  306,
  964,  408,  409,  973,  712,  734,  427,  428,  992,  257,
  705,  455,  466,   57,  644,  233,  596,  312,  183,  606,
  590,  622,  414,  103,   49,  293
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
  109,  109,  109,  109,  110,  110,  111,  111,  113,  113,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   36,   36,   36,   37,   37,
   37,   37,   37,   37,   37,   39,   39,   40,   40,   41,
   41,   42,   42,   43,   43,   44,   44,   45,   45,   46,
   46,   47,   47,   47,   48,   48,   48,   48,   48,   48,
   49,   49,   49,   50,   50,   50,   51,   51,   51,   51,
   52,   52,   53,   53,   53,   53,   53,   53,   53,   54,
   54,   54,   54,   54,   54,   54,   54,   55,   55,   56,
   56,   56,   56,   56,   56,   56,   94,   94,   95,   95,
   95,   95,   95,   95,   58,   58,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   72,   72,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   61,   61,   60,   60,  114,
   62,  112,  112,   65,   65,   67,   67,   66,   66,   66,
   66,   66,   68,   68,   69,   69,   69,   69,   70,   70,
   71,   71,   71,   71,   71,   71,   71,   71,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   63,   63,   63,  115,   64,
   76,   76,   77,   77,   78,   78,   78,   78,   78,   78,
   79,   79,   81,   81,   82,   82,   82,   80,   99,   99,
   83,   83,   83,   83,   83,   83,   83,   84,   84,   84,
   74,   74,   85,   85,   86,   86,   87,   87,   88,   88,
   88,   88,   89,   89,   91,   91,   92,   92,   93,   93,
   93,   93,   93,  100,  100,  100,  101,  101,  101,  102,
  102,   90,   90,   96,   96,   97,   97,   97,   97,   98,
   98,   98,  103
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
    4,    0,    1,    1,    2,    1,    2,    1,    2,    2,
    3,    4,    1,    3,    1,    2,    3,    4,    1,    3,
    5,    5,    3,    3,    3,    3,    2,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    2,    3,    3,    2,    0,    3,
    3,    3,    1,    3,    1,    4,    3,    6,    3,    3,
    1,    3,    1,    1,    6,    6,    7,    1,    0,    2,
    5,    5,    5,    6,    6,    6,    2,    6,    6,    6,
    1,    1,    5,    5,    3,    3,    0,    4,    1,    4,
    3,    3,    0,    3,    0,    1,    1,    3,    1,    4,
    1,    1,    2,    2,    1,    2,    0,    2,    3,    0,
    3,    0,    3,    0,    1,    1,    2,    3,    4,    1,
    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 891
#define YYNLSTATES 487
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
#line 447 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 135:
#line 448 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 136:
#line 452 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 141:
#line 463 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 142:
#line 464 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 143:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 144:
#line 466 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 145:
#line 467 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 146:
#line 468 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 147:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 148:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 149:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 150:
#line 472 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 151:
#line 473 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 152:
#line 474 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 153:
#line 475 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 154:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 158:
#line 486 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 159:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 160:
#line 488 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 161:
#line 489 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 162:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 163:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 164:
#line 492 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 166:
#line 497 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 170:
#line 507 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 172:
#line 512 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 174:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 176:
#line 522 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 178:
#line 527 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 180:
#line 532 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 182:
#line 537 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 183:
#line 538 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 185:
#line 543 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 186:
#line 544 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 187:
#line 545 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 188:
#line 546 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 189:
#line 547 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 191:
#line 552 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 553 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 194:
#line 558 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 559 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 197:
#line 564 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 565 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 199:
#line 566 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 571 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 203:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 205:
#line 578 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 206:
#line 579 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 207:
#line 580 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 208:
#line 581 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 210:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 211:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 212:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 213:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 214:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 215:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 216:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 218:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 220:
#line 602 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 221:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 222:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 223:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 224:
#line 606 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 225:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 226:
#line 611 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 228:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 229:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 230:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 231:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 232:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 233:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 234:
#line 625 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 235:
#line 626 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 236:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 237:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 238:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 239:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 240:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 241:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 242:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 243:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 249:
#line 643 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 250:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 251:
#line 645 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 252:
#line 646 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 253:
#line 647 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 254:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 255:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 256:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 257:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 258:
#line 655 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 259:
#line 656 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 260:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 261:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 262:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 263:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 264:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 265:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 266:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 267:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 268:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 269:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 270:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 271:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 272:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 273:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 274:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 275:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 276:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 277:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 278:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 279:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 280:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 281:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 282:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 283:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 284:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 285:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 286:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 287:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 288:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 289:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 290:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 291:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 292:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 293:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 294:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 295:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 296:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 297:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 298:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 299:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 300:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 301:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 302:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 303:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 304:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 305:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 306:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 307:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 308:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 309:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 310:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 311:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 312:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 313:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 314:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 315:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 316:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 317:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 318:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 319:
#line 728 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 320:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 321:
#line 736 "src/kinx.y"
{} break;
        case 323:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 324:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 325:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 326:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 328:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 329:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 330:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 331:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 333:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 335:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 336:
#line 766 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 337:
#line 767 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 339:
#line 772 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 340:
#line 776 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 341:
#line 777 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 342:
#line 778 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
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
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 347:
#line 783 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-1).strval, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T)); } break;
        case 348:
#line 787 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 349:
#line 788 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 350:
#line 789 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 351:
#line 790 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 352:
#line 791 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 353:
#line 792 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 354:
#line 793 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 355:
#line 794 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 356:
#line 795 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 357:
#line 796 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 358:
#line 797 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 359:
#line 798 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 360:
#line 799 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 361:
#line 800 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 362:
#line 801 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 363:
#line 802 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 364:
#line 803 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 365:
#line 804 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 366:
#line 805 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 367:
#line 806 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 368:
#line 807 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 369:
#line 808 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 370:
#line 809 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 371:
#line 810 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 372:
#line 811 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 373:
#line 812 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 374:
#line 813 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 375:
#line 814 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 376:
#line 815 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 377:
#line 816 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 378:
#line 817 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 379:
#line 818 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 380:
#line 819 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 381:
#line 820 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 382:
#line 824 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 383:
#line 825 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 384:
#line 826 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 385:
#line 827 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 386:
#line 828 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 387:
#line 829 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 388:
#line 830 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 389:
#line 831 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 390:
#line 832 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 391:
#line 833 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 392:
#line 834 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 393:
#line 835 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 394:
#line 836 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 395:
#line 837 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 396:
#line 838 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 397:
#line 839 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 398:
#line 840 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 399:
#line 841 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 400:
#line 842 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 401:
#line 843 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 402:
#line 844 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 403:
#line 845 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 404:
#line 846 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 405:
#line 847 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 406:
#line 848 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 407:
#line 849 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 408:
#line 850 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 409:
#line 851 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 410:
#line 852 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 411:
#line 853 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 412:
#line 854 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 413:
#line 855 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 414:
#line 856 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 415:
#line 857 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 416:
#line 858 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 417:
#line 859 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 418:
#line 860 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 419:
#line 861 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 420:
#line 862 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 421:
#line 863 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 422:
#line 864 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 423:
#line 865 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 424:
#line 866 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 425:
#line 867 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 426:
#line 868 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 427:
#line 869 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 428:
#line 870 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 429:
#line 871 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 430:
#line 872 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 431:
#line 873 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 432:
#line 874 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 433:
#line 875 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 434:
#line 876 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 435:
#line 880 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 436:
#line 881 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 437:
#line 882 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 438:
#line 886 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 439:
#line 890 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 440:
#line 894 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 441:
#line 895 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 443:
#line 900 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 444:
#line 904 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 445:
#line 905 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 446:
#line 906 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 447:
#line 907 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 448:
#line 908 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 449:
#line 909 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 451:
#line 914 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 452:
#line 918 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 453:
#line 919 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 454:
#line 923 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 455:
#line 924 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 456:
#line 925 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 457:
#line 929 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 458:
#line 933 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 459:
#line 934 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 460:
#line 938 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 461:
#line 939 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 462:
#line 940 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 463:
#line 941 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 464:
#line 942 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 465:
#line 943 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 466:
#line 944 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 467:
#line 948 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 468:
#line 949 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 469:
#line 950 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 472:
#line 959 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 473:
#line 960 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 474:
#line 964 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 475:
#line 965 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 476:
#line 969 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 477:
#line 971 "src/kinx.y"
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
        case 479:
#line 987 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 480:
#line 988 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 481:
#line 989 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 482:
#line 993 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 483:
#line 994 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 484:
#line 998 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 487:
#line 1004 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 488:
#line 1008 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 489:
#line 1009 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 490:
#line 1010 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 491:
#line 1011 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 492:
#line 1012 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 493:
#line 1016 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 494:
#line 1017 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 495:
#line 1018 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 496:
#line 1022 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 497:
#line 1023 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 498:
#line 1024 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 499:
#line 1028 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 500:
#line 1029 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 501:
#line 1033 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 502:
#line 1034 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 503:
#line 1038 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 506:
#line 1044 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 507:
#line 1045 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 508:
#line 1046 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 511:
#line 1052 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 512:
#line 1056 "src/kinx.y"
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
