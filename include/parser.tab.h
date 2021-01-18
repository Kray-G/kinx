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
#define ENUM 272
#define NEW 273
#define VAR 274
#define CONST 275
#define RETURN 276
#define THROW 277
#define YIELD 278
#define MIXIN 279
#define EQEQ 280
#define NEQ 281
#define LE 282
#define GE 283
#define LGE 284
#define LOR 285
#define LAND 286
#define INC 287
#define DEC 288
#define SHL 289
#define SHR 290
#define POW 291
#define LUNDEF 292
#define ADDEQ 293
#define SUBEQ 294
#define MULEQ 295
#define DIVEQ 296
#define MODEQ 297
#define ANDEQ 298
#define OREQ 299
#define XOREQ 300
#define LANDEQ 301
#define LOREQ 302
#define LUNDEFEQ 303
#define SHLEQ 304
#define SHREQ 305
#define REGEQ 306
#define REGNE 307
#define NUL 308
#define TRUE 309
#define FALSE 310
#define AS 311
#define IMPORT 312
#define USING 313
#define DARROW 314
#define SQ 315
#define DQ 316
#define MLSTR 317
#define BINEND 318
#define DOTS2 319
#define DOTS3 320
#define REGPF 321
#define NAMESPACE 322
#define SYSNS 323
#define SYSRET_NV 324
#define CLASS 325
#define SYSCLASS 326
#define MODULE 327
#define SYSMODULE 328
#define NATIVE 329
#define FUNCTION 330
#define SYSFUNC 331
#define PUBLIC 332
#define PRIVATE 333
#define PROTECTED 334
#define COROUTINE 335
#define NAME 336
#define STR 337
#define SRCFILE 338
#define BIGINT 339
#define INT 340
#define TYPE 341
#define TYPEOF 342
#define LBBR 343
#define RBBR 344
#define LMBR 345
#define RMBR 346
#define DBL 347
#define BIN 348
