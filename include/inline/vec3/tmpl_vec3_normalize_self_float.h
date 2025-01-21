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
 *                       tmpl_vec3_normalize_self_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for normalizing a vector at single precision.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_NormalizeSelf                                            *
 *  Purpose:                                                                  *
 *      Normalizes vector in R^3.                                             *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat * const):                                    *
 *          A pointer to a vector in R^3. The unit normal is stored here.     *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Divide the components of the input by its norm.                       *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
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
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_NORMALIZE_SELF_FLOAT_H
#define TMPL_VEC3_NORMALIZE_SELF_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_float.h>

/*  Function for normalizing a three dimensional vector.                      */
TMPL_INLINE_DECL
void tmpl_3DFloat_NormalizeSelf(tmpl_ThreeVectorFloat * const P)
{
    /*  The negative of a vector negates all of the components.               */
    const float rcpr_norm = 1.0F / tmpl_3DFloat_L2_Norm(P);
    P->dat[0] *= rcpr_norm;
    P->dat[1] *= rcpr_norm;
    P->dat[2] *= rcpr_norm;
}
/*  End of tmpl_3DFloat_NormalizeSelf.                                        */

#endif
/*  End of include guard.                                                     */
