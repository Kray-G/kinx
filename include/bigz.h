/*
 * Simplified BSD License
 *
 * Copyright (c) 1988-1989, Digital Equipment Corporation & INRIA.
 * Copyright (c) 1992-2020, Eligis
 * All rights reserved.
 *
 * Redistribution and  use in  source and binary  forms, with  or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * o Redistributions  of  source  code must  retain  the  above copyright
 *   notice, this list of conditions and the following disclaimer.
 * o Redistributions  in  binary form  must reproduce the above copyright
 *   notice, this list of conditions and  the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE  IS PROVIDED BY  THE COPYRIGHT HOLDERS  AND CONTRIBUTORS
 * "AS  IS" AND  ANY EXPRESS  OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE  ARE DISCLAIMED. IN NO EVENT  SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL  DAMAGES (INCLUDING,  BUT  NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS  INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF  LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY,  OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING  IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file bigz.h
 * @brief Types and structures for clients of BigZ.
 * @version 2.0.0
 * @copyright Digital Equipment Corporation & INRIA, 1988-1989.
 * @copyright Eligis, 1992-2020
 * @authors B. Serpette
 * @authors J. Vuillemin
 * @authors J.C. Herv&eacute;
 * @authors C. Jullien
 * $Revision: 1.116 $
 * $Date: 2019/12/21 08:22:55 $
 */

#if !defined(__BIGZ_H)
#define __BIGZ_H

#if !defined(__BIGN_H)
#include "bign.h"
#endif

