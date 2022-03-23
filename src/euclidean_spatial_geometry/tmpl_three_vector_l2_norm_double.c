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
 *                        tmpl_three_vector_norm_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Euclidean norm at double precision.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Norm                                                    *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm, also called the L2 norm, of the input.   *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorDouble):                                           *
 *          A vector in R^3.                                                  *
 *  Output:                                                                   *
 *      norm (double):                                                        *
 *          The Euclidean norm of P.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The Euclidean norm, also called the L2 norm of a vector P = (x, y, z) *
 *      is defined as:                                                        *
 *                                                                            *
 *          ||P|| = sqrt(x^2 + y^2 + z^2)                                     *
 *                                                                            *
 *      The computation of x^2, y^2, and z^2 may result in an overflow        *
 *      yielding an answer of infinity even if the norm is less than DBL_MAX. *
 *      To avoid this, compute the max of |x|, |y|, and |z|. Suppose |x| is   *
 *      the max, we then set:                                                 *
 *                                                                            *
 *          t = |x|                                                           *
 *          u = |y| / |x|                                                     *
 *          v = |z| / |x|                                                     *
 *                                                                            *
 *      The norm is then computed as:                                         *
 *                                                                            *
 *          ||P|| = t * sqrt(1 + u^2 + v^2)                                   *
 *                                                                            *
 *      If |y| / |x| or |z| / |x| results in an underflow the value is still  *
 *      accurate to double precision. The variables are checked to see if all *
 *      are zero to avoid division by zero.                                   *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      The macro tmpl_3D_Dot_Product is an alias for this function.          *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_euclidean_spatial_geometry.h:                                    *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/03/03: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 *      Changed routine to be safer, ensuring overflow does not occur in any  *
 *      intermediate steps.                                                   *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Square root function found here.                                          */
#include <libtmpl/include/tmpl_math.h>

/*  Some implementations may inline the square root function from math.h.     *
 *  This can double the efficiency of this routine. If the macro              *
 *  TMPL_USE_MATH_ALGORITHMS is not set to 1, use sqrt from math.h instead.   */
#if TMPL_USE_MATH_ALGORITHMS != 1
#include <math.h>
#endif

/*  Function for computing the length of three dimensional vectors.           */
double tmpl_3DDouble_L2_Norm(const tmpl_ThreeVectorDouble *P)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double x, y, z, t, rcpr_t;

#if TMPL_USE_MATH_ALGORITHMS != 1
    x = fabs(P->dat[0]);
    y = fabs(P->dat[1]);
    z = fabs(P->dat[2]);
#else
    x = tmpl_Double_Abs(P->dat[0]);
    y = tmpl_Double_Abs(P->dat[1]);
    z = tmpl_Double_Abs(P->dat[2]);
#endif

    t = (x < y ? (y < z ? z : y) : (x < z ? z : x));
    rcpr_t = 1.0 / t;
    x *= rcpr_t;
    y *= rcpr_t;
    z *= rcpr_t;

    /*  Use the Pythagorean formula to compute the norm and return.           */
#if TMPL_USE_MATH_ALGORITHMS != 1
    return t*sqrt(x*x + y*y + z*z);
#else
    return t*tmpl_Double_Sqrt(x*x + y*y + z*z);
#endif
}
/*  End of tmpl_3DDouble_L2_Norm.                                             */
