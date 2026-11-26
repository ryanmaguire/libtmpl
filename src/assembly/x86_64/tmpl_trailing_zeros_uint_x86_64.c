/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
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
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  TMPL_CAST macro found here which provides C vs. C++ compatibility.        */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Function prototype / forward declaration.                                 */
extern int tmpl_UInt_Trailing_Zeros(const unsigned int n);

/*  Function for computing the number of trailing zeros in an unsigned int.   */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
int
tmpl_UInt_Trailing_Zeros(const unsigned int n)
TMPL_UNSEQUENCED
{
    /*  Variable for the number of trailing zeros in n.                       */
    unsigned int count;

    /*  With the x86 bit-manipulation-instruction set (BMI) we can use the    *
     *  trailing-zero-count instruction (tzcnt). Check for support.           */
#ifdef __BMI__

    /*  Count the number of trailing zeros in n and store this in count.      */
    __asm__("tzcntl %0, %0" : "=r" (count) : "r" (n) : "cc");

    /*  Unlike bit-scan-forward (bsf), the trailing-zero-count instruction    *
     *  (tzcnt) does accept zero as an input and sets the result to the       *
     *  number of bits in the word. For x86-64 int is 32 bits for all major   *
     *  compilers and operating systems. libtmpl adopts the convention that   *
     *  there are no "trailing" zeros in zero since the only zero that occurs *
     *  is the number itself. Thus, trailing_zeros(0) = 0. To do this we need *
     *  to zero out the higher bits. Perform a bit-wise AND with 31 = 0x1F.   */
    count &= 0x1F;

#else
/*  Else for #ifdef __BMI__.                                                  */

    /*  Older CPUs provide the bit-scan-forward instruction (bsf). This can   *
     *  be used to compute the number of trailing zeros as well.              */
    __asm__(

        /*  Zero out the count. If the input is zero, we'll return zero.      */
        "xorl %0, %0\n\t"

        /*  Use bsf to count the number of trailing zeros.                    */
        "bsfl %1, %0\n\t"

        /*  If the input is zero, then bsf is undefined. Set count to zero if *
         *  this is the case.                                                 */
        "cmovel %1, %0"

        /*  The output / input for this asm block.                            */
        : "=&r" (count) : "r" (n) : "cc"
    );

#endif
/*  End of #ifdef __BMI__.                                                    */

    /*  Following the convention of GCC's __builtin_ctz, this function        *
     *  returns the count as an int. Cast to int and return.                  */
    return TMPL_CAST(count, int);
}
/*  End of tmpl_UInt_Trailing_Zeros.                                          */
