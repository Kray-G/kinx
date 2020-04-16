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
#define YYFINAL  336
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3757

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  94
/* YYNRULES -- Number of rules.  */
#define YYNRULES  373
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  718

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
     548,   549,   550,   551,   552,   553,   554,   555,   559,   560,
     564,   565,   569,   573,   577,   578,   582,   583,   584,   585,
     589,   590,   594,   595,   596,   597,   601,   602,   606,   607,
     608,   609,   613,   614,   615,   616,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   665,   666,   667,   671,   675,   679,   680,   684,   685,
     689,   690,   691,   692,   693,   697,   698,   702,   703,   704,
     708,   712,   713,   717,   718,   719,   720,   721,   722,   726,
     727,   728,   732,   733,   737,   738,   742,   743,   747,   748,
     760,   761,   765,   766,   770,   771,   775,   776,   777,   781,
     782,   786,   787,   791,   792,   796,   797,   801,   802,   803,
     804,   808,   809,   810
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

#define YYPACT_NINF -449

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-449)))

#define YYTABLE_NINF -315

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1701,   -48,   -66,   -34,  1701,   -31,     9,    39,    47,    49,
    3395,    82,    56,  3445,   225,   -45,   -45,  -449,   -55,  2238,
    2238,  2238,    14,  3445,  3445,  3395,   100,   112,   120,   125,
     -32,   225,   225,  -449,  -449,  -449,  -449,    -2,   124,   129,
     129,   126,    94,  -449,  -449,  -449,  -449,   826,   225,  2885,
    2635,    44,   132,   225,  3645,  -449,  3645,  2345,   214,   717,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,   228,  -449,  -449,
    -449,   150,   328,  -449,  -449,   -24,   202,   211,   155,   164,
     169,   185,    33,   216,   -39,   109,   236,   208,   201,    92,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,   182,
    -449,  -449,  -449,  -449,  -449,  3395,  3395,   283,  2685,   938,
     285,   198,   228,   207,   228,   210,  3395,   205,   209,   215,
    -449,  2131,  2231,   182,  -449,   222,  1810,  2338,    31,  -449,
    2935,    -8,    52,  -449,    78,   217,    -1,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,   218,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,   219,   223,
     224,   226,   228,   213,   228,  2338,     9,  -449,    79,   226,
       9,   229,    -1,    92,    92,   124,   233,   230,   242,  -449,
    -449,   227,   237,  -449,  1701,   -66,   -34,  1047,   -31,     9,
      34,    46,    49,  3395,   225,   -45,   -45,   232,   -55,  2238,
    2238,  2238,    14,  2985,  3062,  3139,   100,   -32,   234,   240,
     241,    -2,  3495,   243,   246,  -449,   225,  3216,  2735,    44,
     -60,   225,  3645,   235,  1156,   248,  -449,   249,    92,   250,
    1917,  2124,    87,  3495,  -449,  2338,   251,    -1,  -449,  -449,
    2935,    92,  -449,   124,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,   244,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,   256,  -449,
    3495,  3495,  3495,  3495,  3495,  3495,  3495,  3495,  3495,  3495,
    3495,  3495,  3495,  3295,  -449,  3645,  3395,  3645,  3645,  3645,
    3645,  3645,  3645,  3645,  3645,  3645,  3645,  3645,  3645,  3645,
    3645,  3645,  3645,  3645,  3645,  3645,  3645,  3645,  3645,  3645,
    3645,  -449,  -449,  2785,  3395,  2452,  -449,    37,   -26,  2338,
     -12,   -11,   253,   -29,   345,  3445,  2635,   346,    81,   261,
     347,  3395,   268,  -449,   270,  -449,    36,   266,   281,  3495,
    -449,   269,   275,   272,  -449,  -449,  3545,   251,  3495,    37,
    -449,   -45,  -449,    -1,    93,   273,   274,   276,  -449,  -449,
      -1,    -1,    -1,    -1,   278,   277,   279,  -449,  -449,   293,
     278,  -449,    -1,   280,  -449,   286,   311,   298,  1265,  1374,
    -449,  -449,    99,  -449,  1701,   299,   302,  -449,  2131,   306,
    3395,  -449,  -449,  -449,  2785,  -449,  3395,  2559,  -449,  -449,
    3345,   300,   303,   251,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    3395,  -449,   202,   307,   211,   155,   164,   169,   185,    33,
      33,   216,   216,   216,   216,   216,   -39,   -39,   109,   109,
     236,   236,   236,   208,  -449,  -449,  -449,  -449,  3495,  -449,
    2338,    99,   304,   312,  -449,  1912,  -449,  -449,  -449,  -449,
     301,   309,    -1,  3395,  1701,  1701,  3395,  2935,   399,   110,
     322,   251,  3395,  3445,   332,     9,  -449,    97,  -449,  -449,
       9,  3395,   317,     5,   334,   329,  2024,  2338,   323,  -449,
     330,  -449,   331,  -449,    37,     9,    -1,   335,   336,   337,
     341,   225,     9,  -449,  -449,  -449,     9,   342,     9,   343,
     344,  -449,  -449,  1483,  -449,  1592,  1803,   348,  -449,  -449,
    2338,   349,  2019,  -449,  -449,  3495,  2338,  -449,   357,   355,
    2338,  3395,  -449,  -449,  2835,  -449,  -449,    -1,   350,  2338,
     426,  -449,   108,   251,  3395,  3445,  3445,   351,   114,   352,
     354,  -449,  -449,  -449,  2338,   348,  -449,   356,   363,  -449,
    -449,   364,    37,   366,     9,   330,  -449,  -449,     9,     9,
       9,  -449,   361,  -449,  -449,     9,  -449,   371,   367,  -449,
    -449,  3395,  -449,  -449,  -449,  3595,  -449,  -449,  3495,  -449,
     368,     9,  1701,   373,   370,   118,   376,   374,   435,  1701,
    3445,     9,  -449,     6,  3495,   378,  3495,  -449,  -449,  -449,
    -449,  -449,  2785,  -449,  -449,  -449,  -449,  2338,  -449,  -449,
    -449,     9,  -449,  -449,  -449,   364,  1701,  3445,  1701,  -449,
     379,  -449,  -449,   383,  -449,  -449,  -449,   380,  -449,  -449,
     382,  -449,  1701,  -449,  -449,  1701,  -449,  -449
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    85,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   330,     0,     0,
       0,     0,     0,    83,    83,    73,     0,     0,     0,     0,
       0,     0,     0,   314,   172,   174,   175,     0,     0,     0,
       0,     0,   187,   171,   169,   188,   170,     0,     0,     0,
       0,     0,   242,     0,     0,   314,     0,     0,     0,     0,
       3,     5,     6,     7,    21,    23,     8,     9,    10,    11,
      12,    13,    14,    22,    15,    16,    17,    85,    18,    19,
      20,     0,    85,    87,   110,   113,   114,   116,   118,   120,
     122,   124,   126,   129,   135,   138,   141,   145,   147,   154,
     161,   173,   176,   177,   178,   179,    40,    41,   325,   331,
     112,   326,    42,    43,    25,     0,     0,     0,     0,     0,
      60,     0,    85,     0,    85,     0,     0,     0,     0,     0,
     187,     0,     0,   331,    51,     0,     0,   252,     0,   184,
       0,   320,     0,   318,     0,     0,   352,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   280,   281,   282,   283,   285,   287,
     286,   284,   279,   295,   296,   297,   299,   301,   288,   289,
     290,   291,   292,   342,   293,   294,   303,     0,   308,   309,
     307,   298,   300,   302,   304,   305,   306,   343,     0,     0,
       0,   350,    85,    84,    85,    72,     0,    78,     0,   350,
       0,     0,   352,   159,   160,     0,     0,     0,     0,   313,
      32,     0,     0,    69,     0,   262,   264,     0,   266,   267,
      85,    85,   272,   273,   274,   275,   276,   330,   278,   280,
     281,   282,   283,    83,    83,    73,   284,   279,   172,   174,
     175,   291,     0,   187,   188,    26,   303,     0,     0,   307,
     242,   302,   304,   305,     0,   244,   256,     0,   157,     0,
       0,     0,     0,     0,   238,   246,   244,   352,   338,   240,
       0,   156,   158,     0,   155,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   209,   210,   211,   212,   214,   216,   215,
     213,   208,   222,   223,   224,   226,   228,   217,   218,   219,
     220,   221,   189,   186,   230,     0,   235,   236,   234,   225,
     227,   229,   231,   232,   233,   185,     1,     4,     0,    80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
     152,   167,   168,   365,     0,     0,   162,     0,     0,   250,
       0,     0,     0,     0,   187,    83,     0,     0,     0,     0,
      62,     0,     0,    64,     0,    66,     0,     0,     0,     0,
      50,     0,    34,   244,   253,    70,     0,   244,     0,     0,
     316,     0,   317,   352,     0,   356,     0,   353,   354,   310,
     352,   352,   352,   352,   348,     0,     0,   346,    77,     0,
     348,   347,   352,     0,   312,     0,     0,     0,     0,     0,
      44,   261,   103,   102,     0,     0,   238,    27,   245,     0,
       0,   183,   104,   181,   365,   182,     0,     0,   105,   247,
     245,     0,     0,   244,   311,   237,    71,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,    89,    90,
      75,    88,   115,     0,   117,   119,   121,   123,   125,   127,
     128,   131,   133,   134,   130,   132,   136,   137,   140,   139,
     142,   143,   144,   146,   148,   149,   151,   153,     0,   373,
     371,   372,     0,   366,   367,     0,   165,   164,   360,   359,
       0,     0,   352,     0,     0,     0,     0,     0,     0,     0,
       0,   244,     0,    83,     0,     0,    59,     0,    65,    67,
       0,     0,     0,     0,   245,     0,     0,   254,     0,   322,
     361,   319,     0,   358,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    68,    76,    79,     0,     0,     0,     0,
       0,   315,    28,     0,    29,     0,   259,   183,   257,   243,
     260,     0,     0,   108,   107,     0,   248,   239,     0,     0,
      74,     0,   368,   166,     0,   163,   332,   352,     0,   251,
      45,    47,     0,   244,     0,    83,    83,     0,     0,     0,
       0,    63,    86,    49,   259,     0,    35,     0,    37,    33,
     255,     0,     0,   321,     0,   361,   333,   355,     0,     0,
       0,   351,   363,   344,   345,     0,   334,     0,     0,    30,
      31,     0,   109,   106,   249,     0,   241,   111,     0,   369,
       0,     0,     0,     0,     0,     0,     0,     0,   239,     0,
      83,     0,    36,     0,     0,     0,     0,   327,   357,   339,
     340,   341,   365,   349,   328,    24,   180,   258,   337,   336,
     370,     0,   335,    46,    48,    58,     0,    83,     0,    55,
       0,    61,    38,     0,   324,   362,   323,     0,   329,    56,
       0,    54,     0,    39,   364,     0,    53,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -449,  -449,    11,     4,    -3,  -449,   405,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,    77,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,   -23,    -6,     8,  -185,   -44,  -239,  -449,  -449,   127,
     123,   130,   122,   137,   131,   -82,  -215,   -87,   -86,  -114,
     107,   -27,    13,  -266,    -5,    63,  -370,  -449,  -449,  -449,
    -449,  -237,  -126,  -106,   472,  -449,    32,   -40,  -449,   466,
    -191,  -449,     1,    80,  -449,  -449,     0,   369,  -449,  -449,
       2,  -449,  -449,    60,   294,  -184,  -449,   -62,  -382,  -129,
    -449,  -448,  -449,   -97
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    58,   264,    60,    61,    62,   221,    63,   413,    64,
      65,    66,    67,    68,    69,    70,    71,   397,    72,   400,
     546,    73,    74,    75,    76,    77,    78,    79,   208,    80,
      81,   202,   123,    82,   491,   452,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   386,   100,   101,   335,   102,   103,   280,
     104,   459,   276,   390,   203,   265,   266,   197,   105,   283,
     219,   106,   142,   143,   107,   108,   133,   388,   110,   111,
     198,   112,   113,   572,   434,   426,   427,   428,   530,   633,
     683,   522,   523,   524
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     109,   204,   125,   120,   109,   272,   468,   267,   117,   139,
     391,    59,   398,   453,   417,   527,   591,   144,   132,   216,
     406,   137,   199,   200,   444,   355,   145,   282,   443,   284,
     115,   137,   137,   205,   453,  -298,   130,   560,   121,   471,
      45,   146,   114,   121,   213,   214,   279,   109,   278,   211,
     121,   121,   394,   140,   371,   531,    45,   271,   275,   109,
     528,   268,   116,   337,   212,   118,   281,   451,   372,   537,
     532,   338,   364,   365,   366,   424,   354,   356,   141,   141,
     130,   418,   533,   533,    45,   534,   535,   419,   469,   626,
     702,   267,   474,   472,   217,   201,   267,   594,   627,   703,
     119,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   122,   402,   493,   404,   109,
     122,   415,   529,   389,   389,   416,   389,   124,   124,  -270,
     533,   381,   382,   550,   389,   119,   381,   382,   367,   368,
     277,  -271,   420,   381,   382,   126,   421,   135,   275,   501,
     502,   503,   504,   505,   473,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   422,   438,
     453,   543,   421,   439,   130,   533,   555,   134,    45,   453,
     558,   206,   635,   464,   465,   466,   468,   467,   383,   224,
     384,   533,   385,   207,   622,   464,   435,   466,   436,   467,
     615,   209,   533,   437,   421,   663,   210,   441,   533,   425,
     220,   669,   533,   272,   336,   696,   223,   373,   374,   375,
     218,   204,   362,   363,   109,   125,   120,   109,   450,   139,
     267,   117,   121,   559,   707,   282,   599,   144,   279,   562,
     339,   132,   199,   200,   357,    14,   567,   568,   569,   570,
     675,   137,   137,   205,   358,   468,   278,   359,   577,   510,
     511,   512,   369,   370,   109,   271,   275,   360,   337,   268,
     541,   377,   378,   361,   281,   425,   379,   380,    33,   453,
     499,   500,   506,   507,   376,   508,   509,   387,   275,   392,
      34,    35,    36,   129,   401,   547,   399,   403,   141,   141,
     405,   146,    38,   412,   617,   212,   130,   416,    43,    44,
      45,   217,    46,   423,   445,   430,   131,   429,   448,   431,
     432,    49,   433,    50,   447,   442,   446,  -277,   449,  -288,
      52,  -314,   121,   602,    55,  -289,  -290,    57,   454,   521,
     425,  -293,   458,   475,   460,   470,   476,   461,   608,   536,
     514,   515,   516,   517,   -57,   542,   453,   544,   548,   545,
     549,   551,   657,   552,   553,   532,   554,   573,   564,   574,
     566,   565,   540,   571,   575,   579,   664,   578,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   520,   525,   580,   539,   581,   587,  -310,   589,   597,
     598,   603,   601,   137,   275,   607,   604,   606,   614,   389,
     654,   613,   616,   620,   625,   628,   689,   353,   267,   453,
     521,   629,   631,   660,   557,   647,   632,   655,   634,   656,
     612,   662,   638,   639,   640,   453,   618,   453,   641,   645,
     672,   648,   670,   651,   -58,   222,   652,   661,   109,   109,
     668,   671,   673,   674,   109,   676,   141,   682,   450,   583,
     585,   685,   586,   694,   686,   691,   697,   713,   590,   695,
     538,   698,   520,   690,   592,   705,   712,   714,   596,   715,
     494,   496,   492,   513,   141,   138,   425,   563,   495,   704,
     588,   706,   498,   425,   425,   425,   425,   497,   600,   215,
     576,   561,   411,   440,   637,   425,   678,   659,   665,     0,
       0,     0,     0,     0,     0,     0,   267,     0,     0,     0,
     619,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   109,   109,     0,     0,   610,   611,
       0,   609,   621,     0,   389,   275,     0,   623,     0,     0,
     389,   137,     0,     0,     0,     0,     0,     0,     0,   624,
     521,     0,   636,     0,     0,     0,   642,     0,     0,   643,
       0,     0,     0,   644,     0,   646,     0,     0,     0,     0,
     354,     0,     0,   109,     0,   109,     0,   337,     0,   337,
       0,     0,   666,   667,     0,   425,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   520,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   389,   137,   137,     0,     0,     0,     0,   425,
       0,   677,     0,     0,     0,   679,   680,   681,   521,     0,
       0,     0,   684,     0,     0,     0,     0,   700,     0,     0,
       0,     0,   688,     0,     0,     0,     0,     0,   692,   687,
       0,     0,   109,     0,     0,     0,   693,     0,   701,   109,
     425,     0,     0,   699,   710,     0,     0,     0,   137,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   708,     0,
     520,     0,     0,     0,     0,     0,   109,     0,   109,     0,
     709,     0,   711,     0,     0,   137,     0,     0,     0,     0,
       0,     0,   109,     0,     0,   109,   716,    -2,     1,   717,
       0,     2,     0,     3,     4,     5,     0,     6,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,     0,     0,   -81,    47,     0,
      48,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,     1,    56,    57,
     225,   148,   226,   227,   228,     0,   229,   153,   154,   230,
     231,   232,   233,    11,    12,    13,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,    27,
      28,    29,   247,   173,   174,   175,   176,   177,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   248,   249,   250,   251,   182,     0,     0,     0,     0,
       0,     0,   252,    38,    39,    40,    41,   253,     0,    43,
      44,   254,   185,    46,     0,     0,   -81,    47,   255,   256,
       0,     0,   257,     0,   258,     0,     0,     0,   188,   189,
     259,   260,   192,   261,   262,   263,   196,    56,    57,     1,
       0,     0,     2,     0,     3,     4,     5,     0,     6,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    38,    39,    40,    41,    42,
       0,    43,    44,    45,     0,    46,     0,     0,   -81,    47,
     255,    48,     0,     0,    49,     0,    50,     0,     0,     0,
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
      48,     0,  -265,    49,     0,    50,     0,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,     1,    56,    57,
       2,     0,     3,     4,     5,     0,     6,     0,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,    38,    39,    40,    41,    42,     0,    43,
      44,    45,     0,    46,     0,     0,   -81,    47,   457,    48,
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
      45,     0,    46,     0,     0,   -81,    47,   582,    48,     0,
       0,    49,     0,    50,     0,     0,     0,     0,     0,    51,
      52,     0,    53,    54,    55,     1,    56,    57,     2,     0,
       3,     4,     5,     0,     6,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,    38,    39,    40,    41,    42,     0,    43,    44,    45,
       0,    46,     0,     0,   -81,    47,   584,    48,     0,     0,
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
      46,     0,     0,   -81,    47,   649,    48,     0,     0,    49,
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
       0,     0,   -81,    47,   650,    48,     0,     0,    49,     0,
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
       0,   -81,    47,     0,    48,     0,     0,    49,     0,    50,
       0,     0,     0,     0,     0,    51,    52,   121,    53,    54,
      55,     0,    56,    57,   147,   148,   149,   150,   151,     0,
     152,   153,   154,   155,   156,   157,   158,     0,     0,     0,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,     0,     0,     0,   172,   173,   174,   175,
     176,   177,     0,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   179,   180,   181,   182,
       0,     0,     0,     0,     0,     0,   252,     0,     0,     0,
       0,   407,   353,   -85,     0,   184,   185,     0,     0,     0,
       0,     0,   414,   186,     0,     0,   408,     0,   187,     0,
       0,     0,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   147,   148,   149,   150,   151,     0,   152,   153,   154,
     155,   156,   157,   158,     0,     0,     0,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
       0,     0,     0,   172,   173,   174,   175,   176,   177,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,     0,     0,     0,     0,     0,
       0,     0,   178,   179,   180,   181,   182,     0,     0,     0,
       0,     0,     0,   252,     0,     0,     0,     0,   407,     0,
       0,   409,   184,   185,     0,     0,     0,     0,     0,   462,
     186,   605,     0,   408,     0,   187,     0,     0,     0,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   147,   148,
     149,   150,   151,     0,   152,   153,   154,   155,   156,   157,
     158,     0,     0,     0,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,     0,     0,     0,
     172,   173,   174,   175,   176,   177,     0,     0,     0,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,     0,     0,     0,     0,     0,     0,     0,   178,
     179,   180,   181,   182,     0,     0,     0,     0,     0,     0,
     252,     0,     0,     0,     0,   407,     0,     0,   409,   184,
     185,     0,     0,     0,     0,     0,   630,   186,   653,     0,
     408,     0,   187,     0,     0,     0,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   147,   148,   149,   150,   151,
       0,   152,   153,   154,   155,   156,   157,   158,     0,     0,
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,     0,     0,     0,   172,   173,   174,
     175,   176,   177,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   178,   179,   180,   181,
     182,     0,     0,     0,     0,     0,     0,   252,     0,     0,
       0,     0,   407,   409,     0,     0,   184,   185,     0,     0,
       0,   463,     0,     0,   186,     0,     0,   408,     0,   187,
       0,     0,     0,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   147,   148,   149,   150,   151,     0,   152,   153,
     154,   155,   156,   157,   158,     0,     0,     0,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,     0,     0,     0,   172,   173,   174,   175,   176,   177,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   178,   179,   180,   181,   182,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   183,
     409,     0,     0,   184,   185,     0,   410,     0,     0,     0,
       0,   186,     0,     0,     0,     0,   187,     0,     0,     0,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   285,
     286,   287,   288,   289,     0,   290,   291,   292,   293,   294,
     295,   296,   297,     0,     0,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,     0,     0,
       0,   311,   312,   313,   314,   315,   316,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     317,   318,   319,   320,   321,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   322,   409,     0,     0,
       0,   323,     0,     0,     0,     0,     0,     0,   324,     0,
       0,     0,     0,   325,     0,     0,     0,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   285,   286,   287,   288,
     289,     0,   290,   291,   292,   293,   294,   295,   296,   297,
       0,     0,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,     0,     0,     0,   311,   312,
     313,   314,   315,   316,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   317,   318,   319,
     320,   321,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   322,     0,     0,     0,     0,   526,     0,
       0,     0,     0,     0,     0,   324,     0,     0,     0,     0,
     325,     0,     0,     0,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   285,   286,   287,   288,   289,     0,   290,
     291,   292,   293,   294,   295,   296,   297,     0,     0,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,     0,     0,     0,   311,   312,   313,   314,   315,
     316,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   317,   318,   319,   320,   321,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     322,     0,     0,     0,     0,   593,     0,     0,     0,     0,
       0,     0,   324,     0,     0,    14,     0,   325,    17,   127,
       0,   326,   327,   328,   329,   330,   331,   332,   333,   334,
       0,   128,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,   129,     0,    14,   393,     0,    17,   127,
       0,   273,    38,     0,     0,     0,   130,     0,    43,    44,
      45,   128,    46,     0,     0,     0,   131,     0,    48,    31,
      32,    49,     0,    50,   274,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,     0,    38,     0,     0,     0,   394,     0,    43,    44,
      45,   128,    46,     0,     0,   395,   131,     0,    48,    31,
      32,    49,     0,   396,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,   273,    38,     0,     0,     0,   130,     0,    43,    44,
      45,   128,    46,     0,     0,     0,   131,     0,    48,    31,
      32,    49,     0,    50,   456,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,   518,    38,     0,     0,     0,   130,   519,    43,    44,
      45,   128,    46,     0,     0,     0,   270,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,   658,    38,     0,     0,     0,   130,   519,    43,    44,
      45,   128,    46,     0,     0,     0,   270,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,     0,    38,     0,     0,     0,   130,   269,    43,    44,
      45,   128,    46,     0,     0,     0,   270,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,   273,    38,     0,     0,     0,   130,     0,    43,    44,
      45,   128,    46,     0,     0,     0,   131,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,     0,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,   130,     0,    43,    44,
      45,     0,    46,     0,     0,     0,   136,     0,    48,     0,
    -285,    49,    14,    50,     0,    17,   127,     0,     0,    51,
      52,     0,    53,    54,    55,     0,    56,    57,   128,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
     129,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,   130,     0,    43,    44,    45,     0,    46,
       0,     0,     0,   136,     0,    48,     0,  -287,    49,    14,
      50,     0,    17,   127,     0,     0,    51,    52,     0,    53,
      54,    55,     0,    56,    57,   128,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,    36,   129,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
     130,     0,    43,    44,    45,     0,    46,     0,     0,     0,
     131,     0,    48,     0,  -286,    49,    14,    50,     0,    17,
     127,     0,     0,    51,    52,     0,    53,    54,    55,     0,
      56,    57,   128,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,   129,     0,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,   130,   455,    43,
      44,    45,     0,    46,     0,     0,     0,   270,     0,    48,
       0,     0,    49,     0,    50,    14,     0,     0,    17,   127,
      51,    52,     0,    53,    54,    55,   490,    56,    57,     0,
       0,   128,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,     0,    38,     0,     0,     0,   130,     0,    43,    44,
      45,   128,    46,     0,     0,     0,   270,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,   595,    38,     0,     0,     0,   130,     0,    43,    44,
      45,   128,    46,     0,     0,     0,   131,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,     0,    38,     0,     0,     0,   130,     0,    43,    44,
      45,   128,    46,     0,     0,     0,   131,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,     0,    38,     0,     0,     0,   130,     0,    43,    44,
      45,   128,    46,     0,     0,     0,   136,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,     0,    38,     0,     0,     0,   130,     0,    43,    44,
      45,   128,    46,     0,     0,     0,   270,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,    17,   127,
       0,     0,    38,     0,     0,     0,   130,     0,    43,    44,
      45,   128,    46,     0,     0,     0,   556,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,    14,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,   130,     0,    43,    44,
      45,     0,    46,     0,     0,     0,    47,     0,    48,    31,
      32,    49,     0,    50,     0,     0,     0,     0,    33,    51,
      52,     0,    53,    54,    55,     0,    56,    57,     0,     0,
      34,    35,    36,   129,     0,     0,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,   130,     0,    43,    44,
      45,     0,    46,     0,     0,     0,   131,     0,    48,     0,
       0,    49,     0,    50,     0,     0,     0,     0,     0,     0,
      52,     0,    53,    54,    55,     0,    56,    57
};

static const yytype_int16 yycheck[] =
{
       0,    24,     8,     6,     4,    49,   272,    47,     4,    14,
     116,     0,   118,   252,   140,   385,   464,    16,    10,    21,
     126,    13,    20,    21,   215,    49,    81,    54,   212,    56,
      96,    23,    24,    25,   273,    95,    81,   419,     4,   276,
      85,    96,    90,     4,    31,    32,   106,    47,    51,    81,
       4,     4,    81,    98,    93,    81,    85,    49,    50,    59,
      23,    48,    96,    59,    96,    96,    53,   252,   107,    98,
      96,    77,    39,    40,    41,    76,    82,   101,    15,    16,
      81,    89,    94,    94,    85,    97,    97,    95,   273,    84,
      84,   131,   283,   277,    96,    81,   136,   467,    93,    93,
      91,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,    81,   122,   356,   124,   119,
      81,    90,    85,   115,   116,    94,   118,    81,    81,    95,
      94,    44,    45,    97,   126,    91,    44,    45,   105,   106,
      96,    95,    90,    44,    45,    96,    94,    91,   140,   364,
     365,   366,   367,   368,   280,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,    90,    90,
     409,    90,    94,    94,    81,    94,   413,    95,    85,   418,
     417,    81,   564,    96,    97,    98,   452,   100,    96,    95,
      98,    94,   100,    81,    97,    96,   202,    98,   204,   100,
      90,    81,    94,   206,    94,    97,    81,   210,    94,   146,
      81,    97,    94,   257,     0,    97,    90,   108,   109,   110,
      96,   244,    37,    38,   224,   231,   229,   227,   224,   234,
     270,   227,     4,   418,   682,   262,   473,   236,   106,   423,
      90,   233,   240,   241,    42,    20,   430,   431,   432,   433,
     632,   243,   244,   245,    43,   521,   259,   102,   442,   373,
     374,   375,    46,    47,   264,   257,   258,   103,   264,   256,
     396,    63,    64,   104,   261,   212,    75,    76,    53,   518,
     362,   363,   369,   370,    48,   371,   372,   105,   280,     6,
      65,    66,    67,    68,    96,   401,    11,    90,   235,   236,
      90,    96,    77,    81,   541,    96,    81,    94,    83,    84,
      85,    96,    87,    96,    81,    96,    91,    99,    91,    96,
      96,    96,    96,    98,    82,    96,    96,    95,    91,    95,
     105,    96,     4,   518,   109,    95,    95,   112,    95,   383,
     277,    95,    94,    99,    95,    94,    90,    97,   532,    96,
     377,   378,   379,   380,     9,     9,   595,    96,    90,    12,
      90,    95,   601,    82,    89,    96,    94,    90,    95,    90,
      94,    97,   395,    95,    81,    89,   613,    97,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,   383,   384,    82,   393,    97,    97,    95,    92,    99,
      97,    97,    95,   395,   396,    96,    94,   106,     9,   401,
     595,   537,    90,    81,    97,    81,   655,    89,   458,   658,
     464,    92,    99,   607,   416,    82,    96,    70,    97,    74,
     536,     5,    97,    97,    97,   674,   542,   676,    97,    97,
      84,    97,    90,    95,     9,    40,    97,    97,   448,   449,
      99,    97,    89,    89,   454,    89,   393,    96,   454,   448,
     449,    90,   454,    90,    97,    97,    90,    84,   460,    99,
     393,    97,   464,   658,   466,    97,    97,    97,   470,    97,
     357,   359,   355,   376,   421,    13,   423,   424,   358,   674,
     458,   676,   361,   430,   431,   432,   433,   360,   490,    33,
     440,   421,   133,   209,   566,   442,   635,   604,   614,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   556,    -1,    -1,    -1,
     543,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   534,   535,    -1,    -1,   534,   535,
      -1,   533,   545,    -1,   536,   537,    -1,   550,    -1,    -1,
     542,   543,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   551,
     604,    -1,   565,    -1,    -1,    -1,   571,    -1,    -1,   572,
      -1,    -1,    -1,   576,    -1,   578,    -1,    -1,    -1,    -1,
     586,    -1,    -1,   583,    -1,   585,    -1,   583,    -1,   585,
      -1,    -1,   615,   616,    -1,   532,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   604,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   614,   615,   616,    -1,    -1,    -1,    -1,   566,
      -1,   634,    -1,    -1,    -1,   638,   639,   640,   682,    -1,
      -1,    -1,   645,    -1,    -1,    -1,    -1,   670,    -1,    -1,
      -1,    -1,   655,    -1,    -1,    -1,    -1,    -1,   661,   651,
      -1,    -1,   662,    -1,    -1,    -1,   662,    -1,   671,   669,
     607,    -1,    -1,   669,   697,    -1,    -1,    -1,   670,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   691,    -1,
     682,    -1,    -1,    -1,    -1,    -1,   696,    -1,   698,    -1,
     696,    -1,   698,    -1,    -1,   697,    -1,    -1,    -1,    -1,
      -1,    -1,   712,    -1,    -1,   715,   712,     0,     1,   715,
      -1,     4,    -1,     6,     7,     8,    -1,    10,    -1,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,    -1,
      83,    84,    85,    -1,    87,    -1,    -1,    90,    91,    -1,
      93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,
      -1,   104,   105,    -1,   107,   108,   109,     1,   111,   112,
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
     104,   105,   106,   107,   108,   109,   110,   111,   112,     1,
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
      93,    -1,    95,    96,    -1,    98,    -1,    -1,    -1,    -1,
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
      85,    -1,    87,    -1,    -1,    90,    91,    92,    93,    -1,
      -1,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,
     105,    -1,   107,   108,   109,     1,   111,   112,     4,    -1,
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
      -1,   107,   108,   109,     1,   111,   112,     4,    -1,     6,
       7,     8,    -1,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    -1,    83,    84,    85,    -1,
      87,    -1,    -1,    90,    91,    92,    93,    -1,    -1,    96,
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
      -1,    90,    91,    -1,    93,    -1,    -1,    96,    -1,    98,
      -1,    -1,    -1,    -1,    -1,   104,   105,     4,   107,   108,
     109,    -1,   111,   112,     4,     5,     6,     7,     8,    -1,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    81,    89,    90,    -1,    85,    86,    -1,    -1,    -1,
      -1,    -1,    92,    93,    -1,    -1,    96,    -1,    98,    -1,
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
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    81,    -1,    -1,    89,    85,
      86,    -1,    -1,    -1,    -1,    -1,    92,    93,    99,    -1,
      96,    -1,    98,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     4,     5,     6,     7,     8,
      -1,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    81,    89,    -1,    -1,    85,    86,    -1,    -1,
      -1,    97,    -1,    -1,    93,    -1,    -1,    96,    -1,    98,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      89,    -1,    -1,    85,    86,    -1,    95,    -1,    -1,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    89,    -1,    -1,
      -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,
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
      -1,    -1,    93,    -1,    -1,    20,    -1,    98,    23,    24,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    21,    -1,    23,    24,
      -1,    76,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    99,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    90,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    76,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    99,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    76,    77,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    76,    77,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    77,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    76,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    -1,    87,    -1,    -1,    -1,    91,    -1,    93,    -1,
      95,    96,    20,    98,    -1,    23,    24,    -1,    -1,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    91,    -1,    93,    -1,    95,    96,    20,
      98,    -1,    23,    24,    -1,    -1,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,    -1,
      91,    -1,    93,    -1,    95,    96,    20,    98,    -1,    23,
      24,    -1,    -1,   104,   105,    -1,   107,   108,   109,    -1,
     111,   112,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    -1,    87,    -1,    -1,    -1,    91,    -1,    93,
      -1,    -1,    96,    -1,    98,    20,    -1,    -1,    23,    24,
     104,   105,    -1,   107,   108,   109,    31,   111,   112,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    76,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    -1,    87,    -1,    -1,    -1,    91,    -1,    93,    44,
      45,    96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    -1,    87,    -1,    -1,    -1,    91,    -1,    93,    -1,
      -1,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,
     105,    -1,   107,   108,   109,    -1,   111,   112
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
      67,    68,    69,    81,    85,    86,    93,    98,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   180,   193,   193,
     193,    81,   144,   177,   144,   146,    81,    81,   141,    81,
      81,    81,    96,   165,   165,   182,    21,    96,    96,   183,
      81,   119,   119,    90,    95,     4,     6,     7,     8,    10,
      13,    14,    15,    16,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    36,    65,    66,
      67,    68,    76,    81,    85,    92,    93,    96,    98,   104,
     105,   107,   108,   109,   115,   178,   179,   180,   165,    82,
      91,   146,   148,    76,    99,   146,   175,    96,   117,   106,
     172,   165,   164,   182,   164,     4,     5,     6,     7,     8,
      10,    11,    12,    13,    14,    15,    16,    17,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    36,    37,    38,    39,    40,    41,    65,    66,    67,
      68,    69,    81,    86,    93,    98,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   169,     0,   116,   145,    90,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    89,   145,    49,   101,    42,    43,   102,
     103,   104,    37,    38,    39,    40,    41,   105,   106,    46,
      47,    93,   107,   108,   109,   110,    48,    63,    64,    75,
      76,    44,    45,    96,    98,   100,   166,   105,   190,   146,
     176,   176,     6,    21,    81,    90,    98,   130,   176,    11,
     132,    96,   145,    90,   145,    90,   176,    81,    96,    89,
      95,   190,    81,   121,    92,    90,    94,   175,    89,    95,
      90,    94,    90,    96,    76,   168,   198,   199,   200,    99,
      96,    96,    96,    96,   197,   145,   145,   117,    90,    94,
     197,   117,    96,   198,   183,    81,    96,    82,    91,    91,
     116,   147,   148,   149,    95,    82,    99,    92,    94,   174,
      95,    97,    92,    97,    96,    97,    98,   100,   166,   147,
      94,   174,   198,   175,   183,    99,    90,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
      31,   147,   152,   149,   153,   154,   155,   156,   157,   158,
     158,   159,   159,   159,   159,   159,   160,   160,   161,   161,
     162,   162,   162,   163,   164,   164,   164,   164,    76,    82,
     146,   148,   204,   205,   206,   146,    86,   169,    23,    85,
     201,    81,    96,    94,    97,    97,    96,    98,   130,   185,
     144,   175,     9,    90,    96,    12,   133,   176,    90,    90,
      97,    95,    82,    89,    94,   174,    91,   146,   174,   147,
     201,   186,   198,   168,    95,    97,    94,   198,   198,   198,
     198,    95,   196,    90,    90,    81,   196,   198,    97,    89,
      82,    97,    92,   115,    92,   115,   146,    97,   179,    92,
     146,   204,   146,    86,   169,    76,   146,    99,    97,   174,
     146,    95,   147,    97,    94,    99,   106,    96,   198,   146,
     116,   116,   176,   175,     9,    90,    90,   174,   176,   144,
      81,   117,    97,   117,   146,    97,    84,    93,    81,    92,
      92,    99,    96,   202,    97,   201,   117,   200,    97,    97,
      97,    97,   167,   117,   117,    97,   117,    82,    97,    92,
      92,    95,    97,    99,   147,    70,    74,   149,    76,   206,
     198,    97,     5,    97,   174,   176,   144,   144,    99,    97,
      90,    97,    84,    89,    89,   201,    89,   117,   202,   117,
     117,   117,    96,   203,   117,    90,    97,   146,   117,   149,
     147,    97,   117,   116,    90,    99,    97,    90,    97,   116,
     144,   117,    84,    93,   147,    97,   147,   204,   117,   116,
     144,   116,    97,    84,    97,    97,   116,   116
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
     169,   169,   169,   169,   169,   169,   169,   169,   170,   170,
     171,   171,   172,   173,   174,   174,   175,   175,   175,   175,
     176,   176,   177,   177,   177,   177,   178,   178,   179,   179,
     179,   179,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   181,   181,   181,   182,   183,   184,   184,   185,   185,
     186,   186,   186,   186,   186,   187,   187,   188,   188,   188,
     189,   190,   190,   191,   191,   191,   191,   191,   191,   192,
     192,   192,   193,   193,   194,   194,   195,   195,   196,   196,
     197,   197,   198,   198,   199,   199,   200,   200,   200,   201,
     201,   202,   202,   203,   203,   204,   204,   205,   205,   205,
     205,   206,   206,   206
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
       1,     1,     1,     1,     1,     1,     1,     2,     2,     4,
       2,     5,     0,     4,     0,     1,     1,     2,     3,     4,
       1,     3,     1,     2,     3,     4,     1,     3,     5,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     2,     0,     3,     3,     3,     1,     3,
       1,     4,     3,     6,     6,     1,     1,     6,     6,     7,
       1,     0,     3,     5,     5,     6,     6,     6,     2,     6,
       6,     6,     1,     1,     5,     5,     3,     3,     0,     3,
       0,     3,     0,     1,     1,     3,     1,     4,     2,     1,
       1,     0,     3,     0,     3,     0,     1,     1,     2,     3,
       4,     1,     1,     1
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
#line 2460 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 140 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2466 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 163 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2472 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 164 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2478 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 168 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2484 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 169 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2490 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 173 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2496 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 174 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2502 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 175 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2508 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 176 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2514 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 180 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2520 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 184 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2526 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 188 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2532 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 189 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2538 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 190 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2544 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 191 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2550 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 192 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2556 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 193 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2562 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 204 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2568 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 208 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2574 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 209 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2580 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 213 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2586 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 217 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2592 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 221 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2598 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 225 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2604 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 226 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2610 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 231 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2621 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 238 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2632 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 245 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2643 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 252 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 2649 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 254 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 2655 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 258 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 2661 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 259 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 2667 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 263 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2673 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 267 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2679 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 268 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2685 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 272 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2691 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 273 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2697 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 277 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2703 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 278 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2709 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 279 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2715 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 280 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2721 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 284 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2727 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 285 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); }
#line 2733 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 289 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_COROUTINE, (yyvsp[-1].obj), NULL, NULL); }
#line 2739 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 293 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2745 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 297 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2751 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 298 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2757 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 299 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2763 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 300 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2769 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 304 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2775 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 308 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2781 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 312 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2787 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 313 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2793 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 317 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2799 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 321 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2805 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 322 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2811 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 326 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2817 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 331 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2823 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 332 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2829 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 337 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2835 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 338 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2841 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 339 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2847 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 340 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2853 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 341 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2859 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 342 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2865 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 343 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2871 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 344 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2877 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 345 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2883 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 346 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2889 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 347 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2895 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 348 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2901 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 349 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2907 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 350 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2913 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 359 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2919 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 360 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2925 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 361 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2931 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 362 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2937 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 363 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2943 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 364 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2949 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 369 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2955 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 379 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2961 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 384 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2967 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 389 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2973 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 394 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2979 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 399 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2985 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 404 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2991 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 409 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2997 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 410 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3003 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 415 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3009 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 416 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3015 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 417 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3021 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 418 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3027 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 419 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3033 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 424 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3039 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 425 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3045 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 430 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3051 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 431 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3057 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 436 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3063 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 437 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3069 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 438 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3075 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 443 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3081 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 448 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3087 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 449 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3093 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 450 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-1].obj), kx_gen_special_object(KXVL_NULL), 0); }
#line 3099 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 451 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 3105 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 452 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-1].obj), kx_gen_special_object(KXVL_NULL), 1); }
#line 3111 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 453 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 3117 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 458 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 3123 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 459 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 3129 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 460 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 3135 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 461 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 3141 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 462 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 3147 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 463 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 3153 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 468 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 3159 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 469 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3165 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 470 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3171 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 471 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3177 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 472 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3183 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 476 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3189 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 477 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3195 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 481 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3201 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 482 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3207 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 483 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3213 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 484 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3219 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 485 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3225 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3231 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3237 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 492 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3243 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 493 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3249 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 494 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3255 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3261 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3267 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3273 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3279 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 502 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3285 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3291 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 507 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3297 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3303 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3309 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 510 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3315 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 511 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3321 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 512 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3327 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 513 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3333 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3339 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 515 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3345 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 516 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3351 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 517 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3357 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 518 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3363 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 519 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3369 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3375 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 521 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3381 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 522 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3387 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 523 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3393 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 524 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3399 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 525 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3405 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 526 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3411 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 527 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3417 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 528 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3423 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 529 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3429 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 530 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3435 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 531 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3441 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 532 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3447 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 533 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("yield"); }
#line 3453 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 534 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3459 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 535 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3465 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 536 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3471 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 537 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3477 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3483 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 539 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3489 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 540 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("=="); }
#line 3495 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 541 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("!="); }
#line 3501 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 542 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<="); }
#line 3507 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 543 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<"); }
#line 3513 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 544 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">="); }
#line 3519 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">"); }
#line 3525 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 546 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<=>"); }
#line 3531 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 547 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("+"); }
#line 3537 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 548 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("-"); }
#line 3543 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 549 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("*"); }
#line 3549 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 550 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("/"); }
#line 3555 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 551 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("%"); }
#line 3561 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 552 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("&"); }
#line 3567 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 553 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("|"); }
#line 3573 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 554 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("^"); }
#line 3579 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 555 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("[]"); }
#line 3585 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 559 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3591 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 560 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3597 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 564 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3603 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 565 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3609 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 569 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3615 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 573 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3621 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 577 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3627 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 583 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3633 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 584 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3639 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 585 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3645 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 590 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3651 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 595 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3657 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 596 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3663 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 597 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3669 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 602 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3675 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 606 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3681 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 607 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3687 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 608 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3693 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3699 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 613 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3705 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 614 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3711 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 615 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3717 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 616 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3723 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 617 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3729 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 618 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3735 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 619 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3741 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 620 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3747 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 621 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3753 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 622 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3759 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 623 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3765 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 624 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3771 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 625 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3777 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 626 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3783 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 627 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3789 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 628 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3795 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 629 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3801 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 630 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3807 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 631 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3813 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 632 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3819 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3825 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 634 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3831 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 635 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3837 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 636 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3843 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 637 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3849 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 638 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3855 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 639 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3861 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 640 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3867 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3873 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3879 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 643 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3885 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3891 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3897 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "=="; }
#line 3903 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 647 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "!="; }
#line 3909 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 648 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<="; }
#line 3915 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 649 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<"; }
#line 3921 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">="; }
#line 3927 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 651 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">"; }
#line 3933 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 652 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<=>"; }
#line 3939 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 653 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "+"; }
#line 3945 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 654 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "-"; }
#line 3951 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "*"; }
#line 3957 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "/"; }
#line 3963 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "%"; }
#line 3969 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 658 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "&"; }
#line 3975 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 659 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "|"; }
#line 3981 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 660 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "^"; }
#line 3987 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 661 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "[]"; }
#line 3993 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 665 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3999 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 666 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 4005 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 667 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4011 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 671 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 4017 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 675 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 4023 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 679 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4029 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 680 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 4035 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 685 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4041 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 689 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 4047 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 690 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 4053 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 691 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 4059 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 692 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 4065 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 693 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 4071 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 697 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4077 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 698 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4083 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 702 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4089 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 703 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4095 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 704 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4101 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 708 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 4107 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 712 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 4113 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 713 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4119 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 717 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4125 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 718 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4131 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 719 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4137 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 720 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 4143 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 721 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 4149 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 722 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 4155 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 726 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4161 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 727 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4167 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 728 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4173 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 737 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4179 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 738 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4185 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 742 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4191 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 743 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4197 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 747 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4203 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 749 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 4216 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 760 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4222 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 761 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4228 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 765 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4234 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 771 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4240 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 775 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4246 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 776 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 4252 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 777 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 4258 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 781 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 4264 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 782 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 4270 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 786 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 4276 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 787 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4282 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 791 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4288 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 792 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4294 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 796 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4300 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 802 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 4306 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 803 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 4312 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 804 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 4318 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 810 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 4324 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 4328 "kx.tab.c" /* yacc.c:1646  */
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
#line 813 "src/kinx.y" /* yacc.c:1906  */


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
