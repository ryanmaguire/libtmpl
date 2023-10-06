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
 *                           tmpl_bessel_j0_double                            *
 ******************************************************************************
 *  Code for computing the Bessel J0 function at double precision.            *
 ******************************************************************************
 *                              DEFINED FUNCTIONS                             *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Bessel_J0                                                 *
 *  Purpose:                                                                  *
 *      Computes the J0 Bessel function for a real argument.                  *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for J0(x).                            *
 *  Output:                                                                   *
 *      J0_x:                                                                 *
 *          The Bessel function J0(x).                                        *
 *  Called Functions:                                                         *
 *      tmpl_special_functions_real.h                                         *
 *          tmpl_Double_Bessel_J0_Rat_Remez:                                  *
 *              Computes J0(x) via a rational Remez approximation for |x| < 2.*
 *          tmpl_Double_Bessel_J0_First_Zero:                                 *
 *              Computes J0(x) for 2 <= x < 4 with a Remez approximation.     *
 *          tmpl_Double_Bessel_J0_Second_Zero:                                *
 *              Computes J0(x) for 4 <= x < 7 with a Remez approximation.     *
 *          tmpl_Double_Bessel_J0_Third_Zero:                                 *
 *              Computes J0(x) for 7 <= x < 10 with a Remez approximation.    *
 *          tmpl_Double_Bessel_J0_Fourth_Zero:                                *
 *              Computes J0(x) for 10 <= x < 13 with a Remez approximation.   *
 *          tmpl_Double_Bessel_J0_Fifth_Zero:                                 *
 *              Computes J0(x) for 13 <= x < 16 with a Remez approximation.   *
 *          tmpl_Double_Bessel_J0_Rational_Asymptotic:                        *
 *              Computes J(x) for x >= 16 using a rational approximation.     *
 *  Method:                                                                   *
 *      The Bessel function J0(x) is defined as the power series solution to: *
 *                                                                            *
 *               d^2 y(x)      dy(x)                                          *
 *          x^2 ---------  + x ----- + x^2 y(x) = 0                           *
 *                 dx^2         dx                                            *
 *                                                                            *
 *      This yields the Taylor series:                                        *
 *                                                                            *
 *                    ____                                                    *
 *                   \       (-1)^n x^2n                                      *
 *          J_0(x) = /____   ------------                                     *
 *                   n = 0   (n)!^2 * 4^n                                     *
 *                                                                            *
 *      For large arguments one obtains the asymptotic formula:               *
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
 *          z = x - pi/4                                                      *
 *                                                                            *
 *      Note that this expansion diverges for all real numbers.               *
 *                                                                            *
 *      Many libraries make use of these two formulas, but both can lead to   *
 *      horrible relative error near the zeros of the J0 function. To fix     *
 *      this we compute rational Remez approximations that are expanded about *
 *      the zeros j_{0, k} for k = 1, 2, ..., 5. For large arguments are      *
 *      rational approximation similar to the asymptotic series above is used.*
 *  Error:                                                                    *
 *      The Python library mpmath was used to calculate the relative error    *
 *      since most mathematical libraries do not accurately compute J0 near   *
 *      its zeros. Octuple 224-bit precision was used in the calculations.    *
 *      The peak relative error for |x| <= 16 is about 2 ULP, 4 x 10^-16.     *
 *      For |x| > 16 the asymptotic approximation has a peak absolute error   *
 *      of 2 x 10^-16, but a peak relative error of 2 x 10^-12.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 5, 2023                                               *
 ******************************************************************************/

/*  IEEE-754 data types found here.                                           */
#include <libtmpl/include/tmpl_math.h>

/*  Prototype for the function given here.                                    */
#include <libtmpl/include/tmpl_special_functions_real.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Rational Remez approximations about j_{0, 1}, j_{0, 2}, ..., j_{0, 5}.    */
#include <libtmpl/include/specfunc_real/tmpl_bessel_j0_first_zero_double.h>
#include <libtmpl/include/specfunc_real/tmpl_bessel_j0_second_zero_double.h>
#include <libtmpl/include/specfunc_real/tmpl_bessel_j0_third_zero_double.h>
#include <libtmpl/include/specfunc_real/tmpl_bessel_j0_fourth_zero_double.h>
#include <libtmpl/include/specfunc_real/tmpl_bessel_j0_fifth_zero_double.h>

/*  A rational Remez approximation centered about the origin.                 */
#include <libtmpl/include/specfunc_real/tmpl_bessel_j0_rat_remez_double.h>

