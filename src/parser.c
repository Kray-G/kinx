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
#line 1056 "src/kinx.y"

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
  "KeyValue : VarName",
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
  742,  743,  744,  745,  746,  747,  748,  749,  750,  751,
  752,  753,  754,  756,  755,  109,  757,  758,  759,  768,
  770,  769,  214,  779,  780,  781,  783,  785,  180,  181,
   65,    0,  777,  778,  225,   77,   78,   79,   80,   81,
   82,   83,   84,   85,   86,   87,   88,   89,  330,   16,
  331,  771,  772,  773,  111,  774,  775,  332,  351,  330,
   16,  331,   47,  351,   28,  766,   97,  767,  332,  760,
  761,  762,  763,  764,  765,   19,  741,   38,-32766,  390,
  512,  776,  514,  513,  515,  387,  516,   91,   40,   40,
  787,  517,  518,  388,   62,  519,  239,  792,  793,  791,
  782,  784,  786,  788,  789,  790,  863,  864,  865,  866,
  867,  868,  869,  870,  871,  872,  873,  874,  875,   42,
  876,   44,  877,  878,  879,  887,  889,  888,  -74,  899,
  900,  901,  903,  905,  312,-32766,-32766,-32766,  897,  898,
   38,-32766,  238,-32766,    4,  520,  106,  179,  975,   40,
  521,   56,  523,  522,   45,  307,   26,  890,  891,  892,
  308,  893,  894,  511,  502,-32766,  129,  130,  131,  510,
   76,  885,  101,  886,  179,   93,  880,  881,  882,  883,
  884,-32766,  951,  716,  717,-32766,-32766,  895,  896,  992,
  136,  367,  992,   40,  117,   38,  907,  121,   38,  368,
   98,  806,  137,  912,  913,  911,  902,  904,  906,  908,
  909,  910,  160,  372,  830,  373,   10,  374,  834,  298,
  836,  837,  221,  222,  375,  105,  333,  842,  334,  155,
  218,  219,  299,   53,   57,  280,  398,  111,  108,  262,
   76,  132,  133,  112,  -75,   47,   46,   28,   27,  289,
  734,   48,  552,   29,  138,  139,  140,   40,  118,  223,
 -343,  288, -102,   40,  376,  377,  378, -343,  253,  860,
  117,  807,  540,   75, -102,  282,  283,  335,  379,  337,
  380,  339,  475,  254,  255,   34,   35,   36,    4,  381,
  106,  537,  127,  128,  382,  862,   95,  528,   45,   37,
   26,  462,  -98,  461,  412,   42,   55,   44, -370,   40,
   38,  156,  237,  829,  830,  831,  832,  833,  834,  835,
  836,  837,  838,  839,  840,  841,   76,  842,   40,  843,
  844,  845,  853,  855,  854,  386,  309, -369,  739,  179,
  579,   38,  402,  740,  134,  135,  634,  636,  637,   40,
  145,  146,  796,  147,  148,  360,  123,  806,  122,  115,
  141,  799,  366,  295,  856,  857,  858,  433,  859,  860,
  117,  739,  294,   75,  633,  631,  740,  465,  851,  541,
  852,  428,  632,  846,  847,  848,  849,  850,   59,  396,
  458,  296,  365,  400,  382,  862,  297,  160,  329,  288,
  330,   16,  331,  962,  279,  289,  397,  234,  235,  332,
  102,  333,  398,  334,  441,  215,  216,  481,   60,  103,
  280,  463,  581,  534,  580,  403,  610,  160,  329,  405,
  330,   16,  331,  538,  279,  535,  629,  234,  235,  332,
  102,  333,  705,  334,  738,  215,  216,  481,   60,  103,
  280,   37,  291,  240,    7,  117,  262,    6,   39,   40,
  282,  283,  335,  336,  337,  338,  339,   38,  241,  242,
   31,   32,   33,    5,  341,  711,  801,  710,  816,  606,
  818, -376,  528,  240,  467,  116,  452,  -98,  794,  978,
  282,  283,  335,  336,  337,  338,  339,  237,  241,  242,
   31,   32,   33,  979,  341,  797,  960,  627,  608,  703,
  914,  197,  712,   99,  274,  278,  798,  -98,  160,  329,
    8,  330,   16,  331,  440,  279,   63,   64,  234,  235,
  332,  102,  333,   70,  334,  567,  215,  216,  481,   60,
  103,  280,   67,   68,  550,  501,  571,  578,  570,  160,
  329,  568,  330,   16,  331,  573,  279,  922,  921,  234,
  235,  332,  102,  333,  569,  334,   69,  215,  216,  481,
   60,  103,  280,  582,  240,  572,  120,   71,   66,  646,
  124,  282,  283,  335,  336,  337,  338,  339,  110,  241,
  242,   31,   32,   33,   51,  341,  220,  434,  208,  107,
   58,   43,  125,  712,  553,  240,  484,  226,  -98,  224,
  217,    8,  282,  283,  335,  336,  337,  338,  339,  119,
  241,  242,   31,   32,   33,  100,  341,   96,   92,   41,
 -368, -371,   -1,  160,  329, -372,  330,   16,  331,  -98,
  279, -373, -347,  234,  235,  332,  102,  333,  404,  334,
  362,  215,  216,  481,   60,  103,  280,  361,  227,  207,
  206,  160,  329,  205,  330,   16,  331,  203,  279,  202,
  201,  234,  235,  332,  102,  333,  200,  334,  199,  215,
  216,  481,   60,  103,  280,  198,  196,  195,  194,  240,
   94,   90,   74,   73,   72,   50,  282,  283,  335,  336,
  337,  338,  339,  204,  241,  242,   31,   32,   33,  432,
  341,  639,  733,  588,  469,  310,   21,  240,   20,   18,
   17,  983,  981,  -98,  282,  283,  335,  336,  337,  338,
  339,  630,  241,  242,   31,   32,   33,  732,  341,  638,
  611,  964,  706,  920,  795,  735,  529,  915,  466,  160,
  329,  -98,  330,   16,  331,  459,  279,  451,  448,  234,
  235,  332,  102,  333,  328,  334,  327,  215,  216,  481,
   60,  103,  280,  326,  325,  324,  323,  160,  329,  322,
  330,   16,  331,  320,  279,  318,  317,  234,  235,  332,
  102,  333,  316,  334,   24,  215,  216,  481,   60,  103,
  280,   23,   22,    3,    2,  240,    0,    0,    0,    0,
  126,    0,  282,  283,  335,  336,  337,  338,  339,    0,
  241,  242,   31,   32,   33,    0,  341,    0,    0,    0,
    0,    0,    0,  240,  528,    0,    0,    0,    0,  -98,
  282,  283,  335,  336,  337,  338,  339,    0,  241,  242,
   31,   32,   33,    0,  341,    0,    0,    0,    0,    0,
    0,    0,  715,    0,    0,  160,  329,  -98,  330,   16,
  331,    0,  279,    0,    0,  234,  235,  332,  102,  333,
    0,  334,    0,  215,  216,  481,   60,  103,  280,    0,
    0,    0,    0,  160,  329,    0,  330,   16,  331,    0,
  279,    0,    0,  234,  235,  332,  102,  333,    0,  334,
    0,  215,  216,  481,   60,  103,  280,    0,    0,    0,
    0,  240,    0,    0,    0,    0,    0,    0,  282,  283,
  335,  336,  337,  338,  339,    0,  241,  242,   31,   32,
   33,    0,  341,    0,    0,    0,    0,    0,    0,  240,
  714,    0,    0,    0,    0,  -98,  282,  283,  335,  336,
  337,  338,  339,    0,  241,  242,   31,   32,   33,    0,
  341,    0,    0,    0,    0,    0,    0,    0,  713,    0,
    0,  160,  329,  -98,  330,   16,  331,    0,  279,    0,
    0,  234,  235,  332,  102,  333,    0,  334,    0,  215,
  216,  481,   60,  103,  280,    0,    0,    0,    0,  160,
  329,    0,  330,   16,  331,    0,  279,    0,    0,  234,
  235,  332,  102,  333,    0,  334,    0,  215,  216,  481,
   60,  103,  280,    0,    0,    0,    0,  240,    0,    0,
    0,    0,    0,    0,  282,  283,  335,  336,  337,  338,
  339,    0,  241,  242,   31,   32,   33,    0,  341,    0,
    0,    0,    0,    0,    0,  240,  533,    0,    0,    0,
    0,  -98,  282,  283,  335,  336,  337,  338,  339,    0,
  241,  242,   31,   32,   33,    0,  341,    0,    0,    0,
    0,    0,    0,    0,  532,    0,    0,  160,  329,  -98,
  330,   16,  331,    0,  279,    0,    0,  234,  235,  332,
  102,  333,    0,  334,    0,  215,  216,  481,   60,  103,
  280,    0,    0,    0,    0,  160,  329,    0,  330,   16,
  331,    0,  279,    0,    0,  234,  235,  332,  102,  333,
    0,  334,    0,  215,  216,  481,   60,  103,  280,    0,
    0,    0,    0,  240,    0,    0,    0,    0,    0,    0,
  282,  283,  335,  336,  337,  338,  339,    0,  241,  242,
   31,   32,   33,    0,  341,    0,    0,    0,    0,    0,
    0,  240,  531,    0,    0,    0,    0,  -98,  282,  283,
  335,  336,  337,  338,  339,    0,  241,  242,   31,   32,
   33,  104,  341,    0,    0,  154,    0,    0,    0,    0,
  530,    0,    0,    0,    0,  -98,    0,    0,    0,  149,
  150,    0,    0,    0,    0,    0,    0,    0,  482,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  721,  723,  724,    0,  354,    0,    0,    0,    0,    0,
  281,    0,    0,    0,    0,    0,    0,    0,  938,  355,
  356,    0,    0,    0,  340,  739,    0,  725,  720,  718,
  740,    0,    1,    0,   44,    0,  719,    0,    0,  151,
    0,    0,   54,    0,   30,    0,    0,    0,  236,  284,
    0,  152,  142,  483,    0,  143,  144,   25,  160,  329,
    0,  330,   16,  331,    0,  279,    0,    0,  234,  235,
  332,  102,  333,    0,  334,    0,  215,  216,  481,   60,
  103,  280,-32766,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
-32766,-32766,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  240,    0,    0,    0,    0,    0,
    0,  282,  283,  335,  336,  337,  338,  339,    0,  241,
  242,   31,   32,   33,    0,  341,    0,    0,    0,-32766,
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
   90,    0,   34,   35,   94,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,    4,    5,
    6,   53,   54,   55,   87,   57,   58,   13,    2,    4,
    5,    6,   95,    2,   97,   67,   62,   69,   13,   71,
   72,   73,   74,   75,   76,    3,   78,   85,   14,    4,
    2,   83,    4,    5,    6,   87,    8,   90,   85,   85,
   92,   13,   14,   95,   91,   17,   62,   99,  100,  101,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   85,
   16,   87,   18,   19,   20,   21,   22,   23,    7,   25,
   26,   27,   28,   29,    3,   71,   72,   73,   34,   35,
   85,   77,    9,   59,   85,   67,   87,   16,   71,   85,
   72,   90,   74,   75,   95,   78,   97,   53,   54,   55,
   83,   57,   58,   85,   86,  101,   27,   28,   29,   91,
   62,   67,   62,   69,   16,   62,   72,   73,   74,   75,
   76,   14,   78,   32,   33,  101,   14,   83,   84,   79,
   92,   87,   79,   85,   59,   85,   92,   37,   85,   95,
    7,   93,  104,   99,  100,  101,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,  101,   87,   87,   85,
   62,  102,  103,   87,    7,   95,   95,   97,   97,   78,
   96,   95,   94,   97,  105,  106,  107,   85,   98,   56,
   86,   78,   91,   85,   53,   54,   55,   93,   57,   58,
   59,   93,   82,   62,   91,   64,   65,   66,   67,   68,
   69,   70,   92,   72,   73,   74,   75,   76,   85,   78,
   87,   82,   25,   26,   83,   84,    7,   86,   95,   85,
   97,   92,   91,   79,   79,   85,   95,   87,   94,   85,
   85,   18,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   62,   16,   85,   18,
   19,   20,   21,   22,   23,   79,   10,   94,   78,   16,
   91,   85,   93,   83,   34,   35,   53,   54,   55,   85,
   51,   52,   88,   61,   62,   19,   31,   93,   30,   59,
   36,   60,   78,   78,   53,   54,   55,   79,   57,   58,
   59,   78,   78,   62,   81,   82,   83,   79,   67,   82,
   69,   78,   89,   72,   73,   74,   75,   76,   95,   78,
   78,   78,   78,   78,   83,   84,   78,    1,    2,   78,
    4,    5,    6,   84,    8,   78,   95,   11,   12,   13,
   14,   15,  101,   17,   79,   19,   20,   21,   22,   23,
   24,   78,   78,   78,   78,   78,   84,    1,    2,   79,
    4,    5,    6,   82,    8,   86,   84,   11,   12,   13,
   14,   15,   84,   17,   84,   19,   20,   21,   22,   23,
   24,   85,   85,   57,   85,   59,   85,   85,   85,   85,
   64,   65,   66,   67,   68,   69,   70,   85,   72,   73,
   74,   75,   76,   85,   78,   86,   86,   86,   86,   86,
   86,   94,   86,   57,   87,   59,   87,   91,   88,   88,
   64,   65,   66,   67,   68,   69,   70,  101,   72,   73,
   74,   75,   76,   88,   78,   88,   88,   88,   88,   88,
   88,   95,   86,   90,   90,   90,  103,   91,    1,    2,
   94,    4,    5,    6,   90,    8,   90,   90,   11,   12,
   13,   14,   15,   90,   17,   91,   19,   20,   21,   22,
   23,   24,   91,   91,   91,   91,   91,   91,   91,    1,
    2,   91,    4,    5,    6,   91,    8,   91,   91,   11,
   12,   13,   14,   15,   91,   17,   91,   19,   20,   21,
   22,   23,   24,   91,   57,   91,   59,   91,   91,   94,
   99,   64,   65,   66,   67,   68,   69,   70,   93,   72,
   73,   74,   75,   76,   93,   78,   93,   93,   93,   93,
   93,   93,  100,   86,   94,   57,   94,   94,   91,   94,
   94,   94,   64,   65,   66,   67,   68,   69,   70,   94,
   72,   73,   74,   75,   76,   94,   78,   94,   94,   94,
   94,   94,    0,    1,    2,   94,    4,    5,    6,   91,
    8,   94,   94,   11,   12,   13,   14,   15,   95,   17,
   95,   19,   20,   21,   22,   23,   24,   95,   95,   95,
   95,    1,    2,   95,    4,    5,    6,   95,    8,   95,
   95,   11,   12,   13,   14,   15,   95,   17,   95,   19,
   20,   21,   22,   23,   24,   95,   95,   95,   95,   57,
   95,   95,   95,   95,   95,   95,   64,   65,   66,   67,
   68,   69,   70,   95,   72,   73,   74,   75,   76,   95,
   78,   96,   96,   96,   96,   96,   96,   57,   96,   96,
   96,   96,   96,   91,   64,   65,   66,   67,   68,   69,
   70,   96,   72,   73,   74,   75,   76,   96,   78,   96,
   96,   96,   96,   96,   96,   96,   86,   96,   96,    1,
    2,   91,    4,    5,    6,   96,    8,   96,   96,   11,
   12,   13,   14,   15,   96,   17,   96,   19,   20,   21,
   22,   23,   24,   96,   96,   96,   96,    1,    2,   96,
    4,    5,    6,   96,    8,   96,   96,   11,   12,   13,
   14,   15,   96,   17,   96,   19,   20,   21,   22,   23,
   24,   96,   96,   96,   96,   57,   -1,   -1,   -1,   -1,
  101,   -1,   64,   65,   66,   67,   68,   69,   70,   -1,
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
 1297, 1297, 1297, 1297, 1297,  360,  358,  342,  352,  319,
   -2,  104,  104,  104,  104,  104,  104,  392,  393,  394,
  311,   55,   84,   84,  264,  113,  113,  113,  113,  108,
    3,  110,  178,  214,  256,  225,   -8,  243,    4,  224,
  366,  366,  366,  382,  382,  382,  366,  366,  366,  366,
  382,  366,  374,  374,  374,  382,  382,  382,  382,  382,
  382,  382,  382,  382,  382,  382,  382,  382,  382,  382,
  374,  382,  382,  382,  374,  374,  382,  382,  374,  382,
  382,  382,  374,  374,  374,  374,  374,  373,  374,  374,
  374,  374,  374,  167,  167,  167,  167,  172,  172,  172,
  172,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64, 1308,
 1308, 1308, 1308, 1308, 1308, 1308, 1308,  158,  323,   61,
   78,  616,  421,  420,  615,  419,  418,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,  220,
  293,  293,  203,  154,  -33,   59,   59,   59,   59,  371,
  371,  371,  371,  371,   34,   34,   34,   34,   34,   34,
   34,   34,   34,   34,   34,   34,   34,   34,   34,  150,
  150,  139,  139,  139,  220,  220,  220,   44,  220,  220,
  220,  183,  171,   77,   77,   77,   77,   77,  156,  149,
  149,  149,  121,  131,  321,  327,  416,  608,  614,  260,
  336,  314,  284,  160,  267,  310,   98,  299,  292,  -60,
  467,  466,  249,  336,  314,  284,  174,  303,  624,  623,
  487,  619,  135,  267,  310,  310,  310,  310,  310,   98,
   98,  299,  451,  617,  209,  618,  622,  620,  190,  388,
  346,  555,  345,  345,  413,   56,  515,  133,   56,   56,
  515,  315,   56,  555,  590,  590,  388,  388,  388,  536,
  508,  555,  326,  504,   56,  512,  512,  399,  399,  388,
  388,   56,  485,  563,  388,  388,  388,  388,  388,  485,
  388,  563,  388,  388,  388,  388,  388,  388,  388,  599,
  598,  600,  597,  510,  367,  484,  294,  285,  313,  318,
  591,  516,   31,  482,  328,  325,  481,  502,  709,  324,
   75,  596,  444,  473,  562,  593,  592,  436,  437,  506,
  347,  553,  350,  372,  369,  583,  581,  422,  651,  575,
  574,  572,  599,  598,  600,  597,  537,  541,  547,  294,
  313,  535,  387,  534,  417,  507,  649,  400,  648,  464,
  595,  289,  237,  121,  460,  457,  533,  288,  565,  568,
  424,  456,  344,  434,  335,  647,  513,  696,  505,  690,
  689,  391,  662,  390,  507,  661,  301,  328,  525,  325,
  481,  502,  709,  324,  324,  324,  646,  501,  564,  193,
  436,  452,  312,  659,  343,  349,  423,  423,  423,  455,
  298,  652,  645,  687,  683,  680,  679,  678,  531,  708,
  644,  300,  401,  397,  397,  677,   72,  475,  670,  531,
  707,  643,  351,  425,  443,  454,  641,  415,  668,  453,
  486,  706,  635,  626,  705,  297,  423,  389,  698,  389,
  625,    0,    0,    0,    0, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
   -2,   -2,   -2,   -2,   -2,    0,    0,    0,    0,    0,
    0,    0,  311,  311,  311,    0, 1187,  311,  311, 1187,
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
 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187, 1187,
 1187, 1187,   -3,   -3,   -3,    0,   -3,   -3,   -3,   -3,
   -3,   -3,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  293,    0,    0,  151,  151,  151,
  151,  151,  151,  151,  151,  151,  151,  151,  151,  260,
  260,  260,  260,  260,  260,  260,  260,  260,  260,  260,
  260,  260,  260,  260,  151,  151,    0,    0,    0,  260,
  260,  260,    0,  260,  260,  260,   56,   56,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -60,    0,   56,
   56,  388,  388,  388,    0,  562,  593,  592,    0,    0,
    0,    0,    0,    0,    0,  503,  503,    0,  562,  593,
  592,    0,  568,  495,  495,  495,  495,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  503,  495,    0,
  495,  495,  495
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 278

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  363,  364,  365,32767,32767,32767,
32767,32767,32767,  318,32767,  499,  499,  499,  499,32767,
32767,32767,32767,  100,32767,32767,32767,   90,  325,32767,
  100,  100,  100,32767,32767,32767,  100,  100,  100,  100,
