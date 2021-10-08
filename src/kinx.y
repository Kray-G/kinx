%{
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

%}

%union {
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

%token ERROR
%token IF ELSE WHILE DO FOR IN TRY CATCH FINALLY BREAK CONTINUE SWITCH CASE DEFAULT WHEN OTHERWISE ENUM FALLTHROUGH
%token NEW VAR CONST RETURN THROW YIELD MIXIN
%token EQEQ NEQ LE GE LGE LOR LAND INC DEC SHL SHR POW LUNDEF PIPEOPL2R PIPEOPR2L FCOMPOSL2R FCOMPOSR2L
%token ADDEQ SUBEQ MULEQ DIVEQ MODEQ ANDEQ OREQ XOREQ LANDEQ LOREQ LUNDEFEQ SHLEQ SHREQ REGEQ REGNE
%token NUL TRUE FALSE AS
%token IMPORT USING DARROW SQ DQ MLSTR BINEND DOTS2 DOTS3 REGPF NAMESPACE SYSNS SYSRET_NV
%token<intval> CLASS SYSCLASS MODULE SYSMODULE NATIVE FUNCTION SYSFUNC PUBLIC PRIVATE PROTECTED COROUTINE
%token<strinfo> NAME
%token<strval> STR
%token<strval> SRCFILE
%token<strval> BIGINT
%token<intval> INT
%token<intval> TYPE
%token<intval> TYPEOF
%token<intval> LBBR RBBR
%token<intval> LMBR RMBR
%token<dblval> DBL
%token<binval> BIN

%type<obj> Program
%type<obj> ToplevelStatementList
%type<obj> StatementList
%type<obj> Statement
%type<obj> SemicolonStatement
%type<obj> NonSemicolonStatement
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
%type<obj> CatchVariable
%type<obj> FinallyStatement_Opt
%type<obj> ReturnStatement
%type<obj> YieldStatement
%type<obj> YieldExpression
%type<obj> ThrowStatement
%type<obj> MixinStatement
%type<obj> MixinModuleList
%type<obj> ExpressionStatement
%type<obj> Modifier_Opt
%type<obj> Modifier
%type<obj> BreakStatement
%type<obj> LabelStatement
%type<obj> LabelledStatement
%type<obj> AssignExpression_Opt
%type<obj> AssignExpression
%type<obj> AssignRightHandSide
%type<obj> ObjectSpecialSyntax
%type<obj> AssignExpressionList_Opt
%type<obj> TernaryExpression
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
%type<obj> CastExpression
%type<obj> PostfixExpression
%type<obj> PropertyName
%type<incdec> PostIncDec
%type<obj> Factor
%type<obj> Binary
%type<obj> Array
%type<obj> Object
%type<obj> Regex
%type<strval> RegexString
%type<obj> ArrayItemList
%type<obj> ArrayItemListCore
%type<obj> CommaList
%type<obj> AssignExpressionList
%type<obj> AssignExpressionObjList
%type<obj> KeyValueList
%type<obj> KeyValue
%type<obj> ValueOfKeyValue
%type<obj> VarName
%type<strval> KeySpecialName
%type<strval> ClassFunctionName
%type<strval> ClassFunctionSpecialName
%type<obj> VarDeclStatement
%type<obj> DeclAssignExpressionList
%type<obj> DeclAssignExpression
%type<obj> DeclAssignRightHandSide
%type<intval> NativeKeyword
%type<obj> FunctionDeclStatement
%type<obj> NormalFunctionDeclStatement
%type<obj> AnonymousFunctionDeclExpression
%type<obj> ClassFunctionDeclStatement
%type<obj> ClassDeclStatement
%type<obj> ModuleDeclStatement
%type<namedstmt> Inherit_Opt
%type<obj> InheritFactor
%type<obj> ClassArgumentList_Opts
%type<obj> ClassCallArgumentList_Opts
%type<obj> ArgumentList_Opts
%type<obj> ArgumentList
%type<obj> Argument
%type<obj> SimpleFuncCallFactorOrBlock
%type<obj> SimpleFuncCallFactor
%type<obj> CallArgumentList_Opts
%type<obj> CallArgumentList
%type<obj> CallArgument
%type<arraytype> FunctionType_Opt
%type<arraytype> NativeType_Opt
%type<arraytype> TypeName
%type<intval> ArrayLevel
%type<intval> ReturnType_Opt
%type<intval> GetLineNumber
%type<obj> PipelineExpression
%type<obj> FunctionCompositionExpression
%type<obj> CaseWhenExpression
%type<obj> WhenClauseList
%type<obj> WhenClause
%type<obj> WhenConditionRangeList
%type<obj> WhenConditionRange
%type<obj> WhenPostfixExpression
%type<obj> WhenAnonymousFunctionDeclExpression
%type<obj> WhenCondition
%type<obj> CaseElseClause
%type<obj> WhenClauseBody
%type<obj> WhenClauseBodyBlock

%%

Program
    : ToplevelStatementList { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, $1, kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
    ;

ToplevelStatementList
    : Statement
    | ToplevelStatementList Statement { kx_ast_root = $$ = ($2 == NULL ? $1 : kx_gen_stmtlist($1, $2)); }
    ;

StatementList
    : Statement
    | StatementList Statement { $$ = ($2 == NULL ? $1 : kx_gen_stmtlist($1, $2)); }
    ;

Statement
    : NonSemicolonStatement
    | SemicolonStatement
    ;

NonSemicolonStatement
    : BlockStatement
    | NamespaceStatement
    | EnumStatement
    | IfStatement
    | TryCatchStatement
    | LabelStatement
    | LabelledStatement
    | IMPORT VAR NAME '=' STR ';' { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object($3.name, KX_UNKNOWN_T), kx_gen_import_object($5)); }
    | error RBBR { yyerrok; $$ = NULL; }
    ;

SemicolonStatement
    : ReturnStatement
    | YieldStatement
    | ThrowStatement
    | MixinStatement
    | ExpressionStatement
    | DefinitionStatement
    | BreakStatement
    | error ';'      {                       yyerrok; $$ = NULL; }
    | error LBBR     { yy_restart(LBBR);     yyerrok; $$ = NULL; }
    | error IF       { yy_restart(IF);       yyerrok; $$ = NULL; }
    | error DO       { yy_restart(DO);       yyerrok; $$ = NULL; }
    | error WHILE    { yy_restart(WHILE);    yyerrok; $$ = NULL; }
    | error FOR      { yy_restart(FOR);      yyerrok; $$ = NULL; }
    | error TRY      { yy_restart(TRY);      yyerrok; $$ = NULL; }
    | error SWITCH   { yy_restart(SWITCH);   yyerrok; $$ = NULL; }
    | error CASE     { yy_restart(CASE);     yyerrok; $$ = NULL; }
    | error ENUM     { yy_restart(ENUM);     yyerrok; $$ = NULL; }
    | error CLASS    { yy_restart(CLASS);    yyerrok; $$ = NULL; }
    | error FUNCTION { yy_restart(FUNCTION); yyerrok; $$ = NULL; }
    | error PRIVATE  { yy_restart(PRIVATE);  yyerrok; $$ = NULL; }
    | error PUBLIC   { yy_restart(PUBLIC);   yyerrok; $$ = NULL; }
    ;

LabelledStatement
    : WhileStatement
    | DoWhileStatement
    | SwitchCaseStatement
    | ForStatement
    ;

BlockStatement
    : LBBR RBBR { $$ = NULL; }
    | LBBR StatementList RBBR { $$ = kx_gen_block_object($2); }
    ;

NamespaceStatement
    : NAMESPACE NamespaceName LBBR RBBR { $$ = NULL; }
    | SYSNS NamespaceName LBBR RBBR { $$ = NULL; }
    | NAMESPACE NamespaceName LBBR StatementList RBBR { $$ = kx_gen_namespace_object(0, $2, $4); }
    | SYSNS NamespaceName LBBR StatementList RBBR { $$ = kx_gen_namespace_object(1, $2, $4); }
    ;

NamespaceName
    : NAME { $$ = kx_gen_namespace_name_object($1.name); }
    ;

EnumStatement
    : ENUM LBBR EnumList Comma_Opt RBBR { $$ = kx_gen_enum_reset($3); }
    ;

EnumList
    : NAME { $$ = kx_gen_enum_object($1.name); }
    | NAME '=' INT { $$ = kx_gen_enum_object_with($1.name, $3); }
    | NAME '=' '-' INT { $$ = kx_gen_enum_object_with($1.name, -$4); }
    | EnumList ',' NAME { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_enum_object($3.name)); }
    | EnumList ',' NAME '=' INT { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_enum_object_with($3.name, $5)); }
    | EnumList ',' NAME '=' '-' INT { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_enum_object_with($3.name, -$6)); }
    ;

