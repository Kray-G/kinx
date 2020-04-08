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
#define YYFINAL  277
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3611

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  97
/* YYNRULES -- Number of rules.  */
#define YYNRULES  353
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  706

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
       0,   138,   138,   142,   143,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   171,   172,   176,   177,
     178,   179,   183,   187,   191,   192,   193,   194,   195,   196,
     200,   201,   202,   203,   207,   211,   212,   216,   220,   224,
     228,   229,   233,   240,   247,   254,   256,   261,   262,   266,
     270,   271,   275,   276,   280,   281,   282,   283,   287,   288,
     292,   296,   300,   301,   302,   303,   307,   311,   315,   316,
     320,   324,   325,   329,   330,   334,   335,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   357,   358,   362,   363,   364,   365,   366,   367,
     371,   372,   376,   377,   381,   382,   386,   387,   391,   392,
     396,   397,   401,   402,   406,   407,   411,   412,   413,   417,
     418,   419,   420,   421,   422,   426,   427,   428,   432,   433,
     434,   438,   439,   440,   441,   445,   446,   450,   451,   452,
     456,   457,   458,   459,   460,   461,   462,   463,   467,   468,
     469,   470,   471,   472,   476,   477,   481,   482,   486,   487,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   524,   525,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   565,   566,   570,   571,   575,   579,   583,   584,
     588,   589,   590,   591,   595,   596,   600,   601,   602,   603,
     607,   608,   612,   613,   614,   615,   619,   620,   621,   622,
     623,   624,   625,   626,   627,   628,   629,   630,   631,   632,
     633,   634,   635,   636,   637,   638,   639,   640,   641,   642,
     643,   644,   645,   646,   647,   648,   649,   650,   651,   655,
     656,   657,   661,   665,   669,   670,   674,   675,   679,   680,
     681,   682,   683,   687,   688,   692,   693,   694,   698,   702,
     703,   707,   708,   709,   710,   711,   712,   716,   717,   718,
     722,   723,   727,   728,   732,   733,   745,   746,   750,   751,
     755,   756,   760,   761,   762,   766,   767,   771,   772,   776,
     777,   781,   782,   786,   787,   788,   789,   793,   794,   795,
     799,   800,   801,   802
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,    61,
      59,   123,   125,    45,    44,    58,    40,    41,    91,    93,
      46,    63,   124,    94,    38,    60,    62,    43,    42,    47,
      37,    33,    64
};
# endif

#define YYPACT_NINF -414

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-414)))

