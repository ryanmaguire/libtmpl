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
 *                         tmpl_vec3_scale_by_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs scalar multiplication at long double precision.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_ScaleBy                                                *
 *  Purpose:                                                                  *
 *      Computes scalar multiplication at long double precision.              *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorLongDouble * const):                          *
 *          A pointer to a vector in R^3. The product is stored here.         *
 *      a (long double):                                                      *
 *          A real number, the scalar multiplier.                             *
 *  Output:                                                                   *
 *      None (void).                                                          *
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
 *  2.) tmpl_vec3_ldouble.h:                                                  *
 *          The tmpl_ThreeVectorLongDouble typedef is provided here.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 11, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_SCALE_BY_LDOUBLE_H
#define TMPL_VEC3_SCALE_BY_LDOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_ldouble.h>

/*  Multiply a three vector by a real number.                                 */
TMPL_INLINE_DECL
void
tmpl_3DLDouble_ScaleBy(tmpl_ThreeVectorLongDouble * const target, long double a)
{
    /*  Scalar multiplication is done component-wise, so compute this.        */
    target->dat[0] *= a;
    target->dat[1] *= a;
    target->dat[2] *= a;
}
/*  End of tmpl_3DLDouble_ScaleBy.                                            */

#endif
/*  End of include guard.                                                     */
