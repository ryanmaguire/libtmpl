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
 *                         tmpl_vec3_subtract_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing vector subtraction for long double.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Subtract                                               *
 *  Purpose:                                                                  *
 *      Computes the difference of two vectors at long double precision.      *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorLongDouble * const):                         *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      diff (tmpl_ThreeVectorLongDouble):                                    *
 *          The vector difference P - Q.                                      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of vector subtraction. If P = (Px, Py, Pz) and     *
 *      Q = (Qx, Qy, Qz), then the vector difference P-Q has coordinates:     *
 *          x = Px - Qx                                                       *
 *          y = Py - Qy                                                       *
 *          z = Pz - Qz                                                       *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_ldouble.h:                                                  *
 *          The tmpl_ThreeVectorLongDouble typedef is provided here.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 11, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_SUBTRACT_LDOUBLE_H
#define TMPL_VEC3_SUBTRACT_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  Function for subtracting 2 three-dimensional vectors.                     */
TMPL_INLINE_DECL
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Subtract(const tmpl_ThreeVectorLongDouble * const P,
                        const tmpl_ThreeVectorLongDouble * const Q)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorLongDouble diff;

    /*  The difference of two vectors subtracts their components.             */
    diff.dat[0] = P->dat[0] - Q->dat[0];
    diff.dat[1] = P->dat[1] - Q->dat[1];
    diff.dat[2] = P->dat[2] - Q->dat[2];
    return diff;
}
/*  End of tmpl_3DLDouble_Subtract.                                           */

#endif
/*  End of include guard.                                                     */
