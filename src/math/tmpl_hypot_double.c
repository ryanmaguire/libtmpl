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
 *                             tmpl_hypot_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the magnitude of the vector (x, y) in the plane.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Hypot:                                                    *
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
 *      x (double):                                                           *
 *          A real number.                                                    *
 *      y (double):                                                           *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      mag (double):                                                         *
 *          The magnitude of (x, y).                                          *
 *  Called Functions:                                                         *
 *      tmpl_Double_Abs     (tmpl_math.h)                                     *
 *          Computes the absolute value of a real number.                     *
 *      tmpl_Double_Sqrt    (tmpl_math.h)                                     *
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

#include <libtmpl/include/tmpl_minmax.h>

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  The values 2^512 and 2^-512, to double precision, stored as macros.       */
#define TMPL_BIG_SCALE 1.340780792994259709957402E+154
#define TMPL_RCPR_BIG_SCALE 7.458340731200206743290965E-155

/*  Function for computing the magnitude of the vector (x, y) in the plane.   */
double tmpl_Double_Hypot(double x, double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Double w;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    double abs_x = tmpl_Double_Abs(x);
    double abs_y = tmpl_Double_Abs(y);

    /*  Compute the maximum of |x| and |y| and store it in the double         *
     *  part of the tmpl_IEEE754_Double union w.                              */
    w.r = TMPL_MAX(abs_x, abs_y);

    /*  We want to check if the exponent is less than 512, which is 0x200 in  *
     *  hexadecimal. The exponent of a double is offset by a bias. To check   *
     *  if the exponent is less than 512, check if the exponent part of the   *
     *  double is less than 512 plus the bias.                                */
    if (w.bits.expo < TMPL_DOUBLE_BIAS + 0x200U)
    {
        /*  If both exponents are greater than -512, then both |x| and        *
         *  |y| lie between 2^-512 and 2^512 meaning neither of the           *
         *  values x^2 or y^2 overflow or underflow. It is possible           *
         *  the maximum of |x| and |y| has exponent slightly greater than     *
         *  -512, but the other value has exponent slightly less. To ensure   *
         *  accuracy to 16 decimals, check if the exponent is greater than    *
         *  -486. If the difference in the exponents of |x| and |y| is        *
         *  greater than 26, then to at least 16 decimals (52 bits) we have   *
         *  |z| = max(|x|, |y|). 486 is 0x1E6 in hexadecimal.                 */
        if (w.bits.expo > TMPL_DOUBLE_BIAS - 0x1E6U)
            return tmpl_Double_Sqrt(abs_x*abs_x + abs_y*abs_y);
        else if (w.bits.expo == 0x00U)
        {
            /*  Very very small, denormal number. Scale values up.            */
            abs_x *= TMPL_DOUBLE_NORMALIZE;
            abs_y *= TMPL_DOUBLE_NORMALIZE;

            abs_x *= TMPL_BIG_SCALE;
            abs_y *= TMPL_BIG_SCALE;
            w.r = TMPL_RCPR_BIG_SCALE*tmpl_Double_Sqrt(abs_x*abs_x+abs_y*abs_y);
            return w.r / TMPL_DOUBLE_NORMALIZE;
        }

        /*  Both |x| and |y| are small. To avoid underflow scale by 2^512.    */
        abs_x *= TMPL_BIG_SCALE;
        abs_y *= TMPL_BIG_SCALE;

        /*  |z| can now be computed as 2^-512 * sqrt(x^2 + y^2)               *
         *  without the risk of underflow. Return this.                       */
        return TMPL_RCPR_BIG_SCALE*tmpl_Double_Sqrt(abs_x*abs_x + abs_y*abs_y);
    }

    /*  Both |x| and |y| are large. To avoid overflow scale by 2^-512.        */
    abs_x *= TMPL_RCPR_BIG_SCALE;
    abs_y *= TMPL_RCPR_BIG_SCALE;

    /*  |z| can now be computed as |z| = 2^512 * sqrt(x^2 + y^2) without      *
     *  the risk of overflow. Return this.                                    */
    return TMPL_BIG_SCALE * tmpl_Double_Sqrt(abs_x*abs_x + abs_y*abs_y);
}
/*  End of tmpl_Double_Hypot.                                                 */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  Lacking IEEE-754 support, we can use the standard trick to avoid          *
 *  underflows and overflows that is used in the hypot (hypotenuse) functions.*
 *  This is about 1.4x slower than the method above, but is portable. The     *
 *  reason for the slowness is above we multiply by constants, whereas this   *
 *  algorithm requires divisions and multiplications by non-constants.        */

/*  Function for computing the magnitude of the vector (x, y) in the plane.   */
double tmpl_Double_Hypot(double x, double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double rcpr_t;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    double abs_x = tmpl_Double_Abs(x);
    double abs_y = tmpl_Double_Abs(y);

    /*  Compute the maximum of |x| and |y|.                                   */
    const double t = TMPL_MAX(abs_x, abs_y);

    /*  Division by zero is generally viewed as bad. If the max of |x| and    *
     *  |z| is zero, |z| = 0. Return this.                                    */
    if (t == 0.0)
        return 0.0;

    /*  Precompute 1/t to turn 2 divisions into 1 division and 2 products.    */
    rcpr_t = 1.0 / t;

    /*  Scale x and y by 1/t.                                                 */
    abs_x *= rcpr_t;
    abs_y *= rcpr_t;

    /*  |z| can safely be computed as |z| = t * sqrt((x/t)^2 + (y/t)^2)       *
     *  without risk of underflow or overflow.                                */
    return t * tmpl_Double_Sqrt(abs_x*abs_x + abs_y*abs_y);
}
/*  End of tmpl_Double_Hypot.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
