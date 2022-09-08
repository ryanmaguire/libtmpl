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
 *                        tmpl_math_complex_add_inline                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inline version of the complex addition.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header file containing complex types.                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 8, 2022                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_COMPLEX_ADD_INLINE_H
#define TMPL_MATH_COMPLEX_ADD_INLINE_H

/*  Complex data types declared here.                                         */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision abs squared function.                                    */
static inline tmpl_ComplexFloat
tmpl_CFloat_Add(tmpl_ComplexFloat z0, tmpl_ComplexFloat z1)
{
    /*  Complex addition is done component-wise.                              */
    tmpl_ComplexFloat sum;
    sum.dat[0] = z0.dat[0] + z1.dat[0];
    sum.dat[1] = z0.dat[1] + z1.dat[1];
    return sum;
}
/*  End of tmpl_CFloat_Add.                                                   */

/*  Double precision abs squared function.                                    */
static inline tmpl_ComplexDouble
tmpl_CDouble_Add(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Complex addition is done component-wise.                              */
    tmpl_ComplexDouble sum;
    sum.dat[0] = z0.dat[0] + z1.dat[0];
    sum.dat[1] = z0.dat[1] + z1.dat[1];
    return sum;
}
/*  End of tmpl_CDouble_Add.                                                  */

/*  Long double precision abs squared function.                               */
static inline tmpl_ComplexLongDouble
tmpl_CLDouble_Add(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Complex addition is done component-wise.                              */
    tmpl_ComplexLongDouble sum;
    sum.dat[0] = z0.dat[0] + z1.dat[0];
    sum.dat[1] = z0.dat[1] + z1.dat[1];
    return sum;
}
/*  End of tmpl_CLDouble_Abs_Squared.                                         */

#endif
/*  End of include guard.                                                     */
