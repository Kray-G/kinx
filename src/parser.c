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
#line 1103 "src/kinx.y"

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
#define YYNONTERMS 122

static short yyaction[] = {
  789,  790,  791,  792,  793,  794,  795,  796,  797,  798,
  799,  800,  801,  803,  802,  111,  804,  805,  806,  815,
  817,  816,  226,  825,  826,  827,  829,  831,  187,  188,
   69,  369,  823,  824,  237,   81,   82,   83,   84,   85,
   86,   87,   88,   89,   90,   91,   92,   93,  348,   16,
  349,  818,  819,  820,  114,  821,  822,  350,  121,  348,
   16,  349,   50,  161,   30,  813,   99,  814,  350,  807,
  808,  809,  810,  811,  812,-32766,  787,   39,  125,  162,
  538,  788,  540,  539,  541,  405,  542,   95,   41,   41,
  833,  543,  544,  406,   66,  545,  838,  839,  837,  416,
  828,  830,  832,  834,  835,  836,  910,  911,  912,  913,
  914,  915,  916,  917,  918,  919,  920,  921,  922,   60,
  923, -361,  924,  925,  926,  934,  936,  935, -361,  946,
  947,  948,  950,  952,    5,  761,  762,   80,  944,  945,
   39,  578,  122,  116, 1022,  546,   41,  163,    0,  430,
  547,  320,  549,  548,  113,   39,  321,  937,  938,  939,
   41,  940,  941,  537,  528,  133,  134,  135,  852,  536,
  274,  932,   39,  933,  107,   19,  927,  928,  929,  930,
  931,  778,  998,    4,  114,  108,  113,  942,  943,  369,
  110,  385,   50,   48,   30,   27,  954,  408,   49,  386,
   28,  -74,  959,  960,  958,  -75,  949,  951,  953,  955,
  956,  957,  876,  877,  878,  879,  880,  881,  882,  883,
  884,  885,  886,  887,  888,   80,  889,   96,  159,  891,
  892,  900,  902,  901,  100,  102,  142,  143,  144,  566,
  136,  137,-32766,-32766, 1039,  985,  451,  452,   41,  501,
   39,  453, 1039,  326,  131,  132,  853,  293,   39,   41,
  235,   45,  107,  394,  395,  396,  161,  414,  907,  121,
 -103,   29,   79,  186,  251,   98,  606,  898,  420,  899,
   80,-32766,  893,  894,  895,  896,  897,-32766,  415,    4,
  115,  108,  140,  400,  909,   41,  634,-32766,   51,   48,
   31,   27,-32766,   41,  141,   59,  842,   38,  785,  315,
  416,  852,  323,  786,-32766,-32766, -391,  107,-32766,-32766,
  876,  877,  878,  879,  880,  881,  882,  883,  884,  885,
  886,  887,  888,  292,  889,  563,  159,  891,  892,  900,
  902,  901,  404,  480,   41,  482, -103,-32766,   39,   41,
-32766,-32766,  785, -390,-32766,-32766,-32766,  786,  161,   42,
-32766,   45,  138,  139,  149,  150,  151,  152,   41,  378,
  126,  394,  395,  396,  127,  414,  907,  121,  119,  345,
   79,  145,  845,-32766,  308,  898,  250,  899,  307,-32766,
  893,  894,  895,  896,  897,-32766,  415,  564,  567,  292,
  847,  400,  909,   41,  863,  310, -397,  608,  560,  607,
-32766,  423,  383,   59,  309,  483,  478,  446,  416,  293,
  274,  201,-32766,-32766,  421,  418,-32766,-32766,  876,  877,
  878,  879,  880,  881,  882,  883,  884,  885,  886,  887,
  888,  384,  889,  461,  159,  891,  892,  900,  902,  901,
  485,  673, 1009,  750,  784,  101,  782,  658,-32766,-32766,
  638,  561,  305,    7,    6,    5,   41,   38,   39,   40,
   18,  756,  755,    0,  487,  472,    0,  636, 1026,  394,
  395,  396, 1025,  414,  907,  121,  840,  843,   79,  961,
  748, 1007,  671,  898, -393,  899,   74,-32766,  893,  894,
  895,  896,  897,-32766,  415,   68,   67,  460,  290,  400,
  909,   41,  865,  286,   62,  605,  597,  200,-32766,  598,
  600,   59,  969,  527,  596,  594,  416,  609,  599,   75,
-32766,-32766,   73,   72,-32766,-32766,  167,  390,  877,  391,
   10,  392,  881,  311,  883,  884,  233,  234,  393,  106,
  351,  889,  352,  159,  230,  231,  312,   54,   61,  297,
   71,   70,  576,  968,  595,  128,  130,   53,   43,  112,
  218,  454,  232,  109,    0, -392, -389,   44,   55,   56,
   57,  123,  229,  236,  238,  691,  579,  510,  394,  395,
  396, -394,  265,  907,  121,   97,   94,   79,   78,  299,
  300,  353,  397,  355,  398,  357,   77,  266,  267,   35,
   36,   37,  202,  399,  209,  216,   76,  203,  400,  909,
  199,  554,  450,  422,  380,  379,  -99,  239,  217,  215,
   59,  214,  213,  212,  211,  249,  876,  877,  878,  879,
  880,  881,  882,  883,  884,  885,  886,  887,  888,  210,
  889,  208,  159,  891,  892,  900,  902,  901,  207,  206,
  205,  204,   52,  844,   20,  676,-32766,-32766,   21,  324,
  489,  616,  777,   17, 1030, 1028,  674,  776,  683,  591,
  639, 1011,  751,  967,  841,  779,  962,  394,  395,  396,
  499,  414,  907,  121,  486,  471,   79,  468,  346,  344,
  343,  898,  342,  899,  341,-32766,  893,  894,  895,  896,
  897,-32766,  415,  340,  339,  338,  337,  400,  909,   41,
  336,  334,  332,  331,  330,   24,-32766,   23,   22,   59,
    0,    3,    2,    0,  416,    0,  129,    0,-32766,-32766,
    0,    0,-32766,-32766,  876,  877,  878,  879,  880,  881,
  882,  883,  884,  885,  886,  887,  888,    0,  889,    0,
  159,  891,  892,  900,  902,  901,    0,    0,    0,    0,
    0,    0,    0,    0,-32766,-32766,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  394,  395,  396,    0,  414,
  907,    0,    0,    0,   79,    0,    0,    0,    0,  898,
    0,  899,    0,-32766,  893,  894,  895,  896,  897,-32766,
  415,    0,    0,    0,    0,  400,  909,   41,    0,    0,
    0,    0,    0,    0,-32766,    0,    0,   59,    0,    0,
    0,    0,-32766,    0,    0,    0,-32766,-32766,    0,    0,
-32766,-32766,  167,  347,    0,  348,   16,  349,    0,  296,
    0,    0,  245,  246,  350,  103,  351,    0,  352,    0,
  227,  228,  507,   64,  104,  297,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  252,    0,
  121,    0,    0,    0,    0,  299,  300,  353,  354,  355,
  356,  357,    0,  253,  254,   32,   33,   34,    0,  359,
    0,    0,    0,    0,    0,    0,    0,  554,    0,    0,
    0,    0,  -99,  167,  347,    0,  348,   16,  349,    0,
  296,  249,    0,  245,  246,  350,  103,  351,    0,  352,
    0,  227,  228,  507,   64,  104,  297,    0,    0,    0,
    0,    0,    0,    0,  167,  347,    0,  348,   16,  349,
    0,  296,    0,    0,  245,  246,  350,  103,  351,    0,
  352,    0,  227,  228,  507,   64,  104,  297,    0,  252,
    0,  124,    0,    0,    0,    0,  299,  300,  353,  354,
  355,  356,  357,    0,  253,  254,   32,   33,   34,    0,
  359,    0,    0,    0,    0,    0,    0,    0,  757,    0,
  252,    0,  120,  -99,    0,    0,    8,  299,  300,  353,
  354,  355,  356,  357,    0,  253,  254,   32,   33,   34,
    0,  359,    0,    0,    0,    0,    0,    0,    0,  757,
    0,    0,    0,    0,  -99,  167,  347,    8,  348,   16,
  349,    0,  296,    0,    0,  245,  246,  350,  103,  351,
    0,  352,    0,  227,  228,  507,   64,  104,  297,    0,
    0,    0,    0,    0,    0,   -1,  167,  347,    0,  348,
   16,  349,    0,  296,    0,    0,  245,  246,  350,  103,
  351,    0,  352,    0,  227,  228,  507,   64,  104,  297,
    0,  252,    0,    0,    0,    0,    0,    0,  299,  300,
  353,  354,  355,  356,  357,    0,  253,  254,   32,   33,
   34,    0,  359,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  252,    0,    0,  -99,    0,    0, -368,  299,
  300,  353,  354,  355,  356,  357,    0,  253,  254,   32,
   33,   34,    0,  359,    0,    0,    0,  167,  347,    0,
  348,   16,  349,    0,  296,    0,  -99,  245,  246,  350,
  103,  351,    0,  352,    0,  227,  228,  507,   64,  104,
  297,    0,    0,    0,    0,  167,  347,    0,  348,   16,
  349,    0,  296,    0,    0,  245,  246,  350,  103,  351,
    0,  352,    0,  227,  228,  507,   64,  104,  297,    0,
    0,    0,    0,  252,    0,    0,    0,    0,    0,    0,
  299,  300,  353,  354,  355,  356,  357,    0,  253,  254,
   32,   33,   34,    0,  359,    0,    0,    0,    0,    0,
    0,  252,  760,    0,    0,    0,    0,  -99,  299,  300,
  353,  354,  355,  356,  357,    0,  253,  254,   32,   33,
   34,    0,  359,    0,    0,    0,    0,    0,    0,    0,
  758,    0,    0,  167,  347,  -99,  348,   16,  349,    0,
  296,    0,    0,  245,  246,  350,  103,  351,    0,  352,
    0,  227,  228,  507,   64,  104,  297,    0,    0,    0,
    0,  167,  347,    0,  348,   16,  349,    0,  296,    0,
    0,  245,  246,  350,  103,  351,    0,  352,    0,  227,
  228,  507,   64,  104,  297,    0,    0,    0,    0,  252,
    0,    0,    0,    0,    0,    0,  299,  300,  353,  354,
  355,  356,  357,    0,  253,  254,   32,   33,   34,    0,
  359,    0,    0,    0,    0,    0,    0,  252,  559,    0,
    0,    0,    0,  -99,  299,  300,  353,  354,  355,  356,
  357,    0,  253,  254,   32,   33,   34,    0,  359,    0,
    0,    0,    0,    0,    0,    0,  558,    0,    0,  167,
  347,  -99,  348,   16,  349,    0,  296,    0,    0,  245,
  246,  350,  103,  351,    0,  352,    0,  227,  228,  507,
   64,  104,  297,    0,    0,    0,    0,  167,  347,    0,
  348,   16,  349,    0,  296,    0,    0,  245,  246,  350,
  103,  351,    0,  352,    0,  227,  228,  507,   64,  104,
  297,    0,    0,    0,    0,  252,    0,    0,    0,    0,
    0,    0,  299,  300,  353,  354,  355,  356,  357,    0,
  253,  254,   32,   33,   34,    0,  359,    0,    0,    0,
    0,    0,    0,  252,  557,    0,    0,    0,    0,  -99,
  299,  300,  353,  354,  355,  356,  357,    0,  253,  254,
   32,   33,   34,    0,  359,    0,    0,    0,    0,    0,
    0,    0,  556,    0,    0,  167,  347,  -99,  348,   16,
  349,    0,  296,    0,    0,  245,  246,  350,  103,  351,
    0,  352,    0,  227,  228,  507,   64,  104,  297,    0,
    0,    0,    0,  167,  347,    0,  348,   16,  349,    0,
  296,    0,    0,  245,  246,  350,  103,  351,    0,  352,
    0,  227,  228,  507,   64,  104,  297,    0,    0,    0,
    0,  252,    0,    0,    0,    0,    0,    0,  299,  300,
  353,  354,  355,  356,  357,    0,  253,  254,   32,   33,
   34,    0,  359,    0,    0,    0,    0,    0,    0,  252,
  555,    0,    0,    0,    0,  -99,  299,  300,  353,  354,
  355,  356,  357,    0,  253,  254,   32,   33,   34,    0,
  359,    0,    0,    0,    0,    0,    0,    0,  554,    0,
    0,  167,  347,  -99,  348,   16,  349,    0,  296,    0,
    0,  245,  246,  350,  103,  351,    0,  352,    0,  227,
  228,  507,   64,  104,  297,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  105,    0,    0,    0,  158,    0,
    0,    0,    0,    0,    0,    0,    0,  252,    0,    0,
    0,    0,  153,  154,  299,  300,  353,  354,  355,  356,
  357,  508,  253,  254,   32,   33,   34,    0,  359,    0,
    0,    0,    0,  766,  767,  768,  759,  372,    0,    0,
    0,  -99,    0,  298,    0,    0,    0,    0,    0,    0,
    0,  985,  373,  374,    0,    0,    0,  358,  785,    0,
  769,  765,  763,  786,    0,    1,    0,   45,    0,  764,
    0,    0,  155,    0,    0,   58,    0,   25,    0,    0,
  248,    0,  301,    0,  156,  146,  509,    0,  147,  148,
   26,  167,  347,    0,  348,   16,  349,    0,  296,    0,
    0,  245,  246,  350,  103,  351,    0,  352,    0,  227,
  228,  507,   64,  104,  297,-32766,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,-32766,-32766,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  252,  160,    0,
    0,    0,    0,    0,  299,  300,  353,  354,  355,  356,
  357,    0,  253,  254,   32,   33,   34,    0,  359,    0,
    0,    0,-32766,-32766,-32766,    0,    0,    0,-32766,    0,
    0,  -99,    0,  680,  681,  682,   41,    0,    0,    0,
    0,    0,    0,-32766,    0,    0,    0,    0,    0,    0,
    0,-32766,    0,    0,    0,-32766,-32766,    0,  785,-32766,
-32766,  679,  677,  786,    0,    0,    0,    0,    0,  678,
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
 1064, 1524, 1320, 1292, 1640, 1176, 1780, 1780, 1780, 1780,
 1780, 1780, 1780, 1780, 1780,  372,  370,  369,  376,  373,
  367,  368,  104,  104,  104,  104,  104,  104,  318,  210,
  426,  634,  742,  742,   55,  218,   75,  163,  165,  165,
  165,  165,    3,  173,  222,   87,   87,   87,  263,   70,
   -8,  259,    4,  264,  382,  382,  382,  383,  383,  383,
  382,  382,  382,  382,  383,  382,  381,  381,  381,  383,
  383,  383,  383,  383,  383,  383,  383,  383,  383,  383,
  383,  383,  383,  383,  381,  383,  383,  381,  381,  383,
  381,  383,  383,  381,  381,  381,  381,  381,  381,  384,
  381,  381,  381,  381,  381,  381,  333,  333,  333,  333,
  333,   61,   61,   61,   61,  283,  283,  283,  283,  283,
  283,  283,  283,  283,  283,  283,  283,  283,  283,  283,
  283,  283,  283,  283,  283,  283,  283,  283,  283,  283,
  283,  283,  283, 1791, 1791, 1791, 1791, 1791, 1791, 1791,
 1791,  174,  174,  174,   47,   29,  342,   78,  576,  402,
  389,  569,  404,  403,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3, 1820, 1820, 1820,  204,
   85,  -33,   98,   98,   98,   98,  335,  335,  335,  324,
  324,  324,  324,  324,  324,  324,  324,  324,  324,  324,
  324,  324,  324,  324,  324,  324,  324,  324,  324,   49,
   97,   97,   97,  138,  138,  138,  274,  274,  274,   44,
  274,  274,  274,  255,  179,   73,   73,   73,   73,   73,
  203,  131,  131,  131,  194,  321,  341,  250,  517,  519,
  230,  520,  350,  334,  363,   41,  229,  328,  200,  313,
  305,  -60,  472,  431,  185,  350,  334,  363,   35,  339,
  577,  374,  470,  573,   -1,  229,  328,  328,  328,  328,
  328,  200,  200,  313,  469,  575,  253,  574,  568,  572,
  157,  187,  187,  187,  187,  187,  380,  331,  529,  330,
  330,  560,  489,  300,  489,  347,  529,  522,  522,  380,
  380,  380,  482,  475,  529,  527,  302,  478,  493,  493,
  388,  388,  380,  380,  380,  489,  491,  532,  380,  380,
  380,  380,  380,  491,  380,  532,  380,  380,  380,  380,
  380,  380,  380,  380,  380,  380,  380,  521,  511,  567,
  503,  492,  377,  437,  310,  306,  336,  327,  326,  488,
  148,  436,  340,  343,  467,  637,  466,  345,  193,  501,
  434,  433,  530,  525,  422,  416,  415,  480,  346,  528,
  332,  379,  378,  566,  565,  401,  590,  564,  563,  556,
  521,  511,  567,  503,  481,  400,  497,  310,  336,  483,
  312,  484,  399,  421,  589,  398,  588,  429,  500,  268,
  198,  194,  473,  425,  530,  485,  539,  554,  423,  424,
  329,  417,  364,  587,  490,  628,  477,  627,  626,  386,
  601,  314,  421,  599,  322,  340,  487,  343,  467,  637,
  466,  345,  345,  345,  586,  474,  538,  227,  416,  442,
  338,  537,  536,  534,  337,  375,  365,  365,  365,  428,
  371,  598,  585,  625,  624,  620,  619,  618,  486,  636,
  584,  319,  394,  387,  387,  617,  172,  441,  583,  635,
  582,  533,  315,  418,  406,  432,  581,  390,  608,  471,
  438,  632,  606,  604,  603,  594,  580,  579,  631,  320,
  602,  316,  365,  385,  629,  385,  578,    0,    0,    0,
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
    0,    0,    0,    0,    0,  -60,  187,  187,    0,  380,
  380,    0,  380,  530,  525,  422,    0,    0,    0,    0,
    0,    0,    0,  479,  479,    0,  530,  525,  422,    0,
  554,  476,  476,  476,  476,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  479,  476,    0,  476,  476,
  476
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 290

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  384,  385,  386,32767,32767,
32767,32767,32767,  338,32767,32767,32767,32767,  520,  520,
  520,  520,32767,32767,  101,32767,32767,32767,32767,32767,
32767,   91,  346,32767,  101,  101,  101,32767,32767,32767,
  101,  101,  101,  101,32767,  101,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,   91,32767,  377,32767,32767,32767,
32767,   93,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  221,  223,32767,32767,32767,32767,32767,32767,  379,
32767,32767,32767,32767,32767,  103,32767,32767,32767,32767,
32767,32767,32767,32767,  351,   90,  343,  349,  344,  526,
  353,  362,  347,   92,  350,  363,32767,  148,  150,  233,
32767,  141,  231,  232,  229,  228,  122,  527,  364,  501,
  501,  501,  501,  501,  501,  501,  501,  501,  501,  501,
  501,  501,  501,  501,  501,  501,  501,  501,32767,32767,
  142,  149,  151,  197,  198,  199,32767,32767,32767,32767,
  380,  381,32767,  374,  375,32767,32767,32767,32767,32767,
  518,  209,  211,  210,  461,  103,  103,  174,32767,32767,
32767,32767,32767,32767,32767,  184,  195,  200,  206,  216,
  218,  461,32767,32767,32767,  395,  382,  383,  225,32767,
32767,32767,32767,32767,32767,  196,  202,  204,  205,  201,
  203,  207,  208,  217,32767,32767,32767,32767,32767,32767,
32767,  103,  103,  103,  103,  103,32767,32767,32767,32767,
32767,  335,  475,   77,  475,32767,32767,  499,  499,32767,
32767,  371,  529,  337,32767,   79,   81,  337,  493,  493,
  513,  513,32767,32767,32767,  475,  179,  516,32767,32767,
32767,32767,32767,  179,32767,  516,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  274,
32767,32767,  185,  187,  189,  191,  193,  212,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  102,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  365,  367,  369,  376,  255,  256,  257,  387,  388,  274,
  275,32767,32767,  339,32767,32767,32767,32767,32767,32767,
  261,  259,32767,32767,  395,  274,32767,32767,   51,32767,
32767,32767,32767,32767,  505,32767,  502,32767,32767,32767,
32767,32767,  340,32767,32767,  186,32767,  188,  190,  192,
  194,  213,  214,  215,32767,  521,32767,32767,   75,32767,
32767,32767,32767,32767,  338,32767,  465,  466,  463,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  268,32767,
32767,32767,32767,  512,  510,32767,   62,32767,32767,32767,
32767,32767,32767,   54,  462,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  464,  481,32767,32767,32767,  529,  455,  455,
  529
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  181,  176,  176,  176,  179,  179,  179,  179,  177,  179,
  174,  181,  181,  181,  168,  168,  867,  175,  182,  171,
  174,  174,  174,  870,  411,  868,  174,  174,  174,  174,
  434,  174,  177,  177,  177,  689,  689,  689,  993,  993,
  688,  688,  688,  992,  503,  429,  436,  693,  505,  432,
  177,  457,  458,  177,  177,  435,  177,  502, 1035,  164,
  175,  166,  164,  178,  169,  180,  170,  183,  184,  185,
  172,  173,  437,  302,  302,  302,  302,  302,  302,  302,
  302,  302,  302,  302,  302,  302,  302,  302,  302,  302,
  302,  302,  302,  302,  302,  302,  302,  302,  635,  670,
  192,  193,  194,  195,  635,  635,  635,  572,  753,  438,
  417,  753,  753,  753,  753,  741,  737,  738,  730,  731,
  733,  735,  410,  439,  268,  470,  496,  506,  670,  670,
  670,  481,  440,  675,  675,  675,  686,  647,  689,  427,
  428,  433,  462,  463,  464,  465,  466,  467,  469,  475,
  479,  488,  492,  493,  494,  495,  500,  275,  675,  675,
  675,  872,  872,  872,  872,  872,  872,  994,  994,  283,
  668,  424,  424,  424,  424,  424,  424,  424,  424,  424,
  424,  424,  424,  424,  424,  424,  424,  424,  424,  424,
  424,  783,  749,  637,  657,  672, 1008, 1015,  244,  261,
  261,  447,  261,  261,  261,  198,  441,  442,  443,  197,
  197,  197,  197,  964,  197,  303,  198,  198,  198,  190,
  190,  963, 1020,  276,  277,  278,  279,  280, 1002, 1003,
  303,  654,  654,  654,  325,  325,  325, 1006,  780,  780,
  684,  589,  593,  577,  220,  221,  222, 1000, 1001,  988,
  989,  990,  646,  982,  333,  983,  995,  996,  997,  991,
  984,  663,  664,  665,  667,  666,  655,  655,  655, 1018,
 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018,
 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018, 1018,   14,
   14,  971,  572,   12,   13,   15,  448,  375,  375,  644,
  375,  375,  375,  455, 1019, 1019, 1019, 1019, 1019, 1019,
 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019, 1019,
 1019, 1019, 1019, 1019,  388,  389,  382,  388,  389,  224,
  225,  376,  376,  376,  632,  376,  376,  376,  281,  282,
  319,  632,  632,  632,  987,  327,  335,  497,  632,  656,
  656,  656,  474,  632,  632,  632,  632,  632,  632,  632,
  632,  632,  632,  632,  632,  632,  632,  632,  618,  632,
  632,  611,  329,  632,  118,  632,  632,  754,  640, 1017,
  754,  754,  754,  754,  640,  640,  640,  871,  856,  621,
  622,  623,  624,  625,  626,  627,  628,  629,  630,  631,
  619,  620,  513,  618, 1034,  242,  243,  859,  314,  979,
 1036,  514,  368,  516,  516,  516,  516,  516,  368,  476,
  575,  574,  583,  584,  582,  581,  580,  270,  271,  273,
  157,  295,  449,  650,  649,    0,  477,  490,  491,  498,
  371,  504,  284,    0,  263,  285,    0,  263,  287,  288,
    0,  289,  371,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  407,  412,  413,
  419,  459
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 502

static char yygcheck[] = {
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   73,   37,   37,   37,
   37,   37,   37,   74,   75,   74,   37,   37,   37,   37,
   67,   37,   37,   37,   37,    7,    7,    7,    7,    7,
   41,   41,   41,   41,   41,   41,   41,   41,   41,   68,
   37,   82,   82,   37,   37,   44,   37,   82,  101,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   45,   83,   83,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,   60,   60,
   58,   58,   58,   58,   60,   60,   60,   35,    7,   46,
  102,    7,    7,    7,    7,   56,   56,   56,   56,   56,
   56,   56,   63,   47,   57,   99,   99,   99,   60,   60,
   60,  102,   48,   75,   75,   75,  116,  116,    7,   94,
   94,   94,   94,   94,   94,   94,   94,   94,   94,   94,
   94,   94,   94,   94,   94,   94,   94,   49,   75,   75,
   75,   57,   57,   57,   57,   57,   57,    7,    7,   55,
    7,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
   75,   59,   59,   59,   59,   59,   59,   96,   75,   75,
   75,   19,   75,   75,   75,   39,   54,   54,   54,   39,
   39,   39,   39,   66,   39,    7,   39,   39,   39,   39,
   39,   66,   75,   51,   51,   51,   51,   51,    7,    7,
    7,   63,   63,   63,   83,   83,   83,   61,   61,   61,
   61,    7,    7,    7,  112,  112,  112,    7,    7,    7,
    7,    7,  117,    7,   32,    7,    7,    7,    7,    7,
    7,    7,    7,    7,    7,    7,   64,   64,   64,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,    3,
    3,   81,   35,    3,    3,    3,   63,   63,   63,  109,
   63,   63,   63,  118,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   77,   77,    9,   77,   77,   50,
   50,   64,   64,   64,  107,   64,   64,   64,   52,   52,
   92,  107,  107,  107,  103,  103,  103,  103,  107,   98,
   98,   98,  104,  107,  107,  107,  107,  107,  107,  107,
  107,  107,  107,  107,  107,  107,  107,  107,   38,  107,
  107,   31,   90,  107,  119,  107,  107,   98,   98,  105,
   98,   98,   98,   98,   98,   98,   98,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,    4,   38,   38,   53,   53,   38,  121,   38,
   38,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,   70,   70,   70,
  106,   40,   40,  111,  111,   -1,   40,   40,   40,   40,
   31,   40,   80,   -1,   80,   70,   -1,   80,   70,   70,
   -1,   70,   31,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   31,   31,   31,
   31,   31
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  287,  402,    0,    0,  -81,    0,   26,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -25,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  206,   35,    0,    0,   63,    0,  -44,  308,  161,
  366,  -76,    0,    0,  -70,  -54,  -18,   -5,    3,   27,
  198,   90,  200,  265,   64,   24,  -31,  123,  -53,  165,
  -92,   80,    0,   70,  105,    0,  -93,  -16,    2,    0,
  351,    0,    0,  -27,  -32,  -28,    0,  291,    0,    0,
  216,   59,  -17,   73,    0,    0,    0,    0,    0,    0,
   53,    0,   32,    0,  -61,    0,  -21,    0,  188,   76,
    0,    5, -194,  108,   31,   44,  -80,  274,    0,   52,
    0,  271,   58,    0,    0,    0,   19,   33,  -14,   41,
    0, -101
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  360,    9,   11,  515,  518,  517,  519,  520,  381,
  521,  317,  534,  522,  550,  551,  552,  523,  553,  409,
  524,  316,  322,  587,  529,  530,  291,  531,  532,  264,
  533,  370,  615,  535,  525,  526,  361,  165,  978,  196,
  294,  641,  692,  255,  362,  363,  364,  365,  366,  256,
  223,  257,  258,  241,  367,  259,  260,  736,  189,  781,
  747,  746,  771,  772,  773,  774,  965,  402,  403,   47,
  272,  377,  313,  866,  869,  770,  401,  387,  999,  568,
  262,  970,  456,  304,  569,  980,  694,  981,  570,  571,
  328,  240,  318, 1005,  425,  426, 1014,  752,  775,  444,
  445, 1033,  269,  745,  473,  484,   65,  617,  247,  643,
  219,  648,  191,  651,  669,  642,  645,  687,  431,  117,
   46,  306
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
  107,  107,  108,  108,  109,  109,  109,  110,  110,  110,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  113,  113,  113,  113,  113,  113,  112,  112,
  112,  112,  112,  112,  114,  114,  114,  114,  114,  114,
  114,  114,  114,  114,  115,  115,  116,  116,  117,  119,
  119,   41,   41,   42,   42,   43,   43,   44,   44,   45,
   45,   46,   46,   47,   47,   48,   48,   49,   49,   49,
   50,   50,   50,   50,   50,   50,   51,   51,   51,   52,
   52,   52,   53,   53,   53,   53,   54,   54,   55,   55,
   55,   55,   55,   55,   55,   56,   56,   56,   56,   56,
   56,   56,   56,   57,   57,   58,   58,   58,   58,   58,
   58,   58,   97,   97,   98,   98,   98,   98,   98,   98,
   60,   60,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   75,   75,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   63,   63,   62,   62,  120,   64,  118,  118,   67,
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
   78,   78,   65,   65,   65,  121,   66,   79,   79,   80,
   80,   81,   81,   81,   81,   81,   81,   82,   82,   84,
   84,   85,   85,   85,   83,  102,  102,   86,   86,   86,
   86,   86,   86,   86,   87,   87,   87,   77,   77,   88,
   88,   89,   89,   90,   90,   91,   91,   91,   91,   92,
   92,   94,   94,   95,   95,   96,   96,   96,   96,   96,
  103,  103,  103,  104,  104,  104,  105,  105,   93,   93,
   99,   99,  100,  100,  100,  100,  101,  101,  101,  106
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
    2,    3,    5,    5,    5,    6,    6,    2,    1,    2,
    4,    3,    3,    4,    1,    3,    1,    1,    1,    1,
    1,    1,    3,    2,    0,    3,    1,    1,    1,    0,
    1,    1,    5,    1,    1,    1,    3,    1,    3,    1,
    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,
    1,    3,    3,    3,    3,    3,    1,    3,    3,    1,
    3,    3,    1,    3,    3,    3,    1,    3,    1,    3,
    3,    2,    3,    2,    3,    1,    2,    2,    2,    2,
    2,    2,    2,    1,    3,    1,    2,    4,    3,    3,
    4,    2,    1,    1,    4,    8,    6,    7,    7,    8,
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
    1,    6,    6,    7,    1,    0,    2,    5,    5,    5,
    6,    6,    6,    2,    6,    6,    6,    1,    1,    5,
    5,    3,    3,    0,    4,    1,    4,    3,    3,    0,
    3,    0,    1,    1,    3,    1,    4,    1,    1,    2,
    2,    1,    2,    0,    2,    3,    0,    3,    0,    3,
    0,    1,    1,    2,    3,    4,    1,    1,    1,    0
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
#line 178 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 183 "src/kinx.y"
{ kx_ast_root = yyval.obj = (YYASP(2-2).obj == NULL ? YYASP(1-2).obj : kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 5:
#line 188 "src/kinx.y"
{ yyval.obj = (YYASP(2-2).obj == NULL ? YYASP(1-2).obj : kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 16:
#line 205 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strinfo.name, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 17:
#line 206 "src/kinx.y"
{ yyerrok; yyval.obj = NULL; } break;
        case 25:
#line 217 "src/kinx.y"
{                       yyerrok; yyval.obj = NULL; } break;
        case 26:
#line 218 "src/kinx.y"
{ yy_restart(LBBR);     yyerrok; yyval.obj = NULL; } break;
        case 27:
#line 219 "src/kinx.y"
{ yy_restart(IF);       yyerrok; yyval.obj = NULL; } break;
        case 28:
#line 220 "src/kinx.y"
{ yy_restart(DO);       yyerrok; yyval.obj = NULL; } break;
        case 29:
#line 221 "src/kinx.y"
{ yy_restart(WHILE);    yyerrok; yyval.obj = NULL; } break;
        case 30:
#line 222 "src/kinx.y"
{ yy_restart(FOR);      yyerrok; yyval.obj = NULL; } break;
        case 31:
#line 223 "src/kinx.y"
{ yy_restart(TRY);      yyerrok; yyval.obj = NULL; } break;
        case 32:
#line 224 "src/kinx.y"
{ yy_restart(SWITCH);   yyerrok; yyval.obj = NULL; } break;
        case 33:
#line 225 "src/kinx.y"
{ yy_restart(CASE);     yyerrok; yyval.obj = NULL; } break;
        case 34:
#line 226 "src/kinx.y"
{ yy_restart(ENUM);     yyerrok; yyval.obj = NULL; } break;
        case 35:
#line 227 "src/kinx.y"
{ yy_restart(CLASS);    yyerrok; yyval.obj = NULL; } break;
        case 36:
#line 228 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; yyval.obj = NULL; } break;
        case 37:
#line 229 "src/kinx.y"
{ yy_restart(PRIVATE);  yyerrok; yyval.obj = NULL; } break;
        case 38:
#line 230 "src/kinx.y"
{ yy_restart(PUBLIC);   yyerrok; yyval.obj = NULL; } break;
        case 43:
#line 241 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 44:
#line 242 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 45:
#line 246 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 247 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 47:
#line 248 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 249 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 49:
#line 253 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strinfo.name); } break;
        case 50:
#line 257 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 51:
#line 261 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strinfo.name); } break;
        case 52:
#line 262 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strinfo.name, YYASP(3-3).intval); } break;
        case 53:
#line 263 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strinfo.name, -YYASP(4-4).intval); } break;
        case 54:
#line 264 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strinfo.name)); } break;
        case 55:
#line 265 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strinfo.name, YYASP(5-5).intval)); } break;
        case 56:
#line 266 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strinfo.name, -YYASP(6-6).intval)); } break;
        case 61:
#line 277 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 62:
#line 281 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 63:
#line 282 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 64:
#line 286 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 65:
#line 290 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 66:
#line 294 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 298 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 299 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 304 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 70:
#line 311 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 71:
#line 318 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 72:
#line 325 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 73:
#line 327 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 76:
#line 336 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 77:
#line 340 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 78:
#line 341 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 79:
#line 345 "src/kinx.y"
{ yyval.obj = kx_gen_var_object("_e", KX_UNKNOWN_T); } break;
        case 80:
#line 346 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(2-3).strinfo.name, KX_UNKNOWN_T, YYASP(2-3).strinfo.line, YYASP(2-3).strinfo.pos1, YYASP(2-3).strinfo.pos2); } break;
        case 81:
#line 350 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 82:
#line 351 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 83:
#line 355 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 84:
#line 356 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strinfo.name)); } break;
        case 85:
#line 357 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 86:
#line 358 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strinfo.name)); } break;
        case 87:
#line 362 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 88:
#line 363 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 89:
#line 367 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 90:
#line 371 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 91:
#line 372 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 92:
#line 373 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 93:
#line 374 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 94:
#line 378 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 95:
#line 382 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 96:
#line 386 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_OBJ_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2), NULL); } break;
        case 97:
#line 387 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object_line_pos(YYASP(3-3).strinfo.name, KX_OBJ_T, YYASP(3-3).strinfo.line, YYASP(3-3).strinfo.pos1, YYASP(3-3).strinfo.pos2), NULL); } break;
        case 98:
#line 391 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 99:
#line 395 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 100:
#line 396 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 101:
#line 400 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 103:
#line 405 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 105:
#line 410 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 107:
#line 415 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 108:
#line 416 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 109:
#line 417 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 110:
#line 418 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 111:
#line 419 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 420 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 421 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 423 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 425 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 119:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 120:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 123:
#line 437 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 124:
#line 438 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 125:
#line 439 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 126:
#line 440 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 127:
#line 441 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 128:
#line 442 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 129:
#line 443 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 131:
#line 448 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 133:
#line 453 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 134:
#line 457 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-4).obj, YYASP(4-4).obj, NULL); } break;
        case 135:
#line 458 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-3).obj, YYASP(3-3).obj, NULL); } break;
        case 136:
#line 459 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 138:
#line 464 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 139:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 142:
#line 471 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 146:
#line 475 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 147:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 148:
#line 477 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 149:
#line 478 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 150:
#line 479 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 151:
#line 480 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 152:
#line 485 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 153:
#line 486 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 154:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 155:
#line 488 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 156:
#line 489 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 157:
#line 490 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 159:
#line 495 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 160:
#line 496 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 161:
#line 497 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 162:
#line 498 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 163:
#line 499 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 165:
#line 504 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 166:
#line 505 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 167:
#line 506 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 168:
#line 507 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 169:
#line 508 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 170:
#line 509 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 171:
#line 510 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 172:
#line 511 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 173:
#line 512 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 174:
#line 516 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 175:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 178:
#line 526 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 182:
#line 536 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 186:
#line 546 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 188:
#line 551 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 190:
#line 556 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 192:
#line 561 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 194:
#line 566 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 571 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 199:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 201:
#line 582 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 202:
#line 583 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 203:
#line 584 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 204:
#line 585 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 205:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 207:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 208:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 210:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 211:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 213:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 214:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 215:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 217:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 219:
#line 615 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 220:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 221:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 222:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 223:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 224:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 226:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 227:
#line 626 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 228:
#line 627 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 229:
#line 628 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 230:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 231:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 232:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 234:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype); } break;
        case 236:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 237:
#line 642 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 238:
#line 643 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 239:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 240:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 241:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 242:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 244:
#line 655 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 245:
#line 656 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 246:
#line 657 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 247:
#line 658 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 248:
#line 659 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 249:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 250:
#line 664 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 251:
#line 665 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 252:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 253:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 254:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 255:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 256:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 257:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 258:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 265:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 266:
#line 683 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 267:
#line 684 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 268:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 269:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 270:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_prop_func_object(YYASP(2-2).obj); } break;
        case 271:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_typeprop_func_object(YYASP(2-2).intval); } break;
        case 272:
#line 689 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 273:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 274:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_var_object_line_pos(YYASP(1-1).strinfo.name, KX_UNKNOWN_T, YYASP(1-1).strinfo.line, YYASP(1-1).strinfo.pos1, YYASP(1-1).strinfo.pos2); } break;
        case 275:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(kx_gen_typestr_object(YYASP(1-1).intval), KX_UNKNOWN_T); } break;
        case 276:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strinfo.name); } break;
        case 277:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 278:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 279:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 280:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 281:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 282:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 283:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 284:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 285:
#line 708 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 286:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 287:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 288:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 289:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 290:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 291:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 292:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 293:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 294:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 295:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 296:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 297:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 298:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 299:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 300:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 301:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 302:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 303:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 304:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 305:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 306:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 307:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 308:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 309:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 310:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 311:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 312:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 313:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 314:
#line 737 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 315:
#line 738 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 316:
#line 739 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 317:
#line 740 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 318:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 319:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 320:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 321:
#line 744 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 322:
#line 745 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 323:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 324:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 325:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 326:
#line 749 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 327:
#line 750 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 328:
#line 751 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 329:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 330:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 331:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 332:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 333:
#line 762 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 334:
#line 763 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 335:
#line 767 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 336:
#line 771 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 337:
#line 775 "src/kinx.y"
{} break;
        case 339:
#line 780 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 340:
#line 781 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 341:
#line 785 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 342:
#line 786 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 344:
#line 791 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 345:
#line 792 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 346:
#line 793 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 347:
#line 794 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 348:
#line 795 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 350:
#line 800 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 352:
#line 805 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 353:
#line 806 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 354:
#line 807 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 356:
#line 812 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 357:
#line 816 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 358:
#line 817 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strinfo.name, YYASP(3-3).obj); } break;
        case 359:
#line 818 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 360:
#line 819 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 361:
#line 820 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_shorthand(YYASP(1-1).obj); } break;
        case 363:
#line 825 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; yyval.obj->optional = KXDC_CONST; } break;
        case 365:
#line 830 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 366:
#line 831 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 367:
#line 832 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 368:
#line 833 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 369:
#line 834 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 370:
#line 835 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 371:
#line 836 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 372:
#line 837 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 373:
#line 838 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 374:
#line 839 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 375:
#line 840 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 376:
#line 841 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 377:
#line 842 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 378:
#line 843 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 379:
#line 844 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 380:
#line 845 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 381:
#line 846 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 382:
#line 847 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 383:
#line 848 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 384:
#line 849 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 385:
#line 850 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 386:
#line 851 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 387:
#line 852 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 388:
#line 853 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 389:
#line 854 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 390:
#line 855 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 391:
#line 856 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 392:
#line 857 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 393:
#line 858 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 394:
#line 859 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 395:
#line 860 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 396:
#line 861 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 397:
#line 862 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 398:
#line 863 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 399:
#line 867 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 400:
#line 868 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 401:
#line 869 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 402:
#line 870 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 403:
#line 871 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 404:
#line 872 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 405:
#line 873 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 406:
#line 874 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 407:
#line 875 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 408:
#line 876 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 409:
#line 877 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 410:
#line 878 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 411:
#line 879 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 412:
#line 880 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 413:
#line 881 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 414:
#line 882 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 415:
#line 883 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 416:
#line 884 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 417:
#line 885 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 418:
#line 886 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 419:
#line 887 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 420:
#line 888 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 421:
#line 889 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 422:
#line 890 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 423:
#line 891 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 424:
#line 892 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 425:
#line 893 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 426:
#line 894 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 427:
#line 895 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 428:
#line 896 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 429:
#line 897 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 430:
#line 898 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 431:
#line 899 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 432:
#line 900 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 433:
#line 901 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 434:
#line 902 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 435:
#line 903 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 436:
#line 904 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 437:
#line 905 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 438:
#line 906 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 439:
#line 907 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 440:
#line 908 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 441:
#line 909 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 442:
#line 910 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 443:
#line 911 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 444:
#line 912 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 445:
#line 913 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 446:
#line 914 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 447:
#line 915 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 448:
#line 916 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 449:
#line 917 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 450:
#line 918 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 451:
#line 919 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 452:
#line 923 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 453:
#line 924 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 454:
#line 925 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 455:
#line 929 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 456:
#line 933 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 457:
#line 937 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 458:
#line 938 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 460:
#line 943 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 461:
#line 947 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-1).obj, NULL); } break;
        case 462:
#line 948 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 463:
#line 949 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 464:
#line 950 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).obj, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 465:
#line 951 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 466:
#line 952 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 468:
#line 957 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 469:
#line 961 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 470:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 471:
#line 966 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strinfo.name, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 472:
#line 967 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strinfo.name, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 473:
#line 968 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strinfo.name, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 474:
#line 972 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 475:
#line 976 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 476:
#line 977 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 477:
#line 981 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 478:
#line 982 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 479:
#line 983 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 480:
#line 984 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 481:
#line 985 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 482:
#line 986 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 483:
#line 987 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 484:
#line 991 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 485:
#line 992 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 486:
#line 993 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 487:
#line 997 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strinfo.name; } break;
        case 489:
#line 1002 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 490:
#line 1003 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strinfo.name, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 491:
#line 1007 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 492:
#line 1008 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strinfo.name, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 493:
#line 1012 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 494:
#line 1014 "src/kinx.y"
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
        case 496:
#line 1030 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 497:
#line 1031 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 498:
#line 1032 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 499:
#line 1036 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 500:
#line 1037 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 501:
#line 1041 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 504:
#line 1047 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 506:
#line 1052 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).obj, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 507:
#line 1053 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LARY_T); } break;
        case 508:
#line 1054 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(1-1).obj->lhs, KX_LOBJ_T); } break;
        case 509:
#line 1055 "src/kinx.y"
{ YYASP(2-2).obj->var_type = KX_SPR_T; yyval.obj = YYASP(2-2).obj; } break;
        case 510:
#line 1059 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 511:
#line 1060 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 512:
#line 1061 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strinfo.name) }; } break;
        case 513:
#line 1065 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 514:
#line 1066 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 515:
#line 1067 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 516:
#line 1071 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 517:
#line 1072 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 518:
#line 1076 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 519:
#line 1077 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 520:
#line 1081 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 523:
#line 1087 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 524:
#line 1088 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 525:
#line 1089 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 528:
#line 1095 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 529:
#line 1099 "src/kinx.y"
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
