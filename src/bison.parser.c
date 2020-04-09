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
#define YYLAST   3934

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  99
/* YYNRULES -- Number of rules.  */
#define YYNRULES  382
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  743

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
     575,   576,   577,   578,   579,   580,   584,   585,   589,   590,
     594,   598,   602,   603,   607,   608,   609,   610,   614,   615,
     619,   620,   621,   622,   626,   627,   631,   632,   633,   634,
     638,   639,   640,   641,   642,   643,   644,   645,   646,   647,
     648,   649,   650,   651,   652,   653,   654,   655,   656,   657,
     658,   659,   660,   661,   662,   663,   664,   665,   666,   667,
     668,   669,   670,   671,   672,   673,   674,   675,   676,   677,
     678,   679,   680,   681,   682,   683,   687,   688,   689,   693,
     697,   701,   702,   706,   707,   711,   712,   713,   714,   715,
     719,   720,   724,   725,   726,   730,   734,   735,   739,   740,
     741,   742,   743,   744,   748,   749,   750,   754,   755,   759,
     760,   764,   765,   769,   770,   782,   783,   787,   788,   792,
     793,   797,   798,   799,   803,   804,   808,   809,   813,   814,
     818,   819,   823,   824,   825,   826,   830,   831,   832,   836,
     837,   838,   839
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

#define YYPACT_NINF -459

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-459)))

#define YYTABLE_NINF -320

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1726,   -18,   -29,    96,  1726,   103,    47,    23,    49,   122,
    3522,   -12,    89,  3572,   258,   -23,   -23,  -459,   -11,  2263,
    2263,  2263,   113,  3572,  3572,  3522,   157,   169,   180,   185,
      -4,   258,   258,  -459,   132,   170,   179,     1,   174,   193,
     193,   207,     3,   210,   216,  -459,   243,   851,   258,  2912,
    2619,   -31,   195,   258,  3772,  -459,  3772,  2370,   303,   742,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,   306,  -459,  -459,
    -459,   226,   330,  -459,  -459,    -8,   280,   288,   231,   235,
     236,   283,    41,   281,    28,   117,   307,    32,  -459,  -459,
     254,  -459,    87,  -459,   261,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,   257,  -459,  -459,  -459,  -459,  -459,  3522,  3522,
     360,  2712,   963,   357,   276,   306,   285,   306,   286,  3522,
     282,   297,   301,  -459,  2156,  2363,   257,  -459,   290,  1835,
    2470,   116,  -459,  -459,  -459,  -459,  -459,  -459,  2962,  -459,
    -459,  3012,    95,   119,  -459,   126,   302,   112,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,   300,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,   304,   309,   313,   314,
     306,   317,   306,  2470,    47,  -459,   127,   314,    47,   318,
     112,    87,    87,   174,   332,   320,   336,  -459,  -459,   331,
     333,  -459,  1726,   -29,    96,  1072,   103,    47,    38,    42,
     122,  3522,   258,   -23,   -23,   326,   -11,  2263,  2263,  2263,
     113,  3062,  3139,  3216,   157,    -4,   -26,    25,    81,     1,
     -27,   335,   337,  -459,   258,  3293,  2762,    55,   258,  3772,
     329,  1181,   339,  -459,   340,    87,   334,  1942,  2042,    43,
     -27,  -459,  2470,   343,   112,  -459,  -459,  3012,    87,  -459,
     174,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,   342,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,   344,  -459,  3622,  3622,  3622,  3622,  3622,  3622,
    3622,  3622,  3622,  3622,  3622,  3622,  3622,  3372,  -459,  3822,
    3522,  3822,  3822,  3822,  3822,  3822,  3822,  3822,  3822,  3822,
    3822,  3822,  3822,  3822,  3822,  3822,  3822,  3822,  3822,  3822,
    3822,  3772,  3772,   407,   407,  -459,  -459,  2812,  3522,  2477,
    -459,    17,    53,  2470,   150,   171,   346,     5,   429,  3572,
    2619,   430,   129,   347,   432,  3522,   358,  -459,   362,  -459,
     182,   365,   371,  3622,  -459,   368,   376,   373,  -459,  -459,
    3672,   379,  2149,   343,  3622,    17,  -459,   -23,  -459,   112,
      67,   382,   381,   386,  -459,  -459,   112,   112,   112,   112,
     387,   393,   394,  -459,  -459,   405,   387,  -459,   112,   390,
    -459,   400,   411,   398,  1290,  1399,  -459,  -459,  -459,  -459,
    -459,  -459,  1726,   401,   402,  -459,  2156,   408,  3522,   271,
    -459,   275,  2812,  -459,  3522,  2584,  -459,  -459,  3422,   403,
     404,   343,  -459,  -459,  -459,  -459,   100,  -459,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    3522,  -459,   280,   409,   288,   231,   235,   236,   283,    41,
      41,   281,   281,   281,   281,   281,    28,    28,   117,   117,
     307,   307,   307,    32,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,  -459,  3472,  -459,  -459,  -459,  -459,   -27,  -459,  2470,
     100,   412,   414,  -459,   568,  -459,  -459,  -459,  -459,   399,
     410,   112,  3522,  1726,  1726,  3522,  3012,   501,   134,   421,
     343,  3522,  3572,   431,    47,  -459,   186,  -459,  -459,    47,
    3522,   416,    58,   433,   423,  2049,  2470,  -459,  -459,   417,
    -459,   422,  -459,   424,  -459,    17,    47,   112,   425,   426,
     427,   428,   258,    47,  -459,  -459,  -459,    47,   434,    47,
     438,   435,  -459,  -459,  1508,  -459,  1617,  1828,    84,  -459,
    -459,  2470,   436,  1937,  -459,  -459,   -27,  2470,  -459,   456,
     454,  2470,  3522,   437,  2256,  -459,  -459,  2862,  -459,  -459,
     112,   439,  2470,   524,  -459,   199,   343,  3522,  3572,  3572,
     442,   205,   440,   441,  -459,  -459,  -459,  2470,   447,  -459,
     453,   455,  -459,  -459,   457,    17,   458,    47,   422,  -459,
    -459,    47,    47,    47,  -459,   449,  -459,  -459,    47,  -459,
     459,   446,  -459,  -459,  3522,  -459,  -459,  -459,  3722,  -459,
    -459,  -459,  -459,   -27,  -459,   451,    47,  1726,   460,   452,
     215,   462,   463,   546,  1726,  3572,    47,  -459,    98,  3622,
     467,  3622,  -459,  -459,  -459,  -459,  -459,  2812,  -459,  -459,
    -459,  -459,  2470,  -459,  -459,  -459,    47,  -459,  -459,  -459,
     457,  1726,  3572,  1726,  -459,   468,  -459,  -459,   472,  -459,
    -459,  -459,   470,  -459,  -459,   473,  -459,  1726,  -459,  -459,
    1726,  -459,  -459
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    85,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   335,     0,     0,
       0,     0,     0,    83,    83,    73,     0,     0,     0,     0,
       0,     0,     0,   319,   183,   185,   186,     0,     0,     0,
       0,     0,   198,   182,   180,   199,   181,     0,     0,     0,
       0,     0,   250,     0,     0,   319,     0,     0,     0,     0,
       3,     5,     6,     7,    21,    23,     8,     9,    10,    11,
      12,    13,    14,    22,    15,    16,    17,    85,    18,    19,
      20,     0,    85,    87,   110,   113,   114,   116,   118,   120,
     122,   124,   126,   129,   135,   138,   141,   145,   147,   150,
       0,   151,   165,   172,   184,   187,   188,   189,   190,    40,
      41,   330,   336,   112,   331,    42,    43,    25,     0,     0,
       0,     0,     0,    60,     0,    85,     0,    85,     0,     0,
       0,     0,     0,   198,     0,     0,   336,    51,     0,     0,
     260,     0,   183,   185,   186,   182,   180,   181,     0,   195,
     184,     0,   325,     0,   323,     0,     0,   357,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   288,   289,   290,   291,   293,
     295,   294,   292,   287,   303,   304,   305,   307,   309,   296,
     297,   298,   299,   300,   347,   301,   302,   311,     0,   306,
     308,   310,   312,   313,   314,   348,     0,     0,     0,   355,
      85,    84,    85,    72,     0,    78,     0,   355,     0,     0,
     357,   170,   171,     0,     0,     0,     0,   318,    32,     0,
       0,    69,     0,   270,   272,     0,   274,   275,    85,    85,
     280,   281,   282,   283,   284,   335,   286,   288,   289,   290,
     291,    83,    83,    73,   292,   287,   183,   185,   186,   299,
       0,   198,   199,    26,   311,     0,     0,   250,   310,   312,
     313,     0,   252,   264,     0,   168,     0,     0,     0,     0,
       0,   246,   254,   252,   357,   343,   248,     0,   167,   169,
       0,   166,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     220,   221,   222,   223,   225,   227,   226,   224,   219,   233,
     234,   235,   237,   239,   228,   229,   230,   231,   232,   200,
     197,   241,     0,   236,   238,   240,   242,   243,   244,   196,
       1,     4,     0,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   154,   154,   178,   179,   370,     0,     0,
     173,     0,     0,   258,     0,     0,     0,     0,   198,    83,
       0,     0,     0,     0,    62,     0,     0,    64,     0,    66,
       0,     0,     0,     0,    50,     0,    34,   252,   261,    70,
       0,     0,     0,   252,     0,     0,   321,     0,   322,   357,
       0,   361,     0,   358,   359,   315,   357,   357,   357,   357,
     353,     0,     0,   351,    77,     0,   353,   352,   357,     0,
     317,     0,     0,     0,     0,     0,    44,   379,   380,   381,
     382,   269,     0,     0,   246,    27,   253,     0,     0,   194,
     104,   192,   370,   193,     0,     0,   105,   255,   253,     0,
       0,   252,   316,   245,    71,    91,   103,   102,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,    89,    90,
      75,    88,   115,     0,   117,   119,   121,   123,   125,   127,
     128,   131,   133,   134,   130,   132,   136,   137,   140,   139,
     142,   143,   144,   146,   148,   149,   159,   161,   162,   158,
     156,   157,     0,   152,   155,   160,   153,     0,   378,   376,
     377,     0,   371,   372,     0,   176,   175,   365,   364,     0,
       0,   357,     0,     0,     0,     0,     0,     0,     0,     0,
     252,     0,    83,     0,     0,    59,     0,    65,    67,     0,
       0,     0,     0,   253,     0,     0,   262,   194,   192,     0,
     327,   366,   324,     0,   363,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    68,    76,    79,     0,     0,     0,
       0,     0,   320,    28,     0,    29,     0,   267,   194,   265,
     251,   268,     0,     0,   108,   107,     0,   256,   247,     0,
       0,    74,     0,     0,     0,   373,   177,     0,   174,   337,
     357,     0,   259,    45,    47,     0,   252,     0,    83,    83,
       0,     0,     0,     0,    63,    86,    49,   267,     0,    35,
       0,    37,    33,   263,     0,     0,   326,     0,   366,   338,
     360,     0,     0,     0,   356,   368,   349,   350,     0,   339,
       0,     0,    30,    31,     0,   109,   106,   257,     0,   249,
     111,   164,   163,     0,   374,     0,     0,     0,     0,     0,
       0,     0,     0,   247,     0,    83,     0,    36,     0,     0,
       0,     0,   332,   362,   344,   345,   346,   370,   354,   333,
      24,   191,   266,   342,   341,   375,     0,   340,    46,    48,
      58,     0,    83,     0,    55,     0,    61,    38,     0,   329,
     367,   328,     0,   334,    56,     0,    54,     0,    39,   369,
       0,    53,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -459,  -459,    16,     4,    -3,  -459,   532,  -459,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,   176,  -459,  -459,
    -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,  -459,
    -459,   -22,     2,     7,  -238,   -43,  -182,  -459,  -459,   217,
     213,   218,   212,   214,   220,   -14,  -167,   -16,    -2,   -64,
     201,  -459,  -459,   198,   -24,   -17,    13,  -253,   -13,    20,
    -351,  -255,  -247,  -459,  -237,  -228,  -133,  -110,   573,  -459,
     121,   -40,  -459,   555,  -199,  -459,    -1,   162,  -459,  -459,
       0,   461,  -459,  -459,     8,  -459,  -459,   145,   375,  -131,
    -459,     6,  -404,   -63,  -459,  -458,  -459,   -28,  -268
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    58,   271,    60,    61,    62,   229,    63,   417,    64,
      65,    66,    67,    68,    69,    70,    71,   401,    72,   404,
     565,    73,    74,    75,    76,    77,    78,    79,   216,    80,
      81,   210,   126,    82,   501,   486,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   533,   100,   101,   102,   390,   103,   104,
     339,   105,   106,   287,   107,   467,   283,   394,   211,   272,
     273,   205,   108,   290,   227,   109,   153,   154,   110,   111,
     136,   392,   113,   114,   206,   115,   116,   593,   440,   432,
     433,   434,   549,   656,   708,   541,   542,   543,   461
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     112,   149,   212,   123,   112,   458,   279,   274,   120,   395,
     128,   402,   477,   459,   612,   155,    59,   135,   423,   410,
     140,   581,   224,   460,   450,   458,   476,   124,   207,   208,
     140,   140,   213,   459,   150,   152,   152,   289,   546,   291,
     547,   359,   124,   460,   221,   222,   124,   112,   285,  -159,
    -159,   150,   150,   124,   457,   479,   278,   282,   133,   112,
     122,   275,    45,   341,   134,   284,   288,   118,   150,  -296,
     156,    50,   117,   150,   150,   151,   150,   219,    52,   342,
     368,   369,   370,   137,   358,   157,   398,   385,   386,   449,
      45,   482,   220,   360,   274,   381,   382,   225,   232,   274,
    -161,  -161,   548,   556,   125,   279,   485,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   125,
    -297,   375,   112,   127,   615,   393,   393,   406,   393,   408,
     127,   385,   386,  -278,   550,   376,   393,  -279,   122,   472,
     473,   474,   649,   475,   385,   386,   371,   372,   133,   551,
    -306,   650,    45,   480,   481,   422,  -162,  -162,   282,  -164,
    -164,   286,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,  -298,   431,   503,   674,
     138,   658,   727,   387,   424,   388,   580,   389,   430,   574,
     425,   728,   119,   133,   209,   579,   472,    45,   474,   121,
     475,   511,   512,   513,   514,   515,   419,  -159,  -159,   426,
     420,   443,   441,   427,   442,   447,   428,   444,   129,   562,
     427,   445,   279,   552,   638,   377,   378,   379,   427,   149,
     212,   487,   112,   476,   123,   112,   456,   274,   214,   120,
     431,   128,   487,   155,   552,  -161,  -161,   553,   135,   732,
     215,   700,   289,   620,  -162,  -162,   207,   208,   140,   140,
     213,   217,   150,   152,   152,   552,   218,   560,   554,   625,
     226,   112,   278,   282,   228,   341,   552,   275,    14,   569,
     552,   288,   458,   645,   150,  -158,  -158,   476,   150,   150,
     459,  -156,  -156,   552,   282,   566,   688,   231,   583,   552,
     460,   286,   694,   340,   431,   588,   589,   590,   591,   552,
     124,    33,   721,   520,   521,   522,   343,   598,  -157,  -157,
     366,   367,   361,   142,   143,   144,   132,   373,   374,   383,
     384,   362,   640,   363,   124,    38,  -160,  -160,   364,   133,
     365,   145,   146,    45,   540,   147,  -164,  -164,   677,   134,
    -163,  -163,   509,   510,   148,   380,    50,   516,   517,   534,
     534,   458,   391,    52,   524,   525,   396,    55,   403,   459,
      57,   416,   405,   518,   519,   407,   409,   559,   157,   460,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   220,   539,   544,   558,   225,   429,   435,
     436,   150,   150,   535,   535,   437,   140,   282,   689,   438,
     439,   420,   393,   451,   448,   715,   452,   152,   453,   357,
     631,  -285,   454,   636,   455,  -319,   274,   576,   458,   540,
     462,   469,  -301,   466,   484,   468,   459,   478,   -57,   561,
     680,   483,   555,   563,   564,   635,   460,   152,   567,   431,
     584,   641,   568,   571,   112,   112,   431,   431,   431,   431,
     570,   729,   112,   731,   551,   572,   456,   573,   431,   607,
     604,   606,   526,   527,   528,   611,   577,   585,   586,   539,
     587,   613,   592,   594,   595,   617,   596,   599,   133,   600,
     529,   530,    45,   601,   531,   602,   714,  -315,   608,   685,
     610,   619,   618,   532,   622,   629,   630,   621,   627,   626,
     637,   639,   643,   648,   651,   652,   654,   487,   655,   487,
     670,   657,   661,   662,   663,   664,   678,   690,   679,   687,
     695,   668,   671,   675,   681,   274,   686,   697,   696,   624,
     642,   693,   674,   711,   698,   707,   699,   701,   716,   710,
     719,   720,   722,   112,   112,   -58,   738,   633,   634,   632,
     723,   644,   393,   282,   730,   737,   646,   739,   393,   140,
     740,   431,   230,   557,   504,   506,   502,   647,   507,   665,
     505,   523,   536,   659,   540,   508,   141,   609,   223,   582,
     666,   597,   446,   660,   667,   703,   669,   415,     0,   684,
       0,     0,     0,     0,   112,     0,   112,   431,   341,   358,
     341,     0,   150,     0,     0,     0,   691,   692,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,     0,     0,     0,   539,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   393,   140,   140,     0,     0,     0,
     431,     0,     0,     0,   702,     0,     0,   413,   704,   705,
     706,     0,     0,     0,   540,   709,     0,   628,     0,     0,
       0,     0,     0,   725,     0,   713,     0,     0,     0,     0,
       0,   712,     0,   717,     0,     0,     0,   112,     0,     0,
       0,   718,     0,   726,   112,     0,     0,     0,   724,     0,
     735,     0,   140,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   733,   539,     0,     0,     0,     0,     0,
       0,   112,     0,   112,     0,   734,     0,   736,     0,   140,
       0,     0,     0,     0,     0,     0,     0,   112,     0,     0,
     112,   741,    -2,     1,   742,     0,     2,     0,     3,     4,
       5,     0,     6,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,    38,
      39,    40,    41,    42,     0,    43,    44,    45,     0,    46,
       0,     0,   -81,    47,     0,    48,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,    51,    52,     0,    53,
      54,    55,     1,    56,    57,   233,   159,   234,   235,   236,
       0,   237,   164,   165,   238,   239,   240,   241,    11,    12,
      13,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,    27,    28,    29,   255,   184,   185,
     186,   187,   188,     0,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   256,   257,   258,   259,
     193,     0,     0,     0,     0,     0,     0,   260,    38,    39,
      40,    41,   261,     0,    43,    44,   262,   196,    46,     0,
       0,   -81,    47,   263,   264,     0,     0,   265,     0,   266,
       0,     0,     0,     0,     0,    51,   267,   200,   268,   269,
     270,   204,    56,    57,     1,     0,     0,     2,     0,     3,
       4,     5,     0,     6,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,    42,     0,    43,    44,    45,     0,
      46,     0,     0,   -81,    47,   263,    48,     0,     0,    49,
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
       0,     0,   -81,    47,     0,    48,     0,  -273,    49,     0,
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
       0,   -81,    47,   465,    48,     0,     0,    49,     0,    50,
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
     -81,    47,   603,    48,     0,     0,    49,     0,    50,     0,
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
      47,   605,    48,     0,     0,    49,     0,    50,     0,     0,
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
     672,    48,     0,     0,    49,     0,    50,     0,     0,     0,
       0,     0,    51,    52,     0,    53,    54,    55,     1,    56,
      57,     2,     0,     3,     4,     5,     0,     6,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,     0,     0,   -81,    47,   673,
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
      44,    45,     0,    46,     0,     0,   -81,    47,     0,    48,
       0,     0,    49,     0,    50,     0,     0,     0,     0,     0,
      51,    52,   124,    53,    54,    55,     0,    56,    57,   158,
     159,   160,   161,   162,     0,   163,   164,   165,   166,   167,
     168,   169,     0,     0,     0,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,     0,     0,
       0,   183,   184,   185,   186,   187,   188,     0,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     189,   190,   191,   192,   193,     0,     0,     0,     0,     0,
       0,   260,     0,     0,     0,     0,   411,   357,   -85,     0,
     195,   196,     0,     0,     0,     0,     0,   418,   197,     0,
       0,   412,     0,   198,     0,     0,     0,     0,     0,     0,
     199,   200,   201,   202,   203,   204,   158,   159,   160,   161,
     162,     0,   163,   164,   165,   166,   167,   168,   169,     0,
       0,     0,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,     0,     0,     0,   183,   184,
     185,   186,   187,   188,     0,     0,     0,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
       0,     0,     0,     0,     0,     0,     0,   189,   190,   191,
     192,   193,     0,     0,     0,     0,     0,     0,   260,     0,
       0,     0,     0,   411,     0,     0,   413,   195,   196,     0,
       0,     0,     0,     0,   470,   197,   676,     0,   412,     0,
     198,     0,     0,     0,     0,     0,     0,   199,   200,   201,
     202,   203,   204,   158,   159,   160,   161,   162,     0,   163,
     164,   165,   166,   167,   168,   169,     0,     0,     0,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,     0,     0,     0,   183,   184,   185,   186,   187,
     188,     0,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   189,   190,   191,   192,   193,     0,
       0,     0,     0,     0,     0,   260,     0,     0,     0,     0,
     411,   413,     0,     0,   195,   196,     0,     0,     0,   471,
       0,   653,   197,     0,     0,   412,     0,   198,     0,     0,
       0,     0,     0,     0,   199,   200,   201,   202,   203,   204,
     158,   159,   160,   161,   162,     0,   163,   164,   165,   166,
     167,   168,   169,     0,     0,     0,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,     0,   183,   184,   185,   186,   187,   188,     0,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   189,   190,   191,   192,   193,     0,     0,     0,     0,
       0,     0,   260,     0,     0,     0,     0,   411,   413,     0,
       0,   195,   196,     0,     0,     0,   578,     0,     0,   197,
       0,     0,   412,     0,   198,     0,     0,     0,     0,     0,
       0,   199,   200,   201,   202,   203,   204,   158,   159,   160,
     161,   162,     0,   163,   164,   165,   166,   167,   168,   169,
       0,     0,     0,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,     0,     0,     0,   183,
     184,   185,   186,   187,   188,     0,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   189,   190,
     191,   192,   193,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   194,   413,     0,     0,   195,   196,
       0,     0,     0,   682,     0,     0,   197,     0,     0,     0,
       0,   198,     0,     0,     0,     0,     0,     0,   199,   200,
     201,   202,   203,   204,   292,   293,   294,   295,   296,     0,
     297,   298,   299,   300,   301,   302,   303,   304,     0,     0,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,     0,     0,     0,   318,   319,   320,   321,
     322,   323,     0,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   324,   325,   326,   327,   328,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   329,   413,     0,     0,     0,   330,     0,   414,     0,
       0,     0,     0,   331,     0,     0,     0,     0,   332,     0,
       0,     0,     0,     0,     0,   333,   334,   335,   336,   337,
     338,   292,   293,   294,   295,   296,     0,   297,   298,   299,
     300,   301,   302,   303,   304,     0,     0,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
       0,     0,     0,   318,   319,   320,   321,   322,   323,     0,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   324,   325,   326,   327,   328,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   329,   413,
       0,     0,     0,   545,     0,     0,     0,     0,     0,     0,
     331,     0,     0,     0,     0,   332,     0,     0,     0,     0,
       0,     0,   333,   334,   335,   336,   337,   338,   292,   293,
     294,   295,   296,     0,   297,   298,   299,   300,   301,   302,
     303,   304,     0,     0,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,     0,     0,     0,
     318,   319,   320,   321,   322,   323,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
       0,     0,    17,   130,     0,     0,     0,     0,     0,   324,
     325,   326,   327,   328,     0,   131,     0,     0,     0,     0,
       0,     0,     0,    31,    32,   329,     0,     0,     0,     0,
     614,     0,    33,     0,     0,     0,     0,   331,     0,     0,
       0,     0,   332,     0,    34,    35,    36,   132,     0,   333,
     334,   335,   336,   337,   338,   280,    38,     0,     0,     0,
     133,     0,    43,    44,    45,     0,    46,     0,     0,     0,
     134,     0,    48,     0,     0,    49,     0,    50,   281,     0,
       0,     0,     0,    51,    52,     0,    53,    54,    55,     0,
      56,    57,    14,   397,     0,    17,   130,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   131,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,     0,    38,
       0,     0,     0,   398,     0,    43,    44,    45,   131,    46,
       0,     0,   399,   134,     0,    48,    31,    32,    49,     0,
     400,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,   280,    38,
       0,     0,     0,   133,     0,    43,    44,    45,   131,    46,
       0,     0,     0,   134,     0,    48,    31,    32,    49,     0,
      50,   464,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,   537,    38,
       0,     0,     0,   133,   538,    43,    44,    45,   131,    46,
       0,     0,     0,   277,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,   683,    38,
       0,     0,     0,   133,   538,    43,    44,    45,   131,    46,
       0,     0,     0,   277,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,     0,    38,
       0,     0,     0,   133,   276,    43,    44,    45,   131,    46,
       0,     0,     0,   277,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,     0,    38,
       0,     0,     0,   133,   421,    43,    44,    45,   131,    46,
       0,     0,     0,   277,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,   280,    38,
       0,     0,     0,   133,     0,    43,    44,    45,   131,    46,
       0,     0,     0,   134,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,   133,     0,    43,    44,    45,     0,    46,
       0,     0,     0,   139,     0,    48,     0,  -293,    49,    14,
      50,     0,    17,   130,     0,     0,    51,    52,     0,    53,
      54,    55,     0,    56,    57,   131,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,    36,   132,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
     133,     0,    43,    44,    45,     0,    46,     0,     0,     0,
     139,     0,    48,     0,  -295,    49,    14,    50,     0,    17,
     130,     0,     0,    51,    52,     0,    53,    54,    55,     0,
      56,    57,   131,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,    36,   132,     0,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,   133,     0,    43,
      44,    45,     0,    46,     0,     0,     0,   134,     0,    48,
       0,  -294,    49,    14,    50,     0,    17,   130,     0,     0,
      51,    52,     0,    53,    54,    55,     0,    56,    57,   131,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,   132,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,   133,   463,    43,    44,    45,     0,
      46,     0,     0,     0,   277,     0,    48,     0,     0,    49,
       0,    50,    14,     0,     0,    17,   130,    51,    52,     0,
      53,    54,    55,   500,    56,    57,     0,     0,   131,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,     0,    38,
       0,     0,     0,   133,     0,    43,    44,    45,   131,    46,
       0,     0,     0,   277,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,   616,    38,
       0,     0,     0,   133,     0,    43,    44,    45,   131,    46,
       0,     0,     0,   134,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,     0,    38,
       0,     0,     0,   133,   623,    43,    44,    45,   131,    46,
       0,     0,     0,   134,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,     0,    38,
       0,     0,     0,   133,     0,    43,    44,    45,   131,    46,
       0,     0,     0,   134,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,     0,    38,
       0,     0,     0,   133,     0,    43,    44,    45,   131,    46,
       0,     0,     0,   139,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,     0,    38,
       0,     0,     0,   133,     0,    43,    44,    45,   131,    46,
       0,     0,     0,   277,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,    17,   130,     0,     0,    38,
       0,     0,     0,   133,     0,    43,    44,    45,   131,    46,
       0,     0,     0,   575,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,    14,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,   133,     0,    43,    44,    45,     0,    46,
       0,     0,     0,    47,     0,    48,    31,    32,    49,     0,
      50,     0,     0,     0,     0,    33,    51,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,   142,   143,   144,
     132,     0,    14,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,   133,     0,   145,   146,    45,     0,   147,
       0,     0,     0,   134,     0,    48,    31,    32,   148,     0,
      50,     0,     0,     0,     0,    33,     0,    52,     0,    53,
      54,    55,     0,    56,    57,     0,     0,    34,    35,    36,
     132,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,   133,     0,    43,    44,    45,     0,    46,
       0,     0,     0,   134,     0,    48,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,     0,    52,     0,    53,
      54,    55,     0,    56,    57
};

