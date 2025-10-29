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
 *                   tmpl_config_write_has_floatint_ldouble                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_HAS_FLOATINT_LDOUBLE macro to a file.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_has_floatint_ldouble                                       *
 *  Purpose:                                                                  *
 *      Writes the TMPL_HAS_FLOATINT_LDOUBLE macro to a file.                 *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_check_int_endianness.h:                               *
 *              tmpl_check_int_endianness:                                    *
 *                  Determines the endianness of unsigned integers.           *
 *          tmpl_config_check_widths.h:                                       *
 *              tmpl_check_widths:                                            *
 *                  Checks all of the widths of each unsigned integer type.   *
 *          tmpl_config_det_ldouble_type.h:                                   *
 *              tmpl_check_ldouble_type:                                      *
 *                  Determines how the compiler represents long double.       *
 *  Method:                                                                   *
 *      Check to see if long double is either 64-bit double, 80-bit extended, *
 *      128-bit double-double, or 128-bit quadruple. Check to see if          *
 *      the required fixed-width unsigned integers are available, and then    *
 *      write the TMPL_HAS_FLOATINT_LDOUBLE macro using fputs.                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_HAS_FLOATINT_LDOUBLE_H
#define TMPL_CONFIG_WRITE_HAS_FLOATINT_LDOUBLE_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  Function for determining unsigned integer endianness.                     */
#include "tmpl_config_check_int_endianness.h"

/*  Function for computing the number of unpadded bits in each integer type.  */
#include "tmpl_config_det_widths.h"

/*  Function for checking how long double is implemented.                     */
#include "tmpl_config_check_ldouble_type.h"

/*  Function for writing the TMPL_HAS_FLOATINT_LDOUBLE macro to a file.       */
static void tmpl_write_has_floatint_ldouble(FILE *fp)
{
    /*  Boolean indicated support for type punning with long double.          */
    unsigned int tmpl_has_floatint_long_double = 0U;

    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_has_floatint_ldouble\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  Compute the widths of each unsigned type if needed.                   */
    if (!tmpl_all_widths_are_known)
        tmpl_check_widths();

    /*  The endianness of the unsigned integer types needs to match the       *
     *  endianness of double. Check.                                          */
    if (!tmpl_int_endianness_has_been_checked)
        tmpl_check_int_endianness();

    /*  Lastly, we need to determine how long double is implemented. Check.   */
    if (!tmpl_ldouble_type_has_been_checked)
        tmpl_check_ldouble_type();

    /*  We need to match the endianness of unsigned integers to long double.  */
    switch (tmpl_endian)
    {
        case tmpl_integer_little_endian:

            switch (tmpl_ldouble_rep)
            {
                /*  64-bit double, 128-bit double-double, and 128-bit         *
                 *  quadruple representations of long double only need 64-bit *
                 *  unsigned integers to use type punning. All of these are   *
                 *  handled as the same case.                                 */
                case tmpl_ldouble_64_bit_little_endian:
                case tmpl_ldouble_128_bit_quadruple_little_endian:
                case tmpl_ldouble_128_bit_doubledouble_little_endian:

                    if (tmpl_has_64_bit_uint)
                        tmpl_has_floatint_long_double = 1U;

                    break;

                /*  80-bit extended methods have padding, creating either     *
                 *  96-bit or 128-bit objects. Both of these need 64-bit and  *
                 *  32-bit unsigned integers in order to fill an 80-bit block.*/
                case tmpl_ldouble_96_bit_extended_little_endian:
                case tmpl_ldouble_128_bit_extended_little_endian:

                    if (tmpl_has_32_bit_uint && tmpl_has_64_bit_uint)
                        tmpl_has_floatint_long_double = 1U;

                    break;

                default:
                    break;
            }

            break;

        /*  Same checks, but for big endian integers.                         */
        case tmpl_integer_big_endian:

            switch (tmpl_ldouble_rep)
            {
                case tmpl_ldouble_64_bit_big_endian:
                case tmpl_ldouble_128_bit_quadruple_big_endian:
                case tmpl_ldouble_128_bit_doubledouble_big_endian:
                    if (tmpl_has_64_bit_uint)
                        tmpl_has_floatint_long_double = 1U;

                    break;

                case tmpl_ldouble_96_bit_extended_big_endian:
                case tmpl_ldouble_128_bit_extended_big_endian:

                    if (tmpl_has_32_bit_uint && tmpl_has_64_bit_uint)
                        tmpl_has_floatint_long_double = 1U;

                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }

    /*  Write the TMPL_HAS_FLOATINT_LONG_DOUBLE macro accordingly.            */
    if (tmpl_has_floatint_long_double)
        fputs("#define TMPL_HAS_FLOATINT_LONG_DOUBLE 1\n\n", fp);
    else
        fputs("#define TMPL_HAS_FLOATINT_LONG_DOUBLE 0\n\n", fp);
}
/*  End of tmpl_write_has_floatint_ldouble.                                   */

#endif
/*  End of include guard.                                                     */