32767,  100,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   90,32767,  356,32767,32767,32767,   92,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  202,  204,32767,
32767,32767,32767,32767,32767,  358,32767,32767,32767,  102,
32767,32767,32767,32767,32767,32767,32767,  330,   89,  323,
  328,  505,  332,  338,  340,  326,   91,  329,  336,32767,
  136,  138,  214,32767,  133,  212,  213,  210,  209,  120,
  506,  339,  341,  337,  480,  480,  480,  480,  480,  480,
  480,  480,  480,  480,  480,  480,  480,  480,32767,  137,
  139,  178,  179,  180,32767,32767,32767,32767,  359,  360,
32767,  353,  354,32767,32767,32767,32767,32767,  497,  190,
  192,  191,  440,  156,  102,  102,32767,32767,32767,32767,
32767,32767,32767,  165,  176,  181,  187,  197,  199,  440,
32767,32767,32767,  374,  361,  362,  237,32767,32767,32767,
32767,32767,32767,  177,  183,  185,  186,  182,  184,  188,
  189,  198,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  315,  102,  454,   77,  102,  102,
  454,32767,  102,32767,  478,  478,32767,32767,  350,  508,
  317,32767,   80,  317,  102,  472,  472,  492,  492,32767,
32767,  102,  160,  495,32767,32767,32767,32767,32767,  160,
32767,  495,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  254,32767,32767,  166,  168,  170,  172,  174,  193,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  101,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  344,  346,  348,  355,  236,  238,  239,  366,
  367,  254,  255,32767,32767,  319,32767,32767,32767,32767,
32767,32767,  241,  237,32767,32767,  254,32767,32767,32767,
   51,32767,32767,32767,32767,32767,  484,32767,  481,32767,
32767,32767,32767,32767,  320,32767,32767,  167,32767,  169,
  171,  173,  175,  194,  195,  196,32767,  500,32767,32767,
   75,32767,32767,32767,  318,32767,  444,  445,  442,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  250,32767,
32767,32767,32767,  491,  489,32767,   62,32767,32767,32767,
32767,32767,32767,   54,  441,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  443,  460,32767,32767,
32767,  508,  434,  434,  508
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  173,  212,  213,  169,  171,  171,  171,  171,  169,  170,
  171,  169,  167,  161,  161,  820,  168,  175,  164,  167,
  167,  167,  450,  472,  480,  167,  167,  167,  167,  416,
  167,  170,  170,  170,  709,  612,  256,  709,  709,  709,
  709,  612,  612,  612,  612,  612,  437,  438,  917,  170,
  988,  174,  476,  170,  170,  173,  916,  170,  414,  178,
  617,  157,  168,  158,  157,  162,  172,  163,  176,  177,
  165,  166,  828,  828,  828,  828,  417,  828,  828,  643,
  643,  946,  946,  604,  419,  393,  185,  186,  187,  188,
  604,  604,  604,  230,  231,   14,   14,  604,  420,   12,
   13,   15,  604,  604,  604,  604,  604,  604,  604,  604,
  604,  604,  604,  604,  604,  604,  604,  272,  604,  251,
  604,  487,  251,  422,  604,  546,  604,  421,  604,  271,
  488,  350,  490,  490,  490,  490,  490,  350,  456,  549,
  548,  557,  558,  556,  555,  554,  370,  371,  708,  370,
  371,  708,  708,  708,  708,  286,  286,  286,  286,  286,
  286,  286,  286,  286,  286,  286,  286,  286,  286,  286,
  286,  286,  286,  286,  286,  286,  286,  286,  286,  286,
  392,  409,  410,  415,  442,  443,  444,  445,  446,  447,
  449,  455,  460,  468,  702,  263,  626,  702,  702,  702,
  702,  968,  947,  947,  563,  644,  644,  945,  477,  411,
  418,  648,  479,  364,  635,  635,  635,  924,  304,  431,
  616,  626,  626,  457,  470,  471,  474,  429,  478,  406,
  406,  406,  406,  406,  406,  406,  406,  406,  406,  406,
  406,  406,  406,  406,  399,  287,  423,  424,  425,  232,
  249,  249,  435,  249,  249,  249,  704,  609,  628,  961,
  731,  454,  955,  956,  287,  696,  692,  693,  685,  686,
  688,  690,  269,  270,  973,  566,  551,  258,  259,  261,
  953,  954,  941,  942,  943,  306,  935,  315,  936,  948,
  949,  950,  944,  564,  937,  273,  209,  210,  114,  275,
  276,  546,  301,  277,  970,  153,    0,  584,    0,  619,
  264,  265,  266,  267,  268,  959,  736,  736,  640,  940,
  313,  321,  473,    0,  971,  971,  971,  971,  971,  971,
  971,  971,  971,  971,  971,  971,  971,  971,  971,  620,
    0,    0,    0,    0,  430,  357,  357,    0,  357,  357,
  357,    0,    0,    0,  972,  972,  972,  972,  972,  972,
  972,  972,  972,  972,  972,  972,  972,  972,  972,  590,
  353,    0,    0,    0,  358,  358,  358,    0,  358,  358,
  358,    0,    0,  353,    0,    0,    0,    0,  827,  809,
  593,  594,  595,  596,  597,  598,  599,  600,  601,  602,
  603,  591,  592,    0,  590,    0,  987,    0,    0,    0,
  812,  191,  932,    0,  989,  190,  190,  190,  190,    0,
    0,  190,    0,    0,  183,  183,    0,    0,    0,    0,
    0,    0,    0,  389,    0,    0,  394,  395,    0,    0,
  401,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  439,    0,    0,    0,    0,    0,    0,  319,
    0,    0,  192,    0,    0,    0,  191,    0,    0,    0,
  193
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 471

