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
 *                            tmpl_complex_divide                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex division.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Divide:                                                   *
 *      tmpl_CDouble_Divide:                                                  *
 *      tmpl_CLDouble_Divide:                                                 *
 *  Purpose:                                                                  *
 *      Divides two complex numbers.                                          *
 *                                                                            *
 *          div(z0, z1) = z0 / z1                                             *
 *                                                                            *
 *  Arguments:                                                                *
 *      z0 (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):               *
 *          A complex number.                                                 *
 *      z1 (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):               *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      z0_by_z1 (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):         *
 *          The quotient z0 / z1.                                             *
 *  Method:                                                                   *
 *      Use the fact that z0 / z1 = z0 * z1^-1. The reciprocal formula for z1 *
 *      yields:                                                               *
 *                                                                            *
 *          z1^-1 = (c + id)^-1 = (c - id)/(c^2 + d^2)                        *
 *                                                                            *
 *      We then use complex multiplication with this value on z = a + ib:     *
 *                                                                            *
 *          z0/z1 = (a + ib)/(c + id)                                         *
 *                = (a + ib)(c - id)/(c^2 + d^2)                              *
 *                = (ac + bd)/(c^2 + d^2) + i (bc - ad)/(c^2 + d^2)           *
 *                                                                            *
 *  NOTES:                                                                    *
 *      No error check is performed on the inputs. If the denominator is zero *
 *      this should return NaN + i NaN on most systems since the resulting    *
 *      computation has a 0/0 in it.                                          *
 *                                                                            *
 *      Division is not commutative. tmpl_CDouble_Divide(z0, z1) returns      *
 *      z0/z1 and NOT z1/z0. That is, we divide the first entry by the second.*
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
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z0  *
 *  and double _Complex z1, you can just do z0 / z1. Structs cannot be        *
 *  divided so we need a function for computing this.                         */

/*  Single precision complex division.                                        */
tmpl_ComplexFloat tmpl_CFloat_Divide(tmpl_ComplexFloat z0, tmpl_ComplexFloat z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat div;
    float real0, imag0, real1, imag1, denom;
    float div_re, div_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real0 = tmpl_CFloat_Real_Part(z0);
    real1 = tmpl_CFloat_Real_Part(z1);
    imag0 = tmpl_CFloat_Imag_Part(z0);
    imag1 = tmpl_CFloat_Imag_Part(z1);

    /*  The denominator for both real and imaginary parts is |z1|^2.          */
    denom = 1.0F / tmpl_CFloat_Abs_Squared(z1);

    /*  We compute based on the fact that z0/z1 = z0 * (z1)^-1 and use the    *
     *  formula for the reciprocal of a complex number.                       */
    div_re = (real0*real1 + imag0*imag1)*denom;
    div_im = (imag0*real1 - real0*imag1)*denom;

    /*  Use tmpl_CFloat_Rect to create the output and return.                 */
    div = tmpl_CFloat_Rect(div_re, div_im);
    return div;
}
/*  End of tmpl_CFloat_Divide.                                                */

/*  Double precision complex division.                                        */
tmpl_ComplexDouble
tmpl_CDouble_Divide(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble div;
    double real0, imag0, real1, imag1, denom;
    double div_re, div_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real0 = tmpl_CDouble_Real_Part(z0);
    real1 = tmpl_CDouble_Real_Part(z1);
    imag0 = tmpl_CDouble_Imag_Part(z0);
    imag1 = tmpl_CDouble_Imag_Part(z1);

    /*  The denominator for both real and imaginary parts is |z1|^2.          */
    denom = 1.0 / tmpl_CDouble_Abs_Squared(z1);

    /*  We compute based on the fact that z0/z1 = z0 * (z1)^-1 and use the    *
     *  formula for the reciprocal of a complex number.                       */
    div_re = (real0*real1 + imag0*imag1)*denom;
    div_im = (imag0*real1 - real0*imag1)*denom;

    /*  Use tmpl_CDouble_Rect to create the output and return.                */
    div = tmpl_CDouble_Rect(div_re, div_im);
    return div;
}
/*  End of tmpl_CDouble_Divide.                                               */

/*  Long double precision complex division.                                   */
tmpl_ComplexLongDouble
tmpl_CLDouble_Divide(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble div;
    long double real0, imag0, real1, imag1, denom;
    long double div_re, div_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real0 = tmpl_CLDouble_Real_Part(z0);
    real1 = tmpl_CLDouble_Real_Part(z1);
    imag0 = tmpl_CLDouble_Imag_Part(z0);
    imag1 = tmpl_CLDouble_Imag_Part(z1);

    /*  The denominator for both real and imaginary parts is |z1|^2.          */
    denom = 1.0L / tmpl_CLDouble_Abs_Squared(z1);

    /*  We compute based on the fact that z0/z1 = z0 * (z1)^-1 and use the    *
     *  formula for the reciprocal of a complex number.                       */
    div_re = (real0*real1 + imag0*imag1)*denom;
    div_im = (imag0*real1 - real0*imag1)*denom;

    /*  Use tmpl_CLDouble_Rect and return output.                             */
    div = tmpl_CLDouble_Rect(div_re, div_im);
    return div;
}
/*  End of tmpl_CLDouble_Divide.                                              */
