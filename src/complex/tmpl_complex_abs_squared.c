/******************************************************************************
 *                                 LICENSE                                    *
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
 *                        tmpl_complex_abs_squared                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for f(z) = |z|^2.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Abs_Squared:                                              *
 *      tmpl_CDouble_Abs_Squared:                                             *
 *      tmpl_CLDouble_Abs_Squared:                                            *
 *  Purpose:                                                                  *
 *      Computes the square of the absolute value, f(z) = |z|^2:              *
 *                                                                            *
 *          f(z) = f(x + iy) = x^2 + y^2                                      *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_sq_z (float/double/long double):                                  *
 *          The square of the absolute value of z.                            *
 *  Called Functions:                                                         *
 *      tmpl_CFloat_Real_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Real_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Real_Part (tmpl_complex.h)                              *
 *          Returns the real part of a complex number.                        *
 *      tmpl_CFloat_Imag_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Imag_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Imag_Part (tmpl_complex.h)                              *
 *          Returns the imaginary part of a complex number.                   *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts of z and return x^2 + y^2.       *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
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
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Wrote routines for the complex abs squared function (Wellesley        *
 *      College for librssringoccs).                                          *
 *  2020/12/02: Ryan Maguire                                                  *
 *      Moved functions here from rss_ringoccs_complex_abs.c                  *
 *      Frozen for v1.3.                                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Edited to make it compatible with libtmpl.                            *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2021/05/11: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 ******************************************************************************/

/*  Where the prototypes are given and where complex types are defined.       */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision abs squared function.                                    */
float tmpl_CFloat_Abs_Squared(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float real, imag, abs_sq;

    /*  Extract the real and imaginary parts from the input complex number.   */
    real = tmpl_CFloat_Real_Part(z);
    imag = tmpl_CFloat_Imag_Part(z);

    /*  |z|^2 = x^2 + y^2 so compute this.                                    */
    abs_sq = real*real + imag*imag;
    return abs_sq;
}
/*  End of tmpl_CFloat_Abs_Squared.                                           */

/*  Double precision abs squared function.                                    */
double tmpl_CDouble_Abs_Squared(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double real, imag, abs_sq;

    /*  Extract the real and imaginary parts from the input complex number.   */
    real = tmpl_CDouble_Real_Part(z);
    imag = tmpl_CDouble_Imag_Part(z);

    /*  |z|^2 = x^2 + y^2 so compute this.                                    */
    abs_sq = real*real + imag*imag;
    return abs_sq;
}
/*  End of tmpl_CDouble_Abs_Squared.                                          */

/*  Long double precision abs squared function.                               */
long double tmpl_CLDouble_Abs_Squared(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double real, imag, abs_sq;

    /*  Extract the real and imaginary parts from the input complex number.   */
    real = tmpl_CLDouble_Real_Part(z);
    imag = tmpl_CLDouble_Imag_Part(z);

    /*  |z|^2 = x^2 + y^2 so compute this.                                    */
    abs_sq = real*real + imag*imag;
    return abs_sq;
}
/*  End of tmpl_CLDouble_Abs_Squared.                                         */
