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
 *                          tmpl_leading_zeros_ulong                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for counting the number of leading zeros in an integer. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULong_Leading_Zeros                                              *
 *  Purpose:                                                                  *
 *      Computes the number of leading zeros in the binary representation     *
 *      of the input.                                                         *
 *  Arguments:                                                                *
 *      x (unsigned long int):                                                *
 *          A 64-bit integer.                                                 *
 *  Output:                                                                   *
 *      ctz_x (int):                                                          *
 *          The number of leading zeros in x (binary representation).         *
 *  Called Functions:                                                         *
 *      cmp:                                                                  *
 *          Performs a comparison.                                            *
 *      clz:                                                                  *
 *          Counts the number of leading zeros in a word.                     *
 *      csel:                                                                 *
 *          Conditional select, returns the first argument if condition is    *
 *          satisfied, and the second argument otherwise.                     *
 *  Method:                                                                   *
 *      Use clz on the input, but return zero if the input is zero.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 17, 2026                                                *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

/*  64-bit leading zeros function, aarch64 architecture, GAS syntax.          */
ASM_BEGIN(tmpl_ULong_Leading_Zeros)

    /*  Check if the input is zero. We set leading_zeros(0) = 0.              */
    cmp x0, 0

    /*  Count the number of leading zeros.                                    */
    clz x0, x0

    /*  Set count to zero if input is zero.                                   */
    csel w0, w0, wzr, ne

    /*  Return the count.                                                     */
    ret

ASM_END(tmpl_ULong_Leading_Zeros)
