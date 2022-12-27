/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                     tmpl_three_vector_normalize_double                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing unit normal vectors.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Normalize                                               *
 *  Purpose:                                                                  *
 *      Computes the unit normal of the input non-zero vector.                *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorDouble):                                           *
 *          A non-zero vector in R^3.                                         *
 *  Output:                                                                   *
 *      P_hat (tmpl_ThreeVectorDouble):                                       *
 *          The unit normal of P.                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of unit normal. If P = (x, y, z), the norm is:     *
 *                                                                            *
 *          norm = sqrt(x^2 + y^2 + z^2).                                     *
 *                                                                            *
 *      For a non-zero vector norm is positive. The unit normal is given by:  *
 *                                                                            *
 *          P_hat = P / norm                                                  *
 *                                                                            *
 *      The function tmpl_3DDouble_Norm can overflow for very large values    *
 *      of x, y, and z. In particular, if x = y = z = DBL_MAX, the norm is    *
 *      sqrt(3)*DBL_MAX, which is greater than DBL_MAX, which may result in   *
 *      overflow or infinity. To avoid this, P is first scaled by 1/2. The    *
 *      largest possible result is then sqrt(3/4)*DBL_MAX, which is less than *
 *      DBL_MAX.                                                              *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      If the vector is zero, (NaN, NaN, NaN) is returned.                   *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/03/02: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Square root function found here.                                          */
#include <libtmpl/include/tmpl_math.h>

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  The values 2^512 and 2^-512, to double precision, stored as macros.       */
#define BIG_SCALE 1.340780792994259709957402E+154
#define RCPR_BIG_SCALE 7.458340731200206743290965E-155

/*  Function for computing the length of three dimensional vectors.           */
tmpl_ThreeVectorDouble tmpl_3DDouble_Normalize(const tmpl_ThreeVectorDouble *P)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ThreeVectorDouble normalized;
    tmpl_IEEE754_Double w;
    double rcpr_norm;

    /*  Given P = (x, y, z), compute |x|, |y|, and |z|.                       */
    double x = tmpl_Double_Abs(P->dat[0]);
    double y = tmpl_Double_Abs(P->dat[1]);
    double z = tmpl_Double_Abs(P->dat[2]);

    /*  Compute the maximum of |x|, |y|, and |z| and store it in the double   *
     *  part of the tmpl_IEEE754_Double union w. This syntax from the C       *
     *  language is a bit strange. a = (b < c ? c : b) says if b is less than *
     *  c, set a to c, otherwise set a to b. Below we do this twice, setting  *
     *  w.r to the maximum of |x|, |y|, and |z|.                              */
    w.r = (x < y ? (y < z ? z : y) : (x < z ? z : x));

    /*  If all values are large, scale them by 2^-512.                        */
    if (w.bits.expo > TMPL_DOUBLE_BIAS + 0x1FFU)
    {
        x *= BIG_SCALE;
        y *= BIG_SCALE;
        z *= BIG_SCALE;
    }

    /*  If all values are small, scale them by 2^512.                         */
    else if (w.bits.expo < 0x20AU)
    {
        x *= RCPR_BIG_SCALE;
        y *= RCPR_BIG_SCALE;
        z *= RCPR_BIG_SCALE;
    }

    /*  Compute 1 / ||P||.                                                    */
    rcpr_norm = 1.0 / tmpl_Double_Sqrt(x*x + y*y + z*z);

    /*  Set P_hat to (x/||P||, y/||P||, z/||P||) and return.                  */
    normalized.dat[0] = x*rcpr_norm;
    normalized.dat[1] = y*rcpr_norm;
    normalized.dat[2] = z*rcpr_norm;
    return normalized;
}
/*  End of tmpl_3DDouble_L2_Norm.                                             */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef BIG_SCALE
#undef RCPR_BIG_SCALE

#else
/*  Same algorithm without IEEE754 support.                                   */

/*  Function that normalizes non-zero three dimensional vectors.              */
tmpl_ThreeVectorDouble tmpl_3DDouble_Normalize(const tmpl_ThreeVectorDouble *P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double rcpr_norm, norm, t, rcpr_t;
    tmpl_ThreeVectorDouble P_normalized;

    /*  Given P = (x, y, z), compute |x|, |y|, and |z|.                       */
    double x = tmpl_Double_Abs(P->dat[0]);
    double y = tmpl_Double_Abs(P->dat[1]);
    double z = tmpl_Double_Abs(P->dat[2]);

    /*  Compute the maximum of |x|, |y|, and |z| and store it in the double   *
     *  part of the tmpl_IEEE754_Double union w. This syntax from the C       *
     *  language is a bit strange. a = (b < c ? c : b) says if b is less than *
     *  c, set a to c, otherwise set a to b. Below we do this twice, setting  *
     *  w.r to the maximum of |x|, |y|, and |z|.                              */
    t = (x < y ? (y < z ? z : y) : (x < z ? z : x));

    /*  Get the norm of the input vector P.                                   */
    rcpr_t = 1.0 / t;
    x *= rcpr_t;
    y *= rcpr_t;
    z *= rcpr_t;
    norm = t*tmpl_Double_Sqrt(x*x + y*y + z*z);

    /*  If the norm is zero we cannot normalize. Return NaN in this case.     */
    if (norm == 0.0)
    {
        const double nanval = TMPL_NAN;
        P_normalized.dat[0] = nanval;
        P_normalized.dat[1] = nanval;
        P_normalized.dat[2] = nanval;
        return P_normalized;
    }
    else
    {
        /*  Compute the reciprocal of the norm. Precomputing a division and   *
         *  using multiplication later is faster than repeated division.      */
        rcpr_norm = 1.0 / norm;

        /*  Compute the components of the normalized vector.                  */
        P_normalized.dat[0] = P->dat[0]*rcpr_norm;
        P_normalized.dat[1] = P->dat[1]*rcpr_norm;
        P_normalized.dat[2] = P->dat[2]*rcpr_norm;
    }
    /*  End of if (norm == 0.0).                                              */

    return P_normalized;
}
/*  End of tmpl_3DDouble_Normalize.                                           */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
