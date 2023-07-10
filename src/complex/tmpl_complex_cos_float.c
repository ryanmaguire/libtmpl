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
 *                           tmpl_complex_cos_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex cosine function.             *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Cos                                                       *
 *  Purpose:                                                                  *
 *      Computes the complex cosine of a complex number.                      *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat):                                                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      cos_z (tmpl_ComplexFloat):                                            *
 *          The complex cosine of z.                                          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_SinCos:                                                *
 *              Computes sin(t) and cos(t) simultaneously.                    *
 *          tmpl_Float_SinhCosh:                                              *
 *              Computes sinh(t) and cosh(t) simultaneously.                  *
 *  Method:                                                                   *
 *      Given two real numbers x and y, we have the following formula:        *
 *                                                                            *
 *          cos(x + y) = cos(x)cos(y) - sin(x)sin(y)                          *
 *                                                                            *
 *      We can then write:                                                    *
 *                                                                            *
 *          cos(z) = cos(x + iy) = cos(x)cos(iy) - sin(x)sin(iy)              *
 *                                                                            *
 *      Invoking the definition of the hyperbolic trig functions cosh and     *
 *      sinh, we obtain the following expression using real-valued functions: *
 *                                                                            *
 *          cos(z) = cos(x)cosh(y) - i sin(x)sinh(y)                          *
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
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/11/14: Ryan Maguire                                                  *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2023/07/10: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Greatly      *
 *      simplified code as well.                                              *
 ******************************************************************************/

/*  Trig and hyperbolic trig function.                                        */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and complex typedefs.                                  */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex cosine (ccosf equivalent).                       */
tmpl_ComplexFloat tmpl_CFloat_Cos(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float sin_x, cos_x, sinh_y, cosh_y;
    tmpl_ComplexFloat cos_z;

    /*  Compute (cos(x), sin(x)) and (cosh(y), sinh(y)), simultaneously.      */
    tmpl_Float_SinCos(z.dat[0], &sin_x, &cos_x);
    tmpl_Float_SinhCosh(z.dat[1], &sinh_y, &cosh_y);

    /*  Create the output and return.                                         */
    cos_z.dat[0] = cos_x*cosh_y;
    cos_z.dat[1] = -sin_x*sinh_y;
    return cos_z;
}
/*  End of tmpl_CFloat_Cos.                                                   */