DefinitionStatement
    : VarDeclStatement
    | FunctionDeclStatement
    | ClassDeclStatement
    | ModuleDeclStatement
    ;

LabelStatement
    : NAME ':' LabelledStatement { $$ = kx_gen_label_object(KXST_LABEL, $1.name, $3); } /* for backward compatible */
    | NAME ':' ':' LabelledStatement { $$ = kx_gen_label_object(KXST_LABEL, $1.name, $4); }
    | NAME ':' ':' BlockStatement { $$ = kx_gen_label_object(KXST_LABEL, $1.name, $4); }
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
    | CaseStatement
    ;

CaseStatement
    : CASE AssignExpression ':' { $$ = kx_gen_case_stmt_object(KXCS_CASE, $2); }
    | DEFAULT ':' { $$ = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
    | WHEN AssignExpression ':' { $$ = kx_gen_case_stmt_object(KXCS_WHEN, $2); }
    | ELSE ':' { $$ = kx_gen_case_stmt_object(KXCS_ELSE, NULL); }
    | OTHERWISE ':' { $$ = kx_gen_case_stmt_object(KXCS_ELSE, NULL); }
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
    | FOR '(' VarName IN AssignExpressionList ')' Statement
        { $$ = kx_gen_forin_object($3, $5, $7, 0, 0); }
    | FOR '(' VAR VarName IN AssignExpressionList ')' Statement
        { $$ = kx_gen_forin_object($4, $6, $8, 1, 0); }
    | FOR '(' ForInVariable IN AssignExpressionList ')' Statement
        { $$ = kx_gen_forin_object($3, $5, $7, 0, 1); }
    | FOR '(' VAR ForInVariable IN AssignExpressionList ')' Statement
        { $$ = kx_gen_forin_object($4, $6, $8, 1, 1); }
    ;

ForInVariable
    : Array
    | Object
    ;

TryCatchStatement
    : TRY BlockStatement CatchStatement_Opt FinallyStatement_Opt { $$ = kx_gen_try_stmt_object($2, $3, $4); }
    ;

CatchStatement_Opt
    : { $$ = NULL; }
    | CATCH CatchVariable BlockStatement { $$ = kx_gen_catch_object(KXST_CATCH, $2, $3, NULL); }
    ;

CatchVariable
    : /* empty */  { $$ = kx_gen_var_object("_e", KX_UNKNOWN_T); }
    | '(' NAME ')' { $$ = kx_gen_var_object_line_pos($2.name, KX_UNKNOWN_T, $2.line, $2.pos1, $2.pos2); }
    ;

FinallyStatement_Opt
    : { $$ = NULL; }
    | FINALLY BlockStatement { $$ = $2; }
    ;

BreakStatement
    : BREAK Modifier_Opt ';' { $$ = kx_gen_modifier($2, kx_gen_break_object(KXST_BREAK, NULL)); }
    | BREAK NAME Modifier_Opt ';' { $$ = kx_gen_modifier($3, kx_gen_break_object(KXST_BREAK, $2.name)); }
    | CONTINUE Modifier_Opt ';' { $$ = kx_gen_modifier($2, kx_gen_break_object(KXST_CONTINUE, NULL)); }
    | CONTINUE NAME Modifier_Opt ';' { $$ = kx_gen_modifier($3, kx_gen_break_object(KXST_CONTINUE, $2.name)); }
    | FALLTHROUGH ';' { $$ = kx_gen_break_object(KXST_FALLTHROUGH, NULL); }
    ;

ReturnStatement
    : RETURN GetLineNumber AssignExpressionList_Opt Modifier_Opt ';' { $$ = kx_gen_modifier($4, kx_gen_stmt_object_line(KXST_RET, $3, NULL, NULL, $2)); }
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
    : NAME { $$ = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object_line_pos($1.name, KX_OBJ_T, $1.line, $1.pos1, $1.pos2), NULL); }
    | MixinModuleList ',' NAME { $$ = kx_gen_stmt_object(KXST_MIXIN, $1, kx_gen_var_object_line_pos($3.name, KX_OBJ_T, $3.line, $3.pos1, $3.pos2), NULL); }
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
    | Modifier
    ;

