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
    FUNCTION = 278,
    PUBLIC = 279,
    PRIVATE = 280,
    PROTECTED = 281,
    CLASS = 282,
    RETURN = 283,
    THROW = 284,
    YIELD = 285,
    MODULE = 286,
    MIXIN = 287,
    SYSCLASS = 288,
    SYSMODULE = 289,
    SYSFUNC = 290,
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
    DOTS2 = 329,
    DOTS3 = 330,
    REGPF = 331,
    NAMESPACE = 332,
    SYSNS = 333,
    SYSRET_NV = 334,
    NAME = 335,
    STR = 336,
    BIGINT = 337,
    INT = 338,
    TYPE = 339,
    TYPEOF = 340,
    DBL = 341,
    BIN = 342
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

#line 226 "kx.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE kx_yylval;

int kx_yyparse (void);

#endif /* !YY_KX_YY_KX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 243 "kx.tab.c" /* yacc.c:358  */

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
#define YYFINAL  277
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3388

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  96
/* YYNRULES -- Number of rules.  */
#define YYNRULES  348
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  682

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   342

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   110,     2,     2,     2,   109,   103,     2,
      95,    96,   107,   106,    93,    92,    99,   108,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    94,    89,
     104,    88,   105,   100,   111,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    97,     2,    98,   102,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    90,   101,    91,     2,     2,     2,     2,
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
      85,    86,    87
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   137,   137,   141,   142,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   170,   171,   175,   176,
     177,   178,   182,   186,   190,   191,   192,   193,   194,   195,
     199,   200,   201,   202,   206,   210,   211,   215,   219,   223,
     227,   228,   232,   239,   246,   256,   260,   261,   265,   266,
     270,   271,   272,   273,   277,   278,   282,   286,   290,   291,
     292,   293,   297,   301,   305,   306,   310,   314,   315,   319,
     320,   324,   325,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   347,   348,
     352,   353,   354,   355,   356,   357,   361,   362,   366,   367,
     371,   372,   376,   377,   381,   382,   386,   387,   391,   392,
     396,   397,   401,   402,   403,   407,   408,   409,   410,   411,
     412,   416,   417,   418,   422,   423,   424,   428,   429,   430,
     431,   435,   436,   440,   441,   442,   446,   447,   448,   449,
     450,   451,   452,   453,   457,   458,   459,   460,   461,   462,
     466,   467,   471,   472,   476,   477,   481,   482,   483,   484,
     485,   486,   487,   488,   492,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   513,   514,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   554,   555,   559,
     560,   564,   568,   572,   573,   577,   578,   579,   580,   584,
     585,   589,   590,   591,   592,   596,   597,   601,   602,   603,
     604,   608,   609,   610,   611,   612,   613,   614,   615,   616,
     617,   618,   619,   620,   621,   622,   623,   624,   625,   626,
     627,   628,   629,   630,   631,   632,   633,   634,   635,   636,
     637,   638,   639,   640,   644,   645,   646,   650,   654,   658,
     659,   663,   664,   668,   669,   670,   671,   672,   676,   677,
     681,   682,   683,   687,   691,   692,   696,   697,   698,   699,
     700,   701,   705,   706,   707,   711,   712,   716,   717,   721,
     722,   734,   735,   739,   740,   744,   745,   749,   750,   751,
     755,   756,   760,   761,   765,   766,   770,   771,   775,   776,
     777,   778,   782,   783,   784,   788,   789,   790,   791
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
  "PrefixExpression", "PostfixExpression", "PostIncDec", "Range",
  "RangeFactor_Opt", "RangeFactor", "Factor", "VarName", "PropertyName",
  "Array", "Binary", "BinStart", "Object", "Comma_Opt", "ArrayItemList",
  "AssignExpressionList", "AssignExpressionObjList", "KeyValueList",
  "KeyValue", "KeySpecialName", "Regex", "RegexStart", "RegexString",
  "VarDeclStatement", "DeclAssignExpressionList", "DeclAssignExpression",
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
     335,   336,   337,   338,   339,   340,   341,   342,    61,    59,
     123,   125,    45,    44,    58,    40,    41,    91,    93,    46,
      63,   124,    94,    38,    60,    62,    43,    42,    47,    37,
      33,    64
};
# endif

#define YYPACT_NINF -416

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-416)))

