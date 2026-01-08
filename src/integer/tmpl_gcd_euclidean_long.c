/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                          tmpl_gcd_euclidean_long                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the GCD of signed integers.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Long_GCD_Euclidean                                               *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (const signed long int):                                            *
 *          An integer.                                                       *
 *      n (const signed long int):                                            *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (signed long int):                                                *
 *          The greatest common divisor of m and n.                           *
 *  Called Functions:                                                         *
 *      src/integer/                                                          *
 *          tmpl_Long_Abs:                                                    *
 *              Computes the absolute value of an integer.                    *
 *  Method:                                                                   *
 *      This computes the GCD using the Euclidean algorithm. We iteratively   *
 *      compute:                                                              *
 *                                                                            *
 *          m = m mod n                                                       *
 *                                                                            *
 *      And then swap the variables so that m > n is true. The algorithm      *
 *      terminates once n is zero.                                            *
 *  Notes:                                                                    *
 *      1.) This algorithm is often slower than the binary and mixed-binary   *
 *          algorithms for the GCD, but this is highly sensitive to the       *
 *          compiler used and the underlying architecture.                    *
 *                                                                            *
 *      2.) The GCD is defined to be non-negative. For negative inputs, the   *
 *          GCD of their absolute values is returned.                         *
 *                                                                            *
 *      3.) By definition, GCD(0, 0) = 0, GCD(n, 0) = n, and GCD(0, n) = n.   *
 *          This function follows these requirements.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_USE_INLINE macro.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 17, 2024                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/01/08: Ryan Maguire                                                  *
 *      Fixed bugs and typos, general cleanup, added forward declaration.     *
 ******************************************************************************/

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  Forward declaration / function prototype.                                 */
extern signed long int
tmpl_Long_GCD_Euclidean(const signed long int m, const signed long int n);

/*  The abs function is small enough to be inlined.                           */
#if TMPL_USE_INLINE == 1

/*  Location of the tmpl_Long_Abs function.                                   */
#include <libtmpl/include/inline/integer/tmpl_abs_long.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the abs function.         */
extern signed long int tmpl_Long_Abs(const signed long int n);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Function for computing the GCD of two signed integers.                    */
signed long int
tmpl_Long_GCD_Euclidean(const signed long int m, const signed long int n)
{
    /*  The GCD is non-negative. We compute the absolute values of the inputs *
     *  and then run the algorithm with those values.                         */
    signed long int abs_m, abs_n;

    /*  Save a redundant absolute value. If m is zero, |m| isn't needed.      *
     *  Compute |n| and then check if m is zero.                              */
    abs_n = tmpl_Long_Abs(n);

    /*  Avoid a redundant computation. If m = 0, then GCD(n, 0) = |n|.        */
    if (m == 0L)
        return abs_n;

    /*  Since GCD must be non-negative, compute the absolute value of m.      */
    abs_m = tmpl_Long_Abs(m);

    /*  Apply the Euclidean GCD algorithm.                                    */
    while (abs_n != 0L)
    {
        /*  We swap m and n in a bit. Save the current value of n.            */
        const signed long int tmp = abs_n;

        /*  Euclidean reduction, compute mod n.                               */
        abs_m %= abs_n;

        /*  After m %=n we have m < n. Swap the values so that m is larger.   */
        abs_n = abs_m;
        abs_m = tmp;
    }

    return abs_m;
}
/*  End of tmpl_Long_GCD_Euclidean.                                           */
