%{
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <kvec.h>
#include <kinx.h>
#include <parser.tab.h>

// #define YYDEBUG 1

%}

%union {
    kx_object_t *obj;
    int         type;
    int64_t     intval;
    double      dblval;
    const char  *strval;
}

%token ERROR
%token IF ELSE WHILE DO FOR TRY CATCH FINALLY BREAK CONTINUE
%token NEW VAR FUNCTION PUBLIC PRIVATE PROTECTED CLASS RETURN THROW
%token EQEQ NEQ LE GE LGE LOR LAND INC DEC SHL SHR
%token ADDEQ SUBEQ MULEQ DIVEQ MODEQ ANDEQ OREQ XOREQ LANDEQ LOREQ SHLEQ SHREQ
%token NUL TRUE FALSE
%token IMPORT
%token<strval> MODULENAME
%token<strval> NAME
%token<strval> STR
%token<intval> INT
%token<dblval> DBL

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
%type<obj> Array
%type<obj> Object
%type<obj> AssignExpressionList
%type<obj> KeyValueList
%type<obj> KeyValue
%type<obj> VarDeclStatement
%type<obj> DeclAssignExpressionList
%type<obj> DeclAssignExpression
%type<obj> FunctionDeclStatement
%type<obj> NormalFunctionDeclStatement
%type<obj> AnonymousFunctionDeclStatement
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
    | IMPORT VAR NAME '=' MODULENAME ';' { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($3), kx_gen_import_object($5)); }
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
    : IF '(' AssignExpression ')' Statement { $$ = kx_gen_stmt_object(KXST_IF, $3, $5, NULL); }
    | IF '(' AssignExpression ')' Statement ELSE Statement { $$ = kx_gen_stmt_object(KXST_IF, $3, $5, $7); }
    ;

WhileStatement
    : WHILE '(' AssignExpression ')' Statement { $$ = kx_gen_stmt_object(KXST_WHILE, $3, $5, NULL); }
    ;

DoWhileStatement
    : DO Statement WHILE '(' AssignExpression ')' ';' { $$ = kx_gen_stmt_object(KXST_DO, $5, $2, NULL); }
    ;

ForStatement
    : FOR '(' VAR DeclAssignExpressionList ';' AssignExpression_Opt ';' AssignExpression_Opt ')' Statement
        { $$ = kx_gen_stmt_object(KXST_FOR, kx_gen_stmt_object(KXST_FORCOND, $4, $6, $8), $10, NULL); }
    | FOR '(' AssignExpression ';' AssignExpression_Opt ';' AssignExpression_Opt ')' Statement
        { $$ = kx_gen_stmt_object(KXST_FOR, kx_gen_stmt_object(KXST_FORCOND, $3, $5, $7), $9, NULL); }
    | FOR '(' ';' AssignExpression_Opt ';' AssignExpression_Opt ')' Statement
        { $$ = kx_gen_stmt_object(KXST_FOR, kx_gen_stmt_object(KXST_FORCOND, NULL, $4, $6), $8, NULL); }
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
    : RETURN AssignExpression_Opt ';' { $$ = kx_gen_stmt_object(KXST_RET, $2, NULL, NULL); }
    ;

ThrowStatement
    : THROW AssignExpression_Opt ';' { $$ = kx_gen_stmt_object(KXST_THROW, $2, NULL, NULL); }
    ;

ExpressionStatement
    : AssignExpression_Opt ';' { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    ;

AssignExpression_Opt
    : { $$ = NULL; }
    | AssignExpression
    ;

AssignExpression
    : LogicalOrExpression
    | AssignExpression '=' FunctionExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, $3); }
    | AssignExpression SHLEQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_SHL, $1, $3); }
    | AssignExpression SHREQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_SHR, $1, $3); }
    | AssignExpression ADDEQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_ADD, $1, $3); }
    | AssignExpression SUBEQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_SUB, $1, $3); }
    | AssignExpression MULEQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_MUL, $1, $3); }
    | AssignExpression DIVEQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_DIV, $1, $3); }
    | AssignExpression MODEQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_MOD, $1, $3); }
    | AssignExpression ANDEQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_AND, $1, $3); }
    | AssignExpression OREQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_OR, $1, $3); }
    | AssignExpression XOREQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_XOR, $1, $3); }
    | AssignExpression LANDEQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_LAND, $1, $3); }
    | AssignExpression LOREQ LogicalOrExpression { $$ = kx_gen_bassign_object(KXOP_ASSIGN_LOR, $1, $3); }
    ;

