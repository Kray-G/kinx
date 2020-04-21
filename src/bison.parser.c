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
#define YYFINAL  340
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3830

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  94
/* YYNRULES -- Number of rules.  */
#define YYNRULES  376
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  724

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
       2,     2,     2,   112,     2,     2,     2,   110,   104,     2,
      96,    97,   108,   107,    94,    93,   100,   109,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    95,    90,
     105,    89,   106,   101,   113,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    98,     2,    99,   103,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,   102,    92,   111,     2,     2,     2,
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
       0,   135,   135,   139,   140,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   168,   169,   173,   174,
     175,   176,   180,   184,   188,   189,   190,   191,   192,   193,
     197,   198,   199,   200,   204,   208,   209,   213,   217,   221,
     225,   226,   230,   237,   244,   251,   253,   258,   259,   263,
     267,   268,   272,   273,   277,   278,   279,   280,   284,   285,
     289,   293,   297,   298,   299,   300,   304,   308,   312,   313,
     317,   321,   322,   326,   327,   331,   332,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   354,   355,   359,   360,   361,   362,   363,   364,
     368,   369,   373,   374,   378,   379,   383,   384,   388,   389,
     393,   394,   398,   399,   403,   404,   408,   409,   410,   414,
     415,   416,   417,   418,   419,   423,   424,   425,   429,   430,
     431,   435,   436,   437,   438,   442,   443,   447,   448,   449,
     450,   451,   452,   453,   457,   458,   459,   460,   461,   462,
     463,   464,   468,   469,   470,   471,   472,   473,   477,   478,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   503,   504,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     561,   562,   566,   567,   571,   575,   579,   580,   584,   585,
     586,   587,   591,   592,   596,   597,   598,   599,   603,   604,
     608,   609,   610,   611,   615,   616,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   668,   669,   670,   674,   678,   682,
     683,   687,   688,   692,   693,   694,   695,   696,   700,   701,
     705,   706,   707,   711,   715,   716,   720,   721,   722,   723,
     724,   725,   729,   730,   731,   735,   736,   740,   741,   745,
     746,   750,   751,   763,   764,   768,   769,   773,   774,   778,
     779,   780,   784,   785,   789,   790,   794,   795,   799,   800,
     804,   805,   806,   807,   811,   812,   813
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
  "'+'", "'*'", "'/'", "'%'", "'~'", "'!'", "'@'", "$accept", "Program",
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
      37,   126,    33,    64
};
# endif

#define YYPACT_NINF -455

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-455)))

