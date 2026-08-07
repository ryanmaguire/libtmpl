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
 *                          tmpl_arctan_simd_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-tangent function at double precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arctan                                                    *
 *  Purpose:                                                                  *
 *      Computes atan(x), the inverse tangent function.                       *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (double):                                                      *
 *          The arc-tangent of x.                                             *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Abs:                                                  *
 *              Computes the absolute value of a real number.                 *
 *  Method:                                                                   *
 *      Since atan is odd, reduce x to |x| and then use the formula           *
 *                                                                            *
 *                                       -           -                        *
 *                                      |    x - v    |                       *
 *              atan(x) - atan(v) = atan| ----------- |                       *
 *                                      |  1 + v * x  |                       *
 *                                       -           -                        *
 *                                                                            *
 *      v is selected based on the size of |x|:                               *
 *                                                                            *
 *          0 <= |x| < 7 / 16:                                                *
 *              v = 0                                                         *
 *          7 / 16 <= |x| < 39 / 16:                                          *
 *              v = 1                                                         *
 *          39 / 16 <= |x| < +inf                                             *
 *              v = +inf                                                      *
 *                                                                            *
 *      Note that in this final case, the limit as v -> +inf is used and      *
 *      hence the argument is -1 / x, which results in the asymptotic         *
 *      expansion for atan(x)                                                 *
 *                                                                            *
 *                               -   -                                        *
 *                    pi        | -1  |                                       *
 *          atan(x) = --- + atan| --- |                                       *
 *                     2        |  x  |                                       *
 *                               -   -                                        *
 *                                                                            *
 *      x = +/- infinity is allowed, in which case +/- pi/2 is returned.      *
 *      atan((|x| - v) / (1 + v * |x|)) is computed using a degree (8, 6)     *
 *      rational Remez approximation for (atan(z) - z) / z^3. Since this      *
 *      function is even, there are only 5 non-zero terms in the numerator    *
 *      and 4 non-zero terms in the denominator.                              *
 *  Error:                                                                    *
 *      Based on 100,000,000 samples with -100 < x < 100.                     *
 *          max relative error: 4.0352096078283783E-16                        *
 *          rms relative error: 7.6264247481226795E-17                        *
 *          max absolute error: 2.2204460492503131E-16                        *
 *          rms absolute error: 1.1561627547406510E-16                        *
 *      Values assume 100% accuracy of glibc and were computed using a CPU    *
 *      with AVX2 support and the flags -ffast-math and -march=native. Other  *
 *      SIMD instructions may produce errors of 3-4 ULP instead of 1-2 ULP.   *
 *  Notes:                                                                    *
 *      1.) There are no checks for NaN or infinity. Unit tests show that NaN *
 *          and inf behave as expected with GCC and Clang (output is NaN).    *
 *                                                                            *
 *      2.) There are no checks for subnormal / denormal numbers. Very small  *
 *          numbers will use the same rational Remez expansion as normal      *
 *          numbers. Since atan(x) = x to double-precision for such small     *
 *          numbers, the near-branchless method is considerably slower for    *
 *          subnormal / denormal inputs. This function is best used with      *
 *          ordinary values between. The scalar version of this function is   *
 *          optimized to handle subnormal numbers, but this comes with the    *
 *          cost of branching.                                                *
 *                                                                            *
 *      3.) The relative error for the near-branchless version is about 1 ULP *
 *          worse than the scalar version (see above).                        *
 *                                                                            *
 *      4.) With proper SIMD support (AVX2 or similar), the near-branchless   *
 *          version can get a noticeable speed boost. In a simple for-loop    *
 *          on an x86_64 CPU with AVX2 support, the vectorized version is     *
 *          about twice as fast.                                              *
 *                                                                            *
 *      5.) This file only compiles if the TMPL_USE_SIMD_FAST_MATH macro is   *
 *          set to 1 at build time. At the time of this writing, very few     *
 *          tested compilers can fully support the SIMD version. Compilers    *
 *          that do so include GCC 15+, Clang 22+, and MSVC 19+. All of these *
 *          need the appropriate flags set at build time, which are handled   *
 *          by both the Makefile and the CMakeLists. Use of the SIMD version  *
 *          requires an explicit option enabled at build time.                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_SIMD_DECL macro.                      *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 7, 2026                                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCTAN_SIMD_DOUBLE_H
