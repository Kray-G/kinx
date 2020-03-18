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
    NEW = 273,
    VAR = 274,
    CONST = 275,
    NATIVE = 276,
    SYSFUNC = 277,
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
    EQEQ = 290,
    NEQ = 291,
    LE = 292,
    GE = 293,
    LGE = 294,
    LOR = 295,
    LAND = 296,
    INC = 297,
    DEC = 298,
    SHL = 299,
    SHR = 300,
    POW = 301,
    LUNDEF = 302,
    ADDEQ = 303,
    SUBEQ = 304,
    MULEQ = 305,
    DIVEQ = 306,
    MODEQ = 307,
    ANDEQ = 308,
    OREQ = 309,
    XOREQ = 310,
    LANDEQ = 311,
    LOREQ = 312,
    LUNDEFEQ = 313,
    SHLEQ = 314,
    SHREQ = 315,
    REGEQ = 316,
    REGNE = 317,
    NUL = 318,
    TRUE = 319,
    FALSE = 320,
    IMPORT = 321,
    USING = 322,
    DARROW = 323,
    SQ = 324,
    DQ = 325,
    MLSTR = 326,
    BINEND = 327,
    DOTS3 = 328,
    REGPF = 329,
    NAMESPACE = 330,
    SYSNS = 331,
    NAME = 332,
    STR = 333,
    BIGINT = 334,
    INT = 335,
    TYPE = 336,
    TYPEOF = 337,
    DBL = 338,
    BIN = 339
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

#line 223 "kx.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE kx_yylval;

int kx_yyparse (void);

#endif /* !YY_KX_YY_KX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 240 "kx.tab.c" /* yacc.c:358  */

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
#define YYFINAL  260
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3452

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  109
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  92
/* YYNRULES -- Number of rules.  */
#define YYNRULES  330
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  646

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   107,     2,     2,     2,   106,   100,     2,
      92,    93,   104,   103,    90,    89,    96,   105,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    91,    86,
     101,    85,   102,    97,   108,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    94,     2,    95,    99,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,    98,    88,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   132,   132,   136,   137,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   164,   165,   169,   170,   171,
     172,   176,   180,   184,   185,   186,   187,   188,   189,   193,
     194,   195,   196,   200,   204,   205,   209,   213,   217,   221,
     222,   226,   233,   240,   250,   254,   255,   259,   260,   264,
     265,   266,   267,   271,   275,   279,   280,   281,   282,   286,
     290,   294,   295,   299,   303,   304,   308,   309,   313,   314,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   336,   337,   341,   342,   343,
     344,   345,   346,   350,   351,   355,   356,   360,   361,   365,
     366,   370,   371,   375,   376,   380,   381,   385,   386,   390,
     391,   392,   396,   397,   398,   399,   400,   401,   405,   406,
     407,   411,   412,   413,   417,   418,   419,   420,   424,   425,
     429,   430,   431,   435,   436,   437,   438,   439,   440,   441,
     445,   446,   447,   448,   449,   450,   454,   455,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   480,   481,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     520,   521,   525,   526,   530,   534,   538,   539,   543,   544,
     545,   546,   550,   551,   555,   556,   557,   558,   562,   563,
     567,   568,   569,   570,   574,   575,   576,   577,   578,   579,
     580,   581,   582,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   598,   599,
     600,   601,   602,   603,   604,   605,   609,   610,   611,   615,
     619,   623,   624,   628,   629,   633,   634,   635,   636,   637,
     641,   642,   646,   647,   648,   652,   656,   657,   661,   662,
     663,   664,   665,   666,   670,   671,   672,   676,   677,   681,
     682,   686,   687,   699,   700,   704,   705,   709,   710,   714,
     715,   716,   720,   721,   725,   726,   730,   731,   735,   736,
     740,   741,   742,   743,   747,   748,   749,   753,   754,   755,
     756
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ERROR", "IF", "ELSE", "WHILE", "DO",
  "FOR", "TRY", "CATCH", "FINALLY", "BREAK", "CONTINUE", "SWITCH", "CASE",
  "DEFAULT", "ENUM", "NEW", "VAR", "CONST", "NATIVE", "SYSFUNC",
  "FUNCTION", "PUBLIC", "PRIVATE", "PROTECTED", "CLASS", "RETURN", "THROW",
  "YIELD", "MODULE", "MIXIN", "SYSCLASS", "SYSMODULE", "EQEQ", "NEQ", "LE",
  "GE", "LGE", "LOR", "LAND", "INC", "DEC", "SHL", "SHR", "POW", "LUNDEF",
  "ADDEQ", "SUBEQ", "MULEQ", "DIVEQ", "MODEQ", "ANDEQ", "OREQ", "XOREQ",
  "LANDEQ", "LOREQ", "LUNDEFEQ", "SHLEQ", "SHREQ", "REGEQ", "REGNE", "NUL",
  "TRUE", "FALSE", "IMPORT", "USING", "DARROW", "SQ", "DQ", "MLSTR",
  "BINEND", "DOTS3", "REGPF", "NAMESPACE", "SYSNS", "NAME", "STR",
  "BIGINT", "INT", "TYPE", "TYPEOF", "DBL", "BIN", "'='", "';'", "'{'",
  "'}'", "'-'", "','", "':'", "'('", "')'", "'['", "']'", "'.'", "'?'",
  "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'*'", "'/'", "'%'", "'!'",
  "'@'", "$accept", "Program", "StatementList", "Statement",
  "BlockStatement", "NamespaceStatement", "NamespaceName", "EnumStatement",
  "EnumList", "DefinitionStatement", "LabelStatement", "IfStatement",
  "WhileStatement", "DoWhileStatement", "SwitchCaseStatement",
  "CaseStatement", "ForStatement", "TryCatchStatement",
  "CatchStatement_Opt", "FinallyStatement_Opt", "BreakStatement",
  "ReturnStatement", "YieldStatement", "YieldExpression", "ThrowStatement",
  "MixinStatement", "MixinModuleList", "ExpressionStatement",
  "AssignExpression_Opt", "AssignExpressionList_Opt", "Modifier_Opt",
  "AssignExpression", "AssignRightHandSide", "ObjectSpecialSyntax",
  "TernaryExpression", "FunctionExpression", "LogicalUndefExpression",
  "LogicalOrExpression", "LogicalAndExpression", "BitOrExpression",
  "BitXorExpression", "BitAndExpression", "CompareEqualExpression",
  "CompareExpression", "ShiftExpression", "Expression", "Term",
  "Exponentiation", "RegexMatch", "PrefixExpression", "PostfixExpression",
  "PostIncDec", "Factor", "VarName", "PropertyName", "Array", "Binary",
  "BinStart", "Object", "Comma_Opt", "ArrayItemList",
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
     335,   336,   337,   338,   339,    61,    59,   123,   125,    45,
      44,    58,    40,    41,    91,    93,    46,    63,   124,    94,
      38,    60,    62,    43,    42,    47,    37,    33,    64
};
# endif

#define YYPACT_NINF -385

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-385)))

