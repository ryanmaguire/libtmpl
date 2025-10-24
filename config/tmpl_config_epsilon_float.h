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
 *                         tmpl_config_epsilon_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes single precision epsilon.                                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_float_epsilon                                                    *
 *  Purpose:                                                                  *
 *      Computes single precision epsilon, the smallest power of 2 such that  *
 *      1 != 1 + 2^-n. This is usually epsilon = 2^-23 = 1.19x10^-7.          *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      epsilon (long double):                                                *
 *          Single precision epsilon.                                         *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compare 1 and 1 + 2^-n for equality. The largest n such that          *
 *      1 != 1 + 2^-n produces the value we want, epsilon = 2^-n.             *
 *  Notes:                                                                    *
 *      1.) This assumes float / double / long double are implemented as      *
 *          radix 2 numbers (i.e., in binary).                                *
 *      2.) The IEEE-754 binary256 is a 256-bit "octuple" precision float. It *
 *          has an epsilon value of 2^-236 = 9.06x10^-72. Because of this it  *
 *          is safe to stop our search after at most 256 steps.               *
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
#ifndef TMPL_CONFIG_EPSILON_FLOAT_H
#define TMPL_CONFIG_EPSILON_FLOAT_H

/*  Compute single precision epsilon.                                         */
static long double tmpl_float_epsilon(void)
{
    /*  Float is usually binary32, meaning after 23 iterations we will reach  *
     *  epsilon. Octuple requires 236 iterations. We set the maximum number   *
     *  of iterations to 256 to be (overly and unnecessarily) safe.           */
    const unsigned int max_iterations = 256U;

    /*  We will keep checking for 1 == 1 + 2^-n. Eventually we will obtain    *
     *  equality, and this will give us epsilon.                              */
    const float x = 1.0F;
    float dx = 0.5F;
    float y = x + dx;

    /*  Dummy variable for looping.                                           */
    unsigned int n;

    /*  Loop through powers of two and find single precision epsilon.         */
    for (n = 0U; n < max_iterations; ++n)
    {
        /*  Once 1 == 1 + 2^-n, we've gone one iteration past epsilon. Return *
         *  2 * dx to obtain single precision epsilon.                        */
        if (x == y)
            return (long double)(2.0F * dx);

        /*  Otherwise go to the next iteration.                               */
        dx = 0.5F * dx;
        y = x + dx;
    }

    /*  Could not find epsilon after 256 iterations. Return 32-bit epsilon.   */
    return 1.1920928955078125E-07L;
}
/*  End of tmpl_float_epsilon.                                                */

#endif
/*  End of include guard.                                                     */
