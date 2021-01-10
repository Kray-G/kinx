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
 * @file bign.c
 * @brief the kernel written in pure C (it uses no C library)
 * Description of types and constants.
 *
 * Several conventions are used in the commentary:
 * - A "BigNum" is the name for an infinite-precision number.
 * - Capital letters (e.g., "N") are used to refer to the value of BigNums.
 * - The word "digit" refers to a single BigNum digit.
 * - The notation "Size(N)" refers to the number of digits in N,
 *   which is typically passed to the subroutine as "nl".
 * - The notation "Length(N)" refers to the number of digits in N,
 *   not including any leading zeros.
 * - The word "Base" is used for the number 2 ** BN_DIGIT_SIZE, where
 *   BN_DIGIT_SIZE is the number of bits in a single BigNum digit.
 * - The expression "BBase(N)" is used for Base ** NumDigits(N).
 * - The term "leading zeros" refers to any zeros before the most
 *   significant digit of a number.
 *
 * In the code, we have:
 * - "nn" is a pointer to a big number,
 * - "nl" is the number of digits from nn,
 * - "d" is a digit.
 * @version 2.0.0
 * @copyright Digital Equipment Corporation & INRIA, 1988-1989.
 * @copyright Eligis, 1992-2020
 * @authors B. Serpette
 * @authors J. Vuillemin
 * @authors J.C. Herv&eacute;
 * @authors C. Jullien
 * $Revision: 1.83 $
 * $Date: 2019/12/21 08:22:54 $
 */

#include <dbg.h>
#include "bign.h"

static void
BnnDivideHelper(BigNum nn, BigNumLength nl, BigNum dd, BigNumLength dl);

/**
 * BnnSetToZero.
 * Sets all the specified digits of the BigNum to BN_ZERO (0).
 * @param [in, out] nn BigNum
 * @param [in] nl BigNumLength
 */
void
BnnSetToZero(BigNum nn, BigNumLength nl) {
        BigNumLength d;

        for (d = 0; d < nl; ++d) {
                nn[d] = BN_ZERO;
        }
}

/**
 * BnnAssign.
 * Copies N => M
 * @param [in, out] mm BigNum
 * @param [in] nn const BigNum
 * @param [in] nl BigNumLength
 */
void
BnnAssign(BigNum mm, const BigNum nn, BigNumLength nl) {
        int d;

        if ((mm < nn) || (mm > (nn + nl))) {
                /*
                 * no memory overlap using classic loop
                 */
                for (d = 0; d < (int)nl; ++d) {
                        mm[d] = nn[d];
                }
        } else if (mm > nn) {
                /*
                 * memory overlap, loop starting from most significant digit
                 */
                for (d = (int)(nl - 1); d >= 0; --d) {
                        mm[d] = nn[d];
                }
        }
}

/**
 * BnnSetDigit.
 * Sets a single digit of N to the passed value
 * @param [in, out] nn BigNum
 * @param [in] d BigNumDigit
 */
void
BnnSetDigit(BigNum nn, BigNumDigit d) {
        *nn = d;
}

/**
 * BnnGetDigit.
 * Returns the single digit pointed by N
 * @param [in] nn BigNum
 * @return BigNumDigit
 */
BigNumDigit
BnnGetDigit(const BigNum nn) {
        return *nn;
}

/**
 * BnnNumDigits.
 * Returns the number of digits of N, not counting leading zeros.
 * @param [in] nn BigNum
 * @param [in] nl BigNumLength
 * @return BigNumLength
 */
BigNumLength
BnnNumDigits(const BigNum nn, BigNumLength nl) {
        int d;

        /*
         * loop starting from most significant digit
         */

        for (d = (int)(nl - 1); d >= 0; --d) {
                if (nn[d] != BN_ZERO) {
                        /*
                         * length = d+1
                         */
                        return (BigNumLength)(d + 1);
                }
        }

        return (BigNumLength)1;
}

/**
 * BnnNumLength.
 * Returns the number of bits of N, not counting leading zeros.
 * @param [in] nn BigNum
 * @param [in] nl BigNumLength
 * @return BigNumLength
 */
BigNumLength
BnnNumLength(const BigNum nn, BigNumLength nl) {
        const BigNumDigit d = nn[nl - 1];
        int i;

        for (i = (int)(BN_DIGIT_SIZE - 1); i >= 0; --i) {
                if ((d & (BN_ONE << (BigNumLength)i)) != 0) {
                        BigNumLength bits = (BigNumLength)i + 1;
                        return (BigNumLength)(((nl-1) * BN_DIGIT_SIZE) + bits);
                }
        }

        return 0;
}

/**
 * BnnNumCount.
 * Returns the count of bits set of N.
 * @param [in] nn BigNum
 * @param [in] nl BigNumLength
 * @return BigNumLength
 */
BigNumLength
BnnNumCount(const BigNum nn, BigNumLength nl) {
        BigNumLength count = 0;
        int j;

        for (j = 0; j < (int)nl; ++j) {
                const BigNumDigit d = nn[j];
                int     i;

                for (i = (int)(BN_DIGIT_SIZE - 1); i >= 0; --i) {
                        if ((d & (BN_ONE << (BigNumLength)i)) != 0) {
                                ++count;
                        }
                }
        }

        return count;
}

/**
 * BnnNumLeadingZeroBitsInDigit.
 * Returns the number of leading zero bits in a digit
 * @param [in] d BigNumDigit
 * @return BigNumLength
 */
BigNumLength
BnnNumLeadingZeroBitsInDigit(BigNumDigit d) {
        BigNumDigit  mask = (BigNumDigit)(BN_ONE << (BN_DIGIT_SIZE - 1));
        BigNumLength p;

        if (d == BN_ZERO) {
                return (BigNumLength)BN_DIGIT_SIZE;
        }

        for (p = 0; (d & mask) == 0; ++p) {
                mask >>= 1;
        }

        return p;
}

/**
 * BnnIsPower2.
 * Returns BN_TRUE iff nn is a power of 2.
 * @param [in] nn BigNum
 * @param [in] nl BigNumLength
 * @return BigNumBool
 */
BigNumBool
BnnIsPower2(const BigNum nn, BigNumLength nl) {
        BigNumLength i;
        BigNumLength nbits;
        BigNumDigit  d;

        /*
         * The n-1 digits must be 0
         */

        for (i = 0; i < (nl - 1); ++i) {
                if (nn[i] != BN_ZERO) {
                        return BN_FALSE;
                }
        }

        /*
         * There must be only 1 bit set on the last Digit.
         */

        d     = nn[i];
        nbits = 0;

        for (i = 0; i < (BigNumLength)BN_DIGIT_SIZE; ++i) {
                if ((d & (BN_ONE << i)) != 0) {
                        if (nbits++ > 0) {
                                /*
                                 * More than two digits.
                                 */
                                return BN_FALSE;
                        }
                }
        }

        return BN_TRUE;
}

/**
 * BnnIsDigitZero.
 * Returns BN_TRUE iff digit = 0
 * @param [in] d igNumDigit
 * @return BigNumBool
 */
BigNumBool
BnnIsDigitZero(BigNumDigit d) {
        return (BigNumBool)(d == 0);
}

/**
 * BnnIsDigitNormalized.
 * Returns BN_TRUE iff Base/2 <= digit < Base i.e. if digit's leading
 * bit is 1
 * @param [in] d BigNumDigit
 * @return BigNumBool
 */
BigNumBool
BnnIsDigitNormalized(BigNumDigit d) {
        if ((d & (BN_ONE << (BN_DIGIT_SIZE - 1))) != 0) {
                return BN_TRUE;
        } else {
                return BN_FALSE;
        }
}

/**
 * BnnIsDigitOdd.
 * Returns BN_TRUE iff digit is odd.
 * @param [in] d BigNumDigit
 * @return BigNumBool
 */
BigNumBool
BnnIsDigitOdd(BigNumDigit d) {
        if ((d & 1) != 0) {
                return BN_TRUE;
        } else {
                return BN_FALSE;
        }
}

/**
 * BnnIsDigitEven.
 * Returns BN_TRUE iff digit is even
 * @param [in] d BigNumDigit
 * @return BigNumBool
 */
BigNumBool
BnnIsDigitEven(BigNumDigit d) {
        if ((d & 1) == 0) {
                return BN_TRUE;
        } else {
                return BN_FALSE;
        }
}

