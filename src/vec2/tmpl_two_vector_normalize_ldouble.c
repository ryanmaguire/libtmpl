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
 *                     tmpl_two_vector_normalize_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Normalize a non-zero vector to have length 1.                         *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_Normalize                                              *
 *  Purpose:                                                                  *
 *      Computes a unit vector parallel to the input.                         *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorLongDouble * const):                           *
 *          A point in the Euclidean plane.                                   *
 *  Output:                                                                   *
 *      u (tmpl_TwoVectorLongDouble):                                         *
 *          The vector P / || P ||, the unit vector in the direction of P.    *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Hypot:                                               *
 *              Compute the length of the vector (x, y).                      *
 *          tmpl_LDouble_Sqrt:                                                *
 *              Computes the square root of a real number.                    *
 *          tmpl_LDouble_Is_Inf:                                              *
 *              Determines if the input is positive or negative infinity.     *
 *          tmpl_LDouble_Is_NaN:                                              *
 *              Determines if the input is Not-a-Number.                      *
 *          tmpl_LDouble_Is_NaN_Or_Inf:                                       *
 *              Determines if the input is Not-a-Number or infinity.          *
 *  Method:                                                                   *
 *      Compute || P || and return P / || P ||. In the event that || P || is  *
 *      denormal / subnormal (in which case 1 / || P || will overflow), we    *
 *      first normalize the components of P to prevent this. Similarly if     *
 *      || P || overflows to infinity. If P is the zero vector or contains    *
 *      NaN in one of its components, the vector (NaN, NaN) is returned.      *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P is a valid *
 *          pointer to a 2D vector.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_ldouble.h:                                                  *
 *          The tmpl_TwoVectorLongDouble typedef is provided here.            *
 *  3.) tmpl_nan_ldouble.h:                                                   *
 *          Header file providing long double precision NaN (Not-a-Number).   *
 *  4.) tmpl_ieee754_ldouble.h:                                               *
 *          Header file where the tmpl_IEEE754_LDouble type is defined.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/12/21: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2023/01/01: Ryan Maguire                                                  *
 *      Moved float and long double versions to own files. Changed function   *
 *      to pass by address install of by value.                               *
 *  2025/05/13: Ryan Maguire                                                  *
 *      Added docstring and comments, added checks for denormal / subnormal   *
 *      numbers and checks for overflow / underflow.                          *
 ******************************************************************************/

/*  The TMPL_USE_INLINE macro is provided here.                               */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  TMPL_HAS_IEEE754_LDOUBLE macro and tmpl_IEEE754_LDouble type given here.  */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  TMPL_NANL macro found here which provides long double precision NaN.      */
#include <libtmpl/include/nan/tmpl_nan_ldouble.h>

/*  Prototype / forward declaration for the function.                         */
extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Normalize(const tmpl_TwoVectorLongDouble * const P);

/*  Tell the compiler about the hypotenuse function.                          */
extern long double tmpl_LDouble_Hypot(long double x, long double y);

/*  We can safely handle denormal numbers if IEEE-754 support is available.   */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT || \
    TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                   64-Bit Double / 128-Bit Double-Double                    *
 ******************************************************************************/

/*  The values 2^564 and 2^-514, to double-double precision, stored as macros.*
 *  2^564 is chosen since 564 = 512 + 52. The 2^52 factor will "normalize" a  *
 *  denormal / subnormal number, and the 2^512 part will make sure that the   *
 *  square of the value does not underflow, or become a denormal number. Thus *
 *  multiplying a non-zero denormal / subnormal number by 2^564 is guaranteed *
 *  to produce a number that will square to a normal number. 2^-514 is chosen *
 *  since 514 = 512 + 2, hence scaling a large number by 2^-512 guarantees    *
 *  the square of the product is less than DBL_MAX / 4, which means twice     *
 *  this value is less than DBL_MAX / 2, so no overflow will occur.           */
#define TMPL_BIG_SCALE (+6.0383398797144661635864873295812302254671E+169)
#define TMPL_SMALL_SCALE (+1.8645851828000516858227413288657334593441E-155)

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                              128-Bit Quadruple                             *
 ******************************************************************************/

