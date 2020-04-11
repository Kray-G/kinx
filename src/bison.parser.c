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
    IN = 264,
    TRY = 265,
    CATCH = 266,
    FINALLY = 267,
    BREAK = 268,
    CONTINUE = 269,
    SWITCH = 270,
    CASE = 271,
    DEFAULT = 272,
    ENUM = 273,
    COROUTINE = 274,
    NEW = 275,
    VAR = 276,
    CONST = 277,
    NATIVE = 278,
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
    SYSFUNC = 291,
    EQEQ = 292,
    NEQ = 293,
    LE = 294,
    GE = 295,
    LGE = 296,
    LOR = 297,
    LAND = 298,
    INC = 299,
    DEC = 300,
    SHL = 301,
    SHR = 302,
    POW = 303,
    LUNDEF = 304,
    ADDEQ = 305,
    SUBEQ = 306,
    MULEQ = 307,
    DIVEQ = 308,
    MODEQ = 309,
    ANDEQ = 310,
    OREQ = 311,
    XOREQ = 312,
    LANDEQ = 313,
    LOREQ = 314,
    LUNDEFEQ = 315,
    SHLEQ = 316,
    SHREQ = 317,
    REGEQ = 318,
    REGNE = 319,
    NUL = 320,
    TRUE = 321,
    FALSE = 322,
    IMPORT = 323,
    USING = 324,
    DARROW = 325,
    SQ = 326,
    DQ = 327,
    MLSTR = 328,
    BINEND = 329,
    DOTS2 = 330,
    DOTS3 = 331,
    REGPF = 332,
    NAMESPACE = 333,
    SYSNS = 334,
    SYSRET_NV = 335,
    NAME = 336,
    STR = 337,
    BIGINT = 338,
    INT = 339,
    TYPE = 340,
    TYPEOF = 341,
    DBL = 342,
    BIN = 343
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

#line 227 "kx.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE kx_yylval;

int kx_yyparse (void);

#endif /* !YY_KX_YY_KX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 244 "kx.tab.c" /* yacc.c:358  */

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
#define YYFINAL  347
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4009

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  384
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  746

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   343

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   111,     2,     2,     2,   110,   104,     2,
      96,    97,   108,   107,    94,    93,   100,   109,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    95,    90,
     105,    89,   106,   101,   112,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    98,     2,    99,   103,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,   102,    92,     2,     2,     2,     2,
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
      85,    86,    87,    88
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   143,   144,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   172,   173,   177,   178,
     179,   180,   184,   188,   192,   193,   194,   195,   196,   197,
     201,   202,   203,   204,   208,   212,   213,   217,   221,   225,
     229,   230,   234,   241,   248,   255,   257,   262,   263,   267,
     271,   272,   276,   277,   281,   282,   283,   284,   288,   289,
     293,   297,   301,   302,   303,   304,   308,   312,   316,   317,
     321,   325,   326,   330,   331,   335,   336,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   358,   359,   363,   364,   365,   366,   367,   368,
     372,   373,   377,   378,   382,   383,   387,   388,   392,   393,
     397,   398,   402,   403,   407,   408,   412,   413,   414,   418,
     419,   420,   421,   422,   423,   427,   428,   429,   433,   434,
     435,   439,   440,   441,   442,   446,   447,   451,   452,   453,
     457,   458,   462,   463,   467,   468,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   484,   485,   486,   487,   488,
     489,   490,   494,   495,   496,   497,   498,   499,   503,   504,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   529,   530,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   586,
     587,   591,   592,   596,   600,   604,   605,   609,   610,   611,
     612,   616,   617,   621,   622,   623,   624,   628,   629,   633,
     634,   635,   636,   640,   641,   642,   643,   644,   645,   646,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   659,   660,   661,   662,   663,   664,   665,   666,
     667,   668,   669,   670,   671,   672,   673,   674,   675,   676,
     677,   678,   679,   680,   681,   682,   683,   684,   685,   686,
     687,   688,   692,   693,   694,   698,   702,   706,   707,   711,
     712,   716,   717,   718,   719,   720,   724,   725,   729,   730,
     731,   735,   739,   740,   744,   745,   746,   747,   748,   749,
     753,   754,   755,   759,   760,   764,   765,   769,   770,   774,
     775,   787,   788,   792,   793,   797,   798,   802,   803,   804,
     808,   809,   813,   814,   818,   819,   823,   824,   828,   829,
     830,   831,   835,   836,   837
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ERROR", "IF", "ELSE", "WHILE", "DO",
  "FOR", "IN", "TRY", "CATCH", "FINALLY", "BREAK", "CONTINUE", "SWITCH",
  "CASE", "DEFAULT", "ENUM", "COROUTINE", "NEW", "VAR", "CONST", "NATIVE",
  "FUNCTION", "PUBLIC", "PRIVATE", "PROTECTED", "CLASS", "RETURN", "THROW",
  "YIELD", "MODULE", "MIXIN", "SYSCLASS", "SYSMODULE", "SYSFUNC", "EQEQ",
  "NEQ", "LE", "GE", "LGE", "LOR", "LAND", "INC", "DEC", "SHL", "SHR",
  "POW", "LUNDEF", "ADDEQ", "SUBEQ", "MULEQ", "DIVEQ", "MODEQ", "ANDEQ",
  "OREQ", "XOREQ", "LANDEQ", "LOREQ", "LUNDEFEQ", "SHLEQ", "SHREQ",
  "REGEQ", "REGNE", "NUL", "TRUE", "FALSE", "IMPORT", "USING", "DARROW",
  "SQ", "DQ", "MLSTR", "BINEND", "DOTS2", "DOTS3", "REGPF", "NAMESPACE",
  "SYSNS", "SYSRET_NV", "NAME", "STR", "BIGINT", "INT", "TYPE", "TYPEOF",
  "DBL", "BIN", "'='", "';'", "'{'", "'}'", "'-'", "','", "':'", "'('",
  "')'", "'['", "']'", "'.'", "'?'", "'|'", "'^'", "'&'", "'<'", "'>'",
  "'+'", "'*'", "'/'", "'%'", "'!'", "'@'", "$accept", "Program",
  "StatementList", "Statement", "BlockStatement", "NamespaceStatement",
  "NamespaceName", "EnumStatement", "EnumList", "DefinitionStatement",
  "LabelStatement", "IfStatement", "WhileStatement", "DoWhileStatement",
  "SwitchCaseStatement", "CaseStatement", "ForStatement", "ForInVariable",
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
  "RangeExpression", "Range", "RangeFactor_Opt", "RangeFactor",
  "PrefixExpression", "PostfixExpression", "PostIncDec", "Factor",
  "VarName", "PropertyName", "Array", "Binary", "BinStart", "Object",
  "Comma_Opt", "ArrayItemList", "AssignExpressionList",
  "AssignExpressionObjList", "KeyValueList", "KeyValue", "KeySpecialName",
  "Regex", "RegexStart", "RegexString", "VarDeclStatement",
  "DeclAssignExpressionList", "DeclAssignExpression",
  "FunctionDeclStatement", "NormalFunctionDeclStatement", "NativeKeyword",
  "NativeType_Opt", "AnonymousFunctionDeclExpression",
  "ClassFunctionDeclStatement", "ClassFunctionName", "ClassDeclStatement",
  "ModuleDeclStatement", "Inherit_Opt", "ClassArgumentList_Opts",
  "ArgumentList_Opts", "ArgumentList", "Argument", "TypeName",
  "ReturnType_Opt", "ClassCallArgumentList_Opts", "CallArgumentList_Opts",
  "CallArgumentList", "CallArgument", YY_NULLPTR
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,    61,
      59,   123,   125,    45,    44,    58,    40,    41,    91,    93,
      46,    63,   124,    94,    38,    60,    62,    43,    42,    47,
      37,    33,    64
};
# endif

