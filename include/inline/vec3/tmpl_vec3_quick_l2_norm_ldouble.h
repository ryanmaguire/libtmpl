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
 *                      tmpl_vec3_quick_l2_norm_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Euclidean norm at long double precision.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Quick_L2_Norm                                          *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm, also called the L2 norm, of the input.   *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm (long double):                                                   *
 *          The Euclidean norm of P.                                          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_Quick_Hypot3:                                        *
 *              Computes the magnitude of (x, y, z).                          *
 *  Method:                                                                   *
 *      Pass the components to the Hypot3 function.                           *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *      2.) No checks for Null pointers are performed.                        *
 *      3.) Unlike tmpl_3DLDouble_L2_Norm, this function does not prevent     *
 *          overflow or underflow.                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_ldouble.h:                                                  *
 *          Header containing ThreeVector typedef.                            *
 *  3.) tmpl_math.h:                                                          *
 *          Header file providing the Hypot3 function.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 11, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_QUICK_L2_NORM_LDOUBLE_H
#define TMPL_VEC3_QUICK_L2_NORM_LDOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef given here.                                          */
#include <libtmpl/include/tmpl_vec3_ldouble.h>

/*  quick-hypot3 provided here.                                               */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the Euclidean norm of a vector.                    */
TMPL_INLINE_DECL
long double
tmpl_3DLDouble_Quick_L2_Norm(const tmpl_ThreeVectorLongDouble * const P)
{
    /*  The hypot3 function computes using the Pythagoras formula. Use this.  */
    return tmpl_LDouble_Quick_Hypot3(P->dat[0], P->dat[1], P->dat[2]);
}
/*  End of tmpl_3DLDouble_Quick_L2_Norm.                                      */

#endif
/*  End of include guard.                                                     */
