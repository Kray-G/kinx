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
    SYSRET_NV = 333,
    NAME = 334,
    STR = 335,
    BIGINT = 336,
    INT = 337,
    TYPE = 338,
    TYPEOF = 339,
    DBL = 340,
    BIN = 341
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

#line 225 "kx.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE kx_yylval;

int kx_yyparse (void);

#endif /* !YY_KX_YY_KX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 242 "kx.tab.c" /* yacc.c:358  */

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
#define YYFINAL  267
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3212

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  111
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  93
/* YYNRULES -- Number of rules.  */
#define YYNRULES  335
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  655

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   341

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   109,     2,     2,     2,   108,   102,     2,
      94,    95,   106,   105,    92,    91,    98,   107,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    93,    88,
     103,    87,   104,    99,   110,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    96,     2,    97,   101,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,   100,    90,     2,     2,     2,     2,
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
      85,    86
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
     266,   267,   268,   269,   273,   274,   278,   282,   286,   287,
     288,   289,   293,   297,   301,   302,   306,   310,   311,   315,
     316,   320,   321,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   343,   344,
     348,   349,   350,   351,   352,   353,   357,   358,   362,   363,
     367,   368,   372,   373,   377,   378,   382,   383,   387,   388,
     392,   393,   397,   398,   399,   403,   404,   405,   406,   407,
     408,   412,   413,   414,   418,   419,   420,   424,   425,   426,
     427,   431,   432,   436,   437,   438,   442,   443,   444,   445,
     446,   447,   448,   452,   453,   454,   455,   456,   457,   461,
     462,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   487,
     488,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   528,   529,   533,   534,   538,   542,
     546,   547,   551,   552,   553,   554,   558,   559,   563,   564,
     565,   566,   570,   571,   575,   576,   577,   578,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   618,   619,   620,   624,   628,   632,   633,   637,   638,
     642,   643,   644,   645,   646,   650,   651,   655,   656,   657,
     661,   665,   666,   670,   671,   672,   673,   674,   675,   679,
     680,   681,   685,   686,   690,   691,   695,   696,   708,   709,
     713,   714,   718,   719,   723,   724,   725,   729,   730,   734,
     735,   739,   740,   744,   745,   749,   750,   751,   752,   756,
     757,   758,   762,   763,   764,   765
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
  "SYSNS", "SYSRET_NV", "NAME", "STR", "BIGINT", "INT", "TYPE", "TYPEOF",
  "DBL", "BIN", "'='", "';'", "'{'", "'}'", "'-'", "','", "':'", "'('",
  "')'", "'['", "']'", "'.'", "'?'", "'|'", "'^'", "'&'", "'<'", "'>'",
  "'+'", "'*'", "'/'", "'%'", "'!'", "'@'", "$accept", "Program",
  "StatementList", "Statement", "BlockStatement", "NamespaceStatement",
  "NamespaceName", "EnumStatement", "EnumList", "DefinitionStatement",
  "LabelStatement", "IfStatement", "WhileStatement", "DoWhileStatement",
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
     335,   336,   337,   338,   339,   340,   341,    61,    59,   123,
     125,    45,    44,    58,    40,    41,    91,    93,    46,    63,
     124,    94,    38,    60,    62,    43,    42,    47,    37,    33,
      64
};
# endif

#define YYPACT_NINF -405

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-405)))

