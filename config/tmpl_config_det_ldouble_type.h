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
 *                        tmpl_config_det_ldouble_type                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Detects how long double is implemented by the compiler.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_det_ldouble_type                                                 *
 *  Purpose:                                                                  *
 *      Determines how long double is implemented by the compiler.            *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      ldouble_type (enum tmpl_ldouble_type):                                *
 *          enum representing how ldouble is implemented.                     *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_uchar_width.h:                                    *
 *              tmpl_det_uchar_width:                                         *
 *                  Computes the number of bits in unsigned char.             *
 *  Method:                                                                   *
 *      Use type punning to set the bits of a long double to the bit pattern  *
 *      that represents 1 for either a 64-bit double, 80-bit extended,        *
 *      128-bit extended, or 128-bit double-double, trying both little and    *
 *      big endianness. If none of these work, return unknown.                *
 *  Notes:                                                                    *
 *      1.) This function only attempts to check if long double is either     *
 *          64-bits, 96-bits, or 128-bits.                                    *
 *      2.) This function checks for both big endianness and little           *
 *          endianness.                                                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_globals.h:                                                *
 *          Header file with all of the globals used by config.c.             *
 *  2.) tmpl_config_det_uchar_width.h:                                        *
 *          Provides the tmpl_det_uchar_width function.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/08: Ryan Maguire                                                  *
 *      Moved function to its own file.                                       *
 *  2025/10/27: Ryan Maguire                                                  *
 *      Moved enum definition to the config globals file.                     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_DET_LDOUBLE_TYPE_H
#define TMPL_CONFIG_DET_LDOUBLE_TYPE_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  tmpl_det_uchar_width function provided here.                              */
#include "tmpl_config_det_uchar_width.h"

/*  Function for determining the type of long double implemented.             */
static enum tmpl_ldouble_type tmpl_det_ldouble_type(void)
{
    /*  If the user does not want IEEE support, this function returns unknown.*/
#ifndef TMPL_SET_TMPL_USE_IEEE_FALSE

    /*  The most common type of long double for personal computers is the     *
     *  little endian amd64 format (also the x86_64 format). This uses        *
     *  the IEEE-754 extended precision 80-bit format with 48-bits of padding *
     *  to create a single 128-bit object. The padding components are junk    *
     *  and can almost always be ignored.                                     */
    union {
        struct {
            unsigned int man3 : 16;
            unsigned int man2 : 16;
            unsigned int man1 : 16;
            unsigned int man0 : 15;

            /*  The 80-bit extended format specifies that the 64th bit is the *
             *  integer part of the mantissa. That is, the value n in the     *
             *  representation x = n.m * 2^e (m is the rest of the mantissa,  *
             *  e is the exponent). It is a single bit and can be 0 or 1.     */
            unsigned int intr : 1;
            unsigned int expo : 15;
            unsigned int sign : 1;
            unsigned int pad2 : 16;
            unsigned int pad1 : 16;
            unsigned int pad0 : 16;
        } bits;

        /*  Long double the above struct represents.                          */
        long double r;
    } amd64_type;

    /*  Similar to amd64, but big endian. GCC uses this with ia64.            */
    union {
        struct {
            unsigned int pad0 : 16;
            unsigned int pad1 : 16;
            unsigned int sign : 1;
            unsigned int expo : 15;
            unsigned int pad2 : 16;
            unsigned int intr : 1;
            unsigned int man0 : 15;
            unsigned int man1 : 16;
            unsigned int man2 : 16;
            unsigned int man3 : 16;
        } bits;

        /*  Long double the above struct represents.                          */
        long double r;
    } ia64_type;

    /*  The i386 architecture uses a 96-bit implementation. This uses the     *
     *  80-bit extended precision with 16 bits of padding.                    */
    union {
        struct {
            unsigned int man3 : 16;
            unsigned int man2 : 16;
            unsigned int man1 : 16;
            unsigned int man0 : 15;
            unsigned int intr : 1;
            unsigned int expo : 15;
            unsigned int sign : 1;
            unsigned int pad0 : 16;
        } little_bits;

        struct {
            unsigned int sign : 1;
            unsigned int expo : 15;
            unsigned int pad0 : 16;
            unsigned int intr : 1;
            unsigned int man0 : 15;
            unsigned int man1 : 16;
            unsigned int man2 : 16;
            unsigned int man3 : 16;
        } big_bits;

        /*  Long double the above struct represents.                          */
        long double r;
    } i386_type;

    /*  aarch64 uses the 128-bit quadruple precision for long double.         */
    union {
        struct {
            unsigned int man6 : 16;
            unsigned int man5 : 16;
            unsigned int man4 : 16;
            unsigned int man3 : 16;
            unsigned int man2 : 16;
            unsigned int man1 : 16;
            unsigned int man0 : 16;
            unsigned int expo : 15;
            unsigned int sign : 1;
        } bits;
        long double r;
    } aarch64_type;

    /*  MIPS little endian uses the same structure as double, 64 bit. Note,   *
     *  Microsoft's C Compiler does not support higher precision than double  *
     *  and long double is the same size as double.                           */
    union {
        struct {
            unsigned int man3 : 16;
            unsigned int man2 : 16;
            unsigned int man1 : 16;
            unsigned int man0 : 4;
            unsigned int expo : 11;
            unsigned int sign : 1;
        } bits;
        long double r;
    } mips_little_type;

    /*  MIPS for big endian. PowerPC and S390 also implement long double      *
     *  using this style, which is the same as double.                        */
    union {
        struct {
            unsigned int sign : 1;
            unsigned int expo : 11;
            unsigned int man0 : 4;
            unsigned int man1 : 16;
            unsigned int man2 : 16;
            unsigned int man3 : 16;
        } bits;
        long double r;
    } mips_big_type;

    /*  After some trial and error, I managed to figure out how GCC           *
     *  implements long double on the s390x architecture (64-bit, big endian).*
     *  It uses IEEE-754 quadruple precision, with big endianness. This is    *
     *  similar to ARM64, but with the order flipped.                         */
    union {
        struct {
            unsigned int sign : 1;
            unsigned int expo : 15;
            unsigned int man0 : 16;
            unsigned int man1 : 16;
            unsigned int man2 : 16;
            unsigned int man3 : 16;
            unsigned int man4 : 16;
            unsigned int man5 : 16;
            unsigned int man6 : 16;
        } bits;
        long double r;
    } s390x_type;

    /*  GCC implements long double as 128-bit double-double on ppc64el.       */
    union {
        struct {
            /*  The most significant double.                                  */
            unsigned int man3a : 16;
            unsigned int man2a : 16;
            unsigned int man1a : 16;
            unsigned int man0a : 4;
            unsigned int expoa : 11;
            unsigned int signa : 1;

            /*  The least significant double.                                 */
            unsigned int man3b : 16;
            unsigned int man2b : 16;
            unsigned int man1b : 16;
            unsigned int man0b : 4;
            unsigned int expob : 11;
            unsigned int signb : 1;
        } bits;
        long double r;
    } powerpc_little_type;

    /*  GCC implements long double as 128-bit double double on powerpc.       */
    union {
        struct {
            /*  The most significant double.                                  */
            unsigned int signa : 1;
            unsigned int expoa : 11;
            unsigned int man0a : 4;
            unsigned int man1a : 16;
            unsigned int man2a : 16;
            unsigned int man3a : 16;

            /*  The least significant double.                                 */
            unsigned int signb : 1;
            unsigned int expob : 11;
            unsigned int man0b : 4;
            unsigned int man1b : 16;
            unsigned int man2b : 16;
            unsigned int man3b : 16;
        } bits;
        long double r;
    } powerpc_big_type;

    /*  We need to use the global value tmpl_uchar_width. Check that it has   *
     *  been computed already. If not, compute it.                            */
    if (!tmpl_all_widths_are_known)
        tmpl_check_widths();

    /*  Try the 64-bit types first.                                           */
    if ((sizeof(long double) * tmpl_uchar_width) == 64)
    {
        /*  MIPS big endian (or PowerPC, or s390).                            */
        mips_big_type.bits.man3 = 0x0U;
        mips_big_type.bits.man2 = 0x0U;
        mips_big_type.bits.man1 = 0x0U;
        mips_big_type.bits.man0 = 0x0U;
        mips_big_type.bits.expo = 0x3FFU;
        mips_big_type.bits.sign = 0x0U;

        if (mips_big_type.r == 1.0L)
            return tmpl_ldouble_64_bit_big_endian;

        /*  Next, MIPS little endian (or Microsoft compiler, amd64).          */
        mips_little_type.bits.man3 = 0x0U;
        mips_little_type.bits.man2 = 0x0U;
        mips_little_type.bits.man1 = 0x0U;
        mips_little_type.bits.man0 = 0x0U;
        mips_little_type.bits.expo = 0x3FFU;
        mips_little_type.bits.sign = 0x0U;

        if (mips_little_type.r == 1.0L)
            return tmpl_ldouble_64_bit_little_endian;
    }

