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
#define PIPEOP 295
#define ADDEQ 296
#define SUBEQ 297
#define MULEQ 298
#define DIVEQ 299
#define MODEQ 300
#define ANDEQ 301
#define OREQ 302
#define XOREQ 303
#define LANDEQ 304
#define LOREQ 305
#define LUNDEFEQ 306
#define SHLEQ 307
#define SHREQ 308
#define REGEQ 309
#define REGNE 310
#define NUL 311
#define TRUE 312
#define FALSE 313
#define AS 314
#define IMPORT 315
#define USING 316
#define DARROW 317
#define SQ 318
#define DQ 319
#define MLSTR 320
#define BINEND 321
#define DOTS2 322
#define DOTS3 323
#define REGPF 324
#define NAMESPACE 325
#define SYSNS 326
#define SYSRET_NV 327
#define CLASS 328
#define SYSCLASS 329
#define MODULE 330
#define SYSMODULE 331
#define NATIVE 332
#define FUNCTION 333
#define SYSFUNC 334
#define PUBLIC 335
#define PRIVATE 336
#define PROTECTED 337
#define COROUTINE 338
#define NAME 339
#define STR 340
#define SRCFILE 341
#define BIGINT 342
#define INT 343
#define TYPE 344
#define TYPEOF 345
#define LBBR 346
#define RBBR 347
#define LMBR 348
#define RMBR 349
#define DBL 350
#define BIN 351
