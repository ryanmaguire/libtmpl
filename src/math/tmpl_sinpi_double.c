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
 ******************************************************************************/
#include <libtmpl/include/tmpl_math.h>
#include "auxiliary/tmpl_cospi_maclaurin_double.h"
#include "auxiliary/tmpl_sinpi_maclaurin_double.h"
#include "auxiliary/tmpl_sinpi_remez_double.h"
#include "auxiliary/tmpl_sinpi_rat_remez_double.h"

/*  Significantly faster, and more accurate near integers, using IEEE-754.    */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Computes sin(pi x) at double precision.                                   */
double tmpl_Double_SinPi(double x)
{
    /*  We compute using the angle sum formula for sin(pi(r + dr)). Set aside *
     *  four variables for the right hand side of that equation.              */
    double cos_pi_r, cos_pi_dr, sin_pi_r, sin_pi_dr;

    /*  We will write y = |x| mod 2 = r + dr, and compute sin(pi(r + dr)).    *
     *  r will be an integer multiple of 1 / 128, and sin(pi r) and cos(pi r) *
     *  are computed via a lookup table. Declare a variable for dr.           */
    double dr;

    /*  Variable for the output, sin(pi x).                                   */
    double out;

    /*  We compute the index of the lookup table using some bit-shifting      *
     *  tricks. Declare necessary variables. C89 requires this at the top.    */
    unsigned int lowest_eight_bits, index;

    /*  sin(pi x) is odd, so we reduce x to |x| and compute with this. These  *
     *  variables keep track of whether or not we need to negate the output.  */
    unsigned int negate, sign;

    /*  Unions of doubles and the bits representing them.                     */
    tmpl_IEEE754_Double w, shifted;

    /*  The value 2^45 = 2^(53 - 8). We will use this to get the index of the *
     *  lookup table by shifting the input and extracting the lower 8 bits.   */
    const double shifter = 3.5184372088832E+13;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  Special case, NaN or infinity. Return NaN in either case.             */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
        return TMPL_NAN;

    /*  For small values we skip the lookup table and get a performance boost.*/
    if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 1U)
    {
        /*  For very small x, sin(pi x) = pi x + O(x^3). Return pi x.         */
        if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 27U)
            return tmpl_Double_Pi * x;

        /*  For |x| < 2^-4 we may use a Remez polynomial that is quite fast.  */
        if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 4U)
            return tmpl_Double_SinPi_Remez(x);

        /*  For |x| < 0.5 use the degree (9, 8) rational Remez approximation. */
        return tmpl_Double_SinPi_Rat_Remez(x);
    }

    /*  sin(pi x) is odd, hence sin(-pi x) = -sin(pi x). We save the sign of  *
     *  input and negate the output at the end of the computation if needed.  */
    sign = w.bits.sign;

    /*  Reduce to non-negative inputs, compute |x|.                           */
    w.bits.sign = 0x00U;

    /*  sin(pi x) is periodic with period 2. Reduce to |x| mod 2.             */
    w.r = tmpl_Double_Mod_2(w.r);

    /*  Shift |x| up by 2^45. The most significant 8 bits of |x| are now the  *
     *  least significant 8 bits of shifted, with possible rounding.          */
    shifted.r = w.r + shifter;

    /*  Extract the lowest 8 bits. man3 is a 16-bit word, so we need a bit    *
     *  mask with 8 zeros and 8 ones. 0x00FF is the bit mask for this.        */
    lowest_eight_bits = (0x00FFU & shifted.bits.man3);

    /*  Let y = |x| mod 2. We write y = r + dr where |dr| < 2^-7 and r is and *
     *  integer multiple of 1 / 128. If the leading bit of lowest_eight_bits  *
     *  is 1, then 1 <= r < 2. We reduce this to 0 <= r < 1 by subtracting    *
     *  1 from r, and then invoke the fact that:                              *
     *                                                                        *
     *       sin(pi y) = -sin(pi(y - 1))                                      *
     *                                                                        *
     *  Because of this, we may need to negate the output. We may also need   *
     *  to negate the output if the input x is negative. If the input is      *
     *  positive and 0 <= r < 1, then there is no need to negate the output.  *
     *  If the input is negative and 1 <= r < 2, then there is a double       *
     *  negative which cancels, meaning we do not need to negate the output.  *
     *  Hence, we negate the output if the input is negative XOR 1 <= r < 2,  *
     *  where XOR means "exclusive or." By extracting the leading bit, and    *
     *  performing the exclusive or "^" with the sign, we get the Boolean for *
     *  negating the output.                                                  *
     *                                                                        *
     *  Note:                                                                 *
     *      It is possible for r = 2 to occur (but r > 2 is not possible      *
     *      since we have computed y = |x| mod 2). This will happen if y is   *
     *      very close to 2, such as 1 - 2^-10. In this case, dr is negative  *
     *      and the index for the table will be 0 (see below for both). Since *
     *      sin(pi x) is periodic with period 2, we have:                     *
     *                                                                        *
     *          sin(pi(r + dr)) = sin(pi dr)                                  *
     *                                                                        *
     *      We not need to use sin(pi y) = -sin(pi(y - 1)) in this case, and  *
     *      only negate the output if the input is negative. If r = 2, then   *
     *      the ninth bit of shifted.bits.man3 is 1 and the eigth bit is 0.   *
     *      We do not examine the ninth bit (we've zeroed it out), and hence  *
     *      r = 2 has the same affect as r = 0, as desired. Below we then     *
     *      have:                                                             *
     *                                                                        *
     *          negate = 0 ^ sign                                             *
     *                 = sign                                                 *
     *                                                                        *
     *      which is precisely what we want.                                  */
    negate = (lowest_eight_bits >> 7U) ^ sign;

    /*  Again writing y = |x| mod 2 = r + dr where |dr| < 2^-7 and r is an    *
     *  integer multiple of 1 / 128, we compute sin(pi y) via:                *
     *                                                                        *
     *      sin(pi y) = sin(pi(r + dr))                                       *
     *                = sin(pi r + pi dr)                                     *
     *                = cos(pi r) sin(pi dr) + sin(pi r) cos(pi dr)           *
     *                                                                        *
     *  cos(pi r) and sin(pi r) are computed by a lookup table. The index for *
     *  this lookup table is the integer n such that r = n / 128. This is     *
     *  the lower 7 bits of the "shifted" word. That is, shifted is equal to  *
     *  y + 2^45. Since floating point arithmetic truncates, the lowest       *
     *  8 bits of shifted are equal to the most significant 8 bits of y.      *
     *                                                                        *
     *  If the 8th bit is one, we have 1 <= r < 2. To shift to 0 <= r < 1 we  *
     *  simply zero out the eigth bit (this is the "1's" bit in "shifted").   *
     *  The integer n such that r = n / 128 is then the 7 bits after the      *
     *  binary point, treated as a number. That is:                           *
     *                                                                        *
     *           a     b     c     d     e     f     g                        *
     *      r = --- + --- + --- + --- + --- + --- + ---                       *
     *            1     2     3     4     5     6     7                       *
     *           2     2     2     2     2     2     2                        *
     *                                                                        *
     *  The index is n = abcdefg, read in binary. We compute this by zeroing  *
     *  the leading bit of lowest_eight_bits. We need 9 zeros and 7 ones. The *
     *  bit mask for this is 0x007F.                                          *
     **************************************************************************/
    index = (lowest_eight_bits & 0x007FU);

    /*  shifted - shifter is equal to |x| mod 2 truncated to 2^-7. The dr     *
     *  factor is then just the difference. Compute this.                     */
    dr = w.r - (shifted.r - shifter);

    /*  Compute sin(pi y) using the angle sum formula.                        */
    sin_pi_r = tmpl_double_sinpi_table[index];
    cos_pi_r = tmpl_double_cospi_table[index];
    sin_pi_dr = tmpl_Double_SinPi_Maclaurin(dr);
    cos_pi_dr = tmpl_Double_CosPi_Maclaurin(dr);
    out = cos_pi_r*sin_pi_dr + sin_pi_r*cos_pi_dr;

    /*  Negate if necessary. The "negate" Boolean has the answer.             */
    if (negate)
        return -out;

    /*  Otherwise, we're done. Return the output.                             */
    return out;
}
/*  End of tmpl_Double_SinPi.                                                 */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  Helper macro for C vs. C++ compatibility with casting.                    */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Computes sin(pi x) at double precision.                                   */
double tmpl_Double_SinPi(double x)
{
    double arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    if (tmpl_Double_Is_NaN_Or_Inf(x))
        return TMPL_NAN;

    if (x >= 0.0)
    {
        abs_x = x;
        sgn_x = 1.0;
    }
    else
    {
        abs_x = -x;
        sgn_x = -1.0;
    }

    if (abs_x < 0.5)
    {
        if (abs_x < 7.450580596923828e-09)
            return tmpl_Double_Pi * x;

        if (abs_x < 0.0625)
            return tmpl_Double_SinPi_Remez(x);

        return tmpl_Double_SinPi_Rat_Remez(x);
    }

    arg = tmpl_Double_Mod_2(abs_x);

    if (arg >= 1.0)
    {
        sgn_x *= -1.0;
        arg -= 1.0;
    }

    ind = TMPL_CAST(128.0*arg, unsigned int);
    dx = arg - 0.0078125*TMPL_CAST(ind, double);

    sx = tmpl_double_sinpi_table[ind];
    cx = tmpl_double_cospi_table[ind];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}
/*  End of tmpl_Double_SinPi.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
