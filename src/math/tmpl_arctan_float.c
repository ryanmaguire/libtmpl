/******************************************************************************
 *                                 LICENSE                                    *
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
 *                            tmpl_arctan_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-tangent function at single precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arctan:                                                    *
 *  Purpose:                                                                  *
 *      Computes atan(x).                                                     *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (float):                                                       *
 *          The arc-tangent of x.                                             *
 *  Called Functions:                                                         *
 *      tmpl_Float_Is_NaN (tmpl_math.h)                                       *
 *          Determines if a float is NaN.                                     *
 *      tmpl_Float_Is_Inf (tmpl_math.h)                                      *
 *          Determines if a float is infinity.                                *
 *  Method:                                                                   *
 *      First, use the fact that atan(x) is odd to reduce to the case x >= 0. *
 *      For small values, use a polynomial. For values in certain ranges, use *
 *      formula 4.4.34 from Abramowitz and Stegun to reduce the argument to a *
 *      smaller value. This formula states that:                              *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) - atan(v) = atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *      In particular:                                                        *
 *          x in [0.0,    0.4375)  polynomial.                                *
 *          x in [0.4375, 0.6875)  u = x, v = 1/2, reduce and use polynomial. *
 *          x in [0.6875, 1.1875)  u = x, v = 1, reduce and use polynomial.   *
 *          x in [1.1875, 2.4375)  u = x, v = 3/2, reduce and use polynomial. *
 *          x in [2.4375, inf)     atan(x) = pi/2 + atan(-1/x).               *
 *  NOTE:                                                                     *
 *      There are three special cases. If the input is NaN, the output will   *
 *      also be NaN. If the input is positive infinity, the limit is used and *
 *      pi/2 is returned. If the input is negative infinity, the limit is     *
 *      used and -pi/2 is returned.                                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 09, 2021                                            *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Precompute atan(1/2), atan(1), and atan(3/2).                             */
#define ATAN_OF_ONE_HALF 0.46364760900080611621425623146121440202853705F
#define ATAN_OF_ONE 0.78539816339744830961566084581987572104929234F
#define ATAN_OF_THREE_HALFS 0.98279372324732906798571061101466601449687745F

/*  Coefficients for the computation of the polynomial approximation. The     *
 *  coefficients for the Taylor series are 1 / (1 + 2n).                      */
#define ATAN_A00 3.3333328366E-01F
#define ATAN_A01 1.9999158382E-01F
#define ATAN_A02 1.4253635705E-01F
#define ATAN_A03 1.0648017377E-01F
#define ATAN_A04 6.1687607318E-02F

/*  This function computes arctan(x) via a Taylor series for small |x|.       */
static float tmpl_arctan_small_vals(float x)
{
    /*  Declare necessary variables.                                          */
    float x_sq = x*x;
    float out;

    /*  Use Horner's method to compute the polynomial. The signs of the       *
     *  coefficients oscillate.                                               */
    out = ATAN_A04 * x_sq - ATAN_A03;
    out = out * x_sq + ATAN_A02;
    out = out * x_sq - ATAN_A01;
    out = out * x_sq + ATAN_A00;
    out = x*(1.0F - x_sq * out);
    return out;
}
/*  End of tmpl_arctan_small_vals.                                            */

/*  Single precision inverse tangent.                                         */
float tmpl_Float_Arctan(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float arg, sgn_x;

    /*  If the input is NaN, return NaN.                                      */
    if (tmpl_Float_Is_NaN(x))
        return x;

    /*  atan(x) has limits of +/- pi/2 as |x| -> infinity. Check for this.    */
    if (tmpl_Float_Is_Inf(x))
    {
        if (x > 0.0F)
            return tmpl_Pi_By_Two_F;
        else
            return -tmpl_Pi_By_Two_F;
    }

    /*  For all other x, use the fact that atan is an odd function to reduce  *
     *  to the case of x >= 0.                                                */
    if (x < 0.0F)
    {
        sgn_x = -1.0F;
        arg = -x;
    }
    else
    {
        sgn_x = 1.0F;
        arg = x;
    }

    /*  For small values, use the polynomial provided above.                  */
    if (arg < 0.4375F)
        return sgn_x * tmpl_arctan_small_vals(arg);

    /*  Following Abramowitz and Stegun, equation 4.4.34, we can reduce the   *
     *  argument to a smaller value using:                                    *
     *      atan(x) - atan(y) = atan((x - y) / (1 + xy)) (mod pi).            */
    else if (arg < 0.6875F)
    {
        /*  Use the above formula with atan(1/2).                             */
        arg = (2.0F * arg - 1.0F) / (2.0F + arg);
        return sgn_x * (ATAN_OF_ONE_HALF + tmpl_arctan_small_vals(arg));
    }

    /*  Same reduction, but with 1 instead of 1/2.                            */
    else if (arg < 1.1875F)
    {
        arg = (arg - 1.0F) / (arg + 1.0F);
        return sgn_x * (ATAN_OF_ONE + tmpl_arctan_small_vals(arg));
    }

    /*  Same reduction, but with 3/2 instead of 1.                            */
    else if (arg < 2.4375F)
    {
        arg = (2.0F * arg - 3.0F) / (2.0F + 3.0F * arg);
        return sgn_x * (ATAN_OF_THREE_HALFS + tmpl_arctan_small_vals(arg));
    }

    /*  For larger values, the expansion at infinity is sufficient. We use    *
     *  the polynomial for small values with input -1 / arg and precompute    *
     *  atan(infinity), which is pi / 2.                                      */
    else
    {
        arg = -1.0F / arg;
        return sgn_x * (tmpl_Pi_By_Two_F + tmpl_arctan_small_vals(arg));
    }
}
/*  End of tmpl_Float_Arctan.                                                 */

/*  Undefine all of the macros.                                               */
#undef ATAN_A00
#undef ATAN_A01
#undef ATAN_A02
#undef ATAN_A03
#undef ATAN_A04
#undef ATAN_A05
#undef ATAN_A06
#undef ATAN_A07
#undef ATAN_A08
#undef ATAN_A09
#undef ATAN_A10
#undef ATAN_OF_ONE_HALF
#undef ATAN_OF_ONE
#undef ATAN_OF_THREE_HALFS
