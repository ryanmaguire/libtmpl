/******************************************************************************
 *                                 LICENSE                                    *
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
 *                      tmpl_vec3_quick_normalize_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing unit normal vectors.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Quick_Normalize                                          *
 *  Purpose:                                                                  *
 *      Computes the unit normal of the input non-zero vector.                *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A non-zero vector in R^3.                                         *
 *  Output:                                                                   *
 *      P_hat (tmpl_ThreeVectorFloat):                                        *
 *          The unit normal of P.                                             *
 *  Method:                                                                   *
 *      Divide the components by the norm of the input.                       *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Quick_Hypot3:                                          *
 *              Computes the norm of (x, y, z).                               *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *      2.) If the vector is zero, (NaN, NaN, NaN) is returned.               *
 *      3.) This function does not handle overflow properly. Use              *
 *          tmpl_3DFloat_Normalize if you are working with vectors that       *
 *          have very large components. That function safely handles overflow *
 *          but is slower.                                                    *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_INLINE_DECL macro.                              *
 *  2.) tmpl_vec3_float.h:                                                    *
 *          Header containing ThreeVector typedef.                            *
 *  3.) tmpl_math.h:                                                          *
 *          Provides the hypot3 function.                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 11, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_QUICK_NORMALIZE_FLOAT_H
#define TMPL_VEC3_QUICK_NORMALIZE_FLOAT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef given here.                                          */
#include <libtmpl/include/types/tmpl_vec3_float.h>

/*  Quick hypot3 function provided here.                                      */
#include <libtmpl/include/tmpl_math.h>

/*  Function for normalizing a 3D vector.                                     */
TMPL_INLINE_DECL
tmpl_ThreeVectorFloat
tmpl_3DFloat_Quick_Normalize(const tmpl_ThreeVectorFloat * const P)
{
    /*  Variable for the output.                                              */
    tmpl_ThreeVectorFloat normalized;

    /*  The normalization factor is the reciprocal of the norm.               */
    const float rcpr_norm =
        1.0F / tmpl_Float_Quick_Hypot3(P->dat[0], P->dat[1], P->dat[2]);

    /*  Scale the components of the input to normalize.                       */
    normalized.dat[0] = P->dat[0] * rcpr_norm;
    normalized.dat[1] = P->dat[1] * rcpr_norm;
    normalized.dat[2] = P->dat[2] * rcpr_norm;
    return normalized;
}
/*  End of tmpl_3DFloat_Quick_Normalize.                                      */

#endif
/*  End of include guard.                                                     */