#define YYTABLE_NINF -288

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1687,   -41,    18,    46,  1687,    58,   -39,    26,    31,   108,
    2954,    29,   131,  3004,  3240,    54,    54,  -414,    57,    25,
     128,   157,   161,  3004,  3004,  2954,   171,   178,   185,   199,
      75,  3240,  3240,  -414,    85,    99,   197,    22,   216,   236,
     236,   134,   228,   201,   207,  -414,   210,   815,  3240,  2344,
    2101,    -8,     3,  3240,  3204,  -414,  3204,  3349,   324,   706,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,   323,  -414,  -414,
    -414,   243,  1784,  -414,  -414,    12,   292,   293,   237,   232,
     234,    43,    14,    44,    15,   122,   289,   224,  -414,    -4,
    -414,   230,  -414,   233,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,   238,  -414,  -414,  -414,  -414,  -414,  2954,  2954,   334,
    2194,   924,   330,   246,   323,   256,   323,   257,  2954,   252,
     253,   255,  -414,  2075,  3516,   238,  -414,   271,  1796,  1797,
     100,  -414,  -414,  -414,  -414,  -414,  -414,  2394,  -414,  -414,
     -45,  2444,   112,  -414,   117,   258,   -25,   259,   260,   261,
     262,   323,   265,   323,  1797,   -39,  -414,   118,   262,   -39,
     264,   -25,    -4,    -4,   216,   272,   267,   279,  -414,  -414,
     273,   276,  -414,  1687,    18,  -414,    46,  1033,    58,   -39,
    -414,  -414,    34,    35,   108,  2954,  3240,    54,    54,   274,
      57,    25,   128,   157,   161,  2494,  2571,  2648,   171,    75,
     -13,    70,    72,    22,  -414,    53,   275,   278,  -414,  -414,
    2725,  1142,   277,  -414,   281,    -4,   280,  1889,  3336,     1,
      53,  -414,  1797,   284,   -25,  -414,  -414,  2444,    -4,  -414,
     216,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,   290,
    -414,  3054,  3054,  3054,  3054,  3054,  3054,  3054,  3054,  3054,
    3054,  3054,  3054,  3054,  2804,  -414,  3204,  2954,  3204,  3204,
    3204,  3204,  3204,  3204,  3204,  3204,  3204,  3204,  3204,  3204,
    3204,  3204,  3204,  3204,  3204,  3204,  3204,  3204,  3204,  3204,
    -414,  -414,  2244,  2954,  3432,  -414,   114,   114,    19,    82,
    1797,   146,   147,   283,    59,   359,  3004,  2101,   365,   133,
     285,   370,  2954,   294,  -414,   295,  -414,   152,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,   288,  -414,   304,  3054,  -414,
     296,   300,   301,  -414,  -414,  3104,   299,  3419,  3054,    19,
     284,  -414,    54,  -414,   -25,   144,   302,   303,   305,  -414,
     -25,   -25,   -25,   -25,   306,   312,   313,  -414,  -414,   309,
     306,  -414,   -25,   310,  -414,   319,   328,   314,  1251,  1360,
    -414,  -414,  -414,  -414,  -414,  -414,  1687,   315,  -414,  2075,
     321,  2954,   235,  -414,   240,  2244,  -414,  2954,  3515,  -414,
    -414,  2854,   316,   317,   284,  -414,  -414,  -414,    41,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  2954,  -414,   292,   322,   293,   237,   232,   234,
      43,    14,    14,    44,    44,    44,    44,    44,    15,    15,
     122,   122,   289,   289,   289,   224,  -414,  -414,    53,  -414,
    1797,    41,   325,   326,  -414,  1877,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  2904,  -414,  -414,  -414,  -414,  -414,
    -414,   327,   332,   -25,  2954,  1687,  1687,  2954,    28,  2444,
     412,   143,   333,   284,  2954,  3004,   348,   -39,  -414,   154,
    -414,  -414,   -39,  2954,   335,    80,   354,   344,  1982,  1797,
    -414,  -414,  -414,   342,   343,  -414,   347,  -414,    19,   -39,
     -25,   366,   367,   368,   369,  3240,   -39,  -414,  -414,  -414,
     -39,   371,   -39,   385,   372,  -414,  -414,  1469,  -414,  1578,
     400,    74,  -414,  -414,  1797,   374,  1970,  -414,  -414,    53,
    1797,  -414,   402,   401,  1797,  2954,  -414,  -414,  2294,  -414,
     379,  3502,  -414,   -25,   380,  1797,   436,  -414,   164,   284,
    2954,  3004,  3004,   384,   166,   388,   387,  -414,  -414,  -414,
    1797,   390,  -414,   403,   397,  -414,  -414,    19,   399,   404,
     -39,   342,  -414,  -414,   -39,   -39,   -39,  -414,   398,  -414,
    -414,   -39,  -414,   405,   407,  -414,  -414,  2954,  -414,  -414,
    -414,  3154,  -414,  -414,    53,  -414,  -414,  -414,   408,   -39,
    1687,   406,   409,   170,   410,   413,   488,  1687,  3004,   -39,
    -414,    98,   414,  3054,  3054,  -414,  -414,  -414,  -414,  -414,
    2244,  -414,  -414,  -414,  -414,  1797,  -414,  -414,  -414,   -39,
    -414,  -414,  -414,   404,  1687,  3004,  1687,  -414,   416,  -414,
    -414,   415,  -414,  -414,  -414,   417,  -414,  -414,   420,  -414,
    1687,  -414,  -414,  1687,  -414,  -414
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    85,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   308,     0,     0,
       0,     0,     0,    83,    83,    73,     0,     0,     0,     0,
       0,     0,     0,   292,   182,   184,   185,     0,     0,     0,
       0,     0,   197,   181,   179,   198,   180,     0,     0,     0,
       0,     0,   236,     0,     0,   292,     0,     0,     0,     0,
       3,     5,     6,     7,    21,    23,     8,     9,    10,    11,
      12,    13,    14,    22,    15,    16,    17,    85,    18,    19,
      20,     0,    85,    87,   110,   113,   114,   116,   118,   120,
     122,   124,   126,   129,   135,   138,   141,   145,   147,   150,
     151,     0,   158,   183,   186,   187,   188,   189,    40,    41,
     303,   309,   112,   304,    42,    43,    25,     0,     0,     0,
       0,     0,    60,     0,    85,     0,    85,     0,     0,     0,
       0,     0,   197,     0,     0,   309,    51,     0,     0,   246,
       0,   182,   184,   185,   181,   179,   180,     0,   194,   183,
     298,     0,     0,   296,     0,     0,   328,     0,     0,     0,
     326,    85,    84,    85,    72,     0,    78,     0,   326,     0,
       0,   328,   156,   157,     0,     0,     0,     0,   291,    32,
       0,     0,    69,     0,   256,   257,   258,     0,   260,   261,
     262,   263,    85,    85,   266,   267,   268,   269,   270,   308,
     272,   274,   275,   276,   277,    83,    83,    73,   278,   273,
     182,   184,   185,   285,   286,     0,   197,   198,   288,    26,
       0,     0,   238,   250,     0,   154,     0,     0,     0,     0,
       0,   232,   240,   238,   328,   316,   234,     0,   153,   155,
       0,   152,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     219,   220,   221,   222,   224,   226,   225,   223,   218,   227,
     228,   229,   230,   231,   199,   196,   195,     1,     4,     0,
      80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     164,   165,   341,     0,     0,   159,   168,   168,     0,     0,
     244,     0,     0,     0,     0,   197,    83,     0,     0,     0,
       0,    62,     0,     0,    64,     0,    66,     0,   256,   258,
     259,   260,   261,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   274,   275,   276,   277,   279,   281,   280,   278,
     273,   282,   283,   284,   285,     0,   287,     0,     0,    50,
       0,    34,   238,   247,    70,     0,     0,     0,     0,     0,
     238,   294,     0,   295,   328,     0,   332,     0,   329,   330,
     328,   328,   328,   328,   324,     0,     0,   322,    77,     0,
     324,   323,   328,     0,   290,     0,     0,     0,     0,     0,
      44,   350,   351,   352,   353,   255,     0,     0,    27,   239,
       0,     0,   193,   104,   191,   341,   192,     0,     0,   105,
     241,   239,     0,     0,   238,   289,    71,    91,   103,   102,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
      89,    90,    75,    88,   115,     0,   117,   119,   121,   123,
     125,   127,   128,   131,   133,   134,   130,   132,   136,   137,
     140,   139,   142,   143,   144,   146,   148,   149,     0,   349,
     347,   348,     0,   342,   343,     0,   162,   161,   173,   175,
     176,   172,   170,   171,     0,   166,   169,   174,   167,   336,
     335,     0,     0,   328,     0,     0,     0,     0,   298,     0,
       0,     0,     0,   238,     0,    83,     0,     0,    59,     0,
      65,    67,     0,     0,     0,     0,   239,     0,     0,   248,
     193,   191,   300,   337,     0,   297,     0,   334,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,    76,    79,
       0,     0,     0,     0,     0,   293,    28,     0,    29,     0,
     253,   193,   251,   237,   254,     0,     0,   108,   107,     0,
     242,   233,     0,     0,    74,     0,   344,   163,     0,   160,
       0,     0,   310,   328,     0,   245,    45,    47,     0,   238,
       0,    83,    83,     0,     0,     0,     0,    63,    86,    49,
     253,     0,    35,     0,    37,    33,   249,     0,   299,     0,
       0,   337,   311,   331,     0,     0,     0,   327,   339,   320,
     321,     0,   312,     0,     0,    30,    31,     0,   109,   106,
     243,     0,   235,   111,     0,   345,   178,   177,     0,     0,
       0,     0,     0,     0,     0,     0,   233,     0,    83,     0,
      36,     0,     0,     0,     0,   305,   333,   317,   318,   319,
     341,   325,   306,    24,   190,   252,   315,   314,   346,     0,
     313,    46,    48,    58,     0,    83,     0,    55,     0,    61,
      38,     0,   338,   301,   302,     0,   307,    56,     0,    54,
       0,    39,   340,     0,    53,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -414,  -414,     6,     5,    -3,  -414,   458,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,   167,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,   -22,     7,     8,  -216,   -44,    10,  -414,  -414,   206,
     208,   219,   209,   218,   205,    16,   -89,    11,    13,   -46,
     211,   -29,    47,  -212,  -414,   196,     2,    -7,    79,  -295,
    -214,  -207,  -414,  -204,  -205,  -132,  -108,   513,  -414,   101,
    -414,  -414,   476,  -138,  -414,    -2,   142,  -414,  -414,     0,
     419,  -414,  -414,  -414,  -414,   125,   375,  -147,  -414,   -14,
    -355,   -84,  -414,  -413,  -414,   -50,  -217
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    58,   221,    60,    61,    62,   180,    63,   382,    64,
      65,    66,    67,    68,    69,    70,    71,   338,    72,   341,
     528,    73,    74,    75,    76,    77,    78,    79,   167,    80,
      81,   161,   125,    82,   463,   448,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   325,   100,   505,   101,   102,   103,   276,
     104,   105,   237,   106,   430,   233,   331,   162,   222,   223,
     224,   107,   174,   178,   108,   152,   153,   109,   110,   135,
     329,   112,   113,   114,   115,   556,   404,   397,   398,   399,
     511,   618,   671,   492,   493,   494,   425
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     111,   422,   163,   122,   111,   229,    59,   148,   423,   119,
     332,   424,   339,   440,   154,   127,   422,   439,   134,   390,
     347,   139,   575,   423,   413,   239,   424,   241,   442,   497,
     123,   139,   139,   164,   543,   123,   414,   -57,   123,   123,
     320,   321,   509,   175,   388,   320,   321,   111,   235,   116,
     389,   395,   121,   305,   306,   307,   132,   228,   232,   111,
      45,   296,  -173,  -173,   278,   447,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   172,   173,
     303,   304,  -282,   121,   279,   320,   321,   443,   234,   295,
     310,   311,   322,   149,   323,   225,   324,   435,   436,   437,
     238,   438,   445,   229,   510,   444,   157,   124,   312,   236,
     149,   149,   126,   297,   117,   124,   126,   388,   176,   308,
     309,   111,   313,   389,   136,   330,   330,   149,   330,  -264,
    -265,   343,   149,   345,   421,   150,   330,   435,   155,   437,
     518,   438,   118,   578,   133,  -175,  -175,  -176,  -176,  -178,
    -178,    50,   151,   156,   120,   387,   170,   519,    52,   232,
    -173,  -173,   407,   512,   612,  -283,   411,  -284,   405,   637,
     406,   171,   542,   613,  -175,  -175,   229,   537,   513,   498,
     499,   500,   690,   111,   163,   544,   122,   111,   420,   148,
     384,   691,   119,   621,   385,   132,   154,   501,   502,    45,
     127,   503,   391,   134,   128,   523,   392,   393,   408,   158,
     504,   392,   409,   139,   139,   164,   473,   474,   475,   476,
     477,   111,   137,   525,   182,   132,   278,   514,   228,    45,
     314,   315,   316,   601,   529,   396,   439,   392,   159,   583,
     514,   514,   160,   515,   516,   232,   514,   546,   514,   532,
     396,   608,   165,   551,   552,   553,   554,   695,   514,   166,
     514,   651,   662,   657,   514,   561,   168,   684,   482,   483,
     484,   586,  -176,  -176,   422,   149,  -172,  -172,   491,   439,
     169,   423,  -170,  -170,   424,  -171,  -171,   318,   319,   486,
     487,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   326,   327,   465,  -174,  -174,
    -178,  -178,   177,   396,   522,  -177,  -177,   179,   603,   471,
     472,   478,   479,   183,   277,   480,   481,   123,   506,   506,
     490,   495,   521,   280,   298,   301,   299,   317,   302,   300,
     333,   340,   342,   328,   139,   232,   344,   346,   156,   171,
     330,   176,   381,   415,   394,   400,   401,   402,   403,   385,
     412,   417,   640,   416,   418,   422,   594,   419,   -57,  -271,
     426,   429,   423,  -287,   524,   424,   431,   432,   441,   517,
     446,   526,   527,   533,   530,   531,   534,   599,   449,   535,
     559,   491,   513,   539,   652,   536,   540,   548,   449,   550,
     549,   555,   557,   558,   123,   507,   507,   562,   563,   598,
     564,   565,   571,   573,   582,   581,   604,   585,   111,   111,
     588,   600,   587,   602,   567,   569,   111,   678,   593,   606,
     422,   420,   611,   592,   570,   614,   615,   423,   617,   574,
     424,   650,   619,   490,   620,   576,   648,   693,   694,   580,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   624,   625,   626,   627,   633,   631,   634,
     584,   638,   641,   396,   547,   642,   646,   649,   658,   396,
     396,   396,   396,   656,   659,   637,   661,   660,   663,   294,
     -85,   396,   653,   664,   670,   673,   682,   -58,   181,   701,
     685,   520,   464,   605,   674,   679,   466,   470,   683,   468,
     686,   692,   591,   700,   702,   111,   111,   703,   467,   469,
     596,   597,   595,   508,   607,   330,   140,   232,   485,   609,
     572,   240,   330,   139,   545,   560,   623,   666,   645,     0,
       0,   610,     0,   410,   491,     0,   622,     0,   628,     0,
       0,     0,     0,   629,   380,     0,     0,   630,     0,   632,
       0,     0,     0,     0,     0,     0,     0,   111,     0,   111,
       0,     0,   278,     0,   278,     0,     0,   295,     0,   654,
     655,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   396,     0,     0,   643,   490,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   330,   139,
     139,     0,     0,     0,     0,     0,     0,   665,     0,     0,
       0,   667,   668,   669,     0,     0,   491,     0,   672,   396,
       0,     0,     0,     0,   149,     0,   688,     0,   676,     0,
       0,     0,     0,     0,     0,   675,   680,     0,     0,     0,
     111,   677,     0,     0,     0,   681,   689,   111,     0,     0,
       0,     0,   687,   698,     0,     0,   139,     0,     0,     0,
       0,     0,   396,   449,   449,     0,   696,     0,   490,     0,
       0,     0,     0,     0,   111,     0,   111,     0,     0,   697,
       0,   699,     0,   139,     0,     0,     0,     0,     0,     0,
     111,     0,     0,   111,     0,   704,    -2,     1,   705,     0,
       2,     0,     3,     4,     5,     0,     6,     0,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,    38,    39,    40,    41,    42,     0,    43,
      44,    45,     0,    46,     0,     0,   -81,    47,     0,    48,
       0,     0,    49,     0,    50,     0,     0,     0,     0,     0,
      51,    52,     0,    53,    54,    55,     1,    56,    57,   184,
     185,   186,   187,   188,     0,   189,   190,   191,   192,   193,
     194,   195,    11,    12,    13,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,    27,    28,
      29,   209,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     210,   211,   212,   213,   214,     0,     0,     0,     0,     0,
       0,   215,    38,    39,    40,    41,   216,     0,    43,    44,
     217,   218,    46,     0,     0,   -81,    47,   219,    48,     0,
       0,   220,     0,    50,     0,     0,     0,     0,     0,    51,
      52,     0,    53,    54,    55,     1,    56,    57,     2,     0,
       3,     4,     5,     0,     6,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,    38,    39,    40,    41,    42,     0,    43,    44,    45,
       0,    46,     0,     0,   -81,    47,   219,    48,     0,     0,
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
      46,     0,     0,   -81,    47,     0,    48,     0,  -259,    49,
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
       0,     0,   -81,    47,   428,    48,     0,     0,    49,     0,
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
       0,   -81,    47,   566,    48,     0,     0,    49,     0,    50,
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
     -81,    47,   568,    48,     0,     0,    49,     0,    50,     0,
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
      47,   635,    48,     0,     0,    49,     0,    50,     0,     0,
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
     636,    48,     0,     0,    49,     0,    50,     0,     0,     0,
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
      48,     0,     0,    49,     0,    50,     0,     0,   123,     0,
       0,    51,    52,     0,    53,    54,    55,     0,    56,    57,
     348,   185,   349,   350,   351,     0,   352,   190,   191,   353,
     354,   355,   356,     0,     0,     0,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,     0,
       0,     0,   370,     0,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
       0,   371,   372,   373,   374,   214,     0,     0,     0,     0,
       0,     0,   215,   294,     0,     0,     0,   375,     0,     0,
       0,   376,   218,     0,     0,     0,   378,     0,   383,     0,
       0,     0,   377,   348,   185,   349,   350,   351,     0,   352,
     190,   191,   353,   354,   355,   356,     0,     0,     0,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,     0,     0,     0,   370,     0,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   371,   372,   373,   374,   214,     0,
       0,     0,     0,     0,     0,   215,   378,     0,     0,     0,
     375,     0,     0,     0,   376,   218,   589,     0,     0,     0,
       0,   433,     0,     0,     0,   377,   348,   185,   349,   350,
     351,     0,   352,   190,   191,   353,   354,   355,   356,     0,
       0,     0,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,     0,     0,     0,   370,     0,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,   372,   373,
     374,   214,     0,     0,     0,     0,     0,     0,   215,   378,
       0,     0,     0,   375,     0,     0,     0,   376,   218,   639,
       0,     0,     0,     0,   616,     0,     0,     0,   377,   348,
     185,   349,   350,   351,     0,   352,   190,   191,   353,   354,
     355,   356,     0,     0,     0,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,     0,     0,
       0,   370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,     0,     0,    17,   129,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,     0,     0,
     371,   372,   373,   374,   214,    31,    32,     0,     0,     0,
       0,   215,     0,     0,    33,     0,   375,     0,     0,     0,
     376,   218,     0,     0,     0,     0,    34,    35,    36,   131,
       0,   377,     0,     0,     0,     0,     0,   230,    38,     0,
       0,     0,   132,     0,    43,    44,    45,     0,    46,     0,
       0,     0,   133,     0,    48,     0,     0,    49,     0,    50,
     231,     0,     0,     0,     0,    51,    52,     0,    53,    54,
      55,     0,    56,    57,    14,   334,     0,    17,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
       0,    38,     0,     0,     0,   335,     0,    43,    44,    45,
     130,    46,     0,     0,   336,   133,     0,    48,    31,    32,
      49,     0,   337,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
     488,    38,     0,     0,     0,   132,   489,    43,    44,    45,
     130,    46,     0,     0,     0,   227,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
     644,    38,     0,     0,     0,   132,   489,    43,    44,    45,
     130,    46,     0,     0,     0,   227,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
       0,    38,     0,     0,     0,   132,   226,    43,    44,    45,
     130,    46,     0,     0,     0,   227,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
       0,    38,     0,     0,     0,   132,   386,    43,    44,    45,
     130,    46,     0,     0,     0,   227,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
     230,    38,     0,     0,     0,   132,     0,    43,    44,    45,
     130,    46,     0,     0,     0,   133,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,   132,     0,    43,    44,    45,
       0,    46,     0,     0,     0,   138,     0,    48,     0,  -279,
      49,    14,    50,     0,    17,   129,     0,     0,    51,    52,
       0,    53,    54,    55,     0,    56,    57,   130,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,   131,
       0,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,   132,     0,    43,    44,    45,     0,    46,     0,
       0,     0,   138,     0,    48,     0,  -281,    49,    14,    50,
       0,    17,   129,     0,     0,    51,    52,     0,    53,    54,
      55,     0,    56,    57,   130,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,   131,     0,     0,     0,
       0,     0,     0,     0,     0,    38,     0,     0,     0,   132,
       0,    43,    44,    45,     0,    46,     0,     0,     0,   133,
       0,    48,     0,  -280,    49,    14,    50,     0,    17,   129,
       0,     0,    51,    52,     0,    53,    54,    55,     0,    56,
      57,   130,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,    36,   131,     0,     0,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,   132,   427,    43,    44,
      45,     0,    46,     0,     0,     0,   227,     0,    48,     0,
       0,    49,     0,    50,    14,     0,     0,    17,   129,    51,
      52,     0,    53,    54,    55,   462,    56,    57,     0,     0,
     130,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
       0,    38,     0,     0,     0,   132,     0,    43,    44,    45,
     130,    46,     0,     0,     0,   227,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
     579,    38,     0,     0,     0,   132,     0,    43,    44,    45,
     130,    46,     0,     0,     0,   133,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
       0,    38,     0,     0,     0,   132,   590,    43,    44,    45,
     130,    46,     0,     0,     0,   133,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
       0,    38,     0,     0,     0,   132,     0,    43,    44,    45,
     130,    46,     0,     0,     0,   133,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
       0,    38,     0,     0,     0,   132,     0,    43,    44,    45,
     130,    46,     0,     0,     0,   138,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
       0,    38,     0,     0,     0,   132,     0,    43,    44,    45,
     130,    46,     0,     0,     0,   227,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,    17,   129,     0,
       0,    38,     0,     0,     0,   132,     0,    43,    44,    45,
     130,    46,     0,     0,     0,   538,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
       0,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,    14,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,   132,     0,    43,    44,    45,
       0,    46,     0,     0,     0,    47,     0,    48,    31,    32,
      49,     0,    50,     0,     0,     0,     0,    33,    51,    52,
      14,    53,    54,    55,     0,    56,    57,     0,     0,    34,
      35,    36,   131,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,   132,     0,    43,    44,    45,
       0,    46,     0,    33,     0,   133,     0,    48,     0,     0,
      49,     0,    50,     0,     0,   141,   142,   143,   131,    52,
       0,    53,    54,    55,     0,    56,    57,    38,     0,     0,
       0,   132,     0,   144,   145,    45,     0,   146,     0,     0,
       0,   133,     0,     0,     0,     0,   147,     0,    50,     0,
       0,     0,     0,     0,     0,    52,     0,     0,     0,    55,
       0,     0,    57,   242,   243,   244,   245,   246,     0,   247,
     248,   249,   250,   251,   252,   253,   254,     0,     0,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,     0,     0,     0,   268,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   269,   270,   271,   272,   273,     0,
       0,     0,     0,     0,     0,   378,     0,     0,     0,     0,
     274,     0,     0,   434,     0,   275,   242,   243,   244,   245,
     246,     0,   247,   248,   249,   250,   251,   252,   253,   254,
       0,     0,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,     0,     0,     0,   268,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   269,   270,   271,
     272,   273,     0,     0,     0,     0,     0,     0,   378,     0,
       0,     0,     0,   274,     0,     0,   541,     0,   496,   242,
     243,   244,   245,   246,     0,   247,   248,   249,   250,   251,
     252,   253,   254,     0,     0,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,     0,     0,
       0,   268,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,     0,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,     0,
     269,   270,   271,   272,   273,     0,     0,     0,     0,     0,
       0,   378,     0,     0,     0,     0,   274,     0,     0,   647,
       0,   577,     0,     0,     0,   378,     0,     0,     0,     0,
       0,   379
};

static const yytype_int16 yycheck[] =
{
       0,   215,    24,     6,     4,    49,     0,    14,   215,     4,
     118,   215,   120,   230,    16,     8,   230,   229,    10,   151,
     128,    13,   435,   230,   171,    54,   230,    56,   233,   324,
       4,    23,    24,    25,   389,     4,   174,     9,     4,     4,
      44,    45,    23,    21,    89,    44,    45,    47,    51,    90,
      95,    76,    91,    39,    40,    41,    81,    49,    50,    59,
      85,    49,    75,    76,    59,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,    31,    32,
      37,    38,    95,    91,    77,    44,    45,   234,    96,    82,
      46,    47,    96,    14,    98,    48,   100,    96,    97,    98,
      53,   100,   240,   147,    85,   237,    81,    81,    93,   106,
      31,    32,    81,   101,    96,    81,    81,    89,    96,   105,
     106,   121,   107,    95,    95,   117,   118,    48,   120,    95,
      95,   124,    53,   126,    81,    81,   128,    96,    81,    98,
      81,   100,    96,   438,    91,    75,    76,    75,    76,    75,
      76,    98,    98,    96,    96,   147,    81,    98,   105,   151,
      75,    76,   165,    81,    84,    95,   169,    95,   161,    95,
     163,    96,   388,    93,    75,    76,   220,   382,    96,    65,
      66,    67,    84,   183,   206,   390,   189,   187,   183,   196,
      90,    93,   187,   548,    94,    81,   198,    83,    84,    85,
     193,    87,    90,   195,    96,   337,    94,    90,    90,    81,
      96,    94,    94,   205,   206,   207,   305,   306,   307,   308,
     309,   221,    91,    90,    90,    81,   221,    94,   220,    85,
     108,   109,   110,    90,   342,   156,   448,    94,    81,   444,
      94,    94,    81,    97,    97,   237,    94,   394,    94,    97,
     171,    97,    81,   400,   401,   402,   403,   670,    94,    81,
      94,    97,   617,    97,    94,   412,    81,    97,   314,   315,
     316,   488,    75,    76,   488,   196,    75,    76,   322,   491,
      81,   488,    75,    76,   488,    75,    76,    63,    64,   318,
     319,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,    75,    76,   297,    75,    76,
      75,    76,    96,   234,   336,    75,    76,    81,   523,   303,
     304,   310,   311,    95,     0,   312,   313,     4,   326,   327,
     322,   323,   334,    90,    42,   103,    43,    48,   104,   102,
       6,    11,    96,   105,   336,   337,    90,    90,    96,    96,
     342,    96,    81,    81,    96,    96,    96,    96,    96,    94,
      96,    82,   579,    96,    91,   579,   513,    91,     9,    95,
      95,    94,   579,    95,     9,   579,    95,    97,    94,    96,
      90,    96,    12,    95,    90,    90,    82,   519,   378,    89,
      81,   435,    96,   385,   599,    94,    97,    95,   388,    94,
      97,    95,    90,    90,     4,   326,   327,    97,    89,   517,
      82,    97,    97,    92,    97,    99,   524,    95,   418,   419,
      94,     9,    97,    90,   418,   419,   426,   644,    96,    81,
     644,   426,    97,   106,   426,    81,    92,   644,    96,   431,
     644,     5,    99,   435,    97,   437,   593,   663,   664,   441,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    97,    97,    97,    97,    82,    97,    97,
     462,    97,    70,   394,   395,    74,    97,    97,    90,   400,
     401,   402,   403,    99,    97,    95,    89,    84,    89,    89,
      90,   412,   600,    89,    96,    90,    90,     9,    40,    84,
      90,   334,   296,   525,    97,    97,   298,   302,    99,   300,
      97,    97,   504,    97,    97,   515,   516,    97,   299,   301,
     515,   516,   514,   327,   527,   517,    13,   519,   317,   532,
     429,    55,   524,   525,   392,   410,   550,   621,   588,    -1,
      -1,   533,    -1,   168,   588,    -1,   549,    -1,   555,    -1,
      -1,    -1,    -1,   556,   135,    -1,    -1,   560,    -1,   562,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   567,    -1,   569,
      -1,    -1,   567,    -1,   569,    -1,    -1,   570,    -1,   601,
     602,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   513,    -1,    -1,   585,   588,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   600,   601,
     602,    -1,    -1,    -1,    -1,    -1,    -1,   620,    -1,    -1,
      -1,   624,   625,   626,    -1,    -1,   670,    -1,   631,   550,
      -1,    -1,    -1,    -1,   555,    -1,   658,    -1,   641,    -1,
      -1,    -1,    -1,    -1,    -1,   637,   649,    -1,    -1,    -1,
     650,   641,    -1,    -1,    -1,   650,   659,   657,    -1,    -1,
      -1,    -1,   657,   685,    -1,    -1,   658,    -1,    -1,    -1,
      -1,    -1,   593,   663,   664,    -1,   679,    -1,   670,    -1,
      -1,    -1,    -1,    -1,   684,    -1,   686,    -1,    -1,   684,
      -1,   686,    -1,   685,    -1,    -1,    -1,    -1,    -1,    -1,
     700,    -1,    -1,   703,    -1,   700,     0,     1,   703,    -1,
       4,    -1,     6,     7,     8,    -1,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    78,    79,    80,    81,    -1,    83,
      84,    85,    -1,    87,    -1,    -1,    90,    91,    -1,    93,
      -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,
     104,   105,    -1,   107,   108,   109,     1,   111,   112,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    79,    80,    81,    -1,    83,    84,
      85,    86,    87,    -1,    -1,    90,    91,    92,    93,    -1,
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
      93,    -1,    -1,    96,    -1,    98,    -1,    -1,     4,    -1,
      -1,   104,   105,    -1,   107,   108,   109,    -1,   111,   112,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    36,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    89,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    86,    -1,    -1,    -1,    89,    -1,    92,    -1,
      -1,    -1,    96,     4,     5,     6,     7,     8,    -1,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    89,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    85,    86,    99,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    96,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    89,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    86,    99,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,    96,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      65,    66,    67,    68,    69,    44,    45,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    53,    -1,    81,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    96,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,
      -1,    -1,    91,    -1,    93,    -1,    -1,    96,    -1,    98,
      99,    -1,    -1,    -1,    -1,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,    20,    21,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      36,    87,    -1,    -1,    90,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      76,    77,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      76,    77,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      76,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      -1,    87,    -1,    -1,    -1,    91,    -1,    93,    -1,    95,
      96,    20,    98,    -1,    23,    24,    -1,    -1,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
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
      -1,    -1,    77,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    -1,    87,    -1,    -1,    -1,    91,    -1,    93,    -1,
      -1,    96,    -1,    98,    20,    -1,    -1,    23,    24,   104,
     105,    -1,   107,   108,   109,    31,   111,   112,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      76,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      -1,    87,    -1,    -1,    -1,    91,    -1,    93,    44,    45,
      96,    -1,    98,    -1,    -1,    -1,    -1,    53,   104,   105,
      20,   107,   108,   109,    -1,   111,   112,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      -1,    87,    -1,    53,    -1,    91,    -1,    93,    -1,    -1,
      96,    -1,    98,    -1,    -1,    65,    66,    67,    68,   105,
      -1,   107,   108,   109,    -1,   111,   112,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,
      -1,    91,    -1,    -1,    -1,    -1,    96,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,   109,
      -1,    -1,   112,     4,     5,     6,     7,     8,    -1,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    97,    -1,    86,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    97,    -1,    86,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    81,    -1,    -1,    97,
      -1,    86,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    95
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
     167,   169,   170,   171,   173,   174,   176,   184,   187,   190,
     191,   192,   194,   195,   196,   197,    90,    96,    96,   116,
      96,    91,   117,     4,    81,   145,    81,   145,    96,    24,
      36,    68,    81,    91,   146,   192,    95,    91,    91,   146,
     180,    65,    66,    67,    83,    84,    87,    96,   170,   171,
      81,    98,   188,   189,   188,    81,    96,    81,    81,    81,
      81,   144,   180,   144,   146,    81,    81,   141,    81,    81,
      81,    96,   165,   165,   185,    21,    96,    96,   186,    81,
     119,   119,    90,    95,     4,     5,     6,     7,     8,    10,
      11,    12,    13,    14,    15,    16,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    36,
      65,    66,    67,    68,    69,    76,    81,    85,    86,    92,
      96,   115,   181,   182,   183,   165,    82,    91,   146,   148,
      76,    99,   146,   178,    96,   117,   106,   175,   165,   164,
     185,   164,     4,     5,     6,     7,     8,    10,    11,    12,
      13,    14,    15,    16,    17,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    36,    65,
      66,    67,    68,    69,    81,    86,   172,     0,   116,   145,
      90,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    89,   145,    49,   101,    42,    43,
     102,   103,   104,    37,    38,    39,    40,    41,   105,   106,
      46,    47,    93,   107,   108,   109,   110,    48,    63,    64,
      44,    45,    96,    98,   100,   166,    75,    76,   105,   193,
     146,   179,   179,     6,    21,    81,    90,    98,   130,   179,
      11,   132,    96,   145,    90,   145,    90,   179,     4,     6,
       7,     8,    10,    13,    14,    15,    16,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      36,    65,    66,    67,    68,    81,    85,    96,    89,    95,
     193,    81,   121,    92,    90,    94,    82,   146,    89,    95,
     178,    90,    94,    90,    96,    76,   171,   200,   201,   202,
      96,    96,    96,    96,   199,   145,   145,   117,    90,    94,
     199,   117,    96,   200,   186,    81,    96,    82,    91,    91,
     116,    81,   173,   174,   176,   209,    95,    82,    92,    94,
     177,    95,    97,    92,    97,    96,    97,    98,   100,   166,
     209,    94,   177,   200,   178,   186,    90,   147,   148,   149,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,    31,   147,   152,   149,   153,   154,   155,   156,
     157,   158,   158,   159,   159,   159,   159,   159,   160,   160,
     161,   161,   162,   162,   162,   163,   164,   164,    76,    82,
     146,   148,   206,   207,   208,   146,    86,   172,    65,    66,
      67,    83,    84,    87,    96,   168,   169,   171,   168,    23,
      85,   203,    81,    96,    94,    97,    97,    96,    81,    98,
     130,   188,   144,   178,     9,    90,    96,    12,   133,   179,
      90,    90,    97,    95,    82,    89,    94,   177,    91,   146,
      97,    97,   147,   203,   177,   189,   200,   171,    95,    97,
      94,   200,   200,   200,   200,    95,   198,    90,    90,    81,
     198,   200,    97,    89,    82,    97,    92,   115,    92,   115,
     146,    97,   182,    92,   146,   206,   146,    86,   172,    76,
     146,    99,    97,   177,   146,    95,   209,    97,    94,    99,
      82,   146,   106,    96,   200,   146,   116,   116,   179,   178,
       9,    90,    90,   177,   179,   144,    81,   117,    97,   117,
     146,    97,    84,    93,    81,    92,    92,    96,   204,    99,
      97,   203,   117,   202,    97,    97,    97,    97,   170,   117,
     117,    97,   117,    82,    97,    92,    92,    95,    97,    99,
     209,    70,    74,   149,    76,   208,    97,    97,   200,    97,
       5,    97,   177,   179,   144,   144,    99,    97,    90,    97,
      84,    89,   203,    89,    89,   117,   204,   117,   117,   117,
      96,   205,   117,    90,    97,   146,   117,   149,   209,    97,
     117,   116,    90,    99,    97,    90,    97,   116,   144,   117,
      84,    93,    97,   147,   147,   206,   117,   116,   144,   116,
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
     164,   164,   164,   164,   164,   164,   164,   164,   165,   165,
     165,   165,   165,   165,   166,   166,   167,   167,   168,   168,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   171,   171,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   173,   173,   174,   174,   175,   176,   177,   177,
     178,   178,   178,   178,   179,   179,   180,   180,   180,   180,
     181,   181,   182,   182,   182,   182,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   184,
     184,   184,   185,   186,   187,   187,   188,   188,   189,   189,
     189,   189,   189,   190,   190,   191,   191,   191,   192,   193,
     193,   194,   194,   194,   194,   194,   194,   195,   195,   195,
     196,   196,   197,   197,   198,   198,   199,   199,   200,   200,
     201,   201,   202,   202,   202,   203,   203,   204,   204,   205,
     205,   206,   206,   207,   207,   207,   207,   208,   208,   208,
     209,   209,   209,   209
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
       1,     1,     2,     2,     2,     2,     2,     2,     1,     2,
       4,     3,     3,     4,     1,     1,     3,     3,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       6,     3,     3,     3,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     4,     2,     5,     0,     4,     0,     1,
       1,     2,     3,     4,     1,     3,     1,     2,     3,     4,
       1,     3,     5,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     2,     0,     3,     3,     3,     1,     3,     1,     4,
       3,     6,     6,     1,     1,     6,     6,     7,     1,     0,
       3,     5,     5,     6,     6,     6,     2,     6,     6,     6,
       5,     5,     3,     3,     0,     3,     0,     3,     0,     1,
       1,     3,     1,     4,     2,     1,     1,     0,     3,     0,
       3,     0,     1,     1,     2,     3,     4,     1,     1,     1,
       1,     1,     1,     1
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
#line 138 "src/kinx.y" /* yacc.c:1646  */
    { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[0].obj), kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
#line 2423 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 143 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2429 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 166 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2435 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 167 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2441 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 171 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2447 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 172 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2453 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 176 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2459 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 177 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2465 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 178 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2471 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 179 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2477 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 183 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2483 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 187 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2489 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 191 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2495 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 192 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2501 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 193 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2507 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 194 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2513 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 195 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2519 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 196 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2525 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 207 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2531 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 211 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2537 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 212 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2543 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 216 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2549 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 220 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2555 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 224 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2561 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 228 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2567 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 229 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2573 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 234 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2584 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 241 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2595 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 248 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2606 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 255 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 2612 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 257 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 2618 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 261 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 2624 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 262 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 2630 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 266 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2636 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 270 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2642 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 271 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2648 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 275 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2654 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 276 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2660 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 280 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2666 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 281 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2672 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 282 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2678 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 283 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2684 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 287 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2690 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 288 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); }
#line 2696 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 292 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_COROUTINE, (yyvsp[-1].obj), NULL, NULL); }
#line 2702 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 296 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2708 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 300 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2714 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 301 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2720 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 302 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2726 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 303 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2732 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 307 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2738 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 311 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2744 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 315 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2750 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 316 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2756 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 320 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2762 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 324 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2768 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 325 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2774 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 329 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2780 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 334 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2786 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 335 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2792 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 340 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2798 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 341 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2804 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 342 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2810 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 343 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2816 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 344 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2822 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 345 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2828 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 346 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2834 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 347 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2840 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 348 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2846 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 349 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2852 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 350 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2858 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 351 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2864 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 352 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2870 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 353 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2876 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 362 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2882 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 363 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2888 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 364 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2894 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 365 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2900 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 366 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2906 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 367 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2912 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 372 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2918 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 382 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2924 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 387 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2930 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 392 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2936 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 397 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2942 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 402 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2948 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 407 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2954 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 412 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2960 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 413 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2966 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 418 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2972 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 419 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2978 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 420 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2984 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 421 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2990 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 422 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2996 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 427 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3002 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 428 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3008 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 433 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3014 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 434 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3020 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 439 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3026 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 440 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3032 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 441 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3038 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 446 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3044 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 451 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3050 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 452 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3056 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 458 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 3062 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 459 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 3068 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 460 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 3074 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 461 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 3080 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 462 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 3086 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 463 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 3092 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 468 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 3098 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 469 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3104 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 470 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3110 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 471 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3116 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 472 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3122 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 476 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3128 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 477 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3134 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 481 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 3140 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 482 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 3146 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3152 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 491 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3158 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 492 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3164 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 493 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3170 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 494 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3176 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3182 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3188 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3194 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3200 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 499 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3206 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3212 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 504 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3218 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 505 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3224 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 506 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3230 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 507 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3236 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3242 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3248 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3254 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 515 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3260 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 516 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3266 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 517 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3272 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 518 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3278 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 519 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3284 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3290 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 524 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3296 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 525 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3302 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 529 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3308 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 530 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3314 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 531 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3320 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 532 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3326 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 533 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3332 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 534 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3338 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 535 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3344 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 536 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3350 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 537 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3356 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3362 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 539 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3368 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 540 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3374 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 541 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3380 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 542 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3386 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 543 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3392 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 544 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3398 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3404 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 546 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3410 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 547 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3416 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 548 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3422 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 549 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3428 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 550 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3434 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 551 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3440 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 552 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3446 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 553 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3452 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 554 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3458 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 555 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("yield"); }
#line 3464 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 556 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3470 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 557 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3476 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 558 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3482 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 559 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3488 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 560 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3494 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 561 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3500 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 565 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3506 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 566 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3512 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 570 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3518 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 571 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3524 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 575 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3530 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 579 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3536 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 583 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3542 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 589 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3548 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 590 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3554 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 591 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3560 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 596 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3566 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 601 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3572 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 602 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3578 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 603 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3584 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 608 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3590 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 612 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3596 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 613 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3602 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 614 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3608 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 615 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3614 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 619 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3620 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 620 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3626 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 621 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3632 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 622 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3638 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 623 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3644 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 624 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3650 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 625 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3656 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 626 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3662 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 627 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3668 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 628 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3674 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 629 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3680 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 630 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3686 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 631 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3692 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 632 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3698 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3704 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 634 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3710 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 635 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3716 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 636 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3722 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 637 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3728 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 638 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3734 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 639 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3740 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 640 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3746 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3752 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3758 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 643 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3764 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3770 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3776 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3782 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 647 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3788 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 648 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3794 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 649 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3800 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3806 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 651 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3812 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3818 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 3824 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3830 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 661 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 3836 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 665 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 3842 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 669 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3848 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 3854 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 675 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3860 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 679 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 3866 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 680 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 3872 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 681 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3878 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 682 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 3884 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 683 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 3890 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 687 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3896 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 688 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3902 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 692 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3908 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 693 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3914 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 694 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3920 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 698 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 3926 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 702 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 3932 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 703 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3938 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 707 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3944 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 708 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3950 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 709 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3956 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 710 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 3962 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 711 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 3968 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 712 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 3974 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 716 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3980 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 717 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3986 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 718 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3992 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 722 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3998 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 723 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4004 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 727 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4010 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 728 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4016 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 732 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4022 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 734 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 4035 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 745 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4041 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 746 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4047 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 750 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4053 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 756 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4059 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 760 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4065 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 761 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 4071 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 762 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 4077 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 766 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 4083 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 767 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 4089 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 771 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 4095 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 772 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4101 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 776 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4107 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 777 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4113 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 781 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4119 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 787 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 4125 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 788 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 4131 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 789 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 4137 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 795 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 4143 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 799 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4149 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 800 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4155 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 801 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4161 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 802 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4167 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 4171 "kx.tab.c" /* yacc.c:1646  */
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
#line 805 "src/kinx.y" /* yacc.c:1906  */


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
