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
 *                          tmpl_complex_cosh_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex hyperbolic cosine function.  *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Cosh                                                     *
 *  Purpose:                                                                  *
 *      Computes the complex hyperbolic cosine of a complex number.           *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      cosh_z (tmpl_ComplexDouble):                                          *
 *          The complex hyperbolic cosine of z.                               *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_SinCos:                                               *
 *              Computes sin(t) and cos(t) simultaneously.                    *
 *          tmpl_Double_SinhCosh:                                             *
 *              Computes sinh(t) and cosh(t) simultaneously.                  *
 *  Method:                                                                   *
 *      Given two real numbers x and y, we have the following formula:        *
 *                                                                            *
 *          cosh(x + iy) = cos(i(x + iy))                                     *
 *                       = cos(ix - y)                                        *
 *                       = cos(ix)cos(-y) - sin(ix)sin(-y)                    *
 *                       = cosh(x)cos(y) + i sinh(x)sin(y)                    *
 *                                                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Provides basic math routines.                                     *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/11/14: Ryan Maguire                                                  *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Added float and long double support.                                  *
 *  2023/07/10: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Greatly      *
 *      simplified code as well.                                              *
 ******************************************************************************/

/*  Trig and hyperbolic trig function.                                        */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and complex typedefs.                                  */
#include <libtmpl/include/tmpl_complex.h>

/*  Double precision complex hyperbolic cosine (ccosh equivalent).            */
tmpl_ComplexDouble tmpl_CDouble_Cosh(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double sin_y, cos_y, sinh_x, cosh_x;
    tmpl_ComplexDouble cos_z;

    /*  Compute (cos(y), sin(y)) and (cosh(x), sinh(x)), simultaneously.      */
    tmpl_Double_SinCos(z.dat[1], &sin_y, &cos_y);
    tmpl_Double_SinhCosh(z.dat[0], &sinh_x, &cosh_x);

    /*  Create the output and return.                                         */
    cos_z.dat[0] = cosh_x*cos_y;
    cos_z.dat[1] = sinh_x*sin_y;
    return cos_z;
}
/*  End of tmpl_CDouble_Cosh.                                                 */
