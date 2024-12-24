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
 *                        tmpl_arcsin_tail_end_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the asin(x) for 0.5 <= x < 1.0.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arcsin_Tail_End                                          *
 *  Purpose:                                                                  *
 *      Computes the inverse sine for 0.5 <= x < 1.                           *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      asin_x (long double):                                                 *
 *          The inverse sine of x.                                            *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_Sqrt:                                                *
 *              Computes the square root of a number.                         *
 *  Method:                                                                   *
 *      Use the following trig identity:                                      *
 *          asin(x) = pi/2 - 2*asin(sqrt((1-x)/2))                            *
 *      Compute this using a Remez rational minimax approximation.            *
 *          64-bit double:                                                    *
 *              Order (10, 8) approximant.                                    *
 *          80-bit extended / portable:                                       *
 *              Order (12, 10) approximant.                                   *
 *          128-bit quadruple / 128-bit double-double:                        *
 *              Order (18, 18) approximant.                                   *
 *  Notes:                                                                    *
 *      Accurate for 0.5 <= x < 1.0.                                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2023                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCSIN_TAIL_END_LDOUBLE_H
#define TMPL_ARCSIN_TAIL_END_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  The compiler needs to know about the sqrt function.                       */
extern long double tmpl_LDouble_Sqrt(long double x);

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the numerator.                                           */
#define A00 (+1.66666666666666657415E-01L)
#define A01 (-3.25565818622400915405E-01L)
#define A02 (+2.01212532134862925881E-01L)
#define A03 (-4.00555345006794114027E-02L)
#define A04 (+7.91534994289814532176E-04L)
#define A05 (+3.47933107596021167570E-05L)

/*  Coefficients for the denominator.                                         */
#define B00 (+1.00000000000000000000E+00L)
#define B01 (-2.40339491173441421878E+00L)
#define B02 (+2.02094576023350569471E+00L)
#define B03 (-6.88283971605453293030E-01L)
#define B04 (+7.70381505559019352791e-02L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  128-bit quadruple and double-double, a few more terms.                    */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT || \
      TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                 128-bit Quadruple / 128-bit Double-Double                  *
 ******************************************************************************/

/*  Coefficients for the numerator.                                           */
#define A00 (+1.66666666666666666666666666666700314E-01L)
#define A01 (-7.32816946414566252574527475428622708E-01L)
#define A02 (+1.34215708714992334609030036562143589E+00L)
#define A03 (-1.32483151677116409805070261790752040E+00L)
#define A04 (+7.61206183613632558824485341162121989E-01L)
#define A05 (-2.56165783329023486777386833928147375E-01L)
#define A06 (+4.80718586374448793411019434585413855E-02L)
#define A07 (-4.42523267167024279410230886239774718E-03L)
#define A08 (+1.44551535183911458253205638280410064E-04L)
#define A09 (-2.10558957916600254061591040482706179E-07L)

/*  Coefficients for the denominator.                                         */
#define B00 (+1.00000000000000000000000000000000000E+00L)
#define B01 (-4.84690167848739751544716485245697428E+00L)
#define B02 (+9.96619113536172610135016921140206980E+00L)
#define B03 (-1.13177895428973036660836798461641458E+01L)
#define B04 (+7.74004374389488266169304117714658761E+00L)
#define B05 (-3.25871986053534084709023539900339905E+00L)
#define B06 (+8.27830318881232209752469022352928864E-01L)
#define B07 (-1.18768052702942805423330715206348004E-01L)
#define B08 (+8.32600764660522313269101537926539470E-03L)
#define B09 (-1.99407384882605586705979504567947007E-04L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*(A08+z*A09))))))))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*(B07+z*(B08+z*B09))))))))

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator.                                           */
#define A00 (+1.66666666666666666631E-01L)
#define A01 (-4.16313987993683104320E-01L)
#define A02 (+3.69068046323246813704e-01L)
#define A03 (-1.36213932016738603108E-01L)
#define A04 (+1.78324189708471965733E-02L)
#define A05 (-2.19216428382605211588E-04L)
#define A06 (-7.10526623669075243183E-06L)

/*  Coefficients for the denominator.                                         */
#define B00 (+1.00000000000000000000E+00L)
#define B01 (-2.94788392796209867269E+00L)
#define B02 (+3.27309890266528636716E+00L)
#define B03 (-1.68285799854822427013E+00L)
#define B04 (+3.90699412641738801874E-01L)
#define B05 (-3.14365703596053263322E-02L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*A06)))))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) B00+z*(B01+z*(B02+z*(B03+z*(B04+z*B05))))

#endif
/*  End of 80-bit extended / portable version.                                */

/*  The constant Pi / 2.                                                      */
#define TMPL_PI_BY_TWO (+1.5707963267948966192313216916397514420985846996L)

/*  Function for computing asin(x) for 0.5 <= x < 1.0.                        */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Arcsin_Tail_End(long double x)
{
    /*  Rational function is computed in terms of (1 - x)/2.                  */
    const long double z = 0.5L*(1.0L - x);

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const long double p = TMPL_NUM_EVAL(z);
    const long double q = TMPL_DEN_EVAL(z);

    /*  p(z) / q(z) is the rational minimax approximant for                   *
     *  (asin(sqrt(z)) - sqrt(z)) / z^{3/2}. We need to multiply by z^{3/2}.  */
    const long double r = z*p/q;
    const long double s = tmpl_LDouble_Sqrt(z);
    const long double t = r*s;

    /*  We now have asin(sqrt(z)) - sqrt(z). We need pi/2 - 2*asin(sqrt(z)).  */
    return TMPL_PI_BY_TWO - 2.0L*(s + t);
}
/*  End of tmpl_LDouble_Arcsin_Tail_End.                                      */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
