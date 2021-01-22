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
#line 946 "src/kinx.y"

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
  "KeySpecialName : SHL",
  "KeySpecialName : SHR",
  "KeySpecialName : EQEQ",
  "KeySpecialName : NEQ",
  "KeySpecialName : LE",
  "KeySpecialName : '<'",
  "KeySpecialName : GE",
  "KeySpecialName : '>'",
  "KeySpecialName : LGE",
  "KeySpecialName : '+'",
  "KeySpecialName : '-'",
  "KeySpecialName : '*'",
  "KeySpecialName : '/'",
  "KeySpecialName : '%'",
  "KeySpecialName : '&'",
  "KeySpecialName : '|'",
  "KeySpecialName : '^'",
  "KeySpecialName : LMBR RMBR",
  "KeySpecialName : '(' ')'",
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
  "ClassFunctionName : KeySpecialName",
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
#define YYNONTERMS 106

static short yyaction[] = {
  159,  361,  790,  362,   10,  363,  794,  291,  796,  797,
  213,  214,  364,  107,  324,  325,  157,  210,  211,  292,
   58,   61,  273,  824,  825,  826,  828,  830,  137,  138,
  139,  104,  822,  823,   80,   81,   82,   83,   84,   85,
   86,   87,   88,   89,   90,   91,   92,  342,  917,-32766,
    0,  365,  366,  367,   26,  246,  819,  116,  111,  342,
   78,   19,  275,  276,  326,  368,  328,  369,  330,  231,
  247,  248,   38,   39,   40,  -74,  370,  207,  128,  129,
  130,  371,  821,  120,  524,   43,   94,  678,  679,  -98,
  153,  836,   51,   56,   52,  379,   79,  837,  838,  228,
  229,  829,  154,  144,  293,  835,  789,  790,  791,  792,
  793,  794,  795,  796,  797,  798,  799,  800,  801,   28,
   26,  802,  803,  804,  812,  814,  813,  767,  824,  825,
  826,  828,  830,-32766,-32766,-32766,   79,  822,  823,-32766,
  255,  116,  110,   28,  117,   44,   60,   28,  100,   65,
   46,   96,   31,  131,  132,   28,  815,  816,  817,   28,
  818,  819,  116,-32766, -332,   78,   98,  768,  917,  281,
  810,   28,  811,  900,   26,  805,  806,  807,  808,  809,
  301,  384, -102,  442,  282,  302,  820,  821,  375,  135,
  356,  321,   16,  322,   26,  832,  -75, -102,  254,  101,
  323,  136,  837,  838,  385,  827,  829,  831,  833,  834,
  835,  704,  705,  706,  707,  708,  709,  710,  711,  712,
  713,  714,  715,  716,  717,  230,  718,  719,  720,  729,
  731,  730,  303,  740,  741,  742,  744,  746,    4,  115,
  108,   79,  738,  739,  321,   16,  322,   47,   45,   32,
   30,-32766,  402,  323,-32766,  701,  126,  127,   26,   25,
  702,  732,  733,  734,   28,  735,  736,  757, -333,  840,
  876,   26,  767,   79,   48,  727,   49,  728,  536,  721,
  722,  723,  724,  725,  726,   66,  703,  357,  471,  217,
  349,  737,  533,  836,  121,  376,   28,  133,  134,  401,
  748,  122,  456,  377,  767,  145,  146,  753,  754,  752,
  743,  745,  747,  749,  750,  751,  159,  320,  140,  321,
   16,  322,   48,  272,   53,  113,  225,  226,  323,  105,
  324,  325,  760,  208,  209,  477,   63,  106,  273,  575,
  577,  391,  147,  148,  423,  288,  159,  320,  394,  321,
   16,  322,  530,  272,  576,  289,  225,  226,  323,  105,
  324,  325,  290,  208,  209,  477,   63,  106,  273,  281,
  282,  233,  354,  116,  457,  453,  418,  392,  275,  276,
  326,  327,  328,  329,  330,  387,  234,  235,   35,   36,
   37,  355,  332,  287,  534,  431,  459,  779,  903,  267,
  524,  233,  537,  119,   25,  -98,  606,  887,  275,  276,
  326,  327,  328,  329,  330,  232,  234,  235,   35,   36,
   37,  667,  332,  700,  672,   28,    5,  284,   27,  424,
  674,    6,    7,   26,  215,  -98,  159,  320,    8,  321,
   16,  322,  777,  272,  673,  897,  225,  226,  323,  105,
  324,  325,  531,  208,  209,  477,   63,  106,  273,  762,
  426,  602,  102,    4,  445,  108,  461,  159,  320,  904,
  321,   16,  322,   45,  272,   30,  896,  225,  226,  323,
  105,  324,  325,  885,  208,  209,  477,   63,  106,  273,
  755,  233,  758,  114,  839,  464,  451,  427,  275,  276,
  326,  327,  328,  329,  330,  604,  234,  235,   35,   36,
   37,  665,  332,  567,   73,   71,   70,  430,  271,  123,
  674,  574,  233,  497,  564,  -98,  569,  546,    8,  275,
  276,  326,  327,  328,  329,  330,  846,  234,  235,   35,
   36,   37,  565,  332,  563,  578,  568,   74,   72,   -1,
  159,  320,   69,  321,   16,  322,  -98,  272,   68, -311,
  225,  226,  323,  105,  324,  325,   67,  208,  209,  477,
   63,  106,  273,  847,  566,  218,  696,  212,  159,  320,
  109,  321,   16,  322,   62,  272,   55,   33,  225,  226,
  323,  105,  324,  325,  112,  208,  209,  477,   63,  106,
  273,  202,  190, -353, -346,  233, -339,  548, -336, -335,
 -334, -331,  275,  276,  326,  327,  328,  329,  330,   41,
  234,  235,   35,   36,   37,   95,  332,   99,  549,  103,
  480, -358,  216,  233,  206,  118,    0,  189,  188,  -98,
  275,  276,  326,  327,  328,  329,  330,   97,  234,  235,
   35,   36,   37,   93,  332,   77,   76,   75,   54,  191,
  198,  422,  525,  393,  351,  159,  320,  -98,  321,   16,
  322,   17,  272,  350,  219,  225,  226,  323,  105,  324,
  325,  201,  208,  209,  477,   63,  106,  273,  200,  199,
  197,  196,  195,  159,  320,  194,  321,   16,  322,  193,
  272,  192,  124,  225,  226,  323,  105,  324,  325,   18,
  208,  209,  477,   63,  106,  273,   20,   21,  304,  463,
  233,  584,  695,  908,  906,  694,  607,  275,  276,  326,
  327,  328,  329,  330,  889,  234,  235,   35,   36,   37,
  668,  332,  845,  756,  697,  840,  460,  454,  233,  677,
  444,  440,  319,  318,  -98,  275,  276,  326,  327,  328,
  329,  330,  317,  234,  235,   35,   36,   37,  316,  332,
  315,  314,  313,  311,  310,  309,  308,  676,   24,   23,
  159,  320,  -98,  321,   16,  322,   22,  272,    3,    2,
  225,  226,  323,  105,  324,  325,  125,  208,  209,  477,
   63,  106,  273,  759,    0,    0,    0,    0,  159,  320,
    0,  321,   16,  322,    0,  272,    0,    0,  225,  226,
  323,  105,  324,  325,    0,  208,  209,  477,   63,  106,
  273,    0,    0,    0,    0,  233,    0,    0,    0,    0,
    0,    0,  275,  276,  326,  327,  328,  329,  330,    0,
  234,  235,   35,   36,   37,    0,  332,    0,    0,    0,
    0,    0,    0,  233,  675,    0,    0,    0,    0,  -98,
  275,  276,  326,  327,  328,  329,  330,    0,  234,  235,
   35,   36,   37,    0,  332,    0,    0,    0,    0,    0,
    0,    0,  529,    0,    0,  159,  320,  -98,  321,   16,
  322,    0,  272,    0,    0,  225,  226,  323,  105,  324,
  325,    0,  208,  209,  477,   63,  106,  273,    0,    0,
    0,    0,    0,  159,  320,    0,  321,   16,  322,    0,
  272,    0,    0,  225,  226,  323,  105,  324,  325,    0,
  208,  209,  477,   63,  106,  273,    0,    0,    0,    0,
  233,    0,    0,    0,    0,    0,    0,  275,  276,  326,
  327,  328,  329,  330,    0,  234,  235,   35,   36,   37,
    0,  332,    0,    0,    0,    0,    0,    0,  233,  528,
    0,    0,    0,    0,  -98,  275,  276,  326,  327,  328,
  329,  330,    0,  234,  235,   35,   36,   37,    0,  332,
    0,    0,    0,    0,    0,    0,    0,  527,    0,    0,
  159,  320,  -98,  321,   16,  322,    0,  272,    0,    0,
  225,  226,  323,  105,  324,  325,    0,  208,  209,  477,
   63,  106,  273,    0,    0,    0,    0,    0,  159,  320,
    0,  321,   16,  322,    0,  272,    0,    0,  225,  226,
  323,  105,  324,  325,    0,  208,  209,  477,   63,  106,
  273,    0,    0,    0,    0,  233,    0,    0,    0,    0,
    0,    0,  275,  276,  326,  327,  328,  329,  330,    0,
  234,  235,   35,   36,   37,    0,  332,    0,    0,    0,
    0,    0,    0,  233,  526,    0,    0,    0,    0,  -98,
  275,  276,  326,  327,  328,  329,  330,    0,  234,  235,
   35,   36,   37,    0,  332,    0,    0,    0,    0,    0,
    0,    0,  524,    0,    0,  159,  320,  -98,  321,   16,
  322,    0,  272,    0,    0,  225,  226,  323,  105,  324,
  325,    0,  208,  209,  477,   63,  106,  273,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  156,    0,    0,    0,    0,    0,    0,    0,    0,
  233,    0,    0,    0,    0,  149,  150,  275,  276,  326,
  327,  328,  329,  330,  478,  234,  235,   35,   36,   37,
    0,  332,    0,    0,    0,    0,  683,  685,  686,  508,
  345,  510,  509,  511,  -98,  512,  274,    0,    0,    0,
  513,  514,    0,  515,  863,  346,  347,    0,    0,    0,
  331,  701,    0,  687,  682,  680,  702,    0,    1,    0,
   42,    0,  681,-32766,-32766,  151,    0,    0,   59,    0,
   34,    0,    0,    0,  227,  277,    0,  152,  141,  479,
    0,  142,  143,   29,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  516,    0,    0,    0,    0,  517,    0,
  519,  518,-32766,-32766,-32766,    0,    0,    0,-32766,    0,
    0,  507,  498,    0,    0,    0,   28,  506,    0,    0,
    0,    0,    0,-32766,    0,    0,    0,    0,    0,    0,
    0,    0,-32766,    0,    0,-32766,-32766,    0,    0,-32766,
-32766
#line 174 "build/utility/kmyacc.c.parser"
};
#define YYLAST 1321

