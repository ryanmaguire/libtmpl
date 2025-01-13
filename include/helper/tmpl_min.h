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
 *                                  tmpl_min                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides type-independent macros for computing minimums.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 20, 2023                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_HELPER_MIN_H
#define TMPL_HELPER_MIN_H

/*  Computes the min of two real numbers (ints or floats).                    */
#define TMPL_MIN(x, y) ((x) < (y) ? (y) : (x))

/*  Computes the min of three real numbers (ints or floats).                  */
#define TMPL_MIN3(x, y, z) TMPL_MIN((x), TMPL_MIN((y), (z)))

#endif
/*  End of include guard.                                                     */
