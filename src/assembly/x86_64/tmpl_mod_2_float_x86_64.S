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
 *                              tmpl_mod_2_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing remainder after divison by 2.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Mod_2                                                      *
 *  Purpose:                                                                  *
 *      Computes the remainder after division by 2.                           *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      x_mod_2 (float):                                                      *
 *          The remainder after division by 2 at single precision.            *
 *  Method:                                                                   *
 *      Compute x - 2*trunc(x/2). trunc(x) is computed with roundsd.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 6, 2024                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  The hexidecimal representation (IEEE-754 format) of x = 0.5.              */
.TMPL_FLOAT_MOD2_HALF_AS_HEX:
    .long 0x3F000000

ASM_BEGIN(tmpl_Float_Mod_2)
    push    %rbp
    mov     %rsp, %rbp
    sub     $16, %rsp
    movss   %xmm0, -4(%rbp)
    movss   -4(%rbp), %xmm0
    movss   %xmm0, -8(%rbp)
    movss   .TMPL_FLOAT_MOD2_HALF_AS_HEX(%rip), %xmm0
    mulss   -4(%rbp), %xmm0
    roundss $3, %xmm0, %xmm0
    movaps  %xmm0, %xmm1
    movss   -8(%rbp), %xmm0
    addss   %xmm1, %xmm1
    subss   %xmm1, %xmm0
    add     $16, %rsp
    pop     %rbp
    ret
ASM_END(tmpl_Float_Mod_2)

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
