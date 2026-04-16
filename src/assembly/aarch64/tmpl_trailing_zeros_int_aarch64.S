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
 *                          tmpl_trailing_zeros_int                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for counting the number of trailing zeros in an integer.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Int_Trailing_Zeros                                               *
 *  Purpose:                                                                  *
 *      Computes the number of trailing zeros in the binary representation    *
 *      of the input.                                                         *
 *  Arguments:                                                                *
 *      x (signed int):                                                       *
 *          A 32-bit integer.                                                 *
 *  Output:                                                                   *
 *      ctz_x (int):                                                          *
 *          The number of trailing zeros in x (binary representation).        *
 *  Called Functions:                                                         *
 *      rbit:                                                                 *
 *          Performs a bit reversal on the input.                             *
 *      clz:                                                                  *
 *          Counts the number of leading zeros in a word.                     *
 *      cmp:                                                                  *
 *          Performs a comparison.                                            *
 *      csel:                                                                 *
 *          Conditional select, returns the first argument if condition is    *
 *          satisfied, and the second argument otherwise.                     *
 *  Method:                                                                   *
 *      if the input is zero, return zero. Otherwise, flip the bit order of   *
 *      the input and then count the number of leading zeros.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 10, 2024                                             *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

/*  32-bit trailing zeros function, aarch64 architecture, GAS syntax.         */
ASM_BEGIN(tmpl_Int_Trailing_Zeros)

    /*  Reverse the order of the bits in the input.                           */
    rbit w1, w0

    /*  Check if the input is zero.                                           */
    cmp w0, 0

    /*  Count the number of leading zeros.                                    */
    clz w1, w1

    /*  Set count to zero if input is zero.                                   */
    csel w0, w1, w0, ne

    /*  Return the count.                                                     */
    ret

ASM_END(tmpl_Int_Trailing_Zeros)
