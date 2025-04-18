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
 *                         tmpl_fractional_part_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the fractional part of a real number at double precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Fractional_Part                                           *
 *  Purpose:                                                                  *
 *      Computes the fractional part of the input.                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      frac_x (double):                                                      *
 *          The fractional part of x at double precision.                     *
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
.globl EXT(tmpl_Double_Fractional_Part)
.p2align ALIGN
#endif

ASM_BEGIN(tmpl_Double_Fractional_Part)

    /*  frintz is Round-to-Zero (truncate function). Compute y = trunc(x).    */
    frintz d31, d0

    /*  The fractional part is the input minus the integer part. Compute.     */
    fsub d0, d0, d31

    /*  Return x - trunc(x).                                                  */
    ret

ASM_END(tmpl_Double_Fractional_Part)
