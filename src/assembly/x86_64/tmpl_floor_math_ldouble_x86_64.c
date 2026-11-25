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
 *      x (const long double):                                                *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      floor_x (long double):                                                *
 *          The floor of x at long double precision.                          *
 *  Called Instructions:                                                      *
 *      fnstcw / fldcw:                                                       *
 *          Store and load the FPU control word.                              *
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
 *      frndint:                                                              *
 *          Round to an integer using the current rounding mode.              *
 *  Method:                                                                   *
 *      Set the rounding mode to "towards negative infinity", and then round  *
 *      the input to an integer.                                              *
 *  Notes:                                                                    *
 *      1.) frndint correctly handles NaN, infinity, and signed zero.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_ALWAYS_INLINE macro.                            *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides macros for C23 attributes (for optimization).            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 25, 2024                                             *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration.                                 */
extern long double tmpl_LDouble_Floor(const long double x);

/*  Long double precision floor function for x86_64 machines.                 */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Floor(const long double x)
TMPL_UNSEQUENCED
{
    /*  Variable for the output, floor(x).                                    */
    long double floor_x;

    /*  The x87 FPU control word contains the rounding mode. We'll save the   *
     *  original control word so that we may restore it before exiting the    *
     *  function, and then set the control to "towards negative infinity"     *
     *  which allows us to compute the floor function.                        */
    unsigned short int original_control_word, floor_control_word;

    /*  Register used for editing the control word.                           */
    unsigned int scratch;

    /*  This inline assembly code is a mimicry of the .S file found next to   *
     *  this implementation. The benefit of using inline assembly in C is     *
     *  that compilers like GCC and Clang can inline these instructions when  *
     *  link-time optimization (LTO) is enabled. This gives the .c version a  *
     *  noticeable performance boost compared to the .S version.              */
    __asm__(

        /*  Save the current FPU control word so that we may restore it       *
         *  before returning to the caller.                                   */
        "fnstcw %[original_control_word]\n\t"

        /*  Edit the control word so that the rounding mode in the FPU is     *
         *  towards negative infinity. First, pull the control word into the  *
         *  eax register so we can edit it. This is equivalent to %eax.       */
        "movzwl %[original_control_word], %k[scratch]\n\t"

        /*  The rounding mode is governed by the 11th and 12th bits, which    *
         *  correspond to the 3rd and 4th bits of the high part. Clear these  *
         *  bits. This corresponds to the bit-mask 11110011_2, which is 0xF3  *
         *  in hexadecimal. Use bit-wise and with this value. %h is used for  *
         *  16-bit half-word FP/SIMD registers. This allows us to access %ah. */
        "andb $0xF3, %h[scratch]\n\t"

        /*  Set the 3rd bit, which sets the rounding mode to round towards    *
         *  negative infinity.                                                */
        "orb $0x04, %h[scratch]\n\t"

        /*  Store the modified control word so that the FPU can use it. %w is *
         *  used for 32-bit general-purpose registers. %w allows us to access *
         *  a register, equivalent to %ax.                                    */
        "movw %w[scratch], %[floor_control_word]\n\t"

        /*  Set the FPU to round towards negative infinity.                   */
        "fldcw %[floor_control_word]\n\t"

        /*  Round the top of the FPU stack to an integer in the current       *
         *  rounding mode. Since we've set this to "towards negative          *
         *  infinity", this instruction computes floor(x).                    */
        "frndint\n\t"

        /*  Restore the original FPU control word.                            */
        "fldcw %[original_control_word]"

        /*  Output operands:                                                  *
         *      "=t":                                                         *
         *          floor_x is at the top of the FPU stack, st(0), which      *
         *          is where frndint leaves its result.                       *
         *      "=m":                                                         *
         *          fnstcw and fldcw apply to memory.                         *
         *      "=&Q":                                                        *
         *          The scratch register needs an addressable high byte,      *
         *          which only rax, rbx, rcx, and rdx have. The "&" (early    *
         *          clobber) is needed since it is written before we are      *
         *          done with original_control_word and floor_control_word,   *
         *          so it must not hold either of their addresses.            */
        : "=t" (floor_x),
          [original_control_word] "=m" (original_control_word),
          [floor_control_word] "=m" (floor_control_word),
          [scratch] "=&Q" (scratch)

        /*  Input operand: x goes in st(0), the same register as floor_x.     */
        : "0" (x)

        /*  andb and orb modify the flag register.                            */
        : "cc"
    );

    return floor_x;
}
/*  End of tmpl_LDouble_Floor.                                                */
