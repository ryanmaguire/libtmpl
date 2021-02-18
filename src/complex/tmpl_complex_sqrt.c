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
 *                            tmpl_complex_sqrt                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex square root function.        *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Sqrt:                                                     *
 *      tmpl_CDouble_Sqrt:                                                    *
 *      tmpl_CLDouble_Sqrt:                                                   *
 *  Purpose:                                                                  *
 *      Computes the complex square root of a complex number.                 *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      sqrt_z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):           *
 *          The complex square root of z.                                     *
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
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/11/14: Ryan Maguire                                                  *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Added float and long double support.                                  *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex square root (csqrtf equivalent).                 */
tmpl_ComplexFloat tmpl_CFloat_Sqrt(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float sqrt_r, theta, real, imag;
    tmpl_ComplexFloat sqrt_z;

    /*  We need z in polar coordinates, so compute r and theta.               */
    sqrt_r = tmpl_Float_Sqrt(tmpl_CFloat_Abs(z));
    theta  = tmpl_CFloat_Argument(z);

    /*  Once in the form r*exp(i*theta), the square root is compute as        *
     *  sqrt(z) = sqrt(r) * exp(i*theta / 2). r is non-negative, so this is   *
     *  well defined for all z.                                               */
    real = sqrt_r * tmpl_Float_Cos(0.5F * theta);
    imag = sqrt_r * tmpl_Float_Sin(0.5F * theta);

    /*  Use rssringoccs_CFloatRect to compute and return sqrt_z.              */
    sqrt_z = tmpl_CFloat_Rect(real, imag);
    return sqrt_z;
}
/*  End of tmpl_CFloat_Sqrt.                                                  */

/*  Double precision complex square root (csqrt equivalent).                  */
tmpl_ComplexDouble tmpl_CDouble_Sqrt(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double sqrt_r, theta, real, imag;
    tmpl_ComplexDouble sqrt_z;

    /*  We need z in polar coordinates, so compute r and theta.               */
    sqrt_r = tmpl_Double_Sqrt(tmpl_CDouble_Abs(z));
    theta  = tmpl_CDouble_Argument(z);

    /*  Once in the form r*exp(i*theta), the square root is compute as        *
     *  sqrt(z) = sqrt(r) * exp(i*theta / 2). r is non-negative, so this is   *
     *  well defined for all z.                                               */
    real = sqrt_r * tmpl_Double_Cos(0.5*theta);
    imag = sqrt_r * tmpl_Double_Sin(0.5*theta);

    /*  Use rssringoccs_CDoubleRect to compute and return sqrt_z.             */
    sqrt_z = tmpl_CDouble_Rect(real, imag);
    return sqrt_z;
}
/*  End of tmpl_CDouble_Sqrt.                                                 */

/*  Double precision complex square root (csqrtl equivalent).                 */
tmpl_ComplexLongDouble tmpl_CLDouble_Sqrt(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double sqrt_r, theta, real, imag;
    tmpl_ComplexLongDouble sqrt_z;

    /*  We need z in polar coordinates, so compute r and theta.               */
    sqrt_r = tmpl_LDouble_Sqrt(tmpl_CLDouble_Abs(z));
    theta  = tmpl_CLDouble_Argument(z);

    /*  Once in the form r*exp(i*theta), the square root is compute as        *
     *  sqrt(z) = sqrt(r) * exp(i*theta / 2). r is non-negative, so this is   *
     *  well defined for all z.                                               */
    real = sqrt_r * tmpl_LDouble_Cos(0.5L * theta);
    imag = sqrt_r * tmpl_LDouble_Sin(0.5L * theta);

    /*  Use rssringoccs_CLDoubleRect to compute and return sqrt_z.            */
    sqrt_z = tmpl_CLDouble_Rect(real, imag);
    return sqrt_z;
}
/*  End of tmpl_CLDouble_Sqrt.                                                */