static char yycheck[] = {
    1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
   21,   22,   23,   24,   25,   26,   27,   28,  104,  105,
  106,   61,   33,   34,   37,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,    2,   78,   58,
    0,   52,   53,   54,   84,   56,   57,   58,   22,    2,
   61,    3,   63,   64,   65,   66,   67,   68,   69,   61,
   71,   72,   73,   74,   75,    7,   77,   18,   26,   27,
   28,   82,   83,   36,   85,   86,   89,   31,   32,   90,
   91,  100,   84,   94,   86,    4,   61,   98,   99,  100,
  101,  102,  103,  104,  105,  106,    2,    3,    4,    5,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   84,
   84,   17,   18,   19,   20,   21,   22,   92,   24,   25,
   26,   27,   28,   70,   71,   72,   61,   33,   34,   76,
   84,   58,   86,   84,   97,   86,   89,   84,   61,   90,
   94,   61,   96,  101,  102,   84,   52,   53,   54,   84,
   56,   57,   58,  100,   93,   61,    7,   92,   78,   77,
   66,   84,   68,   70,   84,   71,   72,   73,   74,   75,
   77,   77,   90,  100,   77,   82,   82,   83,   78,   91,
   86,    4,    5,    6,   84,   91,    7,   90,   94,    7,
   13,  103,   98,   99,  100,  101,  102,  103,  104,  105,
  106,    2,    3,    4,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   15,    9,   17,   18,   19,   20,
   21,   22,   10,   24,   25,   26,   27,   28,   84,   86,
   86,   61,   33,   34,    4,    5,    6,   94,   94,   96,
   96,   58,   78,   13,   61,   77,   24,   25,   84,   84,
   82,   52,   53,   54,   84,   56,   57,   87,   93,   95,
   77,   84,   92,   61,   84,   66,   86,   68,   81,   70,
   71,   72,   73,   74,   75,   89,   77,   94,   91,   93,
   18,   82,   81,  100,   29,   86,   84,   33,   34,   87,
   91,   30,   91,   94,   92,   50,   51,   98,   99,  100,
  101,  102,  103,  104,  105,  106,    1,    2,   35,    4,
    5,    6,   84,    8,   86,   58,   11,   12,   13,   14,
   15,   16,   59,   18,   19,   20,   21,   22,   23,   90,
   77,   92,   60,   61,   78,   77,    1,    2,   78,    4,
    5,    6,   77,    8,   77,   77,   11,   12,   13,   14,
   15,   16,   77,   18,   19,   20,   21,   22,   23,   77,
   77,   56,   77,   58,   77,   77,   77,   77,   63,   64,
   65,   66,   67,   68,   69,   77,   71,   72,   73,   74,
   75,   77,   77,   77,   81,   78,   78,   85,   87,   89,
   85,   56,   81,   58,   84,   90,   83,   83,   63,   64,
   65,   66,   67,   68,   69,  100,   71,   72,   73,   74,
   75,   83,   77,   83,   85,   84,   84,   84,   84,   92,
   85,   84,   84,   84,   55,   90,    1,    2,   93,    4,
    5,    6,   85,    8,   85,   85,   11,   12,   13,   14,
   15,   16,   85,   18,   19,   20,   21,   22,   23,   85,
   85,   85,   89,   84,   86,   86,   86,    1,    2,   87,
    4,    5,    6,   94,    8,   96,   87,   11,   12,   13,
   14,   15,   16,   87,   18,   19,   20,   21,   22,   23,
   87,   56,   87,   58,   87,   87,   87,   87,   63,   64,
   65,   66,   67,   68,   69,   87,   71,   72,   73,   74,
   75,   87,   77,   90,   89,   89,   89,   89,   89,   98,
   85,   90,   56,   90,   90,   90,   90,   90,   93,   63,
   64,   65,   66,   67,   68,   69,   90,   71,   72,   73,
   74,   75,   90,   77,   90,   90,   90,   90,   90,    0,
    1,    2,   90,    4,    5,    6,   90,    8,   90,   93,
   11,   12,   13,   14,   15,   16,   90,   18,   19,   20,
   21,   22,   23,   90,   90,   93,   95,   92,    1,    2,
   92,    4,    5,    6,   92,    8,   92,   92,   11,   12,
   13,   14,   15,   16,   92,   18,   19,   20,   21,   22,
   23,   92,   94,   93,   93,   56,   93,   93,   93,   93,
   93,   93,   63,   64,   65,   66,   67,   68,   69,   93,
   71,   72,   73,   74,   75,   93,   77,   93,   93,   93,
   93,   93,   93,   56,   93,   93,   -1,   94,   94,   90,
   63,   64,   65,   66,   67,   68,   69,   94,   71,   72,
   73,   74,   75,   94,   77,   94,   94,   94,   94,   94,
   94,   94,   85,   94,   94,    1,    2,   90,    4,    5,
    6,   95,    8,   94,   94,   11,   12,   13,   14,   15,
   16,   94,   18,   19,   20,   21,   22,   23,   94,   94,
   94,   94,   94,    1,    2,   94,    4,    5,    6,   94,
    8,   94,   99,   11,   12,   13,   14,   15,   16,   95,
   18,   19,   20,   21,   22,   23,   95,   95,   95,   95,
   56,   95,   95,   95,   95,   95,   95,   63,   64,   65,
   66,   67,   68,   69,   95,   71,   72,   73,   74,   75,
   95,   77,   95,   95,   95,   95,   95,   95,   56,   85,
   95,   95,   95,   95,   90,   63,   64,   65,   66,   67,
   68,   69,   95,   71,   72,   73,   74,   75,   95,   77,
   95,   95,   95,   95,   95,   95,   95,   85,   95,   95,
    1,    2,   90,    4,    5,    6,   95,    8,   95,   95,
   11,   12,   13,   14,   15,   16,  100,   18,   19,   20,
   21,   22,   23,  102,   -1,   -1,   -1,   -1,    1,    2,
   -1,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   -1,   18,   19,   20,   21,   22,
   23,   -1,   -1,   -1,   -1,   56,   -1,   -1,   -1,   -1,
   -1,   -1,   63,   64,   65,   66,   67,   68,   69,   -1,
   71,   72,   73,   74,   75,   -1,   77,   -1,   -1,   -1,
   -1,   -1,   -1,   56,   85,   -1,   -1,   -1,   -1,   90,
   63,   64,   65,   66,   67,   68,   69,   -1,   71,   72,
   73,   74,   75,   -1,   77,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   85,   -1,   -1,    1,    2,   90,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   -1,   18,   19,   20,   21,   22,   23,   -1,   -1,
   -1,   -1,   -1,    1,    2,   -1,    4,    5,    6,   -1,
    8,   -1,   -1,   11,   12,   13,   14,   15,   16,   -1,
   18,   19,   20,   21,   22,   23,   -1,   -1,   -1,   -1,
   56,   -1,   -1,   -1,   -1,   -1,   -1,   63,   64,   65,
   66,   67,   68,   69,   -1,   71,   72,   73,   74,   75,
   -1,   77,   -1,   -1,   -1,   -1,   -1,   -1,   56,   85,
   -1,   -1,   -1,   -1,   90,   63,   64,   65,   66,   67,
   68,   69,   -1,   71,   72,   73,   74,   75,   -1,   77,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,   -1,
    1,    2,   90,    4,    5,    6,   -1,    8,   -1,   -1,
   11,   12,   13,   14,   15,   16,   -1,   18,   19,   20,
   21,   22,   23,   -1,   -1,   -1,   -1,   -1,    1,    2,
   -1,    4,    5,    6,   -1,    8,   -1,   -1,   11,   12,
   13,   14,   15,   16,   -1,   18,   19,   20,   21,   22,
   23,   -1,   -1,   -1,   -1,   56,   -1,   -1,   -1,   -1,
   -1,   -1,   63,   64,   65,   66,   67,   68,   69,   -1,
   71,   72,   73,   74,   75,   -1,   77,   -1,   -1,   -1,
   -1,   -1,   -1,   56,   85,   -1,   -1,   -1,   -1,   90,
   63,   64,   65,   66,   67,   68,   69,   -1,   71,   72,
   73,   74,   75,   -1,   77,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   85,   -1,   -1,    1,    2,   90,    4,    5,
    6,   -1,    8,   -1,   -1,   11,   12,   13,   14,   15,
   16,   -1,   18,   19,   20,   21,   22,   23,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   17,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   56,   -1,   -1,   -1,   -1,   31,   32,   63,   64,   65,
   66,   67,   68,   69,   40,   71,   72,   73,   74,   75,
   -1,   77,   -1,   -1,   -1,   -1,   52,   53,   54,    2,
   56,    4,    5,    6,   90,    8,   62,   -1,   -1,   -1,
   13,   14,   -1,   16,   70,   71,   72,   -1,   -1,   -1,
   76,   77,   -1,   79,   80,   81,   82,   -1,   84,   -1,
   86,   -1,   88,   31,   32,   91,   -1,   -1,   94,   -1,
   96,   -1,   -1,   -1,  100,  101,   -1,  103,  104,  105,
   -1,  107,  108,  109,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   66,   -1,   -1,   -1,   -1,   71,   -1,
   73,   74,   70,   71,   72,   -1,   -1,   -1,   76,   -1,
   -1,   84,   85,   -1,   -1,   -1,   84,   90,   -1,   -1,
   -1,   -1,   -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  100,   -1,   -1,  103,  104,   -1,   -1,  107,
  108
#line 179 "build/utility/kmyacc.c.parser"
};

