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
#define YYFINAL  253
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3427

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  109
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  92
/* YYNRULES -- Number of rules.  */
#define YYNRULES  323
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  630

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
       2,     2,     2,   105,     2,     2,     2,   104,    98,     2,
      92,    93,   102,   101,    90,    89,    94,   103,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    91,    86,
      99,    85,   100,    95,   108,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   106,     2,   107,    97,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,    96,    88,     2,     2,     2,     2,
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
     156,   157,   158,   159,   163,   164,   168,   169,   170,   171,
     175,   179,   183,   184,   185,   186,   187,   188,   192,   193,
     194,   195,   199,   203,   204,   208,   212,   216,   220,   221,
     225,   232,   239,   249,   253,   254,   258,   259,   263,   264,
     265,   266,   270,   274,   278,   279,   280,   281,   285,   289,
     293,   294,   298,   302,   303,   307,   308,   312,   313,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   335,   336,   340,   341,   342,   346,
     347,   351,   352,   356,   357,   361,   362,   366,   367,   371,
     372,   376,   377,   381,   382,   386,   387,   388,   392,   393,
     394,   395,   396,   397,   401,   402,   403,   407,   408,   409,
     413,   414,   415,   416,   420,   421,   425,   426,   427,   431,
     432,   433,   434,   435,   436,   440,   441,   442,   443,   444,
     445,   449,   450,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     474,   475,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   514,   515,   519,   520,   524,   528,
     532,   533,   537,   538,   539,   540,   544,   545,   549,   550,
     551,   552,   556,   557,   561,   562,   563,   564,   568,   569,
     570,   571,   572,   573,   574,   575,   576,   577,   578,   579,
     580,   581,   582,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   598,   599,
     603,   604,   605,   609,   613,   617,   618,   622,   623,   627,
     628,   629,   630,   634,   635,   639,   640,   641,   645,   649,
     650,   654,   655,   656,   657,   658,   659,   663,   664,   665,
     669,   670,   674,   675,   679,   680,   692,   693,   697,   698,
     702,   703,   707,   708,   709,   713,   714,   718,   719,   723,
     724,   728,   729,   733,   734,   735,   736,   740,   741,   742,
     746,   747,   748,   749
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
  "'}'", "'-'", "','", "':'", "'('", "')'", "'.'", "'?'", "'|'", "'^'",
  "'&'", "'<'", "'>'", "'+'", "'*'", "'/'", "'%'", "'!'", "'['", "']'",
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
      44,    58,    40,    41,    46,    63,   124,    94,    38,    60,
      62,    43,    42,    47,    37,    33,    91,    93,    64
};
# endif

#define YYPACT_NINF -481

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-481)))

