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
 *                         tmpl_vec3_linf_norm_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the supremum norm at double precision.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_LInf_Norm                                               *
 *  Purpose:                                                                  *
 *      Computes the supremum norm (L-infinity norm) of the input.            *
 *  Arguments:                                                                *
 *      p (const tmpl_ThreeVectorDouble * const):                             *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm (double):                                                        *
 *          The supremum norm of P.                                           *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Abs:                                                  *
 *              Computes the absolute value of a real number.                 *
 *  Method:                                                                   *
 *      Compute the max of the absolute values of the components.             *
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
 *  4.) tmpl_max.h:                                                           *
 *          Provides a helper macro for computing the max of 3 real numbers.  *
 *  5.) tmpl_math.h:                                                          *
 *          Location of the absolute value function.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 5, 2022                                               *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2024/06/11: Ryan Maguire                                                  *
 *      Inlined the routine.                                                  *
 *  2026/07/24: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes.          *
 ******************************************************************************/

/*  The TMPL_ALWAYS_INLINE macro is provided here.                            */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Three-vector typedef and function prototype found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  TMPL_MAX3 helper macro found here.                                        */
#include <libtmpl/include/helper/tmpl_max.h>

/*  Absolute value function found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the L-Infinity norm of a 3D vector.                */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
double tmpl_3DDouble_LInf_Norm(const tmpl_ThreeVectorDouble * const p)
TMPL_UNSEQUENCED
{
    const double abs_x = tmpl_Double_Abs(p->dat[0]);
    const double abs_y = tmpl_Double_Abs(p->dat[1]);
    const double abs_z = tmpl_Double_Abs(p->dat[2]);
    return TMPL_MAX3(abs_x, abs_y, abs_z);
}
/*  End of tmpl_3DDouble_LInf_Norm.                                           */
