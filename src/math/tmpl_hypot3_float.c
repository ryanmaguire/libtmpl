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
 *                        tmpl_three_vector_norm_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Euclidean norm at single precision.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Hypot3                                                     *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm of a point in R^3.                        *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          The x component of the point.                                     *
 *      y (float):                                                            *
 *          The y component of the point.                                     *
 *      z (float):                                                            *
 *          The z component of the point.                                     *
 *  Output:                                                                   *
 *      norm (float):                                                         *
 *          The Euclidean norm of P = (x, y, z).                              *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Abs:                                                   *
 *              Computes the absolute value of a float.                       *
 *          tmpl_Float_Sqrt:                                                  *
 *              Computes the square root of a float.                          *
 *  Method:                                                                   *
 *      The Euclidean norm, also called the L2 norm of a vector P = (x, y, z) *
 *      is defined as:                                                        *
 *                                                                            *
 *          ||P|| = sqrt(x^2 + y^2 + z^2)                                     *
 *                                                                            *
 *      The computation of x^2, y^2, and z^2 may result in an overflow        *
 *      or an underflow, resulting in zero or infinity. If the IEEE-754       *
 *      format is supported, the smallest positive value x such that x^2 will *
 *      overflow is 2^64. The largest positive value such that x will         *
 *      underflow is 2^-64. Using this, we do the following:                  *
 *                                                                            *
 *      Given P = (x, y, z), compute |x|, |y|, and |z|.                       *
 *                                                                            *
 *      Compute the max w = max(|x|, |y|, |z|)                                *
 *                                                                            *
 *      If the exponent of w is greater than 64, multiply x, y, and z by      *
 *      2^-64 and compute 2^64*sqrt(x*x + y*y + z*z).                         *
 *                                                                            *
 *      If the exponent of w is less than -58, multiply x, y, and z by        *
 *      2^64 and compute 2^-64*sqrt(x*x + y*y + z*z).                         *
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
 *      Return t * sqrt(x*x + y*y + z*z)                                      *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header containing the function prototype.                         *
 *  2.) tmpl_max.h:                                                           *
 *          Provides a helper macro for computing the max of 3 integers.      *
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
 *  2024/06/10: Ryan Maguire                                                  *
 *      Migrated from tmpl_3DFloat_L2_Norm code.                              *
 ******************************************************************************/

/*  Square root and absolute value functions found here.                      */
#include <libtmpl/include/tmpl_math.h>

/*  TMPL_MAX3 macro found here. Computes the max of three numbers.            */
#include <libtmpl/include/helper/tmpl_max.h>

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  The values 2^64 and 2^-64, to single precision, stored as macros.         */
#define TMPL_BIG_SCALE 1.8446744073709552E+19F
#define TMPL_RCPR_BIG_SCALE 5.4210108624275222E-20F

