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
 *                      tmpl_vec3_l2_norm_squared_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the square of the Euclidean norm.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_L2_Norm_Squared                                         *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean norm.                            *
 *  Arguments:                                                                *
 *      p (const tmpl_ThreeVectorDouble * const):                             *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm_squared (double):                                                *
 *          The square of the Euclidean norm of p.                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the sum of the squares and return.                            *
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
 *  3.) tmpl_vec3.h:                                                          *
 *          tmpl_ThreeVectorDouble and function prototype provided here.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/07/17: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes.          *
 ******************************************************************************/

/*  The TMPL_ALWAYS_INLINE macro is provided here.                            */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Three-vector typedef and function prototype provided here.                */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the square of the Euclidean norm.                  */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
double tmpl_3DDouble_L2_Norm_Squared(const tmpl_ThreeVectorDouble * const p)
TMPL_UNSEQUENCED
{
    return p->dat[0] * p->dat[0] +
           p->dat[1] * p->dat[1] +
           p->dat[2] * p->dat[2];
}
/*  End of tmpl_3DDouble_L2_Norm_Squared.                                     */
