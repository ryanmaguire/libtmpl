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
 *                         tmpl_vec3_midpoint_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the midpoint of two points in R^3.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Midpoint                                               *
 *  Purpose:                                                                  *
 *      Computes the midpoint of two points in R^3.                           *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorLongDouble * const):                         *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      midpoint (tmpl_ThreeVectorLongDouble):                                *
 *          The midpoint of P and Q.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of midpoints. If P = (Px, Py, Pz) and              *
 *      Q = (Qx, Qy, Qz), then the midpoint has coordinates:                  *
 *          x = (Px + Qx) / 2                                                 *
 *          y = (Py + Qy) / 2                                                 *
 *          z = (Pz + Qz) / 2                                                 *
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
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_MIDPOINT_LDOUBLE_H
#define TMPL_VEC3_MIDPOINT_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_ldouble.h>

/*  Function for computing the midpoint of two points.                        */
TMPL_INLINE_DECL
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Midpoint(const tmpl_ThreeVectorLongDouble * const P,
                        const tmpl_ThreeVectorLongDouble * const Q)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorLongDouble midpoint;

    /*  Use the midpoint formula and return.                                  */
    midpoint.dat[0] = (P->dat[0] + Q->dat[0]) * 0.5L;
    midpoint.dat[1] = (P->dat[1] + Q->dat[1]) * 0.5L;
    midpoint.dat[2] = (P->dat[2] + Q->dat[2]) * 0.5L;
    return midpoint;
}
/*  End of tmpl_3DLDouble_Midpoint.                                           */

#endif
/*  End of include guard.                                                     */
