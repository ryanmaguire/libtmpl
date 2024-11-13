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
 *                              tmpl_sqrt_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sqrt                                                      *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the largest integer less than or equal to x.    *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (double):                                                      *
 *          The square root of x at double precision.                         *
 *  Called Functions:                                                         *
 *      fsqrt                                                                 *
 *  Method:                                                                   *
 *      Use fsqrt on the argument.                                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 11, 2022                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

#ifdef __APPLE__
.section __TEXT, __text, regular, pure_instructions
.globl EXT(tmpl_Double_Sqrt)
.p2align ALIGN
#endif

ASM_BEGIN(tmpl_Double_Sqrt)

    /*  fsqrt is floating-point square root. Compute y = sqrt(x).             */
    fsqrt d0, d0

    /*  return y;                                                             */
    ret

ASM_END(tmpl_Double_Sqrt)