/**
 * BnnCompareDigits.
 * Returns:
 * - BN_GT if d1 > d2
 * - BN_EQ if d1 = d2
 * - BN_LT if d1 < d2
 * @param [in] d1 BigNumDigit
 * @param [in] d2 BigNumDigit
 * @return BigNumCmp
 */
BigNumCmp
BnnCompareDigits(BigNumDigit d1, BigNumDigit d2) {
        return (BigNumCmp)((d1 > d2) ? BN_GT : (d1 == d2 ? BN_EQ : BN_LT));
}

/**
 * BnnComplement.
 * Performs the computation BBase(N) - N - 1 => N
 * @param [in, out] nn BigNum
 * @param [in] nl BigNumLength
 */
void
BnnComplement(BigNum nn, BigNumLength nl) {
        BigNumLength d;

        for (d = 0; d < nl; ++d) {
                nn[d] ^= BN_COMPLEMENT;
        }
}

/**
 * BnnComplement2.
 * Performs the computation neg(N) => N
 * @param [in, out] nn BigNum
 * @param [in] nl BigNumLength
 */
void
BnnComplement2(BigNum nn, BigNumLength nl) {
        BigNumDigit one = BN_ONE;

        /*
         * Initialize constants
         */

        BnnComplement(nn, nl);
        (void)BnnAdd(nn, nl, &one, (BigNumLength)1, BN_NOCARRY);
}

/**
 * BnnAndDigits.
 * Returns the logical computation n[0] AND d in n[0]
 * @param [in, out] n BigNum
 * @param [in] d BigNumDigit
 */
void
BnnAndDigits(BigNum n, BigNumDigit d) {
        *n &= d;
}

/**
 * BnnOrDigits.
 * Returns the logical computation n[0] OR d2 in n[0].
 * @param [in, out] n BigNum
 * @param [in] d BigNumDigit
 */
void
BnnOrDigits(BigNum n, BigNumDigit d) {
        *n |= d;
}

/**
 * BnnXorDigits.
 * Returns the logical computation n[0] XOR d in n[0].
 * @param [in, out] n BigNum
 * @param [in] d BigNumDigit
 */
void
BnnXorDigits(BigNum n, BigNumDigit d) {
        *n ^= d;
}

/*
 *      Shift operations
 */

/**
 * BnnShiftLeft.
 * Shifts M left by "nbits", filling with 0s.
 * Returns the leftmost  "nbits"  of  M in a digit.
 * @pre 0 <= nbits < BN_DIGIT_SIZE.
 * @param [in, out] mm BigNum
 * @param [in] ml BigNumLength
 * @param [in] nbits BigNumLength
 * @return BigNumDigit
 */
BigNumDigit
BnnShiftLeft(BigNum mm, BigNumLength ml, BigNumLength nbits) {
        BigNumDigit res = BN_ZERO;

        if (nbits != 0) {
                BigNumLength rnbits = (BigNumLength)(BN_DIGIT_SIZE - nbits);
                BigNumLength evenlen = (ml & ~(BigNumLength)1);
                BigNumLength d;

                /*
                 * Loop is now unrooled two BigNumDigit at a time.
                 */

                for (d = 0; d < evenlen; ++d) {
                        BigNumDigit save0;
                        BigNumDigit save1;
                        save0 = mm[d];
                        mm[d] = (save0 << nbits) | res;
                        save1 = mm[++d];
                        mm[d] = (save1 << nbits) | (save0 >> rnbits);
                        res   = save1 >> rnbits;
                }

                if (ml != evenlen) {
                        BigNumDigit save = mm[d];
                        mm[d] = (save << nbits) | res;
                        res   = save >> rnbits;
                }
        }

        return res;
}

/**
 * BnnShiftRight.
 * Shifts M right by "nbits", filling with 0s.
 * Returns the rightmost "nbits" of M in a digit.
 * @pre 0 <= nbits < BN_DIGIT_SIZE.
 * @param [in, out] mm BigNum
 * @param [in] ml BigNumLength
 * @param [in] nbits BigNumLength
 * @return BigNumDigit
 */
BigNumDigit
BnnShiftRight(BigNum mm, BigNumLength ml, BigNumLength nbits) {
        BigNumDigit res = BN_ZERO;

        if (nbits != 0) {
                const BigNumLength lnbits = (BigNumLength)BN_DIGIT_SIZE - nbits;

                /*
                 * loop starting from most significant digit
                 */

                if ((ml & (BigNumLength)1) != (BigNumLength)0) {
                        /*
                         * Odd number of digits, start with most significant
                         * digit, then loop on even number of digits.
                         */
                        BigNumDigit save = mm[--ml];
                        mm[ml] = (save >> nbits); /* res==0, no need to | res */
                        res    = save << lnbits;
                }

                /*
                 * Loop is now unrooled two digits at a time.
                 */

                while (ml != (BigNumLength)0) {
                        BigNumDigit save0;
                        BigNumDigit save1;
                        save0  = mm[--ml];
                        mm[ml] = (save0 >> nbits) | res;
                        save1  = mm[--ml];
                        mm[ml] = (save1 >> nbits) | (save0 << lnbits);
                        res    = save1 << lnbits;
                }
        }

        return res;
}

/*
 *      Additions
 */

/**
 * BnnAddCarry.
 * Performs the sum N + CarryIn => N.
 * Returns the CarryOut.
 * @param [in, out] nn BigNum
 * @param [in] nl BigNumLength
 * @param [in] carryin BigNumCarry
 * @return BigNumCarry
 */
BigNumCarry
BnnAddCarry(BigNum nn, BigNumLength nl, BigNumCarry carryin) {
        if (carryin == BN_NOCARRY) {
                return BN_NOCARRY;
        } else if (nl == 0) {
                return BN_CARRY;
        } else {
                BigNumLength d;

                for (d = 0; d < nl; ++d) {
                        if (++nn[d] != 0) {
                                return BN_NOCARRY;
                        }
                }

                return BN_CARRY;
        }
}

/**
 * BnnAdd.
 * Performs the sum M + N + CarryIn => M.
 * Returns the CarryOut.
 * @pre Size(M) >= Size(N).
 * @param [in, out] mm BigNum
 * @param [in] ml BigNumLength
 * @param [in] nn BigNum
 * @param [in] nl BigNumLength
 * @param [in] carryin BigNumCarry
 * @return BigNumCarry
 */
BigNumCarry
BnnAdd(BigNum mm,
       BigNumLength ml,
       const BigNum nn,
       BigNumLength nl,
       BigNumCarry carryin) {
        BigNumProduct c = (BigNumProduct)carryin;
        BigNumLength i;

        for (i = 0; i < nl; ++i) {
                BigNumProduct save = (BigNumProduct)*mm;

                c   += save;
                if (c < save) {
                        *(mm++) = nn[i];
                        c       = (BigNumProduct)1;
                } else {
                        save    = (BigNumProduct)nn[i];
                        c      += save;
                        *(mm++) = (BigNumDigit)c;
                        c       = (BigNumProduct)((c < save) ? 1 : 0);
                }
        }

        return BnnAddCarry(mm, ml-nl, ((c == 0) ? BN_NOCARRY : BN_CARRY));
}

/*
 *      Subtraction
 */

/**
 * BnnSubtractBorrow.
 * Performs the difference N + CarryIn - 1 => N.
 * Returns the CarryOut.
 * @param [in, out] nn BigNum
 * @param [in] nl BigNumLength
 * @param [in] carryin BigNumCarry
 * @return BigNumCarry
 */
BigNumCarry
BnnSubtractBorrow(BigNum nn, BigNumLength nl, BigNumCarry carryin) {
        if (carryin == BN_CARRY) {
                return BN_CARRY;
        } else if (nl == 0) {
                return BN_NOCARRY;
        } else {
                BigNumLength d;

                for (d = 0; d < nl; ++d) {
                        if (nn[d]-- != 0) {
                                return BN_CARRY;
                        }
                }

                return BN_NOCARRY;
        }
}

/**
 * BnnSubtract.
 * Performs the difference M - N + CarryIn - 1 => M.
 * Returns the CarryOut.
 * @pre Size(M) >= Size(N).
 * @param [in, out] mm BigNum
 * @param [in] ml BigNumLength
 * @param [in] nn BigNum
 * @param [in] nl BigNumLength
 * @param [in] carryin BigNumCarry
 * @return BigNumCarry
 */
