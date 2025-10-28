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
 *                       tmpl_config_check_ldouble_type                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines how long double is represented and sets the config globals.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_check_ldouble_type                                               *
 *  Purpose:                                                                  *
 *      Determines if long double uses either IEEE-754 64-bit format, 128-bit *
 *      quadruple format, or 128-bit double-double format and sets the config *
 *      globals that indicate this.                                           *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_ldouble_type.h:                                   *
 *              tmpl_det_ldouble_type:                                        *
 *                  Determines long double representation using type-punning. *
 *  Method:                                                                   *
 *      Set the tmpl_ldouble_rep and tmpl_ldouble_type_has_been_checked       *
 *      globals after calling the tmpl_det_ldouble_type function.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_globals.h:                                                *
 *          Header file with all of the globals used by config.c.             *
 *  2.) tmpl_config_det_ldouble_type.h:                                       *
 *          Provides the tmpl_det_ldouble_type function.                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_CHECK_LDOUBLE_TYPE_H
#define TMPL_CONFIG_CHECK_LDOUBLE_TYPE_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  The tmpl_det_ldouble_type function is found here.                         */
#include "tmpl_config_det_ldouble_type.h"

/*  Function for setting the config globals for the long double type.         */
static void tmpl_check_ldouble_type(void)
{
    tmpl_ldouble_rep = tmpl_det_ldouble_type();
    tmpl_ldouble_type_has_been_checked = 1U;
}
/*  End of tmpl_check_ldouble_type.                                           */

#endif
/*  End of include guard.                                                     */
