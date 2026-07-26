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
 *                         tmpl_vec3_midpoint_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the midpoint of two points in R^3.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Midpoint                                               *
 *  Purpose:                                                                  *
 *      Computes the midpoint of two points in R^3.                           *
 *  Arguments:                                                                *
 *      p (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *      q (const tmpl_ThreeVectorLongDouble * const):                         *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      midpoint (tmpl_ThreeVectorLongDouble):                                *
 *          The midpoint of p and q.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of midpoints. If p = (px, py, pz) and              *
 *      q = (qx, qy, qz), then the midpoint has coordinates:                  *
 *                                                                            *
 *          x = (px + qx) / 2                                                 *
 *          y = (py + qy) / 2                                                 *
 *          z = (pz + qz) / 2                                                 *
 *                                                                            *
 *      These values are stored in a new 3D vector and returned.              *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *                                                                            *
 *      2.) No checks for Null pointers are performed.                        *
 *                                                                            *
 *      3.) The expression (a + b) / 2 will overflow if a and b are large,    *
 *          even if the average is a representable value. There is a safer    *
 *          method, min(a, b) + (max(a, b) - min(a, b)) / 2, but this         *
 *          requires additional operations (min, max, subtract), and will     *
 *          still overflow if a and b are large and have opposite signs.      *
 *          For the sake of speed this function uses the standard method.     *
 *                                                                            *
 *      4.) For normal long double floating-point numbers, division by        *
 *          two is a lossless operation. The midpoint formula hence only      *
 *          produces a single round, not two.                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_ALWAYS_INLINE macro.                         *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides C23 attributes for optimization.                         *
 *  3.) tmpl_vec3.h:                                                          *
 *          tmpl_ThreeVectorLongDouble and function prototype provided here.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/07/25: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes.          *
 ******************************************************************************/

/*  The TMPL_ALWAYS_INLINE macro is provided here.                            */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Three-vector typedef and function prototype found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the midpoint of two points.                        */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Midpoint(const tmpl_ThreeVectorLongDouble * const p,
                        const tmpl_ThreeVectorLongDouble * const q)
TMPL_UNSEQUENCED
{
    /*  Declare a variable for the midpoint of p and q.                       */
    tmpl_ThreeVectorLongDouble midpoint;

    /*  Use the midpoint formula and return.                                  */
    midpoint.dat[0] = (p->dat[0] + q->dat[0]) * 0.5L;
    midpoint.dat[1] = (p->dat[1] + q->dat[1]) * 0.5L;
    midpoint.dat[2] = (p->dat[2] + q->dat[2]) * 0.5L;

    return midpoint;
}
/*  End of tmpl_3DLDouble_Midpoint.                                           */