#define YYTABLE_NINF -259

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1556,   -65,   -45,  1556,   -26,    29,    44,    49,    32,  2420,
     -16,    46,   345,     3,     3,  -481,   -46,   -42,    65,    88,
     101,   125,  2492,  2492,  2420,   140,   142,   143,   145,   345,
     345,  -481,  -481,  -481,  -481,    35,    84,   146,   146,   147,
    -481,  -481,  -481,  -481,   629,   345,  1916,   -47,    91,   345,
    -481,  2759,  1628,  3132,   229,   732,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,   232,  -481,  -481,  -481,   157,   294,  -481,  -481,
     -22,   204,   219,   149,   164,   165,   114,    39,   150,   -30,
     109,   216,   138,  -481,    40,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,   168,  -481,  -481,  -481,  -481,  2420,
    2420,   262,  1700,   835,   259,   181,   232,   188,   232,   189,
    2420,   184,   185,   186,  -481,  3102,  3329,   168,  -481,   202,
    -481,   -27,    45,  -481,    55,   190,    67,   191,    67,   194,
     195,   196,   197,  2864,   232,  3342,   200,   232,  3342,    29,
    -481,    57,   197,    29,    40,    40,    84,   203,   201,   214,
    -481,  -481,   208,   209,  1556,   -65,  -481,   -45,   938,   -26,
      29,  -481,  -481,    37,    38,    32,  2420,   345,     3,     3,
     206,   -46,   -42,    65,    88,   101,   125,  1988,  2060,   140,
     211,   212,   213,    35,  -481,   -38,   215,   218,  -481,  -481,
    2132,  1041,   210,  -481,   220,    40,   221,  3282,    67,  -481,
    -481,  2204,    40,    84,  -481,   -38,  -481,  3342,   217,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,   226,  -481,  2564,  2564,  2564,
    2564,  2564,  2564,  2564,  2564,  2564,  2564,  2564,  2564,  2564,
    2276,  -481,  2759,  2759,  2759,  2759,  2759,  2759,  2759,  2759,
    2759,  2759,  2759,  2759,  2759,  2759,  2759,  2759,  2759,  2759,
    2759,  2759,  2759,  2759,  2759,  2759,  -481,  -481,  1772,  3211,
    2420,  -481,    36,   -25,  3342,    90,    94,   207,     3,  2492,
      81,   223,   270,  2420,   227,  -481,   231,  -481,    95,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,   230,  -481,   240,  2564,  -481,
     228,   237,   234,  2564,    36,  -481,     3,  -481,    67,   -12,
     235,   238,   242,  -481,    67,   244,    67,    67,    67,    67,
     236,  -481,   239,  2636,   247,  -481,  -481,   251,   236,  -481,
    -481,   245,   257,   246,  1144,  1247,  -481,  -481,  -481,  -481,
    -481,  -481,  1556,   264,  -481,  3102,   250,  2420,  -481,  -481,
     265,   217,  -481,  -481,  2348,   198,  -481,  2894,  -481,   263,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  2420,  -481,   204,   -21,   219,   149,   164,
     165,   114,    39,    39,   150,   150,   150,   150,   150,   -30,
     -30,   109,   109,   216,   216,   216,   138,  -481,  -481,   -38,
    -481,  2983,  3342,   266,   271,  -481,  -481,  -481,  3269,  -481,
    -481,   260,   272,    67,  2420,  1556,  1556,  2420,    89,   276,
    2492,   288,    29,  -481,    99,  -481,  -481,    29,  2420,   273,
     -51,   290,   280,  -481,   277,  -481,   278,  -481,    36,    29,
      67,   279,    29,   281,   283,   284,   285,   345,    29,  -481,
    3013,  3342,  -481,  -481,    29,   295,   287,  -481,  -481,  1350,
    -481,  1453,   199,   291,  -481,  -481,  3342,   313,   314,   -38,
    3342,  -481,   293,  1772,  3342,  2759,  -481,  -481,  -481,  1844,
    -481,  -481,    67,   296,  3342,   383,  -481,   100,  2492,  2492,
     308,   302,  -481,  -481,  -481,  3342,   291,  -481,   323,   319,
    -481,    36,   321,    29,   277,  -481,  -481,    29,  -481,    29,
      29,    29,  -481,   320,  -481,  -481,  -481,   327,   322,  -481,
    -481,  2420,  2708,  -481,  -481,  3239,   324,   369,   -38,  -481,
     325,    29,  1556,   335,   337,   334,  2492,    29,  -481,   -17,
     336,  2564,  -481,  -481,  -481,  -481,  -481,  -481,  1772,  -481,
    -481,  -481,  3342,  -481,  -481,  -481,  -481,  -481,    29,  -481,
    -481,  -481,  2492,  1556,   338,  -481,  -481,   350,  -481,  -481,
     342,  -481,   343,  -481,  1556,  -481,  -481,  1556,  -481,  -481
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      73,     0,     0,    73,     0,     0,    77,    77,     0,     0,
       0,     0,     0,     0,     0,   278,     0,     0,     0,     0,
       0,     0,    75,    75,    65,     0,     0,     0,     0,     0,
       0,   263,   156,   158,   159,     0,     0,     0,     0,   170,
     155,   153,   171,   154,    73,     0,     0,     0,   208,     0,
     263,     0,     0,     0,     0,     2,     3,     5,     6,     7,
      20,    22,     8,     9,    10,    11,    12,    13,    14,    21,
      15,    16,    77,    17,    18,    19,     0,    77,    79,    99,
     102,   103,   105,   107,   109,   111,   113,   115,   118,   124,
     127,   130,   134,   136,   139,   145,   157,   160,   161,   162,
     163,    38,    39,   273,   279,   101,   274,    40,    41,     0,
       0,     0,     0,    73,    54,     0,    77,     0,    77,     0,
       0,     0,     0,     0,   170,     0,     0,   279,    49,     0,
     167,   269,     0,   267,     0,     0,   298,     0,   298,     0,
       0,     0,   296,     0,    77,   218,    76,    77,    64,     0,
      70,     0,   296,     0,   143,   144,     0,     0,     0,     0,
     262,    30,     0,     0,    73,   228,   229,   230,    73,   232,
     233,   234,   235,    77,    77,   238,   239,   240,   241,   242,
     278,   245,   244,   246,   247,   248,   249,    75,    75,   250,
     156,   158,   159,   256,   257,     0,   170,   171,   259,    24,
       0,    73,   210,   222,     0,   142,     0,     0,   298,   286,
     206,     0,   141,     0,   140,     0,   204,   212,   210,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   191,   190,   192,   193,
     194,   195,   197,   198,   196,   199,   200,   201,   202,   203,
     172,   169,   168,     1,     4,     0,    72,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   151,   152,   311,     0,
       0,   146,     0,     0,   216,     0,     0,     0,     0,    75,
       0,     0,    56,     0,     0,    58,     0,    60,     0,   228,
     230,   231,   232,   233,   236,   237,   238,   239,   240,   241,
     242,   243,   245,   244,   246,   247,   248,   249,   251,   252,
     250,   253,   254,   255,   256,     0,   258,     0,     0,    48,
       0,    32,   210,     0,     0,   265,     0,   266,   298,     0,
     302,     0,   299,   300,   298,     0,   298,   298,   298,   298,
     294,   219,     0,     0,     0,   292,    69,     0,   294,   293,
     261,     0,     0,     0,    73,    73,    42,   320,   321,   322,
     323,   227,    73,     0,    25,   211,     0,     0,   166,   165,
       0,   210,   260,   213,   211,     0,    63,     0,    83,    95,
      94,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    81,    82,    67,    80,   104,     0,   106,   108,   110,
     112,   114,   116,   117,   120,   122,   123,   119,   121,   125,
     126,   129,   128,   131,   132,   133,   135,   137,   138,     0,
     318,     0,   317,     0,   312,   313,   149,   148,     0,   306,
     305,     0,     0,   298,     0,    73,    73,     0,     0,     0,
      75,     0,     0,    53,     0,    59,    61,     0,     0,     0,
       0,   211,     0,   271,   307,   268,     0,   304,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    62,
       0,   220,    68,    71,     0,     0,     0,   264,    26,    73,
      27,    73,   225,   166,   223,   209,   226,     0,     0,     0,
     214,   205,    96,   311,    66,     0,   314,   319,   150,     0,
     147,   280,   298,     0,   217,    43,    45,     0,    75,    75,
       0,     0,    57,    78,    47,   225,     0,    33,     0,    35,
      31,     0,   270,     0,   307,   282,   301,     0,   281,     0,
       0,     0,   297,   309,   290,   221,   291,     0,     0,    28,
      29,     0,     0,   207,   215,     0,     0,   100,     0,   315,
       0,     0,    73,     0,     0,     0,    75,     0,    34,     0,
       0,     0,   276,   303,   275,   287,   288,   289,   311,   295,
      23,   164,   224,   285,   284,    97,    98,   316,     0,   283,
      44,    46,    75,    73,     0,    55,    36,     0,   308,   272,
       0,   277,     0,    52,    73,    37,   310,    73,    51,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -481,  -481,     6,     5,     4,  -481,   400,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,   -18,
       7,    10,  -157,  -481,  -171,  -481,  -253,   167,   166,   170,
     171,   169,   163,   -75,  -122,   -78,   -74,   -64,   156,   -29,
     107,  -481,   -11,  -134,  -281,  -185,  -179,  -481,  -178,  -194,
     243,   -97,  -481,  -481,    47,  -481,  -481,   393,  -128,  -481,
      -7,   102,  -481,  -481,     0,   328,  -481,  -481,  -481,  -481,
      72,   304,  -127,  -481,   -33,  -333,   -95,  -481,  -480,  -481,
     -69,  -203
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    54,   201,    56,    57,    58,   162,    59,   352,    60,
      61,    62,    63,    64,    65,    66,    67,    68,   312,   473,
      69,    70,    71,    72,    73,    74,   151,    75,    76,   144,
     117,    77,   424,   409,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,   301,    95,    96,   252,    97,    98,   211,    99,   396,
     218,   305,   146,   202,   203,   204,   100,   156,   160,   101,
     132,   133,   102,   103,   127,   303,   105,   106,   107,   108,
     498,   370,   361,   362,   363,   461,   552,   599,   453,   454,
     455,   391
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     104,   130,   360,   104,   360,   147,    55,   134,   111,   114,
     388,   365,   403,   306,   119,   310,   389,   390,   457,   126,
     426,   484,   214,   318,   405,   272,   272,   109,   380,   547,
     388,   135,   145,   145,   148,   137,   389,   390,   548,   387,
     113,   115,   115,   576,   104,   208,   136,   110,   115,   125,
     138,   209,   462,   115,   157,   104,   207,   459,   353,   288,
     254,    48,   217,   616,   354,   124,   112,   463,    52,    42,
     525,   289,   617,   273,   360,   128,   281,   282,   283,   255,
     131,   400,   296,   297,   271,   402,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     408,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   104,   116,   118,   113,   460,   620,   304,
     304,   116,   304,   314,   120,   316,   118,   158,  -236,  -237,
     304,   355,   298,   129,   299,   356,   154,   155,   284,   285,
     359,   357,   139,   376,   124,   356,   300,   377,    42,   279,
     280,   372,   205,   375,   374,   554,   212,   379,   482,   434,
     435,   436,   437,   438,   104,   140,   130,   470,   104,   386,
     147,   464,   134,   111,   114,   538,   159,   410,   141,   356,
     464,   119,   410,   465,   464,   464,   126,   466,   477,   464,
     464,   210,   543,   583,   286,   287,   483,   145,   145,   294,
     295,   104,   142,   115,   432,   433,   254,   518,   439,   440,
     207,   290,   291,   292,   441,   442,   474,   149,   590,   150,
     152,   217,   153,   161,   360,   487,   443,   444,   445,   253,
     360,   486,   360,   360,   360,   360,   115,   491,   164,   493,
     494,   495,   496,   256,   274,   276,   526,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     275,   277,   293,   278,   388,   447,   448,   302,   307,   311,
     389,   390,   577,   313,   315,   317,   136,   138,   158,   351,
     381,   472,   358,   364,   270,   -77,   366,   367,   368,   369,
     373,   469,   383,   382,   605,   384,   385,  -243,   115,   467,
     395,   468,  -253,  -254,  -255,   521,   392,   404,   452,  -258,
     458,   397,   406,   475,   398,   471,   574,   476,   479,   145,
     463,   478,   480,   304,   481,   499,   488,   497,   503,   360,
     505,   489,   490,   502,   388,   506,   533,   492,   515,   507,
     389,   390,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   523,   360,   513,   517,   528,
     531,   529,   539,    12,   532,   541,   546,   549,   550,   551,
     537,   553,   557,   567,   559,   607,   560,   561,   562,   270,
     568,   572,   571,   501,   104,   104,   573,   575,   582,   581,
     509,   511,   104,   388,   586,   587,    31,   386,   360,   389,
     390,   604,   512,   588,   589,   580,   591,   516,    32,    33,
      34,   123,   598,   600,   520,   601,   272,   606,   608,    36,
     410,   611,   124,   612,    40,    41,    42,   613,    43,   618,
     625,   624,   125,   524,   619,   626,   627,    46,   163,   425,
     427,   431,   514,   213,    48,   428,   430,   429,    50,   446,
     504,    52,   540,    53,   401,   350,   378,   556,   485,   593,
     579,     0,     0,     0,     0,   104,   104,     0,     0,     0,
     535,   536,     0,     0,   534,     0,   542,   304,     0,     0,
     145,   544,     0,     0,     0,     0,   563,     0,   545,     0,
       0,     0,     0,   555,     0,     0,   558,     0,     0,     0,
       0,     0,   564,     0,     0,     0,     0,     0,   566,   104,
       0,   104,     0,     0,   254,     0,   254,     0,     0,   271,
     584,   585,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   452,     0,     0,     0,     0,     0,   452,
       0,     0,     0,     0,     0,     0,     0,     0,   145,   145,
       0,     0,     0,     0,     0,     0,     0,   592,     0,     0,
       0,   594,     0,   595,   596,   597,     0,     0,   614,     0,
       0,     0,     0,     0,     0,     0,   603,     0,     0,     0,
       0,   602,   104,     0,     0,   609,     0,   610,     0,     0,
       0,   615,     0,     0,   622,     0,   145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   452,     0,
       0,     0,   621,   104,     0,     0,     0,     0,   623,     0,
       0,     0,   145,     0,   104,     0,     0,   104,     0,   628,
       0,     0,   629,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,    10,    11,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,    24,
     189,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   190,   191,   192,   193,   194,     0,     0,     0,
       0,     0,   195,    36,    37,    38,   196,     0,    40,    41,
     197,   198,    43,     0,     0,     0,    44,   199,    45,     0,
       0,   200,     0,     0,     0,     0,     0,    47,    48,     0,
      49,     0,    50,     0,    51,    52,     1,    53,     2,     3,
       4,     5,     0,     0,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,    29,    30,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,    33,    34,    35,     0,
       0,     0,     0,     0,     0,     0,    36,    37,    38,    39,
       0,    40,    41,    42,     0,    43,     0,     0,   -73,    44,
       0,    45,     0,     0,    46,     0,     0,     0,     0,     0,
      47,    48,     0,    49,     0,    50,     0,    51,    52,     1,
      53,     2,     3,     4,     5,     0,     0,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,     0,     0,     0,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,    33,
      34,    35,     0,     0,     0,     0,     0,     0,     0,    36,
      37,    38,    39,     0,    40,    41,    42,     0,    43,     0,
       0,     0,    44,   199,    45,     0,     0,    46,     0,     0,
       0,     0,     0,    47,    48,     0,    49,     0,    50,     0,
      51,    52,     1,    53,     2,     3,     4,     5,     0,     0,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    32,    33,    34,    35,     0,     0,     0,     0,     0,
       0,     0,    36,    37,    38,    39,     0,    40,    41,    42,
       0,    43,     0,     0,     0,    44,     0,    45,     0,  -231,
      46,     0,     0,     0,     0,     0,    47,    48,     0,    49,
       0,    50,     0,    51,    52,     1,    53,     2,     3,     4,
       5,     0,     0,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,    29,    30,     0,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,    33,    34,    35,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    38,    39,     0,
      40,    41,    42,     0,    43,     0,     0,     0,    44,   394,
      45,     0,     0,    46,     0,     0,     0,     0,     0,    47,
      48,     0,    49,     0,    50,     0,    51,    52,     1,    53,
       2,     3,     4,     5,     0,     0,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,    33,    34,
      35,     0,     0,     0,     0,     0,     0,     0,    36,    37,
      38,    39,     0,    40,    41,    42,     0,    43,     0,     0,
       0,    44,   508,    45,     0,     0,    46,     0,     0,     0,
       0,     0,    47,    48,     0,    49,     0,    50,     0,    51,
      52,     1,    53,     2,     3,     4,     5,     0,     0,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,     0,     0,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,    36,    37,    38,    39,     0,    40,    41,    42,     0,
      43,     0,     0,     0,    44,   510,    45,     0,     0,    46,
       0,     0,     0,     0,     0,    47,    48,     0,    49,     0,
      50,     0,    51,    52,     1,    53,     2,     3,     4,     5,
       0,     0,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    33,    34,    35,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,    39,     0,    40,
      41,    42,     0,    43,     0,     0,     0,    44,   569,    45,
       0,     0,    46,     0,     0,     0,     0,     0,    47,    48,
       0,    49,     0,    50,     0,    51,    52,     1,    53,     2,
       3,     4,     5,     0,     0,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,     0,     0,    29,    30,     0,     0,     0,
       0,     0,     0,     0,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    32,    33,    34,    35,
       0,     0,     0,     0,     0,     0,     0,    36,    37,    38,
      39,     0,    40,    41,    42,     0,    43,     0,     0,     0,
      44,   570,    45,     0,     0,    46,     0,     0,     0,     0,
       0,    47,    48,     0,    49,     0,    50,     0,    51,    52,
       1,    53,     2,     3,     4,     5,     0,     0,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      33,    34,    35,     0,     0,     0,     0,     0,     0,     0,
      36,    37,    38,    39,     0,    40,    41,    42,     0,    43,
       0,     0,     0,    44,     0,    45,    12,     0,    46,    15,
     121,   122,     0,     0,    47,    48,     0,    49,     0,    50,
       0,    51,    52,     0,    53,     0,     0,     0,     0,     0,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    32,    33,    34,   123,     0,     0,     0,     0,     0,
       0,   215,    36,     0,     0,   124,     0,    40,    41,    42,
       0,    43,     0,     0,     0,   125,     0,    45,    12,   308,
      46,    15,   121,   122,     0,     0,    47,    48,     0,    49,
       0,    50,     0,    51,    52,   216,    53,     0,     0,     0,
       0,     0,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    33,    34,   123,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,   124,     0,    40,
      41,    42,     0,    43,     0,     0,   309,   125,     0,    45,
      12,     0,    46,    15,   121,   122,     0,     0,    47,    48,
       0,    49,     0,    50,     0,    51,    52,     0,    53,     0,
       0,     0,     0,     0,    29,    30,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,    33,    34,   123,     0,
       0,     0,     0,     0,     0,   449,    36,     0,     0,   124,
     450,    40,    41,    42,     0,    43,     0,     0,     0,   451,
       0,    45,    12,     0,    46,    15,   121,   122,     0,     0,
      47,    48,     0,    49,     0,    50,     0,    51,    52,     0,
      53,     0,     0,     0,     0,     0,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,    33,    34,
     123,     0,     0,     0,     0,     0,     0,   578,    36,     0,
       0,   124,   450,    40,    41,    42,     0,    43,     0,     0,
       0,   451,     0,    45,    12,     0,    46,    15,   121,   122,
       0,     0,    47,    48,     0,    49,     0,    50,     0,    51,
      52,     0,    53,     0,     0,     0,     0,     0,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      33,    34,   123,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,   124,   206,    40,    41,    42,     0,    43,
       0,     0,     0,   125,     0,    45,    12,     0,    46,    15,
     121,   122,     0,     0,    47,    48,     0,    49,     0,    50,
       0,    51,    52,     0,    53,     0,     0,     0,     0,     0,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    32,    33,    34,   123,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,   124,     0,    40,    41,    42,
       0,    43,     0,     0,     0,   143,     0,    45,    12,  -251,
      46,    15,   121,   122,     0,     0,    47,    48,     0,    49,
       0,    50,     0,    51,    52,     0,    53,     0,     0,     0,
       0,     0,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    33,    34,   123,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,   124,     0,    40,
      41,    42,     0,    43,     0,     0,     0,   143,     0,    45,
      12,  -252,    46,    15,   121,   122,     0,     0,    47,    48,
       0,    49,     0,    50,     0,    51,    52,     0,    53,     0,
       0,     0,     0,     0,    29,    30,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,    33,    34,   123,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,   124,
     393,    40,    41,    42,     0,    43,     0,     0,     0,   125,
       0,    45,    12,     0,    46,    15,   121,   122,     0,     0,
      47,    48,     0,    49,     0,    50,     0,    51,    52,     0,
      53,     0,     0,     0,     0,     0,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,    33,    34,
     123,     0,     0,     0,     0,     0,     0,   215,    36,     0,
       0,   124,     0,    40,    41,    42,     0,    43,     0,     0,
       0,   125,     0,    45,    12,     0,    46,    15,   121,   122,
       0,     0,    47,    48,     0,    49,   423,    50,     0,    51,
      52,     0,    53,     0,     0,     0,     0,     0,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      33,    34,   123,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,   124,     0,    40,    41,    42,     0,    43,
       0,     0,     0,   407,     0,    45,    12,     0,    46,    15,
     121,   122,     0,     0,    47,    48,     0,    49,     0,    50,
       0,    51,    52,     0,    53,     0,     0,     0,     0,     0,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    32,    33,    34,   123,     0,     0,     0,     0,     0,
       0,   519,    36,     0,     0,   124,     0,    40,    41,    42,
       0,    43,     0,     0,     0,   125,     0,    45,    12,     0,
      46,    15,   121,   122,     0,     0,    47,    48,     0,    49,
       0,    50,     0,    51,    52,     0,    53,     0,     0,     0,
       0,     0,    29,    30,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    33,    34,   123,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,   124,     0,    40,
      41,    42,     0,    43,     0,     0,     0,   125,     0,    45,
      12,     0,    46,    15,   121,   122,     0,     0,    47,    48,
       0,    49,     0,    50,     0,    51,    52,     0,    53,     0,
       0,     0,     0,     0,    29,    30,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,    33,    34,   123,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,   124,
       0,    40,    41,    42,     0,    43,     0,     0,     0,   143,
       0,    45,    12,     0,    46,    15,   121,   122,     0,     0,
      47,    48,     0,    49,     0,    50,     0,    51,    52,     0,
      53,     0,     0,     0,     0,     0,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,    33,    34,
     123,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,   124,     0,    40,    41,    42,     0,    43,     0,     0,
       0,   407,     0,    45,    12,     0,    46,    15,   121,   122,
       0,     0,    47,    48,     0,    49,     0,    50,     0,    51,
      52,     0,    53,     0,     0,     0,     0,     0,    29,    30,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      33,    34,   123,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,   124,     0,    40,    41,    42,     0,    43,
       0,     0,     0,   500,     0,    45,    12,     0,    46,    15,
     121,   122,     0,     0,    47,    48,     0,    49,     0,    50,
       0,    51,    52,     0,    53,     0,     0,     0,     0,     0,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    32,    33,    34,   123,     0,     0,    12,     0,     0,
       0,     0,    36,     0,     0,   124,     0,    40,    41,    42,
       0,    43,     0,     0,     0,    44,     0,    45,     0,     0,
      46,    29,    30,     0,     0,     0,    47,    48,     0,    49,
      31,    50,     0,    51,    52,     0,    53,     0,     0,     0,
       0,     0,    32,    33,    34,   123,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,   124,     0,    40,    41,
      42,     0,    43,     0,     0,     0,   125,     0,    45,     0,
       0,    46,     0,     0,     0,     0,     0,     0,    48,     0,
      49,     0,    50,     0,    51,    52,     0,    53,   319,   166,
     320,   321,   322,   323,   171,   172,   324,   325,   326,   327,
       0,     0,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,     0,   340,     0,     0,   319,   166,
     320,   321,   322,   323,   171,   172,   324,   325,   326,   327,
       0,     0,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,     0,   340,     0,   341,   342,   343,
     344,   194,     0,     0,     0,     0,     0,   195,     0,     0,
       0,   345,     0,     0,     0,   346,   198,     0,     0,     0,
       0,     0,   371,     0,     0,     0,   347,   341,   342,   343,
     344,   194,     0,     0,     0,     0,     0,   195,     0,     0,
       0,   345,     0,     0,     0,   346,   198,     0,     0,     0,
       0,     0,   522,     0,     0,     0,   347,   319,   166,   320,
     321,   322,   323,   171,   172,   324,   325,   326,   327,     0,
       0,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,     0,   340,     0,     0,   319,   166,   320,
     321,   322,   323,   171,   172,   324,   325,   326,   327,     0,
       0,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,     0,   340,     0,   341,   342,   343,   344,
     194,     0,     0,     0,     0,     0,   195,     0,     0,     0,
     345,     0,     0,     0,   346,   198,     0,     0,     0,     0,
       0,   527,     0,     0,     0,   347,   341,   342,   343,   344,
     194,     0,     0,     0,     0,     0,   195,     0,     0,     0,
     345,     0,     0,     0,   346,   198,     0,     0,     0,     0,
       0,   565,     0,     0,     0,   347,   319,   166,   320,   321,
     322,   323,   171,   172,   324,   325,   326,   327,     0,     0,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,     0,   340,     0,     0,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,     0,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,     0,   244,     0,   341,   342,   343,   344,   194,
       0,     0,     0,     0,     0,   195,     0,     0,     0,   345,
       0,     0,     0,   346,   198,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   347,   245,   246,   247,   248,   249,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   250,
       0,     0,     0,     0,   251,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,     0,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,     0,   244,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,     0,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,     0,
     244,     0,     0,     0,   245,   246,   247,   248,   249,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   250,     0,
       0,     0,     0,   456,     0,     0,     0,     0,     0,     0,
       0,     0,   245,   246,   247,   248,   249,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   250,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   348,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   348,     0,     0,
       0,     0,     0,     0,     0,   399,   530,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   348,     0,     0,     0,     0,     0,
     349,     0,     0,     0,     0,     0,     0,   348
};

static const yytype_int16 yycheck[] =
{
       0,    12,   136,     3,   138,    23,     0,    14,     3,     5,
     195,   138,   215,   110,     7,   112,   195,   195,   299,     9,
     273,   354,    51,   120,   218,    47,    47,    92,   156,    80,
     215,    77,    22,    23,    24,    77,   215,   215,    89,    77,
      87,     4,     4,   523,    44,    92,    92,    92,     4,    87,
      92,    47,    77,     4,    19,    55,    46,    21,    85,    89,
      55,    99,    52,    80,    91,    77,    92,    92,   106,    81,
      91,   101,    89,    95,   208,    91,    37,    38,    39,    72,
      77,   208,    42,    43,    77,   213,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   113,    77,    77,    87,    81,   598,   109,
     110,    77,   112,   116,    92,   118,    77,    92,    91,    91,
     120,    86,    92,    87,    94,    90,    29,    30,    99,   100,
      73,    86,    77,    86,    77,    90,   106,    90,    81,    35,
      36,   144,    45,   149,   147,   488,    49,   153,   352,   281,
     282,   283,   284,   285,   164,    77,   177,    86,   168,   164,
     188,    90,   179,   168,   170,    86,    92,   348,    77,    90,
      90,   174,   353,    93,    90,    90,   176,    93,    93,    90,
      90,   100,    93,    93,    44,    45,   353,   187,   188,    61,
      62,   201,    77,     4,   279,   280,   201,   401,   286,   287,
     200,   102,   103,   104,   288,   289,   313,    77,   551,    77,
      77,   211,    77,    77,   358,   359,   290,   291,   292,     0,
     364,   358,   366,   367,   368,   369,     4,   364,    91,   366,
     367,   368,   369,    86,    40,    96,   449,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      41,    97,    46,    98,   449,   294,   295,    99,     6,    10,
     449,   449,   525,    92,    86,    86,    92,    92,    92,    77,
      77,    11,    92,    92,    85,    86,    92,    92,    92,    92,
      90,   309,    78,    92,   575,    87,    87,    91,     4,    92,
      90,   308,    91,    91,    91,   107,    91,    90,   298,    91,
     300,    91,    86,    86,    93,    92,   519,    86,    78,   309,
      92,    91,    85,   313,    90,    86,    91,    91,    77,   463,
      85,    93,    90,    86,   519,    78,   463,    93,    88,    93,
     519,   519,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    92,   490,    93,    93,    93,
     100,    90,    86,    18,    92,    77,    93,    77,    88,    92,
     467,    93,    93,    78,    93,   578,    93,    93,    93,    85,
      93,    68,    91,   373,   384,   385,    72,    94,     5,    93,
     384,   385,   392,   578,    86,    93,    51,   392,   532,   578,
     578,   572,   392,    80,    85,   532,    85,   397,    63,    64,
      65,    66,    92,    86,   404,    93,    47,    93,    93,    74,
     591,    86,    77,    86,    79,    80,    81,    93,    83,    93,
      80,    93,    87,   423,   591,    93,    93,    92,    38,   272,
     274,   278,   395,    50,    99,   275,   277,   276,   103,   293,
     378,   106,   470,   108,   211,   127,   152,   490,   356,   554,
     529,    -1,    -1,    -1,    -1,   465,   466,    -1,    -1,    -1,
     465,   466,    -1,    -1,   464,    -1,   472,   467,    -1,    -1,
     470,   477,    -1,    -1,    -1,    -1,   497,    -1,   478,    -1,
      -1,    -1,    -1,   489,    -1,    -1,   492,    -1,    -1,    -1,
      -1,    -1,   498,    -1,    -1,    -1,    -1,    -1,   504,   509,
      -1,   511,    -1,    -1,   509,    -1,   511,    -1,    -1,   512,
     538,   539,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   523,    -1,    -1,    -1,    -1,    -1,   529,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   538,   539,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   553,    -1,    -1,
      -1,   557,    -1,   559,   560,   561,    -1,    -1,   586,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   572,    -1,    -1,    -1,
      -1,   571,   582,    -1,    -1,   581,    -1,   582,    -1,    -1,
      -1,   587,    -1,    -1,   612,    -1,   586,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   598,    -1,
      -1,    -1,   608,   613,    -1,    -1,    -1,    -1,   613,    -1,
      -1,    -1,   612,    -1,   624,    -1,    -1,   627,    -1,   624,
      -1,    -1,   627,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    76,    77,    -1,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    87,    88,    89,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    99,    -1,
     101,    -1,   103,    -1,   105,   106,     4,   108,     6,     7,
       8,     9,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,
      -1,    79,    80,    81,    -1,    83,    -1,    -1,    86,    87,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    99,    -1,   101,    -1,   103,    -1,   105,   106,     4,
     108,     6,     7,     8,     9,    -1,    -1,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      75,    76,    77,    -1,    79,    80,    81,    -1,    83,    -1,
      -1,    -1,    87,    88,    89,    -1,    -1,    92,    -1,    -1,
      -1,    -1,    -1,    98,    99,    -1,   101,    -1,   103,    -1,
     105,   106,     4,   108,     6,     7,     8,     9,    -1,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    -1,    79,    80,    81,
      -1,    83,    -1,    -1,    -1,    87,    -1,    89,    -1,    91,
      92,    -1,    -1,    -1,    -1,    -1,    98,    99,    -1,   101,
      -1,   103,    -1,   105,   106,     4,   108,     6,     7,     8,
       9,    -1,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    -1,
      79,    80,    81,    -1,    83,    -1,    -1,    -1,    87,    88,
      89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,
      99,    -1,   101,    -1,   103,    -1,   105,   106,     4,   108,
       6,     7,     8,     9,    -1,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,    77,    -1,    79,    80,    81,    -1,    83,    -1,    -1,
      -1,    87,    88,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    99,    -1,   101,    -1,   103,    -1,   105,
     106,     4,   108,     6,     7,     8,     9,    -1,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    77,    -1,    79,    80,    81,    -1,
      83,    -1,    -1,    -1,    87,    88,    89,    -1,    -1,    92,
      -1,    -1,    -1,    -1,    -1,    98,    99,    -1,   101,    -1,
     103,    -1,   105,   106,     4,   108,     6,     7,     8,     9,
      -1,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    77,    -1,    79,
      80,    81,    -1,    83,    -1,    -1,    -1,    87,    88,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    99,
      -1,   101,    -1,   103,    -1,   105,   106,     4,   108,     6,
       7,     8,     9,    -1,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
      77,    -1,    79,    80,    81,    -1,    83,    -1,    -1,    -1,
      87,    88,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,
      -1,    98,    99,    -1,   101,    -1,   103,    -1,   105,   106,
       4,   108,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    -1,    87,    -1,    89,    18,    -1,    92,    21,
      22,    23,    -1,    -1,    98,    99,    -1,   101,    -1,   103,
      -1,   105,   106,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    -1,    -1,    77,    -1,    79,    80,    81,
      -1,    83,    -1,    -1,    -1,    87,    -1,    89,    18,    19,
      92,    21,    22,    23,    -1,    -1,    98,    99,    -1,   101,
      -1,   103,    -1,   105,   106,   107,   108,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    79,
      80,    81,    -1,    83,    -1,    -1,    86,    87,    -1,    89,
      18,    -1,    92,    21,    22,    23,    -1,    -1,    98,    99,
      -1,   101,    -1,   103,    -1,   105,   106,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    77,
      78,    79,    80,    81,    -1,    83,    -1,    -1,    -1,    87,
      -1,    89,    18,    -1,    92,    21,    22,    23,    -1,    -1,
      98,    99,    -1,   101,    -1,   103,    -1,   105,   106,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,
      -1,    77,    78,    79,    80,    81,    -1,    83,    -1,    -1,
      -1,    87,    -1,    89,    18,    -1,    92,    21,    22,    23,
      -1,    -1,    98,    99,    -1,   101,    -1,   103,    -1,   105,
     106,    -1,   108,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    77,    78,    79,    80,    81,    -1,    83,
      -1,    -1,    -1,    87,    -1,    89,    18,    -1,    92,    21,
      22,    23,    -1,    -1,    98,    99,    -1,   101,    -1,   103,
      -1,   105,   106,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    77,    -1,    79,    80,    81,
      -1,    83,    -1,    -1,    -1,    87,    -1,    89,    18,    91,
      92,    21,    22,    23,    -1,    -1,    98,    99,    -1,   101,
      -1,   103,    -1,   105,   106,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    79,
      80,    81,    -1,    83,    -1,    -1,    -1,    87,    -1,    89,
      18,    91,    92,    21,    22,    23,    -1,    -1,    98,    99,
      -1,   101,    -1,   103,    -1,   105,   106,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    77,
      78,    79,    80,    81,    -1,    83,    -1,    -1,    -1,    87,
      -1,    89,    18,    -1,    92,    21,    22,    23,    -1,    -1,
      98,    99,    -1,   101,    -1,   103,    -1,   105,   106,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,
      -1,    77,    -1,    79,    80,    81,    -1,    83,    -1,    -1,
      -1,    87,    -1,    89,    18,    -1,    92,    21,    22,    23,
      -1,    -1,    98,    99,    -1,   101,    30,   103,    -1,   105,
     106,    -1,   108,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    77,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    -1,    87,    -1,    89,    18,    -1,    92,    21,
      22,    23,    -1,    -1,    98,    99,    -1,   101,    -1,   103,
      -1,   105,   106,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    -1,    -1,    77,    -1,    79,    80,    81,
      -1,    83,    -1,    -1,    -1,    87,    -1,    89,    18,    -1,
      92,    21,    22,    23,    -1,    -1,    98,    99,    -1,   101,
      -1,   103,    -1,   105,   106,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    79,
      80,    81,    -1,    83,    -1,    -1,    -1,    87,    -1,    89,
      18,    -1,    92,    21,    22,    23,    -1,    -1,    98,    99,
      -1,   101,    -1,   103,    -1,   105,   106,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    77,
      -1,    79,    80,    81,    -1,    83,    -1,    -1,    -1,    87,
      -1,    89,    18,    -1,    92,    21,    22,    23,    -1,    -1,
      98,    99,    -1,   101,    -1,   103,    -1,   105,   106,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    77,    -1,    79,    80,    81,    -1,    83,    -1,    -1,
      -1,    87,    -1,    89,    18,    -1,    92,    21,    22,    23,
      -1,    -1,    98,    99,    -1,   101,    -1,   103,    -1,   105,
     106,    -1,   108,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    77,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    -1,    87,    -1,    89,    18,    -1,    92,    21,
      22,    23,    -1,    -1,    98,    99,    -1,   101,    -1,   103,
      -1,   105,   106,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    77,    -1,    79,    80,    81,
      -1,    83,    -1,    -1,    -1,    87,    -1,    89,    -1,    -1,
      92,    42,    43,    -1,    -1,    -1,    98,    99,    -1,   101,
      51,   103,    -1,   105,   106,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    79,    80,
      81,    -1,    83,    -1,    -1,    -1,    87,    -1,    89,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    99,    -1,
     101,    -1,   103,    -1,   105,   106,    -1,   108,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    31,    -1,    -1,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    31,    -1,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    -1,    92,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    -1,    92,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    -1,    -1,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    -1,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    92,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    92,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    31,    -1,    -1,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    31,    -1,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    82,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    31,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      31,    -1,    -1,    -1,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,   107,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    85
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     6,     7,     8,     9,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    42,
      43,    51,    63,    64,    65,    66,    74,    75,    76,    77,
      79,    80,    81,    83,    87,    89,    92,    98,    99,   101,
     103,   105,   106,   108,   110,   111,   112,   113,   114,   116,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   129,
     130,   131,   132,   133,   134,   136,   137,   140,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   161,   162,   164,   165,   167,
     175,   178,   181,   182,   183,   185,   186,   187,   188,    92,
      92,   112,    92,    87,   113,     4,    77,   139,    77,   139,
      92,    22,    23,    66,    77,    87,   140,   183,    91,    87,
     161,    77,   179,   180,   179,    77,    92,    77,    92,    77,
      77,    77,    77,    87,   138,   140,   171,   138,   140,    77,
      77,   135,    77,    77,   159,   159,   176,    19,    92,    92,
     177,    77,   115,   115,    91,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    31,
      63,    64,    65,    66,    67,    73,    77,    81,    82,    88,
      92,   111,   172,   173,   174,   159,    78,   140,    92,   113,
     100,   166,   159,   176,   158,    73,   107,   140,   169,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    31,    63,    64,    65,    66,    67,
      77,    82,   163,     0,   112,   139,    86,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      85,   139,    47,    95,    40,    41,    96,    97,    98,    35,
      36,    37,    38,    39,    99,   100,    44,    45,    89,   101,
     102,   103,   104,    46,    61,    62,    42,    43,    92,    94,
     106,   160,    99,   184,   140,   170,   170,     6,    19,    86,
     170,    10,   127,    92,   139,    86,   139,    86,   170,     4,
       6,     7,     8,     9,    12,    13,    14,    15,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      31,    63,    64,    65,    66,    77,    81,    92,    85,    91,
     184,    77,   117,    85,    91,    86,    90,    86,    92,    73,
     162,   191,   192,   193,    92,   191,    92,    92,    92,    92,
     190,    88,   139,    90,   139,   113,    86,    90,   190,   113,
     177,    77,    92,    78,    87,    87,   112,    77,   164,   165,
     167,   200,    91,    78,    88,    90,   168,    91,    93,    93,
     191,   169,   177,   200,    90,   168,    86,    87,   141,   142,
     143,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,    30,   141,   146,   145,   147,   148,   149,
     150,   151,   152,   152,   153,   153,   153,   153,   153,   154,
     154,   155,   155,   156,   156,   156,   157,   158,   158,    73,
      78,    87,   140,   197,   198,   199,    82,   163,   140,    21,
      81,   194,    77,    92,    90,    93,    93,    92,   179,   138,
      86,    92,    11,   128,   170,    86,    86,    93,    91,    78,
      85,    90,   168,   141,   194,   180,   191,   162,    91,    93,
      90,   191,    93,   191,   191,   191,   191,    91,   189,    86,
      87,   140,    86,    77,   189,    85,    78,    93,    88,   111,
      88,   111,   140,    93,   173,    88,   140,    93,   168,    73,
     140,   107,    88,    92,   140,    91,   200,    88,    93,    90,
     107,   100,    92,   191,   140,   112,   112,   170,    86,    86,
     138,    77,   113,    93,   113,   140,    93,    80,    89,    77,
      88,    92,   195,    93,   194,   113,   193,    93,   113,    93,
      93,    93,    93,   161,   113,    88,   113,    78,    93,    88,
      88,    91,    68,    72,   200,    94,   197,   145,    73,   199,
     191,    93,     5,    93,   138,   138,    86,    93,    80,    85,
     194,    85,   113,   195,   113,   113,   113,   113,    92,   196,
      86,    93,   140,   113,   143,   163,    93,   200,    93,   113,
     112,    86,    86,    93,   138,   113,    80,    89,    93,   141,
     197,   113,   138,   112,    93,    80,    93,    93,   112,   112
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   109,   110,   111,   111,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   113,   113,   114,   114,   114,   114,
     115,   116,   117,   117,   117,   117,   117,   117,   118,   118,
     118,   118,   119,   120,   120,   121,   122,   123,   124,   124,
     125,   125,   125,   126,   127,   127,   128,   128,   129,   129,
     129,   129,   130,   131,   132,   132,   132,   132,   133,   134,
     135,   135,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   141,   141,   142,   142,   142,   143,
     143,   144,   144,   145,   145,   146,   146,   147,   147,   148,
     148,   149,   149,   150,   150,   151,   151,   151,   152,   152,
     152,   152,   152,   152,   153,   153,   153,   154,   154,   154,
     155,   155,   155,   155,   156,   156,   157,   157,   157,   158,
     158,   158,   158,   158,   158,   159,   159,   159,   159,   159,
     159,   160,   160,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     162,   162,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   164,   164,   165,   165,   166,   167,
     168,   168,   169,   169,   169,   169,   170,   170,   171,   171,
     171,   171,   172,   172,   173,   173,   173,   173,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     175,   175,   175,   176,   177,   178,   178,   179,   179,   180,
     180,   180,   180,   181,   181,   182,   182,   182,   183,   184,
     184,   185,   185,   185,   185,   185,   185,   186,   186,   186,
     187,   187,   188,   188,   189,   189,   190,   190,   191,   191,
     192,   192,   193,   193,   193,   194,   194,   195,   195,   196,
     196,   197,   197,   198,   198,   198,   198,   199,   199,   199,
     200,   200,   200,   200
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     2,     3,     4,     4,     5,     5,
       1,     5,     1,     3,     4,     3,     5,     6,     1,     1,
       1,     1,     3,     5,     7,     5,     7,     5,     3,     2,
      10,     9,     8,     4,     0,     5,     0,     2,     3,     4,
       3,     4,     4,     3,     2,     1,     4,     3,     4,     3,
       1,     3,     2,     0,     2,     0,     1,     0,     4,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     2,     4,     4,     1,
       5,     1,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     3,     1,     3,     3,     1,
       2,     2,     2,     2,     2,     1,     2,     4,     3,     3,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     3,     3,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     4,     2,     5,     0,     4,
       0,     1,     1,     2,     3,     4,     1,     3,     1,     2,
       3,     4,     1,     3,     5,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     2,     0,     3,     3,     3,     1,     3,     1,
       4,     3,     6,     1,     1,     6,     6,     7,     1,     0,
       3,     5,     5,     6,     6,     6,     2,     6,     6,     6,
       5,     5,     3,     3,     0,     3,     0,     3,     0,     1,
       1,     3,     1,     4,     2,     1,     1,     0,     3,     0,
       3,     0,     1,     1,     2,     3,     4,     1,     1,     2,
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
#line 132 "src/kinx.y" /* yacc.c:1646  */
    { kx_ast_root = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[0].obj), kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL)); }