static short yybase[] = {
 1124,   -1,  435,  345,  315, 1037, 1009,  922,  779,  549,
  466,  577,  894,  807,  692,  664, 1124, 1124, 1124, 1124,
 1124, 1124, 1124, 1124, 1124,  357,  376,  312,  104,  340,
  338,  323,  324,   -9,  209,  193,  193,  193,  193,  193,
  193,  187,  180,  212,  180,   90,   90,   90,   35,   35,
   35,   35,   35,   35,   59,  -30,  174,   75,  175,  110,
   36,   71,   87,  320,  320,  320,  349,  320,  320,  320,
  349,  349,  320,  349,  320,  341,  341,  341,  349,  349,
  349,  349,  349,  349,  349,  349,  349,  349,  349,  349,
  349,  349,  349,  341,  349,  349,  349,  341,  341,  349,
  349,  341,  349,  349,  349,  341,  341,  341,  341,  344,
  341,  341,  341, 1154, 1154,  341,  341,  341,  341,  341,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,   63, 1212,
 1212, 1212, 1212, 1212, 1212, 1212, 1212, 1212,   57, 1207,
  514,  627,  424,  418,  396,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,  379,  481,  154,
  154,  154,  154,   56,   56,   56,   56,   56,    8,    8,
    8,    8,    8,    8,    8,    8,    8,    8,    8,    8,
    8,    8,    8,   52,   52,   52,  240,  238,  190,  190,
  190,  190,  190,   92,  107,  103,  103,  103,  103,  103,
  153,  -76,  -76,  -76,   68,  292,  293,  565,  566,  511,
  567,  178,  566,  272,  295,  314,   47,  232,  264,   98,
  255,  282,  196,  446,  483,  249,  272,  295,  314,  299,
  576,  614,  476,  623,  266,   83,  232,  264,  264,  264,
  264,  264,   98,   98,  255,  468,  626,  211,  624,  621,
  622,  197,  342,  277,  570,  275,  275,  701,   45,  539,
  216,   45,   45,  539,  308,   45,  570,  607,  607,  342,
  342,  342,  518,  510,  495,  570,  222,  337,   45,  537,
  537,  378,  378,  342,  342,  580,  342,  342,  342,  342,
  342,  342,  580,  342,  342,  342,  342,  342,  342,  342,
  563,  562,  564,  561,  535,  343,  456,  316,  268,  278,
  285,  508,  541,   50,  455,  265,  271,  421,  603,  696,
  283,   91,  559,  454,  452,  579,  544,  543,  488,  300,
  569,  270,  347,  348,  605,  601,  407,  650,  598,  597,
  596,  563,  562,  564,  561,  517,  516,  515,  316,  278,
  526,  513,  532,  405,  492,  649,  403,  648,  436,  553,
  159,   68,  434,  484,  534,  594,  595,  310,  375,  410,
  431,  263,  428,  317,  647,  482,  681,  509,  680,  679,
  339,  538,  656,  374,  492,  655,  273,  265,  542,  271,
  421,  603,  696,  283,  283,  283,  645,  494,  587,  192,
  409,  462,  298,  652,  297,  367,  427,  426,  373,  423,
  318,  651,  639,  678,  360,  389,  677,  676,  675,  673,
  536,  694,  594,  631,  267,  311,  380,  380,  667,   58,
  408,  189,  458,  658,  536,  693,  313,  429,  425,  433,
  630,  382,  657,  437,  426,  457,  691,  373,  373,  629,
  684,  321,  373,  359,  683,  359,  628,    0,    0,    0,
    0, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154,  104,  104,  104,    0,
  209,  209,  209,  209,  104,    0,  104,  104,  104,  104,
  104,  104, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154,    0,    0, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,
 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154, 1154,   -3,
    0,   -3,   -3,   -3,   -3,   -3,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   56,   56,
   56,   56,   56,   56,    0,    0,    0,    0,    0,  178,
  178,  178,  178,  178,  178,  178,  178,  178,  178,  178,
  178,  178,  178,  178,    0,    0,    0,    0,  178,  178,
  178,  178,  178,  178,   45,   45,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  196,   45,   45,  342,  342,
  701,  342,    0,  342,  579,  544,  543,    0,    0,    0,
    0,    0,    0,    0,  485,  485,    0,  579,  544,  543,
  595,  502,  502,  502,  502,  650,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  485,  502,    0,  502,
  502,  502
#line 183 "build/utility/kmyacc.c.parser"
};
#define YY2TBLSTATE 271

