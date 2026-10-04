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
 *                           tmpl_exp_kernel_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes exp(x) for log(DBL_MIN) < x < log(DBL_MAX).                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp_Kernel                                                *
 *  Purpose:                                                                  *
 *      Computes exp(x) for log(DBL_MIN) < x < log(DBL_MAX).                  *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number, the argument for exp(x).                           *
 *      shift (const double):                                                 *
 *          The shift factor to avoid underflow or overflow.                  *
 *      scale (const double):                                                 *
 *          The scale factor used to cancel the shift factor.                 *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          The exponential of x.                                             *
 *  IEEE-754 Version with 64-Bit Integers:                                    *
 *      Called Functions:                                                     *
 *          include/inline/floatint/                                          *
 *              tmpl_UInt64_To_Double:                                        *
 *                  Performs a bit-cast of a 64-bit integer to a double.      *
 *              tmpl_Double_To_UInt64:                                        *
 *                  Performs a bit-cast of a double to a 64-bit integer.      *
 *          src/split/                                                        *
 *              tmpl_Double_Guarded_Add:                                      *
 *                  Performs floating-point addition while guarding the       *
 *                  variables from aggressive optimizations.                  *
 *              tmpl_Double_Guarded_Subtract:                                 *
 *                  Performs floating-point subtraction while guarding the    *
 *                  variables from aggressive optimizations.                  *
 *          src/math_auxiliary/                                               *
 *              tmpl_Double_Expm1_Remez_Small:                                *
 *                  Computes exp(x) - 1 for small x using a Remez polynomial. *
 *      Method:                                                               *
 *          The exp kernel function computes exp(x) using                     *
 *                                                                            *
 *              exp(x) = exp(ln(2) * x / ln(2))                               *
 *                     = 2^(x / ln(2))                                        *
 *                     = 2^z                                                  *
 *                     = 2^(shift + round7(z) + z - round7(z) - shift)        *
 *                     = scale * 2^(shift + round7(z)) * 2^(z - round7(z))    *
 *                                                                            *
 *          where z = x / ln(2), round7(z) = round(128 * z) / 128 (that is, z *
 *          rounded to the 7th bit past the binary point), and                *
 *          scale = 2^(-shift). Splitting round7(z) into the integer part     *
 *          z_round_hi and the fractional part z_round_lo, we have            *
 *                                                                            *
 *              2^(shift + round7(z)) = 2^(shift + z_round_hi + z_round_lo)   *
 *                                    = 2^(shift + z_round_hi) * z^z_round_lo *
 *                                                                            *
 *          2^z_round_lo is computed using a lookup table. Since z_round_lo   *
 *          only has bits in the 1/2 through 1/128 place, the index for this  *
 *          table can be computed by treating the bits that represent         *
 *          z_round_lo as an integer written in binary.                       *
 *                                                                            *
 *          Since shift + z_round_hi is an integer, 2^(shift + z_round_hi) is *
 *          an integer power of two. We can compute this by setting the       *
 *          exponent bits of a double to this value and clearing the sign and *
 *          mantissa bits.                                                    *
 *                                                                            *
 *          Lastly, to compute 2^(z - round7(z)) we use                       *
 *                                                                            *
 *              2^(z - round7(z)) = 2^(x / ln(2) - round7(x / ln(2)))         *
 *                                = exp(x - ln(2) * round7(x / ln(2)))        *
 *                                = exp(r)                                    *
 *                                                                            *
 *          where r = x - ln(2) * round7(x / ln(2)), and thus |r| <= 1 / 256. *
 *          exp(r) is computed using a Remez polynomial for the expm1         *
 *          function, expm1(r) = exp(r) - 1, meaning exp(r) = 1 + expm1(r).   *
 *                                                                            *
 *          Computing 2^(shift + z_round_hi) * 2^z_round_lo * exp(r) gives us *
 *          exp(x) * 2^shift. The scale factor provided is required to be     *
 *          2^-shift to cancel this. Scaling the final result by this scale   *
 *          factor then gives us exp(x).                                      *
 *  IEEE-754 Version without 64-Bit Integers:                                 *
 *      Called Functions:                                                     *
 *          src/split/                                                        *
 *              tmpl_Double_Guarded_Add:                                      *
 *                  Performs floating-point addition while guarding the       *
 *                  variables from aggressive optimizations.                  *
 *              tmpl_Double_Guarded_Subtract:                                 *
 *                  Performs floating-point subtraction while guarding the    *
 *                  variables from aggressive optimizations.                  *
 *          src/math_auxiliary/                                               *
 *              tmpl_Double_Expm1_Remez_Small:                                *
 *                  Computes exp(x) - 1 for small x using a Remez polynomial. *
 *      Method:                                                               *
 *          Identical to the prior method, but we set the bits of a double    *
 *          manually rather than type-punning using 64-bit integers.          *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/                                                         *
 *              tmpl_Double_Pow2:                                             *
 *                  Computes an integer power of 2.                           *
 *          src/math_auxiliary/                                               *
 *              tmpl_Double_Expm1_Remez_Small:                                *
 *                  Computes exp(x) - 1 for small x using a Remez polynomial. *
 *      Method:                                                               *
 *          Similar to the IEEE-754 method, but we compute 2^k using the      *
 *          tmpl_Double_Pow2 function.                                        *
 *  Notes:                                                                    *
 *      1.) There are no checks for NaN or infinity.                          *
 *                                                                            *
 *      2.) This function assumes log(DBL_MIN) < x < log(DBL_MAX).            *
 *                                                                            *
 *      3.) Accurate to double precision, within 1 ULP of glibc. This         *
 *          includes inputs that produce denormal outputs.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_ALWAYS_INLINE macro.                  *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_ieee754_double.h:                                                *
 *          Provides the typedef for the IEEE-754 union used for type punning.*
 *  4.) tmpl_math_auxiliary.h:                                                *
 *          Header file where the function declaration is found.              *
 *  5.) tmpl_math_constants.h:                                                *
 *          Header with common math constants like pi, sqrt(2), and ln(2).    *
 *  6.) tmpl_math_tables.h:                                                   *
 *          Contains a lookup table for the exponential function.             *
 *  7.) tmpl_split.h:                                                         *
 *          Provides functions to protect against aggressive optimizations.   *
 *  8.) tmpl_inttype.h:                                                       *
 *          Contains the tmpl_UInt64 typedef.                                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 07, 2022                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/30: Ryan Maguire                                                  *
 *      Changed Maclaurin series to Remez Minimax polynomial. Fixed comments. *
 *  2026/10/01: Ryan Maguire                                                  *
 *      Merged the positive and negative exp kernels into one function.       *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Location of the TMPL_HAS_IEEE754_DOUBLE macro and IEEE data type.         */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Common math constants like ln(2) found here.                              */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  Lookup tables provided here.                                              */
#include <libtmpl/include/tmpl_math_tables.h>

/*  Guarded floating-point operations and splitting functions found here.     */
#include <libtmpl/include/tmpl_split.h>

/*  With fixed-width 64-bit integers and 64-bit double we can speed this up.  */
#if TMPL_HAS_FLOATINT64 == 1

/******************************************************************************
 *                    IEEE-754 Version with 64-Bit Integers                   *
 ******************************************************************************/

/*  Fixed-width integers found here.                                          */
#include <libtmpl/include/tmpl_inttype.h>

/*  Functions for converting from int to float and back.                      */
#include <libtmpl/include/inline/floatint/tmpl_uint64_to_double.h>
#include <libtmpl/include/inline/floatint/tmpl_double_to_uint64.h>

/*  Function for computing exp(x) for log(DBL_MIN) < x < log(DBL_MAX).        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Exp_Kernel(const double x,
                       const double shift,
                       const double scale)
TMPL_UNSEQUENCED
{
    /*  ln(2) with extra precision using two doubles. ln_2_hi is ln(2)        *
     *  rounded down to 27 bits in the mantissa, and ln_2_lo is the remainder.*/
    const double ln_2_hi = +6.93147182464599609375000000000000000000000000E-01;
    const double ln_2_lo = -1.90465429995776787854182343192449986563974475E-09;

    /*  We compute the exponential function using                             *
     *                                                                        *
     *      exp(x) = exp(ln(2) x / ln(2))                                     *
     *             = 2^(x / ln(2))                                            *
     *             = 2^z                                                      *
     *                                                                        *
     *  where z = x / ln(2). 2^z is compute by writing                        *
     *                                                                        *
     *      z = round7(z) + (z - round7(z))                                   *
     *                                                                        *
     *  where round7 rounds z to the nearest 7th bit past the binary point.   *
     *  That is, round7 rounds z to the nearest 1 / 128th. Thus we have       *
     *                                                                        *
     *      2^z = 2^(round7(z) + (z - round7(z)))                             *
     *          = 2^round7(z) * 2^(z - round7(z))                             *
     *                                                                        *
     *  Splitting round7(z) into an integer part z_round_hi and a fractional  *
     *  part z_round_lo, we can compute 2^round7(z) using                     *
     *                                                                        *
     *      2^round7(z) = 2^(z_round_hi + z_round_lo)                         *
     *                  = 2^z_round_hi * 2^z_round_lo                         *
     *                                                                        *
     *  Since z_round_hi is an integer, 2^z_round_hi can be computed by       *
     *  setting the exponent bits of a floating-point variable to correspond  *
     *  to this value, and then clearing the sign and mantissa bits. The      *
     *  exponent in a floating-point number has a bias, so we need to adjust  *
     *  z_round_hi by this. The bias for 64-bit double-precision numbers is   *
     *  2^10 - 1. To compute round7(z) we add 2^(52 - 7) to the input, which  *
     *  rounds off the fractional bits below 1 / 128. To account for the bias *
     *  we then add 2^10 - 1 to this. We need to also take into account       *
     *  the possibility of 2^round7(z) being a denormal number or overflowing *
     *  to infinity. To allow for this, we modify the computation slightly    *
     *  and use                                                               *
     *                                                                        *
     *      2^z = 2^round7(z) * 2^(z - round7(z))                             *
     *          = 2^(round7(z) + shift) * 2^(-shift + z - round7(z))          *
     *          = 2^(-shift) * 2^(round7(z) + shift) * 2^(z - round7(z))      *
     *          = scale * 2^(round7(z) + shift) * 2^(z - round7(z))           *
     *                                                                        *
     *  For negative x we use shift = +54 and hence scale = 2^-54. This shift *
     *  factor ensures that 2^(shift + z_round_hi) is never a denormal number *
     *  and therefore no precision is lost in the intermediate steps. For     *
     *  positive inputs we use shift = -1 and hence scale = 2. This simple    *
     *  subtraction means 2^(shift + z_round_hi) will never be infinite,      *
     *  removing the possibility of overflow in the intermediate steps.       *
     *                                                                        *
     *  The exact shift, -1 or +54, is provided as an input. The full shift   *
     *  for x is hence 2^(52 - 7) + 2^10 - 1 + shift. The scale factor, which *
     *  is 2^(-shift), is also provided as an input and applied at the end.   */
    const double full_shift = 3.5184372089855E+13 + shift;

    /*  We use exp(x) = 2^(x / ln(2)). Compute z = x / ln(2).                 */
    const double z = tmpl_double_rcpr_log_e_of_two * x;

    /*  Shift the input to clear out the lower bits of z. This will allow us  *
     *  to extract the integer part of z and the upper 7 bits past the binary *
     *  point, properly rounded, which we will then use to index our table.   */
    const double z_shift = tmpl_Double_Guarded_Add(z, full_shift);

    /*  Bit-cast the input to a 64-bit unsigned integer. z_round_lo is the    *
     *  lower 7 bits of this, and z_round_hi is the upper bits.               */
    const tmpl_UInt64 z_shift_as_uint64 = tmpl_Double_To_UInt64(z_shift);

    /*  2^(shift + z_round_hi) is computed by placing the bits for z_round_hi *
     *  in the exponent of a double-precision number and then clearing the    *
     *  mantissa and sign bits. 2^z_round_lo is computed using a lookup table.*
     *  The index for the lookup table is simply the binary bits used to      *
     *  represent z_round_lo. This is the lower 7 bits of the shifted z       *
     *  value, extract.                                                       */
    const tmpl_UInt64 index = z_shift_as_uint64 & 0x7F;

    /*  Kill off the lower 7 bits and shift what is left up to the exponent   *
     *  bits in order to compute 2^(shift + z_round_hi). The mantissa is      *
     *  52 bits wide, and the lower 7 bits correspond to z_round_lo. Thus we  *
     *  need to subtract off these bits and then shift up by 52 - 7 = 45.     */
    const tmpl_UInt64 expo_as_uint64 = (z_shift_as_uint64 - index) << 45;

    /*  Treating the bits for this 64-bit unsigned integer as a double will   *
     *  give us 2^(shift + z_round_hi).                                       */
    const double pow_2_z_round_hi = tmpl_UInt64_To_Double(expo_as_uint64);

    /*  Treating the bits of z_round_lo as a number written in binary gives   *
     *  us the index for the lookup table. 2^(round7(z) + shift) is then just *
     *  the product of the computed values.                                   */
    const double pow_2_z_round_lo = tmpl_double_pow_2_hi_table[index];
    const double two_pow = pow_2_z_round_hi * pow_2_z_round_lo;

    /*  Since z_round_lo = k / 128 for some 0 <= k < 128, 2^z_round_lo is not *
     *  representable to full precision by a double-precision number (except  *
     *  for when k = 0). To improve the precision, 2^z_round_lo is split      *
     *  into 2^hi * (1 + lo). 2^hi is 2^z_round_lo correctly rounded to a     *
     *  double-precision number. This was extracted in the previous line when *
     *  we computed two_pow. The tail end is also given in a lookup table,    *
     *  and the index is the same. Extract.                                   */
    const double two_pow_tail = tmpl_double_pow_2_lo_table[index];

    /*  To ensure the lower bits of x are not lost due to round off when we   *
     *  performed z = x / ln(2), we now switch back to working with x. We     *
     *  will compute                                                          *
     *                                                                        *
     *      2^(z - round7(z)) = 2^(x / ln(2) - round7(z))                     *
     *                        = 2^(x / ln(2) - ln(2) round7(z) / ln(2))       *
     *                        = 2^((x - ln(2) round7(z)) / ln(2))             *
     *                        = exp(x - ln(2) round7(z))                      *
     *                                                                        *
     *  This final expression, exp(x - ln(2) round7(z)), can be computed      *
     *  using a Remez polynomial for exp since the input is small. Compute    *
     *  round7(z) by subtracting the shift.                                   */
    const double z_round = tmpl_Double_Guarded_Subtract(z_shift, full_shift);

    /*  Compute r = x - ln(2) * round(x / ln(2)). This is the remainder from  *
     *  the round7 operation that we applied to z. The guarded subtract       *
     *  function is used to prevent aggressive compiler optimizations from    *
     *  ruining the difference.                                               *
     *                                                                        *
     *  Note that 1 <= |z_round| <= 1024 = 2^10 and z_round has at most 7     *
     *  bits past the binary point. This means z_round has at most 17         *
     *  significant bits and the lower 52 - 17 = 35 bits in the mantissa are  *
     *  zero. ln_2_hi has the upper 27 bits of ln(2), and the lower bits in   *
     *  this variable are also zero. Since 17 + 27 = 44 < 52, the product     *
     *  ln_2_hi * z_round is exact and there is no rounding error introduced. *
     *  Splitting x - ln(2) * round(x / ln(2)) into two parts allows us to    *
     *  increase the precision considerably.                                  */
    const double z_scaled_hi = z_round * ln_2_hi;
    const double z_scaled_lo = z_round * ln_2_lo;
    const double r_tmp = tmpl_Double_Guarded_Subtract(x, z_scaled_hi);
    const double r = tmpl_Double_Guarded_Subtract(r_tmp, z_scaled_lo);

    /*  Compute exp(r) - 1 using a Remez polynomial.                          */
    const double expm1_r = tmpl_Double_Expm1_Remez_Small(r);

    /*  We now have:                                                          *
     *                                                                        *
     *      two_pow * (1 + two_pow_tail) = 2^(round7(z) + shift)              *
     *                           expm1_r = exp(x - ln(2) * round7(z)) - 1     *
     *                                                                        *
     *  Recalling that scale = 2^(-shift), we obtain                          *
     *                                                                        *
     *      exp(x)  = scale * (1 + two_pow_tail) * two_pow * (1 + expm1_r)    *
     *             ~= scale * two_pow * (1 + two_pow_tail + expm1_r)          *
     *                                                                        *
     *  where we may discard two_pow_tail * expm1_r since this term is        *
     *  extremely small compared to 1 + two_pow_tail + expm1_r. Compute       *
     *  exp(x) using this final approximation.                                */
    const double small = two_pow_tail + expm1_r;
    return scale * (two_pow + two_pow * small);
}
/*  End of tmpl_Double_Exp_Neg_Kernel.                                        */

