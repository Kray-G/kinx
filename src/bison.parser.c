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
#define YYLAST   3932

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  99
/* YYNRULES -- Number of rules.  */
#define YYNRULES  380
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  741

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
       0,   140,   140,   144,   145,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   173,   174,   178,   179,
     180,   181,   185,   189,   193,   194,   195,   196,   197,   198,
     202,   203,   204,   205,   209,   213,   214,   218,   222,   226,
     230,   231,   235,   242,   249,   256,   258,   263,   264,   268,
     272,   273,   277,   278,   282,   283,   284,   285,   289,   290,
     294,   298,   302,   303,   304,   305,   309,   313,   317,   318,
     322,   326,   327,   331,   332,   336,   337,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   359,   360,   364,   365,   366,   367,   368,   369,
     373,   374,   378,   379,   383,   384,   388,   389,   393,   394,
     398,   399,   403,   404,   408,   409,   413,   414,   415,   419,
     420,   421,   422,   423,   424,   428,   429,   430,   434,   435,
     436,   440,   441,   442,   443,   447,   448,   452,   453,   454,
     458,   459,   463,   464,   468,   469,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   485,   486,   487,   488,   489,
     490,   491,   495,   496,   497,   498,   499,   500,   504,   505,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   530,   531,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   583,   584,   588,   589,   593,
     597,   601,   602,   606,   607,   608,   609,   613,   614,   618,
     619,   620,   621,   625,   626,   630,   631,   632,   633,   637,
     638,   639,   640,   641,   642,   643,   644,   645,   646,   647,
     648,   649,   650,   651,   652,   653,   654,   655,   656,   657,
     658,   659,   660,   661,   662,   663,   664,   665,   666,   667,
     668,   669,   670,   671,   672,   673,   674,   675,   676,   677,
     678,   679,   680,   681,   685,   686,   687,   691,   695,   699,
     700,   704,   705,   709,   710,   711,   712,   713,   717,   718,
     722,   723,   724,   728,   732,   733,   737,   738,   739,   740,
     741,   742,   746,   747,   748,   752,   753,   757,   758,   762,
     763,   767,   768,   780,   781,   785,   786,   790,   791,   795,
     796,   797,   801,   802,   806,   807,   811,   812,   816,   817,
     821,   822,   823,   824,   828,   829,   830,   834,   835,   836,
     837
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

#define YYPACT_NINF -457

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-457)))

