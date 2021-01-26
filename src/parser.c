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
#define ENUM 272
#define NEW 273
#define VAR 274
#define CONST 275
#define RETURN 276
#define THROW 277
#define YIELD 278
#define MIXIN 279
#define EQEQ 280
#define NEQ 281
#define LE 282
#define GE 283
#define LGE 284
#define LOR 285
#define LAND 286
#define INC 287
#define DEC 288
#define SHL 289
#define SHR 290
#define POW 291
#define LUNDEF 292
#define ADDEQ 293
#define SUBEQ 294
#define MULEQ 295
#define DIVEQ 296
#define MODEQ 297
#define ANDEQ 298
#define OREQ 299
#define XOREQ 300
#define LANDEQ 301
#define LOREQ 302
#define LUNDEFEQ 303
#define SHLEQ 304
#define SHREQ 305
#define REGEQ 306
#define REGNE 307
#define NUL 308
#define TRUE 309
#define FALSE 310
#define AS 311
#define IMPORT 312
#define USING 313
#define DARROW 314
#define SQ 315
#define DQ 316
#define MLSTR 317
#define BINEND 318
#define DOTS2 319
#define DOTS3 320
#define REGPF 321
#define NAMESPACE 322
#define SYSNS 323
#define SYSRET_NV 324
#define CLASS 325
#define SYSCLASS 326
#define MODULE 327
#define SYSMODULE 328
#define NATIVE 329
#define FUNCTION 330
#define SYSFUNC 331
#define PUBLIC 332
#define PRIVATE 333
#define PROTECTED 334
#define COROUTINE 335
#define NAME 336
#define STR 337
#define SRCFILE 338
#define BIGINT 339
#define INT 340
#define TYPE 341
#define TYPEOF 342
#define LBBR 343
#define RBBR 344
#define LMBR 345
#define RMBR 346
#define DBL 347
#define BIN 348
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
#line 1001 "src/kinx.y"

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
  "AssignExpressionList_Opt : /* empty */",
  "AssignExpressionList_Opt : AssignExpressionObjList",
  "Modifier_Opt : /* empty */",
  "Modifier_Opt : IF '(' AssignExpressionList ')'",
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
    0,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  108,  110,  110,  110,  106,  100,  110,
   94,   95,  104,  103,   92,   91,   96,  105,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,   93,   90,
  101,   89,  102,   97,  109,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,   99,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,   98,  110,  107,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110,  110,  110,    1,  110,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   57,   58,  110,  110,  110,   59,   60,
   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,  110
#line 165 "build/utility/kmyacc.c.parser"
};

#define YYBADCH 110
#define YYMAXLEX 349
#define YYTERMS 110
#define YYNONTERMS 108