#define TMPL_ARCTAN_SIMD_DOUBLE_H

/*  TMPL_SIMD_DECL found here.                                                */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype and the absolute value function provided here.         */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (-3.3333333333333305358836084977349729872904430493533E-01)
#define A01 (-4.3472492564907188177965728150161024261168368906390E-01)
#define A02 (-1.3334294488168034808508355015534558635497629568920E-01)
#define A03 (-2.4969904772119998931757372837712212615734027365186E-03)
#define A04 (+1.5379465545704744220665806416482539586246240054221E-04)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+1.9041747769465982800746104300605799324989704179751E+00)
#define B02 (+1.1139622723156282902092725441043929334082755003327E+00)
#define B03 (+1.9312676035659053034651584234732625248577722279674E-01)

/*  Polynomial helpers using Horner's method.                                 */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))
#define TMPL_DEN_EVAL(z) B00 + z * (B01 + z * (B02 + z * B03))

/*  Near branchless implementation of atan.                                   */
TMPL_SIMD_DECL
TMPL_CONST_FUNC
double tmpl_Double_Arctan(const double x)
TMPL_UNSEQUENCED
{
    /*  Variables for the argument, (x - v) / (1 + x * v), and its square.    */
    double arg, arg_sq, arg_num, arg_den;

    /*  Variables for the numerator and denominator of the rational Remez     *
     *  minimax approximation.                                                */
    double rat_num, rat_den;

    /*  Variables for the offset factor, atan(v), and the final output.       */
    double offset, out;

    /*  Following the ideas from other libraries, we use tan(pi / 8) and      *
     *  tan(3 pi / 8) as threshold values for the offset. Nearest multiples   *
     *  of 1 / 16 are used for simplicity.                                    */
    const double low = 7.0 / 16.0;
    const double high = 39.0 / 16.0;

    /*  atan is an odd function, compute |x| and work with that.              */
    const double abs_x = tmpl_Double_Abs(x);

    /*  Select the offset. This is done using a blend to avoid true branches. *
     *  The following expands to 0 <= |x| < 7 / 16 or 7 / 16 <= |x| < 39 / 16 *
     *  or 39 / 16 <= |x|. The corresponding offset is then selected.         */
    offset = (abs_x > low ? tmpl_double_pi_by_four : 0.0);
    offset = (abs_x > high ? tmpl_double_pi_by_two : offset);

    /*  A similar selection is made for the numerator of the argument. The    *
     *  argument is (|x| - v) / (1 + |x| * v), where v -> infinity is allowed.*/
    arg_num = (abs_x > low ? abs_x - 1.0 : abs_x);
    arg_num = (abs_x > high ? -1.0 : arg_num);

    /*  Finally, select the denominator for the expresion.                    */
    arg_den = (abs_x > low ? abs_x + 1.0 : 1.0);
    arg_den = (abs_x > high ? abs_x : arg_den);

    /*  The argument is the ratio of the two values.                          */
    arg = arg_num / arg_den;

    /*  The numerator and denominator for the rational Remez approximations   *
     *  are in terms of arg^2. Pre-compute this.                              */
    arg_sq = arg * arg;

    /*  Evaluate the numerator and denominator using Horner's method.         */
    rat_num = TMPL_NUM_EVAL(arg_sq);
    rat_den = TMPL_DEN_EVAL(arg_sq);

    /*  We have atan(x) = atan(v) + atan((x - v) / (1 + x * v)). atan(v) is   *
     *  given by the offset, and atan((x - v) / (1 + x * v)) can be obtained  *
     *  from the Remez expansion. This expansion is for (atan(z) - z) / z^3,  *
     *  meaning atan(z) can be computed from z + z^3 * num / den.             */
    out = offset + arg * (1.0 + arg_sq * rat_num / rat_den);

    /*  atan is odd, if the input is negative we need to negate the output.   */
    return (x < 0.0 ? -out : out);
}
/*  End of tmpl_Double_Arctan.                                                */

/*  Undefine everything to avoid collisions with other macros.                */
#include "../auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
