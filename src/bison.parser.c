/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         kx_yyparse
#define yylex           kx_yylex
#define yyerror         kx_yyerror
#define yydebug         kx_yydebug
#define yynerrs         kx_yynerrs

#define yylval          kx_yylval
#define yychar          kx_yychar

/* Copy the first part of user declarations.  */
#line 1 "src/kinx.y" /* yacc.c:339  */

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


#line 89 "kx.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "kx.tab.h".  */
#ifndef YY_KX_YY_KX_TAB_H_INCLUDED
# define YY_KX_YY_KX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int kx_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ERROR = 258,
    IF = 259,
    ELSE = 260,
    WHILE = 261,
    DO = 262,
    FOR = 263,
    TRY = 264,
    CATCH = 265,
    FINALLY = 266,
    BREAK = 267,
    CONTINUE = 268,
    SWITCH = 269,
    CASE = 270,
    DEFAULT = 271,
    ENUM = 272,
    COROUTINE = 273,
    NEW = 274,
    VAR = 275,
    CONST = 276,
    NATIVE = 277,
    SYSFUNC = 278,
    FUNCTION = 279,
    PUBLIC = 280,
    PRIVATE = 281,
    PROTECTED = 282,
    CLASS = 283,
    RETURN = 284,
    THROW = 285,
    YIELD = 286,
    MODULE = 287,
    MIXIN = 288,
    SYSCLASS = 289,
    SYSMODULE = 290,
    EQEQ = 291,
    NEQ = 292,
    LE = 293,
    GE = 294,
    LGE = 295,
    LOR = 296,
    LAND = 297,
    INC = 298,
    DEC = 299,
    SHL = 300,
    SHR = 301,
    POW = 302,
    LUNDEF = 303,
    ADDEQ = 304,
    SUBEQ = 305,
    MULEQ = 306,
    DIVEQ = 307,
    MODEQ = 308,
    ANDEQ = 309,
    OREQ = 310,
    XOREQ = 311,
    LANDEQ = 312,
    LOREQ = 313,
    LUNDEFEQ = 314,
    SHLEQ = 315,
    SHREQ = 316,
    REGEQ = 317,
    REGNE = 318,
    NUL = 319,
    TRUE = 320,
    FALSE = 321,
    IMPORT = 322,
    USING = 323,
    DARROW = 324,
    SQ = 325,
    DQ = 326,
    MLSTR = 327,
    BINEND = 328,
    DOTS3 = 329,
    REGPF = 330,
    NAMESPACE = 331,
    SYSNS = 332,
    NAME = 333,
    STR = 334,
    BIGINT = 335,
    INT = 336,
    TYPE = 337,
    TYPEOF = 338,
    DBL = 339,
    BIN = 340
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "src/kinx.y" /* yacc.c:355  */

    kx_object_t   *obj;
    int           type;
    int64_t       intval;
    double        dblval;
    const char    *strval;
    const uint8_t *binval;

#line 224 "kx.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE kx_yylval;

int kx_yyparse (void);

#endif /* !YY_KX_YY_KX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 241 "kx.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  265
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3564

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  110
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  93
/* YYNRULES -- Number of rules.  */
#define YYNRULES  334
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  653

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   108,     2,     2,     2,   107,   101,     2,
      93,    94,   105,   104,    91,    90,    97,   106,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    92,    87,
     102,    86,   103,    98,   109,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    95,     2,    96,   100,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    88,    99,    89,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   133,   133,   137,   138,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   166,   167,   171,   172,
     173,   174,   178,   182,   186,   187,   188,   189,   190,   191,
     195,   196,   197,   198,   202,   206,   207,   211,   215,   219,
     223,   224,   228,   235,   242,   252,   256,   257,   261,   262,
     266,   267,   268,   269,   273,   277,   281,   285,   286,   287,
     288,   292,   296,   300,   301,   305,   309,   310,   314,   315,
     319,   320,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   342,   343,   347,
     348,   349,   350,   351,   352,   356,   357,   361,   362,   366,
     367,   371,   372,   376,   377,   381,   382,   386,   387,   391,
     392,   396,   397,   398,   402,   403,   404,   405,   406,   407,
     411,   412,   413,   417,   418,   419,   423,   424,   425,   426,
     430,   431,   435,   436,   437,   441,   442,   443,   444,   445,
     446,   447,   451,   452,   453,   454,   455,   456,   460,   461,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   486,   487,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   527,   528,   532,   533,   537,   541,   545,
     546,   550,   551,   552,   553,   557,   558,   562,   563,   564,
     565,   569,   570,   574,   575,   576,   577,   581,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     617,   618,   619,   623,   627,   631,   632,   636,   637,   641,
     642,   643,   644,   645,   649,   650,   654,   655,   656,   660,
     664,   665,   669,   670,   671,   672,   673,   674,   678,   679,
     680,   684,   685,   689,   690,   694,   695,   707,   708,   712,
     713,   717,   718,   722,   723,   724,   728,   729,   733,   734,
     738,   739,   743,   744,   748,   749,   750,   751,   755,   756,
     757,   761,   762,   763,   764
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ERROR", "IF", "ELSE", "WHILE", "DO",
  "FOR", "TRY", "CATCH", "FINALLY", "BREAK", "CONTINUE", "SWITCH", "CASE",
  "DEFAULT", "ENUM", "COROUTINE", "NEW", "VAR", "CONST", "NATIVE",
  "SYSFUNC", "FUNCTION", "PUBLIC", "PRIVATE", "PROTECTED", "CLASS",
  "RETURN", "THROW", "YIELD", "MODULE", "MIXIN", "SYSCLASS", "SYSMODULE",
  "EQEQ", "NEQ", "LE", "GE", "LGE", "LOR", "LAND", "INC", "DEC", "SHL",
  "SHR", "POW", "LUNDEF", "ADDEQ", "SUBEQ", "MULEQ", "DIVEQ", "MODEQ",
  "ANDEQ", "OREQ", "XOREQ", "LANDEQ", "LOREQ", "LUNDEFEQ", "SHLEQ",
  "SHREQ", "REGEQ", "REGNE", "NUL", "TRUE", "FALSE", "IMPORT", "USING",
  "DARROW", "SQ", "DQ", "MLSTR", "BINEND", "DOTS3", "REGPF", "NAMESPACE",
  "SYSNS", "NAME", "STR", "BIGINT", "INT", "TYPE", "TYPEOF", "DBL", "BIN",
  "'='", "';'", "'{'", "'}'", "'-'", "','", "':'", "'('", "')'", "'['",
  "']'", "'.'", "'?'", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'*'",
  "'/'", "'%'", "'!'", "'@'", "$accept", "Program", "StatementList",
  "Statement", "BlockStatement", "NamespaceStatement", "NamespaceName",
  "EnumStatement", "EnumList", "DefinitionStatement", "LabelStatement",
  "IfStatement", "WhileStatement", "DoWhileStatement",
  "SwitchCaseStatement", "CaseStatement", "ForStatement",
  "TryCatchStatement", "CatchStatement_Opt", "FinallyStatement_Opt",
  "BreakStatement", "ReturnStatement", "CoroutineStatement",
  "YieldStatement", "YieldExpression", "ThrowStatement", "MixinStatement",
  "MixinModuleList", "ExpressionStatement", "AssignExpression_Opt",
  "AssignExpressionList_Opt", "Modifier_Opt", "AssignExpression",
  "AssignRightHandSide", "ObjectSpecialSyntax", "TernaryExpression",
  "FunctionExpression", "LogicalUndefExpression", "LogicalOrExpression",
  "LogicalAndExpression", "BitOrExpression", "BitXorExpression",
  "BitAndExpression", "CompareEqualExpression", "CompareExpression",
  "ShiftExpression", "Expression", "Term", "Exponentiation", "RegexMatch",
  "PrefixExpression", "PostfixExpression", "PostIncDec", "Factor",
  "VarName", "PropertyName", "Array", "Binary", "BinStart", "Object",
  "Comma_Opt", "ArrayItemList", "AssignExpressionList",
  "AssignExpressionObjList", "KeyValueList", "KeyValue", "KeySpecialName",
  "Regex", "RegexStart", "RegexString", "VarDeclStatement",
  "DeclAssignExpressionList", "DeclAssignExpression",
  "FunctionDeclStatement", "NormalFunctionDeclStatement", "NativeKeyword",
  "NativeType_Opt", "AnonymousFunctionDeclExpression",
  "ClassFunctionDeclStatement", "ClassDeclStatement",
  "ModuleDeclStatement", "Inherit_Opt", "ClassArgumentList_Opts",
  "ArgumentList_Opts", "ArgumentList", "Argument", "TypeName",
  "ReturnType_Opt", "ClassCallArgumentList_Opts", "CallArgumentList_Opts",
  "CallArgumentList", "CallArgument", "SpreadItem", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,    61,    59,   123,   125,
      45,    44,    58,    40,    41,    91,    93,    46,    63,   124,
      94,    38,    60,    62,    43,    42,    47,    37,    33,    64
};
# endif

