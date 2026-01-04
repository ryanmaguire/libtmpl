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
 *      Creates the tmpl_config.h file.                                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      make_config_h                                                         *
 *  Purpose:                                                                  *
 *      Create the tmpl_config.h file, writing it in the include/ directory.  *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      Lots.                                                                 *
 *  Method:                                                                   *
 *      Call the functions used for determining how integers and floating     *
 *      point types are represented, as well as the functions for indicating  *
 *      support for type punning, and functions that indicate use of later    *
 *      C keywords (like restrict and inline), then close the file.           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
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
#ifndef TMPL_CONFIG_MAKE_CONFIG_H_H
#define TMPL_CONFIG_MAKE_CONFIG_H_H

/*  Functions used for writing the tmpl_config.h file.                        */
#include "tmpl_config_write_config_h_preamble.h"
#include "tmpl_config_write_end_of_file.h"
#include "tmpl_config_write_int_endianness.h"
#include "tmpl_config_write_has_ascii.h"
#include "tmpl_config_write_has_floatint32.h"
#include "tmpl_config_write_has_floatint64.h"
#include "tmpl_config_write_has_floatint_ldouble.h"
#include "tmpl_config_write_license.h"
#include "tmpl_config_write_gcd_algorithm.h"
#include "tmpl_config_write_float_type.h"
#include "tmpl_config_write_double_type.h"
#include "tmpl_config_write_ldouble_type.h"
#include "tmpl_config_write_signed_int_representation.h"
#include "tmpl_config_write_use_inline.h"
#include "tmpl_config_write_use_math.h"
#include "tmpl_config_write_use_memcpy.h"
#include "tmpl_config_write_use_restrict.h"
#include "tmpl_config_write_use_volatile.h"

/*  Function for creating include/tmpl_config.h.                              */
static int make_config_h(void)
{
    /*  Open the file include/tmpl_config.h using fopen and give the file     *
     *  write permissions. If using Windows, we'll need to use backslashes.   *
     *  Forward slashes fail to create the file.                              */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    FILE *fp = fopen(".\\include\\tmpl_config.h", "w");
#else
    FILE *fp = fopen("./include/tmpl_config.h", "w");
#endif

    /*  If fopen fails, it returns NULL. Check that it did not.               */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    make_config_h\n\n"
            "fopen returned NULL for FILE *fp. Aborting.\n"
        );

        return -1;
    }

    /*  Write the docstring to the file.                                      */
    tmpl_write_license(fp);
    tmpl_write_config_h_preamble(fp);

    /*  Add the integer-specific macros.                                      */
    tmpl_write_int_endianness(fp);
    tmpl_write_signed_int_representation(fp);

    /*  Add the floating-point macros.                                        */
    tmpl_write_float_type(fp);
    tmpl_write_double_type(fp);
    tmpl_write_ldouble_type(fp);
    tmpl_write_has_floatint32(fp);
    tmpl_write_has_floatint64(fp);
    tmpl_write_has_floatint_ldouble(fp);

    /*  Add the character set macro.                                          */
    tmpl_write_has_ascii(fp);

    /*  Macros for use of various C keywords.                                 */
    tmpl_write_use_inline(fp);
    tmpl_write_use_math(fp);
    tmpl_write_use_volatile(fp);
    tmpl_write_use_restrict(fp);

    /*  Macro for whether to use memcpy or for-loops.                         */
    tmpl_write_use_memcpy(fp);

    /*  Macro for which GCD algorithm libtmpl should implement as the default.*/
    tmpl_write_gcd_algorithm(fp);

    /*  Write the include guard closer and write the end-of-file.             */
    tmpl_write_end_of_file(fp);

    return 0;
}
/*  End of make_config_h.                                                     */

#endif
/*  End of include guard.                                                     */
