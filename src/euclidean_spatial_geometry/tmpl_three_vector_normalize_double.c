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
 *  1.) tmpl_euclidean_spatial_geometry.h:                                    *
 *          Header containing ThreeVector typedef and the function prototype. *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/03/02: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Square root function found here.                                          */
#include <libtmpl/include/tmpl_math.h>

/*  If the user has not requested tmpl algorithms, use functions from math.h. */
#if TMPL_USE_MATH_ALGORITHMS != 1
#include <math.h>

/*  Set macros for the square root and absolute value functions for later.    *
 *  this avoids more checks for TMPL_USE_MATH_ALGORITHMS in the code.         */
#define square_root sqrt
#define absolute_value fabs

#else
/*  Else for #if TMPL_USE_MATH_ALGORITHMS != 1                                */

/*  If the user requested tmpl algorithm, alias the appropriate functions.    */
#define square_root tmpl_Double_Sqrt
#define absolute_value tmpl_Double_Abs

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

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
    double x = absolute_value(P->dat[0]);
    double y = absolute_value(P->dat[1]);
    double z = absolute_value(P->dat[2]);

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
    rcpr_norm = 1.0 / square_root(x*x + y*y + z*z);

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
tmpl_ThreeVectorDouble tmpl_3DDouble_Normalize(tmpl_ThreeVectorDouble *P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double rcpr_norm, norm, t, u, v, rcpr_t;
    tmpl_ThreeVectorDouble P_normalized;

    /*  Check if any of the components is NaN or Infinity.                    */
    if (tmpl_Double_Is_NaN_Or_Inf(P->dat[0]) ||
        tmpl_Double_Is_NaN_Or_Inf(P->dat[1]) ||
        tmpl_Double_Is_NaN_Or_Inf(P->dat[2]))
    {
        /*  If any component is NaN or Inf, the output is NaN.                */
        const double nanval = TMPL_NAN;
        P_normalized.dat[0] = nanval;
        P_normalized.dat[1] = nanval;
        P_normalized.dat[2] = nanval;
        return P_normalized;
    }

    P->dat[0] = tmpl_Double_Abs(P->dat[0]);
    P->dat[1] = tmpl_Double_Abs(P->dat[1]);
    P->dat[2] = tmpl_Double_Abs(P->dat[2]);

    /*  Check for large values.                                               */
    if (P->dat[0] > 1.0E24 || P->dat[1] > 1.0E24 || P->dat[2] > 1.0E24)
    {
        P->dat[0] *= 0.5;
        P->dat[1] *= 0.5;
        P->dat[2] *= 0.5;
    }

    /*  Get the norm of the input vector P.                                   */

    if (P->dat[0] < P->dat[1])
    {
        if (P->dat[1] < P->dat[2])
        {
            t = P->dat[2];
            u = P->dat[0];
            v = P->dat[1];
        }
        else
        {
            t = P->dat[1];
            u = P->dat[0];
            v = P->dat[2];
        }
    }
    else
    {
        if (P->dat[2] < P->dat[0])
        {
            t = P->dat[0];
            u = P->dat[1];
            v = P->dat[2];
        }
        else
        {
            t = P->dat[2];
            u = P->dat[0];
            v = P->dat[1];
        }
    }

    rcpr_t = 1.0 / t;
    u = u*rcpr_t;
    v = v*rcpr_t;

#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 0
    norm = t*sqrt(1.0 + u*u + v*v);
#else
    norm = t*tmpl_Double_Sqrt(1.0 + u*u + v*v);
#endif

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
