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
 *                         tmpl_config_det_float_type                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Detects how float is implemented by the compiler.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_det_float_type                                                   *
 *  Purpose:                                                                  *
 *      Determines how float is implemented by the compiler.                  *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      float_type (enum tmpl_float_type):                                    *
 *          enum representing how float is implemented.                       *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_uchar_width.h:                                    *
 *              tmpl_det_uchar_width:                                         *
 *                  Computes the number of bits in unsigned char.             *
 *  Method:                                                                   *
 *      Use type punning to set the bits of a float to the bit pattern that   *
 *      represents 1 for an IEEE-754 32-bit float. Try this for both big      *
 *      endianness and little endianness. If neither endianness produces      *
 *      1.0 as a float, return unknown.                                       *
 *  Notes:                                                                    *
 *      1.) This function only attempts to check if float is a 32-bit         *
 *          IEEE-754 single precision floating point number. It will not      *
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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_DET_FLOAT_TYPE_H
#define TMPL_CONFIG_DET_FLOAT_TYPE_H

/*  If the user does not want IEEE support, these functions are not used.     */
#ifndef TMPL_SET_TMPL_USE_IEEE_FALSE

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  tmpl_det_uchar_width function provided here.                              */
#include "tmpl_config_det_uchar_width.h"

/*  IEEE-754 does not specify the endianness of float. It is usually the      *
 *  same as the endianness of integers, but this is not required. Unknown     *
 *  is returned if the function could not determine how float is implemented. */
enum tmpl_float_type {
    tmpl_float_little_endian,
    tmpl_float_big_endian,
    tmpl_float_unknown_endian
};

/*  Function for determining how float is implemented.                        */
static enum tmpl_float_type tmpl_det_float_type(void)
{
    /*  IEEE-754 uses 32-bit single precision, but does not specify the       *
     *  endianness. This function will attempt to determine if IEEE-754 is    *
     *  used, and also determine the endianness of float.                     */
    union {
        /*  A float has 1 bit for the sign, 8 bits for the exponent, and 23   *
         *  bits for the mantissa.                                            */
        struct tmpl_float_type_big_bits {
            unsigned int sign : 1;
            unsigned int expo : 8;
            unsigned int man0 : 7;
            unsigned int man1 : 16;
        } big_bits;

        /*  Same thing for little endianness.                                 */
        struct tmpl_float_type_little_bits {
            unsigned int man1 : 16;
            unsigned int man0 : 7;
            unsigned int expo : 8;
            unsigned int sign : 1;
        } little_bits;

        /*  And a float that the above structs represent.                     */
        float r;
    } f;

    /*  We need to use the global value tmpl_number_of_bits_in_uchar. Check   *
     *  that it has been computed already. If not, compute it.                */
    if (!tmpl_uchar_width_is_known)
        tmpl_det_uchar_width();

    /*  float should have 32 bits. Check for this.                            */
    if ((sizeof(float) * tmpl_number_of_bits_in_uchar) != 32)
        return tmpl_float_unknown_endian;

    /*  Set the bits in the struct to represent the number 1.0 using the      *
     *  IEEE-754 format. If the endianness is flipped, we should get          *
     *  gibberish, whereas if its correct we should get 1.0.                  */
    f.big_bits.sign = 0x0U;
    f.big_bits.expo = 0x7FU;
    f.big_bits.man0 = 0x0U;
    f.big_bits.man1 = 0x0U;

    /*  If the float in the union is actually 1 we have IEEE-754 support and  *
     *  we have big endianness for float.                                     */
    if (f.r == 1.0F)
        return tmpl_float_big_endian;

    /*  Otherwise, try little endianness.                                     */
    f.little_bits.sign = 0x0U;
    f.little_bits.expo = 0x7FU;
    f.little_bits.man0 = 0x0U;
    f.little_bits.man1 = 0x0U;

    /*  If we have little endian IEEE-754 implementation for float, the float *
     *  part of the union should now be 1. Check this.                        */
    if (f.r == 1.0F)
        return tmpl_float_little_endian;

    /*  Otherwise, IEEE-754 is likely not implemented. Return unknown.        */
    return tmpl_float_unknown_endian;
}
/*  End of tmpl_det_float_type.                                               */

#endif
/*  Else for #ifndef TMPL_SET_TMPL_USE_IEEE_FALSE.                            */

#endif
/*  End of include guard.                                                     */