#define YYPACT_NINF -395

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-395)))

#define YYTABLE_NINF -269

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1607,   -23,   -15,   -10,  1607,    51,    13,    31,    33,    75,
    2611,   -22,    63,  2686,   375,   -30,   -30,  -395,   -25,   -17,
      29,    92,   100,   108,  2686,  2686,  2611,   121,   123,   128,
     135,   375,   375,  -395,  -395,  -395,  -395,    20,    89,   137,
     137,    23,  -395,  -395,  -395,  -395,   759,   375,  1998,  1682,
     -16,    17,   375,  2966,  -395,  2966,  3312,   184,   653,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,   216,  -395,  -395,  -395,
     136,   497,  -395,  -395,     4,   188,   194,   140,   142,   143,
     175,     3,   176,   -31,   112,   198,   164,  -395,    42,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,   145,  -395,
    -395,  -395,  -395,  -395,  2611,  2611,   246,  1773,   865,   243,
     161,   216,   168,   216,   170,  2611,   165,   167,   179,  -395,
    3222,  3465,   145,  -395,   183,  3072,  3478,    56,  -395,   -32,
    2073,    58,  -395,    67,   180,    64,   182,    64,   187,   189,
     204,   205,   216,   178,   216,  3478,    13,  -395,    68,   205,
      13,    42,    42,    89,   199,   207,   197,  -395,  -395,   213,
     214,  1607,   -15,  -395,   -10,   971,    51,    13,  -395,  -395,
      32,    34,    75,  2611,   375,   -30,   -30,   225,   -25,   -17,
      29,    92,   100,   108,  2148,  2223,  2298,   121,   228,   230,
     231,    20,  -395,   -33,   232,   233,  -395,  -395,  2373,  1077,
     235,  -395,   236,    42,   237,  3102,  3419,    37,   -33,  -395,
    3478,   239,    64,  -395,  -395,  2073,    42,  -395,    89,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,   240,  -395,  2761,
    2761,  2761,  2761,  2761,  2761,  2761,  2761,  2761,  2761,  2761,
    2761,  2761,  2461,  -395,  2966,  2611,  2966,  2966,  2966,  2966,
    2966,  2966,  2966,  2966,  2966,  2966,  2966,  2966,  2966,  2966,
    2966,  2966,  2966,  2966,  2966,  2966,  2966,  2966,  -395,  -395,
    1848,  2611,  3341,  -395,    22,   -11,  3478,   102,   104,   241,
     -30,  2686,    69,   242,   321,  2611,   249,  -395,   250,  -395,
     106,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,   247,  -395,
     259,  2761,  -395,   252,   254,   258,  -395,  -395,  2836,  2761,
      22,   239,  -395,   -30,  -395,    64,    91,   260,   256,   262,
    -395,    64,   257,    64,    64,    64,    64,   263,   269,   270,
    -395,  -395,   268,   263,  -395,  -395,   272,   280,   266,  1183,
    1289,  -395,  -395,  -395,  -395,  -395,  -395,  1607,   267,  -395,
    3222,   273,  2611,  -395,  -395,  -395,  1848,  -395,  2611,  3421,
    -395,  -395,  2536,   271,   274,   239,  -395,  -395,  -395,    97,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  2611,  -395,   188,   278,   194,   140,   142,
     143,   175,     3,     3,   176,   176,   176,   176,   176,   -31,
     -31,   112,   112,   198,   198,   198,   164,  -395,  -395,   -33,
    -395,  3478,    97,   277,   275,  -395,  1749,  -395,  -395,  -395,
    -395,   276,   279,    64,  2611,  1607,  1607,  2611,    94,   286,
    2686,   285,    13,  -395,   114,  -395,  -395,    13,  2611,   283,
      -6,   287,   291,  3192,  3478,  -395,   281,   288,  -395,   293,
    -395,    22,    13,    64,   294,    13,   295,   296,   297,   298,
     375,    13,  -395,  -395,  -395,    13,   302,   299,  -395,  -395,
    1395,  -395,  1501,   255,   290,  -395,  -395,  3478,   301,  3405,
    -395,  -395,   -33,  3478,  -395,   316,   323,  3478,  2611,  -395,
    -395,  1923,  -395,  -395,    64,   303,  3478,   393,  -395,   116,
    2686,  2686,   314,   310,  -395,  -395,  -395,  3478,   290,  -395,
     324,   322,  -395,  -395,    22,   328,   330,    13,   281,  -395,
    -395,    13,  -395,    13,    13,    13,  -395,   325,  -395,  -395,
     334,   315,  -395,  -395,  2611,  -395,  -395,  -395,  2911,  -395,
    -395,   -33,  -395,   329,    13,  1607,   335,   338,   337,  2686,
      13,  -395,    27,   342,  2761,  2761,  -395,  -395,  -395,  -395,
    -395,  -395,  1848,  -395,  -395,  -395,  3478,  -395,  -395,  -395,
      13,  -395,  -395,  -395,  2686,  1607,   343,  -395,  -395,   336,
    -395,  -395,  -395,   344,  -395,   349,  -395,  1607,  -395,  -395,
    1607,  -395,  -395
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    80,    80,     0,
       0,     0,     0,     0,     0,     0,     0,   289,     0,     0,
       0,     0,     0,     0,    78,    78,    68,     0,     0,     0,
       0,     0,     0,   273,   163,   165,   166,     0,     0,     0,
       0,   178,   162,   160,   179,   161,     0,     0,     0,     0,
       0,   217,     0,     0,   273,     0,     0,     0,     0,     3,
       5,     6,     7,    21,    23,     8,     9,    10,    11,    12,
      13,    14,    22,    15,    16,    17,    80,    18,    19,    20,
       0,    80,    82,   105,   108,   109,   111,   113,   115,   117,
     119,   121,   124,   130,   133,   136,   140,   142,   145,   152,
     164,   167,   168,   169,   170,    40,    41,   284,   290,   107,
     285,    42,    43,    25,     0,     0,     0,     0,     0,    56,
       0,    80,     0,    80,     0,     0,     0,     0,     0,   178,
       0,     0,   290,    51,     0,     0,   227,     0,   175,   279,
       0,     0,   277,     0,     0,   309,     0,   309,     0,     0,
       0,   307,    80,    79,    80,    67,     0,    73,     0,   307,
       0,   150,   151,     0,     0,     0,     0,   272,    32,     0,
       0,     0,   237,   238,   239,     0,   241,   242,   243,   244,
      80,    80,   247,   248,   249,   250,   251,   289,   254,   253,
     255,   256,   257,   258,    78,    78,    68,   259,   163,   165,
     166,   266,   267,     0,   178,   179,   269,    26,     0,     0,
     219,   231,     0,   148,     0,     0,     0,     0,     0,   213,
     221,   219,   309,   297,   215,     0,   147,   149,     0,   146,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   199,   198,   200,
     201,   202,   203,   205,   207,   206,   204,   208,   209,   210,
     211,   212,   180,   177,   176,     1,     4,     0,    75,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    77,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,   159,
     322,     0,     0,   153,     0,     0,   225,     0,     0,     0,
       0,    78,     0,     0,    58,     0,     0,    60,     0,    62,
       0,   237,   239,   240,   241,   242,   245,   246,   247,   248,
     249,   250,   251,   252,   254,   253,   255,   256,   257,   258,
     260,   262,   261,   259,   263,   264,   265,   266,     0,   268,
       0,     0,    50,     0,    34,   219,   228,    65,     0,     0,
       0,   219,   275,     0,   276,   309,     0,   313,     0,   310,
     311,   309,     0,   309,   309,   309,   309,   305,     0,     0,
     303,    72,     0,   305,   304,   271,     0,     0,     0,     0,
       0,    44,   331,   332,   333,   334,   236,     0,     0,    27,
     220,     0,     0,   174,    99,   172,   322,   173,     0,     0,
     100,   222,   220,     0,     0,   219,   270,    66,    86,    98,
      97,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    84,    85,    70,    83,   110,     0,   112,   114,   116,
     118,   120,   122,   123,   126,   128,   129,   125,   127,   131,
     132,   135,   134,   137,   138,   139,   141,   143,   144,     0,
     330,   328,   329,     0,   323,   324,     0,   156,   155,   317,
     316,     0,     0,   309,     0,     0,     0,     0,     0,     0,
      78,     0,     0,    55,     0,    61,    63,     0,     0,     0,
       0,   220,     0,     0,   229,   281,   318,     0,   278,     0,
     315,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,    71,    74,     0,     0,     0,   274,    28,
       0,    29,     0,   234,   174,   232,   218,   235,     0,     0,
     103,   102,     0,   223,   214,     0,     0,    69,     0,   325,
     157,     0,   154,   291,   309,     0,   226,    45,    47,     0,
      78,    78,     0,     0,    59,    81,    49,   234,     0,    35,
       0,    37,    33,   230,     0,   280,     0,     0,   318,   293,
     312,     0,   292,     0,     0,     0,   308,   320,   301,   302,
       0,     0,    30,    31,     0,   104,   101,   224,     0,   216,
     106,     0,   326,     0,     0,     0,     0,     0,     0,    78,
       0,    36,     0,     0,     0,     0,   287,   314,   286,   298,
     299,   300,   322,   306,    24,   171,   233,   296,   295,   327,
       0,   294,    46,    48,    78,     0,     0,    57,    38,     0,
     319,   282,   283,     0,   288,     0,    54,     0,    39,   321,
       0,    53,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -395,  -395,    11,     5,    -3,  -395,   388,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
     -18,    -2,     8,  -181,   -47,    14,  -395,  -395,   148,   158,
     159,   141,   156,   157,   -60,  -131,   -64,   -63,  -175,   144,
     -28,    19,  -204,   -12,  -135,  -283,  -198,  -195,  -395,  -188,
    -182,  -109,  -101,   435,  -395,    44,  -395,  -395,   398,  -114,
    -395,     1,    85,  -395,  -395,     0,   332,  -395,  -395,  -395,
    -395,    72,   307,  -119,  -395,   -53,  -344,  -117,  -395,  -394,
    -395,   -89,  -199
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    57,   209,    59,    60,    61,   169,    62,   365,    63,
      64,    65,    66,    67,    68,    69,    70,    71,   324,   493,
      72,    73,    74,    75,    76,    77,    78,   158,    79,    80,
     152,   122,    81,   444,   429,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,   313,    99,   100,   264,   101,   102,   225,   103,
     411,   221,   317,   153,   210,   211,   212,   104,   163,   167,
     105,   141,   142,   106,   107,   132,   315,   109,   110,   111,
     112,   521,   387,   378,   379,   380,   481,   575,   623,   473,
     474,   475,   406
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     108,   217,   138,   119,   108,   403,   124,   154,   404,   116,
     377,    58,   377,   420,   318,   405,   322,   143,   131,   421,
     403,   136,   538,   404,   330,   227,   506,   229,   382,   478,
     405,   371,   136,   136,   155,   120,   120,   120,   120,   423,
     164,   293,   294,   295,   479,   402,   108,   223,   139,   395,
     161,   162,   284,   144,   369,   130,   216,   220,   108,   300,
     370,   146,    49,   266,   113,   140,   213,   482,   145,    51,
     133,   226,   118,   301,   267,   569,   147,   222,   114,   283,
     308,   309,   483,   115,   570,   308,   309,   377,   428,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   118,   285,   424,   480,   296,   297,   148,   638,   121,
     121,   123,   123,   165,   426,   171,   425,   639,   108,   326,
     224,   328,   316,   316,  -245,   316,  -246,   463,   464,   465,
     416,   417,   418,   316,   419,   310,   541,   311,   376,   312,
     308,   309,   129,   367,   117,   372,    44,   368,   220,   373,
     388,   134,   389,   390,   374,   391,   490,   394,   373,   392,
     484,   217,   454,   455,   456,   457,   458,   578,   125,   129,
     149,   108,   138,    44,   119,   108,   401,   154,   150,   124,
     116,   560,   166,   502,   265,   373,   151,   143,   505,   507,
     416,   131,   418,   484,   419,   484,   485,   484,   486,   156,
     497,   157,   136,   136,   155,   484,   159,   484,   565,   108,
     606,   291,   292,   160,   266,   168,   216,   302,   303,   304,
     120,   298,   299,   268,   494,   420,   306,   307,   643,   286,
     613,   452,   453,   220,   459,   460,   287,   461,   462,   288,
     377,   510,   289,   546,   290,   305,   377,   314,   377,   377,
     377,   377,   319,   323,   325,   327,   509,   329,   145,   120,
     147,   364,   514,   472,   516,   517,   518,   519,   420,   368,
     549,   403,   165,   375,   404,   381,   398,   396,   467,   468,
     383,   405,   384,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   385,   386,   446,
     397,   399,   400,   489,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,  -252,   471,   476,
    -263,   488,  -264,  -265,   407,  -268,   410,   427,   412,   136,
     422,   413,   492,   316,   487,   491,   495,   496,   499,   498,
     500,   282,   -80,   597,   403,   483,   524,   404,   377,   501,
     512,   515,   511,   513,   405,   520,   522,   523,   526,   527,
     528,   534,   536,   563,   555,   571,   551,   544,   545,   472,
     548,   550,   554,   561,   574,   430,   504,   568,   377,   553,
     572,   590,   594,   430,   576,   598,   559,   577,   581,   583,
     584,   585,   586,   591,    14,   595,   599,   604,   605,   108,
     108,   609,   629,   403,   610,   611,   404,   108,   612,   625,
     530,   532,   401,   405,   614,   533,   615,   648,   622,   377,
     537,   624,   633,   630,   471,   634,   539,    33,   170,   449,
     543,   635,   445,   641,   642,   603,   640,   647,   649,    34,
      35,    36,   128,   650,   447,   450,   448,   451,   137,   466,
      38,   547,   228,   129,   535,    42,    43,    44,   508,    45,
     580,   617,   602,   130,   363,   525,   393,     0,    48,     0,
      49,     0,   562,     0,     0,     0,     0,    51,     0,     0,
       0,    54,     0,     0,    56,   108,   108,     0,     0,   564,
     557,   558,   556,     0,   566,   316,     0,     0,   136,     0,
       0,   120,     0,     0,   472,     0,   567,     0,   587,   579,
       0,     0,   582,     0,     0,     0,     0,     0,   588,     0,
       0,     0,   589,     0,     0,     0,     0,     0,     0,     0,
     108,   283,   108,     0,     0,   266,     0,   266,     0,     0,
       0,     0,   607,   608,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   471,
       0,     0,   600,     0,     0,     0,     0,     0,   136,   136,
       0,     0,     0,     0,   616,   472,     0,     0,   618,     0,
     619,   620,   621,   282,     0,     0,     0,     0,     0,     0,
       0,   636,     0,     0,     0,   627,     0,     0,     0,     0,
       0,   631,   626,     0,     0,   108,     0,   637,     0,     0,
     632,     0,   628,     0,     0,     0,   645,   136,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   644,   430,   430,
     471,     0,     0,     0,     0,   108,     0,     0,     0,     0,
     646,     0,   136,     0,     0,     0,     0,   108,     0,     0,
     108,     0,   651,    -2,     1,   652,     0,     2,     0,     3,
       4,     5,     6,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,     0,    42,    43,    44,     0,    45,     0,     0,
     -76,    46,     0,    47,     0,     0,    48,     0,    49,     0,
       0,     0,     0,     0,    50,    51,     0,    52,    53,    54,
       1,    55,    56,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,    11,    12,    13,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   198,   199,   200,   201,   202,     0,     0,
       0,     0,     0,   203,    38,    39,    40,   204,     0,    42,
      43,   205,   206,    45,     0,     0,   -76,    46,   207,    47,
       0,     0,   208,     0,    49,     0,     0,     0,     0,     0,
      50,    51,     0,    52,    53,    54,     1,    55,    56,     2,
       0,     3,     4,     5,     6,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,     0,    42,    43,    44,     0,    45,
       0,     0,   -76,    46,   207,    47,     0,     0,    48,     0,
      49,     0,     0,     0,     0,     0,    50,    51,     0,    52,
      53,    54,     1,    55,    56,     2,     0,     3,     4,     5,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
       0,    42,    43,    44,     0,    45,     0,     0,   -76,    46,
       0,    47,     0,  -240,    48,     0,    49,     0,     0,     0,
       0,     0,    50,    51,     0,    52,    53,    54,     1,    55,
      56,     2,     0,     3,     4,     5,     6,     0,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,     0,    42,    43,    44,
       0,    45,     0,     0,   -76,    46,   409,    47,     0,     0,
      48,     0,    49,     0,     0,     0,     0,     0,    50,    51,
       0,    52,    53,    54,     1,    55,    56,     2,     0,     3,
       4,     5,     6,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,     0,    42,    43,    44,     0,    45,     0,     0,
     -76,    46,   529,    47,     0,     0,    48,     0,    49,     0,
       0,     0,     0,     0,    50,    51,     0,    52,    53,    54,
       1,    55,    56,     2,     0,     3,     4,     5,     6,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,     0,    42,
      43,    44,     0,    45,     0,     0,   -76,    46,   531,    47,
       0,     0,    48,     0,    49,     0,     0,     0,     0,     0,
      50,    51,     0,    52,    53,    54,     1,    55,    56,     2,
       0,     3,     4,     5,     6,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,     0,    42,    43,    44,     0,    45,
       0,     0,   -76,    46,   592,    47,     0,     0,    48,     0,
      49,     0,     0,     0,     0,     0,    50,    51,     0,    52,
      53,    54,     1,    55,    56,     2,     0,     3,     4,     5,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
       0,    42,    43,    44,     0,    45,     0,     0,   -76,    46,
     593,    47,     0,     0,    48,     0,    49,     0,     0,     0,
       0,     0,    50,    51,     0,    52,    53,    54,     1,    55,
      56,     2,     0,     3,     4,     5,     6,     0,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,     0,    42,    43,    44,
       0,    45,     0,     0,   -76,    46,     0,    47,     0,     0,
      48,    14,    49,     0,    17,   126,   127,     0,    50,    51,
       0,    52,    53,    54,     0,    55,    56,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,   128,
       0,     0,     0,     0,     0,     0,   218,    38,     0,     0,
     129,     0,    42,    43,    44,     0,    45,     0,     0,     0,
     130,     0,    47,     0,     0,    48,     0,    49,   219,     0,
       0,     0,     0,    50,    51,     0,    52,    53,    54,     0,
      55,    56,    14,   320,     0,    17,   126,   127,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   361,     0,    34,    35,    36,
     128,     0,     0,     0,     0,   552,     0,     0,    38,     0,
       0,   129,     0,    42,    43,    44,     0,    45,     0,     0,
     321,   130,     0,    47,     0,     0,    48,    14,    49,     0,
      17,   126,   127,     0,    50,    51,     0,    52,    53,    54,
       0,    55,    56,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,   128,     0,     0,     0,     0,
       0,     0,   469,    38,     0,     0,   129,   470,    42,    43,
      44,     0,    45,     0,     0,     0,   215,     0,    47,     0,
       0,    48,    14,    49,     0,    17,   126,   127,     0,    50,
      51,     0,    52,    53,    54,     0,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
     128,     0,     0,     0,     0,     0,     0,   601,    38,     0,
       0,   129,   470,    42,    43,    44,     0,    45,     0,     0,
       0,   215,     0,    47,     0,     0,    48,    14,    49,     0,
      17,   126,   127,     0,    50,    51,     0,    52,    53,    54,
       0,    55,    56,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,   128,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,   129,   214,    42,    43,
      44,     0,    45,     0,     0,     0,   215,     0,    47,     0,
       0,    48,    14,    49,     0,    17,   126,   127,     0,    50,
      51,     0,    52,    53,    54,     0,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
     128,     0,     0,     0,     0,     0,     0,   218,    38,     0,
       0,   129,     0,    42,    43,    44,     0,    45,     0,     0,
       0,   130,     0,    47,     0,     0,    48,    14,    49,     0,
      17,   126,   127,     0,    50,    51,     0,    52,    53,    54,
       0,    55,    56,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,   128,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,   129,     0,    42,    43,
      44,     0,    45,     0,     0,     0,   135,     0,    47,     0,
    -260,    48,    14,    49,     0,    17,   126,   127,     0,    50,
      51,     0,    52,    53,    54,     0,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
     128,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,   129,     0,    42,    43,    44,     0,    45,     0,     0,
       0,   135,     0,    47,     0,  -262,    48,    14,    49,     0,
      17,   126,   127,     0,    50,    51,     0,    52,    53,    54,
       0,    55,    56,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,   128,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,   129,     0,    42,    43,
      44,     0,    45,     0,     0,     0,   130,     0,    47,     0,
    -261,    48,    14,    49,     0,    17,   126,   127,     0,    50,
      51,     0,    52,    53,    54,     0,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
     128,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,   129,   408,    42,    43,    44,     0,    45,     0,     0,
       0,   215,     0,    47,     0,     0,    48,     0,    49,     0,
       0,     0,     0,     0,    50,    51,     0,    52,    53,    54,
      14,    55,    56,    17,   126,   127,     0,     0,     0,     0,
       0,     0,   443,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,   128,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,   129,
       0,    42,    43,    44,     0,    45,     0,     0,     0,   215,
       0,    47,     0,     0,    48,    14,    49,     0,    17,   126,
     127,     0,    50,    51,     0,    52,    53,    54,     0,    55,
      56,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,   128,     0,     0,     0,     0,     0,     0,
     542,    38,     0,     0,   129,     0,    42,    43,    44,     0,
      45,     0,     0,     0,   130,     0,    47,     0,     0,    48,
      14,    49,     0,    17,   126,   127,     0,    50,    51,     0,
      52,    53,    54,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,   128,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,   129,
       0,    42,    43,    44,     0,    45,     0,     0,     0,   130,
       0,    47,     0,     0,    48,    14,    49,     0,    17,   126,
     127,     0,    50,    51,     0,    52,    53,    54,     0,    55,
      56,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,   128,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,   129,     0,    42,    43,    44,     0,
      45,     0,     0,     0,   135,     0,    47,     0,     0,    48,
      14,    49,     0,    17,   126,   127,     0,    50,    51,     0,
      52,    53,    54,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,   128,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,   129,
       0,    42,    43,    44,     0,    45,     0,     0,     0,   215,
       0,    47,     0,     0,    48,    14,    49,     0,    17,   126,
     127,     0,    50,    51,     0,    52,    53,    54,     0,    55,
      56,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,   128,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,   129,     0,    42,    43,    44,     0,
      45,     0,     0,     0,   503,     0,    47,     0,     0,    48,
      14,    49,     0,    17,   126,   127,     0,    50,    51,     0,
      52,    53,    54,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,   128,     0,
       0,     0,     0,     0,     0,    14,    38,     0,     0,   129,
       0,    42,    43,    44,     0,    45,     0,     0,     0,    46,
       0,    47,     0,     0,    48,     0,    49,     0,     0,    31,
      32,     0,    50,    51,     0,    52,    53,    54,    33,    55,
      56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,   128,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,   129,     0,    42,    43,    44,     0,
      45,     0,     0,     0,   130,     0,    47,     0,     0,    48,
       0,    49,     0,     0,     0,     0,     0,     0,    51,     0,
      52,    53,    54,     0,    55,    56,   331,   173,   332,   333,
     334,   335,   178,   179,   336,   337,   338,   339,     0,     0,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,     0,   331,   173,   332,   333,
     334,   335,   178,   179,   336,   337,   338,   339,     0,     0,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,     0,   354,   355,   356,   357,
     202,     0,     0,     0,     0,     0,   203,     0,     0,     0,
     358,     0,     0,     0,   359,   206,     0,     0,     0,     0,
       0,   366,     0,     0,     0,   360,   354,   355,   356,   357,
     202,     0,     0,     0,     0,     0,   203,     0,     0,     0,
     358,     0,     0,     0,   359,   206,     0,     0,     0,     0,
       0,   414,     0,     0,     0,   360,   331,   173,   332,   333,
     334,   335,   178,   179,   336,   337,   338,   339,     0,     0,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,     0,   331,   173,   332,   333,
     334,   335,   178,   179,   336,   337,   338,   339,     0,     0,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,     0,   354,   355,   356,   357,
     202,     0,     0,     0,     0,     0,   203,     0,     0,     0,
     358,     0,     0,     0,   359,   206,     0,     0,     0,     0,
       0,   573,     0,     0,     0,   360,   354,   355,   356,   357,
     202,     0,     0,     0,     0,     0,   203,     0,     0,     0,
     358,     0,     0,     0,   359,   206,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   360,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
       0,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,     0,     0,   257,   258,   259,   260,
     261,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     262,     0,     0,     0,     0,   263,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   257,   258,   259,   260,   261,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   262,
       0,     0,     0,     0,   477,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,     0,     0,     0,     0,   257,   258,   259,   260,   261,
       0,   361,     0,     0,     0,     0,     0,     0,     0,   262,
       0,   596,     0,     0,   540,   361,     0,     0,     0,     0,
       0,     0,     0,   415,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   361,     0,     0,     0,     0,     0,   362,     0,     0,
       0,     0,     0,     0,   361
};

