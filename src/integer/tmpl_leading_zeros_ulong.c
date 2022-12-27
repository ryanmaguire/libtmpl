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

/*  Function prototype here.                                                  */
#include <libtmpl/include/tmpl_integer.h>

/*  The TMPL_ULONG_BIT macro is found here.                                   */
#include <libtmpl/include/tmpl_limits.h>

/*  The C standard requires long to be at least 32 bits wide.                 */
#if TMPL_ULONG_BIT == 32

/*  32-bit leading-zeros function.                                            */
int tmpl_ULong_Leading_Zeros(unsigned long int n)
{
    /*  Variable for the number of leading zeros.                             */
    int bits = 0;

    /*  If n is zero, return 0. That is, 0 has no leading zeros.              */
    if (n != 0U)
    {
        /*  Set the lower 16 bits to zero and see if the number ends up being *
         *  zero. If yes, there are at least 16 leading zeros.                */
        if (!(n & 0xFFFF0000UL))
        {
            bits += 16;
            n <<= 16;
        }

        /*  The next 8 bits.                                                  */
        if (!(n & 0xFF000000UL))
        {
            bits += 8;
            n <<= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0xF0000000UL))
        {
            bits += 4;
            n <<= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0xC0000000UL))
        {
            bits += 2;
            n <<= 2;
        }

        /*  The last bit of n.                                                */
        if (!(n & 0x80000000UL))
            bits += 1;
    }
    return bits;
}
/*  End of tmpl_ULong_Leading_Zeros.                                          */

/*  64-bit long. Common on GNU/Linux and macOS.                               */
#elif TMPL_ULONG_BIT == 64

/*  64-bit leading-zeros function.                                            */
int tmpl_ULong_Leading_Zeros(unsigned long int n)
{
    /*  Variable for the number of leading zeros.                             */
    int bits = 0;

    /*  If n is zero, return 0. That is, 0 has no leading zeros.              */
    if (n != 0U)
    {
        /*  Set the lower 32 bits to zero and see if the number ends up being *
         *  zero. If yes, there are at least 32 leading zeros.                */
        if (!(n & 0xFFFFFFFF00000000UL))
        {
            bits += 32;
            n <<= 32;
        }

        /*  Next 16 bits.                                                     */
        if (!(n & 0xFFFF000000000000UL))
        {
            bits += 16;
            n <<= 16;
        }

        /*  The next 8 bits.                                                  */
        if (!(n & 0xFF00000000000000UL))
        {
            bits += 8;
            n <<= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0xF000000000000000UL))
        {
            bits += 4;
            n <<= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0xC000000000000000UL))
        {
            bits += 2;
            n <<= 2;
        }

        /*  The last bit of n.                                                */
        if (!(n & 0x8000000000000000UL))
            bits += 1;
    }
    return bits;
}
/*  End of tmpl_ULong_Leading_Zeros.                                          */

/*  This is for exotic systems. The C standard requires long to be at least   *
 *  32 bits wide, so we can loop through the bits of the input 32 at a time.  */
#else

/*  Portable leading zeros function.                                          */
int tmpl_ULong_Leading_Zeros(unsigned long int n)
{
    /*  Variable for the number of leading zeros.                             */
    int bits = 0;
    const unsigned long int zero = 0x00UL;
    const unsigned long int top32 = ~((~zero) >> 32UL);
    const unsigned long int top16 = ~((~zero) >> 16UL);
    const unsigned long int top8 = ~((~zero) >> 8UL);
    const unsigned long int top4 = ~((~zero) >> 4UL);
    const unsigned long int top2 = ~((~zero) >> 2UL);
    const unsigned long int top1 = ~((~zero) >> 1UL);

    /*  If n is zero, return 0. That is, 0 has no leading zeros.              */
    if (n != 0U)
    {
        /*  Keep zeroing out the lower 32 bits and shifting the number.       */
        while (!(n & top32))
        {
            bits += 32;
            n <<= 32;
        }

        /*  Next 16 bits.                                                     */
        if (!(n & top16))
        {
            bits += 16;
            n <<= 16;
        }

        /*  The next 8 bits.                                                  */
        if (!(n & top8))
        {
            bits += 8;
            n <<= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & top4))
        {
            bits += 4;
            n <<= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & top2))
        {
            bits += 2;
            n <<= 2;
        }

        /*  The last bit of n.                                                */
        if (!(n & top1))
            bits += 1;
    }
    return bits;
}
/*  End of tmpl_ULong_Leading_Zeros.                                          */

#endif
/*  End of #if TMPL_ULONG_BIT == 64.                                          */
