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

/*  Splitting functions found here.                                           */
#include <libtmpl/include/tmpl_split.h>

/*  Function prototype, absolute value, and mod 2 function found here.        */
#include <libtmpl/include/tmpl_math.h>

/*  C23 attributes for optimization found here.                               */
#include <libtmpl/include/tmpl_attributes.h>

/*  Look-up tables for sinpi and cospi given here.                            */
#include <libtmpl/include/tables/tmpl_cospi_tables.h>
#include <libtmpl/include/tables/tmpl_sinpi_tables.h>

/*  Remez minimax polynomials for very small inputs.                          */
#include "auxiliary/tmpl_cospi_maclaurin_ldouble.h"
#include "auxiliary/tmpl_sinpi_maclaurin_ldouble.h"

/*  Significantly faster, and more accurate near integers, using IEEE-754.    */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT
#define TMPL_LDOUBLE_SHIFTER (+3.5184372088832E+13L)
#define TMPL_LDOUBLE_LOWER_EIGHT_BITS (0x00FFU & shifted.bits.man3)
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT
#define TMPL_LDOUBLE_SHIFTER (+7.2057594037927936E+16L)
#define TMPL_LDOUBLE_LOWER_EIGHT_BITS (0x00FFU & shifted.bits.man3)
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT
#define TMPL_LDOUBLE_SHIFTER (+4.0564819207303340847894502572032E+31L)
#define TMPL_LDOUBLE_LOWER_EIGHT_BITS (0x00FFU & shifted.bits.man6)
#else
#define TMPL_LDOUBLE_SHIFTER (+3.5184372088832E+13L)
#define TMPL_LDOUBLE_LOWER_EIGHT_BITS (0x00FFU & shifted.bits.man3)
#endif

/*  Computes cos(pi x) at long double precision.                              */
TMPL_CONST_FUNC
long double tmpl_LDouble_CosPi(const long double x)
TMPL_UNSEQUENCED
{
    /*  We compute using the angle sum formula for cos(pi(r + dr)). Set aside *
     *  four variables for the right hand side of that equation.              */
    long double cos_pi_r, cos_pi_dr, sin_pi_r, sin_pi_dr;

    /*  We will write y = |x| mod 2 = r + dr, and compute cos(pi(r + dr)).    *
     *  r will be an integer multiple of 1 / 128, and sin(pi r) and cos(pi r) *
     *  are computed via a lookup table. Declare a variable for dr.           */
    long double dr;

    /*  Variable for the output, cos(pi x).                                   */
    long double out;

    /*  We compute the index of the lookup table using some bit-shifting      *
     *  tricks. Declare necessary variables. C89 requires this at the top.    */
    unsigned int lowest_eight_bits, index;

    /*  cos(pi x) is even, so we reduce x to |x| and compute with this. We    *
     *  negate to negate the output if |x| mod 2 falls between 1 and 2. We    *
     *  will compute this later with some bit-shifting tricks.                */
    unsigned int negate;

    /*  Unions of long doubles and the bits representing them.                */
    tmpl_IEEE754_LDouble w;

    /*  If -ffast-math is enabled, this variable needs to be declared as      *
     *  volatile to prevent the compiler from optimizing away the split.      */
    TMPL_VOLATILE tmpl_IEEE754_LDouble shifted;

    /*  The value 2^45 = 2^(53 - 8). We will use this to get the index of the *
     *  lookup table by shifting the input and extracting the lower 8 bits.   */
    const long double shifter = TMPL_LDOUBLE_SHIFTER;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Special case, NaN or infinity. Return NaN in either case.             */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return TMPL_NANL;

    /*  Reduce to non-negative inputs, compute |x|.                           */
    w.r = tmpl_LDouble_Abs(w.r);

    /*  cos(pi x) is periodic with period 2. Reduce to |x| mod 2.             */
    w.r = tmpl_LDouble_Mod_2(w.r);

    /*  Shift |x| up by 2^45. The most significant 8 bits of |x| are now the  *
     *  least significant 8 bits of shifted.                                  */
    shifted.r = w.r + shifter;

    /*  The double-double implementation needs to zero out the low part.      */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE
    shifted.d[1] = 0.0;
#endif

    /*  Extract the lowest 8 bits. The exact location of these bits depends   *
     *  on how long double is represented, use the macro.                     */
    lowest_eight_bits = TMPL_LDOUBLE_LOWER_EIGHT_BITS;

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
    dr = tmpl_LDouble_Right_Difference(w.r, shifted.r, shifter);

    /*  Compute cos(pi y) using the angle sum formula.                        */
    sin_pi_r = tmpl_ldouble_sinpi_table[index];
    cos_pi_r = tmpl_ldouble_cospi_table[index];
    sin_pi_dr = tmpl_LDouble_SinPi_Maclaurin(dr);
    cos_pi_dr = tmpl_LDouble_CosPi_Maclaurin(dr);
    out = cos_pi_r * cos_pi_dr - sin_pi_r * sin_pi_dr;

    /*  Negate if necessary. The "negate" Boolean has the answer.             */
    if (negate)
        return -out;

    /*  Otherwise, we're done. Return the output.                             */
    return out;
}
/*  End of tmpl_LDouble_CosPi.                                                */

#undef TMPL_LDOUBLE_SHIFTER
#undef TMPL_LDOUBLE_LOWER_EIGHT_BITS

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/*  Helper macro for C vs. C++ compatibility with casting.                    */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Computes cos(pi x) at double precision.                                   */
TMPL_NO_ASSOCIATIVE_MATH
TMPL_CONST_FUNC
long double tmpl_LDouble_CosPi(const long double x)
TMPL_UNSEQUENCED
{
    long double arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_LDouble_Mod_2(tmpl_LDouble_Abs(x));

    if (arg >= 1.0L)
    {
        sgn_x = -1.0L;
        arg = arg - 1.0L;
    }
    else
        sgn_x = 1.0L;

    ind = (unsigned int)(128.0L*arg);
    dx = arg - 0.0078125L*ind;

    sx = tmpl_ldouble_sinpi_table[ind];
    cx = tmpl_ldouble_cospi_table[ind];
    sdx = tmpl_LDouble_SinPi_Maclaurin(dx);
    cdx = tmpl_LDouble_CosPi_Maclaurin(dx);
    return sgn_x * (cdx * cx - sx * sdx);
}
/*  End of tmpl_LDouble_CosPi.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */
