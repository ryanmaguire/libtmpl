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
 *                              tmpl_cosh_ldouble                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes hyperbolic cosine at long double precision.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Cosh                                                     *
 *  Purpose:                                                                  *
 *      Computes the hyperbolic cosine of a number.                           *
 *                                                                            *
 *                     exp(x) + exp(-x)                                       *
 *          cosh(x) =  ----------------                                       *
 *                            2                                               *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number, the argument for cosh(x).                          *
 *  Output:                                                                   *
 *      cosh_x (long double):                                                 *
 *          The hyperbolic cosine of x.                                       *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *      Method:                                                               *
 *      Error:                                                                *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_LDouble_Exp:                                             *
 *                  Computes the exponential of a long double.                *
 *      Method:                                                               *
 *          Compute t = exp(x) and return (t + 1/t)/2.                        *
 *      Error:                                                                *
 *  Notes:                                                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 10, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/12/10 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 *  2022/11/03 (Ryan Maguire):                                                *
 *      Migrated to libtmpl from rss_ringoccs. Updated with IEEE-754 method.  *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS macro provided here.                             */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Long double precision hyperbolic cosine (coshl equivalent).               */
long double tmpl_LDouble_Cosh(long double x)
{
    /*  The definition of cosh(x) is [exp(x) + exp(-x)]/2, so return this. It *
     *  is computationally faster to compute exp(x) and then exp(-x) via the  *
     *  formula exp(-x) = 1/exp(x). This saves us from computing two          *
     *  exponentials at the cost of an extra division.                        */
    const long double exp_x = tmpl_LDouble_Exp(x);
    const long double exp_minus_x = 1.0L / exp_x;

    /*  Compute cosh from the two exponentials and return.                    */
    return 0.5L*(exp_x + exp_minus_x);
}
/*  End of tmpl_LDouble_Cosh.                                                 */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
