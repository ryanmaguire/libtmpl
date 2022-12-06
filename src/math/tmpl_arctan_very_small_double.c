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
 *                        tmpl_arctan_very_small_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) at double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arctan_Very_Small                                         *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) for very small values x.     *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (double):                                                      *
 *          The Maclaurin series of atan(x).                                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                      infty                                                 *
 *                      -----                                                 *
 *                      \         (-1)^n                                      *
 *          atan(x) =   /        -------- * x^{2n+1}                          *
 *                      -----    (2n + 1)                                     *
 *                      n = 0                                                 *
 *                                                                            *
 *      Use the first 6 terms (0 <= n <= 5) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for very small values. For |x| < 1/16 this function is  *
 *      accurate to double precision (10^-16 relative error). The larger      *
 *      the input is, the worse the error. By the alternating series theorem, *
 *      the absolute error is bounded by (1/13)*|x|^13.                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2022                                            *
 ******************************************************************************/

/*  TMPL_USE_INLINE macro is found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only compile this file if inline support has not been requested.          */
#if TMPL_USE_INLINE != 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the computation of the polynomial approximation. The     *
 *  coefficients for the Taylor series are 1 / (1 + 2n).                      */
#define A0 (1.00000000000000000000000000000E+00)
#define A1 (-3.33333333333333333333333333333E-01)
#define A2 (2.00000000000000000000000000000E-01)
#define A3 (-1.42857142857142857142857142857E-01)
#define A4 (1.11111111111111111111111111111E-01)
#define A5 (-9.09090909090909090909090909090E-02)

/*  Maclaurin expansion for atan at double precision for small values.        */
double tmpl_Double_Arctan_Very_Small(double x)
{
    /*  The series is in terms of x^{2n+1} = x*{x^2}^{n}. Compute x^2.        */
    const double x2 = x*x;

    /*  Use Horner's method to efficiently evaluate the polynomial.           */
    return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*(A4 + x2*A5)))));
}
/*  End of tmpl_Double_Arctan_Very_Small.                                     */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