BigNumCarry
BnnSubtract(BigNum mm,
            BigNumLength ml,
            const BigNum nn,
            BigNumLength nl,
            BigNumCarry carryin) {
        BigNumProduct c = (BigNumProduct)((carryin == BN_CARRY) ? 1 : 0);
        BigNumDigit   invn;
        BigNumProduct save;
        BigNumLength  i;

        for (i = 0; i < nl; ++i) {
                save = (BigNumProduct)*mm;
                invn = nn[i] ^ BN_COMPLEMENT;
                c += save;

                if (c < save) {
                        *(mm++) = invn;
                        c       = (BigNumProduct)1;
                } else {
                        c      += invn;
                        *(mm++) = (BigNumDigit)c;
                        c       = (BigNumProduct)((c < invn) ? 1 : 0);
                }
        }

        if (c == 0) {
                return BnnSubtractBorrow(mm, ml-nl, BN_NOCARRY);
        } else {
                return BnnSubtractBorrow(mm, ml-nl, BN_CARRY);
        }
}

/*
 *      Multiplication
 */

/** @cond */
#define LOW(x)   (BigNumDigit)(x & ((BN_ONE << (BN_DIGIT_SIZE / 2)) - 1))
#define HIGH(x)  (BigNumDigit)(x >> (BN_DIGIT_SIZE / 2))
#define L2H(x)   (BigNumDigit)(x << (BN_DIGIT_SIZE / 2))

#define UPDATE_S(c, V, X3) c += V; X3 += (BigNumDigit)(c < V);
/** @endcond */

/**
 * BnnMultiplyDigit.
 * Performs the product:
 * - Q = P + M * d
 * - BB = BBase(P)
 * - Q mod BB => P
 * - Q div BB => CarryOut
 * Returns the CarryOut.
 * @pre Size(P) >= Size(M) + 1.
 * @param [in, out] pp BigNum
 * @param [in] pl BigNumLength
 * @param [in] mm BigNum
 * @param [in] ml BigNumLength
 * @param [in] d BigNumDigit
 * @return BigNumCarry
 */
BigNumCarry
BnnMultiplyDigit(BigNum pp,
                 BigNumLength pl,
                 const BigNum mm,
                 BigNumLength ml,
                 BigNumDigit d) {
        BigNumLength    i;
        BigNumProduct   c = 0;
        BigNumDigit     save;

        if (d == BN_ZERO) {
                return BN_NOCARRY;
        }

        if (d == BN_ONE) {
                return BnnAdd(pp, pl, mm, ml, BN_NOCARRY);
        }

        for (i = 0; i < ml; ++i) {
                BigNumDigit Lm;
                BigNumDigit Hm;
                BigNumDigit Ld;
                BigNumDigit Hd;
                BigNumDigit X0;
                BigNumDigit X1;
                BigNumDigit X2;
                BigNumDigit X3;

                Ld = LOW(d);
                Hd = HIGH(d);
                Lm = LOW(mm[i]);
                Hm = HIGH(mm[i]);
                X0 = Ld * Lm;
                X1 = Ld * Hm;
                X2 = Hd * Lm;
                X3 = Hd * Hm;

                UPDATE_S(c, X0,      X3);
                UPDATE_S(c, L2H(X1), X3);
                UPDATE_S(c, L2H(X2), X3);
                UPDATE_S(c, *pp,     X3);

                --pl;
                *(pp++) = (BigNumDigit)c;
                c = X3 + HIGH(X1) + HIGH(X2);
        }

        if (pl == 0) {
                return BN_NOCARRY;
        }

        save  = *pp;
        c    += save;
        *pp   = (BigNumDigit)c;

        if (c >= save) {
                return BN_NOCARRY;
        }

        ++pp;
        --pl;

        while (pl != 0 && (++(*pp++)) == 0) {
                pl--;
        }

        return (pl != 0) ? BN_NOCARRY : BN_CARRY;
}

/*
 * Division
 */

/** @cond */
/* xh:xl -= yh:yl */