static short yydefault[] = {
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,  283,32767,32767,32767,32767,  326,  327,
  328,32767,32767,32767,32767,  428,  428,  428,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  100,32767,
32767,   90,  290,  100,  100,  100,32767,  100,  100,  100,
32767,32767,  100,32767,  100,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,   90,  320,32767,32767,
32767,   92,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,  352,32767,32767,  168,  170,32767,
32767,32767,32767,  351,  350,32767,32767,  321,  102,32767,
32767,32767,32767,32767,32767,  295,   89,  288,  293,  434,
  297,  303,  305,  291,   91,  294,  301,  180,32767,  178,
  179,  176,  175,  120,  435,  304,  306,  302,  409,  409,
  409,  409,  409,  409,  409,  409,  409,  409,  409,  409,
  409,  409,32767,  144,  145,  146,32767,32767,32767,32767,
  322,  323,32767,  317,  318,32767,32767,32767,32767,32767,
  426,  156,  158,  157,  369,  102,  102,32767,  355,  280,
32767,32767,32767,32767,32767,32767,  131,  142,  147,  153,
  163,  165,  369,32767,32767,32767,  337,  324,  325,32767,
32767,32767,32767,32767,32767,32767,  143,  149,  151,  152,
  148,  150,  154,  155,  164,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,  280,  102,  383,
   77,  102,  102,  383,32767,  102,32767,  407,  407,32767,
32767,  314,  437,  363,  282,32767,   80,  282,  102,  401,
  401,  421,  421,32767,32767,  424,32767,32767,32767,32767,
32767,32767,  424,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,  220,32767,32767,  132,  134,  136,  138,  140,
  159,32767,32767,32767,32767,32767,32767,32767,  101,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
32767,  308,  310,  312,  319,  202,  204,  205,  329,  330,
  220,  221,32767,32767,  284,32767,32767,32767,32767,32767,
32767,  203,32767,32767,32767,  355,32767,   51,32767,32767,
32767,32767,32767,32767,32767,  413,32767,  410,32767,32767,
32767,  276,32767,32767,  285,32767,32767,  133,32767,  135,
  137,  139,  141,  160,  161,  162,32767,  429,32767,32767,
32767,32767,32767,32767,  283,32767,32767,32767,  371,32767,
32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
  216,32767,32767,32767,32767,32767,  420,  418,32767,   62,
32767,  277,32767,32767,32767,32767,32767,   54,  370,32767,
32767,32767,32767,32767,   75,32767,32767,  374,  373,32767,
32767,32767,  372,  389,32767,32767,32767,  437,  363,  363,
  437
#line 188 "build/utility/kmyacc.c.parser"
};

static short yygoto[] = {
  171,  167,  167,  167,  169,  169,  169,  167,  167,  167,
  167,  167,  167,  168,  169,  161,  167,  165,  161,  781,
  166,  173,  165,  165,  165,  913,  165,  165,  165,  443,
  476,  165,  404,  165,  168,  168,  168,  398,  399,  405,
  432,  433,  436,  437,  438,  439,  441,  448,  455,  462,
  842,  265,  168,  244,  172,  244,  168,  168,  171,  841,
  168,  381,  176,  407,  160,  166,  160,  162,  170,  163,
  174,  175,  600,  409,  164,  871,  871,  542,  600,  413,
  414,  415,  600,  600,  664,  600,  664,  664,  664,  664,
  600,  600,  600,  600,  600,  600,  600,  600,  600,  600,
  600,  600,  600,  600,  600,  411,  600,  410,  600,  666,
  605,  886,  600,  693,  600,  412,  600,  658,  654,  655,
  658,  647,  648,  650,  652,  870,  473,  256,  400,  408,
  610,  475,  877,  877,  877,  877,  877,  877,  264,  670,
  893,  670,  670,  670,  670,  279,  279,  279,  279,  279,
  279,  279,  279,  279,  279,  279,  279,  279,  279,  279,
  279,  279,  279,  279,  279,  279,  279,  279,  279,  279,
  671,  608,  671,  671,  671,  671,  608,  608,  608,  608,
  608,  204,  205,  298,  421,  419,  452,  465,  466,  872,
  872,  470,  559,  474,  872,  395,  395,  395,  395,  395,
  395,  395,  395,  395,  395,  395,  395,  395,  395,  395,
  250,  251,  253,  849,  224,  242,  242,  242,  242,  242,
  179,  180,  181,  182,  181,  182,  359,  360,  266,  359,
  360,  353,  268,  269,  280,  300,  270,  386,  898,  420,
  307,  580,  542,  388,  389,  406,  434,  435,  450,  262,
  263,  880,  881,  280,   14,   14,  222,  223,   12,   13,
   15,  884,  698,  698,  586,  562,  547,  447,  878,  879,
  866,  867,  868,  860,  425,  861,  873,  874,  875,  869,
  560,  862,  788,  770,  589,  590,  591,  592,  593,  594,
  595,  596,  597,  598,  599,  587,  588,  344,  586,  895,
  912,  483,  467,  468,  773,  472,  857,  286,  914,  344,
  484,  341,  486,  486,  486,  486,  486,  341,  449,  545,
  544,  553,  554,  552,  551,  550,  185,  155,    0,    0,
  184,  184,  184,  257,  258,  259,  260,  261,    0,    0,
  184,  178,    0,    0,  178,  865,  305,  312,  469,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  378,    0,    0,  382,  383,    0,    0,  390,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  186,  429,    0,    0,  185,    0,    0,    0,  187
#line 192 "build/utility/kmyacc.c.parser"
};
#define YYGLAST 389

static char yygcheck[] = {
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   71,
   35,   35,   35,   35,   35,   97,   35,   35,   35,   95,
   95,   35,   66,   35,   35,   35,   35,   90,   90,   90,
   90,   90,   90,   90,   90,   90,   90,   90,   90,   90,
   64,   76,   35,   76,   35,   76,   35,   35,   35,   64,
   35,   72,   35,   42,   35,   35,   35,   35,   35,   35,
   35,   35,   39,   43,   35,    7,    7,   33,   39,   52,
   52,   52,   39,   39,   58,   39,   58,   58,   58,   58,
   39,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   39,   39,   39,   39,   39,   45,   39,   44,   39,   57,
   57,   57,   39,   57,   39,   46,   39,   54,   54,   54,
   54,   54,   54,   54,   54,   39,   39,   47,   39,   39,
   39,   39,   73,   73,   73,   73,   73,   73,   53,    7,
   92,    7,    7,    7,    7,   79,   79,   79,   79,   79,
   79,   79,   79,   79,   79,   79,   79,   79,   79,   79,
   79,   79,   79,   79,   79,   79,   79,   79,   79,   79,
   94,   94,   94,   94,   94,   94,   94,   94,   94,   94,
   94,   48,   48,   38,   38,   19,   38,   38,   38,    7,
    7,   38,    7,   38,    7,   72,   72,   72,   72,   72,
   72,   72,   72,   72,   72,   72,   72,   72,   72,   72,
   68,   68,   68,   77,   72,   72,   72,   72,   72,   72,
   56,   56,   56,   56,   56,   56,   74,   74,   68,   74,
   74,    9,   68,   68,    7,   88,   68,   98,   72,   65,
   86,   30,   33,   65,   65,   65,   65,   65,   65,   50,
   50,    7,    7,    7,    3,    3,   51,   51,    3,    3,
    3,   59,   59,   59,   36,    7,    7,  100,    7,    7,
    7,    7,    7,    7,  103,    7,    7,    7,    7,    7,
    7,    7,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   30,   36,  101,
   36,    4,   78,   78,   36,   78,   36,  105,   36,   30,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,   37,  102,   -1,   -1,
   37,   37,   37,   49,   49,   49,   49,   49,   -1,   -1,
   37,   37,   -1,   -1,   37,   99,   99,   99,   99,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   30,   -1,   -1,   30,   30,   -1,   -1,   30,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   37,   30,   -1,   -1,   37,   -1,   -1,   -1,   37
#line 197 "build/utility/kmyacc.c.parser"
};

