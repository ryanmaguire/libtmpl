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
 *                       tmpl_config_write_end_of_file                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the end of a header file and closes it.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_end_of_file                                                *
 *  Purpose:                                                                  *
 *      Writes the end of a header file and closes it.                        *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          File pointer for the file being closed.                           *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdio.h:                                                              *
 *          fputs:                                                            *
 *              Writes a string to a file.                                    *
 *          fclose:                                                           *
 *              Closes a file.                                                *
 *  Method:                                                                   *
 *      Write the end of the include guard and then close the file.           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          Standard library header file providing FILE and fputs.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 28, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_END_OF_FILE_H
#define TMPL_CONFIG_WRITE_END_OF_FILE_H

/*  Function for writing the end of a header file and then closing the file.  */
static void tmpl_write_end_of_file(FILE *fp)
{
    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_end_of_file\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  Header files start with an include guard. Finish the include guard.   */
    fputs("#endif\n", fp);

    /*  We're now at the end of the file, close it.                           */
    fclose(fp);
}
/*  End of tmpl_write_end_of_file.                                            */

#endif
/*  End of include guard.                                                     */
