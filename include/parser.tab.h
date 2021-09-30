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
#define OTHERWISE 273
#define ENUM 274
#define FALLTHROUGH 275
#define NEW 276
#define VAR 277
#define CONST 278
#define RETURN 279
#define THROW 280
#define YIELD 281
#define MIXIN 282
#define EQEQ 283
#define NEQ 284
#define LE 285
#define GE 286
#define LGE 287
#define LOR 288
#define LAND 289
#define INC 290
#define DEC 291
#define SHL 292
#define SHR 293
#define POW 294
#define LUNDEF 295
#define PIPEOPL2R 296
#define PIPEOPR2L 297
#define FCOMPOSL2R 298
#define FCOMPOSR2L 299
#define ADDEQ 300
#define SUBEQ 301
#define MULEQ 302
#define DIVEQ 303
#define MODEQ 304
#define ANDEQ 305
#define OREQ 306
#define XOREQ 307
#define LANDEQ 308
#define LOREQ 309
#define LUNDEFEQ 310
#define SHLEQ 311
#define SHREQ 312
#define REGEQ 313
#define REGNE 314
#define NUL 315
#define TRUE 316
#define FALSE 317
#define AS 318
#define IMPORT 319
#define USING 320
#define DARROW 321
#define SQ 322
#define DQ 323
#define MLSTR 324
#define BINEND 325
#define DOTS2 326
#define DOTS3 327
#define REGPF 328
#define NAMESPACE 329
#define SYSNS 330
#define SYSRET_NV 331
#define CLASS 332
#define SYSCLASS 333
#define MODULE 334
#define SYSMODULE 335
#define NATIVE 336
#define FUNCTION 337
#define SYSFUNC 338
#define PUBLIC 339
#define PRIVATE 340
#define PROTECTED 341
#define COROUTINE 342
#define NAME 343
#define STR 344
#define SRCFILE 345
#define BIGINT 346
#define INT 347
#define TYPE 348
#define TYPEOF 349
#define LBBR 350
#define RBBR 351
#define LMBR 352
#define RMBR 353
#define DBL 354
#define BIN 355
