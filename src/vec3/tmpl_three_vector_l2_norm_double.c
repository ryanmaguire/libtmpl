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
 *                        tmpl_three_vector_norm_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Euclidean norm at double precision.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_L2_Norm                                                 *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm, also called the L2 norm, of the input.   *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorDouble *):                                   *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm (double):                                                        *
 *          The Euclidean norm of P.                                          *
 *  Called Functions:                                                         *
 *      tmpl_Double_Abs     (tmpl_math.h):                                    *
 *          Computes the absolute value of a double.                          *
 *      tmpl_Double_Sqrt    (tmpl_math.h):                                    *
 *          Computes the square root of a double.                             *
 *  Method:                                                                   *
 *      The Euclidean norm, also called the L2 norm of a vector P = (x, y, z) *
 *      is defined as:                                                        *
 *                                                                            *
 *          ||P|| = sqrt(x^2 + y^2 + z^2)                                     *
 *                                                                            *
 *      The computation of x^2, y^2, and z^2 may result in an overflow        *
 *      or an underflow, resulting in zero or infinity. If the IEEE-754       *
 *      format is supported, the smallest positive value x such that x^2 will *
 *      overflow is 2^512. The largest positive value such that x will        *
 *      underflow is 2^-512. Using this, we do the following:                 *
 *                                                                            *
 *      Given P = (x, y, z), compute |x|, |y|, and |z|.                       *
 *                                                                            *
 *      Compute the max w = max(|x|, |y|, |z|)                                *
 *                                                                            *
 *      If the exponent of w is greater than 512, multiply x, y, and z by     *
 *      2^-512 and compute 2^512*sqrt(x*x + y*y + z*z).                       *
 *                                                                            *
 *      If the exponent of w is less than -520, multiply x, y, and z by       *
 *      2^512 and compute 2^-512*sqrt(x*x + y*y + z*z).                       *
 *                                                                            *
 *      Else, compute sqrt(x*x + y*y + z*z).                                  *
 *                                                                            *
 *      Lacking IEEE-754 support, this trick may not prevent overflow and     *
 *      and underflow. In this case, we do the following.                     *
 *                                                                            *
 *      Given P = (x, y, z), compute |x|, |y|, and |z|.                       *
 *                                                                            *
 *      Compute the max, t = max(|x|, |y|, |z|)                               *
 *                                                                            *
 *      If t == 0.0, return 0.                                                *
 *                                                                            *
 *      Else, set:                                                            *
 *          x = x / t                                                         *
 *          y = y / t                                                         *
 *          z = z / t                                                         *
 *                                                                            *
 *      Return w * sqrt(x*x + y*y + z*z)                                      *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
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
#include <libtmpl/include/tmpl_vec3.h>

/*  Square root function found here.                                          */
#include <libtmpl/include/tmpl_math.h>

#include <libtmpl/include/tmpl_minmax.h>

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  The values 2^512 and 2^-512, to double precision, stored as macros.       */
#define BIG_SCALE 1.340780792994259709957402E+154
#define RCPR_BIG_SCALE 7.458340731200206743290965E-155

