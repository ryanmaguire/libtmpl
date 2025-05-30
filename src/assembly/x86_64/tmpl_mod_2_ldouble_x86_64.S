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
 *                              tmpl_mod_2_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing remainder after divison by 2.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Mod_2                                                    *
 *  Purpose:                                                                  *
 *      Computes the remainder after division by 2.                           *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      x_mod_2 (long double):                                                *
 *          The remainder after division by 2 at long double precision.       *
 *  Method:                                                                   *
 *      Compute x - 2*trunc(x/2). trunc(x) is computed with frndint.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 6, 2024                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

ASM_BEGIN(tmpl_LDouble_Mod_2)
    fnstcw  -10(%rsp)
    fldt    8(%rsp)
    movzwl  -10(%rsp), %eax
    fld     %st(0)
    fmuls   .TMPL_LDOUBLE_MOD2_HALF_AS_HEX(%rip)
    orb     $12, %ah
    movw    %ax, -12(%rsp)
    fldcw   -12(%rsp)
    frndint
    fldcw   -10(%rsp)
    fadd    %st(0), %st
    fsubrp  %st, %st(1)
    ret
.TMPL_LDOUBLE_MOD2_HALF_AS_HEX:
    .long 0x3F000000
ASM_END(tmpl_LDouble_Mod_2)
