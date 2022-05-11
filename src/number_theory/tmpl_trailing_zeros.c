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
 *                            tmpl_trailing_zeros                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the number of trailing zeros, in binary, of an integer.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UInt_Trailing_Zeros:                                             *
 *  Purpose:                                                                  *
 *      Given an unsigned int n, returns the number of trailing zeros for the *
 *      binary representation of n. Ex. If n = 8, then in binary n = 1000_2,  *
 *      so the number of trailing zeros is 3.                                 *
 *  Arguments:                                                                *
 *      n (unsigned int):                                                     *
 *          A non-negative integer.                                           *
 *  Output:                                                                   *
 *      zeros (unsigned int):                                                 *
 *          The number of trailing zeros for n.                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If unsigned int is 16, 32, or 64 bit, use a simple O(1) algorithm to  *
 *      compute the number of trailing zeros. If not, a portable algorithm is *
 *      implemented, though it is slightly slower.                            *
 *  Notes:                                                                    *
 *      If n = 0, the number of trailing zeros is zero.                       *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_number_theory.h:                                                 *
 *          Header where the function prototype is defined.                   *
 *  2.) limits.h:                                                             *
 *          Standard C library header file containing information on the size *
 *          of an unsigned int.                                               *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2021/07/30                                                        *
 ******************************************************************************/

/*  Function prototype here.                                                  */
#include <libtmpl/include/tmpl_number_theory.h>

/*  Size of unsigned int here.                                                */
#include <limits.h>

/*  16-bit trailing-zeros function.                                           */
#define TMPL_8BIT_TRAILING_ZEROS(type, fname)                                  \
unsigned int fname(type n)                                                     \
{                                                                              \
    /*  Variable for the number of trailing zeros.                           */\
    unsigned int bits = 0U;                                                    \
                                                                               \
    /*  If n is zero, return 0. That is, 0 has no trailing zeros.            */\
    if (n > 0U)                                                                \
    {                                                                          \
        /*  Set the upper 4 bits to zero and see if the number ends up being */\
        /*  zero. If yes, there are at least 4 trailing zeros.               */\
        if (!(n & 0x000FU))                                                    \
        {                                                                      \
            bits += 4U;                                                        \
            n >>= 4;                                                           \
        }                                                                      \
                                                                               \
        /*  Next two bits.                                                   */\
        if (!(n & 0x0003U))                                                    \
        {                                                                      \
            bits += 2U;                                                        \
            n >>= 2;                                                           \
        }                                                                      \
                                                                               \
        /*  The last bit can be done with a bitwise XOR.                     */\
        bits += (n & 1U) ^ 1U;                                                 \
    }                                                                          \
    return bits;                                                               \
}
/*  End of TMPL_8BIT_TRAILING_ZEROS.                                          */

/*  16-bit trailing-zeros function.                                           */
#define TMPL_16BIT_TRAILING_ZEROS(type, fname)                                 \
unsigned int fname(type n)                                                     \
{                                                                              \
    /*  Variable for the number of trailing zeros.                           */\
    unsigned int bits = 0U;                                                    \
                                                                               \
    /*  If n is zero, return 0. That is, 0 has no trailing zeros.            */\
    if (n > 0U)                                                                \
    {                                                                          \
        /*  Set the upper 8 bits to zero and see if the number ends up being */\
        /*  zero. If yes, there are at least 8 trailing zeros.               */\
        if (!(n & 0x00FFU))                                                    \
        {                                                                      \
            bits += 8U;                                                        \
            n >>= 8;                                                           \
        }                                                                      \
                                                                               \
        /*  Same thing with the next 4 bits.                                 */\
        if (!(n & 0x000FU))                                                    \
        {                                                                      \
            bits += 4U;                                                        \
            n >>= 4;                                                           \
        }                                                                      \
                                                                               \
        /*  Next two bits.                                                   */\
        if (!(n & 0x0003U))                                                    \
        {                                                                      \
            bits += 2U;                                                        \
            n >>= 2;                                                           \
        }                                                                      \
                                                                               \
        /*  The last bit can be done with a bitwise XOR.                     */\
        bits += (n & 1U) ^ 1U;                                                 \
    }                                                                          \
    return bits;                                                               \
}
/*  End of TMPL_16BIT_TRAILING_ZEROS.                                         */

/*  32-bit trailing-zeros function.                                           */
#define TMPL_32BIT_TRAILING_ZEROS(type, fname)                                 \
unsigned int fname(type n)                                                     \
{                                                                              \
    /*  Variable for the number of trailing zeros.                           */\
    unsigned int bits = 0U;                                                    \
                                                                               \
    /*  If n is zero, return 0. That is, 0 has no trailing zeros.            */\
    if (n > 0U)                                                                \
    {                                                                          \
        /*  Set the upper 16 bits to zero and see if the number ends up as   */\
        /*  zero. If yes, there are at least 16 trailing zeros.              */\
        if (!(n & 0x0000FFFFU))                                                \
        {                                                                      \
            bits += 16U;                                                       \
            n >>= 16;                                                          \
        }                                                                      \
                                                                               \
        /*  Same thing with the next 8 bits.                                 */\
        if (!(n & 0x000000FFU))                                                \
        {                                                                      \
            bits += 8U;                                                        \
            n >>= 8;                                                           \
        }                                                                      \
                                                                               \
        /*  Same thing with the next 4 bits.                                 */\
        if (!(n & 0x0000000FU))                                                \
        {                                                                      \
            bits += 4U;                                                        \
            n >>= 4;                                                           \
        }                                                                      \
                                                                               \
        /*  Next two bits.                                                   */\
        if (!(n & 0x00000003U))                                                \
        {                                                                      \
            bits += 2U;                                                        \
            n >>= 2;                                                           \
        }                                                                      \
                                                                               \
        /*  The last bit can be done with a bitwise XOR.                     */\
        bits += (n & 1U) ^ 1U;                                                 \
    }                                                                          \
    return bits;                                                               \
}
/*  End of TMPL_32BIT_TRAILING_ZEROS.                                         */

/*  64-bit trailing-zeros function.                                           */
#define TMPL_64BIT_TRAILING_ZEROS(type, fname)                                 \
unsigned int fname(type n)                                                     \
{                                                                              \
    /*  Variable for the number of trailing zeros.                           */\
    unsigned int bits = 0U;                                                    \
                                                                               \
    /*  If n is zero, return 0. That is, 0 has no trailing zeros.            */\
    if (n > 0U)                                                                \
    {                                                                          \
        /*  Set the upper 32 bits to zero and see if the number ends up as   */\
        /*  zero. If yes, there are at least 32 trailing zeros.              */\
        if (!(n & 0xFFFFFFFFU))                                                \
        {                                                                      \
            bits += 32U;                                                       \
            n >>= 32;                                                          \
        }                                                                      \
                                                                               \
        /*  Same thing with the next 16 bits.                                */\
        if (!(n & 0xFFFFU))                                                    \
        {                                                                      \
            bits += 16U;                                                       \
            n >>= 16;                                                          \
        }                                                                      \
                                                                               \
        /*  Same thing with the next 8 bits.                                 */\
        if (!(n & 0xFFU))                                                      \
        {                                                                      \
            bits += 8U;                                                        \
            n >>= 8;                                                           \
        }                                                                      \
                                                                               \
        /*  Same thing with the next 4 bits.                                 */\
        if (!(n & 0x0FU))                                                    \
        {                                                                      \
            bits += 4U;                                                        \
            n >>= 4;                                                           \
        }                                                                      \
                                                                               \
        /*  Next two bits.                                                   */\
        if (!(n & 0x03U))                                                      \
        {                                                                      \
            bits += 2U;                                                        \
            n >>= 2;                                                           \
        }                                                                      \
                                                                               \
        /*  The last bit can be done with a bitwise XOR.                     */\
        bits += (n & 1U) ^ 1U;                                                 \
    }                                                                          \
    return bits;                                                               \
}
/*  End of TMPL_64BIT_TRAILING_ZEROS.                                         */

/*  Portable trailing-zeros function.                                         */
#define TMPL_PORTABLE_TRAILING_ZEROS(type, fname)                              \
unsigned int fname(type n)                                                     \
{                                                                              \
    /*  Variable for the number of trailing zeros.                           */\
    unsigned int bits = 0U;                                                    \
                                                                               \
    /*  If n is zero, return 0. That is, 0 has no trailing zeros.            */\
    if (n > 0U)                                                                \
    {                                                                          \
        /*  Keep zeroing out all but the lower 16 bits, since we don't know  */\
        /*  the size of the integer. Once this loop finishes, we're down to  */\
        /*  the last 16 bits of the integer and can proceed as normal.       */\
        while (!(n & 0xFFFFU))                                                 \
        {                                                                      \
            bits += 16U;                                                       \
            n >>= 16;                                                          \
        }                                                                      \
                                                                               \
        /*  Same thing with the next 8 bits.                                 */\
        if (!(n & 0xFFU))                                                      \
        {                                                                      \
            bits += 8U;                                                        \
            n >>= 8;                                                           \
        }                                                                      \
                                                                               \
        /*  Same thing with the next 4 bits.                                 */\
        if (!(n & 0x0000000FU))                                                \
        {                                                                      \
            bits += 4U;                                                        \
            n >>= 4;                                                           \
        }                                                                      \
                                                                               \
        /*  Next two bits.                                                   */\
        if (!(n & 0x00000003U))                                                \
        {                                                                      \
            bits += 2U;                                                        \
            n >>= 2;                                                           \
        }                                                                      \
                                                                               \
        /*  The last bit can be done with a bitwise XOR.                     */\
        bits += (n & 1U) ^ 1U;                                                 \
    }                                                                          \
    return bits;                                                               \
}
/*  End of TMPL_PORTABLE_TRAILING_ZEROS.                                      */

#if UCHAR_MAX == 0xFF
TMPL_8BIT_TRAILING_ZEROS(unsigned char, tmpl_UChar_Trailing_Zeros)
#elif UCHAR_MAX == 0xFFFF
TMPL_16BIT_TRAILING_ZEROS(unsigned char, tmpl_UChar_Trailing_Zeros)
#elif UCHAR_MAX == 0xFFFFFFFF
TMPL_32BIT_TRAILING_ZEROS(unsigned char, tmpl_UChar_Trailing_Zeros)
#elif UCHAR_MAX == 0xFFFFFFFFFFFFFFFF
TMPL_64BIT_TRAILING_ZEROS(unsigned char, tmpl_UChar_Trailing_Zeros)
#else
TMPL_PORTABLE_TRAILING_ZEROS(unsigned char, tmpl_UChar_Trailing_Zeros)
#endif

#if USHRT_MAX == 0xFF
TMPL_8BIT_TRAILING_ZEROS(unsigned short int, tmpl_UShort_Trailing_Zeros)
#elif USHRT_MAX == 0xFFFF
TMPL_16BIT_TRAILING_ZEROS(unsigned short int, tmpl_UShort_Trailing_Zeros)
#elif USHRT_MAX == 0xFFFFFFFF
TMPL_32BIT_TRAILING_ZEROS(unsigned short int, tmpl_UShort_Trailing_Zeros)
#elif USHRT_MAX == 0xFFFFFFFFFFFFFFFF
TMPL_64BIT_TRAILING_ZEROS(unsigned short int, tmpl_UShort_Trailing_Zeros)
#else
TMPL_PORTABLE_TRAILING_ZEROS(unsigned short int, tmpl_UShort_Trailing_Zeros)
#endif

#if UINT_MAX == 0xFF
TMPL_8BIT_TRAILING_ZEROS(unsigned int, tmpl_UInt_Trailing_Zeros)
#elif UINT_MAX == 0xFFFF
TMPL_16BIT_TRAILING_ZEROS(unsigned int, tmpl_UInt_Trailing_Zeros)
#elif UINT_MAX == 0xFFFFFFFF
TMPL_32BIT_TRAILING_ZEROS(unsigned int, tmpl_UInt_Trailing_Zeros)
#elif UINT_MAX == 0xFFFFFFFFFFFFFFFF
TMPL_64BIT_TRAILING_ZEROS(unsigned int, tmpl_UInt_Trailing_Zeros)
#else
TMPL_PORTABLE_TRAILING_ZEROS(unsigned int, tmpl_UInt_Trailing_Zeros)
#endif

#if ULONG_MAX == 0xFF
TMPL_8BIT_TRAILING_ZEROS(unsigned long int, tmpl_ULong_Trailing_Zeros)
#elif ULONG_MAX == 0xFFFF
TMPL_16BIT_TRAILING_ZEROS(unsigned long int, tmpl_ULong_Trailing_Zeros)
#elif ULONG_MAX == 0xFFFFFFFF
TMPL_32BIT_TRAILING_ZEROS(unsigned long int, tmpl_ULong_Trailing_Zeros)
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF
TMPL_64BIT_TRAILING_ZEROS(unsigned long int, tmpl_ULong_Trailing_Zeros)
#else
TMPL_PORTABLE_TRAILING_ZEROS(unsigned long int, tmpl_ULong_Trailing_Zeros)
#endif

#undef TMPL_8BIT_TRAILING_ZEROS
#undef TMPL_16BIT_TRAILING_ZEROS
#undef TMPL_32BIT_TRAILING_ZEROS
#undef TMPL_64BIT_TRAILING_ZEROS
#undef TMPL_PORTABLE_TRAILING_ZEROS
