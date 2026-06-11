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
 *                          tmpl_arccos_simd_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-cosine function at double precision.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arccos                                                    *
 *  Purpose:                                                                  *
 *      Computes acos(x), the inverse cosine function.                        *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (double):                                                      *
 *          The arc-cosine of x.                                              *
 *  Called Functions:                                                         *
 *      __builtin_sqrt / sqrt:                                                *
 *          Compiler intrinsic provided by GCC and Clang. Computes the        *
 *          square root of a double-precision floating-point number.          *
 *          The MSVC compiler intrinsic "sqrt" is used on Windows.            *
 *  Method:                                                                   *
 *      The rational Remez approximation for acos(x) on [-0.5, 0.5],          *
 *      and 2 * asin(sqrt((1 - x) / 2)) on [0.5, 1.0] have the same           *
 *      coefficients. We can use this to create a near-branchless             *
 *      implementation as follows.                                            *
 *                                                                            *
 *      Set u = x^2 if |x| < 1 / 2, and (1 - |x|) / 2 otherwise. This         *
 *      can be made into a branchless operation by, say, GCC or Clang.        *
 *                                                                            *
 *      Compute P(u) and Q(u), the numerator and denominator for the          *
 *      rational Remez approximation. From this, compute both:                *
 *                                                                            *
 *          acos_small_x = pi / 2 - x * (1 + u * P(u) / Q(u))                 *
 *          acos_tail_x  = 2 * sqrt(u) * (1 + u * P(u) / Q(u))                *
 *                                                                            *
 *      Return acos_small_x if |x| < 0.5, acos_tail_x if 0.5 <= x <= 1, and   *
 *      pi - acos_tail_x if -1 <= x <= -0.5. This selection can also be made  *
 *      branchless. NaN is returned if |x| > 1. Depending on compiler flags   *
 *      used, the check for |x| > 1 may be the only branch produced. This     *
 *      check is done at the very end, within the return statement. SIMD      *
 *      versions may use blends here as well, meaning the entire routine      *
 *      is branchless.                                                        *
 *  Error:                                                                    *
 *      Based on 100,000,000 samples with -1 < x < 1.                         *
 *          max relative error: 4.3932830841569839E-16                        *
 *          rms relative error: 9.0168796252044438E-17                        *
 *          max absolute error: 4.4408920985006262E-16                        *
 *          rms absolute error: 1.5047330146850383E-16                        *
 *      Values assume 100% accuracy of glibc and were computed using a CPU    *
 *      with AVX2 support and the flags -ffast-math and -march=native. Other  *
 *      SIMD instructions may produce errors of 3-4 ULP instead of 2 ULP.     *
 *  Notes:                                                                    *
 *      1.) There are no checks for NaN or infinity. Unit tests show that NaN *
 *          and inf behave as expected with GCC and Clang (output is NaN).    *
 *                                                                            *
 *      2.) There are no checks for subnormal / denormal numbers. Very small  *
 *          numbers will use the same rational Remez expansion as normal      *
 *          numbers. Since acos(x) = pi / 2 to double-precision for such      *
 *          small numbers, the near-branchless method is considerably slower  *
 *          for subnormal / denormal inputs. This function is best used with  *
 *          ordinary values between -1 and 1. The scalar version of this      *
 *          function is optimized to handle subnormal numbers, but this comes *
 *          with the cost of branching.                                       *
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
 *          that do include GCC 15+, Clang 22+, and MSVC 19+. All of these    *
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
 *  3.) tmpl_nan_double.h:                                                    *
 *          Header providing double precision NaN (Not-a-Number).             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 26, 2026                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_SIMD_DOUBLE_H
#define TMPL_ARCCOS_SIMD_DOUBLE_H

/*  TMPL_SIMD_DECL found here.                                                */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  TMPL_NAN macro found here which provides double precision NaN.            */
#include <libtmpl/include/nan/tmpl_nan_double.h>

