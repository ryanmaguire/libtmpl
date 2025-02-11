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
 *                           tmpl_bessel_j1_double                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 10, 2025                                             *
 ******************************************************************************/

/*  IEEE-754 data types found here.                                           */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Prototype for the function given here.                                    */
#include <libtmpl/include/tmpl_special_functions_real.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Rational Remez approximation for x near the origin.                       */
#include "auxiliary/tmpl_bessel_j1_rat_remez_double.h"

/*  Rational Remez approximations about j_{1, 1}, j_{1, 2}, ..., j_{1, 5}.    */
#include "auxiliary/tmpl_bessel_j1_first_zero_double.h"
#include "auxiliary/tmpl_bessel_j1_second_zero_double.h"
#include "auxiliary/tmpl_bessel_j1_third_zero_double.h"
#include "auxiliary/tmpl_bessel_j1_fourth_zero_double.h"
#include "auxiliary/tmpl_bessel_j1_fifth_zero_double.h"

/*  Rational approximation using the "Hankel expansion" for J1.               */
#include "auxiliary/tmpl_bessel_j1_rat_asymptotic_double.h"

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Compute the Bessel J1 function for a double precision number x.           */
double tmpl_Double_Bessel_J1(double x)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special case, infinity or not-a-number.                               */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
        return 1.0 / x;

    /*  Small arguments, |x| < 2. Use a rational Remez approximation.         */
    if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS + 1U)
    {
        /*  For very small x, |x| < 2^-20, avoid overflow. Return x / 2.      */
        if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_BIAS - 20U)
            return 0.5 * x;

        /*  Otherwise, use a rational Remez approximation.                    */
        return tmpl_Double_Bessel_J1_Rat_Remez(w.r);
    }

    /*  J1(x) is odd. Reduce to |x| and work with this.                       */
    w.bits.sign = 0x00U;

    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 3U)
    {
        if (w.r < 5.0)
            w.r = tmpl_Double_Bessel_J1_First_Zero(w.r);
        else
            w.r = tmpl_Double_Bessel_J1_Second_Zero(w.r);
    }

    else if (w.r < 18.0)
    {
        if (w.r < 11.5)
            w.r = tmpl_Double_Bessel_J1_Third_Zero(w.r);
        else if (w.r < 15.0)
            w.r = tmpl_Double_Bessel_J1_Fourth_Zero(w.r);
        else
            w.r = tmpl_Double_Bessel_J1_Fifth_Zero(w.r);
    }

    else
        w.r = tmpl_Double_Bessel_J1_Rational_Asymptotic(w.r);

    /*  J1(x) is odd. Return -J1(-x) for negative inputs.                     */
    if (x < 0.0)
        return -w.r;

    /*  Otherwise, we are done. Return J1(x).                                 */
    return w.r;
}
/*  End of tmpl_Double_Bessel_J1.                                             */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Compute the Bessel J1 function for a double precision number x.           */
double tmpl_Double_Bessel_J1(double x)
{
    /*  J1 is an odd function. Compute the absolute value of x.               */
    const double abs_x = tmpl_Double_Abs(x);

    /*  Declare necessary variables. C89 requires this at the top.            */
    double output;

    /*  Small arguments, |x| < 2. Use a rational Remez approximation.         */
    if (abs_x < 4.0)
    {
        /*  For small values, avoid underflow by using the first term of the  *
         *  Maclaurin series for J1.                                          */
        if (abs_x < 9.5367431640625e-07)
            return 0.5 * x;

        /*  Otherwise, use a rational Remez approximation.                    */
        return tmpl_Double_Bessel_J1_Rat_Remez(x);
    }

    /*  There are five zeros between 2 and 18. Handle them carefully.         */
    else if (abs_x < 18.0)
    {
        /*  The zeros are roughly pi apart, meaning the midpoints of the      *
         *  zeros are also roughly pi apart. The rational approximations are  *
         *  computed on intervals of width 3, which is roughly equal to pi.   *
         *  Use the appropriate approximation for each zero, j_{1, k}.        */
        if (abs_x < 5.0)
            output = tmpl_Double_Bessel_J1_First_Zero(abs_x);
        else if (abs_x < 8.0)
            output = tmpl_Double_Bessel_J1_Second_Zero(abs_x);
        else if (abs_x < 11.5)
            output = tmpl_Double_Bessel_J1_Third_Zero(abs_x);
        else if (abs_x < 15.0)
            output = tmpl_Double_Bessel_J1_Fourth_Zero(abs_x);
        else
            output = tmpl_Double_Bessel_J1_Fifth_Zero(abs_x);
    }

    /*  For large arguments use the asymptotic expansion. This does not       *
     *  produce nearly as good relative error about the higher zeros of J1,   *
     *  but the absolute error is excellent.                                  */
    else
        output = tmpl_Double_Bessel_J1_Rational_Asymptotic(abs_x);

    if (x < 0.0)
        return -output;

    return output;
}
/*  End of tmpl_Double_Bessel_J1.                                             */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
