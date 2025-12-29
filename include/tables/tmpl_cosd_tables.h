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
 *                              tmpl_cosd_tables                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides lookup tables for cosine in degrees.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 29, 2025                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TABLES_COSD_TABLES_H
#define TMPL_TABLES_COSD_TABLES_H

/*  The values cos(pi * k / 180) for k = 0, 1, ..., 179.                      */
extern const double tmpl_double_cosd_table[180];
extern const float tmpl_float_cosd_table[180];
extern const long double tmpl_ldouble_cosd_table[180];

#endif
/*  End of include guard.                                                     */
