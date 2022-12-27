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

/*  Only compile if libtmpl has long long support.                            */
#if TMPL_HAS_LONGLONG == 1

/*  The TMPL_ULLONG_BIT macro is found here.                                  */
#include <libtmpl/include/tmpl_limits.h>

/*  The C standard requires long long to be at least 64 bits wide.            */
#if TMPL_ULLONG_BIT == 64

/*  64-bit leading-zeros function.                                            */
int tmpl_ULLong_Leading_Zeros(unsigned long long int n)
{
    /*  Variable for the number of leading zeros.                             */
    int bits = 0;

    /*  If n is zero, return 0. That is, 0 has no leading zeros.              */
    if (n != 0U)
    {
        /*  Set the lower 32 bits to zero and see if the number ends up being *
         *  zero. If yes, there are at least 32 leading zeros.                */
        if (!(n & 0xFFFFFFFF00000000ULL))
        {
            bits += 32;
            n <<= 32;
        }

        /*  Next 16 bits.                                                     */
        if (!(n & 0xFFFF000000000000ULL))
        {
            bits += 16;
            n <<= 16;
        }

        /*  The next 8 bits.                                                  */
        if (!(n & 0xFF00000000000000ULL))
        {
            bits += 8;
            n <<= 8;
        }

        /*  The next four bits in the number.                                 */
        if (!(n & 0xF000000000000000ULL))
        {
            bits += 4;
            n <<= 4;
        }

        /*  Next two bits.                                                    */
        if (!(n & 0xC000000000000000ULL))
        {
            bits += 2;
            n <<= 2;
        }

        /*  The last bit of n.                                                */
        if (!(n & 0x8000000000000000ULL))
            bits += 1;
    }
    return bits;
}
/*  End of tmpl_ULLong_Leading_Zeros.                                         */

/*  This is for exotic systems. The C standard requires long long be at least *
 *  64 bits wide, so we can loop through the bits of the input 64 at a time.  */
#else

/*  Portable leading zeros function.                                          */
int tmpl_ULLong_Leading_Zeros(unsigned long long int n)
{
    /*  Variable for the number of leading zeros.                             */
    int bits = 0;
    const unsigned long long int zero = 0x00ULL;
    const unsigned long long int top64 = ~((~zero) >> 32ULL);
    const unsigned long long int top32 = ~((~zero) >> 32ULL);
    const unsigned long long int top16 = ~((~zero) >> 16ULL);
    const unsigned long long int top8 = ~((~zero) >> 8ULL);
    const unsigned long long int top4 = ~((~zero) >> 4ULL);
    const unsigned long long int top2 = ~((~zero) >> 2ULL);
    const unsigned long long int top1 = ~((~zero) >> 1ULL);

    /*  If n is zero, return 0. That is, 0 has no leading zeros.              */
    if (n != 0U)
    {
        /*  Keep zeroing out the lower 32 bits and shifting the number.       */
        while (!(n & top64))
        {
            bits += 64;
            n <<= 64;
        }

        /*  Next 32 bits.                                                     */
        if (!(n & top32))
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
/*  End of tmpl_ULLong_Leading_Zeros.                                         */

#endif
/*  End of #if TMPL_ULLONG_BIT == 64.                                         */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */
