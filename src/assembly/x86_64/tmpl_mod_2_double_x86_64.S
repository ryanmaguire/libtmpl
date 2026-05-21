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
 *                              tmpl_mod_2_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing remainder after division by 2.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Mod_2                                                     *
 *  Purpose:                                                                  *
 *      Computes the remainder after division by 2.                           *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      x_mod_2 (double):                                                     *
 *          The remainder after division by 2 at double precision.            *
 *  Method:                                                                   *
 *      Compute x - 2 * trunc(x / 2). trunc(x / 2) is computed with roundsd.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 6, 2024                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Double-precision mod 2 function for x86_64 machines.                      */
ASM_BEGIN(tmpl_Double_Mod_2)

    /*  We compute x mod 2 by returning x - 2 * trunc(x / 2). We need to save *
     *  the input value "x" for this final subtraction. Copy xmm0 into xmm1.  *
     *  That is, set y = x.                                                   */
    movsd %xmm0, %xmm1

    /*  Set y = 0.5 * x.                                                      */
    mulsd .TMPL_DOUBLE_MOD2_HALF_AS_HEX(%rip), %xmm1

    /*  Compute y = trunc(0.5 * x). roundsd $11 is round-to-zero, or truncate.*/
    roundsd $11, %xmm1, %xmm1

    /*  Compute y = 2.0 * trunc(0.5 * x) = trunc(0.5 * x) + trunc(0.5 * x).   */
    addsd %xmm1, %xmm1

    /*  Compute y = x - 2.0 * trunc(0.5 * x). This is x mod 2.                */
    subsd %xmm1, %xmm0

    /*  Return y = x - 2.0 * trunc(0.5 * x).                                  */
    ret

/*  The hexadecimal representation (IEEE-754 format) of x = 0.5.              */
    ASM_RODATA
    .p2align 3
.TMPL_DOUBLE_MOD2_HALF_AS_HEX:
    .quad 0x3FE0000000000000
    .text

ASM_END(tmpl_Double_Mod_2)
