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
 *                            tmpl_two_prod_float                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the product of two floats with rounding error.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Two_Prod                                                   *
 *  Purpose:                                                                  *
 *      Evaluates the product of two float, with the rounding error.          *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *      y (float):                                                            *
 *          Another real number.                                              *
 *      out (float * TMPL_RESTRICT const):                                    *
 *          The rounded product x * y will be stored here.                    *
 *      err (float * TMPL_RESTRICT const):                                    *
 *          The error term, prod(x, y) - (x * y), is stored here.             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      We can skip the 2Prod algorithm by the casting to double. An IEEE-754 *
 *      double has a 52-bit mantissa, and a single precision number has 23    *
 *      bits. This means the product of two floats can fit exactly inside a   *
 *      double. We compute the product with error as follows:                 *
 *                                                                            *
 *          prod_exact = (double)x * (double)y                                *
 *          prod_round = (float)prod_exact                                    *
 *          prod_error = prod_exact - prod_round                              *
 *                                                                            *
 *      prod_round is stored in "out" and prod_error is stored in "err".      *
 *  Notes:                                                                    *
 *      1.) On compilers supporting the "restrict" keyword, out and err are   *
 *          declared as "restrict" pointers. This requires that out and err   *
 *          point to different locations. To properly use this function, the  *
 *          caller should do this regardless.                                 *
 *  References:                                                               *
 *      1.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          "Library for Double-Double and Quad-Double Arithmetic."           *
 *      2.) Schewchuk, J. (October 1997).                                     *
 *          "Adaptive Precision Floating-Point Arithmetic                     *
 *              and Fast Robust Geometric Predicates."                        *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305–363 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_cast.h:                                                          *
 *          Provides a helper macro for C vs. C++ compatibility with casting. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 24, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_PROD_FLOAT_H
#define TMPL_TWO_PROD_FLOAT_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_RESTRICT.                   */
#include <libtmpl/include/tmpl_config.h>

/*  Helper macros for C vs. C++ compatibility.                                */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Multiplication with rounding error at single precision.                   */
TMPL_INLINE_DECL
void
tmpl_Float_Two_Prod(float x,
                    float y,
                    float * TMPL_RESTRICT const out,
                    float * TMPL_RESTRICT const err)
{
    /*  Convert the inputs into doubles. The product will then be exact.      */
    const double x_double = TMPL_CAST(x, double);
    const double y_double = TMPL_CAST(y, double);

    /*  The mantissa of an IEEE-754 double is much larger than that of a      *
     *  float, so x*y can be computed exactly.                                */
    const double prod_exact = x_double * y_double;

    /*  The rounded product can be computed by casting back to float.         */
    const float prod_round = TMPL_CAST(prod_exact, float);

    /*  The error can be computed by subtracting.                             */
    const double prod_round_double = TMPL_CAST(prod_round, double);
    const double prod_error = prod_exact - prod_round_double;

    /*  "prod_round" has the rounded product, "prod_error" has the error.     *
     *  Convert this back to a float and return these two values.             */
    *out = prod_round;
    *err = TMPL_CAST(prod_error, float);
}
/*  End of tmpl_Float_Two_Prod.                                               */

#endif
/*  End of include guard.                                                     */