#define YYPACT_NINF -465

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-465)))

#define YYTABLE_NINF -326

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1817,   -44,   -36,    29,  1817,    40,    66,    19,    22,    87,
    3561,     9,    74,  3611,  3897,   130,   130,  -465,   -47,  2354,
    2354,  2354,    25,  3611,  3611,  3561,   104,   112,   129,   140,
      -4,  3897,  3897,  -465,    10,   198,   238,    17,   134,   180,
     180,   -38,   171,   240,   242,  -465,   244,   917,  3897,  2951,
     288,    62,   162,  3897,  3811,  -465,  3811,  2461,   307,   753,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,   306,  -465,  -465,
    -465,   233,   822,  -465,  -465,   -19,   289,   291,   246,   235,
     248,    79,    28,   275,   -12,   146,   314,   263,  -465,  -465,
     254,  -465,    64,  -465,   261,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,   258,  -465,  -465,  -465,  -465,  -465,  3561,  3561,
     360,  2751,  1054,   356,   274,   306,   284,   306,   287,  3561,
     282,   286,   292,  -465,  2247,  2240,   258,  -465,   299,  1926,
    2347,   -16,  -465,  -465,  -465,  -465,  -465,  -465,  3001,  -465,
    -465,  3051,    23,    38,  -465,   123,   293,    39,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,   295,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,   294,
     302,   305,   308,   306,   297,   306,  2347,    66,  -465,   132,
     308,    66,   309,    39,    64,    64,   134,   304,   310,   326,
    -465,  -465,   318,   320,  -465,  1817,   -36,    29,  1163,    40,
      66,    12,    15,    87,  3561,  3897,   130,   130,   317,   -47,
    2354,  2354,  2354,    25,  3101,  3178,  3255,   104,    -4,   -33,
     -22,   -20,    17,  3661,   321,   322,  -465,  3897,  3332,  2801,
      62,   -56,  3897,  3811,   323,  1272,   324,  -465,   331,    64,
     330,  2033,  1919,    -9,  3661,  -465,  2347,   327,    39,  -465,
    -465,  3051,    64,  -465,   134,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,   329,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,   339,
    -465,  3661,  3661,  3661,  3661,  3661,  3661,  3661,  3661,  3661,
    3661,  3661,  3661,  3661,  3411,  -465,  3861,  3561,  3861,  3861,
    3861,  3861,  3861,  3861,  3861,  3861,  3861,  3861,  3861,  3861,
    3861,  3861,  3861,  3861,  3861,  3861,  3861,  3861,  3811,  3811,
     358,   358,  -465,  -465,  2851,  3561,  2568,  -465,     5,     2,
    2347,    41,    69,   334,   131,   423,  3611,   288,   424,   137,
     341,   426,  3561,   350,  -465,   354,  -465,   150,   351,   366,
    3661,  -465,   355,   361,   359,  -465,  -465,  3711,   362,  2026,
     327,  3661,     5,  -465,   130,  -465,    39,   139,   357,   363,
     364,  -465,  -465,    39,    39,    39,    39,   368,   367,   374,
    -465,  -465,   375,   368,  -465,    39,   369,  -465,   376,   386,
     373,  1381,  1490,  -465,  -465,    86,  -465,  1817,   379,   382,
    -465,  2247,   390,  3561,   264,  -465,   267,  2851,  -465,  3561,
    2675,  -465,  -465,  3461,   384,   387,   327,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  3561,  -465,   289,   391,   291,   246,   235,
     248,    79,    28,    28,   275,   275,   275,   275,   275,   -12,
     -12,   146,   146,   314,   314,   314,   263,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  3511,  -465,  -465,  -465,  -465,
    3661,  -465,  2347,    86,   392,   394,  -465,   144,  -465,  -465,
    -465,  -465,   388,   397,    39,  3561,  1817,  1817,  3561,  3051,
     488,   155,   408,   327,  3561,  3611,   418,    66,  -465,   184,
    -465,  -465,    66,  3561,   403,   -14,   420,   410,  2140,  2347,
    -465,  -465,   405,  -465,   409,  -465,   411,  -465,     5,    66,
      39,   412,   413,   416,   417,  3897,    66,  -465,  -465,  -465,
      66,   419,    66,   425,   427,  -465,  -465,  1599,  -465,  1708,
     575,   -11,  -465,  -465,  2347,   428,   236,  -465,  -465,  3661,
    2347,  -465,   436,   441,  2347,  3561,   429,  2133,  -465,  -465,
    2901,  -465,  -465,    39,   430,  2347,   517,  -465,   207,   327,
    3561,  3611,  3611,   431,   208,   433,   432,  -465,  -465,  -465,
    2347,   437,  -465,   444,   445,  -465,  -465,   446,     5,   447,
      66,   409,  -465,  -465,    66,    66,    66,  -465,   443,  -465,
    -465,    66,  -465,   450,   440,  -465,  -465,  3561,  -465,  -465,
    -465,  3761,  -465,  -465,  -465,  -465,  3661,  -465,   448,    66,
    1817,   451,   434,   212,   454,   449,   538,  1817,  3611,    66,
    -465,    30,  3661,   452,  3661,  -465,  -465,  -465,  -465,  -465,
    2851,  -465,  -465,  -465,  -465,  2347,  -465,  -465,  -465,    66,
    -465,  -465,  -465,   446,  1817,  3611,  1817,  -465,   453,  -465,
    -465,   467,  -465,  -465,  -465,   455,  -465,  -465,   456,  -465,
    1817,  -465,  -465,  1817,  -465,  -465
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    85,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   341,     0,     0,
       0,     0,     0,    83,    83,    73,     0,     0,     0,     0,
       0,     0,     0,   325,   183,   185,   186,     0,     0,     0,
       0,     0,   198,   182,   180,   199,   181,     0,     0,     0,
       0,     0,   253,     0,     0,   325,     0,     0,     0,     0,
       3,     5,     6,     7,    21,    23,     8,     9,    10,    11,
      12,    13,    14,    22,    15,    16,    17,    85,    18,    19,
      20,     0,    85,    87,   110,   113,   114,   116,   118,   120,
     122,   124,   126,   129,   135,   138,   141,   145,   147,   150,
       0,   151,   165,   172,   184,   187,   188,   189,   190,    40,
      41,   336,   342,   112,   337,    42,    43,    25,     0,     0,
       0,     0,     0,    60,     0,    85,     0,    85,     0,     0,
       0,     0,     0,   198,     0,     0,   342,    51,     0,     0,
     263,     0,   183,   185,   186,   182,   180,   181,     0,   195,
     184,     0,   331,     0,   329,     0,     0,   363,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   291,   292,   293,   294,   296,
     298,   297,   295,   290,   306,   307,   308,   310,   312,   299,
     300,   301,   302,   303,   353,   304,   305,   314,     0,   319,
     320,   318,   309,   311,   313,   315,   316,   317,   354,     0,
       0,     0,   361,    85,    84,    85,    72,     0,    78,     0,
     361,     0,     0,   363,   170,   171,     0,     0,     0,     0,
     324,    32,     0,     0,    69,     0,   273,   275,     0,   277,
     278,    85,    85,   283,   284,   285,   286,   287,   341,   289,
     291,   292,   293,   294,    83,    83,    73,   295,   290,   183,
     185,   186,   302,     0,   198,   199,    26,   314,     0,     0,
     318,   253,   313,   315,   316,     0,   255,   267,     0,   168,
       0,     0,     0,     0,     0,   249,   257,   255,   363,   349,
     251,     0,   167,   169,     0,   166,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   220,   221,   222,   223,   225,   227,
     226,   224,   219,   233,   234,   235,   237,   239,   228,   229,
     230,   231,   232,   200,   197,   241,     0,   246,   247,   245,
     236,   238,   240,   242,   243,   244,   196,     1,     4,     0,
      80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     154,   154,   178,   179,   376,     0,     0,   173,     0,     0,
     261,     0,     0,     0,     0,   198,    83,     0,     0,     0,
       0,    62,     0,     0,    64,     0,    66,     0,     0,     0,
       0,    50,     0,    34,   255,   264,    70,     0,     0,     0,
     255,     0,     0,   327,     0,   328,   363,     0,   367,     0,
     364,   365,   321,   363,   363,   363,   363,   359,     0,     0,
     357,    77,     0,   359,   358,   363,     0,   323,     0,     0,
       0,     0,     0,    44,   272,   103,   102,     0,     0,   249,
      27,   256,     0,     0,   194,   104,   192,   376,   193,     0,
       0,   105,   258,   256,     0,     0,   255,   322,   248,    71,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,    89,    90,    75,    88,   115,     0,   117,   119,   121,
     123,   125,   127,   128,   131,   133,   134,   130,   132,   136,
     137,   140,   139,   142,   143,   144,   146,   148,   149,   159,
     161,   162,   158,   156,   157,     0,   152,   155,   160,   153,
       0,   384,   382,   383,     0,   377,   378,     0,   176,   175,
     371,   370,     0,     0,   363,     0,     0,     0,     0,     0,
       0,     0,     0,   255,     0,    83,     0,     0,    59,     0,
      65,    67,     0,     0,     0,     0,   256,     0,     0,   265,
     194,   192,     0,   333,   372,   330,     0,   369,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,    76,    79,
       0,     0,     0,     0,     0,   326,    28,     0,    29,     0,
     270,   194,   268,   254,   271,     0,     0,   108,   107,     0,
     259,   250,     0,     0,    74,     0,     0,     0,   379,   177,
       0,   174,   343,   363,     0,   262,    45,    47,     0,   255,
       0,    83,    83,     0,     0,     0,     0,    63,    86,    49,
     270,     0,    35,     0,    37,    33,   266,     0,     0,   332,
       0,   372,   344,   366,     0,     0,     0,   362,   374,   355,
     356,     0,   345,     0,     0,    30,    31,     0,   109,   106,
     260,     0,   252,   111,   164,   163,     0,   380,     0,     0,
       0,     0,     0,     0,     0,     0,   250,     0,    83,     0,
      36,     0,     0,     0,     0,   338,   368,   350,   351,   352,
     376,   360,   339,    24,   191,   269,   348,   347,   381,     0,
     346,    46,    48,    58,     0,    83,     0,    55,     0,    61,
      38,     0,   335,   373,   334,     0,   340,    56,     0,    54,
       0,    39,   375,     0,    53,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -465,  -465,    11,     4,    -3,  -465,   508,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,   151,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,   -23,    -6,     8,  -183,   -43,  -212,  -465,  -465,   188,
     190,   193,   189,   194,   196,   -29,  -187,   -34,   -24,  -102,
     183,  -465,  -465,   185,   -30,   -39,    13,  -278,    -5,   464,
    -369,  -465,  -465,  -465,  -465,  -263,  -137,  -109,   558,  -465,
     103,   -40,  -465,   542,  -197,  -465,     6,   143,  -465,  -465,
       0,   442,  -465,  -465,    20,  -465,  -465,   127,   365,  -186,
    -465,    -8,  -407,   -78,  -465,  -464,  -465,   -46
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    58,   275,    60,    61,    62,   232,    63,   424,    64,
      65,    66,    67,    68,    69,    70,    71,   408,    72,   411,
     568,    73,    74,    75,    76,    77,    78,    79,   219,    80,
      81,   213,   126,    82,   504,   465,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   536,   100,   101,   102,   397,   103,   104,
     346,   105,   106,   291,   107,   472,   287,   401,   214,   276,
     277,   208,   108,   294,   230,   109,   153,   154,   110,   111,
     136,   399,   113,   114,   209,   115,   116,   596,   447,   439,
     440,   441,   552,   659,   711,   544,   545,   546
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     112,   215,   128,   123,   112,   481,   283,   278,   120,   149,
     402,    59,   409,   615,   430,   293,   124,   295,   135,   124,
     417,   140,   155,   124,   484,   584,   124,   549,   550,   457,
     366,   140,   140,   216,   156,   392,   393,   456,   227,  -309,
     210,   211,  -159,  -159,   224,   225,   117,   112,   289,   157,
     290,   466,   234,  -161,  -161,  -162,  -162,   282,   286,   112,
     118,   279,  -299,   348,  -164,  -164,   292,   375,   376,   377,
     652,   349,   466,  -300,   426,  -301,   365,   222,   427,   653,
     464,   382,   367,   553,   677,  -159,  -159,   477,   478,   479,
     551,   480,   223,   125,   278,   383,   127,   487,   554,   278,
     125,   482,   485,   127,   137,   283,   212,  -281,   392,   393,
    -282,   618,   431,   228,   730,   437,   373,   374,   432,   413,
     133,   415,   112,   731,    45,   119,   400,   400,   433,   400,
     392,   393,   434,   378,   379,   555,   121,   400,   556,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   122,   486,   506,   429,   122,   288,   286,
     394,   577,   395,   555,   396,   138,   557,   582,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   661,   477,   129,   479,   217,   480,   481,   514,   515,
     516,   517,   518,   218,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   448,   466,   449,
     220,   133,   405,   435,   450,    45,    45,   434,   454,   466,
     133,   221,   451,   623,    45,   283,   452,   565,   151,   559,
     229,   555,   215,   420,   293,   112,   128,   123,   112,   463,
     149,   278,   120,   631,   555,   641,   735,   572,   583,   434,
     586,   703,   135,   155,   384,   385,   386,   591,   592,   593,
     594,   231,   140,   140,   216,   481,   235,   289,   290,   601,
     563,   210,   211,  -161,  -161,   112,   282,   286,   555,   348,
     279,   648,   523,   524,   525,   292,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   286,
     643,   555,   555,   569,   691,   697,   555,   347,    14,   724,
     124,    17,   130,  -162,  -162,  -158,  -158,  -156,  -156,  -157,
    -157,   380,   381,   350,   131,   420,   388,   389,   466,   390,
     391,   368,    31,    32,   369,   679,  -160,  -160,   371,  -164,
    -164,    33,  -163,  -163,   512,   513,   519,   520,   370,   527,
     528,   543,   372,    34,    35,    36,   132,   628,   521,   522,
     537,   537,   387,   398,   284,    38,   403,   410,   634,   133,
     412,    43,    44,    45,   414,    46,   692,   416,   157,   134,
     423,    48,   223,   562,    49,   458,    50,   285,   228,   436,
     443,   427,    51,    52,   442,    53,    54,    55,   444,    56,
      57,   445,   542,   547,   446,   455,   459,   466,   460,   461,
     561,   462,  -288,   683,   140,   286,   467,  -304,   471,  -325,
     400,   483,   639,   529,   530,   531,   473,   474,   488,   489,
     558,   278,   -57,   564,   543,   579,   680,   566,   567,   133,
     570,   532,   533,    45,   571,   534,   573,   688,   574,   638,
     575,   554,   588,   576,   535,   644,   599,   597,   590,   580,
     589,   112,   112,   595,   598,   603,   602,   112,   604,   717,
     605,   463,   607,   609,   466,   610,   611,  -321,   150,   152,
     152,   614,   613,   621,   622,   542,   625,   616,   630,   629,
     466,   620,   466,   633,   632,   150,   150,   640,   642,   646,
     651,   654,   655,   718,   657,   658,   681,   673,   660,   664,
     665,   624,   150,   666,   667,   682,   671,   150,   150,   732,
     150,   734,   690,   698,   674,   678,   684,   689,   700,   699,
     696,   693,   677,   723,   701,   702,   704,   714,   278,   710,
     713,   722,   645,   627,   725,   719,   726,   -58,   233,   733,
     740,   741,   742,   743,   505,   560,   112,   112,   507,   509,
     636,   637,   508,   635,   647,   510,   400,   286,   511,   649,
     526,   141,   400,   140,   612,   226,   539,   585,   422,   124,
     600,   650,   663,   706,   687,   453,   662,   543,     0,     0,
     668,     0,     0,   669,     0,     0,     0,   670,     0,   672,
       0,     0,     0,     0,   365,     0,     0,   112,     0,   112,
       0,   348,     0,   348,     0,     0,     0,     0,   694,   695,
       0,   438,     0,     0,     0,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   542,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   400,   140,
     140,     0,     0,     0,     0,     0,     0,   705,     0,     0,
       0,   707,   708,   709,   364,   -85,     0,   543,   712,     0,
       0,     0,     0,     0,     0,   728,     0,     0,   716,     0,
       0,     0,     0,     0,     0,   715,   720,   438,     0,     0,
     112,     0,     0,     0,   721,     0,   729,   112,     0,     0,
       0,   727,   738,     0,     0,     0,   140,     0,     0,   150,
     152,   152,     0,     0,     0,     0,   736,     0,   542,     0,
       0,     0,     0,     0,   112,     0,   112,     0,   737,     0,
     739,   150,     0,   140,     0,     0,   150,   150,     0,     0,
     112,     0,     0,   112,   744,     0,     0,   745,     0,     0,
       0,     0,   438,    -2,     1,     0,     0,     2,     0,     3,
       4,     5,     0,     6,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,    37,     0,     0,     0,     0,   124,     0,     0,     0,
      38,    39,    40,    41,    42,     0,    43,    44,    45,     0,
      46,     0,     0,   -81,    47,     0,    48,     0,     0,    49,
       0,    50,   150,   150,   538,   538,     0,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,   152,     0,
       0,     0,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   152,     0,
     438,   587,     0,     0,     0,     0,     0,   438,   438,   438,
     438,   364,     0,     0,     0,     0,     0,     0,     1,   438,
       0,   236,   159,   237,   238,   239,     0,   240,   164,   165,
     241,   242,   243,   244,    11,    12,    13,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
      27,    28,    29,   258,   184,   185,   186,   187,   188,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   259,   260,   261,   262,   193,     0,     0,     0,
       0,     0,     0,   263,    38,    39,    40,    41,   264,     0,
      43,    44,   265,   196,    46,     0,     0,   -81,    47,   266,
     267,     0,     0,   268,     0,   269,     0,     0,   438,   199,
     200,   270,   271,   203,   272,   273,   274,   207,    56,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   438,     1,     0,     0,     2,   150,
       3,     4,     5,     0,     6,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,   438,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,    38,    39,    40,    41,    42,     0,    43,    44,    45,
       0,    46,     0,     0,   -81,    47,   266,    48,     0,     0,
      49,     0,    50,     0,     0,     0,     0,     0,    51,    52,
       0,    53,    54,    55,     1,    56,    57,     2,     0,     3,
       4,     5,     0,     6,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,    42,     0,    43,    44,    45,     0,
      46,     0,     0,   -81,    47,     0,    48,     0,  -276,    49,
       0,    50,     0,     0,     0,     0,     0,    51,    52,     0,
      53,    54,    55,     1,    56,    57,     2,     0,     3,     4,
       5,     0,     6,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,    38,
      39,    40,    41,    42,     0,    43,    44,    45,     0,    46,
       0,     0,   -81,    47,   470,    48,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,    51,    52,     0,    53,
      54,    55,     1,    56,    57,     2,     0,     3,     4,     5,
       0,     6,     0,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    42,     0,    43,    44,    45,     0,    46,     0,
       0,   -81,    47,   606,    48,     0,     0,    49,     0,    50,
       0,     0,     0,     0,     0,    51,    52,     0,    53,    54,
      55,     1,    56,    57,     2,     0,     3,     4,     5,     0,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,    38,    39,    40,
      41,    42,     0,    43,    44,    45,     0,    46,     0,     0,
     -81,    47,   608,    48,     0,     0,    49,     0,    50,     0,
       0,     0,     0,     0,    51,    52,     0,    53,    54,    55,
       1,    56,    57,     2,     0,     3,     4,     5,     0,     6,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
      42,     0,    43,    44,    45,     0,    46,     0,     0,   -81,
      47,   675,    48,     0,     0,    49,     0,    50,     0,     0,
       0,     0,     0,    51,    52,     0,    53,    54,    55,     1,
      56,    57,     2,     0,     3,     4,     5,     0,     6,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    38,    39,    40,    41,    42,
       0,    43,    44,    45,     0,    46,     0,     0,   -81,    47,
     676,    48,     0,     0,    49,     0,    50,     0,     0,     0,
       0,     0,    51,    52,     0,    53,    54,    55,     1,    56,
      57,     2,     0,     3,     4,     5,     0,     6,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,     0,     0,   -81,    47,     0,
      48,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,     0,    56,    57,
     158,   159,   160,   161,   162,     0,   163,   164,   165,   166,
     167,   168,   169,     0,     0,     0,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,     0,   183,   184,   185,   186,   187,   188,     0,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   189,   190,   191,   192,   193,     0,     0,     0,     0,
       0,     0,   263,     0,     0,     0,     0,   418,   420,     0,
       0,   195,   196,     0,     0,     0,   476,     0,   425,   197,
       0,     0,   419,     0,   198,     0,     0,     0,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   158,   159,   160,
     161,   162,     0,   163,   164,   165,   166,   167,   168,   169,
       0,     0,     0,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,     0,     0,     0,   183,
     184,   185,   186,   187,   188,     0,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   189,   190,
     191,   192,   193,     0,     0,     0,     0,     0,     0,   263,
       0,     0,     0,     0,   418,   420,     0,     0,   195,   196,
       0,     0,     0,   581,     0,   475,   197,     0,     0,   419,
       0,   198,     0,     0,     0,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   158,   159,   160,   161,   162,     0,
     163,   164,   165,   166,   167,   168,   169,     0,     0,     0,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,     0,     0,     0,   183,   184,   185,   186,
     187,   188,     0,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   189,   190,   191,   192,   193,
       0,     0,     0,     0,     0,     0,   263,     0,     0,     0,
       0,   418,   420,     0,     0,   195,   196,     0,     0,     0,
     685,     0,   656,   197,     0,     0,   419,     0,   198,     0,
       0,     0,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   158,   159,   160,   161,   162,     0,   163,   164,   165,
     166,   167,   168,   169,     0,     0,     0,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
       0,     0,     0,   183,   184,   185,   186,   187,   188,     0,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   189,   190,   191,   192,   193,     0,     0,     0,
       0,     0,     0,   263,     0,     0,     0,     0,   418,   420,
       0,     0,   195,   196,     0,   421,     0,     0,     0,     0,
     197,     0,     0,   419,     0,   198,     0,     0,     0,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   158,   159,
     160,   161,   162,     0,   163,   164,   165,   166,   167,   168,
     169,     0,     0,     0,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,     0,     0,     0,
     183,   184,   185,   186,   187,   188,     0,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   189,
     190,   191,   192,   193,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   194,   420,     0,     0,   195,
     196,     0,     0,     0,     0,     0,     0,   197,     0,     0,
       0,     0,   198,     0,     0,     0,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   296,   297,   298,   299,   300,
       0,   301,   302,   303,   304,   305,   306,   307,   308,     0,
       0,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,     0,     0,     0,   322,   323,   324,
     325,   326,   327,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   328,   329,   330,   331,
     332,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   333,     0,     0,     0,     0,   334,     0,     0,
       0,     0,     0,     0,   335,     0,     0,     0,     0,   336,
       0,     0,     0,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   296,   297,   298,   299,   300,     0,   301,   302,
     303,   304,   305,   306,   307,   308,     0,     0,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,     0,     0,     0,   322,   323,   324,   325,   326,   327,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   328,   329,   330,   331,   332,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   333,
       0,     0,     0,     0,   548,     0,     0,     0,     0,     0,
       0,   335,     0,     0,     0,     0,   336,     0,     0,     0,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   296,
     297,   298,   299,   300,     0,   301,   302,   303,   304,   305,
     306,   307,   308,     0,     0,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,     0,     0,
       0,   322,   323,   324,   325,   326,   327,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     328,   329,   330,   331,   332,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   333,     0,     0,     0,
       0,   617,     0,     0,     0,     0,     0,     0,   335,     0,
       0,    14,   404,   336,    17,   130,     0,   337,   338,   339,
     340,   341,   342,   343,   344,   345,     0,   131,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,     0,    38,     0,
       0,     0,   405,     0,    43,    44,    45,   131,    46,     0,
       0,   406,   134,     0,    48,    31,    32,    49,     0,   407,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,   284,    38,     0,
       0,     0,   133,     0,    43,    44,    45,   131,    46,     0,
       0,     0,   134,     0,    48,    31,    32,    49,     0,    50,
     469,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,   540,    38,     0,
       0,     0,   133,   541,    43,    44,    45,   131,    46,     0,
       0,     0,   281,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,   686,    38,     0,
       0,     0,   133,   541,    43,    44,    45,   131,    46,     0,
       0,     0,   281,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,     0,    38,     0,
       0,     0,   133,   280,    43,    44,    45,   131,    46,     0,
       0,     0,   281,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,     0,    38,     0,
       0,     0,   133,   428,    43,    44,    45,   131,    46,     0,
       0,     0,   281,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,   284,    38,     0,
       0,     0,   133,     0,    43,    44,    45,   131,    46,     0,
       0,     0,   134,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,   133,     0,    43,    44,    45,     0,    46,     0,
       0,     0,   139,     0,    48,     0,  -296,    49,    14,    50,
       0,    17,   130,     0,     0,    51,    52,     0,    53,    54,
      55,     0,    56,    57,   131,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,   132,     0,     0,     0,
       0,     0,     0,     0,     0,    38,     0,     0,     0,   133,
       0,    43,    44,    45,     0,    46,     0,     0,     0,   139,
       0,    48,     0,  -298,    49,    14,    50,     0,    17,   130,
       0,     0,    51,    52,     0,    53,    54,    55,     0,    56,
      57,   131,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,   132,     0,     0,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,   133,     0,    43,    44,
      45,     0,    46,     0,     0,     0,   134,     0,    48,     0,
    -297,    49,    14,    50,     0,    17,   130,     0,     0,    51,
      52,     0,    53,    54,    55,     0,    56,    57,   131,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
     132,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,   133,   468,    43,    44,    45,     0,    46,
       0,     0,     0,   281,     0,    48,     0,     0,    49,     0,
      50,    14,     0,     0,    17,   130,    51,    52,     0,    53,
      54,    55,   503,    56,    57,     0,     0,   131,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,     0,    38,     0,
       0,     0,   133,     0,    43,    44,    45,   131,    46,     0,
       0,     0,   281,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,   619,    38,     0,
       0,     0,   133,     0,    43,    44,    45,   131,    46,     0,
       0,     0,   134,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,     0,    38,     0,
       0,     0,   133,   626,    43,    44,    45,   131,    46,     0,
       0,     0,   134,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,     0,    38,     0,
       0,     0,   133,     0,    43,    44,    45,   131,    46,     0,
       0,     0,   134,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,     0,    38,     0,
       0,     0,   133,     0,    43,    44,    45,   131,    46,     0,
       0,     0,   139,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,     0,    38,     0,
       0,     0,   133,     0,    43,    44,    45,   131,    46,     0,
       0,     0,   281,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,    17,   130,     0,     0,    38,     0,
       0,     0,   133,     0,    43,    44,    45,   131,    46,     0,
       0,     0,   578,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,    14,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,   133,     0,    43,    44,    45,     0,    46,     0,
       0,     0,    47,     0,    48,    31,    32,    49,     0,    50,
       0,     0,     0,     0,    33,    51,    52,     0,    53,    54,
      55,     0,    56,    57,     0,     0,   142,   143,   144,   132,
       0,    14,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,   133,     0,   145,   146,    45,     0,   147,     0,
       0,     0,   134,     0,    48,    31,    32,   148,     0,    50,
       0,     0,     0,     0,    33,     0,    52,    14,    53,    54,
      55,     0,    56,    57,     0,     0,    34,    35,    36,   132,
       0,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,   133,     0,    43,    44,    45,     0,    46,     0,
      33,     0,   134,     0,    48,     0,     0,    49,     0,    50,
       0,     0,   142,   143,   144,   132,    52,     0,    53,    54,
      55,     0,    56,    57,    38,     0,     0,     0,   133,     0,
     145,   146,    45,     0,   147,     0,     0,     0,   134,     0,
       0,     0,     0,   148,     0,    50,     0,     0,     0,     0,
       0,     0,    52,     0,     0,     0,    55,     0,     0,    57
};