static short yygbase[] = {
    0,    0,    0,  252,  301,    0,    0,  -38,    0,  -45,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -22,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   83,    0,    0,   36,    0,  -41,  204,  285,  119,   12,
    0,    0,  -57,  -48,  -15,  -18,   -9,    2,   55,  205,
  116,  121,  -58,   -2,  -24,    0,   71,   79,  -93,  106,
    0,    0,    0,    0, -236,  195,  -25,    0,  135,    0,
    0,  -14,    7,   97,  190,    0, -156,    1,  232,  145,
    0,    0,    0,    0,    0,    0,  -60,    0,  -53,    0,
 -152,    0,  -62,    0,   -7,  -17,    0,  -30,  -46,  129,
  -35,  -13, -153,  -23,    0, -171
#line 201 "build/utility/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,  333,    9,   11,  485,  488,  487,  489,  490,  352,
  491,  297,  504,  492,  520,  521,  522,  493,  523,  380,
  494,  296,  557,  499,  500,  278,  501,  502,  245,  503,
  343,  505,  495,  496,  334,  158,  856,  183,  285,  585,
  609,  236,  335,  336,  337,  338,  339,  237,  203,  238,
  239,  221,  340,  240,  241,  653,  177,  699,  603,  663,
  689,  688,  690,  692,  843,  373,  374,   57,  252,  348,
  294,  780,  684,  372,  358,  538,  243,  848,  428,  283,
  539,  858,  611,  859,  540,  541,  306,  220,  299,  883,
  396,  397,  892,  669,  691,  416,  417,  911,  249,  662,
  446,  458,   64,  403,   50,  295
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
   55,   55,   56,   56,   56,   56,   56,   56,   56,   93,
   93,   94,   94,   94,   94,   94,   94,   58,   58,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   72,   72,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   61,   61,   60,   60,
  104,   62,  103,  103,   65,   65,   67,   67,   66,   66,
   66,   66,   66,   68,   68,   69,   69,   69,   69,   70,
   70,   71,   71,   71,   71,   71,   71,   71,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   73,   73,   73,   73,   73,   73,   73,   73,   73,
   63,   63,   63,  105,   64,   75,   75,   76,   76,   77,
   77,   77,   77,   77,   77,   78,   78,   80,   80,   81,
   81,   81,   79,   98,   98,   82,   82,   82,   82,   82,
   82,   82,   83,   83,   83,   74,   74,   84,   84,   85,
   85,   86,   86,   87,   87,   87,   87,   88,   88,   90,
   90,   91,   91,   92,   92,   92,   92,   92,   99,   99,
   99,  100,  100,  100,  101,  101,   89,   89,   95,   95,
   96,   96,   96,   96,   97,   97,   97,  102
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
    0,    4,    0,    1,    1,    2,    1,    2,    1,    2,
    2,    3,    4,    1,    3,    1,    2,    3,    4,    1,
    3,    5,    5,    3,    3,    3,    3,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    2,    2,
    3,    3,    2,    0,    3,    3,    3,    1,    3,    1,
    4,    3,    6,    5,    5,    1,    3,    1,    1,    6,
    6,    7,    1,    0,    2,    5,    5,    5,    6,    6,
    6,    2,    6,    6,    6,    1,    1,    5,    5,    3,
    3,    0,    4,    1,    4,    3,    3,    0,    3,    0,
    1,    1,    3,    1,    4,    3,    3,    2,    2,    1,
    2,    0,    2,    3,    0,    3,    0,    3,    0,    1,
    1,    2,    3,    4,    1,    1,    1,    0
#line 213 "build/utility/kmyacc.c.parser"
};

#line 235 "build/utility/kmyacc.c.parser"

#define YYSTATES 818
#define YYNLSTATES 481
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
#line 162 "src/kinx.y"
{ kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, YYASP(1-1).obj, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); } break;
        case 3:
#line 167 "src/kinx.y"
{ kx_ast_root = yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 5:
#line 172 "src/kinx.y"
{ yyval.obj = kx_gen_stmtlist(YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 16:
#line 189 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(3-6).strval, KX_UNKNOWN_T), kx_gen_import_object(YYASP(5-6).strval)); } break;
        case 17:
#line 190 "src/kinx.y"
{ yyerrok; } break;
        case 25:
#line 201 "src/kinx.y"
{ yyerrok; } break;
        case 26:
#line 202 "src/kinx.y"
{ yy_restart(LBBR); yyerrok; } break;
        case 27:
#line 203 "src/kinx.y"
{ yy_restart(IF); yyerrok; } break;
        case 28:
#line 204 "src/kinx.y"
{ yy_restart(DO); yyerrok; } break;
        case 29:
#line 205 "src/kinx.y"
{ yy_restart(WHILE); yyerrok; } break;
        case 30:
#line 206 "src/kinx.y"
{ yy_restart(FOR); yyerrok; } break;
        case 31:
#line 207 "src/kinx.y"
{ yy_restart(TRY); yyerrok; } break;
        case 32:
#line 208 "src/kinx.y"
{ yy_restart(SWITCH); yyerrok; } break;
        case 33:
#line 209 "src/kinx.y"
{ yy_restart(CASE); yyerrok; } break;
        case 34:
#line 210 "src/kinx.y"
{ yy_restart(ENUM); yyerrok; } break;
        case 35:
#line 211 "src/kinx.y"
{ yy_restart(CLASS); yyerrok; } break;
        case 36:
#line 212 "src/kinx.y"
{ yy_restart(FUNCTION); yyerrok; } break;
        case 37:
#line 213 "src/kinx.y"
{ yy_restart(PRIVATE); yyerrok; } break;
        case 38:
#line 214 "src/kinx.y"
{ yy_restart(PUBLIC); yyerrok; } break;
        case 43:
#line 225 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 44:
#line 226 "src/kinx.y"
{ yyval.obj = kx_gen_block_object(YYASP(2-3).obj); } break;
        case 45:
#line 230 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 46:
#line 231 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 47:
#line 232 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(0, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 48:
#line 233 "src/kinx.y"
{ yyval.obj = kx_gen_namespace_object(1, YYASP(2-5).strval, YYASP(4-5).obj); } break;
        case 49:
#line 237 "src/kinx.y"
{ yyval.strval = kx_gen_namespace_name_object(YYASP(1-1).strval); } break;
        case 50:
#line 241 "src/kinx.y"
{ yyval.obj = kx_gen_enum_reset(YYASP(3-5).obj); } break;
        case 51:
#line 245 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object(YYASP(1-1).strval); } break;
        case 52:
#line 246 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-3).strval, YYASP(3-3).intval); } break;
        case 53:
#line 247 "src/kinx.y"
{ yyval.obj = kx_gen_enum_object_with(YYASP(1-4).strval, -YYASP(4-4).intval); } break;
        case 54:
#line 248 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, kx_gen_enum_object(YYASP(3-3).strval)); } break;
        case 55:
#line 249 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-5).obj, kx_gen_enum_object_with(YYASP(3-5).strval, YYASP(5-5).intval)); } break;
        case 56:
#line 250 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-6).obj, kx_gen_enum_object_with(YYASP(3-6).strval, -YYASP(6-6).intval)); } break;
        case 61:
#line 261 "src/kinx.y"
{ yyval.obj = kx_gen_label_object(KXST_LABEL, YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 62:
#line 265 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 63:
#line 266 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj); } break;
        case 64:
#line 270 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_WHILE, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 65:
#line 274 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_DO, YYASP(5-7).obj, YYASP(2-7).obj, NULL); } break;
        case 66:
#line 278 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SWITCH, YYASP(3-5).obj, YYASP(5-5).obj, NULL); } break;
        case 67:
#line 282 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_CASE, YYASP(2-3).obj); } break;
        case 68:
#line 283 "src/kinx.y"
{ yyval.obj = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); } break;
        case 69:
#line 288 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                YYASP(4-10).obj,
                YYASP(6-10).obj,
                YYASP(8-10).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(8-10).obj, NULL, NULL)),
            YYASP(10-10).obj, NULL); } break;
        case 70:
#line 295 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, YYASP(3-9).obj, NULL, NULL),
                YYASP(5-9).obj,
                YYASP(7-9).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(7-9).obj, NULL, NULL)),
            YYASP(9-9).obj, NULL); } break;
        case 71:
#line 302 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                YYASP(4-8).obj,
                YYASP(6-8).obj == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, YYASP(6-8).obj, NULL, NULL)),
            YYASP(8-8).obj, NULL); } break;
        case 72:
