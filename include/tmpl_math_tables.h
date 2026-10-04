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
 *                              tmpl_math_tables                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides lookup tables for various functions.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 1, 2026                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_TABLES_H
#define TMPL_MATH_TABLES_H

/*  Two tables, hi and lo, so that 2^(k / 128) = hi * (1 + lo). The hi table  *
 *  is 2^(k / 128) rounded to the respective precision, and the lo table      *
 *  contains the error that stems from floating-point round off.              */
extern const double tmpl_double_pow_2_hi_table[128];
extern const float tmpl_float_pow_2_hi_table[128];
extern const long double tmpl_ldouble_pow_2_hi_table[128];

extern const double tmpl_double_pow_2_lo_table[128];
extern const float tmpl_float_pow_2_lo_table[128];
extern const long double tmpl_ldouble_pow_2_lo_table[128];

#endif
/*  End of include guard.                                                     */
