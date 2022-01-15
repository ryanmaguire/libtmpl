/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                             tmpl_complex_rect                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for creating complex numbers.                *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 1, 2020                                              *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Create single precision complex numbers in Cartesian coordinates.         */
tmpl_ComplexFloat tmpl_CFloat_Rect(float x, float y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat z;

    /*  Simply set the array dat inside z to {x, y} and return.               */
    z.dat[0] = x;
    z.dat[1] = y;
    return z;
}
/*  End of tmpl_CFloat_Rect.                                                  */

/*  Create double precision complex numbers in Cartesian coordinates.         */
tmpl_ComplexDouble tmpl_CDouble_Rect(double x, double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble z;

    /*  Simply set the array dat inside z to {x, y} and return.               */
    z.dat[0] = x;
    z.dat[1] = y;
    return z;
}
/*  End of tmpl_CDouble_Rect.                                                 */

/*  Create long double precision complex numbers in Cartesian coordinates.    */
tmpl_ComplexLongDouble
tmpl_CLDouble_Rect(long double x, long double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble z;

    /*  Simply set the array dat inside z to {x, y} and return.               */
    z.dat[0] = x;
    z.dat[1] = y;
    return z;
}
/*  End of tmpl_CLDouble_Rect.                                                */
