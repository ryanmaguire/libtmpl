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
 *                         tmpl_gcd_euclidean_ullong                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the GCD of unsigned integers.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULLong_GCD_Euclidean                                             *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (unsigned long long int):                                           *
 *          An integer.                                                       *
 *      n (unsigned long long int):                                           *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (unsigned long long int):                                         *
 *          The greatest common divisor of m and n.                           *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      This computes the GCD using the Euclidean algorithm. We iteratively   *
 *      compute:                                                              *
 *                                                                            *
 *          m = m mod n                                                       *
 *                                                                            *
 *      And then swap the variables so the m > n is true. The algorithm       *
 *      terminates once n is zero.                                            *
 *  Notes:                                                                    *
 *      This is significantly slower than the binary, or mixed-binary, GCD.   *
 *      It is included mostly for research purposes.                          *
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

/*  Function for computing the GCD of two unsigned integers.                  */
unsigned long long int
tmpl_ULLong_GCD_Euclidean(unsigned long long int m, unsigned long long int n)
{
    /*  Avoid a redundant computation. If m = 0, GCD(n, 0) = n.               */
    if (m == 0ULL)
        return n;

    /*  Apply the Euclidean GCD algorithm.                                    */
    while (n != 0ULL)
    {
        /*  We swap m and n in a bit. Save the current value of n.            */
        const unsigned long long int tmp = n;

        /*  Euclidean reduction, compute mod n.                               */
        m %= n;

        /*  After m %=n we have m < n. Swap the values so that m is larger.   */
        n = m;
        m = tmp;
    }

    return m;
}
/*  End of tmpl_ULLong_GCD_Euclidean.                                         */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */
