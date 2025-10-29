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
 *                           tmpl_config_det_widths                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Detects the widths of all unsigned integer types.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_det_widths                                                       *
 *  Purpose:                                                                  *
 *      Detects the widths of all unsigned integer types.                     *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_uchar_width.h:                                    *
 *              tmpl_det_uchar_width:                                         *
 *                  Computes the number of bits in unsigned char.             *
 *          tmpl_config_det_ushort_width.h:                                   *
 *              tmpl_det_ushort_width:                                        *
 *                  Computes the number of bits in unsigned short.            *
 *          tmpl_config_det_uint_width.h:                                     *
 *              tmpl_det_uint_width:                                          *
 *                  Computes the number of bits in unsigned int.              *
 *          tmpl_config_det_ulong_width.h:                                    *
 *              tmpl_det_ulong_width:                                         *
 *                  Computes the number of bits in unsigned long.             *
 *          tmpl_config_det_ullong_width.h:                                   *
 *              tmpl_det_ullong_width:                                        *
 *                  Computes the number of bits in unsigned long long.        *
 *  Method:                                                                   *
 *      Call all of the width functions for each data type.                   *
 *  Notes:                                                                    *
 *      1.) This function does not attempt to determine the width of signed   *
 *          integer data types.                                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_globals.h:                                                *
 *          Header file with all of the globals used by config.c.             *
 *  2.) tmpl_config_det_uchar_width.h:                                        *
 *          Provides the tmpl_det_uchar_width function.                       *
 *  3.) tmpl_config_det_ushort_width.h:                                       *
 *          Provides the tmpl_det_ushort_width function.                      *
 *  4.) tmpl_config_det_uint_width.h:                                         *
 *          Provides the tmpl_det_uint_width function.                        *
 *  5.) tmpl_config_det_ulong_width.h:                                        *
 *          Provides the tmpl_det_ulong_width function.                       *
 *  6.) tmpl_config_det_ullong_width.h:                                       *
 *          Provides the tmpl_det_ullong_width function.                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/08: Ryan Maguire                                                  *
 *      Moved function to its own file.                                       *
 *  2025/10/27: Ryan Maguire                                                  *
 *      Moved enum definition to the config globals file.                     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_DET_WIDTHS_H
#define TMPL_CONFIG_DET_WIDTHS_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  Functions for computing the widths of unsigned types found here.          */
#include "tmpl_config_det_uchar_width.h"
#include "tmpl_config_det_ushort_width.h"
#include "tmpl_config_det_uint_width.h"
#include "tmpl_config_det_ulong_width.h"
#include "tmpl_config_det_ullong_width.h"

/*  Function for determining the number of bits in all unsigned types.        */
static void tmpl_det_widths(void)
{
    /*  Char, short, int, and long are standard in all version of C.          */
    tmpl_det_uchar_width();
    tmpl_det_ushort_width();
    tmpl_det_uint_width();
    tmpl_det_ulong_width();

    /*  Long long was only introduced with the C99 standard.                  */
#ifdef TMPL_LONG_LONG_IS_AVAILABLE
    tmpl_det_ullong_width();
#endif

}
/*  End of tmpl_det_widths.                                                   */

#endif
/*  End of include guard.                                                     */
