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
 *                         tmpl_config_epsilon_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes long double precision epsilon.                               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ldouble_epsilon                                                  *
 *  Purpose:                                                                  *
 *      Computes long double precision epsilon, the smallest power of 2 such  *
 *      that 1 != 1 + 2^-n.                                                   *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      epsilon (long double):                                                *
 *          Long double precision epsilon.                                    *
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
#ifndef TMPL_CONFIG_EPSILON_LDOUBLE_H
#define TMPL_CONFIG_EPSILON_LDOUBLE_H

#include "tmpl_config_globals.h"
#include "tmpl_config_check_ldouble_type.h"

/*  Compute long double precision epsilon.                                    */
static long double tmpl_ldouble_epsilon(void)
{
    /*  Long double is not as standardized as float and double. Some          *
     *  computers use 80-bit extended, some use quadruple precision, and some *
     *  simply have double and long double set to the same precision. The     *
     *  largest precision is 256-bit octuple precision, binary256, which has  *
     *  epsilon = 2^-236. We may hence safely compute epsilon after at most   *
     *  256 iterations.                                                       */
    const unsigned int max_iterations = 256U;

    /*  We will keep checking for 1 == 1 + 2^-n. Eventually we will obtain    *
     *  equality, and this will give us epsilon.                              */
    const long double x = 1.0L;
    long double dx = 0.5L;
    long double y = x + dx;

    /*  Dummy variable for looping.                                           */
    unsigned int n;

    /*  If long double is one of the usual types, we can use a pre-computed   *
     *  value. Determine how long double is implemented.                      */
    if (!tmpl_ldouble_type_has_been_checked)
        tmpl_check_ldouble_type();

    /*  For 64-bit double, 80-bit extended, 128-bit double-double, and        *
     *  128-bit quadruple we use pre-computed values.                         */
    switch (tmpl_ldouble_rep)
    {
        case tmpl_ldouble_64_bit_little_endian:
        case tmpl_ldouble_64_bit_big_endian:
            return 2.220446049250313080847263336181640625E-16L;

        case tmpl_ldouble_96_bit_extended_little_endian:
        case tmpl_ldouble_96_bit_extended_big_endian:
        case tmpl_ldouble_128_bit_extended_little_endian:
        case tmpl_ldouble_128_bit_extended_big_endian:
            return 1.08420217248550443400745280086994171142578125E-19L;

        case tmpl_ldouble_128_bit_doubledouble_little_endian:
        case tmpl_ldouble_128_bit_doubledouble_big_endian:
            return 4.93038065763132378382330353301741393545754021943139378E-32L;

        case tmpl_ldouble_128_bit_quadruple_little_endian:
        case tmpl_ldouble_128_bit_quadruple_big_endian:
            return 1.92592994438723585305597794258492731853810164821538820E-34L;

        default:
            break;
    }

    /*  Loop through powers of two and find long double precision epsilon.    */
    for (n = 0U; n < max_iterations; ++n)
    {
        /*  Once 1 == 1 + 2^-n, we've gone one iteration past epsilon. Return *
         *  2 * dx to obtain long double precision epsilon.                   */
        if (x == y)
            return 2.0L * dx;

        /*  Otherwise go to the next iteration.                               */
        dx = 0.5L * dx;
        y = x + dx;
    }

    /*  Could not find epsilon after 256 iterations. Return 64-bit epsilon.   */
    return 2.220446049250313080847263336181640625E-16L;
}
/*  End of tmpl_ldouble_epsilon.                                              */

#endif
/*  End of include guard.                                                     */
