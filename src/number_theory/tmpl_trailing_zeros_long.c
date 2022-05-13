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
 ******************************************************************************
 *                          tmpl_trailing_zeros_long                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the number of trailing zeros, in binary, of an integer.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Long_Trailing_Zeros                                              *
 *  Purpose:                                                                  *
 *      Given a long int n, returns the number of trailing zeros for the      *
 *      binary representation of n. Ex. If n = 8, then in binary n = 1000_2,  *
 *      so the number of trailing zeros is 3.                                 *
 *  Arguments:                                                                *
 *      n (long int):                                                         *
 *          An integer.                                                       *
 *  Output:                                                                   *
 *      zeros (int):                                                          *
 *          The number of trailing zeros for n.                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If unsigned long is 32 or 64 bit, use a simple O(1) algorithm to      *
 *      compute the number of trailing zeros. If not, a portable algorithm is *
 *      implemented, though it is slightly slower, O(ln(n)).                  *
 *                                                                            *
 *      Some architectures (x86_64/amd64, arm64) have a builtin function that *
 *      is significantly faster. The Makefile will implement this, instead of *
 *      this file, if available unless you explicitly request no assembly     *
 *      code being used when building libtmpl.                                *
 *  Notes:                                                                    *
 *      If n = 0, the number of trailing zeros is zero.                       *
 *                                                                            *
 *      This function works with one's complement, two's complement, and      *
 *      sign-and-magnitude representations of signed integers. I know of no   *
 *      other types of representations, and hence these haven't been tested.  *
 *  Performance and Accuracy:                                                 *
 *      C code (this file):                                                   *
 *          tmpl_Long_Trailing_Zeros vs. bfs_func                             *
 *          samples:        10000000                                          *
 *          libtmpl:        0.029737                                          *
 *          glibc:          0.021084                                          *
 *          glibc (inline): 0.011646                                          *
 *          rms error:      0.000000e+00                                      *
 *          max error:      0.000000e+00                                      *
 *                                                                            *
 *      x86_64 / amd64 assembly (tmpl_trailing_zeros_long_x86_64.S):          *
 *          tmpl_Long_Trailing_Zeros vs. bfs_func                             *
 *          samples:        10000000                                          *
 *          libtmpl:        0.024756                                          *
 *          glibc:          0.023566                                          *
 *          glibc (inline): 0.012156                                          *
 *          rms error:      0.000000e+00                                      *
 *          max error:      0.000000e+00                                      *
 *                                                                            *
 *      These tests were performed with the following specs:                  *
 *          CPU:  AMD Ryzen 3900 12-core                                      *
 *          MIN:  2200.0000 MHz                                               *
 *          MAX:  4672.0698 MHz                                               *
 *          ARCH: x86_64                                                      *
 *          RAM:  Ripjaw DDR4-3600 16GBx4                                     *
 *          MB:   Gigabyte Aorus x570 Elite WiFi                              *
 *          OS:   Debian 11 (Bullseye) GNU/LINUX                              *
 *                                                                            *
 *      Performance will of course vary on different systems.                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_number_theory.h:                                                 *
 *          Header where the function prototype is defined.                   *
 *  2.) limits.h:                                                             *
 *          Standard C library header file containing information on the size *
 *          of an int.                                                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2022/05/12                                                    *
 ******************************************************************************/

/*  Function prototype here.                                                  */
#include <libtmpl/include/tmpl_number_theory.h>

/*  Size of unsigned long int here.                                           */
#include <limits.h>

/*  The C standard requires long to be at LEAST 32 bits.                      */
#if ULONG_MAX == 0xFFFFFFFFU

