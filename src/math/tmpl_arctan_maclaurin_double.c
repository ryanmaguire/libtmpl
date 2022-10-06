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
 *                        tmpl_arctan_maclaurin_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) at double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arctan_Maclaurin                                          *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) for small values x.          *
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
 *  Notes:                                                                    *
 *      Only accurate for small values. For |x| < 1/32, this function         *
 *      is accurate to double precision (10^-8 relative error). The larger    *
 *      the input is, the worse the error. By the alternating series theorem, *
 *      the absolute error is bounded by (1/11)*|x|^11.                       *
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

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the Maclaurin series at double precision.                */
#define A0 (1.00000000000000000000000000000E+00)
#define A1 (-3.33333333333333333333333333333E-01)
#define A2 (2.00000000000000000000000000000E-01)
#define A3 (-1.42857142857142857142857142857E-01)
#define A4 (1.11111111111111111111111111111E-01)
#define A5 (-9.09090909090909090909090909090E-02)
#define A6 (7.69230769230769230769230769231E-02)
#define A7 (-6.66666666666666666666666666667E-02)
#define A8 (5.88235294117647058823529411765E-02)

/*  Maclaurin series for arctan, double precision, to 9 terms.                */
double tmpl_Double_Arctan_Maclaurin(double x)
{
    /*  Declare necessary variables.                                          */
    const double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0+x2*(A1+x2*(A2+x2*(A3+x2*(A4+x2*(A5+x2*(A6+x2*(A7+x2*A8))))))));
}
/*  End of tmpl_Double_Arctan_Maclaurin.                                      */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7
#undef A8

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
