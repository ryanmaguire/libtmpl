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
 *      sqrtss                                                                *
 *  Method:                                                                   *
 *      For x86_64/amd64 machines sqrt is a built-in function.                *
 *  Notes:                                                                    *
 *      This file compiles using GCC, clang, or PCC on GNU/Linux, and         *
 *      using GCC or clang on FreeBSD and macOS (PCC may work on those        *
 *      platforms, but I haven't tested this), for x86_64/amd64 computers.    *
 *      This assembly code is significantly faster than the equivalent C code *
 *      found in tmpl_sqrt_float.c.                                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 5, 2022                                                 *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

ASM_BEGIN(tmpl_Float_Sqrt)
    sqrtss %xmm0, %xmm0
    ret
ASM_END(tmpl_Float_Sqrt)
