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
 *                        tmpl_sinpi_maclaurin_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of sin(pi x) at single precision.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_SinPi_Maclaurin                                            *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of sin(pi x) for small values x.        *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sin_pix (float):                                                      *
 *          The Maclaurin series of sin(pi x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \        (-1)^n pi^{2n+1}                           *
 *          sin(pi x) =   /        ---------------- * x^{2n+1}                *
 *                        -----         (2n+1)!                               *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first 3 terms (0 <= n <= 2) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 24, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SINPI_MACLAURIN_FLOAT_H
#define TMPL_SINPI_MACLAURIN_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the Maclaurin series at single precision.                */
#define A0 (3.1415926535897932384626433832795028841972E+00F)
#define A1 (-5.1677127800499700292460525111835658670375E+00F)
#define A2 (2.5501640398773454438561775836952967206692E+00F)

/*  Maclaurin series for sin(pi x), single precision, to 5 terms.             */
TMPL_INLINE_DECL
float tmpl_Float_SinPi_Maclaurin(float x)
{
    /*  Declare necessary variables.                                          */
    const float x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0 + x2*(A1 + x2*A2));
}
/*  End of tmpl_Float_SinPi_Maclaurin.                                        */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
