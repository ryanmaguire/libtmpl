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
 *                         tmpl_multiply_doubledouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Double-word multiplication implementation.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 12, 2026                                                  *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  tmpl_DoubleDouble typedef provided here.                                  */
#include <libtmpl/include/types/tmpl_doubledouble_double.h>

/*  Function prototype / forward declaration.                                 */
extern tmpl_DoubleDouble
tmpl_DoubleDouble_Multiply(const tmpl_DoubleDouble * const x,
                           const tmpl_DoubleDouble * const y);

/*  Implemented in include/doubledouble/tmpl_multiply_doubledouble.h.         */
#include "../../include/inline/doubledouble/tmpl_multiply_doubledouble.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
