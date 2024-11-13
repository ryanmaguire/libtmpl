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
 *                             tmpl_mod_360_float                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the remainder after division by 360.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Mod_360                                                    *
 *  Purpose:                                                                  *
 *      Computes the remainder after division of the input by 360.            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for x mod 360.                        *
 *  Output:                                                                   *
 *      x_mod_360 (float):                                                    *
 *          The remainder after division of x by 360.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 23, 2024                                             *
 ******************************************************************************/

/*  Function prototype and IEEE-754 float found here.                         */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 float. This method is significantly faster.            */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing x mod 360.                                         */
float tmpl_Float_Mod_360(float x)
{
    tmpl_IEEE754_Float w, tmp, pow2_360, invpow2_360;
    unsigned int ind, n, shift;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Special case, Infinity and NaN.                                       */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
        return TMPL_NANF;

    /*  Save the sign of x for later.                                         */
    tmp.bits.sign = w.bits.sign;

    /*  Compute the absolute value of the input.                              */
    w.bits.sign = 0x00U;

    /*  For inputs with magnitude less than 360, no modulo is computed.       */
    if (w.r < 360.0F)
        return x;

    /*  The value 360 as a float.                                             */
    pow2_360.r = 3.60E2F;

    /*  And the value 1 / 360 to single precision.                            */
    invpow2_360.r = 2.777777777777777777777777777777777777778E-03F;

    /*  360 = 1.xxx * 2^8. Subtract 8 from the exponent and divide by 16      *
     *  to see how many multiples of 16 are needed for the loop.              */
    ind = (w.bits.expo - TMPL_FLOAT_UBIAS - 8U) >> 4U;

    /*  The shift is 16 times the index. Compute this.                        */
    shift = ind << 4U;

    /*  Compute 2^shift * 360 by adding shift to the exponent.                */
    pow2_360.bits.expo += (shift & 0x7FFU) & 0xFFU;

    /*  Similarly, compute 2^-shift / 360.                                    */
    invpow2_360.bits.expo -= (shift & 0x7FFU) & 0xFFU;

    /*  Loop through the bits of the number 16 at a time and compute          *
     *  x mod 2^(ind - n) * 360. This will safely compute x mod 360.          */
    for (n = 0U; n <= ind; ++n)
    {
        /*  Compute x mod 2^(ind - n) * 360 with the floor function.          */
        w.r -= pow2_360.r*tmpl_Float_Floor(w.r * invpow2_360.r);

        /*  expo is 8 bits, so the max value is 256 - 1. -16 is congruent     *
         *  240 mod 256, so add this value. This is equivalent to             *
         *  subtracting 16, but avoids conversion warnings from 16-bit int to *
         *  8-bit int.                                                        */
        pow2_360.bits.expo += 240U;

        /*  We are increasing this power by positive 16. No conversion needed.*/
        invpow2_360.bits.expo += 16U;
    }

    /*  If w.r * invpow2_360 was off by a bit, the floor of this may be off   *
     *  by one. It is then possible that too many multiples of 360 were       *
     *  subtracted off. If w.r is negative, add back 360.                     */
    if (w.bits.sign)
        w.r += 360.0F;

    /*  tmp still has the original sign. Copy this into the output and return.*/
    w.bits.sign = tmp.bits.sign;
    return w.r;
}
/*  End of tmpl_Float_Mod_360.                                                */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for computing x mod 360.                                         */
float tmpl_Float_Mod_360(float x)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    float abs_x, pow2_360, invpow2_360, pow2, invpow2, mant;
    int ind, n, shift;
    signed int expo;

    /*  The values 2^16 and 2^-16.                                            */
    const float pow16 = 6.5536E4F;
    const float invpow16 = 1.52587890625E-05F;

    /*  Special case, Infinity and NaN.                                       */
    if (tmpl_Float_Is_NaN_Or_Inf(x))
        return TMPL_NANF;

    /*  Compute |x|. x mod 360 is odd, we'll restore the sign at the end.     */
    abs_x = tmpl_Float_Abs(x);

    /*  For inputs with magnitude less than 360, no modulo is computed.       */
    if (abs_x < 360.0F)
        return x;

    /*  The value 360 as a float.                                             */
    pow2_360 = 3.60E2F;

    /*  And the value 1 / 360 to single precision.                            */
    invpow2_360 = 2.777777777777777777777777777777777777778E-03F;

    /*  Get the input in scientific form. Note, since |x| >= 360, expo is     *
     *  not a negative integer.                                               */
    tmpl_Float_Base2_Mant_and_Exp(abs_x, &mant, &expo);

    /*  360 = 1.xxx * 2^8. Subtract of 8 from the exponent and divide by 16   *
     *  to see how many multiples of 16 are needed for the loop.              */
    ind = (expo - 8) >> 4;

    /*  The shift is 16 times the index. Compute this.                        */
    shift = ind << 4;

    /*  Compute 360 * 2^shift.                                                */
    pow2 = tmpl_Float_Pow2(shift);
    pow2_360 *= pow2;

    /*  Similarly, compute 2^-shift / 360.                                    */
    invpow2 = 1.0F / pow2;
    invpow2_360 *= invpow2;

    /*  Loop through the bits of the number 16 at a time and compute          *
     *  x mod 2^(ind - n) * 360. This will safely compute x mod 360.          */
    for (n = 0; n <= ind; ++n)
    {
        /*  Compute x mod 2^(ind - n) * 360 with the floor function.          */
        abs_x -= pow2_360*tmpl_Float_Floor(abs_x * invpow2_360);

        /*  Shift the positive power down.                                    */
        pow2_360 *= invpow16;

        /*  And shift the negative power up.                                  */
        invpow2_360 *= pow16;
    }

    /*  If abs_x * invpow2_360 was off by a bit, the floor of this may be off *
     *  by one. It is then possible that too many multiples of 360 were       *
     *  subtracted off. If abs_x is negative, add back 360.                   */
    if (abs_x < 0.0F)
        abs_x += 360.0F;

    /*  x mod 360 is an odd function. Use the original sign of x to finish.   */
    if (x < 0.0F)
        return -abs_x;
    else
        return abs_x;
}
/*  End of tmpl_Float_Mod_360.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
