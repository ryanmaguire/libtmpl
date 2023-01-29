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
 *                         tmpl_exp_pos_kernel_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes exp(x) for 1 < x < log(DBL_MAX).                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp_Pos_Kernel                                            *
 *  Purpose:                                                                  *
 *      Computes exp(x) for positive values, 1 < x < log(DBL_MAX).            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for exp(x).                           *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          The exponential of x.                                             *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Put x into the form x = ln(2)*k + r. Then:                        *
 *                                                                            *
 *              exp(x) = exp(ln(2)k + r)                                      *
 *                     = exp(ln(2^k))*exp(r)                                  *
 *                     = 2^k*exp(r)                                           *
 *                                                                            *
 *              with |r| < ln(2)/2. 2^k can be computed instantly by setting  *
 *              the exponent bit to k. exp(r) is computed as follows. Write:  *
 *                                                                            *
 *                       r = k/128 + t (since |r| < log(2), |k| < 89)         *
 *                  exp(r) = exp(k/128)*exp(t), |t| < 1/128                   *
 *                                                                            *
 *              exp(k/128) is computed via a table and exp(t) is computed     *
 *              using the degree 5 minimax polynomial computed from the Remez *
 *              exchange algorithm on the interval [-1/128, 1/128].           *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Double_Pow2 (tmpl_math.h):                                   *
 *              Computes a power of 2.                                        *
 *      Method:                                                               *
 *          Same as IEEE-754 method, but compute 2^k with tmpl_Double_Pow2.   *
 *  Notes:                                                                    *
 *      This function assumes the input x is not infinity, not NaN, and       *
 *      positive between 1 and log(DBL_MAX) ~= 709 for 64-bit double.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 07, 2022                                             *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline support is not requested.                */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A0 (+1.0000000000000000098676804486032581931971677454305E+00)
#define A1 (+1.0000000000000000077001514598996570259345221024298E+00)
#define A2 (+4.9999999999708980614478940658809472988077097967424E-01)
#define A3 (+1.6666666666585521370389353791249722847045340843435E-01)
#define A4 (+4.1666793819163332764129161759693899954112387250407E-02)
#define A5 (+8.3333564677959633974492787478109645751141070623399E-03)
#define TMPL_ONE_BY_128 (0.0078125)

/*  Check for IEEE-754 support. Significantly faster.                         */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing exp(x) for 1 < x < log(DBL_MAX).                   */
double tmpl_Double_Exp_Pos_Kernel(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double exp_w;

    /*  log(2) split into two components for extra precision.                 */
    const double ln_2_hi = 6.93147180369123816490e-01;
    const double ln_2_lo = 1.90821492927058770002e-10;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const double rcpr_ln_2 = 1.44269504088896338700e+00;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const unsigned int k = (unsigned int)(rcpr_ln_2*x + 0.5);
    const double kd = (double)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  Compute the value r by subtracting k*ln(2) from x.                    */
    const double hi = x - ln_2_hi*kd;
    const double lo = kd*ln_2_lo;
    const double r = hi - lo;

    /*  Split r into r = n/128 + t for an integer n and |t| < 1/128.          */
    const int r128 = (int)(128.0*r);

    /*  The indices range from -89 to + 89. Shift r128 by 89 to make it a     *
     *  positive index for the table.                                         */
    const int ind = r128 + 89;

    /*  Compute t = r - n/128.                                                */
    const double t = r - TMPL_ONE_BY_128*r128;

    /*  Compute exp(t) via the Remez Minimax polynomial. Peak error ~10^-17.  */
    exp_w.r = A0 + t*(A1 + t*(A2 + t*(A3 + t*(A4 + t*A5))));

    /*  Compute exp(n/128)*exp(t) using the table.                            */
    exp_w.r *= tmpl_double_exp_table[ind];

    /*  Compute exp(x) via 2^k * exp(n/128 + t).                              */
    exp_w.bits.expo += k & 0x7FF;
    return exp_w.r;
}
/*  End of tmpl_Double_Exp_Pos_Kernel.                                        */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for computing exp(x) for 1 < x < log(DBL_MAX).                   */
double tmpl_Double_Exp_Pos_Kernel(double x)
{
    /*  log(2) split into two components for extra precision.                 */
    const double ln_2_hi = 6.93147180369123816490e-01;
    const double ln_2_lo = 1.90821492927058770002e-10;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const double rcpr_ln_2 = 1.44269504088896338700e+00;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const signed int k = (signed int)(rcpr_ln_2*x + 0.5);
    const double kd = (double)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  Compute the value r by subtracting k*ln(2) from x.                    */
    const double hi = x - ln_2_hi*kd;
    const double lo = kd*ln_2_lo;
    const double r = hi - lo;

    /*  Split r into r = n/128 + t for an integer n and |t| < 1/128.          */
    const int r128 = (int)(128.0*r);

    /*  The indices range from -89 to + 89. Shift r128 by 89 to make it a     *
     *  positive index for the table.                                         */
    const int ind = r128 + 89;

    /*  Compute t = r - n/128.                                                */
    const double t = r - TMPL_ONE_BY_128*r128;

    /*  Compute exp(t) via the Remez Minimax polynomial. Peak error ~10^-17.  */
    const double exp_t = A0 + t*(A1 + t*(A2 + t*(A3 + t*(A4 + t*A5))));

    /*  Compute exp(x) via 2^k * exp(n/128) * exp(t).                         */
    return exp_t*tmpl_double_exp_table[ind]*tmpl_Double_Pow2(k);
}
/*  End of tmpl_Double_Exp_Pos_Kernel.                                        */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  Undefine all coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef TMPL_ONE_BY_128

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */
