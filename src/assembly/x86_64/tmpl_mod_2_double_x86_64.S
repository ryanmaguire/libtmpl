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
 *                              tmpl_mod_2_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing remainder after division by 2.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Mod_2                                                     *
 *  Purpose:                                                                  *
 *      Computes the remainder after division by 2.                           *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      x_mod_2 (double):                                                     *
 *          The remainder after division by 2 at double precision.            *
 *  Called Instructions:                                                      *
 *      roundsd / vroundsd / vrndscalesd:                                     *
 *          Rounds a double-precision floating-point number in the requested  *
 *          rounding mode. If AVX-512 support is available, then vrndscalesd  *
 *          is used, and if AVX support is available, then vroundsd is used.  *
 *          All three of these instructions can compute trunc(x).             *
 *      subsd / vsubsd:                                                       *
 *          Subtracts double-precision numbers.                               *
 *      addsd / vaddsd:                                                       *
 *          Adds double-precision numbers.                                    *
 *      mulsd / vmulsd:                                                       *
 *          Multiplies double-precision numbers.                              *
 *      movsd / vmovsd:                                                       *
 *          Copies / moves double-precision numbers.                          *
 *  Method:                                                                   *
 *      Compute x - 2 * trunc(x / 2).                                         *
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
 *                                                                            *
 *      4.) AVX-512 has a fused multiply-subtract instruction which allows    *
 *          x - 2 * trunc(x / 2) to be computed efficiently.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 6, 2024                                              *
 ******************************************************************************
 *  2026/05/24: Ryan Maguire                                                  *
 *      Added comments, updated docstring. Added AVX and AVX-512 versions.    *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Double-precision mod 2 function for x86_64 machines.                      */
ASM_BEGIN(tmpl_Double_Mod_2)

    /*  AVX-512 has the vfnmadd132sd (fused multiply-subtract) instruction.   */
#if defined(__AVX512F__)

    /*  Copy the input into the xmm1 register. That is, set y = x.            */
    vmovsd %xmm0, %xmm0, %xmm1

    /*  Compute 0.5 * x and set this into xmm0. That is, set x = 0.5 * x.     */
    vmulsd .TMPL_DOUBLE_MOD2_HALF_AS_HEX(%rip), %xmm0, %xmm0

    /*  Truncate and store the result in xmm0. That is, set x = trunct(x / 2).*/
    vrndscalesd $0x0B, %xmm0, %xmm0, %xmm0

    /*  AVX-512 has FMA-like operations (fused multiply-add). We can compute  *
     *  x - 2 * trunc(x / 2) all at once. xmm1 has x stored in it, and        *
     *  xmm0 has trunc(x / 2) stored. Compute x - 2 * trunc(x / 2) and store  *
     *  the result in xmm0.                                                   */
    vfnmadd132sd .TMPL_DOUBLE_MOD2_TWO_AS_HEX(%rip), %xmm1, %xmm0

    /*  AVX has vmulsd, which lets us store a product in a different register.*/
#elif defined(__AVX__) || defined(__AVX2__)

    /*  Compute 0.5 * x and store it in xmm1. That is, set y = x / 2.         */
    vmulsd .TMPL_DOUBLE_MOD2_HALF_AS_HEX(%rip), %xmm0, %xmm1

    /*  Truncate y = x / 2 by rounding it towards zero. Store the result in   *
     *  xmm1. That is, set y = trunc(y) = trunc(x / 2).                       */
    vroundsd $0x0B, %xmm1, %xmm1, %xmm1

    /*  Compute 2 * trunc(x / 2) = trunc(x / 2) + trunc(x / 2).               */
    vaddsd  %xmm1, %xmm1, %xmm1

    /*  We have avoided modifying the input, xmm0. This still contains the    *
     *  initial input x. We compute x mod 2 via x - 2 * trunc(x / 2).         *
     *  Subtract 2 * trunc(x / 2) from x and store the result in xmm0. That   *
     *  is, set x = x - y = x - 2 * trunc(x / 2).                             */
    vsubsd  %xmm1, %xmm0, %xmm0

    /*  Use SSE4.1 instructions as a fallback. SSE4.1 support is very common. */
#else

    /*  We compute x mod 2 by returning x - 2 * trunc(x / 2). We need to save *
     *  the input value "x" for this final subtraction. Copy xmm0 into xmm1.  *
     *  That is, set y = x.                                                   */
    movsd %xmm0, %xmm1

    /*  Set y = 0.5 * x.                                                      */
    mulsd .TMPL_DOUBLE_MOD2_HALF_AS_HEX(%rip), %xmm1

    /*  Compute y = trunc(0.5 * x). roundsd $11 is round-to-zero, or truncate.*/
    roundsd $0x0B, %xmm1, %xmm1

    /*  Compute y = 2.0 * trunc(0.5 * x) = trunc(0.5 * x) + trunc(0.5 * x).   */
    addsd %xmm1, %xmm1

    /*  Compute y = x - 2.0 * trunc(0.5 * x). This is x mod 2.                */
    subsd %xmm1, %xmm0

#endif
/*  End of #if defined(__AVX512F__).                                          */

    /*  Return y = x - 2.0 * trunc(0.5 * x).                                  */
    ret

/*  The hexadecimal representation (IEEE-754 format) of x = 0.5.              */
    ASM_RODATA
    .p2align 3
.TMPL_DOUBLE_MOD2_HALF_AS_HEX:
    .quad 0x3FE0000000000000
    .text

/*  The AVX-512 method uses FMA and needs the constant for 2. Provide this.   */
#ifdef __AVX512F__
    ASM_RODATA
    .p2align 3
.TMPL_DOUBLE_MOD2_TWO_AS_HEX:
    .quad 0x4000000000000000
    .text
#endif

ASM_END(tmpl_Double_Mod_2)
