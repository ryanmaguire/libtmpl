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
 *                         tmpl_vec3_l2_norm_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Euclidean norm at long double precision.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_L2_Norm                                                *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm, also called the L2 norm, of the input.   *
 *  Arguments:                                                                *
 *      p (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm (long double):                                                   *
 *          The Euclidean norm of p.                                          *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Hypot3:                                              *
 *              Computes the magnitude of (x, y, z).                          *
 *  Method:                                                                   *
 *      Pass the components to the Hypot3 function.                           *
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
 *          Header file providing the hypot3 function.                        *
 *  4.) tmpl_vec3.h:                                                          *
 *          tmpl_ThreeVectorLongDouble and function prototype provided here.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/03: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 *      Changed routine to be safer, ensuring overflow does not occur in any  *
 *      intermediate steps.                                                   *
 *  2024/06/10: Ryan Maguire                                                  *
 *      Migrated the bulk of the code to src/math into the Hypot3 function.   *
 *      Inlined the routine.                                                  *
 *  2026/07/17: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes.          *
 ******************************************************************************/

/*  The TMPL_ALWAYS_INLINE macro is provided here.                            */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Hypot3 function given here.                                               */
#include <libtmpl/include/tmpl_math.h>

/*  Three-vector typedef and function prototype provided here.                */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the L2 norm of a vector at long double precision.  */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
long double tmpl_3DLDouble_L2_Norm(const tmpl_ThreeVectorLongDouble * const p)
TMPL_UNSEQUENCED
{
    return tmpl_LDouble_Hypot3(p->dat[0], p->dat[1], p->dat[2]);
}
/*  End of tmpl_3DLDouble_L2_Norm.                                            */
