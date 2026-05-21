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
 *                               tmpl_ceil_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the ceiling function at single precision.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Ceil                                                       *
 *  Purpose:                                                                  *
 *      Computes y = ceil(x), the smallest integer greater than or equal to x.*
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      ceil_x (float):                                                       *
 *          The ceiling of x at single precision.                             *
 *  Called Instructions:                                                      *
 *      roundss / vroundss / vrndscaless:                                     *
 *          Rounds a single-precision floating-point number in the requested  *
 *          rounding mode. If AVX-512 support is available, then vrndscaless  *
 *          is used, and if AVX support is available, then vroundss is used.  *
 *          All three of these instructions can compute ceil(x).              *
 *  Method:                                                                   *
 *      The roundss instruction with 10 passed to it computes ceil(x). The    *
 *      same is true of the vrndscaless and vroundss instructions.            *
 *  Notes:                                                                    *
 *      1.) roundss, vroundss, and vrndscaless correctly handle NaN,          *
 *          infinity, and signed zero.                                        *
 *                                                                            *
 *      2.) roundss is part of SSE4.1. Use of this file requires a CPU that   *
 *          supports SSE4.1 (introduced in 2007). For older x86_64 CPUs, use  *
 *          the C code instead (set NO_ASM=1 when using the Makefile).        *
 *                                                                            *
 *      3.) vrndscaless requires AVX-512, and vroundss requires AVX support.  *
 *          While most modern CPUs support SSE4.1, AVX-512 support is not as  *
 *          universal at the time of this writing. GCC and Clang set the      *
 *          __AVX512F__ and __AVX__ macros to indicate support. This file     *
 *          checks these macros to select the proper instructions.            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_x86_64_asm.h:                                                    *
 *          Provides x86_64 / amd64 helper macros to improve portability.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 10, 2024                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/21: Ryan Maguire                                                  *
 *      Added comments, updated docstring. Added AVX and AVX-512 versions.    *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Single-precision ceiling function for x86_64 machines.                    */
ASM_BEGIN(tmpl_Float_Ceil)

    /*  AVX-512 has the vrndscaless (round scalar) instruction.               */
#if defined(__AVX512F__)

    /*  SSE4.1 introduced roundss in 2007 (see below). The newer AVX-512      *
     *  extension introduced vrndscaless. It uses a similar syntax to roundss *
     *  but is a bit more general. Using this instruction with rounding mode  *
     *  "10" is equivalent to computing ceil(x) without raising inexact.      */
    vrndscaless $0x0A, %xmm0, %xmm0, %xmm0

    /*  AVX supports the vroundss instruction.                                */
#elif defined(__AVX__) || defined(__AVX2__)

    /*  VEX.128 encoded version of the roundss instruction used below. This   *
     *  is available on CPUs that support AVX, introduced in 2011.            */
    vroundss $0x0A, %xmm0, %xmm0, %xmm0

    /*  Use SSE4.1 instructions as a fallback. SSE4.1 support is very common. */
#else

    /*  roundss rounds a single-precision floating-point number to the        *
     *  requested rounding mode. Rounding mode "2" is round towards positive  *
     *  infinity, which is equivalent to computing the ceiling of the input.  *
     *  Rounding mode "10" is the same as rounding mode "2", except the       *
     *  inexact flag is not raised. Use this.                                 */
    roundss $0x0A, %xmm0, %xmm0

#endif

    /*  We have now computed ceil(x). Return to the caller.                   */
    ret

ASM_END(tmpl_Float_Ceil)
