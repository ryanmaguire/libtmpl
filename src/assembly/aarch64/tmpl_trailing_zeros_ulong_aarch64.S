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
 *                         tmpl_trailing_zeros_ulong                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for counting the number of trailing zeros in an integer.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULong_Trailing_Zeros                                             *
 *  Purpose:                                                                  *
 *      Computes the number of trailing zeros in the binary representation    *
 *      of the input.                                                         *
 *  Arguments:                                                                *
 *      x (unsigned long int):                                                *
 *          A 64-bit integer.                                                 *
 *  Output:                                                                   *
 *      ctz_x (int):                                                          *
 *          The number of trailing zeros in x (binary representation).        *
 *  Called Functions:                                                         *
 *      and:                                                                  *
 *          Performs a bit-wise and.                                          *
 *      rbit:                                                                 *
 *          Performs a bit reversal on the input.                             *
 *      clz:                                                                  *
 *          Counts the number of leading zeros in a word.                     *
 *  Method:                                                                   *
 *      Reverse the input and the compute the number of leading zeros. Return *
 *      the bit-wise and of this count with the number 63. If the input is    *
 *      non-zero, then (since the input can have no more than 63 trailing     *
 *      zeros) bit-wise and with 63 (which is 111111_2 in binary) has no      *
 *      effect. Otherwise, we have 1000000_2 & 0111111_2, which produces zero,*
 *      meaning trailing_zeros(0) = 0, as desired.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 10, 2024                                             *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

/*  64-bit trailing zeros function, aarch64 architecture, GAS syntax.         */
ASM_BEGIN(tmpl_ULong_Trailing_Zeros)

    /*  Reverse the order of the bits in the input.                           */
    rbit x8, x0

    /*  Count the number of leading zeros.                                    */
    clz x8, x8

    /*  If the input is zero, the number of leading zeros in the reversed     *
     *  word is 64, otherwise it is equal to the number of trailing zeros in  *
     *  the input. Since a non-zero input can have no more than 63 trailing   *
     *  zeros, if we perform a bit-wise AND with the current count and the    *
     *  number 63 (111111_2 in binary), we will get zero if the count is 64,  *
     *  and we will get the number of trailing zeros in the input otherwise.  *
     *  Perform bit-wise and between the count and 63 and save this value.    */
    and w0, w8, #0x3F

    /*  Return the count.                                                     */
    ret

ASM_END(tmpl_ULong_Trailing_Zeros)