#define SUB(xh, xl, yh, yl)                               \
        xh -= (BigNumDigit)(yh + (BigNumDigit)(yl > xl)); \
        xl -= yl;
/** @endcond */

/**
 * BnnDivideDigit.
 * Performs the quotient: N div d => Q.
 * Returns R = N mod d.
 * @pre Assumes leading digit of N < d, and d > 0.
 * @param [in, out] qq BigNum
 * @param [in, out] nn BigNum
 * @param [in] nl BigNumLength
 * @param [in] d BigNumDigit
 * @return BigNumDigit
 */
BigNumDigit
BnnDivideDigit(BigNum qq, BigNum nn, BigNumLength nl, BigNumDigit d) {
        BigNumLength k;
        BigNumLength orig_nl;
        BigNumDigit  rh;     /* Two halves of current remainder */
        BigNumDigit  rl;     /* Correspond to quad above        */
        BigNumDigit  ph;
        BigNumDigit  pl;     /* product of c and qa             */
        BigNumDigit  ch;
        BigNumDigit  cl;
        BigNumDigit  prev_qq;

        /*
         * Normalize divisor
         */

        k = BnnNumLeadingZeroBitsInDigit(d);

        if (k != 0) {
#if defined(__GNUC__) && (__GNUC__ >= 9)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif /* __GNUC__ >= 9 */
                prev_qq = qq[-1];
#if defined(__GNUC__) && (__GNUC__ >= 9)
#pragma GCC diagnostic pop
#endif /* __GNUC__ >= 9 */
                orig_nl = nl;
                d <<= k;
                (void)BnnShiftLeft(nn, nl, k);
        } else {
                prev_qq = 0;
                orig_nl = 0;
        }

        nn += nl;
        nl--;
        qq += nl;

        ch = HIGH(d);
        cl = LOW(d);

        /*
         * At this point ch can't be == 0; d has been shifted by k
         * (the number of leading 0).
         */

        rl = *(--nn);

        while (nl-- != 0) {
                BigNumDigit qa; /* Current appr. to quotient */

                rh = rl;
                rl = *(--nn);
                qa = rh / ch;   /* appr. quotient */

                /*
                 * Compute ph, pl
                 */

                pl = cl * qa;
                ph = ch * qa;
                ph += HIGH(pl);
                pl = L2H(pl);

                /*
                 * While ph:pl > rh:rl, decrement qa, adjust qh:ql
                 */

                while ((ph > rh) || ((ph == rh) && (pl > rl))) {
                        qa--;
                        SUB(ph, pl, ch, L2H(cl));
                }

                SUB(rh, rl, ph, pl);

                /*
                 * Top half of quotient is correct; save it
                 */

                *(--qq) = L2H(qa);
                qa = (L2H(rh) | HIGH(rl)) / ch;

                /*
                 * Approx low half of q. Compute ph, pl, again
                 */

                pl = cl * qa;
                ph = ch * qa;
                ph += HIGH(pl);
                pl = LOW(pl) | L2H(LOW(ph));
                ph = HIGH(ph);

                /*
                 * While ph:pl > rh:rl, decrement qa, adjust qh:ql
                 */

                while ((ph > rh) || ((ph == rh) && (pl > rl))) {
                        qa--;
                        SUB(ph, pl, 0, d);
                }

                /*
                 * Subtract ph:pl from rh:rl; we know rh will be 0
                 */

                rl -= pl;
                *qq |= qa;
        }

        /*
         * Denormalize dividend
         */

        if (k != 0) {
                if ((qq > nn) && (qq < &nn[orig_nl])) {
                        /*
                         * Overlap between qq and nn. Care of *qq!
                         */
                        orig_nl = (BigNumLength)(qq - nn);
                        (void)BnnShiftRight(nn, orig_nl, k);
                        nn[orig_nl - 1] = prev_qq;
                } else if (qq == nn) {
                        (void)BnnShiftRight(&nn[orig_nl-1], (BigNumLength)1, k);
                } else {
                        (void)BnnShiftRight(nn, orig_nl, k);
                }
        }
        return rl >> k;
}

/**
 * BnnIsZero.
 * Returns BN_TRUE iff N = 0
 * @param [in] nn BigNum
 * @param [in] nl BigNumLength
 * @return BigNumBool
 */
