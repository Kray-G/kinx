%{
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <kvec.h>
#include <kinx.h>
#include <parser.tab.h>

// #define YYDEBUG 1

%}

%union {
    kx_object_t   *obj;
    int           type;
    int64_t       intval;
    double        dblval;
    const char    *strval;
    const uint8_t *binval;
}

%token ERROR
%token IF ELSE WHILE DO FOR TRY CATCH FINALLY BREAK CONTINUE
%token NEW VAR NATIVE FUNCTION PUBLIC PRIVATE PROTECTED CLASS RETURN THROW
%token EQEQ NEQ LE GE LGE LOR LAND INC DEC SHL SHR
%token ADDEQ SUBEQ MULEQ DIVEQ MODEQ ANDEQ OREQ XOREQ LANDEQ LOREQ SHLEQ SHREQ
%token NUL TRUE FALSE
%token IMPORT USING DARROW SQ DQ MLSTR BINEND
%token<strval> NAME
%token<strval> STR
%token<strval> BIGINT
%token<intval> INT
%token<intval> TYPE
%token<intval> TYPEOF
%token<dblval> DBL
%token<binval> BIN

%type<obj> Program
%type<obj> StatementList
%type<obj> Statement
%type<obj> BlockStatement
%type<obj> DefinitionStatement
%type<obj> IfStatement
%type<obj> WhileStatement
%type<obj> DoWhileStatement
%type<obj> ForStatement
%type<obj> TryCatchStatement
%type<obj> CatchStatement_Opt
%type<obj> FinallyStatement_Opt
%type<obj> ReturnStatement
%type<obj> ThrowStatement
%type<obj> ExpressionStatement
%type<obj> BreakStatement
%type<obj> LabelStatement
%type<obj> AssignExpression_Opt
%type<obj> AssignExpression
%type<obj> AssignExpressionList_Opt
%type<obj> TernaryExpression
%type<obj> FunctionExpression
%type<obj> LogicalOrExpression
%type<obj> LogicalAndExpression
%type<obj> BitOrExpression
%type<obj> BitXorExpression
%type<obj> BitAndExpression
%type<obj> CompareEqualExpression
%type<obj> CompareExpression
%type<obj> ShiftExpression
%type<obj> Expression
%type<obj> Term
%type<obj> PrefixExpression
%type<obj> PostfixExpression
%type<type> IncDec_Opt
%type<obj> Factor
%type<obj> String
%type<obj> Binary
%type<obj> Array
%type<obj> Object
%type<obj> ArrayItemList
%type<obj> AssignExpressionList
%type<obj> KeyValueList
%type<obj> KeyValue
%type<obj> VarDeclStatement
%type<obj> DeclAssignExpressionList
%type<obj> DeclAssignExpression
%type<obj> FunctionDeclStatement
%type<obj> NormalFunctionDeclStatement
%type<obj> AnonymousFunctionDeclExpression
%type<obj> ClassFunctionDeclStatement
%type<obj> ClassDeclStatement
%type<obj> Inherit_Opt
%type<obj> ClassArgumentList_Opts
%type<obj> ClassCallArgumentList_Opts
%type<obj> ArgumentList_Opts
%type<obj> ArgumentList
%type<obj> Argument
%type<obj> CallArgumentList_Opts
%type<obj> CallArgumentList
%type<intval> NativeType

%%

Program
    : StatementList         { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, $1, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
    ;

StatementList
    : Statement
    | StatementList Statement { $$ = kx_gen_bexpr_object(KXST_STMTLIST, $1, $2); }
    ;

Statement
    : BlockStatement
    | IfStatement
    | WhileStatement
    | DoWhileStatement
    | ForStatement
    | TryCatchStatement
    | ReturnStatement
    | ThrowStatement
    | ExpressionStatement
    | DefinitionStatement
    | BreakStatement
    | LabelStatement
    | IMPORT VAR NAME '=' STR ';' { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($3, KX_UNKNOWN_T), kx_gen_import_object($5)); }
    ;

BlockStatement
    : '{' '}' { $$ = NULL; }
    | '{' StatementList '}' { $$ = kx_gen_block_object($2); }
    ;

DefinitionStatement
    : VarDeclStatement
    | FunctionDeclStatement
    | ClassDeclStatement
    ;

BreakStatement
    : BREAK ';' { $$ = kx_gen_break_object(KXST_BREAK, NULL); }
    | BREAK NAME ';' { $$ = kx_gen_break_object(KXST_BREAK, $2); }
    | CONTINUE ';' { $$ = kx_gen_break_object(KXST_CONTINUE, NULL); }
    | CONTINUE NAME ';' { $$ = kx_gen_break_object(KXST_CONTINUE, $2); }
    ;