#line 2345 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 137 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST, (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2351 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 159 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-3].strval), KX_UNKNOWN_T), kx_gen_import_object((yyvsp[-1].strval))); }
#line 2357 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 163 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2363 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 164 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_block_object((yyvsp[-1].obj)); }
#line 2369 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 168 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2375 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 169 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2381 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 170 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(0, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2387 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 171 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_namespace_object(1, (yyvsp[-3].strval), (yyvsp[-1].obj)); }
#line 2393 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 175 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_namespace_name_object((yyvsp[0].strval)); }
#line 2399 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 179 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_reset((yyvsp[-2].obj)); }
#line 2405 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 183 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object((yyvsp[0].strval)); }
#line 2411 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 184 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval)); }
#line 2417 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 185 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval)); }
#line 2423 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 186 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), kx_gen_enum_object((yyvsp[0].strval))); }
#line 2429 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 187 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-4].obj), kx_gen_enum_object_with((yyvsp[-2].strval), (yyvsp[0].intval))); }
#line 2435 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 188 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-5].obj), kx_gen_enum_object_with((yyvsp[-3].strval), -(yyvsp[0].intval))); }
#line 2441 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 199 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_label_object(KXST_LABEL, (yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 2447 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 203 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2453 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 204 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2459 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 208 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_WHILE, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2465 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 212 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_DO, (yyvsp[-2].obj), (yyvsp[-5].obj), NULL); }
#line 2471 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 216 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_SWITCH, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 2477 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 220 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_CASE, (yyvsp[-1].obj)); }
#line 2483 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 221 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_case_stmt_object(KXCS_DEFAULT, NULL); }
#line 2489 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 226 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                (yyvsp[-6].obj),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2500 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 233 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR, (yyvsp[-6].obj), NULL, NULL),
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2511 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 240 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                NULL,
                (yyvsp[-4].obj),
                (yyvsp[-2].obj) == NULL ? NULL : kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)),
            (yyvsp[0].obj), NULL); }
