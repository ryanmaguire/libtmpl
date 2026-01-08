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
 *                          tmpl_gcd_euclidean_ulong                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the GCD of unsigned integers.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULong_GCD_Euclidean                                              *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (const unsigned long int):                                          *
 *          An integer.                                                       *
 *      n (const unsigned long int):                                          *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (unsigned long int):                                              *
 *          The greatest common divisor of m and n.                           *
 *  Called Functions:                                                         *
 *      None.                                                                 *
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
 *      2.) By definition, GCD(0, 0) = 0, GCD(n, 0) = n, and GCD(0, n) = n.   *
 *          This function follows these requirements.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_max.h:                                                           *
 *          Header file containing the TMPL_MAX macro.                        *
 *  2.) tmpl_min.h:                                                           *
 *          Header file containing the TMPL_MIN macro.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 17, 2024                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/01/08: Ryan Maguire                                                  *
 *      Modified to avoid using swap. Small (~3%) performance improvement.    *
 ******************************************************************************/

/*  TMPL_MAX and TMPL_MIN macros found here.                                  */
#include <libtmpl/include/helper/tmpl_max.h>
#include <libtmpl/include/helper/tmpl_min.h>

/*  Function prototype / forward declaration.                                 */
extern unsigned long int
tmpl_ULong_GCD_Euclidean(const unsigned long int m, const unsigned long int n);

/*  Function for computing the GCD of two unsigned integers.                  */
unsigned long int
tmpl_ULong_GCD_Euclidean(const unsigned long int m, const unsigned long int n)
{
    /*  Variables for the algorithm. We start with u > v and then iteratively *
     *  reduce using the Euclidean algorithm.                                 */
    unsigned long int u, v;

    /*  Avoid a redundant computation. If m = 0, then GCD(n, 0) = n.          */
    if (m == 0UL)
        return n;

    /*  Same check with n, GCD(0, m) = m.                                     */
    if (n == 0UL)
        return m;

    /*  Otherwise start the algorithm with u >= v.                            */
    u = TMPL_MAX(m, n);
    v = TMPL_MIN(m, n);

    /*  Apply the Euclidean GCD algorithm.                                    */
    while (1)
    {
        /*  We have u >= v, reduce by setting u = u mod v.                    */
        u %= v;

        /*  If u was a multiple of v before computing the modulus, then it is *
         *  now zero. The GCD is hence the current value of v.                */
        if (u == 0UL)
            return v;

        /*  Otherwise we now have v > u and u is non-zero. Reduce again by    *
         *  setting v = v mod u.                                              */
        v %= u;

        /*  Same check as before, if v is now zero, then the GCD is u.        */
        if (v == 0UL)
            return u;
    }
}
/*  End of tmpl_ULong_GCD_Euclidean.                                          */
