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
 *                      tmpl_config_write_has_floatint64                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_HAS_FLOATINT64 macro to a file.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_has_floatint64                                             *
 *  Purpose:                                                                  *
 *      Writes the TMPL_HAS_FLOATINT64 macro to a file.                       *
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
 *          tmpl_config_det_double_type.h:                                    *
 *              tmpl_check_double_type:                                       *
 *                  Determines how the compiler represents double.            *
 *  Method:                                                                   *
 *      Check to see if double is 64-bits, and if there is an unsigned 64-bit *
 *      integer type that has the same endianness.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_HAS_FLOATINT64_H
#define TMPL_CONFIG_WRITE_HAS_FLOATINT64_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  Function for determining unsigned integer endianness.                     */
#include "tmpl_config_check_int_endianness.h"

/*  Function for computing the number of unpadded bits in each integer type.  */
#include "tmpl_config_det_widths.h"

/*  Function for checking if double is IEEE-754 64-bit double precision.      */
#include "tmpl_config_check_double_type.h"

/*  FILE type and fputs provided here.                                        */
#include <stdio.h>

/*  Function for determining if type punning is available for double.         */
static void tmpl_write_has_floatint64(FILE *fp)
{
    /*  Boolean for determining if we may use type punning.                   */
    unsigned int tmpl_has_floatint64 = 0U;

    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_has_floatint64\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  Compute the widths of each unsigned type if needed.                   */
    if (!tmpl_all_widths_are_known)
        tmpl_check_widths();

    /*  If there is no 64-bit integer type, we may not use type punning. Skip.*/
    if (!tmpl_has_64_bit_uint)
        goto FINISH;

    /*  The endianness of the 64-bit integer type needs to match the          *
     *  endianness of double. Check.                                          */
    if (!tmpl_int_endianness_has_been_checked)
        tmpl_check_int_endianness();

    /*  Lastly, we need to determine if double is binary64. Check for this.   */
    if (!tmpl_double_type_has_been_checked)
        tmpl_check_double_type();

    /*  Unheard of by me, but not impossible by the standards. We need        *
     *  doubles and ints to have the same endianness in order to use type     *
     *  punning with fixed-width integers. Check for this.                    */
    switch (tmpl_endian)
    {
        case tmpl_integer_little_endian:

            if (tmpl_double_rep == tmpl_double_little_endian)
                tmpl_has_floatint64 = 1U;

            break;

        case tmpl_integer_big_endian:

            if (tmpl_double_rep == tmpl_double_big_endian)
                tmpl_has_floatint64 = 1U;

            break;

        default:
            break;
    }

FINISH:

    /*  Write the TMPL_HAS_FLOATINT64 accordingly.                            */
    if (tmpl_has_floatint64)
        fputs("#define TMPL_HAS_FLOATINT64 1\n", fp);
    else
        fputs("#define TMPL_HAS_FLOATINT64 0\n", fp);
}
/*  End of tmpl_write_has_floatint64.                                         */

#endif
/*  End of include guard.                                                     */
