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
#line 1062 "src/kinx.y"

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
  "'^'",
  "'?'",
  "'|'",
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
  "Modifier_Opt : IF '(' AssignExpressionList ')'",
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
  "WhenClause : WHEN WhenConditionRange Modifier_Opt Colon_Opt WhenClauseBody",
  "WhenConditionRange : WhenPostfixExpression",
  "WhenConditionRange : '^' WhenPostfixExpression",
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
  "WhenClauseBody : BlockStatement",
  "WhenClauseBody : TernaryExpression",
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
  "Factor : Array",
  "Factor : Binary",
  "Factor : Object",
  "Factor : SimpleFuncCallFactor",
  "Factor : Regex",
  "Factor : '.' PropertyName",
  "Factor : IMPORT '(' '(' STR ')' ')'",
  "Factor : '(' AssignExpression ')'",
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
  111,  111,  111,  109,  111,  111,  111,  107,  101,  111,
   95,   96,  105,  104,   93,   92,   97,  106,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,   94,   91,
  102,   90,  103,   99,  110,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,   98,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,  111,  100,  111,  108,  111,  111,  111,
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
  745,  746,  747,  748,  749,  750,  751,  752,  753,  754,
  755,  756,  757,  759,  758,  110,  760,  761,  762,  771,
  773,  772,  216,  782,  783,  784,  786,  788,  183,  184,
    0,  353,  780,  781,  241,   80,   81,   82,   83,   84,
   85,   86,   87,   88,   89,   90,   91,   92,    4,  138,
  107,  774,  775,  776,  113,  777,  778,   43,   47,   42,
   26,  139,   49,-32766,   28,  769,   43,  770,   42,  763,
  764,  765,  766,  767,  768,  353,  744,   38,-32766,  182,
  514,  779,  516,  515,  517,  389,  518,   94,   40,   19,
  790,  519,  520,  390,   65,  521,  796,  392,  795,  794,
  785,  787,  789,  791,  792,  793,  867,  868,  869,  870,
  871,  872,  873,  874,  875,  876,  877,  878,  879,   59,
  880, -342,  881,  882,  883,  891,  893,  892, -342,  903,
  904,  905,  907,  909,   40,-32766,-32766,-32766,  901,  902,
  -74,-32766,  332,   16,  333,  522,  114,   99,  979,   40,
  523,  334,  525,  524,   50,  309,   29,  894,  895,  896,
  310,  897,  898,  513,  504,-32766,  332,   16,  333,  512,
  181,  889,   98,  890,  123,  334,  884,  885,  886,  887,
  888,  291,  955,  131,  132,  133,  264,  899,  900,  719,
  720,  369,  463,  113, -102,   40,  911,  737,   40,  370,
   97,   49,  917,   28,  916,  915,  906,  908,  910,  912,
  913,  914,  162,  374,  834,  375,   10,  376,  838,  300,
  840,  841,  223,  224,  377,  105,  335,  846,  336,  157,
  220,  221,  301,   53,   60,  282,  120,  -75,   95,  414,
  101,  140,  141,  142,  109,   38,-32766,   38,  554,   68,
  119,  742,   48,  227,   27,  996,  743,  996,  134,  135,
  112,   38,  225,   38,  378,  379,  380,  240,  255,  864,
  119,  311,  539,   78,-32766,  284,  285,  337,  381,  339,
  382,  341,  464,  256,  257,   34,   35,   36,-32766,  383,
  542,    4,  400,  107,  384,  866,  290,  530,   40,   37,
  477,   47,  -98,   26,  388,   79,   58, -371, -372, -102,
   38,  158,  239,  833,  834,  835,  836,  837,  838,  839,
  840,  841,  842,  843,  844,  845,   79,  846,   40,  847,
  848,  849,  857,  859,  858,  181,  809,  314,   38,  362,
   43,  106,   42,  581,  124,  404,  639,  640,  641,   40,
  181,  112,  799,  129,  130,  136,  137,  809,  147,  148,
  149,  150,  106,  125,  860,  861,  862,  143,  863,  864,
  119,  742,  117,   78,  638,  636,  743,  802,  855,  368,
  856,  298,  637,  850,  851,  852,  853,  854,   62,  398,
  297,  540,  543,  296,  384,  866,  460,  162,  331,  569,
  332,   16,  333,  402,  281,  299,  399,  236,  237,  334,
  102,  335,  400,  336,  405,  217,  218,  483,   63,  103,
  282,   79,  367,  290,  291,  465,  583,  162,  331,  536,
  332,   16,  333,  582,  281,  430,  612,  236,  237,  334,
  102,  335,  443,  336,   40,  217,  218,  483,   63,  103,
  282,  435,  810,  242,  467,  119,  407,  106,  741,  804,
  284,  285,  337,  338,  339,  340,  341,  632,  243,  244,
   31,   32,   33,  708,  343,  966,  713,   39,   38,  264,
  293,  111,  530,  242,   40,  118,   37,  -98,    7,    5,
  284,  285,  337,  338,  339,  340,  341,  239,  243,  244,
   31,   32,   33,    6,  343,  608,  822,  714,  537,  820,
   52,  454,  715,  983,  469,  126,  982,  -98,  162,  331,
    8,  332,   16,  333,  797,  281,  918,  706,  236,  237,
  334,  102,  335,  610,  336,  630,  217,  218,  483,   63,
  103,  282,  964,  800,   70,  222,  280,  276,  100,  162,
  331,   73,  332,   16,  333,   67,  281,   66,  442,  236,
  237,  334,  102,  335,   71,  336,  552,  217,  218,  483,
   63,  103,  282,  503,  242,  573,  122,  580,  572,  570,
  575,  284,  285,  337,  338,  339,  340,  341,  926,  243,
  244,   31,   32,   33,  925,  343,  571,   72,  584,  574,
   74,   69,  127,  715,  436,  242,  209,  108,  -98,   61,
  198,    8,  284,  285,  337,  338,  339,  340,  341,   44,
  243,  244,   31,   32,   33, -378,  343,  649,  555,  486,
  228,  226,   -1,  162,  331,  219,  332,   16,  333,  -98,
  281,  121, -349,  236,  237,  334,  102,  335,   56,  336,
   55,  217,  218,  483,   63,  103,  282,   54,   41, -370,
 -373,  162,  331, -374,  332,   16,  333, -375,  281,  406,
  364,  236,  237,  334,  102,  335,  363,  336,  229,  217,
  218,  483,   63,  103,  282,  208,  207,  206,  204,  242,
  203,  202,  201,  200,  199,  197,  284,  285,  337,  338,
  339,  340,  341,  196,  243,  244,   31,   32,   33,  195,
  343,   96,   93,   77,   76,   75,   51,  242,  205,  434,
    0,  635,  736,  -98,  284,  285,  337,  338,  339,  340,
  341,  590,  243,  244,   31,   32,   33,  471,  343,  312,
   21,   20,   18,   17,  987,  985,  531,  633,  735,  162,
  331,  -98,  332,   16,  333,  642,  281,  613,  968,  236,
  237,  334,  102,  335,  709,  336,  924,  217,  218,  483,
   63,  103,  282,  798,  738,  919,  468,  162,  331,  461,
  332,   16,  333,  453,  281,  450,  330,  236,  237,  334,
  102,  335,  329,  336,  328,  217,  218,  483,   63,  103,
  282,  327,  326,  325,  324,  242,  322,  320,  319,  318,
   24,   23,  284,  285,  337,  338,  339,  340,  341,   22,
  243,  244,   31,   32,   33,    3,  343,    2,  128,  801,
    0,    0,    0,  242,  530,    0,    0,    0,    0,  -98,
  284,  285,  337,  338,  339,  340,  341,    0,  243,  244,
   31,   32,   33,    0,  343,    0,    0,    0,    0,    0,
    0,    0,  718,    0,    0,  162,  331,  -98,  332,   16,
  333,    0,  281,    0,    0,  236,  237,  334,  102,  335,
    0,  336,    0,  217,  218,  483,   63,  103,  282,    0,
    0,    0,    0,  162,  331,    0,  332,   16,  333,    0,
  281,    0,    0,  236,  237,  334,  102,  335,    0,  336,
    0,  217,  218,  483,   63,  103,  282,    0,    0,    0,
    0,  242,    0,    0,    0,    0,    0,    0,  284,  285,
  337,  338,  339,  340,  341,    0,  243,  244,   31,   32,
   33,    0,  343,    0,    0,    0,    0,    0,    0,  242,
  717,    0,    0,    0,    0,  -98,  284,  285,  337,  338,
  339,  340,  341,    0,  243,  244,   31,   32,   33,    0,
  343,    0,    0,    0,    0,    0,    0,    0,  716,    0,
    0,  162,  331,  -98,  332,   16,  333,    0,  281,    0,
    0,  236,  237,  334,  102,  335,    0,  336,    0,  217,
  218,  483,   63,  103,  282,    0,    0,    0,    0,  162,
  331,    0,  332,   16,  333,    0,  281,    0,    0,  236,
  237,  334,  102,  335,    0,  336,    0,  217,  218,  483,
   63,  103,  282,    0,    0,    0,    0,  242,    0,    0,
    0,    0,    0,    0,  284,  285,  337,  338,  339,  340,
  341,    0,  243,  244,   31,   32,   33,    0,  343,    0,
    0,    0,    0,    0,    0,  242,  535,    0,    0,    0,
    0,  -98,  284,  285,  337,  338,  339,  340,  341,    0,
  243,  244,   31,   32,   33,    0,  343,    0,    0,    0,
    0,    0,    0,    0,  534,    0,    0,  162,  331,  -98,
  332,   16,  333,    0,  281,    0,    0,  236,  237,  334,
  102,  335,    0,  336,    0,  217,  218,  483,   63,  103,
  282,    0,    0,    0,    0,  162,  331,    0,  332,   16,
  333,    0,  281,    0,    0,  236,  237,  334,  102,  335,
    0,  336,    0,  217,  218,  483,   63,  103,  282,    0,
    0,    0,    0,  242,    0,    0,    0,    0,    0,    0,
  284,  285,  337,  338,  339,  340,  341,    0,  243,  244,
   31,   32,   33,    0,  343,    0,    0,    0,    0,    0,
    0,  242,  533,    0,    0,    0,    0,  -98,  284,  285,
  337,  338,  339,  340,  341,    0,  243,  244,   31,   32,
   33,  104,  343,    0,    0,  156,    0,    0,    0,    0,
  532,    0,    0,    0,    0,  -98,    0,    0,    0,  151,
  152,    0,    0,    0,    0,    0,    0,    0,  484,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  724,  726,  727,    0,  356,    0,    0,    0,    0,    0,
  283,    0,    0,    0,    0,    0,    0,    0,  942,  357,
  358,    0,    0,    0,  342,  742,    0,  728,  723,  721,
  743,    0,    1,    0,   42,    0,  722,    0,    0,  153,
    0,    0,   57,    0,   30,    0,    0,    0,  238,  286,
    0,  154,  144,  485,    0,  145,  146,   25,  162,  331,
    0,  332,   16,  333,    0,  281,    0,    0,  236,  237,
  334,  102,  335,    0,  336,    0,  217,  218,  483,   63,
  103,  282,-32766,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