#define YYTABLE_NINF -318

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1740,   -56,   -55,   -34,  1740,     2,    -8,    19,    20,     7,
    3413,    26,    37,  3463,    79,   -22,   -22,  -455,   -41,  2278,
    2278,  2278,    15,  3463,  3463,  3413,    55,    90,    92,    98,
     -31,    79,    79,  -455,  -455,  -455,  -455,    22,    57,   110,
     110,   -17,    70,  -455,  -455,  -455,  -455,   836,    79,  2976,
    2676,   -10,   -21,    79,  3663,  -455,  3663,  3663,  2385,   187,
     723,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,   192,  -455,
    -455,  -455,   146,  3741,  -455,  -455,   -19,   159,   197,   140,
     153,   165,   101,    28,   111,   -13,   -20,   196,   150,   188,
      85,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
     178,  -455,  -455,  -455,  -455,  -455,  3413,  3413,   283,  2726,
     949,   282,   198,   192,   205,   192,   206,  3413,   201,   203,
     207,  -455,  2171,  2164,   178,  -455,   221,  1850,  2271,    78,
    -455,  3026,    72,    84,  -455,    86,   208,    67,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,   209,   210,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
     211,   212,   214,   215,   192,   218,   192,  2271,    -8,  -455,
      96,   215,    -8,   217,    67,    85,    85,    57,   224,   232,
     247,  -455,  -455,   240,   241,  -455,  1740,   -55,   -34,  1062,
       2,    -8,    42,    45,     7,  3413,    79,   -22,   -22,   238,
     -41,  2278,  2278,  2278,    15,  3076,  3155,  3234,    55,   -31,
     239,   242,   243,    22,  3513,   244,   245,  -455,    79,  2776,
    2826,   -10,   -53,    79,  3663,   248,  1175,   251,  -455,   246,
      85,   249,  1957,  2057,    97,  3513,  -455,  2271,   253,    67,
    -455,  -455,  3026,    85,  -455,    57,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,   252,   236,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,   258,  -455,  3513,  3513,  3513,  3513,  3513,  3513,
    3513,  3513,  3513,  3513,  3513,  3513,  3513,  3313,  -455,  3663,
    3413,  3663,  3663,  3663,  3663,  3663,  3663,  3663,  3663,  3663,
    3663,  3663,  3663,  3663,  3663,  3663,  3663,  3663,  3663,  3663,
    3663,  3663,  3663,  3663,  3663,  -455,  -455,  2876,  3413,  2492,
    -455,     6,   -25,  2271,   -43,   128,   254,   -11,   327,  3463,
    2676,   342,   109,   257,   343,  3413,   264,  -455,   266,  -455,
     141,   263,   -45,  3513,  -455,   271,   270,   268,  -455,  -455,
    3563,   253,  3513,     6,  -455,   -22,  -455,    67,   126,   265,
     272,   274,  -455,  -455,  -455,    67,    67,    67,    67,   275,
     281,   284,  -455,  -455,   291,   275,  -455,    67,   276,  -455,
     286,   295,   285,  1288,  1401,  -455,  -455,   106,  -455,  1740,
     287,   290,  -455,  2171,   288,  3413,  -455,  -455,  -455,  2876,
    -455,  3413,  2599,  -455,  -455,  3363,   279,   289,   253,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  3413,  -455,   159,   292,
     197,   140,   153,   165,   101,    28,    28,   111,   111,   111,
     111,   111,   -13,   -13,   -20,   -20,   196,   196,   196,   150,
    -455,  -455,  -455,  -455,  3513,  -455,  2271,   106,   293,   294,
    -455,  1845,  -455,  -455,  -455,  -455,   273,   297,    67,  3413,
    1740,  1740,  3413,  3026,   372,   118,   299,   253,  3413,  3463,
     310,    -8,  -455,   163,  -455,  -455,    -8,  3413,   300,    -9,
     313,   307,  2064,  2271,   301,  -455,   305,  -455,   306,  -455,
       6,    -8,    67,   308,   309,   312,   314,    79,    -8,  -455,
    -455,  -455,    -8,   315,    -8,   320,   317,  -455,  -455,  1514,
    -455,  1627,  3728,   321,  -455,  -455,  2271,   322,  1952,  -455,
    -455,  3513,  2271,  -455,   334,   336,  2271,  3413,  -455,  -455,
    2926,  -455,  -455,    67,   323,  2271,   412,  -455,   168,   253,
    3413,  3463,  3463,   319,   181,   331,   325,  -455,  -455,  -455,
    2271,   321,  -455,   345,   337,  -455,  -455,   341,     6,   344,
      -8,   305,  -455,  -455,    -8,    -8,    -8,  -455,   335,  -455,
    -455,    -8,  -455,   346,   340,  -455,  -455,  3413,  -455,  -455,
    -455,  3613,  -455,  -455,  3513,  -455,   347,    -8,  1740,   348,
     333,   185,   349,   350,   425,  1740,  3463,    -8,  -455,    38,
    3513,   351,  3513,  -455,  -455,  -455,  -455,  -455,  2876,  -455,
    -455,  -455,  -455,  2271,  -455,  -455,  -455,    -8,  -455,  -455,
    -455,   341,  1740,  3463,  1740,  -455,   352,  -455,  -455,   359,
    -455,  -455,  -455,   353,  -455,  -455,   354,  -455,  1740,  -455,
    -455,  1740,  -455,  -455
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    85,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   333,     0,     0,
       0,     0,     0,    83,    83,    73,     0,     0,     0,     0,
       0,     0,     0,   317,   173,   175,   176,     0,     0,     0,
       0,     0,   188,   172,   170,   189,   171,     0,     0,     0,
       0,     0,   244,     0,     0,   317,     0,     0,     0,     0,
       0,     3,     5,     6,     7,    21,    23,     8,     9,    10,
      11,    12,    13,    14,    22,    15,    16,    17,    85,    18,
      19,    20,     0,    85,    87,   110,   113,   114,   116,   118,
     120,   122,   124,   126,   129,   135,   138,   141,   145,   147,
     154,   162,   174,   177,   178,   179,   180,    40,    41,   328,
     334,   112,   329,    42,    43,    25,     0,     0,     0,     0,
       0,    60,     0,    85,     0,    85,     0,     0,     0,     0,
       0,   188,     0,     0,   334,    51,     0,     0,   254,     0,
     185,     0,   323,     0,   321,     0,     0,   355,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   282,   283,   284,   285,   287,
     289,   288,   286,   281,   297,   298,   299,   301,   303,   290,
     291,   292,   293,   294,   345,   295,   296,   305,     0,     0,
     310,   311,   309,   300,   302,   304,   306,   307,   308,   346,
       0,     0,     0,   353,    85,    84,    85,    72,     0,    78,
       0,   353,     0,     0,   355,   160,   161,     0,     0,     0,
       0,   316,    32,     0,     0,    69,     0,   264,   266,     0,
     268,   269,    85,    85,   274,   275,   276,   277,   278,   333,
     280,   282,   283,   284,   285,    83,    83,    73,   286,   281,
     173,   175,   176,   293,     0,   188,   189,    26,   305,     0,
       0,   309,   244,   304,   306,   307,     0,   246,   258,     0,
     158,     0,     0,     0,     0,     0,   240,   248,   246,   355,
     341,   242,     0,   157,   159,     0,   155,   156,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   210,   211,   212,   213,
     215,   217,   216,   214,   209,   223,   224,   225,   227,   229,
     218,   219,   220,   221,   222,   190,   187,   231,     0,     0,
     236,   237,   235,   226,   228,   230,   232,   233,   234,   186,
       1,     4,     0,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   152,   168,   169,   368,     0,     0,
     163,     0,     0,   252,     0,     0,     0,     0,   188,    83,
       0,     0,     0,     0,    62,     0,     0,    64,     0,    66,
       0,     0,     0,     0,    50,     0,    34,   246,   255,    70,
       0,   246,     0,     0,   319,     0,   320,   355,     0,   359,
       0,   356,   357,   313,   312,   355,   355,   355,   355,   351,
       0,     0,   349,    77,     0,   351,   350,   355,     0,   315,
       0,     0,     0,     0,     0,    44,   263,   103,   102,     0,
       0,   240,    27,   247,     0,     0,   184,   104,   182,   368,
     183,     0,     0,   105,   249,   247,     0,     0,   246,   314,
     239,   238,    71,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,    89,    90,    75,    88,   115,     0,
     117,   119,   121,   123,   125,   127,   128,   131,   133,   134,
     130,   132,   136,   137,   140,   139,   142,   143,   144,   146,
     148,   149,   151,   153,     0,   376,   374,   375,     0,   369,
     370,     0,   166,   165,   363,   362,     0,     0,   355,     0,
       0,     0,     0,     0,     0,     0,     0,   246,     0,    83,
       0,     0,    59,     0,    65,    67,     0,     0,     0,     0,
     247,     0,     0,   256,     0,   325,   364,   322,     0,   361,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    68,
      76,    79,     0,     0,     0,     0,     0,   318,    28,     0,
      29,     0,   261,   184,   259,   245,   262,     0,     0,   108,
     107,     0,   250,   241,     0,     0,    74,     0,   371,   167,
       0,   164,   335,   355,     0,   253,    45,    47,     0,   246,
       0,    83,    83,     0,     0,     0,     0,    63,    86,    49,
     261,     0,    35,     0,    37,    33,   257,     0,     0,   324,
       0,   364,   336,   358,     0,     0,     0,   354,   366,   347,
     348,     0,   337,     0,     0,    30,    31,     0,   109,   106,
     251,     0,   243,   111,     0,   372,     0,     0,     0,     0,
       0,     0,     0,     0,   241,     0,    83,     0,    36,     0,
       0,     0,     0,   330,   360,   342,   343,   344,   368,   352,
     331,    24,   181,   260,   340,   339,   373,     0,   338,    46,
      48,    58,     0,    83,     0,    55,     0,    61,    38,     0,
     327,   365,   326,     0,   332,    56,     0,    54,     0,    39,
     367,     0,    53,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -455,  -455,    11,     4,    -3,  -455,   405,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,    49,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,   -23,    -6,     8,  -240,   -44,   -30,  -455,  -455,    93,
      94,    95,    99,   102,    91,   -93,  -151,   -82,   -95,   -91,
      81,   -18,    13,  -268,    -5,    63,  -370,  -455,  -455,  -455,
    -455,  -262,  -128,  -107,   445,  -455,     9,   -40,  -455,   435,
    -190,  -455,     1,    44,  -455,  -455,     0,   355,  -455,  -455,
       5,  -455,  -455,    25,   260,  -186,  -455,   -98,  -401,  -166,
    -455,  -454,  -455,  -134
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    59,   266,    61,    62,    63,   223,    64,   417,    65,
      66,    67,    68,    69,    70,    71,    72,   401,    73,   404,
     552,    74,    75,    76,    77,    78,    79,    80,   210,    81,
      82,   204,   124,    83,   497,   457,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   390,   101,   102,   339,   103,   104,   282,
     105,   464,   278,   394,   205,   267,   268,   199,   106,   285,
     221,   107,   143,   144,   108,   109,   134,   392,   111,   112,
     200,   113,   114,   578,   439,   430,   431,   432,   536,   639,
     689,   528,   529,   530
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     110,   206,   126,   121,   110,   274,   473,   269,   118,   140,
     395,    60,   402,   421,   456,   597,   476,   145,   133,   533,
     410,   138,   566,   122,   122,   201,   202,   449,   448,   534,
     359,   138,   138,   207,   115,   474,   284,   558,   286,   287,
     146,   116,  -300,   218,   215,   216,   122,   110,   280,   122,
     213,   539,   433,   281,   540,   147,   537,   273,   277,   131,
     110,   270,   117,    45,   341,   214,   283,   368,   369,   370,
     398,   538,   342,   225,    45,   632,   141,   358,   142,   142,
     375,   120,   360,   120,   633,   281,   279,   543,   377,   378,
     379,   535,   269,   477,   376,   479,   203,   269,   119,    14,
     123,   125,   600,   127,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   406,   219,   408,
     110,   135,   708,   123,   393,   393,   125,   393,   136,   385,
     386,   709,    33,   371,   372,   393,   208,  -272,   366,   367,
    -273,   385,   386,   428,    34,    35,    36,   130,   131,   277,
     385,   386,    45,   220,   478,   561,    38,   373,   374,   564,
     131,   422,    43,    44,    45,   226,    46,   423,   419,   641,
     132,   209,   420,   211,   424,    49,   426,    50,   425,   212,
     425,   387,   565,   388,    52,   389,   443,   340,    55,   473,
     444,   222,    58,   469,   470,   471,   122,   472,   440,   549,
     441,   361,   469,   539,   471,   442,   472,   131,   621,   446,
     429,    45,   425,   381,   382,   274,   605,   507,   508,   509,
     510,   511,   539,   206,   458,   541,   110,   126,   121,   110,
     455,   140,   269,   118,   713,   539,   343,   681,   556,   145,
     362,   568,   363,   133,   380,   458,   284,   201,   202,   573,
     574,   575,   576,   138,   138,   207,   364,   539,   280,   473,
     628,   583,   539,   383,   384,   669,   110,   273,   277,   365,
     341,   270,   547,   505,   506,   539,   283,   429,   675,   539,
     514,   515,   702,   391,   608,   623,   516,   517,   518,   396,
     277,   512,   513,   403,   405,   407,   409,   147,   553,   214,
     142,   142,   416,   219,   427,   450,   433,   435,   436,   434,
     437,   438,   420,   447,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   451,   452,
     499,   453,   454,  -279,  -290,   481,   -57,  -291,  -292,   459,
    -295,   465,   429,   527,  -317,   463,   466,   475,   482,   480,
     542,   548,   614,   550,   554,   551,   555,   670,   557,   559,
     570,   660,   560,   520,   521,   522,   523,   538,   572,   571,
     577,   579,   581,   584,   580,   585,   546,   586,   603,   612,
     595,   620,   587,   458,   593,  -312,   604,   607,   610,   622,
     609,   626,   458,   613,   634,   526,   531,   631,   545,   635,
     637,   638,   653,   640,   661,   644,   645,   138,   277,   646,
     662,   647,   651,   393,   654,   619,   657,   668,   674,   658,
     667,   676,   677,   269,   696,   527,   679,   666,   563,   678,
     680,   688,   701,   682,   -58,   618,   691,   692,   700,   703,
     710,   624,   712,   719,   697,   224,   544,   704,   711,   718,
     720,   721,   498,   110,   110,   500,   504,   501,   139,   110,
     142,   519,   502,   455,   589,   591,   503,   592,   217,   567,
     582,   445,   594,   596,   643,   684,   665,   526,     0,   598,
       0,     0,     0,   602,     0,     0,     0,     0,   142,   415,
     429,   569,     0,     0,   458,     0,     0,     0,   429,   429,
     429,   429,     0,     0,   606,     0,     0,     0,     0,     0,
     429,     0,     0,   671,     0,     0,     0,     0,     0,     0,
       0,     0,   269,     0,     0,     0,   625,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   110,     0,     0,   616,   617,     0,   615,   627,     0,
     393,   277,     0,   629,     0,     0,   393,   138,     0,     0,
       0,     0,     0,     0,     0,   630,   527,     0,   642,     0,
       0,   458,   648,     0,     0,   649,     0,   663,     0,   650,
       0,   652,     0,     0,     0,     0,   358,     0,     0,   110,
       0,   110,     0,   341,     0,   341,     0,     0,   672,   673,
       0,   429,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   526,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   393,   138,
     138,   695,     0,     0,   458,   429,     0,   683,     0,     0,
       0,   685,   686,   687,   527,     0,     0,     0,   690,     0,
     458,     0,   458,   706,     0,     0,     0,     0,   694,     0,
       0,     0,     0,     0,   698,   693,     0,     0,   110,     0,
       0,     0,   699,     0,   707,   110,   429,     0,     0,   705,
     716,     0,     0,     0,   138,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   714,     0,   526,     0,     0,     0,
       0,     0,   110,     0,   110,     0,   715,     0,   717,     0,
       0,   138,     0,     0,     0,     0,     0,     0,   110,     0,
       0,   110,   722,    -2,     1,   723,     0,     2,     0,     3,
       4,     5,     0,     6,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,    42,     0,    43,    44,    45,     0,
      46,     0,     0,   -81,    47,     0,    48,     0,     0,    49,
       0,    50,     0,     0,     0,     0,     0,    51,    52,     0,
      53,    54,    55,     0,    56,    57,    58,     1,     0,     0,
     227,   149,   228,   229,   230,     0,   231,   154,   155,   232,
     233,   234,   235,    11,    12,    13,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,    27,
      28,    29,   249,   174,   175,   176,   177,   178,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,   251,   252,   253,   183,     0,     0,     0,     0,
       0,     0,   254,    38,    39,    40,    41,   255,     0,    43,
      44,   256,   186,    46,     0,     0,   -81,    47,   257,   258,
       0,     0,   259,     0,   260,     0,     0,     0,   190,   191,
     261,   262,   194,   263,   264,   265,   198,    56,    57,    58,
       1,     0,     0,     2,     0,     3,     4,     5,     0,     6,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
      42,     0,    43,    44,    45,     0,    46,     0,     0,   -81,
      47,   257,    48,     0,     0,    49,     0,    50,     0,     0,
       0,     0,     0,    51,    52,     0,    53,    54,    55,     0,
      56,    57,    58,     1,     0,     0,     2,     0,     3,     4,
       5,     0,     6,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,    38,
      39,    40,    41,    42,     0,    43,    44,    45,     0,    46,
       0,     0,   -81,    47,     0,    48,     0,  -267,    49,     0,
      50,     0,     0,     0,     0,     0,    51,    52,     0,    53,
      54,    55,     0,    56,    57,    58,     1,     0,     0,     2,
       0,     3,     4,     5,     0,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,    42,     0,    43,    44,
      45,     0,    46,     0,     0,   -81,    47,   462,    48,     0,
       0,    49,     0,    50,     0,     0,     0,     0,     0,    51,
      52,     0,    53,    54,    55,     0,    56,    57,    58,     1,
       0,     0,     2,     0,     3,     4,     5,     0,     6,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    38,    39,    40,    41,    42,
       0,    43,    44,    45,     0,    46,     0,     0,   -81,    47,
     588,    48,     0,     0,    49,     0,    50,     0,     0,     0,
       0,     0,    51,    52,     0,    53,    54,    55,     0,    56,
      57,    58,     1,     0,     0,     2,     0,     3,     4,     5,
       0,     6,     0,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    42,     0,    43,    44,    45,     0,    46,     0,
       0,   -81,    47,   590,    48,     0,     0,    49,     0,    50,
       0,     0,     0,     0,     0,    51,    52,     0,    53,    54,
      55,     0,    56,    57,    58,     1,     0,     0,     2,     0,
       3,     4,     5,     0,     6,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,    38,    39,    40,    41,    42,     0,    43,    44,    45,
       0,    46,     0,     0,   -81,    47,   655,    48,     0,     0,
      49,     0,    50,     0,     0,     0,     0,     0,    51,    52,
       0,    53,    54,    55,     0,    56,    57,    58,     1,     0,
       0,     2,     0,     3,     4,     5,     0,     6,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,     0,     0,   -81,    47,   656,
      48,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,     0,    56,    57,
      58,     1,     0,     0,     2,     0,     3,     4,     5,     0,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,    38,    39,    40,
      41,    42,     0,    43,    44,    45,     0,    46,     0,     0,
     -81,    47,     0,    48,     0,     0,    49,     0,    50,     0,
       0,     0,     0,     0,    51,    52,     0,    53,    54,    55,
       0,    56,    57,    58,   148,   149,   150,   151,   152,     0,
     153,   154,   155,   156,   157,   158,   159,     0,     0,     0,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,     0,   173,   174,   175,   176,
     177,   178,     0,     0,     0,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   181,   182,   183,
       0,     0,     0,     0,     0,     0,   254,     0,     0,     0,
       0,   411,     0,     0,   413,   185,   186,     0,     0,     0,
       0,     0,   418,   187,   611,     0,   412,     0,   189,     0,
       0,     0,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   148,   149,   150,   151,   152,     0,   153,   154,   155,
     156,   157,   158,   159,     0,     0,     0,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     0,     0,   173,   174,   175,   176,   177,   178,     0,
       0,     0,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,     0,     0,     0,     0,     0,
       0,     0,   179,   180,   181,   182,   183,     0,     0,     0,
       0,     0,     0,   254,     0,     0,     0,     0,   411,     0,
       0,   413,   185,   186,     0,     0,     0,     0,     0,   467,
     187,   659,     0,   412,     0,   189,     0,     0,     0,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   148,   149,
     150,   151,   152,     0,   153,   154,   155,   156,   157,   158,
     159,     0,     0,     0,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
     173,   174,   175,   176,   177,   178,     0,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
     180,   181,   182,   183,     0,     0,     0,     0,     0,     0,
     254,     0,     0,     0,     0,   411,   413,     0,     0,   185,
     186,     0,     0,     0,   468,     0,   636,   187,     0,     0,
     412,     0,   189,     0,     0,     0,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   148,   149,   150,   151,   152,
       0,   153,   154,   155,   156,   157,   158,   159,     0,     0,
       0,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,     0,     0,   173,   174,   175,
     176,   177,   178,     0,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,   180,   181,   182,
     183,     0,     0,     0,     0,     0,     0,   254,     0,     0,
       0,     0,   411,   413,     0,     0,   185,   186,     0,   414,
       0,     0,     0,     0,   187,     0,     0,   412,     0,   189,
       0,     0,     0,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   148,   149,   150,   151,   152,     0,   153,   154,
     155,   156,   157,   158,   159,     0,     0,     0,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,   173,   174,   175,   176,   177,   178,
       0,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,   180,   181,   182,   183,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   184,
     413,     0,     0,   185,   186,     0,     0,     0,     0,     0,
       0,   187,     0,     0,   188,     0,   189,     0,     0,     0,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   288,
     289,   290,   291,   292,     0,   293,   294,   295,   296,   297,
     298,   299,   300,     0,     0,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,     0,     0,
       0,   314,   315,   316,   317,   318,   319,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     320,   321,   322,   323,   324,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   325,     0,     0,     0,
       0,   326,     0,     0,     0,     0,     0,     0,   327,     0,
       0,   328,     0,   329,     0,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   288,   289,   290,   291,
     292,     0,   293,   294,   295,   296,   297,   298,   299,   300,
       0,     0,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,     0,     0,     0,   314,   315,
     316,   317,   318,   319,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   320,   321,   322,
     323,   324,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   325,     0,     0,     0,     0,   532,     0,
       0,     0,     0,     0,     0,   327,     0,     0,   328,     0,
     329,     0,     0,     0,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   288,   289,   290,   291,   292,     0,   293,
     294,   295,   296,   297,   298,   299,   300,     0,     0,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,     0,     0,     0,   314,   315,   316,   317,   318,
     319,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   320,   321,   322,   323,   324,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     325,     0,     0,     0,     0,   599,     0,     0,     0,     0,
       0,     0,   327,     0,     0,   328,    14,   329,     0,    17,
     128,   330,   331,   332,   333,   334,   335,   336,   337,   338,
       0,     0,   129,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,   130,     0,    14,   397,     0,    17,
     128,     0,   275,    38,     0,     0,     0,   131,     0,    43,
      44,    45,   129,    46,     0,     0,     0,   132,     0,    48,
      31,    32,    49,     0,    50,   276,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,    58,
       0,    34,    35,    36,   130,     0,    14,     0,     0,    17,
     128,     0,     0,    38,     0,     0,     0,   398,     0,    43,
      44,    45,   129,    46,     0,     0,   399,   132,     0,    48,
      31,    32,    49,     0,   400,     0,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,    58,
       0,    34,    35,    36,   130,     0,    14,     0,     0,    17,
     128,     0,     0,    38,     0,     0,     0,   131,   460,    43,
      44,    45,   129,    46,     0,     0,     0,   272,     0,    48,
      31,    32,    49,   433,    50,     0,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,    58,
       0,    34,    35,    36,   130,     0,    14,     0,     0,    17,
     128,     0,   275,    38,     0,     0,     0,   131,     0,    43,
      44,    45,   129,    46,     0,     0,     0,   132,     0,    48,
      31,    32,    49,     0,    50,   461,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,    58,
       0,    34,    35,    36,   130,     0,    14,     0,     0,    17,
     128,     0,   524,    38,     0,     0,     0,   131,   525,    43,
      44,    45,   129,    46,     0,     0,     0,   272,     0,    48,
      31,    32,    49,     0,    50,     0,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,    58,
       0,    34,    35,    36,   130,     0,    14,     0,     0,    17,
     128,     0,   664,    38,     0,     0,     0,   131,   525,    43,
      44,    45,   129,    46,     0,     0,     0,   272,     0,    48,
      31,    32,    49,     0,    50,     0,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,    58,
       0,    34,    35,    36,   130,     0,    14,     0,     0,    17,
     128,     0,     0,    38,     0,     0,     0,   131,   271,    43,
      44,    45,   129,    46,     0,     0,     0,   272,     0,    48,
      31,    32,    49,     0,    50,     0,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,    58,
       0,    34,    35,    36,   130,     0,    14,     0,     0,    17,
     128,     0,   275,    38,     0,     0,     0,   131,     0,    43,
      44,    45,   129,    46,     0,     0,     0,   132,     0,    48,
      31,    32,    49,     0,    50,     0,     0,     0,     0,    33,
      51,    52,     0,    53,    54,    55,     0,    56,    57,    58,
       0,    34,    35,    36,   130,     0,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,   131,     0,    43,
      44,    45,     0,    46,     0,     0,     0,   137,     0,    48,
       0,  -287,    49,     0,    50,    14,     0,     0,    17,   128,
      51,    52,     0,    53,    54,    55,     0,    56,    57,    58,
       0,   129,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,   130,     0,     0,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,   131,     0,    43,    44,
      45,     0,    46,     0,     0,     0,   137,     0,    48,     0,
    -289,    49,     0,    50,    14,     0,     0,    17,   128,    51,
      52,     0,    53,    54,    55,     0,    56,    57,    58,     0,
     129,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,   130,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,   131,     0,    43,    44,    45,
       0,    46,     0,     0,     0,   132,     0,    48,     0,  -288,
      49,     0,    50,    14,     0,     0,    17,   128,    51,    52,
       0,    53,    54,    55,   496,    56,    57,    58,     0,   129,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,   130,     0,    14,     0,     0,    17,   128,     0,     0,
      38,     0,     0,     0,   131,     0,    43,    44,    45,   129,
      46,     0,     0,     0,   272,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,    58,     0,    34,    35,
      36,   130,     0,    14,     0,     0,    17,   128,     0,   601,
      38,     0,     0,     0,   131,     0,    43,    44,    45,   129,
      46,     0,     0,     0,   132,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,    58,     0,    34,    35,
      36,   130,     0,    14,     0,     0,    17,   128,     0,     0,
      38,     0,     0,     0,   131,     0,    43,    44,    45,   129,
      46,     0,     0,     0,   132,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,    58,     0,    34,    35,
      36,   130,     0,    14,     0,     0,    17,   128,     0,     0,
      38,     0,     0,     0,   131,     0,    43,    44,    45,   129,
      46,     0,     0,     0,   137,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,    58,     0,    34,    35,
      36,   130,     0,    14,     0,     0,    17,   128,     0,     0,
      38,     0,     0,     0,   131,     0,    43,    44,    45,   129,
      46,     0,     0,     0,   272,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,    58,     0,    34,    35,
      36,   130,     0,    14,     0,     0,    17,   128,     0,     0,
      38,     0,     0,     0,   131,     0,    43,    44,    45,   129,
      46,     0,     0,     0,   562,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,    58,     0,    34,    35,
      36,   130,     0,    14,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,   131,     0,    43,    44,    45,     0,
      46,     0,     0,     0,    47,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,    58,     0,    34,    35,
      36,   130,   122,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,   131,   122,    43,    44,    45,     0,
      46,     0,     0,     0,   132,     0,    48,     0,     0,    49,
       0,    50,     0,     0,     0,     0,     0,     0,    52,     0,
      53,    54,    55,     0,    56,    57,    58,     0,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   357,   -85,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     357
};

