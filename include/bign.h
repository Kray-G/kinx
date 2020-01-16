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
 * @file bign.h
 * @brief Types and structures for clients of BigN.
 * Bignum internal representation
 * ~~~{.unparsed}
 *  <--------------------------- nl ---------------------------->
 *  |   Least                                           Most    |
 *  |Significant|           |           |           |Significant|
 *  |BigNumDigit|           |           |           |BigNumDigit|
 *  |___________|___________|___________|___________|___________|
 *        ^                                          (sometimes
 *        |                                            is zero)
 *       nn
 * ~~~
 * @version 2.0.0
 * @copyright Digital Equipment Corporation & INRIA, 1988-1989.
 * @copyright Eligis, 1992-2020
 * @authors B. Serpette
 * @authors J. Vuillemin
 * @authors J.C. Herv&eacute;
 * @authors C. Jullien
 * $Revision: 1.54 $
 * $Date: 2019/12/21 08:22:54 $
 */

#if !defined(__BIGN_H)
#define __BIGN_H

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(_WIN64) || defined(HAVE_STDINT_H)
#include <stdint.h>
#endif

#if defined(__cplusplus)
extern  "C"     {
#endif

/** @cond */
#if defined(BN_EXPERIMENTAL_128BIT)
#define BN_NUM_DIGIT_TYPE
typedef __uint128_t             BigNumDigit;
#endif

/*
 *      Internal digit type.
 */

#if !defined(BN_NUM_DIGIT_TYPE)
#define BN_NUM_DIGIT_TYPE
#if defined(_WIN64) || ( defined(HAVE_STDINT_H) && (SIZEOF_VOID_P >= 8))
typedef uint64_t                BigNumDigit;
#else
typedef unsigned long           BigNumDigit;
#endif
#endif

#if defined(__GNUC__) && (__GNUC__ >= 3)
#if !defined(BN_CONST_FUNCTION)
#define BN_CONST_FUNCTION       __attribute__((const))
#endif
#if !defined(BN_PURE_FUNCTION)
#define BN_PURE_FUNCTION        __attribute__((pure))
#endif
#endif  /* __GNUC__ >= 3 */

#if !defined(BN_PURE_FUNCTION)
#define BN_PURE_FUNCTION
#endif

#if !defined(BN_CONST_FUNCTION)
#define BN_CONST_FUNCTION
#endif

/*
 *      bignum types: digits, big numbers, carries ...
 */

typedef BigNumDigit *   BigNum;         /* A big number is a digit pointer */
typedef BigNumDigit     BigNumProduct;  /* The product of two digits       */
#if defined(BN_EXPERIMENTAL_128BITX)
typedef __uint128_t     BigNumLength;   /* The length of a bignum          */
#else
typedef unsigned int    BigNumLength;   /* The length of a bignum          */
#endif
/** @endcond */

/**
 * BigNum boolean enum.
 */
typedef enum {
        /** false value (0). */
        BN_FALSE   = 0,
        /** true value (1). */
        BN_TRUE    = 1
} BigNumBool;

/**
 * Results of compare functions.
 */
typedef enum {
        /** Less than value (-1). */
        BN_LT      = -1,
        /** Equal than == value (0). */
        BN_EQ      = 0,
        /** Greater than comparison value (1). */
        BN_GT      = 1
} BigNumCmp;

/**
 * Carry pseudo-boolean enum type.
 */
typedef enum {
        /** No carry (0). */
        BN_NOCARRY = 0,
        /** Carry (1). */
        BN_CARRY   = 1
} BigNumCarry;

/*
 *      sizes
 *
 *      BN_BYTE_SIZE:   number of bits in a byte
 *      BN_DIGIT_SIZE:  number of bits in a digit of a BigNum
 */

#if !defined(BN_BYTE_SIZE)
/**
 * A byte size is generally 8 on most modern machines
 * but may be 9! on old 36bit computers.
 */
#define BN_BYTE_SIZE    ((BigNumLength)8)
#endif

/**
 * Digit size.
 */
#define BN_DIGIT_SIZE   (sizeof(BigNumDigit) * BN_BYTE_SIZE)

/*
 * some constants
 */

/**
 * Digit ZERO constant (0)
 */
#define BN_ZERO         ((BigNumDigit)0)
/**
 * Digit ONE constant (1).
 */
#define BN_ONE          ((BigNumDigit)1)
/**
 * Digit COMPLEMENT constant (~0)
 */
#define BN_COMPLEMENT   (~(BigNumDigit)0)

/*
 *      functions of bign.c
 */

extern BigNumCarry  BnnAdd(BigNum mm, BigNumLength ml, const BigNum nn, BigNumLength nl, BigNumCarry carryin);
extern BigNumCarry  BnnAddCarry(BigNum nn, BigNumLength nl, BigNumCarry carryin);
extern void         BnnAndDigits(BigNum n, BigNumDigit d);
extern void         BnnAssign(BigNum mm, const BigNum nn, BigNumLength nl);
extern BigNumCmp    BnnCompare(const BigNum mm, BigNumLength ml, const BigNum nn, BigNumLength nl) BN_PURE_FUNCTION;
extern BigNumCmp    BnnCompareDigits(BigNumDigit d1, BigNumDigit d2) BN_CONST_FUNCTION;
extern void         BnnComplement(BigNum nn, BigNumLength nl);
extern void         BnnComplement2(BigNum nn, BigNumLength nl);
extern void         BnnDivide(BigNum nn, BigNumLength nl, BigNum dd, BigNumLength dl);
extern BigNumDigit  BnnDivideDigit(BigNum qq, BigNum nn, BigNumLength nl, BigNumDigit d);
extern BigNumDigit  BnnGetDigit(const BigNum nn) BN_PURE_FUNCTION;
extern BigNumBool   BnnIsPower2(const BigNum nn, BigNumLength nl) BN_PURE_FUNCTION;
extern BigNumBool   BnnIsDigitEven(BigNumDigit d) BN_CONST_FUNCTION;
extern BigNumBool   BnnIsDigitOdd(BigNumDigit d) BN_CONST_FUNCTION;
extern BigNumBool   BnnIsDigitNormalized(BigNumDigit d) BN_CONST_FUNCTION;
extern BigNumBool   BnnIsDigitZero(BigNumDigit d) BN_CONST_FUNCTION;
extern BigNumBool   BnnIsZero(const BigNum nn, BigNumLength nl) BN_PURE_FUNCTION;
extern BigNumCarry  BnnMultiply(BigNum pp, BigNumLength pl, const BigNum mm, BigNumLength ml, const BigNum nn, BigNumLength nl);
extern BigNumCarry  BnnMultiplyDigit(BigNum pp, BigNumLength pl, const BigNum mm, BigNumLength ml, BigNumDigit d);
extern BigNumLength BnnNumDigits(const BigNum nn, BigNumLength nl) BN_PURE_FUNCTION;
extern BigNumLength BnnNumLength(const BigNum nn, BigNumLength nl) BN_PURE_FUNCTION;
extern BigNumLength BnnNumCount(const BigNum nn, BigNumLength nl) BN_PURE_FUNCTION;
extern BigNumLength BnnNumLeadingZeroBitsInDigit(BigNumDigit d) BN_CONST_FUNCTION;
extern void         BnnOrDigits(BigNum n, BigNumDigit d);
extern void         BnnSetDigit(BigNum nn, BigNumDigit d);
extern void         BnnSetToZero(BigNum nn, BigNumLength nl);
extern BigNumDigit  BnnShiftLeft(BigNum mm, BigNumLength ml, BigNumLength nbits);
extern BigNumDigit  BnnShiftRight(BigNum mm, BigNumLength ml, BigNumLength nbits);
extern BigNumCarry  BnnSubtract(BigNum mm, BigNumLength ml, const BigNum nn, BigNumLength nl, BigNumCarry carryin);
extern BigNumCarry  BnnSubtractBorrow(BigNum nn, BigNumLength nl, BigNumCarry carryin);
extern void         BnnXorDigits(BigNum n, BigNumDigit d);

#if defined(__cplusplus)
}
#endif

#endif  /* __BIGN_H */
