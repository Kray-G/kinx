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
#define YYFINAL  338
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3735

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  94
/* YYNRULES -- Number of rules.  */
#define YYNRULES  375
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  722

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
     463,   467,   468,   469,   470,   471,   472,   476,   477,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   502,   503,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   560,
     561,   565,   566,   570,   574,   578,   579,   583,   584,   585,
     586,   590,   591,   595,   596,   597,   598,   602,   603,   607,
     608,   609,   610,   614,   615,   616,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   667,   668,   669,   673,   677,   681,   682,
     686,   687,   691,   692,   693,   694,   695,   699,   700,   704,
     705,   706,   710,   714,   715,   719,   720,   721,   722,   723,
     724,   728,   729,   730,   734,   735,   739,   740,   744,   745,
     749,   750,   762,   763,   767,   768,   772,   773,   777,   778,
     779,   783,   784,   788,   789,   793,   794,   798,   799,   803,
     804,   805,   806,   810,   811,   812
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

#define YYPACT_NINF -454

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-454)))

#define YYTABLE_NINF -317

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1705,   -38,   -72,   -24,  1705,    26,   -47,    22,    24,    40,
    3373,    25,    53,  3423,    44,   -36,   -36,  -454,   -46,  2242,
    2242,  2242,    34,  3423,  3423,  3373,    65,    76,   120,   124,
     -43,    44,    44,  -454,  -454,  -454,  -454,    21,   113,   130,
     130,    17,   118,  -454,  -454,  -454,  -454,   830,    44,  2940,
    2640,    98,   131,    44,  3623,  -454,  3623,  2349,   207,   721,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,   237,  -454,  -454,
    -454,   161,  1807,  -454,  -454,   -12,   214,   215,   169,   160,
     176,    46,    27,    48,   -32,   175,   239,   110,   170,   174,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,   191,
    -454,  -454,  -454,  -454,  -454,  3373,  3373,   299,  2690,   942,
     297,   230,   237,   221,   237,   240,  3373,   231,   233,   235,
    -454,  2135,  2235,   191,  -454,   251,  1814,  2342,   -13,  -454,
    2990,    -7,    12,  -454,    14,   238,    69,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,   236,   241,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,   243,
     247,   248,   249,   237,   242,   237,  2342,   -47,  -454,    81,
     249,   -47,   250,    69,   174,   174,   113,   254,   252,   255,
    -454,  -454,   256,   258,  -454,  1705,   -72,   -24,  1051,    26,
     -47,    18,    19,    40,  3373,    44,   -36,   -36,   257,   -46,
    2242,  2242,  2242,    34,  3040,  3117,  3194,    65,   -43,   259,
     260,   261,    21,  3473,   262,   263,  -454,    44,  2740,  2790,
      98,   -52,    44,  3623,   267,  1160,   270,  -454,   271,   174,
     268,  1921,  2128,    41,  3473,  -454,  2342,   273,    69,  -454,
    -454,  2990,   174,  -454,   113,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,   272,   269,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
     280,  -454,  3473,  3473,  3473,  3473,  3473,  3473,  3473,  3473,
    3473,  3473,  3473,  3473,  3473,  3273,  -454,  3623,  3373,  3623,
    3623,  3623,  3623,  3623,  3623,  3623,  3623,  3623,  3623,  3623,
    3623,  3623,  3623,  3623,  3623,  3623,  3623,  3623,  3623,  3623,
    3623,  3623,  3623,  -454,  -454,  2840,  3373,  2456,  -454,    16,
     -26,  2342,    96,   106,   275,   -25,   342,  3423,  2640,   363,
     101,   277,   364,  3373,   285,  -454,   287,  -454,   123,   283,
      -4,  3473,  -454,   284,   290,   288,  -454,  -454,  3523,   273,
    3473,    16,  -454,   -36,  -454,    69,   111,   289,   286,   291,
    -454,  -454,  -454,    69,    69,    69,    69,   292,   296,   298,
    -454,  -454,   308,   292,  -454,    69,   294,  -454,   303,   313,
     300,  1269,  1378,  -454,  -454,   190,  -454,  1705,   301,   304,
    -454,  2135,   309,  3373,  -454,  -454,  -454,  2840,  -454,  3373,
    2563,  -454,  -454,  3323,   305,   306,   273,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  3373,  -454,   214,   307,   215,   169,
     160,   176,    46,    27,    27,    48,    48,    48,    48,    48,
     -32,   -32,   175,   175,   239,   239,   239,   110,  -454,  -454,
    -454,  -454,  3473,  -454,  2342,   190,   311,   315,  -454,  1916,
    -454,  -454,  -454,  -454,   310,   314,    69,  3373,  1705,  1705,
    3373,  2990,   391,   112,   322,   273,  3373,  3423,   332,   -47,
    -454,   127,  -454,  -454,   -47,  3373,   317,   -19,   336,   326,
    2028,  2342,   320,  -454,   324,  -454,   325,  -454,    16,   -47,
      69,   327,   330,   331,   333,    44,   -47,  -454,  -454,  -454,
     -47,   334,   -47,   347,   335,  -454,  -454,  1487,  -454,  1596,
     126,   338,  -454,  -454,  2342,   339,  2023,  -454,  -454,  3473,
    2342,  -454,   365,   367,  2342,  3373,  -454,  -454,  2890,  -454,
    -454,    69,   340,  2342,   433,  -454,   179,   273,  3373,  3423,
    3423,   343,   181,   349,   346,  -454,  -454,  -454,  2342,   338,
    -454,   360,   356,  -454,  -454,   357,    16,   358,   -47,   324,
    -454,  -454,   -47,   -47,   -47,  -454,   352,  -454,  -454,   -47,
    -454,   359,   353,  -454,  -454,  3373,  -454,  -454,  -454,  3573,
    -454,  -454,  3473,  -454,   361,   -47,  1705,   366,   354,   185,
     370,   369,   445,  1705,  3423,   -47,  -454,    59,  3473,   371,
    3473,  -454,  -454,  -454,  -454,  -454,  2840,  -454,  -454,  -454,
    -454,  2342,  -454,  -454,  -454,   -47,  -454,  -454,  -454,   357,
    1705,  3423,  1705,  -454,   372,  -454,  -454,   380,  -454,  -454,
    -454,   373,  -454,  -454,   375,  -454,  1705,  -454,  -454,  1705,
    -454,  -454
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    85,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   332,     0,     0,
       0,     0,     0,    83,    83,    73,     0,     0,     0,     0,
       0,     0,     0,   316,   172,   174,   175,     0,     0,     0,
       0,     0,   187,   171,   169,   188,   170,     0,     0,     0,
       0,     0,   243,     0,     0,   316,     0,     0,     0,     0,
       3,     5,     6,     7,    21,    23,     8,     9,    10,    11,
      12,    13,    14,    22,    15,    16,    17,    85,    18,    19,
      20,     0,    85,    87,   110,   113,   114,   116,   118,   120,
     122,   124,   126,   129,   135,   138,   141,   145,   147,   154,
     161,   173,   176,   177,   178,   179,    40,    41,   327,   333,
     112,   328,    42,    43,    25,     0,     0,     0,     0,     0,
      60,     0,    85,     0,    85,     0,     0,     0,     0,     0,
     187,     0,     0,   333,    51,     0,     0,   253,     0,   184,
       0,   322,     0,   320,     0,     0,   354,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   281,   282,   283,   284,   286,   288,
     287,   285,   280,   296,   297,   298,   300,   302,   289,   290,
     291,   292,   293,   344,   294,   295,   304,     0,     0,   309,
     310,   308,   299,   301,   303,   305,   306,   307,   345,     0,
       0,     0,   352,    85,    84,    85,    72,     0,    78,     0,
     352,     0,     0,   354,   159,   160,     0,     0,     0,     0,
     315,    32,     0,     0,    69,     0,   263,   265,     0,   267,
     268,    85,    85,   273,   274,   275,   276,   277,   332,   279,
     281,   282,   283,   284,    83,    83,    73,   285,   280,   172,
     174,   175,   292,     0,   187,   188,    26,   304,     0,     0,
     308,   243,   303,   305,   306,     0,   245,   257,     0,   157,
       0,     0,     0,     0,     0,   239,   247,   245,   354,   340,
     241,     0,   156,   158,     0,   155,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   209,   210,   211,   212,   214,   216,
     215,   213,   208,   222,   223,   224,   226,   228,   217,   218,
     219,   220,   221,   189,   186,   230,     0,     0,   235,   236,
     234,   225,   227,   229,   231,   232,   233,   185,     1,     4,
       0,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,   152,   167,   168,   367,     0,     0,   162,     0,
       0,   251,     0,     0,     0,     0,   187,    83,     0,     0,
       0,     0,    62,     0,     0,    64,     0,    66,     0,     0,
       0,     0,    50,     0,    34,   245,   254,    70,     0,   245,
       0,     0,   318,     0,   319,   354,     0,   358,     0,   355,
     356,   312,   311,   354,   354,   354,   354,   350,     0,     0,
     348,    77,     0,   350,   349,   354,     0,   314,     0,     0,
       0,     0,     0,    44,   262,   103,   102,     0,     0,   239,
      27,   246,     0,     0,   183,   104,   181,   367,   182,     0,
       0,   105,   248,   246,     0,     0,   245,   313,   238,   237,
      71,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,    89,    90,    75,    88,   115,     0,   117,   119,
     121,   123,   125,   127,   128,   131,   133,   134,   130,   132,
     136,   137,   140,   139,   142,   143,   144,   146,   148,   149,
     151,   153,     0,   375,   373,   374,     0,   368,   369,     0,
     165,   164,   362,   361,     0,     0,   354,     0,     0,     0,
       0,     0,     0,     0,     0,   245,     0,    83,     0,     0,
      59,     0,    65,    67,     0,     0,     0,     0,   246,     0,
       0,   255,     0,   324,   363,   321,     0,   360,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,    76,    79,
       0,     0,     0,     0,     0,   317,    28,     0,    29,     0,
     260,   183,   258,   244,   261,     0,     0,   108,   107,     0,
     249,   240,     0,     0,    74,     0,   370,   166,     0,   163,
     334,   354,     0,   252,    45,    47,     0,   245,     0,    83,
      83,     0,     0,     0,     0,    63,    86,    49,   260,     0,
      35,     0,    37,    33,   256,     0,     0,   323,     0,   363,
     335,   357,     0,     0,     0,   353,   365,   346,   347,     0,
     336,     0,     0,    30,    31,     0,   109,   106,   250,     0,
     242,   111,     0,   371,     0,     0,     0,     0,     0,     0,
       0,     0,   240,     0,    83,     0,    36,     0,     0,     0,
       0,   329,   359,   341,   342,   343,   367,   351,   330,    24,
     180,   259,   339,   338,   372,     0,   337,    46,    48,    58,
       0,    83,     0,    55,     0,    61,    38,     0,   326,   364,
     325,     0,   331,    56,     0,    54,     0,    39,   366,     0,
      53,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -454,  -454,    11,     4,    -3,  -454,   415,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,    72,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,   -23,    -6,     8,  -184,   -44,   -30,  -454,  -454,   116,
     115,   119,   121,   114,   117,   -66,   -75,   -65,   -64,   -73,
     105,   -20,    -2,  -257,    -5,    64,  -372,  -454,  -454,  -454,
    -454,  -264,  -134,  -106,   471,  -454,    30,   -40,  -454,   452,
    -197,  -454,     1,    63,  -454,  -454,     0,   355,  -454,  -454,
      20,  -454,  -454,    50,   293,  -186,  -454,   -69,  -396,  -144,
    -454,  -453,  -454,  -104
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    58,   265,    60,    61,    62,   222,    63,   415,    64,
      65,    66,    67,    68,    69,    70,    71,   399,    72,   402,
     550,    73,    74,    75,    76,    77,    78,    79,   209,    80,
      81,   203,   123,    82,   495,   455,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   388,   100,   101,   337,   102,   103,   281,
     104,   462,   277,   392,   204,   266,   267,   198,   105,   284,
     220,   106,   142,   143,   107,   108,   133,   390,   110,   111,
     199,   112,   113,   576,   437,   428,   429,   430,   534,   637,
     687,   526,   527,   528
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     109,   205,   125,   120,   109,   273,   419,   268,   117,   139,
     393,    59,   400,   474,   595,   531,   471,   144,   132,   447,
     408,   137,   121,   121,   115,   564,   121,   446,   121,   214,
     215,   137,   137,   206,   283,   145,   285,   357,   212,   532,
     200,   201,   217,  -299,   119,   130,   269,   109,   279,    45,
     146,   282,   114,   213,   280,   535,   396,   272,   276,   109,
      45,   373,   140,   339,    14,   630,   366,   367,   368,   454,
     536,   340,   116,   541,   631,   374,   356,   417,   556,   141,
     141,   418,   420,   364,   365,   383,   384,   477,   421,   358,
     472,   268,   475,   431,   371,   372,   268,    33,   598,   122,
     124,   533,   422,   122,   424,   124,   423,   224,   423,    34,
      35,    36,   129,  -271,  -272,   202,   404,   218,   406,   109,
     134,    38,   118,   391,   391,   130,   391,    43,    44,    45,
     121,    46,   369,   370,   391,   131,   126,   467,   468,   469,
      49,   470,    50,   706,   135,   426,   207,   476,   276,    52,
     130,   559,   707,    55,    45,   562,    57,   208,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     493,   441,   639,   379,   380,   442,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   119,
     537,   547,   130,   538,   278,   537,    45,   438,   471,   439,
     537,   210,   619,   539,   440,   211,   423,   338,   444,   219,
     427,   221,   603,   225,   273,   355,   -85,   537,   383,   384,
     554,   537,   205,   456,   626,   109,   125,   120,   109,   453,
     139,   268,   117,   711,   383,   384,   563,   280,   144,   566,
     679,   121,   132,   283,   456,   381,   382,   571,   572,   573,
     574,   341,   137,   137,   206,   269,   359,   279,   360,   581,
     282,   200,   201,   362,   545,   109,   272,   276,   471,   339,
     385,   361,   386,   537,   387,   537,   667,   427,   673,   537,
     363,   621,   700,   375,   376,   377,   467,   378,   469,   276,
     470,   505,   506,   507,   508,   509,   389,   551,   503,   504,
     141,   141,   514,   515,   516,   394,   510,   511,   401,   512,
     513,   405,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   403,   146,   497,   213,
     407,   218,   414,   431,   425,   448,   418,   450,   606,   433,
     432,   525,   427,   434,   435,   436,   445,   451,   449,   452,
     612,   -57,  -278,   668,  -289,  -290,  -291,   457,  -294,   518,
     519,   520,   521,  -316,   461,   464,   463,   473,   479,   478,
     480,   540,   546,   548,   544,   552,   549,   553,   555,   557,
     536,   456,   558,   569,   568,   570,   577,   575,   578,   579,
     456,   582,   583,   524,   529,   584,   543,   585,   591,  -311,
     618,   593,   605,   602,   601,   137,   276,   617,   607,   608,
     611,   391,   620,   624,   629,   658,   610,   632,   633,   635,
     636,   268,   638,   525,   642,   664,   561,   643,   644,   651,
     645,   649,   652,   655,   616,   659,   656,   665,   666,   674,
     622,   660,   672,   675,   676,   677,   678,   680,   686,   689,
     690,   109,   109,   699,   -58,   223,   698,   109,   695,   141,
     701,   453,   587,   589,   717,   590,   702,   542,   709,   716,
     718,   594,   719,   496,   498,   524,   501,   596,   694,   499,
     502,   600,   500,   517,   138,   216,   565,   141,   413,   427,
     567,   592,   456,   580,   708,   682,   710,   427,   427,   427,
     427,   641,   604,   443,   663,     0,     0,     0,     0,   427,
       0,     0,   669,     0,     0,     0,     0,     0,     0,     0,
     268,     0,     0,     0,   623,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   109,   109,
       0,     0,   614,   615,     0,   613,   625,     0,   391,   276,
       0,   627,     0,     0,   391,   137,     0,     0,     0,     0,
       0,     0,     0,   628,   525,     0,   640,     0,     0,   456,
     646,     0,     0,   647,     0,   661,     0,   648,     0,   650,
       0,     0,     0,     0,   356,     0,     0,   109,     0,   109,
       0,   339,     0,   339,     0,     0,   670,   671,     0,     0,
     427,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   524,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   391,   137,   137,   693,
       0,     0,   456,     0,   427,   681,     0,     0,     0,   683,
     684,   685,   525,     0,     0,     0,   688,     0,   456,     0,
     456,   704,     0,     0,     0,     0,   692,     0,     0,     0,
       0,     0,   696,   691,     0,     0,   109,     0,     0,     0,
     697,     0,   705,   109,     0,   427,     0,   703,   714,     0,
       0,     0,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   712,     0,   524,     0,     0,     0,     0,     0,
     109,     0,   109,     0,   713,     0,   715,     0,     0,   137,
       0,     0,     0,     0,     0,     0,   109,     0,     0,   109,
     720,    -2,     1,   721,     0,     2,     0,     3,     4,     5,
       0,     6,     0,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    42,     0,    43,    44,    45,     0,    46,     0,
       0,   -81,    47,     0,    48,     0,     0,    49,     0,    50,
       0,     0,     0,     0,     0,    51,    52,     0,    53,    54,
      55,     1,    56,    57,   226,   148,   227,   228,   229,     0,
     230,   153,   154,   231,   232,   233,   234,    11,    12,    13,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,    27,    28,    29,   248,   173,   174,   175,
     176,   177,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   249,   250,   251,   252,   182,
       0,     0,     0,     0,     0,     0,   253,    38,    39,    40,
      41,   254,     0,    43,    44,   255,   185,    46,     0,     0,
     -81,    47,   256,   257,     0,     0,   258,     0,   259,     0,
       0,     0,   189,   190,   260,   261,   193,   262,   263,   264,
     197,    56,    57,     1,     0,     0,     2,     0,     3,     4,
       5,     0,     6,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,    38,
      39,    40,    41,    42,     0,    43,    44,    45,     0,    46,
       0,     0,   -81,    47,   256,    48,     0,     0,    49,     0,
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
       0,   -81,    47,     0,    48,     0,  -266,    49,     0,    50,
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
     -81,    47,   460,    48,     0,     0,    49,     0,    50,     0,
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
      47,   586,    48,     0,     0,    49,     0,    50,     0,     0,
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
     588,    48,     0,     0,    49,     0,    50,     0,     0,     0,
       0,     0,    51,    52,     0,    53,    54,    55,     1,    56,
      57,     2,     0,     3,     4,     5,     0,     6,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,     0,     0,   -81,    47,   653,
      48,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,     1,    56,    57,
       2,     0,     3,     4,     5,     0,     6,     0,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,    38,    39,    40,    41,    42,     0,    43,
      44,    45,     0,    46,     0,     0,   -81,    47,   654,    48,
       0,     0,    49,     0,    50,     0,     0,     0,     0,     0,
      51,    52,     0,    53,    54,    55,     1,    56,    57,     2,
       0,     3,     4,     5,     0,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,    42,     0,    43,    44,
      45,     0,    46,     0,     0,   -81,    47,     0,    48,     0,
       0,    49,     0,    50,     0,     0,     0,     0,     0,    51,
      52,   121,    53,    54,    55,     0,    56,    57,   147,   148,
     149,   150,   151,     0,   152,   153,   154,   155,   156,   157,
     158,     0,     0,     0,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,     0,     0,     0,
     172,   173,   174,   175,   176,   177,     0,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   178,
     179,   180,   181,   182,     0,     0,     0,     0,     0,     0,
     253,     0,     0,     0,     0,   409,   355,     0,     0,   184,
     185,     0,     0,     0,     0,     0,   416,   186,     0,     0,
     410,     0,   188,     0,     0,     0,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   147,   148,   149,   150,   151,
       0,   152,   153,   154,   155,   156,   157,   158,     0,     0,
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,     0,     0,     0,   172,   173,   174,
     175,   176,   177,     0,     0,     0,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,     0,
       0,     0,     0,     0,     0,     0,   178,   179,   180,   181,
     182,     0,     0,     0,     0,     0,     0,   253,     0,     0,
       0,     0,   409,     0,     0,   411,   184,   185,     0,     0,
       0,     0,     0,   465,   186,   609,     0,   410,     0,   188,
       0,     0,     0,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   147,   148,   149,   150,   151,     0,   152,   153,
     154,   155,   156,   157,   158,     0,     0,     0,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,     0,     0,     0,   172,   173,   174,   175,   176,   177,
       0,     0,     0,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,     0,     0,     0,     0,
       0,     0,     0,   178,   179,   180,   181,   182,     0,     0,
       0,     0,     0,     0,   253,     0,     0,     0,     0,   409,
       0,     0,   411,   184,   185,     0,     0,     0,     0,     0,
     634,   186,   657,     0,   410,     0,   188,     0,     0,     0,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   147,
     148,   149,   150,   151,     0,   152,   153,   154,   155,   156,
     157,   158,     0,     0,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,     0,     0,
       0,   172,   173,   174,   175,   176,   177,     0,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     178,   179,   180,   181,   182,     0,     0,     0,     0,     0,
       0,   253,     0,     0,     0,     0,   409,   411,     0,     0,
     184,   185,     0,     0,     0,   466,     0,     0,   186,     0,
       0,   410,     0,   188,     0,     0,     0,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   147,   148,   149,   150,
     151,     0,   152,   153,   154,   155,   156,   157,   158,     0,
       0,     0,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,     0,     0,     0,   172,   173,
     174,   175,   176,   177,     0,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   178,   179,   180,
     181,   182,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   183,   411,     0,     0,   184,   185,     0,
     412,     0,     0,     0,     0,   186,     0,     0,   187,     0,
     188,     0,     0,     0,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   286,   287,   288,   289,   290,     0,   291,
     292,   293,   294,   295,   296,   297,   298,     0,     0,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,     0,     0,     0,   312,   313,   314,   315,   316,
     317,     0,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   318,   319,   320,   321,   322,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     323,   411,     0,     0,     0,   324,     0,     0,     0,     0,
       0,     0,   325,     0,     0,   326,     0,   327,     0,     0,
       0,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     286,   287,   288,   289,   290,     0,   291,   292,   293,   294,
     295,   296,   297,   298,     0,     0,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,     0,
       0,     0,   312,   313,   314,   315,   316,   317,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   318,   319,   320,   321,   322,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   323,     0,     0,
       0,     0,   530,     0,     0,     0,     0,     0,     0,   325,
       0,     0,   326,     0,   327,     0,     0,     0,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   286,   287,   288,
     289,   290,     0,   291,   292,   293,   294,   295,   296,   297,
     298,     0,     0,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,     0,     0,     0,   312,
     313,   314,   315,   316,   317,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   318,   319,
     320,   321,   322,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   323,     0,     0,     0,     0,   597,
       0,     0,     0,     0,     0,     0,   325,     0,     0,   326,
      14,   327,     0,    17,   127,   328,   329,   330,   331,   332,
     333,   334,   335,   336,     0,     0,   128,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,   129,     0,
      14,   395,     0,    17,   127,     0,   274,    38,     0,     0,
       0,   130,     0,    43,    44,    45,   128,    46,     0,     0,
       0,   131,     0,    48,    31,    32,    49,     0,    50,   275,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
      14,     0,     0,    17,   127,     0,     0,    38,     0,     0,
       0,   396,     0,    43,    44,    45,   128,    46,     0,     0,
     397,   131,     0,    48,    31,    32,    49,     0,   398,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
      14,     0,     0,    17,   127,     0,     0,    38,     0,     0,
       0,   130,   458,    43,    44,    45,   128,    46,     0,     0,
       0,   271,     0,    48,    31,    32,    49,   431,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
      14,     0,     0,    17,   127,     0,   274,    38,     0,     0,
       0,   130,     0,    43,    44,    45,   128,    46,     0,     0,
       0,   131,     0,    48,    31,    32,    49,     0,    50,   459,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
      14,     0,     0,    17,   127,     0,   522,    38,     0,     0,
       0,   130,   523,    43,    44,    45,   128,    46,     0,     0,
       0,   271,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
      14,     0,     0,    17,   127,     0,   662,    38,     0,     0,
       0,   130,   523,    43,    44,    45,   128,    46,     0,     0,
       0,   271,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
      14,     0,     0,    17,   127,     0,     0,    38,     0,     0,
       0,   130,   270,    43,    44,    45,   128,    46,     0,     0,
       0,   271,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
      14,     0,     0,    17,   127,     0,   274,    38,     0,     0,
       0,   130,     0,    43,    44,    45,   128,    46,     0,     0,
       0,   131,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   129,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,   130,     0,    43,    44,    45,     0,    46,     0,     0,
       0,   136,     0,    48,     0,  -286,    49,    14,    50,     0,
      17,   127,     0,     0,    51,    52,     0,    53,    54,    55,
       0,    56,    57,   128,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,   129,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,   130,     0,
      43,    44,    45,     0,    46,     0,     0,     0,   136,     0,
      48,     0,  -288,    49,    14,    50,     0,    17,   127,     0,
       0,    51,    52,     0,    53,    54,    55,     0,    56,    57,
     128,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,   129,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,   130,     0,    43,    44,    45,
       0,    46,     0,     0,     0,   131,     0,    48,     0,  -287,
      49,     0,    50,    14,     0,     0,    17,   127,    51,    52,
       0,    53,    54,    55,   494,    56,    57,     0,     0,   128,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,   129,     0,    14,     0,     0,    17,   127,     0,     0,
      38,     0,     0,     0,   130,     0,    43,    44,    45,   128,
      46,     0,     0,     0,   271,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   129,     0,    14,     0,     0,    17,   127,     0,   599,
      38,     0,     0,     0,   130,     0,    43,    44,    45,   128,
      46,     0,     0,     0,   131,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   129,     0,    14,     0,     0,    17,   127,     0,     0,
      38,     0,     0,     0,   130,     0,    43,    44,    45,   128,
      46,     0,     0,     0,   131,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   129,     0,    14,     0,     0,    17,   127,     0,     0,
      38,     0,     0,     0,   130,     0,    43,    44,    45,   128,
      46,     0,     0,     0,   136,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   129,     0,    14,     0,     0,    17,   127,     0,     0,
      38,     0,     0,     0,   130,     0,    43,    44,    45,   128,
      46,     0,     0,     0,   271,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   129,     0,    14,     0,     0,    17,   127,     0,     0,
      38,     0,     0,     0,   130,     0,    43,    44,    45,   128,
      46,     0,     0,     0,   560,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   129,     0,    14,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,   130,     0,    43,    44,    45,     0,
      46,     0,     0,     0,    47,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   129,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,   130,     0,    43,    44,    45,     0,
      46,     0,     0,     0,   131,     0,    48,     0,     0,    49,
       0,    50,     0,     0,     0,     0,     0,     0,    52,     0,
      53,    54,    55,     0,    56,    57
};

