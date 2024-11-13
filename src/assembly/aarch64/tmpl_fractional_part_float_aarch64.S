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
 *                         tmpl_fractional_part_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the fractional part of a real number at single precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Fractional_Part                                            *
 *  Purpose:                                                                  *
 *      Computes the fractional part of the input.                            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      frac_x (float):                                                       *
 *          The fractional part of x at single precision.                     *
 *  Called Functions:                                                         *
 *      frintz:                                                               *
 *          Truncates a real number, or "rounds to zero."                     *
 *      fsub:                                                                 *
 *          Subtracts real numbers.                                           *
 *  Method:                                                                   *
 *      Compute x - trunc(x) and return.                                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 8, 2024                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

#ifdef __APPLE__
.section __TEXT, __text, regular, pure_instructions
.globl tmpl_Float_Fractional_Part
.p2align ALIGN
#endif

ASM_BEGIN(tmpl_Float_Fractional_Part)

    /*  frintz is Round-to-Zero (truncate function). Compute y = trunc(x).    */
    frintz s31, s0

    /*  The fractional part is the input minus the integer part. Compute.     */
    fsub s0, s0, s31

    /*  Return x - trunc(x).                                                  */
    ret

ASM_END(tmpl_Float_Fractional_Part)
