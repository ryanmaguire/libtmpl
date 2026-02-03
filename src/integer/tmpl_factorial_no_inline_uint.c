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
 *                            tmpl_factorial_uint                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes n!. See include/inline/integer/tmpl_factorial_uint.h.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 25, 2024                                                  *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  Function prototype / forward declaration.                                 */
extern unsigned int tmpl_UInt_Factorial(const unsigned int n);

/*  Implemented here.                                                         */
#include "../../include/inline/integer/tmpl_factorial_uint.h"

#endif
/*  End of #if TMPL_USE_INLINE =! 1.                                          */
