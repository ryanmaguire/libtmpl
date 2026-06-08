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
 *                            tmpl_two_sum_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inlined 2Sum function, or a forward declaration if        *
 *      inline support is not available.                                      *
 *  Notes:                                                                    *
 *      1.) 2Sum does not require |x| >= |y|, but it requires twice as many   *
 *          arithmetic operations as Fast2Sum.                                *
 *                                                                            *
 *      2.) There are no checks for NULL pointers.                            *
 *                                                                            *
 *      3.) There are no checks for NaN or infinity.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_INLINE and TMPL_RESTRICT macros.            *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 29, 2026                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_SUM_TWO_SUM_DOUBLE_H
#define TMPL_TWO_SUM_TWO_SUM_DOUBLE_H

/*  The TMPL_USE_INLINE and TMPL_RESTRICT macros are found here.              */
#include <libtmpl/include/tmpl_config.h>

/*  2Sum is small enough that it should be inlined. Check for support.        */
#if TMPL_USE_INLINE == 1

/*  Implemented in the inline directory.                                      */
#include <libtmpl/include/inline/two_sum/tmpl_two_sum_double.h>

/*  Lacking inline support, provide the forward declaration to the compiler.  */
#else

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function for performing the 2Sum algorithm.                               */
extern void
tmpl_Double_Two_Sum(const double x,
                    const double y,
                    double * TMPL_RESTRICT const out,
                    double * TMPL_RESTRICT const err)
TMPL_REPRODUCIBLE;

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
