typedef union
{
    kx_object_t   *obj;
    int           incdec;
    int64_t       intval;
    double        dblval;
    const char    *strval;
    const uint8_t *binval;
    arytype_t     arraytype;
    named_stmt_t  namedstmt;
    name_t        strinfo;  /* NAME with location */
}
YYSTYPE;
extern YYSTYPE kx_yylval;

#define YYERRTOK 256
#define ERROR 257
#define IF 258
#define ELSE 259
#define WHILE 260
#define DO 261
#define FOR 262
#define IN 263
#define TRY 264
#define CATCH 265
#define FINALLY 266
#define BREAK 267
#define CONTINUE 268
#define SWITCH 269
#define CASE 270
#define DEFAULT 271
#define WHEN 272
#define ENUM 273
#define FALLTHROUGH 274
#define NEW 275
#define VAR 276
#define CONST 277
#define RETURN 278
#define THROW 279
#define YIELD 280
#define MIXIN 281
#define EQEQ 282
#define NEQ 283
#define LE 284
#define GE 285
#define LGE 286
#define LOR 287
#define LAND 288
#define INC 289
#define DEC 290
#define SHL 291
#define SHR 292
#define POW 293
#define LUNDEF 294
#define ADDEQ 295
#define SUBEQ 296
#define MULEQ 297
#define DIVEQ 298
#define MODEQ 299
#define ANDEQ 300
#define OREQ 301
#define XOREQ 302
#define LANDEQ 303
#define LOREQ 304
#define LUNDEFEQ 305
#define SHLEQ 306
#define SHREQ 307
#define REGEQ 308
#define REGNE 309
#define NUL 310
#define TRUE 311
#define FALSE 312
#define AS 313
#define IMPORT 314
#define USING 315
#define DARROW 316
#define SQ 317
#define DQ 318
#define MLSTR 319
#define BINEND 320
#define DOTS2 321
#define DOTS3 322
#define REGPF 323
#define NAMESPACE 324
#define SYSNS 325
#define SYSRET_NV 326
#define CLASS 327
#define SYSCLASS 328
#define MODULE 329
#define SYSMODULE 330
#define NATIVE 331
#define FUNCTION 332
#define SYSFUNC 333
#define PUBLIC 334
#define PRIVATE 335
#define PROTECTED 336
#define COROUTINE 337
#define NAME 338
#define STR 339
#define SRCFILE 340
#define BIGINT 341
#define INT 342
#define TYPE 343
#define TYPEOF 344
#define LBBR 345
#define RBBR 346
#define LMBR 347
#define RMBR 348
#define DBL 349
#define BIN 350
