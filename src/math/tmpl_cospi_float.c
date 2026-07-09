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

/*  Function prototype, absolute value, and mod 2 function found here.        */
#include <libtmpl/include/tmpl_math.h>

/*  C23 attributes for optimization found here.                               */
#include <libtmpl/include/tmpl_attributes.h>

/*  Look-up tables for sinpi and cospi given here.                            */
#include <libtmpl/include/tables/tmpl_cospi_tables.h>
#include <libtmpl/include/tables/tmpl_sinpi_tables.h>

/*  Remez minimax polynomials for very small inputs.                          */
#include "auxiliary/tmpl_cospi_maclaurin_float.h"
#include "auxiliary/tmpl_sinpi_maclaurin_float.h"

/*  Significantly faster, and more accurate near integers, using IEEE-754.    */
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  Computes cos(pi x) at single precision.                                   */
TMPL_NO_ASSOCIATIVE_MATH
TMPL_CONST_FUNC
float tmpl_Float_CosPi(const float x)
TMPL_UNSEQUENCED
{
    /*  We compute using the angle sum formula for cos(pi(r + dr)). Set aside *
     *  four variables for the right hand side of that equation.              */
    float cos_pi_r, cos_pi_dr, sin_pi_r, sin_pi_dr;

    /*  We will write y = |x| mod 2 = r + dr, and compute cos(pi(r + dr)).    *
     *  r will be an integer multiple of 1 / 128, and sin(pi r) and cos(pi r) *
     *  are computed via a lookup table. Declare a variable for dr.           */
    float dr;

    /*  Variable for the output, cos(pi x).                                   */
    float out;

    /*  We compute the index of the lookup table using some bit-shifting      *
     *  tricks. Declare necessary variables. C89 requires this at the top.    */
    unsigned int lowest_eight_bits, index;

    /*  cos(pi x) is even, so we reduce x to |x| and compute with this. We    *
     *  negate to negate the output if |x| mod 2 falls between 1 and 2. We    *
     *  will compute this later with some bit-shifting tricks.                */
    unsigned int negate;

    /*  Unions of floats and the bits representing them.                      */
    tmpl_IEEE754_Float w;

    /*  If -ffast-math is enabled, this variable needs to be declared as      *
     *  volatile to prevent the compiler from optimizing away the split.      */
    TMPL_VOLATILE tmpl_IEEE754_Float shifted;

    /*  The value 2^16 = 2^(24 - 8). We will use this to get the index of the *
     *  lookup table by shifting the input and extracting the lower 8 bits.   */
    const float shifter = 6.5536E+04F;

    /*  Set the float part of the word to the input.                          */
    w.r = x;

    /*  Special case, NaN or infinity. Return NaN in either case.             */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
        return TMPL_NANF;

    /*  Reduce to non-negative inputs, compute |x|.                           */
    w.bits.sign = 0x00U;

    /*  cos(pi x) is periodic with period 2. Reduce to |x| mod 2.             */
    w.r = tmpl_Float_Mod_2(w.r);

    /*  Shift |x| up by 2^16. The most significant 8 bits of |x| are now the  *
     *  least significant 8 bits of shifted.                                  */
    shifted.r = w.r + shifter;

    /*  Extract the lowest 8 bits. man1 is a 16-bit word, so we need a bit    *
     *  mask with 8 zeros and 8 ones. 0x00FF is the bit mask for this.        */
    lowest_eight_bits = (0x00FFU & shifted.bits.man1);

    /*  We only negate if 1 <= |x| mod 2 < 2. This occurs precisely when the  *
     *  1's bit of |x| mod 2 is set to 1 (all higher bits are zero since      *
     *  |x| mod 2 < 2 is true). This is the leading bit of lowest_eight_bits. */
    negate = (lowest_eight_bits >> 7U);

    /*  Write y = |x| mod 2 = r + dr where |dr| < 2^-7 and r is an            *
     *  integer multiple of 1 / 128, we compute cos(pi y) via:                *
     *                                                                        *
     *      cos(pi y) = cos(pi(r + dr))                                       *
     *                = cos(pi r + pi dr)                                     *
     *                = cos(pi r) cos(pi dr) - sin(pi r) sin(pi dr)           *
     *                                                                        *
     *  cos(pi r) and sin(pi r) are computed by a lookup table. The index for *
     *  this lookup table is the integer n such that r = n / 128. This is     *
     *  the lower 7 bits of the "shifted" word. That is, shifted is equal to  *
     *  y + 2^45. Since floating point arithmetic rounds the sum, the lowest  *
     *  8 bits of shifted are equal to the most significant 8 bits of y:      *
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

    /*  Compute cos(pi y) using the angle sum formula.                        */
    sin_pi_r = tmpl_float_sinpi_table[index];
    cos_pi_r = tmpl_float_cospi_table[index];
    sin_pi_dr = tmpl_Float_SinPi_Maclaurin(dr);
    cos_pi_dr = tmpl_Float_CosPi_Maclaurin(dr);
    out = cos_pi_r * cos_pi_dr - sin_pi_r * sin_pi_dr;

    /*  Negate if necessary. The "negate" Boolean has the answer.             */
    if (negate)
        return -out;

    /*  Otherwise, we're done. Return the output.                             */
    return out;
}
/*  End of tmpl_Float_CosPi.                                                  */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/*  Helper macro for C vs. C++ compatibility with casting.                    */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Computes cos(pi x) at single precision.                                   */
TMPL_CONST_FUNC
float tmpl_Float_CosPi(const float x)
TMPL_UNSEQUENCED
{
    float arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_Float_Mod_2(tmpl_Float_Abs(x));

    if (arg >= 1.0F)
    {
        sgn_x = -1.0F;
        arg = arg - 1.0F;
    }
    else
        sgn_x = 1.0F;

    ind = (unsigned int)(128.0F*arg);
    dx = arg - 0.0078125F*(float)ind;

    sx = tmpl_float_sinpi_table[ind];
    cx = tmpl_float_cospi_table[ind];
    sdx = tmpl_Float_SinPi_Maclaurin(dx);
    cdx = tmpl_Float_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
/*  End of tmpl_Float_CosPi.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