#define YYTABLE_NINF -283

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1654,   -26,   -15,    28,  1654,    75,   -19,    20,    22,    86,
    2414,     1,    -1,  2464,  2663,   -28,   -28,  -416,    -5,    21,
      23,    83,   110,  2464,  2464,  2414,   125,   142,   144,   158,
      44,  2663,  2663,  -416,   122,   179,   192,     3,   155,   168,
     168,   147,   162,   194,   196,  -416,   198,   790,  2663,  1904,
    1704,    62,   173,  2663,   394,  -416,   394,  3139,   258,   682,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,   276,  -416,  -416,
    -416,   216,  2853,  -416,  -416,    -6,   246,   273,   215,   217,
     214,   174,    27,   231,   -24,   153,   271,   220,  -416,    61,
    -416,   211,  -416,   229,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,   218,  -416,  -416,  -416,  -416,  -416,  2414,  2414,   314,
    1754,   898,   311,   234,   276,   237,   276,   243,  2414,   238,
     239,   240,  -416,  3047,  3290,   218,  -416,   256,  2771,  2772,
      80,  -416,  -416,  -416,  -416,  -416,  -416,  1904,  -416,  -416,
      -7,  1954,    87,  -416,    93,   242,     4,   244,   245,   247,
     250,   276,   248,   276,  2772,   -19,  -416,   106,   250,   -19,
     251,     4,    61,    61,   155,   268,   254,   257,  -416,  -416,
     260,   261,  -416,  1654,   -15,  -416,    28,  1006,    75,   -19,
    -416,  -416,    40,    47,    86,  2414,  2663,   -28,   -28,   259,
      -5,    21,    23,    83,   110,  2004,  2081,  2158,   125,    44,
     -34,    68,   104,     3,  -416,    57,   262,   263,  -416,  -416,
    2235,  1114,   265,  -416,   266,    61,   267,  2863,  3037,    49,
      57,  -416,  2772,   269,     4,  -416,  -416,  1954,    61,  -416,
     155,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,   270,
    -416,  2514,  2514,  2514,  2514,  2514,  2514,  2514,  2514,  2514,
    2514,  2514,  2514,  2514,  2314,  -416,   394,  2414,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
    -416,  -416,  1804,  2414,  3221,  -416,   -10,   -10,    13,    69,
    2772,    37,   141,   272,   -28,  2464,   119,   289,   343,  2414,
     279,  -416,   296,  -416,   150,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,   292,  -416,   274,  2514,  -416,   294,   277,   299,
    -416,  -416,  2564,  3126,  2514,    13,   269,  -416,   -28,  -416,
       4,   143,   303,   302,   306,  -416,     4,     4,     4,     4,
     307,   313,   317,  -416,  -416,   281,   307,  -416,     4,   312,
    -416,   315,   326,   316,  1222,  1330,  -416,  -416,  -416,  -416,
    -416,  -416,  1654,   320,  -416,  3047,   319,  2414,  -416,  -416,
     232,  1804,  -416,  2414,  3303,  -416,  -416,  2364,   325,   322,
     269,  -416,  -416,  -416,   107,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  2414,  -416,
     246,   323,   273,   215,   217,   214,   174,    27,    27,   231,
     231,   231,   231,   231,   -24,   -24,   153,   153,   271,   271,
     271,   220,  -416,  -416,    57,  -416,  2772,   107,   332,   318,
    -416,   321,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    2414,  -416,  -416,  -416,  -416,  -416,  -416,   327,   338,     4,
    2414,  1654,  1654,  2414,   136,   345,  2464,   356,   -19,  -416,
     151,  -416,  -416,   -19,  2414,   344,   -49,   362,   352,  2955,
    2772,  -416,  -416,   349,   350,  -416,   351,  -416,    13,   -19,
       4,   353,   354,   357,   358,  2663,   -19,  -416,  -416,  -416,
     -19,   359,   -19,   371,   360,  -416,  -416,  1438,  -416,  1546,
    2759,   363,  -416,  -416,  2772,   366,  2943,  -416,  -416,    57,
    2772,  -416,   395,   390,  2772,  2414,  -416,  -416,  1854,  -416,
    3208,  -416,     4,   369,  2772,   462,  -416,   156,  2464,  2464,
     382,   376,  -416,  -416,  -416,  2772,   363,  -416,   392,   385,
    -416,  -416,    13,   391,   393,   -19,   349,  -416,  -416,   -19,
     -19,   -19,  -416,   387,  -416,  -416,   -19,  -416,   396,   397,
    -416,  -416,  2414,  -416,  -416,  -416,  2614,  -416,  -416,    57,
    -416,  -416,   398,   -19,  1654,   399,   401,   400,  2464,   -19,
    -416,    82,   403,  2514,  2514,  -416,  -416,  -416,  -416,  -416,
    1804,  -416,  -416,  -416,  -416,  2772,  -416,  -416,  -416,   -19,
    -416,  -416,  -416,  2464,  1654,   407,  -416,  -416,   404,  -416,
    -416,  -416,   411,  -416,   413,  -416,  1654,  -416,  -416,  1654,
    -416,  -416
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    81,    81,     0,
       0,     0,     0,     0,     0,     0,     0,   303,     0,     0,
       0,     0,     0,    79,    79,    69,     0,     0,     0,     0,
       0,     0,     0,   287,   177,   179,   180,     0,     0,     0,
       0,     0,   192,   176,   174,   193,   175,     0,     0,     0,
       0,     0,   231,     0,     0,   287,     0,     0,     0,     0,
       3,     5,     6,     7,    21,    23,     8,     9,    10,    11,
      12,    13,    14,    22,    15,    16,    17,    81,    18,    19,
      20,     0,    81,    83,   106,   109,   110,   112,   114,   116,
     118,   120,   122,   125,   131,   134,   137,   141,   143,   146,
     147,     0,   154,   178,   181,   182,   183,   184,    40,    41,
     298,   304,   108,   299,    42,    43,    25,     0,     0,     0,
       0,     0,    56,     0,    81,     0,    81,     0,     0,     0,
       0,     0,   192,     0,     0,   304,    51,     0,     0,   241,
       0,   177,   179,   180,   176,   174,   175,     0,   189,   178,
     293,     0,     0,   291,     0,     0,   323,     0,     0,     0,
     321,    81,    80,    81,    68,     0,    74,     0,   321,     0,
       0,   323,   152,   153,     0,     0,     0,     0,   286,    32,
       0,     0,    65,     0,   251,   252,   253,     0,   255,   256,
     257,   258,    81,    81,   261,   262,   263,   264,   265,   303,
     267,   269,   270,   271,   272,    79,    79,    69,   273,   268,
     177,   179,   180,   280,   281,     0,   192,   193,   283,    26,
       0,     0,   233,   245,     0,   150,     0,     0,     0,     0,
       0,   227,   235,   233,   323,   311,   229,     0,   149,   151,
       0,   148,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     214,   215,   216,   217,   219,   221,   220,   218,   213,   222,
     223,   224,   225,   226,   194,   191,   190,     1,     4,     0,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     160,   161,   336,     0,     0,   155,   164,   164,     0,     0,
     239,     0,     0,     0,     0,    79,     0,     0,    58,     0,
       0,    60,     0,    62,     0,   251,   253,   254,   255,   256,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   269,
     270,   271,   272,   274,   276,   275,   273,   268,   277,   278,
     279,   280,     0,   282,     0,     0,    50,     0,    34,   233,
     242,    66,     0,     0,     0,     0,   233,   289,     0,   290,
     323,     0,   327,     0,   324,   325,   323,   323,   323,   323,
     319,     0,     0,   317,    73,     0,   319,   318,   323,     0,
     285,     0,     0,     0,     0,     0,    44,   345,   346,   347,
     348,   250,     0,     0,    27,   234,     0,     0,   188,   100,
     186,   336,   187,     0,     0,   101,   236,   234,     0,     0,
     233,   284,    67,    87,    99,    98,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    85,    86,    71,    84,
     111,     0,   113,   115,   117,   119,   121,   123,   124,   127,
     129,   130,   126,   128,   132,   133,   136,   135,   138,   139,
     140,   142,   144,   145,     0,   344,   342,   343,     0,   337,
     338,     0,   158,   157,   169,   171,   172,   168,   166,   167,
       0,   162,   165,   170,   163,   331,   330,     0,     0,   323,
       0,     0,     0,     0,     0,     0,    79,     0,     0,    55,
       0,    61,    63,     0,     0,     0,     0,   234,     0,     0,
     243,   186,   295,   332,     0,   292,     0,   329,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,    72,    75,
       0,     0,     0,     0,     0,   288,    28,     0,    29,     0,
     248,   188,   246,   232,   249,     0,     0,   104,   103,     0,
     237,   228,     0,     0,    70,     0,   339,   159,     0,   156,
       0,   305,   323,     0,   240,    45,    47,     0,    79,    79,
       0,     0,    59,    82,    49,   248,     0,    35,     0,    37,
      33,   244,     0,   294,     0,     0,   332,   306,   326,     0,
       0,     0,   322,   334,   315,   316,     0,   307,     0,     0,
      30,    31,     0,   105,   102,   238,     0,   230,   107,     0,
     340,   173,     0,     0,     0,     0,     0,     0,    79,     0,
      36,     0,     0,     0,     0,   300,   328,   312,   313,   314,
     336,   320,   301,    24,   185,   247,   310,   309,   341,     0,
     308,    46,    48,    79,     0,     0,    57,    38,     0,   333,
     296,   297,     0,   302,     0,    54,     0,    39,   335,     0,
      53,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -416,  -416,     6,     5,     2,  -416,   443,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
     -21,    14,     8,     7,   -48,  -175,  -416,  -416,   201,   212,
     193,   213,   221,   224,     9,   -89,    -2,    15,   -51,   197,
     -17,    30,  -212,  -416,   188,   -16,   -12,    -3,  -305,  -205,
    -203,  -416,  -200,  -185,  -102,   -82,   506,  -416,    98,  -416,
    -416,   472,  -154,  -416,    -9,   140,  -416,  -416,     0,   405,
    -416,  -416,  -416,  -416,   123,   367,  -157,  -416,    -4,  -372,
     -75,  -416,  -415,  -416,   -44,  -225
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    58,   221,    60,    61,    62,   180,    63,   379,    64,
      65,    66,    67,    68,    69,    70,    71,    72,   338,   519,
      73,    74,    75,    76,    77,    78,    79,   167,    80,    81,
     161,   125,    82,   459,   444,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   325,   100,   501,   101,   102,   103,   276,   104,
     105,   237,   106,   426,   233,   331,   162,   222,   223,   224,
     107,   174,   178,   108,   152,   153,   109,   110,   135,   329,
     112,   113,   114,   115,   546,   400,   393,   394,   395,   507,
     603,   651,   488,   489,   490,   421
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     111,   229,   148,   163,   111,   436,    59,   154,   122,   119,
     418,   149,   419,   533,   409,   420,   565,   435,   134,   493,
     410,   139,   127,   175,   123,   418,   123,   419,   149,   149,
     420,   139,   139,   164,   597,   505,   332,   239,   336,   241,
    -169,  -169,   296,   598,   123,   149,   344,   111,   438,   386,
     149,   123,   150,   235,   494,   495,   496,   228,   232,   111,
    -277,   172,   173,   116,   278,   305,   306,   307,   312,   151,
     132,   121,   497,   498,    45,   155,   499,   439,   225,   391,
     117,   384,   313,   238,   132,   500,   441,   385,    45,   137,
     156,   279,   320,   321,   297,   136,   295,   506,   176,   229,
     124,   157,   126,   158,   320,   321,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     124,   111,   461,   118,   170,   330,   330,   126,   330,   568,
     510,   308,   309,   511,  -259,   440,   330,   417,   340,   171,
     342,  -260,  -171,  -171,   431,   432,   433,   133,   434,   508,
     320,   321,   121,   392,    50,   383,   322,   234,   323,   232,
     324,    52,  -278,   159,   509,   667,   606,   403,   392,   381,
     120,   407,   229,   382,   668,   401,   387,   402,  -172,  -172,
     388,   128,   389,   111,   148,   163,   388,   111,   416,   154,
     160,   122,   119,   149,   528,   404,  -169,  -169,  -279,   405,
     445,   534,   431,   134,   433,   165,   434,   127,   516,   445,
     303,   304,   510,   139,   139,   164,   469,   470,   471,   472,
     473,   111,   166,   132,   168,   588,   278,    45,   228,   388,
     642,   392,   435,   536,   510,   672,   182,   512,   169,   541,
     542,   543,   544,   510,   510,   232,   523,   593,   179,   510,
     177,   551,   635,  -171,  -171,   573,   183,   520,   277,   576,
     314,   315,   316,   478,   479,   480,  -172,  -172,  -168,  -168,
    -166,  -166,  -167,  -167,   487,   435,   310,   311,   236,   418,
     123,   419,   318,   319,   420,   326,   327,   298,   443,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   482,   483,  -170,  -170,   280,  -173,  -173,   474,   475,
     502,   502,   467,   468,   515,   299,   300,   302,   317,   301,
     333,   337,   328,   503,   503,   514,   341,   476,   477,   339,
     486,   491,   343,   156,   171,   176,   378,   390,   413,   396,
     397,   382,   398,   139,   625,   399,   408,   330,   411,   412,
     414,   415,   583,  -266,   518,   525,   422,  -282,   425,   442,
     427,   549,   437,   428,   418,   526,   419,   513,   521,   420,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   487,   517,   522,   524,   392,   537,   509,
     530,   532,   527,   392,   392,   392,   392,   538,   539,   540,
     628,   545,   547,   553,   658,   392,   548,   554,   552,   375,
     563,   578,   555,    14,   111,   111,   561,   575,   572,   579,
     557,   559,   111,   571,   418,   632,   419,   416,   577,   420,
     560,   587,   581,   582,   589,   564,   591,    31,    32,   486,
     596,   566,   599,   600,   602,   570,    33,   605,   604,   609,
     610,   657,   618,   611,   612,   616,   619,   622,    34,    35,
      36,   131,   623,   627,   626,   633,   574,   634,   445,   445,
      38,   638,   639,   641,   132,   640,    43,    44,    45,   643,
      46,   644,   650,   181,   133,   653,    48,   677,   662,    49,
     663,    50,   463,   654,   659,   590,   664,   460,    52,   669,
      53,    54,    55,   676,    56,    57,   392,   678,   580,   679,
     462,   111,   111,   464,   481,   504,   585,   586,   584,   140,
     592,   330,   465,   562,   139,   594,   466,   240,   535,   550,
     487,   646,   595,   613,   630,   406,   608,   392,     0,     0,
     377,   607,   149,     0,     0,     0,     0,     0,   614,     0,
       0,     0,   615,     0,   617,     0,     0,   111,     0,   111,
       0,     0,   278,     0,   278,     0,     0,   636,   637,     0,
       0,     0,     0,     0,   295,     0,     0,     0,     0,   392,
       0,     0,     0,     0,     0,     0,   486,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   139,   139,     0,     0,
       0,     0,   487,     0,     0,     0,     0,   645,     0,     0,
       0,   647,   648,   649,     0,     0,     0,   665,   652,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   656,     0,
     655,     0,     0,     0,   111,   660,     0,     0,     0,   661,
       0,   666,   674,     0,     0,     0,   139,     0,     0,     0,
     670,   671,     0,     0,     0,     0,     0,     0,   486,     0,
       0,   673,     0,     0,   111,     0,     0,     0,     0,   675,
       0,   139,     0,     0,     0,     0,   111,     0,     0,   111,
       0,   680,    -2,     1,   681,     0,     2,     0,     3,     4,
       5,     6,     0,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    42,     0,    43,    44,    45,     0,    46,     0,
       0,   -77,    47,     0,    48,     0,     0,    49,     0,    50,
       0,     0,     0,     0,     0,    51,    52,     0,    53,    54,
      55,     1,    56,    57,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,    11,    12,    13,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,    27,    28,    29,   209,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   210,   211,   212,   213,   214,     0,
       0,     0,     0,     0,     0,   215,    38,    39,    40,    41,
     216,     0,    43,    44,   217,   218,    46,     0,     0,   -77,
      47,   219,    48,     0,     0,   220,     0,    50,     0,     0,
       0,     0,     0,    51,    52,     0,    53,    54,    55,     1,
      56,    57,     2,     0,     3,     4,     5,     6,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,     0,     0,   -77,    47,   219,
      48,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,     1,    56,    57,
       2,     0,     3,     4,     5,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,    42,     0,    43,    44,
      45,     0,    46,     0,     0,   -77,    47,     0,    48,     0,
    -254,    49,     0,    50,     0,     0,     0,     0,     0,    51,
      52,     0,    53,    54,    55,     1,    56,    57,     2,     0,
       3,     4,     5,     6,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,    42,     0,    43,    44,    45,     0,
      46,     0,     0,   -77,    47,   424,    48,     0,     0,    49,
       0,    50,     0,     0,     0,     0,     0,    51,    52,     0,
      53,    54,    55,     1,    56,    57,     2,     0,     3,     4,
       5,     6,     0,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    42,     0,    43,    44,    45,     0,    46,     0,
       0,   -77,    47,   556,    48,     0,     0,    49,     0,    50,
       0,     0,     0,     0,     0,    51,    52,     0,    53,    54,
      55,     1,    56,    57,     2,     0,     3,     4,     5,     6,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
      42,     0,    43,    44,    45,     0,    46,     0,     0,   -77,
      47,   558,    48,     0,     0,    49,     0,    50,     0,     0,
       0,     0,     0,    51,    52,     0,    53,    54,    55,     1,
      56,    57,     2,     0,     3,     4,     5,     6,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,     0,     0,   -77,    47,   620,
      48,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,     1,    56,    57,
       2,     0,     3,     4,     5,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,    42,     0,    43,    44,
      45,     0,    46,     0,     0,   -77,    47,   621,    48,     0,
       0,    49,     0,    50,     0,     0,     0,     0,     0,    51,
      52,     0,    53,    54,    55,     1,    56,    57,     2,     0,
       3,     4,     5,     6,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,    37,     0,    14,     0,     0,    17,   129,     0,     0,
      38,    39,    40,    41,    42,     0,    43,    44,    45,   130,
      46,     0,     0,   -77,    47,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,   334,     0,    17,   129,     0,   230,
      38,     0,     0,     0,   132,     0,    43,    44,    45,   130,
      46,     0,     0,     0,   133,     0,    48,    31,    32,    49,
       0,    50,   231,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,     0,
      38,     0,     0,     0,   132,     0,    43,    44,    45,   130,
      46,     0,     0,   335,   133,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,   484,
      38,     0,     0,     0,   132,   485,    43,    44,    45,   130,
      46,     0,     0,     0,   227,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,   629,
      38,     0,     0,     0,   132,   485,    43,    44,    45,   130,
      46,     0,     0,     0,   227,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,     0,
      38,     0,     0,     0,   132,   226,    43,    44,    45,   130,
      46,     0,     0,     0,   227,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,   230,
      38,     0,     0,     0,   132,     0,    43,    44,    45,   130,
      46,     0,     0,     0,   133,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,   132,     0,    43,    44,    45,     0,
      46,     0,     0,     0,   138,     0,    48,     0,  -274,    49,
      14,    50,     0,    17,   129,     0,     0,    51,    52,     0,
      53,    54,    55,     0,    56,    57,   130,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,   131,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,   132,     0,    43,    44,    45,     0,    46,     0,     0,
       0,   138,     0,    48,     0,  -276,    49,    14,    50,     0,
      17,   129,     0,     0,    51,    52,     0,    53,    54,    55,
       0,    56,    57,   130,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,   131,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,   132,     0,
      43,    44,    45,     0,    46,     0,     0,     0,   133,     0,
      48,     0,  -275,    49,    14,    50,     0,    17,   129,     0,
       0,    51,    52,     0,    53,    54,    55,     0,    56,    57,
     130,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,   131,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,   132,   423,    43,    44,    45,
       0,    46,     0,     0,     0,   227,     0,    48,     0,     0,
      49,     0,    50,    14,     0,     0,    17,   129,    51,    52,
       0,    53,    54,    55,   458,    56,    57,     0,     0,   130,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,     0,
      38,     0,     0,     0,   132,     0,    43,    44,    45,   130,
      46,     0,     0,     0,   227,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,   569,
      38,     0,     0,     0,   132,     0,    43,    44,    45,   130,
      46,     0,     0,     0,   133,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,     0,
      38,     0,     0,     0,   132,     0,    43,    44,    45,   130,
      46,     0,     0,     0,   133,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,     0,
      38,     0,     0,     0,   132,     0,    43,    44,    45,   130,
      46,     0,     0,     0,   138,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,     0,
      38,     0,     0,     0,   132,     0,    43,    44,    45,   130,
      46,     0,     0,     0,   227,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,     0,    14,     0,     0,    17,   129,     0,     0,
      38,     0,     0,     0,   132,     0,    43,    44,    45,   130,
      46,     0,     0,     0,   529,     0,    48,    31,    32,    49,
       0,    50,     0,     0,     0,     0,    33,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,     0,    34,    35,
      36,   131,    14,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,   132,     0,    43,    44,    45,     0,
      46,     0,     0,     0,    47,     0,    48,     0,     0,    49,
       0,    50,     0,     0,     0,    33,     0,    51,    52,     0,
      53,    54,    55,     0,    56,    57,     0,   141,   142,   143,
     131,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,   132,     0,   144,   145,    45,     0,   146,
       0,     0,     0,   133,     0,     0,     0,     0,   147,     0,
      50,     0,     0,   123,     0,     0,     0,    52,     0,     0,
       0,    55,     0,     0,    57,   345,   185,   346,   347,   348,
     349,   190,   191,   350,   351,   352,   353,     0,     0,     0,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,     0,     0,     0,   367,     0,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,     0,   368,   369,   370,   371,   214,
       0,     0,     0,     0,     0,     0,   215,   294,   -81,     0,
       0,   372,     0,     0,     0,   373,   218,   123,     0,     0,
     375,     0,   380,     0,     0,     0,   374,   345,   185,   346,
     347,   348,   349,   190,   191,   350,   351,   352,   353,     0,
       0,     0,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,     0,     0,     0,   367,     0,
       0,     0,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   368,   369,   370,
     371,   214,     0,     0,     0,     0,     0,     0,   215,     0,
       0,   294,     0,   372,     0,     0,     0,   373,   218,     0,
       0,     0,     0,     0,   429,     0,     0,     0,   374,   345,
     185,   346,   347,   348,   349,   190,   191,   350,   351,   352,
     353,     0,     0,     0,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,     0,     0,     0,
     367,     0,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   368,
     369,   370,   371,   214,     0,     0,     0,     0,     0,     0,
     215,   375,     0,     0,     0,   372,     0,     0,     0,   373,
     218,   624,     0,     0,     0,     0,   601,     0,     0,     0,
     374,   345,   185,   346,   347,   348,   349,   190,   191,   350,
     351,   352,   353,     0,     0,     0,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,     0,
       0,     0,   367,     0,     0,     0,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   368,   369,   370,   371,   214,     0,     0,     0,     0,
       0,     0,   215,     0,     0,   375,     0,   372,     0,     0,
       0,   373,   218,   430,     0,     0,     0,     0,     0,     0,
       0,     0,   374,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,     0,     0,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,     0,     0,     0,   268,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   269,   270,   271,   272,   273,     0,     0,
       0,     0,     0,     0,   375,     0,     0,     0,     0,   274,
       0,     0,   531,     0,   275,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,     0,     0,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,     0,     0,     0,   268,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   269,   270,   271,   272,   273,
       0,     0,     0,     0,     0,     0,   375,     0,     0,     0,
       0,   274,     0,     0,   631,     0,   492,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
       0,     0,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,     0,     0,     0,   268,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   269,   270,   271,
     272,   273,     0,     0,     0,     0,     0,     0,   375,     0,
       0,     0,     0,   274,   376,     0,     0,     0,   567
};