static const yytype_int16 yycheck[] =
{
       0,    24,     8,     6,     4,    49,   274,    47,     4,    14,
     117,     0,   119,   141,   254,   469,   278,    16,    10,   389,
     127,    13,   423,     4,     4,    20,    21,   217,   214,    23,
      49,    23,    24,    25,    90,   275,    54,    82,    56,    57,
      81,    96,    95,    21,    31,    32,     4,    47,    51,     4,
      81,    94,    97,   106,    97,    96,    81,    49,    50,    81,
      60,    48,    96,    85,    60,    96,    53,    39,    40,    41,
      81,    96,    78,    90,    85,    84,    98,    83,    15,    16,
      93,    91,   101,    91,    93,   106,    96,    98,   108,   109,
     110,    85,   132,   279,   107,   285,    81,   137,    96,    20,
      81,    81,   472,    96,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   123,    96,   125,
     120,    95,    84,    81,   116,   117,    81,   119,    91,    44,
      45,    93,    53,   105,   106,   127,    81,    95,    37,    38,
      95,    44,    45,    76,    65,    66,    67,    68,    81,   141,
      44,    45,    85,    96,   282,   417,    77,    46,    47,   421,
      81,    89,    83,    84,    85,    95,    87,    95,    90,   570,
      91,    81,    94,    81,    90,    96,    90,    98,    94,    81,
      94,    96,   422,    98,   105,   100,    90,     0,   109,   457,
      94,    81,   113,    96,    97,    98,     4,   100,   204,    90,
     206,    42,    96,    94,    98,   208,   100,    81,    90,   212,
     147,    85,    94,    63,    64,   259,   478,   368,   369,   370,
     371,   372,    94,   246,   254,    97,   226,   233,   231,   229,
     226,   236,   272,   229,   688,    94,    90,   638,    97,   238,
      43,   427,   102,   235,    48,   275,   264,   242,   243,   435,
     436,   437,   438,   245,   246,   247,   103,    94,   261,   527,
      97,   447,    94,    75,    76,    97,   266,   259,   260,   104,
     266,   258,   400,   366,   367,    94,   263,   214,    97,    94,
     375,   376,    97,   105,   524,   547,   377,   378,   379,     6,
     282,   373,   374,    11,    96,    90,    90,    96,   405,    96,
     237,   238,    81,    96,    96,    81,    97,    96,    96,    99,
      96,    96,    94,    96,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,    96,    82,
     360,    91,    91,    95,    95,    99,     9,    95,    95,    95,
      95,    95,   279,   387,    96,    94,    97,    94,    90,    97,
      96,     9,   538,    96,    90,    12,    90,   619,    95,    89,
      95,   601,    94,   381,   382,   383,   384,    96,    94,    97,
      95,    90,    81,    97,    90,    89,   399,    82,    99,   106,
      92,     9,    97,   413,    97,    95,    97,    95,    94,    90,
      97,    81,   422,    96,    81,   387,   388,    97,   397,    92,
      99,    96,    82,    97,    70,    97,    97,   399,   400,    97,
      74,    97,    97,   405,    97,   543,    95,     5,    99,    97,
      97,    90,    97,   463,   664,   469,    89,   613,   420,    84,
      89,    96,    99,    89,     9,   542,    90,    97,    90,    90,
     680,   548,   682,    84,    97,    40,   397,    97,    97,    97,
      97,    97,   359,   453,   454,   361,   365,   362,    13,   459,
     397,   380,   363,   459,   453,   454,   364,   459,    33,   425,
     445,   211,   463,   465,   572,   641,   610,   469,    -1,   471,
      -1,    -1,    -1,   475,    -1,    -1,    -1,    -1,   425,   134,
     427,   428,    -1,    -1,   524,    -1,    -1,    -1,   435,   436,
     437,   438,    -1,    -1,   496,    -1,    -1,    -1,    -1,    -1,
     447,    -1,    -1,   620,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   562,    -1,    -1,    -1,   549,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     540,   541,    -1,    -1,   540,   541,    -1,   539,   551,    -1,
     542,   543,    -1,   556,    -1,    -1,   548,   549,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   557,   610,    -1,   571,    -1,
      -1,   601,   577,    -1,    -1,   578,    -1,   607,    -1,   582,
      -1,   584,    -1,    -1,    -1,    -1,   592,    -1,    -1,   589,
      -1,   591,    -1,   589,    -1,   591,    -1,    -1,   621,   622,
      -1,   538,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   610,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   620,   621,
     622,   661,    -1,    -1,   664,   572,    -1,   640,    -1,    -1,
      -1,   644,   645,   646,   688,    -1,    -1,    -1,   651,    -1,
     680,    -1,   682,   676,    -1,    -1,    -1,    -1,   661,    -1,
      -1,    -1,    -1,    -1,   667,   657,    -1,    -1,   668,    -1,
      -1,    -1,   668,    -1,   677,   675,   613,    -1,    -1,   675,
     703,    -1,    -1,    -1,   676,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   697,    -1,   688,    -1,    -1,    -1,
      -1,    -1,   702,    -1,   704,    -1,   702,    -1,   704,    -1,
      -1,   703,    -1,    -1,    -1,    -1,    -1,    -1,   718,    -1,
      -1,   721,   718,     0,     1,   721,    -1,     4,    -1,     6,
       7,     8,    -1,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    -1,    83,    84,    85,    -1,
      87,    -1,    -1,    90,    91,    -1,    93,    -1,    -1,    96,
      -1,    98,    -1,    -1,    -1,    -1,    -1,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,     1,    -1,    -1,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    -1,    83,
      84,    85,    86,    87,    -1,    -1,    90,    91,    92,    93,
      -1,    -1,    96,    -1,    98,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       1,    -1,    -1,     4,    -1,     6,     7,     8,    -1,    10,
      -1,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,
      81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,    90,
      91,    92,    93,    -1,    -1,    96,    -1,    98,    -1,    -1,
      -1,    -1,    -1,   104,   105,    -1,   107,   108,   109,    -1,
     111,   112,   113,     1,    -1,    -1,     4,    -1,     6,     7,
       8,    -1,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,    81,    -1,    83,    84,    85,    -1,    87,
      -1,    -1,    90,    91,    -1,    93,    -1,    95,    96,    -1,
      98,    -1,    -1,    -1,    -1,    -1,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,   113,     1,    -1,    -1,     4,
      -1,     6,     7,     8,    -1,    10,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    -1,    83,    84,
      85,    -1,    87,    -1,    -1,    90,    91,    92,    93,    -1,
      -1,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,   113,     1,
      -1,    -1,     4,    -1,     6,     7,     8,    -1,    10,    -1,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      -1,    83,    84,    85,    -1,    87,    -1,    -1,    90,    91,
      92,    93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,
      -1,    -1,   104,   105,    -1,   107,   108,   109,    -1,   111,
     112,   113,     1,    -1,    -1,     4,    -1,     6,     7,     8,
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
     109,    -1,   111,   112,   113,     1,    -1,    -1,     4,    -1,
       6,     7,     8,    -1,    10,    -1,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    78,    79,    80,    81,    -1,    83,    84,    85,
      -1,    87,    -1,    -1,    90,    91,    92,    93,    -1,    -1,
      96,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,   113,     1,    -1,
      -1,     4,    -1,     6,     7,     8,    -1,    10,    -1,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,    -1,
      83,    84,    85,    -1,    87,    -1,    -1,    90,    91,    92,
      93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,
      -1,   104,   105,    -1,   107,   108,   109,    -1,   111,   112,
     113,     1,    -1,    -1,     4,    -1,     6,     7,     8,    -1,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,
      80,    81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,
      90,    91,    -1,    93,    -1,    -1,    96,    -1,    98,    -1,
      -1,    -1,    -1,    -1,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,   113,     4,     5,     6,     7,     8,    -1,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    89,    85,    86,    -1,    -1,    -1,
      -1,    -1,    92,    93,    99,    -1,    96,    -1,    98,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    89,    85,    86,    -1,    -1,    -1,    -1,    -1,    92,
      93,    99,    -1,    96,    -1,    98,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    81,    89,    -1,    -1,    85,
      86,    -1,    -1,    -1,    97,    -1,    92,    93,    -1,    -1,
      96,    -1,    98,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     4,     5,     6,     7,     8,
      -1,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    81,    89,    -1,    -1,    85,    86,    -1,    95,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    96,    -1,    98,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      89,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,
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
      -1,    96,    -1,    98,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    96,    -1,
      98,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,     4,     5,     6,     7,     8,    -1,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    96,    20,    98,    -1,    23,
      24,   102,   103,   104,   105,   106,   107,   108,   109,   110,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    20,    21,    -1,    23,
      24,    -1,    76,    77,    -1,    -1,    -1,    81,    -1,    83,
      84,    85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,
      44,    45,    96,    -1,    98,    99,    -1,    -1,    -1,    53,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,    65,    66,    67,    68,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,
      84,    85,    36,    87,    -1,    -1,    90,    91,    -1,    93,
      44,    45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,    65,    66,    67,    68,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    77,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,
      44,    45,    96,    97,    98,    -1,    -1,    -1,    -1,    53,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,    65,    66,    67,    68,    -1,    20,    -1,    -1,    23,
      24,    -1,    76,    77,    -1,    -1,    -1,    81,    -1,    83,
      84,    85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,
      44,    45,    96,    -1,    98,    99,    -1,    -1,    -1,    53,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,    65,    66,    67,    68,    -1,    20,    -1,    -1,    23,
      24,    -1,    76,    77,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,
      44,    45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,    65,    66,    67,    68,    -1,    20,    -1,    -1,    23,
      24,    -1,    76,    77,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,
      44,    45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,    65,    66,    67,    68,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    77,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,
      44,    45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,    65,    66,    67,    68,    -1,    20,    -1,    -1,    23,
      24,    -1,    76,    77,    -1,    -1,    -1,    81,    -1,    83,
      84,    85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,
      44,    45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,
      84,    85,    -1,    87,    -1,    -1,    -1,    91,    -1,    93,
      -1,    95,    96,    -1,    98,    20,    -1,    -1,    23,    24,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    -1,    87,    -1,    -1,    -1,    91,    -1,    93,    -1,
      95,    96,    -1,    98,    20,    -1,    -1,    23,    24,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,   113,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      -1,    87,    -1,    -1,    -1,    91,    -1,    93,    -1,    95,
      96,    -1,    98,    20,    -1,    -1,    23,    24,   104,   105,
      -1,   107,   108,   109,    31,   111,   112,   113,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    76,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    -1,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,    65,    66,
      67,    68,     4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    81,     4,    83,    84,    85,    -1,
      87,    -1,    -1,    -1,    91,    -1,    93,    -1,    -1,    96,
      -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89
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
      98,   104,   105,   107,   108,   109,   111,   112,   113,   115,
     116,   117,   118,   119,   121,   123,   124,   125,   126,   127,
     128,   129,   130,   132,   135,   136,   137,   138,   139,   140,
     141,   143,   144,   147,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   168,   169,   171,   172,   174,   182,   185,   188,   189,
     190,   192,   193,   195,   196,    90,    96,    96,   117,    96,
      91,   118,     4,    81,   146,    81,   146,    96,    24,    36,
      68,    81,    91,   147,   190,    95,    91,    91,   147,   178,
     168,    98,   169,   186,   187,   186,    81,    96,     4,     5,
       6,     7,     8,    10,    11,    12,    13,    14,    15,    16,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    36,    37,    38,    39,    40,    41,    65,
      66,    67,    68,    69,    81,    85,    86,    93,    96,    98,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   181,
     194,   194,   194,    81,   145,   178,   145,   147,    81,    81,
     142,    81,    81,    81,    96,   166,   166,   183,    21,    96,
      96,   184,    81,   120,   120,    90,    95,     4,     6,     7,
       8,    10,    13,    14,    15,    16,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    36,
      65,    66,    67,    68,    76,    81,    85,    92,    93,    96,
      98,   104,   105,   107,   108,   109,   116,   179,   180,   181,
     166,    82,    91,   147,   149,    76,    99,   147,   176,    96,
     118,   106,   173,   166,   165,   183,   165,   165,     4,     5,
       6,     7,     8,    10,    11,    12,    13,    14,    15,    16,
      17,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    36,    37,    38,    39,    40,    41,
      65,    66,    67,    68,    69,    81,    86,    93,    96,    98,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   170,
       0,   117,   146,    90,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    89,   146,    49,
     101,    42,    43,   102,   103,   104,    37,    38,    39,    40,
      41,   105,   106,    46,    47,    93,   107,   108,   109,   110,
      48,    63,    64,    75,    76,    44,    45,    96,    98,   100,
     167,   105,   191,   147,   177,   177,     6,    21,    81,    90,
      98,   131,   177,    11,   133,    96,   146,    90,   146,    90,
     177,    81,    96,    89,    95,   191,    81,   122,    92,    90,
      94,   176,    89,    95,    90,    94,    90,    96,    76,   169,
     199,   200,   201,    97,    99,    96,    96,    96,    96,   198,
     146,   146,   118,    90,    94,   198,   118,    96,   199,   184,
      81,    96,    82,    91,    91,   117,   148,   149,   150,    95,
      82,    99,    92,    94,   175,    95,    97,    92,    97,    96,
      97,    98,   100,   167,   148,    94,   175,   199,   176,   184,
      97,    99,    90,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,    31,   148,   153,   150,
     154,   155,   156,   157,   158,   159,   159,   160,   160,   160,
     160,   160,   161,   161,   162,   162,   163,   163,   163,   164,
     165,   165,   165,   165,    76,    82,   147,   149,   205,   206,
     207,   147,    86,   170,    23,    85,   202,    81,    96,    94,
      97,    97,    96,    98,   131,   186,   145,   176,     9,    90,
      96,    12,   134,   177,    90,    90,    97,    95,    82,    89,
      94,   175,    91,   147,   175,   148,   202,   187,   199,   169,
      95,    97,    94,   199,   199,   199,   199,    95,   197,    90,
      90,    81,   197,   199,    97,    89,    82,    97,    92,   116,
      92,   116,   147,    97,   180,    92,   147,   205,   147,    86,
     170,    76,   147,    99,    97,   175,   147,    95,   148,    97,
      94,    99,   106,    96,   199,   147,   117,   117,   177,   176,
       9,    90,    90,   175,   177,   145,    81,   118,    97,   118,
     147,    97,    84,    93,    81,    92,    92,    99,    96,   203,
      97,   202,   118,   201,    97,    97,    97,    97,   168,   118,
     118,    97,   118,    82,    97,    92,    92,    95,    97,    99,
     148,    70,    74,   150,    76,   207,   199,    97,     5,    97,
     175,   177,   145,   145,    99,    97,    90,    97,    84,    89,
      89,   202,    89,   118,   203,   118,   118,   118,    96,   204,
     118,    90,    97,   147,   118,   150,   148,    97,   118,   117,
      90,    99,    97,    90,    97,   117,   145,   118,    84,    93,
     148,    97,   148,   205,   118,   117,   145,   117,    97,    84,
      97,    97,   117,   117
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   115,   116,   116,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   118,   118,   119,   119,
     119,   119,   120,   121,   122,   122,   122,   122,   122,   122,
     123,   123,   123,   123,   124,   125,   125,   126,   127,   128,
     129,   129,   130,   130,   130,   130,   130,   131,   131,   132,
     133,   133,   134,   134,   135,   135,   135,   135,   136,   136,
     137,   138,   139,   139,   139,   139,   140,   141,   142,   142,
     143,   144,   144,   145,   145,   146,   146,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   148,   148,   149,   149,   149,   149,   149,   149,
     150,   150,   151,   151,   152,   152,   153,   153,   154,   154,
     155,   155,   156,   156,   157,   157,   158,   158,   158,   159,
     159,   159,   159,   159,   159,   160,   160,   160,   161,   161,
     161,   162,   162,   162,   162,   163,   163,   164,   164,   164,
     164,   164,   164,   164,   165,   165,   165,   165,   165,   165,
     165,   165,   166,   166,   166,   166,   166,   166,   167,   167,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   169,   169,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     171,   171,   172,   172,   173,   174,   175,   175,   176,   176,
     176,   176,   177,   177,   178,   178,   178,   178,   179,   179,
     180,   180,   180,   180,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   182,   182,   182,   183,   184,   185,
     185,   186,   186,   187,   187,   187,   187,   187,   188,   188,
     189,   189,   189,   190,   191,   191,   192,   192,   192,   192,
     192,   192,   193,   193,   193,   194,   194,   195,   195,   196,
     196,   197,   197,   198,   198,   199,   199,   200,   200,   201,
     201,   201,   202,   202,   203,   203,   204,   204,   205,   205,
     206,   206,   206,   206,   207,   207,   207
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
       2,     3,     2,     3,     1,     2,     2,     2,     2,     2,
       2,     2,     1,     2,     4,     3,     3,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     6,     3,     3,     3,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     4,     2,     5,     0,     4,     0,     1,     1,     2,
       3,     4,     1,     3,     1,     2,     3,     4,     1,     3,
       5,     3,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     3,     2,     0,     3,     3,
       3,     1,     3,     1,     4,     3,     6,     6,     1,     1,
       6,     6,     7,     1,     0,     3,     5,     5,     6,     6,
       6,     2,     6,     6,     6,     1,     1,     5,     5,     3,
       3,     0,     3,     0,     3,     0,     1,     1,     3,     1,
       4,     2,     1,     1,     0,     3,     0,     3,     0,     1,
       1,     2,     3,     4,     1,     1,     1
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
#line 135 "src/kinx.y" /* yacc.c:1646  */
    { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[0].obj), kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
#line 2479 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 140 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2485 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 163 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2491 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 164 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2497 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 168 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2503 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 169 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2509 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 173 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2515 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 174 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2521 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 175 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2527 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 176 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2533 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 180 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2539 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 184 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2545 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 188 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2551 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 189 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2557 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 190 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2563 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 191 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2569 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 192 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2575 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 193 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2581 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 204 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2587 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 208 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2593 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 209 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2599 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 213 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2605 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 217 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2611 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 221 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2617 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 225 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2623 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 226 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2629 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 231 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2640 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 238 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2651 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 245 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2662 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 252 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 2668 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 254 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 2674 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 258 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 2680 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 259 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 2686 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 263 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2692 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 267 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2698 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 268 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2704 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 272 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2710 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 273 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2716 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 277 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2722 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 278 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2728 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 279 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2734 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 280 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2740 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 284 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2746 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 285 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); }
#line 2752 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 289 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_COROUTINE, (yyvsp[-1].obj), NULL, NULL); }
#line 2758 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 293 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2764 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 297 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2770 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 298 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2776 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 299 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2782 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 300 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2788 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 304 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2794 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 308 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2800 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 312 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2806 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 313 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2812 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 317 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2818 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 321 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2824 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 322 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2830 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 326 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2836 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 331 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2842 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 332 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2848 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 337 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2854 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 338 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2860 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 339 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2866 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 340 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2872 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 341 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2878 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 342 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2884 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 343 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2890 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 344 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2896 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 345 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2902 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 346 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2908 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 347 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2914 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 348 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2920 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 349 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2926 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 350 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2932 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 359 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2938 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 360 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2944 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 361 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2950 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 362 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2956 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 363 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2962 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 364 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2968 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 369 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2974 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 379 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2980 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 384 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2986 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 389 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2992 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 394 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2998 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 399 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3004 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 404 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3010 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 409 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3016 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 410 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3022 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 415 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3028 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 416 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3034 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 417 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3040 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 418 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3046 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 419 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3052 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 424 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3058 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 425 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3064 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 430 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3070 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 431 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3076 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 436 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3082 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 437 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3088 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 438 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3094 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 443 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3100 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 448 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3106 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 449 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3112 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 450 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-1].obj), kx_gen_special_object(KXVL_NULL), 0); }
#line 3118 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 451 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 3124 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 452 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-1].obj), kx_gen_special_object(KXVL_NULL), 1); }
#line 3130 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 453 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 3136 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 458 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_BNOT, (yyvsp[0].obj)); }
#line 3142 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 459 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 3148 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 460 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 3154 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 461 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 3160 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 462 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 3166 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 463 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 3172 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 464 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 3178 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 469 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 3184 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 470 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3190 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 471 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3196 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 472 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3202 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 473 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3208 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 477 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3214 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 478 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3220 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 482 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3226 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 483 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3232 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 484 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3238 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 485 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3244 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3250 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3256 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 488 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3262 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 493 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3268 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 494 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3274 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3280 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3286 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3292 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3298 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 499 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3304 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3310 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 504 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3316 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3322 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3328 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 510 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3334 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 511 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3340 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 512 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3346 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 513 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3352 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3358 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 515 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3364 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 516 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3370 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 517 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3376 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 518 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3382 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 519 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3388 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3394 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 521 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3400 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 522 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3406 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 523 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3412 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 524 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3418 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 525 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3424 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 526 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3430 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 527 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3436 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 528 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3442 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 529 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3448 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 530 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3454 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 531 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3460 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 532 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3466 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 533 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3472 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 534 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("yield"); }
#line 3478 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 535 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3484 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 536 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3490 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 537 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3496 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3502 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 539 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3508 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 540 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3514 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 541 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("=="); }
#line 3520 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 542 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("!="); }
#line 3526 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 543 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<="); }
#line 3532 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 544 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<"); }
#line 3538 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">="); }
#line 3544 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 546 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">"); }
#line 3550 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 547 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<=>"); }
#line 3556 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 548 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("+"); }
#line 3562 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 549 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("-"); }
#line 3568 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 550 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("*"); }
#line 3574 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 551 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("/"); }
#line 3580 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 552 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("%"); }
#line 3586 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 553 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("&"); }
#line 3592 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 554 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("|"); }
#line 3598 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 555 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("^"); }
#line 3604 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 556 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("[]"); }
#line 3610 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 557 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("()"); }
#line 3616 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 561 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3622 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 562 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3628 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 566 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3634 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 567 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3640 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 571 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3646 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 575 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3652 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 579 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3658 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 585 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3664 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 586 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3670 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 587 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3676 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 592 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3682 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 597 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3688 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 598 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3694 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 599 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3700 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 604 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3706 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 608 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3712 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3718 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 610 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3724 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 611 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3730 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 615 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3736 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 616 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3742 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 617 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3748 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 618 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3754 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 619 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3760 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 620 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3766 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 621 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3772 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 622 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3778 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 623 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3784 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 624 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3790 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 625 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3796 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 626 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3802 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 627 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3808 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 628 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3814 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 629 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3820 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 630 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3826 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 631 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3832 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 632 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3838 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3844 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 634 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3850 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 635 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3856 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 636 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3862 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 637 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3868 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 638 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3874 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 639 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3880 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 640 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3886 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3892 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3898 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 643 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3904 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3910 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3916 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3922 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 647 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3928 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 648 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "=="; }
#line 3934 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 649 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "!="; }
#line 3940 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<="; }
#line 3946 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 651 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<"; }
#line 3952 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 652 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">="; }
#line 3958 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 653 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">"; }
#line 3964 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 654 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<=>"; }
#line 3970 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "+"; }
#line 3976 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "-"; }
#line 3982 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "*"; }
#line 3988 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 658 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "/"; }
#line 3994 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 659 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "%"; }
#line 4000 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 660 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "&"; }
#line 4006 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 661 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "|"; }
#line 4012 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 662 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "^"; }
#line 4018 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 663 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "[]"; }
#line 4024 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 664 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "()"; }
#line 4030 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 668 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4036 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 669 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 4042 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4048 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 674 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 4054 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 678 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 4060 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 682 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4066 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 683 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 4072 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 688 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4078 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 692 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 4084 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 693 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 4090 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 694 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 4096 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 695 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 4102 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 696 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 4108 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 700 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4114 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 701 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4120 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 705 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4126 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 706 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4132 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 707 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4138 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 711 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 4144 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 715 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 4150 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 716 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4156 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 720 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4162 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 721 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4168 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 722 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4174 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 723 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 4180 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 724 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 4186 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 725 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 4192 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 729 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4198 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 730 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4204 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 731 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4210 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 740 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4216 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 741 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4222 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 745 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4228 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 746 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4234 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 750 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4240 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 752 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 4253 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 763 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4259 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 764 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4265 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 768 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4271 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 774 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4277 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 778 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4283 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 779 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 4289 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 780 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 4295 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 784 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 4301 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 785 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 4307 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 789 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 4313 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 790 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4319 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 794 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4325 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 795 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4331 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 799 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4337 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 805 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 4343 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 806 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 4349 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 807 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 4355 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 813 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 4361 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 4365 "kx.tab.c" /* yacc.c:1646  */
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
#line 816 "src/kinx.y" /* yacc.c:1906  */


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
