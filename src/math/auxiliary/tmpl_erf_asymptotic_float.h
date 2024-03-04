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
 *                          tmpl_erf_asymptotic_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the erf(x) for large positive x at single precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Erf_Asymptotic                                             *
 *  Purpose:                                                                  *
 *      Computes the error function for x >= 2.                               *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      erf_x (float):                                                        *
 *          The error function evaluated at x.                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      For x >= 4 we have |1 - erf(x)| < 2^-23, single epsilon. Return 1     *
 *      for this. Otherwise shift the domain to (-1, 1) and use a Remez       *
 *      minimax polynomial.                                                   *
 *  Notes:                                                                    *
 *      Only accurate for x >= 2. For negative values use the reflection      *
 *      formula erf(x) = -erf(-x).                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 26, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_ASYMPTOTIC_FLOAT_H
#define TMPL_ERF_ASYMPTOTIC_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez minimax polynomial.                            */
#define P00 (+9.9997798519705139707949243763526723251486810350162E-01F)
#define P01 (+1.3954354705032530273930629828583460941369062191048E-04F)
#define P02 (-4.2098917046748055987556719849874210989117124613863E-04F)
#define P03 (+7.8541382785647088528671048927967006410458503908693E-04F)
#define P04 (-1.0219602901238967754226405922295093184761207176382E-03F)
#define P05 (+1.0268652203475430150177042120773218825236149168701E-03F)
#define P06 (-7.9295126880966289610788143908378925133464057341691E-04F)
#define P07 (+3.8711969695275056765048091024139398543569940470385E-04F)
#define P08 (-8.0959154295579755674836826905608828526197333298183E-05F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
P00+z*(P01+z*(P02+z*(P03+z*(P04+z*(P05+z*(P06+z*(P07+z*P08)))))))

/*  Function for computing erf(x) for large positive values.                  */
TMPL_STATIC_INLINE
float tmpl_Float_Erf_Asymptotic(float x)
{
    /*  For large enough x use the limit, erf(infinity) = 1.                  */
    if (x > 4.0F)
        return 1.0F;

    /*  Otherwise avoid round-off error by shifting the domain to (-1, 1) and *
     *  using a Remez minimax polynomial.                                     */
    else
    {
        /*  Evaluate the polynomial using Horner's method and return.         */
        const float z = x - 3.0F;
        return TMPL_POLY_EVAL(z);
    }
}
/*  End of tmpl_Float_Erf_Asymptotic.                                         */

/*  #undef everything in case someone wants to #include this file.            */
#undef TMPL_POLY_EVAL
#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef P06
#undef P07
#undef P08

#endif
/*  End of include guard.                                                     */