Modifier
    : IF '(' AssignExpressionList ')' { $$ = kx_gen_stmt_object(KXST_IF, $3, NULL, NULL); }
    ;

AssignExpression
    : CaseWhenExpression
    | AssignExpression '=' AssignRightHandSide { $$ = kx_gen_bassign_object(KXOP_ASSIGN, $1, $3); }
    | AssignExpression SHLEQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_SHL, $1, $3); }
    | AssignExpression SHREQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_SHR, $1, $3); }
    | AssignExpression ADDEQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_ADD, $1, $3); }
    | AssignExpression SUBEQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_SUB, $1, $3); }
    | AssignExpression MULEQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_MUL, $1, $3); }
    | AssignExpression DIVEQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_DIV, $1, $3); }
    | AssignExpression MODEQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_MOD, $1, $3); }
    | AssignExpression ANDEQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_AND, $1, $3); }
    | AssignExpression OREQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_OR, $1, $3); }
    | AssignExpression XOREQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_XOR, $1, $3); }
    | AssignExpression LANDEQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_LAND, $1, $3); }
    | AssignExpression LOREQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_LOR, $1, $3); }
    | AssignExpression LUNDEFEQ AssignRightHandSide { $$ = kx_gen_bassign_expr_right_object(KXOP_LUNDEF, $1, $3); }
    ;