/*  32-bit trailing-zeros function.                                           */
int tmpl_Long_Trailing_Zeros(long int n)
{
    /*  Variable for the number of trailing zeros.                            */
    int bits = 0;

    /*  We want the largest value N such that n >> N (n bit-shift to the      *
     *  right N times) does not erase any non-zeros. To avoid sign issues,    *
     *  first convert n to a non-negative number.                             */
    if (n < 0L)
        n = -n;

    /*  If n is zero, return 0. That is, 0 has no trailing zeros.             */
    if (n != 0L)
    {
        /*  Set the upper 16 bits to zero and see if the number ends up being *
         *  zero. If yes, there are at least 16 trailing zeros.               */
        if (!(n & 0xFFFF))
        {
            bits += 16;
            n >>= 16;
        }

        /*  The next 8 bits.                                                  */
        if (!(n & 0xFF))
        {
            bits += 8;
            n >>= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0x0F))
        {
            bits += 4;
            n >>= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0x03))
        {
            bits += 2;
            n >>= 2;
        }

        /*  The last bit of n.                                                */
        if (!(n & 0x01))
            bits += 1;
    }
    return bits;
}
/*  End of tmpl_Long_Trailing_Zeros.                                          */

/*  64-bit is common on Unix-like (Linux, FreeBSD, macOS).                    */
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFFU

/*  64-bit trailing-zeros function.                                           */
int tmpl_Long_Trailing_Zeros(long int n)
{
    /*  Variable for the number of trailing zeros.                            */
    int bits = 0;

    /*  We want the largest value N such that n >> N (n bit-shift to the      *
     *  right N times) does not erase any non-zeros. To avoid sign issues,    *
     *  first convert n to a non-negative number.                             */
    if (n < 0L)
        n = -n;

    /*  If n is zero, return 0. That is, 0 has no trailing zeros.             */
    if (n != 0L)
    {
        /*  Set the upper 32 bits to zero and see if the number ends up being *
         *  zero. If yes, there are at least 32 trailing zeros.               */
        if (!(n & 0xFFFFFFFF))
        {
            bits += 32;
            n >>= 32;
        }

        /*  The next 16-bits.                                                 */
        if (!(n & 0xFFFF))
        {
            bits += 16;
            n >>= 16;
        }

        /*  The next 8 bits.                                                  */
        if (!(n & 0xFF))
        {
            bits += 8;
            n >>= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0x0F))
        {
            bits += 4;
            n >>= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0x03))
        {
            bits += 2;
            n >>= 2;
        }

        /*  The last bit of n.                                                */
        if (!(n & 0x01))
            bits += 1;
    }
    return bits;
}
/*  End of tmpl_Long_Trailing_Zeros.                                          */

/*  This is for exotic systems. The C standard requires long to be at least   *
 *  32 bits wide, so we can loop through the bits of the input 32 at a time.  */
#else

/*  Portable trailing-zeros function.                                         */
int tmpl_Long_Trailing_Zeros(long int n)
{
    /*  Variable for the number of trailing zeros.                            */
    int bits = 0;

    /*  We want the largest value N such that n >> N (n bit-shift to the      *
     *  right N times) does not erase any non-zeros. To avoid sign issues,    *
     *  first convert n to a non-negative number.                             */
    if (n < 0L)
        n = -n;

    /*  If n is zero, return 0. That is, 0 has no trailing zeros.             */
    if (n != 0L)
    {
        /*  Keep zeroing out the lower 32 bits and shifting the number.       */
        while (!(n & 0xFFFFFFFF))
        {
            bits += 32;
            n >>= 32;
        }

        /*  Do the next 16 bits of the number.                                */
        if (!(n & 0xFFFF))
        {
            bits += 16;
            n >>= 16;
        }

        /*  The next 8 bits.                                                  */
        if (!(n & 0xFF))
        {
            bits += 8;
            n >>= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0x0F))
        {
            bits += 4;
            n >>= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0x03))
        {
            bits += 2;
            n >>= 2;
        }

        /*  The last bit of n.                                                */
        if (!(n & 0x01))
            bits += 1;
    }
    return bits;
}
/*  End of tmpl_Int_Trailing_Zeros.                                           */

#endif
/*  End of #if ULONG_MAX == 0xFFFFFFFF.                                       */
