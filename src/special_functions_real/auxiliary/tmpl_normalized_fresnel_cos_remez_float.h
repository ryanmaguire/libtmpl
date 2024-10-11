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
 *               tmpl_float_normalized_fresnel_cos_remez_float                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for small values.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Normalized_Fresnel_Cos_Remez                               *
 *  Purpose:                                                                  *
 *      Computes C(x) for 1 <= x < 2.                                         *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      C_x (float):                                                          *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Floor:                                                 *
 *              Computes the floor of a real number. Only used if neither     *
 *              32-bit type punning nor IEEE-754 support are available.       *
 *  Method:                                                                   *
 *      A lookup table has the coefficients for the degree 3 Remez            *
 *      polynomial for C(x + 1 + n/32) on the interval [0, 1/32) for          *
 *      0 <= n < 32. We shift x to [0, 1/32), compute n, and then evaluate    *
 *      the polynomial using Horner's method.                                 *
 *                                                                            *
 *      If type-punning with 32-bit int is available, we can speed up the     *
 *      computation of n and the shift with bit shifting.                     *
 *                                                                            *
 *      If 32-bit integer type punning is not available, but IEEE-754 support *
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
 *  2.) tmpl_ieee754_float.h:                                                 *
 *          Header file with the tmpl_IEEE754_Float data type.                *
 *  2.) tmpl_floatint.h:                                                      *
 *          Header file with the tmpl_FloatInt32 data type.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 8, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_COS_REMEZ_FLOAT_H
#define TMPL_NORMALIZED_FRESNEL_COS_REMEZ_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  TMPL_HAS_IEEE754_FLOAT macro found here.                                  */
#include <libtmpl/include/tmpl_ieee754_float.h>

/*  Lookup table with the coefficients for the Remez polynomials.             */
extern const float tmpl_float_normalized_fresnel_cos_table[128];

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
tmpl_float_normalized_fresnel_cos_table[n]+z*(\
    tmpl_float_normalized_fresnel_cos_table[n+1U]+z*(\
        tmpl_float_normalized_fresnel_cos_table[n+2U]+z*(\
            tmpl_float_normalized_fresnel_cos_table[n+3U]\
        )\
    )\
)

/*  32-bit integers available for type punning. Fastest method.               */
#if TMPL_HAS_FLOATINT32 == 1

/*  Union of 32-bit integers and IEEE-754 bit representation found here.      */
#include <libtmpl/include/tmpl_floatint.h>

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
float tmpl_Float_Normalized_Fresnel_Cos_Remez(tmpl_IEEE754_Float w)
{
    /*  Union of a 32-bit integer and an IEEE-754 struct.                     */
    tmpl_IEEE754_FloatInt32 u;

    /*  Integer for the index of the Remez polynomial.                        */
    unsigned int n;

    /*  Set the word to the input.                                            */
    u.w = w;

    /*  The shift is obtained by zeroing out the bits that are more           *
     *  significant than 1/32. The index n is also computed from these bits.  *
     *  Zero out all other bits. There are 8 bits for the exponent and 5      *
     *  bits for the mantissa needed, the bits for 1/2, 1/4, 1/8, 1/16, and   *
     *  1/32. 0x7FFC0000, in hexidecimal, is the bit-mask for this.           */
    u.n &= 0x7FFC0000;

    /*  The 5 bits for the mantissa give the index. Read this off by          *
     *  shifting over and zeroing out the bits for the exponent. There are 4  *
     *  coefficients for each polynomial, so we need to scale the result by 4.*
     *  This is equivalent to shifting up by two. So in total, we need to     *
     *  shift down by 18, apply a bit-mask, and shift up by 2. The shifts     *
     *  cancel, so we need to shift down by 16 and apply an altered bit mask. */
    n = (u.n >> 16U) & 0x7CU;

    /*  Shift the input to [0, 1/32) by subtracting off this new value.       */
    w.r -= u.f;

    /*  Compute the Remez polynomial and return.                              */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_Float_Normalized_Fresnel_Cos_Remez.                           */

/*  IEEE-754 support but no 32-bit integer type-punning. Only slightly slower.*/
#elif TMPL_HAS_IEEE754_FLOAT == 1

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
float tmpl_Float_Normalized_Fresnel_Cos_Remez(tmpl_IEEE754_Float w)
{
    /*  The index is obtained from the bits that are at least as significant  *
     *  as 1/32. That is, 1/2, 1/4, 1/8, 1/16, and 1/32. These are the upper  *
     *  5 bits of the mantissa. man0 has the upper 7 bits, so we need to zero *
     *  out the lower 2 bits and shift over by two. There are 4 coefficients  *
     *  per polynomial so we need to then shift up by two. The shifts cancel, *
     *  meaning we only need to use the bitmask.                              */
    const unsigned int n = w.bits.man0 & 0x7CU;

    /*  We now shift the input to [0, 1/32) by zeroing out these upper 5 bits *
     *  and subtracting off one from the input. First, zero the bits.         */
    w.bits.man0 &= 0x03U;

    /*  The input is now between 1 and 1 + 1/32. Shift over to [0, 1/32).     */
    w.r -= 1.0F;

    /*  Compute using the Remez polynomial and return.                        */
    return TMPL_POLY_EVAL(w.r);
}
/*  End of tmpl_Float_Normalized_Fresnel_Cos_Remez.                           */

/*  Portable version. Slowest method.                                         */
#else

/*  Tell the compiler about the floor function.                               */
extern float tmpl_Float_Floor(float x);

/*  Computes C(x) using Remez polynomials and a lookup table.                 */
TMPL_STATIC_INLINE
float tmpl_Float_Normalized_Fresnel_Cos_Remez(float x)
{
    /*  The index is given by the bits up to the 1/32 place. We can get this  *
     *  using the floor function. x-1 shifts the input to [0, 1). By          *
     *  multiplying by 32 and taking the floor function we get these bits as  *
     *  an integer.                                                           */
    const float n_by_4 = tmpl_Float_Floor(32.0F * (x - 1.0F));

    /*  There are 4 coefficients for each polynomial. Scale by 4.             */
    const unsigned int n = (unsigned int)n_by_4 * 4U;

    /*  The shift is floor(32 x) / 32. We've computed floor(32(x-1)) already  *
     *  so we can save a second call to the floor function.                   */
    const float y = (n_by_4 + 32.0F) / 32.0F;

    /*  Shift so that the input is between 0 and 1/32.                        */
    const float z = x - y;

    /*  Compute the Remez polynomial and return.                              */
    return TMPL_POLY_EVAL(z);
}
/*  End of tmpl_Float_Normalized_Fresnel_Cos_Remez.                           */

#endif
/*  End of #if TMPL_HAS_FLOATINT32 == 1.                                      */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