FunctionExpression
    : AnonymousFunctionDeclStatement
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
    | '+' PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_POSITIVE, $2); }
    | '-' PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_NEGATIVE, $2); }
    | INC PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_INC, $2); }
    | DEC PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_DEC, $2); }
    ;

PostfixExpression
    : Factor IncDec_Opt { $$ = (($2 < 0) ? $1 : kx_gen_uexpr_object($2, $1)); }
    | PostfixExpression '[' AssignExpression ']' { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | PostfixExpression '.' NAME { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, kx_gen_str_object($3)); }
    | PostfixExpression '(' CallArgumentList_Opts ')' { $$ = kx_gen_bexpr_object(KXOP_CALL, $1, $3); }
    ;

IncDec_Opt
    : { $$ = -1; }
    | INC { $$ = KXOP_INCP; }
    | DEC { $$ = KXOP_DECP; }
    ;

Factor
    : STR { $$ = kx_gen_str_object($1); }
    | INT { $$ = kx_gen_int_object($1); }
    | DBL { $$ = kx_gen_dbl_object($1); }
    | NUL { $$ = kx_gen_special_object(KXVL_NULL); }
    | NAME { $$ = kx_gen_var_object($1); }
    | TRUE { $$ = kx_gen_special_object(KXVL_TRUE); }
    | FALSE { $$ = kx_gen_special_object(KXVL_FALSE); }
    | Array
    | Object
    | '(' AssignExpression ')' { $$ = $2; }
    | '(' AnonymousFunctionDeclStatement ')' { $$ = $2; }
    | NEW Factor { $$ = kx_gen_bexpr_object(KXOP_IDX, $2, kx_gen_str_object("create")); }
    ;

Array
    : '[' ']' { $$ = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
    | '[' AssignExpressionList Comma_Opt ']' { $$ = kx_gen_uexpr_object(KXOP_MKARY, $2); }
    ;

Object
    : '{' KeyValueList Comma_Opt '}' { $$ = kx_gen_uexpr_object(KXOP_MKOBJ, $2); }
    ;

Comma_Opt
    : {}
    | ','
    ;

AssignExpressionList
    : AssignExpression
    | AssignExpressionList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

KeyValueList
    : KeyValue
    | KeyValueList ',' KeyValue { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

KeyValue
    : STR ':' AssignExpression { $$ = kx_gen_keyvalue_object($1, $3); }
    | STR ':' AnonymousFunctionDeclStatement { $$ = kx_gen_keyvalue_object($1, $3); }
    | NAME ':' AssignExpression { $$ = kx_gen_keyvalue_object($1, $3); }
    | NAME ':' AnonymousFunctionDeclStatement { $$ = kx_gen_keyvalue_object($1, $3); }
    ;

VarDeclStatement
    : VAR DeclAssignExpressionList ';' { $$ = $2; }
    ;

DeclAssignExpressionList
    : DeclAssignExpression
    | DeclAssignExpressionList ',' DeclAssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

DeclAssignExpression
    : NAME { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($1), NULL); }
    | NAME '=' AssignExpression { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($1), $3); }
    | NAME '=' AnonymousFunctionDeclStatement { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($1), $3); }
    ;

FunctionDeclStatement
    : NormalFunctionDeclStatement { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    | ClassFunctionDeclStatement { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    ;

NormalFunctionDeclStatement
    : FUNCTION NAME '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $2, $4, $6, NULL); }
    ;

AnonymousFunctionDeclStatement
    : FUNCTION '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, $3, $5, NULL); }
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
    | ':' Factor ClassCallArgumentList_Opts { $$ =  kx_gen_bexpr_object(KXOP_ASSIGN, kx_gen_var_object("this"), kx_gen_bexpr_object(KXOP_CALL, $2, $3)); }
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
    : NAME { $$ = kx_gen_var_object($1); }
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
    | CallArgumentList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

%%

int yyerror(const char* msg)
{
    return printf("Error: %s at %d (pos:%d)\n", msg, kx_lexinfo.line, kx_lexinfo.pos);
}