#line 2522 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 249 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_TRY, (yyvsp[-2].obj), (yyvsp[-1].obj), (yyvsp[0].obj)); }
#line 2528 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 253 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2534 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 254 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_catch_object(KXST_CATCH, (yyvsp[-2].strval), (yyvsp[0].obj), NULL); }
#line 2540 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 258 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2546 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 259 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 2552 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 263 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, NULL)); }
#line 2558 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 264 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_BREAK, (yyvsp[-2].strval))); }
#line 2564 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 265 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, NULL)); }
#line 2570 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 266 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_break_object(KXST_CONTINUE, (yyvsp[-2].strval))); }
#line 2576 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 270 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[-2].obj), NULL, NULL)); }
#line 2582 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 274 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-2].obj), NULL, NULL)); }
#line 2588 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 278 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj)); }
#line 2594 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 279 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL)); }
#line 2600 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 280 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_YIELD, (yyvsp[0].obj))); }
#line 2606 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 281 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_uexpr_object(KXOP_YIELD, kx_gen_special_object(KXVL_NULL))); }
#line 2612 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 285 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[-1].obj), kx_gen_stmt_object(KXST_THROW, (yyvsp[-2].obj), NULL, NULL)); }
#line 2618 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 289 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2624 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 293 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_MIXIN, NULL, kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2630 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 294 "src/kinx.y" /* yacc.c:1646  */
    { kx_gen_stmt_object(KXST_MIXIN, (yyvsp[-2].obj), kx_gen_var_object((yyvsp[0].strval), KX_OBJ_T), NULL); }
