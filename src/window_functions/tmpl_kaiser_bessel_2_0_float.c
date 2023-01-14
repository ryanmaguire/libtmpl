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
 *                        tmpl_kaiser_bessel_2_0_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Kaiser-Bessel window with alpha = 2 pi.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Kaiser_Bessel_2_0                                          *
 *  Purpose:                                                                  *
 *      Computes the Kaiser-Bessel window function with alpha set to 2 pi.    *
 *      This is defined in terms of modified Bessel functions:                *
 *                                                                            *
 *                        I_0(2 pi sqrt(1 - (2x/W)^2))                        *
 *          kb20(x, W) =  ----------------------------                        *
 *                                 I_0(2 pi)                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the input data value.                              *
 *      W (float):                                                            *
 *          The width of the window. Units are the same as x.                 *
 *  Output:                                                                   *
 *      window (float):                                                       *
 *          The Kaiser-Bessel window with alpha = 2 Pi and window width W     *
 *          evaluated at the point x.                                         *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Compute the value 1 - (2x/W)^2. Check that sign bit. It the       *
 *          value is negative, then x falls outside the window and 0 is       *
 *          returned. Otherwise a degree 11 Taylor series is used.            *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Same as IEEE-754 method but check if 1 - (2x/W)^2 is negative     *
 *          using comparisons, rather than examining the sign bit. This is    *
 *          slightly slower on some machines, but not by much.                *
 *  Error:                                                                    *
 *      Max Relative Error: 4E-8                                              *
 *      RMS Relative Error: 2E-8                                              *
 *                                                                            *
 *      These values are theoretical errors for the Taylor series.            *
 *      Actual error for 32-bit float is 1 ULP, 2^-23 ~= 1.19E-7.             *
 *  Notes:                                                                    *
 *      No checks for x = NaN or x = +/- Inf are performed. For x = +/- inf,  *
 *      1 - (x/W)^2 will be negative, so zero is returned. For NaN the result *
 *      can be +/- NaN or zero.                                               *
 *                                                                            *
 *      No checks for W = NaN, +/- Inf, or zero are performed. W = zero will  *
 *      result in divide-by-zero, and NaN or Inf may return.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing TMPL_HAS_IEEE754_FLOAT macro.              *
 *  2.) tmpl_window_functions.h:                                              *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 27, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/05: Ryan Maguire                                                  *
 *      Moved float version to its own file. Reduced polynomial from degree   *
 *      12 to degree 11. This still attains single precision accuracy.        *
 *  2023/01/06: Ryan Maguire                                                  *
 *      Added license and comments.                                           *
 ******************************************************************************/

/*  TMPL_HAS_IEEE754_FLOAT found here, as is the tmpl_FLOAT_IEEE754 type.     */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_window_functions.h>

/*  Degree 11 Taylor series.                                                  *
 *      Max Relative Error: 4E-8                                              *
 *      RMS Relative Error: 2E-8                                              *
 *          Actual error for 32-bit float is less than 1 ULP.                 */
#define T00 (1.14799345379586479212325625173E-2F)
#define T01 (1.13302412440054404174028755736E-1F)
#define T02 (2.79562497118100660800421522589E-1F)
#define T03 (3.06574583548481935246360365287E-1F)
#define T04 (1.89110616190764661645757930810E-1F)
#define T05 (7.46578787939636569441597855450E-2F)
#define T06 (2.04678813644694334928965293809E-2F)
#define T07 (4.12265085705596709062582845471E-3F)
#define T08 (6.35764578796162329491799908822E-4F)
#define T09 (7.74659862338682228855283637288E-5F)
#define T10 (7.64558638668513481381569815368E-6F)
#define T11 (6.23627380586252011565352895678E-7F)
/* Not needed. #define T12 (4.27427468060687589919240887794E-8F).             */

/*  Helper macro for evaluating the Taylor series.                            */
#define TMPL_TAYLOR_HELPER(x, A) \
A##00 + x*(\
    A##01 + x*(\
        A##02 + x*(\
            A##03 + x*(\
                A##04 + x*(\
                    A##05 + x*(\
                        A##06 + x*(\
                            A##07 + x*(\
                                A##08 + x*(\
                                    A##09 + x*(\
                                        A##10 + x*A##11\
                                    )\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  With IEEE-754 support we can check if the input falls within the window   *
 *  by examining the sign bit. This is slightly faster on some machines.      */
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  Single precision Kaiser-Bessel window with alpha = 2 pi.                  */
float tmpl_Float_Kaiser_Bessel_2_0(float x, float W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2))/I_0(2pi) for values      *
     *  inside the window. To determine if x falls in the window we need to   *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const float c = 2.0F*x/W;

    /*  Set the float part of the union to 1 - (2x/W)^2 and check the sign.   */
    w.r = 1.0F - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (w.bits.sign)
        return 0.0F;

    /*  Otherwise use the Taylor series to compute the window function.       */
    else
        return TMPL_TAYLOR_HELPER(w.r, T);
}
/*  End of tmpl_Float_Kaiser_Bessel_2_0.                                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/*  Single precision Kaiser-Bessel window with alpha = 2 pi.                  */
float tmpl_Float_Kaiser_Bessel_2_0(float x, float W)
{
    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2))/I_0(2pi) for values      *
     *  inside the window. To determine if x falls in the window we need to   *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const float c = 2.0F*x/W;
    const float arg = 1.0F - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (arg < 0.0F)
        return 0.0F;

    /*  Otherwise use the Taylor series to compute the window function.       */
    else
        return TMPL_TAYLOR_HELPER(arg, T);
}
/*  End of tmpl_Float_Kaiser_Bessel_2_0.                                      */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_TAYLOR_HELPER
#undef T00
#undef T01
#undef T02
#undef T03
#undef T04
#undef T05
#undef T06
#undef T07
#undef T08
#undef T09
#undef T10
#undef T11
#undef T12
