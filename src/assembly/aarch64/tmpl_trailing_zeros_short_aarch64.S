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

ASM_BEGIN(tmpl_Short_Trailing_Zeros)
    sxth    w0, w0          /* "Signed-Extend-Halfword", extends input.       */
    cmp     w0, 0
    csneg   w0, w0, w0, ge  /* Compute the absolute value of the input.       */
    and     w0, w0, 0xFFFF  /* Zero out all but the lower 16 bits.            */
    rbit    w0, w0          /* Reverse the order of the input.                */
    clz     w0, w0          /* Count the number of leading zeros.             */
    ret                     /* Return the count.                              */
ASM_END(tmpl_Short_Trailing_Zeros)

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
