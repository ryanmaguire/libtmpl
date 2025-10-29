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
 *                       tmpl_config_write_ldouble_type                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_LDOUBLE_ENDIANNESS macro to a file.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_ldouble_type                                               *
 *  Purpose:                                                                  *
 *      Writes the TMPL_LDOUBLE_ENDIANNESS macro to a file.                   *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_ldouble_type.h:                                   *
 *              tmpl_check_ldouble_type:                                      *
 *                  Determines how the compiler represents long double.       *
 *  Method:                                                                   *
 *      Call the tmpl_check_ldouble_type function and then examine the global *
 *      variable tmpl_ldouble_rep. Write the macro to the file using fputs.   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/28: Ryan Maguire                                                  *
 *      Moved function to its own file.                                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_LDOUBLE_TYPE_H
#define TMPL_CONFIG_WRITE_LDOUBLE_TYPE_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  The tmpl_check_ldouble_type function is provided here.                    */
#include "tmpl_config_check_ldouble_type.h"

/*  Function for writing the TMPL_LDOUBLE_ENDIANNESS macro to a file.         */
static void tmpl_write_ldouble_type(FILE *fp)
{
    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_ldouble_type\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  Set the tmpl_ldouble_rep variable if it hasn't been set already.      */
    if (!tmpl_ldouble_type_has_been_checked)
        tmpl_check_ldouble_type();

    /*  libtmpl support 64-bit double, 80-bit extended, 128-bit double-double,*
     *  and 128-bit quadruple representations of long double, both big and    *
     *  little endian. Check if any of these are being used.                  */
    switch (tmpl_ldouble_rep)
    {
        case tmpl_ldouble_64_bit_little_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_64_BIT\n\n",
                fp
            );

            return;

        case tmpl_ldouble_64_bit_big_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_64_BIT_BIG_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_64_BIT\n\n",
                fp
            );

            return;

        case tmpl_ldouble_96_bit_extended_little_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_80_BIT\n\n",
                fp
            );

            return;

        case tmpl_ldouble_96_bit_extended_big_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_80_BIT\n\n",
                fp
            );

            return;

        case tmpl_ldouble_128_bit_extended_little_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_80_BIT\n\n",
                fp
            );

            return;

        case tmpl_ldouble_128_bit_extended_big_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_80_BIT\n\n",
                fp
            );

            return;

        case tmpl_ldouble_128_bit_quadruple_little_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_128_BIT\n\n",
                fp
            );

            return;

        case tmpl_ldouble_128_bit_quadruple_big_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_128_BIT\n\n",
                fp
            );

            return;

        case tmpl_ldouble_128_bit_doubledouble_little_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_DOUBLEDOUBLE\n\n",
                fp
            );

            return;

        case tmpl_ldouble_128_bit_doubledouble_big_endian:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS "
                    "TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_DOUBLEDOUBLE\n\n",
                fp
            );

            return;

        default:
            fputs(
                "#define TMPL_LDOUBLE_ENDIANNESS TMPL_LDOUBLE_UNKNOWN\n"
                "#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_UNKNOWN\n\n",
                fp
            );
    }
}
/*  End of tmpl_write_ldouble_type.                                           */

#endif
/*  End of include guard.                                                     */