AssignRightHandSide
    : CaseWhenExpression
    | ObjectSpecialSyntax
    ;

ObjectSpecialSyntax
    : LBBR RBBR { $$ = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, $1); }
    | ObjectSpecialSyntax PostIncDec { $$ = kx_gen_uexpr_object($2, $1); }
    | ObjectSpecialSyntax LMBR AssignExpression RMBR { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | ObjectSpecialSyntax '.' PropertyName { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | ObjectSpecialSyntax '.' TYPEOF { $$ = kx_gen_typeof_object($1, $3); }
    | ObjectSpecialSyntax '(' CallArgumentList_Opts ')' { $$ = kx_gen_bexpr_object(KXOP_CALL, $1, $3); }
    | ObjectSpecialSyntax SimpleFuncCallFactor { $$ = kx_gen_bexpr_object(KXOP_CBBLOCK, $1, $2); }
    ;

CaseWhenExpression
    : TernaryExpression
    | CASE AssignExpression WhenClauseList CaseElseClause { $$ = kx_gen_case_expr_object($2, $3, $4); }
    ;

WhenClauseList
    : WhenClause
    | WhenClauseList WhenClause { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $2); }
    ;

WhenClause
    : WHEN WhenConditionRangeList ':' WhenClauseBody { $$ = kx_gen_case_when_object($2, $4, NULL); }
    | WHEN WhenConditionRangeList WhenClauseBodyBlock { $$ = kx_gen_case_when_object($2, $3, NULL); }
    | WHEN WhenConditionRangeList Modifier Colon_Opt WhenClauseBody { $$ = kx_gen_case_when_object($2, $5, $3); }
    ;

WhenConditionRangeList
    : WhenConditionRange
    | WhenConditionRangeList '|' WhenConditionRange { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    | WhenConditionRangeList LOR WhenConditionRange { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

WhenConditionRange
    : WhenAnonymousFunctionDeclExpression
    | WhenPostfixExpression
    | '^' WhenPostfixExpression { $2->optional = KXDC_PIN; $$ = $2; }
    | Array
    | Object
    | SimpleFuncCallFactor
    | '.' PropertyName { $$ = kx_gen_prop_func_object($2); }
    | '.' TYPEOF { $$ = kx_gen_typeprop_func_object($2); }
    | WhenPostfixExpression DOTS2 { $$ = kx_gen_range_object($1, kx_gen_special_object(KXVL_NULL), 0); }
    | WhenPostfixExpression DOTS2 WhenPostfixExpression { $$ = kx_gen_range_object($1, $3, 0); }
    | WhenPostfixExpression DOTS3 { $$ = kx_gen_range_object($1, kx_gen_special_object(KXVL_NULL), 1); }
    | WhenPostfixExpression DOTS3 WhenPostfixExpression { $$ = kx_gen_range_object($1, $3, 1); }
    ;

/* `&() => expr` style will cause conflict, then you should wrap `(` and `)` such as `(&() => expr)`. */
WhenAnonymousFunctionDeclExpression
    : FUNCTION '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, $5, NULL, $3, $6, NULL, $1); }
    | SYSFUNC '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, $5, NULL, $3, $6, NULL, $1); }
    | COROUTINE '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, $5, NULL, $3, $6, NULL, $1); }
    | NativeKeyword '(' ArgumentList_Opts ')' NativeType_Opt BlockStatement { $$ = kx_gen_func_object(KXST_NATIVE, 0, $5, NULL, $3, $6, NULL); }
    | '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $5, NULL, $3, $7, NULL); }
    | '&' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $2, NULL, NULL, $3, NULL); }
    ;

WhenPostfixExpression
    : WhenCondition
    | WhenPostfixExpression PostIncDec { $$ = kx_gen_uexpr_object($2, $1); }
    | WhenPostfixExpression LMBR AssignExpression RMBR { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | WhenPostfixExpression '.' PropertyName { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | WhenPostfixExpression '.' TYPEOF { $$ = kx_gen_typeof_object($1, $3); }
    | WhenPostfixExpression '(' CallArgumentList_Opts ')' { $$ = kx_gen_bexpr_object(KXOP_CALL, $1, $3); }
    ;

WhenCondition
    : VarName
    | '(' AssignExpression ')' { $$ = $2; }
    | INT { $$ = kx_gen_int_object($1); }
    | DBL { $$ = kx_gen_dbl_object($1); }
    | BIGINT { $$ = kx_gen_big_object($1); }
    | NUL { $$ = kx_gen_special_object(KXVL_NULL); }
    | TRUE { $$ = kx_gen_special_object(KXVL_TRUE); }
    | FALSE { $$ = kx_gen_special_object(KXVL_FALSE); }
    | '(' STR ')' { $$ = kx_gen_str_object($2); }
    | NEW Factor { $$ = kx_gen_bexpr_object(KXOP_IDX, $2, kx_gen_str_object("create")); }
    ;

CaseElseClause
    : /* empty */ { $$ = NULL; }
    | ELSE Colon_Opt WhenClauseBody { $$ = kx_gen_stmtlist($3, kx_gen_break_object(KXST_BREAK, NULL)); }
    | OTHERWISE Colon_Opt WhenClauseBody { $$ = kx_gen_stmtlist($3, kx_gen_break_object(KXST_BREAK, NULL)); }
    ;

WhenClauseBody
    : WhenClauseBodyBlock
    | TernaryExpression
    ;

WhenClauseBodyBlock
    : BlockStatement { $$ = kx_gen_bexpr_object(KXOP_CALL, kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, $1, NULL), NULL); }
    ;

Colon_Opt
    : /* empty */
    | ':'
    ;

TernaryExpression
    : AnonymousFunctionDeclExpression
    | PipelineExpression
    | PipelineExpression '?' TernaryExpression ':' TernaryExpression { $$ = kx_gen_texpr_object($1, $3, $5); }
    ;

PipelineExpression
    : FunctionCompositionExpression
    | PipelineExpression PIPEOPL2R FunctionCompositionExpression { $$ = kx_gen_bexpr_object(KXOP_CALLPL, $3, $1); }
    | PipelineExpression PIPEOPR2L FunctionCompositionExpression { $$ = kx_gen_expr_right_object(KXOP_CALLPR, KXOP_CALLPR, $1, $3); }
    ;

FunctionCompositionExpression
    : LogicalUndefExpression
    | FunctionCompositionExpression FCOMPOSL2R LogicalUndefExpression { $$ = kx_gen_bexpr_object(KXOP_COMPOSITL, $1, $3); }
    | FunctionCompositionExpression FCOMPOSR2L LogicalUndefExpression { $$ = kx_gen_expr_right_object(KXOP_COMPOSITR, KXOP_COMPOSITR, $1, $3); }
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
    : CastExpression
    | '~' PrefixExpression { $$ = kx_gen_uexpr_object(KXOP_BNOT, $2); }
    | '!' PrefixExpression { $$ = kx_gen_uexpr_object(KXOP_NOT, $2); }
    | '+' PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_POSITIVE, $2); }
    | '-' PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_NEGATIVE, $2); }
    | '*' PrefixExpression { $$ = kx_gen_uexpr_object(KXOP_CONV, $2); }
    | INC PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_INC, $2); }
    | DEC PostfixExpression { $$ = kx_gen_uexpr_object(KXOP_DEC, $2); }
    ;

