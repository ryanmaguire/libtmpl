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
 *                           tmpl_arccos_simd_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-cosine function at single precision.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arccos                                                     *
 *  Purpose:                                                                  *
 *      Computes acos(x), the inverse cosine function.                        *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          The arc-cosine of x.                                              *
 *  Called Functions:                                                         *
 *      __builtin_sqrtf / sqrtf:                                              *
 *          Compiler intrinsic provided by GCC and Clang. Computes the        *
 *          square root of a single-precision floating-point number.          *
 *          The MSVC compiler intrinsic "sqrtf" is used on Windows.           *
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
 *      Based on 10,000,000 samples with -1 < x < 1.                          *
 *          max relative error: 2.5398855996172642E-07                        *
 *          rms relative error: 5.6840399642546608E-08                        *
 *          max absolute error: 4.7683715820312500E-07                        *
 *          rms absolute error: 9.5722760085168690E-08                        *
 *      Values assume 100% accuracy of glibc and were computed using a CPU    *
 *      with AVX2 support and the flags -ffast-math and -march=native. Other  *
 *      SIMD instructions may produce errors of 3-4 ULP instead of 2 ULP.     *
 *  Notes:                                                                    *
 *      1.) There are no checks for NaN or infinity. Unit tests show that NaN *
 *          and inf behave as expected with GCC and Clang (output is NaN).    *
 *                                                                            *
 *      2.) There are no checks for subnormal / denormal numbers. Very small  *
 *          numbers will use the same rational Remez expansion as normal      *
 *          numbers. Since acos(x) = pi / 2 to single-precision for such      *
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
 *  3.) tmpl_nan_float.h:                                                     *
 *          Header providing single-precision NaN (Not-a-Number).             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 11, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_SIMD_FLOAT_H
#define TMPL_ARCCOS_SIMD_FLOAT_H

/*  TMPL_SIMD_DECL found here.                                                */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  TMPL_NANF macro found here which provides single-precision NaN.           */
#include <libtmpl/include/nan/tmpl_nan_float.h>

/*  Both pi and pi / 2 are needed for the implementation.                     */
extern const float tmpl_float_pi;
extern const float tmpl_float_pi_by_two;

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.6666657332654782511630744878585859634321997276656E-01F)
#define A01 (-4.2035660448040502977938914900697450640872894337286E-02F)
#define A02 (-8.2125492968317658201629446415138054874693066700587E-03F)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (-7.0227698493007347430817019567204548858969498944150E-01F)

/*  Helper macros for evaluating polynomials using Horner's method.           */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * A02)
#define TMPL_DEN_EVAL(z) B00 + z * B01

/*  Near-branchless single-precision inverse cosine (acosf equivalent).       */
TMPL_SIMD_DECL
TMPL_CONST_FUNC
float tmpl_Float_Arccos(const float x)
TMPL_UNSEQUENCED
{
    /*  The absolute value of the input. Modern compilers will produce a      *
     *  branchless instruction (for example by using a bit-mask or by using   *
     *  an fmax / fmin operation).                                            */
    const float abs_x = (x < 0.0F ? -x : x);

    /*  Arguments for the rational Remez expansion. For |x| < 0.5 we use x^2, *
     *  and for 0.5 <= |x| <= 1, we use (1 - |x|) / 2.                        */
    const float u_small = x * x;
    const float u_tail = 0.5F * (1.0F - abs_x);

    /*  Select the correct argument. Recent versions of GCC and Clang may     *
     *  make this branchless by using a blend operation, or similar.          */
    const float u = (abs_x >= 0.5F ? u_tail : u_small);

    /*  Use Horner's method to compute the numerator and denominator of the   *
     *  rational Remez expansion in terms of u.                               */
    const float p = TMPL_NUM_EVAL(u);
    const float q = TMPL_DEN_EVAL(u);

    /*  Both the small-value expansion and the tail-end formula are in terms  *
     *  of 1 + u * P(u) / Q(u). Compute this.                                 */
    const float s = 1.0F + u * (p / q);

    /*  For |x| < 0.5, the rational Remez approximation is for the function   *
     *  f(x) = -(arccos(x) + x - pi / 2) / x^3. Since f(x) ~= P(x^2) / Q(x^2) *
     *  we can compute arccos(x) from this.                                   */
    const float acos_small_x = tmpl_float_pi_by_two - x * s;

    /*  Avoid creating a branch, compute both the small value approximation   *
     *  and the tail-end one. The tail-end formula uses the expression        *
     *  2 * asin(sqrt((1 - x) / 2)), which needs the square root function.    *
     *  GCC, Clang, and MSVC provide this as a compiler intrinsic.            */
#ifdef _MSC_VER
    const float sqrt_u = sqrtf(u);
#else
    const float sqrt_u = __builtin_sqrtf(u);
#endif

    /*  The rest of the tail-end formula can be computed from the variables   *
     *  we have already created. If the input is negative, we need to use the *
     *  reflection formula acos(-x) = pi - acos(x).                           */
    const float acos_tail_x_pos = 2.0F * sqrt_u * s;
    const float acos_tail_x_neg = tmpl_float_pi - acos_tail_x_pos;

    /*  Make the selection for which tail-end formula to use. Since checking  *
     *  if x is negative can be performed by examining the sign bit of x,     *
     *  compilers may be able to make this a branchless operation.            */
    const float acos_tail_x = (x < 0.0F ? acos_tail_x_neg : acos_tail_x_pos);

    /*  The tail-end formula and the small-value expression have both been    *
     *  calculated. Make the final selection based on the size of |x|.        */
    const float out = (abs_x >= 0.5F ? acos_tail_x : acos_small_x);

    /*  Final check, for |x| > 1 return NaN. This usually does create a       *
     *  branch (GCC 16.1 and Clang 22.1 both do), but if the inputs are       *
     *  consistently within the domain of arccos (meaning |x| <= 1), then     *
     *  the branching does not hurt the vectorization at all. With certain    *
     *  compiler flags, this may be turned into a blend as well, removing the *
     *  possibility of branching.                                             */
    return (abs_x > 1.0F ? TMPL_NANF : out);
}
/*  End of tmpl_Float_Arccos.                                                 */

/*  Undefine everything to avoid collisions with other macros.                */
#include "../auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