#define YYTABLE_NINF -318

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1724,   -45,   -18,    28,  1724,    71,    -8,    23,    42,    77,
    3520,     8,   169,  3570,   231,   127,   127,  -457,   -41,  2261,
    2261,  2261,    94,  3570,  3570,  3520,    99,   185,   197,   201,
     -27,   231,   231,  -457,   215,   262,   288,     1,   190,   230,
     230,   229,   218,   290,   294,  -457,   296,   849,   231,  2910,
    2617,    41,   220,   231,  3770,  -457,  3770,  2368,   321,   740,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,   324,  -457,  -457,
    -457,   245,   464,  -457,  -457,    -6,   297,   298,   243,   244,
     276,   339,    47,   332,   -35,   192,   343,   319,  -457,  -457,
     310,  -457,    89,  -457,   312,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,   289,  -457,  -457,  -457,  -457,  -457,  3520,  3520,
     397,  2710,   961,   395,   313,   324,   329,   324,   333,  3520,
     318,   326,   330,  -457,  2154,  2254,   289,  -457,   347,  1833,
     141,    -9,  -457,  -457,  -457,  -457,  -457,  -457,  2960,  -457,
    -457,  3010,   -28,     6,  -457,    75,   334,    17,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,   335,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,   336,   337,   340,   341,   324,
     344,   324,   141,    -8,  -457,   126,   341,    -8,   346,    17,
      89,    89,   190,   350,   348,   357,  -457,  -457,   352,   358,
    -457,  1724,   -18,    28,  1070,    71,    -8,    11,    40,    77,
    3520,   231,   127,   127,   355,   -41,  2261,  2261,  2261,    94,
    3060,  3137,  3214,    99,   -27,    81,    84,    95,     1,   -16,
     356,   363,  -457,   231,  3291,  2760,   -42,   231,  3770,   373,
    1179,   365,  -457,   375,    89,   374,  1940,  1931,    86,   -16,
    -457,   141,   380,    17,  -457,  -457,  3010,    89,  -457,   190,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
     376,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
     386,  -457,  3620,  3620,  3620,  3620,  3620,  3620,  3620,  3620,
    3620,  3620,  3620,  3620,  3620,  3370,  -457,  3820,  3520,  3820,
    3820,  3820,  3820,  3820,  3820,  3820,  3820,  3820,  3820,  3820,
    3820,  3820,  3820,  3820,  3820,  3820,  3820,  3820,  3820,  3770,
    3770,   462,   462,  -457,  -457,  2810,  3520,  2475,  -457,     5,
      85,   141,   -17,   112,   382,   194,   471,  3570,  2617,   472,
     133,   388,   470,  3520,   396,  -457,   398,  -457,   149,   390,
     405,  3620,  -457,   393,   401,   402,  -457,  -457,  3670,   394,
    2038,   380,  3620,     5,  -457,   127,  -457,    17,    93,   403,
     400,   407,  -457,  -457,    17,    17,    17,    17,   404,   412,
     413,  -457,  -457,   411,   404,  -457,    17,   409,  -457,   415,
     425,   414,  1288,  1397,  -457,  -457,  -457,  -457,  -457,  -457,
    1724,   416,   417,  -457,  2154,   418,  3520,   320,  -457,   322,
    2810,  -457,  3520,  2582,  -457,  -457,  3420,   410,   433,   380,
    -457,  -457,  -457,  -457,   119,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  3520,  -457,
     297,   436,   298,   243,   244,   276,   339,    47,    47,   332,
     332,   332,   332,   332,   -35,   -35,   192,   192,   343,   343,
     343,   319,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    3470,  -457,  -457,  -457,  -457,   -16,  -457,   141,   119,   435,
     440,  -457,   566,  -457,  -457,  -457,  -457,   429,   443,    17,
    3520,  1724,  1724,  3520,  3010,   499,   154,   446,   380,  3520,
    3570,   459,    -8,  -457,   183,  -457,  -457,    -8,  3520,   444,
     157,   461,   452,  2047,   141,  -457,  -457,   449,  -457,   454,
    -457,   457,  -457,     5,    -8,    17,   465,   466,   468,   473,
     231,    -8,  -457,  -457,  -457,    -8,   474,    -8,   486,   475,
    -457,  -457,  1506,  -457,  1615,   300,   129,  -457,  -457,   141,
     476,  1824,  -457,  -457,   -16,   141,  -457,   504,   505,   141,
    3520,   481,  2145,  -457,  -457,  2860,  -457,  -457,    17,   483,
     141,   578,  -457,   212,   380,  3520,  3570,  3570,   485,   213,
     495,   489,  -457,  -457,  -457,   141,   492,  -457,   506,   500,
    -457,  -457,   502,     5,   507,    -8,   454,  -457,  -457,    -8,
      -8,    -8,  -457,   497,  -457,  -457,    -8,  -457,   508,   498,
    -457,  -457,  3520,  -457,  -457,  -457,  3720,  -457,  -457,  -457,
    -457,   -16,  -457,   503,    -8,  1724,   509,   510,   223,   511,
     514,   588,  1724,  3570,    -8,  -457,   172,  3620,   515,  3620,
    -457,  -457,  -457,  -457,  -457,  2810,  -457,  -457,  -457,  -457,
     141,  -457,  -457,  -457,    -8,  -457,  -457,  -457,   502,  1724,
    3570,  1724,  -457,   516,  -457,  -457,   519,  -457,  -457,  -457,
     532,  -457,  -457,   533,  -457,  1724,  -457,  -457,  1724,  -457,
    -457
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    85,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   333,     0,     0,
       0,     0,     0,    83,    83,    73,     0,     0,     0,     0,
       0,     0,     0,   317,   183,   185,   186,     0,     0,     0,
       0,     0,   198,   182,   180,   199,   181,     0,     0,     0,
       0,     0,   249,     0,     0,   317,     0,     0,     0,     0,
       3,     5,     6,     7,    21,    23,     8,     9,    10,    11,
      12,    13,    14,    22,    15,    16,    17,    85,    18,    19,
      20,     0,    85,    87,   110,   113,   114,   116,   118,   120,
     122,   124,   126,   129,   135,   138,   141,   145,   147,   150,
       0,   151,   165,   172,   184,   187,   188,   189,   190,    40,
      41,   328,   334,   112,   329,    42,    43,    25,     0,     0,
       0,     0,     0,    60,     0,    85,     0,    85,     0,     0,
       0,     0,     0,   198,     0,     0,   334,    51,     0,     0,
     259,     0,   183,   185,   186,   182,   180,   181,     0,   195,
     184,     0,   323,     0,   321,     0,     0,   355,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   287,   288,   289,   290,   292,
     294,   293,   291,   286,   302,   303,   304,   306,   295,   296,
     297,   298,   299,   345,   300,   301,   309,     0,   305,   307,
     308,   310,   311,   312,   346,     0,     0,     0,   353,    85,
      84,    85,    72,     0,    78,     0,   353,     0,     0,   355,
     170,   171,     0,     0,     0,     0,   316,    32,     0,     0,
      69,     0,   269,   271,     0,   273,   274,    85,    85,   279,
     280,   281,   282,   283,   333,   285,   287,   288,   289,   290,
      83,    83,    73,   291,   286,   183,   185,   186,   298,     0,
     198,   199,    26,   309,     0,     0,   249,   308,   310,   311,
       0,   251,   263,     0,   168,     0,     0,     0,     0,     0,
     245,   253,   251,   355,   341,   247,     0,   167,   169,     0,
     166,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   220,
     221,   222,   223,   225,   227,   226,   224,   219,   233,   234,
     235,   237,   228,   229,   230,   231,   232,   200,   197,   240,
       0,   236,   238,   239,   241,   242,   243,   196,     1,     4,
       0,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   154,   154,   178,   179,   368,     0,     0,   173,     0,
       0,   257,     0,     0,     0,     0,   198,    83,     0,     0,
       0,     0,    62,     0,     0,    64,     0,    66,     0,     0,
       0,     0,    50,     0,    34,   251,   260,    70,     0,     0,
       0,   251,     0,     0,   319,     0,   320,   355,     0,   359,
       0,   356,   357,   313,   355,   355,   355,   355,   351,     0,
       0,   349,    77,     0,   351,   350,   355,     0,   315,     0,
       0,     0,     0,     0,    44,   377,   378,   379,   380,   268,
       0,     0,   245,    27,   252,     0,     0,   194,   104,   192,
     368,   193,     0,     0,   105,   254,   252,     0,     0,   251,
     314,   244,    71,    91,   103,   102,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,    89,    90,    75,    88,
     115,     0,   117,   119,   121,   123,   125,   127,   128,   131,
     133,   134,   130,   132,   136,   137,   140,   139,   142,   143,
     144,   146,   148,   149,   159,   161,   162,   158,   156,   157,
       0,   152,   155,   160,   153,     0,   376,   374,   375,     0,
     369,   370,     0,   176,   175,   363,   362,     0,     0,   355,
       0,     0,     0,     0,     0,     0,     0,     0,   251,     0,
      83,     0,     0,    59,     0,    65,    67,     0,     0,     0,
       0,   252,     0,     0,   261,   194,   192,     0,   325,   364,
     322,     0,   361,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    68,    76,    79,     0,     0,     0,     0,     0,
     318,    28,     0,    29,     0,   266,   194,   264,   250,   267,
       0,     0,   108,   107,     0,   255,   246,     0,     0,    74,
       0,     0,     0,   371,   177,     0,   174,   335,   355,     0,
     258,    45,    47,     0,   251,     0,    83,    83,     0,     0,
       0,     0,    63,    86,    49,   266,     0,    35,     0,    37,
      33,   262,     0,     0,   324,     0,   364,   336,   358,     0,
       0,     0,   354,   366,   347,   348,     0,   337,     0,     0,
      30,    31,     0,   109,   106,   256,     0,   248,   111,   164,
     163,     0,   372,     0,     0,     0,     0,     0,     0,     0,
       0,   246,     0,    83,     0,    36,     0,     0,     0,     0,
     330,   360,   342,   343,   344,   368,   352,   331,    24,   191,
     265,   340,   339,   373,     0,   338,    46,    48,    58,     0,
      83,     0,    55,     0,    61,    38,     0,   327,   365,   326,
       0,   332,    56,     0,    54,     0,    39,   367,     0,    53,
      52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -457,  -457,     9,     4,    -3,  -457,   591,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,   238,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,   -22,     2,     7,  -234,   -43,  -204,  -457,  -457,   277,
     278,   275,   279,   274,   282,    43,   -36,    46,    38,   -52,
     260,  -457,  -457,   257,    39,   -31,    18,  -262,   -13,    20,
    -366,  -246,  -241,  -457,  -240,  -253,  -125,   -59,   628,  -457,
     182,   -40,  -457,   614,  -198,  -457,   -11,   224,  -457,  -457,
       0,   517,  -457,  -457,    21,  -457,  -457,   206,   438,  -182,
    -457,    66,  -411,     3,  -457,  -456,  -457,    35,  -268
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    58,   270,    60,    61,    62,   228,    63,   415,    64,
      65,    66,    67,    68,    69,    70,    71,   399,    72,   402,
     563,    73,    74,    75,    76,    77,    78,    79,   215,    80,
      81,   209,   126,    82,   499,   484,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   531,   100,   101,   102,   388,   103,   104,
     337,   105,   106,   286,   107,   465,   282,   392,   210,   271,
     272,   204,   108,   289,   226,   109,   153,   154,   110,   111,
     136,   390,   113,   114,   205,   115,   116,   591,   438,   430,
     431,   432,   547,   654,   706,   539,   540,   541,   459
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     112,   149,   211,   123,   112,   155,   278,   273,   120,    59,
     128,   475,   579,   456,   610,   124,   474,   135,   457,   458,
     140,   544,   223,   288,   448,   290,   421,   124,   545,   477,
     140,   140,   212,   456,   150,   152,   152,   447,   457,   458,
     156,   206,   207,   357,   124,   117,   124,   112,   284,   220,
     221,   150,   150,  -305,   218,   157,   277,   281,   373,   112,
     393,   422,   400,   339,   285,   455,   274,   423,   150,   219,
     408,   287,   374,   150,   150,   134,   150,   550,   118,   340,
     551,   417,    50,   122,   356,   418,   366,   367,   368,    52,
     546,   480,   125,   428,   273,   358,   424,   224,   133,   273,
     425,   478,    45,   137,   125,   278,  -277,   613,   483,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   127,   112,   127,   119,   391,   391,   404,   391,   406,
     383,   384,   122,   383,   384,  -278,   391,   283,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   369,   370,   501,   420,  -159,  -159,   281,  -161,
    -161,   479,   572,   383,   384,   426,   548,   121,   577,   425,
    -162,  -162,   656,   129,   133,   208,  -295,   429,    45,  -296,
     213,   549,   470,   471,   472,   385,   473,   386,   578,   387,
    -297,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,  -164,  -164,   550,   485,   133,   552,
     441,   439,    45,   440,   445,   470,   442,   472,   485,   473,
     443,   278,   474,   560,   672,   151,   618,   550,   149,   211,
     411,   112,   155,   123,   112,   454,   273,   288,   120,   429,
     128,   647,   698,   550,   636,   581,   567,   135,   425,   730,
     648,    14,   586,   587,   588,   589,   725,   140,   140,   212,
     138,   150,   152,   152,   596,   726,   214,   623,   206,   207,
     112,   277,   281,   558,   339,   396,   474,   550,   216,    45,
     643,   274,   217,   150,    33,   287,   225,   150,   150,   456,
    -159,  -159,   554,   281,   457,   458,   142,   143,   144,   132,
     375,   376,   377,   429,   124,   638,   550,   550,    38,   686,
     692,   227,   133,   231,   145,   146,    45,   550,   147,   230,
     719,   338,   134,   518,   519,   520,   285,   148,   124,    50,
     509,   510,   511,   512,   513,   341,    52,  -161,  -161,   359,
      55,   360,   538,    57,   564,   361,   675,   362,   522,   523,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,  -162,  -162,  -158,  -158,   629,   456,  -156,
    -156,  -157,  -157,   457,   458,   557,   364,   365,   371,   372,
     363,   687,   379,   380,   556,   381,   382,  -160,  -160,   355,
     -85,   378,   537,   542,   389,  -164,  -164,  -163,  -163,   150,
     150,   533,   533,   394,   140,   281,   401,   507,   508,   403,
     391,   516,   517,   713,   157,   152,   678,   514,   515,   405,
     532,   532,   219,   407,   273,   574,   224,   538,   414,   634,
     427,   449,   434,   435,   433,   456,   436,   437,   418,   451,
     457,   458,   446,   452,   450,   152,   683,   429,   582,   453,
    -284,   460,   112,   112,   429,   429,   429,   429,  -300,   464,
     112,   602,   604,   727,   454,   729,   429,   605,   124,  -317,
     466,   467,   712,   609,   476,   481,   482,   537,   553,   611,
     -57,   559,   562,   615,   561,   568,   565,   569,   566,   549,
     570,   575,   594,   485,   633,   485,   571,   584,   583,   590,
     639,   585,   592,   593,   598,   619,   597,   599,   635,   616,
     608,   600,  -313,   606,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   524,   525,   526,
     617,   620,   624,   273,   625,   627,   637,   622,   640,   628,
     641,   646,   649,   133,   650,   527,   528,    45,   652,   529,
     653,   112,   112,   355,   655,   631,   632,   630,   530,   642,
     391,   281,   659,   660,   644,   661,   391,   140,   668,   429,
     662,   666,   669,   673,   676,   645,   688,   663,   679,   677,
     684,   657,   538,   685,   691,   693,   694,   672,   664,   696,
     695,   697,   665,   705,   667,   709,   699,   -58,   708,   717,
     714,   720,   112,   736,   112,   429,   339,   356,   339,   718,
     150,   721,   728,   735,   689,   690,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   737,
     738,   229,   537,   555,   500,   503,   505,   502,   521,   534,
     504,   141,   391,   140,   140,   506,   607,   222,   429,   580,
     595,   658,   700,   413,   444,   411,   702,   703,   704,   701,
     682,     0,   538,   707,     0,   626,     0,     0,     0,     0,
       0,   723,     0,   711,     0,     0,     0,     0,     0,   710,
       0,   715,     0,     0,     0,   112,     0,     0,     0,   716,
       0,   724,   112,     0,     0,     0,   722,     0,   733,     0,
     140,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   731,   537,     0,     0,     0,     0,     0,     0,   112,
       0,   112,     0,   732,     0,   734,     0,   140,     0,     0,
       0,     0,     0,     0,     0,   112,     0,     0,   112,   739,
      -2,     1,   740,     0,     2,     0,     3,     4,     5,     0,
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
       1,    56,    57,   232,   159,   233,   234,   235,     0,   236,
     164,   165,   237,   238,   239,   240,    11,    12,    13,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,    27,    28,    29,   254,   184,   185,   186,   187,
       0,     0,     0,    31,    32,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   255,   256,   257,   258,   192,     0,
       0,     0,     0,     0,     0,   259,    38,    39,    40,    41,
     260,     0,    43,    44,   261,   195,    46,     0,     0,   -81,
      47,   262,   263,     0,     0,   264,     0,   265,     0,     0,
       0,     0,     0,    51,   266,   199,   267,   268,   269,   203,
      56,    57,     1,     0,     0,     2,     0,     3,     4,     5,
       0,     6,     0,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    42,     0,    43,    44,    45,     0,    46,     0,
       0,   -81,    47,   262,    48,     0,     0,    49,     0,    50,
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
     -81,    47,     0,    48,     0,  -272,    49,     0,    50,     0,
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
      47,   463,    48,     0,     0,    49,     0,    50,     0,     0,
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
     601,    48,     0,     0,    49,     0,    50,     0,     0,     0,
       0,     0,    51,    52,     0,    53,    54,    55,     1,    56,
      57,     2,     0,     3,     4,     5,     0,     6,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,     0,     0,   -81,    47,   603,
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
      44,    45,     0,    46,     0,     0,   -81,    47,   670,    48,
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
      45,     0,    46,     0,     0,   -81,    47,   671,    48,     0,
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
       0,    46,     0,     0,   -81,    47,     0,    48,     0,     0,
      49,     0,    50,     0,     0,     0,     0,     0,    51,    52,
       0,    53,    54,    55,     0,    56,    57,   158,   159,   160,
     161,   162,     0,   163,   164,   165,   166,   167,   168,   169,
       0,     0,     0,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,     0,     0,     0,   183,
     184,   185,   186,   187,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,   259,
       0,     0,     0,   411,   409,     0,     0,     0,   194,   195,
       0,     0,     0,   674,     0,   416,   196,     0,     0,   410,
       0,   197,     0,     0,     0,     0,     0,     0,   198,   199,
     200,   201,   202,   203,   158,   159,   160,   161,   162,     0,
     163,   164,   165,   166,   167,   168,   169,     0,     0,     0,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,     0,     0,     0,   183,   184,   185,   186,
     187,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   188,   189,   190,   191,   192,
       0,     0,     0,     0,     0,     0,   259,     0,     0,     0,
     411,   409,     0,     0,     0,   194,   195,     0,   469,     0,
       0,     0,   468,   196,     0,     0,   410,     0,   197,     0,
       0,     0,     0,     0,     0,   198,   199,   200,   201,   202,
     203,   158,   159,   160,   161,   162,     0,   163,   164,   165,
     166,   167,   168,   169,     0,     0,     0,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
       0,     0,     0,   183,   184,   185,   186,   187,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   189,   190,   191,   192,     0,     0,     0,
       0,     0,     0,   259,     0,     0,     0,   411,   409,     0,
       0,     0,   194,   195,     0,   576,     0,     0,     0,   651,
     196,     0,     0,   410,     0,   197,     0,     0,     0,     0,
       0,     0,   198,   199,   200,   201,   202,   203,   158,   159,
     160,   161,   162,     0,   163,   164,   165,   166,   167,   168,
     169,     0,     0,     0,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,     0,     0,     0,
     183,   184,   185,   186,   187,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   188,
     189,   190,   191,   192,     0,     0,     0,     0,     0,     0,
     259,     0,     0,     0,   411,   409,     0,     0,     0,   194,
     195,     0,   680,     0,     0,     0,     0,   196,     0,     0,
     410,     0,   197,     0,     0,     0,     0,     0,     0,   198,
     199,   200,   201,   202,   203,   158,   159,   160,   161,   162,
       0,   163,   164,   165,   166,   167,   168,   169,     0,     0,
       0,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,     0,     0,     0,   183,   184,   185,
     186,   187,     0,     0,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   188,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   193,   411,     0,     0,   194,   195,     0,   412,
       0,     0,     0,     0,   196,     0,     0,     0,     0,   197,
       0,     0,     0,     0,     0,     0,   198,   199,   200,   201,
     202,   203,   291,   292,   293,   294,   295,     0,   296,   297,
     298,   299,   300,   301,   302,   303,     0,     0,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,     0,     0,     0,   317,   318,   319,   320,   321,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   322,   323,   324,   325,   326,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   327,
       0,     0,     0,     0,   328,     0,     0,     0,     0,     0,
       0,   329,     0,     0,     0,     0,   330,     0,     0,     0,
       0,     0,     0,   331,   332,   333,   334,   335,   336,   291,
     292,   293,   294,   295,     0,   296,   297,   298,   299,   300,
     301,   302,   303,     0,     0,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,     0,     0,
       0,   317,   318,   319,   320,   321,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     322,   323,   324,   325,   326,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   327,     0,     0,     0,
       0,   543,     0,     0,     0,     0,     0,     0,   329,     0,
       0,     0,     0,   330,     0,     0,     0,     0,     0,     0,
     331,   332,   333,   334,   335,   336,   291,   292,   293,   294,
     295,     0,   296,   297,   298,   299,   300,   301,   302,   303,
       0,     0,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,     0,     0,     0,   317,   318,
     319,   320,   321,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,     0,     0,
      17,   130,     0,     0,     0,     0,     0,   322,   323,   324,
     325,   326,     0,   131,     0,     0,     0,     0,     0,     0,
       0,    31,    32,   327,     0,     0,     0,     0,   612,     0,
      33,     0,     0,     0,     0,   329,     0,     0,     0,     0,
     330,     0,    34,    35,    36,   132,     0,   331,   332,   333,
     334,   335,   336,   279,    38,     0,     0,     0,   133,     0,
      43,    44,    45,     0,    46,     0,     0,     0,   134,     0,
      48,     0,     0,    49,     0,    50,   280,     0,     0,     0,
       0,    51,    52,     0,    53,    54,    55,     0,    56,    57,
      14,   395,     0,    17,   130,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,     0,    38,     0,     0,
       0,   396,     0,    43,    44,    45,   131,    46,     0,     0,
     397,   134,     0,    48,    31,    32,    49,     0,   398,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,   279,    38,     0,     0,
       0,   133,     0,    43,    44,    45,   131,    46,     0,     0,
       0,   134,     0,    48,    31,    32,    49,     0,    50,   462,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,   535,    38,     0,     0,
       0,   133,   536,    43,    44,    45,   131,    46,     0,     0,
       0,   276,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,   681,    38,     0,     0,
       0,   133,   536,    43,    44,    45,   131,    46,     0,     0,
       0,   276,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,     0,    38,     0,     0,
       0,   133,   275,    43,    44,    45,   131,    46,     0,     0,
       0,   276,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,     0,    38,     0,     0,
       0,   133,   419,    43,    44,    45,   131,    46,     0,     0,
       0,   276,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,   279,    38,     0,     0,
       0,   133,     0,    43,    44,    45,   131,    46,     0,     0,
       0,   134,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,   133,     0,    43,    44,    45,     0,    46,     0,     0,
       0,   139,     0,    48,     0,  -292,    49,    14,    50,     0,
      17,   130,     0,     0,    51,    52,     0,    53,    54,    55,
       0,    56,    57,   131,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,   132,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,   133,     0,
      43,    44,    45,     0,    46,     0,     0,     0,   139,     0,
      48,     0,  -294,    49,    14,    50,     0,    17,   130,     0,
       0,    51,    52,     0,    53,    54,    55,     0,    56,    57,
     131,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,    36,   132,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,   133,     0,    43,    44,    45,
       0,    46,     0,     0,     0,   134,     0,    48,     0,  -293,
      49,    14,    50,     0,    17,   130,     0,     0,    51,    52,
       0,    53,    54,    55,     0,    56,    57,   131,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    36,   132,
       0,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,   133,   461,    43,    44,    45,     0,    46,     0,
       0,     0,   276,     0,    48,     0,     0,    49,     0,    50,
      14,     0,     0,    17,   130,    51,    52,     0,    53,    54,
      55,   498,    56,    57,     0,     0,   131,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,     0,    38,     0,     0,
       0,   133,     0,    43,    44,    45,   131,    46,     0,     0,
       0,   276,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,   614,    38,     0,     0,
       0,   133,     0,    43,    44,    45,   131,    46,     0,     0,
       0,   134,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,     0,    38,     0,     0,
       0,   133,   621,    43,    44,    45,   131,    46,     0,     0,
       0,   134,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,     0,    38,     0,     0,
       0,   133,     0,    43,    44,    45,   131,    46,     0,     0,
       0,   134,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,     0,    38,     0,     0,
       0,   133,     0,    43,    44,    45,   131,    46,     0,     0,
       0,   139,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,     0,    38,     0,     0,
       0,   133,     0,    43,    44,    45,   131,    46,     0,     0,
       0,   276,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,    17,   130,     0,     0,    38,     0,     0,
       0,   133,     0,    43,    44,    45,   131,    46,     0,     0,
       0,   573,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
      14,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,   133,     0,    43,    44,    45,     0,    46,     0,     0,
       0,    47,     0,    48,    31,    32,    49,     0,    50,     0,
       0,     0,     0,    33,    51,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,   142,   143,   144,   132,     0,
      14,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,   133,     0,   145,   146,    45,     0,   147,     0,     0,
       0,   134,     0,    48,    31,    32,   148,     0,    50,     0,
       0,     0,     0,    33,     0,    52,     0,    53,    54,    55,
       0,    56,    57,     0,     0,    34,    35,    36,   132,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,   133,     0,    43,    44,    45,     0,    46,     0,     0,
       0,   134,     0,    48,     0,     0,    49,     0,    50,     0,
       0,     0,     0,     0,     0,    52,     0,    53,    54,    55,
       0,    56,    57
};