static const yytype_int16 yycheck[] =
{
       0,    24,     8,     6,     4,   283,    49,    47,     4,    14,
     119,     0,   121,   477,   151,    54,     4,    56,    10,     4,
     129,    13,    16,     4,   287,   432,     4,   396,    23,   226,
      49,    23,    24,    25,    81,    44,    45,   223,    21,    95,
      20,    21,    75,    76,    31,    32,    90,    47,    51,    96,
     106,   263,    90,    75,    76,    75,    76,    49,    50,    59,
      96,    48,    95,    59,    75,    76,    53,    39,    40,    41,
      84,    77,   284,    95,    90,    95,    82,    81,    94,    93,
     263,    93,   101,    81,    95,    75,    76,    96,    97,    98,
      85,   100,    96,    81,   134,   107,    81,   294,    96,   139,
      81,   284,   288,    81,    95,   148,    81,    95,    44,    45,
      95,   480,    89,    96,    84,    76,    37,    38,    95,   125,
      81,   127,   122,    93,    85,    96,   118,   119,    90,   121,
      44,    45,    94,   105,   106,    94,    96,   129,    97,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,    91,   291,   367,   148,    91,    96,   151,
      96,   424,    98,    94,   100,    91,    97,   430,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   588,    96,    96,    98,    81,   100,   465,   375,   376,
     377,   378,   379,    81,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,   213,   420,   215,
      81,    81,    81,    90,   217,    85,    85,    94,   221,   431,
      81,    81,    90,   486,    85,   268,    94,    90,    98,    98,
      96,    94,   255,    89,   273,   235,   242,   240,   238,   235,
     245,   281,   238,    99,    94,    90,   710,    97,   431,    94,
     436,   658,   244,   247,   108,   109,   110,   443,   444,   445,
     446,    81,   254,   255,   256,   543,    95,   270,   106,   455,
     407,   251,   252,    75,    76,   275,   268,   269,    94,   275,
     267,    97,   384,   385,   386,   272,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,   291,
     563,    94,    94,   412,    97,    97,    94,     0,    20,    97,
       4,    23,    24,    75,    76,    75,    76,    75,    76,    75,
      76,    46,    47,    90,    36,    89,    63,    64,   540,    75,
      76,    42,    44,    45,    43,    99,    75,    76,   103,    75,
      76,    53,    75,    76,   373,   374,   380,   381,   102,   388,
     389,   394,   104,    65,    66,    67,    68,   540,   382,   383,
     390,   391,    48,   105,    76,    77,     6,    11,   554,    81,
      96,    83,    84,    85,    90,    87,   639,    90,    96,    91,
      81,    93,    96,   406,    96,    81,    98,    99,    96,    96,
      96,    94,   104,   105,    99,   107,   108,   109,    96,   111,
     112,    96,   394,   395,    96,    96,    96,   619,    82,    91,
     404,    91,    95,   625,   406,   407,    95,    95,    94,    96,
     412,    94,   559,    65,    66,    67,    95,    97,    99,    90,
      96,   471,     9,     9,   477,   427,   619,    96,    12,    81,
      90,    83,    84,    85,    90,    87,    95,   633,    82,   558,
      89,    96,    95,    94,    96,   564,    81,    90,    94,    97,
      97,   461,   462,    95,    90,    89,    97,   467,    82,   681,
      97,   467,   461,   462,   686,   467,    97,    95,    14,    15,
      16,   473,    92,    99,    97,   477,    95,   479,    94,    97,
     702,   483,   704,    96,   106,    31,    32,     9,    90,    81,
      97,    81,    92,   686,    99,    96,    70,    82,    97,    97,
      97,   503,    48,    97,    97,    74,    97,    53,    54,   702,
      56,   704,     5,    90,    97,    97,    97,    97,    84,    97,
      99,   640,    95,    99,    89,    89,    89,    97,   578,    96,
      90,    90,   565,   535,    90,    97,    97,     9,    40,    97,
      97,    84,    97,    97,   366,   404,   556,   557,   368,   370,
     556,   557,   369,   555,   567,   371,   558,   559,   372,   572,
     387,    13,   564,   565,   471,    33,   391,   434,   136,     4,
     453,   573,   590,   661,   630,   220,   589,   630,    -1,    -1,
     595,    -1,    -1,   596,    -1,    -1,    -1,   600,    -1,   602,
      -1,    -1,    -1,    -1,   610,    -1,    -1,   607,    -1,   609,
      -1,   607,    -1,   609,    -1,    -1,    -1,    -1,   641,   642,
      -1,   157,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,   630,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   640,   641,
     642,    -1,    -1,    -1,    -1,    -1,    -1,   660,    -1,    -1,
      -1,   664,   665,   666,    89,    90,    -1,   710,   671,    -1,
      -1,    -1,    -1,    -1,    -1,   698,    -1,    -1,   681,    -1,
      -1,    -1,    -1,    -1,    -1,   677,   689,   223,    -1,    -1,
     690,    -1,    -1,    -1,   690,    -1,   699,   697,    -1,    -1,
      -1,   697,   725,    -1,    -1,    -1,   698,    -1,    -1,   245,
     246,   247,    -1,    -1,    -1,    -1,   719,    -1,   710,    -1,
      -1,    -1,    -1,    -1,   724,    -1,   726,    -1,   724,    -1,
     726,   267,    -1,   725,    -1,    -1,   272,   273,    -1,    -1,
     740,    -1,    -1,   743,   740,    -1,    -1,   743,    -1,    -1,
      -1,    -1,   288,     0,     1,    -1,    -1,     4,    -1,     6,
       7,     8,    -1,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,     4,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    -1,    83,    84,    85,    -1,
      87,    -1,    -1,    90,    91,    -1,    93,    -1,    -1,    96,
      -1,    98,   388,   389,   390,   391,    -1,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,    -1,    -1,   404,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   434,    -1,
     436,   437,    -1,    -1,    -1,    -1,    -1,   443,   444,   445,
     446,    89,    -1,    -1,    -1,    -1,    -1,    -1,     1,   455,
      -1,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    -1,
      83,    84,    85,    86,    87,    -1,    -1,    90,    91,    92,
      93,    -1,    -1,    96,    -1,    98,    -1,    -1,   554,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   590,     1,    -1,    -1,     4,   595,
       6,     7,     8,    -1,    10,    -1,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,   633,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    78,    79,    80,    81,    -1,    83,    84,    85,
      -1,    87,    -1,    -1,    90,    91,    92,    93,    -1,    -1,
      96,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,   105,
      -1,   107,   108,   109,     1,   111,   112,     4,    -1,     6,
       7,     8,    -1,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    -1,    83,    84,    85,    -1,
      87,    -1,    -1,    90,    91,    -1,    93,    -1,    95,    96,
      -1,    98,    -1,    -1,    -1,    -1,    -1,   104,   105,    -1,
     107,   108,   109,     1,   111,   112,     4,    -1,     6,     7,
       8,    -1,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,    81,    -1,    83,    84,    85,    -1,    87,
      -1,    -1,    90,    91,    92,    93,    -1,    -1,    96,    -1,
      98,    -1,    -1,    -1,    -1,    -1,   104,   105,    -1,   107,
     108,   109,     1,   111,   112,     4,    -1,     6,     7,     8,
      -1,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,
      79,    80,    81,    -1,    83,    84,    85,    -1,    87,    -1,
      -1,    90,    91,    92,    93,    -1,    -1,    96,    -1,    98,
      -1,    -1,    -1,    -1,    -1,   104,   105,    -1,   107,   108,
     109,     1,   111,   112,     4,    -1,     6,     7,     8,    -1,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,
      80,    81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,
      90,    91,    92,    93,    -1,    -1,    96,    -1,    98,    -1,
      -1,    -1,    -1,    -1,   104,   105,    -1,   107,   108,   109,
       1,   111,   112,     4,    -1,     6,     7,     8,    -1,    10,
      -1,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,
      81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,    90,
      91,    92,    93,    -1,    -1,    96,    -1,    98,    -1,    -1,
      -1,    -1,    -1,   104,   105,    -1,   107,   108,   109,     1,
     111,   112,     4,    -1,     6,     7,     8,    -1,    10,    -1,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      -1,    83,    84,    85,    -1,    87,    -1,    -1,    90,    91,
      92,    93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,
      -1,    -1,   104,   105,    -1,   107,   108,   109,     1,   111,
     112,     4,    -1,     6,     7,     8,    -1,    10,    -1,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,    -1,
      83,    84,    85,    -1,    87,    -1,    -1,    90,    91,    -1,
      93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,
      -1,   104,   105,    -1,   107,   108,   109,    -1,   111,   112,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    41,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    81,    89,    -1,
      -1,    85,    86,    -1,    -1,    -1,    97,    -1,    92,    93,
      -1,    -1,    96,    -1,    98,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     4,     5,     6,
       7,     8,    -1,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    41,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    81,    89,    -1,    -1,    85,    86,
      -1,    -1,    -1,    97,    -1,    92,    93,    -1,    -1,    96,
      -1,    98,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     4,     5,     6,     7,     8,    -1,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    81,    89,    -1,    -1,    85,    86,    -1,    -1,    -1,
      97,    -1,    92,    93,    -1,    -1,    96,    -1,    98,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    81,    89,
      -1,    -1,    85,    86,    -1,    95,    -1,    -1,    -1,    -1,
      93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    89,    -1,    -1,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     4,     5,     6,     7,     8,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    20,    21,    98,    23,    24,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    36,    87,    -1,
      -1,    90,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      99,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,
      -1,    -1,    91,    -1,    93,    -1,    95,    96,    20,    98,
      -1,    23,    24,    -1,    -1,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,
      -1,    83,    84,    85,    -1,    87,    -1,    -1,    -1,    91,
      -1,    93,    -1,    95,    96,    20,    98,    -1,    23,    24,
      -1,    -1,   104,   105,    -1,   107,   108,   109,    -1,   111,
     112,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    -1,    87,    -1,    -1,    -1,    91,    -1,    93,    -1,
      95,    96,    20,    98,    -1,    23,    24,    -1,    -1,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    91,    -1,    93,    -1,    -1,    96,    -1,
      98,    20,    -1,    -1,    23,    24,   104,   105,    -1,   107,
     108,   109,    31,   111,   112,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    36,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,
      -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,    98,
      -1,    -1,    -1,    -1,    53,    -1,   105,    20,   107,   108,
     109,    -1,   111,   112,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,
      53,    -1,    91,    -1,    93,    -1,    -1,    96,    -1,    98,
      -1,    -1,    65,    66,    67,    68,   105,    -1,   107,   108,
     109,    -1,   111,   112,    77,    -1,    -1,    -1,    81,    -1,
      83,    84,    85,    -1,    87,    -1,    -1,    -1,    91,    -1,
      -1,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,
      -1,    -1,   105,    -1,    -1,    -1,   109,    -1,    -1,   112
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     6,     7,     8,    10,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    44,    45,    53,    65,    66,    67,    68,    77,    78,
      79,    80,    81,    83,    84,    85,    87,    91,    93,    96,
      98,   104,   105,   107,   108,   109,   111,   112,   114,   115,
     116,   117,   118,   120,   122,   123,   124,   125,   126,   127,
     128,   129,   131,   134,   135,   136,   137,   138,   139,   140,
     142,   143,   146,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     167,   168,   169,   171,   172,   174,   175,   177,   185,   188,
     191,   192,   193,   195,   196,   198,   199,    90,    96,    96,
     116,    96,    91,   117,     4,    81,   145,    81,   145,    96,
      24,    36,    68,    81,    91,   146,   193,    95,    91,    91,
     146,   181,    65,    66,    67,    83,    84,    87,    96,   171,
     172,    98,   172,   189,   190,   189,    81,    96,     4,     5,
       6,     7,     8,    10,    11,    12,    13,    14,    15,    16,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    36,    37,    38,    39,    40,    41,    65,
      66,    67,    68,    69,    81,    85,    86,    93,    98,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   184,   197,
     197,   197,    81,   144,   181,   144,   146,    81,    81,   141,
      81,    81,    81,    96,   169,   169,   186,    21,    96,    96,
     187,    81,   119,   119,    90,    95,     4,     6,     7,     8,
      10,    13,    14,    15,    16,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    36,    65,
      66,    67,    68,    76,    81,    85,    92,    93,    96,    98,
     104,   105,   107,   108,   109,   115,   182,   183,   184,   169,
      82,    91,   146,   148,    76,    99,   146,   179,    96,   117,
     106,   176,   169,   168,   186,   168,     4,     5,     6,     7,
       8,    10,    11,    12,    13,    14,    15,    16,    17,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    36,    37,    38,    39,    40,    41,    65,    66,
      67,    68,    69,    81,    86,    93,    98,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   173,     0,   116,   145,
      90,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    89,   145,    49,   101,    42,    43,
     102,   103,   104,    37,    38,    39,    40,    41,   105,   106,
      46,    47,    93,   107,   108,   109,   110,    48,    63,    64,
      75,    76,    44,    45,    96,    98,   100,   170,   105,   194,
     146,   180,   180,     6,    21,    81,    90,    98,   130,   180,
      11,   132,    96,   145,    90,   145,    90,   180,    81,    96,
      89,    95,   194,    81,   121,    92,    90,    94,    82,   146,
     179,    89,    95,    90,    94,    90,    96,    76,   172,   202,
     203,   204,    99,    96,    96,    96,    96,   201,   145,   145,
     117,    90,    94,   201,   117,    96,   202,   187,    81,    96,
      82,    91,    91,   116,   147,   148,   149,    95,    82,    99,
      92,    94,   178,    95,    97,    92,    97,    96,    97,    98,
     100,   170,   147,    94,   178,   202,   179,   187,    99,    90,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,    31,   147,   152,   149,   153,   154,   155,
     156,   157,   158,   158,   159,   159,   159,   159,   159,   160,
     160,   161,   161,   162,   162,   162,   163,   168,   168,    65,
      66,    67,    83,    84,    87,    96,   166,   167,   172,   166,
      76,    82,   146,   148,   208,   209,   210,   146,    86,   173,
      23,    85,   205,    81,    96,    94,    97,    97,    96,    98,
     130,   189,   144,   179,     9,    90,    96,    12,   133,   180,
      90,    90,    97,    95,    82,    89,    94,   178,    91,   146,
      97,    97,   178,   147,   205,   190,   202,   172,    95,    97,
      94,   202,   202,   202,   202,    95,   200,    90,    90,    81,
     200,   202,    97,    89,    82,    97,    92,   115,    92,   115,
     146,    97,   183,    92,   146,   208,   146,    86,   173,    76,
     146,    99,    97,   178,   146,    95,    82,   146,   147,    97,
      94,    99,   106,    96,   202,   146,   116,   116,   180,   179,
       9,    90,    90,   178,   180,   144,    81,   117,    97,   117,
     146,    97,    84,    93,    81,    92,    92,    99,    96,   206,
      97,   205,   117,   204,    97,    97,    97,    97,   171,   117,
     117,    97,   117,    82,    97,    92,    92,    95,    97,    99,
     147,    70,    74,   149,    97,    97,    76,   210,   202,    97,
       5,    97,   178,   180,   144,   144,    99,    97,    90,    97,
      84,    89,    89,   205,    89,   117,   206,   117,   117,   117,
      96,   207,   117,    90,    97,   146,   117,   149,   147,    97,
     117,   116,    90,    99,    97,    90,    97,   116,   144,   117,
      84,    93,   147,    97,   147,   208,   117,   116,   144,   116,
      97,    84,    97,    97,   116,   116
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   113,   114,   115,   115,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   117,   117,   118,   118,
     118,   118,   119,   120,   121,   121,   121,   121,   121,   121,
     122,   122,   122,   122,   123,   124,   124,   125,   126,   127,
     128,   128,   129,   129,   129,   129,   129,   130,   130,   131,
     132,   132,   133,   133,   134,   134,   134,   134,   135,   135,
     136,   137,   138,   138,   138,   138,   139,   140,   141,   141,
     142,   143,   143,   144,   144,   145,   145,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   147,   147,   148,   148,   148,   148,   148,   148,
     149,   149,   150,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   155,   155,   156,   156,   157,   157,   157,   158,
     158,   158,   158,   158,   158,   159,   159,   159,   160,   160,
     160,   161,   161,   161,   161,   162,   162,   163,   163,   163,
     164,   164,   165,   165,   166,   166,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   168,   168,   168,   168,   168,
     168,   168,   169,   169,   169,   169,   169,   169,   170,   170,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   172,   172,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   174,
     174,   175,   175,   176,   177,   178,   178,   179,   179,   179,
     179,   180,   180,   181,   181,   181,   181,   182,   182,   183,
     183,   183,   183,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   185,   185,   185,   186,   187,   188,   188,   189,
     189,   190,   190,   190,   190,   190,   191,   191,   192,   192,
     192,   193,   194,   194,   195,   195,   195,   195,   195,   195,
     196,   196,   196,   197,   197,   198,   198,   199,   199,   200,
     200,   201,   201,   202,   202,   203,   203,   204,   204,   204,
     205,   205,   206,   206,   207,   207,   208,   208,   209,   209,
     209,   209,   210,   210,   210
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     2,     2,     3,     4,     4,
       5,     5,     1,     5,     1,     3,     4,     3,     5,     6,
       1,     1,     1,     1,     3,     5,     7,     5,     7,     5,
       3,     2,    10,     9,     8,     7,     8,     1,     4,     4,
       0,     5,     0,     2,     3,     4,     3,     4,     4,     2,
       3,     3,     2,     1,     4,     3,     4,     3,     1,     3,
       2,     0,     2,     0,     1,     0,     4,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     2,     2,     4,     3,     3,     4,
       1,     5,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     1,     3,     3,
       1,     1,     3,     3,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     2,     2,     2,     2,
       2,     2,     1,     2,     4,     3,     3,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     6,     3,     3,     3,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       4,     2,     5,     0,     4,     0,     1,     1,     2,     3,
       4,     1,     3,     1,     2,     3,     4,     1,     3,     5,
       3,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     2,     0,     3,     3,     3,     1,
       3,     1,     4,     3,     6,     6,     1,     1,     6,     6,
       7,     1,     0,     3,     5,     5,     6,     6,     6,     2,
       6,     6,     6,     1,     1,     5,     5,     3,     3,     0,
       3,     0,     3,     0,     1,     1,     3,     1,     4,     2,
       1,     1,     0,     3,     0,     3,     0,     1,     1,     2,
       3,     4,     1,     1,     1
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
#line 139 "src/kinx.y" /* yacc.c:1646  */
    { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[0].obj), kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
#line 2523 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 144 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2529 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 167 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2535 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 168 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2541 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 172 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2547 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 173 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2553 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 177 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2559 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 178 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2565 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 179 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2571 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 180 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2577 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 184 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2583 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 188 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2589 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 192 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2595 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 193 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2601 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 194 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2607 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 195 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2613 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 196 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2619 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 197 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2625 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 208 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2631 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 212 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2637 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 213 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2643 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 217 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2649 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 221 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2655 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 225 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2661 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 229 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2667 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 230 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2673 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 235 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2684 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 242 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2695 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 249 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2706 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 256 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 2712 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 258 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 2718 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 262 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 2724 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 263 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 2730 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 267 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2736 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 271 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2742 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 272 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2748 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 276 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2754 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 277 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2760 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 281 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2766 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 282 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2772 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 283 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2778 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 284 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2784 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 288 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2790 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 289 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); }
#line 2796 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 293 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_COROUTINE, (yyvsp[-1].obj), NULL, NULL); }
#line 2802 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 297 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2808 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 301 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2814 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 302 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2820 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 303 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2826 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 304 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2832 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 308 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2838 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 312 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2844 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 316 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2850 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 317 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2856 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 321 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2862 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 325 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2868 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 326 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2874 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 330 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2880 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 335 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2886 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 336 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2892 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 341 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2898 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 342 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2904 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 343 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2910 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 344 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2916 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 345 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2922 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 346 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2928 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 347 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2934 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 348 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2940 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 349 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2946 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 350 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2952 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 351 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2958 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 352 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2964 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 353 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2970 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 354 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2976 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 363 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2982 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 364 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2988 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 365 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2994 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 366 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3000 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 367 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3006 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 368 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3012 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 373 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3018 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 383 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3024 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 388 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3030 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 393 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3036 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 398 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3042 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 403 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3048 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 408 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3054 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 413 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3060 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 414 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3066 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 419 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3072 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 420 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3078 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 421 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3084 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 422 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3090 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 423 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3096 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 428 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3102 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 429 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3108 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 434 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3114 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 435 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3120 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 440 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3126 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 441 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3132 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 442 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3138 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 447 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3144 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 452 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3150 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 453 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3156 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 462 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 3162 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 463 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 3168 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 467 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3174 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 472 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3180 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 473 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3186 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 474 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3192 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 475 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3198 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 476 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3204 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 477 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3210 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 478 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3216 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 479 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3222 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 480 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3228 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 485 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 3234 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 3240 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 3246 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 488 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 3252 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 489 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 3258 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 490 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 3264 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 3270 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3276 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3282 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3288 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 499 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3294 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3300 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 504 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3306 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3312 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3318 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 510 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3324 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 511 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3330 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 512 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3336 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 513 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3342 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3348 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 519 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3354 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3360 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 521 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3366 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 522 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3372 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 523 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3378 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 524 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3384 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 525 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3390 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 529 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3396 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 530 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3402 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 534 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3408 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 535 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3414 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 536 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3420 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 537 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3426 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3432 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 539 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3438 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 540 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3444 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 541 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3450 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 542 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3456 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 543 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3462 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 544 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3468 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3474 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 546 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3480 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 547 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3486 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 548 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3492 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 549 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3498 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 550 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3504 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 551 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3510 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 552 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3516 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 553 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3522 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 554 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3528 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 555 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3534 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 556 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3540 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 557 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3546 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 558 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3552 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 559 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3558 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 560 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("yield"); }
#line 3564 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 561 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3570 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 562 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3576 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 563 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3582 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 564 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3588 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 565 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3594 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 566 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3600 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 567 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("=="); }
#line 3606 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 568 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("!="); }
#line 3612 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 569 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<="); }
#line 3618 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 570 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<"); }
#line 3624 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 571 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">="); }
#line 3630 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 572 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">"); }
#line 3636 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 573 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<=>"); }
#line 3642 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 574 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("+"); }
#line 3648 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 575 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("-"); }
#line 3654 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 576 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("*"); }
#line 3660 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 577 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("/"); }
#line 3666 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 578 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("%"); }
#line 3672 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 579 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("&"); }
#line 3678 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 580 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("|"); }
#line 3684 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 581 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("^"); }
#line 3690 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 582 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("[]"); }
#line 3696 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 586 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3702 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 587 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3708 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 591 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3714 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 592 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3720 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 596 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3726 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 600 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3732 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 604 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3738 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 610 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3744 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 611 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3750 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 612 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3756 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 617 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3762 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 622 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3768 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 623 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3774 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 624 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3780 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 629 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3786 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3792 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 634 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3798 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 635 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3804 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 636 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3810 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 640 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3816 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3822 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3828 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 643 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3834 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3840 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3846 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3852 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 647 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3858 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 648 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3864 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 649 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3870 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3876 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 651 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3882 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 652 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3888 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 653 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3894 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 654 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3900 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3906 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3912 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3918 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 658 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3924 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 659 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3930 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 660 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3936 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 661 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3942 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 662 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3948 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 663 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3954 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 664 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3960 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 665 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3966 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 666 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3972 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 667 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3978 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 668 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3984 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 669 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3990 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3996 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 671 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 4002 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 672 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 4008 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 673 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "=="; }
#line 4014 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 674 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "!="; }
#line 4020 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 675 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<="; }
#line 4026 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 676 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<"; }
#line 4032 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 677 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">="; }
#line 4038 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 678 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">"; }
#line 4044 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 679 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<=>"; }
#line 4050 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 680 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "+"; }
#line 4056 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 681 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "-"; }
#line 4062 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 682 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "*"; }
#line 4068 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 683 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "/"; }
#line 4074 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 684 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "%"; }
#line 4080 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 685 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "&"; }
#line 4086 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 686 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "|"; }
#line 4092 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 687 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "^"; }
#line 4098 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 688 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "[]"; }
#line 4104 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 692 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4110 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 693 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 4116 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 694 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4122 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 698 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 4128 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 702 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 4134 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 706 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4140 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 707 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 4146 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 712 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4152 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 716 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 4158 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 717 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 4164 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 718 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 4170 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 719 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 4176 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 720 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 4182 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 724 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4188 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 725 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4194 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 729 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4200 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 730 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4206 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 731 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4212 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 735 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 4218 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 739 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 4224 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 740 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4230 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 744 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4236 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 745 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4242 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 746 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4248 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 747 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 4254 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 748 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 4260 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 749 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 4266 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 753 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4272 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 754 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4278 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 755 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4284 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 764 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4290 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 765 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4296 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 769 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4302 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 770 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4308 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 774 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4314 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 776 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 4327 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 787 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4333 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 788 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4339 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 792 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4345 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 798 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4351 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 802 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4357 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 803 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 4363 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 804 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 4369 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 808 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 4375 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 809 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 4381 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 813 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 4387 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 814 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4393 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 818 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4399 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 819 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4405 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 823 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4411 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 829 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 4417 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 830 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 4423 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 831 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 4429 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 837 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 4435 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 4439 "kx.tab.c" /* yacc.c:1646  */
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
#line 840 "src/kinx.y" /* yacc.c:1906  */


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
