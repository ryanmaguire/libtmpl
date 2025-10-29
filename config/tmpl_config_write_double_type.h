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
 *                        tmpl_config_write_double_type                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_DOUBLE_ENDIANNESS macro to a file.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_double_type                                                *
 *  Purpose:                                                                  *
 *      Writes the TMPL_DOUBLE_ENDIANNESS macro to a file.                    *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_double_type.h:                                    *
 *              tmpl_check_double_type:                                       *
 *                  Determines how the compiler represents double.            *
 *  Method:                                                                   *
 *      Call the tmpl_check_double_type function and then examine the global  *
 *      variable tmpl_double_rep. Write the macro to the file using fputs.    *
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
#ifndef TMPL_CONFIG_WRITE_DOUBLE_TYPE_H
#define TMPL_CONFIG_WRITE_DOUBLE_TYPE_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  The tmpl_check_double_type function is provided here.                     */
#include "tmpl_config_check_double_type.h"

/*  Function for writing the TMPL_DOUBLE_ENDIANNESS macro to a file.          */
static void tmpl_write_double_type(FILE *fp)
{
    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_double_type\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  Set the tmpl_double_rep variable if it hasn't been set already.       */
    if (!tmpl_double_type_has_been_checked)
        tmpl_check_double_type();

    /*  libtmpl supports IEEE-754 64-bit doubles, both little and big endian. *
     *  If the tmpl_double_rep variable is set to "unknown," then libtmpl     *
     *  provides portable code that does not take advantage of the IEEE-754   *
     *  format. While portable, this is an order of magnitude slower.         */
    switch (tmpl_double_rep)
    {
        case tmpl_double_little_endian:
            fputs("#define TMPL_DOUBLE_ENDIANNESS TMPL_LITTLE_ENDIAN\n", fp);
            return;

        case tmpl_double_big_endian:
            fputs("#define TMPL_DOUBLE_ENDIANNESS TMPL_BIG_ENDIAN\n", fp);
            return;

        default:
            fputs("#define TMPL_DOUBLE_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n", fp);
    }
}
/*  End of tmpl_write_double_type.                                            */

#endif
/*  End of include guard.                                                     */