BigNumBool
BnnIsZero(const BigNum nn, BigNumLength nl) {
        if ((BnnNumDigits(nn, nl) == (BigNumLength)1)
            && (nl == 0 || BnnIsDigitZero(*nn) != BN_FALSE)) {
                return BN_TRUE;
        } else {
                return BN_FALSE;
        }
}

/**
 * BnnMultiplyDigit.
 * Performs the product:
 * - Q = P + M * N
 * - BB = BBase(P)
 * - Q mod BB => P
 * - Q div BB => CarryOut
 *
 * Returns the CarryOut.
 *
 * @pre
 * - Size(P) >= Size(M) + Size(N),
 * - Size(M) >= Size(N).
 * @param [in, out] pp BigNum
 * @param [in] pl BigNumLength
 * @param [in] mm BigNum
 * @param [in] ml BigNumLength
 * @param [in] nn BigNum
 * @param [in] nl BigNumLength
 * @return BigNumCarry
 */
BigNumCarry
BnnMultiply(BigNum pp,
            BigNumLength pl,
            const BigNum mm,
            BigNumLength ml,
            const BigNum nn,
            BigNumLength nl) {
        BigNumLength i;
        BigNumCarry  c = BN_NOCARRY;

        /*
         * Multiply one digit at a time
         */

        for (i = 0; i < nl; ++i) {
                if (BnnMultiplyDigit(&pp[i], pl--, mm, ml, nn[i]) == BN_CARRY) {
                        c = BN_CARRY;
                }
        }

        return c;
}

/** @cond */
#define BNN_COMPARE_DIGITS(d1, d2) (d1 == d2)
/** @endcond */

/**
 * BnnDivideHelper
 *
 * In-place division.
 *
 * Input (N has been EXTENDED by 1 PLACE; D is normalized):
 * ~~~{.unparsed}
 *      +-----------------------------------------------+----+
 *      |                       N                         EXT|
 *      +-----------------------------------------------+----+
 *
 *      +-------------------------------+
 *      |               D              1|
 *      +-------------------------------+
 * ~~~
 * Output (in place of N):
 * ~~~{.unparsed}
 *      +-------------------------------+---------------+----+
 *      |               R               |          Q         |
 *      +-------------------------------+---------------+----+
 * ~~~
 * @pre
 * - N > D
 * - Size(N) > Size(D)
 * - last digit of N < last digit of D
 * - D is normalized (Base/2 <= last digit of D < Base)
 * @param [in, out] nn BigNum
 * @param [in] nl BigNumLength
 * @param [in, out] dd BigNum
 * @param [in] dl BigNumLength
 */
static void
BnnDivideHelper(BigNum nn, BigNumLength nl, BigNum dd, BigNumLength dl) {
        BigNumDigit  DDigit;
        BigNumDigit  BaseMinus1;
        BigNumDigit  QApp;
        BigNumLength ni;

        /*
         * Initialize constants
         */

        /*
         * BaseMinus1 = BN_COMPLEMENT;
         * ->
         *      BnnSetDigit(&BaseMinus1, BN_ZERO);
         *      BnnComplement(&BaseMinus1, (BigNumLength)1);
         */

        BaseMinus1 = BN_COMPLEMENT;

        /*
         * Save the most significant digit of D
         */

        DDigit = BN_ZERO;
        BnnAssign(&DDigit, dd + dl - 1, (BigNumLength)1);

        /*
         * Replace D by Base - D
         */

        BnnComplement(dd, dl);
        (void)BnnAddCarry(dd, dl, BN_CARRY);

        /*
         * For each digit of the divisor, from most significant to least:
         */

        QApp = BN_ZERO;
        nl += 1;
        ni = nl - dl;

        while (ni != 0) {
                /*
                 * Compute the approximate quotient
                 */

                ni--;
                nl--;

                /*
                 * If first digits of numerator and denominator are the same,
                 */

                if (BNN_COMPARE_DIGITS(*(nn + nl), DDigit)) {
                        /*
                         * Use "Base - 1" for the approximate quotient
                         */
                        BnnAssign(&QApp, &BaseMinus1, (BigNumLength)1);
                } else {
                        /*
                         * Divide  the  first  2  digits  of N by the
                         * first digit of D
                         */
                        (void)BnnDivideDigit(&QApp,
                                             nn + nl - 1,
                                             (BigNumLength)2,
                                             DDigit);
                }

                /*
                 * Compute the remainder
                 */

                (void)BnnMultiplyDigit(nn + ni, dl + 1, dd, dl, QApp);

                /*
                 * Correct the approximate quotient, in case it was too large
                 */

                while (!BNN_COMPARE_DIGITS(*(nn + nl), QApp)) {
                        /*
                         * Subtract D from N
                         */

                        (void)BnnSubtract(nn+ni, dl + 1, dd, dl, BN_CARRY);

                        /*
                         * Q -= 1
                         */

                        (void)BnnSubtractBorrow(&QApp,
                                                (BigNumLength)1,
                                                BN_NOCARRY);
                }
        }

        /*
         * Restore original D
         */

        BnnComplement(dd, dl);
        (void)BnnAddCarry(dd, dl, BN_CARRY);
}

