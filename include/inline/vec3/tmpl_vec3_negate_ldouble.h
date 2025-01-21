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
 *                          tmpl_vec3_negate_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for negating a vector at long double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Negate                                                 *
 *  Purpose:                                                                  *
 *      Computes the negative of a vector in R^3.                             *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      minus_P (tmpl_ThreeVectorLongDouble):                                 *
 *          The additive inverse of P.                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of vector negation. If P = (Px, Py, Pz),           *
 *      then the additive inverse of P has coordinates:                       *
 *          x = -Px                                                           *
 *          y = -Py                                                           *
 *          z = -Pz                                                           *
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
#ifndef TMPL_VEC3_NEGATE_LDOUBLE_H
#define TMPL_VEC3_NEGATE_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  Function for negating a three dimensional vector.                         */
TMPL_INLINE_DECL
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Negate(const tmpl_ThreeVectorLongDouble * const P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorLongDouble minus_P;

    /*  The negative of a vector negates all of the components.               */
    minus_P.dat[0] = -P->dat[0];
    minus_P.dat[1] = -P->dat[1];
    minus_P.dat[2] = -P->dat[2];
    return minus_P;
}
/*  End of tmpl_3DLDouble_Negate.                                             */

#endif
/*  End of include guard.                                                     */
