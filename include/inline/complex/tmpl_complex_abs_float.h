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
 *                           tmpl_complex_abs_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex modulus (absolute value).        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Abs                                                       *
 *  Purpose:                                                                  *
 *      Computes the absolute value, or modulus, of a complex number:         *
 *                                                                            *
 *          |z| = |x + iy| = sqrt(x^2 + y^2)                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat):                                                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_z (float):                                                        *
 *          The absolute value of z.                                          *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_Hypot:                                                 *
 *              Function for computing the magnitude of the vector (x, y).    *
 *  Method:                                                                   *
 *      The absolute value of a complex number is the distance from the given *
 *      point and the origin. This is computed via the Pythagorean formula.   *
 *      Given z = x + iy, which we identify as the point (x, y) in the plane, *
 *      the absolute value, or modulus, is:                                   *
 *                                                                            *
 *          |z| = ||(x, y)|| = sqrt(x^2 + y^2)                                *
 *                                                                            *
 *      The intermediate computation x^2 + y^2 may overflow for large inputs. *
 *      This is mitigated using the hypot function. We pass the real and      *
 *      imaginary parts to tmpl_Float_Hypot for the computation.              *
 *  Error:                                                                    *
 *      Based on 268,435,456 random samples:                                  *
 *          Max Relative Error: 1.192092e-07                                  *
 *          RMS Relative Error: 3.451446e-08                                  *
 *      Values assume 100% accuracy of glibc. Actual error in glibc is        *
 *      less than 1 ULP (~1 x 10^-7).                                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          TMPL_INLINE_DECL macro found here.                                *
 *  2.) tmpl_complex_float.h:                                                 *
 *          Header providing single precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved main algorithm to tmpl_hypot_float.c Function now passes the    *
 *      the real and imaginary parts to tmpl_Float_Hypot.                     *
 *  2023/07/06: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_abs_float.c to include this file.    *
 *  2024/09/18: Ryan Maguire                                                  *
 *      Made inline method consistent with other inline routines.             *
 *      tmpl_complex.h is not needed (just tmpl_complex_float.h), and         *
 *      extern is provided for tmpl_Float_Hypot so that tmpl_math.h is not    *
 *      needed explicitly.                                                    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ABS_FLOAT_H
#define TMPL_COMPLEX_ABS_FLOAT_H

/*  The TMPL_INLINE_DECL macro is found here.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_float.h>

/*  The hypot function does all of the heavy lifting.                         */
extern float tmpl_Float_Hypot(float x, float y);

/*  Function for computing the magnitude, or modulus, of a complex number.    */
TMPL_INLINE_DECL
float tmpl_CFloat_Abs(tmpl_ComplexFloat z)
{
    return tmpl_Float_Hypot(z.dat[0], z.dat[1]);
}
/*  End of tmpl_CFloat_Abs.                                                   */

#endif
/*  End of include guard.                                                     */
