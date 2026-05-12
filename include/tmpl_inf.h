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
 *                                  tmpl_inf                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for working with floating-point infinity.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 12, 2026                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_INF_H
#define TMPL_INF_H

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Float_Infinity                                                   *
 *  Purpose:                                                                  *
 *      Returns positive infinity.                                            *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      inf (float):                                                          *
 *          Infinity.                                                         *
 *  Notes:                                                                    *
 *      1.) Double and long double equivalents are also provided.             *
 *                                                                            *
 *      2.) If IEEE-754 support is available, this code creates infinity      *
 *          using the format. If not, the function mimics glibc's method,     *
 *          returning the number 1.0E10000 which is guaranteed to overflow.   *
 ******************************************************************************/
#include <libtmpl/include/inf/tmpl_inf_double.h>
#include <libtmpl/include/inf/tmpl_inf_float.h>
#include <libtmpl/include/inf/tmpl_inf_ldouble.h>

#endif
/*  End of include guard.                                                     */