/*  Both pi and pi / 2 are needed for the implementation.                     */
extern const double tmpl_double_pi;
extern const double tmpl_double_pi_by_two;

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+1.6666666666666675172610409335401762495970069423667E-01)
#define A01 (-2.9647442738212244852684254810912673101657174481766E-01)
#define A02 (+1.6001969221867813049084016184632874497094695883901E-01)
#define A03 (-2.5510481570872249173776491491771394448907125511346E-02)
#define A04 (+2.6066097969323856113412749790103952111930280796716E-04)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (-2.2288465642924490579275829949790393075345284377974E+00)
#define B02 (+1.6952419643599424152439428142515867324057155650851E+00)
#define B03 (-5.0120096652328631713045487959099718175996563925832E-01)
#define B04 (+4.5088915315077310386265964807853660211534733521946E-02)

/*  Helper macros for evaluating polynomials using Horner's method.           */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))
#define TMPL_DEN_EVAL(z) B00 + z * (B01 + z * (B02 + z * (B03 + z * B04)))

/*  Near-branchless double-precision inverse cosine (acos equivalent).        */
TMPL_SIMD_DECL
TMPL_CONST_FUNC
double tmpl_Double_Arccos(const double x)
TMPL_UNSEQUENCED
{
    /*  The absolute value of the input. Modern compilers will produce a      *
     *  branchless instruction (for example by using a bit-mask or by using   *
     *  an fmax / fmin operation).                                            */
    const double abs_x = (x < 0.0 ? -x : x);

    /*  Arguments for the rational Remez expansion. For |x| < 0.5 we use x^2, *
     *  and for 0.5 <= |x| <= 1, we use (1 - |x|) / 2.                        */
    const double u_small = x * x;
    const double u_tail = 0.5 * (1.0 - abs_x);

    /*  Select the correct argument. Recent versions of GCC and Clang may     *
     *  make this branchless by using a blend operation, or similar.          */
    const double u = (abs_x >= 0.5 ? u_tail : u_small);

    /*  Use Horner's method to compute the numerator and denominator of the   *
     *  rational Remez expansion in terms of u.                               */
    const double p = TMPL_NUM_EVAL(u);
    const double q = TMPL_DEN_EVAL(u);

    /*  Both the small-value expansion and the tail-end formula are in terms  *
     *  of 1 + u * P(u) / Q(u). Compute this.                                 */
    const double s = 1.0 + u * (p / q);

    /*  For |x| < 0.5, the rational Remez approximation is for the function   *
     *  f(x) = -(arccos(x) + x - pi / 2) / x^3. Since f(x) ~= P(x^2) / Q(x^2) *
     *  we can compute arccos(x) from this.                                   */
    const double acos_small_x = tmpl_double_pi_by_two - x * s;

    /*  Avoid creating a branch, compute both the small value approximation   *
     *  and the tail-end one. The tail-end formula uses the expression        *
     *  2 * asin(sqrt((1 - x) / 2)), which needs the square root function.    *
     *  GCC, Clang, and MSVC provide this as a compiler intrinsic.            */
#ifdef _MSC_VER
    const double sqrt_u = sqrt(u);
#else
    const double sqrt_u = __builtin_sqrt(u);
#endif

    /*  The rest of the tail-end formula can be computed from the variables   *
     *  we have already created. If the input is negative, we need to use the *
     *  reflection formula acos(-x) = pi - acos(x).                           */
    const double acos_tail_x_pos = 2.0 * sqrt_u * s;
    const double acos_tail_x_neg = tmpl_double_pi - acos_tail_x_pos;

    /*  Make the selection for which tail-end formula to use. Since checking  *
     *  if x is negative can be performed by examining the sign bit of x,     *
     *  compilers may be able to make this a branchless operation.            */
    const double acos_tail_x = (x < 0.0 ? acos_tail_x_neg : acos_tail_x_pos);

    /*  The tail-end formula and the small-value expression have both been    *
     *  calculated. Make the final selection based on the size of |x|.        */
    const double out = (abs_x >= 0.5 ? acos_tail_x : acos_small_x);

    /*  Final check, for |x| > 1 return NaN. This usually does create a       *
     *  branch (GCC 16.1 and Clang 22.1 both do), but if the inputs are       *
     *  consistently within the domain of arccos (meaning |x| <= 1), then     *
     *  the branching does not hurt the vectorization at all. With certain    *
     *  compiler flags, this may be turned into a blend as well, removing the *
     *  possibility of branching.                                             */
    return (abs_x > 1.0 ? TMPL_NAN : out);
}
/*  End of tmpl_Double_Arccos.                                                */

/*  Undefine everything to avoid collisions with other macros.                */
#include "../auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
