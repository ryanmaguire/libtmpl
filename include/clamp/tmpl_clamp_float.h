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
 *                              tmpl_clamp_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inlined clamp function, or a forward declaration if       *
 *      inline support is not available.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_INLINE macro.                               *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 10, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CLAMP_CLAMP_FLOAT_H
#define TMPL_CLAMP_CLAMP_FLOAT_H

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  The clamp function is small enough that it can be inlined. Check for      *
 *  support.                                                                  */
#if TMPL_USE_INLINE == 1

/*  Implemented in the inline directory.                                      */
#include <libtmpl/include/inline/math/tmpl_clamp_impl_float.h>

/*  Lacking inline support, provide the forward declaration to the compiler.  */
#else

/*  Single precision clamp function.                                          */
TMPL_CONST_FUNC
extern float
tmpl_Float_Clamp(const float x, const float min, const float max)
TMPL_UNSEQUENCED;

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
