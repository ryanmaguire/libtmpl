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
 *                              tmpl_sqrt_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at single precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Sqrt                                                       *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (float):                                                       *
 *          The square root of x at single precision.                         *
 *  Called Functions:                                                         *
 *      fsqrt                                                                 *
 *  Method:                                                                   *
 *      For aarch64 (arm64) machines sqrt is a built-in function.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 3, 2022                                                   *
 ******************************************************************************/

/*  The following code works with Apple's M1 chip. Tested with Apple's        *
 *  version of clang.                                                         */
#ifdef __APPLE__

.section  __TEXT,__text,regular,pure_instructions
.globl    _tmpl_Float_Sqrt
.p2align  2

_tmpl_Float_Sqrt:
    fsqrt   s0, s0
    ret

#else
/*  Else of #ifdef __APPLE__.                                                 */

/*  The following works with GCC and LLVM's clang on GNU/Linux platforms. Not *
 *  tested on anything else.                                                  */
.text
.align  2
.global tmpl_Float_Sqrt
.type   tmpl_Float_Sqrt, %function

tmpl_Float_Sqrt:
    fsqrt s0, s0
    ret

.size   tmpl_Float_Sqrt, .-tmpl_Float_Sqrt

#endif
/*  End of #ifdef __APPLE__.                                                  */

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
/*  End of #if defined(__ELF__).                                              */
