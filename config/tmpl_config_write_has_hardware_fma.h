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
    /*  The constants are 1 + 2^-27 and -(1 + 2^-26). Both can be perfectly   *
     *  represented using double-precision floating-point numbers.            */
    volatile const double a = +1.000000007450580596923828125;
    volatile const double b = +1.000000007450580596923828125;
    volatile const double c = -1.000000014901161193847656250;

    /*  Load the constants into non-volatile variables. The register keyword  *
     *  hints that the compiler should most definitely load these variables   *
     *  into registers, which is where FMA-like instructions usually operate. *
     *  The compiler is free to ignore this keyword, but nevertheless loading *
     *  the volatile variables into new variables usually gets the compiler   *
     *  to emit an FMA instruction if supported.                              */
    register const double a_val = a;
    register const double b_val = b;
    register const double c_val = c;

    /*  The exact expression a * b + c produces 2^-54. In the absence of an   *
     *  FMA instruction, a * b + c results in two floating-point rounds which *
     *  results in 0. If FMA is not supported, this variable will be zero.    */
    const double fma_val = a_val * b_val + c_val;
    const int has_fma = (fma_val == 0.0 ? 0 : 1);

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

    /*  Write the macro to the input file.                                    */
    if (has_fma)
        fputs("#define TMPL_HAS_HARDWARE_FMA 1\n\n", fp);
    else
        fputs("#define TMPL_HAS_HARDWARE_FMA 0\n\n", fp);
}
/*  End of tmpl_write_has_hardware_fma.                                       */

#endif
/*  End of include guard.                                                     */
