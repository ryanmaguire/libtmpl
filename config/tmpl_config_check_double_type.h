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
 *                        tmpl_config_check_double_type                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines how double is represented and sets the appropriate globals.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_check_double_type                                                *
 *  Purpose:                                                                  *
 *      Determines if double uses IEEE-754 64-bit format and sets the config  *
 *      globals that indicate this.                                           *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_double_type.h:                                    *
 *              tmpl_det_double_type:                                         *
 *                  Determines double representation using type-punning.      *
 *  Method:                                                                   *
 *      Set the globals tmpl_double_rep and tmpl_double_type_has_been_checked *
 *      after calling the tmpl_det_double_type function.                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_globals.h:                                                *
 *          Header file with all of the globals used by config.c.             *
 *  2.) tmpl_config_det_double_type.h:                                        *
 *          Provides the tmpl_det_double_type function.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_CHECK_DOUBLE_TYPE_H
#define TMPL_CONFIG_CHECK_DOUBLE_TYPE_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  The tmpl_det_double_type function is found here.                          */
#include "tmpl_config_det_double_type.h"

/*  Function for setting the config globals for the double type.              */
static void tmpl_check_double_type(void)
{
    tmpl_double_rep = tmpl_det_double_type();
    tmpl_double_type_has_been_checked = 1U;
}
/*  End of tmpl_check_double_type.                                            */

#endif
/*  End of include guard.                                                     */