CastExpression
    : PostfixExpression
    | PostfixExpression AS TypeName { $$ = kx_gen_cast_object($1, KX_UNKNOWN_T, $3); }
    ;

PostfixExpression
    : Factor
    | PostfixExpression PostIncDec { $$ = kx_gen_uexpr_object($2, $1); }
    | PostfixExpression LMBR AssignExpression RMBR { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | PostfixExpression '.' PropertyName { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | PostfixExpression '.' TYPEOF { $$ = kx_gen_typeof_object($1, $3); }
    | PostfixExpression '(' CallArgumentList_Opts ')' { $$ = kx_gen_bexpr_object(KXOP_CALL, $1, $3); }
    | PostfixExpression SimpleFuncCallFactorOrBlock { $$ = kx_gen_bexpr_object(KXOP_CBBLOCK, $1, $2); }
    ;

SimpleFuncCallFactorOrBlock
    : BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, $1, NULL); }
    | SimpleFuncCallFactor
    ;

SimpleFuncCallFactor
    : LBBR FunctionType_Opt DARROW AssignExpression RBBR { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $2, NULL, NULL, kx_gen_stmt_object(KXST_RET, $4, NULL, NULL), NULL); }
    | LBBR '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW AssignExpression RBBR { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $6, NULL, $4, kx_gen_stmt_object(KXST_RET, $8, NULL, NULL), NULL); }
    | LBBR '&' '(' ArgumentList_Opts ')' FunctionType_Opt StatementList RBBR { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $6, NULL, $4, $7, NULL); }
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
    | TRUE { $$ = kx_gen_special_object(KXVL_TRUE); }
    | FALSE { $$ = kx_gen_special_object(KXVL_FALSE); }
    | SRCFILE { $$ = kx_gen_str_object($1); }
    | VarName
    | Binary
    | Array
    | Object
    | Regex
    | SimpleFuncCallFactor
    | IMPORT '(' '(' STR ')' ')' { $$ = kx_gen_import_object($4); }
    | '(' AssignExpression ')' { $$ = $2; }
    | '(' ObjectSpecialSyntax ')' { $$ = $2; }
    | '(' STR ')' { $$ = kx_gen_str_object($2); }
    | NEW Factor { $$ = kx_gen_bexpr_object(KXOP_IDX, $2, kx_gen_str_object("create")); }
    | '.' PropertyName { $$ = kx_gen_prop_func_object($2); }
    | '.' TYPEOF { $$ = kx_gen_typeprop_func_object($2); }
    | '@' PropertyName { $$ = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), $2); }
    | '@' TYPEOF { $$ = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), $2); }
    ;

