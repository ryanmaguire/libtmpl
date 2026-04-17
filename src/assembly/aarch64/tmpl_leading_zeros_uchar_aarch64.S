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
 *                          tmpl_leading_zeros_uchar                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for counting the number of leading zeros in an integer. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UChar_Leading_Zeros                                              *
 *  Purpose:                                                                  *
 *      Computes the number of leading zeros in the binary representation     *
 *      of the input.                                                         *
 *  Arguments:                                                                *
 *      x (unsigned char):                                                    *
 *          An 8-bit integer.                                                 *
 *  Output:                                                                   *
 *      ctz_x (int):                                                          *
 *          The number of leading zeros in x (binary representation).         *
 *  Called Functions:                                                         *
 *      ands:                                                                 *
 *          Performs a bit-wise and, and sets flags.                          *
 *      clz:                                                                  *
 *          Counts the number of leading zeros in a word.                     *
 *      csel:                                                                 *
 *          Conditional select, returns the first argument if condition is    *
 *          satisfied, and the second argument otherwise.                     *
 *  Method:                                                                   *
 *      Zero out the junk bits of the word, keeping only the lower 8 bits     *
 *      and then count the number of leading zeros in the input.              *
 *      Special case, if the input is zero, return zero.                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 17, 2026                                                *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

/*  8-bit leading zeros function, aarch64 architecture, GAS syntax.           */
ASM_BEGIN(tmpl_UChar_Leading_Zeros)

    /*  Zero out the higher order bits of the word, ensure we are only        *
     *  examining the lower 8 bits using bit-wise and with 255 (8 ones's).    */
    ands w0, w0, #0xFF

    /*  Count the number of leading zeros.                                    */
    clz w0, w0

    /*  Set count to zero if input is zero.                                   */
    csel w0, w0, wzr, ne

    /*  Return the count.                                                     */
    ret

ASM_END(tmpl_UChar_Leading_Zeros)
