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
 *                 tmpl_config_write_signed_int_representation                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_SIGNED_REP macro to a file.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_signed_int_representation                                  *
 *  Purpose:                                                                  *
 *      Writes the TMPL_SIGNED_REP macro to a file.                           *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          File pointer for the file being written to.                       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdio.h:                                                              *
 *          fputs:                                                            *
 *              Writes a string to a file.                                    *
 *      config/                                                               *
 *          tmpl_config_det_signed_int.h:                                     *
 *                  tmpl_det_signed_int:                                      *
 *                      Determines how signed integers are represented.       *
 *  Method:                                                                   *
 *      Use tmpl_det_signed_int to determine how signed integers are          *
 *      represented and then write the TMPL_SIGNED_REP macro using fputs.     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_det_signed_int.h:                                         *
 *          Provides the tmpl_det_signed_int function.                        *
 *  2.) stdio.h:                                                              *
 *          Standard library header file providing FILE and fputs.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_SIGNED_INT_REPRESENTATION_H
#define TMPL_CONFIG_WRITE_SIGNED_INT_REPRESENTATION_H

/*  tmpl_det_signed_int function provided here.                               */
#include "tmpl_config_det_signed_int.h"

/*  FILE type and fputs given here.                                           */
#include <stdio.h>

/*  Function for writing the TMPL_SIGNED_REP macro to a file.                 */
static void tmpl_write_signed_int_representation(FILE * fp)
{
    /*  C89 requires declarations at the top of a block.                      */
    enum tmpl_signed_integer_rep signed_type;

    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_signed_int_representation\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    /*  Determine how signed integers are represented. There are three types  *
     *  that libtmpl checks for:                                              *
     *      1.) Sign and magnitude.                                           *
     *      2.) One's complement.                                             *
     *      3.) Two's complement.                                             *
     *  Note that C99, C11, and C18 require one of these three be implemented *
     *  and C23 requires two's complement. C89 does not specify.              */
    signed_type = tmpl_det_signed_int();

    /*  Check the representation and write the macro to the file.             */
    switch (signed_type)
    {
        case tmpl_ones_complement:
            fputs("#define TMPL_SIGNED_REP TMPL_ONES_COMPLEMENT\n", fp);
            return;

        case tmpl_twos_complement:
            fputs("#define TMPL_SIGNED_REP TMPL_TWOS_COMPLEMENT\n", fp);
            return;

        case tmpl_sign_and_magnitude:
            fputs("#define TMPL_SIGNED_REP TMPL_SIGN_AND_MAGNITUDE\n", fp);
            return;

        /*  This case is not allowed with C99, C11, C18, and C23. C89 does    *
         *  not restrict the ways signed int may be implemented.              */
        default:
            fputs("#define TMPL_SIGNED_REP TMPL_UNKNOWN_SIGNED_REP\n", fp);
    }
}
/*  End of tmpl_write_signed_int_representation.                              */

#endif
/*  End of include guard.                                                     */
