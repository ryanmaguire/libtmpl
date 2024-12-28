/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of rss_ringoccs.                                        *
 *                                                                            *
 *  rss_ringoccs is free software: you can redistribute it and/or modify it   *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  rss_ringoccs is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with rss_ringoccs.  If not, see <https://www.gnu.org/licenses/>.    *
 ******************************************************************************
 *                                Bessel J0                                   *
 ******************************************************************************
 *  This file contains functions for computing the Bessel J0 function.        *
 ******************************************************************************
 * We define J_0(x) as the power series solution to the ODE:                  *
 *                                                                            *
 *           d^2 y(x)      dy(x)                                              *
 *      x^2 ---------  + x ----- + x^2 y(x) = 0                               *
 *             dx^2         dx                                                *
 *                                                                            *
 *  Where J_0 is the Bessel function of the First kind with alpha = 0.        *
 ******************************************************************************
 *                              DEFINED FUNCTIONS                             *
 ******************************************************************************
 *  BesselJ0                                                                  *
 *  Purpose:                                                                  *
 *      Compute the J_0 bessel function for a real argument.                  *
 *  Arguments:                                                                *
 *      x (float, double, or long double):                                    *
 *          A real number, the argument for J_0(x).                           *
 *  Output:                                                                   *
 *      bessel_J0:                                                            *
 *          The Bessel function J_0(x).                                       *
 *  Method:                                                                   *
 *      For small values, the Taylor expansion is used. The J_0(x) function   *
 *      can be defined by the following series:                               *
 *                                                                            *
 *                      ___                                                   *
 *                      \       (-1)^n x^2n                                   *
 *         J_0(x)  =    /__     ------------                                  *
 *                     n = 0    (n)!^2 * 4^n                                  *
 *                                                                            *
 *      For large arguments the asymptotic expansion is used. This is defined *
 *      by the following series:                                              *
 *                                                                            *
 *                      ___          _                                  _     *
 *                      \           |  cos(z) a_{2n}    sin(z) a_{2n+1}  |    *
 *          J_0(x)  ~   /__  (-1)^n |  ------------- -  ---------------  |    *
 *                     n = 1         -      x^2n            x^{2n+1}    -     *
 *                                                                            *
 *      Where:                                                                *
 *                         (2n)!^2                                            *
 *          a_n = (-1)^n ------------                                         *
 *                        32^n (n!)^3                                         *
 *                                                                            *
 *          z   = x - pi/4                                                    *
 *                                                                            *
 *      Note that this expansion diverges for all real numbers. To make use   *
 *      of this series we must stop the sum at a particular N. We compute     *
 *      between 8 and 10 terms of this expansion, depending on the precision  *
 *      desired (float, double, long double).                                 *
 *  Error:                                                                    *
 *      In the region in which the Taylor series is used, relative error is   *
 *      10^-16. In the hand-off region with the asymptotic expansion, the     *
 *      error is 10^-9 but quickly drops back to 10^-16.                      *
 *      The regions where the Taylor series is used are listed below:         *
 *          float:           (-7.07,  7.07)                                   *
 *          double:         (-12.24, 12.24)                                   *
 *          long double:    (-12.24, 12.24)                                   *
 *      The alternating series test gives the error of the partial sums of    *
 *      the Taylor expansion. This, combined with trial and error, produced   *
 *      these selected ranges.                                                *
 ******************************************************************************/

/*  The C standard library header math.h is included here, as are aliases for *
 *  various functions, the macros INFINITY and NAN, as well as the max legal  *
 *  values for the exponential function which don't return INFINITY.          */
#include <libtmpl/include/tmpl_math.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Define Taylor coefficients.                                               */
#define tmpl_BESSEL_J0_TAYLORF_00  1.0F
#define tmpl_BESSEL_J0_TAYLORF_01 -0.25F
#define tmpl_BESSEL_J0_TAYLORF_02  1.56250e-2F
#define tmpl_BESSEL_J0_TAYLORF_03 -4.340277777E-4F
#define tmpl_BESSEL_J0_TAYLORF_04  6.781684027E-6F
#define tmpl_BESSEL_J0_TAYLORF_05 -6.781684027E-8F
#define tmpl_BESSEL_J0_TAYLORF_06  4.709502797E-10F
#define tmpl_BESSEL_J0_TAYLORF_07 -2.402807549E-12F
#define tmpl_BESSEL_J0_TAYLORF_08  9.385966990E-15F
#define tmpl_BESSEL_J0_TAYLORF_09 -2.896903392E-17F
#define tmpl_BESSEL_J0_TAYLORF_10  7.242258480E-20F
#define tmpl_BESSEL_J0_TAYLORF_11 -1.496334396E-22F
#define tmpl_BESSEL_J0_TAYLORF_12  2.597802772E-25F
#define tmpl_BESSEL_J0_TAYLORF_13 -3.842903509E-28F
#define tmpl_BESSEL_J0_TAYLORF_14  4.901662639E-31F
#define tmpl_BESSEL_J0_TAYLORF_15 -5.446291821E-34F
#define tmpl_BESSEL_J0_TAYLORF_16  5.318644356E-37F

