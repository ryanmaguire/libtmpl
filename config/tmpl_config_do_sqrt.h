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
 *                             tmpl_config_do_sqrt                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes sqrt at long double precision using Heron's method.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_do_sqrt                                                          *
 *  Purpose:                                                                  *
 *      Computes sqrt(x) at long double precision.                            *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (long double):                                                 *
 *          The square root of x.                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Iteratively use Heron's method, which is equivalent to Newton's       *
 *      method for the function f(y) = y^2 - x. The output is sqrt(x).        *
 *      Heron's method defines y_{n+1} from y_{n} via:                        *
 *                                                                            *
 *                        2                                                   *
 *                      y   - x                                               *
 *                       n                                                    *
 *          y    = y  - --------                                              *
 *           n+1    n     2 y                                                 *
 *                           n                                                *
 *                                                                            *
 *                    -          -                                            *
 *                 1 |        x   |                                           *
 *               = - |  y  + ---  |                                           *
 *                 2 |   n    y   |                                           *
 *                    -        n -                                            *
 *                                                                            *
 *      We lazily choose y_0 = 1 and apply this for 128 iterations.           *
 *      The convergence is quadratic, meaning for the real numbers we need    *
 *      to compute the square root of in config.c this method should converge *
 *      for any of the common implementations of long double (64-bit, 80-bit, *
 *      128-bit, or double-double).                                           *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) Using 128 iterations of Heron's method is overkill. For normal    *
 *          IEEE-754 float and double we need 16 and 31 iterations,           *
 *          respectively, to compute sqrt(epsilon). For 128-bit quadruple we  *
 *          need 62 iterations. 256-bit octuple requires 119 iterations, but  *
 *          at the time of this writing there are no 256-bit octuple long     *
 *          doubles in existence. Choosing 128 iterations is solely for the   *
 *          sake of future proofing the config file.                          *
 *      2.) This function is only used in the config.c file. libtmpl's actual *
 *          square root algorithms are orders of magnitude faster, but        *
 *          require the details provided by the config.c file. We have a      *
 *          chicken-and-egg scenario. This square root function is provided   *
 *          so that config.c has a sqrt that is free of any dependencies.     *
 *  References:                                                               *
 *      1.) Heath, Thomas (1921)                                              *
 *          A History of Greek Mathematics, Vol. 2                            *
 *          Oxford Clarendon Press                                            *
 *                                                                            *
 *          The history of Heron's method can be found here. Pages 320-344    *
 *          discuss Hero of Alexandria's book Metrica. In particular, Heron's *
 *          method is shown on page 324.                                      *
 *                                                                            *
 *      2.) Press, W., Teukolsky, S., Vetterling, W., Flannery, B. (2007)     *
 *          Numerical Recipes: The Art of Scientific Computing, Third Edition *
 *          Cambridge University Press                                        *
 *                                                                            *
 *          A description of Newton's method is found in chapter 9.           *
 *                                                                            *
 *      3.) Abramowitz, Milton and Stegun, Irene (1964)                       *
 *          Handbook of Mathematical Functions                                *
 *          Applied Mathematics Series Volume 55,                             *
 *          National Bureau of Standards                                      *
 *                                                                            *
 *          Standard reference for formulas on mathematical functions.        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/06: Ryan Maguire                                                  *
 *      Moved function to its own file.                                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_DO_SQRT_H
#define TMPL_CONFIG_DO_SQRT_H

/*  Computes sqrt(x) using Heron's method and without any dependencies.       */
static long double tmpl_do_sqrt(long double x)
{
    /*  Maximum number of iterations we apply for Heron's method. To compute  *
     *  sqrt(epsilon) with initial guess 1 we need to following number of     *
     *  iterations:                                                           *
     *                                                                        *
     *      type                  | epsilon  | iterations                     *
     *      ---------------------------------------------                     *
     *      32-bit single         | 1.19E-07 |         16                     *
     *      64-bit double         | 2.22E-16 |         31                     *
     *      80-bit extended       | 1.08E-19 |         36                     *
     *      128-bit double-double | 4.93E-32 |         58                     *
     *      128-bit quadruple     | 1.93E-34 |         62                     *
     *      256-bit octuple       | 9.06E-72 |        127                     *
     *                                                                        *
     *  I know of no hardware that implements 256-bit octuple, let alone a    *
     *  compiler that sets long double equal to 256-bit precision. Regardless *
     *  setting max_iterations = 128 means we can safely compute the square   *
     *  root of each of these values to the correct precision.                */
    const unsigned int max_iterations = 128U;

    /*  Our starting guess is just 1. Simple, but it works.                   */
    long double y = 1.0L;

    /*  Index for keeping track of the number of iterations performed.        */
    unsigned int n;

    /*  Loop through and iteratively perform Heron's method.                  */
    for (n = 0U; n < max_iterations; ++n)
        y = 0.5L * (y + x / y);

    /*  The convergence in Heron's method is quadratic. For most real numbers *
     *  one works with, y now very accurately approximates sqrt(x). This      *
     *  function is used in config.c to compute sqrt(epsilon). For such an    *
     *  input the error is bounded by 1 ULP.                                  */
    return y;
}
/*  End of tmpl_do_sqrt.                                                      */

#endif
/*  End of include guard.                                                     */
