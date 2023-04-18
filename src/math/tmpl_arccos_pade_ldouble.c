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
 *                          tmpl_arccos_pade_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Pade approximation for acos(x) at long double precision. *
 *      See include/math/tmpl_arccos_pade_ldouble.h for details.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support is not requested.                         */
#if TMPL_USE_INLINE != 1

/*  Implemented in include/math/tmpl_arccos_pade_ldouble.h. Include this.     */
#include "../../include/math/tmpl_arccos_pade_ldouble.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