/**
 * BnnDivide.
 * Performs the quotient:
 * - N div D => high-order bits of N, starting at N[dl]
 * - N mod D => low-order dl bits of N
 * @pre
 * - Size(N) > Size(D),
 * - last digit of N < last digit of D (if N > D).
 * @param [in, out] nn BigNum
 * @param [in] nl BigNumLength
 * @param [in, out] dd BigNum
 * @param [in] dl BigNumLength
 */
void
BnnDivide(BigNum nn, BigNumLength nl, BigNum dd, BigNumLength dl) {
        BigNumLength nshift;

        /*
         * Take care of easy cases first
         */

        switch (BnnCompare(nn, nl, dd, dl)) {
        case BN_LT:     /* n < d */
                /* nop */                              /* N => R */
                BnnSetToZero(nn + dl, nl - dl);        /* 0 => Q */
                return;
        case BN_EQ:     /* n == d */
                BnnSetToZero(nn, nl);                  /* 0 => R */
                BnnSetDigit(nn + nl - 1, BN_ONE);      /* 1 => Q */
                return;
        case BN_GT:     /* n > d */
                /*
                 * If divisor is just 1 digit, use a special divide
                 */

                if (dl == (BigNumLength)1) {
                        /*
                         * note: nn+1 = nn+dl
                         */

                        *nn = BnnDivideDigit(nn + 1, nn, nl, *dd);

                        /*
                         * Otherwise, divide one digit at a time
                         */
                } else {
                        /*
                         * Normalize
                         */

                        nshift = BnnNumLeadingZeroBitsInDigit(*(dd + dl - 1));
                        (void)BnnShiftLeft(dd, dl, nshift);
                        (void)BnnShiftLeft(nn, nl, nshift);

                        /*
                         * Divide
                         */

                        BnnDivideHelper(nn, nl - 1, dd, dl);

                        /*
                         * Unnormalize
                         */

                        (void)BnnShiftRight(dd, dl, nshift);
                        (void)BnnShiftRight(nn, dl, nshift);

                        /*
                         * note: unnormalize N <=> unnormalize R (with R < D)
                         */
                }
        }
}

/**
 * BnnCompare.
 * Compare two bignums M and N and returns:
 * - BN_GT iff M > N
 * - BN_EQ iff N = N
 * - BN_LT iff N < N
 * @param [in] mm BigNum
 * @param [in] ml BigNumLength
 * @param [in] nn BigNum
 * @param [in] nl BigNumLength
 * @return BigNumCmp
 */
BigNumCmp
BnnCompare(const BigNum mm,
           BigNumLength ml,
           const BigNum nn,
           BigNumLength nl) {
        ml = BnnNumDigits(mm, ml);
        nl = BnnNumDigits(nn, nl);

        if (ml != nl) {
                return (ml > nl) ? BN_GT : BN_LT;
        } else {
                int d;

                /*
                 * loop starting from most significant digit
                 */

                for (d = (int)(nl - 1); d >= 0; --d) {
                        if (mm[d] != nn[d]) {
                                return (mm[d] > nn[d]) ? BN_GT : BN_LT;
                        }
                }

                return BN_EQ;
        }
}
