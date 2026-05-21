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
 *      Computes the fractional part of a double.                             *
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
 *  Called Instructions:                                                      *
 *      roundsd / vroundsd / vrndscalesd:                                     *
 *          Rounds a double-precision floating-point number in the requested  *
 *          rounding mode. If AVX-512 support is available, then vrndscalesd  *
 *          is used, and if AVX support is available, then vroundsd is used.  *
 *          All three of these instructions can compute trunc(x).             *
 *      subsd / vsubsd:                                                       *
 *          Subtracts double-precision numbers.                               *
 *  Method:                                                                   *
 *      Compute x - trunc(x).                                                 *
 *  Notes:                                                                    *
 *      1.) roundsd, vroundsd, and vrndscalesd correctly handle NaN,          *
 *          infinity, and signed zero. vsubsd and subsd do as well.           *
 *                                                                            *
 *      2.) roundsd is part of SSE4.1. Use of this file requires a CPU that   *
 *          supports SSE4.1 (introduced in 2007). For older x86_64 CPUs, use  *
 *          the C code instead (set NO_ASM=1 when using the Makefile).        *
 *                                                                            *
 *      3.) vrndscalesd requires AVX-512, and vroundsd requires AVX support.  *
 *          While most modern CPUs support SSE4.1, AVX-512 support is not as  *
 *          universal at the time of this writing. GCC and Clang set the      *
 *          __AVX512F__ and __AVX__ macros to indicate support. This file     *
 *          checks these macros to select the proper instructions.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 6, 2024                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/21: Ryan Maguire                                                  *
 *      Added comments, updated docstring. Added AVX and AVX-512 versions.    *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Double-precision fractional part function for x86_64 machines.            */
ASM_BEGIN(tmpl_Double_Fractional_Part)

    /*  AVX-512 has the vrndscalesd (round scalar) instruction.               */
#if defined(__AVX512F__)

    /*  AVX-512 contains the vrndscalesd instruction which can be used to     *
     *  truncate the input. Rounding mode "3" rounds the value towards zero.  *
     *  Rounding mode "11" is the same as rounding mode "3", except the       *
     *  inexact flag is not raised. Use this and store the result in the xmm1 *
     *  register. That is, set y = trunc(x).                                  */
    vrndscalesd $0x0B, %xmm0, %xmm0, %xmm1

    /*  AVX has the vsubsd instruction, which subtracts double-precision      *
     *  floating-point numbers. Compute x - trunc(x).                         */
    vsubsd %xmm1, %xmm0, %xmm0

    /*  AVX supports the vroundsd instruction.                                */
#elif defined(__AVX__) || defined(__AVX2__)

    /*  VEX.128 encoded version of the roundsd instruction used below. This   *
     *  is available on CPUs that support AVX, introduced in 2011.            */
    vroundsd $0x0B, %xmm0, %xmm0, %xmm1

    /*  Subtract trunc(x) from x.                                             */
    vsubsd %xmm1, %xmm0, %xmm0

    /*  Use SSE4.1 instructions as a fallback. SSE4.1 support is very common. */
#else

    /*  roundsd rounds a double-precision floating-point number using the     *
     *  requested rounding mode. Rounding mode "3" is round towards zero,     *
     *  which is equivalent to truncating the input. Rounding mode "11" is    *
     *  the same as rounding mode "3", except that the inexact flag is not    *
     *  raised. Use this.                                                     */
    roundsd $0x0B, %xmm0, %xmm1

    /*  The xmm1 register now stores trunc(x), and xmm0 still contains x.     *
     *  Compute x - trunc(x) and store this in the xmm0 register.             */
    subsd %xmm1, %xmm0

#endif
/*  End of #if defined(__AVX512F__).                                          */

    /*  We have computed the fractional part of x. Return to the caller.      */
    ret

ASM_END(tmpl_Double_Fractional_Part)
