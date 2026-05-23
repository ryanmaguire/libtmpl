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
 *                        tmpl_fractional_part_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the fractional part of a long double.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Fractional_Part                                          *
 *  Purpose:                                                                  *
 *      Computes the fractional part of the input.                            *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      frac_x (long double):                                                 *
 *          The fractional part of x at long double precision.                *
 *  Called Instructions:                                                      *
 *      fnstcw / fldcw:                                                       *
 *          Store and load the FPU control word.                              *
 *      fldt / fld:                                                           *
 *          Load an 80-bit extended-precision value onto the FPU stack.       *
 *      frndint:                                                              *
 *          Round to an integer using the current rounding mode.              *
 *      movzwl:                                                               *
 *          Moves a word and extends its size by padding zeros.               *
 *      movw:                                                                 *
 *          Moves a word.                                                     *
 *      andb:                                                                 *
 *          Performs bit-wise and on a register.                              *
 *      orb:                                                                  *
 *          Performs bit-wise or on a register.                               *
 *      fsubrp:                                                               *
 *          Performs floating-point subtraction.                              *
 *      fstpt:                                                                *
 *          Store an 80-bit extended precision value from st(0) into memory   *
 *          and then pop the FPU stack (Windows / MinGW version only).        *
 *      addq / subq:                                                          *
 *          Adjust a stack pointer (Windows / MinGW version only).            *
 *  Method:                                                                   *
 *      Compute x - trunc(x).                                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_x86_64_asm.h:                                                    *
 *          Provides x86_64 / amd64 helper macros to improve portability.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 6, 2024                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/22: Ryan Maguire                                                  *
 *      Added comments, updated docstring, created MinGW version.             *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Long double precision fractional part function for x86_64 machines.       */
ASM_BEGIN(tmpl_LDouble_Fractional_Part)

    /*  When using MinGW, MSYS2, or Cygwin on Microsoft Windows, the          *
     *  implementation of long double differs from regular GNU / Linux,       *
     *  FreeBSD, or macOS systems. Check for this.                            */
#ifdef _WIN64

    /*  Allocate a stack frame.                                               */
    subq $24, %rsp

    /*  The input is pointed to by rdx. Load this onto the FPU stack.         */
    fldt (%rdx)

    /*  Save the current 80-bit extended precision input. We will need it     *
     *  later in order to compute x - trunc(x).                               */
    fld %st(0)

    /*  The rest of the algorithm mimics the GNU / Linux, FreeBSD, and macOS  *
     *  Save the original control word so we can restore it later. -10 bytes  *
     *  back is not reserved for scratch, like it is on other systems, so we  *
     *  store the word 14 bytes forward.                                      */
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

    /*  Round the top of the FPU stack towards an integer in the current      *
     *  rounding mode. Since we've set this to "round towards zero", this     *
     *  instruction computes trunc(x).                                        */
    frndint

    /*  Restore the original FPU control word before returning.               */
    fldcw 14(%rsp)

    /*  We saved the input "x", and have now computed trunc(x). The           *
     *  fractional part is given by x - trunc(x). Compute.                    */
    fsubrp %st, %st(1)

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

    /*  Save the current 80-bit extended precision input. We will need it     *
     *  later in order to compute x - trunc(x).                               */
    fld %st(0)

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

    /*  We saved the input "x", and have now computed trunc(x). The           *
     *  fractional part is given by x - trunc(x). Compute.                    */
    fsubrp %st, %st(1)

#endif
/*  End of #ifdef _WIN64.                                                     */

    /*  We have computed the fractional part of x. Return to the caller.      */
    ret

ASM_END(tmpl_LDouble_Fractional_Part)
