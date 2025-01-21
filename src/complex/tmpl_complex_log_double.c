/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                          tmpl_complex_log_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex log function.                *
 *  Notes:                                                                    *
 *      This function implicitly uses the atan2 function via the              *
 *      tmpl_CDouble_Argument function. Because of this the branch cut        *
 *      for the complex log occurs along the negative x-axis. No option is    *
 *      provided to choose different branches. One can artificially change    *
 *      the branch by adding a multiple of 2 pi to the imaginary part.        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file providing log and trig functions.                     *
 *  2.) tmpl_complex.h:                                                       *
 *          Header file where complex types are defined.                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2023/12/20: Ryan Maguire                                                  *
 *      Added IEEE version with improved performance and accuracy. Suports    *
 *      subnormal inputs. Moved float and long double to their own files.     *
 ******************************************************************************/

/*  Header file providing logarithmic and trigonometric functions.            */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Check for IEEE754 support. We can get a decent speed boost with this.     */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Macros for computing the max of two real numbers.                         */
#include <libtmpl/include/helper/tmpl_max.h>

/*  The values 2^512 and 2^-512, to double precision, stored as macros.       */
#define TMPL_BIG_SCALE (1.340780792994259709957402E+154)
#define TMPL_RCPR_BIG_SCALE (7.458340731200206743290965E-155)

/*  The values log(512) and log(512 + 52). Used for shifting the result.      */
#define TMPL_LOG_FACTOR (3.548913564466919984216228461865864028547E+02)
#define TMPL_NORMALIZE_FACTOR (3.909350098358091545113189165024115843946E+02)

/*  Computes the complex log of a real number.                                */
tmpl_ComplexDouble tmpl_CDouble_Log(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Double w;
    tmpl_ComplexDouble ln_z;

    /*  Log is computed via |r| + i*theta. We can ignore the sign of the      *
     *  real and imaginary parts of the input.                                */
    const double abs_x = tmpl_Double_Abs(z.dat[0]);
    const double abs_y = tmpl_Double_Abs(z.dat[1]);

    /*  The imaginary part is the argument. Compute using atan2.              */
    ln_z.dat[1] = tmpl_Double_Arctan2(z.dat[1], z.dat[0]);

    /*  To avoid overflow, find the exponent of the larger of the components. */
    w.r = TMPL_MAX(abs_x, abs_y);

    /*  Check that |z|^2 = x^2 + y^2 will not overflow.                       */
    if (w.bits.expo < TMPL_DOUBLE_BIAS + 0x200U)
    {
        /*  If x^2 + y^2 will not overflow, we can compute log(|z|)           *
         *  via log(|z|) = log(sqrt(x^2 + y^2)) = 0.5*log(x^2 + y^2). This    *
         *  saves us a sqrt call and speeds things up a bit.                  */
        if (w.bits.expo > TMPL_DOUBLE_BIAS - 0x1E6U)
            ln_z.dat[0] = 0.5 * tmpl_Double_Log(abs_x*abs_x + abs_y*abs_y);

        /*  The computation of x^2 + y^2 will underflow. Need to scale.       */
        else
        {
            /*  Special case, subnormal number or zero.                       */
            if (w.bits.expo == 0x00U)
            {
                /*  Normalize by scaling by 2^52. Then scale this value by    *
                 *  2^512 to ensure we will not underflow.                    */
                const double norm_x = abs_x * TMPL_DOUBLE_NORMALIZE;
                const double norm_y = abs_y * TMPL_DOUBLE_NORMALIZE;
                const double scale_x = norm_x * TMPL_BIG_SCALE;
                const double scale_y = norm_y * TMPL_BIG_SCALE;

                /*  r_sq is (2^(512 + 52))^2 * (x^2 + y^2).                   */
                const double r_sq = scale_x*scale_x + scale_y*scale_y;

                /*  We want 0.5 * log(x^2 + y^2). Half of log(r_sq) gives us  *
                 *  0.5*log(x^2 + y^2) + log(512 + 52). Subtracting off this  *
                 *  log(512 + 52) term gives us the correct value.            */
                ln_z.dat[0] = 0.5*tmpl_Double_Log(r_sq) - TMPL_NORMALIZE_FACTOR;
            }

            /*  x^2 + y^2 will underflow, but not subnormal. Need to scale up.*/
            else
            {
                /*  Scaling by 2^512 will ensure the computation does not     *
                 *  underflow.                                                */
                const double scale_x = abs_x * TMPL_BIG_SCALE;
                const double scale_y = abs_y * TMPL_BIG_SCALE;

                /*  r_sq is 2^(512 * 2) * (x^2 + y^2).                        */
                const double r_sq = scale_x*scale_x + scale_y*scale_y;

                /*  0.5*log(r_sq) gives 0.5*log(x^2 + y^2) + log(512). If     *
                 *  we subtract off log(512) we get the desired result.       */
                ln_z.dat[0] = 0.5*tmpl_Double_Log(r_sq) - TMPL_LOG_FACTOR;
            }
        }
    }

    /*  x^2 + y^2 will overflow. Need to scale down.                          */
    else
    {
        /*  Scale by 2^-512 to avoid overflow.                                */
        const double scale_x = abs_x * TMPL_RCPR_BIG_SCALE;
        const double scale_y = abs_y * TMPL_RCPR_BIG_SCALE;

        /*  r_sq is set to 2^(-1024) * (x^2 + y^2).                           */
        const double r_sq = scale_x*scale_x + scale_y*scale_y;

        /*  0.5*log(r_sq) gives us 0.5*log(x^2 + y^2) - log(512). By adding   *
         *  log(512) to the result we get the correct answer.                 */
        ln_z.dat[0] = 0.5*tmpl_Double_Log(r_sq) + TMPL_LOG_FACTOR;
    }

    return ln_z;
}
/*  End of tmpl_CDouble_Log.                                                  */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE
#undef TMPL_LOG_FACTOR
#undef TMPL_NORMALIZE_FACTOR

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Double precision complex log (clog equivalent (C99)).                     */
tmpl_ComplexDouble tmpl_CDouble_Log(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble ln_z;

    /*  Get the polar representation of the complex number z.                 */
    const double r = tmpl_Double_Hypot(z.dat[0], z.dat[1]);
    const double theta = tmpl_Double_Arctan2(z.dat[1], z.dat[0]);

    /*  The real part is just ln(r), and the imaginary part is theta.         */
    const double real = tmpl_Double_Log(r);

    /*  Using rectangular coordinates, create the output complex number.      */
    ln_z.dat[0] = real;
    ln_z.dat[1] = theta;
    return ln_z;
}
/*  End of tmpl_CDouble_Log.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
