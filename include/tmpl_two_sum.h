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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_SUM_H
#define TMPL_TWO_SUM_H

/*  TMPL_USE_INLINE macro provided here, as is TMPL_RESTRICT.                 */
#include <libtmpl/include/tmpl_config.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Fast_Two_Sum                                              *
 *  Purpose:                                                                  *
 *      Performs the standard Fast2Sum algorithm for floating-point addition. *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *      y (double):                                                           *
 *          Another real number.                                              *
 *      out (double * const):                                                 *
 *          The floating-point sum x + y is stored here.                      *
 *      err (double * const):                                                 *
 *          The error, sum(x, y) - (x + y), is stored here.                   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      Fast2Sum assumes |x| >= |y|.                                          *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/

/*  These functions are very small and should be inlined, if possible.        */
#if TMPL_USE_INLINE == 1

/*  Inline versions for each data type found here.                            */
#include <libtmpl/include/inline/two_sum/tmpl_fast_two_sum_float.h>
#include <libtmpl/include/inline/two_sum/tmpl_fast_two_sum_double.h>
#include <libtmpl/include/inline/two_sum/tmpl_fast_two_sum_ldouble.h>

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Lacking inline support, use the versions in src/two_sum/.                 */
extern void
tmpl_Float_Fast_Two_Sum(float x,
                        float y,
                        float * TMPL_RESTRICT const out,
                        float * TMPL_RESTRICT const err);

extern void
tmpl_Double_Fast_Two_Sum(double x,
                         double y,
                         double * TMPL_RESTRICT const out,
                         double * TMPL_RESTRICT const err);

extern void
tmpl_LDouble_Fast_Two_Sum(long double x,
                          long double y,
                          long double * TMPL_RESTRICT const out,
                          long double * TMPL_RESTRICT const err);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Two_Sum                                                   *
 *  Purpose:                                                                  *
 *      Performs the standard 2Sum algorithm for floating-point addition.     *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *      y (double):                                                           *
 *          Another real number.                                              *
 *      out (double * const):                                                 *
 *          The floating-point sum x + y is stored here.                      *
 *      err (double * const):                                                 *
 *          The error, sum(x, y) - (x + y), is stored here.                   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/

/*  These functions are very small and should be inlined, if possible.        */
#if TMPL_USE_INLINE == 1

/*  Inline versions for each data type found here.                            */
#include <libtmpl/include/inline/two_sum/tmpl_two_sum_float.h>
#include <libtmpl/include/inline/two_sum/tmpl_two_sum_double.h>
#include <libtmpl/include/inline/two_sum/tmpl_two_sum_ldouble.h>

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Lacking inline support, use the versions in src/two_sum/.                 */
extern void
tmpl_Float_Two_Sum(float x,
                   float y,
                   float * TMPL_RESTRICT const out,
                   float * TMPL_RESTRICT const err);

extern void
tmpl_Double_Two_Sum(double x,
                    double y,
                    double * TMPL_RESTRICT const out,
                    double * TMPL_RESTRICT const err);

extern void
tmpl_LDouble_Two_Sum(long double x,
                     long double y,
                     long double * TMPL_RESTRICT const out,
                     long double * TMPL_RESTRICT const err);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
