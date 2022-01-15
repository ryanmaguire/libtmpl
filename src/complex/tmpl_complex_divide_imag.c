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
 *      tmpl_CFloat_Divide_Imag:                                              *
 *      tmpl_CDouble_Divide_Imag:                                             *
 *      tmpl_CLDouble_Divide_Imag:                                            *
 *  Purpose:                                                                  *
 *      Divides an imaginary number by a complex one.                         *
 *                                                                            *
 *          div(y, z) = iy / z                                                *
 *                                                                            *
 *  Arguments:                                                                *
 *      y (float/double/long double):                                         *
 *          An imaginary number.                                              *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      y_by_z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):           *
 *          The quotient iy / z.                                              *
 *  Method:                                                                   *
 *      Use the fact that y / z = y * z^-1. The reciprocal formula for z      *
 *      yields:                                                               *
 *                                                                            *
 *          z^-1 = (a + ib)^-1 = (a - ib)/(a^2 + b^2)                         *
 *                                                                            *
 *      We then use complex multiplication with this value on z = a + ib:     *
 *                                                                            *
 *          y/z = ic/(a + ib)                                                 *
 *              = ic(a - ib)/(a^2 + b^2)                                      *
 *              = bc/(a^2 + b^2) + i ac/(a^2 + b^2)                           *
 *                                                                            *
 *  NOTES:                                                                    *
 *      No error check is performed on the inputs. If the denominator is zero *
 *      this should return NaN + i NaN on most systems since the resulting    *
 *      computation has a 0/0 in it.                                          *
 *                                                                            *
 *      Division is not commutative. tmpl_CDouble_Divide(y, z) returns        *
 *      y/z and NOT z/y. That is, we divide the first entry by the second.    *
 *      To divide a complex number by an imaginary one, use the function      *
 *      tmpl_CDouble_Multiply_Imag with 1/y and z.                            *
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
 *  2021/02/16: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z   *
 *  and double y, you can just do y*_Complex_I / z. Structs cannot be divided *
 *  so we need a function for computing this.                                 */

/*  Single precision complex division where one variable is imaginary.        */
tmpl_ComplexFloat tmpl_CFloat_Divide_Imag(float y, tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat div;
    float real, imag, denom;
    float div_re, div_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real = tmpl_CFloat_Real_Part(z);
    imag = tmpl_CFloat_Imag_Part(z);

    /*  The denominator for both real and imaginary parts is |z|^2.           */
    denom = 1.0F / tmpl_CFloat_Abs_Squared(z);

    /*  We compute based on the fact that y/z = y * (z)^-1 and use the        *
     *  formula for the reciprocal of a complex number.                       */
    div_re = y*imag*denom;
    div_im = y*real*denom;

    /*  Use tmpl_CFloat_Rect to create the output and return.                 */
    div = tmpl_CFloat_Rect(div_re, div_im);
    return div;
}
/*  End of tmpl_CFloat_Divide_Imag.                                           */

/*  Double precision complex division where one variable is imaginary.        */
tmpl_ComplexDouble tmpl_CDouble_Divide_Imag(double y, tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble div;
    double real, imag, denom;
    double div_re, div_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real = tmpl_CDouble_Real_Part(z);
    imag = tmpl_CDouble_Imag_Part(z);

    /*  The denominator for both real and imaginary parts is |z|^2.           */
    denom = 1.0 / tmpl_CDouble_Abs_Squared(z);

    /*  We compute based on the fact that y/z = y * (z)^-1 and use the        *
     *  formula for the reciprocal of a complex number.                       */
    div_re = y*imag*denom;
    div_im = y*real*denom;

    /*  Use tmpl_CDouble_Rect to create the output and return.                */
    div = tmpl_CDouble_Rect(div_re, div_im);
    return div;
}
/*  End of tmpl_CDouble_Divide_Imag.                                          */

/*  Long double precision complex division.                                   */
tmpl_ComplexLongDouble
tmpl_CLDouble_Divide_Imag(long double y, tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble div;
    long double real, imag, denom;
    long double div_re, div_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real = tmpl_CLDouble_Real_Part(z);
    imag = tmpl_CLDouble_Imag_Part(z);

    /*  The denominator for both real and imaginary parts is |z1|^2.          */
    denom = 1.0L / tmpl_CLDouble_Abs_Squared(z);

    /*  We compute based on the fact that y/z = y * (z)^-1 and use the        *
     *  formula for the reciprocal of a complex number.                       */
    div_re = y*imag*denom;
    div_im = y*real*denom;

    /*  Use tmpl_CLDouble_Rect and return output.                             */
    div = tmpl_CLDouble_Rect(div_re, div_im);
    return div;
}
/*  End of tmpl_CLDouble_Divide_Imag.                                         */
