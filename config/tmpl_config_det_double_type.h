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
 *                        tmpl_config_det_double_type                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Detects how double is implemented by the compiler.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_det_double_type                                                  *
 *  Purpose:                                                                  *
 *      Determines how double is implemented by the compiler.                 *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      double_type (enum tmpl_double_type):                                  *
 *          enum representing how double is implemented.                      *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_uchar_width.h:                                    *
 *              tmpl_det_uchar_width:                                         *
 *                  Computes the number of bits in unsigned char.             *
 *  Method:                                                                   *
 *      Use type punning to set the bits of a double to the bit pattern that  *
 *      represents 1 for an IEEE-754 64-bit double. Try this for both big     *
 *      endianness and little endianness. If neither endianness produces      *
 *      1.0 as a double, return unknown.                                      *
 *  Notes:                                                                    *
 *      1.) This function only attempts to check if double is a 64-bit        *
 *          IEEE-754 double precision floating point number. It will not      *
 *          attempt to check any of the other possible representations and    *
 *          will instead simply return unknown.                               *
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
#ifndef TMPL_CONFIG_DET_DOUBLE_TYPE_H
#define TMPL_CONFIG_DET_DOUBLE_TYPE_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  tmpl_det_uchar_width function provided here.                              */
#include "tmpl_config_det_uchar_width.h"

/*  Function for determining the type of double implemented.                  */
static enum tmpl_double_type tmpl_det_double_type(void)
{
    /*  If the user does not want IEEE support, this function returns unknown.*/
#ifndef TMPL_SET_TMPL_USE_IEEE_FALSE

    /*  libtmpl has many tools that can take advantage of the IEEE-754        *
     *  floating point format, if your compiler supports it. The format does  *
     *  not specify the endianness of floating point numbers, so this         *
     *  function attempts to determine this. If your compiler does not        *
     *  support IEEE-754 format at all (most do in modern times), the         *
     *  endianness will be set to unknown and none of those tools will be     *
     *  used in libtmpl.                                                      *
     *  The IEEE-754 format specifies that a 64-bit double is comprised of a  *
     *  sign bit (positive or negative), 11 bits for the exponent (the value  *
     *  b in the expression x = 1.m * 2^b), and 52 bits for the mantissa (the *
     *  value m in x = 1.m * 2^b). Big endian will have sign -> expo -> mant, *
     *  whereas little endian will have mant -> expo -> sign. Use a union     *
     *  with two structs and a double to determine which one, if either, is   *
     *  implemented.                                                          */
    union {

        /*  Store the bits in a bit-field. This allows us to store an exact   *
         *  number of bits (up to 16, per the standard) for a single variable *
         *  inside the struct. Use this to have 1 bit for the sign, 11 bits   *
         *  for the exponent, and 52 bits for the mantissa. Note, to avoid    *
         *  padding (adding extra redundant bits), ensure that the 4-bit      *
         *  mantissa component is adjacent to the 11 bit exponent. This way   *
         *  the sign, exponent, and smallest mantissa component will occupy a *
         *  16 bit block and no padding will be needed.                       */
        struct _big_bits {
            unsigned int sign : 1;
            unsigned int expo : 11;
            unsigned int man0 : 4;
            unsigned int man1 : 16;
            unsigned int man2 : 16;
            unsigned int man3 : 16;
        } big_bits;

        /*  Little endianness is the reverse of big endianness.               */
        struct _little_bits {
            unsigned int man3 : 16;
            unsigned int man2 : 16;
            unsigned int man1 : 16;
            unsigned int man0 : 4;
            unsigned int expo : 11;
            unsigned int sign : 1;
        } little_bits;

        /*  And lastly, a double that the above structs are representing.     */
        double r;
    } d;

    /*  We need to use the global value tmpl_uchar_width. Check that it has   *
     *  been computed already. If not, compute it.                            */
    if (!tmpl_all_widths_are_known)
        tmpl_det_widths();

    /*  double should have 64 bits. Check for this.                           */
    if ((sizeof(double) * tmpl_uchar_width) != 64)
        return tmpl_double_unknown_endian;

    /*  Set the bits to represent 1.0 using the IEEE-754 format. If this is   *
     *  big endian, we should get gibberish. If it's little endian, we should *
     *  get exactly 1.0.                                                      */
    d.little_bits.sign = 0x0U;
    d.little_bits.expo = 0x3FFU;
    d.little_bits.man0 = 0x0U;
    d.little_bits.man1 = 0x0U;
    d.little_bits.man2 = 0x0U;
    d.little_bits.man3 = 0x0U;

    /*  If the double in the union is actually 1 we have IEEE-754 support and *
     *  we have little endianness for double.                                 */
    if (d.r == 1.0)
        return tmpl_double_little_endian;

    /*  Otherwise, try big endian.                                            */
    d.big_bits.sign = 0x0U;
    d.big_bits.expo = 0x3FFU;
    d.big_bits.man0 = 0x0U;
    d.big_bits.man1 = 0x0U;
    d.big_bits.man2 = 0x0U;
    d.big_bits.man3 = 0x0U;

    /*  Check if the double is 1.                                             */
    if (d.r == 1.0)
        return tmpl_double_big_endian;

#endif
/*  End of #ifndef TMPL_SET_TMPL_USE_IEEE_FALSE.                              */

    /*  If not, IEEE-754 is likely not supported.                             */
    return tmpl_double_unknown_endian;
}
/*  End of tmpl_det_double_type.                                              */

#endif
/*  End of include guard.                                                     */
