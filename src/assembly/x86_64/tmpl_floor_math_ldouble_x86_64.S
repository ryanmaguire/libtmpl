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
 *                             tmpl_floor_ldouble                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the floor function at long double precision.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Floor                                                    *
 *  Purpose:                                                                  *
 *      Computes y = floor(x), the largest integer less than or equal to x.   *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      floor_x (long double):                                                *
 *          The floor of x at long double precision.                          *
 *  Called Instructions:                                                      *
 *      fnstcw / fldcw:                                                       *
 *          Store and load the FPU control word.                              *
 *      fldt:                                                                 *
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
 *  Method:                                                                   *
 *      Set the rounding mode to "towards negative infinity", and then round  *
 *      the input to an integer.                                              *
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
 *      Added comments, updated docstring.                                    *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Long double precision floor function for x86_64 machines.                 */
ASM_BEGIN(tmpl_LDouble_Floor)

    /*  Save the current FPU control word so that we may restore it before    *
     *  returning to the caller. The 16-bit control word occupies bytes -10   *
     *  and -9.                                                               */
    fnstcw -10(%rsp)

    /*  Load the input onto the FPU stack.                                    */
    fldt 8(%rsp)

    /*  Edit the control word so that the rounding mode in the FPU is         *
     *  towards negative infinity. First, pull the control word into the eax  *
     *  register so we can edit it.                                           */
    movzwl -10(%rsp), %eax

    /*  The rounding mode is governed by the 11th and 12th bits, which        *
     *  correspond to the 3rd and 4th bits of the high part (ah). Clear these *
     *  bits. This corresponds to the bit-mask 11110011_2, which is 0xF3 in   *
     *  hexadecimal. Use bit-wise and with this value.                        */
    andb $0xF3, %ah

    /*  Set the 3rd bit, which sets the rounding mode to round towards        *
     *  negative infinity.                                                    */
    orb $0x04, %ah

    /*  Store the modified control word so that the FPU can use it.           */
    movw %ax, -12(%rsp)

    /*  Set the FPU to round towards negative infinity.                       */
    fldcw -12(%rsp)

    /*  Round the top of the FPU stack towards an integer in the current      *
     *  rounding mode. Since we've set this to "towards negative infinity",   *
     *  this instruction computes floor(x).                                   */
    frndint

    /*  Restore the original FPU control word before returning.               */
    fldcw -10(%rsp)

    /*  We have now computed floor(x). Return to the caller.                  */
    ret

ASM_END(tmpl_LDouble_Floor)