/*  And the asmyptotic coefficients.                                          */
#define tmpl_BESSEL_J0_ASYMF_00 1.0F
#define tmpl_BESSEL_J0_ASYMF_01 0.1250F
#define tmpl_BESSEL_J0_ASYMF_02 -0.07031250F
#define tmpl_BESSEL_J0_ASYMF_03 -0.07324218750F
#define tmpl_BESSEL_J0_ASYMF_04 0.1121520996093750F
#define tmpl_BESSEL_J0_ASYMF_05 0.2271080017089843750F
#define tmpl_BESSEL_J0_ASYMF_06 -0.57250142097473144531250F
#define tmpl_BESSEL_J0_ASYMF_07 -1.72772750258445739746093750F
#define tmpl_BESSEL_J0_ASYMF_08 6.07404200127348303794860839844F

/*  Compute the Bessel J_0 function for a floating point number x.            */
float tmpl_Float_Bessel_J0(float x)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    float bessel_J0, arg;
    float sinarg, cosarg;

    /*  Bessel J0 is even and in terms of the square of x, so compute this.   */
    arg = x*x;

    /*  For small arguments, use the Taylor series of J_0.                    */
    if (arg < 4.0F)
    {
        bessel_J0 = tmpl_BESSEL_J0_TAYLORF_10;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_09;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_08;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_07;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_06;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_05;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_04;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_03;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_02;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_01;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_00;
    }
    else if (arg < 16.0F)
    {
        bessel_J0 = tmpl_BESSEL_J0_TAYLORF_12;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_11;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_10;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_09;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_08;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_07;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_06;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_05;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_04;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_03;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_02;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_01;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_00;
    }
    else if (arg < 25.0F)
    {
        bessel_J0 = tmpl_BESSEL_J0_TAYLORF_14;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_13;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_12;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_11;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_10;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_09;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_08;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_07;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_06;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_05;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_04;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_03;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_02;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_01;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_00;
    }
    else if (arg < 36.0F)
    {
        bessel_J0 = tmpl_BESSEL_J0_TAYLORF_16;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_15;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_14;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_13;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_12;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_11;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_10;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_09;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_08;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_07;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_06;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_05;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_04;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_03;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_02;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_01;
        bessel_J0 = arg * bessel_J0 + tmpl_BESSEL_J0_TAYLORF_00;
    }

    /*  For large arguments use the asymptotic expansion.                     */
    else if (arg < 1.0e32F)
    {
        /*  J_0 is an even function so use the absolute value of x.           */
        x = tmpl_Float_Abs(x);

        /*  The argument for the asymptotic expansion is 1/x^2.               */
        arg = 1.0F/arg;

        /*  Use Horner's method to compute the polynomial part.               */
        sinarg = arg * tmpl_BESSEL_J0_ASYMF_07 + tmpl_BESSEL_J0_ASYMF_05;
        sinarg = arg * sinarg + tmpl_BESSEL_J0_ASYMF_03;
        sinarg = arg * sinarg + tmpl_BESSEL_J0_ASYMF_01;

        /*  Multiply the output by the coefficient factor.                    */
        sinarg *= tmpl_Float_Sin(x - tmpl_Float_Pi_By_Four)/x;

        /*  Do the same as above for the Cosine portion.                      */
        cosarg  = arg * tmpl_BESSEL_J0_ASYMF_08 + tmpl_BESSEL_J0_ASYMF_06;
        cosarg  = arg * cosarg + tmpl_BESSEL_J0_ASYMF_04;
        cosarg  = arg * cosarg + tmpl_BESSEL_J0_ASYMF_02;
        cosarg  = arg * cosarg + tmpl_BESSEL_J0_ASYMF_00;
        cosarg *= tmpl_Float_Cos(x - tmpl_Float_Pi_By_Four);

        /*  Multiply the result by the coefficient and return.                */
        bessel_J0 = (cosarg + sinarg)*tmpl_Float_Sqrt_Two_By_Pi;
        bessel_J0 = bessel_J0 / tmpl_Float_Sqrt(x);
    }

    /*  For very large arguments, use the limit (which is zero).              */
    else
        bessel_J0 = 0.0F;

    return bessel_J0;
}
/*  End of tmpl_Float_Bessel_J0.                                              */