/*  Lacking 64-bit integers, but having 64-bit double (strange), use this.    */
#elif TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing exp(x) for log(DBL_MIN) < x < log(DBL_MAX).        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Exp_Kernel(const double x,
                       const double shift,
                       const double scale)
TMPL_UNSEQUENCED
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double pow_2_z_round_hi;
    unsigned int index, exponent_hi, exponent_lo;
    double small, pow_2_z_round_lo, two_pow_tail, two_pow;

    /*  The ln(2) factors, and the shift and scale factors are the same as    *
     *  the ones in the previous method.                                      */
    const double ln_2_hi = +6.93147182464599609375000000000000000000000000E-01;
    const double ln_2_lo = -1.90465429995776787854182343192449986563974475E-09;

    /*  We use exp(x) = 2^(x / ln(x)). Compute z = x / ln(x).                 */
    const double z = tmpl_double_rcpr_log_e_of_two * x;

    /*  This is the same shift used in the previous method. It is used to     *
     *  compute the index for the lookup tables and the exponent for the      *
     *  power of 2 that is used.                                              */
    const double full_shift = 3.5184372089855E+13 + shift;
    const double z_shift = tmpl_Double_Guarded_Add(z, full_shift);
    const double z_round = tmpl_Double_Guarded_Subtract(z_shift, full_shift);

    /*  Revert back to computing use exp directly via                         *
     *                                                                        *
     *      2^(z - round7(z)) = exp(x - ln(2) * round7(z))                    *
     *                                                                        *
     *  Compute r = x - ln(2) * round7(z).                                    */
    const double z_scaled_hi = z_round * ln_2_hi;
    const double z_scaled_lo = z_round * ln_2_lo;
    const double r_tmp = tmpl_Double_Guarded_Subtract(x, z_scaled_hi);
    const double r = tmpl_Double_Guarded_Subtract(r_tmp, z_scaled_lo);

    /*  exp(r) - 1 can be computed using a Remez polynomial.                  */
    const double expm1_r = tmpl_Double_Expm1_Remez_Small(r);

    /*  The index for the lookup tables is given by the lower 7 bits of the   *
     *  shifted number. Extract this bits.                                    */
    pow_2_z_round_hi.r = z_shift;
    index = pow_2_z_round_hi.bits.man3 & 0x7F;

    /*  Splitting round7(z) into the integer part z_round_hi and the          *
     *  fractional bits z_round_lo, we compute 2^z_round_lo = 2^hi(1 + lo)    *
     *  where 2^hi is 2^z_round_lo rounded to a double, and lo is used to     *
     *  increase the precision. Both of these values are given in tables.     */
    pow_2_z_round_lo = tmpl_double_pow_2_hi_table[index];
    two_pow_tail = tmpl_double_pow_2_lo_table[index];

    /*  2^(shift + z_round_hi) is computed by setting the exponent bits of    *
     *  double equal to shift + z_round_hi. Note, the bias is already         *
     *  included in z_round_hi so we do not need to add it again.             */
    exponent_lo = pow_2_z_round_hi.bits.man3 >> 7;
    exponent_hi = (pow_2_z_round_hi.bits.man2 & 0x7) << 9;

    /*  Compute the power of two.                                             */
    pow_2_z_round_hi.r = 0.0;
    pow_2_z_round_hi.bits.expo = (exponent_lo + exponent_hi) & 0x7FF;
    two_pow = pow_2_z_round_hi.r * pow_2_z_round_lo;

    /*  Combine everything to obtain exp(x).                                  */
    small = two_pow_tail + expm1_r;
    return scale * (two_pow + two_pow * small);
}
/*  End of tmpl_Double_Exp_Kernel.                                            */

#else
/*  Else for #if TMPL_HAS_FLOATINT64 == 1.                                    */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  TMPL_CAST macro provided here for casting with C vs. C++ compatibility.   */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  The tmpl_Double_Pow2 function is found here.                              */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing exp(x) for log(DBL_MIN) < x < log(DBL_MAX).        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Exp_Kernel(const double x,
                       const double shift,
                       const double scale)
TMPL_UNSEQUENCED
{
    /*  The ln(2) factors, and the shift and scale factors are the same as    *
     *  the ones in the previous method.                                      */
    const double ln_2_hi = +6.93147182464599609375000000000000000000000000E-01;
    const double ln_2_lo = -1.90465429995776787854182343192449986563974475E-09;

    /*  We use exp(x) = 2^(x / ln(x)). Compute z = x / ln(x).                 */
    const double z = tmpl_double_rcpr_log_e_of_two * x;

    /*  Variables for shifting and round z, computing powers of 2, and        *
     *  computing exp(x) using Remez polynomials.                             */
    double z_round, z_scaled_hi, z_scaled_lo, r, expm1_r;
    double two_pow, two_pow_hi, two_pow_lo, two_pow_tail, small;
    signed int z_scaled, index, exponent;

    /*  The portable method does not use the shift or scale inputs. Note,     *
     *  this means the portable method does not attempt to prevent underflow  *
     *  or overflow. If double is not implemented using the IEEE-754 format,  *
     *  then there is no attempt to try to detect such issues.                */
    (void)shift;
    (void)scale;

    /*  We want the 7 bits of z past the binary point in order to use this    *
     *  for the lookup table. To avoid using right-shift and bit-wise and     *
     *  with negative integers, we split the computation into two cases: z is *
     *  positive or z is negative.                                            */
    if (z > 0.0)
    {
        /*  For positive z, we simply round 128 * z to an integer and then    *
         *  extract the lower 7 bits. This is the index for the tables.       */
        z_scaled = TMPL_CAST(128.0 * z + 0.5, signed int);
        index = z_scaled & 0x7F;

        /*  The exponent for the power of two is given by the higher bits.    */
        exponent = z_scaled >> 7;
        z_round = TMPL_CAST(z_scaled, double) / 128.0;
        two_pow_hi = tmpl_Double_Pow2(exponent);
        two_pow_lo = tmpl_double_pow_2_hi_table[index];

        /*  For positive z we have                                            *
         *                                                                    *
         *      2^(z_round_hi + z_round_lo) = 2^z_round_hi * z_round_lo       *
         *                                                                    *
         *  Compute the product.                                              */
        two_pow = two_pow_hi * two_pow_lo;
    }

    else
    {
        /*  For negative z we flip the sign first and then extract the bits.  */
        z_scaled = TMPL_CAST(-128.0 * z + 0.5, signed int);
        index = z_scaled & 0x7F;
        exponent = -(z_scaled >> 7);
        z_round = -TMPL_CAST(z_scaled, double) / 128.0;
        two_pow_hi = tmpl_Double_Pow2(exponent);
        two_pow_lo = tmpl_double_pow_2_hi_table[index];

        /*  For negative z we have                                            *
         *                                                                    *
         *      2^(z_round_hi - z_round_lo) = 2^z_round_hi / z_round_lo       *
         *                                                                    *
         *  Compute the quotient.                                             */
        two_pow = two_pow_hi / two_pow_lo;
    }

    /*  2^z_round_lo is computed with extra precision by writing              *
     *  2^z_round_hi = 2^hi * (1 + lo). 2^hi has already been computed, the   *
     *  lo factor is also given by a table.                                   */
    two_pow_tail = tmpl_double_pow_2_lo_table[index];

    /*  Revert back to computing use exp directly via                         *
     *                                                                        *
     *      2^(z - round7(z)) = exp(x - ln(2) * round7(z))                    *
     *                                                                        *
     *  Compute r = x - ln(2) * round7(z).                                    */
    z_scaled_hi = z_round * ln_2_hi;
    z_scaled_lo = z_round * ln_2_lo;
    r = tmpl_Double_Guarded_Subtract(x, z_scaled_hi);
    r = tmpl_Double_Guarded_Subtract(r, z_scaled_lo);

    /*  Compute exp(r) - 1 using a Remez polynomial.                          */
    expm1_r = tmpl_Double_Expm1_Remez_Small(r);

    /*  Combine everything to obtain exp(x).                                  */
    small = two_pow_tail + expm1_r;
    return two_pow + two_pow * small;
}
/*  End of tmpl_Double_Exp_Kernel.                                            */

#endif
/*  End of #if TMPL_HAS_FLOATINT64 == 1.                                      */
