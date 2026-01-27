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
 *                         tmpl_vec3_normalize_double                         *
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
 *      P (const tmpl_ThreeVectorDouble * const):                             *
 *          A non-zero vector in R^3.                                         *
 *  Output:                                                                   *
 *      P_hat (tmpl_ThreeVectorDouble):                                       *
 *          The unit normal of P.                                             *
 *  IEEE-754 Version:                                                         *
 *      Method:                                                               *
 *          Use the definition of unit normal. If P = (x, y, z), the norm is: *
 *                                                                            *
 *              norm = sqrt(x^2 + y^2 + z^2).                                 *
 *                                                                            *
 *          For a non-zero vector norm is positive. The unit normal is        *
 *          given by:                                                         *
 *                                                                            *
 *              P_hat = P / norm                                              *
 *                                                                            *
 *          To avoid overflow, or underflow, we first scale the input to      *
 *          have a "reasonable" magnitude. The norm is then computed and this *
 *          division is carried out.                                          *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Sqrt:                                             *
 *                  Computes the square root of a real number.                *
 *  Portable Version:                                                         *
 *      Method:                                                               *
 *          Similar to the IEEE-754 method, but without checking if the       *
 *          normalization will overflow or underflow in the intermediate      *
 *          steps.                                                            *
 *      Called Functions:                                                     *
 *          tmpl_vec3.h:                                                      *
 *              tmpl_3DDouble_L2_Norm:                                        *
 *                  Computes the norm of a vector.                            *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      If the vector is zero, (NaN, NaN, NaN) is returned.                   *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_max.h:                                                           *
 *          Provides a helper macro for computing the max of 3 real numbers.  *
 *  2.) tmpl_math.h:                                                          *
 *          Provides the square root function.                                *
 *  3.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/03/02: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 *  2024/06/10: Ryan Maguire                                                  *
 *      Fixed bug for vectors with negative components.                       *
 ******************************************************************************/

/*  square root function provided here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Safer and more efficient computation with IEEE-754 support.               */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  The TMPL_MAX3 macro is found here.                                        */
#include <libtmpl/include/helper/tmpl_max.h>

/*  The values 2^512 and 2^-512, to double precision, stored as macros.       */
#define TMPL_BIG_SCALE (1.340780792994259709957402E+154)
#define TMPL_RCPR_BIG_SCALE (7.458340731200206743290965E-155)

/*  Function for computing the unit normal of a given vector.                 */
tmpl_ThreeVectorDouble
tmpl_3DDouble_Normalize(const tmpl_ThreeVectorDouble * const P)
{
    /*  Words for the components of the vector.                               */
    tmpl_IEEE754_Double wx, wy, wz;

    /*  Variable for storing the exponent of the largest component.           */
    unsigned int max_expo;

    /*  Variables for the multiplicative factors used in normalizing.         */
    double norm, rcpr_norm;

    /*  And lastly, a variable for the output.                                */
    tmpl_ThreeVectorDouble normalized;

    /*  Copy the data from P to avoid overwriting it.                         */
    wx.r = P->dat[0];
    wy.r = P->dat[1];
    wz.r = P->dat[2];

    /*  Get the exponent of the largest component.                            */
    max_expo = TMPL_MAX3(wx.bits.expo, wy.bits.expo, wz.bits.expo);

    /*  If this exponent is very large, scale the components down.            */
    if (max_expo > TMPL_DOUBLE_UBIAS + 0x200U)
    {
        wx.r *= TMPL_RCPR_BIG_SCALE;
        wy.r *= TMPL_RCPR_BIG_SCALE;
        wz.r *= TMPL_RCPR_BIG_SCALE;
    }

    /*  If it is very small, scale the components up.                         */
    else if (max_expo < TMPL_DOUBLE_UBIAS - 0x1E6U)
    {
        /*  If the components are denormal, normalize them.                   */
        if (max_expo == 0x00U)
        {
            wx.r *= TMPL_DOUBLE_NORMALIZE;
            wy.r *= TMPL_DOUBLE_NORMALIZE;
            wz.r *= TMPL_DOUBLE_NORMALIZE;
        }

        wx.r *= TMPL_BIG_SCALE;
        wy.r *= TMPL_BIG_SCALE;
        wz.r *= TMPL_BIG_SCALE;
    }

    /*  The components are now safe to square. Compute the norm.              */
    norm = tmpl_Double_Sqrt(wx.r*wx.r + wy.r*wy.r + wz.r*wz.r);

    /*  The reciprocal of the norm is used as the scale factor.               */
    rcpr_norm = 1.0 / norm;

    /*  Compute the unit normal and return.                                   */
    normalized.dat[0] = wx.r * rcpr_norm;
    normalized.dat[1] = wy.r * rcpr_norm;
    normalized.dat[2] = wz.r * rcpr_norm;
    return normalized;
}
/*  End of tmpl_3DDouble_Normalize.                                           */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Lacking IEEE-754 support, we just used the standard definition. This may  *
 *  not catch certain overflows. For example, is x = y = z = DBL_MAX, this    *
 *  should normalize to (1/sqrt(3)) * (1, 1, 1). But the norm of (x, y, z) is *
 *  sqrt(3) * DBL_MAX, which will overflow. Because of this the output will   *
 *  be infinite. Aside from these extreme cases, this method is very portable.*/

/*  Function for computing the unit normal of a given vector.                 */
tmpl_ThreeVectorDouble
tmpl_3DDouble_Normalize(const tmpl_ThreeVectorDouble * const P)
{
    /*  Scale factor for the normalization.                                   */
    const double norm = tmpl_3DDouble_L2_Norm(P);
    const double rcpr_norm = 1.0 / norm;

    /*  Variable for the output.                                              */
    tmpl_ThreeVectorDouble normalized;

    /*  Normalize the input and return.                                       */
    normalized.dat[0] = P->dat[0] * rcpr_norm;
    normalized.dat[1] = P->dat[1] * rcpr_norm;
    normalized.dat[2] = P->dat[2] * rcpr_norm;
    return normalized;
}
/*  End of tmpl_3DDouble_Normalize.                                           */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
