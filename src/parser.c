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
#line 1057 "src/kinx.y"

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
  "KeyValue : NAME",
  "KeyValue : KeySpecialName",
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
  741,  742,  743,  744,  745,  746,  747,  748,  749,  750,
  751,  752,  753,  755,  754,    0,  756,  757,  758,  767,
  769,  768,  214,  778,  779,  780,  782,  784,  180,  181,
   65,  355,  776,  777,  226,   77,   78,   79,   80,   81,
   82,   83,   84,   85,   86,   87,   88,   89,  334,   16,
  335,  770,  771,  772,  111,  773,  774,  336,  389,  334,
   16,  335,   47,  355,   28,  765,  109,  766,  336,  759,
  760,  761,  762,  763,  764,   19,  740,-32766,-32766,  244,
  511,  775,  513,  512,  514,  386,  515,   91,   40,   98,
  786,  516,  517,  387,   62,  518,  245,  791,  792,  790,
  781,  783,  785,  787,  788,  789,  863,  864,  865,  866,
  867,  868,  869,  870,  871,  872,  873,  874,  875,   42,
  876,   44,  877,  878,  879,  887,  889,  888,   38,  899,
  900,  901,  903,  905,  121,-32766,-32766,-32766,  897,  898,
   38,-32766,   95,-32766,    5,  519,  106,  -74,   40,   40,
  520,   57,  522,  521,   45,  117,   26,  890,  891,  892,
 -100,  893,  894,  510,  501,-32766,  129,  130,  131,  509,
   76,  885,  -90,  886,  975,  101,  880,  881,  882,  883,
  884,  311,  951,  715,  716,-32766,  312,  895,  896,  179,
  136,  371,  992,   40,  411,  118,  907,  397,   38,  372,
   38,  805,  137,  912,  913,  911,  902,  904,  906,  908,
  909,  910,  160,  376,  830,  377,    4,  378,  834,  303,
  836,  837,  221,  222,  379,  105,  337,  842,  338,  155,
  218,  219,  223,   51,   54,  285,  -75,   93,  108,   97,
   76,  132,  133,   37,  313, -373,   46,-32766,   27, -100,
 -343,  179, -373, -373,  992,   40,  364, -343,   41,  224,
   38,  -90,   40,   40,  231,  232,  233,  551,  259,  860,
  117,  806,   42,   75,   44,  287,  288,  339,  380,  341,
  381,  343,  267,  260,  261,   34,   35,   36,    5,  234,
  106,  112,  316,  733,  235,  862, -374,  527,   45,   48,
   26,   29,  -98, -374, -374,  179,   56,  138,  139,  140,
  123,  156,  243,  829,  830,  831,  832,  833,  834,  835,
  836,  837,  838,  839,  840,  841,   76,  842,  111,  843,
  844,  845,  853,  855,  854, -369,   47, -372,   28,  122,
  293,  294, -369, -369, -372, -372,  633,  635,  636,   40,
  539, -377,  795, -102, -102,  460,  141,  805, -377, -377,
  474,   40,  536,  115,  856,  857,  858,  798,  859,  860,
  117,  738,  461,   75,  632,  630,  739,  578,  851,  401,
  852,  302,  631,  846,  847,  848,  849,  850,   59,  395,
  294,  738,  540,  385,  861,  862,  739,  160,  333,   38,
  334,   16,  335,  399,  284,  402,  396,  240,  241,  336,
  102,  337,  397,  338,  369,  215,  216,  480,   60,  103,
  285,  301,  127,  128,  134,  135,  300,  160,  333,  299,
  334,   16,  335,  457,  284,  145,  146,  240,  241,  336,
  102,  337,  462,  338,  293,  215,  216,  480,   60,  103,
  285,  533,  579,  246,  580,  117,  147,  148,  427,  370,
  287,  288,  339,  340,  341,  342,  343,  440,  247,  248,
   31,   32,   33,  432,  345,  537,  962,  404,  464,  793,
  566,   92,  527,  246,  704,  120,  628,  -98,  609,  737,
  287,  288,  339,  340,  341,  342,  343,  243,  247,  248,
   31,   32,   33,   40,  345,  267,   39,    8,    7,    6,
  296,  645,  711,   37,   38,  979,  710,  -98,  160,  333,
    9,  334,   16,  335,  534,  284,  815,  800,  240,  241,
  336,  102,  337,  709,  338,  605,  215,  216,  480,   60,
  103,  285,  817,  960,  466,  451,  110,  978,  914,  160,
  333,  796,  334,   16,  335,  702,  284,  607,  626,  240,
  241,  336,  102,  337,   64,  338,   70,  215,  216,  480,
   60,  103,  285,   99,  246,  279,  116,  439,  283,   63,
  552,  287,  288,  339,  340,  341,  342,  343,   67,  247,
  248,   31,   32,   33,   68,  345,  549,  500,  570,  577,
  569,  567,  572,  711,  922,  246,  921,  568,  -98,   69,
  581,    9,  287,  288,  339,  340,  341,  342,  343,  571,
  247,  248,   31,   32,   33,   71,  345,   66,   52,  638,
  220,  433,  208,  107, -348,   58,   43,  732,  483,  -98,
  227, -348, -348,   -1,  160,  333,  225,  334,   16,  335,
  217,  284,  119,  100,  240,  241,  336,  102,  337,   96,
  338,  197,  215,  216,  480,   60,  103,  285,  403,  366,
  365,  228,  160,  333,  207,  334,   16,  335,  206,  284,
  205,  203,  240,  241,  336,  102,  337,  202,  338,  201,
  215,  216,  480,   60,  103,  285,  200,  199,  198,  196,
  246,  195,  194,   94,   90,   74,   73,  287,  288,  339,
  340,  341,  342,  343,   72,  247,  248,   31,   32,   33,
   50,  345,  204,  431,  125,  587,  468,  314,  246,   21,
   20,   18,   17,  983,  -98,  287,  288,  339,  340,  341,
  342,  343,  981,  247,  248,   31,   32,   33,  629,  345,
  731,  637,  610,  964,  705,  920,  794,  529,  734,  915,
  160,  333,  -98,  334,   16,  335,  465,  284,  458,  450,
  240,  241,  336,  102,  337,  447,  338,  332,  215,  216,
  480,   60,  103,  285,  331,  330,  329,  328,  160,  333,
  327,  334,   16,  335,  326,  284,  324,  322,  240,  241,
  336,  102,  337,  321,  338,  320,  215,  216,  480,   60,
  103,  285,   24,   23,   22,    3,  246,    2,  797,  124,
    0,    0,    0,  287,  288,  339,  340,  341,  342,  343,
  126,  247,  248,   31,   32,   33,    0,  345,    0,    0,
    0,    0,    0,    0,  246,  528,    0,    0,    0,    0,
  -98,  287,  288,  339,  340,  341,  342,  343,    0,  247,
  248,   31,   32,   33,    0,  345,    0,    0,    0,    0,
    0,    0,    0,  714,    0,    0,  160,  333,  -98,  334,
   16,  335,    0,  284,    0,    0,  240,  241,  336,  102,
  337,    0,  338,    0,  215,  216,  480,   60,  103,  285,
    0,    0,    0,    0,  160,  333,    0,  334,   16,  335,
    0,  284,    0,    0,  240,  241,  336,  102,  337,    0,
  338,    0,  215,  216,  480,   60,  103,  285,    0,    0,
    0,    0,  246,    0,    0,    0,    0,    0,    0,  287,
  288,  339,  340,  341,  342,  343,    0,  247,  248,   31,
   32,   33,    0,  345,    0,    0,    0,    0,    0,    0,
  246,  713,    0,    0,    0,    0,  -98,  287,  288,  339,
  340,  341,  342,  343,    0,  247,  248,   31,   32,   33,
    0,  345,    0,    0,    0,    0,    0,    0,    0,  712,
    0,    0,  160,  333,  -98,  334,   16,  335,    0,  284,
    0,    0,  240,  241,  336,  102,  337,    0,  338,    0,
  215,  216,  480,   60,  103,  285,    0,    0,    0,    0,
  160,  333,    0,  334,   16,  335,    0,  284,    0,    0,
  240,  241,  336,  102,  337,    0,  338,    0,  215,  216,
  480,   60,  103,  285,    0,    0,    0,    0,  246,    0,
    0,    0,    0,    0,    0,  287,  288,  339,  340,  341,
  342,  343,    0,  247,  248,   31,   32,   33,    0,  345,
    0,    0,    0,    0,    0,    0,  246,  532,    0,    0,
    0,    0,  -98,  287,  288,  339,  340,  341,  342,  343,
    0,  247,  248,   31,   32,   33,    0,  345,    0,    0,
    0,    0,    0,    0,    0,  531,    0,    0,  160,  333,
  -98,  334,   16,  335,    0,  284,    0,    0,  240,  241,
  336,  102,  337,    0,  338,    0,  215,  216,  480,   60,
  103,  285,    0,    0,    0,    0,  160,  333,    0,  334,
   16,  335,    0,  284,    0,    0,  240,  241,  336,  102,
  337,    0,  338,    0,  215,  216,  480,   60,  103,  285,
    0,    0,    0,    0,  246,    0,    0,    0,    0,    0,
    0,  287,  288,  339,  340,  341,  342,  343,    0,  247,
  248,   31,   32,   33,    0,  345,    0,    0,    0,    0,
    0,    0,  246,  530,    0,    0,    0,    0,  -98,  287,
  288,  339,  340,  341,  342,  343,    0,  247,  248,   31,
   32,   33,  104,  345,    0,    0,  154,    0,    0,    0,
    0,  527,    0,    0,    0,    0,  -98,    0,    0,    0,
  149,  150,    0,    0,    0,    0,    0,    0,    0,  481,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  720,  722,  723,    0,  358,    0,    0,    0,    0,
    0,  286,    0,    0,    0,    0,    0,    0,    0,  938,
  359,  360,    0,    0,    0,  344,  738,    0,  724,  719,
  717,  739,    0,    1,    0,   44,    0,  718,    0,    0,
  151,    0,    0,   55,    0,   30,    0,    0,    0,  242,
  289,    0,  152,  142,  482,    0,  143,  144,   25,  160,
  333,    0,  334,   16,  335,    0,  284,    0,    0,  240,
  241,  336,  102,  337,    0,  338,    0,  215,  216,  480,
   60,  103,  285,-32766,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,-32766,-32766,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  246,    0,    0,    0,    0,
    0,    0,  287,  288,  339,  340,  341,  342,  343,    0,
  247,  248,   31,   32,   33,    0,  345,    0,    0,    0,
-32766,-32766,-32766,    0,    0,    0,-32766,    0,    0,  -98,
    0,    0,    0,    0,   40,    0,    0,    0,    0,    0,
    0,-32766,    0,    0,    0,    0,    0,    0,    0,    0,
-32766,    0,    0,-32766,-32766,    0,    0,-32766,-32766
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1429

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,    0,   18,   19,   20,   21,
   22,   23,   19,   25,   26,   27,   28,   29,   61,   62,
   90,    2,   34,   35,   94,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,    4,    5,
    6,   53,   54,   55,   87,   57,   58,   13,    4,    4,
    5,    6,   95,    2,   97,   67,   23,   69,   13,   71,
   72,   73,   74,   75,   76,    3,   78,   14,   14,    9,
    2,   83,    4,    5,    6,   87,    8,   90,   85,    7,
   92,   13,   14,   95,   91,   17,   62,   99,  100,  101,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   85,
   16,   87,   18,   19,   20,   21,   22,   23,   85,   25,
   26,   27,   28,   29,   37,   71,   72,   73,   34,   35,
   85,   77,    7,   59,   85,   67,   87,    7,   85,   85,
   72,   90,   74,   75,   95,   59,   97,   53,   54,   55,
    2,   57,   58,   85,   86,  101,   27,   28,   29,   91,
   62,   67,    2,   69,   71,   62,   72,   73,   74,   75,
   76,   78,   78,   32,   33,  101,   83,   83,   84,   16,
   92,   87,   79,   85,   79,   98,   92,  101,   85,   95,
   85,   93,  104,   99,  100,  101,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,    7,   62,   87,   62,
   62,  102,  103,   85,   10,   86,   95,   14,   97,   91,
   86,   16,   93,   94,   79,   85,   19,   93,   94,   56,
   85,   91,   85,   85,   53,   54,   55,   94,   57,   58,
   59,   93,   85,   62,   87,   64,   65,   66,   67,   68,
   69,   70,   85,   72,   73,   74,   75,   76,   85,   78,
   87,   87,    3,   96,   83,   84,   86,   86,   95,   95,
   97,   97,   91,   93,   94,   16,   95,  105,  106,  107,
   31,   18,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   62,   16,   87,   18,
   19,   20,   21,   22,   23,   86,   95,   86,   97,   30,
   78,   78,   93,   94,   93,   94,   53,   54,   55,   85,
   82,   86,   88,   91,   91,   79,   36,   93,   93,   94,
   92,   85,   82,   59,   53,   54,   55,   60,   57,   58,
   59,   78,   92,   62,   81,   82,   83,   91,   67,   93,
   69,   78,   89,   72,   73,   74,   75,   76,   95,   78,
   78,   78,   82,   79,   83,   84,   83,    1,    2,   85,
    4,    5,    6,   78,    8,   78,   95,   11,   12,   13,
   14,   15,  101,   17,   78,   19,   20,   21,   22,   23,
   24,   78,   25,   26,   34,   35,   78,    1,    2,   78,
    4,    5,    6,   78,    8,   51,   52,   11,   12,   13,
   14,   15,   78,   17,   78,   19,   20,   21,   22,   23,
   24,   78,   78,   57,   78,   59,   61,   62,   78,   78,
   64,   65,   66,   67,   68,   69,   70,   79,   72,   73,
   74,   75,   76,   79,   78,   82,   84,   79,   79,   88,
   91,   94,   86,   57,   84,   59,   84,   91,   84,   84,
   64,   65,   66,   67,   68,   69,   70,  101,   72,   73,
   74,   75,   76,   85,   78,   85,   85,   85,   85,   85,
   85,   94,   86,   85,   85,   88,   86,   91,    1,    2,
   94,    4,    5,    6,   86,    8,   86,   86,   11,   12,
   13,   14,   15,   86,   17,   86,   19,   20,   21,   22,
   23,   24,   86,   88,   87,   87,   93,   88,   88,    1,
    2,   88,    4,    5,    6,   88,    8,   88,   88,   11,
   12,   13,   14,   15,   90,   17,   90,   19,   20,   21,
   22,   23,   24,   90,   57,   90,   59,   90,   90,   90,
   94,   64,   65,   66,   67,   68,   69,   70,   91,   72,
   73,   74,   75,   76,   91,   78,   91,   91,   91,   91,
   91,   91,   91,   86,   91,   57,   91,   91,   91,   91,
   91,   94,   64,   65,   66,   67,   68,   69,   70,   91,
   72,   73,   74,   75,   76,   91,   78,   91,   93,   96,
   93,   93,   93,   93,   86,   93,   93,   96,   94,   91,
   94,   93,   94,    0,    1,    2,   94,    4,    5,    6,
   94,    8,   94,   94,   11,   12,   13,   14,   15,   94,
   17,   95,   19,   20,   21,   22,   23,   24,   95,   95,
   95,   95,    1,    2,   95,    4,    5,    6,   95,    8,
   95,   95,   11,   12,   13,   14,   15,   95,   17,   95,
   19,   20,   21,   22,   23,   24,   95,   95,   95,   95,
   57,   95,   95,   95,   95,   95,   95,   64,   65,   66,
   67,   68,   69,   70,   95,   72,   73,   74,   75,   76,
   95,   78,   95,   95,  100,   96,   96,   96,   57,   96,
   96,   96,   96,   96,   91,   64,   65,   66,   67,   68,
   69,   70,   96,   72,   73,   74,   75,   76,   96,   78,
   96,   96,   96,   96,   96,   96,   96,   86,   96,   96,
    1,    2,   91,    4,    5,    6,   96,    8,   96,   96,
   11,   12,   13,   14,   15,   96,   17,   96,   19,   20,
   21,   22,   23,   24,   96,   96,   96,   96,    1,    2,
   96,    4,    5,    6,   96,    8,   96,   96,   11,   12,
   13,   14,   15,   96,   17,   96,   19,   20,   21,   22,
   23,   24,   96,   96,   96,   96,   57,   96,  103,   99,
   -1,   -1,   -1,   64,   65,   66,   67,   68,   69,   70,
  101,   72,   73,   74,   75,   76,   -1,   78,   -1,   -1,
   -1,   -1,   -1,   -1,   57,   86,   -1,   -1,   -1,   -1,
   91,   64,   65,   66,   67,   68,   69,   70,   -1,   72,
   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   86,   -1,   -1,    1,    2,   91,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   -1,   17,   -1,   19,   20,   21,   22,   23,   24,
   -1,   -1,   -1,   -1,    1,    2,   -1,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   -1,
   17,   -1,   19,   20,   21,   22,   23,   24,   -1,   -1,
   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,   64,
   65,   66,   67,   68,   69,   70,   -1,   72,   73,   74,
   75,   76,   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,
   57,   86,   -1,   -1,   -1,   -1,   91,   64,   65,   66,
   67,   68,   69,   70,   -1,   72,   73,   74,   75,   76,
   -1,   78,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   86,
   -1,   -1,    1,    2,   91,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   -1,   17,   -1,
   19,   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,
    1,    2,   -1,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   14,   15,   -1,   17,   -1,   19,   20,
   21,   22,   23,   24,   -1,   -1,   -1,   -1,   57,   -1,
   -1,   -1,   -1,   -1,   -1,   64,   65,   66,   67,   68,
   69,   70,   -1,   72,   73,   74,   75,   76,   -1,   78,
   -1,   -1,   -1,   -1,   -1,   -1,   57,   86,   -1,   -1,
   -1,   -1,   91,   64,   65,   66,   67,   68,   69,   70,
   -1,   72,   73,   74,   75,   76,   -1,   78,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   86,   -1,   -1,    1,    2,
   91,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   -1,   17,   -1,   19,   20,   21,   22,
   23,   24,   -1,   -1,   -1,   -1,    1,    2,   -1,    4,
    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,
   15,   -1,   17,   -1,   19,   20,   21,   22,   23,   24,
   -1,   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,
   -1,   64,   65,   66,   67,   68,   69,   70,   -1,   72,
   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,   -1,
   -1,   -1,   57,   86,   -1,   -1,   -1,   -1,   91,   64,
   65,   66,   67,   68,   69,   70,   -1,   72,   73,   74,
   75,   76,   14,   78,   -1,   -1,   18,   -1,   -1,   -1,
   -1,   86,   -1,   -1,   -1,   -1,   91,   -1,   -1,   -1,
   32,   33,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   41,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   53,   54,   55,   -1,   57,   -1,   -1,   -1,   -1,
   -1,   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   71,
   72,   73,   -1,   -1,   -1,   77,   78,   -1,   80,   81,
   82,   83,   -1,   85,   -1,   87,   -1,   89,   -1,   -1,
   92,   -1,   -1,   95,   -1,   97,   -1,   -1,   -1,  101,
  102,   -1,  104,  105,  106,   -1,  108,  109,  110,    1,
    2,   -1,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   -1,   17,   -1,   19,   20,   21,
   22,   23,   24,   14,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   32,   33,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,
   -1,   -1,   64,   65,   66,   67,   68,   69,   70,   -1,
   72,   73,   74,   75,   76,   -1,   78,   -1,   -1,   -1,
   71,   72,   73,   -1,   -1,   -1,   77,   -1,   -1,   91,
   -1,   -1,   -1,   -1,   85,   -1,   -1,   -1,   -1,   -1,
   -1,   92,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  101,   -1,   -1,  104,  105,   -1,   -1,  108,  109
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1308,  211,  517,  426,  548,  396, 1135,  671, 1107,  903,
  643,  759, 1019,  991,  875,  787, 1308, 1308, 1308, 1308,
 1308, 1308, 1308, 1308, 1308,  405,  400,  404,  402,  392,
   -2,  104,  104,  104,  104,  104,  104,  440,  449,  456,
  311,   55,   84,   84,  264,  175,  175,  175,  175,  108,
    3,  158,  113,  178,  170,  314,  115,   43,  177,  276,
  428,  428,  428,  429,  429,  429,  428,  428,  428,  428,
  429,  428,  418,  418,  418,  429,  429,  429,  429,  429,
  429,  429,  429,  429,  429,  429,  429,  429,  429,  429,
  418,  429,  429,  429,  418,  418,  429,  429,  418,  429,
  429,  429,  418,  418,  418,  418,  418,  421,  418,  418,
  418,  418,  418,  233,  233,  233,  233,   63,   63,   63,
   63,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64, 1319,
 1319, 1319, 1319, 1319, 1319, 1319, 1319,  173,  235,   61,
   78,  541,  467,  469,  533,  470,  455,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,  187,
  293,  293,  203,  197,  -33,   59,   59,   59,   59,  420,
  420,  420,  420,  420,   34,   34,   34,   34,   34,   34,
   34,   34,   34,   34,   34,   34,   34,   34,   34,  241,
  241,  139,  139,  139,  187,  187,  187,   44,  187,  187,
  187,  262,  263,  249,  103,  103,  103,  103,  103,  204,
  202,  251,  159,  210,  164,  265,  202,  202,  140,  289,
  366,  312,  566,  627,  628,  313,  237,  336,  381,   97,
  397,  390,   98,  384,  395,  -60,  515,  513,  286,  237,
  336,  381,  380,  636,  635,  536,  631,   96,  397,  390,
  390,  390,  390,  390,   98,   98,  384,  497,  629,  280,
  630,  634,  633,  268,  424,  374,  574,  373,  373,  715,
   29,  552,   70,   29,   29,  552,  325,   29,  574,  603,
  603,  424,  424,  424,  543,  574,  234,  538,   29,  544,
  544,  458,  458,  424,  424,   29,  417,  576,  424,  424,
  424,  424,  424,  417,  424,  576,  424,  424,  424,  424,
  424,  424,  424,  619,  611,  625,  610,  486,  425,  528,
  351,  348,  343,  303,  604,  556,   15,  519,  309,  279,
  720,  624,  729,  320,   54,  609,  389,  516,  575,  607,
  606,  489,  474,  540,  327,  573,  398,  423,  422,  602,
  601,  460,  663,  594,  592,  586,  619,  611,  625,  610,
  351,  343,  387,  463,  542,  662,  391,  660,  511,  608,
  135,  229,  140,  510,  509,  565,  394,  583,  585,  485,
  508,  376,  487,  388,  659,  546,  709,  539,  707,  701,
  447,  679,  441,  542,  673,  307,  309,  558,  279,  720,
  624,  729,  320,  320,  320,  658,  535,  579,   82,  489,
  503,  355,  672,  364,  438,  483,  483,  483,  507,  399,
  670,  657,  700,  698,  694,  691,  690,  559,  721,  656,
  304,  459,  457,  457,  689,   72,  518,  688,  559,  719,
  655,  393,  488,  476,  506,  654,  427,  681,  505,  534,
  718,  652,  646,  717,  310,  483,  430,  716,  430,  637,
    0,    0,    0,    0, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,   -2,
   -2,   -2,   -2,   -2,    0,    0,    0,    0,    0,    0,
    0,  311,  311,  311,    0, 1198,  311,  311, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198,
 1198,   -3,   -3,   -3,    0,   -3,   -3,   -3,   -3,   -3,
   -3,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  293,    0,    0,  151,  151,  151,  151,
  151,  151,  151,  151,  151,  151,  151,  151,  313,  313,
  313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
  313,  313,  313,  151,  151,    0,    0,    0,  313,  313,
  313,    0,  313,  313,  313,   29,   29,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -60,    0,   29,   29,  424,  424,  424,    0,
  575,  607,  606,    0,    0,    0,    0,    0,    0,    0,
  537,  537,    0,  575,  607,  606,  585,  453,  453,  453,
  453,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  537,  453,    0,  453,  453,  453
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 283

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  364,  365,  366,32767,32767,32767,
32767,32767,32767,  318,32767,  500,  500,  500,  500,32767,
32767,  371,32767,32767,  370,32767,32767,32767,  325,32767,
  100,  100,  100,32767,32767,32767,  100,  100,  100,  100,
