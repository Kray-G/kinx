/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 16 "src/kinx.y" /* yacc.c:1909  */

    kx_object_t   *obj;
    int           type;
    int64_t       intval;
    double        dblval;
    const char    *strval;
    const uint8_t *binval;

#line 151 "kx.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE kx_yylval;

int kx_yyparse (void);

#endif /* !YY_KX_YY_KX_TAB_H_INCLUDED  */
