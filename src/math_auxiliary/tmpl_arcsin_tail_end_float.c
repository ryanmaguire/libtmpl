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
 *                         tmpl_arcsin_tail_end_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes asin(x) for 1/2 <= |x| < 1 at single precision.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arcsin_Tail_End                                            *
 *  Purpose:                                                                  *
 *      Computes arcsin for 1/2 <= |x| < 1.                                   *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number with 1/2 <= |x| < 1.                                *
 *  Output:                                                                   *
 *      asin_x (float):                                                       *
 *          asin(x) to single precision.                                      *
 *  Called Functions:                                                         *
 *      src/math_auxiliary/                                                   *
 *          tmpl_Float_Arcsin_Aux_Rat_Remez:                                  *
 *              Computes a degree (10, 8) rational Remez approximation for    *
 *              (asin(x) - x) / x.                                            *
 *          tmpl_Float_Arcsin_Aux_Shifted_Rat_Remez:                          *
 *              Computes a degree (7, 6) rational Remez approximation for     *
 *              asin(x) centered about x = 5 / 8 on the interval [1/2, 3/4].  *
 *      src/math/                                                             *
 *          tmpl_Float_Sqrt:                                                  *
 *              Computes the square root of a number.                         *
 *  Method:                                                                   *
 *      asin(x) is odd, so we may reduce x to 1/2 <= x <= 1.                  *
 *      If 1/2 <= x < 3/4, a degree (3, 2) rational Remez approximation is    *
 *      used. For 3/4 <= x <= 1, we use the identity                          *
 *                                                                            *
 *          asin(x) = pi / 2 - 2 * asin(sqrt((1 - x) / 2))                    *
 *                                                                            *
 *      The auxiliary helper function computes a degree (6, 2) rational       *
 *      Remez approximation for the function                                  *
 *                                                                            *
 *                 asin(x) - x                                                *
 *          f(x) = -----------                                                *
 *                      x                                                     *
 *                                                                            *
 *      asin(x) can then be computed using                                    *
 *                                                                            *
 *          asin(x) = pi / 2 - 2 * (z + z * r(z))                             *
 *                                                                            *
 *      where z = sqrt((1 - x) / 2) and r is the rational Remez approximation *
 *      for f. For improved accuracy, we split pi into two parts              *
 *      pi = pi_hi + pi_lo and compute                                        *
 *                                                                            *
 *          asin(x) = pi_hi / 2 - 2 * (z + (z * r(z) - pi_lo / 4))            *
 *                                                                            *
 *      This final expression is returned.                                    *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision for 1/2 <= |x| <= 1. There are no    *
 *          checks that the input falls within these intervals.               *
 *  References:                                                               *
 *      1.) Maguire, Ryan (2024)                                              *
 *          tmpld                                                             *
 *          https://github.com/ryanmaguire/libtmpl_data                       *
 *                                                                            *
 *          Python library providing an implementation of the rational        *
 *          Remez exchange algorithm. The coefficients for the                *
 *          approximation used by this function were computed using this.     *
 *                                                                            *
 *      2.) Tasissa, Abiy (2019)                                              *
 *          Function Approximation and the Remez Exchange Algorithm.          *
 *          https://sites.tufts.edu/atasissa/files/2019/09/remez.pdf          *
 *                                                                            *
 *          Survey of the Remez polynomial and Remez exchange algorithm.      *
 *          The implementation in tmpld is based on these notes.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_math_constants.h:                                                *
 *          Provides common math constants like pi and e.                     *
 *  4.) tmpl_math.h:                                                          *
 *          Square root function declared here.                               *
 *  5.) tmpl_math_auxiliary.h:                                                *
 *          Function prototype / forward declaration found here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2023                                                   *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/10/30: Ryan Maguire                                                  *
 *      Rewrote to use the new auxiliary functions. Moved to math_auxiliary   *
 *      directory and replaced TMPL_STATIC_INLINE with TMPL_ALWAYS_INLINE.    *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Common math constants like pi / 2 found here.                             */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  The square root function is provided here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Function for computing asin(x) for 1/2 <= |x| <= 1.                       */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float
tmpl_Float_Arcsin_Tail_End(const float x)
TMPL_UNSEQUENCED
{
    /*  asin(x) is odd, for negative x use asin(x) = -asin(-x).               */
    if (x < 0.0F)
    {
        /*  There is a jump is the accuracy of the tail-end formula for asin  *
         *  that occurs around x = 5/8. The peak error is about 2 ULP instead *
         *  of 1. To improve the precision and speed we use a small rational  *
         *  Remez approximation on the interval [1/2, 3/4] for such x.        */
        if (x > -0.75F)
            return -tmpl_Float_Arcsin_Aux_Shifted_Rat_Remez(-x);

        /*  For larger x, use the reflection formula with sqrt((1 - |x|) / 2).*/
        else
        {
            /*  x is negative, we have (1 - |x|) / 2 = (1 + x) / 2.           */
            const float z_sq = 0.5F * (1.0F + x);
            const float z = tmpl_Float_Sqrt(z_sq);

            /*  Compute (asin(z) - z) / z using the helper function. Note,    *
             *  this takes in the square of z as the argument, not z.         */
            const float rat = tmpl_Float_Arcsin_Aux_Rat_Remez(z_sq);

            /*  For negative x, we have asin(x) = 2 * acos(z) - pi / 2, where *
             *  z = sqrt((1 + x) / 2). To improve the accuracy, we write pi   *
             *  as pi = pi_hi + pi_lo. Subtract off the lower bits of pi / 4  *
             *  from the rational approximation. Since this is scaled by 2    *
             *  after we compute acos(z), the net result is subtraction by    *
             *  the lower bits of pi / 2.                                     */
            const float low_bits = z * rat - tmpl_float_pi_by_four_lo;
            const float acos_z_minus_pi_by_four_lo = z + low_bits;
            return 2.0F * acos_z_minus_pi_by_four_lo - tmpl_float_pi_by_two_hi;
        }
    }

    /*  Positive x, compute asin(x) normally.                                 */
    else
    {
        /*  The spike in the error is symmetric, we need to handle [1/2, 3/4] *
         *  carefully to avoid the error getting above 1 ULP.                 */
        if (x < 0.75F)
            return tmpl_Float_Arcsin_Aux_Shifted_Rat_Remez(x);

        /*  For all other positive x, use the reflection formula.             */
        else
        {
            /*  For positive x we have (1 - |x|) / 2 = (1 - x) / 2.           */
            const float z_sq = 0.5F * (1.0F - x);
            const float z = tmpl_Float_Sqrt(z_sq);

            /*  Compute the Remez approximation for (asin(z) - z) / z.        */
            const float rat = tmpl_Float_Arcsin_Aux_Rat_Remez(z_sq);

            /*  We have asin(x) = pi / 2 - 2 * acos(z). Like the negative     *
             *  case, we improve the accuracy by writing pi = pi_hi + pi_lo.  */
            const float low_bits = z * rat - tmpl_float_pi_by_four_lo;
            const float acos_z_minus_pi_by_four_lo = z + low_bits;
            return tmpl_float_pi_by_two_hi - 2.0F * acos_z_minus_pi_by_four_lo;
        }
    }
}
/*  End of tmpl_Float_Arcsin_Tail_End.                                        */
