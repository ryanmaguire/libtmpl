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
 *                         tmpl_vec3_orthogonal_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a vector orthogonal to the input.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Orthogonal                                               *
 *  Purpose:                                                                  *
 *      Computes a vector orthogonal to the input and with the same norm.     *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A vector in R^3.                                                  *
 *  Output:                                                                   *
 *      orth (tmpl_ThreeVectorFloat):                                         *
 *          A vector orthogonal to P and of the same magnitude.               *
 *  Method:                                                                   *
 *      A corollary of the hairy ball theorem from topology is that there is  *
 *      no continuous function f:R^3 -> R^3 such that for all P the vectors   *
 *      f(P) and P are orthogonal, and such that P and f(P) have the same     *
 *      magnitude. The proof is quite simple. Suppose f:R^3 -> R^3 is such a  *
 *      function. Restricting f to the unit sphere gives us a vector field on *
 *      the sphere that is tangential at each point. But the hairy ball       *
 *      theorem says no such vector field can exist.                          *
 *                                                                            *
 *      We reduce this difficulty by placing the discontinuity along a single *
 *      line through the origin. That is, we can indeed choose a function     *
 *      f:R^3 -> R^3 such that P and f(P) are orthogonal and of the same      *
 *      magnitude, such that f is continuous at every point P that does not   *
 *      fall on the line z = x, y = -x. The function is given by:             *
 *                                                                            *
 *                           (y + z, z - x, -x - y)                           *
 *          f((x, y, z)) = -------------------------- ||(x, y, z)||           *
 *                         ||(y + z, z - x, -x - y)||                         *
 *                                                                            *
 *      This formula is undefined on the line z = x, y = -x. For these points *
 *      we write:                                                             *
 *                                                                            *
 *          f((x, -x, x)) = (sqrt(3/2) * x, sqrt(3/2) * x, 0)                 *
 *                                                                            *
 *      The sqrt(3/2) factor is used to ensure the input and output have the  *
 *      same length.                                                          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Hypot3:                                                *
 *              Computes the norm of (x, y, z).                               *
 *      tmpl_vec3.h:                                                          *
 *          tmpl_3DFloat_L2_Norm:                                             *
 *              Computes the Euclidean norm of a vector.                      *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *      2.) No checks for NULL pointers are performed.                        *
 *      3.) This function is not continuous. No such continuous function      *
 *          exists. All of the discontinuities fall on the line z = x, y = -x.*
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Provides the hypot3 function.                                     *
 *  2.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/06/12: Ryan Maguire                                                  *
 *      Simplified function dramatically. Isolated discontinuities to a       *
 *      single line through the origin. Added license and comments.           *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>
#include <libtmpl/include/tmpl_math.h>

/*  Scale factor used for points on the line z = x, y = -x.                   */
#define TMPL_SQRT_3_BY_2 (+1.224744871391589049098642037352945695983E+00F)

/*  Function for computing an orthogonal vector to the given input.           */
tmpl_ThreeVectorFloat
tmpl_3DFloat_Orthogonal(const tmpl_ThreeVectorFloat * const P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorFloat out;

    /*  (y + z, z - x, -x - y) is always orthogonal to (x, y, z), but it may  *
     *  be the zero vector. We'll check for this.                             */
    const float a = P->dat[1] + P->dat[2];
    const float b = P->dat[2] - P->dat[0];
    const float c = -P->dat[0] - P->dat[1];
    const float norm = tmpl_Float_Hypot3(a, b, c);

    /*  If P lies on the line z = x, y = -x, then this output vector is zero. */
    if (norm == 0.0F)
    {
        /*  For points (x, -x, x), the vector (x, x, 0) is orthogonal.        */
        out.dat[0] = P->dat[0] * TMPL_SQRT_3_BY_2;
        out.dat[1] = out.dat[0];
        out.dat[2] = 0.0F;
    }

    /*  For all over points not lying on the line z = x, y = -x.              */
    else
    {
        /*  Normalize so that the output and input have the same norm.        */
        const float factor = tmpl_3DFloat_L2_Norm(P) / norm;
        out.dat[0] = factor * a;
        out.dat[1] = factor * b;
        out.dat[2] = factor * c;
    }

    return out;
}
/*  End of tmpl_3DFloat_Orthogonal.                                           */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_SQRT_3_BY_2
