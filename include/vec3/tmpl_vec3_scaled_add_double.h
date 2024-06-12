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
 *                        tmpl_vec3_scaled_add_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing vector addition at double precision.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Scaled_Add                                              *
 *  Purpose:                                                                  *
 *      Computes the affine transformation L = P + a*Q.                       *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorDouble * const):                             *
 *          A pointer to a vector in R^3.                                     *
 *      a (double):                                                           *
 *          Scale factor for Q.                                               *
 *      Q (const tmpl_ThreeVectorDouble * const):                             *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      sum (tmpl_ThreeVectorDouble):                                         *
 *          The sum P + a*Q.                                                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of vector addition. If P = (Px, Py, Pz) and        *
 *      Q = (Qx, Qy, Qz), then the vector sum P + a*Q has coordinates:        *
 *          x = Px + a*Qx                                                     *
 *          y = Py + a*Qy                                                     *
 *          z = Pz + a*Qz                                                     *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_double.h:                                                   *
 *          The tmpl_ThreeVectorDouble typedef is provided here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 11, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_SCALED_ADD_DOUBLE_H
#define TMPL_VEC3_SCALED_ADD_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_double.h>

/*  Function for performing affine transformations.                           */
TMPL_INLINE_DECL
tmpl_ThreeVectorDouble
tmpl_3DDouble_Scaled_Add(const tmpl_ThreeVectorDouble * const P,
                         double a,
                         const tmpl_ThreeVectorDouble * const Q)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorDouble sum;

    /*  Affine transformation, add scaled components of Q to P.               */
    sum.dat[0] = P->dat[0] + a*Q->dat[0];
    sum.dat[1] = P->dat[1] + a*Q->dat[1];
    sum.dat[2] = P->dat[2] + a*Q->dat[2];
    return sum;
}
/*  End of tmpl_3DDouble_Scaled_Add.                                          */

#endif
/*  End of include guard.                                                     */
