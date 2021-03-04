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
 *      tmpl_CFloat_Divide_Real:                                              *
 *      tmpl_CDouble_Divide_Real:                                             *
 *      tmpl_CLDouble_Divide_Real:                                            *
 *  Purpose:                                                                  *
 *      Divides a real number by a complex one.                               *
 *                                                                            *
 *          div(x, z) = x / z                                                 *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (float/double/long double):                                         *
 *          A real number.                                                    *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      x_by_z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):           *
 *          The quotient x / z.                                               *
 *  Method:                                                                   *
 *      Use the fact that x / z = x * z^-1. The reciprocal formula for z      *
 *      yields:                                                               *
 *                                                                            *
 *          z^-1 = (a + ib)^-1 = (a - ib)/(a^2 + b^2)                         *
 *                                                                            *
 *      We then use complex multiplication with this value on z = a + ib:     *
 *                                                                            *
 *          x/z = x/(a + ib)                                                  *
 *              = x(a - ib)/(a^2 + b^2)                                       *
 *              = ax/(a^2 + b^2) - i bx/(a^2 + b^2)                           *
 *                                                                            *
 *  NOTES:                                                                    *
 *      No error check is performed on the inputs. If the denominator is zero *
 *      this should return NaN + i NaN on most systems since the resulting    *
 *      computation has a 0/0 in it.                                          *
 *                                                                            *
 *      Division is not commutative. tmpl_CDouble_Divide(x, z) returns        *
 *      x/z and NOT z/x. That is, we divide the first entry by the second.    *
 *      To divide a complex number by a real one, use the function            *
 *      tmpl_CDouble_Multiply_Real with 1/x and z.                            *
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
 *  and double x, you can just do x / z. Structs cannot be divided so we need *
 *  a function for computing this.                                            */

/*  Single precision complex division where one variable is real.             */
tmpl_ComplexFloat tmpl_CFloat_Divide_Real(float x, tmpl_ComplexFloat z)
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

    /*  We compute based on the fact that x/z = x * (z)^-1 and use the        *
     *  formula for the reciprocal of a complex number.                       */
    div_re =  x*real*denom;
    div_im = -x*imag*denom;

    /*  Use tmpl_CFloat_Rect to create the output and return.                 */
    div = tmpl_CFloat_Rect(div_re, div_im);
    return div;
}
/*  End of tmpl_CFloat_Divide_Real.                                           */

/*  Double precision complex division where one variable is real.             */
tmpl_ComplexDouble tmpl_CDouble_Divide_Real(double x, tmpl_ComplexDouble z)
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

    /*  We compute based on the fact that x/z = x * (z)^-1 and use the        *
     *  formula for the reciprocal of a complex number.                       */
    div_re =  x*real*denom;
    div_im = -x*imag*denom;

    /*  Use tmpl_CDouble_Rect to create the output and return.                */
    div = tmpl_CDouble_Rect(div_re, div_im);
    return div;
}
/*  End of tmpl_CDouble_Divide_Real.                                          */

/*  Long double precision complex division.                                   */
tmpl_ComplexLongDouble
tmpl_CLDouble_Divide_Real(long double x, tmpl_ComplexLongDouble z)
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

    /*  We compute based on the fact that x/z = x * (z)^-1 and use the        *
     *  formula for the reciprocal of a complex number.                       */
    div_re =  x*real*denom;
    div_im = -x*imag*denom;

    /*  Use tmpl_CLDouble_Rect and return output.                             */
    div = tmpl_CLDouble_Rect(div_re, div_im);
    return div;
}
/*  End of tmpl_CLDouble_Divide_Real.                                         */

