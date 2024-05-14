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
 *                       tmpl_complex_poly_eval_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates a polynomial with real coefficients at a complex number.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Poly_Eval_Real_Coeffs                                    *
 *  Purpose:                                                                  *
 *      Evaluates a polynomial with real coefficients at a complex number.    *
 *  Arguments:                                                                *
 *      coeffs (const tmpl_ComplexDouble * const):                            *
 *          The coefficients array for the polynomial.                        *
 *      degree (size_t):                                                      *
 *          The degree of the polynomial. There must be at least degree + 1   *
 *          elements in the coeffs array.                                     *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      p_z (tmpl_ComplexDouble):                                             *
 *          The polynomial evaluated at z.                                    *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial at the given point.    *
 *  Notes:                                                                    *
 *      For very large polynomials with varying sizes for the coefficients,   *
 *      error may accumulate as one performs the sum.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header file with complex data types and the function prototype.   *
 *  2.) stddef.h:                                                             *
 *          Standard library header file containing the size_t type.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *      Added float and long double support.                                  *
 *  2021/09/08: Ryan Maguire                                                  *
 *      Removed "exit" call. NULL pointer is now treated as zero polynomial,  *
 *      and the value "zero" is returned.                                     *
 *  2024/05/13: Ryan Maguire                                                  *
 *      Optimized and cleaned up. Name change. Moved float and long double    *
 *      versions to their own files.                                          *
 ******************************************************************************/

/*  Where the prototype is declared and where complex types are defined.      */
#include <libtmpl/include/tmpl_complex.h>

/*  size_t typedef provided here.                                             */
#include <stddef.h>

/*  Evaluates a polynomial of a complex argument with complex coefficients.   */
tmpl_ComplexDouble
tmpl_CDouble_Poly_Eval(const tmpl_ComplexDouble * const coeffs,
                       size_t degree, tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble poly;
    size_t n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Treat this as the zero polynomial and *
     *  return zero if it is.                                                 */
    if (!coeffs)
        return tmpl_CDouble_Zero;

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, we'll just return the      *
     *  zeroth coefficient (a constant polynomial).                           */
    if (degree == 0)
        return coeffs[0];

    /*  Set poly equal to a_{N}, where N is the degree.                       */
    poly = coeffs[degree];

    /*  Use Horner's method of polynomial evaluation.                         */
    for (n = 1; n <= degree; ++n)
    {
        /*  Current index for the coeffs array.                               */
        const size_t ind = degree - n;

        /*  Avoid overwriting, save the real part of poly.                    */
        const double re = poly.dat[0];

        /*  Compute poly = z*poly + a_{n} using complex multiplication.       */
        poly.dat[0] = re*z.dat[0] - z.dat[1]*poly.dat[1] + coeffs[ind].dat[0];
        poly.dat[1] = re*z.dat[1] + poly.dat[1]*z.dat[0] + coeffs[ind].dat[1];
    }

    return poly;
}
/*  End of tmpl_CDouble_Poly_Eval.                                            */
