/******************************************************************************
 *                                  LICENSE                                   *
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
 *  Purpose:                                                                  *
 *      Function for multiplying a three vector by a real number.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 17, 2022                                                *
 ******************************************************************************/

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_ldouble.h>

/*  Multiply a three vector by a real number.                                 */
TMPL_INLINE_DECL
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Scale(long double a, const tmpl_ThreeVectorLongDouble * const P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorLongDouble scaled;

    /*  Scalar multiplication is done component-wise, so compute this.        */
    scaled.dat[0] = a*P->dat[0];
    scaled.dat[1] = a*P->dat[1];
    scaled.dat[2] = a*P->dat[2];
    return scaled;
}
/*  End of tmpl_3DDouble_Scale.                                               */
