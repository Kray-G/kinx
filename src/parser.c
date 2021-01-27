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
#line 1035 "src/kinx.y"

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
  "WhenClause : WHEN ArrayItemListCoreRight Modifier_Opt ':' WhenClauseBody",
  "CaseElseClause : /* empty */",
  "CaseElseClause : ELSE ':' WhenClauseBody",
  "WhenClauseBody : BlockStatement",
  "WhenClauseBody : TernaryExpression",
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
  "ArrayItemListCoreRight : SRCFILE",
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
#define YYNONTERMS 113

static short yyaction[] = {
  732,  733,  734,  735,  736,  737,  738,  739,  740,  741,
  742,  743,  744,  746,  745,    0,  747,  748,  749,  758,
  760,  759,  348,  769,  770,  771,  773,  775,  141,  142,
  143,  348,  767,  768,  239,   69,   70,   71,   72,   73,
   74,   75,   76,   77,   78,   79,   80,   81,    4,  391,
  112,  761,  762,  763,  978,  764,  765,   30,   54,   31,
   38,  306,  179,  111,   62,  756,  307,  757,  224,  750,
  751,  752,  753,  754,  755,-32766,  731,  111,-32766,   19,
  525,  766,  527,  526,  528,  388,  529,   82,  -74,  111,
  777,  530,  531,  389,   27,  532,   32,  782,  783,  781,
  772,  774,  776,  778,  779,  780,  866,  867,  868,  869,
  870,  871,  872,  873,  874,  875,  876,  877,  878,   60,
  879,-32766,  880,  881,  882,  890,  892,  891,  414,  902,
  903,  904,  906,  908,   49,-32766,-32766,-32766,  900,  901,
  565,-32766,  327,   16,  328,  533,   48,-32766,   49,   51,
  534,  329,  536,  535,  386, -360,  102,  893,  894,  895,
   49,  896,  897,  524,  515,-32766,  810,  812,  813,  523,
  729,  888,  111,  889,  104,  730,  883,  884,  885,  886,
  887,  115,  954,  124,  436,  705,  706,  898,  899,-32766,
  -75,  362,   51,  814,  809,  807,  910,  179,   33,  363,
   34, -359,  808,  915,  916,  914,  905,  907,  909,  911,
  912,  913,  162,  367,  833,  368,   10,  369,  837,  297,
  839,  840,  220,  221,  370,  110,  330,  845,  331,  158,
  217,  218,  298,   66,   87,  279,-32766,-32766,  261,  288,
  114,  119,  308,   49,  121,  327,   16,  328,   55,   56,
   39,   40, -103,  238,  329,-32766,   27,-32766,   28,  222,
  132,  133,  134,  120,  371,  372,  373,-32766,  253,  863,
  120,-32766,  214,   67,-32766,  281,  282,  332,  374,  334,
  375,  336,  179,  254,  255,   45,   46,   47,    4,  376,
  112,-32766,  139,  355,  377,  865,  287,  541,   54,  125,
   38,  553,  -98,  126,  140,  398,   59,   50,   49, -103,
-32766,  488,  237,  832,  833,  834,  835,  836,  837,  838,
  839,  840,  841,  842,  843,  844,   49,  845,   51,  846,
  847,  848,  856,  858,  857,  135,  136,  550,   51,   83,
   26,  592,   48,  404,   90,  130,  131,  473,  137,  138,
  148,  149,  150,  151,  144,  789,  995,  117,   86,  593,
  547,  594,   49,  293,  859,  860,  861,  288,  862,  863,
  120,  474,  467,   67,  554,  995,  407,  459,  854,  430,
  855,   49,  405,  849,  850,  851,  852,  853,  400,  396,
  361,  360,  694,  296,  864,  865,  476,  295,  551,  294,
  287,  213,  444,  435,  197,  127,  397,    0,  788,  633,
  728,  965,  398,  832,  833,  834,  835,  836,  837,  838,
  839,  840,  841,  842,  843,  844,  290,  845,    7,  158,
  847,  848,  856,  858,  857,    6,    5,  982,  629,  820,
  822,  700,  816,  975,  548,  791,  439,  699,  128,  478,
    0,  815,  963,  981,  974,  784,  787,  917,  481,  465,
  440,  692,  631,    0,  371,  372,  373,  273,  379,  863,
   85,   65,-32766,   68,   64,   63,  443,  277,  854,  584,
  855,  591,  514,  380,  381,  851,  852,  853,  581,  382,
-32766,-32766,  586,  563,  377,  865,   51,  924,  582,  786,
  580,  595, -363,  585,  796,  832,  833,  834,  835,  836,
  837,  838,  839,  840,  841,  842,  843,  844,   95,  845,
   94,  158,  847,  848,  856,  858,  857,   93,   92,-32766,
-32766,-32766,   91,  925,  583,-32766,  724,  437,  219,  113,
   61,   52,   36,   51,  116,  209,   17, -362, -361, -358,
-32766,   53,   18,  100,  103,  105,  371,  372,  373,-32766,
  379,  863,-32766,-32766,  106,   68,-32766,-32766,  107,  566,
  854,  122,  855,  497,  225,  380,  381,  851,  852,  853,
  223,  382, -366,  183,  182,  181,  377,  865,   51,  180,
   20,  196,  195,  101,   99,   98,  797,  832,  833,  834,
  835,  836,  837,  838,  839,  840,  841,  842,  843,  844,
   97,  845,   96,  158,  847,  848,  856,  858,  857,   58,
  198,  205,  434,  406,  357,  356,  226,  208,  207,  206,
  204,  203,  202,  201,  200,  199,    0,   21,  309,  480,
  602,  722,  986,  984,  721,  634,  967,  695,  371,  372,
  373,  923,  379,  863,  785,  723,  725,   68,  918,  477,
  468,  458,  854,  453,  855,  325,  324,  380,  381,  851,
  852,  853,  323,  382,  322,  321,  320,  319,  377,  865,
   51,  317,  316,  315,  314,   24,   23,   22,  796,  832,
  833,  834,  835,  836,  837,  838,  839,  840,  841,  842,
  843,  844,    3,  845,    2,  158,  847,  848,  856,  858,
  857,  162,  326,  129,  327,   16,  328,    0,  278,    0,
    0,  234,  235,  329,    0,  330,    0,  331,    0,  215,
  216,  494,   88,  109,  279,    0,    0,    0,    0,    0,
  371,  372,  373,    0,  379,  863,    0,    0,    0,   84,
    0,    0,    0,    0,  854,    0,  855,    0,    0,  380,
  381,  851,  852,  853,    0,  455,    0,  240,    0,  120,
  377,  865,   51,    0,  281,  282,  332,  333,  334,  335,
  336,    0,  241,  242,   42,   43,   44,    0,  338,    0,
    0,    0,    0,    0,    0,    0,  541,    0,    0,    0,
    0,  -98,  162,  326,    0,  327,   16,  328,    0,  278,
    0,  237,  234,  235,  329,    0,  330,    0,  331,    0,
  215,  216,  494,   88,  109,  279,    0,    0,    0,    0,
    0,    0,    0,  162,  326,    0,  327,   16,  328,    0,
  278,    0,    0,  234,  235,  329,    0,  330,    0,  331,
    0,  215,  216,  494,   88,  109,  279,    0,  240,    0,
  118,    0,    0,    0,    0,  281,  282,  332,  333,  334,
  335,  336,    0,  241,  242,   42,   43,   44,    0,  338,
    0,    0,    0,    0,    0,    0,    0,  701,    0,  240,
    0,  123,  -98,    0,    0,    8,  281,  282,  332,  333,
  334,  335,  336,    0,  241,  242,   42,   43,   44,  108,
  338,    0,    0,  157,    0,    0,    0,    0,  701,    0,
    0,    0,    0,  -98,    0,    0,    8,  152,  153,    0,
    0,    0,    0,    0,    0,    0,  495,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  710,  712,
  713,    0,  351,    0,    0,    0,    0,    0,  280,    0,
    0,    0,    0,    0,    0,    0,  941,  352,  353,    0,
    0,    0,  337,  729,    0,  714,  709,  707,  730,    0,
    1,    0,   25,    0,  708,    0,    0,  154,    0,    0,
   57,    0,   41,    0,    0,    0,  236,  283,    0,  155,
  145,  496,    0,  146,  147,   37,  162,  326,    0,  327,
   16,  328,    0,  278,    0,    0,  234,  235,  329,    0,
  330,    0,  331,    0,  215,  216,  494,   88,  109,  279,
    0,    0,    0,    0,    0,    0,   -1,  162,  326,    0,
  327,   16,  328,    0,  278,    0,    0,  234,  235,  329,
    0,  330,    0,  331,    0,  215,  216,  494,   88,  109,
  279,    0,  240,    0,    0,    0,    0,    0,    0,  281,
  282,  332,  333,  334,  335,  336,    0,  241,  242,   42,
   43,   44,    0,  338,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  240,    0,    0,  -98,    0,    0, -337,
  281,  282,  332,  333,  334,  335,  336,    0,  241,  242,
   42,   43,   44,    0,  338,    0,    0,    0,  162,  326,
    0,  327,   16,  328,    0,  278,    0,  -98,  234,  235,
  329,    0,  330,    0,  331,    0,  215,  216,  494,   88,
  109,  279,    0,    0,    0,    0,  162,  326,    0,  327,
   16,  328,    0,  278,    0,    0,  234,  235,  329,    0,
  330,    0,  331,    0,  215,  216,  494,   88,  109,  279,
    0,    0,    0,    0,  240,    0,    0,    0,    0,    0,
    0,  281,  282,  332,  333,  334,  335,  336,    0,  241,
  242,   42,   43,   44,    0,  338,    0,    0,    0,    0,
    0,    0,  240,  544,    0,    0,    0,    0,  -98,  281,
  282,  332,  333,  334,  335,  336,    0,  241,  242,   42,
   43,   44,    0,  338,    0,    0,    0,    0,    0,    0,
    0,  543,    0,    0,  162,  326,  -98,  327,   16,  328,
    0,  278,    0,    0,  234,  235,  329,    0,  330,    0,
  331,    0,  215,  216,  494,   88,  109,  279,    0,    0,
    0,    0,  162,  326,    0,  327,   16,  328,    0,  278,
    0,    0,  234,  235,  329,    0,  330,    0,  331,    0,
  215,  216,  494,   88,  109,  279,    0,    0,    0,    0,
  240,    0,    0,    0,    0,    0,    0,  281,  282,  332,
  333,  334,  335,  336,    0,  241,  242,   42,   43,   44,
    0,  338,    0,    0,    0,    0,    0,    0,  240,  542,
    0,    0,    0,    0,  -98,  281,  282,  332,  333,  334,
  335,  336,    0,  241,  242,   42,   43,   44,    0,  338,
    0,    0,    0,    0,    0,    0,    0,  702,    0,    0,
  162,  326,  -98,  327,   16,  328,    0,  278,    0,    0,
  234,  235,  329,    0,  330,    0,  331,    0,  215,  216,
  494,   88,  109,  279,    0,    0,    0,    0,  162,  326,
    0,  327,   16,  328,    0,  278,    0,    0,  234,  235,
  329,    0,  330,    0,  331,    0,  215,  216,  494,   88,
  109,  279,    0,    0,    0,    0,  240,    0,    0,    0,
    0,    0,    0,  281,  282,  332,  333,  334,  335,  336,
    0,  241,  242,   42,   43,   44,    0,  338,    0,    0,
    0,    0,    0,    0,  240,  704,    0,    0,    0,    0,
  -98,  281,  282,  332,  333,  334,  335,  336,    0,  241,
  242,   42,   43,   44,    0,  338,    0,    0,    0,    0,
    0,    0,    0,  546,    0,    0,  162,  326,  -98,  327,
   16,  328,    0,  278,    0,    0,  234,  235,  329,    0,
  330,    0,  331,    0,  215,  216,  494,   88,  109,  279,
    0,    0,    0,    0,  162,  326,    0,  327,   16,  328,
    0,  278,    0,    0,  234,  235,  329,    0,  330,    0,
  331,    0,  215,  216,  494,   88,  109,  279,    0,    0,
    0,    0,  240,    0,    0,    0,    0,    0,    0,  281,
  282,  332,  333,  334,  335,  336,    0,  241,  242,   42,
   43,   44,    0,  338,    0,    0,    0,    0,    0,    0,
  240,  545,    0,    0,    0,    0,  -98,  281,  282,  332,
  333,  334,  335,  336,    0,  241,  242,   42,   43,   44,
    0,  338,    0,    0,    0,    0,    0,    0,    0,  703,
    0,    0,  162,  326,  -98,  327,   16,  328,    0,  278,
    0,    0,  234,  235,  329,    0,  330,    0,  331,    0,
  215,  216,  494,   88,  109,  279,    0,    0,    0,    0,
  162,  326,    0,  327,   16,  328,    0,  278,    0,    0,
  234,  235,  329,    0,  330,    0,  331,    0,  215,  216,
  494,   88,  109,  279,    0,    0,    0,    0,  240,    0,
    0,    0,    0,    0,    0,  281,  282,  332,  333,  334,
  335,  336,    0,  241,  242,   42,   43,   44,    0,  338,
    0,    0,    0,    0,    0,    0,  240,  541,    0,    0,
    0,    0,  -98,  281,  282,  332,  333,  334,  335,  336,
    0,  241,  242,   42,   43,   44,    0,  338,    0,    0,
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
   72,   13,   74,   75,   79,   94,    7,   53,   54,   55,
   85,   57,   58,   85,   86,  101,   53,   54,   55,   91,
   78,   67,   14,   69,    7,   83,   72,   73,   74,   75,
   76,   23,   78,   37,    3,   32,   33,   83,   84,  101,
    7,   87,   85,   80,   81,   82,   92,   16,   85,   95,
   87,   94,   89,   99,  100,  101,  102,  103,  104,  105,
  106,  107,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   14,   14,   85,   78,
   87,   87,   10,   85,   98,    4,    5,    6,   95,   95,
   97,   97,   91,    9,   13,   14,   85,   14,   87,   56,
   27,   28,   29,   59,   53,   54,   55,   14,   57,   58,
   59,   14,   19,   62,   14,   64,   65,   66,   67,   68,
   69,   70,   16,   72,   73,   74,   75,   76,   85,   78,
   87,   14,   92,   19,   83,   84,   78,   86,   95,   30,
   97,   82,   91,   31,  104,  101,   95,   85,   85,   91,
   14,   92,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   85,   16,   85,   18,
   19,   20,   21,   22,   23,  102,  103,   82,   85,   62,
   87,   91,   85,   93,   91,   25,   26,   92,   34,   35,
   51,   52,   61,   62,   36,   60,   79,   59,   62,   78,
   78,   78,   85,   78,   53,   54,   55,   78,   57,   58,
   59,   78,   78,   62,   82,   79,   79,   87,   67,   78,
   69,   85,   78,   72,   73,   74,   75,   76,   78,   78,
   78,   78,   84,   78,   83,   84,   79,   78,   82,   78,
   78,   94,   79,   79,   95,   99,   95,   -1,  103,   84,
   84,   84,  101,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   85,   16,   85,   18,
   19,   20,   21,   22,   23,   85,   85,   88,   86,   86,
   86,   86,   86,   86,   86,   86,   86,   86,  100,   87,
   -1,   88,   88,   88,   88,   88,   88,   88,   88,   88,
   88,   88,   88,   -1,   53,   54,   55,   90,   57,   58,
   90,   90,   14,   62,   90,   90,   90,   90,   67,   91,
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
   94,   78,   94,   94,   94,   94,   83,   84,   85,   94,
   96,   95,   95,   95,   95,   95,   93,    2,    3,    4,
    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   95,   16,   95,   18,   19,   20,   21,   22,   23,   95,
   95,   95,   95,   95,   95,   95,   95,   95,   95,   95,
   95,   95,   95,   95,   95,   95,   -1,   96,   96,   96,
   96,   96,   96,   96,   96,   96,   96,   96,   53,   54,
   55,   96,   57,   58,   96,   96,   96,   62,   96,   96,
   96,   96,   67,   96,   69,   96,   96,   72,   73,   74,
   75,   76,   96,   78,   96,   96,   96,   96,   83,   84,
   85,   96,   96,   96,   96,   96,   96,   96,   93,    2,
    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   96,   16,   96,   18,   19,   20,   21,   22,
   23,    1,    2,  101,    4,    5,    6,   -1,    8,   -1,
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
  595,  595,  595,  595,  595,  503,  687,  326,  308,  325,
  327,   -2,  104,  104,  104,  104,  104,  104,  353,  352,
  354,  311,   88,  241,  277,  277,  277,   75,  253,   49,
  158,  296,   63,   63,   63,   63,   61,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,  107,  257,  257,
  257,  257,  257,  257,  257,  257,  243,  243,  243,  243,
  223,  243,  243,  223,  243,  260,  223,  260,  243,  243,
  243,  243,  243,  222,  243,  243,  243,  260,  260,  243,
  243,  243,  243,  243,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,  458,  458,  458,  458,  458,  458,  458,   46,
  266,   29,   78,  545,  373,  374,  364,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,  113,
  113,  113,  113,  113,  203,  440,  -37,  -37,  -37,  -37,
  153,  153,  153,  153,  153,  -28,  -28,  -28,  -28,  -28,
  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,
  233,  233,  233,  138,    9,  171,  171,  171,  171,  171,
  218,  161,  -17,  -17,  -17,  -17,  -17,  154,  -77,  -77,
  -77,   81,  181,  181,  322,  289,  525,  526,  527,   92,
  274,  313,  312,  146,  320,  314,  200,  299,  291,  -26,
  406,  442,  250,  274,  313,  312,  301,  450,  456,  441,
  542,  204,  320,  314,  314,  314,  314,  314,  200,  200,
  299,  437,  544,  255,  543,  494,  541,  219,  351,  281,
  529,  282,  282,  305,   20,  486,  244,   20,   20,  486,
  310,   20,  529,  540,  540,  351,  351,  351,  455,  448,
  529,  232,  444,   20,  479,  479,  290,  290,  351,  351,
   20,  531,  351,  351,  351,  351,  351,  351,  531,  351,
  351,  351,  351,  351,  351,  351,  517,  515,  524,  500,
  475,  341,  412,  285,  321,  319,  315,  309,  307,   15,
  410,  269,  272,  306,  348,  612,  318,   45,  499,  409,
  407,  530,  497,  496,  446,  304,  528,  297,  350,  343,
  539,  538,  369,  562,  537,  536,  535,  517,  515,  524,
  500,  454,  453,  408,  285,  319,  457,  488,  459,  530,
  497,  496,  495,  368,  449,  491,  560,  559,  367,  558,
  401,  498,  149,   81,  397,  443,  460,  324,  533,  534,
  377,  360,  372,  390,  283,  386,  323,  555,  480,  588,
  452,  587,  586,  361,  567,  359,  449,  565,  295,  269,
  477,  272,  306,  348,  612,  318,  318,  318,  551,  447,
  532,  167,  371,  436,  294,  564,  461,  293,  358,  385,
  384,  380,  388,  317,  563,  550,  585,  357,  366,  581,
  580,  579,  578,  470,  608,  490,  489,  549,  298,  365,
  362,  362,  576,   76,  370,  183,  429,  570,  470,  606,
  356,  363,  474,  316,  387,  381,  391,  548,  349,  569,
  402,  384,  427,  591,  380,  380,  547,  590,  292,  380,
  355,  589,  355,  546,    0,    0,    0,    0,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,   -2,   -2,   -2,   -2,    0,
    0,    0,    0,    0,    0,    0,  311,  311,  311,    0,
  311,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,  895,  895,  895,  895,   -3,   -3,   -3,
    0,   -3,   -3,   -3,   -3,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   92,   92,   92,
   92,   92,  153,  153,  153,  153,  153,  153,    0,    0,
    0,    0,    0,   92,   92,   92,   92,   92,   92,   92,
   92,   92,   92,   92,   92,   92,   92,   92,    0,    0,
    0,    0,   92,   92,   92,   92,   92,   92,   20,   20,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -26,
    0,    0,   20,   20,  351,  351,  351,    0,  530,  497,
  496,    0,    0,    0,    0,    0,    0,    0,  445,  445,
    0,  530,  497,  496,  534,  451,  451,  451,  451,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  445,
  451,    0,  451,  451,  451
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 277

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  304,32767,32767,32767,
32767,32767,32767,32767,32767,  353,  354,  355,32767,32767,
32767,32767,  295,32767,  489,  489,  489,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  101,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,   90,  101,  101,
  101,  101,  101,  101,  101,  101,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,   90,
  346,32767,32767,32767,32767,   92,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  178,  180,32767,32767,32767,32767,32767,32767,  348,32767,
32767,  103,32767,32767,32767,32767,32767,  321,   89,  300,
  319,  495,  323,  329,  331,  305,   91,  320,  327,32767,
32767,32767,32767,32767,  190,32767,  188,  189,  186,  185,
  129,  496,  330,  332,  328,  470,  470,  470,  470,  470,
  470,  470,  470,  470,  470,  470,  470,  470,  470,32767,
  154,  155,  156,32767,32767,32767,32767,  349,  350,32767,
  343,  344,32767,32767,32767,32767,32767,  487,  166,  168,
  167,  430,  109,  109,  103,  103,32767,32767,32767,32767,
32767,32767,32767,  141,  152,  157,  163,  173,  175,  430,
32767,32767,32767,  364,  351,  352,32767,32767,32767,32767,
32767,32767,  153,  159,  161,  162,  158,  160,  164,  165,
  174,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  292,  103,  444,   77,  103,  103,  444,
32767,  103,32767,  468,  468,32767,32767,  340,  498,  294,
32767,   80,  294,  103,  462,  462,  482,  482,32767,32767,
  103,  485,32767,32767,32767,32767,32767,32767,  485,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  231,32767,
32767,  142,  144,  146,  148,  150,  169,32767,32767,32767,
32767,32767,32767,32767,  102,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  334,  336,  338,
  345,  212,  214,  215,  356,  357,  231,  232,32767,  364,
  351,  352,  231,32767,  296,32767,32767,32767,32767,32767,
32767,32767,32767,  213,32767,32767,32767,32767,32767,32767,
   51,32767,32767,32767,32767,32767,32767,32767,  474,32767,
  471,32767,32767,32767,32767,32767,  297,32767,32767,  143,
32767,  145,  147,  149,  151,  170,  171,  172,32767,  490,
32767,32767,32767,32767,32767,32767,32767,  295,32767,32767,
32767,  432,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  227,32767,  231,32767,32767,32767,32767,
  481,  479,32767,   62,32767,  289,32767,32767,32767,32767,
32767,32767,32767,32767,   54,  431,32767,32767,32767,32767,
32767,   75,32767,32767,  435,  434,32767,32767,32767,  433,
  450,32767,32767,32767,  498,  424,  424,  498
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  169,  169,  169,  169,  169,  169,  169,  169,  169,  169,
  169,  175,  559,  257,  258,  260,  272,  416,  274,  275,
  393,  276,  691,  824,  691,  691,  691,  691,  173,  171,
  171,  171,  163,  170,  163,  920,  171,  693,  632,  964,
  720,  167,  609,  919,  609,  432,  401,  402,  418,  447,
  448,  464,  470,  471,  949,  949,  263,  264,  265,  266,
  267,  606,  168,  167,  167,  167,  167,  167,  167,  167,
  167,  170,  170,  170,  170,  174,  170,  170,  173,  170,
  387,  178,  387,  159,  168,  159,  160,  164,  172,  165,
  176,  177,  991,  626,  166,  626,  626,  626,  626,  421,
  626,  626,  626,  626,  626,  626,  626,  626,  626,  626,
  626,  626,  626,  626,  626,  626,  626,  626,  626,  626,
  419,  697,  423,  697,  697,  697,  697,  698,  635,  698,
  698,  698,  698,  635,  635,  635,  635,  635,  610,  422,
  610,  811,  811,  811,  811,  811,  186,  187,  188,  189,
  948,  490,  424,  413,  420,  637,  492,  408,  408,  408,
  408,  408,  408,  408,  408,  408,  408,  408,  408,  408,
  408,  408,  559,  950,  950,  576,  231,  249,  249,  249,
  249,  249,  411,  412,  417,  445,  446,  449,  450,  451,
  452,  454,  462,  469,  479,  484,  485,  489,   14,   14,
  262,  976,   12,   13,   15,  457,  493,  500,  303,  433,
  466,  482,  483,  487,  491,  286,  501,  347,  503,  503,
  503,  503,  503,  347,  463,  562,  561,  570,  571,  569,
  568,  567,  958,  959,  286,  685,  681,  682,  674,  675,
  677,  679,  425,  426,  427,  579,  564,  211,  212,  956,
  957,  944,  945,  946,  938,  233,  939,  951,  952,  953,
  947,  577,  940,  285,  285,  285,  285,  285,  285,  285,
  285,  285,  285,  285,  285,  285,  285,  285,  285,  285,
  285,  285,  285,  285,  285,  285,  285,  285,  612,  597,
  378,  799,  800,  804,  805,  831,  801,  615,  616,  617,
  618,  619,  620,  621,  622,  623,  624,  625,  613,  614,
  612,  990,  806,  935,  992,  192,  191,  191,  191,  185,
  271,  185,  251,  191,  251,  456,  365,  366,  270,  365,
  366,  943,  311,  318,  486,  268,  269,  378,  378,  378,
  378,  378,  962,  726,  726,  229,  230,  605,  605,  350,
  971,  431,  927,  603,  359,  399,  305,  438,  313,  461,
  973,  300,  193,  350,  156,  192,    0,    0,  194,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  390,    0,    0,  394,  395,    0,    0,  403,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  442,    0,    0,    0,    0,    0,    0,  472
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 439

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
   54,   54,   52,   52,   52,    7,    7,   48,   48,    7,
    7,    7,    7,    7,    7,  106,    7,    7,    7,    7,
    7,    7,    7,   81,   81,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   36,   30,
   74,   67,   67,   67,   67,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   37,   37,   37,   37,   37,
   78,   37,   78,   37,   78,   74,   75,   75,   53,   75,
   75,  101,  101,  101,  101,   50,   50,   74,   74,   74,
   74,   74,   59,   59,   59,   51,   51,  107,  107,   30,
   94,   19,   79,  108,    9,  100,   90,  110,   88,  102,
  103,  112,   37,   30,  104,   37,   -1,   -1,   37,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   30,   -1,   -1,   30,   30,   -1,   -1,   30,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   30,   -1,   -1,   -1,   -1,   -1,   -1,   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  196,  207,    0,    0,  -63,    0,   72,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  137,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  128,    0,    0,  -41,    0,  -25,  228,  262,  119,   33,
    0,    0,   -4,  -26,   13,   -5,   24,   71,  117,  -76,
  198,  206,  101,  184,   90,    0,   -6,   -1, -162,  186,
    0,    0,    0,    0, -257,   19,  -18,  111,    0,  -83,
    0,    0,  -29,  -38,  289,  283,    0,    0,  106,  133,
  132,  263,    0,    0,    0,    0,    0,    0,   53,    0,
   62,    0,  -14,    0,  141,    0,  -57,  150,    0,   31,
   66,  108,   52,   42, -133,   23,   95,  115,  120,  -46,
   55,    0, -135
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  339,    9,   11,  502,  505,  504,  506,  507,  358,
  508,  302,  521,  509,  537,  538,  539,  510,  540,  392,
  511,  301,  574,  516,  517,  284,  518,  519,  252,  520,
  349,  522,  512,  513,  340,  161,  934,  190,  291,  611,
  636,  243,  341,  342,  343,  344,  345,  244,  210,  245,
  246,  228,  346,  247,  248,  680,  184,  727,  630,  690,
  716,  715,  717,  719,  921,  383,  384,  310,   35,  259,
  354,  299,  823,  711,  385,  364,  955,  555,  250,  926,
  441,  289,  556,  936,  638,  937,  557,  558,  312,  227,
  304,  961,  409,  410,  970,  696,  718,  428,  429,  989,
  256,  689,  460,  475,   89,  628,  232,  604,  598,  608,
  415,   29,  292
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
  108,  109,  109,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   36,   36,
   36,   37,   37,   37,   37,   37,   37,   37,   39,   39,
   40,   40,   41,   41,   42,   42,   43,   43,   44,   44,
   45,   45,   46,   46,   47,   47,   47,   48,   48,   48,
   48,   48,   48,   49,   49,   49,   50,   50,   50,   51,
   51,   51,   51,   52,   52,   53,   53,   53,   53,   53,
   53,   53,   54,   54,   54,   54,   54,   54,   54,   54,
   55,   55,   56,   56,   56,   56,   56,   56,   56,   95,
   95,   96,   96,   96,   96,   96,   96,   58,   58,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   73,   73,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   61,   61,
   60,   60,  111,   62,  110,  110,   65,   65,   68,   68,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   67,
   67,   67,   67,   67,   67,   67,   67,   67,   67,   69,
   69,   70,   70,   70,   70,   71,   71,   72,   72,   72,
   72,   72,   72,   72,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   63,   63,   63,  112,   64,   77,   77,   78,   78,
   79,   79,   79,   79,   79,   79,   80,   80,   82,   82,
   83,   83,   83,   81,  100,  100,   84,   84,   84,   84,
   84,   84,   84,   85,   85,   85,   75,   75,   86,   86,
   87,   87,   88,   88,   89,   89,   89,   89,   90,   90,
   92,   92,   93,   93,   94,   94,   94,   94,   94,  101,
  101,  101,  102,  102,  102,  103,  103,   91,   91,   97,
   97,   98,   98,   98,   98,   99,   99,   99,  104
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
    3,    1,    1,    1,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    1,    1,
    1,    2,    2,    4,    3,    3,    4,    2,    1,    5,
    1,    1,    1,    3,    1,    3,    1,    3,    1,    3,
    1,    3,    1,    3,    1,    3,    3,    1,    3,    3,
    3,    3,    3,    1,    3,    3,    1,    3,    3,    1,
    3,    3,    3,    1,    3,    1,    3,    3,    2,    3,
    2,    3,    1,    2,    2,    2,    2,    2,    2,    2,
    1,    3,    1,    2,    4,    3,    3,    4,    2,    1,
    1,    4,    8,    6,    7,    7,    8,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    6,    3,    3,    3,    3,    2,    2,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    2,    2,    3,
    2,    4,    0,    4,    0,    1,    1,    2,    1,    2,
    1,    3,    3,    2,    2,    3,    5,    5,    4,    1,
    1,    1,    1,    1,    1,    1,    1,    3,    3,    1,
    3,    1,    2,    3,    4,    1,    3,    5,    5,    3,
    3,    3,    3,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    2,
    2,    3,    3,    2,    0,    3,    3,    3,    1,    3,
    1,    4,    3,    6,    5,    5,    1,    3,    1,    1,
    6,    6,    7,    1,    0,    2,    5,    5,    5,    6,
    6,    6,    2,    6,    6,    6,    1,    1,    5,    5,
    3,    3,    0,    4,    1,    4,    3,    3,    0,    3,
    0,    1,    1,    3,    1,    4,    3,    3,    2,    2,
    1,    2,    0,    2,    3,    0,    3,    0,    3,    0,
    1,    1,    2,    3,    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 895
#define YYNLSTATES 498
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
        case 114:
#line 422 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 115:
#line 423 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 425 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 119:
#line 427 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 120:
#line 428 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 121:
#line 429 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 122:
#line 430 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 123:
#line 431 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 124:
#line 432 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 125:
#line 433 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 126:
#line 434 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 127:
#line 435 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 131:
#line 445 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 132:
#line 446 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 133:
#line 447 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 134:
#line 448 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 135:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 136:
#line 450 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 137:
#line 451 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 139:
#line 456 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 143:
#line 466 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 145:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 147:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 149:
#line 481 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 151:
#line 486 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 153:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 155:
#line 496 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 156:
#line 497 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 158:
#line 502 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 159:
#line 503 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 160:
#line 504 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 161:
#line 505 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 162:
#line 506 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 164:
#line 511 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 165:
#line 512 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 167:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 168:
#line 518 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 170:
#line 523 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 171:
#line 524 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 172:
#line 525 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 174:
#line 530 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 176:
#line 535 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 177:
#line 536 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 178:
#line 537 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 179:
#line 538 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 180:
#line 539 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 181:
#line 540 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 183:
#line 545 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 184:
#line 546 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 185:
#line 547 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 186:
#line 548 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 187:
#line 549 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 188:
#line 550 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 189:
#line 551 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 191:
#line 556 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 193:
#line 561 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 194:
#line 562 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 195:
#line 563 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 196:
#line 564 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 197:
#line 565 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 198:
#line 566 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 199:
#line 570 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 201:
#line 575 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 202:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 203:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 204:
#line 578 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 205:
#line 579 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 206:
#line 580 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 207:
#line 584 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 208:
#line 585 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 209:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 210:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 211:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 212:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 213:
#line 593 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 214:
#line 594 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 215:
#line 595 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 216:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 222:
#line 602 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 223:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 224:
#line 604 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 225:
#line 605 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 226:
#line 606 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 227:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 228:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 229:
#line 609 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 230:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 231:
#line 614 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 232:
#line 615 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 233:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 234:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 235:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 236:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 237:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 238:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 239:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 240:
#line 626 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 241:
#line 627 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 242:
#line 628 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 243:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 244:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 245:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 246:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 247:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("when"); } break;
        case 248:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 249:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 250:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 251:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 252:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 253:
#line 639 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 254:
#line 640 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 255:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 256:
#line 642 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 257:
#line 643 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 258:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 259:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 260:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 261:
#line 647 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 262:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 263:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 264:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 265:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 266:
#line 652 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 267:
#line 653 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 268:
#line 654 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 269:
#line 655 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 270:
#line 656 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 271:
#line 657 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 272:
#line 658 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 273:
#line 659 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 274:
#line 660 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 275:
#line 661 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 276:
#line 662 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 277:
#line 663 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 278:
#line 664 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 279:
#line 665 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 280:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 281:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 282:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 283:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 284:
#line 670 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 285:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 286:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 287:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 288:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 289:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 290:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 291:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 292:
#line 687 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 293:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 294:
#line 695 "src/kinx.y"
{} break;
        case 296:
#line 700 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 297:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 298:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 299:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 301:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 302:
#line 712 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 303:
#line 713 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 304:
#line 714 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 305:
#line 715 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 306:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_keyvalue_object(YYASP(3-5).strval, YYASP(5-5).obj)); } break;
        case 307:
#line 717 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_keyvalue_object(YYASP(3-5).strval, YYASP(5-5).obj)); } break;
        case 308:
#line 718 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 309:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 310:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 311:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 312:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 313:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 314:
#line 727 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 315:
#line 728 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 316:
#line 729 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 317:
#line 730 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 318:
#line 731 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 320:
#line 736 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 322:
#line 741 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 323:
#line 742 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 324:
#line 743 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 326:
#line 748 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 327:
#line 752 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 328:
#line 753 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 329:
#line 754 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 330:
#line 755 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 331:
#line 756 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 332:
#line 757 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 333:
#line 758 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 334:
#line 762 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 335:
#line 763 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 336:
#line 764 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 337:
#line 765 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 338:
#line 766 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 339:
#line 767 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 340:
#line 768 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 341:
#line 769 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 342:
#line 770 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 343:
#line 771 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 344:
#line 772 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 345:
#line 773 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 346:
#line 774 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 347:
#line 775 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 348:
#line 776 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 349:
#line 777 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 350:
#line 778 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 351:
#line 779 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 352:
#line 780 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 353:
#line 781 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 354:
#line 782 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 355:
#line 783 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 356:
#line 784 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 357:
#line 785 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 358:
#line 786 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 359:
#line 787 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 360:
#line 788 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 361:
#line 789 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 362:
#line 790 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 363:
#line 791 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 364:
#line 792 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 365:
#line 793 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 366:
#line 794 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 367:
#line 795 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 368:
#line 799 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 369:
#line 800 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 370:
#line 801 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 371:
#line 802 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 372:
#line 803 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 373:
#line 804 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 374:
#line 805 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 375:
#line 806 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 376:
#line 807 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 377:
#line 808 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 378:
#line 809 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 379:
#line 810 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 380:
#line 811 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 381:
#line 812 "src/kinx.y"
{ yyval.strval = "when"; } break;
        case 382:
#line 813 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 383:
#line 814 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 384:
#line 815 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 385:
#line 816 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 386:
#line 817 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 387:
#line 818 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 388:
#line 819 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 389:
#line 820 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 390:
#line 821 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 391:
#line 822 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 392:
#line 823 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 393:
#line 824 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 394:
#line 825 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 395:
#line 826 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 396:
#line 827 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 397:
#line 828 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 398:
#line 829 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 399:
#line 830 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 400:
#line 831 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 401:
#line 832 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 402:
#line 833 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 403:
#line 834 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 404:
#line 835 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 405:
#line 836 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 406:
#line 837 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 407:
#line 838 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 408:
#line 839 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 409:
#line 840 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 410:
#line 841 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 411:
#line 842 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 412:
#line 843 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 413:
#line 844 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 414:
#line 845 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 415:
#line 846 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 416:
#line 847 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 417:
#line 848 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 418:
#line 849 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 419:
#line 850 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 420:
#line 851 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 421:
#line 855 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 422:
#line 856 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 423:
#line 857 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 424:
#line 861 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 425:
#line 865 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 426:
#line 869 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 427:
#line 870 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 429:
#line 875 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 430:
#line 879 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 431:
#line 880 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 432:
#line 881 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 433:
#line 882 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 434:
#line 883 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 435:
#line 884 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 437:
#line 889 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 438:
#line 893 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 439:
#line 894 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 440:
#line 898 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 441:
#line 899 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 442:
#line 900 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 443:
#line 904 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 444:
#line 908 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 445:
#line 909 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 446:
#line 913 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 447:
#line 914 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 448:
#line 915 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 449:
#line 916 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 450:
#line 917 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 451:
#line 918 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 452:
#line 919 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 453:
#line 923 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 454:
#line 924 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 455:
#line 925 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 458:
#line 934 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 459:
#line 935 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 460:
#line 939 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 461:
#line 940 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 462:
#line 944 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 463:
#line 946 "src/kinx.y"
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
        case 465:
#line 962 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 466:
#line 963 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 467:
#line 964 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 468:
#line 968 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 469:
#line 969 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 470:
#line 973 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 473:
#line 979 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 474:
#line 983 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 475:
#line 984 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 476:
#line 985 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LARY_T); } break;
        case 477:
#line 986 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LOBJ_T); } break;
        case 478:
#line 987 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 479:
#line 991 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 480:
#line 992 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 481:
#line 993 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 482:
#line 997 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 483:
#line 998 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 484:
#line 999 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 485:
#line 1003 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 486:
#line 1004 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 487:
#line 1008 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 488:
#line 1009 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 489:
#line 1013 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 492:
#line 1019 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 493:
#line 1020 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 494:
#line 1021 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 497:
#line 1027 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 498:
#line 1031 "src/kinx.y"
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