#line 2636 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 298 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 2642 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 302 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, NULL, NULL, NULL); }
#line 2648 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 303 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_modifier((yyvsp[0].obj), kx_gen_stmt_object(KXST_EXPR, (yyvsp[-1].obj), NULL, NULL)); }
#line 2654 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 307 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2660 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 312 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 2666 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 313 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_IF, (yyvsp[-1].obj), NULL, NULL); }
#line 2672 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 318 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2678 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 319 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2684 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 320 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2690 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 321 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2696 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 322 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2702 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 323 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2708 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 324 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2714 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 325 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2720 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 326 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2726 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 327 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2732 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 328 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2738 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 329 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2744 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 330 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2750 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 331 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bassign_object(KXOP_ASSIGN, (yyvsp[-2].obj), kx_gen_bassign_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj))); }
#line 2756 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 340 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 2762 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 341 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_uexpr_object(KXOP_MKOBJ, NULL), (yyvsp[0].obj)); }
#line 2768 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 342 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2774 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 347 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_texpr_object((yyvsp[-4].obj), (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2780 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 357 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LUNDEF, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2786 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 362 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2792 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 367 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LAND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2798 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 372 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_OR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2804 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 377 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_XOR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2810 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 382 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_AND, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2816 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 387 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_EQEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2822 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 388 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_NEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2828 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 393 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2834 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 394 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2840 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 395 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GT, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2846 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 396 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_GE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2852 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 397 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_LGE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2858 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 402 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2864 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 403 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SHR, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2870 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 408 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_ADD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2876 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 409 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_SUB, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2882 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 414 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MUL, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2888 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 415 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DIV, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2894 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 416 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_MOD, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2900 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 421 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_POW, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2906 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 426 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2912 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 427 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_REGNE, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2918 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 432 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NOT, (yyvsp[0].obj)); }
#line 2924 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 433 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_POSITIVE, (yyvsp[0].obj)); }
#line 2930 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 434 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_NEGATIVE, (yyvsp[0].obj)); }
#line 2936 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 435 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_INC, (yyvsp[0].obj)); }
#line 2942 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 436 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_DEC, (yyvsp[0].obj)); }
#line 2948 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 441 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object((yyvsp[0].type), (yyvsp[-1].obj)); }
#line 2954 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 442 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2960 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 443 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 2966 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 444 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object((yyvsp[-2].obj), (yyvsp[0].intval)); }
#line 2972 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 445 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_CALL, (yyvsp[-3].obj), (yyvsp[-1].obj)); }
#line 2978 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 449 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_INCP; }
#line 2984 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 450 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.type) = KXOP_DECP; }
#line 2990 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 454 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_int_object((yyvsp[0].intval)); }
#line 2996 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 455 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_dbl_object((yyvsp[0].dblval)); }
#line 3002 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 456 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_big_object((yyvsp[0].strval)); }
#line 3008 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 457 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_NULL); }
#line 3014 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 458 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3020 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 459 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_TRUE); }
#line 3026 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 460 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_special_object(KXVL_FALSE); }
#line 3032 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 465 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_import_object((yyvsp[-2].strval)); }
#line 3038 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 466 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3044 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 467 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[-1].strval)); }
#line 3050 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 468 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, (yyvsp[0].obj), kx_gen_str_object("create")); }
#line 3056 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 469 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3062 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 470 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_typeof_object(kx_gen_var_object("this", KX_UNKNOWN_T), (yyvsp[0].intval)); }
#line 3068 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 474 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[0].strval); }
#line 3074 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 475 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3080 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 479 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3086 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 480 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("if"); }
#line 3092 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 481 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("else"); }
#line 3098 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 482 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("while"); }
#line 3104 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 483 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("do"); }
#line 3110 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 484 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("for"); }
#line 3116 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 485 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("try"); }
#line 3122 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 486 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("catch"); }
#line 3128 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 487 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("finally"); }
#line 3134 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 488 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("break"); }
#line 3140 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 489 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("continue"); }
#line 3146 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 490 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("switch"); }
#line 3152 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 491 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("case"); }
#line 3158 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 492 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("default"); }
#line 3164 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 493 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("new"); }
#line 3170 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 494 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("var"); }
#line 3176 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 495 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("const"); }
#line 3182 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 496 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("native"); }
#line 3188 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 497 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("function"); }
#line 3194 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 498 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("_function"); }
#line 3200 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 499 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("public"); }
#line 3206 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 500 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("private"); }
#line 3212 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 501 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("protectd"); }
#line 3218 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 502 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("class"); }
#line 3224 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 503 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("module"); }
#line 3230 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 504 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("return"); }
#line 3236 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 505 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("throw"); }
#line 3242 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 506 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("null"); }
#line 3248 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 507 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("true"); }
#line 3254 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 508 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("false"); }
#line 3260 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 509 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("import"); }
#line 3266 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 510 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object("using"); }
#line 3272 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 514 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, NULL); }
#line 3278 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 515 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKARY, (yyvsp[-2].obj)); }
#line 3284 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 519 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, NULL); }
#line 3290 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 520 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKBIN, (yyvsp[-2].obj)); }
#line 3296 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 524 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_bin_mode(); }
#line 3302 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 528 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, (yyvsp[-2].obj)); }
#line 3308 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 532 "src/kinx.y" /* yacc.c:1646  */
    {}
#line 3314 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 538 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3320 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 539 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3326 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 540 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3332 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 545 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3338 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 550 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3344 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 551 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3350 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 552 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRSEQ, (yyvsp[-3].obj), kx_gen_uexpr_object(KXOP_MKOBJ, NULL)); }
#line 3356 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 557 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3362 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 561 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-3].strval), (yyvsp[0].obj)); }
#line 3368 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 562 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3374 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 563 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object((yyvsp[-2].strval), (yyvsp[0].obj)); }
#line 3380 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 564 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_keyvalue_object(NULL, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj))); }
#line 3386 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 568 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "if"; }
#line 3392 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 569 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "else"; }
#line 3398 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 570 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "while"; }
#line 3404 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 571 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "do"; }
#line 3410 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 572 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "for"; }
#line 3416 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 573 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "try"; }
#line 3422 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 574 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "catch"; }
#line 3428 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 575 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "finally"; }
#line 3434 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 576 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "break"; }
#line 3440 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 577 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "continue"; }
#line 3446 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 578 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "switch"; }
#line 3452 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 579 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "case"; }
#line 3458 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 580 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "new"; }
#line 3464 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 581 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "var"; }
#line 3470 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 582 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "const"; }
#line 3476 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 583 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "native"; }
#line 3482 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 584 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "function"; }
#line 3488 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 585 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "_function"; }
#line 3494 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 586 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "public"; }
#line 3500 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 587 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "private"; }
#line 3506 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 588 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "protectd"; }
#line 3512 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 589 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "class"; }
#line 3518 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 590 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "module"; }
#line 3524 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 591 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "return"; }
#line 3530 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 592 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "throw"; }
#line 3536 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 593 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "null"; }
#line 3542 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 594 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "true"; }
#line 3548 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 595 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "false"; }
#line 3554 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 596 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "import"; }
#line 3560 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 597 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = "using"; }
#line 3566 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 598 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typestr_object((yyvsp[0].intval)); }
#line 3572 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 599 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = kx_gen_typeofstr_object((yyvsp[0].intval)); }
#line 3578 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 603 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3584 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 604 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 1); }
#line 3590 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 605 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_regex_object((yyvsp[0].strval), 0); }
#line 3596 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 609 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_regex_mode('/'); }
#line 3602 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 613 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.strval) = (yyvsp[-1].strval); }
#line 3608 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 617 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3614 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 618 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_add_const((yyvsp[-1].obj)); }
#line 3620 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 623 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3626 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 627 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T), NULL); }
#line 3632 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 628 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)), NULL); }
#line 3638 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 629 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object((yyvsp[-2].strval), KX_UNKNOWN_T), (yyvsp[0].obj)); }
#line 3644 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 630 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_type_object((yyvsp[-5].strval), (yyvsp[-3].intval), (yyvsp[-2].intval)), (yyvsp[0].obj)); }
#line 3650 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 634 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3656 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 635 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_stmt_object(KXST_EXPR, (yyvsp[0].obj), NULL, NULL); }
#line 3662 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 639 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3668 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 640 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3674 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 641 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-5].intval), (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3680 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 645 "src/kinx.y" /* yacc.c:1646  */
    { kx_make_native_mode(); }