static const yytype_int16 yycheck[] =
{
       0,    49,    14,    24,     4,   230,     0,    16,     6,     4,
     215,    14,   215,   385,   171,   215,   431,   229,    10,   324,
     174,    13,     8,    20,     4,   230,     4,   230,    31,    32,
     230,    23,    24,    25,    83,    22,   118,    54,   120,    56,
      74,    75,    48,    92,     4,    48,   128,    47,   233,   151,
      53,     4,    80,    51,    64,    65,    66,    49,    50,    59,
      94,    31,    32,    89,    59,    38,    39,    40,    92,    97,
      80,    90,    82,    83,    84,    80,    86,   234,    48,    75,
      95,    88,   106,    53,    80,    95,   240,    94,    84,    90,
      95,    77,    43,    44,   100,    94,    82,    84,    95,   147,
      80,    80,    80,    80,    43,    44,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      80,   121,   297,    95,    80,   117,   118,    80,   120,   434,
      93,   104,   105,    96,    94,   237,   128,    80,   124,    95,
     126,    94,    74,    75,    95,    96,    97,    90,    99,    80,
      43,    44,    90,   156,    97,   147,    95,    95,    97,   151,
      99,   104,    94,    80,    95,    83,   538,   165,   171,    89,
      95,   169,   220,    93,    92,   161,    89,   163,    74,    75,
      93,    95,    89,   183,   196,   206,    93,   187,   183,   198,
      80,   189,   187,   196,   379,    89,    74,    75,    94,    93,
     375,   386,    95,   195,    97,    80,    99,   193,    89,   384,
      36,    37,    93,   205,   206,   207,   305,   306,   307,   308,
     309,   221,    80,    80,    80,    89,   221,    84,   220,    93,
     602,   234,   444,   390,    93,   650,    89,    96,    80,   396,
     397,   398,   399,    93,    93,   237,    96,    96,    80,    93,
      95,   408,    96,    74,    75,   440,    94,   339,     0,   484,
     107,   108,   109,   314,   315,   316,    74,    75,    74,    75,
      74,    75,    74,    75,   322,   487,    45,    46,   105,   484,
       4,   484,    62,    63,   484,    74,    75,    41,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   318,   319,    74,    75,    89,    74,    75,   310,   311,
     326,   327,   303,   304,   335,    42,   101,   103,    47,   102,
       6,    10,   104,   326,   327,   334,    89,   312,   313,    95,
     322,   323,    89,    95,    95,    95,    80,    95,    81,    95,
      95,    93,    95,   335,   569,    95,    95,   339,    80,    95,
      90,    90,   509,    94,    11,    81,    94,    94,    93,    89,
      94,    80,    93,    96,   569,    88,   569,    95,    89,   569,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,   431,    95,    89,    94,   390,   391,    95,
     382,   384,    93,   396,   397,   398,   399,    94,    96,    93,
     575,    94,    89,    88,   629,   408,    89,    81,    96,    88,
      91,    93,    96,    19,   414,   415,    96,    94,    96,    98,
     414,   415,   422,    98,   629,   582,   629,   422,    96,   629,
     422,   513,   105,    95,    89,   427,    80,    43,    44,   431,
      96,   433,    80,    91,    95,   437,    52,    96,    98,    96,
      96,   626,    81,    96,    96,    96,    96,    94,    64,    65,
      66,    67,    96,    73,    69,    96,   458,     5,   643,   644,
      76,    89,    96,    88,    80,    83,    82,    83,    84,    88,
      86,    88,    95,    40,    90,    89,    92,    83,    89,    95,
      89,    97,   299,    96,    96,   516,    96,   296,   104,    96,
     106,   107,   108,    96,   110,   111,   509,    96,   500,    96,
     298,   511,   512,   300,   317,   327,   511,   512,   510,    13,
     518,   513,   301,   425,   516,   523,   302,    55,   388,   406,
     578,   606,   524,   545,   578,   168,   540,   540,    -1,    -1,
     135,   539,   545,    -1,    -1,    -1,    -1,    -1,   546,    -1,
      -1,    -1,   550,    -1,   552,    -1,    -1,   557,    -1,   559,
      -1,    -1,   557,    -1,   559,    -1,    -1,   588,   589,    -1,
      -1,    -1,    -1,    -1,   560,    -1,    -1,    -1,    -1,   582,
      -1,    -1,    -1,    -1,    -1,    -1,   578,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   588,   589,    -1,    -1,
      -1,    -1,   650,    -1,    -1,    -1,    -1,   605,    -1,    -1,
      -1,   609,   610,   611,    -1,    -1,    -1,   638,   616,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   626,    -1,
     622,    -1,    -1,    -1,   634,   633,    -1,    -1,    -1,   634,
      -1,   639,   663,    -1,    -1,    -1,   638,    -1,    -1,    -1,
     643,   644,    -1,    -1,    -1,    -1,    -1,    -1,   650,    -1,
      -1,   659,    -1,    -1,   664,    -1,    -1,    -1,    -1,   664,
      -1,   663,    -1,    -1,    -1,    -1,   676,    -1,    -1,   679,
      -1,   676,     0,     1,   679,    -1,     4,    -1,     6,     7,
       8,     9,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    -1,    86,    -1,
      -1,    89,    90,    -1,    92,    -1,    -1,    95,    -1,    97,
      -1,    -1,    -1,    -1,    -1,   103,   104,    -1,   106,   107,
     108,     1,   110,   111,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    82,    83,    84,    85,    86,    -1,    -1,    89,
      90,    91,    92,    -1,    -1,    95,    -1,    97,    -1,    -1,
      -1,    -1,    -1,   103,   104,    -1,   106,   107,   108,     1,
     110,   111,     4,    -1,     6,     7,     8,     9,    -1,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,    -1,
      82,    83,    84,    -1,    86,    -1,    -1,    89,    90,    91,
      92,    -1,    -1,    95,    -1,    97,    -1,    -1,    -1,    -1,
      -1,   103,   104,    -1,   106,   107,   108,     1,   110,   111,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    -1,    86,    -1,    -1,    89,    90,    -1,    92,    -1,
      94,    95,    -1,    97,    -1,    -1,    -1,    -1,    -1,   103,
     104,    -1,   106,   107,   108,     1,   110,   111,     4,    -1,
       6,     7,     8,     9,    -1,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78,    79,    80,    -1,    82,    83,    84,    -1,
      86,    -1,    -1,    89,    90,    91,    92,    -1,    -1,    95,
      -1,    97,    -1,    -1,    -1,    -1,    -1,   103,   104,    -1,
     106,   107,   108,     1,   110,   111,     4,    -1,     6,     7,
       8,     9,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    -1,    86,    -1,
      -1,    89,    90,    91,    92,    -1,    -1,    95,    -1,    97,
      -1,    -1,    -1,    -1,    -1,   103,   104,    -1,   106,   107,
     108,     1,   110,   111,     4,    -1,     6,     7,     8,     9,
      -1,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    -1,    82,    83,    84,    -1,    86,    -1,    -1,    89,
      90,    91,    92,    -1,    -1,    95,    -1,    97,    -1,    -1,
      -1,    -1,    -1,   103,   104,    -1,   106,   107,   108,     1,
     110,   111,     4,    -1,     6,     7,     8,     9,    -1,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,    -1,
      82,    83,    84,    -1,    86,    -1,    -1,    89,    90,    91,
      92,    -1,    -1,    95,    -1,    97,    -1,    -1,    -1,    -1,
      -1,   103,   104,    -1,   106,   107,   108,     1,   110,   111,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    -1,    86,    -1,    -1,    89,    90,    91,    92,    -1,
      -1,    95,    -1,    97,    -1,    -1,    -1,    -1,    -1,   103,
     104,    -1,   106,   107,   108,     1,   110,   111,     4,    -1,
       6,     7,     8,     9,    -1,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      76,    77,    78,    79,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    89,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    20,    -1,    22,    23,    -1,    75,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    98,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    89,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    75,
      76,    -1,    -1,    -1,    80,    81,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    75,
      76,    -1,    -1,    -1,    80,    81,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      76,    -1,    -1,    -1,    80,    81,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    75,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    -1,    -1,    -1,    90,    -1,    92,    -1,    94,    95,
      19,    97,    -1,    22,    23,    -1,    -1,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    80,    -1,    82,    83,    84,    -1,    86,    -1,    -1,
      -1,    90,    -1,    92,    -1,    94,    95,    19,    97,    -1,
      22,    23,    -1,    -1,   103,   104,    -1,   106,   107,   108,
      -1,   110,   111,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    80,    -1,
      82,    83,    84,    -1,    86,    -1,    -1,    -1,    90,    -1,
      92,    -1,    94,    95,    19,    97,    -1,    22,    23,    -1,
      -1,   103,   104,    -1,   106,   107,   108,    -1,   110,   111,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    80,    81,    82,    83,    84,
      -1,    86,    -1,    -1,    -1,    90,    -1,    92,    -1,    -1,
      95,    -1,    97,    19,    -1,    -1,    22,    23,   103,   104,
      -1,   106,   107,   108,    30,   110,   111,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    75,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    35,
      86,    -1,    -1,    -1,    90,    -1,    92,    43,    44,    95,
      -1,    97,    -1,    -1,    -1,    -1,    52,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    -1,    64,    65,
      66,    67,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    -1,    -1,    -1,    90,    -1,    92,    -1,    -1,    95,
      -1,    97,    -1,    -1,    -1,    52,    -1,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    80,    -1,    82,    83,    84,    -1,    86,
      -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,    95,    -1,
      97,    -1,    -1,     4,    -1,    -1,    -1,   104,    -1,    -1,
      -1,   108,    -1,    -1,   111,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    35,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    88,    89,    -1,
      -1,    80,    -1,    -1,    -1,    84,    85,     4,    -1,    -1,
      88,    -1,    91,    -1,    -1,    -1,    95,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    88,    -1,    80,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    95,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      35,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    88,    -1,    -1,    -1,    80,    -1,    -1,    -1,    84,
      85,    98,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,
      95,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    35,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    88,    -1,    80,    -1,    -1,
      -1,    84,    85,    96,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    35,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    96,    -1,    85,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    35,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    96,    -1,    85,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    35,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    -1,    80,    94,    -1,    -1,    -1,    85
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     6,     7,     8,     9,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    43,    44,    52,    64,    65,    66,    67,    76,    77,
      78,    79,    80,    82,    83,    84,    86,    90,    92,    95,
      97,   103,   104,   106,   107,   108,   110,   111,   113,   114,
     115,   116,   117,   119,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   132,   133,   134,   135,   136,   137,   138,
     140,   141,   144,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     165,   167,   168,   169,   171,   172,   174,   182,   185,   188,
     189,   190,   192,   193,   194,   195,    89,    95,    95,   115,
      95,    90,   116,     4,    80,   143,    80,   143,    95,    23,
      35,    67,    80,    90,   144,   190,    94,    90,    90,   144,
     178,    64,    65,    66,    82,    83,    86,    95,   168,   169,
      80,    97,   186,   187,   186,    80,    95,    80,    80,    80,
      80,   142,   178,   142,   144,    80,    80,   139,    80,    80,
      80,    95,   163,   163,   183,    20,    95,    95,   184,    80,
     118,   118,    89,    94,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    35,
      64,    65,    66,    67,    68,    75,    80,    84,    85,    91,
      95,   114,   179,   180,   181,   163,    81,    90,   144,   146,
      75,    98,   144,   176,    95,   116,   105,   173,   163,   162,
     183,   162,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    35,    64,
      65,    66,    67,    68,    80,    85,   170,     0,   115,   143,
      89,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    88,   143,    48,   100,    41,    42,
     101,   102,   103,    36,    37,    38,    39,    40,   104,   105,
      45,    46,    92,   106,   107,   108,   109,    47,    62,    63,
      43,    44,    95,    97,    99,   164,    74,    75,   104,   191,
     144,   177,   177,     6,    20,    89,   177,    10,   130,    95,
     143,    89,   143,    89,   177,     4,     6,     7,     8,     9,
      12,    13,    14,    15,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    35,    64,    65,
      66,    67,    80,    84,    95,    88,    94,   191,    80,   120,
      91,    89,    93,   144,    88,    94,   176,    89,    93,    89,
      95,    75,   169,   198,   199,   200,    95,    95,    95,    95,
     197,   143,   143,   116,    89,    93,   197,   116,    95,   198,
     184,    80,    95,    81,    90,    90,   115,    80,   171,   172,
     174,   207,    94,    81,    91,    93,   175,    94,    96,    91,
      96,    95,    96,    97,    99,   164,   207,    93,   175,   198,
     176,   184,    89,   145,   146,   147,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,    30,   145,
     150,   147,   151,   152,   153,   154,   155,   156,   156,   157,
     157,   157,   157,   157,   158,   158,   159,   159,   160,   160,
     160,   161,   162,   162,    75,    81,   144,   146,   204,   205,
     206,   144,    85,   170,    64,    65,    66,    82,    83,    86,
      95,   166,   167,   169,   166,    22,    84,   201,    80,    95,
      93,    96,    96,    95,   186,   142,    89,    95,    11,   131,
     177,    89,    89,    96,    94,    81,    88,    93,   175,    90,
     144,    96,   145,   201,   175,   187,   198,   169,    94,    96,
      93,   198,   198,   198,   198,    94,   196,    89,    89,    80,
     196,   198,    96,    88,    81,    96,    91,   114,    91,   114,
     144,    96,   180,    91,   144,   204,   144,    85,   170,    75,
     144,    98,    96,   175,   144,    94,   207,    96,    93,    98,
     144,   105,    95,   198,   144,   115,   115,   177,    89,    89,
     142,    80,   116,    96,   116,   144,    96,    83,    92,    80,
      91,    91,    95,   202,    98,    96,   201,   116,   200,    96,
      96,    96,    96,   168,   116,   116,    96,   116,    81,    96,
      91,    91,    94,    96,    98,   207,    69,    73,   147,    75,
     206,    96,   198,    96,     5,    96,   142,   142,    89,    96,
      83,    88,   201,    88,    88,   116,   202,   116,   116,   116,
      95,   203,   116,    89,    96,   144,   116,   147,   207,    96,
     116,   115,    89,    89,    96,   142,   116,    83,    92,    96,
     145,   145,   204,   116,   142,   115,    96,    83,    96,    96,
     115,   115
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   112,   113,   114,   114,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   116,   116,   117,   117,
     117,   117,   118,   119,   120,   120,   120,   120,   120,   120,
     121,   121,   121,   121,   122,   123,   123,   124,   125,   126,
     127,   127,   128,   128,   128,   129,   130,   130,   131,   131,
     132,   132,   132,   132,   133,   133,   134,   135,   136,   136,
     136,   136,   137,   138,   139,   139,   140,   141,   141,   142,
     142,   143,   143,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   145,   145,
     146,   146,   146,   146,   146,   146,   147,   147,   148,   148,
     149,   149,   150,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   155,   155,   155,   156,   156,   156,   156,   156,
     156,   157,   157,   157,   158,   158,   158,   159,   159,   159,
     159,   160,   160,   161,   161,   161,   162,   162,   162,   162,
     162,   162,   162,   162,   163,   163,   163,   163,   163,   163,
     164,   164,   165,   165,   166,   166,   167,   167,   167,   167,
     167,   167,   167,   167,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   169,   169,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   171,   171,   172,
     172,   173,   174,   175,   175,   176,   176,   176,   176,   177,
     177,   178,   178,   178,   178,   179,   179,   180,   180,   180,
     180,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   182,   182,   182,   183,   184,   185,
     185,   186,   186,   187,   187,   187,   187,   187,   188,   188,
     189,   189,   189,   190,   191,   191,   192,   192,   192,   192,
     192,   192,   193,   193,   193,   194,   194,   195,   195,   196,
     196,   197,   197,   198,   198,   199,   199,   200,   200,   200,
     201,   201,   202,   202,   203,   203,   204,   204,   205,   205,
     205,   205,   206,   206,   206,   207,   207,   207,   207
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
       3,     1,     3,     1,     3,     3,     1,     1,     2,     2,
       2,     2,     2,     2,     1,     2,     4,     3,     3,     4,
       1,     1,     3,     3,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     6,     3,     3,     3,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     2,
       5,     0,     4,     0,     1,     1,     2,     3,     4,     1,
       3,     1,     2,     3,     4,     1,     3,     5,     3,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     0,     3,     3,
       3,     1,     3,     1,     4,     3,     6,     6,     1,     1,
       6,     6,     7,     1,     0,     3,     5,     5,     6,     6,
       6,     2,     6,     6,     6,     5,     5,     3,     3,     0,
       3,     0,     3,     0,     1,     1,     3,     1,     4,     2,
       1,     1,     0,     3,     0,     3,     0,     1,     1,     2,
       3,     4,     1,     1,     1,     1,     1,     1,     1
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
#line 137 "src/kinx.y" /* yacc.c:1646  */
    { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[0].obj), kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
#line 2367 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 142 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2373 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 165 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2379 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 166 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2385 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 170 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2391 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 171 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2397 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 175 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2403 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 176 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2409 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 177 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2415 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 178 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2421 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 182 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2427 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 186 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2433 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 190 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2439 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 191 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2445 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 192 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2451 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 193 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2457 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 194 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2463 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 195 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2469 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 206 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2475 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 210 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2481 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 211 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2487 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 215 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2493 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 219 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2499 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 223 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2505 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 227 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2511 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 228 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2517 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 233 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2528 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 240 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2539 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 247 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2550 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 256 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2556 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 260 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2562 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 261 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2568 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 265 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2574 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 266 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2580 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 270 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2586 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 271 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2592 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 272 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2598 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 273 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2604 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 277 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2610 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 278 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); }
#line 2616 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 282 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_COROUTINE, (yyvsp[-1].obj), NULL, NULL); }
#line 2622 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 286 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2628 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 290 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2634 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 291 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2640 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 292 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2646 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 293 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2652 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 297 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2658 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 301 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2664 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 305 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2670 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 306 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2676 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 310 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2682 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 314 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2688 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 315 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2694 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 319 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2700 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 324 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2706 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 325 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2712 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 330 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2718 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 331 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2724 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 332 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2730 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 333 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2736 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 334 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2742 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 335 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2748 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 336 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2754 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 337 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2760 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 338 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2766 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 339 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2772 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 340 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2778 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 341 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2784 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 342 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2790 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 343 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2796 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 352 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2802 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 353 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2808 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 354 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2814 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 355 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2820 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 356 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2826 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 357 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2832 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 362 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2838 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 372 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2844 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 377 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2850 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 382 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2856 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 387 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2862 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 392 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2868 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 397 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2874 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 402 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2880 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 403 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2886 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 408 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2892 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 409 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2898 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 410 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2904 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 411 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2910 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 412 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2916 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 417 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2922 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 418 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2928 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 423 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2934 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 424 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2940 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 429 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2946 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 430 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2952 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 431 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2958 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 436 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2964 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 441 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2970 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 442 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2976 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 448 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 2982 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 449 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 2988 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 450 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 2994 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 451 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 3000 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 452 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 3006 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 453 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 3012 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 458 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 3018 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 459 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3024 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 460 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3030 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 461 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3036 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 462 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3042 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 466 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3048 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 467 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3054 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 471 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 3060 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 472 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 3066 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 476 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3072 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 481 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3078 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 482 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3084 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 483 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3090 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 484 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3096 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 485 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3102 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3108 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3114 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 488 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3120 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 492 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3126 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 493 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3132 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 494 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3138 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3144 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3150 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3156 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3162 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3168 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 504 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3174 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 505 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3180 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 506 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3186 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 507 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3192 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3198 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3204 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 513 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3210 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3216 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 518 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3222 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 519 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3228 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3234 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 521 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3240 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 522 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3246 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 523 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3252 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 524 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3258 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 525 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3264 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 526 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3270 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 527 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3276 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 528 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3282 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 529 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3288 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 530 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3294 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 531 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3300 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 532 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3306 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 533 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3312 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 534 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3318 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 535 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3324 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 536 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3330 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 537 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3336 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3342 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 539 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3348 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 540 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3354 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 541 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3360 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 542 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3366 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 543 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3372 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 544 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("yield"); }
#line 3378 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3384 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 546 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3390 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 547 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3396 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 548 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3402 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 549 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3408 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 550 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3414 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 554 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3420 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 555 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3426 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 559 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3432 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 560 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3438 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 564 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3444 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 568 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3450 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 572 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3456 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 578 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3462 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 579 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3468 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 580 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3474 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 585 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3480 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 590 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3486 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 591 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3492 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 592 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3498 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 597 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3504 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 601 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3510 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 602 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3516 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 603 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3522 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 604 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3528 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 608 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3534 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3540 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 610 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3546 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 611 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3552 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 612 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3558 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 613 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3564 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 614 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3570 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 615 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3576 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 616 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3582 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 617 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3588 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 618 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3594 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 619 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3600 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 620 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3606 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 621 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3612 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 622 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3618 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 623 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3624 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 624 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3630 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 625 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3636 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 626 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3642 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 627 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3648 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 628 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3654 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 629 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3660 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 630 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3666 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 631 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3672 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 632 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3678 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3684 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 634 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3690 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 635 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3696 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 636 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3702 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 637 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3708 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 638 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3714 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 639 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3720 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 640 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3726 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3732 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 3738 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3744 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 3750 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 654 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 3756 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 658 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3762 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 659 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 3768 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 664 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3774 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 668 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 3780 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 669 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 3786 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3792 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 671 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 3798 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 672 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 3804 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 676 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3810 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 677 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3816 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 681 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3822 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 682 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3828 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 683 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3834 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 687 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 3840 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 691 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 3846 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 692 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3852 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 696 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3858 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 697 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3864 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 698 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3870 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 699 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 3876 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 700 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 3882 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 701 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 3888 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 705 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3894 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 706 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3900 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 707 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3906 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 711 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3912 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 712 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3918 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 716 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3924 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 717 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3930 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 721 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3936 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 723 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 3949 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 734 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3955 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 735 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3961 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 739 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3967 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 745 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3973 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 749 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3979 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 750 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 3985 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 751 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 3991 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 755 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 3997 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 756 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 4003 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 760 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 4009 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 761 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4015 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 765 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4021 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 766 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4027 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 770 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4033 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 776 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 4039 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 777 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 4045 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 778 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 4051 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 784 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 4057 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 788 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4063 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 789 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4069 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 790 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4075 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 791 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4081 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 4085 "kx.tab.c" /* yacc.c:1646  */
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
#line 794 "src/kinx.y" /* yacc.c:1906  */


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
