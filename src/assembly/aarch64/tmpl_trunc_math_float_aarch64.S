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
 *                              tmpl_trunc_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing truncation at single precision.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Truncate                                                   *
 *  Purpose:                                                                  *
 *      Computes y = trunc(x), the fractional part of the input x.            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      trunc_x (float):                                                      *
 *          The truncation of x at single precision.                          *
 *  Called Functions:                                                         *
 *      frintz                                                                *
 *  Method:                                                                   *
 *      Use frintz on the argument.                                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 10, 2024                                             *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

#ifdef __APPLE__
.section __TEXT, __text, regular, pure_instructions
.globl tmpl_Float_Truncate
.p2align ALIGN
#endif

ASM_BEGIN(tmpl_Float_Truncate)

    /*  frintz is Round-to-Zero (truncation). Compute y = trunc(x).           */
    frintz s0, s0

    /*  return y;                                                             */
    ret

ASM_END(tmpl_Float_Truncate)