#line 3686 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 649 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_INT_T; }
#line 3692 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 650 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3698 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 654 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3704 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 655 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3710 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 656 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_NATIVE, (yyvsp[-4].intval), NULL, (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3716 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 657 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), kx_gen_stmt_object(KXST_RET, (yyvsp[0].obj), NULL, NULL), NULL); }
#line 3722 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 658 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, (yyvsp[-3].obj), (yyvsp[0].obj), NULL); }
#line 3728 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 659 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION, NULL, NULL, (yyvsp[0].obj), NULL); }
#line 3734 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 663 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PUBLIC, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3740 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 664 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PRIVATE, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3746 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 665 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_FUNCTION, KXFT_PROTECTED, (yyvsp[-4].strval), (yyvsp[-2].obj), (yyvsp[0].obj), NULL); }
#line 3752 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 669 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3758 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 670 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_CLASS, (yyvsp[-3].strval), (yyvsp[-2].obj), (yyvsp[0].obj), (yyvsp[-1].obj)); }
#line 3764 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 674 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_CLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3770 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 675 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_func_object(KXST_SYSCLASS, KXFT_MODULE, (yyvsp[-1].strval), NULL, (yyvsp[0].obj), NULL); }
#line 3776 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 679 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3782 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 681 "src/kinx.y" /* yacc.c:1646  */
    {
            (yyval.obj) = kx_gen_bexpr_object(KXST_STMTLIST,
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, (yyvsp[-1].obj), kx_gen_str_object("create")), (yyvsp[0].obj))),
                kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("super", KX_UNKNOWN_T),
                    kx_gen_bexpr_object(KXOP_CALL, kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("System", KX_UNKNOWN_T), kx_gen_str_object("makeSuper")), kx_gen_var_object("this", KX_UNKNOWN_T)))
            );
        }
#line 3795 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 692 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3801 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 693 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3807 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 697 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3813 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 703 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[-2].obj), (yyvsp[0].obj)); }
#line 3819 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 707 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3825 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 708 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_type_object((yyvsp[-3].strval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 3831 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 709 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_SPR_T); }
#line 3837 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 713 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval); }
#line 3843 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 714 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_NFNC_T; }
#line 3849 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 718 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = KX_UNKNOWN_T; }
#line 3855 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 719 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3861 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 723 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3867 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 724 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[-1].obj); }
#line 3873 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 728 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = NULL; }
#line 3879 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 734 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)); }
#line 3885 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 735 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, (yyvsp[0].obj), (yyvsp[-2].obj)); }
#line 3891 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 736 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_bexpr_object(KXST_EXPRLIST, kx_gen_uexpr_object(KXOP_SPREAD, (yyvsp[0].obj)), (yyvsp[-3].obj)); }
#line 3897 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 741 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_str_object((yyvsp[0].strval)); }
#line 3903 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 742 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_uexpr_object(KXOP_MKOBJ, NULL); }
#line 3909 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 746 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = kx_gen_var_object((yyvsp[0].strval), KX_UNKNOWN_T); }
#line 3915 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 747 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 3921 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 748 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 3927 "kx.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 749 "src/kinx.y" /* yacc.c:1646  */
    { (yyval.obj) = (yyvsp[0].obj); }
#line 3933 "kx.tab.c" /* yacc.c:1646  */
    break;


#line 3937 "kx.tab.c" /* yacc.c:1646  */
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
#line 752 "src/kinx.y" /* yacc.c:1906  */


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