#line 309 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(3-7).obj, YYASP(5-7).obj, YYASP(7-7).obj, 0); } break;
        case 73:
#line 311 "src/kinx.y"
{ yyval.obj = kx_gen_forin_object(YYASP(4-8).obj, YYASP(6-8).obj, YYASP(8-8).obj, 1); } break;
        case 74:
#line 315 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 75:
#line 316 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 76:
#line 320 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_TRY, YYASP(2-4).obj, YYASP(3-4).obj, YYASP(4-4).obj); } break;
        case 77:
#line 324 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 78:
#line 325 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, "_e", YYASP(2-2).obj, NULL); } break;
        case 79:
#line 326 "src/kinx.y"
{ yyval.obj = kx_gen_catch_object(KXST_CATCH, YYASP(3-5).strval, YYASP(5-5).obj, NULL); } break;
        case 80:
#line 330 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 81:
#line 331 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 82:
#line 335 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_BREAK, NULL)); } break;
        case 83:
#line 336 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_BREAK, YYASP(2-4).strval)); } break;
        case 84:
#line 337 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_break_object(KXST_CONTINUE, NULL)); } break;
        case 85:
#line 338 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_break_object(KXST_CONTINUE, YYASP(2-4).strval)); } break;
        case 86:
#line 342 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(4-5).obj, kx_gen_stmt_object_line(KXST_RET, YYASP(3-5).obj, NULL, NULL, YYASP(2-5).intval)); } break;
        case 87:
#line 343 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); } break;
        case 88:
#line 347 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-3).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-3).obj, NULL, NULL)); } break;
        case 89:
#line 351 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, YYASP(2-2).obj); } break;
        case 90:
#line 352 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); } break;
        case 91:
#line 353 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_YIELD, YYASP(4-4).obj)); } break;
        case 92:
#line 354 "src/kinx.y"
{ yyval.obj = yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); } break;
        case 93:
#line 358 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(3-4).obj, kx_gen_stmt_object(KXST_THROW, YYASP(2-4).obj, NULL, NULL)); } break;
        case 94:
#line 362 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 95:
#line 366 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object(YYASP(1-1).strval, KX_OBJ_T), NULL); } break;
        case 96:
#line 367 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_MIXIN, YYASP(1-3).obj, kx_gen_var_object(YYASP(3-3).strval, KX_OBJ_T), NULL); } break;
        case 97:
#line 371 "src/kinx.y"
{ yyval.obj = YYASP(1-2).obj; } break;
        case 98:
#line 375 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); } break;
        case 99:
#line 376 "src/kinx.y"
{ yyval.obj = kx_gen_modifier(YYASP(2-2).obj, kx_gen_stmt_object(KXST_EXPR, YYASP(1-2).obj, NULL, NULL)); } break;
        case 100:
#line 380 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 102:
#line 385 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 103:
#line 386 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_IF, YYASP(3-4).obj, NULL, NULL); } break;
        case 105:
#line 391 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 106:
#line 392 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 107:
#line 393 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 108:
#line 394 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 109:
#line 395 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 110:
#line 396 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 111:
#line 397 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 112:
#line 398 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 113:
#line 399 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 114:
#line 400 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 115:
#line 401 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 116:
#line 402 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 117:
#line 403 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 118:
#line 404 "src/kinx.y"
{ yyval.obj = kx_gen_bassign_object(KXOP_ASSIGN, YYASP(1-3).obj, kx_gen_bassign_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj)); } break;
        case 121:
#line 413 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 122:
#line 414 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 123:
#line 415 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 124:
#line 416 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 125:
#line 417 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 126:
#line 418 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 127:
#line 419 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 129:
#line 424 "src/kinx.y"
{ yyval.obj = kx_gen_texpr_object(YYASP(1-5).obj, YYASP(3-5).obj, YYASP(5-5).obj); } break;
        case 133:
#line 434 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LUNDEF, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 135:
#line 439 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 137:
#line 444 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LAND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 139:
#line 449 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_OR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 141:
#line 454 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_XOR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 143:
#line 459 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_AND, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 145:
#line 464 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_EQEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 146:
#line 465 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_NEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 148:
#line 470 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 149:
#line 471 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 150:
#line 472 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GT, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 151:
#line 473 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_GE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 152:
#line 474 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_LGE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 154:
#line 479 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 155:
#line 480 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SHR, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 157:
#line 485 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ADD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 158:
#line 486 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_SUB, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 160:
#line 491 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MUL, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 161:
#line 492 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DIV, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 162:
#line 493 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_MOD, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 164:
#line 498 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_POW, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 166:
#line 503 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 167:
#line 504 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_REGNE, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 168:
#line 505 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 0); } break;
        case 169:
#line 506 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 0); } break;
        case 170:
#line 507 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-2).obj, kx_gen_special_object(KXVL_NULL), 1); } break;
        case 171:
#line 508 "src/kinx.y"
{ yyval.obj = kx_gen_range_object(YYASP(1-3).obj, YYASP(3-3).obj, 1); } break;
        case 173:
#line 513 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_BNOT, YYASP(2-2).obj); } break;
        case 174:
#line 514 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NOT, YYASP(2-2).obj); } break;
        case 175:
#line 515 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_POSITIVE, YYASP(2-2).obj); } break;
        case 176:
#line 516 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_NEGATIVE, YYASP(2-2).obj); } break;
        case 177:
#line 517 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_CONV, YYASP(2-2).obj); } break;
        case 178:
#line 518 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_INC, YYASP(2-2).obj); } break;
        case 179:
#line 519 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_DEC, YYASP(2-2).obj); } break;
        case 181:
#line 524 "src/kinx.y"
{ yyval.obj = kx_gen_cast_object(YYASP(1-3).obj, KX_UNKNOWN_T, YYASP(3-3).arraytype.type); } break;
        case 183:
#line 529 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(YYASP(2-2).incdec, YYASP(1-2).obj); } break;
        case 184:
#line 530 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 185:
#line 531 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 186:
#line 532 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 187:
#line 533 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CALL, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 188:
#line 534 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_CBBLOCK, YYASP(1-2).obj, YYASP(2-2).obj); } break;
        case 189:
#line 538 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(1-1).obj, NULL); } break;
        case 191:
#line 543 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, kx_gen_stmt_object(KXST_RET, YYASP(3-4).obj, NULL, NULL), NULL); } break;
        case 192:
#line 544 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, kx_gen_stmt_object(KXST_RET, YYASP(7-8).obj, NULL, NULL), NULL); } break;
        case 193:
#line 545 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-6).obj, NULL, NULL); } break;
        case 194:
#line 546 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, NULL, NULL); } break;
        case 195:
#line 547 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-7).obj, YYASP(6-7).obj, NULL); } break;
        case 196:
#line 548 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(4-8).obj, YYASP(7-8).obj, NULL); } break;
        case 197:
#line 552 "src/kinx.y"
{ yyval.incdec = KXOP_INCP; } break;
        case 198:
#line 553 "src/kinx.y"
{ yyval.incdec = KXOP_DECP; } break;
        case 199:
#line 557 "src/kinx.y"
{ yyval.obj = kx_gen_int_object(YYASP(1-1).intval); } break;
        case 200:
#line 558 "src/kinx.y"
{ yyval.obj = kx_gen_dbl_object(YYASP(1-1).dblval); } break;
        case 201:
#line 559 "src/kinx.y"
{ yyval.obj = kx_gen_big_object(YYASP(1-1).strval); } break;
        case 202:
#line 560 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_NULL); } break;
        case 203:
#line 561 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 204:
#line 562 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_TRUE); } break;
        case 205:
#line 563 "src/kinx.y"
{ yyval.obj = kx_gen_special_object(KXVL_FALSE); } break;
        case 206:
#line 564 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 212:
#line 570 "src/kinx.y"
{ yyval.obj = YYASP(2-2).obj; } break;
        case 213:
#line 571 "src/kinx.y"
{ yyval.obj = kx_gen_import_object(YYASP(4-6).strval); } break;
        case 214:
#line 572 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 215:
#line 573 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 216:
#line 574 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(2-3).strval); } break;
        case 217:
#line 575 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(2-2).obj, kx_gen_str_object("create")); } break;
        case 218:
#line 576 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).obj); } break;
        case 219:
#line 577 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), YYASP(2-2).intval); } break;
        case 220:
#line 581 "src/kinx.y"
{ yyval.strval = YYASP(1-1).strval; } break;
        case 221:
#line 582 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 222:
#line 586 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 223:
#line 587 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("if"); } break;
        case 224:
#line 588 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("else"); } break;
        case 225:
#line 589 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("while"); } break;
        case 226:
#line 590 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("do"); } break;
        case 227:
#line 591 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("for"); } break;
        case 228:
#line 592 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("in"); } break;
        case 229:
#line 593 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("try"); } break;
        case 230:
#line 594 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("catch"); } break;
        case 231:
#line 595 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("finally"); } break;
        case 232:
#line 596 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("break"); } break;
        case 233:
#line 597 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("continue"); } break;
        case 234:
#line 598 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("switch"); } break;
        case 235:
#line 599 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("case"); } break;
        case 236:
#line 600 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("default"); } break;
        case 237:
#line 601 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("new"); } break;
        case 238:
#line 602 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("var"); } break;
        case 239:
#line 603 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("const"); } break;
        case 240:
#line 604 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("native"); } break;
        case 241:
#line 605 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("function"); } break;
        case 242:
#line 606 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("_function"); } break;
        case 243:
#line 607 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("public"); } break;
        case 244:
#line 608 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("private"); } break;
        case 245:
#line 609 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("protectd"); } break;
        case 246:
#line 610 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("class"); } break;
        case 247:
#line 611 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("module"); } break;
        case 248:
#line 612 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("return"); } break;
        case 249:
#line 613 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("yield"); } break;
        case 250:
#line 614 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("throw"); } break;
        case 251:
#line 615 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("null"); } break;
        case 252:
#line 616 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("true"); } break;
        case 253:
#line 617 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("false"); } break;
        case 254:
#line 618 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("import"); } break;
        case 255:
#line 619 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("using"); } break;
        case 256:
#line 620 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(kx_gen_typestr_object(YYASP(1-1).intval)); } break;
        case 257:
#line 621 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<<"); } break;
        case 258:
#line 622 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">>"); } break;
        case 259:
#line 623 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("=="); } break;
        case 260:
#line 624 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("!="); } break;
        case 261:
#line 625 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<="); } break;
        case 262:
#line 626 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<"); } break;
        case 263:
#line 627 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">="); } break;
        case 264:
#line 628 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(">"); } break;
        case 265:
#line 629 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("<=>"); } break;
        case 266:
#line 630 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("+"); } break;
        case 267:
#line 631 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("-"); } break;
        case 268:
#line 632 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("*"); } break;
        case 269:
#line 633 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("/"); } break;
        case 270:
#line 634 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("%"); } break;
        case 271:
#line 635 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("&"); } break;
        case 272:
#line 636 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("|"); } break;
        case 273:
#line 637 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("^"); } break;
        case 274:
#line 638 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("[]"); } break;
        case 275:
#line 639 "src/kinx.y"
{ yyval.obj = kx_gen_str_object("()"); } break;
        case 276:
#line 643 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, YYASP(1-2).intval); } break;
        case 277:
#line 644 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-3).obj, YYASP(1-3).intval); } break;
        case 278:
#line 648 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, NULL); } break;
        case 279:
#line 649 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_MKBIN, YYASP(3-4).obj); } break;
        case 280:
#line 653 "src/kinx.y"
{ kx_make_bin_mode(); } break;
        case 281:
#line 657 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-4).obj, YYASP(1-4).intval); } break;
        case 282:
#line 661 "src/kinx.y"
{} break;
        case 284:
#line 666 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(YYASP(1-1).obj); } break;
        case 285:
#line 667 "src/kinx.y"
{ yyval.obj = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, YYASP(2-2).obj)); } break;
        case 286:
#line 671 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(NULL, KX_UND_T); } break;
        case 287:
#line 672 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 289:
#line 677 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 290:
#line 678 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-2).obj, kx_gen_var_object(NULL, KX_UND_T)); } break;
        case 291:
#line 679 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 292:
#line 680 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-4).obj, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj)); } break;
        case 294:
#line 685 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 296:
#line 690 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(1-2).intval); } break;
        case 297:
#line 691 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 298:
#line 692 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRSEQ, YYASP(1-4).obj, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, YYASP(3-4).intval)); } break;
        case 300:
#line 697 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 301:
#line 701 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 302:
#line 702 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(2-5).strval, YYASP(5-5).obj); } break;
        case 303:
#line 703 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 304:
#line 704 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 305:
#line 705 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 306:
#line 706 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(YYASP(1-3).strval, YYASP(3-3).obj); } break;
        case 307:
#line 707 "src/kinx.y"
{ yyval.obj = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj)); } break;
        case 308:
#line 711 "src/kinx.y"
{ yyval.strval = "if"; } break;
        case 309:
#line 712 "src/kinx.y"
{ yyval.strval = "else"; } break;
        case 310:
#line 713 "src/kinx.y"
{ yyval.strval = "while"; } break;
        case 311:
#line 714 "src/kinx.y"
{ yyval.strval = "do"; } break;
        case 312:
#line 715 "src/kinx.y"
{ yyval.strval = "for"; } break;
        case 313:
#line 716 "src/kinx.y"
{ yyval.strval = "in"; } break;
        case 314:
#line 717 "src/kinx.y"
{ yyval.strval = "try"; } break;
        case 315:
#line 718 "src/kinx.y"
{ yyval.strval = "catch"; } break;
        case 316:
#line 719 "src/kinx.y"
{ yyval.strval = "finally"; } break;
        case 317:
#line 720 "src/kinx.y"
{ yyval.strval = "break"; } break;
        case 318:
#line 721 "src/kinx.y"
{ yyval.strval = "continue"; } break;
        case 319:
#line 722 "src/kinx.y"
{ yyval.strval = "switch"; } break;
        case 320:
#line 723 "src/kinx.y"
{ yyval.strval = "case"; } break;
        case 321:
#line 724 "src/kinx.y"
{ yyval.strval = "new"; } break;
        case 322:
#line 725 "src/kinx.y"
{ yyval.strval = "var"; } break;
        case 323:
#line 726 "src/kinx.y"
{ yyval.strval = "const"; } break;
        case 324:
#line 727 "src/kinx.y"
{ yyval.strval = "function"; } break;
        case 325:
#line 728 "src/kinx.y"
{ yyval.strval = "_function"; } break;
        case 326:
#line 729 "src/kinx.y"
{ yyval.strval = "public"; } break;
        case 327:
#line 730 "src/kinx.y"
{ yyval.strval = "private"; } break;
        case 328:
#line 731 "src/kinx.y"
{ yyval.strval = "protectd"; } break;
        case 329:
#line 732 "src/kinx.y"
{ yyval.strval = "class"; } break;
        case 330:
#line 733 "src/kinx.y"
{ yyval.strval = "module"; } break;
        case 331:
#line 734 "src/kinx.y"
{ yyval.strval = "return"; } break;
        case 332:
#line 735 "src/kinx.y"
{ yyval.strval = "yield"; } break;
        case 333:
#line 736 "src/kinx.y"
{ yyval.strval = "throw"; } break;
        case 334:
#line 737 "src/kinx.y"
{ yyval.strval = "null"; } break;
        case 335:
#line 738 "src/kinx.y"
{ yyval.strval = "true"; } break;
        case 336:
#line 739 "src/kinx.y"
{ yyval.strval = "false"; } break;
        case 337:
#line 740 "src/kinx.y"
{ yyval.strval = "import"; } break;
        case 338:
#line 741 "src/kinx.y"
{ yyval.strval = "using"; } break;
        case 339:
#line 742 "src/kinx.y"
{ yyval.strval = kx_gen_typestr_object(YYASP(1-1).intval); } break;
        case 340:
#line 743 "src/kinx.y"
{ yyval.strval = kx_gen_typeofstr_object(YYASP(1-1).intval); } break;
        case 341:
#line 744 "src/kinx.y"
{ yyval.strval = "<<"; } break;
        case 342:
#line 745 "src/kinx.y"
{ yyval.strval = ">>"; } break;
        case 343:
#line 746 "src/kinx.y"
{ yyval.strval = "=="; } break;
        case 344:
#line 747 "src/kinx.y"
{ yyval.strval = "!="; } break;
        case 345:
