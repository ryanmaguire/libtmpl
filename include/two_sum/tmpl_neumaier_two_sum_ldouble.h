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
 *                       tmpl_neumaier_two_sum_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inlined Neumaier 2Sum function, or a forward declaration  *
 *      if inline support is not available.                                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_INLINE and TMPL_RESTRICT macros.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 29, 2026                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_SUM_NEUMAIER_TWO_SUM_LDOUBLE_H
#define TMPL_TWO_SUM_NEUMAIER_TWO_SUM_LDOUBLE_H

/*  The TMPL_USE_INLINE and TMPL_RESTRICT macros are found here.              */
#include <libtmpl/include/tmpl_config.h>

/*  Neumaier 2Sum is small enough that it should be inlined.                  */
#if TMPL_USE_INLINE == 1

/*  Implemented in the inline directory.                                      */
#include <libtmpl/include/inline/two_sum/tmpl_neumaier_two_sum_ldouble.h>

/*  Lacking inline support, provide the forward declaration to the compiler.  */
#else

/*  Function for performing the Neumaier 2Sum algorithm.                      */
extern void
tmpl_LDouble_Neumaier_Two_Sum(const long double summand,
                              long double * TMPL_RESTRICT const sum,
                              long double * TMPL_RESTRICT const err);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
