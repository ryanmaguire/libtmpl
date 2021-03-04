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
 *                            tmpl_complex_cos                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex cosine function.             *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Cos:                                                      *
 *      tmpl_CDouble_Cos:                                                     *
 *      tmpl_CLDouble_Cos:                                                    *
 *  Purpose:                                                                  *
 *      Computes the complex cosine of a complex number.                      *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      cos_z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):            *
 *          The complex cosine of z.                                          *
 *  Method:                                                                   *
 *      Given two real numbers x and y, we have the following formula:        *
 *                                                                            *
 *          cos(x + y) = cos(x)cos(y) - sin(x)sin(y)                          *
 *                                                                            *
 *      We can then write:                                                    *
 *                                                                            *
 *          cos(z) = cos(x + iy) = cos(x)cos(iy) - sin(x)sin(iy)              *
 *                                                                            *
 *      Invoking the definition of the hyperbolic trig functions cosh and     *
 *      sinh, we obtain the following expression using real-valued functions: *
 *                                                                            *
 *          cos(z) = cos(x)cosh(y) - i sin(x)sinh(y)                          *
 *                                                                            *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
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
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/11/14: Ryan Maguire                                                  *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Soft freeze for alpha release of libtmpl.                             *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex cosine (ccosf equivalent).                       */
tmpl_ComplexFloat tmpl_CFloat_Cos(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float x, y, real, imag;
    tmpl_ComplexFloat cos_z;

    /*  Extract the real and imaginary parts from z.                          */
    x = tmpl_CFloat_Real_Part(z);
    y = tmpl_CFloat_Imag_Part(z);

    /*  The real part is cos(x)cosh(y).                                       */
    real = tmpl_Float_Cos(x) * tmpl_Float_Cosh(y);

    /*  And the imaginary part is -sin(x)sinh(y).                             */
    imag = -tmpl_Float_Sin(x) * tmpl_Float_Sinh(y);

    /*  Create the output and return.                                         */
    cos_z = tmpl_CFloat_Rect(real, imag);
    return cos_z;
}
/*  End of tmpl_CFloat_Cos.                                                   */

/*  Double precision complex cosine (ccos equivalent).                        */
tmpl_ComplexDouble tmpl_CDouble_Cos(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double x, y, real, imag;
    tmpl_ComplexDouble cos_z;

    /*  Extract the real and imaginary parts from z.                          */
    x = tmpl_CDouble_Real_Part(z);
    y = tmpl_CDouble_Imag_Part(z);

    /*  The real part is cos(x)cosh(y).                                       */
    real = tmpl_Double_Cos(x) * tmpl_Double_Cosh(y);

    /*  And the imaginary part is -sin(x)sinh(y).                             */
    imag = -tmpl_Double_Sin(x) * tmpl_Double_Sinh(y);

    /*  Create the output and return.                                         */
    cos_z = tmpl_CDouble_Rect(real, imag);
    return cos_z;
}
/*  End of tmpl_CDouble_Cos.                                                  */

/*  Long double precision complex cosine (ccosl equivalent).                  */
tmpl_ComplexLongDouble tmpl_CLDouble_Cos(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double x, y, real, imag;
    tmpl_ComplexLongDouble cos_z;

    /*  Extract the real and imaginary parts from z.                          */
    x = tmpl_CLDouble_Real_Part(z);
    y = tmpl_CLDouble_Imag_Part(z);

    /*  The real part is cos(x)cosh(y).                                       */
    real = tmpl_LDouble_Cos(x) * tmpl_LDouble_Cosh(y);

    /*  And the imaginary part is -sin(x)sinh(y).                             */
    imag = -tmpl_LDouble_Sin(x) * tmpl_LDouble_Sinh(y);

    /*  Create the output and return.                                         */
    cos_z = tmpl_CLDouble_Rect(real, imag);
    return cos_z;
}
/*  End of tmpl_CLDouble_Cos.                                                 */

