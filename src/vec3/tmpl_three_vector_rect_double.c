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
 *                        tmpl_three_vector_rect_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for creating 3D vectors via Cartesian coordinates.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Rect                                                    *
 *  Purpose:                                                                  *
 *      Creates a double-precision 3D vector from Cartesian coordinates.      *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          The x coordinate of the output vector.                            *
 *      y (double):                                                           *
 *          The y coordinate of the output vector.                            *
 *      z (double):                                                           *
 *          The z coordinate of the output vector.                            *
 *  Output:                                                                   *
 *      V (tmpl_ThreeVectorDouble):                                           *
 *          The vector (x, y, z).                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Set the components of V to x, y, and z.                               *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/17/02: Ryan Maguire                                                  *
 *      Added doc-string.                                                     *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for returning the point (x, y, z) given three doubles x, y, z.   */
tmpl_ThreeVectorDouble tmpl_3DDouble_Rect(double x, double y, double z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ThreeVectorDouble P;

    /*  Set the zeroth entry of P.dat to x, the first to y, and second to z.  */
    P.dat[0] = x;
    P.dat[1] = y;
    P.dat[2] = z;
    return P;
}
/*  End of tmpl_3DDouble_Rect.                                                */
