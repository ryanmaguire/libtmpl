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
 *                        tmpl_complex_argument_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex argument.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Argument                                                  *
 *  Purpose:                                                                  *
 *      Computes the argument of a complex number:                            *
 *                                                                            *
 *          arg(z) =  arg(r * exp(i theta)) = theta                           *
 *                                                                            *
 *      Equivalently:                                                         *
 *                                                                            *
 *          arg(z) = arg(x + iy) = arctan(y, x)                               *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat):                                                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      arg (float):                                                          *
 *          The argument of z.                                                *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_Arctan2:                                               *
 *              Computes the angle the point (x, y) makes with the x axis.    *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts and return atan2(y, x).          *
 *  Notes:                                                                    *
 *      1.) Because the atan2 function is used, there is a discontinuity      *
 *          along the negative real axis. That is, the argument returns a     *
 *          real value in the interval (-pi, pi] (+pi is inclusive).          *
 *      2.) No checks for NaN or infinity are performed explicitly. The       *
 *          tmpl_Float_Arctan2 function handles NaN and infinity as           *
 *          special cases.                                                    *
 *      3.) This file is a fork of code I wrote for rss_rinoccs.              *
 *          librssringoccs is also released under GPL3.                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_complex_float.h:                                                 *
 *          Header providing single precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/02 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Made compatible with the rest of libtmpl.                             *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2021/06/26: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 *  2023/02/06: Ryan Maguire                                                  *
 *      Moved float and long double to their own files. Inlined routines.     *
 *  2023/07/10: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_argument_float.c to include this.    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ARGUMENT_FLOAT_H
#define TMPL_COMPLEX_ARGUMENT_FLOAT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_float.h>

/*  Tell the compiler about the arctan2 function. Provided by tmpl_math.h.    */
extern float tmpl_Float_Arctan2(float y, float x);

/*  Single precision complex argument function (cargf equivalent).            */
TMPL_INLINE_DECL
float tmpl_CFloat_Argument(tmpl_ComplexFloat z)
{
    /*  Compute the argument using arctan and return.                         */
    return tmpl_Float_Arctan2(z.dat[1], z.dat[0]);
}
/*  End of tmpl_CFloat_Argument.                                              */

#endif
/*  End of include guard.                                                     */
