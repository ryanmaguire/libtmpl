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
 *                         tmpl_trailing_zeros_uchar                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the number of trailing zeros, in binary, of an integer.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UChar_Trailing_Zeros                                             *
 *  Purpose:                                                                  *
 *      Given an unsigned char n, returns the number of trailing zeros for    *
 *      the binary representation of n. Ex. If n = 8, then in binary          *
 *      n = 1000_2, so the number of trailing zeros is 3.                     *
 *  Arguments:                                                                *
 *      n (unsigned char):                                                    *
 *          An integer.                                                       *
 *  Output:                                                                   *
 *      zeros (int):                                                          *
 *          The number of trailing zeros for n.                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If unsigned char is 8, 16, 32, or 64 bit, use an O(1) algorithm to    *
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
 *          tmpl_UChar_Trailing_Zeros vs. bfs_func                            *
 *          samples:        10000000                                          *
 *          libtmpl:        0.025666                                          *
 *          glibc:          0.022084                                          *
 *          glibc (inline): 0.014555                                          *
 *          rms error:      0.000000e+00                                      *
 *          max error:      0.000000e+00                                      *
 *                                                                            *
 *      x86_64 / amd64 assembly (tmpl_trailing_zeros_uchar_x86_64.S):         *
 *          tmpl_UChar_Trailing_Zeros vs. bfs_func                            *
 *          samples:        10000000                                          *
 *          libtmpl:        0.022505                                          *
 *          glibc:          0.022055                                          *
 *          glibc (inline): 0.014644                                          *
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
 *          of an unsigned char.                                              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2022/05/12                                                    *
 ******************************************************************************/

/*  Function prototype here.                                                  */
#include <libtmpl/include/tmpl_number_theory.h>

/*  Size of unsigned char here.                                               */
#include <limits.h>

/*  This is the most likely candidate for char. 8-bits wide.                  */
#if UCHAR_MAX == 0xFFU

/*  8-bit trailing-zeros function.                                            */
int tmpl_UChar_Trailing_Zeros(unsigned char n)
{
    /*  Variable for the number of trailing zeros.                            */
    int bits = 0;

    /*  If n is zero, return 0. That is, 0 has no trailing zeros.             */
    if (n != 0U)
    {
        /*  Set the upper 4 bits to zero and see if the number ends up being  *
         *  zero. If yes, there are at least 4 trailing zeros.                */
        if (!(n & 0x0FU))
        {
            bits += 4;
            n >>= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0x03U))
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
/*  End of tmpl_UChar_Trailing_Zeros.                                         */

/*  Not unheard of, but rare (some calculators use this). 16-bit char.        */
#elif UCHAR_MAX == 0xFFFFU

/*  16-bit trailing-zeros function.                                           */
int tmpl_UChar_Trailing_Zeros(unsigned char n)
{
    /*  Variable for the number of trailing zeros.                            */
    int bits = 0;

    /*  If n is zero, return 0. That is, 0 has no trailing zeros.             */
    if (n != 0U)
    {
        /*  Set the upper 8 bits to zero and see if the number ends up being  *
         *  zero. If yes, there are at least 8 trailing zeros.                */
        if (!(n & 0xFFU))
        {
            bits += 8;
            n >>= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0x0FU))
        {
            bits += 4;
            n >>= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0x03U))
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
/*  End of tmpl_UChar_Trailing_Zeros.                                         */

/*  Essentially unheard of, 32-bit char.                                      */
#elif UCHAR_MAX == 0xFFFFFFFFU

/*  32-bit trailing-zeros function.                                           */
int tmpl_UChar_Trailing_Zeros(unsigned char n)
{
    /*  Variable for the number of trailing zeros.                            */
    int bits = 0;

    /*  If n is zero, return 0. That is, 0 has no trailing zeros.             */
    if (n != 0U)
    {
        /*  Set the upper 16 bits to zero and see if the number ends up being *
         *  zero. If yes, there are at least 16 trailing zeros.               */
        if (!(n & 0xFFFFU))
        {
            bits += 16;
            n >>= 16;
        }

        /*  The next 8 bits.                                                  */
        if (!(n & 0xFFU))
        {
            bits += 8;
            n >>= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0x0FU))
        {
            bits += 4;
            n >>= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0x03U))
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
/*  End of tmpl_UChar_Trailing_Zeros.                                         */

/*  I once read there's a calculator with char = short = int = long = 64-bit. */
#elif UCHAR_MAX == 0xFFFFFFFFFFFFFFFFU

/*  64-bit trailing-zeros function.                                           */
int tmpl_UChar_Trailing_Zeros(unsigned char n)
{
    /*  Variable for the number of trailing zeros.                            */
    int bits = 0U;

    /*  If n is zero, return 0. That is, 0 has no trailing zeros.             */
    if (n != 0U)
    {
        /*  Set the upper 32 bits to zero and see if the number ends up being *
         *  zero. If yes, there are at least 4 trailing zeros.                */
        if (!(n & 0xFFFFFFFFU))
        {
            bits += 32;
            n >>= 32;
        }

        /*  The next 16-bits.                                                 */
        if (!(n & 0xFFFFU))
        {
            bits += 16;
            n >>= 16;
        }

        /*  The next 8 bits.                                                  */
        if (!(n & 0xFFU))
        {
            bits += 8;
            n >>= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0x0FU))
        {
            bits += 4;
            n >>= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0x03U))
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
/*  End of tmpl_UChar_Trailing_Zeros.                                         */

/*  All other strange architectures. There are 12-bit, 24-bit, 36-bit, and    *
 *  even 9-bit char's out there. The C standard requires char is at least 8   *
 *  bits wide, so we can loop through the bits of the number 8 at a time.     */
#else

/*  Portable trailing zeros function.                                         */
int tmpl_UChar_Trailing_Zeros(unsigned char n)
{
    /*  Variable for the number of trailing zeros.                            */
    int bits = 0;

    /*  If n is zero, return 0. That is, 0 has no trailing zeros.             */
    if (n != 0U)
    {
        /*  Keep zeroing out the lower 8 bits and shifting the number.        */
        while (!(n & 0xFFU))
        {
            bits += 8;
            n >>= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0x0FU))
        {
            bits += 4;
            n >>= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0x03U))
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
/*  End of tmpl_UChar_Trailing_Zeros.                                         */

#endif
/*  End of #if UCHAR_MAX == 0xFFU.                                            */
