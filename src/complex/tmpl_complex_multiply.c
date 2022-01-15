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
 *                          tmpl_complex_multiply                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex multiplication.                  *
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
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z1  *
 *  and double _Complex z2, you can just do z1 * z2. Structs cannot be        *
 *  multiplied so we need a function for computing this.                      */

/*  Single precision complex multiplication.                                  */
tmpl_ComplexFloat
tmpl_CFloat_Multiply(tmpl_ComplexFloat z0, tmpl_ComplexFloat z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat prod;
    float real0, real1;
    float imag0, imag1;
    float prod_re, prod_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real0 = tmpl_CFloat_Real_Part(z0);
    real1 = tmpl_CFloat_Real_Part(z1);
    imag0 = tmpl_CFloat_Imag_Part(z0);
    imag1 = tmpl_CFloat_Imag_Part(z1);

    /*  The product uses the distributive law in combination with the fact    *
     *  that i^2 = -1. This gives us the following formulas:                  */
    prod_re = real0*real1 - imag0*imag1;
    prod_im = real0*imag1 + imag0*real1;

    /*  Create the output from prod_re and prod_im and return.                */
    prod = tmpl_CFloat_Rect(prod_re, prod_im);
    return prod;
}
/*  End of tmpl_CFloat_Multiply.                                              */

/*  Double precision complex multiplication.                                  */
tmpl_ComplexDouble
tmpl_CDouble_Multiply(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble prod;
    double real0, real1;
    double imag0, imag1;
    double prod_re, prod_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real0 = tmpl_CDouble_Real_Part(z0);
    real1 = tmpl_CDouble_Real_Part(z1);
    imag0 = tmpl_CDouble_Imag_Part(z0);
    imag1 = tmpl_CDouble_Imag_Part(z1);

    /*  The product uses the distributive law in combination with the fact    *
     *  that i^2 = -1. This gives us the following formulas:                  */
    prod_re = real0*real1 - imag0*imag1;
    prod_im = real0*imag1 + imag0*real1;

    /*  Create the output from prod_re and prod_im and return.                */
    prod = tmpl_CDouble_Rect(prod_re, prod_im);
    return prod;
}
/*  End of tmpl_CDouble_Multiply.                                             */

/*  Long double precision complex multiplication.                             */
tmpl_ComplexLongDouble
tmpl_CLDouble_Multiply(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble prod;
    long double real0, real1;
    long double imag0, imag1;
    long double prod_re, prod_im;

    /*  Extract the real and imaginary parts from the inputs.                 */
    real0 = tmpl_CLDouble_Real_Part(z0);
    real1 = tmpl_CLDouble_Real_Part(z1);
    imag0 = tmpl_CLDouble_Imag_Part(z0);
    imag1 = tmpl_CLDouble_Imag_Part(z1);

    /*  The product uses the distributive law in combination with the fact    *
     *  that i^2 = -1. This gives us the following formulas:                  */
    prod_re = real0*real1 - imag0*imag1;
    prod_im = real0*imag1 + imag0*real1;

    /*  Create the output from prod_re and prod_im and return.                */
    prod = tmpl_CLDouble_Rect(prod_re, prod_im);
    return prod;
}
/*  End of tmpl_CLDouble_Multiply.                                            */
