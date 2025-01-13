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
 *                           tmpl_vec3_scale_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs scalar multiplication at single precision.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Scale                                                    *
 *  Purpose:                                                                  *
 *      Computes scalar multiplication at single precision.                   *
 *  Arguments:                                                                *
 *      a (float):                                                            *
 *          A real number, the scalar multiplier.                             *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      prod (tmpl_ThreeVectorFloat):                                         *
 *          The product a*P.                                                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of scalar multiplication. If P = (Px, Py, Pz),     *
 *      then a*P has coordinates:                                             *
 *          x = a*Px                                                          *
 *          y = a*Py                                                          *
 *          z = a*Pz                                                          *
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
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/17: Ryan Maguire                                                  *
 *      Added float and long double versions.                                 *
 *  2024/06/11: Ryan Maguire                                                  *
 *      Changed function to pass by reference instead of by value. Inlined.   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_SCALE_FLOAT_H
#define TMPL_VEC3_SCALE_FLOAT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_float.h>

/*  Multiply a three vector by a real number.                                 */
TMPL_INLINE_DECL
tmpl_ThreeVectorFloat
tmpl_3DFloat_Scale(float a, const tmpl_ThreeVectorFloat * const P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorFloat scaled;

    /*  Scalar multiplication is done component-wise, so compute this.        */
    scaled.dat[0] = a*P->dat[0];
    scaled.dat[1] = a*P->dat[1];
    scaled.dat[2] = a*P->dat[2];
    return scaled;
}
/*  End of tmpl_3DFloat_Scale.                                                */

#endif
/*  End of include guard.                                                     */
