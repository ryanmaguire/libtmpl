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
 *                           tmpl_vec3_angle_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing angles at double precision.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Angle                                                   *
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
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Arctan2:                                              *
 *              Computes the angle the point (x, y) makes in the plane with   *
 *              the positive x axis.                                          *
 *      src/vec3/                                                             *
 *          tmpl_3DDouble_Cross_Product:                                      *
 *              Computes the cross product of two vectors.                    *
 *          tmpl_3DDouble_Dot_Product:                                        *
 *              Computes the Euclidean dot product of two vectors.            *
 *          tmpl_3DDouble_L2_Norm:                                            *
 *              Computes the Euclidean length of a vector.                    *
 *          tmpl_3DDouble_Normalize:                                          *
 *              Normalizes a vector to unit magnitude.                        *
 *  Method:                                                                   *
 *      The standard method of                                                *
 *                                                                            *
 *                        -           -                                       *
 *                       |    p . q    |                                      *
 *          angle = acos | ----------- |                                      *
 *                       | ||p|| ||q|| |                                      *
 *                        -           -                                       *
 *                                                                            *
 *      is unstable and yields poor results when the angle is small. The      *
 *      alternative definition                                                *
 *                                                                            *
 *                        -           -                                       *
 *                       |  ||p x q||  |                                      *
 *          angle = asin | ----------- |                                      *
 *                       | ||p|| ||q|| |                                      *
 *                        -           -                                       *
 *                                                                            *
 *      is similarly unstable, and results in poor error when the angle is    *
 *      close to perpendicular. A third definition is used that is stable:    *
 *                                                                            *
 *          angle = atan2(||p x q||, p . q)                                   *
 *                                                                            *
 *      This is stable, but also has the added bonus of being slightly faster *
 *      than either of the two previous methods. Performance tests showed     *
 *      this to be 20-50% faster, depending on compiler and hardware.         *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *                                                                            *
 *      2.) No checks for NULL pointers are performed.                        *
 *                                                                            *
 *      3.) If either vector is zero, the behavior of the output is identical *
 *          to how the atan2 function works for zero-valued inputs.           *
 *                                                                            *
 *      4.) To avoid possible overflows with the intermediate steps, we first *
 *          normalize p and q to unit length. This is likely an unnecessary   *
 *          step that simply slows down the computation. If speed if          *
 *          critical, and if you are not working with vectors that have       *
 *          massive components, use tmpl_3DDouble_Quick_Angle.                *
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
 *  Date:       June 10, 2024                                                 *
 ******************************************************************************/

/*  atan2 function provided here.                                             */
#include <libtmpl/include/tmpl_math.h>

/*  Three-vector typedef and function prototype given here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  The TMPL_HAS_IEEE754_DOUBLE macro is found here.                          */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  With IEEE-754 support we can determine if || p || or || q || are too      *
 *  small or too big by examining the exponents of their components. This is  *
 *  significantly faster than normalizing using square roots.                 */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Scale factor is 2^512 for small values and 2^-512 for large ones.         */
#define TMPL_2_POW_512 (+1.34078079299425970995740249982058461274793658206E+154)

/*  Function for computing the angle between two vectors.                     */
double
tmpl_3DDouble_Angle(const tmpl_ThreeVectorDouble * const p,
                    const tmpl_ThreeVectorDouble * const q)
{
    /*  Variables for p x q, || p x q ||, and p . q, computed after scaling.  */
    tmpl_ThreeVectorDouble cross;
    double dot, norm_cross;

    /*  To avoid overflows and undeflows we scale the inputs. Make a copy.    */
    tmpl_ThreeVectorDouble pn = *p;
    tmpl_ThreeVectorDouble qn = *q;

    /*  We only scale if || p || or || q || is very small or very large. To   *
     *  avoid a square root call, we check if either of these are large by    *
     *  examining the exponents of the components.                            */
    const unsigned int p_max_exp = TMPL_VEC3_DOUBLE_MAX_EXP(pn);
    const unsigned int q_max_exp = TMPL_VEC3_DOUBLE_MAX_EXP(qn);

    /*  If || p || > 2^504, scale the components by 2^-512. This guarantees   *
     *  the the scaled result will not produce overflows in the intermediate  *
     *  calculations (cross product, dot product).                            */
    if (p_max_exp > TMPL_DOUBLE_UBIAS + 0x1F8U)
        tmpl_3DDouble_ScaleBy(&pn, 1 / TMPL_2_POW_512);

    /*  Similarly, if || p || < 2^-504, scale by 2^512. This prevent          *
     *  underflow from occuring in the intermediate steps.                    */
    else if (p_max_exp < TMPL_DOUBLE_UBIAS - 0x1F8U)
        tmpl_3DDouble_ScaleBy(&pn, TMPL_2_POW_512);

    /*  Same check for || q ||.                                               */
    if (q_max_exp > TMPL_DOUBLE_UBIAS + 0x1F8U)
        tmpl_3DDouble_ScaleBy(&qn, 1 / TMPL_2_POW_512);
    else if (q_max_exp < TMPL_DOUBLE_UBIAS - 0x1F8U)
        tmpl_3DDouble_ScaleBy(&qn, TMPL_2_POW_512);

    /*  From vector geometry, ||p x q|| = ||p|| ||q|| sin(theta). Computing   *
     *  the norm of ||p x q|| gives us a formula for the angle.               */
    cross = tmpl_3DDouble_Cross_Product(&pn, &qn);

    /*  p and q have been scaled to avoid underflow and overflow. The         *
     *  L2 norm function performs checks and normalizations to carefully      *
     *  handle large numbers. Since we are not working with such numbers,     *
     *  we may use the Quick L2 norm function.                                */
    norm_cross = tmpl_3DDouble_Quick_L2_Norm(&cross);

    /*  Also from vector geometry, ||p . q|| = ||p|| ||q|| cos(theta). By     *
     *  keeping track of the sign, we can get "oriented" angles.              */
    dot = tmpl_3DDouble_Dot_Product(&pn, &qn);

    /*  tan(theta) is the ratio of ||p x q|| and p . q. The angle can be      *
     *  computed using the atan2 function in the plane.                       */
    return tmpl_Double_Arctan2(norm_cross, dot);
}
/*  End of tmpl_3DDouble_Angle.                                               */

#else

/*  Function for computing the angle between two vectors.                     */
double
tmpl_3DDouble_Angle(const tmpl_ThreeVectorDouble * const p,
                    const tmpl_ThreeVectorDouble * const q)
{
    /*  To avoid overflows, or undeflows, normalize the inputs.               */
    const tmpl_ThreeVectorDouble pn = tmpl_3DDouble_Normalize(p);
    const tmpl_ThreeVectorDouble qn = tmpl_3DDouble_Normalize(q);

    /*  From vector geometry, ||p x q|| = ||p|| ||q|| sin(theta). Computing   *
     *  the norm of ||p x q|| gives us a formula for the angle.               */
    const tmpl_ThreeVectorDouble cross = tmpl_3DDouble_Cross_Product(&pn, &qn);
    const double norm_cross = tmpl_3DDouble_L2_Norm(&cross);

    /*  Also from vector geometry, ||p . q|| = ||p|| ||q|| cos(theta). By     *
     *  keeping track of the sign, we can get "oriented" angles.              */
    const double dot = tmpl_3DDouble_Dot_Product(&pn, &qn);

    /*  tan(theta) is the ratio of ||p x q|| and p . q. The angle can be      *
     *  computed using the atan2 function in the plane.                       */
    return tmpl_Double_Arctan2(norm_cross, dot);
}
/*  End of tmpl_3DDouble_Angle.                                               */

#endif
