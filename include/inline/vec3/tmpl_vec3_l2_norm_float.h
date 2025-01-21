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
 *                          tmpl_vec3_l2_norm_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Euclidean norm at single precision.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_L2_Norm                                                  *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm, also called the L2 norm, of the input.   *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm (float):                                                         *
 *          The Euclidean norm of P.                                          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Hypot3:                                                *
 *              Computes the magnitude of (x, y, z).                          *
 *  Method:                                                                   *
 *      Pass the components to the Hypot3 function.                           *
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
 *  3.) tmpl_math.h:                                                          *
 *          Header file providing the Hypot3 function.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/03/03: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 *      Changed routine to be safer, ensuring overflow does not occur in any  *
 *      intermediate steps.                                                   *
 *  2024/06/10: Ryan Maguire                                                  *
 *      Migrated the bulk of the code to src/math into the Hypot3 function.   *
 *      Inlined the routine.                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_L2_NORM_FLOAT_H
#define TMPL_VEC3_L2_NORM_FLOAT_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_float.h>

/*  Hypot3 function found here.                                               */
#include <libtmpl/include/tmpl_math.h>

/*  Computes the L2 norm of a 3D vector.                                      */
TMPL_INLINE_DECL
float tmpl_3DFloat_L2_Norm(const tmpl_ThreeVectorFloat * const P)
{
    return tmpl_Float_Hypot3(P->dat[0], P->dat[1], P->dat[2]);
}
/*  End of tmpl_3DFloat_L2_Norm.                                              */

#endif
/*  End of include guard.                                                     */
