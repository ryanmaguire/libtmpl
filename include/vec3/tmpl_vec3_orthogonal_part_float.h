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
 *                      tmpl_vec3_orthogonal_part_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the orthogonal part of one vector along another.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Orthogonal_Part                                          *
 *  Purpose:                                                                  *
 *      Computes the orthogonal part of a vector along another.               *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A vector in R^3.                                                  *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          The vector P is projected along.                                  *
 *  Output:                                                                   *
 *      orth (tmpl_ThreeVectorFloat):                                         *
 *          The orthogonal part of P along Q.                                 *
 *  Method:                                                                   *
 *      Subtract the component of P along Q from P.                           *
 *  Called Functions:                                                         *
 *      tmpl_vec3.h:                                                          *
 *          tmpl_3DFloat_Component:                                           *
 *              Computes the component of one vector along another.           *
 *          tmpl_3DFloat_Subtract:                                            *
 *              Performs vector subtraction.                                  *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *      2.) No checks for NULL pointers are performed.                        *
 *      3.) If the second vector is zero, the output is NaN.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 13, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_ORTHOGONAL_PART_FLOAT_H
#define TMPL_VEC3_ORTHOGONAL_PART_FLOAT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef and function prototype given here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the orthogonal part of one vector along another.   */
TMPL_INLINE_DECL
tmpl_ThreeVectorFloat
tmpl_3DFloat_Orthogonal_Part(const tmpl_ThreeVectorFloat * const P,
                             const tmpl_ThreeVectorFloat * const Q)
{
    /*  Variable for the output.                                              */
    const tmpl_ThreeVectorFloat component = tmpl_3DFloat_Component(P, Q);
    return tmpl_3DFloat_Subtract(P, &component);
}
/*  End of tmpl_3DFloat_Orthogonal_Part.                                      */

#endif
/*  End of include guard.                                                     */
