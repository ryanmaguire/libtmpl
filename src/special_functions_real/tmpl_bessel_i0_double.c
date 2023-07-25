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
 *                           tmpl_bessel_i0_double                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for computing the Bessel I0 function at double precision.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_I0:                                                *
 *  Purpose:                                                                  *
 *      Compute the I0 bessel function for a real argument.                   *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for I0(x).                            *
 *  Output:                                                                   *
 *      I0_x:                                                                 *
 *          The Bessel function I0(x).                                        *
 *  Called Functions:                                                         *
 *      tmpl_Double_Bessel_I0_Maclaurin (tmpl_special_functions_real.h):      *
 *          Computes I0(x) using a Maclaurin series for small inputs.         *
 *      tmpl_Double_Bessel_I0_Asymptotic (tmpl_special_functions_real.h):     *
 *          Computes I0(x) using an asymptotic expansion for large inputs.    *
 *      tmpl_Double_Bessel_I0_Chebyshev (tmpl_special_functions_real.h):      *
 *          Computes I0(x) for x >= 8 using a Chebyshev expansion.            *
 *  Method:                                                                   *
 *      Since I0(x) is even, reduce x to being non-negative. Split the input  *
 *      into one of three windows:                                            *
 *          0 <= x < 8:   Maclaurin Series                                    *
 *          8 <= x < 64:  Chebyshev expansion                                 *
 *          64 < x < max: Asymptotic expansion                                *
 *          max <= x:     Return infinity                                     *
 *      Where max is the largest value for double such that exp(x) will not   *
 *      overflow. For 64-bit double this is roughly 709.                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing infinity, nan, and other math tools.       *
 *  2.) tmpl_special_functions_real.h:                                        *
 *          Header file containing the functions prototype.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 23, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2019/09/15  Ryan Maguire:                                                 *
 *      Created file (Wellesley college for librssringoccs).                  *
 *  2020/09/12  Ryan Maguire:                                                 *
 *      Made code compliant with the C89 standard. Added comments.            *
 *  2021/06/23  Ryan Maguire:                                                 *
 *      Moved to libtmpl. Made changes so -Weverything mode in LLVM's clang   *
 *      does not complain.                                                    *
 *  2022/01/10: Ryan Maguire                                                  *
 *      Improved relative error from 1.0E-10 to 2.0E-16.                      *
 ******************************************************************************/

/*  TMPL_INFINITY is found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Slight performance boost with IEEE-754 support.                           */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Computes the Modified Bessel function I0 at double precision.             */
double tmpl_Double_Bessel_I0(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  For small arguments use a Remez polynomial to approximate I0(x).      */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 3U)
        return tmpl_Double_Bessel_I0_Remez(w.r);

    /*  I0 is even so compute the absolute value of x and use that.           */
    w.bits.sign = 0x00U;

    /*  For intermediate values use a Chebyshev expansion.                    */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 7U)
        return tmpl_Double_Bessel_I0_Chebyshev(w.r);

    /*  For larger values use the asymptotic expansion.                       */
    else if (w.r < tmpl_Max_Double_Base_E)
        return tmpl_Double_Bessel_I0_Asymptotic(w.r);

    /*  For very large inputs, return infinity.                               */
    return TMPL_INFINITY;
}
/*  End of tmpl_Double_Bessel_I0.                                             */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Computes the Modified Bessel function I0 at double precision.             */
double tmpl_Double_Bessel_I0(double x)
{
    /*  I0 is even so compute the absolute value of x and use that.           */
    const double abs_x = tmpl_Double_Abs(x);

    /*  For small arguments use a Remez polynomial to approximate I0(x).      */
    if (abs_x < 8.0)
        return tmpl_Double_Bessel_I0_Remez(abs_x);

    /*  For intermediate values use a Chebyshev expansion.                    */
    else if (abs_x < 64.0)
        return tmpl_Double_Bessel_I0_Chebyshev(abs_x);

    /*  For larger values use the asymptotic expansion.                       */
    else if (abs_x < tmpl_Max_Double_Base_E)
        return tmpl_Double_Bessel_I0_Asymptotic(abs_x);

    /*  For very large inputs, return infinity.                               */
    return TMPL_INFINITY;
}
/*  End of tmpl_Double_Bessel_I0.                                             */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
