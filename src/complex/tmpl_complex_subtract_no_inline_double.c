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
 *                        tmpl_complex_subtract_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Complex subtraction.                                                  *
 *      Source: include/inline/complex/tmpl_complex_subtract_double.h.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 15, 2026                                              *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not requested.                             */
#if TMPL_USE_INLINE != 1

/*  Double precision complex numbers.                                         */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  Function prototype / forward declaration.                                 */
extern tmpl_ComplexDouble
tmpl_CDouble_Subtract(const tmpl_ComplexDouble z, const tmpl_ComplexDouble w);

/*  Implemented here.                                                         */
#include "../../include/inline/complex/tmpl_complex_subtract_double.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
