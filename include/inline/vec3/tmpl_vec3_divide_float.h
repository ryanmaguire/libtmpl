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
 *                           tmpl_vec3_divide_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing the Hadamard quotient.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Divide                                                   *
 *  Purpose:                                                                  *
 *      Computes the Hadamard quotient of two vectors at single precision.    *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      quot (tmpl_ThreeVectorFloat):                                         *
 *          The Hadamard quotient of P and Q.                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of Hadamard quotient. If P = (Px, Py, Pz) and      *
 *      Q = (Qx, Qy, Qz), then the quotient has coordinates:                  *
 *          x = Px / Qx                                                       *
 *          y = Py / Qy                                                       *
 *          z = Pz / Qz                                                       *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_float.h:                                                    *
 *          The tmpl_ThreeVectorFloat typedef is provided here.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 13, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_DIVIDE_FLOAT_H
#define TMPL_VEC3_DIVIDE_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_float.h>

/*  Function for performing the Hadamard quotient in R^3.                     */
TMPL_INLINE_DECL
tmpl_ThreeVectorFloat
tmpl_3DFloat_Divide(const tmpl_ThreeVectorFloat * const P,
                    const tmpl_ThreeVectorFloat * const Q)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorFloat quot;

    /*  The Hadamard quotient divides the components.                         */
    quot.dat[0] = P->dat[0] / Q->dat[0];
    quot.dat[1] = P->dat[1] / Q->dat[1];
    quot.dat[2] = P->dat[2] / Q->dat[2];
    return quot;
}
/*  End of tmpl_3DFloat_Divide.                                               */

#endif
/*  End of include guard.                                                     */
