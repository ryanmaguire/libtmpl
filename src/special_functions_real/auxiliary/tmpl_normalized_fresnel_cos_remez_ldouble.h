/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *              tmpl_double_normalized_fresnel_cos_remez_ldouble              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for small values.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Normalized_Fresnel_Cos_Remez                             *
 *  Purpose:                                                                  *
 *      Computes C(x) for 1 <= x < 2.                                         *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      C_x (long double):                                                    *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_Floor:                                               *
 *              Computes the floor of a real number. Only used if neither     *
 *              type punning nor IEEE-754 support are available.              *
 *  Method:                                                                   *
 *      A lookup table has the coefficients for the Remez polynomial for      *
 *      C(x + 1 + n/32) on the interval [0, 1/32) for 0 <= n < 32. We shift x *
 *      to [0, 1/32), compute n, and then evaluate the polynomial using       *
 *      Horner's method.                                                      *
 *  Notes:                                                                    *
 *      This function assumes the input is between 1 and 2.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 *  2.) tmpl_ieee754_ldouble.h:                                               *
 *          Header file with the tmpl_IEEE754_LDouble data type.              *
 *  2.) tmpl_floatint_ldouble.h:                                              *
 *          Header file with the tmpl_FloatIntLongDouble data type.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 8, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_COS_REMEZ_LDOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_REMEZ_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  TMPL_HAS_IEEE754_LDOUBLE macro found here.                                */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  64-bit long double is implemented the same way as double.                 */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                                64-Bit Double                               *
 ******************************************************************************/

