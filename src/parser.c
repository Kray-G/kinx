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
#line 1040 "src/kinx.y"

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
  "AssignExpression_Opt : CASE AssignExpression WhenClauseList CaseElseClause",
  "AssignExpressionList_Opt : /* empty */",
  "AssignExpressionList_Opt : AssignExpressionObjList",
  "Modifier_Opt : /* empty */",
  "Modifier_Opt : IF '(' AssignExpressionList ')'",
  "CaseWhenExpression : CASE AssignExpression WhenClauseList CaseElseClause",
  "WhenClauseList : WhenClause",
  "WhenClauseList : WhenClauseList WhenClause",
  "WhenClause : WHEN ArrayItemListCoreRight Modifier_Opt Colon_Opt WhenClauseBody",
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
#define YYNONTERMS 114

static short yyaction[] = {
  736,  737,  738,  739,  740,  741,  742,  743,  744,  745,
  746,  747,  748,  750,  749,    0,  751,  752,  753,  762,
  764,  763,  350,  773,  774,  775,  777,  779,  141,  142,
  143,  350,  771,  772,  239,   69,   70,   71,   72,   73,
   74,   75,   76,   77,   78,   79,   80,   81,    4,  393,
  112,  765,  766,  767,  982,  768,  769,   30,   54,   31,
   38,  306,  179,  111,   62,  760,  307,  761,  224,  754,
  755,  756,  757,  758,  759,-32766,  735,  111,-32766,   19,
  527,  770,  529,  528,  530,  390,  531,   82,  -74,  111,
  781,  532,  533,  391,   27,  534,   32,  786,  787,  785,
  776,  778,  780,  782,  783,  784,  870,  871,  872,  873,
  874,  875,  876,  877,  878,  879,  880,  881,  882,   60,
  883,-32766,  884,  885,  886,  894,  896,  895,  416,  906,
  907,  908,  910,  912,   49,-32766,-32766,-32766,  904,  905,
  567,-32766,  329,   16,  330,  535,   48,-32766,   49,   51,
  536,  331,  538,  537,  388, -362,  120,  897,  898,  899,
   49,  900,  901,  526,  517,-32766,  132,  133,  134,  525,
  733,  892,  111,  893,  -75,  734,  887,  888,  889,  890,
  891,  115,  958,  124,  311,  709,  710,  902,  903,-32766,
-32766,  364,   51,  130,  131,  214,  914,  179,  400,  365,
-32766, -361,  102,  919,  920,  918,  909,  911,  913,  915,
  916,  917,  162,  369,  837,  370,   10,  371,  841,  297,
  843,  844,  220,  221,  372,  110,  332,  849,  333,  158,
  217,  218,  298,   66,   87,  279,  104,  139,  261,-32766,
  114,  135,  136,   49,  121,  329,   16,  330,   55,  140,
   39,   27,  119,   28,  331,-32766,  238,-32766,  308,  222,
   56,   51,   40,   26,  373,  374,  375,   90,  253,  867,
  120,   50,  552,   67,-32766,  281,  282,  334,  376,  336,
  377,  338,  475,  254,  255,   45,   46,   47,    4,  378,
  112,  287,-32766,-32766,  379,  869,-32766,  543,   54,  179,
   38,  555,  -98,  594, -103,  406,   59,  814,  816,  817,
   49,  490,  237,  836,  837,  838,  839,  840,  841,  842,
  843,  844,  845,  846,  847,  848,   49,  849,   51,  850,
  851,  852,  860,  862,  861,  813,  811,  288,  357,   33,
   83,   34,  144,  812,   86,   48,  137,  138,  125,  438,
 -103,  148,  149,  150,  151,  126,  117,  999,  793,  288,
  969,  999,  595,   49,  863,  864,  865,   49,  866,  867,
  120,  287,  549,   67,  596,  637,  703,  476,  858,  469,
  859,  432,  407,  853,  854,  855,  856,  857,  402,  398,
  556,  363,  362,  296,  868,  869,  478,  986,  295,  293,
  294,    7,  474,  728,  446,  437,  399,  409,  792,  553,
    0,    0,  400,  836,  837,  838,  839,  840,  841,  842,
  843,  844,  845,  846,  847,  848,  732,  849,  698,  158,
  851,  852,  860,  862,  861,    6,  290,    5,  273,  826,
  824,  704,  820,  979,  550,  795,  441,  633,  127,  480,
  461,    0,  967,  819,  985,  978,  788,  791,  921,  483,
  467,  442,  635,  696,  373,  374,  375,   85,  381,  867,
   65,   64,-32766,   68,   63,  445,  277,  223,  858,  586,
  859,  593,  516,  382,  383,  855,  856,  857,  583,  384,
-32766,-32766,  588,  565,  379,  869,   51,  928,  584,  790,
  582,  597, -365,  587,  800,  836,  837,  838,  839,  840,
  841,  842,  843,  844,  845,  846,  847,  848,   95,  849,
   94,  158,  851,  852,  860,  862,  861,   93,   92,-32766,
-32766,-32766,   91,  929,  585,-32766,   17,  439,  219,  113,
   61,   52,   36,   51,  116,  209,   18, -364, -363, -360,
-32766,   53,   20,  100,  103,  106,  373,  374,  375,-32766,
  381,  867,-32766,-32766,  122,   68,-32766,-32766,  180,  614,
  858,  181,  859,  568,  499,  382,  383,  855,  856,  857,
  225,  384, -368,  213,  183,  182,  379,  869,   51,  197,
  196,  195,  101,   99,   98,   97,  801,  836,  837,  838,
  839,  840,  841,  842,  843,  844,  845,  846,  847,  848,
   96,  849,   58,  158,  851,  852,  860,  862,  861,  198,
  205,  436,  408,  359,  358,  226,  208,  207,  206,  204,
  203,  202,  201,  200,  199,    0,   21,  309,  482,  604,
  726,  990,  988,  725,  818,  638,  971,  699,  373,  374,
  375,  927,  381,  867,  789,  727,  729,   68,  922,  479,
  470,  460,  858,  455,  859,  327,  326,  382,  383,  855,
  856,  857,  325,  384,  324,  323,  322,  321,  379,  869,
   51,  319,  317,  316,  315,   24,   23,   22,  800,  836,
  837,  838,  839,  840,  841,  842,  843,  844,  845,  846,
  847,  848,    3,  849,    2,  158,  851,  852,  860,  862,
  861,  162,  328,  128,  329,   16,  330,  129,  278,    0,
    0,  234,  235,  331,    0,  332,    0,  333,    0,  215,
  216,  496,   88,  109,  279,    0,    0,    0,    0,    0,
  373,  374,  375,    0,  381,  867,    0,    0,    0,   84,
    0,    0,    0,    0,  858,    0,  859,    0,    0,  382,
  383,  855,  856,  857,    0,  457,    0,  240,    0,  120,
  379,  869,   51,    0,  281,  282,  334,  335,  336,  337,
  338,    0,  241,  242,   42,   43,   44,    0,  340,    0,
    0,    0,    0,    0,    0,    0,  543,    0,    0,    0,
    0,  -98,  162,  328,    0,  329,   16,  330,    0,  278,
    0,  237,  234,  235,  331,    0,  332,    0,  333,    0,
  215,  216,  496,   88,  109,  279,    0,    0,    0,    0,
    0,    0,    0,  162,  328,    0,  329,   16,  330,    0,
  278,    0,    0,  234,  235,  331,    0,  332,    0,  333,
    0,  215,  216,  496,   88,  109,  279,    0,  240,    0,
  118,    0,    0,    0,    0,  281,  282,  334,  335,  336,
  337,  338,    0,  241,  242,   42,   43,   44,    0,  340,
    0,    0,    0,    0,    0,    0,    0,  705,    0,  240,
    0,  123,  -98,    0,    0,    8,  281,  282,  334,  335,
  336,  337,  338,    0,  241,  242,   42,   43,   44,  108,
  340,    0,    0,  157,    0,    0,    0,    0,  705,    0,
    0,    0,    0,  -98,    0,    0,    8,  152,  153,    0,
    0,    0,    0,    0,    0,    0,  497,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  714,  716,
  717,    0,  353,    0,    0,    0,    0,    0,  280,    0,
    0,    0,    0,    0,    0,    0,  945,  354,  355,    0,
    0,    0,  339,  733,    0,  718,  713,  711,  734,    0,
    1,    0,   25,    0,  712,    0,    0,  154,    0,    0,
   57,    0,   41,    0,    0,    0,  236,  283,    0,  155,
  145,  498,    0,  146,  147,   37,  162,  328,    0,  329,
   16,  330,    0,  278,    0,    0,  234,  235,  331,    0,
  332,    0,  333,    0,  215,  216,  496,   88,  109,  279,
    0,    0,    0,    0,    0,    0,   -1,  162,  328,    0,
  329,   16,  330,    0,  278,    0,    0,  234,  235,  331,
    0,  332,    0,  333,    0,  215,  216,  496,   88,  109,
  279,    0,  240,    0,    0,    0,    0,    0,    0,  281,
  282,  334,  335,  336,  337,  338,    0,  241,  242,   42,
   43,   44,    0,  340,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  240,    0,    0,  -98,    0,    0, -339,
  281,  282,  334,  335,  336,  337,  338,    0,  241,  242,
   42,   43,   44,    0,  340,    0,    0,    0,  162,  328,
    0,  329,   16,  330,    0,  278,    0,  -98,  234,  235,
  331,    0,  332,    0,  333,    0,  215,  216,  496,   88,
  109,  279,    0,    0,    0,    0,  162,  328,    0,  329,
   16,  330,    0,  278,    0,    0,  234,  235,  331,    0,
  332,    0,  333,    0,  215,  216,  496,   88,  109,  279,
    0,    0,    0,    0,  240,    0,    0,    0,    0,    0,
    0,  281,  282,  334,  335,  336,  337,  338,    0,  241,
  242,   42,   43,   44,    0,  340,    0,    0,    0,    0,
    0,    0,  240,  546,    0,    0,    0,    0,  -98,  281,
  282,  334,  335,  336,  337,  338,    0,  241,  242,   42,
   43,   44,    0,  340,    0,    0,    0,    0,    0,    0,
    0,  545,    0,    0,  162,  328,  -98,  329,   16,  330,
    0,  278,    0,    0,  234,  235,  331,    0,  332,    0,
  333,    0,  215,  216,  496,   88,  109,  279,    0,    0,
    0,    0,  162,  328,    0,  329,   16,  330,    0,  278,
    0,    0,  234,  235,  331,    0,  332,    0,  333,    0,
  215,  216,  496,   88,  109,  279,    0,    0,    0,    0,
  240,    0,    0,    0,    0,    0,    0,  281,  282,  334,
  335,  336,  337,  338,    0,  241,  242,   42,   43,   44,
    0,  340,    0,    0,    0,    0,    0,    0,  240,  544,
    0,    0,    0,    0,  -98,  281,  282,  334,  335,  336,
  337,  338,    0,  241,  242,   42,   43,   44,    0,  340,
    0,    0,    0,    0,    0,    0,    0,  706,    0,    0,
  162,  328,  -98,  329,   16,  330,    0,  278,    0,    0,
  234,  235,  331,    0,  332,    0,  333,    0,  215,  216,
  496,   88,  109,  279,    0,    0,    0,    0,  162,  328,
    0,  329,   16,  330,    0,  278,    0,    0,  234,  235,
  331,    0,  332,    0,  333,    0,  215,  216,  496,   88,
  109,  279,    0,    0,    0,    0,  240,    0,    0,    0,
    0,    0,    0,  281,  282,  334,  335,  336,  337,  338,
    0,  241,  242,   42,   43,   44,    0,  340,    0,    0,
    0,    0,    0,    0,  240,  708,    0,    0,    0,    0,
  -98,  281,  282,  334,  335,  336,  337,  338,    0,  241,
  242,   42,   43,   44,    0,  340,    0,    0,    0,    0,
    0,    0,    0,  548,    0,    0,  162,  328,  -98,  329,
   16,  330,    0,  278,    0,    0,  234,  235,  331,    0,
  332,    0,  333,    0,  215,  216,  496,   88,  109,  279,
    0,    0,    0,    0,  162,  328,    0,  329,   16,  330,
    0,  278,    0,    0,  234,  235,  331,    0,  332,    0,
  333,    0,  215,  216,  496,   88,  109,  279,    0,    0,
    0,    0,  240,    0,    0,    0,    0,    0,    0,  281,
  282,  334,  335,  336,  337,  338,    0,  241,  242,   42,
   43,   44,    0,  340,    0,    0,    0,    0,    0,    0,
  240,  547,    0,    0,    0,    0,  -98,  281,  282,  334,
  335,  336,  337,  338,    0,  241,  242,   42,   43,   44,
    0,  340,    0,    0,    0,    0,    0,    0,    0,  707,
    0,    0,  162,  328,  -98,  329,   16,  330,    0,  278,
    0,    0,  234,  235,  331,    0,  332,    0,  333,    0,
  215,  216,  496,   88,  109,  279,    0,    0,    0,    0,
  162,  328,    0,  329,   16,  330,    0,  278,    0,    0,
  234,  235,  331,    0,  332,    0,  333,    0,  215,  216,
  496,   88,  109,  279,    0,    0,    0,    0,  240,    0,
    0,    0,    0,    0,    0,  281,  282,  334,  335,  336,
  337,  338,    0,  241,  242,   42,   43,   44,    0,  340,
    0,    0,    0,    0,    0,    0,  240,  543,    0,    0,
    0,    0,  -98,  281,  282,  334,  335,  336,  337,  338,
    0,  241,  242,   42,   43,   44,    0,  340,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -98
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1701

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,    0,   18,   19,   20,   21,
   22,   23,    2,   25,   26,   27,   28,   29,  105,  106,
  107,    2,   34,   35,   62,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   85,    4,
   87,   53,   54,   55,   71,   57,   58,   85,   95,   87,
   97,   78,   16,   14,   90,   67,   83,   69,   94,   71,
   72,   73,   74,   75,   76,   14,   78,   14,   14,    3,
    2,   83,    4,    5,    6,   87,    8,   90,    7,   14,
   92,   13,   14,   95,   85,   17,   87,   99,  100,  101,
  102,  103,  104,  105,  106,  107,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   90,
   16,   14,   18,   19,   20,   21,   22,   23,   79,   25,
   26,   27,   28,   29,   85,   71,   72,   73,   34,   35,
   94,   77,    4,    5,    6,   67,   85,   59,   85,   85,
   72,   13,   74,   75,   79,   94,   59,   53,   54,   55,
   85,   57,   58,   85,   86,  101,   27,   28,   29,   91,
   78,   67,   14,   69,    7,   83,   72,   73,   74,   75,
   76,   23,   78,   37,    3,   32,   33,   83,   84,  101,
   14,   87,   85,   25,   26,   19,   92,   16,  101,   95,
   14,   94,    7,   99,  100,  101,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,    7,   92,   85,   14,
   87,  102,  103,   85,   98,    4,    5,    6,   95,  104,
   97,   85,   87,   87,   13,   14,    9,   14,   10,   56,
   95,   85,   97,   87,   53,   54,   55,   91,   57,   58,
   59,   85,   82,   62,   14,   64,   65,   66,   67,   68,
   69,   70,   92,   72,   73,   74,   75,   76,   85,   78,
   87,   78,   14,   14,   83,   84,   14,   86,   95,   16,
   97,   82,   91,   91,   91,   93,   95,   53,   54,   55,
   85,   92,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   85,   16,   85,   18,
   19,   20,   21,   22,   23,   81,   82,   78,   19,   85,
   62,   87,   36,   89,   62,   85,   34,   35,   30,   95,
   91,   51,   52,   61,   62,   31,   59,   79,   60,   78,
   84,   79,   78,   85,   53,   54,   55,   85,   57,   58,
   59,   78,   78,   62,   78,   84,   86,   78,   67,   78,
   69,   78,   78,   72,   73,   74,   75,   76,   78,   78,
   82,   78,   78,   78,   83,   84,   79,   88,   78,   78,
   78,   85,   79,   96,   79,   79,   95,   79,  103,   82,
   -1,   -1,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   84,   16,   84,   18,
   19,   20,   21,   22,   23,   85,   85,   85,   90,   86,
   86,   86,   86,   86,   86,   86,   86,   86,   99,   87,
   87,   -1,   88,   88,   88,   88,   88,   88,   88,   88,
   88,   88,   88,   88,   53,   54,   55,   90,   57,   58,
   90,   90,   14,   62,   90,   90,   90,   94,   67,   91,
   69,   91,   91,   72,   73,   74,   75,   76,   91,   78,
   32,   33,   91,   91,   83,   84,   85,   91,   91,   88,
   91,   91,   94,   91,   93,    2,    3,    4,    5,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   91,   16,
   91,   18,   19,   20,   21,   22,   23,   91,   91,   71,
   72,   73,   91,   91,   91,   77,   96,   93,   93,   93,
   93,   93,   93,   85,   93,   93,   96,   94,   94,   94,
   92,   94,   96,   94,   94,   94,   53,   54,   55,  101,
   57,   58,  104,  105,   94,   62,  108,  109,   94,   94,
   67,   94,   69,   94,   94,   72,   73,   74,   75,   76,
   94,   78,   94,   94,   94,   94,   83,   84,   85,   95,
   95,   95,   95,   95,   95,   95,   93,    2,    3,    4,
    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   95,   16,   95,   18,   19,   20,   21,   22,   23,   95,
   95,   95,   95,   95,   95,   95,   95,   95,   95,   95,
   95,   95,   95,   95,   95,   -1,   96,   96,   96,   96,
   96,   96,   96,   96,   96,   96,   96,   96,   53,   54,
   55,   96,   57,   58,   96,   96,   96,   62,   96,   96,
   96,   96,   67,   96,   69,   96,   96,   72,   73,   74,
   75,   76,   96,   78,   96,   96,   96,   96,   83,   84,
   85,   96,   96,   96,   96,   96,   96,   96,   93,    2,
    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   96,   16,   96,   18,   19,   20,   21,   22,
   23,    1,    2,  100,    4,    5,    6,  101,    8,   -1,
   -1,   11,   12,   13,   -1,   15,   -1,   17,   -1,   19,
   20,   21,   22,   23,   24,   -1,   -1,   -1,   -1,   -1,
   53,   54,   55,   -1,   57,   58,   -1,   -1,   -1,   62,
   -1,   -1,   -1,   -1,   67,   -1,   69,   -1,   -1,   72,
   73,   74,   75,   76,   -1,   78,   -1,   57,   -1,   59,
   83,   84,   85,   -1,   64,   65,   66,   67,   68,   69,
   70,   -1,   72,   73,   74,   75,   76,   -1,   78,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   86,   -1,   -1,   -1,
   -1,   91,    1,    2,   -1,    4,    5,    6,   -1,    8,
   -1,  101,   11,   12,   13,   -1,   15,   -1,   17,   -1,
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
 1609,  211,  801,  832,  710, 1581, 1145, 1117, 1261, 1036,
 1005, 1233, 1465, 1377, 1493, 1349, 1609, 1609, 1609, 1609,
 1609, 1609, 1609, 1609, 1609,  411,  411,  595,  595,  595,
  595,  595,  595,  595,  595,  503,  687,  342,  344,  291,
  276,   -2,  104,  104,  104,  104,  104,  104,  354,  361,
  353,  311,   88,  241,  278,  278,  278,   75,  176,   49,
  158,  282,   63,   63,   63,   63,   61,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,  107,  260,  260,
  260,  260,  260,  260,  260,  260,  243,  243,  243,  243,
  225,  243,  243,  225,  243,  279,  225,  279,  243,  243,
  243,  243,  243,  186,  243,  243,  243,  279,  279,  243,
  243,  243,  243,  243,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,  458,  458,  458,  458,  458,  458,  458,   46,
  283,   29,   78,  544,  375,  374,  364,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,  254,
  254,  254,  254,  254,  203,  307,  -37,  -37,  -37,  -37,
  153,  153,  153,  153,  153,  -28,  -28,  -28,  -28,  -28,
  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,
  139,  139,  139,  138,    9,  166,  166,  166,  166,  166,
  213,  259,  -17,  -17,  -17,  -17,  -17,  165,  -77,  -77,
  -77,   81,  181,  181,  293,  281,  524,  525,  526,   92,
  319,  314,  313,  146,  168,  312,  145,  300,  292,  -26,
  406,  442,  212,  319,  314,  313,  303,  440,  450,  441,
  541,   97,  168,  312,  312,  312,  312,  312,  145,  145,
  300,  437,  543,  190,  542,  456,  540,  219,  352,  284,
  528,  294,  294,  305,   20,  383,  247,   20,   20,  383,
  310,   20,  528,  539,  539,  352,  352,  352,  455,  448,
  528,  248,  444,   20,  480,  480,  363,  363,  352,  352,
   20,  475,  530,  352,  352,  352,  352,  352,  475,  352,
  530,  352,  352,  352,  352,  352,  352,  352,  515,  500,
  517,  499,  479,  351,  412,  321,  322,  320,  315,  494,
  489,   15,  410,  318,  324,  349,  613,  616,  306,   45,
  498,  409,  407,  529,  496,  495,  446,  304,  527,  328,
  350,  316,  538,  537,  370,  562,  536,  535,  534,  515,
  500,  517,  499,  454,  453,  408,  321,  320,  457,  488,
  459,  529,  496,  495,  474,  369,  449,  477,  560,  559,
  368,  558,  401,  497,  195,   81,  397,  443,  460,  326,
  532,  533,  348,  360,  373,  390,  296,  385,  325,  555,
  486,  588,  452,  587,  586,  290,  567,  359,  449,  565,
  298,  318,  470,  324,  349,  613,  616,  306,  306,  306,
  551,  447,  531,  229,  372,  436,  301,  564,  323,  299,
  358,  384,  381,  377,  388,  317,  563,  550,  585,  357,
  367,  581,  580,  579,  578,  461,  608,  491,  490,  549,
  297,  366,  362,  362,  576,   76,  371,  167,  429,  570,
  461,  606,  356,  365,  548,  327,  386,  380,  391,  547,
  309,  569,  402,  381,  427,  591,  377,  377,  546,  590,
  308,  377,  355,  589,  355,  545,    0,    0,    0,    0,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,   -2,   -2,   -2,
   -2,    0,    0,    0,    0,    0,    0,    0,  311,  311,
  311,    0,  311,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,   -3,
   -3,   -3,    0,   -3,   -3,   -3,   -3,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   92,
   92,   92,   92,   92,  153,  153,  153,  153,  153,  153,
    0,    0,    0,    0,    0,   92,   92,   92,   92,   92,
   92,   92,   92,   92,   92,   92,   92,   92,   92,   92,
    0,    0,    0,    0,   92,   92,   92,   92,   92,   92,
   20,   20,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -26,    0,    0,   20,   20,  352,  352,  352,    0,
  529,  496,  495,    0,    0,    0,    0,    0,    0,    0,
  445,  445,    0,  529,  496,  495,  533,  451,  451,  451,
  451,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  445,  451,    0,  451,  451,  451
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 277

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  306,32767,32767,32767,
32767,32767,32767,32767,32767,  355,  356,  357,32767,32767,
32767,32767,  297,32767,  491,  491,  491,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  101,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,   90,  101,  101,
  101,  101,  101,  101,  101,  101,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,   90,
  348,32767,32767,32767,32767,   92,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  180,  182,32767,32767,32767,32767,32767,32767,  350,32767,
32767,  103,32767,32767,32767,32767,32767,  323,   89,  302,
  321,  497,  325,  331,  333,  307,   91,  322,  329,32767,
32767,32767,32767,32767,  192,32767,  190,  191,  188,  187,
  131,  498,  332,  334,  330,  472,  472,  472,  472,  472,
  472,  472,  472,  472,  472,  472,  472,  472,  472,32767,
  156,  157,  158,32767,32767,32767,32767,  351,  352,32767,
  345,  346,32767,32767,32767,32767,32767,  489,  168,  170,
  169,  432,  109,  109,  103,  103,32767,32767,32767,32767,
32767,32767,32767,  143,  154,  159,  165,  175,  177,  432,
32767,32767,32767,  366,  353,  354,32767,32767,32767,32767,
32767,32767,  155,  161,  163,  164,  160,  162,  166,  167,
  176,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  294,  103,  446,   77,  103,  103,  446,
32767,  103,32767,  470,  470,32767,32767,  342,  500,  296,
32767,   80,  296,  103,  464,  464,  484,  484,32767,32767,
  103,  113,  487,32767,32767,32767,32767,32767,  113,32767,
  487,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  233,32767,32767,  144,  146,  148,  150,  152,  171,32767,
32767,32767,32767,32767,32767,32767,  102,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  336,
  338,  340,  347,  214,  216,  217,  358,  359,  233,  234,
32767,  366,  353,  354,  233,32767,  298,32767,32767,32767,
32767,32767,32767,32767,32767,  215,32767,32767,32767,32767,
32767,32767,   51,32767,32767,32767,32767,32767,32767,32767,
  476,32767,  473,32767,32767,32767,32767,32767,  299,32767,
32767,  145,32767,  147,  149,  151,  153,  172,  173,  174,
32767,  492,32767,32767,32767,32767,32767,32767,32767,  297,
32767,32767,32767,  434,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,  229,32767,  233,32767,32767,
32767,32767,  483,  481,32767,   62,32767,  291,32767,32767,
32767,32767,32767,32767,32767,32767,   54,  433,32767,32767,
32767,32767,32767,   75,32767,32767,  437,  436,32767,32767,
32767,  435,  452,32767,32767,32767,  500,  426,  426,  500
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  169,  169,  169,  169,  169,  169,  169,  169,  169,  169,
  169,  175,  561,  257,  258,  260,  272,  418,  274,  275,
  395,  276,  695,  828,  695,  695,  695,  695,  173,  171,
  171,  171,  163,  170,  163,  924,  171,  697,  636,  968,
  724,  167,  611,  923,  611,  434,  403,  404,  420,  449,
  450,  466,  472,  473,  953,  953,  263,  264,  265,  266,
  267,  608,  168,  167,  167,  167,  167,  167,  167,  167,
  167,  170,  170,  170,  170,  174,  170,  170,  173,  170,
  389,  178,  389,  159,  168,  159,  160,  164,  172,  165,
  176,  177,  995,  630,  166,  630,  630,  630,  630,  423,
  630,  630,  630,  630,  630,  630,  630,  630,  630,  630,
  630,  630,  630,  630,  630,  630,  630,  630,  630,  630,
  421,  701,  425,  701,  701,  701,  701,  702,  639,  702,
  702,  702,  702,  639,  639,  639,  639,  639,  612,  424,
  612,  815,  815,  815,  815,  815,  186,  187,  188,  189,
  952,  492,  426,  415,  422,  641,  494,  410,  410,  410,
  410,  410,  410,  410,  410,  410,  410,  410,  410,  410,
  410,  410,  561,  954,  954,  578,  231,  249,  249,  249,
  249,  249,  413,  414,  419,  447,  448,  451,  452,  453,
  454,  456,  464,  471,  481,  486,  487,  491,   14,   14,
  262,  980,   12,   13,   15,  459,  495,  502,  303,  435,
  468,  484,  485,  489,  493,  286,  503,  349,  505,  505,
  505,  505,  505,  349,  465,  564,  563,  572,  573,  571,
  570,  569,  962,  963,  286,  689,  685,  686,  678,  679,
  681,  683,  427,  428,  429,  581,  566,  966,  730,  730,
  960,  961,  948,  949,  950,  270,  942,  233,  943,  955,
  956,  957,  951,  579,  944,  285,  285,  285,  285,  285,
  285,  285,  285,  285,  285,  285,  285,  285,  285,  285,
  285,  285,  285,  285,  285,  285,  285,  285,  285,  285,
  616,  599,  380,  803,  804,  808,  809,  835,  805,  619,
  620,  621,  622,  623,  624,  625,  626,  627,  628,  629,
  617,  618,  616,  994,  810,  939,  996,  192,  191,  191,
  191,  185,  271,  185,  251,  191,  251,  458,  367,  368,
  975,  367,  368,  947,  312,  320,  488,  268,  269,  380,
  380,  380,  380,  380,  211,  212,  931,  229,  230,  607,
  607,  352,  433,  605,  361,  401,  305,  440,  314,  463,
  107,  977,  300,    0,  193,  352,  156,  192,    0,    0,
  194,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  392,    0,    0,  396,  397,    0,
    0,  405,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  444,    0,    0,    0,    0,    0,    0,
  318
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 441

static char yygcheck[] = {
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   33,   69,   69,   69,   69,   66,   69,   69,
   73,   69,   58,   72,   58,   58,   58,   58,   35,   35,
   35,   35,   35,   35,   35,   64,   35,   57,   57,   57,
   57,   35,    7,   64,    7,   65,   65,   65,   65,   65,
   65,   65,   65,   65,    7,    7,   49,   49,   49,   49,
   49,  109,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
  105,   35,  105,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   99,   39,   35,   39,   39,   39,   39,   43,
   39,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   39,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   42,    7,   45,    7,    7,    7,    7,   96,   96,   96,
   96,   96,   96,   96,   96,   96,   96,   96,   39,   44,
   39,   73,   73,   73,   73,   73,   56,   56,   56,   56,
   39,   39,   46,   39,   39,   39,   39,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   33,    7,    7,    7,   73,   73,   73,   73,
   73,   73,   92,   92,   92,   92,   92,   92,   92,   92,
   92,   92,   92,   92,   92,   80,   80,   80,    3,    3,
   47,   73,    3,    3,    3,   97,   97,    4,   38,   38,
   38,   38,   38,   38,   38,    7,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    7,    7,    7,   54,   54,   54,   54,   54,
   54,   54,   52,   52,   52,    7,    7,   59,   59,   59,
    7,    7,    7,    7,    7,   53,    7,  106,    7,    7,
    7,    7,    7,    7,    7,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   36,   30,   74,   67,   67,   67,   67,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   37,   37,   37,
   37,   37,   78,   37,   78,   37,   78,   74,   75,   75,
   94,   75,   75,  101,  101,  101,  101,   50,   50,   74,
   74,   74,   74,   74,   48,   48,   79,   51,   51,  107,
  107,   30,   19,  108,    9,  100,   90,  110,   88,  102,
  111,  103,  113,   -1,   37,   30,  104,   37,   -1,   -1,
   37,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   30,   -1,   -1,   30,   30,   -1,
   -1,   30,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   30,   -1,   -1,   -1,   -1,   -1,   -1,
   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  196,  207,    0,    0,  -63,    0,   72,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  138,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  130,    0,    0,  -41,    0,  -25,  230,  264,  119,   33,
    0,    0,   -4,  -26,   13,   -5,   24,   71,  214,  -76,
  200,  208,  101,  111,   90,    0,   -6,   -1, -162,   91,
    0,    0,    0,    0, -257,   19,  -18,  113,    0,  -83,
    0,    0,  -29,  -38,  291,  285,    0,    0,  108,  127,
  132,  265,    0,    0,    0,    0,    0,    0,   53,    0,
   62,    0,  -14,    0,  121,    0,  -57,  150,    0,   31,
   66,  110,   52,   41, -133,   23,   97,  117,  120,  -46,
   55,   42,    0, -136
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  341,    9,   11,  504,  507,  506,  508,  509,  360,
  510,  302,  523,  511,  539,  540,  541,  512,  542,  394,
  513,  301,  576,  518,  519,  284,  520,  521,  252,  522,
  351,  524,  514,  515,  342,  161,  938,  190,  291,  615,
  640,  243,  343,  344,  345,  346,  347,  244,  210,  245,
  246,  228,  348,  247,  248,  684,  184,  731,  634,  694,
  720,  719,  721,  723,  925,  385,  386,  310,   35,  259,
  356,  299,  827,  715,  387,  366,  959,  557,  250,  930,
  443,  289,  558,  940,  642,  941,  559,  560,  313,  227,
  304,  965,  411,  412,  974,  700,  722,  430,  431,  993,
  256,  693,  462,  477,   89,  632,  232,  606,  600,  610,
  417,  105,   29,  292
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
   34,   38,   38,   30,   30,  105,  106,  106,  107,  108,
  108,  109,  109,  111,  111,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   36,   36,   36,   37,   37,   37,   37,   37,   37,   37,
   39,   39,   40,   40,   41,   41,   42,   42,   43,   43,
   44,   44,   45,   45,   46,   46,   47,   47,   47,   48,
   48,   48,   48,   48,   48,   49,   49,   49,   50,   50,
   50,   51,   51,   51,   51,   52,   52,   53,   53,   53,
   53,   53,   53,   53,   54,   54,   54,   54,   54,   54,
   54,   54,   55,   55,   56,   56,   56,   56,   56,   56,
   56,   95,   95,   96,   96,   96,   96,   96,   96,   58,
   58,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   73,   73,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   61,   61,   60,   60,  112,   62,  110,  110,   65,   65,
   68,   68,   66,   66,   66,   66,   66,   66,   66,   66,
   66,   67,   67,   67,   67,   67,   67,   67,   67,   67,
   67,   69,   69,   70,   70,   70,   70,   71,   71,   72,
   72,   72,   72,   72,   72,   72,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   63,   63,   63,  113,   64,   77,   77,
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
    9,    8,    7,    8,    1,    3,    4,    0,    2,    5,
    0,    2,    3,    4,    3,    4,    5,    2,    3,    2,
    1,    4,    3,    4,    3,    1,    3,    2,    0,    2,
    4,    0,    1,    0,    4,    4,    1,    2,    5,    0,
    3,    1,    1,    0,    1,    1,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    1,    1,    1,    2,    2,    4,    3,    3,    4,    2,
    1,    5,    1,    1,    1,    3,    1,    3,    1,    3,
    1,    3,    1,    3,    1,    3,    1,    3,    3,    1,
    3,    3,    3,    3,    3,    1,    3,    3,    1,    3,
    3,    1,    3,    3,    3,    1,    3,    1,    3,    3,
    2,    3,    2,    3,    1,    2,    2,    2,    2,    2,
    2,    2,    1,    3,    1,    2,    4,    3,    3,    4,
    2,    1,    1,    4,    8,    6,    7,    7,    8,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    2,    6,    3,    3,    3,    3,
    2,    2,    2,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    2,    2,
    2,    3,    2,    4,    0,    4,    0,    1,    1,    2,
    1,    2,    1,    3,    3,    2,    2,    3,    5,    5,
    4,    1,    1,    1,    1,    1,    1,    1,    3,    3,
    3,    1,    3,    1,    2,    3,    4,    1,    3,    5,
    5,    3,    3,    3,    3,    2,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    2,    2,    3,    3,    2,    0,    3,    3,    3,
    1,    3,    1,    4,    3,    6,    5,    5,    1,    3,
    1,    1,    6,    6,    7,    1,    0,    2,    5,    5,
    5,    6,    6,    6,    2,    6,    6,    6,    1,    1,
    5,    5,    3,    3,    0,    4,    1,    4,    3,    3,
    0,    3,    0,    1,    1,    3,    1,    4,    3,    3,
    2,    2,    1,    2,    0,    2,    3,    0,    3,    0,
    3,    0,    1,    1,    2,    3,    4,    1,    1,    1,
    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 898
#define YYNLSTATES 500
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
#line 169 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 174 "src/kinx.y"
{ kx_ast_root = yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 5:
#line 179 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 16:
#line 196 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strval, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 17:
#line 197 "src/kinx.y"
{ yyerrok; } break;
        case 25:
#line 208 "src/kinx.y"
{ yyerrok; } break;
        case 26:
#line 209 "src/kinx.y"
{ yy_restart(LBBR); yyerrok; } break;
        case 27:
#line 210 "src/kinx.y"
{ yy_restart(IF); yyerrok; } break;
        case 28:
#line 211 "src/kinx.y"
{ yy_restart(DO); yyerrok; } break;
        case 29:
#line 212 "src/kinx.y"
{ yy_restart(WHILE); yyerrok; } break;
        case 30:
#line 213 "src/kinx.y"
{ yy_restart(FOR); yyerrok; } break;
        case 31:
#line 214 "src/kinx.y"
{ yy_restart(TRY); yyerrok; } break;
        case 32:
#line 215 "src/kinx.y"
{ yy_restart(SWITCH); yyerrok; } break;
        case 33:
#line 216 "src/kinx.y"
{ yy_restart(CASE); yyerrok; } break;
        case 34:
#line 217 "src/kinx.y"
{ yy_restart(ENUM); yyerrok; } break;
        case 35:
#line 218 "src/kinx.y"
{ yy_restart(CLASS); yyerrok; } break;
        case 36:
#line 219 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; } break;
        case 37:
#line 220 "src/kinx.y"
{ yy_restart(PRIVATE); yyerrok; } break;
        case 38:
#line 221 "src/kinx.y"
{ yy_restart(PUBLIC); yyerrok; } break;
        case 43:
#line 232 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 44:
#line 233 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 45:
#line 237 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 238 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 47:
#line 239 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 240 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 49:
#line 244 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strval); } break;
        case 50:
#line 248 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 51:
#line 252 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strval); } break;
        case 52:
#line 253 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strval, YYASP(3-3).intval); } break;
        case 53:
#line 254 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strval, -YYASP(4-4).intval); } break;
        case 54:
#line 255 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strval)); } break;
        case 55:
#line 256 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strval, YYASP(5-5).intval)); } break;
        case 56:
#line 257 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strval, -YYASP(6-6).intval)); } break;
        case 61:
#line 268 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 62:
#line 272 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 63:
#line 273 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 64:
#line 277 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 65:
#line 281 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 66:
#line 285 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 289 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 290 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 295 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 70:
#line 302 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 71:
#line 309 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 72:
#line 316 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 73:
#line 318 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 74:
#line 322 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 75:
#line 323 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 76:
#line 327 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 77:
#line 331 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 78:
#line 332 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, "_e", YYASP(2-2).obj, NULL); } break;
        case 79:
#line 333 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(3-5).strval, YYASP(5-5).obj, NULL); } break;
        case 80:
#line 337 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 81:
#line 338 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 82:
#line 342 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 83:
#line 343 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strval)); } break;
        case 84:
#line 344 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 85:
#line 345 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strval)); } break;
        case 86:
#line 349 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 87:
#line 350 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 88:
#line 354 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 89:
#line 358 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 90:
#line 359 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 91:
#line 360 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 92:
#line 361 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 93:
#line 365 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 94:
#line 369 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 95:
#line 373 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object(YYASP(1-1).strval, KX_OBJ_T), NULL); } break;
        case 96:
#line 374 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object(YYASP(3-3).strval, KX_OBJ_T), NULL); } break;
        case 97:
#line 378 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 98:
#line 382 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 99:
#line 383 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 100:
#line 384 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj), NULL, NULL); } break;
        case 101:
#line 388 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 103:
#line 393 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 104:
#line 394 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 105:
#line 398 "src/kinx.y"
{ yyval.obj = kx_gen_case_expr_object(YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 107:
#line 403 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 108:
#line 407 "src/kinx.y"
{ yyval.obj = kx_gen_case_when_object(YYASP(2-5).obj, YYASP(5-5).obj, YYASP(3-5).obj); } break;
        case 109:
#line 411 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 110:
#line 412 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(3-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 111:
#line 416 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL), NULL); } break;
        case 116:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 117:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 119:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 120:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 121:
#line 432 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 122:
#line 433 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 123:
#line 434 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 124:
#line 435 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 125:
#line 436 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 126:
#line 437 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 127:
#line 438 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 128:
#line 439 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 129:
#line 440 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 133:
#line 450 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 134:
#line 451 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 135:
#line 452 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 136:
#line 453 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 137:
#line 454 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 138:
#line 455 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 139:
#line 456 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 141:
#line 461 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 145:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 147:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 149:
#line 481 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 151:
#line 486 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 153:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 155:
#line 496 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 157:
#line 501 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 158:
#line 502 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 160:
#line 507 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 161:
#line 508 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 162:
#line 509 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 163:
#line 510 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 164:
#line 511 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 166:
#line 516 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 167:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 169:
#line 522 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 170:
#line 523 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 172:
#line 528 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 173:
#line 529 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 174:
#line 530 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 176:
#line 535 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 178:
#line 540 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 179:
#line 541 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 180:
#line 542 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 181:
#line 543 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 182:
#line 544 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 183:
#line 545 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 185:
#line 550 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 186:
#line 551 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 187:
#line 552 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 188:
#line 553 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 189:
#line 554 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 190:
#line 555 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 191:
#line 556 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 193:
#line 561 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 195:
#line 566 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 196:
#line 567 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 197:
#line 568 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 198:
#line 569 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 199:
#line 570 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 200:
#line 571 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 201:
#line 575 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 203:
#line 580 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 204:
#line 581 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 205:
#line 582 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 206:
#line 583 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 207:
#line 584 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 208:
#line 585 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 209:
#line 589 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 210:
#line 590 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 211:
#line 594 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 212:
#line 595 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 213:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 214:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 215:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 216:
#line 599 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 217:
#line 600 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 218:
#line 601 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 224:
#line 607 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 225:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 226:
#line 609 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 227:
#line 610 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 228:
#line 611 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 229:
#line 612 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 230:
#line 613 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 231:
#line 614 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 232:
#line 615 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 233:
#line 619 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 234:
#line 620 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 235:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 236:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 237:
#line 626 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 238:
#line 627 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 239:
#line 628 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 240:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 241:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 242:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 243:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 244:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 245:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 246:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 247:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 248:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 249:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 250:
#line 639 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 251:
#line 640 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 252:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 253:
#line 642 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 254:
#line 643 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 255:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 256:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 257:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 258:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 259:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 260:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 261:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 262:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 263:
#line 652 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 264:
#line 653 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 265:
#line 654 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 266:
#line 655 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 267:
#line 656 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 268:
#line 657 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 269:
#line 658 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 270:
#line 659 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 271:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 272:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 273:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 274:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 275:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 276:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 277:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 278:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 279:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 280:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 281:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 282:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 283:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 284:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 285:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 286:
#line 675 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 287:
#line 676 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 288:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 289:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 290:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 291:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 292:
#line 687 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 293:
#line 688 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 294:
#line 692 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 295:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 296:
#line 700 "src/kinx.y"
{} break;
        case 298:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 299:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 300:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 301:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 303:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 304:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 305:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 306:
#line 719 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 307:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 308:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_keyvalue_object(YYASP(3-5).strval, YYASP(5-5).obj)); } break;
        case 309:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_keyvalue_object(YYASP(3-5).strval, YYASP(5-5).obj)); } break;
        case 310:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 311:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 312:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 313:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 314:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 315:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 316:
#line 732 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 317:
#line 733 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 318:
#line 734 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 319:
#line 735 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 320:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 322:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 324:
#line 746 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 325:
#line 747 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 326:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 328:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 329:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 330:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 331:
#line 759 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 332:
#line 760 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 333:
#line 761 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 334:
#line 762 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 335:
#line 763 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 336:
#line 767 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 337:
#line 768 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 338:
#line 769 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 339:
#line 770 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 340:
#line 771 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 341:
#line 772 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 342:
#line 773 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 343:
#line 774 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 344:
#line 775 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 345:
#line 776 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 346:
#line 777 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 347:
#line 778 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 348:
#line 779 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 349:
#line 780 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 350:
#line 781 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 351:
#line 782 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 352:
#line 783 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 353:
#line 784 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 354:
#line 785 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 355:
#line 786 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 356:
#line 787 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 357:
#line 788 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 358:
#line 789 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 359:
#line 790 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 360:
#line 791 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 361:
#line 792 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 362:
#line 793 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 363:
#line 794 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 364:
#line 795 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 365:
#line 796 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 366:
#line 797 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 367:
#line 798 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 368:
#line 799 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 369:
#line 800 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 370:
#line 804 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 371:
#line 805 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 372:
#line 806 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 373:
#line 807 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 374:
#line 808 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 375:
#line 809 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 376:
#line 810 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 377:
#line 811 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 378:
#line 812 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 379:
#line 813 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 380:
#line 814 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 381:
#line 815 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 382:
#line 816 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 383:
#line 817 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 384:
#line 818 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 385:
#line 819 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 386:
#line 820 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 387:
#line 821 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 388:
#line 822 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 389:
#line 823 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 390:
#line 824 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 391:
#line 825 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 392:
#line 826 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 393:
#line 827 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 394:
#line 828 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 395:
#line 829 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 396:
#line 830 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 397:
#line 831 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 398:
#line 832 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 399:
#line 833 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 400:
#line 834 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 401:
#line 835 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 402:
#line 836 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 403:
#line 837 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 404:
#line 838 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 405:
#line 839 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 406:
#line 840 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 407:
#line 841 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 408:
#line 842 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 409:
#line 843 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 410:
#line 844 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 411:
#line 845 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 412:
#line 846 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 413:
#line 847 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 414:
#line 848 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 415:
#line 849 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 416:
#line 850 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 417:
#line 851 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 418:
#line 852 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 419:
#line 853 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 420:
#line 854 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 421:
#line 855 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 422:
#line 856 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 423:
#line 860 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 424:
#line 861 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 425:
#line 862 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 426:
#line 866 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 427:
#line 870 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 428:
#line 874 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 429:
#line 875 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 431:
#line 880 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 432:
#line 884 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 433:
#line 885 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 434:
#line 886 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 435:
#line 887 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 436:
#line 888 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 437:
#line 889 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 439:
#line 894 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 440:
#line 898 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 441:
#line 899 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 442:
#line 903 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 443:
#line 904 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 444:
#line 905 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 445:
#line 909 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 446:
#line 913 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 447:
#line 914 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 448:
#line 918 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 449:
#line 919 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 450:
#line 920 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 451:
#line 921 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 452:
#line 922 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 453:
#line 923 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 454:
#line 924 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 455:
#line 928 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 456:
#line 929 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 457:
#line 930 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 460:
#line 939 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 461:
#line 940 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 462:
#line 944 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 463:
#line 945 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 464:
#line 949 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 465:
#line 951 "src/kinx.y"
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
        case 467:
#line 967 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 468:
#line 968 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 469:
#line 969 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 470:
#line 973 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 471:
#line 974 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 472:
#line 978 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 475:
#line 984 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 476:
#line 988 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 477:
#line 989 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 478:
#line 990 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LARY_T); } break;
        case 479:
#line 991 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LOBJ_T); } break;
        case 480:
#line 992 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 481:
#line 996 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 482:
#line 997 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 483:
#line 998 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 484:
#line 1002 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 485:
#line 1003 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 486:
#line 1004 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 487:
#line 1008 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 488:
#line 1009 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 489:
#line 1013 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 490:
#line 1014 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 491:
#line 1018 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 494:
#line 1024 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 495:
#line 1025 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 496:
#line 1026 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 499:
#line 1032 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 500:
#line 1036 "src/kinx.y"
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