#define YYTABLE_NINF -270

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1618,   -46,   -45,   -34,  1618,   -22,     2,    31,    35,    -7,
    2376,    -4,     4,  2425,   369,   -29,   -29,  -405,   -17,   -11,
      56,    71,    76,    78,  2425,  2425,  2376,    83,    90,   113,
     121,   369,   369,  -405,  -405,  -405,  -405,    21,   108,   136,
     136,   125,   124,  -405,  -405,  -405,  -405,   762,   369,  1863,
    1667,   -13,   115,   369,  2621,  -405,  2621,  2972,   224,   655,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,   249,  -405,  -405,
    -405,   140,   258,  -405,  -405,    -5,   214,   226,   170,   172,
     176,   130,    14,   129,   -40,   101,   235,   123,  -405,   116,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,   181,
    -405,  -405,  -405,  -405,  -405,  2376,  2376,   280,  1716,   869,
     277,   207,   249,   215,   249,   216,  2376,   208,   212,   228,
    -405,  2881,  3080,   181,  -405,   245,  2728,  3125,    80,  -405,
      -8,  1912,    95,  -405,   103,   231,    -1,   234,    -1,   236,
     238,   240,   242,   249,   237,   249,  3125,     2,  -405,   106,
     242,     2,   116,   116,   108,   254,   243,   261,  -405,  -405,
     253,   257,  -405,  1618,   -45,  -405,   -34,   976,   -22,     2,
    -405,  -405,    32,    34,    -7,  2376,   369,   -29,   -29,   250,
     -17,   -11,    56,    71,    76,    78,  1961,  2037,  2113,    83,
     255,   260,   262,    21,  -405,   -33,   279,   281,  -405,  -405,
    2189,  1083,   246,  -405,   283,   116,   252,  2759,  3067,   127,
     -33,  -405,  3125,   259,    -1,  -405,  -405,  1912,   116,  -405,
     108,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,   266,
    -405,  2474,  2474,  2474,  2474,  2474,  2474,  2474,  2474,  2474,
    2474,  2474,  2474,  2474,  2278,  -405,  2621,  2376,  2621,  2621,
    2621,  2621,  2621,  2621,  2621,  2621,  2621,  2621,  2621,  2621,
    2621,  2621,  2621,  2621,  2621,  2621,  2621,  2621,  2621,  2621,
    -405,  -405,  1765,  2376,  3001,  -405,     9,   -10,  3125,   -21,
     134,   256,   -29,  2425,   109,   276,   362,  2376,   289,  -405,
     292,  -405,   168,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
     288,  -405,   302,  2474,  -405,   290,   296,   293,  -405,  -405,
    2523,  2474,     9,   259,  -405,   -29,  -405,    -1,     7,   294,
     291,   297,  -405,    -1,   295,    -1,    -1,    -1,    -1,   298,
     304,   305,  -405,  -405,   315,   298,  -405,  -405,   309,   317,
     311,  1190,  1297,  -405,  -405,  -405,  -405,  -405,  -405,  1618,
     312,  -405,  2881,   314,  2376,  -405,  -405,  -405,  1765,  -405,
    2376,  3082,  -405,  -405,  2327,   313,   320,   259,  -405,  -405,
    -405,   187,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
    -405,  -405,  -405,  -405,  -405,  2376,  -405,   214,   323,   226,
     170,   172,   176,   130,    14,    14,   129,   129,   129,   129,
     129,   -40,   -40,   101,   101,   235,   235,   235,   123,  -405,
    -405,   -33,  -405,  3125,   187,   324,   316,  -405,   308,  -405,
    -405,  -405,  -405,   319,   330,    -1,  2376,  1618,  1618,  2376,
     111,   341,  2425,   339,     2,  -405,   169,  -405,  -405,     2,
    2376,   335,    70,   352,   347,  2850,  3125,  -405,   344,   342,
    -405,   345,  -405,     9,     2,    -1,   348,     2,   350,   351,
     354,   360,   369,     2,  -405,  -405,  -405,     2,   367,   361,
    -405,  -405,  1404,  -405,  1511,   239,   364,  -405,  -405,  3125,
     365,   498,  -405,  -405,   -33,  3125,  -405,   390,   388,  3125,
    2376,  -405,  -405,  1814,  -405,  -405,    -1,   371,  3125,   457,
    -405,   177,  2425,  2425,   376,   372,  -405,  -405,  -405,  3125,
     364,  -405,   386,   382,  -405,  -405,     9,   383,   384,     2,
     344,  -405,  -405,     2,  -405,     2,     2,     2,  -405,   379,
    -405,  -405,   387,   385,  -405,  -405,  2376,  -405,  -405,  -405,
    2572,  -405,  -405,   -33,  -405,   389,     2,  1618,   395,   397,
     391,  2425,     2,  -405,    74,   394,  2474,  2474,  -405,  -405,
    -405,  -405,  -405,  -405,  1765,  -405,  -405,  -405,  3125,  -405,
    -405,  -405,     2,  -405,  -405,  -405,  2425,  1618,   400,  -405,
    -405,   396,  -405,  -405,  -405,   403,  -405,   404,  -405,  1618,
    -405,  -405,  1618,  -405,  -405
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    81,    81,     0,
       0,     0,     0,     0,     0,     0,     0,   290,     0,     0,
       0,     0,     0,     0,    79,    79,    69,     0,     0,     0,
       0,     0,     0,   274,   164,   166,   167,     0,     0,     0,
       0,     0,   179,   163,   161,   180,   162,     0,     0,     0,
       0,     0,   218,     0,     0,   274,     0,     0,     0,     0,
       3,     5,     6,     7,    21,    23,     8,     9,    10,    11,
      12,    13,    14,    22,    15,    16,    17,    81,    18,    19,
      20,     0,    81,    83,   106,   109,   110,   112,   114,   116,
     118,   120,   122,   125,   131,   134,   137,   141,   143,   146,
     153,   165,   168,   169,   170,   171,    40,    41,   285,   291,
     108,   286,    42,    43,    25,     0,     0,     0,     0,     0,
      56,     0,    81,     0,    81,     0,     0,     0,     0,     0,
     179,     0,     0,   291,    51,     0,     0,   228,     0,   176,
     280,     0,     0,   278,     0,     0,   310,     0,   310,     0,
       0,     0,   308,    81,    80,    81,    68,     0,    74,     0,
     308,     0,   151,   152,     0,     0,     0,     0,   273,    32,
       0,     0,    65,     0,   238,   239,   240,     0,   242,   243,
     244,   245,    81,    81,   248,   249,   250,   251,   252,   290,
     255,   254,   256,   257,   258,   259,    79,    79,    69,   260,
     164,   166,   167,   267,   268,     0,   179,   180,   270,    26,
       0,     0,   220,   232,     0,   149,     0,     0,     0,     0,
       0,   214,   222,   220,   310,   298,   216,     0,   148,   150,
       0,   147,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   200,
     199,   201,   202,   203,   204,   206,   208,   207,   205,   209,
     210,   211,   212,   213,   181,   178,   177,     1,     4,     0,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     159,   160,   323,     0,     0,   154,     0,     0,   226,     0,
       0,     0,     0,    79,     0,     0,    58,     0,     0,    60,
       0,    62,     0,   238,   240,   241,   242,   243,   246,   247,
     248,   249,   250,   251,   252,   253,   255,   254,   256,   257,
     258,   259,   261,   263,   262,   260,   264,   265,   266,   267,
       0,   269,     0,     0,    50,     0,    34,   220,   229,    66,
       0,     0,     0,   220,   276,     0,   277,   310,     0,   314,
       0,   311,   312,   310,     0,   310,   310,   310,   310,   306,
       0,     0,   304,    73,     0,   306,   305,   272,     0,     0,
       0,     0,     0,    44,   332,   333,   334,   335,   237,     0,
       0,    27,   221,     0,     0,   175,   100,   173,   323,   174,
       0,     0,   101,   223,   221,     0,     0,   220,   271,    67,
      87,    99,    98,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    85,    86,    71,    84,   111,     0,   113,
     115,   117,   119,   121,   123,   124,   127,   129,   130,   126,
     128,   132,   133,   136,   135,   138,   139,   140,   142,   144,
     145,     0,   331,   329,   330,     0,   324,   325,     0,   157,
     156,   318,   317,     0,     0,   310,     0,     0,     0,     0,
       0,     0,    79,     0,     0,    55,     0,    61,    63,     0,
       0,     0,     0,   221,     0,     0,   230,   282,   319,     0,
     279,     0,   316,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,    72,    75,     0,     0,     0,
     275,    28,     0,    29,     0,   235,   175,   233,   219,   236,
       0,     0,   104,   103,     0,   224,   215,     0,     0,    70,
       0,   326,   158,     0,   155,   292,   310,     0,   227,    45,
      47,     0,    79,    79,     0,     0,    59,    82,    49,   235,
       0,    35,     0,    37,    33,   231,     0,   281,     0,     0,
     319,   294,   313,     0,   293,     0,     0,     0,   309,   321,
     302,   303,     0,     0,    30,    31,     0,   105,   102,   225,
       0,   217,   107,     0,   327,     0,     0,     0,     0,     0,
       0,    79,     0,    36,     0,     0,     0,     0,   288,   315,
     287,   299,   300,   301,   323,   307,    24,   172,   234,   297,
     296,   328,     0,   295,    46,    48,    79,     0,     0,    57,
      38,     0,   320,   283,   284,     0,   289,     0,    54,     0,
      39,   322,     0,    53,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -405,  -405,    11,     5,    -3,  -405,   437,  -405,  -405,  -405,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
    -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,  -405,
     -18,    -2,     8,  -135,   -47,  -175,  -405,  -405,   204,   213,
     218,   219,   211,   220,   -54,  -167,   -55,   -28,   -72,   196,
     -32,    13,  -194,    -6,  -136,  -288,  -204,  -200,  -405,  -192,
    -183,  -111,   -89,   491,  -405,    93,  -405,  -405,   455,  -109,
    -405,     1,   138,  -405,  -405,     0,   392,  -405,  -405,  -405,
    -405,   120,   357,  -129,  -405,     3,  -349,   -61,  -405,  -404,
    -405,   -31,  -205
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    58,   211,    60,    61,    62,   170,    63,   367,    64,
      65,    66,    67,    68,    69,    70,    71,    72,   326,   495,
      73,    74,    75,    76,    77,    78,    79,   159,    80,    81,
     153,   123,    82,   446,   431,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   315,   100,   101,   266,   102,   103,   227,   104,
     413,   223,   319,   154,   212,   213,   214,   105,   164,   168,
     106,   142,   143,   107,   108,   133,   317,   110,   111,   112,
     113,   523,   389,   380,   381,   382,   483,   577,   625,   475,
     476,   477,   408
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     109,   405,   219,   120,   109,   406,   125,   155,   139,   117,
     379,    59,   379,   407,   540,   423,   405,   144,   132,   384,
     406,   137,   229,   508,   231,   422,   480,   320,   407,   324,
     373,   481,   137,   137,   156,   121,   121,   332,   121,   121,
     425,   165,   114,   286,   162,   163,   404,   109,   225,   115,
     140,   302,   295,   296,   297,   397,   131,   218,   222,   109,
     116,   215,   145,    50,   268,   303,   228,   141,   147,   484,
      52,   486,   118,   378,   487,   269,   119,   146,   130,   371,
     285,   224,    45,   148,   485,   372,   130,   126,   379,   134,
      45,   119,   482,   135,   287,   426,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     122,   122,   448,   124,   124,   166,   427,   298,   299,   109,
     328,   428,   330,   318,   318,  -246,   318,  -247,   456,   457,
     458,   459,   460,   543,   318,   149,   430,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   222,
     150,   390,   571,   391,   392,   151,   640,   152,   396,   310,
     311,   572,   157,   219,   580,   641,   293,   294,   369,   158,
     310,   311,   370,   109,   300,   301,   120,   109,   403,   155,
     139,   125,   117,   374,   504,   308,   309,   375,   432,   144,
     509,   376,   160,   132,   393,   375,   432,   492,   394,   562,
     161,   486,   167,   375,   137,   137,   156,   304,   305,   306,
     312,   109,   313,   172,   314,   169,   268,   173,   218,   226,
     645,   418,   419,   420,   267,   421,   486,   615,   270,   488,
     310,   311,   465,   466,   467,   222,   507,   422,   496,   454,
     455,   379,   512,   121,   548,   461,   462,   379,   511,   379,
     379,   379,   379,   121,   516,   288,   518,   519,   520,   521,
     486,   486,   121,   499,   567,   474,   551,   405,   289,   486,
     290,   406,   608,   291,   463,   464,   469,   470,   292,   407,
     422,   418,   307,   420,   316,   421,   321,   325,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   327,   146,   329,   331,   491,   148,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     473,   478,   166,   490,   366,   377,   284,   -81,   383,   370,
     385,   137,   386,   398,   387,   318,   388,   399,   412,   599,
     405,   400,   401,  -253,   406,   284,   402,   415,  -264,   379,
     489,   424,   407,  -265,   429,  -266,   557,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     493,   474,   409,   494,  -269,   602,   414,   497,   506,   379,
     498,   500,   501,   502,   485,   503,   514,   513,    14,   515,
     517,   522,   524,   525,   526,   363,   528,   529,   631,   405,
     561,   109,   109,   406,   538,   554,   530,   536,   553,   109,
     546,   407,   532,   534,   403,   547,   550,   535,   565,   552,
     379,    33,   539,   555,   556,   630,   473,   605,   541,   563,
     570,   573,   545,    34,    35,    36,   129,   574,   576,   578,
     579,   432,   432,   583,    38,   585,   586,   592,   130,   587,
      43,    44,    45,   549,    46,   588,   593,   596,   131,   600,
     597,   601,   607,    49,   611,    50,   606,   612,   613,   614,
     616,   617,    52,   624,   564,   626,    55,   171,   650,    57,
     627,   643,   644,   635,   632,   636,   637,   109,   109,   642,
     447,   566,   559,   560,   558,   649,   568,   318,   651,   652,
     137,   449,   452,   468,   138,   537,   474,   450,   569,   451,
     230,   581,   453,   510,   584,   527,   589,   395,   582,   619,
     590,     0,   604,     0,   591,   365,     0,     0,     0,     0,
       0,     0,   109,   285,   109,     0,     0,   268,     0,   268,
       0,     0,     0,     0,   609,   610,     0,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
       0,   473,     0,     0,     0,     0,     0,     0,     0,     0,
     137,   137,     0,     0,     0,     0,   618,   474,     0,     0,
     620,     0,   621,   622,   623,   363,     0,     0,     0,     0,
       0,     0,     0,   638,     0,   598,     0,   629,     0,     0,
       0,     0,     0,   633,   628,     0,     0,   109,     0,   639,
       0,     0,   634,     0,     0,     0,     0,     0,   647,   137,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   646,
       0,     0,   473,     0,     0,     0,     0,   109,     0,     0,
       0,     0,   648,     0,   137,     0,     0,     0,     0,   109,
       0,     0,   109,     0,   653,    -2,     1,   654,     0,     2,
       0,     3,     4,     5,     6,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,    42,     0,    43,    44,    45,     0,
      46,     0,     0,   -77,    47,     0,    48,     0,     0,    49,
       0,    50,     0,     0,     0,     0,     0,    51,    52,     0,
      53,    54,    55,     1,    56,    57,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,    11,    12,
      13,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,    28,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,   201,   202,   203,
     204,     0,     0,     0,     0,     0,   205,    38,    39,    40,
      41,   206,     0,    43,    44,   207,   208,    46,     0,     0,
     -77,    47,   209,    48,     0,     0,   210,     0,    50,     0,
       0,     0,     0,     0,    51,    52,     0,    53,    54,    55,
       1,    56,    57,     2,     0,     3,     4,     5,     6,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,     0,     0,   -77,    47,   209,
      48,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,     1,    56,    57,
       2,     0,     3,     4,     5,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,    38,    39,    40,    41,    42,     0,    43,    44,    45,
       0,    46,     0,     0,   -77,    47,     0,    48,     0,  -241,
      49,     0,    50,     0,     0,     0,     0,     0,    51,    52,
       0,    53,    54,    55,     1,    56,    57,     2,     0,     3,
       4,     5,     6,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    42,     0,    43,    44,    45,     0,    46,     0,
       0,   -77,    47,   411,    48,     0,     0,    49,     0,    50,
       0,     0,     0,     0,     0,    51,    52,     0,    53,    54,
      55,     1,    56,    57,     2,     0,     3,     4,     5,     6,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,    38,    39,    40,    41,    42,
       0,    43,    44,    45,     0,    46,     0,     0,   -77,    47,
     531,    48,     0,     0,    49,     0,    50,     0,     0,     0,
       0,     0,    51,    52,     0,    53,    54,    55,     1,    56,
      57,     2,     0,     3,     4,     5,     6,     0,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,    42,     0,    43,    44,
      45,     0,    46,     0,     0,   -77,    47,   533,    48,     0,
       0,    49,     0,    50,     0,     0,     0,     0,     0,    51,
      52,     0,    53,    54,    55,     1,    56,    57,     2,     0,
       3,     4,     5,     6,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,    38,
      39,    40,    41,    42,     0,    43,    44,    45,     0,    46,
       0,     0,   -77,    47,   594,    48,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,    51,    52,     0,    53,
      54,    55,     1,    56,    57,     2,     0,     3,     4,     5,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
      42,     0,    43,    44,    45,     0,    46,     0,     0,   -77,
      47,   595,    48,     0,     0,    49,     0,    50,     0,     0,
       0,     0,     0,    51,    52,     0,    53,    54,    55,     1,
      56,    57,     2,     0,     3,     4,     5,     6,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,    14,     0,     0,    17,
     127,   128,     0,    38,    39,    40,    41,    42,     0,    43,
      44,    45,     0,    46,     0,     0,   -77,    47,     0,    48,
      31,    32,    49,     0,    50,     0,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,     0,
       0,    34,    35,    36,   129,    14,   322,     0,    17,   127,
     128,   220,    38,     0,     0,     0,   130,     0,    43,    44,
      45,     0,    46,     0,     0,     0,   131,     0,    48,    31,
      32,    49,     0,    50,   221,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,    14,     0,     0,    17,   127,   128,
       0,    38,     0,     0,     0,   130,     0,    43,    44,    45,
       0,    46,     0,     0,   323,   131,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   129,    14,     0,     0,    17,   127,   128,   471,
      38,     0,     0,     0,   130,   472,    43,    44,    45,     0,
      46,     0,     0,     0,   217,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   129,    14,     0,     0,    17,   127,   128,   603,    38,
       0,     0,     0,   130,   472,    43,    44,    45,     0,    46,
       0,     0,     0,   217,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     129,    14,     0,     0,    17,   127,   128,     0,    38,     0,
       0,     0,   130,   216,    43,    44,    45,     0,    46,     0,
       0,     0,   217,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   129,
      14,     0,     0,    17,   127,   128,   220,    38,     0,     0,
       0,   130,     0,    43,    44,    45,     0,    46,     0,     0,
       0,   131,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
     130,     0,    43,    44,    45,     0,    46,     0,     0,     0,
     136,     0,    48,     0,  -261,    49,    14,    50,     0,    17,
     127,   128,     0,    51,    52,     0,    53,    54,    55,     0,
      56,    57,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,   129,     0,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,   130,     0,    43,    44,
      45,     0,    46,     0,     0,     0,   136,     0,    48,     0,
    -263,    49,    14,    50,     0,    17,   127,   128,     0,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
     129,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,   130,     0,    43,    44,    45,     0,    46,     0,
       0,     0,   131,     0,    48,     0,  -262,    49,    14,    50,
       0,    17,   127,   128,     0,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,   129,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,   130,   410,
      43,    44,    45,     0,    46,     0,     0,     0,   217,     0,
      48,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,    14,    56,    57,
      17,   127,   128,     0,     0,     0,     0,     0,     0,   445,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,   129,    14,     0,     0,    17,
     127,   128,     0,    38,     0,     0,     0,   130,     0,    43,
      44,    45,     0,    46,     0,     0,     0,   217,     0,    48,
      31,    32,    49,     0,    50,     0,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,     0,
       0,    34,    35,    36,   129,    14,     0,     0,    17,   127,
     128,   544,    38,     0,     0,     0,   130,     0,    43,    44,
      45,     0,    46,     0,     0,     0,   131,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,    14,     0,     0,    17,   127,   128,
       0,    38,     0,     0,     0,   130,     0,    43,    44,    45,
       0,    46,     0,     0,     0,   131,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   129,    14,     0,     0,    17,   127,   128,     0,
      38,     0,     0,     0,   130,     0,    43,    44,    45,     0,
      46,     0,     0,     0,   136,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   129,    14,     0,     0,    17,   127,   128,     0,    38,
       0,     0,     0,   130,     0,    43,    44,    45,     0,    46,
       0,     0,     0,   217,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     129,    14,     0,     0,    17,   127,   128,     0,    38,     0,
       0,     0,   130,     0,    43,    44,    45,     0,    46,     0,
       0,     0,   505,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   129,
      14,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,   130,     0,    43,    44,    45,     0,    46,     0,     0,
       0,    47,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
     130,     0,    43,    44,    45,     0,    46,     0,     0,     0,
     131,     0,    48,     0,     0,    49,     0,    50,     0,     0,
       0,     0,     0,     0,    52,     0,    53,    54,    55,     0,
      56,    57,   333,   175,   334,   335,   336,   337,   180,   181,
     338,   339,   340,   341,     0,     0,     0,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,     0,     0,   333,   175,   334,   335,   336,   337,   180,
     181,   338,   339,   340,   341,     0,     0,     0,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   204,     0,     0,     0,
       0,     0,   205,     0,     0,     0,     0,   360,     0,     0,
       0,   361,   208,     0,     0,     0,     0,     0,   368,     0,
       0,     0,   362,   356,   357,   358,   359,   204,     0,     0,
       0,     0,     0,   205,     0,     0,     0,     0,   360,     0,
       0,     0,   361,   208,     0,     0,     0,     0,     0,   416,
       0,     0,     0,   362,   333,   175,   334,   335,   336,   337,
     180,   181,   338,   339,   340,   341,     0,     0,     0,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,     0,     0,   333,   175,   334,   335,   336,
     337,   180,   181,   338,   339,   340,   341,     0,     0,     0,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   204,     0,
       0,     0,     0,     0,   205,     0,     0,     0,     0,   360,
       0,     0,     0,   361,   208,     0,     0,     0,     0,     0,
     575,     0,     0,     0,   362,   356,   357,   358,   359,   204,
       0,     0,     0,     0,     0,   205,     0,     0,     0,     0,
     360,     0,     0,     0,   361,   208,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   362,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,     0,
       0,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,     0,     0,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,     0,     0,   259,   260,   261,   262,
     263,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   264,     0,     0,     0,     0,   265,     0,     0,     0,
       0,     0,     0,     0,     0,   259,   260,   261,   262,   263,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     264,     0,     0,     0,     0,   479,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,     0,
       0,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,     0,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,     0,     0,     0,     0,   259,   260,   261,   262,
     263,     0,     0,     0,   363,     0,     0,     0,     0,     0,
       0,   264,   417,     0,     0,     0,   542,   363,     0,     0,
       0,     0,     0,   364,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   363
};

