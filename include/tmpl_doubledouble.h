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
 *                             tmpl_doubledouble                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a software implementation of double-double.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_inttype.h:                                                       *
 *          Header file with the TMPL_HAS_LONGLONG macro.                     *
 *  2.) stddef.h:                                                             *
 *          Standard header file where size_t is declared.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 27, 2024                                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_DOUBLEDOUBLE_H
#define TMPL_DOUBLEDOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  If we already have double-double for long double, we don't need anything  *
 *  new and can just typedef long double.                                     */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE
typedef long double tmpl_DoubleDouble;
#else
typedef struct tmpl_DoubleDouble_Def {
    double dat[2];
} tmpl_DoubleDouble;
#endif

/*  If long double and double are the same we don't need two types.           */
#if TMPL_LDOUBLE_TYPE != TMPL_LDOUBLE_64_BIT
typedef struct tmpld_LongDoubleDouble_Def {
    long double dat[2];
} tmpl_LongDoubleDouble;
#else
typedef tmpl_DoubleDouble tmpl_LongDoubleDouble;
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_DoubleDouble_Create                                              *
 *  Purpose:                                                                  *
 *      Creates a double-double from two doubles.                             *
 *  Arguments:                                                                *
 *      hi (double):                                                          *
 *          The high part of the double.                                      *
 *      lo (double):                                                          *
 *          The low part of the double.                                       *
 *  Output:                                                                   *
 *      val (tmpl_DoubleDouble):                                              *
 *          The double-double value hi + lo.                                  *
 *  Notes:                                                                    *
 *      long double-double is also provided.                                  *
 ******************************************************************************/
extern tmpl_DoubleDouble
tmpl_DoubleDouble_Create(double hi, double lo);

extern tmpl_LongDoubleDouble
tmpl_LongDoubleDouble_Create(long double hi, long double lo);

#endif
/*  End of include guard.                                                     */
