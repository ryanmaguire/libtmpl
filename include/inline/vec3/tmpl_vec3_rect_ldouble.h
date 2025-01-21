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
 *                           tmpl_vec3_rect_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for creating 3D vectors via Cartesian coordinates.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Rect                                                   *
 *  Purpose:                                                                  *
 *      Creates a single-precision 3D vector from Cartesian coordinates.      *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          The x coordinate of the output vector.                            *
 *      y (long double):                                                      *
 *          The y coordinate of the output vector.                            *
 *      z (long double):                                                      *
 *          The z coordinate of the output vector.                            *
 *  Output:                                                                   *
 *      P (tmpl_ThreeVectorLongDouble):                                       *
 *          The vector (x, y, z).                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Set the components of P to x, y, and z.                               *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_vec3_ldouble.h:                                                  *
 *          Header containing ThreeVector typedef.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/10/05: Ryan Maguire                                                  *
 *      Added doc-string.                                                     *
 *  2024/06/11: Ryan Maguire                                                  *
 *      Inlined the function.                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_RECT_LDOUBLE_H
#define TMPL_VEC3_RECT_LDOUBLE_H

/*  TMPL_INLINE_DECL macro provided here.                                     */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  Function for returning the point (x, y, z) given three numbers x, y, z.   */
TMPL_INLINE_DECL
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Rect(long double x, long double y, long double z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ThreeVectorLongDouble P;

    /*  Set the zeroth entry of P.dat to x, the first to y, and second to z.  */
    P.dat[0] = x;
    P.dat[1] = y;
    P.dat[2] = z;
    return P;
}
/*  End of tmpl_3DLDouble_Rect.                                               */

#endif
/*  End of include guard.                                                     */