static const yytype_int16 yycheck[] =
{
       0,    48,    14,     6,     4,   203,     8,    25,   203,     4,
     145,     0,   147,   217,   115,   203,   117,    16,    10,   218,
     218,    13,   416,   218,   125,    53,   370,    55,   147,   312,
     218,   140,    24,    25,    26,     4,     4,     4,     4,   221,
      20,    38,    39,    40,    22,    78,    46,    50,    78,   163,
      31,    32,    48,    78,    86,    88,    48,    49,    58,    90,
      92,    78,    95,    58,    87,    95,    47,    78,    93,   102,
      92,    52,    88,   104,    76,    81,    93,    93,    93,    81,
      43,    44,    93,    93,    90,    43,    44,   222,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,    88,    98,   222,    82,   102,   103,    78,    81,    78,
      78,    78,    78,    93,   228,    92,   225,    90,   118,   121,
     103,   123,   114,   115,    92,   117,    92,   302,   303,   304,
      93,    94,    95,   125,    97,    93,   419,    95,    74,    97,
      43,    44,    78,    87,    93,    87,    82,    91,   140,    91,
     152,    88,   154,   156,    87,    87,    87,   160,    91,    91,
      91,   208,   293,   294,   295,   296,   297,   511,    93,    78,
      78,   171,   184,    82,   177,   175,   171,   195,    78,   181,
     175,    87,    93,   365,     0,    91,    78,   186,   369,   371,
      93,   183,    95,    91,    97,    91,    94,    91,    94,    78,
      94,    78,   194,   195,   196,    91,    78,    91,    94,   209,
      94,    36,    37,    78,   209,    78,   208,   105,   106,   107,
       4,    45,    46,    87,   325,   429,    62,    63,   622,    41,
     574,   291,   292,   225,   298,   299,    42,   300,   301,    99,
     375,   376,   100,   425,   101,    47,   381,   102,   383,   384,
     385,   386,     6,    10,    93,    87,   375,    87,    93,     4,
      93,    78,   381,   310,   383,   384,   385,   386,   472,    91,
     469,   469,    93,    93,   469,    93,    79,    78,   306,   307,
      93,   469,    93,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,    93,    93,   285,
      93,    88,    88,   321,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    92,   310,   311,
      92,   320,    92,    92,    92,    92,    91,    87,    92,   321,
      91,    94,    11,   325,    93,    93,    87,    87,    79,    92,
      86,    86,    87,   542,   542,    93,    78,   542,   483,    91,
      94,    94,    92,    91,   542,    92,    87,    87,    86,    79,
      94,    94,    89,    78,   483,    78,    91,    96,    94,   416,
      92,    94,    93,    87,    93,   361,   368,    94,   513,   103,
      89,    79,    92,   369,    96,    69,   487,    94,    94,    94,
      94,    94,    94,    94,    19,    94,    73,    94,     5,   399,
     400,    87,   601,   601,    94,    81,   601,   407,    86,    94,
     399,   400,   407,   601,    86,   407,    86,    81,    93,   554,
     412,    87,    87,    94,   416,    87,   418,    52,    40,   288,
     422,    94,   284,   614,   615,   554,    94,    94,    94,    64,
      65,    66,    67,    94,   286,   289,   287,   290,    13,   305,
      75,   443,    54,    78,   410,    80,    81,    82,   373,    84,
     513,   578,   551,    88,   132,   393,   159,    -1,    93,    -1,
      95,    -1,   490,    -1,    -1,    -1,    -1,   102,    -1,    -1,
      -1,   106,    -1,    -1,   109,   485,   486,    -1,    -1,   492,
     485,   486,   484,    -1,   497,   487,    -1,    -1,   490,    -1,
      -1,     4,    -1,    -1,   551,    -1,   498,    -1,   520,   512,
      -1,    -1,   515,    -1,    -1,    -1,    -1,    -1,   521,    -1,
      -1,    -1,   525,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     530,   533,   532,    -1,    -1,   530,    -1,   532,    -1,    -1,
      -1,    -1,   560,   561,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,   551,
      -1,    -1,   548,    -1,    -1,    -1,    -1,    -1,   560,   561,
      -1,    -1,    -1,    -1,   577,   622,    -1,    -1,   581,    -1,
     583,   584,   585,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   609,    -1,    -1,    -1,   598,    -1,    -1,    -1,    -1,
      -1,   604,   594,    -1,    -1,   605,    -1,   610,    -1,    -1,
     605,    -1,   598,    -1,    -1,    -1,   634,   609,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   630,   614,   615,
     622,    -1,    -1,    -1,    -1,   635,    -1,    -1,    -1,    -1,
     635,    -1,   634,    -1,    -1,    -1,    -1,   647,    -1,    -1,
     650,    -1,   647,     0,     1,   650,    -1,     4,    -1,     6,
       7,     8,     9,    -1,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    -1,    80,    81,    82,    -1,    84,    -1,    -1,
      87,    88,    -1,    90,    -1,    -1,    93,    -1,    95,    -1,
      -1,    -1,    -1,    -1,   101,   102,    -1,   104,   105,   106,
       1,   108,   109,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,    80,
      81,    82,    83,    84,    -1,    -1,    87,    88,    89,    90,
      -1,    -1,    93,    -1,    95,    -1,    -1,    -1,    -1,    -1,
     101,   102,    -1,   104,   105,   106,     1,   108,   109,     4,
      -1,     6,     7,     8,     9,    -1,    -1,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    -1,    80,    81,    82,    -1,    84,
      -1,    -1,    87,    88,    89,    90,    -1,    -1,    93,    -1,
      95,    -1,    -1,    -1,    -1,    -1,   101,   102,    -1,   104,
     105,   106,     1,   108,   109,     4,    -1,     6,     7,     8,
       9,    -1,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      -1,    80,    81,    82,    -1,    84,    -1,    -1,    87,    88,
      -1,    90,    -1,    92,    93,    -1,    95,    -1,    -1,    -1,
      -1,    -1,   101,   102,    -1,   104,   105,   106,     1,   108,
     109,     4,    -1,     6,     7,     8,     9,    -1,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    -1,    80,    81,    82,
      -1,    84,    -1,    -1,    87,    88,    89,    90,    -1,    -1,
      93,    -1,    95,    -1,    -1,    -1,    -1,    -1,   101,   102,
      -1,   104,   105,   106,     1,   108,   109,     4,    -1,     6,
       7,     8,     9,    -1,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    -1,    80,    81,    82,    -1,    84,    -1,    -1,
      87,    88,    89,    90,    -1,    -1,    93,    -1,    95,    -1,
      -1,    -1,    -1,    -1,   101,   102,    -1,   104,   105,   106,
       1,   108,   109,     4,    -1,     6,     7,     8,     9,    -1,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    -1,    80,
      81,    82,    -1,    84,    -1,    -1,    87,    88,    89,    90,
      -1,    -1,    93,    -1,    95,    -1,    -1,    -1,    -1,    -1,
     101,   102,    -1,   104,   105,   106,     1,   108,   109,     4,
      -1,     6,     7,     8,     9,    -1,    -1,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    -1,    80,    81,    82,    -1,    84,
      -1,    -1,    87,    88,    89,    90,    -1,    -1,    93,    -1,
      95,    -1,    -1,    -1,    -1,    -1,   101,   102,    -1,   104,
     105,   106,     1,   108,   109,     4,    -1,     6,     7,     8,
       9,    -1,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      -1,    80,    81,    82,    -1,    84,    -1,    -1,    87,    88,
      89,    90,    -1,    -1,    93,    -1,    95,    -1,    -1,    -1,
      -1,    -1,   101,   102,    -1,   104,   105,   106,     1,   108,
     109,     4,    -1,     6,     7,     8,     9,    -1,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    -1,    80,    81,    82,
      -1,    84,    -1,    -1,    87,    88,    -1,    90,    -1,    -1,
      93,    19,    95,    -1,    22,    23,    24,    -1,   101,   102,
      -1,   104,   105,   106,    -1,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    -1,
      78,    -1,    80,    81,    82,    -1,    84,    -1,    -1,    -1,
      88,    -1,    90,    -1,    -1,    93,    -1,    95,    96,    -1,
      -1,    -1,    -1,   101,   102,    -1,   104,   105,   106,    -1,
     108,   109,    19,    20,    -1,    22,    23,    24,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    96,    -1,    -1,    75,    -1,
      -1,    78,    -1,    80,    81,    82,    -1,    84,    -1,    -1,
      87,    88,    -1,    90,    -1,    -1,    93,    19,    95,    -1,
      22,    23,    24,    -1,   101,   102,    -1,   104,   105,   106,
      -1,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    -1,    -1,    78,    79,    80,    81,
      82,    -1,    84,    -1,    -1,    -1,    88,    -1,    90,    -1,
      -1,    93,    19,    95,    -1,    22,    23,    24,    -1,   101,
     102,    -1,   104,   105,   106,    -1,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    -1,
      -1,    78,    79,    80,    81,    82,    -1,    84,    -1,    -1,
      -1,    88,    -1,    90,    -1,    -1,    93,    19,    95,    -1,
      22,    23,    24,    -1,   101,   102,    -1,   104,   105,   106,
      -1,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    78,    79,    80,    81,
      82,    -1,    84,    -1,    -1,    -1,    88,    -1,    90,    -1,
      -1,    93,    19,    95,    -1,    22,    23,    24,    -1,   101,
     102,    -1,   104,   105,   106,    -1,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    -1,
      -1,    78,    -1,    80,    81,    82,    -1,    84,    -1,    -1,
      -1,    88,    -1,    90,    -1,    -1,    93,    19,    95,    -1,
      22,    23,    24,    -1,   101,   102,    -1,   104,   105,   106,
      -1,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    78,    -1,    80,    81,
      82,    -1,    84,    -1,    -1,    -1,    88,    -1,    90,    -1,
      92,    93,    19,    95,    -1,    22,    23,    24,    -1,   101,
     102,    -1,   104,   105,   106,    -1,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    78,    -1,    80,    81,    82,    -1,    84,    -1,    -1,
      -1,    88,    -1,    90,    -1,    92,    93,    19,    95,    -1,
      22,    23,    24,    -1,   101,   102,    -1,   104,   105,   106,
      -1,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    78,    -1,    80,    81,
      82,    -1,    84,    -1,    -1,    -1,    88,    -1,    90,    -1,
      92,    93,    19,    95,    -1,    22,    23,    24,    -1,   101,
     102,    -1,   104,   105,   106,    -1,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    78,    79,    80,    81,    82,    -1,    84,    -1,    -1,
      -1,    88,    -1,    90,    -1,    -1,    93,    -1,    95,    -1,
      -1,    -1,    -1,    -1,   101,   102,    -1,   104,   105,   106,
      19,   108,   109,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    78,
      -1,    80,    81,    82,    -1,    84,    -1,    -1,    -1,    88,
      -1,    90,    -1,    -1,    93,    19,    95,    -1,    22,    23,
      24,    -1,   101,   102,    -1,   104,   105,   106,    -1,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    -1,    -1,    78,    -1,    80,    81,    82,    -1,
      84,    -1,    -1,    -1,    88,    -1,    90,    -1,    -1,    93,
      19,    95,    -1,    22,    23,    24,    -1,   101,   102,    -1,
     104,   105,   106,    -1,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    78,
      -1,    80,    81,    82,    -1,    84,    -1,    -1,    -1,    88,
      -1,    90,    -1,    -1,    93,    19,    95,    -1,    22,    23,
      24,    -1,   101,   102,    -1,   104,   105,   106,    -1,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    78,    -1,    80,    81,    82,    -1,
      84,    -1,    -1,    -1,    88,    -1,    90,    -1,    -1,    93,
      19,    95,    -1,    22,    23,    24,    -1,   101,   102,    -1,
     104,   105,   106,    -1,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    78,
      -1,    80,    81,    82,    -1,    84,    -1,    -1,    -1,    88,
      -1,    90,    -1,    -1,    93,    19,    95,    -1,    22,    23,
      24,    -1,   101,   102,    -1,   104,   105,   106,    -1,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    78,    -1,    80,    81,    82,    -1,
      84,    -1,    -1,    -1,    88,    -1,    90,    -1,    -1,    93,
      19,    95,    -1,    22,    23,    24,    -1,   101,   102,    -1,
     104,   105,   106,    -1,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    75,    -1,    -1,    78,
      -1,    80,    81,    82,    -1,    84,    -1,    -1,    -1,    88,
      -1,    90,    -1,    -1,    93,    -1,    95,    -1,    -1,    43,
      44,    -1,   101,   102,    -1,   104,   105,   106,    52,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    78,    -1,    80,    81,    82,    -1,
      84,    -1,    -1,    -1,    88,    -1,    90,    -1,    -1,    93,
      -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
     104,   105,   106,    -1,   108,   109,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    -1,    93,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    -1,    93,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    -1,    93,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    -1,    83,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    96,    -1,    -1,    83,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,
      -1,    -1,    -1,    -1,    86
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     6,     7,     8,     9,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    43,    44,    52,    64,    65,    66,    67,    75,    76,
      77,    78,    80,    81,    82,    84,    88,    90,    93,    95,
     101,   102,   104,   105,   106,   108,   109,   111,   112,   113,
     114,   115,   117,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   130,   131,   132,   133,   134,   135,   136,   138,
     139,   142,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   163,
     164,   166,   167,   169,   177,   180,   183,   184,   185,   187,
     188,   189,   190,    87,    93,    93,   113,    93,    88,   114,
       4,    78,   141,    78,   141,    93,    23,    24,    67,    78,
      88,   142,   185,    92,    88,    88,   142,   173,   163,    78,
      95,   181,   182,   181,    78,    93,    78,    93,    78,    78,
      78,    78,   140,   173,   140,   142,    78,    78,   137,    78,
      78,   161,   161,   178,    20,    93,    93,   179,    78,   116,
     116,    92,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    64,    65,
      66,    67,    68,    74,    78,    82,    83,    89,    93,   112,
     174,   175,   176,   161,    79,    88,   142,   144,    74,    96,
     142,   171,    93,   114,   103,   168,   161,   160,   178,   160,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    64,    65,    66,
      67,    68,    78,    83,   165,     0,   113,   141,    87,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    86,   141,    48,    98,    41,    42,    99,   100,
     101,    36,    37,    38,    39,    40,   102,   103,    45,    46,
      90,   104,   105,   106,   107,    47,    62,    63,    43,    44,
      93,    95,    97,   162,   102,   186,   142,   172,   172,     6,
      20,    87,   172,    10,   128,    93,   141,    87,   141,    87,
     172,     4,     6,     7,     8,     9,    12,    13,    14,    15,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    64,    65,    66,    67,    78,    82,
      93,    86,    92,   186,    78,   118,    89,    87,    91,    86,
      92,   171,    87,    91,    87,    93,    74,   164,   193,   194,
     195,    93,   193,    93,    93,    93,    93,   192,   141,   141,
     114,    87,    91,   192,   114,   179,    78,    93,    79,    88,
      88,   113,    78,   166,   167,   169,   202,    92,    79,    89,
      91,   170,    92,    94,    89,    94,    93,    94,    95,    97,
     162,   202,    91,   170,   193,   171,   179,    87,   143,   144,
     145,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,    31,   143,   148,   145,   149,   150,   151,
     152,   153,   154,   154,   155,   155,   155,   155,   155,   156,
     156,   157,   157,   158,   158,   158,   159,   160,   160,    74,
      79,   142,   144,   199,   200,   201,   142,    83,   165,    22,
      82,   196,    78,    93,    91,    94,    94,    93,   181,   140,
      87,    93,    11,   129,   172,    87,    87,    94,    92,    79,
      86,    91,   170,    88,   142,   143,   196,   170,   182,   193,
     164,    92,    94,    91,   193,    94,   193,   193,   193,   193,
      92,   191,    87,    87,    78,   191,    86,    79,    94,    89,
     112,    89,   112,   142,    94,   175,    89,   142,   199,   142,
      83,   165,    74,   142,    96,    94,   170,   142,    92,   202,
      94,    91,    96,   103,    93,   193,   142,   113,   113,   172,
      87,    87,   140,    78,   114,    94,   114,   142,    94,    81,
      90,    78,    89,    89,    93,   197,    96,    94,   196,   114,
     195,    94,   114,    94,    94,    94,    94,   163,   114,   114,
      79,    94,    89,    89,    92,    94,    96,   202,    69,    73,
     145,    74,   201,   193,    94,     5,    94,   140,   140,    87,
      94,    81,    86,   196,    86,    86,   114,   197,   114,   114,
     114,   114,    93,   198,    87,    94,   142,   114,   145,   202,
      94,   114,   113,    87,    87,    94,   140,   114,    81,    90,
      94,   143,   143,   199,   114,   140,   113,    94,    81,    94,
      94,   113,   113
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   110,   111,   112,   112,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   114,   114,   115,   115,
     115,   115,   116,   117,   118,   118,   118,   118,   118,   118,
     119,   119,   119,   119,   120,   121,   121,   122,   123,   124,
     125,   125,   126,   126,   126,   127,   128,   128,   129,   129,
     130,   130,   130,   130,   131,   132,   133,   134,   134,   134,
     134,   135,   136,   137,   137,   138,   139,   139,   140,   140,
     141,   141,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   143,   143,   144,
     144,   144,   144,   144,   144,   145,   145,   146,   146,   147,
     147,   148,   148,   149,   149,   150,   150,   151,   151,   152,
     152,   153,   153,   153,   154,   154,   154,   154,   154,   154,
     155,   155,   155,   156,   156,   156,   157,   157,   157,   157,
     158,   158,   159,   159,   159,   160,   160,   160,   160,   160,
     160,   160,   161,   161,   161,   161,   161,   161,   162,   162,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   164,   164,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   166,   166,   167,   167,   168,   169,   170,
     170,   171,   171,   171,   171,   172,   172,   173,   173,   173,
     173,   174,   174,   175,   175,   175,   175,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     177,   177,   177,   178,   179,   180,   180,   181,   181,   182,
     182,   182,   182,   182,   183,   183,   184,   184,   184,   185,
     186,   186,   187,   187,   187,   187,   187,   187,   188,   188,
     188,   189,   189,   190,   190,   191,   191,   192,   192,   193,
     193,   194,   194,   195,   195,   195,   196,   196,   197,   197,
     198,   198,   199,   199,   200,   200,   200,   200,   201,   201,
     201,   202,   202,   202,   202
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     2,     2,     3,     4,     4,
       5,     5,     1,     5,     1,     3,     4,     3,     5,     6,
       1,     1,     1,     1,     3,     5,     7,     5,     7,     5,
       3,     2,    10,     9,     8,     4,     0,     5,     0,     2,
       3,     4,     3,     4,     4,     3,     3,     2,     1,     4,
       3,     4,     3,     1,     3,     2,     0,     2,     0,     1,
       0,     4,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     2,
       2,     4,     3,     3,     4,     1,     5,     1,     1,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     3,     1,     3,     3,     1,     2,     2,     2,     2,
       2,     2,     1,     2,     4,     3,     3,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     6,     3,     3,     3,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     4,     2,     5,     0,     4,     0,
       1,     1,     2,     3,     4,     1,     3,     1,     2,     3,
       4,     1,     3,     5,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     2,     0,     3,     3,     3,     1,     3,     1,
       4,     3,     6,     6,     1,     1,     6,     6,     7,     1,
       0,     3,     5,     5,     6,     6,     6,     2,     6,     6,
       6,     5,     5,     3,     3,     0,     3,     0,     3,     0,
       1,     1,     3,     1,     4,     2,     1,     1,     0,     3,
       0,     3,     0,     1,     1,     2,     3,     4,     1,     1,
       1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 133 "src/kinx.y" /* yacc.c:1646  */
    { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[0].obj), kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
#line 2388 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 138 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2394 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 161 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2400 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 162 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2406 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 166 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2412 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 167 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2418 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 171 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2424 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 172 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2430 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 173 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2436 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 174 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2442 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 178 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2448 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 182 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2454 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 186 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2460 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 187 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2466 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 188 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2472 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 189 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2478 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 190 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2484 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 191 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2490 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 202 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2496 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 206 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2502 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 207 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2508 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 211 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2514 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 215 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2520 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 219 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2526 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 223 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2532 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 224 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2538 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 229 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2549 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 236 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2560 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 243 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2571 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 252 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2577 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 256 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2583 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 257 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2589 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 261 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2595 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 262 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2601 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 266 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2607 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 267 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2613 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 268 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2619 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 269 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2625 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 273 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2631 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 277 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_COROUTINE, (yyvsp[-1].obj), NULL, NULL); }
#line 2637 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 281 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2643 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 285 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2649 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 286 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2655 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 287 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2661 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 288 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2667 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 292 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2673 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 296 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2679 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 300 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2685 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 301 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2691 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 305 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2697 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 309 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2703 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 310 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2709 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 314 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2715 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 319 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2721 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 320 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2727 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 325 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2733 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 326 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2739 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 327 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2745 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 328 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2751 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 329 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2757 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 330 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2763 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 331 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2769 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 332 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2775 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 333 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2781 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 334 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2787 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 335 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2793 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 336 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2799 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 337 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2805 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 338 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2811 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 347 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2817 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 348 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2823 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 349 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2829 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 350 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2835 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 351 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2841 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 352 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2847 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 357 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2853 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 367 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2859 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 372 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2865 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 377 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2871 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 382 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2877 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 387 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2883 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 392 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2889 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 397 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2895 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 398 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2901 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 403 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2907 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 404 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2913 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 405 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2919 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 406 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2925 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 407 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2931 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 412 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2937 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 413 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2943 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 418 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2949 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 419 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2955 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 424 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2961 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 425 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2967 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 426 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2973 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 431 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2979 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 436 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2985 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 437 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2991 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 442 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 2997 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 443 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 3003 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 444 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 3009 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 445 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 3015 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 446 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 3021 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 447 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 3027 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 452 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 3033 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 453 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3039 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 454 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3045 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 455 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3051 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 456 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3057 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 460 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3063 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 461 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3069 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 465 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3075 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 466 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3081 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 467 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3087 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 468 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3093 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 469 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3099 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 470 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3105 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 471 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3111 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 476 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3117 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 477 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3123 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 478 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3129 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 479 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3135 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 480 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3141 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 481 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3147 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 482 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3153 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3159 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3165 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 491 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3171 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 492 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3177 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 493 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3183 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 494 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3189 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3195 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3201 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3207 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3213 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 499 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3219 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 500 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3225 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 501 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3231 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 502 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3237 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3243 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 504 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3249 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 505 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3255 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 506 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3261 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 507 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3267 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3273 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3279 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 510 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3285 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 511 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3291 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 512 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3297 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 513 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3303 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3309 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 515 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3315 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 516 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3321 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 517 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("yield"); }
#line 3327 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 518 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3333 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 519 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3339 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3345 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 521 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3351 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 522 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3357 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 523 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3363 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 527 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3369 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 528 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3375 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 532 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3381 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 533 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3387 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 537 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3393 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 541 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3399 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3405 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 551 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3411 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 552 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3417 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 553 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3423 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 558 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3429 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 563 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3435 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 564 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3441 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 565 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3447 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 570 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3453 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 574 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3459 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 575 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3465 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 576 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3471 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 577 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3477 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 581 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3483 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 582 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3489 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 583 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3495 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 584 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3501 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 585 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3507 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 586 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3513 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 587 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3519 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 588 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3525 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 589 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3531 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 590 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3537 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 591 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3543 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 592 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3549 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 593 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3555 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 594 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3561 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 595 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3567 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 596 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3573 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 597 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3579 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 598 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3585 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 599 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3591 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 600 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3597 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 601 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3603 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 602 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3609 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 603 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3615 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 604 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3621 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 605 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3627 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 606 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3633 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 607 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3639 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 608 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3645 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3651 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 610 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3657 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 611 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3663 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 612 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3669 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 613 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3675 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 617 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3681 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 618 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 3687 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 619 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3693 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 623 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 3699 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 627 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 3705 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 631 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3711 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 632 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 3717 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 637 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3723 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 3729 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 3735 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 643 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3741 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 3747 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 3753 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 649 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3759 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3765 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 654 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3771 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3777 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3783 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 660 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 3789 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 664 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 3795 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 665 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3801 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 669 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3807 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3813 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 671 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3819 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 672 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 3825 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 673 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 3831 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 674 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 3837 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 678 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3843 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 679 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3849 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 680 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3855 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 684 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3861 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 685 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3867 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 689 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3873 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 690 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3879 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 694 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3885 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 696 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 3898 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 707 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3904 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 708 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3910 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 712 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3916 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 718 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3922 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 722 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3928 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 723 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 3934 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 724 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 3940 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 728 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 3946 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 729 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 3952 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 733 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 3958 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 734 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3964 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 738 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3970 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 739 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3976 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 743 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3982 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 749 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3988 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 750 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 3994 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 751 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 4000 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 757 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 4006 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 761 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4012 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 762 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4018 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 763 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4024 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 764 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4030 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 4034 "kx.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 767 "src/kinx.y" /* yacc.c:1906  */


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