static short yyaction[] = {
  710,  711,  712,  713,  714,  715,  716,  717,  718,  719,
  720,  721,  722,  723,  117,  724,  725,  726,  735,  737,
  736,  953,  746,  747,  748,  750,  752,  121,  299,  127,
  128,  744,  745,  300,   81,   82,   83,   84,   85,   86,
   87,   88,   89,   90,   91,   92,   93,-32766,-32766,-32766,
  738,  739,  740,-32766,  741,  742,  389,  129,  130,  131,
  340,   51,  340,   67,  733,  281,  734,  219,  727,  728,
  729,  730,  731,  732,   19,  709,-32766,-32766, -102,  514,
  743,  516,  515,  517,  379,  518,   95,    0,  118,  754,
  519,  520,  380,  521,  134,  135,  759,  760,  758,  749,
  751,  753,  755,  756,  757,  842,  843,  844,  845,  846,
  847,  848,  849,  850,  851,  852,  853,  854,-32766,  382,
  855,  856,  857,  865,  867,  866,  -75,  877,  878,  879,
  881,  883,  132,  133,  539,   97,  875,  876,  319,   16,
  320,  344,  345,  522,  460,  344,  345,  321,  523,   62,
  525,  524,  970,  -74,   51,  868,  869,  870,   49,  871,
  872,  513,  504, -346,  787,  789,  790,  512,  707,  863,
   27,  864,   28,  708,  858,  859,  860,  861,  862,  301,
  929,  209,  280,  684,  685,  873,  874,  136,   99,  354,
  112,  791,  786,  784,  885, -102,   33,  355,   34,  137,
  785,  890,  891,  889,  880,  882,  884,  886,  887,  888,
  157,  359,  810,  360,   10,  361,  814,  290,  816,  817,
  215,  216,  362,  108,  322,  323,  155,  212,  213,  291,
   59,   63,  272,  105,  344,  345,  254,  102,  111,  344,
  345,  344,  345,  344,  345,  542,   55,   51,   39,   26,
  970,  231,   49,   66,   49,  477,   49,  347,  344,  345,
  122,  363,  364,  365,  123,  246,  839,  117,  145,  146,
   79,   50,  274,  275,  324,  366,  326,  367,  328,  141,
  247,  248,   45,   46,   47,  114,  368,  319,   16,  320,
  116,  369,  841,  286,  530,    4,  321,  109,   56,  -98,
   40,  280,  217,   61,   27,   54,   32,   38,  766,  230,
  809,  810,  811,  812,  813,  814,  815,  816,  817,  818,
  819,  820,  821,  344,  345,  822,  823,  824,  832,  834,
  833,    4,  281,  109,  232,  583,   48,  344,  345,  344,
  345,   54,  536,   38,  378, -347,  405,  138,  139,  140,
   49,  581,   49,  395,  344,  345,  582,   30,  287,   31,
  835,  836,  837,  288,  838,  839,  117,   49,  289,   79,
  461,  344,  345,  457,  830,  421,  831,  147,  148,  825,
  826,  827,  828,  829,   51,  387,  344,  345,  396,  391,
  840,  841,  398,-32766,-32766,  344,  345,  353,  352,   48,
  426,  463,  388,  434,  678,  671,   68,  543,  389,  809,
  810,  811,  812,  813,  814,  815,  816,  817,  818,  819,
  820,  821,  540,  706,  155,  823,  824,  832,  834,  833,
  940,  673,-32766,-32766,-32766,  612,  797,    6,-32766,  283,
    7,    5,   58,  608,  799,  679,   51,  467,  793,  950,
  537,  768,  429,-32766,  449,    0,  957,  792,  610,  363,
  364,  365,-32766,  371,  839,-32766,-32766,  956,   80,-32766,
-32766,  949,  761,  830,  764,  831,  892,  470,  372,  373,
  827,  828,  829,  938,  374,  455,  430,  552,  218,  369,
  841,   51,  270,  266,  763,  103,  192,   74,   72,  773,
  809,  810,  811,  812,  813,  814,  815,  816,  817,  818,
  819,  820,  821,   71,  433,  155,  823,  824,  832,  834,
  833,  503,  573,  580,  572,  570,  575,   69,  900,  899,
  571,  569,  584,  574,   75,   73,   70,    0,    0,   36,
  427,  204,  113,  214,   53,  110,    0, -350, -349, -348,
  363,  364,  365, -345,  371,  839,  554,   52,   96,   80,
  100,  104,  119,  175,  830,  555,  831,  486,  176,  372,
  373,  827,  828,  829,  220,  374, -353,  208,  178,  177,
  369,  841,   51,  191,  190,   98,   94,   78,   77,   76,
  773,  809,  810,  811,  812,  813,  814,  815,  816,  817,
  818,  819,  820,  821,   57,  193,  155,  823,  824,  832,
  834,  833,  200,  425,  397,  349,  348,  221,  203,  202,
  201,  199,  198,  197,  196,  195,  194,    0,  702,   17,
   18,   20,   21,  302,  469,  701,  590,  961,  959,  700,
  613,  363,  364,  365,  942,  371,  839,  674,  898,  762,
   80,  703,  893,  464,  458,  830,  448,  831,  443,  317,
  372,  373,  827,  828,  829,  316,  374,  315,  314,  313,
  312,  369,  841,   51,  311,  309,  308,  307,  306,   24,
   23,  774,  809,  810,  811,  812,  813,  814,  815,  816,
  817,  818,  819,  820,  821,   22,    3,  155,  823,  824,
  832,  834,  833,  157,  318,    2,  319,   16,  320,  124,
  271,  125,    0,  227,  228,  321,  106,  322,  323,  126,
  210,  211,  483,   64,  107,  272,  765,    0,    0,    0,
    0,    0,  363,  364,  365,    0,  371,  839,    0,    0,
    0,  101,    0,    0,    0,    0,  830,    0,  831,    0,
    0,  372,  373,  827,  828,  829,    0,  445,  233,    0,
  117,    0,  369,  841,   51,  274,  275,  324,  325,  326,
  327,  328,    0,    0,    0,   42,   43,   44,    0,  330,
    0,    0,    0,    0,    0,    0,    0,  530,    0,    0,
    0,    0,  -98,  157,  318,    0,  319,   16,  320,    0,
  271,    0,  230,  227,  228,  321,  106,  322,  323,    0,
  210,  211,  483,   64,  107,  272,    0,    0,    0,    0,
    0,    0,    0,    0,  157,  318,    0,  319,   16,  320,
    0,  271,    0,    0,  227,  228,  321,  106,  322,  323,
    0,  210,  211,  483,   64,  107,  272,    0,  233,    0,
  115,    0,    0,    0,    0,  274,  275,  324,  325,  326,
  327,  328,    0,    0,    0,   42,   43,   44,    0,  330,
    0,    0,    0,    0,    0,    0,    0,  680,    0,  233,
    0,  120,  -98,    0,    0,    8,  274,  275,  324,  325,
  326,  327,  328,    0,    0,    0,   42,   43,   44,    0,
  330,    0,    0,    0,    0,    0,    0,    0,  680,    0,
    0,    0,    0,  -98,  157,  318,    8,  319,   16,  320,
    0,  271,    0,    0,  227,  228,  321,  106,  322,  323,
    0,  210,  211,  483,   64,  107,  272,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  154,    0,    0,    0,    0,    0,    0,    0,    0,  233,
    0,    0,    0,    0,  149,  150,  274,  275,  324,  325,
  326,  327,  328,  484,    0,    0,   42,   43,   44,    0,
  330,    0,    0,    0,    0,  689,  691,  692,    0,  343,
    0,    0,    0,  -98,    0,  273, -325,    0,    0,    0,
    0,    0,    0,  916,  234,  235,    0,    0,    0,  329,
  707,    0,  693,  688,  686,  708,    0,    1,    0,   25,
    0,  687,    0,    0,  151,    0,    0,   60,    0,   41,
    0,    0,    0,  229,  276,    0,  152,  142,  485,    0,
  143,  144,   37,   -1,  157,  318,    0,  319,   16,  320,
    0,  271,    0,    0,  227,  228,  321,  106,  322,  323,
    0,  210,  211,  483,   64,  107,  272,    0,    0,    0,
    0,    0,  157,  318,    0,  319,   16,  320,    0,  271,
    0,    0,  227,  228,  321,  106,  322,  323,    0,  210,
  211,  483,   64,  107,  272,    0,    0,    0,    0,  233,
    0,    0,    0,    0,    0,    0,  274,  275,  324,  325,
  326,  327,  328,    0,    0,    0,   42,   43,   44,    0,
  330,    0,    0,    0,    0,    0,    0,  233,    0,    0,
    0,    0,    0,  -98,  274,  275,  324,  325,  326,  327,
  328,    0,    0,    0,   42,   43,   44,    0,  330,    0,
    0,    0,    0,    0,    0,    0,  681,    0,    0,  157,
  318,  -98,  319,   16,  320,    0,  271,    0,    0,  227,
  228,  321,  106,  322,  323,    0,  210,  211,  483,   64,
  107,  272,    0,    0,    0,    0,    0,  157,  318,    0,
  319,   16,  320,    0,  271,    0,    0,  227,  228,  321,
  106,  322,  323,    0,  210,  211,  483,   64,  107,  272,
    0,    0,    0,    0,  233,    0,    0,    0,    0,    0,
    0,  274,  275,  324,  325,  326,  327,  328,    0,    0,
    0,   42,   43,   44,    0,  330,    0,    0,    0,    0,
    0,    0,  233,  532,    0,    0,    0,    0,  -98,  274,
  275,  324,  325,  326,  327,  328,    0,    0,    0,   42,
   43,   44,    0,  330,    0,    0,    0,    0,    0,    0,
    0,  531,    0,    0,  157,  318,  -98,  319,   16,  320,
    0,  271,    0,    0,  227,  228,  321,  106,  322,  323,
    0,  210,  211,  483,   64,  107,  272,    0,    0,    0,
    0,    0,  157,  318,    0,  319,   16,  320,    0,  271,
    0,    0,  227,  228,  321,  106,  322,  323,    0,  210,
  211,  483,   64,  107,  272,    0,    0,    0,    0,  233,
    0,    0,    0,    0,    0,    0,  274,  275,  324,  325,
  326,  327,  328,    0,    0,    0,   42,   43,   44,    0,
  330,    0,    0,    0,    0,    0,    0,  233,  530,    0,
    0,    0,    0,  -98,  274,  275,  324,  325,  326,  327,
  328,    0,    0,    0,   42,   43,   44,    0,  330,    0,
    0,    0,    0,    0,    0,    0,  533,    0,    0,  157,
  318,  -98,  319,   16,  320,    0,  271,    0,    0,  227,
  228,  321,  106,  322,  323,    0,  210,  211,  483,   64,
  107,  272,    0,    0,    0,    0,    0,  157,  318,    0,
  319,   16,  320,    0,  271,    0,    0,  227,  228,  321,
  106,  322,  323,    0,  210,  211,  483,   64,  107,  272,
    0,    0,    0,    0,  233,    0,    0,    0,    0,    0,
    0,  274,  275,  324,  325,  326,  327,  328,    0,    0,
    0,   42,   43,   44,    0,  330,    0,    0,    0,    0,
    0,    0,  233,  683,    0,    0,    0,    0,  -98,  274,
  275,  324,  325,  326,  327,  328,    0,    0,    0,   42,
   43,   44,    0,  330,    0,    0,    0,    0,    0,    0,
    0,  682,    0,    0,  157,  318,  -98,  319,   16,  320,
    0,  271,    0,    0,  227,  228,  321,  106,  322,  323,
    0,  210,  211,  483,   64,  107,  272,    0,    0,    0,
    0,    0,  157,  318,    0,  319,   16,  320,    0,  271,
    0,    0,  227,  228,  321,  106,  322,  323,    0,  210,
  211,  483,   64,  107,  272,    0,    0,    0,    0,  233,
    0,    0,    0,    0,    0,    0,  274,  275,  324,  325,
  326,  327,  328,    0,    0,    0,   42,   43,   44,    0,
  330,    0,    0,    0,    0,    0,    0,  233,  534,    0,
    0,    0,    0,  -98,  274,  275,  324,  325,  326,  327,
  328,    0,    0,    0,   42,   43,   44,    0,  330,    0,
    0,    0,    0,    0,    0,    0,  535,    0,    0,  157,
  318,  -98,  319,   16,  320,    0,  271,    0,    0,  227,
  228,  321,  106,  322,  323,    0,  210,  211,  483,   64,
  107,  272,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  233,    0,    0,    0,    0,    0,
    0,  274,  275,  324,  325,  326,  327,  328,    0,    0,
    0,   42,   43,   44,    0,  330,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -98
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1719

static char yycheck[] = {
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   58,   17,   18,   19,   20,   21,
   22,   70,   24,   25,   26,   27,   28,   36,   77,   24,
   25,   33,   34,   82,   37,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   70,   71,   72,
   52,   53,   54,   76,   56,   57,  100,   26,   27,   28,
    2,   84,    2,   89,   66,   77,   68,   93,   70,   71,
   72,   73,   74,   75,    3,   77,   58,  100,   90,    2,
   82,    4,    5,    6,   86,    8,   89,    0,   97,   91,
   13,   14,   94,   16,   33,   34,   98,   99,  100,  101,
  102,  103,  104,  105,  106,    2,    3,    4,    5,    6,
    7,    8,    9,   10,   11,   12,   13,   14,  100,    4,
   17,   18,   19,   20,   21,   22,    7,   24,   25,   26,
   27,   28,  101,  102,   81,   61,   33,   34,    4,    5,
    6,   71,   72,   66,   91,   71,   72,   13,   71,   89,
   73,   74,   78,    7,   84,   52,   53,   54,   84,   56,
   57,   84,   85,   93,   52,   53,   54,   90,   77,   66,
   84,   68,   86,   82,   71,   72,   73,   74,   75,   10,
   77,   18,   77,   31,   32,   82,   83,   91,    7,   86,
   22,   79,   80,   81,   91,   90,   84,   94,   86,  103,
   88,   98,   99,  100,  101,  102,  103,  104,  105,  106,
    1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
   21,   22,   23,   61,   71,   72,   84,    7,   86,   71,
   72,   71,   72,   71,   72,   81,   94,   84,   96,   86,
   78,    9,   84,   90,   84,   91,   84,   18,   71,   72,
   29,   52,   53,   54,   30,   56,   57,   58,   50,   51,
   61,   84,   63,   64,   65,   66,   67,   68,   69,   35,
   71,   72,   73,   74,   75,   58,   77,    4,    5,    6,
   86,   82,   83,   77,   85,   84,   13,   86,   94,   90,
   96,   77,   55,   94,   84,   94,   86,   96,   59,  100,
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   71,   72,   17,   18,   19,   20,   21,
   22,   84,   77,   86,   61,   77,   84,   71,   72,   71,
   72,   94,   77,   96,   78,   93,   78,  104,  105,  106,
   84,   90,   84,   92,   71,   72,   77,   84,   77,   86,
   52,   53,   54,   77,   56,   57,   58,   84,   77,   61,
   77,   71,   72,   77,   66,   77,   68,   60,   61,   71,
   72,   73,   74,   75,   84,   77,   71,   72,   77,   77,
   82,   83,   78,   31,   32,   71,   72,   77,   77,   84,
   78,   78,   94,   78,   85,   87,   90,   81,  100,    2,
    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   81,   83,   17,   18,   19,   20,   21,   22,
   83,   83,   70,   71,   72,   83,   85,   84,   76,   84,
   84,   84,   92,   85,   85,   85,   84,   86,   85,   85,
   85,   85,   85,   91,   86,   -1,   87,   87,   87,   52,
   53,   54,  100,   56,   57,  103,  104,   87,   61,  107,
  108,   87,   87,   66,   87,   68,   87,   87,   71,   72,
   73,   74,   75,   87,   77,   87,   87,   90,   93,   82,
   83,   84,   89,   89,   87,   89,   94,   89,   89,   92,
    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   89,   89,   17,   18,   19,   20,   21,
   22,   90,   90,   90,   90,   90,   90,   90,   90,   90,
   90,   90,   90,   90,   90,   90,   90,   -1,   -1,   92,
   92,   92,   92,   92,   92,   92,   -1,   93,   93,   93,
   52,   53,   54,   93,   56,   57,   93,   93,   93,   61,
   93,   93,   93,   93,   66,   93,   68,   93,   93,   71,
   72,   73,   74,   75,   93,   77,   93,   93,   93,   93,
   82,   83,   84,   94,   94,   94,   94,   94,   94,   94,
   92,    2,    3,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   94,   94,   17,   18,   19,   20,
   21,   22,   94,   94,   94,   94,   94,   94,   94,   94,
   94,   94,   94,   94,   94,   94,   94,   -1,   95,   95,
   95,   95,   95,   95,   95,   95,   95,   95,   95,   95,
   95,   52,   53,   54,   95,   56,   57,   95,   95,   95,
   61,   95,   95,   95,   95,   66,   95,   68,   95,   95,
   71,   72,   73,   74,   75,   95,   77,   95,   95,   95,
   95,   82,   83,   84,   95,   95,   95,   95,   95,   95,
   95,   92,    2,    3,    4,    5,    6,    7,    8,    9,
   10,   11,   12,   13,   14,   95,   95,   17,   18,   19,
   20,   21,   22,    1,    2,   95,    4,    5,    6,   98,
    8,   99,   -1,   11,   12,   13,   14,   15,   16,  100,
   18,   19,   20,   21,   22,   23,  102,   -1,   -1,   -1,
   -1,   -1,   52,   53,   54,   -1,   56,   57,   -1,   -1,
   -1,   61,   -1,   -1,   -1,   -1,   66,   -1,   68,   -1,
   -1,   71,   72,   73,   74,   75,   -1,   77,   56,   -1,
   58,   -1,   82,   83,   84,   63,   64,   65,   66,   67,
   68,   69,   -1,   -1,   -1,   73,   74,   75,   -1,   77,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,   -1,
   -1,   -1,   90,    1,    2,   -1,    4,    5,    6,   -1,
    8,   -1,  100,   11,   12,   13,   14,   15,   16,   -1,
   18,   19,   20,   21,   22,   23,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,    1,    2,   -1,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   -1,   18,   19,   20,   21,   22,   23,   -1,   56,   -1,
   58,   -1,   -1,   -1,   -1,   63,   64,   65,   66,   67,
   68,   69,   -1,   -1,   -1,   73,   74,   75,   -1,   77,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,   56,
   -1,   58,   90,   -1,   -1,   93,   63,   64,   65,   66,
   67,   68,   69,   -1,   -1,   -1,   73,   74,   75,   -1,
   77,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,
   -1,   -1,   -1,   90,    1,    2,   93,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   -1,   18,   19,   20,   21,   22,   23,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   17,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   56,
   -1,   -1,   -1,   -1,   31,   32,   63,   64,   65,   66,
   67,   68,   69,   40,   -1,   -1,   73,   74,   75,   -1,
   77,   -1,   -1,   -1,   -1,   52,   53,   54,   -1,   56,
   -1,   -1,   -1,   90,   -1,   62,   93,   -1,   -1,   -1,
   -1,   -1,   -1,   70,   71,   72,   -1,   -1,   -1,   76,
   77,   -1,   79,   80,   81,   82,   -1,   84,   -1,   86,
   -1,   88,   -1,   -1,   91,   -1,   -1,   94,   -1,   96,
   -1,   -1,   -1,  100,  101,   -1,  103,  104,  105,   -1,
  107,  108,  109,    0,    1,    2,   -1,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   -1,   18,   19,   20,   21,   22,   23,   -1,   -1,   -1,
   -1,   -1,    1,    2,   -1,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   -1,   18,
   19,   20,   21,   22,   23,   -1,   -1,   -1,   -1,   56,
   -1,   -1,   -1,   -1,   -1,   -1,   63,   64,   65,   66,
   67,   68,   69,   -1,   -1,   -1,   73,   74,   75,   -1,
   77,   -1,   -1,   -1,   -1,   -1,   -1,   56,   -1,   -1,
   -1,   -1,   -1,   90,   63,   64,   65,   66,   67,   68,
   69,   -1,   -1,   -1,   73,   74,   75,   -1,   77,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,   -1,    1,
    2,   90,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   -1,   18,   19,   20,   21,
   22,   23,   -1,   -1,   -1,   -1,   -1,    1,    2,   -1,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   -1,   18,   19,   20,   21,   22,   23,
   -1,   -1,   -1,   -1,   56,   -1,   -1,   -1,   -1,   -1,
   -1,   63,   64,   65,   66,   67,   68,   69,   -1,   -1,
   -1,   73,   74,   75,   -1,   77,   -1,   -1,   -1,   -1,
   -1,   -1,   56,   85,   -1,   -1,   -1,   -1,   90,   63,
   64,   65,   66,   67,   68,   69,   -1,   -1,   -1,   73,
   74,   75,   -1,   77,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   85,   -1,   -1,    1,    2,   90,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   -1,   18,   19,   20,   21,   22,   23,   -1,   -1,   -1,
   -1,   -1,    1,    2,   -1,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   -1,   18,
   19,   20,   21,   22,   23,   -1,   -1,   -1,   -1,   56,
   -1,   -1,   -1,   -1,   -1,   -1,   63,   64,   65,   66,
   67,   68,   69,   -1,   -1,   -1,   73,   74,   75,   -1,
   77,   -1,   -1,   -1,   -1,   -1,   -1,   56,   85,   -1,
   -1,   -1,   -1,   90,   63,   64,   65,   66,   67,   68,
   69,   -1,   -1,   -1,   73,   74,   75,   -1,   77,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,   -1,    1,
    2,   90,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   -1,   18,   19,   20,   21,
   22,   23,   -1,   -1,   -1,   -1,   -1,    1,    2,   -1,
    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,   13,
   14,   15,   16,   -1,   18,   19,   20,   21,   22,   23,
   -1,   -1,   -1,   -1,   56,   -1,   -1,   -1,   -1,   -1,
   -1,   63,   64,   65,   66,   67,   68,   69,   -1,   -1,
   -1,   73,   74,   75,   -1,   77,   -1,   -1,   -1,   -1,
   -1,   -1,   56,   85,   -1,   -1,   -1,   -1,   90,   63,
   64,   65,   66,   67,   68,   69,   -1,   -1,   -1,   73,
   74,   75,   -1,   77,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   85,   -1,   -1,    1,    2,   90,    4,    5,    6,
   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,   16,
   -1,   18,   19,   20,   21,   22,   23,   -1,   -1,   -1,
   -1,   -1,    1,    2,   -1,    4,    5,    6,   -1,    8,
   -1,   -1,   11,   12,   13,   14,   15,   16,   -1,   18,
   19,   20,   21,   22,   23,   -1,   -1,   -1,   -1,   56,
   -1,   -1,   -1,   -1,   -1,   -1,   63,   64,   65,   66,
   67,   68,   69,   -1,   -1,   -1,   73,   74,   75,   -1,
   77,   -1,   -1,   -1,   -1,   -1,   -1,   56,   85,   -1,
   -1,   -1,   -1,   90,   63,   64,   65,   66,   67,   68,
   69,   -1,   -1,   -1,   73,   74,   75,   -1,   77,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,   -1,    1,
    2,   90,    4,    5,    6,   -1,    8,   -1,   -1,   11,
   12,   13,   14,   15,   16,   -1,   18,   19,   20,   21,
   22,   23,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   56,   -1,   -1,   -1,   -1,   -1,
   -1,   63,   64,   65,   66,   67,   68,   69,   -1,   -1,
   -1,   73,   74,   75,   -1,   77,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   90
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1628,  209,  792,  823,  702, 1283, 1168, 1311, 1081, 1053,
  913, 1196, 1513, 1541, 1426, 1398, 1628, 1628, 1628, 1628,
 1628, 1628, 1628, 1628, 1628,  407,  407,  498,  498,  498,
  498,  498,  498,  498,  498,  589,  680,  340,  348,  352,
  347,   -2,  103,  103,  103,  103,  103,  103,  351,  358,
  359,  308,  283,   18,   74,   74,   74,  163,  172,  252,
  266,  268,  168,   70,  315,  315,  315,  170,  315,  315,
  315,  170,  170,  315,  170,  315,  300,  300,  300,  170,
  170,  170,  170,  170,  170,  170,  170,  170,  170,  170,
  170,  170,  170,  170,  300,  170,  170,  170,  300,  300,
  170,  170,  300,  170,  170,  170,  300,  300,  300,  300,
  187,  300,  300,  300,  324,  324,  300,  300,  300,  300,
  300,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,
  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,
  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  362,
  362,  362,  362,  362,  362,  362,   60,   77,  463,  540,
  318,  371,  396,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,  112,  112,  112,  112,  247,
  533,  211,  211,  211,  211,  152,  152,  152,  152,  152,
  273,  273,  273,  273,  273,  273,  273,  273,  273,  273,
  273,  273,  273,  273,  273,   31,   31,   31,  134,  220,
   86,   86,   86,   86,   86,  105,  -12,  -49,  -49,  -49,
  -49,  -49,  204,  243,  243,  243,  146,  224,  255,  511,
  518,  519,   91,  239,  321,  320,   -9,    5,   61,   96,
  218,  317,  -26,  439,  438,  261,  239,  321,  320,  298,
  534,  535,  316,  538,  -44,    5,   61,   61,   61,   61,
   61,   96,   96,  218,  437,  541,   53,  539,  536,  537,
  164,  357,  279,  521,  265,  265,  624,   58,  395,  242,
   58,   58,  395,  312,   58,  521,  532,  532,  357,  357,
  357,  460,  452,  521,  169,  448,   58,  474,  474,  368,
  368,  357,  357,  523,  357,  357,  357,  357,  357,  357,
  523,  357,  357,  357,  357,  357,  357,  357,  495,  494,
  510,  493,  472,  355,  443,  216,  281,  286,  291,  402,
  484,   87,  442,  231,  234,  611,  612,  619,  244,  115,
  492,  441,  440,  522,  490,  489,  453,  311,  520,  314,
  353,  356,  531,  530,  389,  557,  529,  528,  527,  495,
  494,  510,  493,  456,  455,  454,  216,  286,  464,  483,
  465,  522,  490,  489,  470,  387,  447,  475,  556,  385,
  554,  436,  491,  181,  146,  435,  434,  467,  322,  525,
  526,  404,  367,  399,  433,  258,  425,  325,  553,  481,
  583,  449,  582,  581,  319,  563,  366,  447,  561,  249,
  231,  469,  234,  611,  612,  619,  244,  244,  244,  552,
  350,  524,  230,  398,  446,  296,  559,  293,  365,  424,
  409,  406,  432,  323,  558,  549,  580,  364,  384,  579,
  575,  574,  573,  468,  610,  486,  485,  545,  227,  380,
  361,  361,  572,   71,  390,  119,  445,  570,  468,  601,
  341,  403,  408,  431,  544,  363,  370,  369,  564,  397,
  409,  444,  600,  406,  406,  543,  585,  326,  406,  360,
  584,  360,  542,    0,    0,    0,    0,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,   -2,   -2,   -2,   -2,    0,    0,
    0,    0,    0,    0,    0,  308,  308,  308,    0,  943,
  308,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,  943,  943,  943,  943,  943,  943,  943,
  943,  943,  943,   -3,    0,   -3,   -3,   -3,   -3,   -3,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   91,   91,   91,   91,  152,  152,  152,  152,
  152,  152,    0,    0,    0,    0,    0,   91,   91,   91,
   91,   91,   91,   91,   91,   91,   91,   91,   91,   91,
   91,   91,    0,    0,    0,    0,   91,   91,   91,   91,
   91,   91,   58,   58,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -26,   58,   58,  357,  357,  357,    0,
  522,  490,  489,    0,    0,    0,    0,    0,    0,    0,
  451,  451,    0,  522,  490,  489,  526,  450,  450,  450,
  450,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  451,  450,    0,  450,  450,  450
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 270

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  292,32767,32767,32767,
32767,32767,32767,32767,32767,  340,  341,  342,32767,32767,
32767,32767,32767,  283,  475,  475,  475,32767,32767,  100,
32767,32767,32767,   90,  100,  100,  100,32767,  100,  100,
  100,32767,32767,  100,32767,  100,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,   90,  334,32767,
32767,32767,   92,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  168,  170,32767,
32767,32767,32767,32767,32767,  335,  102,32767,32767,32767,
32767,32767,32767,  309,   89,  288,  307,  481,  311,  317,
  319,  293,   91,  308,  315,32767,32767,32767,32767,  180,
32767,  178,  179,  176,  175,  120,  482,  318,  320,  316,
  456,  456,  456,  456,  456,  456,  456,  456,  456,  456,
  456,  456,  456,  456,32767,  144,  145,  146,32767,32767,
32767,32767,  336,  337,32767,  331,  332,32767,32767,32767,
32767,32767,  473,  156,  158,  157,  416,  102,  102,32767,
32767,32767,32767,32767,32767,32767,  131,  142,  147,  153,
  163,  165,  416,32767,32767,32767,  351,  338,  339,32767,
32767,32767,32767,32767,32767,  143,  149,  151,  152,  148,
  150,  154,  155,  164,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,  280,  102,  430,   77,
  102,  102,  430,32767,  102,32767,  454,  454,32767,32767,
  328,  484,  282,32767,   80,  282,  102,  448,  448,  468,
  468,32767,32767,  471,32767,32767,32767,32767,32767,32767,
  471,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  220,32767,32767,  132,  134,  136,  138,  140,  159,32767,
32767,32767,32767,32767,32767,32767,  101,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,  322,
  324,  326,  333,  202,  204,  205,  343,  344,  220,  221,
32767,  351,  338,  339,  220,32767,  284,32767,32767,32767,
32767,32767,32767,32767,  203,32767,32767,32767,32767,32767,
32767,   51,32767,32767,32767,32767,32767,32767,32767,  460,
32767,  457,32767,32767,32767,32767,32767,  285,32767,32767,
  133,32767,  135,  137,  139,  141,  160,  161,  162,32767,
  476,32767,32767,32767,32767,32767,32767,  283,32767,32767,
32767,  418,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  216,32767,  220,32767,32767,32767,32767,
  467,  465,32767,   62,32767,  277,32767,32767,32767,32767,
32767,   54,  417,32767,32767,32767,32767,32767,32767,32767,
   75,32767,32767,  421,  420,32767,32767,32767,  419,  436,
32767,32767,32767,  484,  410,  410,  484
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  165,  165,  165,  165,  165,  165,  165,  165,  165,  165,
  165,  171,  296,  424,  407,  456,  471,  472,  801,  384,
  476,  670,  480,  670,  670,  670,  670,  169,  966,  167,
  167,  167,  166,  167,  163,  159,  159,  548,  164,  163,
  163,  163,  410,  163,  163,  163,  447,  482,  163,  412,
  163,  166,  166,  166,  677,  614,  677,  677,  677,  677,
  614,  614,  614,  614,  614,  413,  924,  924,  264,  166,
  244,  170,  244,  166,  166,  169,  415,  166,  414,  174,
  263,  158,  164,  158,  160,  168,  161,  172,  173,  606,
  255,  162,  357,  358,  606,  357,  358,  946,  606,  606,
  422,  606,  672,  611,  939,  699,  606,  606,  606,  606,
  606,  606,  606,  606,  606,  606,  606,  606,  606,  606,
  606,  902,  606,  351,  606,  390,  473,  474,  606,  478,
  606,  676,  606,  676,  676,  676,  676,  788,  788,  788,
  788,  923,  479,  298,  404,  411,  616,  481,  181,  182,
  183,  184,  399,  399,  399,  399,  399,  399,  399,  399,
  399,  399,  399,  399,  399,  399,  399,  918,  303,  310,
  475,  226,  242,  242,  242,  242,  242,  416,  417,  418,
  428,  925,  925,  565,  423,  392,  393,  409,  437,  438,
  454,  465,  466,  548,  951,  278,  278,  278,  278,  278,
  278,  278,  278,  278,  278,  278,  278,  278,  278,  278,
  278,  278,  278,  278,  278,  278,  278,  278,  278,  278,
  937,  704,  704,  279,  402,  403,  408,  435,  436,  439,
  440,  441,  442,  444,  452,  459,  468,  777,  781,  782,
  933,  934,  279,  664,  660,  661,  653,  654,  656,  658,
  206,  207,  293,  568,  553,  592,  931,  932,  919,  920,
  921,  913,  153,  914,  926,  927,  928,  922,  566,  915,
  586,  305,  808,  778,  595,  596,  597,  598,  599,  600,
  601,  602,  603,  604,  605,  593,  594,  895,  592,  451,
  965,  489,  224,  225,  783,  894,  910,  370,  967,    0,
  490,  339,  492,  492,  492,  492,  492,  339,  453,  551,
  550,  559,  560,  558,  557,  556,  187,  948,  186,  186,
  186,    0,  186,    0,  180,  180,  261,  262,    0,    0,
  342,    0,  446,  250,  251,  253,  256,  257,  258,  259,
  260,    0,  342,    0,  370,  370,  370,  370,    0,  370,
    0,  265,    0,    0,    0,  267,  268,   14,   14,  269,
  188,   12,   13,   15,  187,    0,    0,    0,  189,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  381,    0,    0,  385,  386,    0,    0,  394,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  432
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 411

static char yygcheck[] = {
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   38,   38,   66,   38,   38,   38,   72,   73,
   38,   58,   38,   58,   58,   58,   58,   35,   99,   35,
   35,   35,   35,   35,   35,   35,   35,   33,   35,   35,
   35,   35,   42,   35,   35,   35,   97,   97,   35,   43,
   35,   35,   35,   35,   96,   96,   96,   96,   96,   96,
   96,   96,   96,   96,   96,   44,    7,    7,   78,   35,
   78,   35,   78,   35,   35,   35,   46,   35,   45,   35,
   53,   35,   35,   35,   35,   35,   35,   35,   35,   39,
   47,   35,   75,   75,   39,   75,   75,   94,   39,   39,
   19,   39,   57,   57,   57,   57,   39,   39,   39,   39,
   39,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   39,   79,   39,    9,   39,  100,   80,   80,   39,   80,
   39,    7,   39,    7,    7,    7,    7,   73,   73,   73,
   73,   39,   39,   90,   39,   39,   39,   39,   56,   56,
   56,   56,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,  101,  101,  101,
  101,   73,   73,   73,   73,   73,   73,   52,   52,   52,
  105,    7,    7,    7,   65,   65,   65,   65,   65,   65,
   65,   65,   65,   33,   73,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   81,   81,   81,   81,   81,   81,   81,   81,   81,   81,
   59,   59,   59,    7,   92,   92,   92,   92,   92,   92,
   92,   92,   92,   92,   92,   92,   92,   67,   67,   67,
    7,    7,    7,   54,   54,   54,   54,   54,   54,   54,
   48,   48,  107,    7,    7,   36,    7,    7,    7,    7,
    7,    7,  104,    7,    7,    7,    7,    7,    7,    7,
   30,   88,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   64,   36,  102,
   36,    4,   51,   51,   36,   64,   36,   74,   36,   -1,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,   37,  103,   37,   37,
   37,   -1,   37,   -1,   37,   37,   50,   50,   -1,   -1,
   30,   -1,   74,   69,   69,   69,   49,   49,   49,   49,
   49,   -1,   30,   -1,   74,   74,   74,   74,   -1,   74,
   -1,   69,   -1,   -1,   -1,   69,   69,    3,    3,   69,
   37,    3,    3,    3,   37,   -1,   -1,   -1,   37,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   30,   -1,   -1,   30,   30,   -1,   -1,   30,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   30
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  355,  291,    0,    0,  -48,    0, -152,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -109,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  114,    0,    0,  -15,    0,  -25,  193,  264,  -53,   27,
    0,    0,  -79,  -73,  -58,  -46,  -49,  -36,  123,  207,
  192,  156,   39,  -61,  101,    0,   -1,   64, -158,   67,
    0,    0,    0,    0,    2,  158,  -21,   61,    0,  257,
    0,    0,  -35,  -38,  296,   49,    0,    0, -141,  -93,
   55,  195,    0,    0,    0,    0,    0,    0,  -27,    0,
 -144,    0,   33,    0, -107,    0, -125,   -9,    0,  -30,
 -157,  -51,  -11,    7, -224, -115,    0, -233
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  331,    9,   11,  491,  494,  493,  495,  496,  350,
  497,  295,  510,  498,  526,  527,  528,  499,  529,  383,
  500,  294,  563,  505,  506,  277,  507,  508,  245,  509,
  341,  511,  501,  502,  332,  156,  909,  185,  284,  591,
  615,  236,  333,  334,  335,  336,  337,  237,  205,  238,
  239,  223,  338,  240,  241,  659,  179,  705,  609,  669,
  695,  694,  696,  698,  896,  375,  376,  776,   35,  252,
  346,  292,  800,  690,  377,  356,  930,  544,  243,  901,
  431,  282,  545,  911,  617,  912,  546,  547,  304,  222,
  297,  936,  400,  401,  945,  675,  697,  419,  420,  964,
  249,  668,  450,  462,   65,  406,   29,  285
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
   73,   73,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   61,   61,   60,   60,
  106,   62,  105,  105,   65,   65,   68,   68,   66,   66,
   66,   66,   66,   66,   66,   66,   66,   67,   67,   67,
   67,   67,   67,   67,   67,   67,   67,   69,   69,   70,
   70,   70,   70,   71,   71,   72,   72,   72,   72,   72,
   72,   72,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,   76,   63,   63,   63,
  107,   64,   77,   77,   78,   78,   79,   79,   79,   79,
   79,   79,   80,   80,   82,   82,   83,   83,   83,   81,
  100,  100,   84,   84,   84,   84,   84,   84,   84,   85,
   85,   85,   75,   75,   86,   86,   87,   87,   88,   88,
   89,   89,   89,   89,   90,   90,   92,   92,   93,   93,
   94,   94,   94,   94,   94,  101,  101,  101,  102,  102,
  102,  103,  103,   91,   91,   97,   97,   98,   98,   98,
   98,   99,   99,   99,  104
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
    0,    1,    0,    4,    1,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    1,
    1,    2,    2,    4,    3,    3,    4,    2,    1,    5,
    1,    1,    1,    3,    1,    3,    1,    3,    1,    3,
    1,    3,    1,    3,    1,    3,    3,    1,    3,    3,
    3,    3,    3,    1,    3,    3,    1,    3,    3,    1,
    3,    3,    3,    1,    3,    1,    3,    3,    2,    3,
    2,    3,    1,    2,    2,    2,    2,    2,    2,    2,
    1,    3,    1,    2,    4,    3,    3,    4,    2,    1,
    1,    4,    8,    6,    7,    7,    8,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    6,    3,    3,    3,    2,    2,    2,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    2,    2,    2,    3,    2,    4,
    0,    4,    0,    1,    1,    2,    1,    2,    1,    3,
    3,    2,    2,    3,    5,    5,    4,    1,    1,    1,
    1,    1,    1,    1,    1,    3,    3,    1,    3,    1,
    2,    3,    4,    1,    3,    5,    5,    3,    3,    3,
    3,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    2,    2,    3,    3,    2,
    0,    3,    3,    3,    1,    3,    1,    4,    3,    6,
    5,    5,    1,    3,    1,    1,    6,    6,    7,    1,
    0,    2,    5,    5,    5,    6,    6,    6,    2,    6,
    6,    6,    1,    1,    5,    5,    3,    3,    0,    4,
    1,    4,    3,    3,    0,    3,    0,    1,    1,    3,
    1,    4,    3,    3,    2,    2,    1,    2,    0,    2,
    3,    0,    3,    0,    3,    0,    1,    1,    2,    3,
    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 871
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
#line 164 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 169 "src/kinx.y"
{ kx_ast_root = yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 5:
#line 174 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 16:
#line 191 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strval, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 17:
#line 192 "src/kinx.y"
{ yyerrok; } break;
        case 25:
#line 203 "src/kinx.y"
{ yyerrok; } break;
        case 26:
#line 204 "src/kinx.y"
{ yy_restart(LBBR); yyerrok; } break;
        case 27:
#line 205 "src/kinx.y"
{ yy_restart(IF); yyerrok; } break;
        case 28:
#line 206 "src/kinx.y"
{ yy_restart(DO); yyerrok; } break;
        case 29:
#line 207 "src/kinx.y"
{ yy_restart(WHILE); yyerrok; } break;
        case 30:
#line 208 "src/kinx.y"
{ yy_restart(FOR); yyerrok; } break;
        case 31:
#line 209 "src/kinx.y"
{ yy_restart(TRY); yyerrok; } break;
        case 32:
#line 210 "src/kinx.y"
{ yy_restart(SWITCH); yyerrok; } break;
        case 33:
#line 211 "src/kinx.y"
{ yy_restart(CASE); yyerrok; } break;
        case 34:
#line 212 "src/kinx.y"
{ yy_restart(ENUM); yyerrok; } break;
        case 35:
#line 213 "src/kinx.y"
{ yy_restart(CLASS); yyerrok; } break;
        case 36:
#line 214 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; } break;
        case 37:
#line 215 "src/kinx.y"
{ yy_restart(PRIVATE); yyerrok; } break;
        case 38:
#line 216 "src/kinx.y"
{ yy_restart(PUBLIC); yyerrok; } break;
        case 43:
#line 227 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 44:
#line 228 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 45:
#line 232 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 233 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 47:
#line 234 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 235 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 49:
#line 239 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strval); } break;
        case 50:
#line 243 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 51:
#line 247 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strval); } break;
        case 52:
#line 248 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strval, YYASP(3-3).intval); } break;
        case 53:
#line 249 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strval, -YYASP(4-4).intval); } break;
        case 54:
#line 250 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strval)); } break;
        case 55:
#line 251 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strval, YYASP(5-5).intval)); } break;
        case 56:
#line 252 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strval, -YYASP(6-6).intval)); } break;
        case 61:
#line 263 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 62:
#line 267 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 63:
#line 268 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 64:
#line 272 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 65:
#line 276 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 66:
#line 280 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 284 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 285 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 290 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 70:
#line 297 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 71:
#line 304 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 72:
#line 311 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 73:
#line 313 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 74:
#line 317 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 75:
#line 318 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 76:
#line 322 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 77:
#line 326 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 78:
#line 327 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, "_e", YYASP(2-2).obj, NULL); } break;
        case 79:
#line 328 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(3-5).strval, YYASP(5-5).obj, NULL); } break;
        case 80:
#line 332 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 81:
#line 333 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 82:
#line 337 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 83:
#line 338 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strval)); } break;
        case 84:
#line 339 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 85:
#line 340 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strval)); } break;
        case 86:
#line 344 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 87:
#line 345 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 88:
#line 349 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 89:
#line 353 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 90:
#line 354 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 91:
#line 355 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 92:
#line 356 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 93:
#line 360 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 94:
#line 364 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 95:
#line 368 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object(YYASP(1-1).strval, KX_OBJ_T), NULL); } break;
        case 96:
#line 369 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object(YYASP(3-3).strval, KX_OBJ_T), NULL); } break;
        case 97:
#line 373 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 98:
#line 377 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 99:
#line 378 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 100:
#line 382 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 102:
#line 387 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 103:
#line 388 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 105:
#line 393 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 106:
#line 394 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 107:
#line 395 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 108:
#line 396 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 109:
#line 397 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 110:
#line 398 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 111:
#line 399 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 400 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 401 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 402 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 403 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 404 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 405 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 406 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 121:
#line 415 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 122:
#line 416 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 123:
#line 417 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 124:
#line 418 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 125:
#line 419 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 126:
#line 420 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 127:
#line 421 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 129:
#line 426 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 133:
#line 436 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 135:
#line 441 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 137:
#line 446 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 139:
#line 451 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 141:
#line 456 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 143:
#line 461 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 145:
#line 466 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 146:
#line 467 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 148:
#line 472 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 149:
#line 473 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 150:
#line 474 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 151:
#line 475 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 152:
#line 476 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 154:
#line 481 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 155:
#line 482 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 157:
#line 487 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 158:
#line 488 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 160:
#line 493 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 161:
#line 494 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 162:
#line 495 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 164:
#line 500 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 166:
#line 505 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 167:
#line 506 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 168:
#line 507 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 169:
#line 508 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 170:
#line 509 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 171:
#line 510 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 173:
#line 515 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 174:
#line 516 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 175:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 176:
#line 518 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 177:
#line 519 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 178:
#line 520 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 179:
#line 521 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 181:
#line 526 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 183:
#line 531 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 184:
#line 532 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 185:
#line 533 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 186:
#line 534 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 187:
#line 535 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 188:
#line 536 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 189:
#line 540 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 191:
#line 545 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 192:
#line 546 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 193:
#line 547 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 194:
#line 548 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 195:
#line 549 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 196:
#line 550 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 197:
#line 554 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 198:
#line 555 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 199:
#line 559 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 200:
#line 560 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 201:
#line 561 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 202:
#line 562 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 203:
#line 563 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 204:
#line 564 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 205:
#line 565 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 206:
#line 566 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 212:
#line 572 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 213:
#line 573 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 214:
#line 574 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 215:
#line 575 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 216:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 217:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 218:
#line 578 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 219:
#line 579 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 220:
#line 583 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 221:
#line 584 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 222:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 223:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 224:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 225:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 226:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 227:
#line 593 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 228:
#line 594 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 229:
#line 595 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 230:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 231:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 232:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 233:
#line 599 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 234:
#line 600 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 235:
#line 601 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 236:
#line 602 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 237:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 238:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 239:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 240:
#line 606 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 241:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 242:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 243:
#line 609 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 244:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 245:
#line 611 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 246:
#line 612 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 247:
#line 613 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 248:
#line 614 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 249:
#line 615 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 250:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 251:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 252:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 253:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 254:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 255:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 256:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 257:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 258:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 259:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 260:
#line 626 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 261:
#line 627 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 262:
#line 628 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 263:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 264:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 265:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 266:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 267:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 268:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 269:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 270:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 271:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 272:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 273:
#line 639 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 274:
#line 640 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 275:
#line 641 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 276:
#line 645 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 277:
#line 646 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 278:
#line 650 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 279:
#line 651 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 280:
#line 655 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 281:
#line 659 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 282:
#line 663 "src/kinx.y"
{} break;
        case 284:
#line 668 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 285:
#line 669 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 286:
#line 673 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 287:
#line 674 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 289:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 290:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 291:
#line 681 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 292:
#line 682 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 293:
#line 683 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 294:
#line 684 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_keyvalue_object(YYASP(3-5).strval, YYASP(5-5).obj)); } break;
        case 295:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_keyvalue_object(YYASP(3-5).strval, YYASP(5-5).obj)); } break;
        case 296:
#line 686 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 297:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 298:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 299:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 300:
#line 693 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 301:
#line 694 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 302:
#line 695 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 303:
#line 696 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 304:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 305:
#line 698 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 306:
#line 699 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 308:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 310:
#line 709 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 311:
#line 710 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 312:
#line 711 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 314:
#line 716 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 315:
#line 720 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 316:
#line 721 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 317:
#line 722 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 318:
#line 723 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 319:
#line 724 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 320:
#line 725 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 321:
#line 726 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 322:
#line 730 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 323:
#line 731 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 324:
#line 732 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 325:
#line 733 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 326:
#line 734 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 327:
#line 735 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 328:
#line 736 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 329:
#line 737 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 330:
#line 738 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 331:
#line 739 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 332:
#line 740 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 333:
#line 741 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 334:
#line 742 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 335:
#line 743 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 336:
#line 744 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 337:
#line 745 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 338:
#line 746 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 339:
#line 747 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 340:
#line 748 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 341:
#line 749 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 342:
#line 750 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 343:
#line 751 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 344:
#line 752 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 345:
#line 753 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 346:
#line 754 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 347:
#line 755 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 348:
#line 756 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 349:
#line 757 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 350:
#line 758 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 351:
#line 759 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 352:
#line 760 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 353:
#line 761 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 354:
#line 762 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 355:
#line 766 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 356:
#line 767 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 357:
#line 768 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 358:
#line 769 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 359:
#line 770 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 360:
#line 771 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 361:
#line 772 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 362:
#line 773 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 363:
#line 774 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 364:
#line 775 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 365:
#line 776 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 366:
#line 777 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 367:
#line 778 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 368:
#line 779 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 369:
#line 780 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 370:
#line 781 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 371:
#line 782 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 372:
#line 783 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 373:
#line 784 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 374:
#line 785 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 375:
#line 786 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 376:
#line 787 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 377:
#line 788 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 378:
#line 789 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 379:
#line 790 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 380:
#line 791 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 381:
#line 792 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 382:
#line 793 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 383:
#line 794 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 384:
#line 795 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 385:
#line 796 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 386:
#line 797 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 387:
#line 798 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 388:
#line 799 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 389:
#line 800 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 390:
#line 801 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 391:
#line 802 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 392:
#line 803 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 393:
#line 804 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 394:
#line 805 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 395:
#line 806 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 396:
#line 807 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 397:
#line 808 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 398:
#line 809 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 399:
#line 810 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 400:
#line 811 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 401:
#line 812 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 402:
#line 813 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 403:
#line 814 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 404:
#line 815 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 405:
#line 816 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 406:
#line 817 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 407:
#line 821 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 408:
#line 822 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 409:
#line 823 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 410:
#line 827 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 411:
#line 831 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 412:
#line 835 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 413:
#line 836 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 415:
#line 841 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 416:
#line 845 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 417:
#line 846 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 418:
#line 847 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 419:
#line 848 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 420:
#line 849 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 421:
#line 850 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 423:
#line 855 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 424:
#line 859 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 425:
#line 860 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 426:
#line 864 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 427:
#line 865 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 428:
#line 866 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 429:
#line 870 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 430:
#line 874 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 431:
#line 875 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 432:
#line 879 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 433:
#line 880 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 434:
#line 881 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 435:
#line 882 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 436:
#line 883 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 437:
#line 884 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 438:
#line 885 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 439:
#line 889 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 440:
#line 890 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 441:
#line 891 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 444:
#line 900 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 445:
#line 901 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 446:
#line 905 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 447:
#line 906 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 448:
#line 910 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 449:
#line 912 "src/kinx.y"
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
        case 451:
#line 928 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 452:
#line 929 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 453:
#line 930 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 454:
#line 934 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 455:
#line 935 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 456:
#line 939 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 459:
#line 945 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 460:
#line 949 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 461:
#line 950 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 462:
#line 951 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LARY_T); } break;
        case 463:
#line 952 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LOBJ_T); } break;
        case 464:
#line 953 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 465:
#line 957 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 466:
#line 958 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 467:
#line 959 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 468:
#line 963 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 469:
#line 964 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 470:
#line 965 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 471:
#line 969 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 472:
#line 970 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 473:
#line 974 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 474:
#line 975 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 475:
#line 979 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 478:
#line 985 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 479:
#line 986 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 480:
#line 987 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 483:
#line 993 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 484:
#line 997 "src/kinx.y"
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