-32766,-32766,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  242,    0,    0,    0,    0,    0,
    0,  284,  285,  337,  338,  339,  340,  341,    0,  243,
  244,   31,   32,   33,    0,  343,    0,    0,    0,-32766,
-32766,-32766,    0,    0,    0,-32766,    0,    0,  -98,    0,
    0,    0,    0,   40,    0,    0,    0,    0,    0,    0,
-32766,    0,    0,    0,    0,    0,    0,    0,    0,-32766,
    0,    0,-32766,-32766,    0,    0,-32766,-32766
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1418

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   23,   18,   19,   20,   21,
   22,   23,   19,   25,   26,   27,   28,   29,   61,   62,
    0,    2,   34,   35,   62,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   85,   92,
   87,   53,   54,   55,   87,   57,   58,   85,   95,   87,
   97,  104,   95,   14,   97,   67,   85,   69,   87,   71,
   72,   73,   74,   75,   76,    2,   78,   85,   14,   98,
    2,   83,    4,    5,    6,   87,    8,   90,   85,    3,
   92,   13,   14,   95,   91,   17,   98,    4,  100,  101,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   90,
   16,   86,   18,   19,   20,   21,   22,   23,   93,   25,
   26,   27,   28,   29,   85,   71,   72,   73,   34,   35,
    7,   77,    4,    5,    6,   67,   87,    7,   71,   85,
   72,   13,   74,   75,   95,   78,   97,   53,   54,   55,
   83,   57,   58,   85,   86,  101,    4,    5,    6,   91,
   16,   67,   62,   69,   37,   13,   72,   73,   74,   75,
   76,   78,   78,   27,   28,   29,   85,   83,   84,   32,
   33,   87,   79,   87,   91,   85,   92,   96,   85,   95,
    7,   95,   98,   97,  100,  101,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   99,    7,   62,   79,
   62,  105,  106,  107,   87,   85,   59,   85,   94,   90,
   59,   78,   95,   94,   97,   79,   83,   79,  102,  103,
   98,   85,   56,   85,   53,   54,   55,    9,   57,   58,
   59,   10,   82,   62,   14,   64,   65,   66,   67,   68,
   69,   70,   92,   72,   73,   74,   75,   76,  101,   78,
   82,   85,  101,   87,   83,   84,   78,   86,   85,   85,
   92,   95,   91,   97,   79,   62,   95,   94,   94,   91,
   85,   18,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   62,   16,   85,   18,
   19,   20,   21,   22,   23,   16,   93,    3,   85,   19,
   85,   98,   87,   91,   30,   93,   53,   54,   55,   85,
   16,   98,   88,   25,   26,   34,   35,   93,   51,   52,
   61,   62,   98,   31,   53,   54,   55,   36,   57,   58,
   59,   78,   59,   62,   81,   82,   83,   60,   67,   78,
   69,   78,   89,   72,   73,   74,   75,   76,   95,   78,
   78,   82,   82,   78,   83,   84,   78,    1,    2,   91,
    4,    5,    6,   78,    8,   78,   95,   11,   12,   13,
   14,   15,  101,   17,   78,   19,   20,   21,   22,   23,
   24,   62,   78,   78,   78,   78,   78,    1,    2,   78,
    4,    5,    6,   78,    8,   78,   84,   11,   12,   13,
   14,   15,   79,   17,   85,   19,   20,   21,   22,   23,
   24,   79,   93,   57,   79,   59,   79,   98,   84,   86,
   64,   65,   66,   67,   68,   69,   70,   84,   72,   73,
   74,   75,   76,   84,   78,   84,   86,   85,   85,   85,
   85,   93,   86,   57,   85,   59,   85,   91,   85,   85,
   64,   65,   66,   67,   68,   69,   70,  101,   72,   73,
   74,   75,   76,   85,   78,   86,   86,   86,   86,   86,
   93,   87,   86,   88,   87,  100,   88,   91,    1,    2,
   94,    4,    5,    6,   88,    8,   88,   88,   11,   12,
   13,   14,   15,   88,   17,   88,   19,   20,   21,   22,
   23,   24,   88,   88,   91,   93,   90,   90,   90,    1,
    2,   90,    4,    5,    6,   90,    8,   90,   90,   11,
   12,   13,   14,   15,   91,   17,   91,   19,   20,   21,
   22,   23,   24,   91,   57,   91,   59,   91,   91,   91,
   91,   64,   65,   66,   67,   68,   69,   70,   91,   72,
   73,   74,   75,   76,   91,   78,   91,   91,   91,   91,
   91,   91,   98,   86,   93,   57,   93,   93,   91,   93,
   95,   94,   64,   65,   66,   67,   68,   69,   70,   93,
   72,   73,   74,   75,   76,   94,   78,   94,   94,   94,
   94,   94,    0,    1,    2,   94,    4,    5,    6,   91,
    8,   94,   94,   11,   12,   13,   14,   15,   94,   17,
   94,   19,   20,   21,   22,   23,   24,   94,   94,   94,
   94,    1,    2,   94,    4,    5,    6,   94,    8,   95,
   95,   11,   12,   13,   14,   15,   95,   17,   95,   19,
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
   72,   73,   74,   75,   76,   96,   78,   96,  101,  103,
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
   76,   14,   78,   -1,   -1,   18,   -1,   -1,   -1,   -1,
   86,   -1,   -1,   -1,   -1,   91,   -1,   -1,   -1,   32,
   33,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   41,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   53,   54,   55,   -1,   57,   -1,   -1,   -1,   -1,   -1,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   71,   72,
   73,   -1,   -1,   -1,   77,   78,   -1,   80,   81,   82,
   83,   -1,   85,   -1,   87,   -1,   89,   -1,   -1,   92,
   -1,   -1,   95,   -1,   97,   -1,   -1,   -1,  101,  102,
   -1,  104,  105,  106,   -1,  108,  109,  110,    1,    2,
   -1,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   -1,   17,   -1,   19,   20,   21,   22,
   23,   24,   14,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   32,   33,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,
   -1,   64,   65,   66,   67,   68,   69,   70,   -1,   72,
   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,   71,
   72,   73,   -1,   -1,   -1,   77,   -1,   -1,   91,   -1,
   -1,   -1,   -1,   85,   -1,   -1,   -1,   -1,   -1,   -1,
   92,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  101,
   -1,   -1,  104,  105,   -1,   -1,  108,  109
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1297,  211,  426,  517,  396,  748, 1124, 1096,  892,  632,
  548,  660, 1008,  980,  864,  776, 1297, 1297, 1297, 1297,
 1297, 1297, 1297, 1297, 1297,  374,  389,  352,  383,  391,
   -2,  104,  104,  104,  104,  104,  104,  423,  419,  420,
  311,  162,  264,  187,  187,  243,  359,  176,  176,  176,
  176,    3,  178,  214,  253,  253,  253,  225,  160,   -8,
  213,  110,  113,  401,  401,  401,  393,  393,  393,  401,
  401,  401,  401,  393,  401,  399,  399,  399,  393,  393,
  393,  393,  393,  393,  393,  393,  393,  393,  393,  393,
  393,  393,  393,  399,  393,  393,  399,  399,  393,  399,
  393,  393,  399,  399,  399,  399,  399,  399,  392,  399,
  399,  399,  399,  399,  399,  260,  260,  260,  260,   49,
   49,   49,   49,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64, 1308, 1308, 1308, 1308, 1308, 1308, 1308, 1308,  154,
  319,   29,   78,  626,  439,  445,  625,  447,  454,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,  -19,  293,  293,  293,  206,  101,  -33,  -37,  -37,
  -37,  -37,  394,  394,  394,  -28,  -28,  -28,  -28,  -28,
  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,
  106,  106,  106,  156,  156,  156,  255,  255,  255,  138,
  255,  255,  255,  218,  103,   77,   77,   77,   77,   77,
   59,  136,  136,  136,  133,  334,  345,  346,  515,  623,
  624,  173,  320,  344,  301,  137,  328,  321,  -43,  307,
  299,  159,  503,  497,  252,  320,  344,  301,   35,  357,
  647,  646,  510,  643,  191,  328,  321,  321,  321,  321,
  321,  -43,  -43,  307,  453,  635,  190,  641,  645,  644,
  208,  404,  355,  575,  351,  351,  726,   73,  537,  258,
   73,   73,  537,  325,   73,  575,  599,  599,  404,  404,
  404,  565,  526,  575,  261,  511,   73,  535,  535,  424,
  424,  404,  404,   73,  533,  583,  404,  404,  404,  404,
  404,  533,  404,  583,  404,  404,  404,  404,  404,  404,
  404,  620,  619,  621,  618,  534,  395,  508,  315,  312,
  303,  327,  600,  541,   30,  507,  314,  332,  415,  504,
  727,  331,   93,  617,  308,  505,  581,  614,  608,  467,
  465,  514,  336,  574,  377,  418,  403,  598,  597,  438,
  679,  596,  595,  593,  620,  619,  621,  618,  566,  569,
  573,  315,  303,  564,  531,  563,  455,  516,  678,  436,
  677,  489,  616,  193,  230,  133,  488,  487,  556,  372,
  591,  592,  457,  486,  348,  468,  363,  670,  536,  713,
  513,  712,  711,  390,  689,  373,  516,  687,  317,  314,
  547,  332,  415,  504,  727,  331,  331,  331,  668,  417,
  590,  140,  467,  473,  318,  683,  347,  422,  458,  458,
  458,  484,  375,  680,  662,  710,  708,  707,  706,  705,
  554,  731,  661,  313,  428,  427,  427,  698,   86,  506,
  696,  554,  729,  659,  309,  456,  461,  482,  652,  425,
  690,  475,  509,  723,  651,  649,  715,  310,  458,  421,
  714,  421,  648,    0,    0,    0,    0, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187,   -2,   -2,   -2,   -2,   -2,    0,    0,    0,
    0,    0,    0,    0,  311,  311,  311,    0, 1187, 1187,
  311,  311, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187,   -3,   -3,   -3,    0,
   -3,   -3,   -3,   -3,   -3,   -3,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  293,    0,
    0,    0,  157,  157,  157,  157,  157,  157,  157,  157,
  157,  157,  173,  173,  173,  173,  173,  173,  173,  173,
  173,  173,  173,  173,  173,  173,  173,  157,  157,  157,
    0,    0,    0,  173,  173,  173,    0,  173,  173,  173,
   73,   73,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  159,    0,   73,   73,  404,  404,  404,    0,  581,
  614,  608,    0,    0,    0,    0,    0,    0,    0,  452,
  452,    0,  581,  614,  608,    0,  592,  388,  388,  388,
  388,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  452,  388,    0,  388,  388,  388
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 280

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  365,  366,  367,32767,32767,32767,
32767,32767,32767,32767,  319,32767,32767,  501,  501,  501,
  501,32767,32767,  100,32767,32767,32767,32767,32767,32767,
   90,  327,32767,  100,  100,  100,32767,32767,32767,  100,
  100,  100,  100,32767,  100,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   90,32767,  358,32767,32767,32767,32767,
   92,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  203,
  205,32767,32767,32767,32767,32767,32767,  360,32767,32767,
