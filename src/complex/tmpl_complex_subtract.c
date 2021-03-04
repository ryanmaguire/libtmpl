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
 *                            tmpl_complex_subtract                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex subtraction.                     *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) rss_ringoccs_complex.h:                                               *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       November 30, 2020                                             *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z1  *
 *  and double _Complex z2, you can just do z1 + z2. Structs can't be added,  *
 *  so we need a function for computing the sum of two complex values.        */

/*  Single precision complex subtraction.                                     */
tmpl_ComplexFloat
tmpl_CFloat_Subtract(tmpl_ComplexFloat z0, tmpl_ComplexFloat z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat sum;
    float real0, real1;
    float imag0, imag1;
    float sum_re, sum_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real0 = tmpl_CFloat_Real_Part(z0);
    real1 = tmpl_CFloat_Real_Part(z1);
    imag0 = tmpl_CFloat_Imag_Part(z0);
    imag1 = tmpl_CFloat_Imag_Part(z1);

    /*  The sum of two complex numbers simply adds their components.          */
    sum_re = real0 - real1;
    sum_im = imag0 - imag1;

    /*  Create the output from sum_re and sum_im and return.                  */
    sum = tmpl_CFloat_Rect(sum_re, sum_im);
    return sum;
}
/*  End of tmpl_CFloat_Subtract.                                              */

/*  Double precision complex subtraction.                                     */
tmpl_ComplexDouble
tmpl_CDouble_Subtract(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble sum;
    double real0, real1;
    double imag0, imag1;
    double sum_re, sum_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real0 = tmpl_CDouble_Real_Part(z0);
    real1 = tmpl_CDouble_Real_Part(z1);
    imag0 = tmpl_CDouble_Imag_Part(z0);
    imag1 = tmpl_CDouble_Imag_Part(z1);

    /*  The sum of two complex numbers simply adds their components.          */
    sum_re = real0 - real1;
    sum_im = imag0 - imag1;

    /*  Create the output from sum_re and sum_im and return.                  */
    sum = tmpl_CDouble_Rect(sum_re, sum_im);
    return sum;
}
/*  End of tmpl_CDouble_Subtract.                                             */

/*  Long double precision complex subtraction.                                */
tmpl_ComplexLongDouble
tmpl_CLDouble_Subtract(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble sum;
    long double real0, real1;
    long double imag0, imag1;
    long double sum_re, sum_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real0 = tmpl_CLDouble_Real_Part(z0);
    real1 = tmpl_CLDouble_Real_Part(z1);
    imag0 = tmpl_CLDouble_Imag_Part(z0);
    imag1 = tmpl_CLDouble_Imag_Part(z1);

    /*  The sum of two complex numbers simply adds their components.          */
    sum_re = real0 - real1;
    sum_im = imag0 - imag1;

    /*  Create the output from sum_re and sum_im and return.                  */
    sum = tmpl_CLDouble_Rect(sum_re, sum_im);
    return sum;
}
/*  End of tmpl_CLDouble_Subtract.                                            */

