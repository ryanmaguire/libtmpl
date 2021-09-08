/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                     tmpl_complex_poly_complex_coeffs                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Efficiently compute polynomials of a complex variable using Horner's  *
 *      method. Two functions are provided allowing for real coefficients and *
 *      complex coefficients.                                                 *
 *  NOTES:                                                                    *
 *      These functions use "exit" to abort a computation if an error occurs. *
 *      This is to prevent the possibility of a segmentation fault, which     *
 *      often prints out a less-than-helpful error message. Improper use of   *
 *      this function will cause your program to crash (However, the error    *
 *      message will tell you why).                                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          The standard C library for input and output. This is needed for   *
 *          the "puts" function for printing error messages should the        *
 *          program fail.                                                     *
 *  2.) stdlib:                                                               *
 *          The C standard library header file. This contains the "exit"      *
 *          function which is used to terminate a program if an error occurs. *
 *  2.) tmpl_complex.h:                                                       *
 *          Header file where tmpl_ComplexDouble is defined, as well          *
 *          as the prototypes for the functions.                              *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
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
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Use Horner's method to compute a polynomial of a complex variable z with  *
 *  complex coefficients.                                                     */
tmpl_ComplexFloat
tmpl_CFloat_Poly_Complex_Coeffs(tmpl_ComplexFloat *coeffs,
                                unsigned int degree, tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat poly;
    unsigned int n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (!coeffs)
        return tmpl_CFloat_Zero;

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, we'll just return the      *
     *  zeroth coefficient (a constant polynomial).                           */
    if (degree == 0)
        return coeffs[0];

    /*  Set poly equal to a_{N}*z, where N is the degree of the polynomial.   */
    poly = tmpl_CFloat_Multiply(coeffs[degree], z);

    /*  Reset poly to a_{N}*z + a_{N-1}.                                      */
    poly = tmpl_CFloat_Add(poly, coeffs[degree-1]);

    /*  Use Horner's method of polynomial computation.                        */
    for (n=2; n<=degree; ++n)
    {
        poly = tmpl_CFloat_Multiply(z, poly);
        poly = tmpl_CFloat_Add(poly, coeffs[degree-n]);
    }

    return poly;
}
/*  End of tmpl_CFloat_Poly_Complex_Coeffs.                                   */

/*  Use Horner's method to compute a polynomial of a complex variable z with  *
 *  complex coefficients.                                                     */
tmpl_ComplexDouble
tmpl_CDouble_Poly_Complex_Coeffs(tmpl_ComplexDouble *coeffs,
                                 unsigned int degree, tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble poly;
    unsigned int n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (!coeffs)
        return tmpl_CDouble_Zero;

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, we'll just return the      *
     *  zeroth coefficient (a constant polynomial).                           */
    if (degree == 0)
        return coeffs[0];

    /*  Set poly equal to a_{N}*z, where N is the degree of the polynomial.   */
    poly = tmpl_CDouble_Multiply(coeffs[degree], z);

    /*  Reset poly to a_{N}*z + a_{N-1}.                                      */
    poly = tmpl_CDouble_Add(poly, coeffs[degree-1]);

    /*  Use Horner's method of polynomial computation.                        */
    for (n=2; n<=degree; ++n)
    {
        poly = tmpl_CDouble_Multiply(z, poly);
        poly = tmpl_CDouble_Add(poly, coeffs[degree-n]);
    }

    return poly;
}
/*  End of tmpl_CDouble_Poly_Complex_Coeffs.                                  */

/*  Use Horner's method to compute a polynomial of a complex variable z with  *
 *  complex coefficients.                                                     */
tmpl_ComplexLongDouble
tmpl_CLDouble_Poly_Complex_Coeffs(tmpl_ComplexLongDouble *coeffs,
                                  unsigned int degree, tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble poly;
    unsigned int n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (!coeffs)
        return tmpl_CLDouble_Zero;

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, we'll just return the      *
     *  zeroth coefficient (a constant polynomial).                           */
    if (degree == 0)
        return coeffs[0];

    /*  Set poly equal to a_{N}*z, where N is the degree of the polynomial.   */
    poly = tmpl_CLDouble_Multiply(coeffs[degree], z);

    /*  Reset poly to a_{N}*z + a_{N-1}.                                      */
    poly = tmpl_CLDouble_Add(poly, coeffs[degree-1]);

    /*  Use Horner's method of polynomial computation.                        */
    for (n=2; n<=degree; ++n)
    {
        poly = tmpl_CLDouble_Multiply(z, poly);
        poly = tmpl_CLDouble_Add(poly, coeffs[degree-n]);
    }

    return poly;
}
/*  End of tmpl_CLDouble_Poly_Complex_Coeffs.                                 */

