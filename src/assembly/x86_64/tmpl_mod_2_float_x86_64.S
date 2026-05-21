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
 *      Contains code for computing remainder after division by 2.            *
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
 *      Compute x - 2 * trunc(x / 2). trunc(x / 2) is computed with roundss.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 6, 2024                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Single-precision mod 2 function for x86_64 machines.                      */
ASM_BEGIN(tmpl_Float_Mod_2)

    /*  We compute x mod 2 by returning x - 2 * trunc(x / 2). We need to save *
     *  the input value "x" for this final subtraction. Copy xmm0 into xmm1.  *
     *  That is, set y = x.                                                   */
    movss %xmm0, %xmm1

    /*  Set y = 0.5 * x.                                                      */
    mulss .TMPL_FLOAT_MOD2_HALF_AS_HEX(%rip), %xmm1

    /*  Compute y = trunc(0.5 * x). roundss $11 is round-to-zero, or truncate.*/
    roundss $11, %xmm1, %xmm1

    /*  Compute y = 2.0 * trunc(0.5 * x) = trunc(0.5 * x) + trunc(0.5 * x).   */
    addss %xmm1, %xmm1

    /*  Compute y = x - 2.0 * trunc(0.5 * x). This is x mod 2.                */
    subss %xmm1, %xmm0

    /*  Return y = x - 2.0 * trunc(0.5 * x).                                  */
    ret

/*  The hexadecimal representation (IEEE-754 format) of x = 0.5.              */
.TMPL_FLOAT_MOD2_HALF_AS_HEX:
    .long 0x3F000000

ASM_END(tmpl_Float_Mod_2)