32767,  102,32767,32767,32767,32767,32767,32767,32767,  332,
   89,  324,  330,  325,  507,  334,  343,  328,   91,  331,
  344,32767,32767,  137,  139,  215,32767,  133,  213,  214,
  211,  210,  120,  508,  345,  482,  482,  482,  482,  482,
  482,  482,  482,  482,  482,  482,  482,  482,  482,32767,
  134,  138,  140,  179,  180,  181,32767,32767,32767,32767,
  361,  362,32767,  355,  356,32767,32767,32767,32767,32767,
  499,  191,  193,  192,  442,  157,  102,  102,32767,32767,
32767,32767,32767,32767,32767,  166,  177,  182,  188,  198,
  200,  442,32767,32767,32767,  376,  363,  364,  238,32767,
32767,32767,32767,32767,32767,  178,  184,  186,  187,  183,
  185,  189,  190,  199,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  316,  102,  456,   77,
  102,  102,  456,32767,  102,32767,  480,  480,32767,32767,
  352,  510,  318,32767,   80,  318,  102,  474,  474,  494,
  494,32767,32767,  102,  161,  497,32767,32767,32767,32767,
32767,  161,32767,  497,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  255,32767,32767,  167,  169,  171,  173,
  175,  194,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  101,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  346,  348,  350,  357,  237,  239,
  240,  368,  369,  255,  256,32767,32767,  320,32767,32767,
