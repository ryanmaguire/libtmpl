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
 *                       tmpl_config_write_use_restrict                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_RESTRICT macro to a file.                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_use_restrict                                               *
 *  Purpose:                                                                  *
 *      Writes the TMPL_RESTRICT macro to a file.                             *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          File pointer for the file being written to.                       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdio.h:                                                              *
 *          fputs:                                                            *
 *              Writes a string to a file.                                    *
 *  Method:                                                                   *
 *      Check the TMPL_NO_RESTRICT macro and C99 support and then call fputs. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          Standard library header file providing FILE and fputs.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_USE_RESTRICT_H
#define TMPL_CONFIG_WRITE_USE_RESTRICT_H

/*  FILE type and fputs given here.                                           */
#include <stdio.h>

/*  By default we assume restrict is not allowed. We'll reset this later.     */
#define TMPL_HAS_RESTRICT 0

/*  The restrict keyword was only introduced with the C99 standard. Check.    */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/*  Users may optionally request libtmpl not use restrict at all. Check.      */
#ifndef TMPL_NO_RESTRICT

/*  restrict is supported and requested. Reset the macro to 1.                */
#undef TMPL_HAS_RESTRICT
#define TMPL_HAS_RESTRICT 1

#endif
/*  End of #ifndef TMPL_NO_RESTRICT.                                          */

#endif
/*  End of #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.      */

/*  Function for writing the TMPL_RESTRICT macro to a file.                   */
static void tmpl_write_use_restrict(FILE *fp)
{
    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_use_restrict\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

#if TMPL_HAS_RESTRICT == 1
    fputs("#define TMPL_RESTRICT restrict\n\n", fp);
#else
    fputs("#define TMPL_RESTRICT\n\n", fp);
#endif
}
/*  End of tmpl_write_use_restrict.                                           */

/*  Undefine everything to avoid conflicts.                                   */
#undef TMPL_HAS_RESTRICT

#endif
/*  End of include guard.                                                     */
