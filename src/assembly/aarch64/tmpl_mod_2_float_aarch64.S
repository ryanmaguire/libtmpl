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
 *  Date:       November 8, 2024                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

#ifdef __APPLE__
.section __TEXT, __text, regular, pure_instructions
.globl EXT(tmpl_Float_Mod_2)
.p2align ALIGN
#endif

ASM_BEGIN(tmpl_Float_Mod_2)

    /*  Create constant 0.5.                                                  */
    fmov s31, 5.0e-1

    /*  Create constant 2.0.                                                  */
    fmov s30, 2.0e+0

    /*  y = 0.5*x;                                                            */
    fmul s31, s0, s31

    /*  y = trunc(0.5*x); frintz is round-to-zero (truncate).                 */
    frintz s31, s31

    /*  y = x - 2.0 * trunc(0.5 * x);                                         */
    fmsub s0, s31, s30, s0

    /* return y;                                                              */
    ret

ASM_END(tmpl_Float_Mod_2)
