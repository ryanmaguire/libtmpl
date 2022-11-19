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
 *                          tmpl_cbrt_taylor_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Taylor series of cbrt(x) at double precision at x = 1.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cbrt_Taylor                                               *
 *  Purpose:                                                                  *
 *      Computes the Taylor series of cbrt(x) for values near 1.              *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cbrt_x (double):                                                      *
 *          The Taylor series of cbrt(x).                                     *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *      Use the first 4 terms (0 <= n <= 3) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for values near 1.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 21, 2022                                              *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the Taylor series at x = 1.                              */
#define A0 (1.0000000000000000000000000000E+00)
#define A1 (3.3333333333333333333333333333E-01)
#define A2 (-1.1111111111111111111111111111E-01)
#define A3 (6.1728395061728395061728395061E-02)

/*  Function for computing the Taylor series of cbrt(x) at x = 1 to 4 terms.  */
double tmpl_Double_Cbrt_Taylor(double x)
{
    /*  The series is computed at x = 1. Shift the input.                     */
    const double xs = x - 1.0;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return A0 + xs*(A1 + xs*(A2 + xs*A3));
}
/*  End of tmpl_Double_Cbrt_Taylor.                                           */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