VarName
    : NAME { $$ = kx_gen_var_object_line_pos($1.name, KX_UNKNOWN_T, $1.line, $1.pos1, $1.pos2); }
    | TYPE { $$ = kx_gen_var_object(kx_gen_typestr_object($1), KX_UNKNOWN_T); }
    ;

PropertyName
    : NAME { $$ = kx_gen_str_object_pos($1); }
    | TYPE { $$ = kx_gen_str_object(kx_gen_typestr_object($1)); }
    | IF { $$ = kx_gen_str_object("if"); }
    | ELSE { $$ = kx_gen_str_object("else"); }
    | OTHERWISE { $$ = kx_gen_str_object("otherwise"); }
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
    | WHEN { $$ = kx_gen_str_object("when"); }
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
    | PIPEOPL2R { $$ = kx_gen_str_object("|>"); }
    | POW { $$ = kx_gen_str_object("**"); }
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
    | LMBR RMBR { $$ = kx_gen_str_object("[]"); }
    | '(' ')' { $$ = kx_gen_str_object("()"); }
    ;

Array
    : LMBR RMBR { $$ = kx_gen_uexpr_object_line(KXOP_MKARY, NULL, $1); }
    | LMBR ArrayItemList RMBR { $$ = kx_gen_uexpr_object_line(KXOP_MKARY, $2, $1); }
    ;

Binary
    : '<' '>' { $$ = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
    | '<' BinStart ArrayItemList BINEND { $$ = kx_gen_uexpr_object(KXOP_MKBIN, $3); }
    ;

BinStart
    : { kx_make_bin_mode(); }
    ;

Object
    : LBBR KeyValueList Comma_Opt RBBR { $$ = kx_gen_uexpr_object_line(KXOP_MKOBJ, $2, $1); }
    ;

Comma_Opt
    : {}
    | ','
    ;

ArrayItemList
    : ArrayItemListCore { $$ = kx_gen_adjust_array($1); }
    | CommaList ArrayItemListCore { $$ = kx_gen_adjust_array(kx_gen_bexpr_object(KXST_EXPRLIST, $1, $2)); }
    ;

CommaList
    : ',' { $$ = kx_gen_var_object(NULL, KX_UND_T); }
    | CommaList ',' { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_var_object(NULL, KX_UND_T)); }
    ;

ArrayItemListCore
    : AssignExpression
    | '^' AssignExpression { $2->optional = KXDC_PIN; $$ = $2; }
    | DOTS3 AssignRightHandSide { $$ = kx_gen_uexpr_object(KXOP_SPREAD, $2); }
    | ArrayItemListCore ',' { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_var_object(NULL, KX_UND_T)); }
    | ArrayItemListCore ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    | ArrayItemListCore ',' '^' AssignExpression { $4->optional = KXDC_PIN; $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $4); }
    | ArrayItemListCore ',' DOTS3 AssignRightHandSide { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, kx_gen_uexpr_object(KXOP_SPREAD, $4)); }
    ;

AssignExpressionList
    : AssignExpression
    | AssignExpressionList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRSEQ, $1, $3); }
    ;

AssignExpressionObjList
    : AssignExpression
    | LBBR RBBR { $$ = kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, $1); }
    | AssignExpressionObjList ',' AssignExpression { $$ = kx_gen_bexpr_object(KXST_EXPRSEQ, $1, $3); }
    | AssignExpressionObjList ',' LBBR RBBR { $$ = kx_gen_bexpr_object(KXST_EXPRSEQ, $1, kx_gen_uexpr_object_line(KXOP_MKOBJ, NULL, $3)); }
    ;

