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
 *                             tmpl_complex_polar                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for creating complex numbers using their     *
 *      polar representation.                                                 *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/01: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *      Added float and long double support.                                  *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Create a single precision complex number from its polar coordinates.      */
tmpl_ComplexFloat tmpl_CFloat_Polar(float r, float theta)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat z;
    float real, imag;

    /*  Use Euler's formula for the polar representation of a complex number. */
    real = r * tmpl_Float_Cos(theta);
    imag = r * tmpl_Float_Sin(theta);

    /*  Use tmpl_CDouble_Rect to compute and return.                          */
    z = tmpl_CFloat_Rect(real, imag);
    return z;
}
/*  End of tmpl_CFloat_Polar.                                                 */

/*  Create a double precision complex number from its polar coordinates.      */
tmpl_ComplexDouble tmpl_CDouble_Polar(double r, double theta)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble z;
    double real, imag;

    /*  Use Euler's formula for the polar representation of a complex number. */
    real = r * tmpl_Double_Cos(theta);
    imag = r * tmpl_Double_Sin(theta);

    /*  Use tmpl_CDouble_Rect to compute and return.                          */
    z = tmpl_CDouble_Rect(real, imag);
    return z;
}
/*  End of tmpl_CDouble_Polar.                                                */

/*  Create a long double precision complex number from its polar coordinates. */
tmpl_ComplexLongDouble tmpl_CLDouble_Polar(long double r, long double theta)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble z;
    long double real, imag;

    /*  Use Euler's formula for the polar representation of a complex number. */
    real = r * tmpl_LDouble_Cos(theta);
    imag = r * tmpl_LDouble_Sin(theta);

    /*  Use tmpl_CLDouble_Rect to compute and return.                         */
    z = tmpl_CLDouble_Rect(real, imag);
    return z;
}
/*  End of tmpl_CLDouble_Polar.                                               */

