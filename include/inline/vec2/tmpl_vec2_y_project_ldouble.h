/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
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
 *                        tmpl_vec2_y_project_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Projects a point in the plane onto the y axis.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_Y_Project                                              *
 *  Purpose:                                                                  *
 *      Computes the projection of a vector onto the y axis.                  *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorLongDouble * const):                           *
 *          A pointer to a point in the Euclidean plane.                      *
 *  Output:                                                                   *
 *      y_projection (tmpl_TwoVectorLongDouble):                              *
 *          The projection of P onto the y axis.                              *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The projection is obtained by zeroing out the x part of P. That is,   *
 *      if P = (a, b), the projection is given by setting:                    *
 *                                                                            *
 *          x = 0                                                             *
 *          y = b                                                             *
 *                                                                            *
 *      We copy these values and return.                                      *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P is a valid *
 *          pointer to a 2D vector.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_ldouble.h:                                                  *
 *          The tmpl_TwoVectorLongDouble typedef is provided here.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 6, 2025                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_Y_PROJECT_LDOUBLE_H
#define TMPL_VEC2_Y_PROJECT_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Function for projecting a point onto the y axis.                          */
TMPL_INLINE_DECL
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Y_Project(const tmpl_TwoVectorLongDouble * const P)
{
    /*  Output variable for the projection of P onto the y axis.              */
    tmpl_TwoVectorLongDouble y_projection;

    /*  The projection copies the y component and zeroes out the x value.     */
    y_projection.dat[0] = 0.0F;
    y_projection.dat[1] = P->dat[1];
    return y_projection;
}
/*  End of tmpl_2DLDouble_Y_Project.                                          */

#endif
/*  End of include guard.                                                     */