static const yytype_int16 yycheck[] =
{
       0,    14,    24,     6,     4,    16,    49,    47,     4,     0,
       8,   279,   423,   259,   470,     4,   278,    10,   259,   259,
      13,   387,    21,    54,   222,    56,   151,     4,    23,   282,
      23,    24,    25,   279,    14,    15,    16,   219,   279,   279,
      81,    20,    21,    49,     4,    90,     4,    47,    51,    31,
      32,    31,    32,    95,    81,    96,    49,    50,    93,    59,
     119,    89,   121,    59,   106,    81,    48,    95,    48,    96,
     129,    53,   107,    53,    54,    91,    56,    94,    96,    77,
      97,    90,    98,    91,    82,    94,    39,    40,    41,   105,
      85,   289,    81,    76,   134,   101,    90,    96,    81,   139,
      94,   283,    85,    95,    81,   148,    95,   473,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,    81,   122,    81,    96,   118,   119,   125,   121,   127,
      44,    45,    91,    44,    45,    95,   129,    96,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   105,   106,   358,   148,    75,    76,   151,    75,
      76,   286,   415,    44,    45,    90,    81,    96,   421,    94,
      75,    76,   583,    96,    81,    81,    95,   157,    85,    95,
      81,    96,    96,    97,    98,    96,   100,    98,   422,   100,
      95,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    75,    76,    94,   411,    81,    97,
     213,   209,    85,   211,   217,    96,    90,    98,   422,   100,
      94,   264,   484,    90,    95,    98,   479,    94,   241,   251,
      89,   231,   243,   236,   234,   231,   276,   268,   234,   219,
     238,    84,   653,    94,    90,   427,    97,   240,    94,   705,
      93,    20,   434,   435,   436,   437,    84,   250,   251,   252,
      91,   241,   242,   243,   446,    93,    81,   535,   247,   248,
     270,   264,   265,   398,   270,    81,   538,    94,    81,    85,
      97,   263,    81,   263,    53,   267,    96,   267,   268,   535,
      75,    76,    98,   286,   535,   535,    65,    66,    67,    68,
     108,   109,   110,   283,     4,   558,    94,    94,    77,    97,
      97,    81,    81,    95,    83,    84,    85,    94,    87,    90,
      97,     0,    91,   375,   376,   377,   106,    96,     4,    98,
     366,   367,   368,   369,   370,    90,   105,    75,    76,    42,
     109,    43,   385,   112,   403,   102,   614,   103,   379,   380,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    75,    76,    75,    76,   549,   614,    75,
      76,    75,    76,   614,   614,   397,    37,    38,    46,    47,
     104,   634,    63,    64,   395,    75,    76,    75,    76,    89,
      90,    48,   385,   386,   105,    75,    76,    75,    76,   379,
     380,   381,   382,     6,   397,   398,    11,   364,   365,    96,
     403,   373,   374,   681,    96,   395,   620,   371,   372,    90,
     381,   382,    96,    90,   464,   418,    96,   470,    81,   554,
      96,    81,    96,    96,    99,   681,    96,    96,    94,    82,
     681,   681,    96,    91,    96,   425,   628,   427,   428,    91,
      95,    95,   452,   453,   434,   435,   436,   437,    95,    94,
     460,   452,   453,   697,   460,   699,   446,   460,     4,    96,
      95,    97,   676,   466,    94,    99,    90,   470,    96,   472,
       9,     9,    12,   476,    96,    95,    90,    82,    90,    96,
      89,    97,    81,   697,   553,   699,    94,    97,    95,    95,
     559,    94,    90,    90,    89,   498,    97,    82,     9,    99,
      92,    97,    95,    97,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    65,    66,    67,
      97,    95,    97,   573,    94,   106,    90,   530,   560,    96,
      81,    97,    81,    81,    92,    83,    84,    85,    99,    87,
      96,   551,   552,    89,    97,   551,   552,   550,    96,   562,
     553,   554,    97,    97,   567,    97,   559,   560,    82,   549,
      97,    97,    97,    97,    70,   568,   635,   590,    97,    74,
      97,   584,   625,     5,    99,    90,    97,    95,   591,    89,
      84,    89,   595,    96,   597,    97,    89,     9,    90,    90,
      97,    90,   602,    84,   604,   585,   602,   605,   604,    99,
     590,    97,    97,    97,   636,   637,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    97,
      97,    40,   625,   395,   357,   360,   362,   359,   378,   382,
     361,    13,   635,   636,   637,   363,   464,    33,   628,   425,
     444,   585,   655,   136,   216,    89,   659,   660,   661,   656,
     625,    -1,   705,   666,    -1,    99,    -1,    -1,    -1,    -1,
      -1,   693,    -1,   676,    -1,    -1,    -1,    -1,    -1,   672,
      -1,   684,    -1,    -1,    -1,   685,    -1,    -1,    -1,   685,
      -1,   694,   692,    -1,    -1,    -1,   692,    -1,   720,    -1,
     693,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   714,   705,    -1,    -1,    -1,    -1,    -1,    -1,   719,
      -1,   721,    -1,   719,    -1,   721,    -1,   720,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   735,    -1,    -1,   738,   735,
       0,     1,   738,    -1,     4,    -1,     6,     7,     8,    -1,
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
       1,   111,   112,     4,     5,     6,     7,     8,    -1,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,
      81,    -1,    83,    84,    85,    86,    87,    -1,    -1,    90,
      91,    92,    93,    -1,    -1,    96,    -1,    98,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,   107,   108,   109,   110,
     111,   112,     1,    -1,    -1,     4,    -1,     6,     7,     8,
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
      90,    91,    -1,    93,    -1,    95,    96,    -1,    98,    -1,
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
      -1,    87,    -1,    -1,    90,    91,    -1,    93,    -1,    -1,
      96,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,     4,     5,     6,
       7,     8,    -1,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    89,    81,    -1,    -1,    -1,    85,    86,
      -1,    -1,    -1,    99,    -1,    92,    93,    -1,    -1,    96,
      -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,
     107,   108,   109,   110,     4,     5,     6,     7,     8,    -1,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      89,    81,    -1,    -1,    -1,    85,    86,    -1,    97,    -1,
      -1,    -1,    92,    93,    -1,    -1,    96,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,   105,   106,   107,   108,   109,
     110,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    89,    81,    -1,
      -1,    -1,    85,    86,    -1,    97,    -1,    -1,    -1,    92,
      93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,
      -1,    -1,   105,   106,   107,   108,   109,   110,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    89,    81,    -1,    -1,    -1,    85,
      86,    -1,    97,    -1,    -1,    -1,    -1,    93,    -1,    -1,
      96,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,   107,   108,   109,   110,     4,     5,     6,     7,     8,
      -1,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    89,    -1,    -1,    85,    86,    -1,    95,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,    -1,   105,   106,   107,   108,
     109,   110,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,
     105,   106,   107,   108,   109,   110,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    81,    -1,    -1,    -1,    -1,    86,    -1,
      53,    -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      98,    -1,    65,    66,    67,    68,    -1,   105,   106,   107,
     108,   109,   110,    76,    77,    -1,    -1,    -1,    81,    -1,
      83,    84,    85,    -1,    87,    -1,    -1,    -1,    91,    -1,
      93,    -1,    -1,    96,    -1,    98,    99,    -1,    -1,    -1,
      -1,   104,   105,    -1,   107,   108,   109,    -1,   111,   112,
      20,    21,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      90,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
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
      96,    20,    98,    -1,    23,    24,    -1,    -1,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    -1,    87,    -1,
      -1,    -1,    91,    -1,    93,    -1,    -1,    96,    -1,    98,
      20,    -1,    -1,    23,    24,   104,   105,    -1,   107,   108,
     109,    31,   111,   112,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    76,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,   104,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,
      -1,    91,    -1,    93,    44,    45,    96,    -1,    98,    -1,
      -1,    -1,    -1,    53,    -1,   105,    -1,   107,   108,   109,
      -1,   111,   112,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,
      -1,    91,    -1,    93,    -1,    -1,    96,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,   105,    -1,   107,   108,   109,
      -1,   111,   112
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
      30,    31,    32,    36,    37,    38,    39,    40,    65,    66,
      67,    68,    69,    81,    85,    86,    93,    98,   105,   106,
     107,   108,   109,   110,   184,   197,   197,   197,    81,   144,
     181,   144,   146,    81,    81,   141,    81,    81,    81,    96,
     169,   169,   186,    21,    96,    96,   187,    81,   119,   119,
      90,    95,     4,     6,     7,     8,    10,    13,    14,    15,
      16,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    36,    65,    66,    67,    68,    76,
      81,    85,    92,    93,    96,    98,   105,   107,   108,   109,
     115,   182,   183,   184,   169,    82,    91,   146,   148,    76,
      99,   146,   179,    96,   117,   106,   176,   169,   168,   186,
     168,     4,     5,     6,     7,     8,    10,    11,    12,    13,
      14,    15,    16,    17,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    36,    37,    38,
      39,    40,    65,    66,    67,    68,    69,    81,    86,    93,
      98,   105,   106,   107,   108,   109,   110,   173,     0,   116,
     145,    90,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    89,   145,    49,   101,    42,
      43,   102,   103,   104,    37,    38,    39,    40,    41,   105,
     106,    46,    47,    93,   107,   108,   109,   110,    48,    63,
      64,    75,    76,    44,    45,    96,    98,   100,   170,   105,
     194,   146,   180,   180,     6,    21,    81,    90,    98,   130,
     180,    11,   132,    96,   145,    90,   145,    90,   180,    81,
      96,    89,    95,   194,    81,   121,    92,    90,    94,    82,
     146,   179,    89,    95,    90,    94,    90,    96,    76,   172,
     202,   203,   204,    99,    96,    96,    96,    96,   201,   145,
     145,   117,    90,    94,   201,   117,    96,   202,   187,    81,
      96,    82,    91,    91,   116,    81,   174,   175,   177,   211,
      95,    82,    99,    92,    94,   178,    95,    97,    92,    97,
      96,    97,    98,   100,   170,   211,    94,   178,   202,   179,
     187,    99,    90,   147,   148,   149,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,    31,   147,
     152,   149,   153,   154,   155,   156,   157,   158,   158,   159,
     159,   159,   159,   159,   160,   160,   161,   161,   162,   162,
     162,   163,   168,   168,    65,    66,    67,    83,    84,    87,
      96,   166,   167,   172,   166,    76,    82,   146,   148,   208,
     209,   210,   146,    86,   173,    23,    85,   205,    81,    96,
      94,    97,    97,    96,    98,   130,   189,   144,   179,     9,
      90,    96,    12,   133,   180,    90,    90,    97,    95,    82,
      89,    94,   178,    91,   146,    97,    97,   178,   147,   205,
     190,   202,   172,    95,    97,    94,   202,   202,   202,   202,
      95,   200,    90,    90,    81,   200,   202,    97,    89,    82,
      97,    92,   115,    92,   115,   146,    97,   183,    92,   146,
     208,   146,    86,   173,    76,   146,    99,    97,   178,   146,
      95,    82,   146,   211,    97,    94,    99,   106,    96,   202,
     146,   116,   116,   180,   179,     9,    90,    90,   178,   180,
     144,    81,   117,    97,   117,   146,    97,    84,    93,    81,
      92,    92,    99,    96,   206,    97,   205,   117,   204,    97,
      97,    97,    97,   171,   117,   117,    97,   117,    82,    97,
      92,    92,    95,    97,    99,   211,    70,    74,   149,    97,
      97,    76,   210,   202,    97,     5,    97,   178,   180,   144,
     144,    99,    97,    90,    97,    84,    89,    89,   205,    89,
     117,   206,   117,   117,   117,    96,   207,   117,    90,    97,
     146,   117,   149,   211,    97,   117,   116,    90,    99,    97,
      90,    97,   116,   144,   117,    84,    93,   147,    97,   147,
     208,   117,   116,   144,   116,    97,    84,    97,    97,   116,
     116
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
     173,   173,   173,   173,   173,   174,   174,   175,   175,   176,
     177,   178,   178,   179,   179,   179,   179,   180,   180,   181,
     181,   181,   181,   182,   182,   183,   183,   183,   183,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   185,   185,   185,   186,   187,   188,
     188,   189,   189,   190,   190,   190,   190,   190,   191,   191,
     192,   192,   192,   193,   194,   194,   195,   195,   195,   195,
     195,   195,   196,   196,   196,   197,   197,   198,   198,   199,
     199,   200,   200,   201,   201,   202,   202,   203,   203,   204,
     204,   204,   205,   205,   206,   206,   207,   207,   208,   208,
     209,   209,   209,   209,   210,   210,   210,   211,   211,   211,
     211
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
       1,     1,     1,     1,     2,     2,     4,     2,     5,     0,
       4,     0,     1,     1,     2,     3,     4,     1,     3,     1,
       2,     3,     4,     1,     3,     5,     3,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     3,     2,     0,     3,     3,
       3,     1,     3,     1,     4,     3,     6,     6,     1,     1,
       6,     6,     7,     1,     0,     3,     5,     5,     6,     6,
       6,     2,     6,     6,     6,     1,     1,     5,     5,     3,
       3,     0,     3,     0,     3,     0,     1,     1,     3,     1,
       4,     2,     1,     1,     0,     3,     0,     3,     0,     1,
       1,     2,     3,     4,     1,     1,     1,     1,     1,     1,
       1
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
#line 140 "src/kinx.y" /* yacc.c:1646  */
    { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[0].obj), kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
#line 2509 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 145 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2515 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 168 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2521 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 169 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2527 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 173 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2533 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 174 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2539 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 178 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2545 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 179 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2551 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 180 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2557 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 181 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2563 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 185 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2569 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 189 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2575 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 193 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2581 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 194 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2587 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 195 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2593 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 196 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2599 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 197 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2605 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 198 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2611 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 209 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2617 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 213 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2623 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 214 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2629 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 218 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2635 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 222 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2641 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 226 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2647 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 230 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2653 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 231 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2659 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 236 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2670 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 243 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2681 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 250 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2692 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 257 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 2698 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 259 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_forin_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 2704 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 263 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 2710 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 264 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 2716 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 268 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2722 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 272 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2728 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 273 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2734 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 277 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2740 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 278 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2746 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 282 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2752 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 283 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2758 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 284 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2764 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 285 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2770 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 289 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2776 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 290 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SYSRET_NV, NULL, NULL, NULL); }
#line 2782 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 294 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_COROUTINE, (yyvsp[-1].obj), NULL, NULL); }
#line 2788 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 298 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2794 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 302 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2800 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 303 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2806 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 304 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2812 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 305 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2818 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 309 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2824 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 313 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2830 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 317 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2836 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 318 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2842 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 322 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2848 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 326 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2854 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 327 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2860 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 331 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2866 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 336 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2872 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 337 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2878 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 342 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2884 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 343 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2890 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 344 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2896 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 345 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2902 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 346 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2908 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 347 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2914 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 348 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2920 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 349 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2926 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 350 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2932 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 351 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2938 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 352 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2944 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 353 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2950 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 354 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2956 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 355 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2962 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 364 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2968 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 365 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2974 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 366 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2980 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 367 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2986 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 368 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2992 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 369 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2998 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 374 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3004 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 384 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3010 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 389 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3016 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 394 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3022 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 399 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3028 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 404 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3034 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 409 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3040 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 414 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3046 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 415 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3052 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 420 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3058 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 421 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3064 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 422 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3070 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 423 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3076 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 424 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3082 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 429 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3088 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 430 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3094 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 435 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3100 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 436 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3106 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 441 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3112 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 442 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3118 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 443 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3124 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 448 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3130 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 453 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3136 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 454 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3142 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 463 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 0); }
#line 3148 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 464 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_range_object((yyvsp[-2].obj), (yyvsp[0].obj), 1); }
#line 3154 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 468 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3160 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 473 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3166 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 474 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3172 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 475 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3178 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 476 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3184 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 477 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3190 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 478 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3196 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 479 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3202 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 480 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3208 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 481 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3214 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 3220 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 3226 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 488 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 3232 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 489 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 3238 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 490 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 3244 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 491 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 3250 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 3256 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3262 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3268 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 499 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3274 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 500 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3280 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 504 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3286 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 505 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3292 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3298 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 510 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3304 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 511 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3310 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 512 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3316 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 513 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3322 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3328 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 515 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3334 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3340 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 521 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3346 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 522 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3352 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 523 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3358 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 524 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3364 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 525 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3370 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 526 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3376 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 530 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3382 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 531 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3388 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 535 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3394 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 536 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3400 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 537 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3406 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3412 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 539 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3418 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 540 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3424 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 541 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3430 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 542 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3436 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 543 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3442 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 544 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3448 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3454 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 546 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3460 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 547 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3466 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 548 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3472 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 549 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3478 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 550 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3484 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 551 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3490 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 552 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3496 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 553 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3502 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 554 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3508 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 555 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3514 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 556 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3520 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 557 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3526 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 558 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3532 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 559 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3538 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 560 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3544 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 561 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("yield"); }
#line 3550 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 562 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3556 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 563 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3562 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 564 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3568 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 565 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3574 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 566 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3580 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 567 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3586 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 568 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("=="); }
#line 3592 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 569 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("!="); }
#line 3598 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 570 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<="); }
#line 3604 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 571 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("<"); }
#line 3610 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 572 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">="); }
#line 3616 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 573 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object(">"); }
#line 3622 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 574 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("+"); }
#line 3628 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 575 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("-"); }
#line 3634 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 576 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("*"); }
#line 3640 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 577 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("/"); }
#line 3646 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 578 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("%"); }
#line 3652 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 579 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("[]"); }
#line 3658 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 583 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3664 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 584 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3670 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 588 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3676 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 589 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3682 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 593 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3688 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 597 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3694 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 601 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3700 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 607 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3706 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 608 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3712 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3718 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 614 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3724 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 619 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3730 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 620 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3736 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 621 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3742 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 626 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3748 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 630 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3754 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 631 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3760 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 632 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3766 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3772 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 637 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3778 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 638 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3784 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 639 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3790 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 640 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3796 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3802 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3808 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 643 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3814 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3820 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3826 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3832 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 647 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3838 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 648 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3844 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 649 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3850 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3856 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 651 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3862 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 652 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3868 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 653 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3874 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 654 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3880 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3886 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3892 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3898 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 658 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3904 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 659 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3910 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 660 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3916 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 661 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3922 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 662 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3928 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 663 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3934 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 664 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3940 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 665 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3946 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 666 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3952 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 667 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3958 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 668 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3964 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 669 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3970 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "=="; }
#line 3976 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 671 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "!="; }
#line 3982 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 672 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<="; }
#line 3988 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 673 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<"; }
#line 3994 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 674 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">="; }
#line 4000 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 675 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">"; }
#line 4006 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 676 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "+"; }
#line 4012 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 677 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "-"; }
#line 4018 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 678 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "*"; }
#line 4024 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 679 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "/"; }
#line 4030 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 680 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "%"; }
#line 4036 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 681 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "[]"; }
#line 4042 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 685 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4048 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 686 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 4054 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 687 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4060 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 691 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 4066 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 695 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 4072 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 699 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4078 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 700 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 4084 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 705 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4090 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 709 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 4096 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 710 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 4102 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 711 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 4108 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 712 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 4114 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 713 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 4120 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 717 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4126 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 718 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4132 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 722 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4138 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 723 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4144 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 724 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4150 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 728 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 4156 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 732 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 4162 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 733 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4168 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 737 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4174 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 738 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4180 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 739 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4186 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 740 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 4192 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 741 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 4198 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 742 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 4204 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 746 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4210 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 747 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4216 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 748 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4222 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 757 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4228 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 758 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4234 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 762 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4240 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 763 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4246 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 767 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4252 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 769 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 4265 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 780 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4271 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 781 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4277 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 785 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4283 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 791 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4289 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 795 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4295 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 796 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 4301 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 797 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 4307 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 801 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 4313 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 802 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 4319 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 806 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 4325 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 807 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4331 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 811 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4337 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 812 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4343 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 816 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4349 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 822 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 4355 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 823 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 4361 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 824 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 4367 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 830 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 4373 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 834 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4379 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 835 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4385 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 836 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4391 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 837 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4397 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 4401 "kx.tab.c" /* yacc.c:1646  */
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