/*  Rational approximation using the "Hankel expansion" for J0.               */
#include <libtmpl/include/specfunc_real/tmpl_bessel_j0_rat_asymptotic_double.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Compute the Bessel J0 function for a double precision number x.           */
double tmpl_Double_Bessel_J0(double x)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  J0 is an even function. Compute the absolute value of x.              */
    w.bits.sign = 0x00U;

    /*  Small arguments, |x| < 4. Use one of two rational approximations.     */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 2U)
    {
        /*  For small values away from j_{0, 1}, use a rational Remez         *
         *  approximation centered about the origin. Peak theoretical error   *
         *  is around 10^-17. Actually floating-point error is about 10^-16.  */
        if (w.bits.expo < TMPL_DOUBLE_UBIAS + 1U)
            return tmpl_Double_Bessel_J0_Rat_Remez(w.r);

        /*  For values near j_{0, 1} use a rational approximation expanded    *
         *  about j_{0, 1}. This yields good relative error, about 1 ULP.     */
        return tmpl_Double_Bessel_J0_First_Zero(w.r);
    }

    /*  There are four more zeros between 4 and 16. Handle them carefully.    */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS + 4U)
    {
        /*  The zeros are roughly pi apart, meaning the midpoints of the      *
         *  zeros are also roughly pi apart. The rational approximations are  *
         *  computed on intervals of width 3, which is roughly equal to pi.   *
         *  Use the appropriate approximation for each zero, j_{0, k}.        */
        if (w.r < 7.0)
            return tmpl_Double_Bessel_J0_Second_Zero(w.r);
        else if (w.r < 10.0)
            return tmpl_Double_Bessel_J0_Third_Zero(w.r);
        else if (w.r < 13.0)
            return tmpl_Double_Bessel_J0_Fourth_Zero(w.r);

        /*  The last window ends at x = 16.0. There is a zero near x = 15.    */
        return tmpl_Double_Bessel_J0_Fifth_Zero(w.r);
    }

    /*  For large arguments use the asymptotic expansion. This does not       *
     *  produce nearly as good relative error about the higher zeros of J0,   *
     *  but the absolute error is excellent.                                  */
    return tmpl_Double_Bessel_J0_Rational_Asymptotic(w.r);
}
/*  End of tmpl_Double_Bessel_J0.                                             */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Compute the Bessel J0 function for a double precision number x.           */
double tmpl_Double_Bessel_J0(double x)
{
    /*  J0 is an even function. Compute the absolute value of x.              */
    const double abs_x = tmpl_Double_Abs(x);

    /*  Small arguments, |x| < 4. Use one of two rational approximations.     */
    if (abs_x < 4.0)
    {
        /*  For small values away from j_{0, 1}, use a rational Remez         *
         *  approximation centered about the origin. Peak theoretical error   *
         *  is around 10^-17. Actually floating-point error is about 10^-16.  */
        if (abs_x < 2.0)
            return tmpl_Double_Bessel_J0_Rat_Remez(abs_x);

        /*  For values near j_{0, 1} use a rational approximation expanded    *
         *  about j_{0, 1}. This yields good relative error, about 1 ULP.     */
        return tmpl_Double_Bessel_J0_First_Zero(abs_x);
    }

    /*  There are four more zeros between 4 and 16. Handle them carefully.    */
    else if (abs_x < 16.0)
    {
        /*  The zeros are roughly pi apart, meaning the midpoints of the      *
         *  zeros are also roughly pi apart. The rational approximations are  *
         *  computed on intervals of width 3, which is roughly equal to pi.   *
         *  Use the appropriate approximation for each zero, j_{0, k}.        */
        if (abs_x < 7.0)
            return tmpl_Double_Bessel_J0_Second_Zero(abs_x);
        else if (abs_x < 10.0)
            return tmpl_Double_Bessel_J0_Third_Zero(abs_x);
        else if (abs_x < 13.0)
            return tmpl_Double_Bessel_J0_Fourth_Zero(abs_x);

        /*  The last window ends at x = 16.0. There is a zero near x = 15.    */
        return tmpl_Double_Bessel_J0_Fifth_Zero(abs_x);
    }

    /*  For large arguments use the asymptotic expansion. This does not       *
     *  produce nearly as good relative error about the higher zeros of J0,   *
     *  but the absolute error is excellent.                                  */
    return tmpl_Double_Bessel_J0_Rational_Asymptotic(abs_x);
}
/*  End of tmpl_Double_Bessel_J0.                                             */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
