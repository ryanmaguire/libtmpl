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
 *                      tmpl_vec3_quick_linf_norm_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the supremum norm at single precision.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_LInf_Norm                                                *
 *  Purpose:                                                                  *
 *      Computes the supremum norm (L-infinity norm) of the input.            *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm (float):                                                         *
 *          The supremum norm of P.                                           *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Abs:                                                   *
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
 *  2.) tmpl_vec3_float.h:                                                    *
 *          Header containing ThreeVector typedef.                            *
 *  3.) tmpl_max.h:                                                           *
 *          Provides a helper macro for computing the max of 3 real numbers.  *
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
#ifndef TMPL_VEC3_LINF_FLOAT_H
#define TMPL_VEC3_LINF_FLOAT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_float.h>

/*  TMPL_MAX3 helper macro found here.                                        */
#include <libtmpl/include/helper/tmpl_max.h>

/*  The absolute value function is small enough to inline. Check for this.    */
#if TMPL_USE_INLINE == 1

/*  The function is found in the math inline directory.                       */
#include <libtmpl/include/inline/math/tmpl_abs_float.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise, just tell the compiler about the function.                     */
extern float tmpl_Float_Abs(float x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Function for computing the L-Infinity norm of a 3D vector.                */
TMPL_INLINE_DECL
float tmpl_3DFloat_LInf_Norm(const tmpl_ThreeVectorFloat * const P)
{
    const float absx = tmpl_Float_Abs(P->dat[0]);
    const float absy = tmpl_Float_Abs(P->dat[1]);
    const float absz = tmpl_Float_Abs(P->dat[2]);
    return TMPL_MAX3(absx, absy, absz);
}
/*  End of tmpl_3DFloat_LInf_Norm.                                            */

#endif
/*  End of include guard.                                                     */
