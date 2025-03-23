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
 *                                  tmpl_nan                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for working with NaN (Not-a-Number).                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_INLINE macro.                               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 23, 2025                                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NAN_H
#define TMPL_NAN_H

/*  Provides the TMPL_USE_INLINE macro for inlining functions.                */
#include <libtmpl/include/tmpl_config.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Float_NaN                                                        *
 *  Purpose:                                                                  *
 *      Returns Not-a-Number.                                                 *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      nan (float):                                                          *
 *          Not-a-Number.                                                     *
 *  Notes::                                                                   *
 *      1.) Double and long double equivalents are also provided.             *
 *      2.) If IEEE-754 support is available, this code creates NaN using     *
 *          the format. If not, the function mimics glibc's method, returning *
 *          the number 0.0 / 0.0 which should be NaN. This works in practice, *
 *          but it is technically undefined behavior.                         *
 ******************************************************************************/
#include <libtmpl/include/nan/tmpl_nan_double.h>
#include <libtmpl/include/nan/tmpl_nan_float.h>
#include <libtmpl/include/nan/tmpl_nan_ldouble.h>

#endif
/*  End of include guard.                                                     */
