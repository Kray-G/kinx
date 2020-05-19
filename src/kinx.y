%{
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <kvec.h>
#include <kinx.h>

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
%token IF ELSE WHILE DO FOR IN TRY CATCH FINALLY BREAK CONTINUE SWITCH CASE DEFAULT ENUM COROUTINE
%token NEW VAR CONST NATIVE FUNCTION PUBLIC PRIVATE PROTECTED CLASS RETURN THROW YIELD MODULE MIXIN
%token SYSCLASS SYSMODULE SYSFUNC
%token EQEQ NEQ LE GE LGE LOR LAND INC DEC SHL SHR POW LUNDEF
%token ADDEQ SUBEQ MULEQ DIVEQ MODEQ ANDEQ OREQ XOREQ LANDEQ LOREQ LUNDEFEQ SHLEQ SHREQ REGEQ REGNE
%token NUL TRUE FALSE
%token IMPORT USING DARROW SQ DQ MLSTR BINEND DOTS2 DOTS3 REGPF NAMESPACE SYSNS SYSRET_NV
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
%type<obj> NamespaceStatement
%type<strval> NamespaceName
%type<obj> EnumStatement
%type<obj> EnumList
%type<obj> DefinitionStatement
%type<obj> IfStatement
%type<obj> WhileStatement
%type<obj> DoWhileStatement
%type<obj> SwitchCaseStatement
%type<obj> CaseStatement
%type<obj> ForStatement
%type<obj> ForInVariable
%type<obj> TryCatchStatement
%type<obj> CatchStatement_Opt
%type<obj> FinallyStatement_Opt
%type<obj> ReturnStatement
%type<obj> YieldStatement
%type<obj> YieldExpression
%type<obj> ThrowStatement
%type<obj> MixinStatement
%type<obj> MixinModuleList
%type<obj> ExpressionStatement
%type<obj> Modifier_Opt
%type<obj> BreakStatement
%type<obj> LabelStatement
%type<obj> AssignExpression_Opt
%type<obj> AssignExpression
%type<obj> AssignRightHandSide
%type<obj> ObjectSpecialSyntax
%type<obj> AssignExpressionList_Opt
%type<obj> TernaryExpression
%type<obj> FunctionExpression
%type<obj> LogicalUndefExpression
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
%type<obj> Exponentiation
%type<obj> RegexMatch
%type<obj> PrefixExpression
%type<obj> PostfixExpression
%type<obj> PropertyName
%type<type> PostIncDec
%type<obj> Factor
%type<obj> Binary
%type<obj> Array
%type<obj> Object
%type<obj> Regex
%type<strval> RegexString
%type<obj> ArrayItemList
%type<obj> AssignExpressionList
%type<obj> AssignExpressionObjList
%type<obj> KeyValueList
%type<obj> KeyValue
%type<strval> VarName
%type<strval> KeySpecialName
%type<strval> ClassFunctionName
%type<obj> VarDeclStatement
%type<obj> DeclAssignExpressionList
%type<obj> DeclAssignExpression
%type<obj> FunctionDeclStatement
%type<obj> NormalFunctionDeclStatement
%type<obj> AnonymousFunctionDeclExpression
%type<obj> ClassFunctionDeclStatement
%type<obj> ClassDeclStatement
%type<obj> ModuleDeclStatement
%type<obj> Inherit_Opt
%type<obj> ClassArgumentList_Opts
%type<obj> ClassCallArgumentList_Opts
%type<obj> ArgumentList_Opts
%type<obj> ArgumentList
%type<obj> Argument
%type<obj> CallArgumentList_Opts
%type<obj> CallArgumentList
%type<obj> CallArgument
%type<intval> NativeType_Opt
%type<intval> TypeName
%type<intval> ReturnType_Opt

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
    | NamespaceStatement
    | EnumStatement
    | IfStatement
    | WhileStatement
    | DoWhileStatement
    | SwitchCaseStatement
    | CaseStatement
    | ForStatement
    | TryCatchStatement
    | ReturnStatement
    | YieldStatement
    | ThrowStatement
    | MixinStatement
    | ExpressionStatement
    | DefinitionStatement
    | BreakStatement
    | LabelStatement
    | IMPORT VAR NAME '=' STR ';' { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($3, KX_UNKNOWN_T), kx_gen_import_object($5)); }
    | error ';' { yyerrok; }
    ;

