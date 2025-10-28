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
 *                        tmpl_config_write_use_memcpy                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_USE_MEMCPY macro to a file.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_use_memcpy                                                 *
 *  Purpose:                                                                  *
 *      Writes the TMPL_USE_MEMCPY macro to a file.                           *
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
 *      Inspect the TMPL_SET_USE_MEMCPY_TRUE macro and call fputs.            *
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
#ifndef TMPL_CONFIG_WRITE_USE_MEMCPY_H
#define TMPL_CONFIG_WRITE_USE_MEMCPY_H

/*  FILE type and fputs given here.                                           */
#include <stdio.h>

/*  Function for writing the TMPL_USE_MEMCPY macro to a file.                 */
static void tmpl_write_use_memcpy(FILE *fp)
{
#ifdef TMPL_SET_USE_MEMCPY_TRUE
    fputs("#define TMPL_USE_MEMCPY 1\n\n", fp);
#else
    fputs("#define TMPL_USE_MEMCPY 0\n\n", fp);
#endif
}
/*  End of tmpl_write_use_memcpy.                                             */

#endif
/*  End of include guard.                                                     */
