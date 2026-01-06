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
 *                          tmpl_complex_abs_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(z) = |z|, the modulus of a complex number.                 *
 *      Source: include/inline/complex/tmpl_complex_abs_ldouble.h.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not requested.                             */
#if TMPL_USE_INLINE != 1

/*  Long double precision complex numbers.                                    */
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  Function prototype / forward declaration.                                 */
extern long double tmpl_CLDouble_Abs(const tmpl_ComplexLongDouble z);

/*  Implemented here.                                                         */
#include "../../include/inline/complex/tmpl_complex_abs_ldouble.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