BlockStatement
    : '{' '}' { $$ = NULL; }
    | '{' StatementList '}' { $$ = kx_gen_block_object($2); }
    ;

NamespaceStatement
    : NAMESPACE NamespaceName '{' '}' { $$ = NULL; }
    | SYSNS NamespaceName '{' '}' { $$ = NULL; }
    | NAMESPACE NamespaceName '{' StatementList '}' { $$ = kx_gen_namespace_object(0, $2, $4); }
    | SYSNS NamespaceName '{' StatementList '}' { $$ = kx_gen_namespace_object(1, $2, $4); }
    ;

NamespaceName
    : NAME { $$ = kx_gen_namespace_name_object($1); }
    ;

EnumStatement
    : ENUM '{' EnumList Comma_Opt '}' { $$ = kx_gen_enum_reset($3); }
    ;

EnumList
    : NAME { $$ = kx_gen_enum_object($1); }
    | NAME '=' INT { $$ = kx_gen_enum_object_with($1, $3); }
    | NAME '=' '-' INT { $$ = kx_gen_enum_object_with($1, -$4); }
    | EnumList ',' NAME { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_enum_object($3)); }
    | EnumList ',' NAME '=' INT { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_enum_object_with($3, $5)); }
    | EnumList ',' NAME '=' '-' INT { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_enum_object_with($3, -$6)); }
    ;

DefinitionStatement
    : VarDeclStatement
    | FunctionDeclStatement
    | ClassDeclStatement
    | ModuleDeclStatement
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

SwitchCaseStatement
    : SWITCH '(' AssignExpressionList ')' BlockStatement { $$ = kx_gen_stmt_object(KXST_SWITCH, $3, $5, NULL); }
    ;

CaseStatement
    : CASE AssignExpression ':' { $$ = kx_gen_case_stmt_object(KXCS_CASE, $2); }
    | DEFAULT ':' { $$ = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
    ;

ForStatement
    : FOR '(' VAR DeclAssignExpressionList ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement
        { $$ = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                $4,
                $6,
                $8 == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, $8, NULL, NULL)),
            $10, NULL); }
    | FOR '(' AssignExpressionList ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement
        { $$ = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, $3, NULL, NULL),
                $5,
                $7 == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, $7, NULL, NULL)),
            $9, NULL); }
    | FOR '(' ';' AssignExpressionList_Opt ';' AssignExpressionList_Opt ')' Statement
        { $$ = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                $4,
                $6 == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, $6, NULL, NULL)),
            $8, NULL); }
    | FOR '(' ForInVariable IN AssignExpressionList ')' Statement
        { $$ = kx_gen_forin_object($3, $5, $7, 0); }
    | FOR '(' VAR ForInVariable IN AssignExpressionList ')' Statement
        { $$ = kx_gen_forin_object($4, $6, $8, 1); }
    ;

ForInVariable
    : NAME { $$ = kx_gen_var_object($1, KX_UNKNOWN_T); }
    | '[' ArrayItemList Comma_Opt ']' { $$ = kx_gen_uexpr_object(KXOP_MKARY, $2); }
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

BreakStatement
    : BREAK Modifier_Opt ';' { $$ = kx_gen_modifier($2, kx_gen_break_object(KXST_BREAK, NULL)); }
    | BREAK NAME Modifier_Opt ';' { $$ = kx_gen_modifier($3, kx_gen_break_object(KXST_BREAK, $2)); }
    | CONTINUE Modifier_Opt ';' { $$ = kx_gen_modifier($2, kx_gen_break_object(KXST_CONTINUE, NULL)); }
    | CONTINUE NAME Modifier_Opt ';' { $$ = kx_gen_modifier($3, kx_gen_break_object(KXST_CONTINUE, $2)); }
    ;

