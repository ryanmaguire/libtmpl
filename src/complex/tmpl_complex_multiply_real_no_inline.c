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
 *                         tmpl_complex_multiply_real                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex multiplication where one         *
 *      variable is real.                                                     *
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
 *  2021/02/18: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z1  *
 *  and double _Complex z2, you can just do z1 * z2. Structs cannot be        *
 *  multiplied so we need a function for computing this.                      */

/*  Single precision complex multiplication where one variable is real.       */
tmpl_ComplexFloat tmpl_CFloat_Multiply_Real(float x, tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat prod;
    float real, imag;
    float prod_re, prod_im;

    /*  Extract the real and imaginary parts from the input.                  */
    real = tmpl_CFloat_Real_Part(z);
    imag = tmpl_CFloat_Imag_Part(z);

    /*  The product simply multiplies the real number with the components     *
     *  of the complex one.                                                   */
    prod_re = x*real;
    prod_im = x*imag;

    /*  Create the output from prod_re and prod_im and return.                */
    prod = tmpl_CFloat_Rect(prod_re, prod_im);
    return prod;
}
/*  End of tmpl_CFloat_Multiply_Real.                                         */

/*  Double precision complex multiplication where one variable is real.       */
tmpl_ComplexDouble tmpl_CDouble_Multiply_Real(double x, tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble prod;
    double real, imag;
    double prod_re, prod_im;

    /*  Extract the real and imaginary parts from the input.                  */
    real = tmpl_CDouble_Real_Part(z);
    imag = tmpl_CDouble_Imag_Part(z);

    /*  The product simply multiplies the real number with the components     *
     *  of the complex one.                                                   */
    prod_re = x*real;
    prod_im = x*imag;

    /*  Create the output from prod_re and prod_im and return.                */
    prod = tmpl_CDouble_Rect(prod_re, prod_im);
    return prod;
}
/*  End of tmpl_CDouble_Multiply_Real.                                        */

/*  Double precision complex multiplication where one variable is real.       */
tmpl_ComplexLongDouble
tmpl_CLDouble_Multiply_Real(long double x, tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble prod;
    long double real, imag;
    long double prod_re, prod_im;

    /*  Extract the real and imaginary parts from the input.                  */
    real = tmpl_CLDouble_Real_Part(z);
    imag = tmpl_CLDouble_Imag_Part(z);

    /*  The product simply multiplies the real number with the components     *
     *  of the complex one.                                                   */
    prod_re = x*real;
    prod_im = x*imag;

    /*  Create the output from prod_re and prod_im and return.                */
    prod = tmpl_CLDouble_Rect(prod_re, prod_im);
    return prod;
}
/*  End of tmpl_CLDouble_Multiply_Real.                                       */
