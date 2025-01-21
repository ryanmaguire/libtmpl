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
 *                          tmpl_create_ldoubledouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      DW construction. See include/doubledouble/tmpl_create_ldoubledouble.h.*
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 29, 2024                                             *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_doubledouble.h>

/*  Implemented in include/doubledouble/tmpl_create_ldoubledouble.h.          */
#include "../../include/inline/doubledouble/tmpl_create_ldoubledouble.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
