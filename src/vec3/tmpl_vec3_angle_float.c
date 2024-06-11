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
 *                           tmpl_vec3_angle_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing unit normal vectors.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Angle                                                    *
 *  Purpose:                                                                  *
 *      Computes the angle two vectors in R^3 make.                           *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A vector in R^3.                                                  *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          Another vector in R^3.                                            *
 *  Output:                                                                   *
 *      angle (float):                                                        *
 *          The angle P and Q make.                                           *
 *  Method:                                                                   *
 *      The standard method of:                                               *
 *                                                                            *
 *                          P . Q                                             *
 *          angle = acos -----------                                          *
 *                       ||P|| ||Q||                                          *
 *                                                                            *
 *      Is unstable and yields poor results when the angle is small. The      *
 *      altenative definition:                                                *
 *                                                                            *
 *                        ||P x Q||                                           *
 *          angle = asin -----------                                          *
 *                       ||P|| ||Q||                                          *
 *                                                                            *
 *      Is similarly unstable, and results in poor error when the angle is    *
 *      close to perpendicular. A third definition is used that is stable:    *
 *                                                                            *
 *          angle = atan2(||PxQ||, P.Q)                                       *
 *                                                                            *
 *      This is stable, but also has the added bonus of being slightly faster *
 *      than either of the two previous methods. Performance tests showed     *
 *      this to be 20-50% faster, depending on compiler and hardware.         *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *      2.) No checks for NULL pointers are performed.                        *
 *      3.) If either vector is zero, the behavior of the output is identical *
 *          to how the atan2 function works for zero-valued inputs.           *
 *      4.) To avoid possible overflows with the intermediate steps, we first *
 *          normalize P and Q to unit length. This is likely an unnecessary   *
 *          step that simply slows down the computation. If speed if          *
 *          critical, and if you are not working with vectors that have       *
 *          massive components, use tmpl_3DFloat_Quick_Angle.                 *
 *  References:                                                               *
 *      Kahan, William                                                        *
 *      How Futile are Mindless Assessments of Roundoff                       *
 *      in Floating-Point Computation?                                        *
 *      https://people.eecs.berkeley.edu/~wkahan/Mindless.pdf                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Provides the atan2 function.                                      *
 *  2.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 10, 2024                                                 *
 ******************************************************************************/

/*  atan2 function provided here.                                             */
#include <libtmpl/include/tmpl_math.h>

/*  Three-vector typedef and function prototype given here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the angle between two vectors.                     */
float
tmpl_3DFloat_Angle(const tmpl_ThreeVectorFloat * const P,
                   const tmpl_ThreeVectorFloat * const Q)
{
    /*  To avoid overflows, or undeflows, normalize the inputs.               */
    const tmpl_ThreeVectorFloat Pn = tmpl_3DFloat_Normalize(P);
    const tmpl_ThreeVectorFloat Qn = tmpl_3DFloat_Normalize(Q);

    /*  From vector geometry, ||PxQ|| = ||P|| ||Q|| sin(theta). Computing     *
     *  the norm of ||PxQ|| gives us a formula for the angle.                 */
    const tmpl_ThreeVectorFloat cross = tmpl_3DFloat_Cross_Product(&Pn, &Qn);
    const float norm_cross = tmpl_3DFloat_L2_Norm(&cross);

    /*  Also from vector geometry, ||P.Q|| = ||P|| ||Q|| cos(theta). By       *
     *  keeping track of the sign, we can get "oriented" angles.              */
    const float dot = tmpl_3DFloat_Dot_Product(&Pn, &Qn);

    /*  tan(theta) is the ratio of ||PxQ|| and P.Q. The angle can be computed *
     *  using the arctan2 function in the plane.                              */
    return tmpl_Float_Arctan2(norm_cross, dot);
}
/*  End of tmpl_3DFloat_Angle.                                                */
