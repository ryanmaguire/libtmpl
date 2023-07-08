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
 *                        tmpl_complex_add_imag_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Add_Imag                                                *
 *  Purpose:                                                                  *
 *      Adds an imaginary number to a complex one.                            *
 *                                                                            *
 *          w = z + iy = (a + ib) + iy = a + i(b + y)                         *
 *                                                                            *
 *  Arguments:                                                                *
 *      y (long double):                                                      *
 *          The imaginary number we wish to add to z.                         *
 *      z (tmpl_ComplexLongDouble):                                           *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      w (tmpl_ComplexLongDouble):                                           *
 *          The sum of z and iy.                                              *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Add the real-valued input to the imaginary part of the complex number.*
 *  Notes:                                                                    *
 *      This file is a fork of the code I wrote for rss_ringoccs.             *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/12/03: Ryan Maguire                                                  *
 *      Created function (Wellesley college for librssringoccs).              *
 *      Moved here from rss_ringoccs_complex_add.c.                           *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Made compatible with libtmpl.                                         *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2021/06/03: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 *  2023/02/06: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files.              *
 *      Added inline support.                                                 *
 *  2023/07/06: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_add_imag_ldouble.c to use this file. *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ADD_IMAG_LDOUBLE_H
#define TMPL_COMPLEX_ADD_IMAG_LDOUBLE_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, long doubles and _Complex *
 *  long doubles can be added via y*_Complex_I + z. With C89 we use structs to*
 *  define complex numbers. Since we can't add a long double to a struct, and *
 *  since the _Complex_I macro is undefined, we need a function for computing *
 *  the sum of complex numbers with imaginary ones.                           */

/*  Long double precision complex addition where one variable is imaginary.   */
TMPL_INLINE_DECL
tmpl_ComplexLongDouble
tmpl_CLDouble_Add_Imag(long double y, tmpl_ComplexLongDouble z)
{
    /*  Add the value to the imaginary part of the complex number and return. */
    z.dat[1] += y;
    return z;
}
/*  End of tmpl_CLDouble_Add_Imag.                                            */

#endif
/*  End of include guard.                                                     */
