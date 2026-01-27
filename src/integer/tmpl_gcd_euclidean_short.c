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
 *                          tmpl_gcd_euclidean_short                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the GCD of signed integers.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Short_GCD_Euclidean                                              *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (const signed short int):                                           *
 *          An integer.                                                       *
 *      n (const signed short int):                                           *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (signed short int):                                               *
 *          The greatest common divisor of m and n.                           *
 *  Called Functions:                                                         *
 *      src/integer/                                                          *
 *          tmpl_Short_Abs:                                                   *
 *              Computes the absolute value of an integer.                    *
 *  Method:                                                                   *
 *      This computes the GCD using the Euclidean algorithm. We iteratively   *
 *      compute:                                                              *
 *                                                                            *
 *          m = m mod n                                                       *
 *                                                                            *
 *      And then swap the variables so that m > n is true. The algorithm      *
 *      terminates once one of them is zero.                                  *
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
 *  References:                                                               *
 *      1.) Klain, Daniel A. (2020)                                           *
 *          Essentials of Number Theory                                       *
 *          Preliminary Edition                                               *
 *                                                                            *
 *          Undergraduate level introduction to number theory.                *
 *          Euclid's algorithm follows from proposition 6.2.                  *
 *                                                                            *
 *      2.) Stein, William (2009)                                             *
 *          Elementary Number Theory: Primes, Congruences, and Secrets        *
 *          Springer Undergraduate Texts in Mathematics                       *
 *                                                                            *
 *          From the creator of SageMath, Euclid's algorithm is detailed      *
 *          in algorithm 1.1.13.                                              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_USE_INLINE macro.                 *
 *  2.) tmpl_max.h:                                                           *
 *          Header file containing the TMPL_MAX macro.                        *
 *  3.) tmpl_min.h:                                                           *
 *          Header file containing the TMPL_MIN macro.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 17, 2024                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/01/08: Ryan Maguire                                                  *
 *      Fixed bugs and typos, general cleanup, added forward declaration.     *
 *  2026/01/27: Ryan Maguire                                                  *
 *      Modified to avoid using swap. Small performance improvement.          *
 ******************************************************************************/

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  Forward declaration / function prototype.                                 */
extern signed short int
tmpl_Short_GCD_Euclidean(const signed short int m, const signed short int n);

/*  TMPL_MAX and TMPL_MIN macros found here.                                  */
#include <libtmpl/include/helper/tmpl_max.h>
#include <libtmpl/include/helper/tmpl_min.h>

/*  The abs function is small enough to be inlined.                           */
#if TMPL_USE_INLINE == 1

/*  Location of the tmpl_Short_Abs function.                                  */
#include <libtmpl/include/inline/integer/tmpl_abs_short.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the abs function.         */
extern signed short int tmpl_Short_Abs(const signed short int n);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Function for computing the GCD of two signed integers.                    */
signed short int
tmpl_Short_GCD_Euclidean(const signed short int m, const signed short int n)
{
    /*  Variables for the algorithm. We start with u > v and then iteratively *
     *  reduce using the Euclidean algorithm. We also reduce to non-negative  *
     *  integers since GCD(m, n) = GCD(|m|, |n|).                             */
    signed short int abs_m, abs_n, u, v;

    /*  Since GCD(m, n) = GCD(|m|, |n|), we may reduce m and n to positive    *
     *  by taking their absolute values. We can save a possibly redundant     *
     *  absolute value computation. If m is zero, then |m| isn't needed.      *
     *  Compute |n| and then check if m is zero.                              */
    abs_n = tmpl_Short_Abs(n);

    /*  Avoid a redundant computation. If m = 0, then GCD(n, 0) = |n|.        */
    if (m == 0L)
        return abs_n;

    /*  Similar computation for m, we use GCD(m, n) = GCD(|m|, |n|) to reduce *
     *  the arguments to positive. Compute |m| and work with that.            */
    abs_m = tmpl_Short_Abs(m);

    /*  Same check with n, GCD(0, m) = |m|.                                   */
    if (n == 0L)
        return abs_m;

    /*  Otherwise start the algorithm with u >= v.                            */
    u = TMPL_MAX(abs_m, abs_n);
    v = TMPL_MIN(abs_m, abs_n);

    /*  Apply the Euclidean GCD algorithm.                                    */
    while (1)
    {
        /*  We have u >= v, reduce by setting u = u mod v.                    */
        u %= v;

        /*  If u was a multiple of v before computing the modulus, then it is *
         *  now zero. The GCD is hence the current value of v.                */
        if (u == 0L)
            return v;

        /*  Otherwise we now have v > u and u is non-zero. Reduce again by    *
         *  setting v = v mod u.                                              */
        v %= u;

        /*  Same check as before, if v is now zero, then the GCD is u.        */
        if (v == 0L)
            return u;
    }
}
/*  End of tmpl_Short_GCD_Euclidean.                                          */
