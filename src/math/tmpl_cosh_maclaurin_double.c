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
 *                         tmpl_cosh_maclaurin_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of hyperbolic cosine.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cosh_Maclaurin                                            *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of cosh for small values x.             *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cosh_x (double):                                                      *
 *          The Maclaurin series of hyperbolic cosh.                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \          1                                        *
 *          cosh(x)   =   /        ----- * x^{2n}                             *
 *                        -----    (2n)!                                      *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first 4 terms (0 <= n <= 3) and compute.                      *
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
 *  Date:       October 25, 2022                                              *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the polynonial. They are 1 / (2n)!.                      */
#define A0 (1.00000000000000000000000000000E+00)
#define A1 (0.50000000000000000000000000000E+00)
#define A2 (4.16666666666666666666666666666E-02)
#define A3 (1.38888888888888888888888888888E-03)

/*  Maclaurin series of hyperbolic cosine to 3 terms.                         */
double tmpl_Double_Cosh_Maclaurin(double x)
{
    /*  The function is even and the series is in terms of x^2.               */
    const double x2 = x*x;

    /*  Compute the polynomial via Horner's method and return.                */
    return A0 + x2*(A1 + x2*(A2 + x2*A3));
}
/*  End of tmpl_Double_Cosh_Maclaurin.                                        */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