ReturnStatement
    : RETURN AssignExpressionList_Opt Modifier_Opt ';' { $$ = kx_gen_modifier($3, kx_gen_stmt_object(KXST_RET, $2, NULL, NULL)); }
    | SYSRET_NV ';' { $$ = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); }
    ;

YieldStatement
    : YieldExpression Modifier_Opt ';' { $$ = kx_gen_modifier($2, kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL)); }
    ;

YieldExpression
    : YIELD AssignExpression { $$ = kx_gen_uexpr_object(KXOP_YIELD, $2); }
    | YIELD { $$ = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
    | AssignExpression '=' YIELD AssignExpression { $$ = $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_uexpr_object(KXOP_YIELD, $4)); }
    | AssignExpression '=' YIELD { $$ = $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
    ;

ThrowStatement
    : THROW AssignExpressionList_Opt Modifier_Opt ';' { $$ = kx_gen_modifier($3, kx_gen_stmt_object(KXST_THROW, $2, NULL, NULL)); }
    ;

MixinStatement
    : MIXIN MixinModuleList ';' { $$ = $2; }
    ;

MixinModuleList
    : NAME { $$ = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object($1, KX_OBJ_T), NULL); }
    | MixinModuleList ',' NAME { kx_gen_stmt_object(KXST_MIXIN, $1, kx_gen_var_object($3, KX_OBJ_T), NULL); }
    ;

ExpressionStatement
    : AssignExpression_Opt ';' { $$ = $1; }
    ;

AssignExpression_Opt
    : { $$ = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
    | AssignExpression Modifier_Opt { $$ = kx_gen_modifier($2, kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL)); }
    ;

AssignExpressionList_Opt
    : { $$ = NULL; }
    | AssignExpressionObjList
    ;

Modifier_Opt
    : { $$ = NULL; }
    | IF '(' AssignExpressionList ')' { $$ = kx_gen_stmt_object(KXST_IF, $3, NULL, NULL); }
    ;

AssignExpression
    : TernaryExpression
    | AssignExpression '=' AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, $3); }
    | AssignExpression SHLEQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_SHL, $1, $3)); }
    | AssignExpression SHREQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_SHR, $1, $3)); }
    | AssignExpression ADDEQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_ADD, $1, $3)); }
    | AssignExpression SUBEQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_SUB, $1, $3)); }
    | AssignExpression MULEQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_MUL, $1, $3)); }
    | AssignExpression DIVEQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_DIV, $1, $3)); }
    | AssignExpression MODEQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_MOD, $1, $3)); }
    | AssignExpression ANDEQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_AND, $1, $3)); }
    | AssignExpression OREQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_OR, $1, $3)); }
    | AssignExpression XOREQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_XOR, $1, $3)); }
    | AssignExpression LANDEQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_LAND, $1, $3)); }
    | AssignExpression LOREQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_LOR, $1, $3)); }
    | AssignExpression LUNDEFEQ AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, kx_gen_bassign_object(KXOP_LUNDEF, $1, $3)); }
    ;

AssignRightHandSide
    : TernaryExpression
    | ObjectSpecialSyntax
    ;

ObjectSpecialSyntax
    : '{' '}' { $$ = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
    | ObjectSpecialSyntax PostIncDec { $$ = kx_gen_uexpr_object($2, $1); }
    | ObjectSpecialSyntax '[' AssignExpression ']' { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | ObjectSpecialSyntax '.' PropertyName { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | ObjectSpecialSyntax '.' TYPEOF { $$ = kx_gen_typeof_object($1, $3); }
    | ObjectSpecialSyntax '(' CallArgumentList_Opts ')' { $$ = kx_gen_bexpr_object(KXOP_CALL, $1, $3); }
    ;

TernaryExpression
    : FunctionExpression
    | LogicalUndefExpression '?' TernaryExpression ':' TernaryExpression { $$ = kx_gen_texpr_object($1, $3, $5); }
    ;

FunctionExpression
    : AnonymousFunctionDeclExpression
    | LogicalUndefExpression
    ;

LogicalUndefExpression
    : LogicalOrExpression
    | LogicalUndefExpression LUNDEF LogicalOrExpression { $$ = kx_gen_bexpr_object(KXOP_LUNDEF, $1, $3); }
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
    : Exponentiation
    | Term '*' Exponentiation { $$ = kx_gen_bexpr_object(KXOP_MUL, $1, $3); }
    | Term '/' Exponentiation { $$ = kx_gen_bexpr_object(KXOP_DIV, $1, $3); }
    | Term '%' Exponentiation { $$ = kx_gen_bexpr_object(KXOP_MOD, $1, $3); }
    ;

Exponentiation
    : RegexMatch
    | Exponentiation POW RegexMatch { $$ = kx_gen_bexpr_object(KXOP_POW, $1, $3); }
    ;

RegexMatch
    : PrefixExpression
    | RegexMatch REGEQ PrefixExpression { $$ = kx_gen_bexpr_object(KXOP_REGEQ, $1, $3); }
    | RegexMatch REGNE PrefixExpression { $$ = kx_gen_bexpr_object(KXOP_REGNE, $1, $3); }
    | PrefixExpression DOTS2 { $$ = kx_gen_range_object($1, kx_gen_special_object(KXVL_NULL), 0); }
    | PrefixExpression DOTS2 PrefixExpression { $$ = kx_gen_range_object($1, $3, 0); }
    | PrefixExpression DOTS3 { $$ = kx_gen_range_object($1, kx_gen_special_object(KXVL_NULL), 1); }
    | PrefixExpression DOTS3 PrefixExpression { $$ = kx_gen_range_object($1, $3, 1); }
    ;

PrefixExpression
    : PostfixExpression
    | '~' PrefixExpression { $$ = kx_gen_uexpr_object(KXOP_BNOT, $2); }
    | '!' PrefixExpression { $$ = kx_gen_uexpr_object(KXOP_NOT, $2); }
    | '+' PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_POSITIVE, $2); }
    | '-' PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_NEGATIVE, $2); }
    | '*' PrefixExpression { $$ = kx_gen_uexpr_object(KXOP_CONV, $2); }
    | INC PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_INC, $2); }
    | DEC PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_DEC, $2); }
    ;

PostfixExpression
    : Factor
    | PostfixExpression PostIncDec { $$ = kx_gen_uexpr_object($2, $1); }
    | PostfixExpression '[' AssignExpression ']' { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | PostfixExpression '.' PropertyName { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | PostfixExpression '.' TYPEOF { $$ = kx_gen_typeof_object($1, $3); }
    | PostfixExpression '(' CallArgumentList_Opts ')' { $$ = kx_gen_bexpr_object(KXOP_CALL, $1, $3); }
    ;

PostIncDec
    : INC { $$ = KXOP_INCP; }
    | DEC { $$ = KXOP_DECP; }
    ;

Factor
    : INT { $$ = kx_gen_int_object($1); }
    | DBL { $$ = kx_gen_dbl_object($1); }
    | BIGINT { $$ = kx_gen_big_object($1); }
    | NUL { $$ = kx_gen_special_object(KXVL_NULL); }
    | VarName { $$ = kx_gen_var_object($1, KX_UNKNOWN_T); }
    | TRUE { $$ = kx_gen_special_object(KXVL_TRUE); }
    | FALSE { $$ = kx_gen_special_object(KXVL_FALSE); }
    | Array
    | Binary
    | Object
    | Regex
    | '.' PropertyName { $$ = $2; }
    | IMPORT '(' '(' STR ')' ')' { $$ = kx_gen_import_object($4); }
    | '(' AssignExpression ')' { $$ = $2; }
    | '(' ObjectSpecialSyntax ')' { $$ = $2; }
    | '(' STR ')' { $$ = kx_gen_str_object($2); }
    | NEW Factor { $$ = kx_gen_bexpr_object(KXOP_IDX, $2, kx_gen_str_object("create")); }
    | '@' PropertyName { $$ = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), $2); }
    | '@' TYPEOF { $$ = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), $2); }
    ;

