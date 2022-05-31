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
 *                     tmpl_three_vector_normalize_float                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing unit normal vectors.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Normalize                                                *
 *  Purpose:                                                                  *
 *      Computes the unit normal of the input non-zero vector.                *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A non-zero vector in R^3.                                         *
 *  Output:                                                                   *
 *      P_hat (tmpl_ThreeVectorFloat):                                        *
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
 *      The function tmpl_3DFloat_Norm can overflow for very large values     *
 *      of x, y, and z. In particular, if x = y = z = FLT_MAX, the norm is    *
 *      sqrt(3)*FLT_MAX, which is greater than FLT_MAX, which may result in   *
 *      overflow or infinity. To avoid this, P is first scaled by 1/2. The    *
 *      largest possible result is then sqrt(3/4)*FLT_MAX, which is less than *
 *      FLT_MAX.                                                              *
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

/*  NaN is defined here.                                                      */
#include <libtmpl/include/tmpl_math.h>

/*  It's faster to check for large inputs, and NaN/Inf, with IEEE754 support. */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

/*  Function that normalizes non-zero three dimensional vectors.              */
tmpl_ThreeVectorFloat tmpl_3DFloat_Normalize(tmpl_ThreeVectorFloat P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float rcpr_norm, norm;
    tmpl_ThreeVectorFloat P_normalized;
    tmpl_IEEE754_Float wx, wy, wz;

    /*  Set the float parts of the unions to the components of the vector.    */
    wx.r = P.dat[0];
    wy.r = P.dat[1];
    wz.r = P.dat[2];

    /*  Check for large values.                                               */
    if (wx.bits.expo > TMPL_FLOAT_BIAS - 2U ||
        wy.bits.expo > TMPL_FLOAT_BIAS - 2U ||
        wz.bits.expo > TMPL_FLOAT_BIAS - 2U)
    {
        /*  Check for NaN or Inf.                                             */
        if (wx.bits.expo == TMPL_FLOAT_BIAS ||
            wy.bits.expo == TMPL_FLOAT_BIAS ||
            wz.bits.expo == TMPL_FLOAT_BIAS)
        {
            /*  If any component is NaN or Inf, the output is NaN.            */
            const float nanval = TMPL_NANF;
            P_normalized.dat[0] = nanval;
            P_normalized.dat[1] = nanval;
            P_normalized.dat[2] = nanval;
            return P_normalized;
        }

        /*  At least one component is very large. Scale the result by 1/2 to  *
         *  avoid overflow in the computation of ||P||.                       */
        else
        {
            P.dat[0] *= 0.5F;
            P.dat[1] *= 0.5F;
            P.dat[2] *= 0.5F;
        }
    }

    /*  Get the norm of the input vector P.                                   */
    norm = tmpl_3DFloat_L2_Norm(&P);

    /*  If the norm is zero we cannot normalize. Return NaN in this case.     */
    if (norm == 0.0F)
    {
        const float nanval = TMPL_NANF;
        P_normalized.dat[0] = nanval;
        P_normalized.dat[1] = nanval;
        P_normalized.dat[2] = nanval;
        return P_normalized;
    }
    else
    {
        /*  Compute the reciprocal of the norm. Precomputing a division and   *
         *  using multiplication later is faster than repeated division.      */
        rcpr_norm = 1.0F / norm;

        /*  Compute the components of the normalized vector.                  */
        P_normalized.dat[0] = P.dat[0]*rcpr_norm;
        P_normalized.dat[0] = P.dat[0]*rcpr_norm;
        P_normalized.dat[0] = P.dat[0]*rcpr_norm;
    }
    /*  End of if (norm == 0.0).                                              */

    return P_normalized;
}
/*  End of tmpl_3DFloat_Normalize.                                            */

#else
/*  Same algorithm without IEEE754 support.                                   */

/*  Function that normalizes non-zero three dimensional vectors.              */
tmpl_ThreeVectorFloat tmpl_3DFloat_Normalize(tmpl_ThreeVectorFloat P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float rcpr_norm, norm;
    tmpl_ThreeVectorFloat P_normalized;

    /*  Check if any of the components is NaN or Infinity.                    */
    if (tmpl_Float_Is_NaN_Or_Inf(P.dat[0]) ||
        tmpl_Float_Is_NaN_Or_Inf(P.dat[1]) ||
        tmpl_Float_Is_NaN_Or_Inf(P.dat[2]))
    {
        /*  If any component is NaN or Inf, the output is NaN.                */
        const float nanval = TMPL_NANF;
        P_normalized.dat[0] = nanval;
        P_normalized.dat[1] = nanval;
        P_normalized.dat[2] = nanval;
        return P_normalized;
    }

    /*  Check for large values.                                               */
    if (tmpl_Float_Abs(P.dat[0]) > 1.0E16F ||
        tmpl_Float_Abs(P.dat[1]) > 1.0E16F ||
        tmpl_Float_Abs(P.dat[2]) > 1.0E16F)
    {
        P.dat[0] *= 0.5F;
        P.dat[1] *= 0.5F;
        P.dat[2] *= 0.5F;
    }

    /*  Get the norm of the input vector P.                                   */
    norm = tmpl_3DFloat_L2_Norm(&P);

    /*  If the norm is zero we cannot normalize. Return NaN in this case.     */
    if (norm == 0.0F)
    {
        const float nanval = TMPL_NANF;
        P_normalized.dat[0] = nanval;
        P_normalized.dat[1] = nanval;
        P_normalized.dat[2] = nanval;
        return P_normalized;
    }
    else
    {
        /*  Compute the reciprocal of the norm. Precomputing a division and   *
         *  using multiplication later is faster than repeated division.      */
        rcpr_norm = 1.0F / norm;

        /*  Compute the components of the normalized vector.                  */
        P_normalized.dat[0] = P.dat[0]*rcpr_norm;
        P_normalized.dat[0] = P.dat[0]*rcpr_norm;
        P_normalized.dat[0] = P.dat[0]*rcpr_norm;
    }
    /*  End of if (norm == 0.0).                                              */

    return P_normalized;
}
/*  End of tmpl_3DFloat_Normalize.                                            */

#endif
/*  End #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1.   */
