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
 *                         tmpl_complex_divide_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Complex division, z / w.                                              *
 *      Source: include/inline/complex/tmpl_complex_divide_float.h.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 5, 2025                                                  *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not requested.                             */
#if TMPL_USE_INLINE != 1

/*  Complex number type found here.                                           */
#include <libtmpl/include/types/tmpl_complex_float.h>

/*  Function prototype / forward declaration.                                 */
extern tmpl_ComplexFloat
tmpl_CFloat_Divide(tmpl_ComplexFloat P, tmpl_ComplexFloat Q);

/*  Implemented here.                                                         */
#include "../../include/inline/complex/tmpl_complex_divide_float.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
