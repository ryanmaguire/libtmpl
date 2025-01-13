/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                      tmpl_vec3_quick_linf_norm_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the supremum norm at double precision.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_LInf_Norm                                               *
 *  Purpose:                                                                  *
 *      Computes the supremum norm (L-infinity norm) of the input.            *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorDouble * const):                             *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm (double):                                                        *
 *          The supremum norm of P.                                           *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Abs:                                                  *
 *              Computes the absolute value of a real number.                 *
 *  Method:                                                                   *
 *      Compute the max of the absolute values of the components.             *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_double.h:                                                   *
 *          Header containing ThreeVector typedef.                            *
 *  3.) tmpl_math.h:                                                          *
 *          Header file providing the absolute value function.                *
 *  4.) tmpl_minmax.h:                                                        *
 *          Provides helper macros for computing min and max.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 5, 2022                                               *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2024/06/11: Ryan Maguire                                                  *
 *      Inlined the routine.                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_LINF_DOUBLE_H
#define TMPL_VEC3_LINF_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_double.h>

/*  Absolute value function found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  TMPL_MAX3 helper macro found here.                                        */
#include <libtmpl/include/tmpl_minmax.h>

/*  Function for computing the L-Infinity norm of a 3D vector.                */
TMPL_INLINE_DECL
double tmpl_3DDouble_LInf_Norm(const tmpl_ThreeVectorDouble * const P)
{
    const double absx = tmpl_Double_Abs(P->dat[0]);
    const double absy = tmpl_Double_Abs(P->dat[1]);
    const double absz = tmpl_Double_Abs(P->dat[2]);
    return TMPL_MAX3(absx, absy, absz);
}
/*  End of tmpl_3DDouble_LInf_Norm.                                           */

#endif
/*  End of include guard.                                                     */
