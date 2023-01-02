/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
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
 *                             tmpl_hypot_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the magnitude of the vector (x, y) in the plane.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Hypot:                                                     *
 *  Purpose:                                                                  *
 *      Computes the magnitude of the vector (x, y) in the plane:             *
 *                                                                            *
 *          ||P||_2 = ||(x, y)||_2 = sqrt(x^2 + y^2)                          *
 *                                                                            *
 *      Because x^2 and y^2 are computed as intermediate steps, this method   *
 *      will overflow for values greater than sqrt(DBL_MAX). The safe way to  *
 *      do this is via:                                                       *
 *                                                                            *
 *          |z| = |x| sqrt(1+(y/x)^2)                                         *
 *                                                                            *
 *      if |x| > |y|, and:                                                    *
 *                                                                            *
 *          |z| = |y| sqrt(1 + (x/y)^2)                                       *
 *                                                                            *
 *      otherwise. This is about 1.3-1.5x slower. If IEEE-754 support is      *
 *      available, we need only check if max(|x|, |y|) is in the range        *
 *      (2^-512, 2^512), scaling by a constant if not. This is about as fast  *
 *      as the naive method.                                                  *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *      y (float):                                                            *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      mag (float):                                                          *
 *          The magnitude of (x, y).                                          *
 *  Called Functions:                                                         *
 *      tmpl_Float_Abs     (tmpl_math.h)                                      *
 *          Computes the absolute value of a real number.                     *
 *      tmpl_Float_Sqrt    (tmpl_math.h)                                      *
 *          Computes the square root of a real number.                        *
 *  Error:                                                                    *
 *      Based on 134,217,728 random samples:                                  *
 *          Max Relative Error: 2.220446E-16                                  *
 *          RMS Relative Error: 3.751642e-17                                  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing basic math functions.                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 30, 2022                                             *
 ******************************************************************************/

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  The values 2^64 and 2^-64, to single precision, stored as macros.         */
#define TMPL_BIG_SCALE 1.8446744073709552E+19F
#define TMPL_RCPR_BIG_SCALE 5.4210108624275222E-20F

/*  Function for computing the magnitude of the vector (x, y) in the plane.   */
float tmpl_Float_Hypot(float x, float y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Float w;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    float abs_x = tmpl_Float_Abs(x);
    float abs_y = tmpl_Float_Abs(y);

    /*  Compute the maximum of |x| and |y| and store it in the float          *
     *  part of the tmpl_IEEE754_Float union w.                               */
    if (abs_x < abs_y)
        w.r = abs_y;
    else
        w.r = abs_x;

    /*  We want to check if the exponent is less than 64, which is 0x40 in    *
     *  hexidecimal. The exponent of a float is offset by a bias. To check    *
     *  if the exponent is less than 64, check if the exponent part of the    *
     *  float is less than 64 plus the bias.                                  */
    if (w.bits.expo < TMPL_FLOAT_BIAS + 0x40U)
    {
        /*  If both exponents are greater than -64, then both |x| and         *
         *  |y| lie between 2^-64 and 2^64 meaning neither of the             *
         *  values x^2 or y^2 overflow or underflow. It is possible           *
         *  the maximum of |x| and |y| has exponent slightly greater than     *
         *  -64, but the other value has exponent slightly less. To ensure    *
         *  accuracy to 16 decimals, check if the exponent is greater than    *
         *  -52. If the difference in the exponents of |x| and |y| is         *
         *  greater than 10, then to at least 16 decimals we have             *
         *  |z| = max(|x|, |y|).                                              */
        if (w.bits.expo > 0x4BU)
            return tmpl_Float_Sqrt(abs_x*abs_x + abs_y*abs_y);

        /*  Both |x| and |y| are small. To avoid underflow scale by 2^512.    */
        abs_x *= TMPL_BIG_SCALE;
        abs_y *= TMPL_BIG_SCALE;

        /*  |z| can now be computed as 2^-512 * sqrt(x^2 + y^2)               *
         *  without the risk of underflow. Return this.                       */
        return TMPL_RCPR_BIG_SCALE*tmpl_Float_Sqrt(abs_x*abs_x + abs_y*abs_y);
    }

    /*  Both |x| and |y| are large. To avoid overflow scale by 2^-512.        */
    abs_x *= TMPL_RCPR_BIG_SCALE;
    abs_x *= TMPL_RCPR_BIG_SCALE;

    /*  |z| can now be computed as |z| = 2^512 * sqrt(x^2 + y^2) without      *
     *  the risk of overflow. Return this.                                    */
    return TMPL_BIG_SCALE * tmpl_Float_Sqrt(abs_x*abs_x + abs_y*abs_y);
}
/*  End of tmpl_Float_Hypot.                                                  */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/*  Lacking IEEE-754 support, we can use the standard trick to avoid          *
 *  underflows and overflows that is used in the hypot (hypotenuse) functions.*
 *  This is about 1.4x slower than the method above, but is portable. The     *
 *  reason for the slowness is above we multiply by constants, whereas this   *
 *  algorithm requires divisions and multiplications by non-constants.        */

/*  Function for computing the magnitude of the vector (x, y) in the plane.   */
float tmpl_Float_Hypot(float x, float y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float rcpr_t;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    float abs_x = tmpl_Float_Abs(x);
    float abs_y = tmpl_Float_Abs(y);

    /*  Compute the maximum of |x| and |y|. This syntax from the C language   *
     *  is a bit strange. a = (b < c ? c : b) says if b is less than c, set a *
     *  to c, otherwise set a to b.                                           */
    const float t = (abs_x < abs_y ? abs_y : abs_x);

    /*  Division by zero is generally viewed as bad. If the max of |x| and    *
     *  |z| is zero, |z| = 0. Return this.                                    */
    if (t == 0.0F)
        return 0.0F;

    /*  Precompute 1/t to turn 2 divisions into 1 division and 2 products.    */
    rcpr_t = 1.0F / t;

    /*  Scale x and y by 1/t.                                                 */
    abs_x *= rcpr_t;
    abs_y *= rcpr_t;

    /*  |z| can safely be computed as |z| = t * sqrt((x/t)^2 + (y/t)^2)       *
     *  without risk of underflow or overflow.                                */
    return t * tmpl_Float_Sqrt(abs_x*abs_x + abs_y*abs_y);
}
/*  End of tmpl_Float_Hypot.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