KeyValueList
    : KeyValue
    | KeyValueList ',' KeyValue { $$ = kx_gen_exprlist($1, $3); }
    ;

KeyValue
    : '(' STR ')' ':' ValueOfKeyValue { $$ = kx_gen_keyvalue_object($2, $5); }
    | NAME ':' ValueOfKeyValue { $$ = kx_gen_keyvalue_object($1.name, $3); }
    | KeySpecialName ':' ValueOfKeyValue { $$ = kx_gen_keyvalue_object($1, $3); }
    | DOTS3 AssignRightHandSide { $$ = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, $2)); }
    | CastExpression { $$ = kx_gen_keyvalue_shorthand($1); }
    ;

ValueOfKeyValue
    : AssignExpression
    | '^' AssignExpression { $2->optional = KXDC_PIN; $$ = $2; }
    | ObjectSpecialSyntax
    ;

KeySpecialName
    : IF { $$ = "if"; }
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
    | WHEN { $$ = "when"; }
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
    ;

ClassFunctionSpecialName
    : IF { $$ = "if"; }
    | ELSE { $$ = "else"; }
    | OTHERWISE { $$ = "otherwise"; }
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
    | WHEN { $$ = "when"; }
    | NEW { $$ = "new"; }
    | VAR { $$ = "var"; }
    | CONST { $$ = "const"; }
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
    | POW { $$ = "**"; }
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
    | LMBR RMBR { $$ = "[]"; }
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
    : VarName { $$ = kx_gen_bexpr_object(KXOP_DECL, $1, NULL); }
    | VarName ':' TypeName ReturnType_Opt { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object($1, $3, $4), NULL); }
    | VarName '=' DeclAssignRightHandSide { $$ = kx_gen_bexpr_object(KXOP_DECL, $1, $3); }
    | VarName ':' TypeName ReturnType_Opt '=' DeclAssignRightHandSide { $$ = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object($1, $3, $4), $6); }
    | Array '=' DeclAssignRightHandSide { $$ = kx_gen_bexpr_object(KXOP_DECL, $1, $3); }
    | Object '=' DeclAssignRightHandSide { $$ = kx_gen_bexpr_object(KXOP_DECL, $1, $3); }
    ;

DeclAssignRightHandSide
    : AssignRightHandSide
    | DeclAssignRightHandSide '=' AssignRightHandSide { $$ = kx_gen_bexpr_object(KXOP_ASSIGN, $1, $3); }
    ;

FunctionDeclStatement
    : NormalFunctionDeclStatement { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    | ClassFunctionDeclStatement { $$ = kx_gen_stmt_object(KXST_EXPR, $1, NULL, NULL); }
    ;

NormalFunctionDeclStatement
    : FUNCTION NAME '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, $6, $2.name, $4, $7, NULL, $1); }
    | SYSFUNC NAME '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, $6, $2.name, $4, $7, NULL, $1); }
    | NativeKeyword NAME '(' ArgumentList_Opts ')' NativeType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_NATIVE, 0, $6, $2.name, $4, $7, NULL, $1); }
    ;

NativeKeyword
    : NATIVE { kx_make_native_mode(); $$ = $1; }
    ;

FunctionType_Opt
    : { $$ = (arytype_t){ .type = KX_UNKNOWN_T }; }
    | ':' TypeName { $$ = $2; }
    ;

NativeType_Opt
    : { $$ = (arytype_t){ .type = KX_INT_T }; }
    | ':' TypeName { $$ = $2; }
    ;

AnonymousFunctionDeclExpression
    : FUNCTION '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_FUNCTION, KXFT_FUNCTION, $5, NULL, $3, $6, NULL, $1); }
    | SYSFUNC '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_FUNCTION, KXFT_SYSFUNC, $5, NULL, $3, $6, NULL, $1); }
    | COROUTINE '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_COROUTINE, KXFT_SYSFUNC, $5, NULL, $3, $6, NULL, $1); }
    | NativeKeyword '(' ArgumentList_Opts ')' NativeType_Opt BlockStatement { $$ = kx_gen_func_object(KXST_NATIVE, 0, $5, NULL, $3, $6, NULL); }
    | '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW AssignExpression { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $5, NULL, $3, kx_gen_stmt_object(KXST_RET, $7, NULL, NULL), NULL); }
    | '&' '(' ArgumentList_Opts ')' FunctionType_Opt DARROW BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $5, NULL, $3, $7, NULL); }
    | '&' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, $2, NULL, NULL, $3, NULL); }
    ;