static const yytype_int16 yycheck[] =
{
       0,    24,     8,     6,     4,    49,   140,    47,     4,    14,
     116,     0,   118,   277,   467,   387,   273,    16,    10,   216,
     126,    13,     4,     4,    96,   421,     4,   213,     4,    31,
      32,    23,    24,    25,    54,    81,    56,    49,    81,    23,
      20,    21,    21,    95,    91,    81,    48,    47,    51,    85,
      96,    53,    90,    96,   106,    81,    81,    49,    50,    59,
      85,    93,    98,    59,    20,    84,    39,    40,    41,   253,
      96,    77,    96,    98,    93,   107,    82,    90,    82,    15,
      16,    94,    89,    37,    38,    44,    45,   284,    95,   101,
     274,   131,   278,    97,    46,    47,   136,    53,   470,    81,
      81,    85,    90,    81,    90,    81,    94,    90,    94,    65,
      66,    67,    68,    95,    95,    81,   122,    96,   124,   119,
      95,    77,    96,   115,   116,    81,   118,    83,    84,    85,
       4,    87,   105,   106,   126,    91,    96,    96,    97,    98,
      96,   100,    98,    84,    91,    76,    81,   281,   140,   105,
      81,   415,    93,   109,    85,   419,   112,    81,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,    90,   568,    63,    64,    94,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    91,
      94,    90,    81,    97,    96,    94,    85,   203,   455,   205,
      94,    81,    90,    97,   207,    81,    94,     0,   211,    96,
     146,    81,   476,    95,   258,    89,    90,    94,    44,    45,
      97,    94,   245,   253,    97,   225,   232,   230,   228,   225,
     235,   271,   228,   686,    44,    45,   420,   106,   237,   425,
     636,     4,   234,   263,   274,    75,    76,   433,   434,   435,
     436,    90,   244,   245,   246,   257,    42,   260,    43,   445,
     262,   241,   242,   103,   398,   265,   258,   259,   525,   265,
      96,   102,    98,    94,   100,    94,    97,   213,    97,    94,
     104,   545,    97,   108,   109,   110,    96,    48,    98,   281,
     100,   366,   367,   368,   369,   370,   105,   403,   364,   365,
     236,   237,   375,   376,   377,     6,   371,   372,    11,   373,
     374,    90,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,    96,    96,   358,    96,
      90,    96,    81,    97,    96,    81,    94,    82,   522,    96,
      99,   385,   278,    96,    96,    96,    96,    91,    96,    91,
     536,     9,    95,   617,    95,    95,    95,    95,    95,   379,
     380,   381,   382,    96,    94,    97,    95,    94,    99,    97,
      90,    96,     9,    96,   397,    90,    12,    90,    95,    89,
      96,   411,    94,    97,    95,    94,    90,    95,    90,    81,
     420,    97,    89,   385,   386,    82,   395,    97,    97,    95,
       9,    92,    95,    97,    99,   397,   398,   541,    97,    94,
      96,   403,    90,    81,    97,   599,   106,    81,    92,    99,
      96,   461,    97,   467,    97,   611,   418,    97,    97,    82,
      97,    97,    97,    95,   540,    70,    97,    97,     5,    90,
     546,    74,    99,    97,    84,    89,    89,    89,    96,    90,
      97,   451,   452,    99,     9,    40,    90,   457,    97,   395,
      90,   457,   451,   452,    84,   457,    97,   395,    97,    97,
      97,   463,    97,   357,   359,   467,   362,   469,   662,   360,
     363,   473,   361,   378,    13,    33,   423,   423,   133,   425,
     426,   461,   522,   443,   678,   639,   680,   433,   434,   435,
     436,   570,   494,   210,   608,    -1,    -1,    -1,    -1,   445,
      -1,    -1,   618,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     560,    -1,    -1,    -1,   547,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   538,   539,
      -1,    -1,   538,   539,    -1,   537,   549,    -1,   540,   541,
      -1,   554,    -1,    -1,   546,   547,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   555,   608,    -1,   569,    -1,    -1,   599,
     575,    -1,    -1,   576,    -1,   605,    -1,   580,    -1,   582,
      -1,    -1,    -1,    -1,   590,    -1,    -1,   587,    -1,   589,
      -1,   587,    -1,   589,    -1,    -1,   619,   620,    -1,    -1,
     536,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   608,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   618,   619,   620,   659,
      -1,    -1,   662,    -1,   570,   638,    -1,    -1,    -1,   642,
     643,   644,   686,    -1,    -1,    -1,   649,    -1,   678,    -1,
     680,   674,    -1,    -1,    -1,    -1,   659,    -1,    -1,    -1,
      -1,    -1,   665,   655,    -1,    -1,   666,    -1,    -1,    -1,
     666,    -1,   675,   673,    -1,   611,    -1,   673,   701,    -1,
      -1,    -1,   674,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   695,    -1,   686,    -1,    -1,    -1,    -1,    -1,
     700,    -1,   702,    -1,   700,    -1,   702,    -1,    -1,   701,
      -1,    -1,    -1,    -1,    -1,    -1,   716,    -1,    -1,   719,
     716,     0,     1,   719,    -1,     4,    -1,     6,     7,     8,
      -1,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,
      79,    80,    81,    -1,    83,    84,    85,    -1,    87,    -1,
      -1,    90,    91,    -1,    93,    -1,    -1,    96,    -1,    98,
      -1,    -1,    -1,    -1,    -1,   104,   105,    -1,   107,   108,
     109,     1,   111,   112,     4,     5,     6,     7,     8,    -1,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    -1,    83,    84,    85,    86,    87,    -1,    -1,
      90,    91,    92,    93,    -1,    -1,    96,    -1,    98,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,     1,    -1,    -1,     4,    -1,     6,     7,
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
      -1,    90,    91,    -1,    93,    -1,    95,    96,    -1,    98,
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
      83,    84,    85,    -1,    87,    -1,    -1,    90,    91,    92,
      93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,
      -1,   104,   105,    -1,   107,   108,   109,     1,   111,   112,
       4,    -1,     6,     7,     8,    -1,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    78,    79,    80,    81,    -1,    83,
      84,    85,    -1,    87,    -1,    -1,    90,    91,    92,    93,
      -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,
     104,   105,    -1,   107,   108,   109,     1,   111,   112,     4,
      -1,     6,     7,     8,    -1,    10,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    -1,    83,    84,
      85,    -1,    87,    -1,    -1,    90,    91,    -1,    93,    -1,
      -1,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,
     105,     4,   107,   108,   109,    -1,   111,   112,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    81,    89,    -1,    -1,    85,
      86,    -1,    -1,    -1,    -1,    -1,    92,    93,    -1,    -1,
      96,    -1,    98,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     4,     5,     6,     7,     8,
      -1,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    89,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    93,    99,    -1,    96,    -1,    98,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    89,    85,    86,    -1,    -1,    -1,    -1,    -1,
      92,    93,    99,    -1,    96,    -1,    98,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    81,    89,    -1,    -1,
      85,    86,    -1,    -1,    -1,    97,    -1,    -1,    93,    -1,
      -1,    96,    -1,    98,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    89,    -1,    -1,    85,    86,    -1,
      95,    -1,    -1,    -1,    -1,    93,    -1,    -1,    96,    -1,
      98,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,     4,     5,     6,     7,     8,    -1,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    89,    -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    96,    -1,    98,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,    93,
      -1,    -1,    96,    -1,    98,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     4,     5,     6,
       7,     8,    -1,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    96,
      20,    98,    -1,    23,    24,   102,   103,   104,   105,   106,
     107,   108,   109,   110,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    21,    -1,    23,    24,    -1,    76,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    99,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      90,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    97,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    99,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,
      -1,    91,    -1,    93,    -1,    95,    96,    20,    98,    -1,
      23,    24,    -1,    -1,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,
      83,    84,    85,    -1,    87,    -1,    -1,    -1,    91,    -1,
      93,    -1,    95,    96,    20,    98,    -1,    23,    24,    -1,
      -1,   104,   105,    -1,   107,   108,   109,    -1,   111,   112,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      -1,    87,    -1,    -1,    -1,    91,    -1,    93,    -1,    95,
      96,    -1,    98,    20,    -1,    -1,    23,    24,   104,   105,
      -1,   107,   108,   109,    31,   111,   112,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,    -1,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    76,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,    -1,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,    -1,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,    -1,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,    -1,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,    -1,    -1,    65,    66,
      67,    68,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    -1,
      87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,
      -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,
     107,   108,   109,    -1,   111,   112,    -1,    -1,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,    -1,
      87,    -1,    -1,    -1,    91,    -1,    93,    -1,    -1,    96,
      -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,
     107,   108,   109,    -1,   111,   112
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
     167,   168,   170,   171,   173,   181,   184,   187,   188,   189,
     191,   192,   194,   195,    90,    96,    96,   116,    96,    91,
     117,     4,    81,   145,    81,   145,    96,    24,    36,    68,
      81,    91,   146,   189,    95,    91,    91,   146,   177,   167,
      98,   168,   185,   186,   185,    81,    96,     4,     5,     6,
       7,     8,    10,    11,    12,    13,    14,    15,    16,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    36,    37,    38,    39,    40,    41,    65,    66,
      67,    68,    69,    81,    85,    86,    93,    96,    98,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   180,   193,
     193,   193,    81,   144,   177,   144,   146,    81,    81,   141,
      81,    81,    81,    96,   165,   165,   182,    21,    96,    96,
     183,    81,   119,   119,    90,    95,     4,     6,     7,     8,
      10,    13,    14,    15,    16,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    36,    65,
      66,    67,    68,    76,    81,    85,    92,    93,    96,    98,
     104,   105,   107,   108,   109,   115,   178,   179,   180,   165,
      82,    91,   146,   148,    76,    99,   146,   175,    96,   117,
     106,   172,   165,   164,   182,   164,     4,     5,     6,     7,
       8,    10,    11,    12,    13,    14,    15,    16,    17,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    36,    37,    38,    39,    40,    41,    65,    66,
      67,    68,    69,    81,    86,    93,    96,    98,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   169,     0,   116,
     145,    90,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    89,   145,    49,   101,    42,
      43,   102,   103,   104,    37,    38,    39,    40,    41,   105,
     106,    46,    47,    93,   107,   108,   109,   110,    48,    63,
      64,    75,    76,    44,    45,    96,    98,   100,   166,   105,
     190,   146,   176,   176,     6,    21,    81,    90,    98,   130,
     176,    11,   132,    96,   145,    90,   145,    90,   176,    81,
      96,    89,    95,   190,    81,   121,    92,    90,    94,   175,
      89,    95,    90,    94,    90,    96,    76,   168,   198,   199,
     200,    97,    99,    96,    96,    96,    96,   197,   145,   145,
     117,    90,    94,   197,   117,    96,   198,   183,    81,    96,
      82,    91,    91,   116,   147,   148,   149,    95,    82,    99,
      92,    94,   174,    95,    97,    92,    97,    96,    97,    98,
     100,   166,   147,    94,   174,   198,   175,   183,    97,    99,
      90,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,    31,   147,   152,   149,   153,   154,
     155,   156,   157,   158,   158,   159,   159,   159,   159,   159,
     160,   160,   161,   161,   162,   162,   162,   163,   164,   164,
     164,   164,    76,    82,   146,   148,   204,   205,   206,   146,
      86,   169,    23,    85,   201,    81,    96,    94,    97,    97,
      96,    98,   130,   185,   144,   175,     9,    90,    96,    12,
     133,   176,    90,    90,    97,    95,    82,    89,    94,   174,
      91,   146,   174,   147,   201,   186,   198,   168,    95,    97,
      94,   198,   198,   198,   198,    95,   196,    90,    90,    81,
     196,   198,    97,    89,    82,    97,    92,   115,    92,   115,
     146,    97,   179,    92,   146,   204,   146,    86,   169,    76,
     146,    99,    97,   174,   146,    95,   147,    97,    94,    99,
     106,    96,   198,   146,   116,   116,   176,   175,     9,    90,
      90,   174,   176,   144,    81,   117,    97,   117,   146,    97,
      84,    93,    81,    92,    92,    99,    96,   202,    97,   201,
     117,   200,    97,    97,    97,    97,   167,   117,   117,    97,
     117,    82,    97,    92,    92,    95,    97,    99,   147,    70,
      74,   149,    76,   206,   198,    97,     5,    97,   174,   176,
     144,   144,    99,    97,    90,    97,    84,    89,    89,   201,
      89,   117,   202,   117,   117,   117,    96,   203,   117,    90,
      97,   146,   117,   149,   147,    97,   117,   116,    90,    99,
      97,    90,    97,   116,   144,   117,    84,    93,   147,    97,
     147,   204,   117,   116,   144,   116,    97,    84,    97,    97,
     116,   116
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
     163,   163,   163,   163,   164,   164,   164,   164,   164,   164,
     164,   165,   165,   165,   165,   165,   165,   166,   166,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   168,   168,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   170,
     170,   171,   171,   172,   173,   174,   174,   175,   175,   175,
     175,   176,   176,   177,   177,   177,   177,   178,   178,   179,
     179,   179,   179,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   181,   181,   181,   182,   183,   184,   184,
     185,   185,   186,   186,   186,   186,   186,   187,   187,   188,
     188,   188,   189,   190,   190,   191,   191,   191,   191,   191,
     191,   192,   192,   192,   193,   193,   194,   194,   195,   195,
     196,   196,   197,   197,   198,   198,   199,   199,   200,   200,
     200,   201,   201,   202,   202,   203,   203,   204,   204,   205,
     205,   205,   205,   206,   206,   206
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
       2,     1,     2,     4,     3,     3,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       6,     3,     3,     3,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       4,     2,     5,     0,     4,     0,     1,     1,     2,     3,
       4,     1,     3,     1,     2,     3,     4,     1,     3,     5,
       3,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     3,     2,     0,     3,     3,     3,
       1,     3,     1,     4,     3,     6,     6,     1,     1,     6,
       6,     7,     1,     0,     3,     5,     5,     6,     6,     6,
       2,     6,     6,     6,     1,     1,     5,     5,     3,     3,
       0,     3,     0,     3,     0,     1,     1,     3,     1,     4,
       2,     1,     1,     0,     3,     0,     3,     0,     1,     1,
       2,     3,     4,     1,     1,     1
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
#line 2459 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 140 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2465 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 163 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2471 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 164 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2477 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 168 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2483 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 169 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2489 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 173 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2495 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 174 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2501 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 175 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2507 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 176 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2513 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 180 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2519 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 184 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2525 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 188 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2531 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 189 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2537 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 190 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2543 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 191 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2549 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 192 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2555 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 193 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2561 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 204 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2567 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 208 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2573 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 209 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2579 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 213 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2585 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 217 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2591 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 221 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2597 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 225 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2603 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 226 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2609 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 231 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2620 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 238 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2631 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 245 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2642 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 252 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 2648 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 254 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 2654 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 258 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 2660 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 259 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 2666 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 263 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2672 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 267 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2678 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 268 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2684 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 272 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2690 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 273 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2696 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 277 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2702 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 278 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2708 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 279 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2714 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 280 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2720 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 284 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2726 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 285 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); }
#line 2732 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 289 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_COROUTINE, (yyvsp[-1].obj), NULL, NULL); }
#line 2738 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 293 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2744 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 297 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2750 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 298 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2756 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 299 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2762 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 300 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2768 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 304 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2774 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 308 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2780 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 312 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2786 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 313 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2792 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 317 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2798 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 321 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2804 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 322 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2810 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 326 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2816 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 331 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2822 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 332 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2828 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 337 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2834 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 338 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2840 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 339 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2846 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 340 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2852 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 341 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2858 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 342 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2864 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 343 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2870 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 344 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2876 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 345 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2882 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 346 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2888 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 347 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2894 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 348 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2900 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 349 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2906 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 350 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2912 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 359 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2918 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 360 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2924 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 361 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2930 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 362 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2936 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 363 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2942 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 364 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2948 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 369 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2954 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 379 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2960 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 384 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2966 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 389 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2972 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 394 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2978 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 399 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2984 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 404 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2990 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 409 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2996 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 410 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3002 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 415 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3008 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 416 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3014 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 417 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3020 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 418 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3026 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 419 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3032 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 424 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3038 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 425 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3044 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 430 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3050 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 431 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3056 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 436 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3062 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 437 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3068 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 438 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3074 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 443 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3080 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 448 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3086 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 449 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3092 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 450 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-1].obj), kx_gen_special_object(KXVL_NULL), 0); }
#line 3098 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 451 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 3104 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 452 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-1].obj), kx_gen_special_object(KXVL_NULL), 1); }
#line 3110 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 453 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 3116 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 458 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 3122 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 459 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 3128 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 460 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 3134 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 461 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 3140 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 462 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 3146 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 463 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 3152 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 468 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 3158 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 469 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3164 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 470 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3170 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 471 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3176 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 472 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3182 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 476 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3188 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 477 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3194 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 481 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3200 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 482 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3206 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 483 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3212 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 484 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3218 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 485 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3224 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3230 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3236 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 492 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3242 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 493 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3248 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 494 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3254 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3260 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3266 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3272 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3278 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 502 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3284 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3290 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 507 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3296 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3302 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3308 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 510 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3314 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 511 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3320 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 512 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3326 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 513 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3332 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3338 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 515 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3344 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 516 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3350 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 517 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3356 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 518 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3362 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 519 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3368 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3374 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 521 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3380 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 522 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3386 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 523 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3392 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 524 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3398 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 525 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3404 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 526 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3410 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 527 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3416 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 528 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3422 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 529 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3428 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 530 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3434 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 531 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3440 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 532 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3446 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 533 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("yield"); }
#line 3452 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 534 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3458 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 535 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3464 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 536 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3470 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 537 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3476 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3482 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 539 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3488 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 540 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("=="); }
#line 3494 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 541 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("!="); }
#line 3500 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 542 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<="); }
#line 3506 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 543 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<"); }
#line 3512 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 544 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">="); }
#line 3518 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">"); }
#line 3524 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 546 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<=>"); }
#line 3530 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 547 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("+"); }
#line 3536 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 548 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("-"); }
#line 3542 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 549 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("*"); }
#line 3548 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 550 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("/"); }
#line 3554 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 551 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("%"); }
#line 3560 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 552 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("&"); }
#line 3566 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 553 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("|"); }
#line 3572 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 554 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("^"); }
#line 3578 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 555 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("[]"); }
#line 3584 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 556 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("()"); }
#line 3590 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 560 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3596 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 561 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3602 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 565 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3608 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 566 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3614 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 570 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3620 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 574 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3626 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 578 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3632 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 584 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3638 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 585 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3644 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 586 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3650 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 591 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3656 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 596 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3662 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 597 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3668 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 598 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3674 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 603 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3680 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 607 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3686 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 608 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3692 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3698 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 610 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3704 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 614 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3710 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 615 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3716 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 616 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3722 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 617 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3728 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 618 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3734 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 619 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3740 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 620 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3746 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 621 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3752 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 622 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3758 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 623 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3764 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 624 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3770 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 625 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3776 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 626 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3782 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 627 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3788 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 628 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3794 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 629 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3800 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 630 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3806 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 631 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3812 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 632 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3818 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3824 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 634 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3830 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 635 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3836 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 636 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3842 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 637 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3848 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 638 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3854 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 639 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3860 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 640 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3866 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3872 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3878 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 643 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3884 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3890 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3896 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3902 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 647 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "=="; }
#line 3908 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 648 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "!="; }
#line 3914 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 649 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<="; }
#line 3920 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<"; }
#line 3926 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 651 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">="; }
#line 3932 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 652 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">"; }
#line 3938 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 653 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<=>"; }
#line 3944 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 654 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "+"; }
#line 3950 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "-"; }
#line 3956 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "*"; }
#line 3962 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "/"; }
#line 3968 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 658 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "%"; }
#line 3974 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 659 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "&"; }
#line 3980 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 660 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "|"; }
#line 3986 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 661 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "^"; }
#line 3992 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 662 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "[]"; }
#line 3998 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 663 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "()"; }
#line 4004 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 667 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4010 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 668 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 4016 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 669 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4022 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 673 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 4028 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 677 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 4034 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 681 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4040 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 682 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 4046 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 687 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4052 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 691 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 4058 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 692 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 4064 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 693 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 4070 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 694 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 4076 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 695 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 4082 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 699 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4088 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 700 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4094 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 704 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4100 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 705 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4106 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 706 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4112 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 710 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 4118 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 714 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 4124 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 715 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4130 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 719 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4136 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 720 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4142 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 721 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4148 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 722 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 4154 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 723 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 4160 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 724 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 4166 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 728 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4172 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 729 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4178 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 730 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4184 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 739 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4190 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 740 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4196 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 744 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4202 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 745 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4208 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 749 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4214 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 751 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 4227 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 762 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4233 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 763 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4239 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 767 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4245 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 773 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4251 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 777 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4257 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 778 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 4263 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 779 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 4269 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 783 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 4275 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 784 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 4281 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 788 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 4287 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 789 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4293 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 793 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4299 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 794 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4305 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 798 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4311 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 804 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 4317 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 805 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 4323 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 806 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 4329 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 812 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 4335 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 4339 "kx.tab.c" /* yacc.c:1646  */
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
#line 815 "src/kinx.y" /* yacc.c:1906  */


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