VarName
    : NAME { $$ = $1; }
    | TYPE { $$ = kx_gen_typestr_object($1); }
    ;

PropertyName
    : NAME { $$ = kx_gen_str_object($1); }
    | IF { $$ = kx_gen_str_object("if"); }
    | ELSE { $$ = kx_gen_str_object("else"); }
    | WHILE { $$ = kx_gen_str_object("while"); }
    | DO { $$ = kx_gen_str_object("do"); }
    | FOR { $$ = kx_gen_str_object("for"); }
    | IN { $$ = kx_gen_str_object("in"); }
    | TRY { $$ = kx_gen_str_object("try"); }
    | CATCH { $$ = kx_gen_str_object("catch"); }
    | FINALLY { $$ = kx_gen_str_object("finally"); }
    | BREAK { $$ = kx_gen_str_object("break"); }
    | CONTINUE { $$ = kx_gen_str_object("continue"); }
    | SWITCH { $$ = kx_gen_str_object("switch"); }
    | CASE { $$ = kx_gen_str_object("case"); }
    | DEFAULT { $$ = kx_gen_str_object("default"); }
    | NEW { $$ = kx_gen_str_object("new"); }
    | VAR { $$ = kx_gen_str_object("var"); }
    | CONST { $$ = kx_gen_str_object("const"); }
    | NATIVE { $$ = kx_gen_str_object("native"); }
    | FUNCTION { $$ = kx_gen_str_object("function"); }
    | SYSFUNC { $$ = kx_gen_str_object("_function"); }
    | PUBLIC { $$ = kx_gen_str_object("public"); }
    | PRIVATE { $$ = kx_gen_str_object("private"); }
    | PROTECTED { $$ = kx_gen_str_object("protectd"); }
    | CLASS { $$ = kx_gen_str_object("class"); }
    | MODULE { $$ = kx_gen_str_object("module"); }
    | RETURN { $$ = kx_gen_str_object("return"); }
    | YIELD { $$ = kx_gen_str_object("yield"); }
    | THROW { $$ = kx_gen_str_object("throw"); }
    | NUL { $$ = kx_gen_str_object("null"); }
    | TRUE { $$ = kx_gen_str_object("true"); }
    | FALSE { $$ = kx_gen_str_object("false"); }
    | IMPORT { $$ = kx_gen_str_object("import"); }
    | USING { $$ = kx_gen_str_object("using"); }
    | SHL { $$ = kx_gen_str_object("<<"); }
    | SHR { $$ = kx_gen_str_object(">>"); }
    | EQEQ { $$ = kx_gen_str_object("=="); }
    | NEQ { $$ = kx_gen_str_object("!="); }
    | LE { $$ = kx_gen_str_object("<="); }
    | '<' { $$ = kx_gen_str_object("<"); }
    | GE { $$ = kx_gen_str_object(">="); }
    | '>' { $$ = kx_gen_str_object(">"); }
    | LGE { $$ = kx_gen_str_object("<=>"); }
    | '+' { $$ = kx_gen_str_object("+"); }
    | '-' { $$ = kx_gen_str_object("-"); }
    | '*' { $$ = kx_gen_str_object("*"); }
    | '/' { $$ = kx_gen_str_object("/"); }
    | '%' { $$ = kx_gen_str_object("%"); }
    | '&' { $$ = kx_gen_str_object("&"); }
    | '|' { $$ = kx_gen_str_object("|"); }
    | '^' { $$ = kx_gen_str_object("^"); }
    | '[' ']' { $$ = kx_gen_str_object("[]"); }
    | '(' ')' { $$ = kx_gen_str_object("()"); }
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
    | DOTS3 AssignRightHandSide { $$ = kx_gen_uexpr_object(KXOP_SPREAD, $2); }
    | ArrayItemList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    | ArrayItemList ',' DOTS3 AssignRightHandSide { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_uexpr_object(KXOP_SPREAD, $4)); }
    ;

