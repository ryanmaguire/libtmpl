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
 *              tmpl_double_normalized_fresnel_sin_remez_double               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine for small values.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Sin_Remez                              *
 *  Purpose:                                                                  *
 *      Computes C(x) for 1 <= x < 2.                                         *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      S_x (double):                                                         *
 *          The normalized Fresnel sine of x.                                 *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Floor:                                                *
 *              Computes the floor of a real number. Only used if neither     *
 *              64-bit type punning nor IEEE-754 support are available.       *
 *  Method:                                                                   *
 *      A lookup table has the coefficients for the degree 9 Remez            *
 *      polynomial for C(x + 1 + n/32) on the interval [0, 1/32) for          *
 *      0 <= n < 32. We shift x to [0, 1/32), compute n, and then evaluate    *
 *      the polynomial using Horner's method.                                 *
 *                                                                            *
 *      If type-punning with 64-bit int is available, we can speed up the     *
 *      computation of n and the shift with bit shifting.                     *
 *                                                                            *
 *      If 64-bit integer type punning is not available, but IEEE-754 support *
 *      exists (rare), we can achieve the same effect by examining the bits   *
 *      of the input.                                                         *
 *                                                                            *
 *      Lacking IEEE-754 support we compute n using the floor function.       *
 *  Notes:                                                                    *
 *      This function assumes the input is between 1 and 2.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 *  2.) tmpl_ieee754_double.h:                                                *
 *          Header file with the tmpl_IEEE754_Double data type.               *
 *  2.) tmpl_floatint_double.h:                                               *
 *          Header file with the tmpl_FloatInt64 data type.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 8, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_SIN_REMEZ_DOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_SIN_REMEZ_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  TMPL_HAS_IEEE754_DOUBLE macro found here.                                 */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Lookup table with the coefficients for the Remez polynomials.             */
extern const double tmpl_double_normalized_fresnel_sin_table[288];

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
tmpl_double_normalized_fresnel_sin_table[n]+z*(\
    tmpl_double_normalized_fresnel_sin_table[n+1U]+z*(\
        tmpl_double_normalized_fresnel_sin_table[n+2U]+z*(\
            tmpl_double_normalized_fresnel_sin_table[n+3u]+z*(\
                tmpl_double_normalized_fresnel_sin_table[n+4U]+z*(\
                    tmpl_double_normalized_fresnel_sin_table[n+5U]+z*(\
                        tmpl_double_normalized_fresnel_sin_table[n+6U]+z*(\
                            tmpl_double_normalized_fresnel_sin_table[n+7U]+z*(\
                                tmpl_double_normalized_fresnel_sin_table[n+8U]\
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

/*  Union of 64-bit integers and IEEE-754 bit representation found here.      */
#include <libtmpl/include/types/tmpl_floatint_double.h>

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
double tmpl_Double_Normalized_Fresnel_Sin_Remez(tmpl_IEEE754_Double w)
{
    /*  Union of a 64-bit integer and an IEEE-754 struct.                     */
    tmpl_IEEE754_FloatInt64 u;

    /*  Integer for the index of the Remez polynomial.                        */
    unsigned int n;

    /*  Set the word to the input.                                            */
    u.w = w;

    /*  The shift is obtained by zeroing out the bits that are more           *
     *  significant than 1/32. The index n computed from these bits as well.  *
     *  Zero out all other bits. There are 11 bits for the exponent and 5     *
     *  bits for the mantissa needed, the bits for 1/2, 1/4, 1/8, 1/16, and   *
     *  1/32. 0x7FFF800000000000, in hexidecimal, is the bit-mask for this.   */
    u.n &= 0x7FFF800000000000U;

    /*  The 5 bits for the mantissa give the index. Read this off by by       *
     *  shifting over and zeroing out the bits for the exponent. There are 9  *
     *  coefficients for each polynomial, so we need to scale the result by 9.*/
    n = 9U * ((u.n >> 47U) & 0x1FU);

    /*  Shift the input to [0, 1/32) by subtracting off this new value.       */
    w.r -= u.f;

    /*  Compute the Remez polynomial and return.                              */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_Double_Normalized_Fresnel_Sin_Remez.                          */

/*  IEEE-754 support but no 64-bit integer type-punning. Only slightly slower.*/
#elif TMPL_HAS_IEEE754_DOUBLE == 1

/*  Computes S(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
double tmpl_Double_Normalized_Fresnel_Sin_Remez(tmpl_IEEE754_Double w)
{
    /*  The index is obtained from the bits that are at least as significant  *
     *  as 1/32. That is, 1/2, 1/4, 1/8, 1/16, and 1/32. These are the upper  *
     *  5 bits of the mantissa. man0 has the upper 4 bits, and man1 has 16    *
     *  bits. We can disregard the lower 15 bits of man1 by shifting. There   *
     *  are 9 coefficients for each polynomial, so we scale the result by 9.  */
    const unsigned int hi = w.bits.man0 << 1U;
    const unsigned int lo = w.bits.man1 >> 15U;
    const unsigned int n = 9U * (hi + lo);

    /*  We now shift the input to [0, 1/32) by zeroing out these upper 5 bits *
     *  and subtracting off one from the input. First, zero the bits.         */
    w.bits.man0 = 0x00U;
    w.bits.man1 &= 0x7FFFU;

    /*  The input is now between 1 and 1 + 1/32. Shift over to [0, 1/32).     */
    w.r -= 1.0;

    /*  Compute using the Remez polynomial and return.                        */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_Double_Normalized_Fresnel_Sin_Remez.                          */

/*  Portable version. Slowest method.                                         */
#else

/*  Tell the compiler about the floor function.                               */
extern double tmpl_Double_Floor(double x);

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
double tmpl_Double_Normalized_Fresnel_Sin_Remez(double x)
{
    /*  The index is given by the bits up to the 1/32 place. We can get this  *
     *  using the floor function. x-1 shifts the input to [0, 1). By          *
     *  multiplying by 32 and taking the floor function we get these bits as  *
     *  an integer.                                                           */
    const double n_by_9 = tmpl_Double_Floor(32.0 * (x - 1.0));

    /*  There are 9 coefficients for each polynomial. Scale by 9.             */
    const unsigned int n = (unsigned int)n_by_9 * 9U;

    /*  The shift is floor(32 x) / 32. We've computed floor(32(x-1)) already  *
     *  so we can save a second call to the floor function.                   */
    const double y = (n_by_9 + 32.0) / 32.0;

    /*  Shift so that the input is between 0 and 1/32.                        */
    const double z = x - y;

    /*  Compute the Remez polynomial and return.                              */
    return TMPL_POLY_EVAL(z);
}
/*  End of tmpl_Double_Normalized_Fresnel_Sin_Remez.                          */

#endif
/*  End of #if TMPL_HAS_FLOATINT64 == 1.                                      */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