/*  Function for computing the length of three dimensional vectors.           */
double tmpl_3DDouble_L2_Norm(const tmpl_ThreeVectorDouble *P)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Double w;

    /*  Given P = (x, y, z), compute |x|, |y|, and |z|.                       */
    double x = tmpl_Double_Abs(P->dat[0]);
    double y = tmpl_Double_Abs(P->dat[1]);
    double z = tmpl_Double_Abs(P->dat[2]);

    /*  Compute the maximum of |x|, |y|, and |z| and store it in the double   *
     *  part of the tmpl_IEEE754_Double union w.                              */
    w.r = TMPL_MAX3(x, y, z);

    /*  We want to check if the exponent is less than 512, which is 0x200 in  *
     *  hexidecimal. The exponent of a double is offset by a biased. To check *
     *  if the exponent is less than 512, check if the exponent part of the   *
     *  double is less than 512 plus the bias.                                */
    if (w.bits.expo < TMPL_DOUBLE_BIAS + 0x200U)
    {
        /*  If the exponent is greater than -512, then all values of |x|,     *
         *  |y|, and |z| lie between 2^-512 and 2^512 meaning none of the     *
         *  values x^2, y^2, z^2 will overflow or underflow. It is possible   *
         *  the maximum of |x|, |y|, |z| has exponent slightly greater than   *
         *  -512, but the other values have exponent slightly less. To ensure *
         *  accuracy to 16 decimals, check if the exponent is greater than    *
         *  -502. If the difference in the exponents of the largest and       *
         *  second largest of |x|, |y|, and |z| is greater than 10, then to   *
         *  at least 16 decimals we have ||P|| = max(|x|, |y|, |z|).          */
        if (w.bits.expo > 0x20AU)
            return tmpl_Double_Sqrt(x*x + y*y + z*z);

        /*  All values of |x|, |y|, and |z| are very small. To avoid          *
         *  underflow errors, scale these values by 2^512.                    */
        x *= BIG_SCALE;
        y *= BIG_SCALE;
        z *= BIG_SCALE;

        /*  ||P|| can now be computed as 2^-512 * sqrt(x^2 + y^2 + z^2)       *
         *  without the risk of underflow. Return this.                       */
        return RCPR_BIG_SCALE * tmpl_Double_Sqrt(x*x + y*y + z*z);
    }

    /*  All values of |x|, |y|, and |z| are very large and x^2, y^2, and      *
     *  x^2, y^2, and z^2 will all overflow to infinity. Scale by 2^-512.     */
    x *= RCPR_BIG_SCALE;
    y *= RCPR_BIG_SCALE;
    z *= RCPR_BIG_SCALE;

    /*  ||P|| can now be computed as 2^512 * sqrt(x^2 + y^2 + z^2) without    *
     *  the risk of overflow. Return this.                                    */
    return BIG_SCALE * tmpl_Double_Sqrt(x*x + y*y + z*z);
}
/*  End of tmpl_3DDouble_L2_Norm.                                             */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef BIG_SCALE
#undef RCPR_BIG_SCALE

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  Lacking IEEE-754 support, we can use the standard trick to avoid          *
 *  underflows and overflows that is used in the hypot (hypotenuse) functions.*
 *  This is about 1.4x slower than the method above, but is portable. The     *
 *  reason for the slowness is above we multiply by constants, whereas this   *
 *  algorithm requires divisions and multiplications by non-constants.        */

/*  Function for computing the length of three dimensional vectors.           */
double tmpl_3DDouble_L2_Norm(const tmpl_ThreeVectorDouble *P)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double rcpr_t;

    /*  Given P = (x, y, z), compute |x|, |y|, and |z|.                       */
    double x = tmpl_Double_Abs(P->dat[0]);
    double y = tmpl_Double_Abs(P->dat[1]);
    double z = tmpl_Double_Abs(P->dat[2]);

    /*  Compute the maximum of |x|, |y|, and |z|.                             */
    const double t = TMPL_MAX3(x, y, z);

    /*  Division by zero is generally viewed as bad. If the max of |x|, |y|,  *
     *  and |z| is zero, ||P|| = 0. Return this.                              */
    if (t == 0.0)
        return 0.0;

    /*  Precompte 1/t to turn 3 divisions into 1 division and 3 products.     */
    rcpr_t = 1.0 / t;

    /*  Scale x, y, and z and 1/t.                                            */
    x *= rcpr_t;
    y *= rcpr_t;
    z *= rcpr_t;

    /*  ||P|| can safely be computed a t * sqrt((x/t)^2 + (y/t)^2 + (z/t)^2)  *
     *  without risk of underflow or overflow.                                */
    return t * tmpl_Double_Sqrt(x*x + y*y + z*z);
}
/*  End of tmpl_3DDouble_L2_Norm.                                             */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
