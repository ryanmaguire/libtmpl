/******************************************************************************
 *                                 LICENSE                                    *
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
 *                        tmpl_vec3_quick_angle_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing angles at double precision.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Quick_Angle                                             *
 *  Purpose:                                                                  *
 *      Computes the angle two vectors in R^3 make.                           *
 *  Arguments:                                                                *
 *      p (const tmpl_ThreeVectorDouble * const):                             *
 *          A vector in R^3.                                                  *
 *      q (const tmpl_ThreeVectorDouble * const):                             *
 *          Another vector in R^3.                                            *
 *  Output:                                                                   *
 *      angle (double):                                                       *
 *          The angle p and q make.                                           *
 *  Method:                                                                   *
 *      The standard method of                                                *
 *                                                                            *
 *                        -               -                                   *
 *                       |      p . q      |                                  *
 *          angle = acos | --------------- |                                  *
 *                       | || p || || q || |                                  *
 *                        -               -                                   *
 *                                                                            *
 *      is unstable and yields poor results when the angle is small. The      *
 *      alternative definition                                                *
 *                                                                            *
 *                        -               -                                   *
 *                       |   || p x q ||   |                                  *
 *          angle = asin | --------------- |                                  *
 *                       | || p || || q || |                                  *
 *                        -               -                                   *
 *                                                                            *
 *      is similarly unstable, and results in poor error when the angle       *
 *      is close to perpendicular. A third definition is used that is         *
 *      stable, accurate for small angles and near perpendicular ones:        *
 *                                                                            *
 *          angle = atan2(|| p x q ||, p . q)                                 *
 *                                                                            *
 *      This is stable, but also has the added bonus of being faster          *
 *      than either of the two previous methods. Performance tests have       *
 *      shown this to be 20-50% faster, depending on compiler / hardware.     *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *                                                                            *
 *      2.) No checks for NULL pointers are performed.                        *
 *                                                                            *
 *      3.) There are no checks for zero vectors. Such inputs are handled     *
 *          the same way the atan2 function handles zero.                     *
 *                                                                            *
 *      4.) This method does not handle overflows or underflows properly. If  *
 *          the vectors you are working with have massive components, use     *
 *          tmpl_3DDouble_Angle instead. That function safely handles such    *
 *          cases, but is slower.                                             *
 *  References:                                                               *
 *      1.) Kahan, William                                                    *
 *          How Futile are Mindless Assessments of Roundoff                   *
 *          in Floating-Point Computation?                                    *
 *          https://people.eecs.berkeley.edu/~wkahan/Mindless.pdf             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Provides the atan2 function.                                      *
 *  2.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 11, 2024                                                 *
 ******************************************************************************/

/*  atan2 function provided here.                                             */
#include <libtmpl/include/tmpl_math.h>

/*  Three-vector typedef and function prototype given here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the angle between two vectors.                     */
double
tmpl_3DDouble_Quick_Angle(const tmpl_ThreeVectorDouble * const p,
                          const tmpl_ThreeVectorDouble * const q)
{
    /*  From vector geometry, || p x q || = || p || || q || sin(theta).       *
     *  Computing the norm of || p x q || gives us a formula for the angle.   */
    const tmpl_ThreeVectorDouble cross = tmpl_3DDouble_Cross_Product(p, q);
    const double norm_cross = tmpl_3DDouble_Quick_L2_Norm(&cross);

    /*  Also from vector geometry, || p . q || = || p || || q || cos(theta).  *
     *  By keeping track of the sign, we can get "oriented" angles.           */
    const double dot = tmpl_3DDouble_Dot_Product(p, q);

    /*  tan(theta) is the ratio of || p x q || and p . q. The angle can be    *
     *  computed using the atan2 function in the plane.                       */
    return tmpl_Double_Arctan2(norm_cross, dot);
}
/*  End of tmpl_3DDouble_Quick_Angle.                                         */
