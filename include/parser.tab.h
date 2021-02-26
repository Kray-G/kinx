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
#define FCOMPOSL2R 297
#define FCOMPOSR2L 298
#define ADDEQ 299
#define SUBEQ 300
#define MULEQ 301
#define DIVEQ 302
#define MODEQ 303
#define ANDEQ 304
#define OREQ 305
#define XOREQ 306
#define LANDEQ 307
#define LOREQ 308
#define LUNDEFEQ 309
#define SHLEQ 310
#define SHREQ 311
#define REGEQ 312
#define REGNE 313
#define NUL 314
#define TRUE 315
#define FALSE 316
#define AS 317
#define IMPORT 318
#define USING 319
#define DARROW 320
#define SQ 321
#define DQ 322
#define MLSTR 323
#define BINEND 324
#define DOTS2 325
#define DOTS3 326
#define REGPF 327
#define NAMESPACE 328
#define SYSNS 329
#define SYSRET_NV 330
#define CLASS 331
#define SYSCLASS 332
#define MODULE 333
#define SYSMODULE 334
#define NATIVE 335
#define FUNCTION 336
#define SYSFUNC 337
#define PUBLIC 338
#define PRIVATE 339
#define PROTECTED 340
#define COROUTINE 341
#define NAME 342
#define STR 343
#define SRCFILE 344
#define BIGINT 345
#define INT 346
#define TYPE 347
#define TYPEOF 348
#define LBBR 349
#define RBBR 350
#define LMBR 351
#define RMBR 352
#define DBL 353
#define BIN 354
