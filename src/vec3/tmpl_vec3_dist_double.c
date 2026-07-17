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
 *                            tmpl_vec3_dist_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Euclidean distance between two points in R^3.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Dist                                                    *
 *  Purpose:                                                                  *
 *      Computes the distance between two points in space.                    *
 *  Arguments:                                                                *
 *      p (const tmpl_ThreeVectorDouble * const):                             *
 *          A pointer to a vector in R^3.                                     *
 *      q (const tmpl_ThreeVectorDouble * const):                             *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      dist (double):                                                        *
 *          The distance between p and q.                                     *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Hypot3:                                               *
 *              Computes the magnitude of (x, y, z).                          *
 *  Method:                                                                   *
 *      Compute the L2 norm of p - q and return.                              *
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
 *          Header file providing the Hypot3 function.                        *
 *  4.) tmpl_vec3.h:                                                          *
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

/*  Hypot3 function found here.                                               */
#include <libtmpl/include/tmpl_math.h>

/*  Three-vector typedef and function prototype found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Computes the Euclidean distance between two points.                       */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_3DDouble_Dist(const tmpl_ThreeVectorDouble * const p,
                   const tmpl_ThreeVectorDouble * const q)
TMPL_UNSEQUENCED
{
    /*  Compute the components of p - q.                                      */
    const double dx = p->dat[0] - q->dat[0];
    const double dy = p->dat[1] - q->dat[1];
    const double dz = p->dat[2] - q->dat[2];

    /*  The Euclidean distance is the norm of p - q. Return this.             */
    return tmpl_Double_Hypot3(dx, dy, dz);
}
/*  End of tmpl_3DDouble_Dist.                                                */
