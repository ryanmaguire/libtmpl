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
 *                          tmpl_gcd_euclidean_char                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the GCD of signed integers.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Char_GCD_Euclidean                                               *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (signed char):                                                      *
 *          An integer.                                                       *
 *      n (signed char):                                                      *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (signed char):                                                    *
 *          The greatest common divisor of m and n.                           *
 *  Called Functions:                                                         *
 *      tmpl_integer.h:                                                       *
 *          tmpl_Char_Abs:                                                    *
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
 *  1.) tmpl_integer.h:                                                       *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 17, 2024                                                  *
 ******************************************************************************/

/*  Function prototype is found here.                                         */
#include <libtmpl/include/tmpl_integer.h>

/*  Function for computing the GCD of two signed integers.                    */
signed char tmpl_Char_GCD_Euclidean(signed char m, signed char n)
{
    /*  The GCD is non-negative. We compute the absolute values of the inputs *
     *  and then run the algorithm with those values.                         */
    signed char abs_m, abs_n;

    /*  Save a redundant absolute value. If m is zero, |m| isn't needed.      *
     *  Compute |n| and then check if m is zero.                              */
    abs_n = tmpl_Char_Abs(n);

    /*  Avoid a redundant computation. If m = 0, GCD(n, 0) = |n|.             */
    if (m == 0x00)
        return abs_n;

    /*  Since GCD must be non-negative, compute the absolute value of m.      */
    abs_m = tmpl_Char_Abs(m);

    /*  Apply the Euclidean GCD algorithm.                                    */
    while (abs_n != 0x00)
    {
        /*  We swap m and n in a bit. Save the current value of n.            */
        const signed char tmp = abs_n;

        /*  Euclidean reduction, compute mod n.                               */
        abs_m %= abs_n;

        /*  After m %=n we have m < n. Swap the values so that m is larger.   */
        abs_n = abs_m;
        abs_m = tmp;
    }

    return m;
}
/*  End of tmpl_Char_GCD_Euclidean.                                           */
