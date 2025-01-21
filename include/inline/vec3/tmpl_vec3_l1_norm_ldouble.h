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
 *                         tmpl_vec3_l1_norm_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Manhattan norm at long double precision.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_L1_Norm                                                *
 *  Purpose:                                                                  *
 *      Computes the Manhattan norm, also called the L1 norm, of the input.   *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm (long double):                                                   *
 *          The Manhattan norm of P.                                          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_Abs:                                                 *
 *              Computes the absolute value of a real number.                 *
 *  Method:                                                                   *
 *      Sum the absolute values of the components.                            *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
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
 *  Date:       October 5, 2022                                               *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2024/06/11: Ryan Maguire                                                  *
 *      Inlined the routine.                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_L1_NORM_LDOUBLE_H
#define TMPL_VEC3_L1_NORM_LDOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  Absolute value function found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the L1 norm of a vector at long double precision.  */
TMPL_INLINE_DECL
long double tmpl_3DLDouble_L1_Norm(const tmpl_ThreeVectorLongDouble * const P)
{
    return tmpl_LDouble_Abs(P->dat[0]) +
           tmpl_LDouble_Abs(P->dat[1]) +
           tmpl_LDouble_Abs(P->dat[2]);
}
/*  End of tmpl_3DLDouble_L1_Norm.                                            */

#endif
/*  End of include guard.                                                     */
