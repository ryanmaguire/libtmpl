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
 *                        tmpl_vec3_negate_self_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for negating a vector at double precision.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_NegateSelf                                              *
 *  Purpose:                                                                  *
 *      Computes the negative of a vector in R^3.                             *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorDouble * const):                                   *
 *          A pointer to a vector in R^3. The negative is stored here.        *
 *  Output:                                                                   *
 *      None (void).                                                          *
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
 *  2.) tmpl_vec3_double.h:                                                   *
 *          The tmpl_ThreeVectorDouble typedef is provided here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_NEGATE_SELF_DOUBLE_H
#define TMPL_VEC3_NEGATE_SELF_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_double.h>

/*  Function for negating a three dimensional vector.                         */
TMPL_INLINE_DECL
void tmpl_3DDouble_NegateSelf(tmpl_ThreeVectorDouble * const P)
{
    /*  The negative of a vector negates all of the components.               */
    P->dat[0] = -P->dat[0];
    P->dat[1] = -P->dat[1];
    P->dat[2] = -P->dat[2];
}
/*  End of tmpl_3DDouble_NegateSelf.                                          */

#endif
/*  End of include guard.                                                     */