/*  For 128-bit quadruple, the exponent has 15 bits, meaning the max value is *
 *  2^(2^14 - 1), so our scale factor should be the square root of this, or   *
 *  2^2^13 = 2^8192. As was the case about with 64-bit double, we need a      *
 *  larger value to account for normalizing a denormal number. 128-bit        *
 *  quadruples have a 112-bit mantissa, so we choose 2^(8192 + 112) = 2^8304. *
 *  For the small scale we choose 2^-(2^13 - 2) = 2^-8190. Doing this means   *
 *  the product of a large number with this number will square to something   *
 *  bounded by LDBL_MAX / 4, preventing overflow.                             */
#define TMPL_BIG_SCALE (5.6634881180294134530431951355845905739182358273E+2499L)
#define TMPL_SMALL_SCALE (2.29200483444355895702676549006060395744545621E-2467L)

#else

/******************************************************************************
 *                               80-Bit Extended                              *
 ******************************************************************************/

/*  80-bit extended also has a 15-bit exponent, so the small scale is the     *
 *  same as the one for 128-bit quadruple: 2^-8190 = 2^-(2^13 - 2). The       *
 *  mantissa is 63-bits, not 112, so the big scale is 2^(2^13 + 63) = 2^8255. */
#define TMPL_BIG_SCALE (2.0120751706647203082820834423161892963769886319E+2485L)
#define TMPL_SMALL_SCALE (2.29200483444355895702676549006060395744545621E-2467L)

#endif
/*  End of double / double-double vs. extended vs. quadrule.                  */

/*  Tell the compiler about the sqrt function. If we need to scale the input  *
 *  components because they are too large, then after the scaling we may      *
 *  safely compute || P || vis sqrt(x*x + y*y), saving a call to the hypot    *
 *  function.                                                                 */
extern long double tmpl_LDouble_Sqrt(long double x);

/*  Function for normalizing a non-zero vector to length 1.                   */
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Normalize(const tmpl_TwoVectorLongDouble * const P)
{
    /*  Variable for the output, the unit vector in the direction of P.       */
    tmpl_TwoVectorLongDouble u;

    /*  Union of a long double and the bits representing it. Used for || P ||.*/
    tmpl_IEEE754_LDouble wnorm;

    /*  Variable for 1 / || P ||, scaling P by this creates a unit vector.    */
    long double rcpr_norm;

    /*  Set the long double part of the word to the norm of P, || P ||.       */
    wnorm.r = tmpl_LDouble_Hypot(P->dat[0], P->dat[1]);

    /*  Make sure we can divide by wnorm. If the exponent bits are zero, then *
     *  either || P || = 0 (in which case the output is NaN), or || P || is a *
     *  subnormal / denormal number and needs to be normalized.               */
    if (TMPL_LDOUBLE_EXPO_BITS(wnorm) == 0x00U)
    {
        /*  If the input is the zero vector, normalization is undefined.      */
        if (wnorm.r == 0.0L)
        {
            /*  The unit vector for (0, 0) is (NaN, NaN). Return this.        */
            u.dat[0] = TMPL_NANL;
            u.dat[1] = TMPL_NANL;
            return u;
        }

        /*  If we get here, then P is not the zero vector but the components  *
         *  are so small that || P || is a denormal number. We need to scale  *
         *  the components of P by a large number to ensure that we can       *
         *  compute 1 / || P || without overflowing to infinity.              */
        u.dat[0] = P->dat[0] * TMPL_BIG_SCALE;
        u.dat[1] = P->dat[1] * TMPL_BIG_SCALE;

        /*  Recompute the norm. Since the x and y values are now large enough *
         *  that their squares will not underflow, we may compute the norm    *
         *  via sqrt(x^2 + y^2). Note, since the largest component of the     *
         *  input is denormal, if the first n bits of its mantissa are zero,  *
         *  then sqrt(2) times this number will only be accurate to roughly   *
         *  2^-(N-n) relative error, where N is the number of bits in the     *
         *  mantissa. Using 80-bit extended as an example, where N = 63, if   *
         *  if the components of P are 2^-16445, which is the smallest        *
         *  possible non-zero extended precision denormal number, then the    *
         *  calculation sqrt(2) * 2^-16445 will produce 2^-16445. That is,    *
         *  multiplying by sqrt(2) does not change the result, and this will  *
         *  result in horrible precision loss. This is because sqrt(2) is     *
         *  less than 1.5, and hence the calculation sqrt(2) * 2^-16445 will  *
         *  will round down to 2^-16445, since all of the mantissa bits of    *
         *  2^-16445 are being used as the "denormal exponent" part of the    *
         *  word. To avoid this we assume that the wnorm calculation above is *
         *  mostly junk, and recompute it using the scaled components in u.   */
        wnorm.r = tmpl_LDouble_Sqrt(u.dat[0] * u.dat[0] + u.dat[1] * u.dat[1]);

        /*  The norm is now large enough that the reciprocal can be computed. *
         *  That is, wnorm.r is no longer a denormal number.                  */
        rcpr_norm = 1.0L / wnorm.r;

        /*  The unit normal can now be computed by scaling the components by  *
         *  the reciprocal of the norm.                                       */
        u.dat[0] *= rcpr_norm;
        u.dat[1] *= rcpr_norm;
        return u;
    }

    /*  The tmpl_LDouble_Hypot function safely handles large numbers, meaning *
     *  || P || can be computed even if the components are close to LDBL_MAX, *
     *  the largest representable long double. If both components are set to  *
     *  LDBL_MAX, then || P || = sqrt(2) * LDBL_MAX, which will overflow. We  *
     *  can still normalize such a vector by first scaling the components of  *
     *  P so that the norm will not overflow.                                 */
    if (TMPL_LDOUBLE_EXPO_BITS(wnorm) == TMPL_LDOUBLE_NANINF_EXP)
    {
        /*  Words for the x and y components of P.                            */
        tmpl_IEEE754_LDouble wx, wy;

        /*  If one of the components of P is Not-a-Number (NaN), then the     *
         *  norm will be NaN as well. In this case the unit normal is set to  *
         *  the vector (NaN, NaN).                                            */
        if (TMPL_LDOUBLE_IS_NAN(wnorm))
        {
            u.dat[0] = TMPL_NANL;
            u.dat[1] = TMPL_NANL;
            return u;
        }

        /*  If either of the x or y components of P are infinite, we cannot   *
         *  normalize the input. Check for this, grab the components of P and *
         *  store them in the long double part of the words wx and wy.        */
        wx.r = P->dat[0];
        wy.r = P->dat[1];

        /*  Check for infinity, return NaN if this is the case.               */
        if (TMPL_LDOUBLE_IS_INFINITY(wx) || TMPL_LDOUBLE_IS_INFINITY(wy))
        {
            u.dat[0] = TMPL_NANL;
            u.dat[1] = TMPL_NANL;
            return u;
        }

        /*  Neither of the components are infinity, we can scale them to be   *
         *  much smaller. This will prevent the norm from overflowing.        */
        u.dat[0] = P->dat[0] * TMPL_SMALL_SCALE;
        u.dat[1] = P->dat[1] * TMPL_SMALL_SCALE;

        /*  Recompute the norm. Since we have scaled the components (and      *
         *  we checked for NaNs and infinities), this will be finite. We have *
         *  also ensured the x^2 + y^2 will not overflow, so we can compute   *
         *  || P || via tmpl_LDouble_Sqrt saving a call to tmpl_LDouble_Hypot.*/
        wnorm.r = tmpl_LDouble_Sqrt(u.dat[0] * u.dat[0] + u.dat[1] * u.dat[1]);

        /*  The norm is positive and normal meaning we can compute the        *
         *  reciprocal. This will be the final scale factor for u.            */
        rcpr_norm = 1.0L / wnorm.r;

        /*  The unit normal can now be computed by scaling the components by  *
         *  the reciprocal of the norm.                                       */
        u.dat[0] *= rcpr_norm;
        u.dat[1] *= rcpr_norm;
        return u;
    }

    /*  It is more than likely that || P || was computed without issue, and   *
     *  that the output is a positive normal number. The reciprocal can be    *
     *  computed without issue and u = P / || P || can be carried out safely. */
    rcpr_norm = 1.0L / wnorm.r;
    u.dat[0] = P->dat[0] * rcpr_norm;
    u.dat[1] = P->dat[1] * rcpr_norm;
    return u;
}
/*  End of tmpl_2DLDouble_Normalize.                                          */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  The value 2^-128, used for scaling vectors with large components.         */
#define TMPL_SMALL_SCALE (+2.9387358770557187699218413430556141945467E-39L)

/*  Without IEEE-754 support we can still check for NaN and infinity using    *
 *  the following functions. These functions are small enough to inline,      *
 *  check for inline support.                                                 */
#if TMPL_USE_INLINE == 1

#include <libtmpl/include/inline/math/tmpl_is_inf.h>
#include <libtmpl/include/inline/math/tmpl_is_nan.h>
#include <libtmpl/include/inline/math/tmpl_is_nan_or_inf.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  C89 compatible Booleans provided here.                                    */
#include <libtmpl/include/tmpl_bool.h>

/*  Lacking inline support, provide the prototype / forward declaration for   *
 *  the functions. That is, tell the compiler they exist.                     */
extern tmpl_Bool tmpl_LDouble_Is_Inf(long double x);
extern tmpl_Bool tmpl_LDouble_Is_NaN(long double x);
extern tmpl_Bool tmpl_LDouble_Is_NaN_Or_Inf(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Function for normalizing a non-zero vector to length 1.                   */
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Normalize(const tmpl_TwoVectorLongDouble * const P)
{
    /*  Variable for the output, the unit vector in the direction of P.       */
    tmpl_TwoVectorLongDouble u;

    /*  The Euclidean, or L2 norm, of the input, || P ||.                     */
    long double norm = tmpl_LDouble_Hypot(P->dat[0], P->dat[1]);

    /*  Variable for 1 / || P ||, scaling P by this creates a unit vector.    */
    long double rcpr_norm;

    /*  Avoid division-by-zero. The zero vector cannot be normalized.         */
    if (norm == 0.0L)
    {
        /*  We set the unit vector for (0, 0) to (NaN, NaN). Return this.     */
        u.dat[0] = TMPL_NANL;
        u.dat[1] = TMPL_NANL;
        return u;
    }

    /*  If the input vector contains NaN as one of its components, the norm   *
     *  will be NaN. Similarly if one of the components is infinite, then the *
     *  norm will be as well. If the components are both very big, say equal  *
     *  to FLT_MAX, then the norm will be || P || = sqrt(2) * FLT_MAX, which  *
     *  will overflow to infinity. We need to handle these cases, check if    *
     *  the norm is either infinity or NaN.                                   */
    if (tmpl_LDouble_Is_NaN_Or_Inf(norm))
    {
        /*  If one of the components of P is Not-a-Number (NaN), then the     *
         *  norm will be NaN as well. In this case the unit normal is set to  *
         *  the vector (NaN, NaN).                                            */
        if (tmpl_LDouble_Is_NaN(norm))
        {
            u.dat[0] = TMPL_NANL;
            u.dat[1] = TMPL_NANL;
            return u;
        }

        /*  Check for infinity, return NaN if this is the case.               */
        if (tmpl_LDouble_Is_Inf(P->dat[0]) || tmpl_LDouble_Is_Inf(P->dat[1]))
        {
            u.dat[0] = TMPL_NANL;
            u.dat[1] = TMPL_NANL;
            return u;
        }

        /*  Neither of the components are infinity, we can scale them to be   *
         *  much smaller. This will prevent the norm from overflowing.        */
        u.dat[0] = P->dat[0] * TMPL_SMALL_SCALE;
        u.dat[1] = P->dat[1] * TMPL_SMALL_SCALE;

        /*  Recompute the norm. Since we have scaled the components (and      *
         *  we checked for NaNs and infinities), this will be finite.         */
        norm = tmpl_LDouble_Hypot(u.dat[0], u.dat[1]);

        /*  The norm is positive and normal meaning we can compute the        *
         *  reciprocal. This will be the final scale factor for u.            */
        rcpr_norm = 1.0L / norm;

        /*  The unit normal can now be computed by scaling the components by  *
         *  the reciprocal of the norm.                                       */
        u.dat[0] *= rcpr_norm;
        u.dat[1] *= rcpr_norm;
        return u;
    }

    /*  It is more than likely that || P || was computed without issue, and   *
     *  that the output is a positive normal number. The reciprocal can be    *
     *  computed without issue and u = P / || P || can be carried out safely. */
    rcpr_norm = 1.0L / norm;
    u.dat[0] = P->dat[0] * rcpr_norm;
    u.dat[1] = P->dat[1] * rcpr_norm;
    return u;
}
/*  End of tmpl_2DLDouble_Normalize.                                          */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_BIG_SCALE
#undef TMPL_SMALL_SCALE
