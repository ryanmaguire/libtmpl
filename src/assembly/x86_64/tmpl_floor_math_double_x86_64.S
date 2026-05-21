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
 *                              tmpl_floor_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the floor function at double precision.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Floor                                                     *
 *  Purpose:                                                                  *
 *      Computes y = floor(x), the largest integer less than or equal to x.   *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      floor_x (double):                                                     *
 *          The floor of x at double precision.                               *
 *  Called Instructions:                                                      *
 *      roundsd / vroundsd / vrndscalesd:                                     *
 *          Rounds a double-precision floating-point number in the requested  *
 *          rounding mode. If AVX-512 support is available, then vrndscalesd  *
 *          is used, and if AVX support is available, then vroundsd is used.  *
 *          All three of these instructions can compute floor(x).             *
 *  Method:                                                                   *
 *      The roundsd instruction with 9 passed to it computes floor(x). The    *
 *      same is true of the vrndscalesd and vroundsd instructions.            *
 *  Notes:                                                                    *
 *      1.) roundsd, vroundsd, and vrndscalesd correctly handle NaN,          *
 *          infinity, and signed zero.                                        *
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
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_x86_64_asm.h:                                                    *
 *          Provides x86_64 / amd64 helper macros to improve portability.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 5, 2022                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/21: Ryan Maguire                                                  *
 *      Added comments, updated docstring. Added AVX and AVX-512 versions.    *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Double-precision floor function for x86_64 machines.                      */
ASM_BEGIN(tmpl_Double_Floor)

    /*  AVX-512 has the vrndscalesd (round scalar) instruction.               */
#if defined(__AVX512F__)

    /*  SSE4.1 introduced roundsd in 2007 (see below). The newer AVX-512      *
     *  extension introduced vrndscalesd. It uses a similar syntax to roundsd *
     *  but is a bit more general. Using this instruction with rounding mode  *
     *  "9" is equivalent to computing floor(x) without raising inexact.      */
    vrndscalesd $0x09, %xmm0, %xmm0, %xmm0

    /*  AVX supports the vroundsd instruction.                                */
#elif defined(__AVX__) || defined(__AVX2__)

    /*  VEX.128 encoded version of the roundsd instruction used below. This   *
     *  is available on CPUs that support AVX, introduced in 2011.            */
    vroundsd $0x09, %xmm0, %xmm0, %xmm0

    /*  Use SSE4.1 instructions as a fallback. SSE4.1 support is very common. */
#else

    /*  roundsd rounds a double-precision floating-point number to the        *
     *  requested rounding mode. Rounding mode "1" is round towards negative  *
     *  infinity, which is equivalent to computing the floor of the input.    *
     *  Rounding mode "9" is the same as rounding mode "1", except the        *
     *  inexact flag is not raised. Use this.                                 */
    roundsd $0x09, %xmm0, %xmm0

#endif
/*  End of #if defined(__AVX512F__).                                          */

    /*  We have now computed floor(x). Return to the caller.                  */
    ret

ASM_END(tmpl_Double_Floor)