32767,32767,32767,32767,  242,  238,32767,32767,  255,32767,
32767,32767,   51,32767,32767,32767,32767,32767,  486,32767,
  483,32767,32767,32767,32767,32767,  321,32767,32767,  168,
32767,  170,  172,  174,  176,  195,  196,  197,32767,  502,
32767,32767,   75,32767,32767,32767,  319,32767,  446,  447,
  444,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  251,32767,32767,32767,32767,  493,  491,32767,   62,32767,
32767,32767,32767,32767,32767,   54,  443,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  445,  462,
32767,32767,32767,  510,  436,  436,  510
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  176,  171,  824,  258,  171,  171,  174,  174,  174,  174,
  172,  174,  169,  176,  176,  176,  163,  163,  418,  170,
  177,  166,  169,  169,  169,  452,  474,  482,  169,  169,
  169,  169,  416,  169,  172,  172,  172,  439,  440,  829,
  829,  829,  829,  478,  992,  829,  829,  619,  646,  646,
  950,  950,  172,  395,  421,  172,  172,  827,  172,  825,
  419,  159,  170,  160,  159,  173,  164,  175,  165,  178,
  179,  180,  167,  168,  606,  707,  611,  631,  965,  734,
  423,  606,  606,  606,  921,   14,   14,  422,  606,   12,
   13,   15,  920,  606,  606,  606,  606,  606,  606,  606,
  606,  606,  606,  606,  606,  606,  606,  606,  548,  606,
  606,  424,  274,  606,  253,  606,  606,  253,  711,  214,
  215,  711,  711,  711,  711,  288,  288,  288,  288,  288,
  288,  288,  288,  288,  288,  288,  288,  288,  288,  288,
  288,  288,  288,  288,  288,  288,  288,  288,  288,  288,
  394,  411,  412,  417,  444,  445,  446,  447,  448,  449,
  451,  457,  462,  470,  188,  189,  190,  191,  609,  629,
  265,  951,  951,  565,  609,  609,  609,  266,  267,  268,
  269,  270,  273,  634,  634,  634,  634,  372,  373,  972,
  372,  373,  629,  629,  629,  271,  272,  408,  408,  408,
  408,  408,  408,  408,  408,  408,  408,  408,  408,  408,
  408,  408,  232,  233,  289,  425,  426,  427,  234,  251,
  251,  431,  251,  251,  251,  963,  739,  739,  643,  928,
  618,  959,  960,  289,  647,  647,  949,  479,  413,  420,
  651,  481,  366,  977,  568,  553,  592,  308,  401,  957,
  958,  945,  946,  947,  437,  939,  317,  940,  952,  953,
  954,  948,  566,  941,  116,  828,  813,  595,  596,  597,
  598,  599,  600,  601,  602,  603,  604,  605,  593,  594,
  622,  592,  991,  974,  456,  816,  548,  936,  993,  944,
  315,  323,  475,  303,  975,  975,  975,  975,  975,  975,
  975,  975,  975,  975,  975,  975,  975,  975,  975,  623,
  155,  210,  211,  212,  586,  432,  359,  359,    0,  359,
  359,  359,    0,  976,  976,  976,  976,  976,  976,  976,
  976,  976,  976,  976,  976,  976,  976,  976,    0,    0,
    0,    0,  489,    0,  360,  360,  360,    0,  360,  360,
  360,  490,  352,  492,  492,  492,  492,  492,  352,  458,
  551,  550,  559,  560,  558,  557,  556,  194,    0,    0,
    0,    0,    0,  193,  193,  193,  193,  355,  193,    0,
  194,  194,  194,  186,  186,  260,  261,  263,  712,  614,
  355,  712,  712,  712,  712,  614,  614,  614,    0,    0,
    0,    0,    0,  275,    0,    0,  277,  278,    0,  279,
  306,  433,    0,    0,    0,  459,  472,  473,  476,    0,
  480,  699,  695,  696,  688,  689,  691,  693,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  391,    0,    0,  396,  397,    0,    0,  403,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  441,
    0,    0,    0,    0,    0,    0,  321
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 467

