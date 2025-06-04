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
 *                       tmpl_vec2_y_reflectself_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Reflects a point in the plane across the y axis.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DFloat_Y_ReflectSelf                                            *
 *  Purpose:                                                                  *
 *      Computes the reflection of a vector across the y axis.                *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorFloat * const):                                      *
 *          A point in the Euclidean plane. The reflection is stored here.    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The reflection of P across the y axis can be computed by negating the *
 *      x component and leaving the y coordinate alone. That is, if           *
 *      P = (a, b), the reflection is given by setting:                       *
 *                                                                            *
 *          x = -a                                                            *
 *          y = b                                                             *
 *                                                                            *
 *      We negate the x coordinate of P and return.                           *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P is a valid *
 *          pointer to a 2D vector.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_float.h:                                                    *
 *          The tmpl_TwoVectorFloat typedef is provided here.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 4, 2025                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_Y_REFLECTSELF_FLOAT_H
#define TMPL_VEC2_Y_REFLECTSELF_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  Function for reflecting a point across the y axis.                        */
TMPL_INLINE_DECL
void tmpl_2DFloat_Y_ReflectSelf(tmpl_TwoVectorFloat * const P)
{
    /*  The reflection simply negates the x coordinate of P.                  */
    P->dat[0] = -P->dat[0];
}
/*  End of tmpl_2DFloat_Y_ReflectSelf.                                        */

#endif
/*  End of include guard.                                                     */
