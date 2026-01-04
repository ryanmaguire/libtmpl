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
 *                       tmpl_config_write_gcd_algorithm                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks what the default GCD algorithm should be.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_gcd_algorithm                                              *
 *  Purpose:                                                                  *
 *      Writes the TMPL_GCD_ALGORITHM macro to a file.                        *
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
 *      Check if any macros have been set for specific algorithm and then     *
 *      write the corresponding value to the file.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          Standard library header where the FILE type is provided.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 4, 2026                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_GCD_ALGORITHM_H
#define TMPL_CONFIG_WRITE_GCD_ALGORITHM_H

/*  Function for writing the TMPL_GCD_ALGORITHM macro to a file.              */
static void tmpl_write_gcd_algorithm(FILE *fp)
{
    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_gcd_algorithm\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  Check if a specific algorithm has been requested.                     */
#if defined(TMPL_GCD_USE_BINARY)
    fputs("#define TMPL_GCD_ALGORITHM TMPL_GCD_ALGORITHM_BINARY\n\n", fp);
#elif defined(TMPL_GCD_USE_EUCLIDEAN)
    fputs("#define TMPL_GCD_ALGORITHM TMPL_GCD_ALGORITHM_EUCLIDEAN\n\n", fp);
#elif defined(TMPL_GCD_USE_NAIVE)
    fputs("#define TMPL_GCD_ALGORITHM TMPL_GCD_ALGORITHM_NAIVE\n\n", fp);
#else
    fputs("#define TMPL_GCD_ALGORITHM TMPL_GCD_ALGORITHM_MIXED_BINARY\n\n", fp);
#endif
}
/*  End of tmpl_write_gcd_algorithm.                                          */

#endif
/*  End of include guard.                                                     */