LabelStatement
    : NAME ':' Statement { $$ = kx_gen_label_object(KXST_LABEL, $1, $3); }
    ;

IfStatement
    : IF '(' AssignExpressionList ')' Statement { $$ = kx_gen_stmt_object(KXST_IF, $3, $5, NULL); }
    | IF '(' AssignExpressionList ')' Statement ELSE Statement { $$ = kx_gen_stmt_object(KXST_IF, $3, $5, $7); }
    ;

WhileStatement
    : WHILE '(' AssignExpressionList ')' Statement { $$ = kx_gen_stmt_object(KXST_WHILE, $3, $5, NULL); }
    ;

DoWhileStatement
    : DO Statement WHILE '(' AssignExpressionList ')' ';' { $$ = kx_gen_stmt_object(KXST_DO, $5, $2, NULL); }
    ;

ForStatement
    : FOR '(' VAR DeclAssignExpressionList ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement
        { $$ = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                $4,
                $6,
                kx_gen_stmt_object(KXST_EXPR, $8, NULL, NULL)),
            $10, NULL); }
    | FOR '(' AssignExpressionList ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement
        { $$ = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, $3, NULL, NULL),
                $5,
                kx_gen_stmt_object(KXST_EXPR, $7, NULL, NULL)),
            $9, NULL); }
    | FOR '(' ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement
        { $$ = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                $4,
                kx_gen_stmt_object(KXST_EXPR, $6, NULL, NULL)),
            $8, NULL); }
    ;

TryCatchStatement
    : TRY BlockStatement CatchStatement_Opt FinallyStatement_Opt { $$ = kx_gen_stmt_object(KXST_TRY, $2, $3, $4); }
    ;

CatchStatement_Opt
    : { $$ = NULL; }
    | CATCH '(' NAME ')' BlockStatement { $$ = kx_gen_catch_object(KXST_CATCH, $3, $5, NULL); }
    ;

FinallyStatement_Opt
    : { $$ = NULL; }
    | FINALLY BlockStatement { $$ = $2; }
    ;

ReturnStatement
    : RETURN AssignExpressionList_Opt ';' { $$ = kx_gen_stmt_object(KXST_RET, $2, NULL, NULL); }
    ;

ThrowStatement
    : THROW AssignExpressionList_Opt ';' { $$ = kx_gen_stmt_object(KXST_THROW, $2, NULL, NULL); }
    ;

ExpressionStatement
    : AssignExpression_Opt ';' { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    ;

AssignExpression_Opt
    : { $$ = NULL; }
    | AssignExpression
    ;

AssignExpressionList_Opt
    : { $$ = NULL; }
    | AssignExpressionList
    ;

AssignExpression
    : TernaryExpression
    | AssignExpression '=' TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, $3); }
    | AssignExpression SHLEQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_SHL, $1, $3); }
    | AssignExpression SHREQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_SHR, $1, $3); }
    | AssignExpression ADDEQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_ADD, $1, $3); }
    | AssignExpression SUBEQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_SUB, $1, $3); }
    | AssignExpression MULEQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_MUL, $1, $3); }
    | AssignExpression DIVEQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_DIV, $1, $3); }
    | AssignExpression MODEQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_MOD, $1, $3); }
    | AssignExpression ANDEQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_AND, $1, $3); }
    | AssignExpression OREQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_OR, $1, $3); }
    | AssignExpression XOREQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_XOR, $1, $3); }
    | AssignExpression LANDEQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_LAND, $1, $3)); }
    | AssignExpression LOREQ TernaryExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_LOR, $1, $3)); }
    ;

TernaryExpression
    : FunctionExpression
    | LogicalOrExpression '?' LogicalOrExpression ':' LogicalOrExpression { $$ = kx_gen_texpr_object($1, $3, $5); }
    ;

FunctionExpression
    : AnonymousFunctionDeclExpression
    | LogicalOrExpression
    ;

LogicalOrExpression
    : LogicalAndExpression
    | LogicalOrExpression LOR LogicalAndExpression { $$ = kx_gen_bexpr_object(KXOP_LOR, $1, $3); }
    ;

LogicalAndExpression
    : BitOrExpression
    | LogicalAndExpression LAND BitOrExpression { $$ = kx_gen_bexpr_object(KXOP_LAND, $1, $3); }
    ;

BitOrExpression
    : BitXorExpression
    | BitOrExpression '|' BitXorExpression { $$ = kx_gen_bexpr_object(KXOP_OR, $1, $3); }
    ;

BitXorExpression
    : BitAndExpression
    | BitXorExpression '^' BitAndExpression  { $$ = kx_gen_bexpr_object(KXOP_XOR, $1, $3); }
    ;