AssignExpressionList
    : AssignExpression
    | AssignExpressionList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRSEQ, $1, $3); }
    ;

AssignExpressionObjList
    : AssignExpression
    | '{' '}' { $$ = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
    | AssignExpressionObjList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRSEQ, $1, $3); }
    | AssignExpressionObjList ',' '{' '}' { $$ = kx_gen_bexpr_object(KXST_EXPRSEQ, $1, kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
    ;

KeyValueList
    : KeyValue
    | KeyValueList ',' KeyValue { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

KeyValue
    : '(' STR ')' ':' AssignExpression { $$ = kx_gen_keyvalue_object($2, $5); }
    | NAME ':' AssignExpression { $$ = kx_gen_keyvalue_object($1, $3); }
    | KeySpecialName ':' AssignExpression { $$ = kx_gen_keyvalue_object($1, $3); }
    | DOTS3 AssignRightHandSide { $$ = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, $2)); }
    ;

KeySpecialName
    : IF { $$ = "if"; }
    | ELSE { $$ = "else"; }
    | WHILE { $$ = "while"; }
    | DO { $$ = "do"; }
    | FOR { $$ = "for"; }
    | IN { $$ = "in"; }
    | TRY { $$ = "try"; }
    | CATCH { $$ = "catch"; }
    | FINALLY { $$ = "finally"; }
    | BREAK { $$ = "break"; }
    | CONTINUE { $$ = "continue"; }
    | SWITCH { $$ = "switch"; }
    | CASE { $$ = "case"; }
    | NEW { $$ = "new"; }
    | VAR { $$ = "var"; }
    | CONST { $$ = "const"; }
    | NATIVE { $$ = "native"; }
    | FUNCTION { $$ = "function"; }
    | SYSFUNC { $$ = "_function"; }
    | PUBLIC { $$ = "public"; }
    | PRIVATE { $$ = "private"; }
    | PROTECTED { $$ = "protectd"; }
    | CLASS { $$ = "class"; }
    | MODULE { $$ = "module"; }
    | RETURN { $$ = "return"; }
    | YIELD { $$ = "yield"; }
    | THROW { $$ = "throw"; }
    | NUL { $$ = "null"; }
    | TRUE { $$ = "true"; }
    | FALSE { $$ = "false"; }
    | IMPORT { $$ = "import"; }
    | USING { $$ = "using"; }
    | TYPE { $$ = kx_gen_typestr_object($1); }
    | TYPEOF { $$ = kx_gen_typeofstr_object($1); }
    | SHL { $$ = "<<"; }
    | SHR { $$ = ">>"; }
    | EQEQ { $$ = "=="; }
    | NEQ { $$ = "!="; }
    | LE { $$ = "<="; }
    | '<' { $$ = "<"; }
    | GE { $$ = ">="; }
    | '>' { $$ = ">"; }
    | LGE { $$ = "<=>"; }
    | '+' { $$ = "+"; }
    | '-' { $$ = "-"; }
    | '*' { $$ = "*"; }
    | '/' { $$ = "/"; }
    | '%' { $$ = "%"; }
    | '&' { $$ = "&"; }
    | '|' { $$ = "|"; }
    | '^' { $$ = "^"; }
    | '[' ']' { $$ = "[]"; }
    | '(' ')' { $$ = "()"; }
    ;

Regex
    : '/' RegexStart RegexString { $$ = kx_gen_regex_object($3, 0); }
    | DIVEQ RegexStart RegexString { $$ = kx_gen_regex_object($3, 1); }
    | REGPF RegexString { $$ = kx_gen_regex_object($2, 0); }
    ;

RegexStart
    : { kx_make_regex_mode('/'); }
    ;

RegexString
    : '(' STR ')' { $$ = $2; }
    ;

VarDeclStatement
    : VAR DeclAssignExpressionList ';' { $$ = $2; }
    | CONST DeclAssignExpressionList ';' { $$ = kx_add_const($2); }
    ;

DeclAssignExpressionList
    : DeclAssignExpression
    | DeclAssignExpressionList ',' DeclAssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

DeclAssignExpression
    : VarName { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($1, KX_UNKNOWN_T), NULL); }
    | VarName ':' TypeName ReturnType_Opt { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object($1, $3, $4), NULL); }
    | VarName '=' AssignRightHandSide { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($1, KX_UNKNOWN_T), $3); }
    | VarName ':' TypeName ReturnType_Opt '=' AssignRightHandSide { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object($1, $3, $4), $6); }
    | '[' ArrayItemList Comma_Opt ']' '=' AssignRightHandSide { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, $2), $6); }
    ;

