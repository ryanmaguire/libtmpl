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
 *                             tmpl_sinpi_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized sine function, f(x) = sin(pi x).              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_SinPi                                                     *
 *  Purpose:                                                                  *
 *      Computes sin(pi x), the normalized sine function.                     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sin_pi_x (double):                                                    *
 *          The sine of pi * x.                                               *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/auxiliary/                                               *
 *              tmpl_Double_SinPi_Maclaurin:                                  *
 *                  Computes sin(pi x) for small x using a MacLaurin series.  *
 *              tmpl_Double_CosPi_Maclaurin:                                  *
 *                  Computes cos(pi x) for small x using a MacLaurin series.  *
 *              tmpl_Double_SinPi_Remez:                                      *
 *                  Computes sin(pi x) via a Remez polynomial for |x| < 1/16. *
 *              tmpl_Double_SinPi_Rat_Remez:                                  *
 *                  Computes acos via a minimax approximation for |x| < 1/2.  *
 *              tmpl_Double_Mod_2:                                            *
 *                  Computes the real remainder after division by 2.          *
 *      Method:                                                               *
 *          If x is NaN or +/- infinity:                                      *
 *              Return NaN (not-a-number).                                    *
 *          0 <= |x| < 2^-27:                                                 *
 *              Return pi * x, avoiding underflow. The error is O(x^3).       *
 *          2^-27 <= |x| < 2^-4:                                              *
 *              Use a degree 8 Remez polynomial for the function:             *
 *                                                                            *
 *                         sin(pi x)                                          *
 *                  g(x) = ---------                                          *
 *                             x                                              *
 *                                                                            *
 *              This function is even, meaning the degree 8 Remez polynomial  *
 *              needs only 5 non-zero terms. We evaluate sin(pi x) via:       *
 *                                                                            *
 *                  sin(pi x) = x * p(x)                                      *
 *                                                                            *
 *              where p is the degree 8 Remez polynomial for g.               *
 *          2^-4 <= |x| < 2^-1:                                               *
 *              Use a degree (8, 6) rational minimax approximation for the    *
 *              function g given above, g(x) = sin(pi x) / x. sin(pi x) is    *
 *              then computed via:                                            *
 *                                                                            *
 *                                  p(x)                                      *
 *                  sin(pi x) = x * ----                                      *
 *                                  q(x)                                      *
 *                                                                            *
 *              where p is the numerator and q is the denominator for the     *
 *              minimax approximation, respectively. Since sin(pi x) / x is   *
 *              an even function, the degree (8, 6) rational minimax          *
 *              approximation needs 5 non-zero terms for the numerator and 4  *
 *              non-zero terms for the denominator, and one division. The     *
 *              evaluation is quite fast, giving us a speed boost for values  *
 *              in this range.                                                *
 *          2^-1 <= |x| < infinity:                                           *
 *              sin(pi x) is an odd function, sin(-pi x) = -sin(pi x). Reduce *
 *              x to positive. sin(pi x) is also periodic with period 2,      *
 *              reduce x to x mod 2. With 0 <= x < 2, we compute using a      *
 *              lookup table and the angle sum formula. We split x into       *
 *              r + dr with |dr| < 2^-7, and then evaluate the following:     *
 *                                                                            *
 *                  sin(r + dr) = sin(r) cos(dr) + cos(r) sin(dr)             *
 *                                                                            *
 *              sin(r) and cos(r) are computed using a lookup table, and      *
 *              sin(dr) and cos(dr) are computed using a small MacLaurin      *
 *              polynomial. This allows us to obtain sin(pi n) = 0 for        *
 *              integer n. The index r for the table is obtained by summing   *
 *              together x and 2^(53 - 8). By reading the lowest 8 bits of    *
 *              this sum we get the index for the lookup table. This assumes  *
 *              round-to-nearest IEEE-754 double precision addition.          *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/                                                         *
 *              tmpl_Double_Abs:                                              *
 *                  Computes the absolute value of a real number.             *
 *          src/math/auxiliary/                                               *
 *              tmpl_Double_SinPi_Maclaurin:                                  *
 *                  Computes sin(pi x) for small x using a MacLaurin series.  *
 *              tmpl_Double_CosPi_Maclaurin:                                  *
 *                  Computes cos(pi x) for small x using a MacLaurin series.  *
 *              tmpl_Double_SinPi_Remez:                                      *
 *                  Computes sin(pi x) via a Remez polynomial for |x| < 1/16. *
 *              tmpl_Double_SinPi_Rat_Remez:                                  *
 *                  Computes acos via a minimax approximation for |x| < 1/2.  *
 *              tmpl_Double_Mod_2:                                            *
 *                  Computes the real remainder after division by 2.          *
 *      Method:                                                               *
 *          Similar to the IEEE-754 version, but determine the index for the  *
 *          lookup table using casting, instead of round-to-nearest addition. *
 *  Notes:                                                                    *
 *  References:                                                               *
 *      1.) Maguire, Ryan (2024)                                              *
 *          tmpld                                                             *
 *          https://github.com/ryanmaguire/libtmpl_data                       *
 *                                                                            *
 *          Python library providing an implementation of the rational        *
 *          Remez exchange algorithm. The coefficients for the                *
 *          approximations used by this function were computed using this.    *
 *                                                                            *
 *      2.) Tasissa, Abiy (2019)                                              *
 *          Function Approximation and the Remez Exchange Algorithm.          *
 *          https://sites.tufts.edu/atasissa/files/2019/09/remez.pdf          *
 *                                                                            *
 *          Survey of the Remez polynomial and Remez exchange algorithm,      *
 *          including an excellent discussion on the rational Remez exchange  *
 *          algorithm. The implementation in tmpld is based on these notes.   *
 *                                                                            *
 *      3.) Abramowitz, Milton and Stegun, Irene (1964)                       *
 *          Handbook of Mathematical Functions                                *
 *          Applied Mathematics Series Volume 55,                             *
 *          National Bureau of Standards                                      *
 *                                                                            *
 *          Standard reference for formulas on mathematical functions. The    *
 *          trigonometric functions are found in chapter 4 section 3.         *
 *                                                                            *
 *      4.) C23 standard (2024)                                               *
 *          ISO/IEC 9899:2024                                                 *
 *          Section 7.12.4.13, pages 247 - 248.                               *
 *                                                                            *
 *          The sinpi function was introduced to libm with the C23 standard.  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_nan_double.h:                                                    *
 *          Header file providing double precision NaN (Not-a-Number).        *
 *  3.) tmpl_math_constants.h:                                                *
 *          Header file providing pi and pi / 2.                              *
 *  4.) tmpl_ieee754_double.h:                                                *
 *          Header file where the tmpl_IEEE754_Double type is defined.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 25, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/12/27: Ryan Maguire                                                  *
 *      Rewrite of sinpi using IEEE-754 tricks and round-to-nearest addition. *
 *  2025/12/29: Ryan Maguire                                                  *
 *      Added docstring with comments, license, and references.               *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  TMPL_NAN macro found here which provides double precision NaN.            */