    /*  96-bit implementations.                                               */
    else if ((sizeof(long double) * tmpl_uchar_width) == 96)
    {
        /*  Try the i386 implementation.                                      */
        i386_type.big_bits.man3 = 0x0U;
        i386_type.big_bits.man2 = 0x0U;
        i386_type.big_bits.man1 = 0x0U;
        i386_type.big_bits.man0 = 0x0U;
        i386_type.big_bits.intr = 0x1U;
        i386_type.big_bits.expo = 0x3FFFU;
        i386_type.big_bits.sign = 0x0U;
        i386_type.big_bits.pad0 = 0x0U;

        if (i386_type.r == 1.0L)
            return tmpl_ldouble_96_bit_extended_big_endian;

        /*  Try little endianness as well.                                    */
        i386_type.little_bits.man3 = 0x0U;
        i386_type.little_bits.man2 = 0x0U;
        i386_type.little_bits.man1 = 0x0U;
        i386_type.little_bits.man0 = 0x0U;
        i386_type.little_bits.intr = 0x1U;
        i386_type.little_bits.expo = 0x3FFFU;
        i386_type.little_bits.sign = 0x0U;
        i386_type.little_bits.pad0 = 0x0U;

        if (i386_type.r == 1.0L)
            return tmpl_ldouble_96_bit_extended_little_endian;
    }
    else if ((sizeof(long double) * tmpl_uchar_width) == 128)
    {
        /*  Set the bits to represent 1.0 for AMD64 architecture.             */
        amd64_type.bits.man3 = 0x0U;
        amd64_type.bits.man2 = 0x0U;
        amd64_type.bits.man1 = 0x0U;
        amd64_type.bits.man0 = 0x0U;
        amd64_type.bits.intr = 0x1U;
        amd64_type.bits.expo = 0x3FFFU;
        amd64_type.bits.sign = 0x0U;
        amd64_type.bits.pad0 = 0x0U;
        amd64_type.bits.pad1 = 0x0U;
        amd64_type.bits.pad2 = 0x0U;

        /*  Check if this worked.                                             */
        if (amd64_type.r == 1.0L)
            return tmpl_ldouble_128_bit_extended_little_endian;

        ia64_type.bits.man3 = 0x0U;
        ia64_type.bits.man2 = 0x0U;
        ia64_type.bits.man1 = 0x0U;
        ia64_type.bits.man0 = 0x0U;
        ia64_type.bits.intr = 0x1U;
        ia64_type.bits.expo = 0x3FFFU;
        ia64_type.bits.sign = 0x0U;
        ia64_type.bits.pad0 = 0x0U;
        ia64_type.bits.pad1 = 0x0U;
        ia64_type.bits.pad2 = 0x0U;

        /*  Check if this worked.                                             */
        if (ia64_type.r == 1.0L)
            return tmpl_ldouble_128_bit_extended_big_endian;

        /*  Next, try aarch64.                                                */
        aarch64_type.bits.man6 = 0x0U;
        aarch64_type.bits.man5 = 0x0U;
        aarch64_type.bits.man4 = 0x0U;
        aarch64_type.bits.man3 = 0x0U;
        aarch64_type.bits.man2 = 0x0U;
        aarch64_type.bits.man1 = 0x0U;
        aarch64_type.bits.man0 = 0x0U;
        aarch64_type.bits.expo = 0x3FFFU;
        aarch64_type.bits.sign = 0x0U;

        if (aarch64_type.r == 1.0L)
            return tmpl_ldouble_128_bit_quadruple_little_endian;

        /*  s390x architecture using GCC.                                     */
        s390x_type.bits.man6 = 0x0U;
        s390x_type.bits.man5 = 0x0U;
        s390x_type.bits.man4 = 0x0U;
        s390x_type.bits.man3 = 0x0U;
        s390x_type.bits.man2 = 0x0U;
        s390x_type.bits.man1 = 0x0U;
        s390x_type.bits.man0 = 0x0U;
        s390x_type.bits.expo = 0x3FFFU;
        s390x_type.bits.sign = 0x0U;

        if (s390x_type.r == 1.0L)
            return tmpl_ldouble_128_bit_quadruple_big_endian;

        /*  Lastly, try the two double-double implementations.                */
        powerpc_little_type.bits.man3a = 0x0U;
        powerpc_little_type.bits.man2a = 0x0U;
        powerpc_little_type.bits.man1a = 0x0U;
        powerpc_little_type.bits.man0a = 0x0U;
        powerpc_little_type.bits.expoa = 0x3FFU;
        powerpc_little_type.bits.signa = 0x0U;
        powerpc_little_type.bits.man3b = 0x0U;
        powerpc_little_type.bits.man2b = 0x0U;
        powerpc_little_type.bits.man1b = 0x0U;
        powerpc_little_type.bits.man0b = 0x0U;
        powerpc_little_type.bits.expob = 0x0U;
        powerpc_little_type.bits.signb = 0x0U;

        if (powerpc_little_type.r == 1.0L)
            return tmpl_ldouble_128_bit_doubledouble_little_endian;

        powerpc_big_type.bits.man3a = 0x0U;
        powerpc_big_type.bits.man2a = 0x0U;
        powerpc_big_type.bits.man1a = 0x0U;
        powerpc_big_type.bits.man0a = 0x0U;
        powerpc_big_type.bits.expoa = 0x3FFU;
        powerpc_big_type.bits.signa = 0x0U;
        powerpc_big_type.bits.man3b = 0x0U;
        powerpc_big_type.bits.man2b = 0x0U;
        powerpc_big_type.bits.man1b = 0x0U;
        powerpc_big_type.bits.man0b = 0x0U;
        powerpc_big_type.bits.expob = 0x0U;
        powerpc_big_type.bits.signb = 0x0U;

        if (powerpc_big_type.r == 1.0L)
            return tmpl_ldouble_128_bit_doubledouble_big_endian;
    }

#endif
/*  End of #ifndef TMPL_SET_TMPL_USE_IEEE_FALSE.                              */

    /*  If all failed, return unknown.                                        */
    return tmpl_ldouble_unknown;
}
/*  End of tmpl_det_ldouble_type.                                             */

#endif
/*  End of include guard.                                                     */