32767,  100,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,   90,32767,  357,32767,32767,32767,   92,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  202,  204,32767,
32767,32767,32767,32767,32767,  359,32767,32767,32767,  102,
32767,32767,32767,32767,32767,32767,32767,  330,   89,  323,
  328,  506,  332,  338,  340,  326,   91,  329,  336,32767,
  136,  138,  214,32767,  133,  212,  213,  210,  209,  120,
  507,  339,  341,  337,  481,  481,  481,  481,  481,  481,
  481,  481,  481,  481,  481,  481,  481,  481,32767,  137,
  139,  178,  179,  180,32767,32767,32767,32767,  360,  361,
32767,  354,  355,  509,32767,32767,32767,32767,32767,  498,
  190,  236,  238,  239,  254,  255,  192,  191,  441,  156,
  102,  102,32767,32767,32767,32767,32767,32767,32767,  165,
  176,  181,  187,  197,  199,  441,32767,32767,32767,  375,
  362,  363,32767,32767,32767,32767,32767,32767,  177,  183,
  185,  186,  182,  184,  188,  189,  198,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  315,
  102,  455,   77,  102,  102,  455,32767,  102,32767,  479,
  479,32767,32767,  351,  317,32767,   80,  317,  102,  473,
  473,  493,  493,32767,32767,  102,  160,  496,32767,32767,
