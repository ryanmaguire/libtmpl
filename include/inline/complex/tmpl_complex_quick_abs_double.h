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
 *                       tmpl_complex_quick_abs_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex modulus (absolute value), done   *
 *      "quickly". This method is up to 1.5 times faster than the default one *
 *      but is susceptible to underflow and overflow.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Quick_Abs                                                *
 *  Purpose:                                                                  *
 *      Computes the absolute value, or modulus, of a complex number:         *
 *                                                                            *
 *          |z| = |x + iy| = sqrt(x^2 + y^2)                                  *
 *                                                                            *
 *      Because x^2 and y^2 are computed as intermediate steps, this method   *
 *      will overflow for values greater than sqrt(DBL_MAX). The safe way to  *
 *      do this is via:                                                       *
 *                                                                            *
 *          |z| = |x| sqrt(1+(y/x)^2)                                         *
 *                                                                            *
 *      if |x| > |y|, and:                                                    *
 *                                                                            *
 *          |z| = |y| sqrt(1 + (x/y)^2)                                       *
 *                                                                            *
 *      otherwise. This involves computing |x|, |y|, and seeing which one is  *
 *      the max as intermediate steps, and a division. The resulting time     *
 *      tests indicate that this is up to 1.5x slower. The naive method is    *
 *      kept here in case the user needs extra speed and is not worried about *
 *      overflowing. On IEEE-754 compliant implementations, this means        *
 *      working with numbers less than 10^154, which is very plausible.       *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_z (double):                                                       *
 *          The absolute value of z.                                          *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Sqrt:                                                 *
 *              Computes the square root of a real number.                    *
 *  Notes:                                                                    *
 *      1.) This function is susceptible to underflow and overflow, but it is *
 *          faster than tmpl_CDouble_Abs. Only use this function when you are *
 *          sure that the square of the input will not underflow or overflow. *
 *                                                                            *
 *      2.) There are no checks for NaN or infinity. NaN inputs will produce  *
 *          NaN, and infinity (positive or negative) will output infinity.    *
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
 *      Changed this to "Quick_Abs". Numbers greater than sqrt(DBL_MAX) will  *
 *      overflow using this method. On most computers this is 10^154. These   *
 *      numbers shouldn't overflow for a proper implementation of complex abs.*
 *      A proper implementation is now implemented in tmpl_CDouble_Abs. These *
 *      functions are 1.3-1.5x faster and are kept for users who will not be  *
 *      using large numbers but would prefer speed.                           *
 *  2023/02/06: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files.              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_QUICK_ABS_DOUBLE_H
#define TMPL_COMPLEX_QUICK_ABS_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  Tell the compiler about the square root function.                         */
extern double tmpl_Double_Sqrt(double x);

/*  Double precision complex abs function (cabs equivalent).                  */
TMPL_INLINE_DECL
double tmpl_CDouble_Quick_Abs(tmpl_ComplexDouble z)
{
    /*  The absolute value is just sqrt(x^2 + y^2) so compute this.           */
    return tmpl_Double_Sqrt(z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1]);
}
/*  End of tmpl_CDouble_Quick_Abs.                                            */

#endif
/*  End of include guard.                                                     */
