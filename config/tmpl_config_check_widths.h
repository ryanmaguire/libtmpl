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
 *                          tmpl_config_check_widths                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Sets the config globals for the sizes and widths of unsigned types.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_check_widths                                                     *
 *  Purpose:                                                                  *
 *      Sets the config globals for the sizes and widths of unsigned types.   *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_widths.h:                                         *
 *              tmpl_det_widths:                                              *
 *                  Determines long double representation using type-punning. *
 *  Method:                                                                   *
 *      Call the tmpl_det_widths function and then examine the config globals *
 *      to see if there are any unsigned types that have 32 bits of storage   *
 *      and 32 numerical bits, and similarly check for 64 bit types.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_globals.h:                                                *
 *          Header file with all of the globals used by config.c.             *
 *  2.) tmpl_config_det_widths.h:                                             *
 *          Provides the tmpl_det_widths function.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_CHECK_WIDTHS_H
#define TMPL_CONFIG_CHECK_WIDTHS_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  The tmpl_det_widths function is provided here.                            */
#include "tmpl_config_det_widths.h"

/*  Function for setting the config globals for unsigned integer types.       */
static void tmpl_check_widths(void)
{
    /*  This function computes the widths and storage size for all of the     *
     *  standard unsigned types (char, short, int, long, and long long).      */
    tmpl_det_widths();
    tmpl_all_widths_are_known = 1U;

    /*  The user may opt to skip code that uses fixed-width integers.         */
#ifdef TMPL_SET_NO_INT

    tmpl_has_32_bit_uint = 0U;
    tmpl_has_64_bit_uint = 0U;

#else
/*  Else for #ifdef TMPL_SET_NO_INT.                                          */

    /*  Otherwise, check for 32-bit unsigned integers. The C standard does    *
     *  not require any data type to be 32-bits, it only specifies that long  *
     *  must be at least 32 bits. In practice, on modern computers, int is    *
     *  32 bits. Check each type.                                             */
    if (tmpl_uchar_width == 32U && tmpl_number_of_bits_in_uchar == 32U)
        tmpl_has_32_bit_uint = 1U;
    else if (tmpl_ushort_width == 32U && tmpl_number_of_bits_in_ushort == 32U)
        tmpl_has_32_bit_uint = 1U;
    else if (tmpl_uint_width == 32U && tmpl_number_of_bits_in_uint == 32U)
        tmpl_has_32_bit_uint = 1U;
    else if (tmpl_ulong_width == 32U && tmpl_number_of_bits_in_ulong == 32U)
        tmpl_has_32_bit_uint = 1U;
    else
        tmpl_has_32_bit_uint = 0U;

    /*  Similarly, no data type is required to be 64-bits. The C standard     *
     *  only specifies that long long is at least 64 bits. In practice, on    *
     *  modern non-Windows machines (GNU, Linux, FreeBSD, macOS, etc.) long   *
     *  is 64-bit, and on Windows long long is 64-bit. Check each type.       */
    if (tmpl_uchar_width == 64U && tmpl_number_of_bits_in_uchar == 64U)
        tmpl_has_64_bit_uint = 1U;
    else if (tmpl_ushort_width == 64U && tmpl_number_of_bits_in_ushort == 64U)
        tmpl_has_64_bit_uint = 1U;
    else if (tmpl_uint_width == 64U && tmpl_number_of_bits_in_uint == 64U)
        tmpl_has_64_bit_uint = 1U;
    else if (tmpl_ulong_width == 64U && tmpl_number_of_bits_in_ulong == 64U)
        tmpl_has_64_bit_uint = 1U;
#ifdef TMPL_LONG_LONG_IS_AVAILABLE
    else if (tmpl_ullong_width == 64U && tmpl_number_of_bits_in_ullong == 64U)
        tmpl_has_64_bit_uint = 1U;
#endif
    else
        tmpl_has_64_bit_uint = 0U;

#endif
/*  End of #ifdef TMPL_SET_NO_INT.                                            */

}
/*  End of tmpl_check_widths.                                                 */

#endif
/*  End of include guard.                                                     */
