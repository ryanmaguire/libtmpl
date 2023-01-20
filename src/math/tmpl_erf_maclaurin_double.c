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
 *                          tmpl_erf_maclaurin_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of erf(x) at double precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Erf_Maclaurin                                             *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of erf(x) for small values x.           *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      erf_x (double):                                                       *
 *          The Maclaurin series of erf(x).                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                             infty                                          *
 *                             -----                                          *
 *                      2      \        (-1)^n                                *
 *          erf(x) = --------  /      ----------- * x^{2n+1}                  *
 *                   sqrt(pi)  -----  (2n + 1) n!                             *
 *                             n = 0                                          *
 *                                                                            *
 *      Use the first 7 terms (0 <= n <= 6) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for small values. For |x| < 0.125 this function is      *
 *      accurate to double precision (10^-16 relative error). The larger      *
 *      the input is, the worse the error. By the alternating series theorem, *
 *      the absolute error is bounded by (1/75600)*|x|^15.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2023                                              *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support is not requested.                         */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.1283791670955125738961589031215451716881012586580E+00)
#define A01 (-3.7612638903183752463205296770718172389603375288600E-01)
#define A02 (+1.1283791670955125738961589031215451716881012586580E-01)
#define A03 (-2.6866170645131251759432354836227265992573839491857E-02)
#define A04 (+5.2239776254421878421118467737108572763338021234167E-03)
#define A05 (-8.5483270234508528325466583569814028158189489292273E-04)
#define A06 (+1.2055332981789664251027338708563516791539543361731E-04)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*A06)))))

/*  Function for computing erf(x) via a Maclaurin series.                     */
double tmpl_Double_Erf_Maclaurin(double x)
{
    /*  The polynomial is odd, in terms of x^{2n+1}. Compute x^2.             */
    const double x2 = x*x;

    /*  Evaluate the polynomial using Horner's method and return.             */
    const double poly = TMPL_POLY_EVAL(x2);
    return x*poly;
}
/*  End of tmpl_Double_Erf_Maclaurin.                                         */

/*  #undef everything in case someone wants to #include this file.            */
#undef TMPL_POLY_EVAL
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