static const yytype_int16 yycheck[] =
{
       0,    14,    24,     6,     4,   260,    49,    47,     4,   119,
       8,   121,   280,   260,   472,    16,     0,    10,   151,   129,
      13,   425,    21,   260,   223,   280,   279,     4,    20,    21,
      23,    24,    25,   280,    14,    15,    16,    54,   389,    56,
      23,    49,     4,   280,    31,    32,     4,    47,    51,    75,
      76,    31,    32,     4,    81,   283,    49,    50,    81,    59,
      91,    48,    85,    59,    91,    96,    53,    96,    48,    95,
      81,    98,    90,    53,    54,    98,    56,    81,   105,    77,
      39,    40,    41,    95,    82,    96,    81,    44,    45,   220,
      85,   290,    96,   101,   134,    63,    64,    96,    95,   139,
      75,    76,    85,    98,    81,   148,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,    81,
      95,    93,   122,    81,   475,   118,   119,   125,   121,   127,
      81,    44,    45,    95,    81,   107,   129,    95,    91,    96,
      97,    98,    84,   100,    44,    45,   105,   106,    81,    96,
      95,    93,    85,   284,   287,   148,    75,    76,   151,    75,
      76,   106,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,    95,   157,   360,    95,
      91,   585,    84,    96,    89,    98,   424,   100,    76,   417,
      95,    93,    96,    81,    81,   423,    96,    85,    98,    96,
     100,   368,   369,   370,   371,   372,    90,    75,    76,    90,
      94,   214,   210,    94,   212,   218,    90,    90,    96,    90,
      94,    94,   265,    94,    90,   108,   109,   110,    94,   242,
     252,   413,   232,   486,   237,   235,   232,   277,    81,   235,
     220,   239,   424,   244,    94,    75,    76,    97,   241,   707,
      81,   655,   269,   481,    75,    76,   248,   249,   251,   252,
     253,    81,   242,   243,   244,    94,    81,   400,    97,   537,
      96,   271,   265,   266,    81,   271,    94,   264,    20,    97,
      94,   268,   537,    97,   264,    75,    76,   540,   268,   269,
     537,    75,    76,    94,   287,   405,    97,    90,   429,    94,
     537,   106,    97,     0,   284,   436,   437,   438,   439,    94,
       4,    53,    97,   377,   378,   379,    90,   448,    75,    76,
      37,    38,    42,    65,    66,    67,    68,    46,    47,    75,
      76,    43,   560,   102,     4,    77,    75,    76,   103,    81,
     104,    83,    84,    85,   387,    87,    75,    76,   616,    91,
      75,    76,   366,   367,    96,    48,    98,   373,   374,   383,
     384,   616,   105,   105,   381,   382,     6,   109,    11,   616,
     112,    81,    96,   375,   376,    90,    90,   399,    96,   616,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    96,   387,   388,   397,    96,    96,    99,
      96,   381,   382,   383,   384,    96,   399,   400,   636,    96,
      96,    94,   405,    81,    96,   683,    96,   397,    82,    89,
     551,    95,    91,   556,    91,    96,   466,   420,   683,   472,
      95,    97,    95,    94,    90,    95,   683,    94,     9,     9,
     622,    99,    96,    96,    12,   555,   683,   427,    90,   429,
     430,   561,    90,    82,   454,   455,   436,   437,   438,   439,
      95,   699,   462,   701,    96,    89,   462,    94,   448,   462,
     454,   455,    65,    66,    67,   468,    97,    95,    97,   472,
      94,   474,    95,    90,    90,   478,    81,    97,    81,    89,
      83,    84,    85,    82,    87,    97,   678,    95,    97,   630,
      92,    97,    99,    96,    95,   106,    96,   500,    94,    97,
       9,    90,    81,    97,    81,    92,    99,   699,    96,   701,
      82,    97,    97,    97,    97,    97,    70,   637,    74,     5,
      90,    97,    97,    97,    97,   575,    97,    84,    97,   532,
     562,    99,    95,    97,    89,    96,    89,    89,    97,    90,
      90,    99,    90,   553,   554,     9,    84,   553,   554,   552,
      97,   564,   555,   556,    97,    97,   569,    97,   561,   562,
      97,   551,    40,   397,   361,   363,   359,   570,   364,   592,
     362,   380,   384,   586,   627,   365,    13,   466,    33,   427,
     593,   446,   217,   587,   597,   658,   599,   136,    -1,   627,
      -1,    -1,    -1,    -1,   604,    -1,   606,   587,   604,   607,
     606,    -1,   592,    -1,    -1,    -1,   638,   639,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    -1,   627,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   637,   638,   639,    -1,    -1,    -1,
     630,    -1,    -1,    -1,   657,    -1,    -1,    89,   661,   662,
     663,    -1,    -1,    -1,   707,   668,    -1,    99,    -1,    -1,
      -1,    -1,    -1,   695,    -1,   678,    -1,    -1,    -1,    -1,
      -1,   674,    -1,   686,    -1,    -1,    -1,   687,    -1,    -1,
      -1,   687,    -1,   696,   694,    -1,    -1,    -1,   694,    -1,
     722,    -1,   695,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   716,   707,    -1,    -1,    -1,    -1,    -1,
      -1,   721,    -1,   723,    -1,   721,    -1,   723,    -1,   722,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   737,    -1,    -1,
     740,   737,     0,     1,   740,    -1,     4,    -1,     6,     7,
       8,    -1,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,    81,    -1,    83,    84,    85,    -1,    87,
      -1,    -1,    90,    91,    -1,    93,    -1,    -1,    96,    -1,
      98,    -1,    -1,    -1,    -1,    -1,   104,   105,    -1,   107,
     108,   109,     1,   111,   112,     4,     5,     6,     7,     8,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    -1,    83,    84,    85,    86,    87,    -1,
      -1,    90,    91,    92,    93,    -1,    -1,    96,    -1,    98,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,   108,
     109,   110,   111,   112,     1,    -1,    -1,     4,    -1,     6,
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
      -1,    -1,    90,    91,    -1,    93,    -1,    95,    96,    -1,
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
      84,    85,    -1,    87,    -1,    -1,    90,    91,    -1,    93,
      -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,
     104,   105,     4,   107,   108,   109,    -1,   111,   112,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    81,    89,    90,    -1,
      85,    86,    -1,    -1,    -1,    -1,    -1,    92,    93,    -1,
      -1,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,
     105,   106,   107,   108,   109,   110,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    89,    85,    86,    -1,
      -1,    -1,    -1,    -1,    92,    93,    99,    -1,    96,    -1,
      98,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,   107,
     108,   109,   110,     4,     5,     6,     7,     8,    -1,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,
      81,    89,    -1,    -1,    85,    86,    -1,    -1,    -1,    97,
      -1,    92,    93,    -1,    -1,    96,    -1,    98,    -1,    -1,
      -1,    -1,    -1,    -1,   105,   106,   107,   108,   109,   110,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    41,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    81,    89,    -1,
      -1,    85,    86,    -1,    -1,    -1,    97,    -1,    -1,    93,
      -1,    -1,    96,    -1,    98,    -1,    -1,    -1,    -1,    -1,
      -1,   105,   106,   107,   108,   109,   110,     4,     5,     6,
       7,     8,    -1,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    41,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    89,    -1,    -1,    85,    86,
      -1,    -1,    -1,    97,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,
     107,   108,   109,   110,     4,     5,     6,     7,     8,    -1,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    89,    -1,    -1,    -1,    86,    -1,    95,    -1,
      -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,   105,   106,   107,   108,   109,
     110,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    89,
      -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,
      -1,    -1,   105,   106,   107,   108,   109,   110,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    81,    -1,    -1,    -1,    -1,
      86,    -1,    53,    -1,    -1,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    98,    -1,    65,    66,    67,    68,    -1,   105,
     106,   107,   108,   109,   110,    76,    77,    -1,    -1,    -1,
      81,    -1,    83,    84,    85,    -1,    87,    -1,    -1,    -1,
      91,    -1,    93,    -1,    -1,    96,    -1,    98,    99,    -1,
      -1,    -1,    -1,   104,   105,    -1,   107,   108,   109,    -1,
     111,   112,    20,    21,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,    87,
      -1,    -1,    90,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    99,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
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
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,
      84,    85,    -1,    87,    -1,    -1,    -1,    91,    -1,    93,
      -1,    95,    96,    20,    98,    -1,    23,    24,    -1,    -1,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,
      87,    -1,    -1,    -1,    91,    -1,    93,    -1,    -1,    96,
      -1,    98,    20,    -1,    -1,    23,    24,   104,   105,    -1,
     107,   108,   109,    31,   111,   112,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    76,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    91,    -1,    93,    44,    45,    96,    -1,
      98,    -1,    -1,    -1,    -1,    53,    -1,   105,    -1,   107,
     108,   109,    -1,   111,   112,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    91,    -1,    93,    -1,    -1,    96,    -1,
      98,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,   107,
     108,   109,    -1,   111,   112
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
      66,    67,    68,    69,    81,    85,    86,    93,    98,   105,
     106,   107,   108,   109,   110,   184,   197,   197,   197,    81,
     144,   181,   144,   146,    81,    81,   141,    81,    81,    81,
      96,   169,   169,   186,    21,    96,    96,   187,    81,   119,
     119,    90,    95,     4,     6,     7,     8,    10,    13,    14,
      15,    16,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    36,    65,    66,    67,    68,
      76,    81,    85,    92,    93,    96,    98,   105,   107,   108,
     109,   115,   182,   183,   184,   169,    82,    91,   146,   148,
      76,    99,   146,   179,    96,   117,   106,   176,   169,   168,
     186,   168,     4,     5,     6,     7,     8,    10,    11,    12,
      13,    14,    15,    16,    17,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    36,    37,
      38,    39,    40,    41,    65,    66,    67,    68,    69,    81,
      86,    93,    98,   105,   106,   107,   108,   109,   110,   173,
       0,   116,   145,    90,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    89,   145,    49,
     101,    42,    43,   102,   103,   104,    37,    38,    39,    40,
      41,   105,   106,    46,    47,    93,   107,   108,   109,   110,
      48,    63,    64,    75,    76,    44,    45,    96,    98,   100,
     170,   105,   194,   146,   180,   180,     6,    21,    81,    90,
      98,   130,   180,    11,   132,    96,   145,    90,   145,    90,
     180,    81,    96,    89,    95,   194,    81,   121,    92,    90,
      94,    82,   146,   179,    89,    95,    90,    94,    90,    96,
      76,   172,   202,   203,   204,    99,    96,    96,    96,    96,
     201,   145,   145,   117,    90,    94,   201,   117,    96,   202,
     187,    81,    96,    82,    91,    91,   116,    81,   174,   175,
     177,   211,    95,    82,    99,    92,    94,   178,    95,    97,
      92,    97,    96,    97,    98,   100,   170,   211,    94,   178,
     202,   179,   187,    99,    90,   147,   148,   149,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
      31,   147,   152,   149,   153,   154,   155,   156,   157,   158,
     158,   159,   159,   159,   159,   159,   160,   160,   161,   161,
     162,   162,   162,   163,   168,   168,    65,    66,    67,    83,
      84,    87,    96,   166,   167,   172,   166,    76,    82,   146,
     148,   208,   209,   210,   146,    86,   173,    23,    85,   205,
      81,    96,    94,    97,    97,    96,    98,   130,   189,   144,
     179,     9,    90,    96,    12,   133,   180,    90,    90,    97,
      95,    82,    89,    94,   178,    91,   146,    97,    97,   178,
     147,   205,   190,   202,   172,    95,    97,    94,   202,   202,
     202,   202,    95,   200,    90,    90,    81,   200,   202,    97,
      89,    82,    97,    92,   115,    92,   115,   146,    97,   183,
      92,   146,   208,   146,    86,   173,    76,   146,    99,    97,
     178,   146,    95,    82,   146,   211,    97,    94,    99,   106,
      96,   202,   146,   116,   116,   180,   179,     9,    90,    90,
     178,   180,   144,    81,   117,    97,   117,   146,    97,    84,
      93,    81,    92,    92,    99,    96,   206,    97,   205,   117,
     204,    97,    97,    97,    97,   171,   117,   117,    97,   117,
      82,    97,    92,    92,    95,    97,    99,   211,    70,    74,
     149,    97,    97,    76,   210,   202,    97,     5,    97,   178,
     180,   144,   144,    99,    97,    90,    97,    84,    89,    89,
     205,    89,   117,   206,   117,   117,   117,    96,   207,   117,
      90,    97,   146,   117,   149,   211,    97,   117,   116,    90,
      99,    97,    90,    97,   116,   144,   117,    84,    93,   147,
      97,   147,   208,   117,   116,   144,   116,    97,    84,    97,
      97,   116,   116
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
     173,   173,   173,   173,   173,   173,   174,   174,   175,   175,
     176,   177,   178,   178,   179,   179,   179,   179,   180,   180,
     181,   181,   181,   181,   182,   182,   183,   183,   183,   183,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   185,   185,   185,   186,
     187,   188,   188,   189,   189,   190,   190,   190,   190,   190,
     191,   191,   192,   192,   192,   193,   194,   194,   195,   195,
     195,   195,   195,   195,   196,   196,   196,   197,   197,   198,
     198,   199,   199,   200,   200,   201,   201,   202,   202,   203,
     203,   204,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208,   209,   209,   209,   209,   210,   210,   210,   211,
     211,   211,   211
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
       1,     1,     1,     1,     1,     2,     2,     4,     2,     5,
       0,     4,     0,     1,     1,     2,     3,     4,     1,     3,
       1,     2,     3,     4,     1,     3,     5,     3,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     2,     0,
       3,     3,     3,     1,     3,     1,     4,     3,     6,     6,
       1,     1,     6,     6,     7,     1,     0,     3,     5,     5,
       6,     6,     6,     2,     6,     6,     6,     1,     1,     5,
       5,     3,     3,     0,     3,     0,     3,     0,     1,     1,
       3,     1,     4,     2,     1,     1,     0,     3,     0,     3,
       0,     1,     1,     2,     3,     4,     1,     1,     1,     1,
       1,     1,     1
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
    { (yyval.obj) = kx_gen_str_object("<=>"); }
#line 3628 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 575 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("+"); }
#line 3634 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 576 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("-"); }
#line 3640 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 577 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("*"); }
#line 3646 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 578 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("/"); }
#line 3652 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 579 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("%"); }
#line 3658 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 580 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("[]"); }
#line 3664 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 584 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3670 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 585 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3676 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 589 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3682 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 590 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3688 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 594 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3694 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 598 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3700 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 602 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3706 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 608 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3712 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3718 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 610 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3724 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 615 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3730 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 620 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3736 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 621 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3742 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 622 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3748 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 627 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3754 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 631 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3760 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 632 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3766 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3772 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 634 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3778 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 638 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3784 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 639 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3790 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 640 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3796 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3802 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3808 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 643 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3814 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 644 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3820 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3826 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3832 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 647 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3838 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 648 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3844 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 649 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3850 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3856 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 651 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3862 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 652 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3868 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 653 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3874 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 654 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3880 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3886 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3892 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3898 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 658 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3904 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 659 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3910 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 660 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3916 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 661 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3922 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 662 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "yield"; }
#line 3928 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 663 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3934 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 664 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3940 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 665 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3946 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 666 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3952 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 667 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3958 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 668 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3964 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 669 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3970 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3976 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 671 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "=="; }
#line 3982 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 672 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "!="; }
#line 3988 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 673 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<="; }
#line 3994 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 674 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<"; }
#line 4000 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 675 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">="; }
#line 4006 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 676 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = ">"; }
#line 4012 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 677 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "<=>"; }
#line 4018 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 678 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "+"; }
#line 4024 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 679 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "-"; }
#line 4030 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 680 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "*"; }
#line 4036 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 681 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "/"; }
#line 4042 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 682 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "%"; }
#line 4048 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 683 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "[]"; }
#line 4054 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 687 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4060 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 688 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 4066 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 689 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 4072 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 693 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 4078 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 697 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 4084 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 701 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4090 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 702 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 4096 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 707 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4102 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 711 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 4108 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 712 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 4114 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 713 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 4120 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 714 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 4126 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 715 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 4132 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 719 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4138 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 720 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 4144 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 724 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4150 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 725 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4156 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 726 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4162 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 730 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 4168 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 734 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 4174 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 735 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4180 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 739 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4186 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 740 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4192 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 741 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4198 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 742 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 4204 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 743 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 4210 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 744 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 4216 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 748 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4222 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 749 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4228 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 750 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 4234 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 759 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4240 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 760 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 4246 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 764 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4252 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 765 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 4258 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 769 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4264 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 771 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 4277 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 782 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4283 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 783 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4289 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 787 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4295 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 793 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 4301 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 797 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4307 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 798 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 4313 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 799 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 4319 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 803 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 4325 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 804 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 4331 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 808 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 4337 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 809 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 4343 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 813 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4349 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 814 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 4355 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 818 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 4361 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 824 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 4367 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 825 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 4373 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 826 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 4379 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 832 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 4385 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 836 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 4391 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 837 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4397 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 838 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4403 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 839 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 4409 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 4413 "kx.tab.c" /* yacc.c:1646  */
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
#line 842 "src/kinx.y" /* yacc.c:1906  */


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