/*  Function for computing the length of three dimensional vectors.           */
float tmpl_Float_Hypot3(float x, float y, float z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Float w;

    /*  Given P = (x, y, z), compute |x|, |y|, and |z|.                       */
    float abs_x = tmpl_Float_Abs(x);
    float abs_y = tmpl_Float_Abs(y);
    float abs_z = tmpl_Float_Abs(z);

    /*  Compute the maximum of |x|, |y|, and |z| and store it in the float    *
     *  part of the tmpl_IEEE754_Float union w.                               */
    w.r = TMPL_MAX3(abs_x, abs_y, abs_z);

    /*  We want to check if the exponent is less than 64, which is 0x40 in    *
     *  hexidecimal. The exponent of a float is offset by a bias. To check    *
     *  if the exponent is less than 64, check if the exponent part of the    *
     *  float is less than 64 plus the bias.                                  */
    if (w.bits.expo < TMPL_FLOAT_BIAS + 0x40U)
    {
        /*  If the exponent is greater than -64, then all values of |x|,      *
         *  |y|, and |z| lie between 2^-64 and 2^64 meaning none of the       *
         *  values x^2, y^2, z^2 will overflow or underflow. It is possible   *
         *  the maximum of |x|, |y|, |z| has exponent slightly greater than   *
         *  -64, but the other values have exponent slightly less. To ensure  *
         *  accuracy to 8 decimals, check if the exponent is greater than     *
         *  -50. If the difference in the exponents of the largest and        *
         *  second largest of |x|, |y|, and |z| is greater than 14, then to   *
         *  at least 8 decimals we have ||P|| = max(|x|, |y|, |z|).           */
        if (w.bits.expo > 0x4DU)
            return tmpl_Float_Sqrt(abs_x*abs_x + abs_y*abs_y + abs_z*abs_z);

        /*  All values of |x|, |y|, and |z| are very small. To avoid          *
         *  underflow errors, scale these values by 2^512.                    */
        abs_x *= TMPL_BIG_SCALE;
        abs_y *= TMPL_BIG_SCALE;
        abs_z *= TMPL_BIG_SCALE;

        /*  ||P|| can now be computed as 2^-512 * sqrt(x^2 + y^2 + z^2)       *
         *  without the risk of underflow. Return this.                       */
        return TMPL_RCPR_BIG_SCALE *
               tmpl_Float_Sqrt(abs_x*abs_x + abs_y*abs_y + abs_z*abs_z);
    }

    /*  All values of |x|, |y|, and |z| are very large and x^2, y^2, and      *
     *  z^2 will all overflow to infinity. Scale by 2^-512.                   */
    abs_x *= TMPL_RCPR_BIG_SCALE;
    abs_y *= TMPL_RCPR_BIG_SCALE;
    abs_z *= TMPL_RCPR_BIG_SCALE;

    /*  ||P|| can now be computed as 2^512 * sqrt(x^2 + y^2 + z^2) without    *
     *  the risk of overflow. Return this.                                    */
    return TMPL_BIG_SCALE *
           tmpl_Float_Sqrt(abs_x*abs_x + abs_y*abs_y + abs_z*abs_z);
}
/*  End of tmpl_Float_Hypot3.                                                 */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Lacking IEEE-754 support, we can use the standard trick to avoid          *
 *  underflows and overflows that is used in the hypot (hypotenuse) functions.*
 *  This is about 1.4x slower than the method above, but is portable. The     *
 *  reason for the slowness is above we multiply by constants, whereas this   *
 *  algorithm requires divisions and multiplications by non-constants.        */

/*  Function for computing the length of three dimensional vectors.           */
float tmpl_Float_Hypot3(float x, float y, float z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float rcpr_t;

    /*  Given P = (x, y, z), compute |x|, |y|, and |z|.                       */
    float abs_x = tmpl_Float_Abs(x);
    float abs_y = tmpl_Float_Abs(y);
    float abs_z = tmpl_Float_Abs(z);

    /*  Compute the maximum of |x|, |y|, and |z|.                             */
    const float t = TMPL_MAX3(abs_x, abs_y, abs_z);

    /*  Division by zero is generally viewed as bad. If the max of |x|, |y|,  *
     *  and |z| is zero, ||P|| = 0. Return this.                              */
    if (t == 0.0F)
        return 0.0F;

    /*  Precompute 1/t to turn 3 divisions into 1 division and 3 products.    */
    rcpr_t = 1.0F / t;

    /*  Scale x, y, and z and 1/t.                                            */
    abs_x *= rcpr_t;
    abs_y *= rcpr_t;
    abs_z *= rcpr_t;

    /*  ||P|| can safely be computed as t * sqrt((x/t)^2 + (y/t)^2 + (z/t)^2) *
     *  without risk of underflow or overflow.                                */
    return t * tmpl_Float_Sqrt(abs_x*abs_x + abs_y*abs_y + abs_z*abs_z);
}
/*  End of tmpl_Float_Hypot3.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
