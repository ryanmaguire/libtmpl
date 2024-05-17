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
 *                            tmpl_gcd_naive_uchar                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the GCD of unsigned integers.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UChar_GCD_Naive                                                  *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (unsigned char):                                                    *
 *          An integer.                                                       *
 *      n (unsigned char):                                                    *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (unsigned char):                                                  *
 *          The greatest common divisor of m and n.                           *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      This computes the GCD using the naive, or "by-hand", algorithm. Given *
 *      integers m and n, with n < m, if g = GCD(m, n), then g divides m and  *
 *      n, so we can write:                                                   *
 *                                                                            *
 *          m = ag                                                            *
 *          n = bg                                                            *
 *                                                                            *
 *      For some integers m and n. Subtracting, we get:                       *
 *                                                                            *
 *          m - n = ag - bg                                                   *
 *                = (a - b)g                                                  *
 *                                                                            *
 *      And hence g divides m - n as well. Moreover, g is the GCD of m - n    *
 *      and n. For if g' is a divisor of m - n and n, then:                   *
 *                                                                            *
 *          m - n = a'g'                                                      *
 *              n = b'g'                                                      *
 *                                                                            *
 *      for some integers a' and b'. Because of this, we see that             *
 *      g is a divisor of m as well, since:                                   *
 *                                                                            *
 *          m = (m - n) + n                                                   *
 *            = a'g' + b'g'                                                   *
 *            = (a' + b')g'                                                   *
 *                                                                            *
 *      Since g is the GCD of m and n we see that g' <= g. Hence g is the     *
 *      GCD of m - n and n. That is:                                          *
 *                                                                            *
 *          GCD(m, n) = GCD(n, m - n)                                         *
 *                                                                            *
 *      We update the variables by setting:                                   *
 *                                                                            *
 *          m' = max(n, m - n)                                                *
 *          n' = min(n, m - n)                                                *
 *                                                                            *
 *      And then repeat the process, noting that If n' = m', then             *
 *      GCD(m', n') = m'. Since max(n, m - n) <= max(m, n), we see that after *
 *      at most max(m, n) iterations we will have either n' = 0, m' = 0, or   *
 *      n' = m', and we can exit the algorithm.                               *
 *  Notes:                                                                    *
 *      This is very slow, running with worst-case complexity O(n). It is     *
 *      better to use the binary GCD (tmpl_UChar_GCD) which runs in O(log(n)).*
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_integer.h:                                                       *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 17, 2024                                                  *
 ******************************************************************************/

/*  Function prototype is found here.                                         */
#include <libtmpl/include/tmpl_integer.h>

/*  Function for computing the GCD of two unsigned integers.                  */
unsigned char tmpl_UChar_GCD_Naive(unsigned char m, unsigned char n)
{
    /*  Special case. The while loop can be infinite if one of the entries is *
     *  zero. GCD(n, 0) = n, so use this.                                     */
    if (m == 0x00U)
        return n;

    /*  Same check for n. If it is zero, GCD(m, 0) = m.                       */
    if (n == 0x00U)
        return m;

    /*  The "by-hand" algorithm repeatedly subtracts the smaller value from   *
     *  the larger value until the two are equal.                             */
    while (m != n)
    {
        /*  If m > n, we have GCD(m, n) = GCD(n, m - n), reducing the maximum *
         *  of the two values.                                                */
        if (m > n)
            m -= n;

        /*  If n > m, we have GCD(m, n) = GCD(m, n - m), similarly reducing   *
         *  the maximum of the two values.                                    */
        else
            n -= m;
    }

    return m;
}
/*  End of tmpl_UChar_GCD_Naive.                                              */
