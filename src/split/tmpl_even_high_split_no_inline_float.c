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
 *                         tmpl_even_high_split_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Splits a number into two parts and returns the high word. See         *
 *      include/split/tmpl_even_high_split_float.h. for details.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 28, 2024                                               *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_split.h>

/*  Implemented in include/split/tmpl_even_high_split_float.h.                */
#include "../../include/split/tmpl_even_high_split_float.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