static char yygcheck[] = {
   35,   35,   71,   73,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   65,   35,
   35,   35,   35,   35,   35,   97,   97,   97,   35,   35,
   35,   35,   66,   35,   35,   35,   35,   80,   80,   73,
   73,   73,   73,   80,   99,   73,   73,  112,    7,    7,
    7,    7,   35,   73,   43,   35,   35,   72,   35,   72,
   42,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,  105,   57,   57,   57,   57,   57,
   45,  105,  105,  105,   64,    3,    3,   44,  105,    3,
    3,    3,   64,  105,  105,  105,  105,  105,  105,  105,
  105,  105,  105,  105,  105,  105,  105,  105,   33,  105,
  105,   46,   78,  105,   78,  105,  105,   78,    7,   48,
   48,    7,    7,    7,    7,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   61,   92,   92,   92,   92,   92,   92,   92,   92,   92,
   92,   92,   92,   92,   56,   56,   56,   56,   58,   58,
   47,    7,    7,    7,   58,   58,   58,   49,   49,   49,
   49,   49,   53,   73,   73,   73,   73,   75,   75,   94,
   75,   75,   58,   58,   58,   50,   50,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   51,   51,    7,   52,   52,   52,   73,   73,
   73,   19,   73,   73,   73,   59,   59,   59,   59,   79,
  107,    7,    7,    7,   39,   39,   39,   39,   39,   39,
   39,   39,    9,   73,    7,    7,   36,   90,  100,    7,
    7,    7,    7,    7,  113,    7,   88,    7,    7,    7,
    7,    7,    7,    7,  114,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   61,   36,   36,  103,  102,   36,   33,   36,   36,  101,
  101,  101,  101,  116,   61,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   62,
  104,  109,  109,  109,   30,   61,   61,   61,   -1,   61,
   61,   61,   -1,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   -1,   -1,
   -1,   -1,    4,   -1,   62,   62,   62,   -1,   62,   62,
   62,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,   37,   -1,   -1,
   -1,   -1,   -1,   37,   37,   37,   37,   30,   37,   -1,
   37,   37,   37,   37,   37,   68,   68,   68,   96,   96,
   30,   96,   96,   96,   96,   96,   96,   96,   -1,   -1,
   -1,   -1,   -1,   68,   -1,   -1,   68,   68,   -1,   68,
   38,   38,   -1,   -1,   -1,   38,   38,   38,   38,   -1,
   38,   54,   54,   54,   54,   54,   54,   54,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   30,   -1,   -1,   30,   30,   -1,   -1,   30,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   30,
   -1,   -1,   -1,   -1,   -1,   -1,   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,   83,  342,    0,    0,  -67,    0,  -43,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    5,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  153,    0,    0,   67,    0,  -41,  187,  326,  346,  119,
    0,    0,  -63,  -70,  -38,  -46,  -16,   42,  -10,   46,
   59,   74,   75,   39,  277,    0,   13,   49,  -18,   70,
    0,   99,  128,    0, -211,  -27,  -14,    0,  310,    0,
    0,  -42,    3,    2,    0,  155,    0,    0, -104,    7,
  -30,  125,    0,    0,    0,    0,    0,    0,  -52,    0,
  -50,    0,  -45,    0,  -20,    0,  203,  -23,    0,   -8,
  -44,   63,  -26,  -40, -176,   15,    0,   -5,    0,  129,
    0,    0,  -69,  -51,  -57,    0, -192
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  344,    9,   11,  491,  494,  493,  495,  496,  365,
  497,  305,  510,  498,  526,  527,  528,  499,  529,  393,
  500,  304,  563,  505,  506,  287,  507,  508,  254,  509,
  354,  511,  501,  502,  345,  161,  935,  192,  294,  615,
  650,  245,  346,  347,  348,  349,  350,  246,  213,  247,
  248,  231,  351,  249,  250,  694,  185,  740,  705,  704,
  730,  729,  731,  733,  922,  386,  387,   46,  262,  361,
  302,  823,  826,  725,  385,  371,  956,  544,  252,  927,
  438,  292,  545,  937,  652,  938,  546,  547,  316,  230,
  307,  962,  409,  410,  971,  710,  732,  428,  429,  990,
  259,  703,  455,  466,   64,  591,  235,  617,  313,  187,
  628,  616,  645,  415,  115,   45,  295
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
   22,   22,   31,   31,   31,   31,   23,   23,   24,   25,
   25,   25,   25,   26,   27,   28,   28,   29,   34,   34,
   38,   38,   30,   30,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   36,
   36,   37,   37,   37,   37,   37,   37,   37,  105,  105,
  106,  106,  107,  108,  108,  108,  108,  108,  108,  108,
  108,  109,  109,  109,  109,  109,  109,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  111,  111,  112,
  112,  114,  114,   39,   39,   40,   40,   41,   41,   42,
   42,   43,   43,   44,   44,   45,   45,   46,   46,   47,
   47,   47,   48,   48,   48,   48,   48,   48,   49,   49,
   49,   50,   50,   50,   51,   51,   51,   51,   52,   52,
   53,   53,   53,   53,   53,   53,   53,   54,   54,   54,
   54,   54,   54,   54,   54,   55,   55,   56,   56,   56,
   56,   56,   56,   56,   95,   95,   96,   96,   96,   96,
   96,   96,   58,   58,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   73,   73,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   61,   61,   60,   60,  115,   62,  113,  113,
   65,   65,   67,   67,   66,   66,   66,   66,   66,   66,
   68,   68,   69,   69,   69,   69,   70,   70,   71,   71,
   71,   71,   71,   72,   72,   72,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   63,   63,   63,  116,   64,   77,   77,
   78,   78,   79,   79,   79,   79,   79,   79,   80,   80,
   82,   82,   83,   83,   83,   81,  100,  100,   84,   84,
   84,   84,   84,   84,   84,   85,   85,   85,   75,   75,
   86,   86,   87,   87,   88,   88,   89,   89,   89,   89,
   90,   90,   92,   92,   93,   93,   94,   94,   94,   94,
   94,  101,  101,  101,  102,  102,  102,  103,  103,   91,
   91,   97,   97,   98,   98,   98,   98,   99,   99,   99,
  104
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
    0,    1,    0,    4,    1,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    1,
    1,    2,    2,    4,    3,    3,    4,    2,    1,    4,
    1,    2,    5,    1,    2,    1,    1,    2,    3,    2,
    3,    1,    2,    4,    3,    3,    4,    1,    3,    1,
    1,    1,    1,    1,    1,    3,    2,    0,    3,    1,
    1,    0,    1,    1,    5,    1,    1,    1,    3,    1,
    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
    3,    3,    1,    3,    3,    3,    3,    3,    1,    3,
    3,    1,    3,    3,    1,    3,    3,    3,    1,    3,
    1,    3,    3,    2,    3,    2,    3,    1,    2,    2,
    2,    2,    2,    2,    2,    1,    3,    1,    2,    4,
    3,    3,    4,    2,    1,    1,    4,    8,    6,    7,
    7,    8,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    2,    6,    3,
    3,    3,    2,    2,    2,    1,    1,    1,    1,    1,
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
    1,    1,    6,    6,    7,    1,    0,    2,    5,    5,
    5,    6,    6,    6,    2,    6,    6,    6,    1,    1,
    5,    5,    3,    3,    0,    4,    1,    4,    3,    3,
    0,    3,    0,    1,    1,    3,    1,    4,    1,    1,
    2,    2,    1,    2,    0,    2,    3,    0,    3,    0,
    3,    0,    1,    1,    2,    3,    4,    1,    1,    1,
    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 890
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
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 88:
#line 357 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 89:
#line 361 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 90:
#line 362 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 91:
#line 363 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 92:
#line 364 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 93:
#line 368 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 94:
#line 372 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 95:
#line 376 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object(YYASP(1-1).strval, KX_OBJ_T), NULL); } break;
        case 96:
#line 377 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object(YYASP(3-3).strval, KX_OBJ_T), NULL); } break;
        case 97:
#line 381 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 98:
#line 385 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 99:
#line 386 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 100:
#line 390 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 102:
#line 395 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 103:
#line 396 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 105:
#line 401 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 106:
#line 402 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 107:
#line 403 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 108:
#line 404 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 109:
#line 405 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 110:
#line 406 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 111:
#line 407 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 408 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 409 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 410 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 411 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 412 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 413 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 414 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 121:
#line 423 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 122:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 123:
#line 425 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 124:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 125:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 126:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 127:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 129:
#line 434 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 131:
#line 439 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 132:
#line 443 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 134:
#line 448 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 137:
#line 451 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 138:
#line 452 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 139:
#line 453 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 140:
#line 454 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 142:
#line 459 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 143:
#line 460 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 144:
#line 461 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 145:
#line 462 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 146:
#line 463 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 147:
#line 467 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 148:
#line 468 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 149:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 150:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 151:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 152:
#line 472 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 153:
#line 473 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 154:
#line 474 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 155:
#line 475 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 156:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 157:
#line 480 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 158:
#line 481 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 159:
#line 485 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 164:
#line 496 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 168:
#line 506 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 170:
#line 511 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 172:
#line 516 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 174:
#line 521 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 176:
#line 526 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 178:
#line 531 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 180:
#line 536 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 181:
#line 537 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 183:
#line 542 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 184:
#line 543 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 185:
#line 544 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 186:
#line 545 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 187:
#line 546 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 189:
#line 551 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 190:
#line 552 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 557 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 193:
#line 558 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 563 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 564 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 197:
#line 565 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 199:
#line 570 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 575 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 203:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 204:
#line 578 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 205:
#line 579 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 206:
#line 580 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 208:
#line 585 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 209:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 210:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 211:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 212:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 213:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 214:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 216:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 218:
#line 601 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 219:
#line 602 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 220:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 221:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 222:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 223:
#line 606 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 224:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 226:
#line 615 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 227:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 228:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 229:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 230:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 231:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 232:
#line 624 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 233:
#line 625 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 234:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 235:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 236:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 237:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 238:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 239:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 240:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 241:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 247:
#line 642 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 248:
#line 643 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 249:
#line 644 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 250:
#line 645 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 251:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 252:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 253:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 254:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 255:
#line 653 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 256:
#line 654 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 257:
#line 658 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 258:
#line 659 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 259:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 260:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 261:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 262:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 263:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 264:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 265:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 266:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 267:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 268:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 269:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 270:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 271:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 272:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 273:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 274:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 275:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 276:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 277:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 278:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 279:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 280:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 281:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 282:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 283:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 284:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 285:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 286:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 287:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 288:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 289:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 290:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 291:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 292:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 293:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 294:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 295:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 296:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 297:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 298:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 299:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 300:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 301:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 302:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 303:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 304:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 305:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 306:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 307:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 308:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 309:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 310:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 311:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 312:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 313:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 314:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 315:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 316:
#line 726 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 317:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 318:
#line 734 "src/kinx.y"
{} break;
        case 320:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 321:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 322:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 323:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 325:
#line 750 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 326:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 327:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 328:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 329:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 331:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 333:
#line 764 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 334:
#line 765 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 335:
#line 766 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 337:
#line 771 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 338:
#line 775 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 339:
#line 776 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 340:
#line 777 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 341:
#line 778 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 342:
#line 779 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-1).strval, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T)); } break;
        case 344:
#line 784 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 346:
#line 789 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 347:
#line 790 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 348:
#line 791 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 349:
#line 792 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 350:
#line 793 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 351:
#line 794 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 352:
#line 795 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 353:
#line 796 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 354:
#line 797 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 355:
#line 798 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 356:
#line 799 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 357:
#line 800 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 358:
#line 801 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 359:
#line 802 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 360:
#line 803 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 361:
#line 804 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 362:
#line 805 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 363:
#line 806 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 364:
#line 807 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 365:
#line 808 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 366:
#line 809 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 367:
#line 810 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 368:
#line 811 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 369:
#line 812 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 370:
#line 813 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 371:
#line 814 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 372:
#line 815 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 373:
#line 816 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 374:
#line 817 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 375:
#line 818 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 376:
#line 819 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 377:
#line 820 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 378:
#line 821 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 379:
#line 822 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 380:
#line 826 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 381:
#line 827 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 382:
#line 828 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 383:
#line 829 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 384:
#line 830 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 385:
#line 831 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 386:
#line 832 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 387:
#line 833 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 388:
#line 834 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 389:
#line 835 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 390:
#line 836 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 391:
#line 837 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 392:
#line 838 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 393:
#line 839 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 394:
#line 840 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 395:
#line 841 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 396:
#line 842 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 397:
#line 843 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 398:
#line 844 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 399:
#line 845 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 400:
#line 846 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 401:
#line 847 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 402:
#line 848 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 403:
#line 849 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 404:
#line 850 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 405:
#line 851 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 406:
#line 852 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 407:
#line 853 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 408:
#line 854 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 409:
#line 855 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 410:
#line 856 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 411:
#line 857 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 412:
#line 858 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 413:
#line 859 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 414:
#line 860 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 415:
#line 861 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 416:
#line 862 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 417:
#line 863 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 418:
#line 864 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 419:
#line 865 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 420:
#line 866 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 421:
#line 867 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 422:
#line 868 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 423:
#line 869 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 424:
#line 870 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 425:
#line 871 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 426:
#line 872 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 427:
#line 873 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 428:
#line 874 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 429:
#line 875 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 430:
#line 876 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 431:
#line 877 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 432:
#line 878 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 433:
#line 882 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 434:
#line 883 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 435:
#line 884 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 436:
#line 888 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 437:
#line 892 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 438:
#line 896 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 439:
#line 897 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 441:
#line 902 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 442:
#line 906 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 443:
#line 907 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 444:
#line 908 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 445:
#line 909 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 446:
#line 910 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 447:
#line 911 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 449:
#line 916 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 450:
#line 920 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 451:
#line 921 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 452:
#line 925 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 453:
#line 926 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 454:
#line 927 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 455:
#line 931 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 456:
#line 935 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 457:
#line 936 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 458:
#line 940 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 459:
#line 941 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 460:
#line 942 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 461:
#line 943 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 462:
#line 944 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 463:
#line 945 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 464:
#line 946 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 465:
#line 950 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 466:
#line 951 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 467:
#line 952 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 470:
#line 961 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 471:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 472:
#line 966 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 473:
#line 967 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 474:
#line 971 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 475:
#line 973 "src/kinx.y"
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
        case 477:
#line 989 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 478:
#line 990 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 479:
#line 991 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 480:
#line 995 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 481:
#line 996 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 482:
#line 1000 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 485:
#line 1006 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 486:
#line 1010 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 487:
#line 1011 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 488:
#line 1012 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 489:
#line 1013 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 490:
#line 1014 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 491:
#line 1018 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 492:
#line 1019 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 493:
#line 1020 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 494:
#line 1024 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 495:
#line 1025 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 496:
#line 1026 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 497:
#line 1030 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 498:
#line 1031 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 499:
#line 1035 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 500:
#line 1036 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 501:
#line 1040 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 504:
#line 1046 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 505:
#line 1047 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 506:
#line 1048 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 509:
#line 1054 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 510:
#line 1058 "src/kinx.y"
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
