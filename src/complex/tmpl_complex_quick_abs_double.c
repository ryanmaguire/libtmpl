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
 *      "quickly". This method is about 1.5 times faster than the default one *
 *      but may overflow for certain values.                                  *
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
 *      tests indicate that this is about 1.5x slower. The naive method is    *
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
 *      tmpl_Double_Sqrt        (tmpl_math.h)                                 *
 *          Computes the square root of a real number.                        *
 *  Notes:                                                                    *
 *      This code is a fork of the code I wrote for rss_ringoccs.             *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_USE_INLINE macro.                 *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing basic math functions.                      *
 *  3.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
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
 *      Changed this to "QuickAbs". Numbers greater than sqrt(DBL_MAX) will   *
 *      overflow using this method. On most computers, this is 10^154. These  *
 *      numbers shouldn't overflow for a proper implementation of complex abs.*
 *      A proper implementation is now implemented in tmpl_CDouble_Abs. These *
 *      functions are 1.3-1.5x faster and are kept for users who will not be  *
 *      using large numbers but would prefer speed.                           *
 *  2023/02/06: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files.              *
 ******************************************************************************/

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only used if inline support is not requested.                */
#if TMPL_USE_INLINE != 1

/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are given and where complex types are defined.       */
#include <libtmpl/include/tmpl_complex.h>

/*  Double precision complex abs function (cabs equivalent).                  */
double tmpl_CDouble_Quick_Abs(tmpl_ComplexDouble z)
{
    /*  The absolute value is just sqrt(x^2 + y^2) so compute this.           */
    return tmpl_Double_Sqrt(z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1]);
}
/*  End of tmpl_CDouble_Quick_Abs.                                            */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
