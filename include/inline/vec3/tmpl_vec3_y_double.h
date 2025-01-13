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
 *                             tmpl_vec3_y_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Projection onto the y axis.                                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Y                                                       *
 *  Purpose:                                                                  *
 *      Projects a vector onto the y axis.                                    *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorDouble * const):                             *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      y (double):                                                           *
 *          The y component of P.                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Return the first entry of the data array.                             *
 *  Notes:                                                                    *
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
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/06/06: Ryan Maguire                                                  *
 *      Inlined the function.                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_Y_DOUBLE_H
#define TMPL_VEC3_Y_DOUBLE_H

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_double.h>

/*  Function for returning the y component of a three dimensional vector.     */
TMPL_INLINE_DECL
double tmpl_3DDouble_Y(const tmpl_ThreeVectorDouble * const P)
{
    /*  The first coordinate of the dat array is the y-component.             */
    return P->dat[1];
}
/*  End of tmpl_3DDouble_Y.                                                   */

#endif
/*  End of include guard.                                                     */
