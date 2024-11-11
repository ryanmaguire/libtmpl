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

ASM_BEGIN(tmpl_Float_Mod_2)
    sub     $24, %rsp
    movss   %xmm0, 12(%rsp)
    mulss   .TMPL_FLOAT_MOD2_HALF_AS_HEX(%rip), %xmm0
    roundss $3, %xmm0, %xmm0
    movss   12(%rsp), %xmm1
    add     $24, %rsp
    addss   %xmm0, %xmm0
    subss   %xmm0, %xmm1
    movaps  %xmm1, %xmm0
    ret

/*  The hexidecimal representation (IEEE-754 format) of x = 0.5.              */
.TMPL_FLOAT_MOD2_HALF_AS_HEX:
    .long 0x3F000000
ASM_END(tmpl_Float_Mod_2)
