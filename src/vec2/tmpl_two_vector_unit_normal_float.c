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
 *                     tmpl_two_vector_unit_normal_float                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Normalize a non-zero vector to have length 1.                         *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DFloat_Unit_Normal                                              *
 *  Purpose:                                                                  *
 *      Computes a unit vector parallel to the input.                         *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorFloat * const):                                *
 *          A point in the Euclidean plane.                                   *
 *  Output:                                                                   *
 *      u (tmpl_TwoVectorFloat):                                              *
 *          The vector P / || P ||, the unit vector in the direction of P.    *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_Hypot:                                                 *
 *              Compute the length of the vector (x, y).                      *
 *          tmpl_Float_Sqrt:                                                  *
 *              Computes the square root of a real number.                    *
 *          tmpl_Float_Is_Inf:                                                *
 *              Determines if the input is positive or negative infinity.     *
 *          tmpl_Float_Is_NaN:                                                *
 *              Determines if the input is Not-a-Number.                      *
 *          tmpl_Float_Is_NaN_Or_Inf:                                         *
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
 *  2.) tmpl_vec2_float.h:                                                    *
 *          The tmpl_TwoVectorFloat typedef is provided here.                 *
 *  3.) tmpl_nan_float.h:                                                     *
 *          Header file providing single precision NaN (Not-a-Number).        *
 *  4.) tmpl_ieee754_float.h:                                                 *
 *          Header file where the tmpl_IEEE754_Float type is defined.         *
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
 *      Added docstring, renamed function to "Unit_Normal", added protections *
 *      for denormal / subnormal numbers and checks for overflow / underflow. *
 ******************************************************************************/

/*  The TMPL_USE_INLINE macro is provided here.                               */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  TMPL_HAS_IEEE754_FLOAT macro and tmpl_IEEE754_Float type given here.      */
#include <libtmpl/include/types/tmpl_ieee754_float.h>

/*  TMPL_NANF macro found here which provides single precision NaN.           */
#include <libtmpl/include/nan/tmpl_nan_float.h>

/*  Prototype / forward declaration for the function.                         */
extern tmpl_TwoVectorFloat
tmpl_2DFloat_Unit_Normal(const tmpl_TwoVectorFloat * const P);

/*  Tell the compiler about the hypotenuse function.                          */
extern float tmpl_Float_Hypot(float x, float y);

/*  We can safely handle denormal numbers if IEEE-754 support is available.   */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  The values 2^64 and 2^-64, to single precision, stored as macros.         */
#define TMPL_BIG_SCALE (1.8446744073709552E+19F)
#define TMPL_RCPR_BIG_SCALE (5.4210108624275222E-20F)

/*  Tell the compiler about the sqrt function. If we need to scale the input  *
 *  components because they are too large, then after the scaling we may      *
 *  safely compute || P || vis sqrt(x*x + y*y), saving a call to the hypot    *
 *  function.                                                                 */
extern float tmpl_Float_Sqrt(float x);

/*  Function for normalizing a non-zero vector to length 1.                   */
tmpl_TwoVectorFloat
tmpl_2DFloat_Unit_Normal(const tmpl_TwoVectorFloat * const P)
{
    /*  Variable for the output, the unit vector in the direction of P.       */
    tmpl_TwoVectorFloat u;

    /*  Union of a float and the bits representing it. Used for || P ||.      */
    tmpl_IEEE754_Float wnorm;

    /*  Variable for 1 / || P ||, scaling P by this creates a unit vector.    */
    float rcpr_norm;

    /*  Set the float part of the word to the norm of P, || P ||.             */
    wnorm.r = tmpl_Float_Hypot(P->dat[0], P->dat[1]);

    /*  Make sure we can divide by wnorm. If the exponent bits are zero, then *
     *  either || P || = 0 (in which case the output is NaN), or || P || is a *
     *  subnormal / denormal number and needs to be normalized.               */
    if (TMPL_FLOAT_EXPO_BITS(wnorm) == 0x00U)
    {
        /*  If the input is the zero vector, normalization is undefined.      */
        if (wnorm.r == 0.0F)
        {
            /*  The unit vector for (0, 0) is (NaN, NaN). Return this.        */
            u.dat[0] = TMPL_NANF;
            u.dat[1] = TMPL_NANF;
            return u;
        }

        /*  If we get here, then P is not the zero vector but the components  *
         *  are so small that || P || is a denormal number. We need to scale  *
         *  the components of P by a large number to ensure that we can       *
         *  compute 1 / || P || without overflowing to infinity.              */
        u.dat[0] = P->dat[0] * TMPL_BIG_SCALE;
        u.dat[1] = P->dat[1] * TMPL_BIG_SCALE;

        /*  Since we have scaled P by a number, we must scale the norm by the *
         *  same number. This is because || r * P || = |r| * || P ||.         */
        wnorm.r *= TMPL_BIG_SCALE;

        /*  The norm is now large enough that the reciprocal can be computed. *
         *  That is, wnorm.r is no longer a denormal number.                  */
        rcpr_norm = 1.0F / wnorm.r;

        /*  The unit normal can now be computed by scaling the components by  *
         *  the reciprocal of the norm.                                       */
        u.dat[0] *= rcpr_norm;
        u.dat[1] *= rcpr_norm;
        return u;
    }

    /*  The tmpl_Float_Hypot function safely handles large numbers, meaning   *
     *  || P || can be computed even if the components are close to FLT_MAX,  *
     *  the largest representable float. But if both components are equal to  *
     *  FLT_MAX, then || P || = sqrt(2) * FLT_MAX, which will overflow. We    *
     *  can still normalize such a vector by first scaling the components of  *
     *  P so that the norm will not overflow.                                 */
    if (TMPL_FLOAT_EXPO_BITS(wnorm) == TMPL_FLOAT_NANINF_EXP)
    {
        /*  Words for the x and y components of P.                            */
        tmpl_IEEE754_Float wx, wy;

        /*  If one of the components of P is Not-a-Number (NaN), then the     *
         *  norm will be NaN as well. In this case the unit normal is set to  *
         *  the vector (NaN, NaN).                                            */
        if (TMPL_FLOAT_IS_NAN(wnorm))
        {
            u.dat[0] = TMPL_NANF;
            u.dat[1] = TMPL_NANF;
            return u;
        }

        /*  If either of the x or y components of P are infinite, we cannot   *
         *  normalize the input. Check for this, grab the components of P and *
         *  store them in the float part of the words wx and wy.              */
        wx.r = P->dat[0];
        wy.r = P->dat[1];

        /*  Check for infinity, return NaN if this is the case.               */
        if (TMPL_FLOAT_IS_INFINITY(wx) || TMPL_FLOAT_IS_INFINITY(wy))
        {
            u.dat[0] = TMPL_NANF;
            u.dat[1] = TMPL_NANF;
            return u;
        }

        /*  Neither of the components are infinity, we can scale them to be   *
         *  much smaller. This will prevent the norm from overflowing.        */
        u.dat[0] = P->dat[0] * TMPL_RCPR_BIG_SCALE;
        u.dat[1] = P->dat[1] * TMPL_RCPR_BIG_SCALE;

        /*  Recompute the norm. Since we have scaled the components (and      *
         *  we checked for NaNs and infinities), this will be finite. We have *
         *  also ensured the x^2 + y^2 will not overflow, so we can compute   *
         *  || P || via tmpl_Float_Sqrt saving a call to tmpl_Float_Hypot.    */
        wnorm.r = tmpl_Float_Sqrt(u.dat[0] * u.dat[0] + u.dat[1] * u.dat[1]);

        /*  The norm is positive and normal meaning we can compute the        *
         *  reciprocal. This will be the final scale factor for u.            */
        rcpr_norm = 1.0F / wnorm.r;

        /*  The unit normal can now be computed by scaling the components by  *
         *  the reciprocal of the norm.                                       */
        u.dat[0] *= rcpr_norm;
        u.dat[1] *= rcpr_norm;
        return u;
    }

    /*  It is more than likely that || P || was computed without issue, and   *
     *  that the output is a positive normal number. The reciprocal can be    *
     *  computed without issue and u = P / || P || can be carried out safely. */
    rcpr_norm = 1.0F / wnorm.r;
    u.dat[0] = P->dat[0] * rcpr_norm;
    u.dat[1] = P->dat[1] * rcpr_norm;
    return u;
}
/*  End of tmpl_2DFloat_Unit_Normal.                                          */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  The value 2^-64, used for scaling vectors with large components.          */
#define TMPL_RCPR_BIG_SCALE (5.4210108624275222E-20F)

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
extern tmpl_Bool tmpl_Float_Is_Inf(float x);
extern tmpl_Bool tmpl_Float_Is_NaN(float x);
extern tmpl_Bool tmpl_Float_Is_NaN_Or_Inf(float x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Function for normalizing a non-zero vector to length 1.                   */
tmpl_TwoVectorFloat
tmpl_2DFloat_Unit_Normal(const tmpl_TwoVectorFloat * const P)
{
    /*  Variable for the output, the unit vector in the direction of P.       */
    tmpl_TwoVectorFloat u;

    /*  The Euclidean, or L2 norm, of the input, || P ||.                     */
    float norm = tmpl_Float_Hypot(P->dat[0], P->dat[1]);

    /*  Variable for 1 / || P ||, scaling P by this creates a unit vector.    */
    float rcpr_norm;

    /*  Avoid division-by-zero. The zero vector cannot be normalized.         */
    if (norm == 0.0F)
    {
        /*  We set the unit vector for (0, 0) to (NaN, NaN). Return this.     */
        u.dat[0] = TMPL_NANF;
        u.dat[1] = TMPL_NANF;
        return u;
    }

    /*  If the input vector contains NaN as one of its components, the norm   *
     *  will be NaN. Similarly if one of the components is infinite, then the *
     *  norm will be as well. If the components are both very big, say equal  *
     *  to FLT_MAX, then the norm will be || P || = sqrt(2) * FLT_MAX, which  *
     *  will overflow to infinity. We need to handle these cases, check if    *
     *  the norm is either infinity or NaN.                                   */
    if (tmpl_Float_Is_NaN_Or_Inf(norm))
    {
        /*  If one of the components of P is Not-a-Number (NaN), then the     *
         *  norm will be NaN as well. In this case the unit normal is set to  *
         *  the vector (NaN, NaN).                                            */
        if (tmpl_Float_Is_NaN(norm))
        {
            u.dat[0] = TMPL_NANF;
            u.dat[1] = TMPL_NANF;
            return u;
        }

        /*  Check for infinity, return NaN if this is the case.               */
        if (tmpl_Float_Is_Inf(P->dat[0]) || tmpl_Float_Is_Inf(P->dat[1]))
        {
            u.dat[0] = TMPL_NANF;
            u.dat[1] = TMPL_NANF;
            return u;
        }

        /*  Neither of the components are infinity, we can scale them to be   *
         *  much smaller. This will prevent the norm from overflowing.        */
        u.dat[0] = P->dat[0] * TMPL_RCPR_BIG_SCALE;
        u.dat[1] = P->dat[1] * TMPL_RCPR_BIG_SCALE;

        /*  Recompute the norm. Since we have scaled the components (and      *
         *  we checked for NaNs and infinities), this will be finite.         */
        norm = tmpl_Float_Hypot(u.dat[0], u.dat[1]);

        /*  The norm is positive and normal meaning we can compute the        *
         *  reciprocal. This will be the final scale factor for u.            */
        rcpr_norm = 1.0F / norm;

        /*  The unit normal can now be computed by scaling the components by  *
         *  the reciprocal of the norm.                                       */
        u.dat[0] *= rcpr_norm;
        u.dat[1] *= rcpr_norm;
        return u;
    }

    /*  It is more than likely that || P || was computed without issue, and   *
     *  that the output is a positive normal number. The reciprocal can be    *
     *  computed without issue and u = P / || P || can be carried out safely. */
    rcpr_norm = 1.0F / norm;
    u.dat[0] = P->dat[0] * rcpr_norm;
    u.dat[1] = P->dat[1] * rcpr_norm;
    return u;
}
/*  End of tmpl_2DFloat_Unit_Normal.                                          */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE
