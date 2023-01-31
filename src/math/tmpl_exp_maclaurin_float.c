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
 *                          tmpl_exp_maclaurin_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of exp(x).                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Exp_Maclaurin                                              *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of exp for small values of x.           *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (float):                                                        *
 *          The Maclaurin series of exp.                                      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \        1   n                                      *
 *           exp(x)   =   /       --- x                                       *
 *                        -----    n!                                         *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first 5 terms (0 <= n <= 4) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 9, 2022                                              *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only used if inline support is not requested.                */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the polynomial. They are 1 / n!.                         */
#define A0 (1.000000000000000000000000000000000000000E+00F)
#define A1 (1.000000000000000000000000000000000000000E+00F)
#define A2 (5.000000000000000000000000000000000000000E-01F)
#define A3 (1.666666666666666666666666666666666666667E-01F)
#define A4 (4.166666666666666666666666666666666666667E-02F)

/*  Maclaurin series of exp to 5 terms.                                       */
float tmpl_Float_Exp_Maclaurin(float x)
{
    /*  Compute the polynomial via Horner's method and return.                */
    return A0 + x*(A1 + x*(A2 + x*(A3 + x*A4)));
}
/*  End of tmpl_Float_Exp_Maclaurin.                                          */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
