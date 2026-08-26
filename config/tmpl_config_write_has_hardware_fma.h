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
 *                     tmpl_config_write_has_hardware_fma                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_HAS_HARDWARE_FMA macro to a file.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_has_hardware_fma                                           *
 *  Purpose:                                                                  *
 *      Writes the TMPL_HAS_ASCII macro to a file.                            *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          File pointer for the file being written to.                       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdio.h:                                                              *
 *          fputs:                                                            *
 *              Writes a string to a file.                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          Standard library header file providing FILE and fputs.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 26, 2026                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_HAS_HARDWARE_FMA_H
#define TMPL_CONFIG_WRITE_HAS_HARDWARE_FMA_H

/*  FILE type and fputs given here.                                           */
#include <stdio.h>

/*  Function for writing the TMPL_HAS_HARDWARE_FMA macro to a file.           */
static void tmpl_write_has_hardware_fma(FILE *fp)
{
    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_has_hardware_fma\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  The build system determines this and sets the following macro.        */
#ifdef TMPL_USE_HARDWARE_FMA
    fputs("#define TMPL_HAS_HARDWARE_FMA 1\n\n", fp);
#else
    fputs("#define TMPL_HAS_HARDWARE_FMA 0\n\n", fp);
#endif
}
/*  End of tmpl_write_has_ascii.                                              */

#endif
/*  End of include guard.                                                     */
