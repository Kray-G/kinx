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
#define PIPEOPL2R 295
#define PIPEOPR2L 296
#define ADDEQ 297
#define SUBEQ 298
#define MULEQ 299
#define DIVEQ 300
#define MODEQ 301
#define ANDEQ 302
#define OREQ 303
#define XOREQ 304
#define LANDEQ 305
#define LOREQ 306
#define LUNDEFEQ 307
#define SHLEQ 308
#define SHREQ 309
#define REGEQ 310
#define REGNE 311
#define NUL 312
#define TRUE 313
#define FALSE 314
#define AS 315
#define IMPORT 316
#define USING 317
#define DARROW 318
#define SQ 319
#define DQ 320
#define MLSTR 321
#define BINEND 322
#define DOTS2 323
#define DOTS3 324
#define REGPF 325
#define NAMESPACE 326
#define SYSNS 327
#define SYSRET_NV 328
#define CLASS 329
#define SYSCLASS 330
#define MODULE 331
#define SYSMODULE 332
#define NATIVE 333
#define FUNCTION 334
#define SYSFUNC 335
#define PUBLIC 336
#define PRIVATE 337
#define PROTECTED 338
#define COROUTINE 339
#define NAME 340
#define STR 341
#define SRCFILE 342
#define BIGINT 343
#define INT 344
#define TYPE 345
#define TYPEOF 346
#define LBBR 347
#define RBBR 348
#define LMBR 349
#define RMBR 350
#define DBL 351
#define BIN 352
