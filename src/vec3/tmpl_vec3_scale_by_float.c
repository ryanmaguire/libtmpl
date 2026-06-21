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
 *                          tmpl_vec3_scale_by_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs scalar multiplication at single precision.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_ScaleBy                                                  *
 *  Purpose:                                                                  *
 *      Computes scalar multiplication at single precision.                   *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorFloat * const):                               *
 *          A pointer to a vector in R^3. The product is stored here.         *
 *      a (const float):                                                      *
 *          A real number, the scalar multiplier.                             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of scalar multiplication. If p = (px, py, pz),     *
 *      then a * p has coordinates:                                           *
 *                                                                            *
 *          x = a * px                                                        *
 *          y = a * py                                                        *
 *          z = a * pz                                                        *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *                                                                            *
 *      2.) No checks for Null pointers are performed.                        *
 *                                                                            *
 *      3.) This function acts as p *= operator for vectors. It is much       *
 *          faster to do tmpl_3DFloat_ScaleBy(&p, a) instead of               *
 *          p = tmpl_3DFloat_Scale(a, &p).                                    *
 *                                                                            *
 *      4.) Modern compilers with link-time optimization can inline this      *
 *          function across translation units.                                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_attributes.h:                                                    *
 *          Provides C23 attributes for optimization.                         *
 *  2.) tmpl_vec3.h:                                                          *
 *          tmpl_ThreeVectorFloat and function prototype provided here.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 11, 2024                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/06/21: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes.          *
 ******************************************************************************/

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Three-vector typedef and function prototype found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Multiply a three vector by a real number.                                 */
TMPL_PURE_FUNC
void
tmpl_3DFloat_ScaleBy(tmpl_ThreeVectorFloat * const target, const float a)
{
    /*  Scalar multiplication is done component-wise, compute this.           */
    target->dat[0] *= a;
    target->dat[1] *= a;
    target->dat[2] *= a;
}
/*  End of tmpl_3DFloat_ScaleBy.                                              */
