/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
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
 *                        tmpl_complex_multiply_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex multiplication.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_USE_INLINE macro.                 *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only used if inline support is not requested.                */
#if TMPL_USE_INLINE != 1

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Two algorithms are offered. The standard one, and the Gauss-Karatsuba     *
 *  algorithm for complex multiplication.                                     */
#ifndef TMPL_COMPLEX_DOUBLE_MULTIPLY_ALGORITHM
#define TMPL_COMPLEX_DOUBLE_MULTIPLY_ALGORITHM 0
#endif

/*  Check the value of the macro. 0 corresponds to the classic method, and 1  *
 *  represents the Gauss-Karatsuba algorithm.                                 */
#if TMPL_COMPLEX_DOUBLE_MULTIPLY_ALGORITHM == 0

/*  In C99, since _Complex is a built-in data type, given double _Complex z1  *
 *  and double _Complex z2, you can just do z1 * z2. Structs cannot be        *
 *  multiplied so we need a function for computing this.                      */

/*  Double precision complex multiplication.                                  */
tmpl_ComplexDouble
tmpl_CDouble_Multiply(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble prod;

    /*  The product uses the distributive law in combination with the fact    *
     *  that i^2 = -1. This gives us the following formulas:                  */
    prod.dat[0] = z0.dat[0]*z1.dat[0] - z0.dat[1]*z1.dat[1];
    prod.dat[1] = z0.dat[0]*z1.dat[1] + z0.dat[1]*z1.dat[0];
    return prod;
}
/*  End of tmpl_CDouble_Multiply.                                             */

#else
/*  Else for #if TMPL_COMPLEX_DOUBLE_MULTIPLY_ALGORITHM == 0.                 */

/*  Double precision complex multiplication.                                  */
tmpl_ComplexDouble
tmpl_CDouble_Multiply(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble prod;

    /*  The Gauss-Karatsuba algorithm requires 3 multipications, instead of   *
     *  4, but needs more additions and subtractions.                         */
    const double k1 = z1.dat[0] * (z0.dat[0] + z0.dat[1]);
    const double k2 = z0.dat[0] * (z1.dat[1] - z1.dat[0]);
    const double k3 = z0.dat[1] * (z1.dat[0] + z1.dat[1]);
    prod.dat[0] = k1 - k3;
    prod.dat[1] = k1 + k2;
    return prod;
}
/*  End of tmpl_CDouble_Multiply.                                             */

#endif
/*  End of #if TMPL_COMPLEX_DOUBLE_MULTIPLY_ALGORITHM == 0.                   */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
