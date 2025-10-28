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
 *                         tmpl_config_write_has_ascii                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_HAS_ASCII macro to a file.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_has_ascii                                                  *
 *  Purpose:                                                                  *
 *      Writes the TMPL_HAS_ASCII macro to a file.                            *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          File pointer for the file being written to.                       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_has_ascii.h:                                          *
 *              tmpl_has_ascii:                                               *
 *                  Determines if the ASCII character set is used.            *
 *      stdio.h:                                                              *
 *          fputs:                                                            *
 *              Writes a string to a file.                                    *
 *  Method:                                                                   *
 *      Call tmpl_has_ascii to check for ASCII support and write with fputs.  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_has_ascii.h:                                              *
 *          Provides the tmpl_has_ascii function.                             *
 *  2.) stdio.h:                                                              *
 *          Standard library header file providing FILE and fputs.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_HAS_ASCII_H
#define TMPL_CONFIG_WRITE_HAS_ASCII_H

/*  tmpl_has_ascii function found here, used for checking ASCII support.      */
#include "tmpl_config_has_ascii.h"

/*  FILE type and fputs given here.                                           */
#include <stdio.h>

/*  Function for writing the TMPL_HAS_ASCII macro to a file.                  */
static void tmpl_write_has_ascii(FILE *fp)
{
    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_has_ascii\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  Probe for ASCII support and set the macro accordingly.                */
    if (tmpl_has_ascii())
        fputs("#define TMPL_HAS_ASCII 1\n\n", fp);
    else
        fputs("#define TMPL_HAS_ASCII 0\n\n", fp);
}
/*  End of tmpl_write_has_ascii.                                              */

#endif
/*  End of include guard.                                                     */