FunctionDeclStatement
    : NormalFunctionDeclStatement { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    | ClassFunctionDeclStatement { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    ;

NormalFunctionDeclStatement
    : FUNCTION NAME '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $2, $4, $6, NULL); }
    | SYSFUNC NAME '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, $2, $4, $6, NULL); }
    | NativeKeyword NativeType_Opt NAME '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_NATIVE, $2, $3, $5, $7, NULL); }
    ;

NativeKeyword
    : NATIVE { kx_make_native_mode(); }
    ;

NativeType_Opt
    : { $$ = KX_INT_T; }
    | '<' TypeName '>' { $$ = $2; }
    ;

AnonymousFunctionDeclExpression
    : FUNCTION '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, $3, $5, NULL); }
    | SYSFUNC '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, $3, $5, NULL); }
    | COROUTINE '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_COROUTINE, KXFT_SYSFUNC, NULL, $3, $5, NULL); }
    | NativeKeyword NativeType_Opt '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_NATIVE, $2, NULL, $4, $6, NULL); }
    | '&' '(' ArgumentList_Opts ')' DARROW TernaryExpression { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, $3, kx_gen_stmt_object(KXST_RET, $6, NULL, NULL), NULL); }
    | '&' '(' ArgumentList_Opts ')' DARROW BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, $3, $6, NULL); }
    | '&' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, $2, NULL); }
    ;

ClassFunctionDeclStatement
    : PUBLIC ClassFunctionName '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, $2, $4, $6, NULL); }
    | PRIVATE ClassFunctionName '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, $2, $4, $6, NULL); }
    | PROTECTED ClassFunctionName '(' ArgumentList_Opts ')' BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, $2, $4, $6, NULL); }
    ;

ClassFunctionName
    : NAME
    | KeySpecialName
    ;

ClassDeclStatement
    : CLASS NAME ClassArgumentList_Opts Inherit_Opt BlockStatement { $$ = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, $2, $3, $5, $4); }
    | SYSCLASS NAME ClassArgumentList_Opts Inherit_Opt BlockStatement { $$ = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, $2, $3, $5, $4); }
    ;

ModuleDeclStatement
    : MODULE NAME BlockStatement { $$ = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, $2, NULL, $3, NULL); }
    | SYSMODULE NAME BlockStatement { $$ = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, $2, NULL, $3, NULL); }
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
    : VarName { $$ = kx_gen_var_object($1, KX_UNKNOWN_T); }
    | VarName ':' TypeName ReturnType_Opt { $$ = kx_gen_var_type_object($1, $3, $4); }
    | DOTS3 VarName { $$ = kx_gen_var_object($2, KX_SPR_T); }
    ;

TypeName
    : TYPE  { $$ = $1; }
    | NATIVE { $$ = KX_NFNC_T; }
    ;

ReturnType_Opt
    : { $$ = KX_UNKNOWN_T; }
    | '(' TypeName ')' { $$ = $2; }
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
    : CallArgument
    | DOTS3 AssignRightHandSide { $$ = kx_gen_uexpr_object(KXOP_SPREAD, $2); }
    | CallArgumentList ',' CallArgument { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $3, $1); }
    | CallArgumentList ',' DOTS3 AssignRightHandSide { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, $4), $1); }
    ;

CallArgument
    : AssignExpression
    | ObjectSpecialSyntax
    | STR { $$ = kx_gen_str_object($1); }
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
