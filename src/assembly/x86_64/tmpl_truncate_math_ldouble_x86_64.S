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
 *                           tmpl_truncate_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for truncating a long double.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Truncate                                                 *
 *  Purpose:                                                                  *
 *      Computes the truncation of the input.                                 *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      trunc_x (long double):                                                *
 *          The truncation of x at long double precision.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 6, 2024                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

ASM_BEGIN(tmpl_LDouble_Truncate)

    /*  When using MinGW, MSYS2, or Cygwin on Microsoft Windows, the          *
     *  implementation of long double differs from regular GNU / Linux,       *
     *  FreeBSD, or macOS systems. Check for this.                            */
#ifdef _WIN64

    /*  MinGW has the following ABI for 80-bit long double precision:         *
     *      rdx = pointer to the input.                                       *
     *      rcx = pointer to the output.                                      *
     *  rax preserves the original rcx. Start by allocating a stack frame.    */
    subq $24, %rsp

    /*  The input is pointed to by rdx. Load this onto the FPU stack.         */
    fldt (%rdx)

    /*  The rest of the algorithm mimics the GNU / Linux, FreeBSD, and macOS  *
     *  version provided below. We save the original control word so we can   *
     *  restore it later. -10 bytes back is not reserved for scratch, like it *
     *  is on other systems, so we store the word 14 bytes forward.           */
    fnstcw 14(%rsp)

    /*  rcx is a pointer to the output. Move this into rax. rax must equal    *
     *  the original rcx on return, hence we perform this move now.           */
    movq %rcx, %rax

    /*  Load the control word into a register so that we may edit it.         */
    movzwl 14(%rsp), %edx

    /*  The rounding mode is governed by the 11th and 12th bits, which        *
     *  correspond to the 3rd and 4th bits of the high part (dh). Set these   *
     *  both to 1 using bit-wise or, which sets the rounding mode to round    *
     *  towards zero. This is equivalent to truncating the input.             */
    orb $0x0C, %dh

    /*  Store the modified control word so that the FPU can use it.           */
    movw %dx, 12(%rsp)

    /*  Set the FPU to round towards zero.                                    */
    fldcw 12(%rsp)

    /*  With the control word set, we can compute trunc(x).                   */
    frndint

    /*  Restore the original FPU control word before returning.               */
    fldcw 14(%rsp)

    /*  For the caller, rcx points to the output. Store the result there.     */
    fstpt (%rcx)

    /*  Tear down the frame (undo the first "subq $24, %rsp" instruction).    */
    addq $24, %rsp

#else
/*  Else for #ifdef _WIN64.                                                   */

    /*  Save the current FPU control word so that we may restore it before    *
     *  returning to the caller. The 16-bit control word occupies bytes -10   *
     *  and -9.                                                               */
    fnstcw -10(%rsp)

    /*  Load the input onto the FPU stack.                                    */
    fldt 8(%rsp)

    /*  Edit the control word so that the rounding mode in the FPU is         *
     *  towards zero. First, pull the control word into the eax register so   *
     *  we can edit it.                                                       */
    movzwl -10(%rsp), %eax

    /*  The rounding mode is governed by the 11th and 12th bits, which        *
     *  correspond to the 3rd and 4th bits of the high part (ah). Set these   *
     *  both to 1 using bit-wise or, which sets the rounding mode to round    *
     *  towards zero. This is equivalent to truncating the input.             */
    orb $0x0C, %ah

    /*  Store the modified control word so that the FPU can use it.           */
    movw %ax, -12(%rsp)

    /*  Set the FPU to round towards zero.                                    */
    fldcw -12(%rsp)

    /*  Round the top of the FPU stack towards an integer in the current      *
     *  rounding mode. Since we've set this to "round towards zero", this     *
     *  instruction computes trunc(x).                                        */
    frndint

    /*  Restore the original FPU control word before returning.               */
    fldcw -10(%rsp)

#endif
/*  End of #ifdef _WIN64.                                                     */

    ret

ASM_END(tmpl_LDouble_Truncate)