static const yytype_int16 yycheck[] =
{
       0,   205,    49,     6,     4,   205,     8,    25,    14,     4,
     146,     0,   148,   205,   418,   220,   220,    16,    10,   148,
     220,    13,    54,   372,    56,   219,   314,   116,   220,   118,
     141,    22,    24,    25,    26,     4,     4,   126,     4,     4,
     223,    20,    88,    48,    31,    32,    79,    47,    51,    94,
      79,    91,    38,    39,    40,   164,    89,    49,    50,    59,
      94,    48,    79,    96,    59,   105,    53,    96,    79,    79,
     103,    92,    94,    74,    95,    77,    89,    94,    79,    87,
      82,    94,    83,    94,    94,    93,    79,    94,   224,    93,
      83,    89,    83,    89,    99,   224,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      79,    79,   287,    79,    79,    94,   227,   103,   104,   119,
     122,   230,   124,   115,   116,    93,   118,    93,   295,   296,
     297,   298,   299,   421,   126,    79,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   141,
      79,   153,    82,   155,   157,    79,    82,    79,   161,    43,
      44,    91,    79,   210,   513,    91,    36,    37,    88,    79,
      43,    44,    92,   173,    45,    46,   179,   177,   173,   197,
     186,   183,   177,    88,   367,    62,    63,    92,   363,   188,
     373,    88,    79,   185,    88,    92,   371,    88,    92,    88,
      79,    92,    94,    92,   196,   197,   198,   106,   107,   108,
      94,   211,    96,    88,    98,    79,   211,    93,   210,   104,
     624,    94,    95,    96,     0,    98,    92,   576,    88,    95,
      43,    44,   304,   305,   306,   227,   371,   431,   327,   293,
     294,   377,   378,     4,   427,   300,   301,   383,   377,   385,
     386,   387,   388,     4,   383,    41,   385,   386,   387,   388,
      92,    92,     4,    95,    95,   312,   471,   471,    42,    92,
     100,   471,    95,   101,   302,   303,   308,   309,   102,   471,
     474,    94,    47,    96,   103,    98,     6,    10,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    94,    94,    88,    88,   323,    94,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
     312,   313,    94,   322,    79,    94,    87,    88,    94,    92,
      94,   323,    94,    79,    94,   327,    94,    94,    92,   544,
     544,    80,    89,    93,   544,    87,    89,    95,    93,   485,
      94,    92,   544,    93,    88,    93,   485,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      94,   418,    93,    11,    93,   550,    93,    88,   370,   515,
      88,    93,    80,    87,    94,    92,    95,    93,    19,    92,
      95,    93,    88,    88,    79,    87,    87,    80,   603,   603,
     489,   401,   402,   603,    90,    97,    95,    95,    92,   409,
      97,   603,   401,   402,   409,    95,    93,   409,    79,    95,
     556,    52,   414,   104,    94,   600,   418,   556,   420,    88,
      95,    79,   424,    64,    65,    66,    67,    90,    94,    97,
      95,   616,   617,    95,    75,    95,    95,    80,    79,    95,
      81,    82,    83,   445,    85,    95,    95,    93,    89,    69,
      95,    73,     5,    94,    88,    96,    95,    95,    82,    87,
      87,    87,   103,    94,   492,    88,   107,    40,    82,   110,
      95,   616,   617,    88,    95,    88,    95,   487,   488,    95,
     286,   494,   487,   488,   486,    95,   499,   489,    95,    95,
     492,   288,   291,   307,    13,   412,   553,   289,   500,   290,
      55,   514,   292,   375,   517,   395,   522,   160,   515,   580,
     523,    -1,   553,    -1,   527,   133,    -1,    -1,    -1,    -1,
      -1,    -1,   532,   535,   534,    -1,    -1,   532,    -1,   534,
      -1,    -1,    -1,    -1,   562,   563,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,   553,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     562,   563,    -1,    -1,    -1,    -1,   579,   624,    -1,    -1,
     583,    -1,   585,   586,   587,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   611,    -1,    97,    -1,   600,    -1,    -1,
      -1,    -1,    -1,   606,   596,    -1,    -1,   607,    -1,   612,
      -1,    -1,   607,    -1,    -1,    -1,    -1,    -1,   636,   611,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   632,
      -1,    -1,   624,    -1,    -1,    -1,    -1,   637,    -1,    -1,
      -1,    -1,   637,    -1,   636,    -1,    -1,    -1,    -1,   649,
      -1,    -1,   652,    -1,   649,     0,     1,   652,    -1,     4,
      -1,     6,     7,     8,     9,    -1,    -1,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    -1,    81,    82,    83,    -1,
      85,    -1,    -1,    88,    89,    -1,    91,    -1,    -1,    94,
      -1,    96,    -1,    -1,    -1,    -1,    -1,   102,   103,    -1,
     105,   106,   107,     1,   109,   110,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,
      78,    79,    -1,    81,    82,    83,    84,    85,    -1,    -1,
      88,    89,    90,    91,    -1,    -1,    94,    -1,    96,    -1,
      -1,    -1,    -1,    -1,   102,   103,    -1,   105,   106,   107,
       1,   109,   110,     4,    -1,     6,     7,     8,     9,    -1,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    -1,
      81,    82,    83,    -1,    85,    -1,    -1,    88,    89,    90,
      91,    -1,    -1,    94,    -1,    96,    -1,    -1,    -1,    -1,
      -1,   102,   103,    -1,   105,   106,   107,     1,   109,   110,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    -1,    81,    82,    83,
      -1,    85,    -1,    -1,    88,    89,    -1,    91,    -1,    93,
      94,    -1,    96,    -1,    -1,    -1,    -1,    -1,   102,   103,
      -1,   105,   106,   107,     1,   109,   110,     4,    -1,     6,
       7,     8,     9,    -1,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    -1,    81,    82,    83,    -1,    85,    -1,
      -1,    88,    89,    90,    91,    -1,    -1,    94,    -1,    96,
      -1,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,   106,
     107,     1,   109,   110,     4,    -1,     6,     7,     8,     9,
      -1,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      -1,    81,    82,    83,    -1,    85,    -1,    -1,    88,    89,
      90,    91,    -1,    -1,    94,    -1,    96,    -1,    -1,    -1,
      -1,    -1,   102,   103,    -1,   105,   106,   107,     1,   109,
     110,     4,    -1,     6,     7,     8,     9,    -1,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    -1,    81,    82,
      83,    -1,    85,    -1,    -1,    88,    89,    90,    91,    -1,
      -1,    94,    -1,    96,    -1,    -1,    -1,    -1,    -1,   102,
     103,    -1,   105,   106,   107,     1,   109,   110,     4,    -1,
       6,     7,     8,     9,    -1,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    -1,    81,    82,    83,    -1,    85,
      -1,    -1,    88,    89,    90,    91,    -1,    -1,    94,    -1,
      96,    -1,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
     106,   107,     1,   109,   110,     4,    -1,     6,     7,     8,
       9,    -1,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    -1,    81,    82,    83,    -1,    85,    -1,    -1,    88,
      89,    90,    91,    -1,    -1,    94,    -1,    96,    -1,    -1,
      -1,    -1,    -1,   102,   103,    -1,   105,   106,   107,     1,
     109,   110,     4,    -1,     6,     7,     8,     9,    -1,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    19,    -1,    -1,    22,
      23,    24,    -1,    75,    76,    77,    78,    79,    -1,    81,
      82,    83,    -1,    85,    -1,    -1,    88,    89,    -1,    91,
      43,    44,    94,    -1,    96,    -1,    -1,    -1,    -1,    52,
     102,   103,    -1,   105,   106,   107,    -1,   109,   110,    -1,
      -1,    64,    65,    66,    67,    19,    20,    -1,    22,    23,
      24,    74,    75,    -1,    -1,    -1,    79,    -1,    81,    82,
      83,    -1,    85,    -1,    -1,    -1,    89,    -1,    91,    43,
      44,    94,    -1,    96,    97,    -1,    -1,    -1,    52,   102,
     103,    -1,   105,   106,   107,    -1,   109,   110,    -1,    -1,
      64,    65,    66,    67,    19,    -1,    -1,    22,    23,    24,
      -1,    75,    -1,    -1,    -1,    79,    -1,    81,    82,    83,
      -1,    85,    -1,    -1,    88,    89,    -1,    91,    43,    44,
      94,    -1,    96,    -1,    -1,    -1,    -1,    52,   102,   103,
      -1,   105,   106,   107,    -1,   109,   110,    -1,    -1,    64,
      65,    66,    67,    19,    -1,    -1,    22,    23,    24,    74,
      75,    -1,    -1,    -1,    79,    80,    81,    82,    83,    -1,
      85,    -1,    -1,    -1,    89,    -1,    91,    43,    44,    94,
      -1,    96,    -1,    -1,    -1,    -1,    52,   102,   103,    -1,
     105,   106,   107,    -1,   109,   110,    -1,    -1,    64,    65,
      66,    67,    19,    -1,    -1,    22,    23,    24,    74,    75,
      -1,    -1,    -1,    79,    80,    81,    82,    83,    -1,    85,
      -1,    -1,    -1,    89,    -1,    91,    43,    44,    94,    -1,
      96,    -1,    -1,    -1,    -1,    52,   102,   103,    -1,   105,
     106,   107,    -1,   109,   110,    -1,    -1,    64,    65,    66,
      67,    19,    -1,    -1,    22,    23,    24,    -1,    75,    -1,
      -1,    -1,    79,    80,    81,    82,    83,    -1,    85,    -1,
      -1,    -1,    89,    -1,    91,    43,    44,    94,    -1,    96,
      -1,    -1,    -1,    -1,    52,   102,   103,    -1,   105,   106,
     107,    -1,   109,   110,    -1,    -1,    64,    65,    66,    67,
      19,    -1,    -1,    22,    23,    24,    74,    75,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    -1,    85,    -1,    -1,
      -1,    89,    -1,    91,    43,    44,    94,    -1,    96,    -1,
      -1,    -1,    -1,    52,   102,   103,    -1,   105,   106,   107,
      -1,   109,   110,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      79,    -1,    81,    82,    83,    -1,    85,    -1,    -1,    -1,
      89,    -1,    91,    -1,    93,    94,    19,    96,    -1,    22,
      23,    24,    -1,   102,   103,    -1,   105,   106,   107,    -1,
     109,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    79,    -1,    81,    82,
      83,    -1,    85,    -1,    -1,    -1,    89,    -1,    91,    -1,
      93,    94,    19,    96,    -1,    22,    23,    24,    -1,   102,
     103,    -1,   105,   106,   107,    -1,   109,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    79,    -1,    81,    82,    83,    -1,    85,    -1,
      -1,    -1,    89,    -1,    91,    -1,    93,    94,    19,    96,
      -1,    22,    23,    24,    -1,   102,   103,    -1,   105,   106,
     107,    -1,   109,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,
      81,    82,    83,    -1,    85,    -1,    -1,    -1,    89,    -1,
      91,    -1,    -1,    94,    -1,    96,    -1,    -1,    -1,    -1,
      -1,   102,   103,    -1,   105,   106,   107,    19,   109,   110,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    19,    -1,    -1,    22,
      23,    24,    -1,    75,    -1,    -1,    -1,    79,    -1,    81,
      82,    83,    -1,    85,    -1,    -1,    -1,    89,    -1,    91,
      43,    44,    94,    -1,    96,    -1,    -1,    -1,    -1,    52,
     102,   103,    -1,   105,   106,   107,    -1,   109,   110,    -1,
      -1,    64,    65,    66,    67,    19,    -1,    -1,    22,    23,
      24,    74,    75,    -1,    -1,    -1,    79,    -1,    81,    82,
      83,    -1,    85,    -1,    -1,    -1,    89,    -1,    91,    43,
      44,    94,    -1,    96,    -1,    -1,    -1,    -1,    52,   102,
     103,    -1,   105,   106,   107,    -1,   109,   110,    -1,    -1,
      64,    65,    66,    67,    19,    -1,    -1,    22,    23,    24,
      -1,    75,    -1,    -1,    -1,    79,    -1,    81,    82,    83,
      -1,    85,    -1,    -1,    -1,    89,    -1,    91,    43,    44,
      94,    -1,    96,    -1,    -1,    -1,    -1,    52,   102,   103,
      -1,   105,   106,   107,    -1,   109,   110,    -1,    -1,    64,
      65,    66,    67,    19,    -1,    -1,    22,    23,    24,    -1,
      75,    -1,    -1,    -1,    79,    -1,    81,    82,    83,    -1,
      85,    -1,    -1,    -1,    89,    -1,    91,    43,    44,    94,
      -1,    96,    -1,    -1,    -1,    -1,    52,   102,   103,    -1,
     105,   106,   107,    -1,   109,   110,    -1,    -1,    64,    65,
      66,    67,    19,    -1,    -1,    22,    23,    24,    -1,    75,
      -1,    -1,    -1,    79,    -1,    81,    82,    83,    -1,    85,
      -1,    -1,    -1,    89,    -1,    91,    43,    44,    94,    -1,
      96,    -1,    -1,    -1,    -1,    52,   102,   103,    -1,   105,
     106,   107,    -1,   109,   110,    -1,    -1,    64,    65,    66,
      67,    19,    -1,    -1,    22,    23,    24,    -1,    75,    -1,
      -1,    -1,    79,    -1,    81,    82,    83,    -1,    85,    -1,
      -1,    -1,    89,    -1,    91,    43,    44,    94,    -1,    96,
      -1,    -1,    -1,    -1,    52,   102,   103,    -1,   105,   106,
     107,    -1,   109,   110,    -1,    -1,    64,    65,    66,    67,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    -1,    85,    -1,    -1,
      -1,    89,    -1,    91,    43,    44,    94,    -1,    96,    -1,
      -1,    -1,    -1,    52,   102,   103,    -1,   105,   106,   107,
      -1,   109,   110,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      79,    -1,    81,    82,    83,    -1,    85,    -1,    -1,    -1,
      89,    -1,    91,    -1,    -1,    94,    -1,    96,    -1,    -1,
      -1,    -1,    -1,    -1,   103,    -1,   105,   106,   107,    -1,
     109,   110,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    79,    -1,    -1,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      -1,    -1,    94,    64,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    90,
      -1,    -1,    -1,    94,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    -1,    -1,    94,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    -1,    84,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    95,    -1,    -1,    -1,    84,    87,    -1,    -1,
      -1,    -1,    -1,    93,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     6,     7,     8,     9,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    43,    44,    52,    64,    65,    66,    67,    75,    76,
      77,    78,    79,    81,    82,    83,    85,    89,    91,    94,
      96,   102,   103,   105,   106,   107,   109,   110,   112,   113,
     114,   115,   116,   118,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   131,   132,   133,   134,   135,   136,   137,
     139,   140,   143,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     164,   165,   167,   168,   170,   178,   181,   184,   185,   186,
     188,   189,   190,   191,    88,    94,    94,   114,    94,    89,
     115,     4,    79,   142,    79,   142,    94,    23,    24,    67,
      79,    89,   143,   186,    93,    89,    89,   143,   174,   164,
      79,    96,   182,   183,   182,    79,    94,    79,    94,    79,
      79,    79,    79,   141,   174,   141,   143,    79,    79,   138,
      79,    79,   162,   162,   179,    20,    94,    94,   180,    79,
     117,   117,    88,    93,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      64,    65,    66,    67,    68,    74,    79,    83,    84,    90,
      94,   113,   175,   176,   177,   162,    80,    89,   143,   145,
      74,    97,   143,   172,    94,   115,   104,   169,   162,   161,
     179,   161,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    64,
      65,    66,    67,    68,    79,    84,   166,     0,   114,   142,
      88,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    87,   142,    48,    99,    41,    42,
     100,   101,   102,    36,    37,    38,    39,    40,   103,   104,
      45,    46,    91,   105,   106,   107,   108,    47,    62,    63,
      43,    44,    94,    96,    98,   163,   103,   187,   143,   173,
     173,     6,    20,    88,   173,    10,   129,    94,   142,    88,
     142,    88,   173,     4,     6,     7,     8,     9,    12,    13,
      14,    15,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    64,    65,    66,    67,
      79,    83,    94,    87,    93,   187,    79,   119,    90,    88,
      92,    87,    93,   172,    88,    92,    88,    94,    74,   165,
     194,   195,   196,    94,   194,    94,    94,    94,    94,   193,
     142,   142,   115,    88,    92,   193,   115,   180,    79,    94,
      80,    89,    89,   114,    79,   167,   168,   170,   203,    93,
      80,    90,    92,   171,    93,    95,    90,    95,    94,    95,
      96,    98,   163,   203,    92,   171,   194,   172,   180,    88,
     144,   145,   146,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,    31,   144,   149,   146,   150,
     151,   152,   153,   154,   155,   155,   156,   156,   156,   156,
     156,   157,   157,   158,   158,   159,   159,   159,   160,   161,
     161,    74,    80,   143,   145,   200,   201,   202,   143,    84,
     166,    22,    83,   197,    79,    94,    92,    95,    95,    94,
     182,   141,    88,    94,    11,   130,   173,    88,    88,    95,
      93,    80,    87,    92,   171,    89,   143,   144,   197,   171,
     183,   194,   165,    93,    95,    92,   194,    95,   194,   194,
     194,   194,    93,   192,    88,    88,    79,   192,    87,    80,
      95,    90,   113,    90,   113,   143,    95,   176,    90,   143,
     200,   143,    84,   166,    74,   143,    97,    95,   171,   143,
      93,   203,    95,    92,    97,   104,    94,   194,   143,   114,
     114,   173,    88,    88,   141,    79,   115,    95,   115,   143,
      95,    82,    91,    79,    90,    90,    94,   198,    97,    95,
     197,   115,   196,    95,   115,    95,    95,    95,    95,   164,
     115,   115,    80,    95,    90,    90,    93,    95,    97,   203,
      69,    73,   146,    74,   202,   194,    95,     5,    95,   141,
     141,    88,    95,    82,    87,   197,    87,    87,   115,   198,
     115,   115,   115,   115,    94,   199,    88,    95,   143,   115,
     146,   203,    95,   115,   114,    88,    88,    95,   141,   115,
      82,    91,    95,   144,   144,   200,   115,   141,   114,    95,
      82,    95,    95,   114,   114
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   111,   112,   113,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   115,   115,   116,   116,
     116,   116,   117,   118,   119,   119,   119,   119,   119,   119,
     120,   120,   120,   120,   121,   122,   122,   123,   124,   125,
     126,   126,   127,   127,   127,   128,   129,   129,   130,   130,
     131,   131,   131,   131,   132,   132,   133,   134,   135,   135,
     135,   135,   136,   137,   138,   138,   139,   140,   140,   141,
     141,   142,   142,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   144,   144,
     145,   145,   145,   145,   145,   145,   146,   146,   147,   147,
     148,   148,   149,   149,   150,   150,   151,   151,   152,   152,
     153,   153,   154,   154,   154,   155,   155,   155,   155,   155,
     155,   156,   156,   156,   157,   157,   157,   158,   158,   158,
     158,   159,   159,   160,   160,   160,   161,   161,   161,   161,
     161,   161,   161,   162,   162,   162,   162,   162,   162,   163,
     163,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   165,
     165,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   167,   167,   168,   168,   169,   170,
     171,   171,   172,   172,   172,   172,   173,   173,   174,   174,
     174,   174,   175,   175,   176,   176,   176,   176,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   178,   178,   178,   179,   180,   181,   181,   182,   182,
     183,   183,   183,   183,   183,   184,   184,   185,   185,   185,
     186,   187,   187,   188,   188,   188,   188,   188,   188,   189,
     189,   189,   190,   190,   191,   191,   192,   192,   193,   193,
     194,   194,   195,   195,   196,   196,   196,   197,   197,   198,
     198,   199,   199,   200,   200,   201,   201,   201,   201,   202,
     202,   202,   203,   203,   203,   203
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
       3,     4,     3,     4,     4,     2,     3,     3,     2,     1,
       4,     3,     4,     3,     1,     3,     2,     0,     2,     0,
       1,     0,     4,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       2,     2,     4,     3,     3,     4,     1,     5,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     3,     1,     3,     3,     1,     2,     2,     2,
       2,     2,     2,     1,     2,     4,     3,     3,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     6,     3,     3,     3,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     4,     2,     5,     0,     4,
       0,     1,     1,     2,     3,     4,     1,     3,     1,     2,
       3,     4,     1,     3,     5,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     0,     3,     3,     3,     1,     3,
       1,     4,     3,     6,     6,     1,     1,     6,     6,     7,
       1,     0,     3,     5,     5,     6,     6,     6,     2,     6,
       6,     6,     5,     5,     3,     3,     0,     3,     0,     3,
       0,     1,     1,     3,     1,     4,     2,     1,     1,     0,
       3,     0,     3,     0,     1,     1,     2,     3,     4,     1,
       1,     1,     1,     1,     1,     1
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
#line 2320 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 138 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2326 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 161 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2332 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 162 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2338 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 166 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2344 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 167 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2350 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 171 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2356 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 172 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2362 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 173 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2368 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 174 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2374 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 178 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2380 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 182 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2386 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 186 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2392 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 187 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2398 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 188 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2404 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 189 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2410 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 190 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2416 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 191 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2422 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 202 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2428 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 206 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2434 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 207 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2440 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 211 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2446 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 215 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2452 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 219 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2458 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 223 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2464 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 224 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2470 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 229 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2481 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 236 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2492 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 243 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2503 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 252 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2509 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 256 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2515 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 257 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2521 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 261 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2527 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 262 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2533 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 266 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2539 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 267 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2545 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 268 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2551 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 269 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2557 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 273 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2563 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 274 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); }
#line 2569 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 278 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_COROUTINE, (yyvsp[-1].obj), NULL, NULL); }
#line 2575 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 282 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2581 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 286 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2587 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 287 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2593 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 288 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2599 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 289 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2605 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 293 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2611 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 297 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2617 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 301 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2623 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 302 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2629 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 306 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2635 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 310 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2641 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 311 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2647 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 315 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2653 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 320 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2659 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 321 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2665 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 326 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2671 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 327 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2677 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 328 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2683 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 329 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2689 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 330 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2695 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 331 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2701 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 332 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2707 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 333 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2713 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 334 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2719 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 335 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2725 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 336 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2731 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 337 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2737 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 338 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2743 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 339 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2749 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 348 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2755 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 349 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2761 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 350 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2767 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 351 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2773 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 352 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2779 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 353 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2785 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 358 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2791 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 368 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2797 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 373 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2803 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 378 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2809 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 383 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2815 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 388 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2821 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 393 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2827 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 398 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2833 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 399 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2839 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 404 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2845 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 405 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2851 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 406 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2857 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 407 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2863 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 408 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2869 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 413 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2875 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 414 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2881 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 419 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2887 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 420 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2893 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 425 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2899 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 426 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2905 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 427 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2911 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 432 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2917 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 437 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2923 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 438 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2929 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 443 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 2935 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 444 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 2941 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 445 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 2947 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 446 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 2953 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 447 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 2959 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 448 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 2965 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 453 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2971 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 454 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2977 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 455 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2983 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 456 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2989 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 457 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2995 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 461 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3001 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 462 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3007 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 466 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3013 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 467 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3019 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 468 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3025 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 469 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3031 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 470 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3037 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 471 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3043 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 472 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3049 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 477 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3055 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 478 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3061 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 479 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3067 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 480 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3073 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 481 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3079 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 482 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3085 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 483 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3091 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3097 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 488 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3103 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 492 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3109 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 493 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3115 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 494 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3121 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3127 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3133 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3139 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3145 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 499 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3151 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 500 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3157 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 501 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3163 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 502 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3169 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3175 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 504 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3181 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 505 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3187 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 506 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3193 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 507 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3199 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3205 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3211 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 510 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3217 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 511 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3223 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 512 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3229 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 513 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3235 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3241 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 515 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3247 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 516 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3253 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 517 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3259 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 518 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("yield"); }
#line 3265 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 519 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3271 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3277 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 521 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3283 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 522 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3289 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 523 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3295 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 524 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3301 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 528 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3307 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 529 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3313 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 533 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3319 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 534 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3325 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3331 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 542 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3337 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 546 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3343 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 552 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3349 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 553 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3355 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 554 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3361 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 559 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3367 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 564 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3373 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 565 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3379 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 566 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3385 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 571 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3391 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 575 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3397 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 576 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3403 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 577 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3409 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 578 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3415 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 582 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3421 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 583 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3427 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 584 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3433 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 585 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3439 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 586 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3445 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 587 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3451 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 588 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3457 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 589 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3463 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 590 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3469 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 591 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3475 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 592 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3481 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 593 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3487 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 594 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3493 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 595 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3499 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 596 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3505 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 597 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3511 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 598 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3517 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 599 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3523 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 600 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3529 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 601 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3535 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 602 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3541 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 603 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3547 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 604 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3553 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 605 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3559 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 606 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3565 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 607 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3571 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 608 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3577 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3583 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 610 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3589 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 611 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3595 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 612 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3601 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 613 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3607 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 614 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3613 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 618 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3619 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 619 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 3625 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 620 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3631 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 624 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 3637 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 628 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 3643 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 632 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3649 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 3655 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 638 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3661 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 3667 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 643 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 3673 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3679 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 3685 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 3691 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3697 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 651 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3703 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3709 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3715 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3721 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 661 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 3727 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 665 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 3733 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 666 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3739 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3745 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 671 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3751 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 672 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3757 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 673 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 3763 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 674 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 3769 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 675 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 3775 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 679 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3781 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 680 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3787 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 681 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3793 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 685 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3799 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 686 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3805 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 690 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3811 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 691 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3817 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 695 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3823 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 697 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 3836 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 708 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3842 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 709 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3848 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 713 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3854 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 719 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3860 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 723 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3866 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 724 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 3872 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 725 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 3878 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 729 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 3884 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 730 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 3890 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 734 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 3896 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 735 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3902 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 739 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3908 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 740 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3914 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 744 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3920 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 750 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3926 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 751 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 3932 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 752 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 3938 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 758 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3944 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 762 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3950 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 763 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 3956 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 764 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 3962 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 765 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 3968 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 3972 "kx.tab.c" /* yacc.c:1646  */
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
#line 768 "src/kinx.y" /* yacc.c:1906  */


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
