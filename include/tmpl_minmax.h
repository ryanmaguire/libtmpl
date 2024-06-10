/******************************************************************************
 *                                 LICENSE                                    *
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
 *                                tmpl_minmax                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides type-independent macros for computing min and max.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 20, 2023                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MINMAX_H
#define TMPL_MINMAX_H

/*  Computes the max and min of two real numbers (ints or floats).            */
#define TMPL_MAX(x, y) ((x) < (y) ? (y) : (x))
#define TMPL_MIN(x, y) ((x) < (y) ? (x) : (y))

/*  Computes the max and min of three real numbers (ints or floats).          */
#define TMPL_MAX3(x, y, z) TMPL_MAX((x), TMPL_MAX((y), (z)))
#define TMPL_MIN3(x, y, z) TMPL_MIN((x), TMPL_MIN((y), (z)))

#endif
/*  End of include guard.                                                     */
