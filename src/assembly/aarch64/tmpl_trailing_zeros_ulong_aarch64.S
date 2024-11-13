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
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

#ifdef __APPLE__
.section __TEXT, __text, regular, pure_instructions
.globl EXT(tmpl_ULong_Trailing_Zeros)
.p2align ALIGN
#endif

ASM_BEGIN(tmpl_ULong_Trailing_Zeros)

    rbit    x1, x0          /* Reverse the order of the input.                */
    cmp     x0, 0           /* Check if the input is zero.                    */
    clz     x1, x1          /* Count the number of leading zeros.             */
    csel    w0, w1, wzr, ne /* If the input was zero, return zero.            */
    ret                     /* Return the count.                              */

ASM_END(tmpl_ULong_Trailing_Zeros)
