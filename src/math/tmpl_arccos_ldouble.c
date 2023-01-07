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
 *                             tmpl_arccos_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-cosine function at double precision.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arccos                                                    *
 *  Purpose:                                                                  *
 *      Computes acos(x), the inverse cosine function.                        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (double):                                                      *
 *          The arc-cosine of x.                                              *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *                                                                            *
 *      Method:                                                               *
 *                                                                            *
 *      Error:                                                                *
 *          Based on 788,968,857 random samples with -10^6 < x < 10^6.        *
 *              max relative error: 2.3223344540012894e-16                    *
 *              rms relative error: 7.4233764024303319e-17                    *
 *              max absolute error: 2.2204460492503131e-16                    *
 *              rms absolute error: 1.1660491924987274e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 03, 2023                                              *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Double precision inverse cosine (acos equivalent).                        */
long double tmpl_LDouble_Arccos(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  For |x| < 0.5 use the Pade approximant.                               */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 1U)
        return tmpl_LDouble_Arccos_Pade(x);

    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
    {
        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return tmpl_One_Pi_L - tmpl_LDouble_Arccos_Tail_End(-x);
        else
            return tmpl_LDouble_Arccos_Tail_End(x);
    }
    else
    {
        if (x == -1.0L)
            return tmpl_One_Pi_L;
        else if (x == 1.0L)
            return 0.0L;
        else
            return TMPL_NANL;
    }
}
/*  End of tmpl_LDouble_Arccos.                                               */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Double precision inverse cosine (acos equivalent).                        */
long double tmpl_LDouble_Arccos(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const long double abs_x = tmpl_LDouble_Abs(x);

    /*  For |x| < 0.5 use the Pade approximant.                               */
    if (abs_x < 0.5L)
        return tmpl_LDouble_Arccos_Pade(x);

    else if (abs_x < 1.0L)
    {
        if (x < 0.0L)
            return tmpl_One_Pi_L - tmpl_LDouble_Arccos_Tail_End(abs_x);
        else
            return tmpl_LDouble_Arccos_Tail_End(abs_x);
    }
    else
    {
        if (x == -1.0L)
            return tmpl_One_Pi_L;
        else if (x == 1.0L)
            return 0.0L;
        else
            return TMPL_NANL;
    }
}
/*  End of tmpl_LDouble_Arccos.                                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
