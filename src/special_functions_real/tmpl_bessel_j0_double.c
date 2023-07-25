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
 *      J0_x:                                                                 *
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

static double tmpl_Double_Bessel_J0_Asym[9] = {
     1.0,
     0.1250,
    -0.07031250,
    -0.07324218750,
     0.1121520996093750,
     0.2271080017089843750,
    -0.57250142097473144531250,
    -1.72772750258445739746093750,
    6.074042001273483037948608398
};

/*  Compute the Bessel J_0 function for a double precision number x.          */
double tmpl_Double_Bessel_J0(double x)
{
    tmpl_IEEE754_Double w;
    double sinarg, cosarg, arg, J0_x;
    w.r = x;

    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 1U)
    {
        if (w.bits.expo < TMPL_DOUBLE_UBIAS - 1U)
        {
            if (w.bits.expo < TMPL_DOUBLE_UBIAS - 27U)
                return 1.0;

            return tmpl_Double_Bessel_J0_Maclaurin(x);
        }

        return tmpl_Double_Bessel_J0_Remez(x);
    }

    w.bits.sign = 0x00U;

    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 3U)
        return tmpl_Double_Bessel_J0_Two_To_Eight(w.r);

    arg = x*x;

    /*  For large arguments use the asymptotic expansion.                     */
    if (arg < 1.0e32)
    {
        /*  J_0 is an even function so use the absolute value of x.           */
        x = tmpl_Double_Abs(x);

        /*  The argument for the asymptotic expansion is 1/x^2.               */
        arg = 1.0/arg;

        /*  Use Horner's method to compute the polynomial part.               */
        sinarg = arg * tmpl_Double_Bessel_J0_Asym[7] +
                       tmpl_Double_Bessel_J0_Asym[5];
        sinarg = arg * sinarg + tmpl_Double_Bessel_J0_Asym[3];
        sinarg = arg * sinarg + tmpl_Double_Bessel_J0_Asym[1];

        /*  Multiply the output by the coefficient factor.                    */
        sinarg *= tmpl_Double_Sin(x - tmpl_Pi_By_Four)/x;

        /*  Do the same as above for the Cosine portion.                      */
        cosarg  = arg * tmpl_Double_Bessel_J0_Asym[8] +
                        tmpl_Double_Bessel_J0_Asym[6];
        cosarg  = arg * cosarg + tmpl_Double_Bessel_J0_Asym[4];
        cosarg  = arg * cosarg + tmpl_Double_Bessel_J0_Asym[2];
        cosarg  = arg * cosarg + tmpl_Double_Bessel_J0_Asym[0];
        cosarg *= tmpl_Double_Cos(x - tmpl_Pi_By_Four);

        /*  Multiply the result by the coefficient and return.                */
        J0_x = (cosarg + sinarg)*tmpl_Sqrt_Two_By_Pi;
        return J0_x / tmpl_Double_Sqrt(x);
    }

    /*  For very large arguments, use the limit (which is zero).              */
    return 0.0;
}
