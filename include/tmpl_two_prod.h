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
#ifndef TMPL_TWO_PROD_H
#define TMPL_TWO_PROD_H

/*  TMPL_USE_INLINE macro provided here, as is TMPL_RESTRICT.                 */
#include <libtmpl/include/tmpl_config.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Two_Prod                                                  *
 *  Purpose:                                                                  *
 *      Performs the 2Prod algorithm for floating-point multiplication.       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *      y (double):                                                           *
 *          Another real number.                                              *
 *      out (double * const):                                                 *
 *          The floating-point product x * y is stored here.                  *
 *      err (double * const):                                                 *
 *          The error, prod(x, y) - (x * y), is stored here.                  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/

/*  These functions are very small and should be inlined, if possible.        */
#if TMPL_USE_INLINE == 1

/*  Inline versions for each data type found here.                            */
#include <libtmpl/include/inline/two_prod/tmpl_two_prod_float.h>
#include <libtmpl/include/inline/two_prod/tmpl_two_prod_double.h>
#include <libtmpl/include/inline/two_prod/tmpl_two_prod_ldouble.h>

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Lacking inline support, use the versions in src/two_prod/.                */
extern void
tmpl_Float_Two_Prod(float x,
                    float y,
                    float * const TMPL_RESTRICT out,
                    float * const TMPL_RESTRICT err);

extern void
tmpl_Double_Two_Prod(double x,
                     double y,
                     double * const TMPL_RESTRICT out,
                     double * const TMPL_RESTRICT err);

extern void
tmpl_LDouble_Two_Prod(long double x,
                      long double y,
                      long double * const TMPL_RESTRICT out,
                      long double * const TMPL_RESTRICT err);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
