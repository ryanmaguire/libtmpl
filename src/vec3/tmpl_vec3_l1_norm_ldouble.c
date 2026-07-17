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
 *      p (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm (long double):                                                   *
 *          The Manhattan norm of p.                                          *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Abs:                                                 *
 *              Computes the absolute value of a real number.                 *
 *  Method:                                                                   *
 *      Sum the absolute values of the components.                            *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *                                                                            *
 *      2.) No checks for Null pointers are performed.                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_ALWAYS_INLINE macro.                         *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides C23 attributes for optimization.                         *
 *  3.) tmpl_math.h:                                                          *
 *          Header file providing the absolute value function.                *
 *  4.) tmpl_vec3.h:                                                          *
 *          tmpl_ThreeVectorLongDouble and function prototype provided here.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 5, 2022                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/06/11: Ryan Maguire                                                  *
 *      Inlined the routine.                                                  *
 *  2026/07/17: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes.          *
 ******************************************************************************/

/*  The TMPL_ALWAYS_INLINE macro is provided here.                            */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Absolute value function given here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Three-vector typedef and function prototype provided here.                */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the L1 norm of a vector at long double precision.  */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
long double tmpl_3DLDouble_L1_Norm(const tmpl_ThreeVectorLongDouble * const p)
TMPL_UNSEQUENCED
{
    return tmpl_LDouble_Abs(p->dat[0]) +
           tmpl_LDouble_Abs(p->dat[1]) +
           tmpl_LDouble_Abs(p->dat[2]);
}
/*  End of tmpl_3DLDouble_L1_Norm.                                            */
