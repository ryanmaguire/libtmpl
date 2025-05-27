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
 *                          tmpl_complex_abs_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex modulus (absolute value).        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Abs                                                      *
 *  Purpose:                                                                  *
 *      Computes the absolute value, or modulus, of a complex number:         *
 *                                                                            *
 *          |z| = |x + iy| = sqrt(x^2 + y^2)                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_z (double):                                                       *
 *          The absolute value of z.                                          *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Hypot:                                                *
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
 *      imaginary parts to tmpl_Double_Hypot for the computation.             *
 *  Error:                                                                    *
 *      Based on 134,217,728 random samples:                                  *
 *          Max Relative Error: 2.220446e-16                                  *
 *          RMS Relative Error: 3.751642e-17                                  *
 *      Values assume 100% accuracy of glibc. Actual error in glibc is        *
 *      less than 1 ULP (~2 x 10^-16).                                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          TMPL_INLINE_DECL macro found here.                                *
 *  2.) tmpl_complex_double.h:                                                *
 *          Header providing double precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley college for librssringoccs).                  *
 *  2020/12/01: Ryan Maguire                                                  *
 *      Added abs squared functions.                                          *
 *  2020/12/02: Ryan Maguire                                                  *
 *      Moved abs squared functions to their own file.                        *
 *      Frozen for rss_ringoccs v1.3.                                         *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from librssringoccs to libtmpl.                                *
 *      Edited code, made it compatibile with the rest of libtmpl. Removed    *
 *      "C99" mode. Removed complex.h as a dependency.                        *
 *      Soft freeze for alpha version of libtmpl.                             *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited license.                                                       *
 *  2021/05/11: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 *  2021/10/19: Ryan Maguire                                                  *
 *      Changed the algorithm to prevent certain numbers from overflowing.    *
 *      Complex numbers with a magnitude greater than sqrt(DBL_MAX) will      *
 *      overflow, even though they shouldn't for a proper implementation.     *
 *      This has been fixed, albeit at the expense of speed.                  *
 *  2022/04/28: Ryan Maguire                                                  *
 *      Changed algorithm to incorporate IEEE-754 tricks. 1.4x speed up.      *
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved main algorithm to tmpl_hypot_double.c Function now passes the   *
 *      the real and imaginary parts to tmpl_Double_Hypot.                    *
 *  2023/07/06: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_abs_double.c to include this file.   *
 *  2024/09/18: Ryan Maguire                                                  *
 *      Made inline method consistent with other inline routines.             *
 *      tmpl_complex.h is not needed (just tmpl_complex_double.h), and        *
 *      extern is provided for tmpl_Double_Hypot so that tmpl_math.h is not   *
 *      needed explicitly.                                                    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ABS_DOUBLE_H
#define TMPL_COMPLEX_ABS_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  The hypot function does all of the heavy lifting.                         */
extern double tmpl_Double_Hypot(double x, double y);

/*  Function for computing the magnitude, or modulus, of a complex number.    */
TMPL_INLINE_DECL
double tmpl_CDouble_Abs(tmpl_ComplexDouble z)
{
    return tmpl_Double_Hypot(z.dat[0], z.dat[1]);
}
/*  End of tmpl_CDouble_Abs.                                                  */

#endif
/*  End of include guard.                                                     */
