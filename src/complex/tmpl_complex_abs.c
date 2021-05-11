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
 *                            tmpl_complex_abs                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex modulus (absolute value).        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Abs:                                                      *
 *      tmpl_CDouble_Abs:                                                     *
 *      tmpl_CLDouble_Abs:                                                    *
 *  Purpose:                                                                  *
 *      Computes the absolute value, or modulus, of a complex number:         *
 *                                                                            *
 *          |z| = |x + iy| = sqrt(x^2 + y^2)                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_z (float/double/long double):                                     *
 *          The absolute value of z.                                          *
 *  Called Functions:                                                         *
 *      tmpl_Float_Sqrt         (tmpl_math.h)                                 *
 *      tmpl_Double_Sqrt        (tmpl_math.h)                                 *
 *      tmpl_LDouble_Sqrt       (tmpl_math.h)                                 *
 *          Computes the square root of a float/double/long double.           *
 *      tmpl_CFloat_Real_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Real_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Real_Part (tmpl_complex.h)                              *
 *          Returns the real part of a complex number.                        *
 *      tmpl_CFloat_Imag_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Imag_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Imag_Part (tmpl_complex.h)                              *
 *          Returns the imaginary part of a complex number.                   *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts of z and return sqrt(x^2 + y^2). *
 *  NOTES:                                                                    *
 *      This code is a fork of the code I wrote for rss_ringoccs.             *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing basic math functions.                      *
 *  2.) tmpl_complex.h:                                                       *
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
 *      Created file (Wellesley college for librssringoccs).                  *
 *  2020/12/01: Ryan Maguire                                                  *
 *      Added abs squared functions.                                          *
 *  2020/12/02: Ryan Maguire                                                  *
 *      Moved abs squared functions to their own file.                        *
 *      Frozen for rss_ringoccs v1.3.                                         *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from librssringoccs to libtmpl.                                *
 *      Edited code, made it compatibile with the rest of libtmpl. Removed    *
 *      "C99" mode. Removed complex.h as a dependency.                        *
 *      Soft freeze for alpha version of libtmpl.                             *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited license.                                                       *
 *  2021/05/11: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 ******************************************************************************/

/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are gven and where complex types are defined.        */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex abs function (cabsf equivalent).                 */
float tmpl_CFloat_Abs(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float real, imag, abs_value;

    /*  Extract the real and imaginary parts from the input complex number.   */
    real = tmpl_CFloat_Real_Part(z);
    imag = tmpl_CFloat_Imag_Part(z);

    /*  The absolute value is just sqrt(x^2 + y^2) so compute this.           */
    abs_value = tmpl_Float_Sqrt(real*real + imag*imag);
    return abs_value;
}
/*  End of tmpl_CFloat_Abs.                                                   */

/*  Double precision complex abs function (cabs equivalent).                  */
double tmpl_CDouble_Abs(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double real, imag, abs_value;

    /*  Extract the real and imaginary parts from the input complex number.   */
    real = tmpl_CDouble_Real_Part(z);
    imag = tmpl_CDouble_Imag_Part(z);

    /*  The absolute value is just sqrt(x^2 + y^2) so compute this.           */
    abs_value = tmpl_Double_Sqrt(real*real + imag*imag);
    return abs_value;
}
/*  End of tmpl_CDouble_Abs.                                                  */

/*  Long double precision complex abs function (cabsl equivalent).            */
long double tmpl_CLDouble_Abs(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double real, imag, abs_value;

    /*  Extract the real and imaginary parts from the input complex number.   */
    real = tmpl_CLDouble_Real_Part(z);
    imag = tmpl_CLDouble_Imag_Part(z);

    /*  The absolute value is just sqrt(x^2 + y^2) so compute this.           */
    abs_value = tmpl_LDouble_Sqrt(real*real + imag*imag);
    return abs_value;
}
/*  End of tmpl_CLDouble_Abs.                                                 */