static char yygcheck[] = {
   35,   48,   48,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   71,   35,   35,   35,   35,
   35,   35,   96,   96,   96,   35,   35,   35,   35,   65,
   35,   35,   35,   35,   95,   95,   72,   95,   95,   95,
   95,   95,   95,   95,   95,   95,   79,   79,   64,   35,
   98,   35,   79,   35,   35,   35,   64,   35,   66,   35,
  111,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   72,   72,   72,   72,   42,   72,   72,    7,
    7,    7,    7,  104,   43,   72,   56,   56,   56,   56,
  104,  104,  104,   51,   51,    3,    3,  104,   44,    3,
    3,    3,  104,  104,  104,  104,  104,  104,  104,  104,
  104,  104,  104,  104,  104,  104,  104,   77,  104,   77,
  104,    4,   77,   46,  104,   33,  104,   45,  104,   53,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,   74,   74,    7,   74,
   74,    7,    7,    7,    7,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,   80,   80,   80,   80,   80,
   61,   91,   91,   91,   91,   91,   91,   91,   91,   91,
   91,   91,   91,   91,   58,   47,   58,   58,   58,   58,
   58,   93,    7,    7,    7,   39,   39,   39,   39,   39,
   39,   39,   39,    9,   72,   72,   72,   78,   38,   38,
  106,   58,   58,   38,   38,   38,   38,   19,   38,   72,
   72,   72,   72,   72,   72,   72,   72,   72,   72,   72,
   72,   72,   72,   72,   99,    7,   52,   52,   52,   72,
   72,   72,  112,   72,   72,   72,   57,   57,   57,   57,
   57,  101,    7,    7,    7,   54,   54,   54,   54,   54,
   54,   54,   50,   50,   72,    7,    7,   68,   68,   68,
    7,    7,    7,    7,    7,   89,    7,   87,    7,    7,
    7,    7,    7,    7,    7,   68,  108,  108,  113,   68,
   68,   33,  115,   68,  102,  103,   -1,   30,   -1,   61,
   49,   49,   49,   49,   49,   59,   59,   59,   59,  100,
  100,  100,  100,   -1,   61,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   62,
   -1,   -1,   -1,   -1,   61,   61,   61,   -1,   61,   61,
   61,   -1,   -1,   -1,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   36,
   30,   -1,   -1,   -1,   62,   62,   62,   -1,   62,   62,
   62,   -1,   -1,   30,   -1,   -1,   -1,   -1,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   -1,   36,   -1,   36,   -1,   -1,   -1,
   36,   37,   36,   -1,   36,   37,   37,   37,   37,   -1,
   -1,   37,   -1,   -1,   37,   37,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   30,   -1,   -1,   30,   30,   -1,   -1,
   30,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   30,   -1,   -1,   -1,   -1,   -1,   -1,   30,
   -1,   -1,   37,   -1,   -1,   -1,   37,   -1,   -1,   -1,
   37
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,   93,  121,    0,    0,  -34,    0,  -70,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   13,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  148,    0,    0,   84,    0,  -41,  313,  370,  157,   92,
    0,    0,  -45,  -38,  -25,    3,   -2,   69, -126,  181,
  138,  -43,  108,  -12,  123,    0,  -63,  230,   12,  162,
    0,  130,  160,    0, -245,  -20,    6,    0,  205,    0,
    0,  -28,   35,    0,  114,    0,    0,  -97,   -3,  -18,
  155,    0,    0,    0,    0,    0,    0,  -19,    0,  -10,
    0,  -14,    0,   -7,    0, -148,  -24,    0,   -1,  -46,
   95,  -47,  -17, -179,   27,    0,  -13,    0,  116,    0,
    0,  -54,  -51,  -21,    0, -181
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  342,    9,   11,  489,  492,  491,  493,  494,  363,
  495,  303,  508,  496,  524,  525,  526,  497,  527,  391,
  498,  302,  561,  503,  504,  285,  505,  506,  252,  507,
  352,  509,  499,  500,  343,  159,  931,  189,  292,  613,
  647,  243,  344,  345,  346,  347,  348,  244,  211,  245,
  246,  229,  349,  247,  248,  691,  182,  737,  607,  701,
  727,  726,  728,  730,  918,  384,  385,   52,  260,  359,
  300,  819,  722,  383,  369,  952,  542,  250,  923,  436,
  290,  543,  933,  649,  934,  544,  545,  314,  228,  305,
  958,  407,  408,  967,  707,  729,  426,  427,  986,  257,
  700,  453,  464,   61,  589,  233,  615,  311,  184,  625,
  614,  642,  413,  113,   49,  293
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
   36,   37,   37,   37,   37,   37,   37,   37,  104,  104,
  105,  105,  106,  107,  107,  107,  107,  107,  107,  107,
  108,  108,  108,  108,  108,  108,  109,  109,  109,  109,
  109,  109,  109,  109,  109,  109,  110,  110,  111,  111,
  113,  113,   39,   39,   40,   40,   41,   41,   42,   42,
   43,   43,   44,   44,   45,   45,   46,   46,   47,   47,
   47,   48,   48,   48,   48,   48,   48,   49,   49,   49,
   50,   50,   50,   51,   51,   51,   51,   52,   52,   53,
   53,   53,   53,   53,   53,   53,   54,   54,   54,   54,
   54,   54,   54,   54,   55,   55,   56,   56,   56,   56,
   56,   56,   56,   94,   94,   95,   95,   95,   95,   95,
   95,   58,   58,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   72,   72,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   61,   61,   60,   60,  114,   62,  112,  112,   65,
   65,   67,   67,   66,   66,   66,   66,   66,   68,   68,
   69,   69,   69,   69,   70,   70,   71,   71,   71,   71,
   71,   71,   71,   71,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   63,   63,   63,  115,   64,   76,   76,   77,   77,
   78,   78,   78,   78,   78,   78,   79,   79,   81,   81,
   82,   82,   82,   80,   99,   99,   83,   83,   83,   83,
   83,   83,   83,   84,   84,   84,   74,   74,   85,   85,
   86,   86,   87,   87,   88,   88,   88,   88,   89,   89,
   91,   91,   92,   92,   93,   93,   93,   93,   93,  100,
  100,  100,  101,  101,  101,  102,  102,   90,   90,   96,
   96,   97,   97,   97,   97,   98,   98,   98,  103
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
    1,    2,    5,    1,    1,    1,    2,    3,    2,    3,
    1,    2,    4,    3,    3,    4,    1,    1,    1,    1,
    1,    1,    1,    3,    3,    2,    0,    3,    1,    1,
    0,    1,    1,    5,    1,    1,    1,    3,    1,    3,
    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
    3,    1,    3,    3,    3,    3,    3,    1,    3,    3,
    1,    3,    3,    1,    3,    3,    3,    1,    3,    1,
    3,    3,    2,    3,    2,    3,    1,    2,    2,    2,
    2,    2,    2,    2,    1,    3,    1,    2,    4,    3,
    3,    4,    2,    1,    1,    4,    8,    6,    7,    7,
    8,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    6,    3,    3,
    3,    2,    2,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    2,
    2,    2,    3,    2,    4,    0,    4,    0,    1,    1,
    2,    1,    2,    1,    2,    2,    3,    4,    1,    3,
    1,    2,    3,    4,    1,    3,    5,    5,    3,    3,
    3,    3,    2,    1,    1,    1,    1,    1,    1,    1,
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

#define YYSTATES 885
#define YYNLSTATES 485
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
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 88:
#line 356 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 89:
#line 360 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 90:
#line 361 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 91:
#line 362 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 92:
#line 363 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 93:
#line 367 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 94:
#line 371 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 95:
#line 375 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object(YYASP(1-1).strval, KX_OBJ_T), NULL); } break;
        case 96:
#line 376 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object(YYASP(3-3).strval, KX_OBJ_T), NULL); } break;
        case 97:
#line 380 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 98:
#line 384 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 99:
#line 385 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 100:
#line 389 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 102:
#line 394 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 103:
#line 395 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 105:
#line 400 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 106:
#line 401 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 107:
#line 402 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 108:
#line 403 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 109:
#line 404 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 110:
#line 405 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 111:
#line 406 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 407 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 408 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 409 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 410 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 411 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 412 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 413 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 121:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 122:
#line 423 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 123:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 124:
#line 425 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 125:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 126:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 127:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 129:
#line 433 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 131:
#line 438 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 132:
#line 442 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 136:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 137:
#line 450 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 138:
#line 451 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 139:
#line 452 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 141:
#line 457 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 142:
#line 458 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 143:
#line 459 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 144:
#line 460 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 145:
#line 461 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 146:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 147:
#line 466 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 148:
#line 467 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 149:
#line 468 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 150:
#line 469 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 151:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 152:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 153:
#line 472 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 154:
#line 473 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 155:
#line 474 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 156:
#line 478 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 157:
#line 479 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 158:
#line 483 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 163:
#line 494 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 167:
#line 504 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 169:
#line 509 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 171:
#line 514 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 173:
#line 519 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 175:
#line 524 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 177:
#line 529 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 179:
#line 534 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 180:
#line 535 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 182:
#line 540 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 183:
#line 541 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 184:
#line 542 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 185:
#line 543 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 186:
#line 544 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 188:
#line 549 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 189:
#line 550 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 191:
#line 555 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 556 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 194:
#line 561 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 195:
#line 562 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 563 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 568 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 200:
#line 573 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 574 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 575 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 203:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 204:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 205:
#line 578 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 207:
#line 583 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 208:
#line 584 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 209:
#line 585 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 210:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 211:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 212:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 213:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 215:
#line 594 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 217:
#line 599 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 218:
#line 600 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 219:
#line 601 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 220:
#line 602 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 221:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 222:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 223:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 225:
#line 613 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 226:
#line 614 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 227:
#line 615 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 228:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 229:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 230:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 231:
#line 622 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 232:
#line 623 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 233:
#line 627 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 234:
#line 628 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 235:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 236:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 237:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 238:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 239:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 240:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 246:
#line 640 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 247:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 248:
#line 642 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 249:
#line 643 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 250:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 251:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 252:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 253:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 254:
#line 651 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 255:
#line 652 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 256:
#line 656 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 257:
#line 657 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 258:
#line 658 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 259:
#line 659 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 260:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 261:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 262:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 263:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 264:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 265:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 266:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 267:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 268:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 269:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 270:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 271:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 272:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 273:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 274:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 275:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 276:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 277:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 278:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 279:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 280:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 281:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 282:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 283:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 284:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 285:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 286:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 287:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 288:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 289:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 290:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 291:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 292:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 293:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 294:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 295:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 296:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 297:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 298:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 299:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 300:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 301:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 302:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 303:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 304:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 305:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 306:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 307:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 308:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 309:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 310:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 311:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 312:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 313:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 314:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 315:
#line 724 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 316:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 317:
#line 732 "src/kinx.y"
{} break;
        case 319:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 320:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 321:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 322:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 324:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 325:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 326:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 327:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 329:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 331:
#line 761 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 332:
#line 762 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 333:
#line 763 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 335:
#line 768 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 336:
#line 772 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 337:
#line 773 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 338:
#line 774 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 339:
#line 775 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 340:
#line 776 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 341:
#line 777 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 342:
#line 778 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 343:
#line 779 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-1).strval, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T)); } break;
        case 344:
#line 783 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 345:
#line 784 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 346:
#line 785 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 347:
#line 786 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 348:
#line 787 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 349:
#line 788 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 350:
#line 789 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 351:
#line 790 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 352:
#line 791 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 353:
#line 792 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 354:
#line 793 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 355:
#line 794 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 356:
#line 795 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 357:
#line 796 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 358:
#line 797 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 359:
#line 798 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 360:
#line 799 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 361:
#line 800 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 362:
#line 801 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 363:
#line 802 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 364:
#line 803 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 365:
#line 804 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 366:
#line 805 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 367:
#line 806 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 368:
#line 807 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 369:
#line 808 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 370:
#line 809 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 371:
#line 810 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 372:
#line 811 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 373:
#line 812 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 374:
#line 813 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 375:
#line 814 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 376:
#line 815 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 377:
#line 816 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 378:
#line 820 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 379:
#line 821 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 380:
#line 822 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 381:
#line 823 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 382:
#line 824 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 383:
#line 825 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 384:
#line 826 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 385:
#line 827 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 386:
#line 828 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 387:
#line 829 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 388:
#line 830 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 389:
#line 831 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 390:
#line 832 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 391:
#line 833 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 392:
#line 834 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 393:
#line 835 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 394:
#line 836 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 395:
#line 837 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 396:
#line 838 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 397:
#line 839 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 398:
#line 840 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 399:
#line 841 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 400:
#line 842 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 401:
#line 843 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 402:
#line 844 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 403:
#line 845 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 404:
#line 846 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 405:
#line 847 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 406:
#line 848 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 407:
#line 849 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 408:
#line 850 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 409:
#line 851 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 410:
#line 852 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 411:
#line 853 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 412:
#line 854 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 413:
#line 855 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 414:
#line 856 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 415:
#line 857 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 416:
#line 858 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 417:
#line 859 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 418:
#line 860 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 419:
#line 861 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 420:
#line 862 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 421:
#line 863 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 422:
#line 864 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 423:
#line 865 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 424:
#line 866 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 425:
#line 867 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 426:
#line 868 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 427:
#line 869 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 428:
#line 870 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 429:
#line 871 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 430:
#line 872 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 431:
#line 876 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 432:
#line 877 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 433:
#line 878 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 434:
#line 882 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 435:
#line 886 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 436:
#line 890 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 437:
#line 891 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 439:
#line 896 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 440:
#line 900 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 441:
#line 901 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 442:
#line 902 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 443:
#line 903 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 444:
#line 904 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 445:
#line 905 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 447:
#line 910 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 448:
#line 914 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 449:
#line 915 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 450:
#line 919 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 451:
#line 920 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 452:
#line 921 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 453:
#line 925 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 454:
#line 929 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 455:
#line 930 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 456:
#line 934 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 457:
#line 935 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 458:
#line 936 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 459:
#line 937 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 460:
#line 938 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 461:
#line 939 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 462:
#line 940 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 463:
#line 944 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 464:
#line 945 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 465:
#line 946 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 468:
#line 955 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 469:
#line 956 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 470:
#line 960 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 471:
#line 961 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 472:
#line 965 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 473:
#line 967 "src/kinx.y"
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
        case 475:
#line 983 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 476:
#line 984 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 477:
#line 985 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 478:
#line 989 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 479:
#line 990 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 480:
#line 994 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 483:
#line 1000 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 484:
#line 1004 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 485:
#line 1005 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 486:
#line 1006 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 487:
#line 1007 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 488:
#line 1008 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 489:
#line 1012 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 490:
#line 1013 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 491:
#line 1014 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 492:
#line 1018 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 493:
#line 1019 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 494:
#line 1020 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 495:
#line 1024 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 496:
#line 1025 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 497:
#line 1029 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 498:
#line 1030 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 499:
#line 1034 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 502:
#line 1040 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 503:
#line 1041 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 504:
#line 1042 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 507:
#line 1048 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 508:
#line 1052 "src/kinx.y"
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
