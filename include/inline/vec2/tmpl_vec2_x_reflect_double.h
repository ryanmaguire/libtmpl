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
 *                         tmpl_vec2_x_reflect_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Reflects a point in the plane across the x axis.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DDouble_X_Reflect                                               *
 *  Purpose:                                                                  *
 *      Computes the reflection of a vector across the x axis.                *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a point in the Euclidean plane.                      *
 *  Output:                                                                   *
 *      x_reflection (tmpl_TwoVectorDouble):                                  *
 *          The reflection of P across the x axis.                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The reflection of P across the x axis can be computed by negating the *
 *      y component and leaving the x coordinate alone. That is, if           *
 *      P = (a, b), the reflection is given by setting:                       *
 *                                                                            *
 *          x = a                                                             *
 *          y = -b                                                            *
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
 *  2.) tmpl_vec2_double.h:                                                   *
 *          The tmpl_TwoVectorDouble typedef is provided here.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 29, 2025                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_X_REFLECT_DOUBLE_H
#define TMPL_VEC2_X_REFLECT_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Function for reflecting a point across the x axis.                        */
TMPL_INLINE_DECL
tmpl_TwoVectorDouble
tmpl_2DDouble_X_Reflect(const tmpl_TwoVectorDouble * const P)
{
    /*  Output variable for the reflection of P across the x axis.            */
    tmpl_TwoVectorDouble x_reflection;

    /*  The reflection copies the x component and negates the y value.        */
    x_reflection.dat[0] = P->dat[0];
    x_reflection.dat[1] = -P->dat[1];
    return x_reflection;
}
/*  End of tmpl_2DDouble_X_Reflect.                                           */

#endif
/*  End of include guard.                                                     */