BitAndExpression
    : CompareEqualExpression
    | BitAndExpression '&' CompareEqualExpression { $$ = kx_gen_bexpr_object(KXOP_AND, $1, $3); }
    ;

CompareEqualExpression
    : CompareExpression
    | CompareEqualExpression EQEQ CompareExpression { $$ = kx_gen_bexpr_object(KXOP_EQEQ, $1, $3); }
    | CompareEqualExpression NEQ CompareExpression { $$ = kx_gen_bexpr_object(KXOP_NEQ, $1, $3); }
    ;

CompareExpression
    : ShiftExpression
    | CompareExpression '<' ShiftExpression { $$ = kx_gen_bexpr_object(KXOP_LT, $1, $3); }
    | CompareExpression LE ShiftExpression { $$ = kx_gen_bexpr_object(KXOP_LE, $1, $3); }
    | CompareExpression '>' ShiftExpression { $$ = kx_gen_bexpr_object(KXOP_GT, $1, $3); }
    | CompareExpression GE ShiftExpression { $$ = kx_gen_bexpr_object(KXOP_GE, $1, $3); }
    | CompareExpression LGE ShiftExpression { $$ = kx_gen_bexpr_object(KXOP_LGE, $1, $3); }
    ;

ShiftExpression
    : Expression
    | ShiftExpression SHL Expression { $$ = kx_gen_bexpr_object(KXOP_SHL, $1, $3); }
    | ShiftExpression SHR Expression { $$ = kx_gen_bexpr_object(KXOP_SHR, $1, $3); }
    ;

Expression
    : Term
    | Expression '+' Term { $$ = kx_gen_bexpr_object(KXOP_ADD, $1, $3); }
    | Expression '-' Term { $$ = kx_gen_bexpr_object(KXOP_SUB, $1, $3); }
    ;

Term
    : PrefixExpression
    | Term '*' PrefixExpression { $$ = kx_gen_bexpr_object(KXOP_MUL, $1, $3); }
    | Term '/' PrefixExpression { $$ = kx_gen_bexpr_object(KXOP_DIV, $1, $3); }
    | Term '%' PrefixExpression { $$ = kx_gen_bexpr_object(KXOP_MOD, $1, $3); }
    ;

PrefixExpression
    : PostfixExpression
    | '!' PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_NOT, $2); }
    | '+' PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_POSITIVE, $2); }
    | '-' PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_NEGATIVE, $2); }
    | INC PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_INC, $2); }
    | DEC PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_DEC, $2); }
    ;

PostfixExpression
    : Factor IncDec_Opt { $$ = (($2 < 0) ? $1 : kx_gen_uexpr_object($2, $1)); }
    | PostfixExpression '[' AssignExpression ']' { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | PostfixExpression '.' NAME { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, kx_gen_str_object($3)); }
    | PostfixExpression '.' TYPEOF { $$ = kx_gen_typeof_object($1, $3); }
    | PostfixExpression '(' CallArgumentList_Opts ')' { $$ = kx_gen_bexpr_object(KXOP_CALL, $1, $3); }
    ;

IncDec_Opt
    : { $$ = -1; }
    | INC { $$ = KXOP_INCP; }
    | DEC { $$ = KXOP_DECP; }
    ;

Factor
    : INT { $$ = kx_gen_int_object($1); }
    | DBL { $$ = kx_gen_dbl_object($1); }
    | BIGINT { $$ = kx_gen_big_object($1); }
    | NUL { $$ = kx_gen_special_object(KXVL_NULL); }
    | NAME { $$ = kx_gen_var_object($1, KX_UNKNOWN_T); }
    | TRUE { $$ = kx_gen_special_object(KXVL_TRUE); }
    | FALSE { $$ = kx_gen_special_object(KXVL_FALSE); }
    | String
    | Array
    | Binary
    | Object
    | IMPORT '(' STR ')' { $$ = kx_gen_import_object($3); }
    | '(' AssignExpression ')' { $$ = $2; }
    | NEW Factor { $$ = kx_gen_bexpr_object(KXOP_IDX, $2, kx_gen_str_object("create")); }
    | '@' NAME { $$ = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), kx_gen_str_object($2)); }
    ;

String
    : STR { $$ = kx_gen_str_object($1); }
    | String STR { $$ = kx_gen_bexpr_object(KXOP_ADD, $1, kx_gen_str_object($2)); }
    ;

Array
    : '[' ']' { $$ = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
    | '[' ArrayItemList Comma_Opt ']' { $$ = kx_gen_uexpr_object(KXOP_MKARY, $2); }
    ;

Binary
    : '<' '>' { $$ = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
    | '<' BinStart ArrayItemList Comma_Opt BINEND { $$ = kx_gen_uexpr_object(KXOP_MKBIN, $3); }
    ;

BinStart
    : { kx_make_bin_mode(); }
    ;

Object
    : '{' KeyValueList Comma_Opt '}' { $$ = kx_gen_uexpr_object(KXOP_MKOBJ, $2); }
    ;

Comma_Opt
    : {}
    | ','
    ;

ArrayItemList
    : AssignExpression
    | ArrayItemList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

AssignExpressionList
    : AssignExpression
    | AssignExpressionList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRSEQ, $1, $3); }
    ;

KeyValueList
    : KeyValue
    | KeyValueList ',' KeyValue { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

KeyValue
    : STR ':' AssignExpression { $$ = kx_gen_keyvalue_object($1, $3); }
    | NAME ':' AssignExpression { $$ = kx_gen_keyvalue_object($1, $3); }
    ;

VarDeclStatement
    : VAR DeclAssignExpressionList ';' { $$ = $2; }
    ;

DeclAssignExpressionList
    : DeclAssignExpression
    | DeclAssignExpressionList ',' DeclAssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

DeclAssignExpression
    : NAME { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($1, KX_UNKNOWN_T), NULL); }
    | NAME ':' TYPE { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($1, $3), NULL); }
    | NAME '=' AssignExpression { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($1, KX_UNKNOWN_T), $3); }
    | NAME ':' TYPE '=' AssignExpression { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($1, $3), $5); }
    ;

FunctionDeclStatement
    : NormalFunctionDeclStatement { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    | ClassFunctionDeclStatement { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    ;

NormalFunctionDeclStatement
    : FUNCTION NAME '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $2, $4, $6, NULL); }
    | NativeKeyword NativeType NAME '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_NATIVE, $2, $3, $5, $7, NULL); }
    ;

NativeKeyword
    : NATIVE { kx_make_native_mode(); }
    ;

NativeType
    : { $$ = KX_UNKNOWN_T; }
    | ':' TYPE { $$ = $2; }
    ;

AnonymousFunctionDeclExpression
    : FUNCTION '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, $3, $5, NULL); }
    | NativeKeyword NativeType '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_NATIVE, $2, NULL, $4, $6, NULL); }
    | '&' '(' ArgumentList_Opts ')' DARROW LogicalOrExpression { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, $3, kx_gen_stmt_object(KXST_RET, $6, NULL, NULL), NULL); }
    ;

ClassFunctionDeclStatement
    : PUBLIC NAME '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, $2, $4, $6, NULL); }
    | PRIVATE NAME '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, $2, $4, $6, NULL); }
    | PROTECTED NAME '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, $2, $4, $6, NULL); }
    ;

ClassDeclStatement
    : CLASS NAME ClassArgumentList_Opts Inherit_Opt BlockStatement { $$ = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, $2, $3, $5, $4); }
    ;

Inherit_Opt
    : { $$ = NULL; }
    | ':' Factor ClassCallArgumentList_Opts
        {
            $$ = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, $2, kx_gen_str_object("create")), $3)),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
    ;

ClassArgumentList_Opts
    : { $$ = NULL; }
    | '(' ArgumentList_Opts ')' { $$ = $2; }
    ;

ArgumentList_Opts
    : { $$ = NULL; }
    | ArgumentList
    ;

ArgumentList
    : Argument
    | ArgumentList ',' Argument { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

Argument
    : NAME { $$ = kx_gen_var_object($1, KX_UNKNOWN_T); }
    | NAME ':' TYPE { $$ = kx_gen_var_object($1, $3); }
    ;

ClassCallArgumentList_Opts
    : { $$ = NULL; }
    | '(' CallArgumentList_Opts ')' { $$ = $2; }
    ;

CallArgumentList_Opts
    : { $$ = NULL; }
    | CallArgumentList
    ;

CallArgumentList
    : AssignExpression
    | CallArgumentList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $3, $1); }
    ;

%%

int yyerror(const char *msg)
{
    ++g_yyerror;
    if (!kx_lexinfo.quiet) {
        if (kx_lexinfo.file) {
            return printf("Error: %s near the %s:%d\n", msg, kx_lexinfo.file, kx_lexinfo.line);
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
        return printf("Error: %s near the %s:%d\n", msg, file, line);
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
        r += printf(" near the %s:%d\n", file, line);
        return r;
    }
    return 0;
}

int kx_yywarning(const char *msg)
{
    ++g_yywarning;
    if (!kx_lexinfo.quiet) {
        if (kx_lexinfo.file) {
            return printf("Warning: %s near the %s:%d\n", msg, kx_lexinfo.file, kx_lexinfo.line);
        } else {
            return printf("Warning: %s near the <eval>:%d\n", msg, kx_lexinfo.line);
        }
    }
    return 0;
}
