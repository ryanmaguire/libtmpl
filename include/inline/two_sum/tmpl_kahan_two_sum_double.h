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
 *                          tmpl_kahan_two_sum_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates the Kahan summand from the Kahan summation algorithm.       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2025                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_KAHAN_TWO_SUM_DOUBLE_H
#define TMPL_KAHAN_TWO_SUM_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_VOLATILE and TMPL_RESTRICT. */
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_two_sum.h>

/*  Kahan summation algorithm for accurately evaluating sum += input.         */
TMPL_INLINE_DECL
void
tmpl_Double_Kahan_Two_Sum(double input,
                          double * TMPL_RESTRICT const sum,
                          double * TMPL_RESTRICT const err)
{
    const double add = input + *sum;
    tmpl_Double_Fast_Two_Sum(add, *sum, sum, err);
}
/*  End of tmpl_Double_Kahan_Two_Sum.                                         */

#endif
/*  End of include guard.                                                     */
