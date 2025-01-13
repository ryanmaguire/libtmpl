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
 *                           tmpl_vec3_add_to_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing vector addition at single precision.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_AddTo                                                    *
 *  Purpose:                                                                  *
 *      Computes the vector sum of two vectors at single precision.           *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorFloat * const):                               *
 *          A pointer to a vector in R^3. The sum will be stored here.        *
 *      source (const tmpl_ThreeVectorFloat * const):                         *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of vector addition. If P = (Px, Py, Pz) and        *
 *      Q = (Qx, Qy, Qz), then the vector sum P+Q has coordinates:            *
 *          x = Px + Qx                                                       *
 *          y = Py + Qy                                                       *
 *          z = Pz + Qz                                                       *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      If tmpl_3DFloat_Add is the equivalent of the "+" operator for the     *
 *      tmpl_ThreeVectorFloat struct, this is the equivalent of "+=". It is   *
 *      about 2-3x faster to do tmpl_3DFloat_AddTo(&P, &Q) instead of doing   *
 *      P = tmpl_3DFloat_Add(&P, &Q).                                         *
 *                                                                            *
 *      A %40 to %50 increase in performance was found (pending hardware and  *
 *      compiler used) by inlining this function.                             *
 *                                                                            *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_float.h:                                                    *
 *          The tmpl_ThreeVectorFloat typedef is provided here.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 15, 2022                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/17: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 *  2024/06/06: Ryan Maguire                                                  *
 *      Inlined the function.                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_ADD_TO_FLOAT_H
#define TMPL_VEC3_ADD_TO_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_float.h>

/*  Function for performing vector addition in R^3.                           */
TMPL_INLINE_DECL
void tmpl_3DFloat_AddTo(tmpl_ThreeVectorFloat * const target,
                        const tmpl_ThreeVectorFloat * const source)
{
    target->dat[0] += source->dat[0];
    target->dat[1] += source->dat[1];
    target->dat[2] += source->dat[2];
}
/*  End of tmpl_3DFloat_AddTo.                                                */

#endif
/*  End of include guard.                                                     */