#line 748 "src/kinx.y"
{ yyval.strval = "<="; } break;
        case 346:
#line 749 "src/kinx.y"
{ yyval.strval = "<"; } break;
        case 347:
#line 750 "src/kinx.y"
{ yyval.strval = ">="; } break;
        case 348:
#line 751 "src/kinx.y"
{ yyval.strval = ">"; } break;
        case 349:
#line 752 "src/kinx.y"
{ yyval.strval = "<=>"; } break;
        case 350:
#line 753 "src/kinx.y"
{ yyval.strval = "+"; } break;
        case 351:
#line 754 "src/kinx.y"
{ yyval.strval = "-"; } break;
        case 352:
#line 755 "src/kinx.y"
{ yyval.strval = "*"; } break;
        case 353:
#line 756 "src/kinx.y"
{ yyval.strval = "/"; } break;
        case 354:
#line 757 "src/kinx.y"
{ yyval.strval = "%"; } break;
        case 355:
#line 758 "src/kinx.y"
{ yyval.strval = "&"; } break;
        case 356:
#line 759 "src/kinx.y"
{ yyval.strval = "|"; } break;
        case 357:
#line 760 "src/kinx.y"
{ yyval.strval = "^"; } break;
        case 358:
#line 761 "src/kinx.y"
{ yyval.strval = "[]"; } break;
        case 359:
#line 762 "src/kinx.y"
{ yyval.strval = "()"; } break;
        case 360:
#line 766 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 0); } break;
        case 361:
#line 767 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(3-3).strval, 1); } break;
        case 362:
#line 768 "src/kinx.y"
{ yyval.obj = kx_gen_regex_object(YYASP(2-2).strval, 0); } break;
        case 363:
#line 772 "src/kinx.y"
{ kx_make_regex_mode('/'); } break;
        case 364:
#line 776 "src/kinx.y"
{ yyval.strval = YYASP(2-3).strval; } break;
        case 365:
#line 780 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 366:
#line 781 "src/kinx.y"
{ yyval.obj = kx_add_const(YYASP(2-3).obj); } break;
        case 368:
#line 786 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 369:
#line 790 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T), NULL); } break;
        case 370:
#line 791 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval), NULL); } break;
        case 371:
#line 792 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object(YYASP(1-3).strval, KX_UNKNOWN_T), YYASP(3-3).obj); } break;
        case 372:
#line 793 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object(YYASP(1-6).strval, YYASP(3-6).arraytype, YYASP(4-6).intval), YYASP(6-6).obj); } break;
        case 373:
#line 794 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKARY, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 374:
#line 795 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object_line(KXOP_MKOBJ, YYASP(2-5).obj, YYASP(1-5).intval), YYASP(5-5).obj); } break;
        case 376:
#line 800 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_ASSIGN, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 377:
#line 804 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 378:
#line 805 "src/kinx.y"
{ yyval.obj = kx_gen_stmt_object(KXST_EXPR, YYASP(1-1).obj, NULL, NULL); } break;
        case 379:
#line 809 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 380:
#line 810 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 381:
#line 811 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_NATIVE, YYASP(2-7).arraytype.type, YYASP(2-7).arraytype.depth, YYASP(3-7).strval, YYASP(5-7).obj, YYASP(7-7).obj, NULL, YYASP(1-7).intval); } break;
        case 382:
#line 815 "src/kinx.y"
{ kx_make_native_mode(); yyval.intval = YYASP(1-1).intval; } break;
        case 383:
#line 819 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_INT_T }; } break;
        case 384:
#line 820 "src/kinx.y"
{ yyval.arraytype = YYASP(2-2).arraytype; } break;
        case 385:
#line 824 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 386:
#line 825 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 387:
#line 826 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, 0, NULL, YYASP(3-5).obj, YYASP(5-5).obj, NULL, YYASP(1-5).intval); } break;
        case 388:
#line 827 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_NATIVE, YYASP(2-6).arraytype.type, YYASP(2-6).arraytype.depth, NULL, YYASP(4-6).obj, YYASP(6-6).obj, NULL); } break;
        case 389:
#line 828 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, kx_gen_stmt_object(KXST_RET, YYASP(6-6).obj, NULL, NULL), NULL); } break;
        case 390:
#line 829 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, YYASP(3-6).obj, YYASP(6-6).obj, NULL); } break;
        case 391:
#line 830 "src/kinx.y"
{ yyval.obj = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, 0, NULL, NULL, YYASP(2-2).obj, NULL); } break;
        case 392:
#line 834 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 393:
#line 835 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 394:
#line 836 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, 0, YYASP(2-6).strval, YYASP(4-6).obj, YYASP(6-6).obj, NULL, YYASP(1-6).intval); } break;
        case 397:
#line 845 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 398:
#line 846 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, 0, YYASP(2-5).strval, YYASP(3-5).obj, YYASP(5-5).obj, YYASP(4-5).namedstmt, YYASP(1-5).intval); } break;
        case 399:
#line 850 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 400:
#line 851 "src/kinx.y"
{ yyval.obj = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, 0, YYASP(2-3).strval, NULL, YYASP(3-3).obj, NULL, YYASP(1-3).intval); } break;
        case 401:
#line 855 "src/kinx.y"
{ yyval.namedstmt = (named_stmt_t){ .name = NULL, .stmt = NULL }; } break;
        case 402:
#line 857 "src/kinx.y"
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
        case 404:
#line 873 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-4).obj, YYASP(3-4).obj); } break;
        case 405:
#line 874 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXOP_IDX, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 406:
#line 875 "src/kinx.y"
{ yyval.obj = kx_gen_typeof_object(YYASP(1-3).obj, YYASP(3-3).intval); } break;
        case 407:
#line 879 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 408:
#line 880 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 409:
#line 884 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 412:
#line 890 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(1-3).obj, YYASP(3-3).obj); } break;
        case 413:
#line 894 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(1-1).strval, KX_UNKNOWN_T); } break;
        case 414:
#line 895 "src/kinx.y"
{ yyval.obj = kx_gen_var_type_object(YYASP(1-4).strval, YYASP(3-4).arraytype, YYASP(4-4).intval); } break;
        case 415:
#line 896 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LARY_T); } break;
        case 416:
#line 897 "src/kinx.y"
{ yyval.obj = kx_gen_ary_var_object(YYASP(2-3).obj, KX_LOBJ_T); } break;
        case 417:
#line 898 "src/kinx.y"
{ yyval.obj = kx_gen_var_object(YYASP(2-2).strval, KX_SPR_T); } break;
        case 418:
#line 902 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = YYASP(1-2).intval, .depth = YYASP(2-2).intval }; } break;
        case 419:
#line 903 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_NFNC_T }; } break;
        case 420:
#line 904 "src/kinx.y"
{ yyval.arraytype = (arytype_t){ .type = KX_OBJ_T, .depth = YYASP(2-2).intval, .name = kx_gen_constant_string(YYASP(1-2).strval) }; } break;
        case 421:
#line 908 "src/kinx.y"
{ yyval.intval = 0; } break;
        case 422:
#line 909 "src/kinx.y"
{ yyval.intval = 1; } break;
        case 423:
#line 910 "src/kinx.y"
{ yyval.intval = YYASP(1-3).intval + 1; } break;
        case 424:
#line 914 "src/kinx.y"
{ yyval.intval = KX_UNKNOWN_T; } break;
        case 425:
#line 915 "src/kinx.y"
{ yyval.intval = YYASP(2-3).arraytype.type; } break;
        case 426:
#line 919 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 427:
#line 920 "src/kinx.y"
{ yyval.obj = YYASP(2-3).obj; } break;
        case 428:
#line 924 "src/kinx.y"
{ yyval.obj = NULL; } break;
        case 431:
#line 930 "src/kinx.y"
{ yyval.obj = kx_gen_uexpr_object(KXOP_SPREAD, YYASP(2-2).obj); } break;
        case 432:
#line 931 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, YYASP(3-3).obj, YYASP(1-3).obj); } break;
        case 433:
#line 932 "src/kinx.y"
{ yyval.obj = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, YYASP(4-4).obj), YYASP(1-4).obj); } break;
        case 436:
#line 938 "src/kinx.y"
{ yyval.obj = kx_gen_str_object(YYASP(1-1).strval); } break;
        case 437:
#line 942 "src/kinx.y"
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