#define YYTABLE_NINF -265

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1591,     6,    38,    53,  1591,    59,    72,    34,    36,    82,
    2520,    27,   115,   290,   -34,   -34,  -385,   -19,   -16,   119,
     127,   134,   146,  2595,  2595,  2520,   147,   148,   149,   150,
     290,   290,  -385,  -385,  -385,  -385,    22,    88,   151,   151,
     141,  -385,  -385,  -385,  -385,   751,   290,  1982,  1666,    68,
     136,   290,  2875,  -385,  2875,  3218,   236,   646,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,   235,  -385,  -385,  -385,   160,   486,
    -385,  -385,   -13,   208,   213,   157,   158,   156,    32,    26,
      35,   -14,   109,   212,   105,  -385,    45,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,   159,  -385,  -385,  -385,
    -385,  -385,  2520,  2520,   255,  1757,   856,   252,   171,   235,
     178,   235,   179,  2520,   174,   175,   176,  -385,  3129,  3323,
     159,  -385,   194,  -385,   -41,  2057,   -39,  -385,    67,   180,
      75,   184,    75,   200,   201,   217,   218,  2980,   235,  3367,
     221,   235,  3367,    72,  -385,    93,   218,    72,    45,    45,
      88,   238,   220,   239,  -385,  -385,   231,   232,  1591,    38,
    -385,    53,   961,    59,    72,  -385,  -385,    31,    33,    82,
    2520,   290,   -34,   -34,   229,   -19,   -16,   119,   127,   134,
     146,  2132,  2207,   147,   230,   234,   240,    22,  -385,   -35,
     242,   243,  -385,  -385,  2282,  1066,   233,  -385,   244,    45,
     237,  3010,  3310,    40,   -35,  -385,  3367,   246,    75,  -385,
    -385,  2057,    45,  -385,    88,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,   241,  -385,  2670,  2670,  2670,  2670,  2670,  2670,
    2670,  2670,  2670,  2670,  2670,  2670,  2670,  2370,  -385,  2875,
    2875,  2875,  2875,  2875,  2875,  2875,  2875,  2875,  2875,  2875,
    2875,  2875,  2875,  2875,  2875,  2875,  2875,  2875,  2875,  2875,
    2875,  2875,  2875,  -385,  -385,  1832,  2520,  3246,  -385,    28,
      -7,  3367,   -12,   102,   245,   -34,  2595,    96,   248,   311,
    2520,   253,  -385,   257,  -385,   104,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,   254,  -385,   251,  2670,  -385,   260,   261,   259,
    2670,    28,   246,  -385,   -34,  -385,    75,   110,   266,   265,
     269,  -385,    75,   267,    75,    75,    75,    75,   270,  -385,
     276,  2745,   279,  -385,  -385,   289,   270,  -385,  -385,   283,
     297,   285,  1171,  1276,  -385,  -385,  -385,  -385,  -385,  -385,
    1591,   286,  -385,  3129,   250,  2520,  -385,  -385,  -385,  1832,
    -385,  2520,  3325,  -385,  -385,  2445,   281,   288,   246,  -385,
    -385,  -385,    48,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  2520,  -385,   208,    24,
     213,   157,   158,   156,    32,    26,    26,    35,    35,    35,
      35,    35,   -14,   -14,   109,   109,   212,   212,   212,   105,
    -385,  -385,   -35,  -385,  3367,    48,   293,   298,  -385,   247,
    -385,  -385,  -385,  -385,   292,   291,    75,  2520,  1591,  1591,
    2520,   103,   301,  2595,   313,    72,  -385,   108,  -385,  -385,
      72,  2520,   303,    46,   320,   314,  -385,   307,   306,  -385,
     310,  -385,    28,    72,    75,   317,    72,   321,   323,   325,
     331,   290,    72,  -385,  3099,  3367,  -385,  -385,    72,   326,
     332,  -385,  -385,  1381,  -385,  1486,   416,   335,  -385,  -385,
    3367,   334,  1733,  -385,  -385,   -35,  3367,  -385,   360,   357,
    3367,  2875,  -385,  -385,  1907,  -385,  -385,    75,   337,  3367,
     426,  -385,   113,  2595,  2595,   346,   340,  -385,  -385,  -385,
    3367,   335,  -385,   354,   350,  -385,    28,   351,   355,    72,
     307,  -385,  -385,    72,  -385,    72,    72,    72,  -385,   347,
    -385,  -385,  -385,   356,   348,  -385,  -385,  2520,  -385,  -385,
    -385,  2820,  -385,   396,   -35,  -385,   352,    72,  1591,   361,
     362,   353,  2595,    72,  -385,    58,   358,  2670,  2670,  -385,
    -385,  -385,  -385,  -385,  -385,  1832,  -385,  -385,  -385,  3367,
    -385,  -385,  -385,    72,  -385,  -385,  -385,  2595,  1591,   359,
    -385,  -385,   369,  -385,  -385,  -385,   363,  -385,   364,  -385,
    1591,  -385,  -385,  1591,  -385,  -385
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    78,    78,     0,
       0,     0,     0,     0,     0,     0,   285,     0,     0,     0,
       0,     0,     0,    76,    76,    66,     0,     0,     0,     0,
       0,     0,   269,   161,   163,   164,     0,     0,     0,     0,
     176,   160,   158,   177,   159,     0,     0,     0,     0,     0,
     214,     0,     0,   269,     0,     0,     0,     0,     3,     5,
       6,     7,    20,    22,     8,     9,    10,    11,    12,    13,
      14,    21,    15,    16,    78,    17,    18,    19,     0,    78,
      80,   103,   106,   107,   109,   111,   113,   115,   117,   119,
     122,   128,   131,   134,   138,   140,   143,   150,   162,   165,
     166,   167,   168,    39,    40,   280,   286,   105,   281,    41,
      42,    24,     0,     0,     0,     0,     0,    55,     0,    78,
       0,    78,     0,     0,     0,     0,     0,   176,     0,     0,
     286,    50,     0,   173,   275,     0,     0,   273,     0,     0,
     305,     0,   305,     0,     0,     0,   303,     0,    78,   224,
      77,    78,    65,     0,    71,     0,   303,     0,   148,   149,
       0,     0,     0,     0,   268,    31,     0,     0,     0,   234,
     235,   236,     0,   238,   239,   240,   241,    78,    78,   244,
     245,   246,   247,   248,   285,   251,   250,   252,   253,   254,
     255,    76,    76,   256,   161,   163,   164,   262,   263,     0,
     176,   177,   265,    25,     0,     0,   216,   228,     0,   146,
       0,     0,     0,     0,     0,   210,   218,   216,   305,   293,
     212,     0,   145,   147,     0,   144,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   197,   196,   198,   199,   200,   201,   203,
     204,   202,   205,   206,   207,   208,   209,   178,   175,   174,
       1,     4,     0,    73,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   156,   157,   318,     0,     0,   151,     0,
       0,   222,     0,     0,     0,     0,    76,     0,     0,    57,
       0,     0,    59,     0,    61,     0,   234,   236,   237,   238,
     239,   242,   243,   244,   245,   246,   247,   248,   249,   251,
     250,   252,   253,   254,   255,   257,   258,   256,   259,   260,
     261,   262,     0,   264,     0,     0,    49,     0,    33,   216,
       0,     0,   216,   271,     0,   272,   305,     0,   309,     0,
     306,   307,   305,     0,   305,   305,   305,   305,   301,   225,
       0,     0,     0,   299,    70,     0,   301,   300,   267,     0,
       0,     0,     0,     0,    43,   327,   328,   329,   330,   233,
       0,     0,    26,   217,     0,     0,   172,    97,   170,   318,
     171,     0,     0,    98,   219,   217,     0,     0,   216,   266,
      64,    84,    96,    95,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    82,    83,    68,    81,   108,     0,
     110,   112,   114,   116,   118,   120,   121,   124,   126,   127,
     123,   125,   129,   130,   133,   132,   135,   136,   137,   139,
     141,   142,     0,   326,   324,   325,     0,   319,   320,     0,
     154,   153,   313,   312,     0,     0,   305,     0,     0,     0,
       0,     0,     0,    76,     0,     0,    54,     0,    60,    62,
       0,     0,     0,     0,   217,     0,   277,   314,     0,   274,
       0,   311,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,     0,   226,    69,    72,     0,     0,
       0,   270,    27,     0,    28,     0,   231,   172,   229,   215,
     232,     0,     0,   101,   100,     0,   220,   211,     0,     0,
      67,     0,   321,   155,     0,   152,   287,   305,     0,   223,
      44,    46,     0,    76,    76,     0,     0,    58,    79,    48,
     231,     0,    34,     0,    36,    32,     0,   276,     0,     0,
     314,   289,   308,     0,   288,     0,     0,     0,   304,   316,
     297,   227,   298,     0,     0,    29,    30,     0,   102,    99,
     221,     0,   213,   104,     0,   322,     0,     0,     0,     0,
       0,     0,    76,     0,    35,     0,     0,     0,     0,   283,
     310,   282,   294,   295,   296,   318,   302,    23,   169,   230,
     292,   291,   323,     0,   290,    45,    47,    76,     0,     0,
      56,    37,     0,   315,   278,   279,     0,   284,     0,    53,
       0,    38,   317,     0,    52,    51
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -385,  -385,    19,     5,    -3,  -385,   411,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,   -22,
      -2,     8,    14,   -46,  -170,  -385,  -250,   181,   172,   173,
     197,   170,   177,   -70,  -127,   -75,   -74,   -90,   163,   -32,
      23,  -192,    -6,  -132,  -283,  -188,  -187,  -385,  -185,  -181,
     -96,  -100,  -385,  -385,    55,  -385,  -385,   406,  -112,  -385,
       1,   117,  -385,  -385,     0,   365,  -385,  -385,  -385,  -385,
      91,   330,  -125,  -385,   -15,  -333,   -78,  -385,  -384,  -385,
     -51,  -209
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    56,   205,    58,    59,    60,   166,    61,   359,    62,
      63,    64,    65,    66,    67,    68,    69,    70,   319,   486,
      71,    72,    73,    74,    75,    76,   155,    77,    78,   148,
     120,    79,   437,   422,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,   308,    97,    98,   259,    99,   100,   221,   101,   404,
     217,   312,   150,   206,   207,   208,   102,   160,   164,   103,
     136,   137,   104,   105,   130,   310,   107,   108,   109,   110,
     512,   378,   369,   370,   371,   474,   567,   616,   466,   467,
     468,   399
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     106,   213,   151,   117,   106,   414,   122,   133,   368,   114,
     368,   396,   397,   313,   398,   317,   138,   373,   129,    57,
     223,   413,   225,   325,   471,   531,   396,   397,   497,   398,
     439,   149,   149,   152,   279,   118,   416,   118,   118,   362,
     118,   161,   395,   134,   360,   106,   219,   363,   388,   472,
     361,   364,   128,   158,   159,   212,   216,   106,   139,    48,
     135,   141,   261,   288,   289,   290,    50,   286,   287,   209,
     475,   279,   262,   140,   222,   295,   142,   278,   477,   293,
     294,   478,   303,   304,   280,   476,   368,   303,   304,   296,
     303,   304,   111,   417,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   119,   473,
     121,   119,   419,   121,   162,   541,   106,   321,   131,   323,
     311,   311,  -242,   311,  -243,   418,   562,   291,   292,   534,
     112,   311,   409,   410,   411,   563,   412,   305,   631,   306,
     409,   307,   411,   216,   412,   113,   380,   632,   367,   382,
     383,   115,   127,   365,   387,   116,    43,   364,   213,   116,
     218,   447,   448,   449,   450,   451,   301,   302,   106,   570,
     151,   117,   106,   394,   123,   133,   122,   114,   495,   384,
     163,   498,   483,   385,   138,   423,   477,   127,   129,   553,
     423,    43,   477,   364,   477,   479,   143,   490,   477,   149,
     149,   558,   132,   477,   144,   106,   599,   456,   457,   458,
     261,   145,   212,   297,   298,   299,   445,   446,   452,   453,
     487,   454,   455,   146,   153,   154,   156,   157,   165,   216,
     413,   636,   168,   606,   368,   501,   260,   539,   220,   118,
     368,   500,   368,   368,   368,   368,   263,   505,   281,   507,
     508,   509,   510,   542,   282,   283,   285,   284,   300,   465,
     309,   314,   318,   320,   322,   324,   140,   142,   162,   460,
     461,   358,   366,   413,   396,   397,   372,   398,   421,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   593,   374,   375,   482,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,    13,   376,
     377,   381,   390,   464,   469,   389,   481,   391,   392,   393,
    -249,  -259,   485,   403,   149,  -260,   590,   420,   311,   492,
     406,  -261,   355,   400,  -264,   405,   415,   480,   529,   488,
     484,    32,   545,   489,   368,   491,   493,   396,   397,   494,
     398,   548,   476,    33,    34,    35,   126,   502,   503,   504,
     506,   511,   513,   465,    37,   516,   517,   127,   519,    41,
      42,    43,   368,    44,   496,   520,   537,   128,   521,   527,
     552,   538,    47,   547,    48,   622,   543,   554,   544,   515,
     556,    50,   106,   106,   546,    53,   561,   564,    55,   566,
     106,   568,   565,   569,   583,   394,   396,   397,   526,   398,
     573,   523,   525,   530,   575,   368,   576,   464,   577,   532,
     118,   621,   596,   536,   578,   584,   587,   588,   591,   592,
     597,   598,   602,   603,   604,   605,   607,   423,   423,   615,
     608,   618,   617,   279,   540,   623,   628,   626,   627,   641,
     167,   633,   640,   440,   443,   441,   642,   643,   528,   224,
     438,   555,   444,   459,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   518,   106,   106,
     442,   499,   557,   550,   551,   549,   386,   559,   311,   572,
     118,   149,   610,   595,     0,   357,     0,     0,   465,   560,
     571,   277,   -78,   574,     0,   579,     0,     0,     0,   580,
       0,     0,     0,     0,     0,   582,     0,     0,     0,     0,
       0,     0,     0,   106,   278,   106,     0,     0,   261,     0,
     261,   600,   601,     0,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,     0,     0,     0,
       0,     0,   464,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   149,     0,     0,     0,   609,     0,     0,   465,
     611,   277,   612,   613,   614,     0,     0,     0,     0,     0,
     629,     0,     0,     0,     0,     0,     0,     0,   620,     0,
       0,     0,     0,     0,   624,   619,     0,     0,   106,     0,
     630,     0,     0,   625,     0,   638,     0,     0,     0,     0,
     149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     637,   634,   635,   464,     0,     0,     0,     0,   106,     0,
       0,     0,     0,   639,     0,   149,     0,     0,     0,     0,
     106,     0,     0,   106,     0,   644,    -2,     1,   645,     0,
       2,     0,     3,     4,     5,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,     0,     0,     0,     0,     0,    30,    31,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,    36,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,    41,    42,    43,     0,    44,
       0,     0,   -74,    45,     0,    46,     0,     0,    47,     0,
      48,     0,     0,     0,     0,     0,    49,    50,     0,    51,
      52,    53,     1,    54,    55,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,    11,    12,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,    25,   193,    27,    28,    29,     0,     0,     0,     0,
       0,     0,     0,    30,    31,     0,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   194,   195,   196,   197,   198,     0,
       0,     0,     0,     0,   199,    37,    38,    39,   200,     0,
      41,    42,   201,   202,    44,     0,     0,   -74,    45,   203,
      46,     0,     0,   204,     0,    48,     0,     0,     0,     0,
       0,    49,    50,     0,    51,    52,    53,     1,    54,    55,
       2,     0,     3,     4,     5,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,     0,     0,     0,     0,     0,    30,    31,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,    36,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,    41,    42,    43,     0,    44,
       0,     0,   -74,    45,   203,    46,     0,     0,    47,     0,
      48,     0,     0,     0,     0,     0,    49,    50,     0,    51,
      52,    53,     1,    54,    55,     2,     0,     3,     4,     5,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     0,     0,     0,     0,
       0,     0,     0,    30,    31,     0,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,    34,    35,    36,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,     0,
      41,    42,    43,     0,    44,     0,     0,   -74,    45,     0,
      46,     0,  -237,    47,     0,    48,     0,     0,     0,     0,
       0,    49,    50,     0,    51,    52,    53,     1,    54,    55,
       2,     0,     3,     4,     5,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,     0,     0,     0,     0,     0,    30,    31,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,    36,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,    41,    42,    43,     0,    44,
       0,     0,   -74,    45,   402,    46,     0,     0,    47,     0,
      48,     0,     0,     0,     0,     0,    49,    50,     0,    51,
      52,    53,     1,    54,    55,     2,     0,     3,     4,     5,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     0,     0,     0,     0,
       0,     0,     0,    30,    31,     0,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,    34,    35,    36,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,     0,
      41,    42,    43,     0,    44,     0,     0,   -74,    45,   522,
      46,     0,     0,    47,     0,    48,     0,     0,     0,     0,
       0,    49,    50,     0,    51,    52,    53,     1,    54,    55,
       2,     0,     3,     4,     5,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,     0,     0,     0,     0,     0,    30,    31,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,    36,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,    41,    42,    43,     0,    44,
       0,     0,   -74,    45,   524,    46,     0,     0,    47,     0,
      48,     0,     0,     0,     0,     0,    49,    50,     0,    51,
      52,    53,     1,    54,    55,     2,     0,     3,     4,     5,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     0,     0,     0,     0,
       0,     0,     0,    30,    31,     0,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,    34,    35,    36,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,     0,
      41,    42,    43,     0,    44,     0,     0,   -74,    45,   585,
      46,     0,     0,    47,     0,    48,     0,     0,     0,     0,
       0,    49,    50,     0,    51,    52,    53,     1,    54,    55,
       2,     0,     3,     4,     5,     6,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,     0,     0,     0,     0,     0,    30,    31,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,    36,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,    41,    42,    43,     0,    44,
       0,     0,   -74,    45,   586,    46,     0,     0,    47,     0,
      48,     0,     0,     0,     0,     0,    49,    50,     0,    51,
      52,    53,     1,    54,    55,     2,     0,     3,     4,     5,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     0,     0,     0,     0,
       0,     0,     0,    30,    31,     0,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,    34,    35,    36,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,     0,
      41,    42,    43,     0,    44,     0,     0,   -74,    45,     0,
      46,     0,     0,    47,    13,    48,     0,    16,   124,   125,
       0,    49,    50,     0,    51,    52,    53,     0,    54,    55,
       0,     0,     0,     0,     0,     0,     0,     0,    30,    31,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,   126,     0,     0,     0,     0,     0,     0,   214,
      37,     0,     0,   127,     0,    41,    42,    43,     0,    44,
       0,     0,     0,   128,     0,    46,     0,     0,    47,     0,
      48,   215,     0,     0,     0,     0,    49,    50,     0,    51,
      52,    53,     0,    54,    55,    13,   315,     0,    16,   124,
     125,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,     0,     0,     0,     0,     0,    30,
      31,     0,     0,     0,     0,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   355,     0,
      33,    34,    35,   126,     0,     0,     0,     0,   589,     0,
       0,    37,     0,     0,   127,     0,    41,    42,    43,     0,
      44,     0,     0,   316,   128,     0,    46,     0,     0,    47,
      13,    48,     0,    16,   124,   125,     0,    49,    50,     0,
      51,    52,    53,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    31,     0,     0,     0,     0,
       0,     0,     0,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,    34,    35,   126,     0,
       0,     0,     0,     0,     0,   462,    37,     0,     0,   127,
     463,    41,    42,    43,     0,    44,     0,     0,     0,   211,
       0,    46,     0,     0,    47,    13,    48,     0,    16,   124,
     125,     0,    49,    50,     0,    51,    52,    53,     0,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,     0,     0,     0,     0,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      33,    34,    35,   126,     0,     0,     0,     0,     0,     0,
     594,    37,     0,     0,   127,   463,    41,    42,    43,     0,
      44,     0,     0,     0,   211,     0,    46,     0,     0,    47,
      13,    48,     0,    16,   124,   125,     0,    49,    50,     0,
      51,    52,    53,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    31,     0,     0,     0,     0,
       0,     0,     0,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,    34,    35,   126,     0,
       0,     0,     0,     0,     0,     0,    37,     0,     0,   127,
     210,    41,    42,    43,     0,    44,     0,     0,     0,   211,
       0,    46,     0,     0,    47,    13,    48,     0,    16,   124,
     125,     0,    49,    50,     0,    51,    52,    53,     0,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,     0,     0,     0,     0,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      33,    34,    35,   126,     0,     0,     0,     0,     0,     0,
     214,    37,     0,     0,   127,     0,    41,    42,    43,     0,
      44,     0,     0,     0,   128,     0,    46,     0,     0,    47,
      13,    48,     0,    16,   124,   125,     0,    49,    50,     0,
      51,    52,    53,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    31,     0,     0,     0,     0,
       0,     0,     0,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,    34,    35,   126,     0,
       0,     0,     0,     0,     0,     0,    37,     0,     0,   127,
       0,    41,    42,    43,     0,    44,     0,     0,     0,   147,
       0,    46,     0,  -257,    47,    13,    48,     0,    16,   124,
     125,     0,    49,    50,     0,    51,    52,    53,     0,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,     0,     0,     0,     0,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      33,    34,    35,   126,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,   127,     0,    41,    42,    43,     0,
      44,     0,     0,     0,   147,     0,    46,     0,  -258,    47,
      13,    48,     0,    16,   124,   125,     0,    49,    50,     0,
      51,    52,    53,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    31,     0,     0,     0,     0,
       0,     0,     0,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,    34,    35,   126,     0,
       0,     0,     0,     0,     0,     0,    37,     0,     0,   127,
     401,    41,    42,    43,     0,    44,     0,     0,     0,   211,
       0,    46,     0,     0,    47,     0,    48,     0,     0,     0,
       0,     0,    49,    50,     0,    51,    52,    53,    13,    54,
      55,    16,   124,   125,     0,     0,     0,     0,     0,     0,
     436,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    31,     0,     0,     0,     0,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,    34,    35,   126,     0,     0,     0,
       0,     0,     0,     0,    37,     0,     0,   127,     0,    41,
      42,    43,     0,    44,     0,     0,     0,   211,     0,    46,
       0,     0,    47,    13,    48,     0,    16,   124,   125,     0,
      49,    50,     0,    51,    52,    53,     0,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,     0,
       0,     0,     0,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    34,
      35,   126,     0,     0,     0,     0,     0,     0,   535,    37,
       0,     0,   127,     0,    41,    42,    43,     0,    44,     0,
       0,     0,   128,     0,    46,     0,     0,    47,    13,    48,
       0,    16,   124,   125,     0,    49,    50,     0,    51,    52,
      53,     0,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    31,     0,     0,     0,     0,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,    34,    35,   126,     0,     0,     0,
       0,     0,     0,     0,    37,     0,     0,   127,     0,    41,
      42,    43,     0,    44,     0,     0,     0,   128,     0,    46,
       0,     0,    47,    13,    48,     0,    16,   124,   125,     0,
      49,    50,     0,    51,    52,    53,     0,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,     0,
       0,     0,     0,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    34,
      35,   126,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,   127,     0,    41,    42,    43,     0,    44,     0,
       0,     0,   147,     0,    46,     0,     0,    47,    13,    48,
       0,    16,   124,   125,     0,    49,    50,     0,    51,    52,
      53,     0,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    31,     0,     0,     0,     0,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,    34,    35,   126,     0,     0,     0,
       0,     0,     0,     0,    37,     0,     0,   127,     0,    41,
      42,    43,     0,    44,     0,     0,     0,   211,     0,    46,
       0,     0,    47,    13,    48,     0,    16,   124,   125,     0,
      49,    50,     0,    51,    52,    53,     0,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,     0,
       0,     0,     0,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    34,
      35,   126,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,   127,     0,    41,    42,    43,     0,    44,     0,
       0,     0,   514,     0,    46,     0,     0,    47,    13,    48,
       0,    16,   124,   125,     0,    49,    50,     0,    51,    52,
      53,     0,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    31,     0,     0,     0,     0,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,    34,    35,   126,     0,     0,     0,
       0,     0,     0,    13,    37,     0,     0,   127,     0,    41,
      42,    43,     0,    44,     0,     0,     0,    45,     0,    46,
       0,     0,    47,     0,    48,     0,     0,    30,    31,     0,
      49,    50,     0,    51,    52,    53,    32,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    34,
      35,   126,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,   127,     0,    41,    42,    43,     0,    44,     0,
       0,     0,   128,     0,    46,     0,     0,    47,     0,    48,
       0,     0,     0,     0,     0,     0,    50,     0,    51,    52,
      53,     0,    54,    55,   326,   170,   327,   328,   329,   330,
     175,   176,   331,   332,   333,   334,     0,     0,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
       0,   347,     0,     0,   326,   170,   327,   328,   329,   330,
     175,   176,   331,   332,   333,   334,     0,     0,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
       0,   347,     0,   348,   349,   350,   351,   198,     0,     0,
       0,     0,     0,   199,     0,     0,     0,   352,     0,     0,
       0,   353,   202,     0,     0,     0,     0,     0,   379,     0,
       0,     0,   354,   348,   349,   350,   351,   198,     0,     0,
       0,     0,     0,   199,     0,     0,     0,   352,     0,     0,
       0,   353,   202,     0,     0,     0,     0,     0,   407,     0,
       0,     0,   354,   326,   170,   327,   328,   329,   330,   175,
     176,   331,   332,   333,   334,     0,     0,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,     0,
     347,     0,     0,   326,   170,   327,   328,   329,   330,   175,
     176,   331,   332,   333,   334,     0,     0,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,     0,
     347,     0,   348,   349,   350,   351,   198,     0,     0,     0,
       0,     0,   199,     0,     0,     0,   352,     0,     0,     0,
     353,   202,     0,     0,     0,     0,     0,   581,     0,     0,
       0,   354,   348,   349,   350,   351,   198,     0,     0,     0,
       0,     0,   199,     0,     0,     0,   352,     0,     0,     0,
     353,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   354,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,     0,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,     0,   251,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,     0,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,     0,   251,     0,     0,
       0,   252,   253,   254,   255,   256,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   257,     0,     0,     0,     0,
     258,     0,     0,     0,     0,     0,     0,     0,     0,   252,
     253,   254,   255,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   257,     0,     0,     0,     0,   470,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,     0,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,     0,   251,     0,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,     0,     0,     0,     0,   252,   253,
     254,   255,   256,     0,     0,   355,     0,     0,     0,     0,
       0,     0,   257,   408,     0,     0,     0,   533,   355,     0,
       0,     0,     0,     0,   356,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   355
};