#if defined(__cplusplus)
extern  "C"     {
#endif

#include <stdlib.h>

#if defined(_WIN64) || ( defined(HAVE_STDINT_H) && (SIZEOF_VOID_P >= 8))
#include <stdint.h>
#endif

/** @cond */
#define BZ_PURE_FUNCTION                BN_PURE_FUNCTION
#define BZ_CONST_FUNCTION               BN_CONST_FUNCTION
/** @endcond */

/**
 * BigZ version MM.mm.pp.
 */
#define BZ_VERSION                      "2.0.0"

/**
 * BigZ sign
 */
typedef enum {
        /** Negative */
        BZ_MINUS = -1,
        /** Zero */
        BZ_ZERO  = 0,
        /** Positive */
        BZ_PLUS  = 1
} BzSign;

/**
 * BigZ compare result
 */
typedef enum {
        /** Less than value (-1). */
        BZ_LT    = BN_LT,
        /** Equal than == value (0). */
        BZ_EQ    = BN_EQ,
        /** Greater than comparison value (1). */
        BZ_GT    = BN_GT
} BzCmp;

/** @cond */
typedef enum {
        BZ_UNTIL_END     = 0,
        BZ_UNTIL_INVALID = 1,
        BZ_UNTIL_SLASH   = 2,
        BZ_UNTIL_SPACE   = 3
} BzStrFlag;

/**
 * BigZ number header.
 */
typedef struct {
        BigNumLength    Size;
        BzSign          Sign;
} BigZHeader;

/*
 * define a dummy positive value to declare a Digits vector.
 * BigZ is allocated with required size. Choose a rather large value
 * to prevent 'smart' compilers to exchange fields.
 */

#define BZ_DUMMY_SIZE   32

typedef struct {
        int mark;
        BigZHeader Header;
        /*
         * Digit vector should be the last field to allow allocation
         * of the real size (BZ_DUMMY_SIZE is never used).
         */
        BigNumDigit Digits[BZ_DUMMY_SIZE];
} BigZStruct;

typedef BigZStruct *                    __BigZ;
typedef const BigZStruct *              __CBigZ;

/**
 * BzToString and related functions add sign only when number is negative ('-').
 */
#define BZ_DEFAULT_SIGN                 0

/**
 * Force BzToString and related functions to always add a sign [+|-] when
 * number is not 0.
 */
#define BZ_FORCE_SIGN                   1

/*
 * macros of bigz.c
 */

#if !defined(BZ_BIGNUM_TYPE)
#define BZ_BIGNUM_TYPE
typedef __BigZ                          BigZ;
typedef __CBigZ                         CBigZ;
#endif

#if !defined(BZ_CHAR_TYPE)
#define BZ_CHAR_TYPE
typedef char                            BzChar;
#endif

#if defined(BZ_EXPERIMENTAL_128BIT)
/*
 * No really need to use those types. The most important thing to have is
 * bucket size of 128bit as provided by BN_EXPERIMENTAL_128BIT.
 */
#define BZ_INT_TYPE
typedef __int128_t                      BzInt;
#define BZ_UINT_TYPE
typedef __uint128_t                     BzUInt;
#endif


#if !defined(BZ_INT_TYPE)
#define BZ_INT_TYPE
#if defined(_WIN64) || ( defined(HAVE_STDINT_H) && (SIZEOF_VOID_P >= 8))
typedef int64_t                         BzInt;
#else
typedef int                             BzInt;
#endif
#endif

#if !defined(BZ_UINT_TYPE)
#define BZ_UINT_TYPE
#if defined(_WIN64) || ( defined(HAVE_STDINT_H) && (SIZEOF_VOID_P >= 8))
typedef uint64_t                        BzUInt;
#else
typedef unsigned int                    BzUInt;
#endif
#endif

/*
 * Random seed type, by contract it must be an unsigned int.
 */
typedef unsigned int                    BzSeed;

#define BZ_OPTIMIZE_PRINT

#if !defined(BZ_BUCKET_SIZE)
#if defined(_WIN64) || ( defined(SIZEOF_LONG) && (SIZEOF_LONG == 8))
#define BZ_BUCKET_SIZE 64
#else
#define BZ_BUCKET_SIZE 32
#endif
#endif
/** @endcond */

#if !defined(__EXTERNAL_BIGZ_MEMORY)
/**
 * User overloadable macro that gets native BigZ implementation from
 * a high level object (for example managed in C++ or Lisp).
 */
#define __toBzObj(z)                    ((__BigZ)z)
/**
 * NULL BigZ.
 */
#define BZNULL                          ((BigZ)0)
/**
 * User overloadable macro called to allocate size bytes to store a BigZ.
 */
#define BzAlloc(size)                   kx_malloc(size)
// #define BzAlloc(size)                   bzalloc(size)
// extern void *bzalloc(size_t size);
/**
 * User overloadable macro called to free a BigZ allocated by BzAlloc.
 */
#define BzFree(z)                       kx_free(z)
// #define BzFree(z)                       bzfree(z)
// extern void bzfree(void *p);
/**
 * User overloadable macro called to allocate size BzChar that represent
 * a BzString.
 */
#define BzStringAlloc(size)             kx_malloc(size * sizeof(BzChar))
/**
 * User overloadable macro called to free a buffer allocated by BzStringAlloc.
 */
#define BzFreeString(s)                 kx_free(s)
#endif

/** @cond */
#define BzGetSize(z)                    (__toBzObj(z)->Header.Size)
#define BzGetSign(z)                    (__toBzObj(z)->Header.Sign)
#define BzGetDigit(z,n)                 (__toBzObj(z)->Digits[n])
#define BzToBn(z)                       (__toBzObj(z)->Digits)
#define BzSetSize(z, s)                 (__toBzObj(z)->Header.Size = (s))
#define BzSetSign(z, s)                 (__toBzObj(z)->Header.Sign = (s))
#define BzSetDigit(z, n, v)             (__toBzObj(z)->Digits[n]   = (v))
/** @endcond */

/*
 *      functions of bigz.c
 */

extern const char * BzVersion(void) BZ_CONST_FUNCTION;
extern BigZ         BzCreate(BigNumLength Size);
extern BigNumLength BzNumDigits(const BigZ z) BZ_PURE_FUNCTION;
extern BigNumLength BzLength(const BigZ z) BZ_PURE_FUNCTION;
extern BigZ         BzCopy(const BigZ z);
extern BigZ         BzNegate(const BigZ z);
extern BigZ         BzAbs(const BigZ z);
extern BzCmp        BzCompare(const BigZ y, const BigZ z) BZ_PURE_FUNCTION;
extern BigZ         BzAdd(const BigZ y, const BigZ z);
extern BigZ         BzSubtract(const BigZ y, const BigZ z);
extern BigZ         BzMultiply(const BigZ y, const BigZ z);
extern BigZ         BzDivide(const BigZ y, const BigZ z, BigZ *r);
extern BigZ         BzDiv(const BigZ y, const BigZ z);
extern BigZ         BzTruncate(const BigZ y, const BigZ z);
extern BigZ         BzFloor(const BigZ y, const BigZ z);
extern BigZ         BzCeiling(const BigZ y, const BigZ z);
extern BigZ         BzRound(const BigZ y, const BigZ z);
extern BigZ         BzMod(const BigZ y, const BigZ z);
extern BigZ         BzRem(const BigZ y, const BigZ z);
extern BigZ         BzPow(const BigZ base, BzUInt exponent);
extern BigNumBool   BzIsEven(const BigZ y) BZ_PURE_FUNCTION;
extern BigNumBool   BzIsOdd(const BigZ y) BZ_PURE_FUNCTION;
extern BzChar *     BzToString(const BigZ z, BigNumDigit base, int sign);
extern size_t       BzStrLen(const BzChar *s) BN_PURE_FUNCTION;
extern BzChar *     BzToStringBuffer(const BigZ z, BigNumDigit base, int sign, /*@null@*/ BzChar * const buf, /*@null@*/ size_t *len);
extern BzChar *     BzToStringBufferExt(const BigZ z, BigNumDigit base, int sign, /*@null@*/ BzChar * const buf, /*@null@*/ size_t *len, /*@null@*/ size_t *slen);
extern BigZ         BzFromStringLen(const BzChar *s, size_t len, BigNumDigit base, BzStrFlag flag);
extern BigZ         BzFromString(const BzChar *s, BigNumDigit base, BzStrFlag flag);
extern BigZ         BzFromInteger(BzInt i);
extern BigZ         BzFromUnsignedInteger(BzUInt i);
extern BzInt        BzToInteger(const BigZ z) BZ_PURE_FUNCTION;
extern double       BzToDouble(const BigZ z) BZ_PURE_FUNCTION;
extern int          BzToIntegerPointer(const BigZ z, BzInt *p);
extern BzUInt       BzToUnsignedInteger(const BigZ z) BZ_PURE_FUNCTION;
extern int          BzToUnsignedIntegerPointer(const BigZ z, BzUInt *p);
extern BigZ         BzFromBigNum(const BigNum n, BigNumLength nl);
extern BigNum       BzToBigNum(const BigZ z, BigNumLength *nl);
extern BigNumBool   BzTestBit(BigNumLength bit, const BigZ z);
extern BigNumLength BzBitCount(const BigZ z);
extern BigZ         BzNot(const BigZ z);
extern BigZ         BzAnd(const BigZ y, const BigZ z);
extern BigZ         BzOr(const BigZ y, const BigZ z);
extern BigZ         BzXor(const BigZ y, const BigZ z);
extern BigZ         BzNand(const BigZ x, const BigZ y);
extern BigZ         BzNor(const BigZ x, const BigZ y);
extern BigZ         BzEqv(const BigZ x, const BigZ y);
extern BigZ         BzAndC1(const BigZ x, const BigZ y);
extern BigZ         BzAndC2(const BigZ x, const BigZ y);
extern BigZ         BzOrC1(const BigZ x, const BigZ y);
extern BigZ         BzOrC2(const BigZ x, const BigZ y);
extern BigZ         BzAsh(const BigZ y, int n);
extern BigZ         BzSqrt(const BigZ z);
extern BigZ         BzLcm(const BigZ y, const BigZ z);
extern BigZ         BzGcd(const BigZ y, const BigZ z);
extern BigZ         BzRandom(const BigZ n, BzSeed *seed);
extern BigZ         BzModExp(const BigZ base, const BigZ exponent, const BigZ modulus);

/*
#define BZ_DEBUG
*/

#if defined(BZ_DEBUG)
extern void         BnDebug(const char *m, const BzChar *bzstr, const BigNum n, BigNumLength nl, BzSign sign);
extern void         BzDebug(const char *m, const BigZ y);
#endif

#if defined(__cplusplus)
}
#endif

#endif  /* __BIGZ_H */