ClassFunctionDeclStatement
    : PUBLIC ClassFunctionName '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PUBLIC, $6, $2, $4, $7, NULL, $1); }
    | PRIVATE ClassFunctionName '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PRIVATE, $6, $2, $4, $7, NULL, $1); }
    | PROTECTED ClassFunctionName '(' ArgumentList_Opts ')' FunctionType_Opt BlockStatement { $$ = kx_gen_func_object_line(KXST_FUNCTION, KXFT_PROTECTED, $6, $2, $4, $7, NULL, $1); }
    ;

ClassFunctionName
    : NAME { $$ = $1.name; }
    | ClassFunctionSpecialName
    ;

ClassDeclStatement
    : CLASS NAME ClassArgumentList_Opts Inherit_Opt BlockStatement { $$ = kx_gen_func_object_name_line(KXST_CLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, $2.name, $3, $5, $4, $1); }
    | SYSCLASS NAME ClassArgumentList_Opts Inherit_Opt BlockStatement { $$ = kx_gen_func_object_name_line(KXST_SYSCLASS, KXFT_CLASS, (arytype_t){ .type = KX_UNKNOWN_T }, $2.name, $3, $5, $4, $1); }
    ;

ModuleDeclStatement
    : MODULE NAME BlockStatement { $$ = kx_gen_func_object_line(KXST_CLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, $2.name, NULL, $3, NULL, $1); }
    | SYSMODULE NAME BlockStatement { $$ = kx_gen_func_object_line(KXST_SYSCLASS, KXFT_MODULE, (arytype_t){ .type = KX_UNKNOWN_T }, $2.name, NULL, $3, NULL, $1); }
    ;

Inherit_Opt
    : { $$ = (named_stmt_t){ .name = NULL, .stmt = NULL }; }
    | ':' GetLineNumber InheritFactor ClassCallArgumentList_Opts
        {
            $$ = (named_stmt_t){
                .name = kx_check_the_name($3),
                .stmt =
                    kx_gen_bexpr_object(KXST_STMTLIST,
                        kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object_line("this", KX_OBJ_T, $2),
                            kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, $3, kx_gen_str_object("create")), $4)),
                        kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object_line("super", KX_OBJ_T, $2),
                            kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
                    ),
            };
        }
    ;

InheritFactor
    : Factor
    | InheritFactor LMBR AssignExpression RMBR { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | InheritFactor '.' PropertyName { $$ = kx_gen_bexpr_object(KXOP_IDX, $1, $3); }
    | InheritFactor '.' TYPEOF { $$ = kx_gen_typeof_object($1, $3); }
    ;

ClassArgumentList_Opts
    : { $$ = NULL; }
    | '(' ArgumentList_Opts ')' { $$ = $2; }
    ;

ArgumentList_Opts
    : { $$ = NULL; }
    | ArgumentList Comma_Opt
    ;

ArgumentList
    : Argument
    | ArgumentList ',' Argument { $$ = kx_gen_bexpr_object(KXST_EXPRLIST, $1, $3); }
    ;

Argument
    : VarName
    | VarName ':' TypeName ReturnType_Opt { $$ = kx_gen_var_type_object($1, $3, $4); }
    | Array { $$ = kx_gen_ary_var_object($1->lhs, KX_LARY_T); }
    | Object { $$ = kx_gen_ary_var_object($1->lhs, KX_LOBJ_T); }
    | DOTS3 VarName { $2->var_type = KX_SPR_T; $$ = $2; }
    ;

TypeName
    : TYPE ArrayLevel { $$ = (arytype_t){ .type = $1, .depth = $2 }; }
    | NATIVE { $$ = (arytype_t){ .type = KX_NFNC_T }; }
    | NAME ArrayLevel { $$ = (arytype_t){ .type = KX_OBJ_T, .depth = $2, .name = kx_gen_constant_string($1.name) }; }
    ;

ArrayLevel
    : /* empty */ { $$ = 0; }
    | LMBR RMBR { $$ = 1; }
    | ArrayLevel LMBR RMBR { $$ = $1 + 1; }
    ;

ReturnType_Opt
    : { $$ = KX_UNKNOWN_T; }
    | '(' TypeName ')' { $$ = $2.type; }
    ;

ClassCallArgumentList_Opts
    : { $$ = NULL; }
    | '(' CallArgumentList_Opts ')' { $$ = $2; }
    ;

CallArgumentList_Opts
    : { $$ = NULL; }
    | CallArgumentList Comma_Opt
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

GetLineNumber
    : { $$ = kx_lexinfo.line; }
    ;

%%

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
