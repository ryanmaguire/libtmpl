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
 *                      tmpl_config_write_int_endianness                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_DOUBLE_ENDIANNESS macro to a file.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_double_type                                                *
 *  Purpose:                                                                  *
 *      Writes the TMPL_ENDIANNESS macro to a file.                           *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_check_int_endianness.h:                               *
 *              tmpl_check_int_endianness:                                    *
 *                  Determines the endianness of unsigned integers.           *
 *  Method:                                                                   *
 *      Call the tmpl_check_int_endianness function and then examine the      *
 *      global variable tmpl_endian. Write the macro to the file using fputs. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_globals.h:                                                *
 *          Header file with all of the globals used by config.c.             *
 *  2.) tmpl_config_check_int_endianness.h:                                   *
 *          tmpl_check_int_endianness function provided here.                 *
 *  3.) stdio.h:                                                              *
 *          Standard library header file providing FILE and fputs.            *
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
#ifndef TMPL_CONFIG_WRITE_INT_ENDIANNESS_TYPE_H
#define TMPL_CONFIG_WRITE_INT_ENDIANNESS_TYPE_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  Function for determining integer endianness found here.                   */
#include "tmpl_config_check_int_endianness.h"

/*  fputs and the FILE type are found here.                                   */
#include <stdio.h>

static void tmpl_write_int_endianness(FILE * fp)
{
    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_int_endianness\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  Determine the endianness if it hasn't been already.                   */
    if (!tmpl_int_endianness_has_been_checked)
        tmpl_check_int_endianness();

    /*  Four possibilities: little, big, mixed, and unknown endian. libtmpl   *
     *  uses some tricks with little and big endianness, mixed endian is      *
     *  ignored. Mixed endian systems will use the portable code instead.     */
    switch (tmpl_endian)
    {
        case tmpl_integer_little_endian:
            fputs("#define TMPL_ENDIANNESS TMPL_LITTLE_ENDIAN\n", fp);
            return;

        case tmpl_integer_big_endian:
            fputs("#define TMPL_ENDIANNESS TMPL_BIG_ENDIAN\n", fp);
            return;

        case tmpl_integer_mixed_endian:
            fputs("#define TMPL_ENDIANNESS TMPL_MIXED_ENDIAN\n", fp);
            return;

        default:
            fputs("#define TMPL_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n", fp);
    }
}
/*  End of tmpl_write_int_endianness.                                         */

#endif
/*  End of include guard.                                                     */
