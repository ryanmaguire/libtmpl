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
 *                             tmpl_average_uchar                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes unsigned integer averages without overflow.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UChar_Average                                                    *
 *  Purpose:                                                                  *
 *      Computes the average, rounded down, of two unsigned chars.            *
 *  Arguments:                                                                *
 *      m (const unsigned char):                                              *
 *          An integer.                                                       *
 *      n (const unsigned char):                                              *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      avg (unsigned char):                                                  *
 *          The average of m and n, rounded down.                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If m and n are unsigned integers, then their sum can be computed      *
 *      using bit-wise AND and bit-wise XOR                                   *
 *                                                                            *
 *          m + n = 2 * (m & n) + (m ^ n)                                     *
 *                                                                            *
 *      m & n computes the bits common to m and n, and hence there are two    *
 *      copies of such bits in the sum. n ^ m computes the bits contained by  *
 *      one but not the other, and hence there is only one copy of these      *
 *      bits. The total sum is thus twice the bit-wise AND plus the bit-wise  *
 *      XOR. The average can be computed by bit shifting                      *
 *                                                                            *
 *          (n + m) / 2 = (n & m) + ((n ^ m) / 2)                             *
 *                      = (n & m) + ((n ^ m) >> 1)                            *
 *                                                                            *
 *      This final expression has the benefit of never producing an overflow  *
 *      in any of the intermediate steps, nor does one occur in the sum.      *
 *  References:                                                               *
 *      1.) Warren, Henry (2013)                                              *
 *          Hacker's Delight, Second Edition                                  *
 *          Addison-Wesley                                                    *
 *                                                                            *
 *          Chapter 2 contains basic bit tricks, and section 2.5 contains     *
 *          this algorithm verbatim.                                          *
 *                                                                            *
 *      2.) Dietz, Hank                                                       *
 *          MAGIC                                                             *
 *          https://aggregate.org/MAGIC/                                      *
 *                                                                            *
 *          A collection of algorithms, the averaging of unsigned integers    *
 *          is one of them.                                                   *
 *                                                                            *
 *      3.) HAKMEM                                                            *
 *          Beeler, M., Gosper, R. W., and Schroeppel, R.                     *
 *          MIT Artificial Intelligence Laboratory                            *
 *          https://w3.pppl.gov/~hammett/work/2009/AIM-239-ocr.pdf            *
 *                                                                            *
 *          A short description of the summation algorithm is provided in     *
 *          item 23 of the hack memo.                                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  2.) tmpl_integer.h:                                                       *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 28, 2026                                                 *
 ******************************************************************************/

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_integer.h>

/*  Function for averaging two unsigned chars, rounded down.                  */
TMPL_CONST_FUNC
unsigned char tmpl_UChar_Average(const unsigned char m, const unsigned char n)
TMPL_UNSEQUENCED
{
    /*  The summation algorithm gives m + n = 2 * (m & n) + (m ^ n), and      *
     *  hence the (rounded down) average is (m & n) + ((m ^ n) >> 1).         */
    return (m & n) + ((m ^ n) >> 1);
}
/*  End of tmpl_UChar_Average.                                                */
