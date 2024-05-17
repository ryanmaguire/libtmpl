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
 *                          tmpl_gcd_euclidean_llong                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the GCD of signed integers.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LLong_GCD_Euclidean                                              *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (signed long long int):                                             *
 *          An integer.                                                       *
 *      n (signed long long int):                                             *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (signed long long int):                                           *
 *          The greatest common divisor of m and n.                           *
 *  Called Functions:                                                         *
 *      tmpl_integer.h:                                                       *
 *          tmpl_LLong_Abs:                                                   *
 *              Computes the absolute value of an integer.                    *
 *  Method:                                                                   *
 *      This computes the GCD using the Euclidean algorithm. We iteratively   *
 *      compute:                                                              *
 *                                                                            *
 *          m = m mod n                                                       *
 *                                                                            *
 *      And then swap the variables so the m > n is true. The algorithm       *
 *      terminates once n is zero.                                            *
 *  Notes:                                                                    *
 *      1.) This is significantly slower than the binary, or mixed-binary,    *
 *          GCD. It is included mostly for research purposes.                 *
 *      2.) The GCD is defined to be non-negative. For negative inputs, the   *
 *          GCD of their absolute values is returned.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_inttype.h:                                                       *
 *          TMPL_HAS_LONGLONG macro defined here.                             *
 *  2.) tmpl_integer.h:                                                       *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 17, 2024                                                  *
 ******************************************************************************/

/*  The TMPL_HAS_LONGLONG macro is defined here.                              */
#include <libtmpl/include/tmpl_inttype.h>

/*  Only compile this if long long support is available.                      */
#if TMPL_HAS_LONGLONG == 1

/*  Function prototype is found here.                                         */
#include <libtmpl/include/tmpl_integer.h>

/*  Function for computing the GCD of two signed integers.                    */
signed long long int
tmpl_LLong_GCD_Euclidean(signed long long int m, signed long long int n)
{
    /*  The GCD is non-negative. We compute the absolute values of the inputs *
     *  and then run the algorithm with those values.                         */
    signed long long int abs_m, abs_n;

    /*  Save a redundant absolute value. If m is zero, |m| isn't needed.      *
     *  Compute |n| and then check if m is zero.                              */
    abs_n = tmpl_LLong_Abs(n);

    /*  Avoid a redundant computation. If m = 0, GCD(n, 0) = |n|.             */
    if (m == 0LL)
        return abs_n;

    /*  Since GCD must be non-negative, compute the absolute value of m.      */
    abs_m = tmpl_LLong_Abs(m);

    /*  Apply the Euclidean GCD algorithm.                                    */
    while (abs_n != 0LL)
    {
        /*  We swap m and n in a bit. Save the current value of n.            */
        const signed long long int tmp = abs_n;

        /*  Euclidean reduction, compute mod n.                               */
        abs_m %= abs_n;

        /*  After m %=n we have m < n. Swap the values so that m is larger.   */
        abs_n = abs_m;
        abs_m = tmp;
    }

    return m;
}
/*  End of tmpl_LLong_GCD_Euclidean.                                          */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */
