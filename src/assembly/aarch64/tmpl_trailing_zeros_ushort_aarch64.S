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
 *                         tmpl_trailing_zeros_ushort                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for counting the number of trailing zeros in an integer.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UShort_Trailing_Zeros                                            *
 *  Purpose:                                                                  *
 *      Computes the number of trailing zeros in the binary representation    *
 *      of the input.                                                         *
 *  Arguments:                                                                *
 *      x (unsigned short int):                                               *
 *          An 16-bit integer.                                                *
 *  Output:                                                                   *
 *      ctz_x (int):                                                          *
 *          The number of trailing zeros in x (binary representation).        *
 *  Called Functions:                                                         *
 *      ands:                                                                 *
 *          Performs a bit-wise and, and sets flags.                          *
 *      rbit:                                                                 *
 *          Performs a bit reversal on the input.                             *
 *      clz:                                                                  *
 *          Counts the number of leading zeros in a word.                     *
 *      csel:                                                                 *
 *          Conditional select, returns the first argument if condition is    *
 *          satisfied, and the second argument otherwise.                     *
 *  Method:                                                                   *
 *      Zero out the junk bits of the word, keeping only the lower 16 bits,   *
 *      flip the order, and then count the number of leading zeros in the     *
 *      input. Special case, if the input is zero, return zero.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 10, 2024                                             *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

/*  16-bit trailing zeros function, aarch64 architecture, GAS syntax.         */
ASM_BEGIN(tmpl_UShort_Trailing_Zeros)

    /*  Zero out the higher order bits of the word, ensure we are only        *
     *  examining the lower 16 bits using bit-wise and with 65535 (16 ones's).*/
    ands w0, w0, #0xFFFF

    /*  Reverse the order of the bits in the input.                           */
    rbit w1, w0

    /*  Count the number of leading zeros.                                    */
    clz w1, w1

    /*  Set count to zero if input is zero.                                   */
    csel w0, w1, wzr, ne

    /*  Return the count.                                                     */
    ret

ASM_END(tmpl_UShort_Trailing_Zeros)