32767,32767,32767,  160,32767,  496,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  254,32767,32767,  166,  168,
  170,  172,  174,  193,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  101,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  345,  347,  349,  356,
  367,  368,  344,32767,  319,32767,32767,32767,32767,32767,
32767,  241,  237,32767,32767,  343,32767,32767,32767,   51,
32767,32767,32767,32767,32767,  485,32767,  482,32767,32767,
32767,32767,32767,  320,32767,32767,  167,32767,  169,  171,
  173,  175,  194,  195,  196,32767,  501,32767,32767,   75,
32767,32767,32767,  318,32767,  445,  446,  443,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  250,32767,32767,
32767,32767,  492,  490,32767,   62,32767,32767,32767,32767,
32767,32767,   54,  442,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  444,  461,32767,32767,32767,
  509,  435,  435,  509
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  173,  819,  392,  169,  171,  171,  171,  171,  169,  170,
  167,  171,  169,  168,  161,  161,  415,  175,  164,  167,
  167,  167,  449,  471,  479,  167,  167,  167,  167,  616,
  167,  170,  170,  170,  642,  642,  946,  946,  643,  643,
  945,  476,  410,  417,  647,  478,  436,  437,  988,  170,
  413,  174,  475,  170,  170,  173,  416,  170,  418,  178,
  545,  157,  168,  158,  157,  162,  172,  163,  176,  177,
  165,  166,  291,  291,  291,  291,  291,  291,  291,  291,
  291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
  291,  291,  291,  291,  291,  291,  291,  374,  375,  619,
  374,  375,  419,  707,  212,  213,  707,  707,  707,  707,
  185,  186,  187,  188,  972,  972,  972,  972,  972,  972,
  972,  972,  972,  972,  972,  972,  972,  972,  972,  420,
  917,  634,  634,  634,  362,  362,  362,  916,  362,  362,
  362,  703,  608,  627,  961,  730,  405,  405,  405,  405,
  405,  405,  405,  405,  405,  405,  405,  405,  405,  405,
  405,  421,  391,  947,  947,  562,  238,  255,  255,  486,
  255,  255,  255,  354,  269,  270,  271,  272,  273,  487,
  489,  489,  489,  489,  489,  354,  455,  548,  547,  556,
  557,  555,  554,  553,  277,  268,  257,  973,  701,  257,
  625,  701,  701,  701,  701,  292,  408,  409,  414,  441,
  442,  443,  444,  445,  446,  448,  454,  459,  467,  422,
  423,  424,  955,  956,  292,  625,  625,  695,  691,  692,
  684,  685,  687,  689,  565,  550,  545,  274,  275,  953,
  954,  941,  942,  943,  428,  935,  276,  936,  948,  949,
  950,  944,  563,  937,  603,  236,  237,  968,   14,   14,
  603,  603,  603,   12,   13,   15,  924,  603,  940,  317,
  325,  472,  603,  603,  603,  603,  603,  603,  603,  603,
  603,  603,  603,  603,  603,  603,  603,  615,  603,  368,
  603,  618,  310,  583,  603,  434,  603,  398,  603,  959,
  735,  735,  639,  209,  210,  319,  971,  971,  971,  971,
  971,  971,  971,  971,  971,  971,  971,  971,  971,  971,
  971,  589,  453,  970,  305,    0,  429,  361,  361,  114,
  361,  361,  361,  153,    0,    0,    0,    0,    0,  826,
  808,  592,  593,  594,  595,  596,  597,  598,  599,  600,
  601,  602,  590,  591,    0,  589,  357,  987,    0,    0,
    0,  811,  191,  932,    0,  989,  190,  190,  190,  190,
    0,    0,    0,  190,    0,  357,  183,  183,  708,  611,
    0,  708,  708,  708,  708,  611,  611,  611,  611,  611,
  308,  430,  263,  264,  266,  456,  469,  470,  473,    0,
  477,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  278,    0,    0,  192,  280,  281,    0,  191,  282,    0,
    0,  193,    0,    0,  388,    0,    0,  393,  394,    0,
    0,  400,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  438,    0,    0,    0,    0,    0,    0,  323
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 450

static char yygcheck[] = {
   35,   71,   72,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   65,   35,   35,   35,
   35,   35,   96,   96,   96,   35,   35,   35,   35,  111,
   35,   35,   35,   35,    7,    7,    7,    7,   39,   39,
   39,   39,   39,   39,   39,   39,   79,   79,   98,   35,
   66,   35,   79,   35,   35,   35,   42,   35,   43,   35,
   33,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   80,   80,   80,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,   80,   80,   74,   74,   62,
   74,   74,   44,    7,   48,   48,    7,    7,    7,    7,
   56,   56,   56,   56,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   45,
   64,   72,   72,   72,   62,   62,   62,   64,   62,   62,
   62,   57,   57,   57,   57,   57,   72,   72,   72,   72,
   72,   72,   72,   72,   72,   72,   72,   72,   72,   72,
   72,   46,   61,    7,    7,    7,   72,   72,   72,    4,
   72,   72,   72,    4,   49,   49,   49,   49,   49,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,   77,   47,   77,   72,   58,   77,
   58,   58,   58,   58,   58,    7,   91,   91,   91,   91,
   91,   91,   91,   91,   91,   91,   91,   91,   91,   52,
   52,   52,    7,    7,    7,   58,   58,   54,   54,   54,
   54,   54,   54,   54,    7,    7,   33,   50,   50,    7,
    7,    7,    7,    7,   19,    7,   53,    7,    7,    7,
    7,    7,    7,    7,  104,   51,   51,   93,    3,    3,
  104,  104,  104,    3,    3,    3,   78,  104,  100,  100,
  100,  100,  104,  104,  104,  104,  104,  104,  104,  104,
  104,  104,  104,  104,  104,  104,  104,  106,  104,    9,
  104,   61,   89,   30,  104,  112,  104,   99,  104,   59,
   59,   59,   59,  108,  108,   87,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   36,  101,  102,  115,   -1,   61,   61,   61,  113,
   61,   61,   61,  103,   -1,   -1,   -1,   -1,   -1,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   -1,   36,   30,   36,   -1,   -1,
   -1,   36,   37,   36,   -1,   36,   37,   37,   37,   37,
   -1,   -1,   -1,   37,   -1,   30,   37,   37,   95,   95,
   -1,   95,   95,   95,   95,   95,   95,   95,   95,   95,
   38,   38,   68,   68,   68,   38,   38,   38,   38,   -1,
   38,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   68,   -1,   -1,   37,   68,   68,   -1,   37,   68,   -1,
   -1,   37,   -1,   -1,   30,   -1,   -1,   30,   30,   -1,
   -1,   30,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   30,   -1,   -1,   -1,   -1,   -1,   -1,   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  256,  169,    0,    0,  -79,    0,    1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   30,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  134,    0,    0,   19,    0,  -41,  264,  321,  329,  -75,
    0,    0,  -65,  -64,  -21,    5,   36,   69,  -23,   45,
  103,  119,   81,  105,   85,    0,  -39,  115,   16,  146,
    0,  112,  -80,    0, -168,  -33,   -3,    0,  320,    0,
    0,  -42,  -48,    0,   65,    0,    0,  -20,   46,  -18,
   72,    0,    0,    0,    0,    0,    0,   -5,    0,   -8,
    0,   11,    0,   49,    0,  196,  -24,    0,   -4,    2,
   43,   10,   -2, -150,  197,    0,   48,    0,  123,    0,
    0,  -85,  -12,    6,    0, -158
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  346,   10,   11,  488,  491,  490,  492,  493,  367,
  494,  307,  507,  495,  523,  524,  525,  496,  526,  390,
  497,  306,  560,  502,  503,  290,  504,  505,  258,  506,
  356,  508,  498,  499,  347,  159,  931,  189,  297,  612,
  646,  249,  348,  349,  350,  351,  352,  250,  211,  251,
  252,  230,  353,  253,  254,  690,  182,  736,  606,  700,
  726,  725,  727,  729,  918,  383,  384,   53,  265,  363,
  304,  818,  721,  382,  373,  952,  541,  256,  923,  435,
  295,  542,  933,  648,  934,  543,  544,  318,  229,  309,
  958,  406,  407,  967,  706,  728,  425,  426,  986,  262,
  699,  452,  463,   61,  588,  239,  614,  315,  184,  624,
  613,  641,  412,  113,   49,  298
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
   71,   71,   71,   71,   71,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   63,   63,   63,  115,   64,   76,   76,   77,
   77,   78,   78,   78,   78,   78,   78,   79,   79,   81,
   81,   82,   82,   82,   80,   99,   99,   83,   83,   83,
   83,   83,   83,   83,   84,   84,   84,   74,   74,   85,
   85,   86,   86,   87,   87,   88,   88,   88,   88,   89,
   89,   91,   91,   92,   92,   93,   93,   93,   93,   93,
  100,  100,  100,  101,  101,  101,  102,  102,   90,   90,
   96,   96,   97,   97,   97,   97,   98,   98,   98,  103
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
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    2,    3,    3,    2,    0,    3,    3,    3,    1,
    3,    1,    4,    3,    6,    3,    3,    1,    3,    1,
    1,    6,    6,    7,    1,    0,    2,    5,    5,    5,
    6,    6,    6,    2,    6,    6,    6,    1,    1,    5,
    5,    3,    3,    0,    4,    1,    4,    3,    3,    0,
    3,    0,    1,    1,    3,    1,    4,    1,    1,    2,
    2,    1,    2,    0,    2,    3,    0,    3,    0,    3,
    0,    1,    1,    2,    3,    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 884
#define YYNLSTATES 484
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
#line 780 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-1).strval, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T)); } break;
        case 345:
#line 784 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 346:
#line 785 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 347:
#line 786 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 348:
#line 787 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 349:
#line 788 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 350:
#line 789 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 351:
#line 790 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 352:
#line 791 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 353:
#line 792 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 354:
#line 793 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 355:
#line 794 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 356:
#line 795 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 357:
#line 796 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 358:
#line 797 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 359:
#line 798 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 360:
#line 799 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 361:
#line 800 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 362:
#line 801 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 363:
#line 802 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 364:
#line 803 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 365:
#line 804 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 366:
#line 805 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 367:
#line 806 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 368:
#line 807 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 369:
#line 808 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 370:
#line 809 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 371:
#line 810 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 372:
#line 811 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 373:
#line 812 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 374:
#line 813 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 375:
#line 814 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 376:
#line 815 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 377:
#line 816 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 378:
#line 817 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 379:
#line 821 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 380:
#line 822 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 381:
#line 823 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 382:
#line 824 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 383:
#line 825 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 384:
#line 826 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 385:
#line 827 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 386:
#line 828 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 387:
#line 829 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 388:
#line 830 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 389:
#line 831 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 390:
#line 832 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 391:
#line 833 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 392:
#line 834 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 393:
#line 835 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 394:
#line 836 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 395:
#line 837 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 396:
#line 838 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 397:
#line 839 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 398:
#line 840 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 399:
#line 841 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 400:
#line 842 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 401:
#line 843 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 402:
#line 844 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 403:
#line 845 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 404:
#line 846 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 405:
#line 847 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 406:
#line 848 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 407:
#line 849 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 408:
#line 850 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 409:
#line 851 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 410:
#line 852 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 411:
#line 853 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 412:
#line 854 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 413:
#line 855 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 414:
#line 856 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 415:
#line 857 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 416:
#line 858 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 417:
#line 859 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 418:
#line 860 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 419:
#line 861 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 420:
#line 862 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 421:
#line 863 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 422:
#line 864 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 423:
#line 865 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 424:
#line 866 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 425:
#line 867 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 426:
#line 868 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 427:
#line 869 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 428:
#line 870 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 429:
#line 871 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 430:
#line 872 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 431:
#line 873 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 432:
#line 877 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 433:
#line 878 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 434:
#line 879 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 435:
#line 883 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 436:
#line 887 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 437:
#line 891 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 438:
#line 892 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 440:
#line 897 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 441:
#line 901 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 442:
#line 902 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 443:
#line 903 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 444:
#line 904 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 445:
#line 905 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 446:
#line 906 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 448:
#line 911 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 449:
#line 915 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 450:
#line 916 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 451:
#line 920 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 452:
#line 921 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 453:
#line 922 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 454:
#line 926 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 455:
#line 930 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 456:
#line 931 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 457:
#line 935 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 458:
#line 936 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 459:
#line 937 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 460:
#line 938 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 461:
#line 939 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 462:
#line 940 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 463:
#line 941 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 464:
#line 945 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 465:
#line 946 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 466:
#line 947 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 469:
#line 956 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 470:
#line 957 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 471:
#line 961 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 472:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 473:
#line 966 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 474:
#line 968 "src/kinx.y"
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
        case 476:
#line 984 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 477:
#line 985 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 478:
#line 986 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 479:
#line 990 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 480:
#line 991 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 481:
#line 995 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 484:
#line 1001 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 485:
#line 1005 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 486:
#line 1006 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 487:
#line 1007 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 488:
#line 1008 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 489:
#line 1009 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 490:
#line 1013 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 491:
#line 1014 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 492:
#line 1015 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 493:
#line 1019 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 494:
#line 1020 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 495:
#line 1021 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 496:
#line 1025 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 497:
#line 1026 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
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
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 504:
#line 1042 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 505:
#line 1043 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 508:
#line 1049 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 509:
#line 1053 "src/kinx.y"
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
