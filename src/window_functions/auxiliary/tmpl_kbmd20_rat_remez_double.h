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
 *                        tmpl_kbmd20_rat_remez_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) for small x.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_KBMD20_Rat_Remez                                          *
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) using a        *
 *      rational Remez approximation for small arguments.                     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      kbmd20_x (double):                                                    *
 *          The modified Kaiser-Bessel window (alpha = 2) of x.               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the (10, 8) rational Remez approximation for the *
 *      modified Kaiser-Bessel window (alpha = 2) have been pre-computed on   *
 *      the interval [-1/4, 1/4]. Since the window is an even function, half  *
 *      of the coefficients are zero, meaning we only have 6 non-zero terms   *
 *      in the numerator and 5 non-zero terms in the denominator. The         *
 *      approximation is performed using Horner's method for the numerator    *
 *      and denominator, and then returning their ratio.                      *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 0.25.                      *
 *                                                                            *
 *      2.) This function assumes a normalized window of width 1 is being     *
 *          used on the interval [-1/2, 1/2].                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_KBMD20_RAT_REMEZ_DOUBLE_H
#define TMPL_KBMD20_RAT_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.9999999999999999366600378259771379869378926410852E-01)
#define A01 (-9.4212661861610618389182687877338447490565358937343E+00)
#define A02 (+3.2924950968533714211260399764822484280641871514011E+01)
#define A03 (-5.5478200884536421439946455007527188358710270248590E+01)
#define A04 (+4.5955380454711921805431324786962958768702779852283E+01)
#define A05 (-1.5523654895689552074358932031563523118063969102151E+01)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+2.2301555070371895676893883291386650151597404400153E+00)
#define B02 (+2.3384956231098968317299016143783847487680799293970E+00)
#define B03 (+1.4039036477276375600119534981510529794871571385465E+00)
#define B04 (+4.2233936108924244735545866013547998564883503796379E-01)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Computes the modified Kaiser-Bessel window via a rational Remez expansion.*/
TMPL_STATIC_INLINE
double tmpl_Double_KBMD20_Rat_Remez(const double x)
{
    /*  The polynomials are in terms of x^2. Compute.                         */
    const double x2 = x * x;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const double numer = TMPL_NUM_EVAL(x2);
    const double denom = TMPL_DEN_EVAL(x2);

    /*  The modified Kaiser-Bessel window is the ratio.                       */
    return numer / denom;
}
/*  End of tmpl_Double_KBMD20_Rat_Remez.                                      */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
