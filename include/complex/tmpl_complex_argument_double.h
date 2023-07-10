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
 *                        tmpl_complex_argument_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex argument.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Argument                                                 *
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
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      arg (double):                                                         *
 *          The argument of z.                                                *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts and return atan2(y, x).          *
 *  Notes:                                                                    *
 *      Because the atan2 function is used, there is a discontinuity along    *
 *      the negative real axis. That is, the argument returns a real value    *
 *      in the interval (-pi, pi] (+pi is inclusive).                         *
 *                                                                            *
 *      This file is a fork of the code I wrote for rss_rinoccs.              *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing 2D arctan.                                 *
 *  3.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
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
 *      Changed src/complex/tmpl_complex_argument_double.c to include this.   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ARGUMENT_DOUBLE_H
#define TMPL_COMPLEX_ARGUMENT_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Arctan2 function found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Double precision complex argument function (carg equivalent).             */
TMPL_INLINE_DECL
double tmpl_CDouble_Argument(tmpl_ComplexDouble z)
{
    /*  Compute the argument using arctan and return.                         */
    return tmpl_Double_Arctan2(z.dat[1], z.dat[0]);
}
/*  End of tmpl_CDouble_Argument.                                             */

#endif
/*  End of include guard.                                                     */