#include <libtmpl/include/nan/tmpl_nan_double.h>

/*  Mathematical constants like pi and pi / 2 are found here.                 */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  TMPL_HAS_IEEE754_DOUBLE macro and tmpl_IEEE754_Double type given here.    */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Forward declaration for the function, also found in tmpl_math.h.          */
extern double tmpl_Double_SinPi(const double x);

/*  Tell the compiler about the mod 2 function, used for argument reduction.  */
extern double tmpl_Double_Mod_2(const double x);

/******************************************************************************
 *                                   Tables                                   *
 ******************************************************************************/

/*  The values cos(pi * k / 128) and sin(pi * k / 128) for k = 0, 1, ..., 127.*/
extern const double tmpl_double_cospi_table[128];
extern const double tmpl_double_sinpi_table[128];

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Maclaurin series for sin(pi x) and cos(pi x), accurate for |x| < 2^-7.    */
#include "auxiliary/tmpl_cospi_maclaurin_double.h"
#include "auxiliary/tmpl_sinpi_maclaurin_double.h"

/*  Remez polynomial for sin(pi x), accurate for |x| < 2^-4.                  */
#include "auxiliary/tmpl_sinpi_remez_double.h"

/*  Rational minimax approximation for sin(pi x), accurate for |x| < 2^-1.    */
#include "auxiliary/tmpl_sinpi_rat_remez_double.h"

/*  Significantly faster, and more accurate near integers, using IEEE-754.    */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Computes sin(pi x) at double precision.                                   */
double tmpl_Double_SinPi(const double x)
{
    /*  We compute using the angle sum formula for sin(pi(r + dr)). Set aside *
     *  four variables for the right-hand side of that equation.              */
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
            return tmpl_double_pi * x;

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
     *  y + 2^45. Since floating point arithmetic rounds to nearest, the      *
     *  lowest 8 bits of shifted are equal to the most significant 8 bits of  *
     *  y rounded to nearest.                                                 *
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

    /*  shifted - shifter is equal to |x| mod 2 rounded to the nearest 2^-7.  *
     *  The dr factor is then just the difference. Compute this.              */
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

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Helper macro for C vs. C++ compatibility with casting.                    */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Computes sin(pi x) at double precision.                                   */
double tmpl_Double_SinPi(const double x)
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
            return tmpl_double_pi * x;

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
