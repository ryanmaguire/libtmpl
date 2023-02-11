/******************************************************************************
 *                                 LICENSE                                    *
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
 *                            tmpl_complex_add                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Add:                                                      *
 *      tmpl_CDouble_Add:                                                     *
 *      tmpl_CLDouble_Add:                                                    *
 *  Purpose:                                                                  *
 *      Adds two complex numbers:                                             *
 *                                                                            *
 *          z + w = (a + ib) + (c + id) = (a + c) + i(b + d)                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      sum (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):              *
 *          The sum of z and w.                                               *
 *  Called Functions:                                                         *
 *      tmpl_CFloat_Real_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Real_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Real_Part (tmpl_complex.h)                              *
 *          Returns the real part of a complex number.                        *
 *      tmpl_CFloat_Imag_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Imag_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Imag_Part (tmpl_complex.h)                              *
 *          Returns the imaginary part of a complex number.                   *
 *      tmpl_CFloat_Rect        (tmpl_complex.h)                              *
 *      tmpl_CDouble_Rect       (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Rect      (tmpl_complex.h)                              *
 *          Creates a complex number from two real ones.                      *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts and compute a component-wise sum.*
 *  Notes:                                                                    *
 *      This file is a fork of the code I wrote for rss_ringoccs.             *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains the TMPL_USE_INLINE macro.                               *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/02: Ryan Maguire                                                  *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Edited to make compatibile with libtmpl.                              *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2021/05/11: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 *  2022/09/08: Ryan Maguire                                                  *
 *      Greatly simplified code. Added inline support.                        *
 ******************************************************************************/

/*  TMPL_USE_INLINE found here.                                               */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if defined(TMPL_USE_INLINE) && TMPL_USE_INLINE != 1

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z0  *
 *  and double _Complex z1, you can just do z0 + z1. With C89 we use structs  *
 *  to define complex numbers. Structs cannot be added, so we need a function *
 *  for computing the sum of two complex values.                              */

/*  Single precision complex addition.                                        */
tmpl_ComplexFloat tmpl_CFloat_Add(tmpl_ComplexFloat z0, tmpl_ComplexFloat z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat sum;

    /*  The sum of two complex numbers simply adds their components.          */
    sum.dat[0] = z0.dat[0] + z1.dat[0];
    sum.dat[1] = z0.dat[1] + z1.dat[1];
    return sum;
}
/*  End of tmpl_CFloat_Add.                                                   */

/*  Double precision complex addition.                                        */
tmpl_ComplexDouble
tmpl_CDouble_Add(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble sum;

    /*  The sum of two complex numbers simply adds their components.          */
    sum.dat[0] = z0.dat[0] + z1.dat[0];
    sum.dat[1] = z0.dat[1] + z1.dat[1];
    return sum;
}
/*  End of tmpl_CDouble_Add.                                                  */

/*  Long double precision complex addition.                                   */
tmpl_ComplexLongDouble
tmpl_CLDouble_Add(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble sum;

    /*  The sum of two complex numbers simply adds their components.          */
    sum.dat[0] = z0.dat[0] + z1.dat[0];
    sum.dat[1] = z0.dat[1] + z1.dat[1];
    return sum;
}
/*  End of tmpl_CLDouble_Add.                                                 */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */