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
 *                       tmpl_complex_are_equal_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks for equality of two complex numbers.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Are_Equal                                                *
 *  Purpose:                                                                  *
 *      Checks two complex numbers for equality.                              *
 *  Arguments:                                                                *
 *      z0 (tmpl_ComplexDouble):                                              *
 *          A complex number.                                                 *
 *      z1 (tmpl_ComplexDouble):                                              *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      compare (tmpl_Bool):                                                  *
 *          True if z0 = z1, false otherwise.                                 *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts of both inputs and compare them. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains the TMPL_INLINE_DECL macro.                              *
 *  2.) tmpl_complex_double.h:                                                *
 *          Header providing double precision complex numbers.                *
 *  3.) tmpl_bool.h:                                                          *
 *          Header containing Boolean typedef.                                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/02: Ryan Maguire                                                  *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2024/05/10: Ryan Maguire                                                  *
 *      Renamed to "Are_Equal" instead of "Compare".                          *
 *      Moved float and long double to their own files.                       *
 *      Converted into an inline function.                                    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ARE_EQUAL_DOUBLE_H
#define TMPL_COMPLEX_ARE_EQUAL_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Boolean data type and True/False are defined here.                        */
#include <libtmpl/include/tmpl_bool.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  Double precision complex comparison.                                      */
TMPL_INLINE_DECL
tmpl_Bool tmpl_CDouble_Are_Equal(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  C does not allow structures to be compared, so we need to compare the *
     *  members of the two complex structs. Two complex numbers are equal if  *
     *  and only if their real and imaginary parts are equal. Check this.     */
    if ((z0.dat[0] == z1.dat[0]) && (z0.dat[1] == z1.dat[1]))
        return tmpl_True;

    return tmpl_False;
}
/*  End of tmpl_CDouble_Are_Equal.                                            */

#endif
/*  End of include guard.                                                     */