/*  Lookup table with the coefficients for the Remez polynomials.             */
extern const long double tmpl_ldouble_normalized_fresnel_cos_table[288];

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
tmpl_ldouble_normalized_fresnel_cos_table[n]+z*(\
    tmpl_ldouble_normalized_fresnel_cos_table[n+1U]+z*(\
        tmpl_ldouble_normalized_fresnel_cos_table[n+2U]+z*(\
            tmpl_ldouble_normalized_fresnel_cos_table[n+3u]+z*(\
                tmpl_ldouble_normalized_fresnel_cos_table[n+4U]+z*(\
                    tmpl_ldouble_normalized_fresnel_cos_table[n+5U]+z*(\
                        tmpl_ldouble_normalized_fresnel_cos_table[n+6U]+z*(\
                            tmpl_ldouble_normalized_fresnel_cos_table[n+7U]+z*(\
                                tmpl_ldouble_normalized_fresnel_cos_table[n+8U]\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  64-bit integers available for type punning. Fastest method.               */
#if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1

/******************************************************************************
 *                        64-Bit Double with 64-Bit Int                       *
 ******************************************************************************/

/*  Union of 64-bit integers and IEEE-754 bit representation found here.      */
#include <libtmpl/include/types/tmpl_floatint_ldouble.h>

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Remez(tmpl_IEEE754_LDouble w)
{
    /*  Union of a 64-bit integer and an IEEE-754 struct.                     */
    tmpl_IEEE754_FloatIntLongDouble u;

    /*  Integer for the index of the Remez polynomial.                        */
    unsigned int n;

    /*  Set the word to the input.                                            */
    u.f = (double)w.r;

    /*  The shift is obtained by zeroing out the bits that are more           *
     *  significant than 1/32. The index n is also computed from these bits.  *
     *  Zero out all other bits. There are 11 bits for the exponent and 5     *
     *  bits for the mantissa needed, the bits for 1/2, 1/4, 1/8, 1/16, and   *
     *  1/32. 0x7FFF800000000000, in hexidecimal, is the bit-mask for this.   */
    u.n &= 0x7FFF800000000000U;

    /*  The 5 bits for the mantissa give the index. Read this off by by       *
     *  shifting over and zeroing out the bits for the exponent. There are 9  *
     *  coefficients for each polynomial, so we need to scale the result by 9.*/
    n = 9U * ((u.n >> 47U) & 0x1FU);

    /*  Shift the input to [0, 1/32) by subtracting off this new value.       */
    w.r -= (long double)u.f;

    /*  Compute the Remez polynomial and return.                              */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Cos_Remez.                         */

/*  IEEE-754 support but no 64-bit integer type-punning. Only slightly slower.*/
#else

/******************************************************************************
 *                      64-Bit Double without 64-Bit Int                      *
 ******************************************************************************/

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Remez(tmpl_IEEE754_LDouble w)
{
    /*  The index is obtained from the bits that are at least as significant  *
     *  as 1/32. That is, 1/2, 1/4, 1/8, 1/16, and 1/32. These are the upper  *
     *  5 bits of the mantissa. man0 has the upper 4 bits, and man1 has 16    *
     *  bits. We can disregard the lower 15 bits of man1 by shifting. There   *
     *  are 9 coefficients for each polynomial, so we scale the result by 9.  */
    const unsigned int n = 9U * ((w.bits.man0 << 1U) + (w.bits.man1 >> 15U));

    /*  We now shift the input to [0, 1/32) by zeroing out these upper 5 bits *
     *  and subtracting off one from the input. First, zero the bits.         */
    w.bits.man0 = 0x00U;
    w.bits.man1 &= 0x7FFFU;

    /*  The input is now between 1 and 1 + 1/32. Shift over to [0, 1/32).     */
    w.r -= 1.0L;

    /*  Compute using the Remez polynomial and return.                        */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Cos_Remez.                         */

#endif
/*  End of 64-bit methods.                                                    */

/*  128-bit double-double uses a modified 64-bit method.                      */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                            128-Bit Double-Double                           *
 ******************************************************************************/

/*  Lookup table with the coefficients for the Remez polynomials.             */
extern const long double tmpl_ldouble_normalized_fresnel_cos_table[480];

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
tmpl_ldouble_normalized_fresnel_cos_table[n]+z*(\
 tmpl_ldouble_normalized_fresnel_cos_table[n+1U]+z*(\
  tmpl_ldouble_normalized_fresnel_cos_table[n+2U]+z*(\
   tmpl_ldouble_normalized_fresnel_cos_table[n+3u]+z*(\
    tmpl_ldouble_normalized_fresnel_cos_table[n+4U]+z*(\
     tmpl_ldouble_normalized_fresnel_cos_table[n+5U]+z*(\
      tmpl_ldouble_normalized_fresnel_cos_table[n+6U]+z*(\
       tmpl_ldouble_normalized_fresnel_cos_table[n+7U]+z*(\
        tmpl_ldouble_normalized_fresnel_cos_table[n+8U]+z*(\
         tmpl_ldouble_normalized_fresnel_cos_table[n+9U]+z*(\
          tmpl_ldouble_normalized_fresnel_cos_table[n+10U]+z*(\
           tmpl_ldouble_normalized_fresnel_cos_table[n+11U]+z*(\
            tmpl_ldouble_normalized_fresnel_cos_table[n+12U]+z*(\
             tmpl_ldouble_normalized_fresnel_cos_table[n+13U]+z*(\
              tmpl_ldouble_normalized_fresnel_cos_table[n+14U]\
             )\
            )\
           )\
          )\
         )\
        )\
       )\
      )\
     )\
    )\
   )\
  )\
 )\
)

/*  64-bit integers available for type punning. Fastest method.               */
#if TMPL_HAS_FLOATINT64 == 1

/******************************************************************************
 *                    128-Bit Double-Double with 64-Bit Int                   *
 ******************************************************************************/

/*  Union of 64-bit integers and IEEE-754 bit representation found here.      */
#include <libtmpl/include/types/tmpl_floatint_ldouble.h>

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Remez(tmpl_IEEE754_LDouble w)
{
    /*  Union of a 64-bit integer and an IEEE-754 struct.                     */
    tmpl_IEEE754_FloatInt64 u;

    /*  Integer for the index of the Remez polynomial.                        */
    unsigned int n;

    /*  Set the word to the input.                                            */
    u.f = w.d[0];

    /*  The shift is obtained by zeroing out the bits that are more           *
     *  significant than 1/32. The index n is also computed from these bits.  *
     *  Zero out all other bits. There are 11 bits for the exponent and 5     *
     *  bits for the mantissa needed, the bits for 1/2, 1/4, 1/8, 1/16, and   *
     *  1/32. 0x7FFF800000000000, in hexidecimal, is the bit-mask for this.   */
    u.n &= 0x7FFF800000000000U;

    /*  The 5 bits for the mantissa give the index. Read this off by by       *
     *  shifting over and zeroing out the bits for the exponent. There are 15 *
     *  coefficients for each polynomial, so we scale the result by 15.       */
    n = 15U * ((u.n >> 47U) & 0x1FU);

    /*  Shift the input to [0, 1/32) by subtracting off this new value.       */
    w.r -= (long double)u.f;

    /*  Compute the Remez polynomial and return.                              */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Cos_Remez.                         */

/*  IEEE-754 support but no 64-bit integer type-punning. Only slightly slower.*/
#else

/******************************************************************************
 *                  128-Bit Double-Double without 64-Bit Int                  *
 ******************************************************************************/

/*  Union for IEEE-754 doubles found here.                                    */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Remez(tmpl_IEEE754_LDouble w)
{
    /*  The index is obtained from the bits that are at least as significant  *
     *  as 1/32. That is, 1/2, 1/4, 1/8, 1/16, and 1/32. These are the upper  *
     *  5 bits of the mantissa. man0 has the upper 4 bits, and man1 has 16    *
     *  bits. We can disregard the lower 15 bits of man1 by shifting. There   *
     *  are 15 coefficients for each polynomial, so we scale the result by 15.*/
    const unsigned int n = 15U * ((w.bits.man0 << 1U) + (w.bits.man1 >> 15U));

    /*  We now shift the input to [0, 1/32) by zeroing out these upper 5 bits *
     *  and subtracting off one from the input. First, zero the bits.         */
    w.bits.man0 = 0x00U;
    w.bits.man1 &= 0x7FFFU;

    /*  The input is now between 1 and 1 + 1/32. Shift over to [0, 1/32).     */
    w.r -= 1.0L;

    /*  Compute using the Remez polynomial and return.                        */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Cos_Remez.                         */

#endif
/*  End of double-double methods.                                             */

/*  Extended and quadruple use similar methods, but the size of the Remez     *
 *  polynomial differs.                                                       */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                              128-Bit Quadruple                             *
 ******************************************************************************/

/*  Lookup table with the coefficients for the Remez polynomials.             */
extern const long double tmpl_ldouble_normalized_fresnel_cos_table[512];

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
tmpl_ldouble_normalized_fresnel_cos_table[n]+z*(\
 tmpl_ldouble_normalized_fresnel_cos_table[n+1U]+z*(\
  tmpl_ldouble_normalized_fresnel_cos_table[n+2U]+z*(\
   tmpl_ldouble_normalized_fresnel_cos_table[n+3u]+z*(\
    tmpl_ldouble_normalized_fresnel_cos_table[n+4U]+z*(\
     tmpl_ldouble_normalized_fresnel_cos_table[n+5U]+z*(\
      tmpl_ldouble_normalized_fresnel_cos_table[n+6U]+z*(\
       tmpl_ldouble_normalized_fresnel_cos_table[n+7U]+z*(\
        tmpl_ldouble_normalized_fresnel_cos_table[n+8U]+z*(\
         tmpl_ldouble_normalized_fresnel_cos_table[n+9U]+z*(\
          tmpl_ldouble_normalized_fresnel_cos_table[n+10U]+z*(\
           tmpl_ldouble_normalized_fresnel_cos_table[n+11U]+z*(\
            tmpl_ldouble_normalized_fresnel_cos_table[n+12U]+z*(\
             tmpl_ldouble_normalized_fresnel_cos_table[n+13U]+z*(\
              tmpl_ldouble_normalized_fresnel_cos_table[n+14U]+z*(\
               tmpl_ldouble_normalized_fresnel_cos_table[n+15U]\
              )\
             )\
            )\
           )\
          )\
         )\
        )\
       )\
      )\
     )\
    )\
   )\
  )\
 )\
)

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Remez(tmpl_IEEE754_LDouble w)
{
    /*  The index is obtained from the bits that are at least as significant  *
     *  as 1/32. That is, 1/2, 1/4, 1/8, 1/16, and 1/32. These are the upper  *
     *  5 bits of the mantissa. man0 has the upper 16 bits, so we shift by 11.*
     *  There are 16 coefficients for each polynomial, so we scale by 16.     *
     *  This is equivalent to shifting up by 4. The shifts cancel, so we need *
     *  to shift down by 7 and zero out the lower 4 bits.                     */
    const unsigned int n = (w.bits.man0 >> 7U) & 0xFFF0;

    /*  Zero out the upper 5 bits. There are 16 bits total, so the bit-mask   *
     *  is 0x7FF.                                                             */
    w.bits.man0 &= 0x7FFU;

    /*  The input is now between 1 and 1 + 1/32. Shift over to [0, 1/32).     */
    w.r -= 1.0L;

    /*  Compute using the Remez polynomial and return.                        */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Cos_Remez.                         */

/*  Extended / portable. Extended is nearly identical to quadruple.           */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Lookup table with the coefficients for the Remez polynomials.             */
extern const long double tmpl_ldouble_normalized_fresnel_cos_table[320];

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
tmpl_ldouble_normalized_fresnel_cos_table[n]+z*(\
  tmpl_ldouble_normalized_fresnel_cos_table[n+1U]+z*(\
    tmpl_ldouble_normalized_fresnel_cos_table[n+2U]+z*(\
      tmpl_ldouble_normalized_fresnel_cos_table[n+3u]+z*(\
        tmpl_ldouble_normalized_fresnel_cos_table[n+4U]+z*(\
          tmpl_ldouble_normalized_fresnel_cos_table[n+5U]+z*(\
            tmpl_ldouble_normalized_fresnel_cos_table[n+6U]+z*(\
              tmpl_ldouble_normalized_fresnel_cos_table[n+7U]+z*(\
                tmpl_ldouble_normalized_fresnel_cos_table[n+8U]+z*(\
                  tmpl_ldouble_normalized_fresnel_cos_table[n+9U]\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Extended uses a bit trick similar to quadruple, but with different values *
 *  for the number of bits. Explicitly, quadruple has 16 bits in the highest  *
 *  mantissa component, but extended has 15. Also, quadruple uses a degree 15 *
 *  expansion, and extended uses degree 9. These are the only differences.    */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT

/******************************************************************************
 *                               80-Bit Extended                              *
 ******************************************************************************/

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Remez(tmpl_IEEE754_LDouble w)
{
    /*  The index is obtained from the bits that are at least as significant  *
     *  as 1/32. That is, 1/2, 1/4, 1/8, 1/16, and 1/32. These are the upper  *
     *  5 bits of the mantissa. man0 has the upper 15, so we shift down by    *
     *  10. There are 10 coefficients for each polynomial, so we scale by 10. */
    const unsigned int n = 10U * (w.bits.man0 >> 10U);

    /*  Zero out the upper 5 bits. There are 15 bits total, so the bit-mask   *
     *  is 0x3FF.                                                             */
    w.bits.man0 &= 0x3FFU;

    /*  The input is now between 1 and 1 + 1/32. Shift over to [0, 1/32).     */
    w.r -= 1.0L;

    /*  Compute using the Remez polynomial and return.                        */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Cos_Remez.                         */

/*  Portable version. Slowest method.                                         */
#else

/******************************************************************************
 *                                  Portable                                  *
 ******************************************************************************/

/*  Tell the compiler about the floor function.                               */
extern long double tmpl_LDouble_Floor(long double x);

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Remez(long double x)
{
    /*  The index is given by the bits up to the 1/32 place. We can get this  *
     *  using the floor function. x-1 shifts the input to [0, 1). By          *
     *  multiplying by 32 and taking the floor function we get these bits as  *
     *  an integer.                                                           */
    const long double n_by_10 = tmpl_LDouble_Floor(32.0L * (x - 1.0L));

    /*  There are 10 coefficients for each polynomial. Scale by 10.           */
    const unsigned int n = (unsigned int)n_by_10 * 10U;

    /*  The shift is floor(32 x) / 32. We've computed floor(32(x-1)) already  *
     *  so we can save a second call to the floor function.                   */
    const long double y = (n_by_10 + 32.0L) / 32.0L;

    /*  Shift so that the input is between 0 and 1/32.                        */
    const long double z = x - y;

    /*  Compute the Remez polynomial and return.                              */
    return TMPL_POLY_EVAL(z);
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Cos_Remez.                         */

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT.                      */

#endif
/*  End of double vs. double-double vs. quadruple vs. extended vs. portable.  */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