static const yytype_int16 yycheck[] =
{
       0,    47,    24,     6,     4,   214,     8,    13,   140,     4,
     142,   199,   199,   113,   199,   115,    15,   142,    10,     0,
      52,   213,    54,   123,   307,   409,   214,   214,   361,   214,
     280,    23,    24,    25,    47,     4,   217,     4,     4,   135,
       4,    19,    77,    77,    85,    45,    49,    86,   160,    21,
      91,    90,    87,    30,    31,    47,    48,    57,    77,    94,
      94,    77,    57,    37,    38,    39,   101,    35,    36,    46,
      77,    47,    74,    92,    51,    89,    92,    79,    90,    44,
      45,    93,    42,    43,    97,    92,   218,    42,    43,   103,
      42,    43,    86,   218,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,    77,    81,
      77,    77,   224,    77,    92,    91,   116,   119,    91,   121,
     112,   113,    91,   115,    91,   221,    80,   101,   102,   412,
      92,   123,    92,    93,    94,    89,    96,    92,    80,    94,
      92,    96,    94,   135,    96,    92,   148,    89,    73,   151,
     153,    92,    77,    86,   157,    87,    81,    90,   204,    87,
      92,   288,   289,   290,   291,   292,    61,    62,   168,   502,
     192,   174,   172,   168,    92,   181,   178,   172,   359,    86,
      92,   362,    86,    90,   183,   355,    90,    77,   180,    86,
     360,    81,    90,    90,    90,    93,    77,    93,    90,   191,
     192,    93,    87,    90,    77,   205,    93,   297,   298,   299,
     205,    77,   204,   104,   105,   106,   286,   287,   293,   294,
     320,   295,   296,    77,    77,    77,    77,    77,    77,   221,
     422,   615,    91,   566,   366,   367,     0,   418,   102,     4,
     372,   366,   374,   375,   376,   377,    86,   372,    40,   374,
     375,   376,   377,   462,    41,    98,   100,    99,    46,   305,
     101,     6,    10,    92,    86,    86,    92,    92,    92,   301,
     302,    77,    92,   465,   462,   462,    92,   462,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   541,    92,    92,   316,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    18,    92,
      92,    90,    92,   305,   306,    77,   315,    78,    87,    87,
      91,    91,    11,    90,   316,    91,   535,    86,   320,    78,
      93,    91,    85,    91,    91,    91,    90,    92,    88,    86,
      92,    51,    95,    86,   476,    91,    85,   535,   535,    90,
     535,   476,    92,    63,    64,    65,    66,    91,    93,    90,
      93,    91,    86,   409,    74,    86,    77,    77,    85,    79,
      80,    81,   504,    83,   360,    78,    95,    87,    93,    93,
     480,    93,    92,    92,    94,   594,    93,    86,    90,   381,
      77,   101,   392,   393,   102,   105,    93,    77,   108,    92,
     400,    95,    88,    93,    78,   400,   594,   594,   400,   594,
      93,   392,   393,   405,    93,   547,    93,   409,    93,   411,
       4,   591,   547,   415,    93,    93,    91,    93,    68,    72,
      93,     5,    86,    93,    80,    85,    85,   607,   608,    92,
      85,    93,    86,    47,   436,    93,    93,    86,    86,    80,
      39,    93,    93,   281,   284,   282,    93,    93,   403,    53,
     279,   483,   285,   300,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,   386,   478,   479,
     283,   364,   485,   478,   479,   477,   156,   490,   480,   504,
       4,   483,   570,   544,    -1,   130,    -1,    -1,   544,   491,
     503,    85,    86,   506,    -1,   511,    -1,    -1,    -1,   512,
      -1,    -1,    -1,    -1,    -1,   518,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   523,   526,   525,    -1,    -1,   523,    -1,
     525,   553,   554,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,   544,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   553,   554,    -1,    -1,    -1,   569,    -1,    -1,   615,
     573,    85,   575,   576,   577,    -1,    -1,    -1,    -1,    -1,
     602,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   591,    -1,
      -1,    -1,    -1,    -1,   597,   587,    -1,    -1,   598,    -1,
     603,    -1,    -1,   598,    -1,   627,    -1,    -1,    -1,    -1,
     602,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     623,   607,   608,   615,    -1,    -1,    -1,    -1,   628,    -1,
      -1,    -1,    -1,   628,    -1,   627,    -1,    -1,    -1,    -1,
     640,    -1,    -1,   643,    -1,   640,     0,     1,   643,    -1,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    86,    87,    -1,    89,    -1,    -1,    92,    -1,
      94,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,   103,
     104,   105,     1,   107,   108,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,    -1,
      79,    80,    81,    82,    83,    -1,    -1,    86,    87,    88,
      89,    -1,    -1,    92,    -1,    94,    -1,    -1,    -1,    -1,
      -1,   100,   101,    -1,   103,   104,   105,     1,   107,   108,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,    -1,
      94,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,   103,
     104,   105,     1,   107,   108,     4,    -1,     6,     7,     8,
       9,    -1,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    -1,
      79,    80,    81,    -1,    83,    -1,    -1,    86,    87,    -1,
      89,    -1,    91,    92,    -1,    94,    -1,    -1,    -1,    -1,
      -1,   100,   101,    -1,   103,   104,   105,     1,   107,   108,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,    -1,
      94,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,   103,
     104,   105,     1,   107,   108,     4,    -1,     6,     7,     8,
       9,    -1,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    -1,
      79,    80,    81,    -1,    83,    -1,    -1,    86,    87,    88,
      89,    -1,    -1,    92,    -1,    94,    -1,    -1,    -1,    -1,
      -1,   100,   101,    -1,   103,   104,   105,     1,   107,   108,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,    -1,
      94,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,   103,
     104,   105,     1,   107,   108,     4,    -1,     6,     7,     8,
       9,    -1,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    -1,
      79,    80,    81,    -1,    83,    -1,    -1,    86,    87,    88,
      89,    -1,    -1,    92,    -1,    94,    -1,    -1,    -1,    -1,
      -1,   100,   101,    -1,   103,   104,   105,     1,   107,   108,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,    -1,
      94,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,   103,
     104,   105,     1,   107,   108,     4,    -1,     6,     7,     8,
       9,    -1,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    -1,
      79,    80,    81,    -1,    83,    -1,    -1,    86,    87,    -1,
      89,    -1,    -1,    92,    18,    94,    -1,    21,    22,    23,
      -1,   100,   101,    -1,   103,   104,   105,    -1,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    -1,    -1,    77,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    -1,    87,    -1,    89,    -1,    -1,    92,    -1,
      94,    95,    -1,    -1,    -1,    -1,   100,   101,    -1,   103,
     104,   105,    -1,   107,   108,    18,    19,    -1,    21,    22,
      23,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    95,    -1,
      -1,    74,    -1,    -1,    77,    -1,    79,    80,    81,    -1,
      83,    -1,    -1,    86,    87,    -1,    89,    -1,    -1,    92,
      18,    94,    -1,    21,    22,    23,    -1,   100,   101,    -1,
     103,   104,   105,    -1,   107,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    77,
      78,    79,    80,    81,    -1,    83,    -1,    -1,    -1,    87,
      -1,    89,    -1,    -1,    92,    18,    94,    -1,    21,    22,
      23,    -1,   100,   101,    -1,   103,   104,   105,    -1,   107,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    -1,    -1,    77,    78,    79,    80,    81,    -1,
      83,    -1,    -1,    -1,    87,    -1,    89,    -1,    -1,    92,
      18,    94,    -1,    21,    22,    23,    -1,   100,   101,    -1,
     103,   104,   105,    -1,   107,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    77,
      78,    79,    80,    81,    -1,    83,    -1,    -1,    -1,    87,
      -1,    89,    -1,    -1,    92,    18,    94,    -1,    21,    22,
      23,    -1,   100,   101,    -1,   103,   104,   105,    -1,   107,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    -1,    -1,    77,    -1,    79,    80,    81,    -1,
      83,    -1,    -1,    -1,    87,    -1,    89,    -1,    -1,    92,
      18,    94,    -1,    21,    22,    23,    -1,   100,   101,    -1,
     103,   104,   105,    -1,   107,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    77,
      -1,    79,    80,    81,    -1,    83,    -1,    -1,    -1,    87,
      -1,    89,    -1,    91,    92,    18,    94,    -1,    21,    22,
      23,    -1,   100,   101,    -1,   103,   104,   105,    -1,   107,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    77,    -1,    79,    80,    81,    -1,
      83,    -1,    -1,    -1,    87,    -1,    89,    -1,    91,    92,
      18,    94,    -1,    21,    22,    23,    -1,   100,   101,    -1,
     103,   104,   105,    -1,   107,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    77,
      78,    79,    80,    81,    -1,    83,    -1,    -1,    -1,    87,
      -1,    89,    -1,    -1,    92,    -1,    94,    -1,    -1,    -1,
      -1,    -1,   100,   101,    -1,   103,   104,   105,    18,   107,
     108,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    79,
      80,    81,    -1,    83,    -1,    -1,    -1,    87,    -1,    89,
      -1,    -1,    92,    18,    94,    -1,    21,    22,    23,    -1,
     100,   101,    -1,   103,   104,   105,    -1,   107,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      -1,    -1,    77,    -1,    79,    80,    81,    -1,    83,    -1,
      -1,    -1,    87,    -1,    89,    -1,    -1,    92,    18,    94,
      -1,    21,    22,    23,    -1,   100,   101,    -1,   103,   104,
     105,    -1,   107,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    79,
      80,    81,    -1,    83,    -1,    -1,    -1,    87,    -1,    89,
      -1,    -1,    92,    18,    94,    -1,    21,    22,    23,    -1,
     100,   101,    -1,   103,   104,   105,    -1,   107,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    -1,    77,    -1,    79,    80,    81,    -1,    83,    -1,
      -1,    -1,    87,    -1,    89,    -1,    -1,    92,    18,    94,
      -1,    21,    22,    23,    -1,   100,   101,    -1,   103,   104,
     105,    -1,   107,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    79,
      80,    81,    -1,    83,    -1,    -1,    -1,    87,    -1,    89,
      -1,    -1,    92,    18,    94,    -1,    21,    22,    23,    -1,
     100,   101,    -1,   103,   104,   105,    -1,   107,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    -1,    77,    -1,    79,    80,    81,    -1,    83,    -1,
      -1,    -1,    87,    -1,    89,    -1,    -1,    92,    18,    94,
      -1,    21,    22,    23,    -1,   100,   101,    -1,   103,   104,
     105,    -1,   107,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    74,    -1,    -1,    77,    -1,    79,
      80,    81,    -1,    83,    -1,    -1,    -1,    87,    -1,    89,
      -1,    -1,    92,    -1,    94,    -1,    -1,    42,    43,    -1,
     100,   101,    -1,   103,   104,   105,    51,   107,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    -1,    77,    -1,    79,    80,    81,    -1,    83,    -1,
      -1,    -1,    87,    -1,    89,    -1,    -1,    92,    -1,    94,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,   103,   104,
     105,    -1,   107,   108,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    -1,    -1,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    -1,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      31,    -1,    -1,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      31,    -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    92,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    92,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    31,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    31,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    82,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    31,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    93,    -1,    -1,    -1,    82,    85,    -1,
      -1,    -1,    -1,    -1,    91,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     6,     7,     8,     9,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      42,    43,    51,    63,    64,    65,    66,    74,    75,    76,
      77,    79,    80,    81,    83,    87,    89,    92,    94,   100,
     101,   103,   104,   105,   107,   108,   110,   111,   112,   113,
     114,   116,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   129,   130,   131,   132,   133,   134,   136,   137,   140,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   161,   162,   164,
     165,   167,   175,   178,   181,   182,   183,   185,   186,   187,
     188,    86,    92,    92,   112,    92,    87,   113,     4,    77,
     139,    77,   139,    92,    22,    23,    66,    77,    87,   140,
     183,    91,    87,   161,    77,    94,   179,   180,   179,    77,
      92,    77,    92,    77,    77,    77,    77,    87,   138,   140,
     171,   138,   140,    77,    77,   135,    77,    77,   159,   159,
     176,    19,    92,    92,   177,    77,   115,   115,    91,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    31,    63,    64,    65,    66,    67,    73,
      77,    81,    82,    88,    92,   111,   172,   173,   174,   159,
      78,    87,   140,   142,    73,    95,   140,   169,    92,   113,
     102,   166,   159,   158,   176,   158,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    31,    63,    64,    65,    66,    67,    77,    82,   163,
       0,   112,   139,    86,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    85,   139,    47,
      97,    40,    41,    98,    99,   100,    35,    36,    37,    38,
      39,   101,   102,    44,    45,    89,   103,   104,   105,   106,
      46,    61,    62,    42,    43,    92,    94,    96,   160,   101,
     184,   140,   170,   170,     6,    19,    86,   170,    10,   127,
      92,   139,    86,   139,    86,   170,     4,     6,     7,     8,
       9,    12,    13,    14,    15,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    31,    63,    64,
      65,    66,    77,    81,    92,    85,    91,   184,    77,   117,
      85,    91,   169,    86,    90,    86,    92,    73,   162,   191,
     192,   193,    92,   191,    92,    92,    92,    92,   190,    88,
     139,    90,   139,   113,    86,    90,   190,   113,   177,    77,
      92,    78,    87,    87,   112,    77,   164,   165,   167,   200,
      91,    78,    88,    90,   168,    91,    93,    88,    93,    92,
      93,    94,    96,   160,   200,    90,   168,   191,   169,   177,
      86,   141,   142,   143,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,    30,   141,   146,   145,
     147,   148,   149,   150,   151,   152,   152,   153,   153,   153,
     153,   153,   154,   154,   155,   155,   156,   156,   156,   157,
     158,   158,    73,    78,   140,   142,   197,   198,   199,   140,
      82,   163,    21,    81,   194,    77,    92,    90,    93,    93,
      92,   179,   138,    86,    92,    11,   128,   170,    86,    86,
      93,    91,    78,    85,    90,   168,   141,   194,   168,   180,
     191,   162,    91,    93,    90,   191,    93,   191,   191,   191,
     191,    91,   189,    86,    87,   140,    86,    77,   189,    85,
      78,    93,    88,   111,    88,   111,   140,    93,   173,    88,
     140,   197,   140,    82,   163,    73,   140,    95,    93,   168,
     140,    91,   200,    93,    90,    95,   102,    92,   191,   140,
     112,   112,   170,    86,    86,   138,    77,   113,    93,   113,
     140,    93,    80,    89,    77,    88,    92,   195,    95,    93,
     194,   113,   193,    93,   113,    93,    93,    93,    93,   161,
     113,    88,   113,    78,    93,    88,    88,    91,    93,    95,
     200,    68,    72,   145,    73,   199,   191,    93,     5,    93,
     138,   138,    86,    93,    80,    85,   194,    85,    85,   113,
     195,   113,   113,   113,   113,    92,   196,    86,    93,   140,
     113,   143,   200,    93,   113,   112,    86,    86,    93,   138,
     113,    80,    89,    93,   141,   141,   197,   113,   138,   112,
      93,    80,    93,    93,   112,   112
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   109,   110,   111,   111,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   113,   113,   114,   114,   114,
     114,   115,   116,   117,   117,   117,   117,   117,   117,   118,
     118,   118,   118,   119,   120,   120,   121,   122,   123,   124,
     124,   125,   125,   125,   126,   127,   127,   128,   128,   129,
     129,   129,   129,   130,   131,   132,   132,   132,   132,   133,
     134,   135,   135,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   141,   141,   142,   142,   142,
     142,   142,   142,   143,   143,   144,   144,   145,   145,   146,
     146,   147,   147,   148,   148,   149,   149,   150,   150,   151,
     151,   151,   152,   152,   152,   152,   152,   152,   153,   153,
     153,   154,   154,   154,   155,   155,   155,   155,   156,   156,
     157,   157,   157,   158,   158,   158,   158,   158,   158,   158,
     159,   159,   159,   159,   159,   159,   160,   160,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   162,   162,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     164,   164,   165,   165,   166,   167,   168,   168,   169,   169,
     169,   169,   170,   170,   171,   171,   171,   171,   172,   172,
     173,   173,   173,   173,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   175,   175,   175,   176,
     177,   178,   178,   179,   179,   180,   180,   180,   180,   180,
     181,   181,   182,   182,   182,   183,   184,   184,   185,   185,
     185,   185,   185,   185,   186,   186,   186,   187,   187,   188,
     188,   189,   189,   190,   190,   191,   191,   192,   192,   193,
     193,   193,   194,   194,   195,   195,   196,   196,   197,   197,
     198,   198,   198,   198,   199,   199,   199,   200,   200,   200,
     200
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     2,     2,     3,     4,     4,     5,
       5,     1,     5,     1,     3,     4,     3,     5,     6,     1,
       1,     1,     1,     3,     5,     7,     5,     7,     5,     3,
       2,    10,     9,     8,     4,     0,     5,     0,     2,     3,
       4,     3,     4,     4,     3,     2,     1,     4,     3,     4,
       3,     1,     3,     2,     0,     2,     0,     1,     0,     4,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     2,     2,     4,
       3,     3,     4,     1,     5,     1,     1,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     3,
       1,     3,     3,     1,     2,     2,     2,     2,     2,     2,
       1,     2,     4,     3,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     6,
       3,     3,     3,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     4,     2,     5,     0,     4,     0,     1,     1,     2,
       3,     4,     1,     3,     1,     2,     3,     4,     1,     3,
       5,     3,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     2,     0,
       3,     3,     3,     1,     3,     1,     4,     3,     6,     6,
       1,     1,     6,     6,     7,     1,     0,     3,     5,     5,
       6,     6,     6,     2,     6,     6,     6,     5,     5,     3,
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
#line 132 "src/kinx.y" /* yacc.c:1646  */
    { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[0].obj), kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
#line 2360 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 137 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2366 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 159 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2372 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 160 "src/kinx.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2378 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 164 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2384 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 165 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2390 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 169 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2396 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 170 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2402 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 171 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2408 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 172 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2414 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 176 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2420 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 180 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2426 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 184 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2432 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 185 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2438 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 186 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2444 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 187 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2450 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 188 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2456 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 189 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2462 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 200 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2468 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 204 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2474 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 205 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2480 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 209 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2486 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 213 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2492 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 217 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2498 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 221 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2504 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 222 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2510 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 227 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2521 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 234 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2532 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 241 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2543 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 250 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2549 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 254 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2555 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 255 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2561 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 259 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2567 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 260 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2573 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 264 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2579 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 265 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2585 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 266 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2591 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 267 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2597 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 271 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2603 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 275 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2609 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 279 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2615 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 280 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2621 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 281 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2627 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 282 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2633 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 286 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2639 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 290 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2645 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 294 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2651 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 295 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2657 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 299 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2663 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 303 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2669 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 304 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2675 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 308 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2681 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 313 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2687 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 314 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2693 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 319 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2699 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 320 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2705 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 321 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2711 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 322 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2717 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 323 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2723 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 324 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2729 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 325 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2735 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 326 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2741 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 327 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2747 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 328 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2753 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 329 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2759 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 330 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2765 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 331 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2771 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 332 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2777 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 341 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2783 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 342 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2789 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 343 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2795 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 344 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2801 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 345 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2807 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 346 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2813 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 351 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2819 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 361 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2825 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 366 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2831 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 371 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2837 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 376 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2843 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 381 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2849 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 386 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2855 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 391 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2861 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 392 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2867 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 397 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2873 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 398 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2879 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 399 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2885 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 400 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2891 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 401 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2897 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 406 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2903 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 407 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2909 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 412 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2915 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 413 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2921 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 418 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2927 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 419 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2933 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 420 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2939 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 425 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2945 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 430 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2951 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 431 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2957 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 436 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 2963 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 437 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 2969 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 438 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 2975 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 439 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_CONV, (yyvsp[0].obj)); }
#line 2981 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 440 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 2987 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 441 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 2993 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 446 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2999 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 447 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3005 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 448 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3011 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 449 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 3017 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 450 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 3023 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 454 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 3029 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 455 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 3035 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 459 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 3041 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 460 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3047 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 461 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3053 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 462 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3059 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 463 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3065 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 464 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3071 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 465 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3077 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 470 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3083 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 471 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3089 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 472 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3095 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 473 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3101 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 474 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3107 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 475 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3113 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 476 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3119 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 480 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3125 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 481 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3131 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 485 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3137 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3143 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3149 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 488 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3155 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 489 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3161 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 490 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3167 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 491 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3173 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 492 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3179 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 493 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3185 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 494 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3191 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3197 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3203 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3209 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3215 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 499 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3221 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 500 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3227 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 501 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3233 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 502 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3239 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3245 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 504 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3251 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 505 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3257 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 506 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3263 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 507 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3269 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3275 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3281 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 510 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3287 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 511 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3293 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 512 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3299 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 513 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3305 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3311 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 515 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3317 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 516 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3323 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3329 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 521 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3335 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 525 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3341 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 526 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3347 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 530 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3353 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 534 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3359 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3365 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 544 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3371 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3377 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 546 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3383 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 551 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3389 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 556 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3395 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 557 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3401 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 558 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3407 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 563 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3413 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 567 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3419 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 568 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3425 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 569 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3431 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 570 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3437 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 574 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3443 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 575 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3449 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 576 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3455 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 577 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3461 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 578 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3467 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 579 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3473 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 580 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3479 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 581 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3485 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 582 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3491 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 583 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3497 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 584 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3503 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 585 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3509 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 586 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3515 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 587 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3521 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 588 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3527 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 589 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3533 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 590 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3539 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 591 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3545 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 592 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3551 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 593 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3557 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 594 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3563 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 595 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3569 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 596 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3575 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 597 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3581 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 598 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3587 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 599 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3593 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 600 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3599 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 601 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3605 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 602 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3611 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 603 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3617 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 604 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3623 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 605 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3629 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3635 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 610 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 3641 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 611 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3647 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 615 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 3653 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 619 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 3659 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 623 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3665 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 624 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 3671 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 629 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3677 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 633 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 3683 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 634 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 3689 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 635 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3695 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 636 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 3701 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 637 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-4].obj)), (yyvsp[0].obj)); }
#line 3707 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3713 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 642 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3719 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 646 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3725 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 647 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3731 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 648 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3737 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 652 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 3743 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 3749 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3755 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 661 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3761 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 662 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3767 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 663 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3773 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 664 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 3779 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 665 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 3785 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 666 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 3791 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3797 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 671 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3803 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 672 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3809 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 676 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3815 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 677 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3821 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 681 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3827 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 682 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3833 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 686 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3839 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 688 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 3852 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 699 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3858 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 700 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3864 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 704 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3870 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 710 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3876 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 714 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3882 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 715 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 3888 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 716 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 3894 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 720 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 3900 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 721 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 3906 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 725 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 3912 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 726 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3918 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 730 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3924 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 731 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3930 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 735 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3936 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 741 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3942 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 742 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 3948 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 743 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 3954 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 749 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3960 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 753 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3966 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 754 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 3972 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 755 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 3978 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 756 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 3984 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 3988 "kx.tab.c" /* yacc.c:1646  */
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
#line 759 "src/kinx.y" /* yacc.c:1906  */


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
